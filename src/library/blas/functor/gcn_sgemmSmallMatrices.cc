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
#include "gcn_sgemmSmallMatrices.h"


#if BUILD_KERNEL_FROM_STRING
#include "sgemm_gcn_SmallMatrices.clT"
#else 

#include "sgemm_gcn_SmallMatrices.clHawaii_64.bin.clT"
#include "sgemm_gcn_SmallMatrices.clBonaire_64.bin.clT"
#include "sgemm_gcn_SmallMatrices.clTahiti_64.bin.clT"

#endif


#define SGEMM_SRC_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,MULT)    sgemm_##TA##TB##_##DIVN##_##DIVM##_##DIVK##_##BS0##x##BS1##_##NV0##x##NV1##MULT
#define SGEMM_SRC_NAME_TAHITI(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS,MULT)   sgemm_##TA##TB##_##DIVN##_##DIVM##_##DIVK##_##BS0##x##BS1##_##NV0##x##NV1##MULT##_##BITS##_bin_Tahiti
#define SGEMM_SRC_NAME_HAWAII(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS,MULT)   sgemm_##TA##TB##_##DIVN##_##DIVM##_##DIVK##_##BS0##x##BS1##_##NV0##x##NV1##MULT##_##BITS##_bin_Hawaii
#define SGEMM_SRC_NAME_BONAIRE(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS,MULT)   sgemm_##TA##TB##_##DIVN##_##DIVM##_##DIVK##_##BS0##x##BS1##_##NV0##x##NV1##MULT##_##BITS##_bin_Bonaire


//
// The name of the 'const char []' global variable that contain the SPIR data.
// That name is similar to the one produced by DGEMM_SRC_NAME but suffixed by _spir
//
#define SGEMM_SPIR_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,MULT)   sgemm_##TA##TB##_##DIVN##_##DIVM##_##DIVK##_##BS0##x##BS1##_##NV0##x##NV1_spir

//
// The name of the 'const char []' global variable that contain the CL binaries data.
// That name is similar to the one produced by DGEMM_SRC_NAME but suffixed by _bin
//


// The name of the kernel itself.
// This is basically the name returned by DGEMM_SRC_NAME but as string
//
#define SGEMM_KERNEL_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,MULT) "sgemm_"  #TA #TB "_" #DIVN "_" #DIVM "_" #DIVK "_" #BS0 "x" #BS1 "_" #NV0 "x" #NV1 #MULT 

//
// Helpers to transform N and T in proper clblas values for the macros above
//
#define trans_N clblasNoTrans
#define trans_T clblasTrans


// Fill a variant descriptor using OpenCL source 
#define SGEMM_VARIANT_SRC(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1, MULT) { \
  SGEMM_KERNEL_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1, MULT) ,     \
  SGEMM_SRC_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1, MULT) ,        \
  NULL, NULL, 0,                                                \
  trans_##TA, trans_##TB,                                       \
  DIVN,DIVM,DIVK,                                               \
{ BS0, BS1 } ,                                                \
{ NV0, NV1 } ,                                                      \
#MULT                                                               \
} 

// Fill a variant descriptor using SPIR  
#define SGEMM_VARIANT_SPIR(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1, MULT) {  \
  SGEMM_KERNEL_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1, MULT) ,       \
  NULL , "-x spir -spir-std=1.2"                                  \
  SGEMM_SPIR_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1),          \
  sizeof(SGEMM_SPIR_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1)),  \
  trans_##TA,trans_##TB,                                          \
  DIVN,DIVM,DIVK,                                                 \
{ BS0, BS1 } ,                                                  \
{ NV0, NV1 }  ,                                                      \
#MULT                                                               \
} 

// Fill a variant descriptor using CL Binaries  
#define SGEMM_VARIANT_BIN_CL1(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS,DEVICE, MULT) {  \
  SGEMM_KERNEL_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1, MULT) ,           \
  NULL , NULL,                                                        \
  SGEMM_SRC_NAME##_##DEVICE(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS, MULT),          \
  sizeof(SGEMM_SRC_NAME##_##DEVICE(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS, MULT)),  \
  trans_##TA,trans_##TB,                                              \
  DIVN,DIVM,DIVK,                                                     \
{ BS0, BS1 } ,                                                      \
{ NV0, NV1 } ,                                                      \
#MULT                                                               \
} 


#define SGEMM_VARIANT_BIN_CL2(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS,DEVICE, MULT) {  \
  SGEMM_KERNEL_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1, MULT) ,           \
  NULL , "-cl-std=CL2.0",                                                        \
  SGEMM_SRC_NAME##_##DEVICE(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS, MULT),          \
  sizeof(SGEMM_SRC_NAME##_##DEVICE(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS, MULT)),  \
  trans_##TA,trans_##TB,                                              \
  DIVN,DIVM,DIVK,                                                     \
{ BS0, BS1 } ,                                                      \
{ NV0, NV1 } ,                                                      \
#MULT                                                               \
} 

// Just because the full name is too long
typedef clBlasGCNSgemmSmallMatricesFunctor::Variant Variant ; 

typedef clblasFunctorCache<clBlasGCNSgemmSmallMatricesFunctor,const Variant *> CacheSMallsgemm ;
static CacheSMallsgemm cachesmall  ;

// Make it 1 to enable additional debug 'print' 
#define VERB 0



static bool applicable( const Variant & var, clblasSgemmFunctor::Args & args ) 
{
#if 0
  // Transpose values are tested in select_variant
  if ( args.transA != var.transA ) return false ;
  if ( args.transB != var.transB ) return false ;
#endif

  //if (args.N>=var.divN && args.N % var.divN != 0 )
  if ( args.N % var.divN != 0 ) 
    return false ; 
  if ( args.M % var.divM != 0 ) 
    return false ; 
  if ( args.beta==0 && var.mult.compare("__ALPHA")!=0)
    return false ;
  return true ;
}




static const Variant * select_variant_GCNSmallMatrices( clblasSgemmFunctor::Args & args, const char* DevName, cl_uint _64BitsUse )
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

      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(N,N,32,32,16,16,16,2,2,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ; 

        static const Variant variantA = DGEMM_VARIANT_SRC(N,N,32,32,16,16,16,2,2,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ; 

#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
            static const Variant variant = SGEMM_VARIANT_BIN_CL1(N,N,32,32,16,16,16,2,2,64,TAHITI,__ALPHABETA ) ;
            if ( applicable(variant,args) ) 
              return &variant ; 
           

            static const Variant variantA = SGEMM_VARIANT_BIN_CL1(N,N,32,32,16,16,16,2,2,64,TAHITI,__ALPHA ) ;
            if ( applicable(variantA,args) ) 
              return &variantA ; 
#endif //#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
            static const Variant variant = SGEMM_VARIANT_BIN_CL2(N,N,32,32,16,16,16,2,2,64,HAWAII,__ALPHABETA ) ;
            if ( applicable(variant,args) ) 
              return &variant ; 

            static const Variant variantA = SGEMM_VARIANT_BIN_CL2(N,N,32,32,16,16,16,2,2,64,HAWAII,__ALPHA ) ;
            if ( applicable(variantA,args) ) 
              return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }

        else if(!strcmp(DevName, "Bonaire"))
        {
#ifndef CLBLAS_BONAIRE_DYNAMIC_KERNEL
            static const Variant variant = SGEMM_VARIANT_BIN_CL2(N,N,32,32,16,16,16,2,2,64,BONAIRE,__ALPHABETA ) ;
            if ( applicable(variant,args) ) 
              return &variant ; 

            static const Variant variantA = SGEMM_VARIANT_BIN_CL2(N,N,32,32,16,16,16,2,2,64,BONAIRE,__ALPHA ) ;
            if ( applicable(variantA,args) ) 
              return &variantA ; 
#endif //#ifndef CLBLAS_BONAIRE_DYNAMIC_KERNEL
        }

#endif
      } 

      

    }
    if (args.transB == clblasTrans)
    {
            if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(N,T,32,32,16,16,16,2,2,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ; 

        static const Variant variantA = DGEMM_VARIANT_SRC(N,T,32,32,16,16,16,2,2,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ; 
#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
            static const Variant variant = SGEMM_VARIANT_BIN_CL1(N,T,32,32,16,16,16,2,2,64,TAHITI,__ALPHABETA ) ;
            if ( applicable(variant,args) ) 
              return &variant ; 
           
            static const Variant variantA = SGEMM_VARIANT_BIN_CL1(N,T,32,32,16,16,16,2,2,64,TAHITI,__ALPHA ) ;
            if ( applicable(variantA,args) ) 
              return &variantA ; 
#endif //#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
            static const Variant variant = SGEMM_VARIANT_BIN_CL2(N,T,32,32,16,16,16,2,2,64,HAWAII,__ALPHABETA ) ;
            if ( applicable(variant,args) ) 
              return &variant ;           

            static const Variant variantA = SGEMM_VARIANT_BIN_CL2(N,T,32,32,16,16,16,2,2,64,HAWAII,__ALPHA ) ;
            if ( applicable(variantA,args) ) 
              return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }
        else if(!strcmp(DevName, "Bonaire"))
        {
#ifndef CLBLAS_BONAIRE_DYNAMIC_KERNEL
            static const Variant variant = SGEMM_VARIANT_BIN_CL2(N,T,32,32,16,16,16,2,2,64,BONAIRE,__ALPHABETA ) ;
            if ( applicable(variant,args) ) 
              return &variant ;           

            static const Variant variantA = SGEMM_VARIANT_BIN_CL2(N,T,32,32,16,16,16,2,2,64,BONAIRE,__ALPHA ) ;
            if ( applicable(variantA,args) ) 
              return &variantA ; 
#endif //#ifndef CLBLAS_BONAIRE_DYNAMIC_KERNEL
        }
#endif
      } 
    }
  }
  else
  {
    if ( args.transB == clblasNoTrans ) 
    {
      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(T,N,32,32,16,16,16,2,2,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ; 

        static const Variant variantA = DGEMM_VARIANT_SRC(T,N,32,32,16,16,16,2,2,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ; 

#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
            static const Variant variant = SGEMM_VARIANT_BIN_CL1(T,N,32,32,16,16,16,2,2,64,TAHITI,__ALPHABETA ) ;
            if ( applicable(variant,args) ) 
              return &variant ; 
           

            static const Variant variantA = SGEMM_VARIANT_BIN_CL1(T,N,32,32,16,16,16,2,2,64,TAHITI,__ALPHA ) ;
            if ( applicable(variantA,args) ) 
              return &variantA ;
#endif //#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
            static const Variant variant = SGEMM_VARIANT_BIN_CL2(T,N,32,32,16,16,16,2,2,64,HAWAII,__ALPHABETA ) ;
            if ( applicable(variant,args) ) 
              return &variant ; 

            static const Variant variantA = SGEMM_VARIANT_BIN_CL2(T,N,32,32,16,16,16,2,2,64,HAWAII,__ALPHA ) ;
            if ( applicable(variantA,args) ) 
              return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }

        else if(!strcmp(DevName, "Bonaire"))
        {
#ifndef CLBLAS_BONAIRE_DYNAMIC_KERNEL
            static const Variant variant = SGEMM_VARIANT_BIN_CL2(T,N,32,32,16,16,16,2,2,64,BONAIRE,__ALPHABETA ) ;
            if ( applicable(variant,args) ) 
              return &variant ; 

            static const Variant variantA = SGEMM_VARIANT_BIN_CL2(T,N,32,32,16,16,16,2,2,64,BONAIRE,__ALPHA ) ;
            if ( applicable(variantA,args) ) 
              return &variantA ;
#endif //#ifndef CLBLAS_BONAIRE_DYNAMIC_KERNEL
        }

#endif
      } 
    }
  }


  return NULL;
}

clBlasGCNSgemmSmallMatricesFunctor::clBlasGCNSgemmSmallMatricesFunctor(Args & args, const Variant * variant, cl_int & err) 
{

  cl_device_id device;
  cl_context context;
  m_program=NULL;
  m_variant = variant;


  cl_command_queue queue = args.queue;
  err = getDeviceAndContext(queue, device, context);
  if( err != CL_SUCCESS )
  {
    return;
  }

  if (VERB) printf(" ===> GET KERNEL %s\n", this->m_variant->kernel_name) ;

  //Ben do I use the correct "kernel_name"?
  BinaryLookup bl(context, device, "clBlasGCNSgemmSmallMatricesFunctor");

  bl.variantRaw( this->m_variant->kernel_name, strlen(this->m_variant->kernel_name)+1 ) ;

  if ( !bl.found() ) // may create empty file or may wait until file is ready  
  {
    if ( this->m_variant->bin != NULL ) 
    {
      // build from a pre-compiled version of the kernel (SPIR or cl binaries)
      //only 1 binary containing all the kernel
      err = bl.buildFromBinary(this->m_variant->bin, this->m_variant->bin_size, this->m_variant->build_options);
    }
    else
    {
      //// directly build from a char* 
         err = bl.buildFromSource(this->m_variant->source);
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



clBlasGCNSgemmSmallMatricesFunctor * 
  clBlasGCNSgemmSmallMatricesFunctor::provide(clblasSgemmFunctor::Args & args, const char* DevName) 
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

  const Variant * variant = select_variant_GCNSmallMatrices( args, DevName,  bitness ) ;
  if ( variant == NULL )  
    return NULL ; 



  CacheSMallsgemm::Lookup lookup(cachesmall, ctxt, dev, variant) ;


  if ( lookup.ok() )
  {
    clBlasGCNSgemmSmallMatricesFunctor * functor = lookup.get();
    functor->retain(); // increment the reference counter to avoid deletion while it is still beeing used
    return functor;
  }

  clBlasGCNSgemmSmallMatricesFunctor * functor = new clBlasGCNSgemmSmallMatricesFunctor(args, variant, err);
  if (err != CL_SUCCESS)
  {
    return NULL;
  }

  lookup.set(functor) ;

  return functor;

}




//need to rewrite execute!!!
clblasStatus clBlasGCNSgemmSmallMatricesFunctor::execute(Args &args)
{
  cl_int err;
  cl_command_queue queue = args.queue;

  if (VERB) printf(" ===> EXECUTE KERNEL %s, alpha =%f ,beta = %f\n", this->m_variant->kernel_name, args.alpha, args.beta) ;

  cl_kernel kernel; 
 // int NBKernel = 0;

 
      kernel= clCreateKernel( this->m_program, this->m_variant->kernel_name,  &err);
      if (err != CL_SUCCESS) return clblasStatus(err) ; 


  //if (NBKernel != 4) return clblasStatus(clblasBuildProgramFailure) ; 

  if (VERB)
  {
    
      printf(" ===> FOUND %s\n", this->m_variant->kernel_name) ;
  }

  int M   = args.M, N = args.N, K = args.K;
  int lda = args.lda, ldb = args.ldb, ldc = args.ldc;

  int offsetA = args.offA;
  int offsetB = args.offB;
  int offsetC = args.offC;

  int arg=0 ; 

  //// All dgemm kernels shall have the same arguments: (A,B,C,M,N,K,alpha,beta,lda,ldb,ldc,offa,offb,offc) 

  setKernelArg<cl_mem>(kernel, arg++, args.A);
  setKernelArg<cl_mem>(kernel, arg++, args.B);
  setKernelArg<cl_mem>(kernel, arg++, args.C);

  setKernelArg<int>(kernel, arg++, M);
  setKernelArg<int>(kernel, arg++, N);
  setKernelArg<int>(kernel, arg++, K);

  setKernelArg<cl_float>(kernel, arg++, args.alpha);
  if (args.beta!=0 && this->m_variant->mult.compare("__ALPHA")!=0)
    setKernelArg<cl_float>(kernel, arg++, args.beta);

  setKernelArg<int>(kernel, arg++, lda);
  setKernelArg<int>(kernel, arg++, ldb);
  setKernelArg<int>(kernel, arg++, ldc);

  setKernelArg<int>(kernel, arg++, offsetA);
  setKernelArg<int>(kernel, arg++, offsetB);
  setKernelArg<int>(kernel, arg++, offsetC);


 // err = KernelsLaunch(queue, kernel, args);
  const size_t * ls  = this->m_variant->ls  ; // Each work group is made of ls[0] x ls[1]  PE
  const size_t * bwi = this->m_variant->bwi ; // Each PE updates bwi[0] x bwi[1] values

  size_t globalThreads[2];

  unsigned int thx, thy;

  thx   = M/bwi[0] + ((M%bwi[0] != 0) ? 1 : 0);   
  thx   = thx/ls[0] + ((thx%ls[0] != 0) ? 1 : 0); 
  thx   = ls[0] * thx;

  thy   = N/bwi[1] + ((N%bwi[1] != 0) ? 1 : 0);  
  thy   = thy/ls[1] + ((thy%ls[1] != 0) ? 1 : 0); 
  thy   = ls[1] * thy;

  globalThreads[0] = thx;
  globalThreads[1] = thy;

  err = clEnqueueNDRangeKernel(queue, kernel, 2, NULL,
    globalThreads, ls , 
    args.numEventsInWaitList, 
    args.eventWaitList, 
    args.events);



 
  clReleaseKernel(kernel) ;

  if (VERB) printf(" ===> ERR=%d \n",(int)err) ;

  return clblasStatus(err) ;

}

