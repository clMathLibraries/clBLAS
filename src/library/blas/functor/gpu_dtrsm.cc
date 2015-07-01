#include <stdio.h>
#include <string.h>
#include <clBLAS.h>

#include <devinfo.h>
#include "clblas-internal.h"
#include "solution_seq.h"

#include "functor.h"
#include "binary_lookup.h"
#include <iostream>

#include "functor_xtrsm.h"
#include "gpu_dtrsm.h"
#include "tahiti.h"
#include "BinaryBuild.h"

#if BUILD_KERNEL_FROM_STRING
#include "dtrsm_gpu.clT"
#else

#include "dtrsm_gpu.clHawaii_64.bin.clT"


#include "dtrsm_gpu.clTahiti_64.bin.clT"
#endif


// Make it 1 to enable additional debug 'print' 
#define VERB 0


//TODO
//clReleaseKernel(kernel) ;

#define BLOCK_SIZE 16 // inner blocking size, <=32
#define NB 128        // outer blocking size, >BLOCK_SIZE


//
// The static cache used to store all instances of clblasDtrsmFunctorGpu /clblasDgemmFunctorTahiti 
//
typedef clblasFunctorCache<clblasDtrsmFunctorGpu, bool> Cache ;
static Cache cache  ;


clblasDtrsmFunctorGpu::clblasDtrsmFunctorGpu(Args & args,  cl_int & err, const char* DevName, cl_uint _64BitsUse)  :
  m_program(0)
{
  
  cl_device_id device;
  cl_context context;

  cl_command_queue queue = args.queue;
  err = getDeviceAndContext(queue, device, context);




  if( err != CL_SUCCESS )
  {
      return;
  }

  if (VERB) printf(" ===> GET KERNEL %s\n", "clblasDtrsmFunctorGpu") ;

  BinaryLookup bl(context, device, "clblasDtrsmFunctorGpu");

  if ( !bl.found() ) // may create empty file or may wait until file is ready  
  {
    // directly build from a char* 
#if BUILD_KERNEL_FROM_STRING
    err = bl.buildFromSource(dtrsm_gpu_kernels);
#else 
    if(!strcmp(DevName, "Tahiti"))
    {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
      if(_64BitsUse==64)
        err = bl.buildFromBinary(dtrsm_gpu_kernels_64_bin_Tahiti, sizeof(dtrsm_gpu_kernels_64_bin_Tahiti), NULL);
      else
      {
        std::cout<<"we don't support clblas on 32 bits"<< std::endl;
			  assert(1);
      }
#endif
    }

    else if(!strcmp(DevName, "Hawaii"))
    {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
      if(_64BitsUse==64)
        err = bl.buildFromBinary(dtrsm_gpu_kernels_64_bin_Hawaii, sizeof(dtrsm_gpu_kernels_64_bin_Hawaii), NULL);
      else
      {
        std::cout<<"we don't support clblas on 32 bits"<< std::endl;
        assert(1);
      }
#endif
    }

#endif
 
    if ( err != CL_SUCCESS )
    {  
      if (VERB) printf(" ===> BUILD PROBLEM\n") ;

      return;
    }
  }

  this->m_program = bl.getProgram();
}




#define CALL_KERNEL_TRIPLE_UPDATE(kernel_name, prg, queue, A, offA, d_dinvA, i, lda, M, event)   \
do{                                                                                              \
  err = call_kernel_triple_update(kernel_name, prg, queue, A, offA, d_dinvA, i, lda, M, event);  \
  if(err != CL_SUCCESS) {                                                                        \
    return err;                                                                                  \
  }                                                                                              \
} while(0)



cl_int call_kernel_triple_update(const char* kernel_name, 
                                 const cl_program prg,
                                 const cl_command_queue queue,
                                 cl_mem A,
                                 unsigned int offA,
                                 cl_mem d_dinvA,
                                 int i,
                                 unsigned int lda,
                                 int M, 
                                 cl_event *event)
{
  cl_int err = 0;

  unsigned int m = M; 

  int npages = M/(i*2)+(M%(i*2)!=0);
  size_t globalLocal  [2] = { (i <= 32)?(i/4):16, 4};
  size_t globalThreads[2] = { (i/(globalLocal[0]*globalLocal[1]))* globalLocal[0],
				npages*(i/16) * globalLocal[1]};

  cl_kernel kernel = clCreateKernel(prg, kernel_name, &err);
  if (err != CL_SUCCESS) {
    //printf( "create kernel %s failed with %d\n", kernel_name, err );
    return err;
  }

  clSetKernelArg(kernel, 0, sizeof(cl_mem), &A);
  clSetKernelArg(kernel, 1, sizeof(unsigned int), &offA);
  clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_dinvA);
  clSetKernelArg(kernel, 3, sizeof(int), &i);
  clSetKernelArg(kernel, 4, sizeof(unsigned int), &lda);
  clSetKernelArg(kernel, 5, sizeof(int), &npages);
  clSetKernelArg(kernel, 6, sizeof(unsigned int), &m);

  err = clEnqueueNDRangeKernel(queue, kernel, 2, NULL,
			       globalThreads, globalLocal , 
			       0, NULL, event);
  
 
  if (err != CL_SUCCESS) {
    clReleaseKernel(kernel);
    //printf( "execution of kernel %s failed with %d\n", kernel_name, err );
    return err;
  }

  err = clReleaseKernel(kernel);
  return err;

}




//extern "C"
cl_int diag_dtrtri (cl_program prg,
                    cl_command_queue queue,		  
                    int M, 
                    clblasUplo uplo, 
                    clblasDiag diag, 
                    cl_mem A, 
                    size_t offA,
                    cl_mem d_dinvA, 
                    size_t lda,
                    cl_event *event )
{

  cl_int err = 0;

  /*
    This routine is used in dtrsm
  */


  int nthreads = (M/BLOCK_SIZE + (M % BLOCK_SIZE != 0)) * BLOCK_SIZE;
  unsigned int m = M;
 
  if (uplo == clblasLower) {


    cl_kernel diag_dtrtri_kernel_lower = clCreateKernel(prg, "DIAG_DTRTRI_KERNEL_LOWER", &err);
    if (err != CL_SUCCESS) {
      //printf( "create kernel -diag_dtrtri_kernel_lower- failed with %d\n", err );
      return err;
    }

    int isDiagUnit = (diag == clblasUnit);
    clSetKernelArg(diag_dtrtri_kernel_lower, 0, sizeof(int), &isDiagUnit);
    clSetKernelArg(diag_dtrtri_kernel_lower, 1, sizeof(cl_mem), &A);
    clSetKernelArg(diag_dtrtri_kernel_lower, 2, sizeof(unsigned int), &offA);
    clSetKernelArg(diag_dtrtri_kernel_lower, 3, sizeof(cl_mem), &d_dinvA);
    clSetKernelArg(diag_dtrtri_kernel_lower, 4, sizeof(unsigned int), &lda);
    clSetKernelArg(diag_dtrtri_kernel_lower, 5, sizeof(unsigned int), &m);


    size_t globalThreads[1] = { nthreads };
    size_t globalLocal  [1] = { BLOCK_SIZE };
 
    err = clEnqueueNDRangeKernel(queue, diag_dtrtri_kernel_lower, 1, NULL,
				 globalThreads, globalLocal , 
				 0, NULL, event);

    if (err != CL_SUCCESS) {
      //printf( "kernel -diag_dtrtri_kernel_lower- failed with %d\n", err );
      return err;
    }

    err = clReleaseKernel(diag_dtrtri_kernel_lower);
    if (err != CL_SUCCESS) {
      return err;
    }


    // update the inverse up to the size of BLOCK_SIZE
    for( int i=BLOCK_SIZE; i < NB; i*=2 ) {

      switch (i) {
      case 16:
	CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_16_PART1_L", prg, queue, A, offA, d_dinvA, i, lda, M, event);
	CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_16_PART2_L", prg, queue, A, offA, d_dinvA, i, lda, M, event);
	break;

      case 32:
	CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_32_PART1_L", prg, queue, A, offA, d_dinvA, i, lda, M, event);
	CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_32_PART2_L", prg, queue, A, offA, d_dinvA, i, lda, M, event);
	break;

      case 64:
	CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_64_PART1_L", prg, queue, A, offA, d_dinvA, i, lda, M, event);
	CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_64_PART2_L", prg, queue, A, offA, d_dinvA, i, lda, M, event);
	break;

      default:
	CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_ABOVE64_PART1_L", prg, queue, A, offA, d_dinvA, i, lda, M, event);
	CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_ABOVE64_PART2_L", prg, queue, A, offA, d_dinvA, i, lda, M, event);
	CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_ABOVE64_PART3_L", prg, queue, A, offA, d_dinvA, i, lda, M, event);
	break;
	
      }
      if (i*2 >= M) break;
    }
    
  }
  else {

    cl_kernel diag_dtrtri_kernel_upper = clCreateKernel(prg, "DIAG_DTRTRI_KERNEL_UPPER", &err);
    if (err != CL_SUCCESS) {
      //printf( "create kernel -diag_dtrtri_kernel_upper- failed with %d\n", err );
      return err;
    }

    int isDiagUnit = (diag == clblasUnit);
    clSetKernelArg(diag_dtrtri_kernel_upper, 0, sizeof(int), &isDiagUnit);
    clSetKernelArg(diag_dtrtri_kernel_upper, 1, sizeof(cl_mem), &A);
    clSetKernelArg(diag_dtrtri_kernel_upper, 2, sizeof(unsigned int), &offA);
    clSetKernelArg(diag_dtrtri_kernel_upper, 3, sizeof(cl_mem), &d_dinvA);
    clSetKernelArg(diag_dtrtri_kernel_upper, 4, sizeof(unsigned int), &lda);
    clSetKernelArg(diag_dtrtri_kernel_upper, 5, sizeof(unsigned int), &m);

    size_t globalThreads[1] = { nthreads };
    size_t globalLocal  [1] = { BLOCK_SIZE };
 
    err = clEnqueueNDRangeKernel(queue, diag_dtrtri_kernel_upper, 1, NULL,
				 globalThreads, globalLocal , 
				 0, NULL, event);

    if (err != CL_SUCCESS) {
      //printf( "kernel -diag_dtrtri_kernel_upper- failed with %d\n", err );
      return err;
    }
 
    clReleaseKernel(diag_dtrtri_kernel_upper);
    if (err != CL_SUCCESS) {
      return err;
    }

    // update the inverse up to the size of BLOCK_SIZE
    for( int i=BLOCK_SIZE; i < NB; i*=2 ) {

      switch (i) {
      case 16:
	CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_16_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
	break;

      case 32:
	CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_32_PART1_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
	CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_32_PART2_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
	break;

      case 64:
	CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_64_PART1_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
	CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_64_PART2_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
	break;

      default:
	CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_ABOVE64_PART1_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
	CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_ABOVE64_PART2_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
	CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_ABOVE64_PART3_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);

	break;
      }
      
      if (i*2 >= M) break;
    }
    
  }

  return err;

}




#define check_error(cmd)                   \
do{                                        \
  cl_int xxxerr = cmd ;                    \
  if (xxxerr != CL_SUCCESS) {              \
    if(InvA != 0)                          \
      clReleaseMemObject(InvA);            \
    if(X != 0)                             \
      clReleaseMemObject(X);               \
    return xxxerr;                         \
  }                                        \
} while(0)


static cl_int clearBuffer( cl_command_queue  queue ,
                           cl_mem  buffer ,
                           size_t  buffer_size )
{
  
  cl_int err = 0;
  cl_event  event; 
  // Hummm clEnqueueFillBuffer is OpenCL 1.2 !!! 
  double zero = 0.0 ; 
  err = clEnqueueFillBuffer(queue, 
                            buffer, 
                            &zero, 
                            sizeof(double), 
                            0,  // offset 
                            buffer_size, 
                            0,
                            NULL, 
                            &event 
                            ) ;

  return err;

}



#define nb 128        // outer blocking size, >BLOCK_SIZE
#define min(x,y) ((x)<(y)?(x):(y))



cl_int cl_dtrsm( cl_program prg,
                 cl_command_queue  queue , 
                 clblasSide side, 
                 clblasUplo uplo, 
                 clblasTranspose transA, 
                 clblasDiag diag, 
                 int M, 
                 int N,
                 double alpha,
                 cl_mem A, size_t offA, size_t ldA,
                 cl_mem B, size_t offB, size_t ldB,
                 cl_event *event
                 ) 
{
  cl_int err = 0;

  int i;
  cl_context context;
  err = getQueueContext(queue, &context);
  if(err != CL_SUCCESS) return err;

  /* quick return on wrong size */
  if (M <= 0 || N <= 0)
    return clblasInvalidDim;
    
  double neg_one = -1.0 ;
  double one     =  1.0 ;
  double zero    =  0.0 ; 



  // Compute the number of blocks of the specified 'size' to fully cover 'n' 
  // Simply speaking, this is n/size rounded up.
#define BLOCKS(n,size) ( ( (n) / size ) + ( (n) % (size) != 0 ) )

#define CLEANUP   

#define END_DGEMM_ARGS 1,&queue,0,NULL,event

  // Helper to compute pass the 3 arguments describing a (sub)-matrix to clblasDgemm 
#define _(M,i,j)       M    , (off##M + ((i)+(j)*ld##M) ) , ld##M 

  cl_mem InvA = 0;
  cl_mem X    = 0;
  // X of size mxn  will contain the result 
  size_t ldX = M ; 
  size_t offX = 0; //must be 0: needed by the _(X,i,j) macro
  size_t size_X = N*ldX * sizeof(double);
  X = clCreateBuffer(context, CL_MEM_READ_WRITE, size_X, NULL, &err);
  check_error(err) ;         
  err = clearBuffer( queue, X, size_X ) ;
  check_error(err) ; 


  if (side == clblasLeft) 
    {
      // side=L
      /* invert the diagonals
       * Allocate device memory for the inverted diagonal blocks, size=m*nb
       */
      size_t ldInvA = nb ; 
      size_t offInvA = 0; //must be 0: needed by the _(X,i,j) macro
      size_t size_InvA = ldInvA * BLOCKS(M,nb) * nb *sizeof(double); 
      InvA = clCreateBuffer(context, CL_MEM_READ_WRITE, size_InvA, NULL, &err);

      check_error(err) ;         
      err = clearBuffer( queue, InvA, size_InvA ) ;
      check_error(err) ; 

      diag_dtrtri (prg, queue, M, uplo, diag, A, offA, InvA, ldA, event);

      //
      // Helper for C = alpha * transp(A) * B + beta * C         
      //
      // In the calls below:
      //   - the 1st matrix shall be either A or InvA transposed according to transA.
      //   - the 2nd and 3rd matrices are either B and X 
      // 
#define DGEMM_LEFT(m, n, k, alpha, A,  B, beta,  C) \
    do { \
        err = clblasDgemm(clblasColumnMajor, transA, clblasNoTrans , m, n, k, alpha, A, B, beta, C , 1, &queue, 0, NULL, event ) ; \
        check_error(err) ; \
    } while(0) 


      if (transA == clblasNoTrans) 
        {
          /* the non-transpose case */
          if (uplo == clblasLower) 
            {
              
              /* the lower case */
              /* handle the first block seperately with alpha */
              int mm = min(nb, (int) M);
              DGEMM_LEFT( mm, N, mm, alpha, _(InvA,0,0) , _(B,0,0),  zero, _(X,0,0) );

              if (nb < M) 
                {
                  DGEMM_LEFT( M-nb, N, nb, neg_one, _(A,nb,0), _(X,0,0), alpha, _(B,nb,0)  );
                  
                  /* the rest blocks */
                  for( i=nb; i < M; i += nb ) {
                    mm = min((int)M-i, nb);
                    DGEMM_LEFT( mm, N, mm, one, _(InvA,0,i), _(B,i,0), zero, _(X,i,0) );
                    
                    if (i+nb >= M)
                      break;
                    
                    DGEMM_LEFT( M-i-nb, N, nb, neg_one, _(A,i+nb,i), _(X,i,0), one, _(B,i+nb,0) );
                  }
                  
                  //check_last_error() ; 
                }


            }
          else // if ( uplo == clblasUpper) 
            {
             /* the upper case */
              /* handle the first block seperately with alpha */
              int mm = (M % nb == 0) ? nb : (M % nb);
              i = M-mm;
              DGEMM_LEFT( mm, N, mm, alpha, _(InvA,0,i), _(B,i,0), zero, _(X,i,0) );

              if (i-nb >= 0)
                {                 
                  DGEMM_LEFT( i, N, mm, neg_one, _(A,0,i), _(X,i,0), alpha, _(B,0,0) );

                  /* the rest blocks */
                  for( i=M-mm-nb; i >= 0; i -= nb ) {
                    DGEMM_LEFT( nb, N, nb, one, _(InvA,0,i), _(B,i,0), zero, _(X,i,0) );

                    if (i-nb < 0)
                      break;

                    DGEMM_LEFT( i, N, nb, neg_one, _(A,0,i), _(X,i,0), one, _(B,0,0) );
                  }
                }
            }
        }
      else 
        {
          /* the transpose case */
          if (uplo == clblasLower) 
            {
              /* the lower case */
              /* handle the first block seperately with alpha */

              int mm = (M % nb == 0) ? nb : (M % nb);
              i = M-mm;
              DGEMM_LEFT(  mm, N, mm, alpha, _(InvA,0,i), _(B,i,0), zero, _(X,i,0) );

              if (i-nb >= 0)
                {
                  DGEMM_LEFT(  i, N, mm, neg_one, _(A,i,0), _(X,i,0), alpha, _(B,0,0)  );
                  
                  /* the rest blocks */
                  for( i=M-mm-nb; i >= 0; i -= nb ) {
                    DGEMM_LEFT(  nb, N, nb, one, _(InvA,0,i), _(B,i,0), zero, _(X,i,0)  );
                    
                    if (i-nb < 0)
                      break;
                    
                    DGEMM_LEFT( i, N, nb, neg_one, _(A,i,0), _(X,i,0), one, _(B,0,0)  );
                  }
                }
            }
          else 
            {
              /* the upper case */
              /* handle the first block seperately with alpha */
              int mm = min(nb, (int)M);
              DGEMM_LEFT( mm, N, mm, alpha, _(InvA,0,0), _(B,0,0), zero, _(X,0,0) );

              if (nb < M) 
                {
                 
                  DGEMM_LEFT( M-nb, N, nb, neg_one, _(A,0,nb) , _(X,0,0), alpha, _(B,nb,0)  );

                  /* the rest blocks */
                  for( i=nb; i < M; i += nb ) {
                    mm = min((int)M-i, nb);
                    DGEMM_LEFT( mm, N, mm, one, _(InvA,0,i), _(B,i,0), zero, _(X,i,0) );

                    if (i+nb >= M)
                      break;

                    DGEMM_LEFT( M-i-nb, N, nb, neg_one, _(A,i,i+nb), _(X,i,0), one, _(B,i+nb,0)  );
                  }
                }
            }
        }
    }
  else 
    {

      //
      // Helper for C = alpha * B * A + beta * C        
      //
      // In the calls below
      //  - the 2nd matrix shall be either A or InvA transposed according to transA
      //  - the 1st and 3rd matrices are either B and X
      //
#define DGEMM_RIGHT(m,n,k, alpha,  B, A, beta, C )   \
    do { \
      err = clblasDgemm(clblasColumnMajor, clblasNoTrans, transA , m, n, k, alpha, B, A, beta, C , 1, &queue, 0, NULL, event ) ; \
      check_error(err) ; \
    } while(0) 


      // side=R
      /* invert the diagonals
       * Allocate device memory for the inverted diagonal blocks, size=n*BLOCK_SIZE
       */
      
      /* invert the diagonals
       * Allocate device memory for the inverted diagonal blocks, size=m*nb
       */
      size_t ldInvA = nb ; 
      size_t offInvA = 0; //must be 0: needed by the _(X,i,j) macro
      size_t size_InvA = ldInvA * BLOCKS(N,nb) * nb *sizeof(double); 
      InvA = clCreateBuffer(context, CL_MEM_READ_WRITE, size_InvA, NULL, &err);
      check_error(err) ;         
      err = clearBuffer( queue, InvA, size_InvA ) ;
      check_error(err) ; 

      diag_dtrtri (prg, queue, N, uplo, diag, A, offA, InvA, ldA, event);

      if (transA == clblasNoTrans) 
        {
          /* the non-transpose case */
          if (uplo == clblasLower) 
            {
              /* the lower case */
              /* handle the first block seperately with alpha */

              int nn = (N % nb == 0) ? nb : (N % nb);
              i = N-nn;
              DGEMM_RIGHT(  M, nn, nn, alpha, _(B,0,i), _(InvA,0,i), zero, _(X,0,i) );

              if (i-nb >= 0)
                {
                 
                  DGEMM_RIGHT(  M, i, nn, neg_one, _(X,0,i), _(A,i,0), alpha, _(B,0,0) );

                  /* the rest blocks */
                  for( i=N-nn-nb; i >= 0; i -= nb ) {
                    DGEMM_RIGHT(  M, nb, nb, one, _(B,0,i), _(InvA,0,i), zero, _(X,0,i) );
                    
                    if (i-nb < 0)
                      break;
                    
                    DGEMM_RIGHT(  M, i, nb, neg_one, _(X,0,i), _(A,i,0), one, _(B,0,0) );
                  }
                }
            }
          else 
            {
              /* the upper case */
              /* handle the first block seperately with alpha */
              int nn = min(nb, (int)N);
              DGEMM_RIGHT(  M, nn, nn, alpha, _(B,0,0), _(InvA,0,0), zero, _(X,0,0) );

              if (nb < N)
                {
                  
                  DGEMM_RIGHT(  M, N-nb, nb, neg_one, _(X,0,0), _(A,0,nb), alpha, _(B,0,nb)  );
                  
                  /* the rest blocks */
                  for( i=nb; i < N; i += nb ) {
                    nn = min(nb, (int)N-i);
                    DGEMM_RIGHT(  M, nn, nn, one, _(B,0,i), _(InvA,0,i), zero, _(X,0,i) );
                    
                    if (i+nb >= N)
                      break;
                    
                    DGEMM_RIGHT(  M, N-i-nb, nb, neg_one, _(X,0,i),   _(A,i,i+nb), one, _(B,0,i+nb)  );
                  }
                }
            }
        }
      else 
        {

          /* the transpose case */
          if (uplo == clblasLower) 
            {
              /* the lower case */
              /* handle the first block seperately with alpha */

              int nn = min(nb, (int)N);
              DGEMM_RIGHT(  M, nn, nn, alpha, _(B,0,0), _(InvA,0,0), zero, _(X,0,0) );

              if (nb < N) 
                {
                  
                  DGEMM_RIGHT(  M, N-nb, nb, neg_one, _(X,0,0), _(A,nb,0), alpha, _(B,0,nb)  );
                  
                  /* the rest blocks */
                  for( i=nb; i < N; i += nb ) {
                    nn = min(nb, (int)N-i);
                    DGEMM_RIGHT(  M, nn, nn, one, _(B,0,i), _(InvA,0,i), zero, _(X,0,i) );
                    
                    if (i+nb >= N)
                      break;
                    
                    DGEMM_RIGHT(  M, N-i-nb, nb, neg_one, _(X,0,i),  _(A,nb+i,i), one, _(B,0,i+nb) );
                  }
                }
            }
          else 
            {
              /* the upper case */
              /* handle the first block seperately with alpha */
              int nn = (N % nb == 0) ? nb : (N % nb);
              i = N-nn;
              DGEMM_RIGHT(  M, nn, nn, alpha, _(B,0,i), _(InvA,0,i), zero, _(X,0,i) );

              if (i-nb >= 0)
                {
                 
                  DGEMM_RIGHT(  M, i, nn, neg_one, _(X,0,i), _(A,0,i), alpha, _(B,0,0) );

                  /* the rest blocks */
                  for( i=N-nn-nb; i >= 0; i -= nb ) {
                    DGEMM_RIGHT(  M, nb, nb, one, _(B,0,i), _(InvA,0,i), zero, _(X,0,i) );

                    if (i-nb < 0)
                      break;

                    DGEMM_RIGHT(  M, i, nb, neg_one, _(X,0,i), _(A,0,i), one, _(B,0,0) );
                  }
                }
            }
        }
      
    }

  // Copy X(m,n) to B(m,n)
  {     
    size_t src_origin[3] = { 0, 0, 0 } ;
    size_t dst_origin[3] = { offB*sizeof(double), 0, 0 } ;
    size_t region[3]     = { M*sizeof(double), N, 1 } ;
    

    err =  clEnqueueCopyBufferRect( queue,
                                    X,
                                    B,
                                    src_origin,
                                    dst_origin,
                                    region,
                                    ldX*sizeof(double), 0,  
                                    ldB*sizeof(double), 0,  
                                    0, NULL,
                                    event) ;
    check_error(err) ;         

    clReleaseMemObject(InvA);
    clReleaseMemObject(X);

  }

  return err;

}



clblasStatus clblasDtrsmFunctorGpu::execute(Args &args) 
{
  cl_int err;
  cl_command_queue queue = args.queue;

  if (VERB) printf(" ===> EXECUTE KERNEL %s\n", "dtrsm_gpu") ;

  
  cl_program prg = this->m_program;
  

  err = cl_dtrsm( prg,
                  queue , 
                  args.side, 
                  args.uplo, 
                  args.transA, 
                  args.diag, 
                  args.M, 
                  args.N,
                  args.alpha,
                  args.A, args.offA, args.lda,
                  args.B, args.offB, args.ldb,
                  args.events
                  );



  if (VERB) printf(" ===> ERR=%d \n",(int)err) ;

  return clblasStatus(err) ;
}



clblasDtrsmFunctorGpu * 
clblasDtrsmFunctorGpu::provide(clblasDtrsmFunctor::Args & args , const char* DevName) 
{

  if ( args.order == clblasRowMajor ) 
    return NULL ;   // The RowMajor case shall never occur. 


  cl_device_id dev;
  cl_context   ctxt;

  cl_int err = getDeviceAndContext(args.queue, dev, ctxt);

  if (err != CL_SUCCESS)
  {
      return NULL;
  }
  cl_uint bitness = getAddressBits(dev);
  Cache::Lookup lookup(cache, ctxt, dev, true) ;

  if ( lookup.ok() ){
    clblasDtrsmFunctorGpu * functor = lookup.get();
    functor->retain(); // increment the reference counter to avoid deletion while it is still beeing used
    return functor;
  }
 
  clblasDtrsmFunctorGpu * functor = new clblasDtrsmFunctorGpu(args, err, DevName, bitness);
  if (err != CL_SUCCESS)
  {
      return NULL;
  }

  lookup.set(functor) ;

  return functor;
    
}

