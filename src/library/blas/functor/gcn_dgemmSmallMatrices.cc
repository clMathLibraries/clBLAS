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
#include "gcn_dgemmSmallMatrices.h"


#if BUILD_KERNEL_FROM_STRING
#include "dgemm_gcn_SmallMatrices.clT"
#else 

#include "dgemm_gcn_SmallMatrices.clHawaii_64.bin.clT"

#include "dgemm_gcn_SmallMatrices.clTahiti_64.bin.clT"

#endif


#define DGEMM_SRC_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,MULT)    dgemm_##TA##TB##_##DIVN##_##DIVM##_##DIVK##_##BS0##x##BS1##_##NV0##x##NV1##MULT
#define DGEMM_SRC_NAME_TAHITI(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS,MULT)   dgemm_##TA##TB##_##DIVN##_##DIVM##_##DIVK##_##BS0##x##BS1##_##NV0##x##NV1##MULT##_##BITS##_bin_Tahiti
#define DGEMM_SRC_NAME_HAWAII(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS,MULT)   dgemm_##TA##TB##_##DIVN##_##DIVM##_##DIVK##_##BS0##x##BS1##_##NV0##x##NV1##MULT##_##BITS##_bin_Hawaii

//
// The name of the 'const char []' global variable that contain the SPIR data.
// That name is similar to the one produced by DGEMM_SRC_NAME but suffixed by _spir
//
#define DGEMM_SPIR_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,MULT)   dgemm_##TA##TB##_##DIVN##_##DIVM##_##DIVK##_##BS0##x##BS1##_##NV0##x##NV1_spir

//
// The name of the 'const char []' global variable that contain the CL binaries data.
// That name is similar to the one produced by DGEMM_SRC_NAME but suffixed by _bin
//


// The name of the kernel itself.
// This is basically the name returned by DGEMM_SRC_NAME but as string
//
#define DGEMM_KERNEL_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,MULT) "dgemm_"  #TA #TB "_" #DIVN "_" #DIVM "_" #DIVK "_" #BS0 "x" #BS1 "_" #NV0 "x" #NV1 #MULT 

//
// Helpers to transform N and T in proper clblas values for the macros above
//
#define trans_N clblasNoTrans
#define trans_T clblasTrans


// Fill a variant descriptor using OpenCL source 
#define DGEMM_VARIANT_SRC(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1, MULT) { \
  DGEMM_KERNEL_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1, MULT) ,     \
  DGEMM_SRC_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1, MULT) ,        \
  NULL, NULL, 0,                                                \
  trans_##TA, trans_##TB,                                       \
  DIVN,DIVM,DIVK,                                               \
{ BS0, BS1 } ,                                                \
{ NV0, NV1 } ,                                                      \
#MULT                                                               \
} 

// Fill a variant descriptor using SPIR  
#define DGEMM_VARIANT_SPIR(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1, MULT) {  \
  DGEMM_KERNEL_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1, MULT) ,       \
  NULL , "-x spir -spir-std=1.2"                                  \
  DGEMM_SPIR_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1),          \
  sizeof(DGEMM_SPIR_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1)),  \
  trans_##TA,trans_##TB,                                          \
  DIVN,DIVM,DIVK,                                                 \
{ BS0, BS1 } ,                                                  \
{ NV0, NV1 }  ,                                                      \
#MULT                                                               \
} 

// Fill a variant descriptor using CL Binaries  
#define DGEMM_VARIANT_BIN(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS,DEVICE, MULT) {  \
  DGEMM_KERNEL_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1, MULT) ,           \
  NULL , NULL,                                                        \
  DGEMM_SRC_NAME##_##DEVICE(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS, MULT),          \
  sizeof(DGEMM_SRC_NAME##_##DEVICE(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS, MULT)),  \
  trans_##TA,trans_##TB,                                              \
  DIVN,DIVM,DIVK,                                                     \
{ BS0, BS1 } ,                                                      \
{ NV0, NV1 } ,                                                      \
#MULT                                                               \
} 


// Just because the full name is too long
typedef clBlasGCNDgemmSmallMatricesFunctor::Variant Variant ; 

////define the string name of the soure/binary code
//#define DGEMM_SRC_NAME(TA,TB,MULT)    dgemm_##TA##TB##_SMALL##MULT
//#define DGEMM_SRC_NAME_HAWAII(TA,TB,  MULT, BITS)   dgemm_##TA##TB##_SMALL##MULT##_##BITS##_bin_Hawaii
//
////variant name used to differentiate the different ones
//#define DGEMM_VARIANT_NAME(TA,TB, MULT) "dgemm_" #TA #TB "_SMALL" #MULT
////DGEMM_VARIANT_NAME(TA, TB, DIVM , DIVN, DIVK, GREATER48M, GREATER48N, NBKERNEL),    
//
//#define DGEMM_KERNEL_NAME(TA,TB,DIVM,DIVN,DIVK,BS0,BS1,NV0,NV1,MULT, BLOC) "dgemm_"  #TA #TB "_" #DIVM "_" #DIVN "_" #DIVK "_" #BS0 "x" #BS1 "_" #NV0 "x" #NV1 #MULT "_SPLIT_" #BLOC
//
//
//#define trans_N clblasNoTrans
//#define trans_T clblasTrans
//
//// Fill a variant descriptor using OpenCL source 
//#define DGEMM_VARIANT_OBJ(TA,TB,DIVK,BS0,BS1,NV0,NV1, BITS, MULT,  \
//  KERNEL_NAME_MAIN, KERNEL_NAME_ROW, \
//  KERNELS_SRC,  \
//  KERNEL_BUILD_OPTIONS,  \
//  KERNELS_BIN,  \
//  KERNEL_BIN_SIZE) { \
//  DGEMM_VARIANT_NAME(TA,TB, MULT),                                          \
//{ KERNEL_NAME_MAIN, KERNEL_NAME_ROW } , \
//  KERNELS_SRC,  \
//  KERNEL_BUILD_OPTIONS, \
//  KERNELS_BIN, \
//  KERNEL_BIN_SIZE, \
//  trans_##TA, trans_##TB,                                       \
//  DIVK ,                                                        \
//{ BS0, BS1 } ,                                                \
//{ NV0, NV1 } ,                                                      \
//#MULT                                                               \
//} 

typedef clblasFunctorCache<clBlasGCNDgemmSmallMatricesFunctor,const Variant *> CacheSMall ;
static CacheSMall cachesmall  ;

// Make it 1 to enable additional debug 'print' 
#define VERB 0



static bool applicable( const Variant & var, clblasDgemmFunctor::Args & args ) 
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




static const Variant * select_variant_GCNSmallMatrices( clblasDgemmFunctor::Args & args, const char* DevName, cl_uint _64BitsUse )
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
        static const Variant variant = DGEMM_VARIANT_SRC(N,N,16,16,8,8,8,2,2,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ; 

        static const Variant variantA = DGEMM_VARIANT_SRC(N,N,16,16,8,8,8,2,2,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ; 

#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
            static const Variant variant = DGEMM_VARIANT_BIN(N,N,16,16,8,8,8,2,2,64,TAHITI,__ALPHABETA ) ;
            if ( applicable(variant,args) ) 
              return &variant ; 
           
           // const char * test = DGEMM_KERNEL_NAME(N,N,48,48,8,8,8,6,6, __ALPHA);
           // test
            static const Variant variantA = DGEMM_VARIANT_BIN(N,N,16,16,8,8,8,2,2,64,TAHITI,__ALPHA ) ;
            if ( applicable(variantA,args) ) 
              return &variantA ; 
#endif //#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
            static const Variant variant = DGEMM_VARIANT_BIN(N,N,16,16,8,8,8,2,2,64,HAWAII,__ALPHABETA ) ;
            if ( applicable(variant,args) ) 
              return &variant ; 
           
            //const char * test = DGEMM_KERNEL_NAME(N,N,48,48,8,8,8,6,6, __ALPHA);
           // test
            static const Variant variantA = DGEMM_VARIANT_BIN(N,N,16,16,8,8,8,2,2,64,HAWAII,__ALPHA ) ;
            if ( applicable(variantA,args) ) 
              return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }

#endif
      } 
      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(N,N,24,24,8,8,8,3,3,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ; 

        static const Variant variantA = DGEMM_VARIANT_SRC(N,N,24,24,8,8,8,3,3,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ; 

#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
            static const Variant variant = DGEMM_VARIANT_BIN(N,N,24,24,8,8,8,3,3,64,TAHITI,__ALPHABETA ) ;
            if ( applicable(variant,args) ) 
              return &variant ; 
           
            static const Variant variantA = DGEMM_VARIANT_BIN(N,N,24,24,8,8,8,3,3,64,TAHITI,__ALPHA ) ;
            if ( applicable(variantA,args) ) 
              return &variantA ; 
#endif //#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
            static const Variant variant = DGEMM_VARIANT_BIN(N,N,24,24,8,8,8,3,3,64,HAWAII,__ALPHABETA ) ;
            if ( applicable(variant,args) ) 
              return &variant ; 
           
            static const Variant variantA = DGEMM_VARIANT_BIN(N,N,24,24,8,8,8,3,3,64,HAWAII,__ALPHA ) ;
            if ( applicable(variantA,args) ) 
              return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }

#endif
      } 
      

    }
    if (args.transB == clblasTrans)
    {
            if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(N,T,16,16,8,8,8,2,2,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ; 

        static const Variant variantA = DGEMM_VARIANT_SRC(N,T,16,16,8,8,8,2,2,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ; 

#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
            static const Variant variant = DGEMM_VARIANT_BIN(N,T,16,16,8,8,8,2,2,64,TAHITI,__ALPHABETA ) ;
            if ( applicable(variant,args) ) 
              return &variant ; 
           
           // const char * test = DGEMM_KERNEL_NAME(N,N,48,48,8,8,8,6,6, __ALPHA);
           // test
            static const Variant variantA = DGEMM_VARIANT_BIN(N,T,16,16,8,8,8,2,2,64,TAHITI,__ALPHA ) ;
            if ( applicable(variantA,args) ) 
              return &variantA ; 
#endif //#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
            static const Variant variant = DGEMM_VARIANT_BIN(N,T,16,16,8,8,8,2,2,64,HAWAII,__ALPHABETA ) ;
            if ( applicable(variant,args) ) 
              return &variant ; 
           
            //const char * test = DGEMM_KERNEL_NAME(N,N,48,48,8,8,8,6,6, __ALPHA);
           // test
            static const Variant variantA = DGEMM_VARIANT_BIN(N,T,16,16,8,8,8,2,2,64,HAWAII,__ALPHA ) ;
            if ( applicable(variantA,args) ) 
              return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }

#endif
      } 

      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(N,T,24,24,8,8,8,3,3,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ; 

        static const Variant variantA = DGEMM_VARIANT_SRC(N,T,24,24,8,8,8,3,3,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ; 

#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
            static const Variant variant = DGEMM_VARIANT_BIN(N,T,24,24,8,8,8,3,3,64,TAHITI,__ALPHABETA ) ;
            if ( applicable(variant,args) ) 
              return &variant ; 
           
            static const Variant variantA = DGEMM_VARIANT_BIN(N,T,24,24,8,8,8,3,3,64,TAHITI,__ALPHA ) ;
            if ( applicable(variantA,args) ) 
              return &variantA ;
#endif //#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
            static const Variant variant = DGEMM_VARIANT_BIN(N,T,24,24,8,8,8,3,3,64,HAWAII,__ALPHABETA ) ;
            if ( applicable(variant,args) ) 
              return &variant ; 
           
            static const Variant variantA = DGEMM_VARIANT_BIN(N,T,24,24,8,8,8,3,3,64,HAWAII,__ALPHA ) ;
            if ( applicable(variantA,args) ) 
              return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }

#endif
      } 
    }

  }

  return NULL;
}

clBlasGCNDgemmSmallMatricesFunctor::clBlasGCNDgemmSmallMatricesFunctor(Args & args, const Variant * variant, cl_int & err) 
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
  BinaryLookup bl(context, device, "clBlasGCNDgemmSmallMatricesFunctor");

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
      //for (int i=0; i<4; i++)
      //  if(this->m_variantSplit->source[i] != 0)
         err = bl.buildFromSource(this->m_variant->source);
      //if (VERB) printf(" ===> BUILD PROBLEM WE DON'T SUPPORT SOURCE BUILD FOR SPLIT DGEMM\n") ;
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



clBlasGCNDgemmSmallMatricesFunctor * 
  clBlasGCNDgemmSmallMatricesFunctor::provide(clblasDgemmFunctor::Args & args, const char* DevName) 
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



  CacheSMall::Lookup lookup(cachesmall, ctxt, dev, variant) ;


  if ( lookup.ok() )
  {
    clBlasGCNDgemmSmallMatricesFunctor * functor = lookup.get();
    functor->retain(); // increment the reference counter to avoid deletion while it is still beeing used
    return functor;
  }

  clBlasGCNDgemmSmallMatricesFunctor * functor = new clBlasGCNDgemmSmallMatricesFunctor(args, variant, err);
  if (err != CL_SUCCESS)
  {
    return NULL;
  }

  lookup.set(functor) ;

  return functor;

}


//cl_int clBlasGCNDgemmSmallMatricesFunctor::KernelsLaunch(cl_command_queue queue, cl_kernel Kernel[4], Args &args)
//{
//  size_t GlobalX =args.M/m_variantSplit->bwi[0];
//  GlobalX-=GlobalX%m_variantSplit->ls[0];
//  //
//
//  size_t GlobalY = args.N/m_variantSplit->bwi[1];
//  GlobalY-=GlobalY%m_variantSplit->ls[1];
//
//
//  std::size_t gs[2] = {GlobalX, GlobalY};
//  cl_int error = 0;
//
//  if (args.M%48==0 && args.N%48==0)
//  {
//    if (VERB) printf(" ===> EXECUTE KERNEL 0 \n") ;
//    error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList,args.events);
//    return error;
//  }
//
//  if (args.M%48!=0 && args.N%48!=0 && args.M>=48 && args.N>=48 )
//  {
//    if (VERB) printf(" ===> EXECUTE KERNEL 0, 1, 2, 3 \n") ;
//    error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList,NULL);
//
//    gs[0] = 8;
//    error |= clEnqueueNDRangeKernel(queue, Kernel[1], 2, NULL, gs, m_variantSplit->ls, 0, NULL,NULL);
//
//    gs[1] = 8;
//    gs[0] = GlobalX;
//    error |= clEnqueueNDRangeKernel(queue, Kernel[2], 2, NULL, gs, m_variantSplit->ls, 0, NULL,NULL);
//
//    gs[0] = 8; gs[1] = 8;
//    error |= clEnqueueNDRangeKernel(queue, Kernel[3], 2, NULL, gs, m_variantSplit->ls, 0, NULL,args.events);
//    return error;
//  }
//  if (args.M%48==0 && args.N%48!=0 &&  args.N>48 )
//  {
//    if (VERB) printf(" ===> EXECUTE KERNEL 0, 2, \n") ;
//
//    error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList,NULL);
//    gs[1] = 8;
//    error |= clEnqueueNDRangeKernel(queue, Kernel[2], 2, NULL, gs, m_variantSplit->ls, 0, NULL,NULL);
//
//    return error;
//  }
//  if (args.N%48==0 && args.M%48!=0 &&  args.M>48 )
//  {
//        if (VERB) printf(" ===> EXECUTE KERNEL 0, 1 \n") ;
//
//    error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList,NULL);
//    gs[0] = 8;
//    error |= clEnqueueNDRangeKernel(queue, Kernel[1], 2, NULL, gs, m_variantSplit->ls, 0, NULL,NULL);
//
//    return error;
//  }
//  if(args.M<48 && args.N%48==0)
//  {
//        if (VERB) printf(" ===> EXECUTE KERNEL 1, \n") ;
//
//    gs[0] = 8;
//    error |= clEnqueueNDRangeKernel(queue, Kernel[1], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList, args.events);
//    return error;
//  }
//  if(args.M<48 && args.N%48!=0 && args.N>=48)
//  {
//        if (VERB) printf(" ===> EXECUTE KERNEL  1, 3 \n") ;
//
//    gs[0] = 8;
//    error |= clEnqueueNDRangeKernel(queue, Kernel[1], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList, NULL);
//    gs[1] = 8;
//    error |= clEnqueueNDRangeKernel(queue, Kernel[3], 2, NULL, gs, m_variantSplit->ls, 0, NULL,args.events);
//    return error;
//  }
//  if(args.N<48 && args.M%48==0)
//  {
//        if (VERB) printf(" ===> EXECUTE KERNEL  2 \n") ;
//
//    gs[1] = 8;  
//    error |= clEnqueueNDRangeKernel(queue, Kernel[2], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList, args.events);
//    return error;
//  }
//  if(args.N<48 && args.M%48!=0&& args.M>=48)
//  {
//        if (VERB) printf(" ===> EXECUTE KERNEL 2, 3 \n") ;
//
//    gs[1] = 8;  
//    error |= clEnqueueNDRangeKernel(queue, Kernel[2], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList, NULL);
//
//    gs[0] = 8;
//    error |= clEnqueueNDRangeKernel(queue, Kernel[3], 2, NULL, gs, m_variantSplit->ls, 0, NULL,args.events);
//    return error;
//  }
//  if (args.N<48 && args.M<48)
//  {
//     if (VERB) printf(" ===> EXECUTE KERNEL  3 \n") ;
//    gs[0] = 8; gs[1] = 8;
//    error |= clEnqueueNDRangeKernel(queue, Kernel[3], 2, NULL, gs, m_variantSplit->ls,args.numEventsInWaitList, args.eventWaitList, args.events);
//    return error;
//  }
//
//  return clblasNotImplemented;
//}



//need to rewrite execute!!!
clblasStatus clBlasGCNDgemmSmallMatricesFunctor::execute(Args &args)
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

  setKernelArg<cl_double>(kernel, arg++, args.alpha);
  if (args.beta!=0 && this->m_variant->mult.compare("__ALPHA")!=0)
    setKernelArg<cl_double>(kernel, arg++, args.beta);

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

