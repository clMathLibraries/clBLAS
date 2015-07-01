#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
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
#include "hawaii_dgemmSplitKernel.h"


#if BUILD_KERNEL_FROM_STRING
#include "dgemm_hawaiiSplitKernel.clT"
#else 

#include "dgemm_hawaiiSplitKernel.clHawaii_64.bin.clT"
#endif

// Just because the full name is too long
typedef clBlashawaiiDgemmSplitKernelFunctor::Variant Variant ; 

//define the string name of the soure/binary code
#define DGEMM_SRC_NAME(TA,TB, DIVK, MULT)    dgemm_##TA##TB##_##DIVK##_SPLIT##MULT
#define DGEMM_SRC_NAME_HAWAII(TA,TB, DIVK, MULT, BITS)   dgemm_##TA##TB##_##DIVK##_SPLIT##MULT##_##BITS##_bin_Hawaii

//variant name used to differentiate the different ones
#define DGEMM_VARIANT_NAME(TA,TB, DIVK, MULT) "dgemm_" #TA #TB "_" #DIVK "_SPLIT" #MULT
//DGEMM_VARIANT_NAME(TA, TB, DIVM , DIVN, DIVK, GREATER48M, GREATER48N, NBKERNEL),    

#define DGEMM_KERNEL_NAME(TA,TB,DIVM,DIVN,DIVK,BS0,BS1,NV0,NV1,MULT, BLOC) "dgemm_"  #TA #TB "_" #DIVM "_" #DIVN "_" #DIVK "_" #BS0 "x" #BS1 "_" #NV0 "x" #NV1 #MULT "_SPLIT_" #BLOC


#define trans_N clblasNoTrans
#define trans_T clblasTrans

// Fill a variant descriptor using OpenCL source 
#define DGEMM_VARIANT_OBJ(TA,TB,DIVK,BS0,BS1,NV0,NV1, BITS, MULT,  \
  KERNEL_NAME_MAIN, KERNEL_NAME_ROW, KERNEL_NAME_COLUMN, KERNEL_NAME_SINGLE, \
  KERNELS_SRC,  \
  KERNEL_BUILD_OPTIONS,  \
  KERNELS_BIN,  \
  KERNEL_BIN_SIZE) { \
  DGEMM_VARIANT_NAME(TA,TB, DIVK, MULT),                                          \
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

typedef clblasFunctorCache<clBlashawaiiDgemmSplitKernelFunctor,const Variant *> CacheSplit ;
static CacheSplit cachesplit  ;

// Make it 1 to enable additional debug 'print' 
#define VERB 0



//static bool applicable( const Variant & var, clblasDgemmFunctor::Args & args, int RefMultiple ) 
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




static const Variant * select_variant_hawaiiSplitKernel( clblasDgemmFunctor::Args & args, cl_uint _64BitsUse )
{



  if ( args.transA == clblasNoTrans ) 
  {
    if ( args.transB == clblasNoTrans ) 
    {

      // ===== dgemm NN ======

      const char* KName_NNMain = DGEMM_KERNEL_NAME(N, N, 48, 48, 8, 8, 8, 6, 6, __ALPHABETA, MAIN) ;
      const char* KName_NNRow = DGEMM_KERNEL_NAME(N, N, 1, 48, 8, 8, 8, 6, 6, __ALPHABETA, ROW) ;
      const char* KName_NNColumn = DGEMM_KERNEL_NAME(N, N, 48, 1, 8, 8, 8, 6, 6, __ALPHABETA, COLUMN) ;
      const char* KName_NNSingleWave = DGEMM_KERNEL_NAME(N, N, 1, 1, 8, 8, 8, 6, 6, __ALPHABETA, SINGLE) ;
                         
      const char* KName_NNMainAlpha = DGEMM_KERNEL_NAME(N, N, 48, 48, 8, 8, 8, 6, 6, __ALPHA, MAIN) ;
      const char* KName_NNRowAlpha = DGEMM_KERNEL_NAME(N, N, 1, 48, 8, 8, 8, 6, 6, __ALPHA, ROW) ;
      const char* KName_NNColumnAlpha = DGEMM_KERNEL_NAME(N, N, 48, 1, 8, 8, 8, 6, 6, __ALPHA, COLUMN) ;
      const char* KName_NNSingleWaveAlpha = DGEMM_KERNEL_NAME(N, N, 1, 1, 8, 8, 8, 6, 6, __ALPHA, SINGLE) ;
                         
      const char* KName_NNMainK1 = DGEMM_KERNEL_NAME(N, N, 48, 48, 1, 8, 8, 6, 6, __ALPHABETA, MAIN) ;
      const char* KName_NNRowK1 = DGEMM_KERNEL_NAME(N, N, 1, 48, 1, 8, 8, 6, 6, __ALPHABETA, ROW) ;
      const char* KName_NNColumnK1 = DGEMM_KERNEL_NAME(N, N, 48, 1, 1, 8, 8, 6, 6, __ALPHABETA, COLUMN) ;
      const char* KName_NNSingleWaveK1 = DGEMM_KERNEL_NAME(N, N, 1, 1, 1, 8, 8, 6, 6, __ALPHABETA, SINGLE) ;
                         
      const char* KName_NNMainK1Alpha = DGEMM_KERNEL_NAME(N, N, 48, 48, 1, 8, 8, 6, 6, __ALPHA, MAIN) ;
      const char* KName_NNRowK1Alpha = DGEMM_KERNEL_NAME(N, N, 1, 48, 1, 8, 8, 6, 6, __ALPHA, ROW) ;
      const char* KName_NNColumnK1Alpha = DGEMM_KERNEL_NAME(N, N, 48, 1, 1, 8, 8, 6, 6, __ALPHA, COLUMN) ;
      const char* KName_NNSingleWaveK1Alpha = DGEMM_KERNEL_NAME(N, N, 1, 1, 1, 8, 8, 6, 6, __ALPHA, SINGLE) ;

#if BUILD_KERNEL_FROM_STRING
      const char* KSrc_NTMain = DGEMM_SRC_NAME(N, N, 48, 48, 8, 8, 8, 6, 6, __ALPHABETA) ;
      const char* KSrc_NTRow = DGEMM_SRC_NAME(N, N, 1, 48, 8,8, 8, 6, 6, __ALPHABETA) ;
      const char* KSrc_NTColumn = DGEMM_SRC_NAME(N, N, 48, 1, 8, 8, 8, 6, 6, __ALPHABETA) ;
      const char* KSrc_NTSingleWave = DGEMM_SRC_NAME(N, N, 1, 1, 8, 8, 8, 6, 6, __ALPHABETA) ;
#else

      const char*  KBin_NNMain64 = DGEMM_SRC_NAME_HAWAII(N, N, 8, __ALPHABETA,  64) ;
      const size_t KBin_NNMainSize64 = sizeof(DGEMM_SRC_NAME_HAWAII(N, N, 8, __ALPHABETA,  64)) ;
                         
      const char*  KBin_NNMainAlpha64 = DGEMM_SRC_NAME_HAWAII(N, N, 8, __ALPHA,  64) ;
      const size_t KBin_NNMainAlphaSize64 = sizeof(DGEMM_SRC_NAME_HAWAII(N, N, 8, __ALPHA,  64)) ;
                         
      const char*  KBin_NNMainK164 = DGEMM_SRC_NAME_HAWAII(N, N, 1, __ALPHABETA,  64) ;
      const size_t KBin_NNMainK1Size64 = sizeof(DGEMM_SRC_NAME_HAWAII(N, N, 1, __ALPHABETA,  64)) ;
                         
      const char*  KBin_NNMainK1Alpha64 = DGEMM_SRC_NAME_HAWAII(N, N, 1, __ALPHA,  64) ;
      const size_t KBin_NNMainK1AlphaSize64 = sizeof(DGEMM_SRC_NAME_HAWAII(N, N, 1, __ALPHA,  64)) ;
#endif
      if(args.K%8==0)
      {
        if (args.beta!=0)
        {

          if(_64BitsUse==64)
          {
            static const Variant variant = DGEMM_VARIANT_OBJ(N,N,8,8,8,6,6,64,__ALPHABETA, 
              KName_NNMain,KName_NNRow, KName_NNColumn, KName_NNSingleWave ,
              NULL,
              NULL,
              KBin_NNMain64,
              KBin_NNMainSize64) ;

            return &variant ; 
          }
          else
          {
            std::cout<<"we don't support clblas on 32 bits"<< std::endl;
			      assert(1);
            return NULL;
          }   
        }
        else
        {
          if(_64BitsUse==64)
          {
            static const Variant variant = DGEMM_VARIANT_OBJ(N,N,8,8,8,6,6,64,__ALPHA,
              KName_NNMainAlpha,KName_NNRowAlpha, KName_NNColumnAlpha, KName_NNSingleWaveAlpha ,
              NULL,
              NULL,
              KBin_NNMainAlpha64,
              KBin_NNMainAlphaSize64) ;

            return &variant ; 
          }
          else
          {
            std::cout<<"we don't support clblas on 32 bits"<< std::endl;
			      assert(1);
            return NULL;
          }   
        }
      }
      else
      {
        if (args.beta!=0)
        {

          if(_64BitsUse==64)
          {
            static const Variant variant = DGEMM_VARIANT_OBJ(N,N,1,8,8,6,6,64,__ALPHABETA, 
              KName_NNMainK1,KName_NNRowK1, KName_NNColumnK1, KName_NNSingleWaveK1 ,
              NULL,
              NULL,
              KBin_NNMainK164,
              KBin_NNMainK1Size64) ;

            return &variant ; 
          }
          else
          {
            std::cout<<"we don't support clblas on 32 bits"<< std::endl;
			      assert(1);
            return NULL;
          }   
        }
        else
        {
          if(_64BitsUse==64)
          {
            static const Variant variant = DGEMM_VARIANT_OBJ(N,N,1,8,8,6,6,64,__ALPHA,
              KName_NNMainK1Alpha,KName_NNRowK1Alpha, KName_NNColumnK1Alpha, KName_NNSingleWaveK1Alpha ,
              NULL,
              NULL,
              KBin_NNMainK1Alpha64,
              KBin_NNMainK1AlphaSize64) ;

            return &variant ; 
          }
          else
          {
            std::cout<<"we don't support clblas on 32 bits"<< std::endl;
			      assert(1);
            return NULL;
          }   
        }
      }


    }
    if (args.transB == clblasTrans)
    {

      const char* KName_NTMain = DGEMM_KERNEL_NAME(N, T, 48, 48, 8, 8, 8, 6, 6, __ALPHABETA, MAIN) ;
      const char* KName_NTRow = DGEMM_KERNEL_NAME(N, T, 1, 48, 8, 8, 8, 6, 6, __ALPHABETA, ROW) ;
      const char* KName_NTColumn = DGEMM_KERNEL_NAME(N, T, 48, 1, 8, 8, 8, 6, 6, __ALPHABETA, COLUMN) ;
      const char* KName_NTSingleWave = DGEMM_KERNEL_NAME(N, T, 1, 1, 8, 8, 8, 6, 6, __ALPHABETA, SINGLE) ;

      const char* KName_NTMainAlpha = DGEMM_KERNEL_NAME(N, T, 48, 48, 8, 8, 8, 6, 6, __ALPHA, MAIN) ;
      const char* KName_NTRowAlpha = DGEMM_KERNEL_NAME(N, T, 1, 48, 8, 8, 8, 6, 6, __ALPHA, ROW) ;
      const char* KName_NTColumnAlpha = DGEMM_KERNEL_NAME(N, T, 48, 1, 8, 8, 8, 6, 6, __ALPHA, COLUMN) ;
      const char* KName_NTSingleWaveAlpha = DGEMM_KERNEL_NAME(N, T, 1, 1, 8, 8, 8, 6, 6, __ALPHA, SINGLE) ;

      const char* KName_NTMainK1 = DGEMM_KERNEL_NAME(N, T, 48, 48, 1, 8, 8, 6, 6, __ALPHABETA, MAIN) ;
      const char* KName_NTRowK1 = DGEMM_KERNEL_NAME(N, T, 1, 48, 1, 8, 8, 6, 6, __ALPHABETA, ROW) ;
      const char* KName_NTColumnK1 = DGEMM_KERNEL_NAME(N, T, 48, 1, 1, 8, 8, 6, 6, __ALPHABETA, COLUMN) ;
      const char* KName_NTSingleWaveK1 = DGEMM_KERNEL_NAME(N, T, 1, 1, 1, 8, 8, 6, 6, __ALPHABETA, SINGLE) ;

      const char* KName_NTMainK1Alpha = DGEMM_KERNEL_NAME(N, T, 48, 48, 1, 8, 8, 6, 6, __ALPHA, MAIN) ;
      const char* KName_NTRowK1Alpha = DGEMM_KERNEL_NAME(N, T, 1, 48, 1, 8, 8, 6, 6, __ALPHA, ROW) ;
      const char* KName_NTColumnK1Alpha = DGEMM_KERNEL_NAME(N, T, 48, 1, 1, 8, 8, 6, 6, __ALPHA, COLUMN) ;
      const char* KName_NTSingleWaveK1Alpha = DGEMM_KERNEL_NAME(N, T, 1, 1, 1, 8, 8, 6, 6, __ALPHA, SINGLE) ;

#if BUILD_KERNEL_FROM_STRING
      const char* KSrc_NTMain = DGEMM_SRC_NAME(N, T, 48, 48, 8, 8, 8, 6, 6, __ALPHABETA) ;
      const char* KSrc_NTRow = DGEMM_SRC_NAME(N, T, 1, 48, 8,8, 8, 6, 6, __ALPHABETA) ;
      const char* KSrc_NTColumn = DGEMM_SRC_NAME(N, T, 48, 1, 8, 8, 8, 6, 6, __ALPHABETA) ;
      const char* KSrc_NTSingleWave = DGEMM_SRC_NAME(N, T, 1, 1, 8, 8, 8, 6, 6, __ALPHABETA) ;
#else

      const char* KBin_NTMain64 = DGEMM_SRC_NAME_HAWAII(N, T, 8, __ALPHABETA,  64) ;
      const size_t KBin_NTMainSize64 = sizeof(DGEMM_SRC_NAME_HAWAII(N, T, 8, __ALPHABETA,  64)) ;

      const char* KBin_NTMainAlpha64 = DGEMM_SRC_NAME_HAWAII(N, T, 8, __ALPHA,  64) ;
      const size_t KBin_NTMainAlphaSize64 = sizeof(DGEMM_SRC_NAME_HAWAII(N, T, 8, __ALPHA,  64)) ;

      const char* KBin_NTMainK164 = DGEMM_SRC_NAME_HAWAII(N, T, 1, __ALPHABETA,  64) ;
      const size_t KBin_NTMainK1Size64 = sizeof(DGEMM_SRC_NAME_HAWAII(N, T, 1, __ALPHABETA,  64)) ;

      const char* KBin_NTMainK1Alpha64 = DGEMM_SRC_NAME_HAWAII(N, T, 1, __ALPHA,  64) ;
      const size_t KBin_NTMainK1AlphaSize64 = sizeof(DGEMM_SRC_NAME_HAWAII(N, T, 1, __ALPHA,  64)) ;
#endif

      // ===== dgemm NT ======
      if(args.K%8==0)
      {
        if (args.beta!=0)
        {

          if(_64BitsUse==64)
          {
            static const Variant variant = DGEMM_VARIANT_OBJ(N,T,8,8,8,6,6,64,__ALPHABETA, 
              KName_NTMain,KName_NTRow, KName_NTColumn, KName_NTSingleWave ,
              NULL,
              NULL,
              KBin_NTMain64,
              KBin_NTMainSize64) ;

            return &variant ; 
          }
          else
          {
            std::cout<<"we don't support clblas on 32 bits"<< std::endl;
			      assert(1);
            return NULL;
          }   
        }
        else
        {
          if(_64BitsUse==64)
          {
            static const Variant variant = DGEMM_VARIANT_OBJ(N,T,8,8,8,6,6,64,__ALPHA,
              KName_NTMainAlpha,KName_NTRowAlpha, KName_NTColumnAlpha, KName_NTSingleWaveAlpha ,
              NULL,
              NULL,
              KBin_NTMainAlpha64,
              KBin_NTMainAlphaSize64) ;

            return &variant ; 
          }
          else
          {
            std::cout<<"we don't support clblas on 32 bits"<< std::endl;
			      assert(1);
            return NULL;
          }   
        }
      }
      else
      {
        if (args.beta!=0)
        {

          if(_64BitsUse==64)
          {
            static const Variant variant = DGEMM_VARIANT_OBJ(N,T,1,8,8,6,6,64,__ALPHABETA, 
              KName_NTMainK1,KName_NTRowK1, KName_NTColumnK1, KName_NTSingleWaveK1 ,
              NULL,
              NULL,
              KBin_NTMainK164,
              KBin_NTMainK1Size64) ;

            return &variant ; 
          }
          else
          {
            std::cout<<"we don't support clblas on 32 bits"<< std::endl;
			      assert(1);
            return NULL;
          }   
        }
        else
        {
          if(_64BitsUse==64)
          {
            static const Variant variant = DGEMM_VARIANT_OBJ(N,T,1,8,8,6,6,64,__ALPHA,
              KName_NTMainK1Alpha,KName_NTRowK1Alpha, KName_NTColumnK1Alpha, KName_NTSingleWaveK1Alpha ,
              NULL,
              NULL,
              KBin_NTMainK1Alpha64,
              KBin_NTMainK1AlphaSize64) ;

            return &variant ; 
          }
          else
          {
            std::cout<<"we don't support clblas on 32 bits"<< std::endl;
			      assert(1);
            return NULL;
          }   
        }
      }

    }
  }

  return NULL;
}

clBlashawaiiDgemmSplitKernelFunctor::clBlashawaiiDgemmSplitKernelFunctor(Args & args, const Variant * variant, cl_int & err) 
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
  BinaryLookup bl(context, device, "clBlashawaiiDgemmSplitKernelFunctor");

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
      if (VERB) printf(" ===> BUILD PROBLEM WE DON'T SUPPORT SOURCE BUILD FOR SPLIT DGEMM\n") ;
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



clBlashawaiiDgemmSplitKernelFunctor * 
  clBlashawaiiDgemmSplitKernelFunctor::provide(clblasDgemmFunctor::Args & args) 
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

  if (major<2)
    return NULL;

  const Variant * variant = select_variant_hawaiiSplitKernel( args,  bitness ) ;
  if ( variant == NULL )  
    return NULL ; 



  CacheSplit::Lookup lookup(cachesplit, ctxt, dev, variant) ;


  if ( lookup.ok() )
  {
    clBlashawaiiDgemmSplitKernelFunctor * functor = lookup.get();
    functor->retain(); // increment the reference counter to avoid deletion while it is still beeing used
    return functor;
  }

  clBlashawaiiDgemmSplitKernelFunctor * functor = new clBlashawaiiDgemmSplitKernelFunctor(args, variant, err);
  if (err != CL_SUCCESS)
  {
    return NULL;
  }

  lookup.set(functor) ;

  return functor;

}


cl_int clBlashawaiiDgemmSplitKernelFunctor::KernelsLaunch(cl_command_queue queue, cl_kernel Kernel[4], Args &args)
{
  size_t GlobalX =args.M/m_variantSplit->bwi[0];
  GlobalX-=GlobalX%m_variantSplit->ls[0];
  //

  size_t GlobalY = args.N/m_variantSplit->bwi[1];
  GlobalY-=GlobalY%m_variantSplit->ls[1];


  std::size_t gs[2] = {GlobalX, GlobalY};
  cl_int error = 0;

  if (args.M%48==0 && args.N%48==0)
  {
    if (VERB) printf(" ===> EXECUTE KERNEL 0 \n") ;
    error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList,args.events);
    return error;
  }

  if (args.M%48!=0 && args.N%48!=0 && args.M>=48 && args.N>=48 )
  {
    if (VERB) printf(" ===> EXECUTE KERNEL 0, 1, 2, 3 \n") ;
    error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList,NULL);

    gs[0] = 8;
    error |= clEnqueueNDRangeKernel(queue, Kernel[1], 2, NULL, gs, m_variantSplit->ls, 0, NULL,NULL);

    gs[1] = 8;
    gs[0] = GlobalX;
    error |= clEnqueueNDRangeKernel(queue, Kernel[2], 2, NULL, gs, m_variantSplit->ls, 0, NULL,NULL);

    gs[0] = 8; gs[1] = 8;
    error |= clEnqueueNDRangeKernel(queue, Kernel[3], 2, NULL, gs, m_variantSplit->ls, 0, NULL,args.events);
    return error;
  }
  if (args.M%48==0 && args.N%48!=0 &&  args.N>48 )
  {
    if (VERB) printf(" ===> EXECUTE KERNEL 0, 2, \n") ;

    error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList,NULL);
    gs[1] = 8;
	error |= clEnqueueNDRangeKernel(queue, Kernel[2], 2, NULL, gs, m_variantSplit->ls, 0, NULL, args.events);

    return error;
  }
  if (args.N%48==0 && args.M%48!=0 &&  args.M>48 )
  {
        if (VERB) printf(" ===> EXECUTE KERNEL 0, 1 \n") ;

    error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList,NULL);
    gs[0] = 8;
	error |= clEnqueueNDRangeKernel(queue, Kernel[1], 2, NULL, gs, m_variantSplit->ls, 0, NULL, args.events);

    return error;
  }
  if(args.M<48 && args.N%48==0)
  {
        if (VERB) printf(" ===> EXECUTE KERNEL 1, \n") ;

    gs[0] = 8;
    error |= clEnqueueNDRangeKernel(queue, Kernel[1], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList, args.events);
    return error;
  }
  if(args.M<48 && args.N%48!=0 && args.N>=48)
  {
        if (VERB) printf(" ===> EXECUTE KERNEL  1, 3 \n") ;

    gs[0] = 8;
    error |= clEnqueueNDRangeKernel(queue, Kernel[1], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList, NULL);
    gs[1] = 8;
    error |= clEnqueueNDRangeKernel(queue, Kernel[3], 2, NULL, gs, m_variantSplit->ls, 0, NULL,args.events);
    return error;
  }
  if(args.N<48 && args.M%48==0)
  {
        if (VERB) printf(" ===> EXECUTE KERNEL  2 \n") ;

    gs[1] = 8;  
    error |= clEnqueueNDRangeKernel(queue, Kernel[2], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList, args.events);
    return error;
  }
  if(args.N<48 && args.M%48!=0&& args.M>=48)
  {
        if (VERB) printf(" ===> EXECUTE KERNEL 2, 3 \n") ;

    gs[1] = 8;  
    error |= clEnqueueNDRangeKernel(queue, Kernel[2], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList, NULL);

    gs[0] = 8;
    error |= clEnqueueNDRangeKernel(queue, Kernel[3], 2, NULL, gs, m_variantSplit->ls, 0, NULL,args.events);
    return error;
  }
  if (args.N<48 && args.M<48)
  {
     if (VERB) printf(" ===> EXECUTE KERNEL  3 \n") ;
    gs[0] = 8; gs[1] = 8;
    error |= clEnqueueNDRangeKernel(queue, Kernel[3], 2, NULL, gs, m_variantSplit->ls,args.numEventsInWaitList, args.eventWaitList, args.events);
    return error;
  }

  return clblasNotImplemented;
}



clblasStatus clBlashawaiiDgemmSplitKernelFunctor::execute(Args &args)
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
      if (err != CL_SUCCESS) return clblasStatus(err) ; 
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

  unsigned int M  = (unsigned int )args.M, N = (unsigned int )args.N, K = (unsigned int )args.K;
  unsigned int lda = (unsigned int )args.lda, ldb = (unsigned int )args.ldb, ldc = (unsigned int )args.ldc;

  int offsetA = (int)args.offA;
  int offsetB = (int)args.offB;
  int offsetC = (int)args.offC;

  int arg[4]={0, 0, 0, 0} ; 

  //// All dgemm kernels shall have the same arguments: (A,B,C,M,N,K,alpha,beta,lda,ldb,ldc,offa,offb,offc) 

  for (int i=0; i<NBKernel; i++)
  {
    setKernelArg<cl_mem>(kernel[i], arg[i]++, args.A);
    setKernelArg<cl_mem>(kernel[i], arg[i]++, args.B);
    setKernelArg<cl_mem>(kernel[i], arg[i]++, args.C);

    setKernelArg<int>(kernel[i], arg[i]++, M);
    setKernelArg<int>(kernel[i], arg[i]++, N);
    setKernelArg<int>(kernel[i], arg[i]++, K);

    setKernelArg<cl_double>(kernel[i], arg[i]++, args.alpha);
    if (args.beta!=0 && this->m_variantSplit->mult.compare("__ALPHA")!=0)
      setKernelArg<cl_double>(kernel[i], arg[i]++, args.beta);

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

  return clblasStatus(err) ;

}
#endif
