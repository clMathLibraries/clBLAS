/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_DIAG_DTRTRI_UPPER_128_16_SRC_CPP
#define KERNEL_DIAG_DTRTRI_UPPER_128_16_SRC_CPP
#pragma message("#define KERNEL_DIAG_DTRTRI_UPPER_128_16_SRC_CPP.")

#ifndef STRINGIFY
#define STRINGIFY2(...) #__VA_ARGS__
#define STRINGIFY(...) STRINGIFY2(__VA_ARGS__)
#endif

unsigned char *diag_dtrtri_upper_128_16_bin = 0;
size_t diag_dtrtri_upper_128_16_binSize = 0;

const char * const diag_dtrtri_upper_128_16_src = STRINGIFY(
#define BLOCK_SIZE 16 \n
#define NB 128 \n
#define ZERO              ( 0.0) \n
#define ONE               ( 1.0) \n
#ifdef DOUBLE_PRECISION \n
#ifdef cl_khr_fp64 \n
#pragma OPENCL EXTENSION cl_khr_fp64 : enable \n
#else \n
#pragma OPENCL EXTENSION cl_amd_fp64 : enable \n
#endif \n
#endif \n
__kernel void diag_dtrtri_upper_128_16_src(\n
int  isDiagUnit,\n
__global double const * restrict A, \n
uint offA, \n
__global double *d_dinvA, \n
uint lda, \n
uint na)\n
{ \n
  int i, j;\n
  double Ystx = 0;\n
  __local double *y = 0;\n
  double switcher;\n
  double neg_switcher;\n

  // Thread index
  int tx = get_local_id(0);\n

  // Thread index
  int gx = get_global_id(0);\n

  // Block index
  int bx = get_group_id(0);\n

  A = A + offA;\n

  __global const double *Aoff = A + bx*lda*BLOCK_SIZE + bx*BLOCK_SIZE;\n
  int NumBLperNB = NB/BLOCK_SIZE;\n
  d_dinvA += bx/NumBLperNB*NB*NB + (bx % NumBLperNB)*(NB*BLOCK_SIZE + BLOCK_SIZE);\n

  __local double Bs[BLOCK_SIZE*BLOCK_SIZE];\n
  __local double workspace[BLOCK_SIZE]; \n   // workspace used to store the current working column

  // load A
  _Pragma("unroll")\n
  for( i=0; i < BLOCK_SIZE; i++ )\n
    {\n
      if(tx <= i && i+bx*BLOCK_SIZE < na )\n
        {\n
	  Bs[i*BLOCK_SIZE+tx] = *(Aoff+i*lda+tx);\n    
        }\n
      else\n
        {\n
	  Bs[i*BLOCK_SIZE+tx] = ZERO;\n
        }\n
    }\n 
  // read in the whole square block of my A and zero out the non data triangular
 
  // Synchronize to make sure the matrices are loaded
  //__syncthreads(); 
  barrier(CLK_LOCAL_MEM_FENCE);\n

  // solve the diagonals

   if(isDiagUnit == 1)\n
    {\n
      Bs[tx*BLOCK_SIZE+tx] = ONE;\n
    }\n
  else\n
    {\n
      if( Bs[tx*BLOCK_SIZE+tx] == ZERO )\n
	{\n
	  Bs[tx*BLOCK_SIZE+tx] = ONE; \n
	}\n
      else \n
	{\n
	  Bs[tx*BLOCK_SIZE+tx] = ONE / ( Bs[tx*BLOCK_SIZE+tx]) ;\n
	}\n      
    }\n
    barrier(CLK_LOCAL_MEM_FENCE);\n

	  /* the upper case */
  for( i=0; i < BLOCK_SIZE; i++ ) {\n
    Ystx =  ZERO;\n
    if( tx < i)\n
      {\n
	switcher = ONE;\n
      }\n
    else\n
      {\n
	switcher = ZERO;\n
      }\n

    //dtrmv
    workspace[tx] = *(Bs+i*BLOCK_SIZE+tx);\n
    y = Bs+i*BLOCK_SIZE;\n
    barrier(CLK_LOCAL_MEM_FENCE);\n

    _Pragma("unroll")\n
    //for( j=tx; j < i; j++ )
    for( j=0; j < i; j++ )\n
	{\n
      Ystx += switcher * (*(Bs+j*BLOCK_SIZE+tx)*workspace[j]);\n
	}\n

    //sscal
    // if (tx != i) y[tx]=switcher*Ystx*(-Bs[i*BLOCK_SIZE+i]);

    if( tx != i)\n
      {\n
	switcher = ONE;\n
	neg_switcher =  ZERO;\n
      }\n
    else\n
      {\n
	switcher = ZERO;\n
	neg_switcher =  ONE;\n
      }\n

    y[tx] = switcher *Ystx*(-Bs[i*BLOCK_SIZE+i])+neg_switcher*y[tx];\n

    // __syncthreads();
    barrier(CLK_LOCAL_MEM_FENCE);\n
  }\n
  
    // write back A
  _Pragma("unroll")\n
  for( i=0; i < BLOCK_SIZE; i++ )\n
  {\n
    *(d_dinvA+i*NB+tx) = Bs[i*BLOCK_SIZE+tx];\n
  }\n
  
}\n
// end of kernel
);
#endif
