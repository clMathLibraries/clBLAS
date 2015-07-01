#if !defined CLBLAS_HAWAII_DYNAMIC_KERNEL || !defined CLBLAS_BONAIRE_DYNAMIC_KERNEL
//this split kernel algorithm solves the main matrix with 64x64 micro tile size
//solves the row boundry with 32x64 micro tile size
//solves the column boundry with 64x32 micro tile size
//solves the rest boundry with 32x32 micro tile size
//assumption : after the main matrix being computed by kernels with 64x64 micro tile size, the boundary are of size 32.
//in other words, M and N are mod32 and not mod64
#include <stdio.h>
#include <string.h>
#include <clBLAS.h>

#include <devinfo.h>
#include "clblas-internal.h"
#include "solution_seq.h"

#include <functor.h>
#include <binary_lookup.h>
#include <iostream>

#include <functor_xgemm.h>
#include <tahiti.h>
#include <hawaii.h>

#include "BinaryBuild.h"
#include "hawaii_sgemmSplit64_32.h"


#if BUILD_KERNEL_FROM_STRING
//#include "sgemm_hawaiiSplitKernel.clT"
#else 

#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
#include "sgemm_hawaiiSplit64_32.clHawaii_64.bin.clT"
#include "sgemm_gcn.clHawaii_64.bin.clT"
#endif//CLBLAS_HAWAII_DYNAMIC_KERNEL

#ifndef CLBLAS_BONAIRE_DYNAMIC_KERNEL
//#include "sgemm_hawaiiSplitKernel.clBonaire_64.bin.clT"
#endif //CLBLAS_BONAIRE_DYNAMIC_KERNEL

#endif //BUILD_KERNEL_FROM_STRING

// Just because the full name is too long
typedef clBlashawaiiSgemmSplit64_32Functor::Variant Variant;

//define the string name of the soure/binary code
#define SGEMM_SRC_NAME(TA,TB, DIVK, MULT)    sgemm_##TA##TB##_##DIVK##_SPLIT##MULT
#define SGEMM_SRC_NAME_HAWAII(TA,TB, DIVK, MULT, BITS)   sgemm_##TA##TB##_##DIVK##_SPLIT##MULT##_##BITS##_bin_Hawaii
#define SGEMM_SRC_NAME_BONAIRE(TA,TB, DIVK, MULT, BITS)   sgemm_##TA##TB##_##DIVK##_SPLIT##MULT##_##BITS##_bin_Bonaire
#define SGEMM_SRC_NAME_BIN(TA,TB, DIVK, MULT, BITS, DEVICE)   SGEMM_SRC_NAME##_##DEVICE(TA,TB, DIVK, MULT, BITS)


//variant name used to differentiate the different ones
#define SGEMM_VARIANT_NAME(TA,TB, DIVK, MULT) "sgemm_" #TA #TB "_" #DIVK "_SPLIT64_32" #MULT
//SGEMM_VARIANT_NAME(TA, TB, DIVM , DIVN, DIVK, GREATER48M, GREATER48N, NBKERNEL),    

#define SGEMM_KERNEL_NAME(TA,TB,DIVM,DIVN,DIVK,BS0,BS1,NV0,NV1,MULT, BLOC) "sgemm_"  #TA #TB "_" #DIVM "_" #DIVN "_" #DIVK "_" #BS0 "x" #BS1 "_" #NV0 "x" #NV1 #MULT "_SPLIT_" #BLOC


#define trans_N clblasNoTrans
#define trans_T clblasTrans

// Fill a variant descriptor using OpenCL source 
#define SGEMM_VARIANT_OBJ(TA,TB,DIVK,BS0,BS1,NV0,NV1, BITS, MULT,  \
  KERNEL_NAME_MAIN, KERNEL_NAME_ROW, KERNEL_NAME_COLUMN, KERNEL_NAME_SINGLE, \
  KERNELS_SRC,  \
  KERNEL_BUILD_OPTIONS,  \
  KERNELS_BIN,  \
  KERNEL_BIN_SIZE) { \
  SGEMM_VARIANT_NAME(TA,TB, DIVK, MULT),                                          \
{ KERNEL_NAME_MAIN, KERNEL_NAME_ROW, KERNEL_NAME_COLUMN, KERNEL_NAME_SINGLE } , \
  KERNELS_SRC,  \
  KERNEL_BUILD_OPTIONS, \
  KERNELS_BIN, \
  KERNEL_BIN_SIZE, \
  trans_##TA, trans_##TB,                                       \
  DIVK ,                                                        \
{ BS0, BS1 } ,                                                \
{ NV0, NV1 } ,                                                      \
#MULT                                                               \
} 

typedef clblasFunctorCache<clBlashawaiiSgemmSplit64_32Functor, const Variant *> CacheSplit;
static CacheSplit cachesplit  ;

// Make it 1 to enable additional debug 'print' 
#define VERB 0



//static bool applicable( const Variant & var, clblasSgemmFunctor::Args & args, int RefMultiple ) 
//{
//#if 0
//  // Transpose values are tested in select_variant
//  if ( args.transA != var.transA ) return false ;
//  if ( args.transB != var.transB ) return false ;
//#endif
//
//  //if (args.N>=var.divN && args.N % var.divN != 0 )
//  if ( args.N % var.divN != 0 ) 
//    return false ; 
//  if ( args.M % var.divM != 0 ) 
//    return false ; 
//  if(var.Greater[0]?args.M<RefMultiple:args.M>=RefMultiple)
//    return false;
//  if(var.Greater[1]?args.N<RefMultiple:args.N>=RefMultiple)
//    return false;
//  if ( args.beta==0 && var.mult.compare("__ALPHA")!=0)
//    return false ;
//  return true ;
//}

static void to_upper(char* input)
{
  while(*input)
  {
    *input=toupper(*input);
    input++;
  }
}


static const Variant * select_variant_SplitKernel( clblasSgemmFunctor::Args & args, const char* DevName, cl_uint _64BitsUse )
{
  if(_64BitsUse!=64)
  {
    std::cout<<"we don't support clblas on 32 bits"<< std::endl;
    assert(1);
    return NULL;
  }


  if ( args.transA == clblasNoTrans ) 
  {
    if ( args.transB == clblasNoTrans ) 
    {

      // ===== sgemm NN ======
	  // NN not implemented yet
      return NULL;


    }
    if (args.transB == clblasTrans)
    {

      const char* KName_NTMain = "sgemm_NT_64_64_16_16x16_4x4__ALPHABETA_SPLIT_MAIN" ;
      const char* KName_NTRow = "sgemm_NT_32_64_16_16x16_2x4__ALPHABETA_SPLIT_ROW" ;
      const char* KName_NTColumn = "sgemm_NT_64_32_16_16x16_4x2__ALPHABETA_SPLIT_COLUMN" ;
      const char* KName_NTSingleWave = "sgemm_NT_32_32_16_16x16_2x2__ALPHABETA_SPLIT_SINGLE" ;



      const char* KBin_NTMain64 ;           
      size_t KBin_NTMainSize64 = 0;       




      if (!strcmp(DevName, "Hawaii"))
      {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        //KBin_NTMain64             = SGEMM_SRC_NAME_BIN(N, T, 16, __ALPHABETA,  64, HAWAII) ;
        //KBin_NTMainSize64        = sizeof(SGEMM_SRC_NAME_BIN(N, T, 16, __ALPHABETA,  64, HAWAII)) ;
		  KBin_NTMain64 = sgemm_NT_64_32_SPLIT__ALPHABETA_64_bin_Hawaii;
		  KBin_NTMainSize64 = sizeof(sgemm_NT_64_32_SPLIT__ALPHABETA_64_bin_Hawaii);

#endif //CLBLAS_HAWAII_DYNAMIC_KERNEL
      }

      else if (!strcmp(DevName, "Bonaire"))
      {
#ifndef CLBLAS_BONAIRE_DYNAMIC_KERNEL
       //not implemented for Bonaire yet
#endif //#ifndef CLBLAS_BONAIRE_DYNAMIC_KERNEL
      }


      // ===== SGEMM NT ======


          static const Variant variant = SGEMM_VARIANT_OBJ(N,T,16,16,16,4,4,64,__ALPHABETA, 
            KName_NTMain,KName_NTRow, KName_NTColumn, KName_NTSingleWave ,
            NULL,
            NULL,
            KBin_NTMain64,
            KBin_NTMainSize64) ;

          return &variant ; 

    }
  }
  else
  {
    // TN and TT are not implemented yet
	return NULL;
  }

  return NULL;
}

clBlashawaiiSgemmSplit64_32Functor::clBlashawaiiSgemmSplit64_32Functor(Args & args, const Variant * variant, cl_int & err)
{

  cl_device_id device;
  cl_context context;
  m_program=NULL;
  m_variantSplit = variant;


  cl_command_queue queue = args.queue;
  err = getDeviceAndContext(queue, device, context);
  if( err != CL_SUCCESS )
  {
    return;
  }

  if (VERB) printf(" ===> GET KERNEL %s\n", this->m_variantSplit->variantName) ;

  //Ben do I use the correct "kernel_name"?
  BinaryLookup bl(context, device, "clBlashawaiiSgemmSplitKernelFunctor");

  bl.variantRaw( this->m_variantSplit->variantName, strlen(this->m_variantSplit->variantName)+1 ) ;

  if ( !bl.found() ) // may create empty file or may wait until file is ready  
  {
    if ( this->m_variantSplit->bin != NULL ) 
    {
      // build from a pre-compiled version of the kernel (SPIR or cl binaries)
      //only 1 binary containing all the kernel
      err = bl.buildFromBinary(this->m_variantSplit->bin, this->m_variantSplit->bin_size, /*this->m_variantSplit->build_options[i]*/ "-cl-std=2.0");
    }
    else
    {
      //// directly build from a char* 
      //for (int i=0; i<4; i++)
      //  if(this->m_variantSplit->source[i] != 0)
      //    err = bl.buildFromSource(this->m_variantSplit->source[i]);
      if (VERB) printf(" ===> BUILD PROBLEM WE DON'T SUPPORT SOURCE BUILD FOR SPLIT SGEMM\n") ;
      return;
    } 

    if ( err != CL_SUCCESS )
    {  
      if (VERB) printf(" ===> BUILD PROBLEM\n") ;

      return;
    }
  }

  this->m_program = bl.getProgram();
}



clBlashawaiiSgemmSplit64_32Functor *
clBlashawaiiSgemmSplit64_32Functor::provide(clblasSgemmFunctor::Args & args, char* DevName)
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

  int major;
  int minor;

  getCLVersion(dev, major, minor);

  //if (major<2)
  //  return NULL;

  // to_upper( DevName);
  const Variant * variant = select_variant_SplitKernel( args, DevName, bitness ) ;
  if ( variant == NULL )  
    return NULL ; 



  CacheSplit::Lookup lookup(cachesplit, ctxt, dev, variant) ;


  if ( lookup.ok() )
  {
	clBlashawaiiSgemmSplit64_32Functor * functor = lookup.get();
    functor->retain(); // increment the reference counter to avoid deletion while it is still beeing used
    return functor;
  }

  clBlashawaiiSgemmSplit64_32Functor * functor = new clBlashawaiiSgemmSplit64_32Functor(args, variant, err);
  if (err != CL_SUCCESS)
  {
    return NULL;
  }

  lookup.set(functor) ;

  return functor;

}


cl_int clBlashawaiiSgemmSplit64_32Functor::KernelsLaunch(cl_command_queue queue, cl_kernel Kernel[4], Args &args)
{
  //GlobalX = ((Mvalue - 1) / 64) * 16
  //GlobalY = ((Nvalue - 1) / 64) * 16
  size_t GlobalX = ((args.M - 1) / (m_variantSplit->bwi[0] * m_variantSplit->ls[0])) * 16;
  size_t GlobalY = ((args.N - 1) / (m_variantSplit->bwi[1] * m_variantSplit->ls[1])) * 16;


  std::size_t gs[2] = {GlobalX, GlobalY};
  cl_int error = 0;
  //M and N are not mod64 and are mod32 
  if (args.M % 64 != 0 && args.N % 64 != 0 && args.M % 32 == 0 && args.N % 32 == 0 && args.M >= 64 && args.N >= 64)
  {
    if (VERB) printf(" ===> EXECUTE KERNEL 0, 1, 2, 3 \n") ;
    error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList,NULL);

    gs[0] = 16;
    error |= clEnqueueNDRangeKernel(queue, Kernel[1], 2, NULL, gs, m_variantSplit->ls, 0, NULL,NULL);

    gs[1] = 16;
    gs[0] = GlobalX;
    error |= clEnqueueNDRangeKernel(queue, Kernel[2], 2, NULL, gs, m_variantSplit->ls, 0, NULL,NULL);

    gs[0] = 16; gs[1] = 16;
    error |= clEnqueueNDRangeKernel(queue, Kernel[3], 2, NULL, gs, m_variantSplit->ls, 0, NULL,args.events);
    return error;
  }


  return clblasNotImplemented;
}



clblasStatus clBlashawaiiSgemmSplit64_32Functor::execute(Args &args)
{
  cl_int err;
  cl_command_queue queue = args.queue;

  if (VERB) printf(" ===> EXECUTE KERNEL %s, alpha =%f ,beta = %f\n", this->m_variantSplit->kernel_name, args.alpha, args.beta) ;

  cl_kernel kernel[4]; 
  int NBKernel = 0;

  for (int i=0; i<4; i++)
  {
    if (this->m_variantSplit->kernel_name[i])
    {
      kernel[i ]= clCreateKernel( this->m_program, this->m_variantSplit->kernel_name[i],  &err);
      if (err != CL_SUCCESS)
        return clblasStatus(err) ; 
      NBKernel++;
    }
    else
      break;
  }

  if (NBKernel != 4) return clblasStatus(clblasBuildProgramFailure) ; 

  if (VERB)
  {
    for (int i=0; i<NBKernel; i++)
      printf(" ===> FOUND %s\n", this->m_variantSplit->kernel_name[i]) ;
  }

  int M   = args.M, N = args.N, K = args.K;
  int lda = args.lda, ldb = args.ldb, ldc = args.ldc;

  int offsetA = args.offA;
  int offsetB = args.offB;
  int offsetC = args.offC;

  int arg[4]={0, 0, 0, 0} ; 

  //// All sgemm kernels shall have the same arguments: (A,B,C,M,N,K,alpha,beta,lda,ldb,ldc,offa,offb,offc) 

  for (int i=0; i<NBKernel; i++)
  {
    setKernelArg<cl_mem>(kernel[i], arg[i]++, args.A);
    setKernelArg<cl_mem>(kernel[i], arg[i]++, args.B);
    setKernelArg<cl_mem>(kernel[i], arg[i]++, args.C);

    setKernelArg<int>(kernel[i], arg[i]++, M);
    setKernelArg<int>(kernel[i], arg[i]++, N);
    setKernelArg<int>(kernel[i], arg[i]++, K);

    setKernelArg<cl_float>(kernel[i], arg[i]++, args.alpha);
    //if (args.beta!=0 && this->m_variantSplit->mult.compare("__ALPHA")!=0)
    setKernelArg<cl_float>(kernel[i], arg[i]++, args.beta);

    setKernelArg<int>(kernel[i], arg[i]++, lda);
    setKernelArg<int>(kernel[i], arg[i]++, ldb);
    setKernelArg<int>(kernel[i], arg[i]++, ldc);

    setKernelArg<int>(kernel[i], arg[i]++, offsetA);
    setKernelArg<int>(kernel[i], arg[i]++, offsetB);
    setKernelArg<int>(kernel[i], arg[i]++, offsetC);
  }

  err = KernelsLaunch(queue, kernel, args);



  for (int i = 0; i<NBKernel; i++)
    clReleaseKernel(kernel[i]) ;

  if (VERB) printf(" ===> ERR=%d \n",(int)err) ;

  // err= clFinish(queue);
  return clblasStatus(err) ;

}
#endif
