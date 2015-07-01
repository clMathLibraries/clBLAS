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
#include <gcn_zgemm.h>

#include "BinaryBuild.h"

//for the moment only managing source code and cl binary

#if BUILD_KERNEL_FROM_STRING
#include "zgemm_gcn.clT"
#else 

#include "zgemm_gcn.clHawaii_64.bin.clT"
//#include "zgemm_gcn.clBonaire_64.bin.clT"

//#include "ZGEMM_gcn.clTahiti_64.bin.clT"
#endif


//
// The name of the 'const char *' providing the kernel OpenCL source
//
//  dgemm_TATB_DIVN_DIVM_DIVK_BS0xBS1_NV0xNV1
//
// For instance, DGEMM_SRC_NAME(N,T,32,64,8,8,8,4,8) is dgemm_NT_32_64_8_8x8_4x8
//
#define ZGEMM_SRC_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,MULT)               zgemm_##TA##TB##_##DIVN##_##DIVM##_##DIVK##_##BS0##x##BS1##_##NV0##x##NV1##MULT
#define ZGEMM_SRC_NAME_TAHITI(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS,MULT)   zgemm_##TA##TB##_##DIVN##_##DIVM##_##DIVK##_##BS0##x##BS1##_##NV0##x##NV1##MULT##_##BITS##_bin_Tahiti
#define ZGEMM_SRC_NAME_HAWAII(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS,MULT)   zgemm_##TA##TB##_##DIVN##_##DIVM##_##DIVK##_##BS0##x##BS1##_##NV0##x##NV1##MULT##_##BITS##_bin_Hawaii
#define ZGEMM_SRC_NAME_BONAIRE(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS,MULT)  zgemm_##TA##TB##_##DIVN##_##DIVM##_##DIVK##_##BS0##x##BS1##_##NV0##x##NV1##MULT##_##BITS##_bin_Bonaire

//
// The name of the 'const char []' global variable that contain the SPIR data.
// That name is similar to the one produced by DGEMM_SRC_NAME but suffixed by _spir
//
#define ZGEMM_SPIR_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,MULT)  zgemm_##TA##TB##_##DIVN##_##DIVM##_##DIVK##_##BS0##x##BS1##_##NV0##x##NV1_spir

//
// The name of the 'const char []' global variable that contain the CL binaries data.
// That name is similar to the one produced by DGEMM_SRC_NAME but suffixed by _bin
//


// The name of the kernel itself.
// This is basically the name returned by DGEMM_SRC_NAME but as string
//
#define ZGEMM_KERNEL_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,MULT) "zgemm_"  #TA #TB "_" #DIVN "_" #DIVM "_" #DIVK "_" #BS0 "x" #BS1 "_" #NV0 "x" #NV1 #MULT

//
// Helpers to transform N and T in proper clblas values for the macros above
//
#define trans_N clblasNoTrans
#define trans_T clblasTrans


// Fill a variant descriptor using OpenCL source 
#define ZGEMM_VARIANT_SRC(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,MULT) { \
  ZGEMM_KERNEL_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,MULT) ,     \
  ZGEMM_SRC_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,MULT) ,        \
  NULL, NULL, 0,                                                \
  trans_##TA, trans_##TB,                                       \
  DIVN,DIVM,DIVK,                                               \
{ BS0, BS1 } ,                                                \
{ NV0, NV1 }                                                  \
} 

// Fill a variant descriptor using SPIR  
#define ZGEMM_VARIANT_SPIR(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,MULT) {  \
  ZGEMM_KERNEL_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1) ,       \
  NULL , "-x spir -spir-std=1.2"                                  \
  ZGEMM_SPIR_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1),          \
  sizeof(ZGEMM_SPIR_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1)),  \
  trans_##TA,trans_##TB,                                          \
  DIVN,DIVM,DIVK,                                                 \
{ BS0, BS1 } ,                                                  \
{ NV0, NV1 }                                                    \
} 

// Fill a variant descriptor using CL Binaries  
#define ZGEMM_VARIANT_BIN_CL1(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS,DEVICE,MULT) {  \
  ZGEMM_KERNEL_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,MULT) ,           \
  NULL , NULL,                                                        \
  ZGEMM_SRC_NAME##_##DEVICE(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS,MULT),          \
  sizeof(ZGEMM_SRC_NAME##_##DEVICE(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS,MULT)),  \
  trans_##TA,trans_##TB,                                              \
  DIVN,DIVM,DIVK,                                                     \
{ BS0, BS1 } ,                                                      \
{ NV0, NV1 }                                                        \
} 


#define ZGEMM_VARIANT_BIN_CL2(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS,DEVICE,MULT) {  \
  ZGEMM_KERNEL_NAME(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,MULT) ,           \
  NULL , "-cl-std=CL2.0",                                                        \
  ZGEMM_SRC_NAME##_##DEVICE(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS,MULT),          \
  sizeof(ZGEMM_SRC_NAME##_##DEVICE(TA,TB,DIVN,DIVM,DIVK,BS0,BS1,NV0,NV1,BITS,MULT)),  \
  trans_##TA,trans_##TB,                                              \
  DIVN,DIVM,DIVK,                                                     \
{ BS0, BS1 } ,                                                      \
{ NV0, NV1 }                                                        \
} 

// Make it 1 to enable additional debug 'print' 
#define VERB 0

// Just because the full name is too long
typedef clblasZgemmFunctorGCN::Variant Variant ; 

//
// The static cache used to store all instances of clblasZgemmFunctorGCN 
//
typedef clblasFunctorCache<clblasZgemmFunctorGCN,const Variant *> Cache ;
static Cache cache  ;


// return true iff a kernel variant is applicable to the specified args
static bool applicable( const Variant & var, clblasZgemmFunctor::Args & args ) 
{
#if 0
  // Transpose values are tested in select_variant
  if ( args.transA != var.transA ) return false ;
  if ( args.transB != var.transB ) return false ;
#endif
  if ( args.N % var.divN != 0 ) return false ; 
  if ( args.M % var.divM != 0 ) return false ; 
  if ( args.K % var.divK != 0 ) return false ; 
  //if ( args.beta==0 && var.mult.compare("__ALPHA")!=0)
  //  return false ;

  return true ;
}

//
// The goal of this function is to return the Variant to be used 
// for the ZGEMM specified by 'args'. 
//
// The variants are typically tested sequentially from the more 
// specific to the more generic. Additional conditions can be 
// placed into the surrounding 'if' (typically that would be 
// to perform additional tests on M, N and K).
// 
//

static const Variant * select_variant( clblasZgemmFunctor::Args & args, const char* DevName, cl_uint _64BitsUse )
{
  if(_64BitsUse!=64)
  {
    std::cout<<"we don't support clblas on 32 bits"<< std::endl;
    assert(1);
    return NULL;
  }

  if ( args.transA == clblasNoTrans ) 
  {
    if ( args.transB == clblasTrans ) 
    {
        //we only manage the binary version here
        if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          //zgemm_NT_32_64_8_16x16_2x4__ALPHABETA_64_bin_Hawaii
          static const Variant variant = ZGEMM_VARIANT_BIN_CL2(N,T,64,32,8,16,16,2,4,64,HAWAII, __ALPHABETA) ;
          if ( applicable(variant,args) ) // needs to return true
            return &variant;
#endif
        }
    }
  }

  return NULL ; // No suitable variant ... will use the fallback

}  

/*
 * constructor
 */
clblasZgemmFunctorGCN::clblasZgemmFunctorGCN(Args & args, const Variant * variant, cl_int & err)  :
  m_program(0) , m_variant(variant)
{

  cl_device_id device;
  cl_context context;

  cl_command_queue queue = args.queue;
  err = getDeviceAndContext(queue, device, context);
  if( err != CL_SUCCESS )
  {
    return;
  }

  if (VERB) printf(" ===> GET KERNEL %s\n", this->m_variant->kernel_name) ;

  //Ben do I use the correct "kernel_name"?
  BinaryLookup bl(context, device, "clblasZgemmFunctorGCN");
  //clGetDeviceInfo(device, CL_DEVICE_NAME);

  bl.variantRaw( this->m_variant->kernel_name, strlen(this->m_variant->kernel_name)+1 ) ;

  if ( !bl.found() ) // may create empty file or may wait until file is ready  
  {
    if ( this->m_variant->bin != 0 ) 
    {
      // build from a pre-compiled version of the kernel (SPIR or cl binaries)
      err = bl.buildFromBinary(this->m_variant->bin, this->m_variant->bin_size, this->m_variant->build_options);
    }
    else
    {
      // directly build from a char* 
      err = bl.buildFromSource(this->m_variant->source);
    } 

    if ( err != CL_SUCCESS )
    {  
      if (VERB) printf(" ===> BUILD PROBLEM\n") ;

      return;
    }
  }

  this->m_program = bl.getProgram();
}

clblasStatus clblasZgemmFunctorGCN::execute(Args &args) 
{
  cl_int err;
  cl_command_queue queue = args.queue;

  if (VERB) printf(" ===> EXECUTE KERNEL %s\n", this->m_variant->kernel_name) ;

  cl_kernel kernel = clCreateKernel( this->m_program, this->m_variant->kernel_name,  &err);
  if (err != CL_SUCCESS) return clblasStatus(err) ;

  if (VERB) printf(" ===> FOUND %s\n", this->m_variant->kernel_name) ;

  int M   = args.M, N = args.N, K = args.K;
  int lda = args.lda, ldb = args.ldb, ldc = args.ldc;

  int offsetA = args.offA;
  int offsetB = args.offB;
  int offsetC = args.offC;

  int arg=0 ; 

  // All zgemm kernels shall have the same arguments: (A,B,C,M,N,K,alpha,beta,lda,ldb,ldc,offa,offb,offc) 
  
  setKernelArg<int>(kernel, arg++, M);
  setKernelArg<int>(kernel, arg++, N);
  setKernelArg<int>(kernel, arg++, K);
  setKernelArg<DoubleComplex>(kernel, arg++, args.alpha);
  setKernelArg<DoubleComplex>(kernel, arg++, args.beta);

  setKernelArg<cl_mem>(kernel, arg++, args.A);
  setKernelArg<cl_mem>(kernel, arg++, args.B);
  setKernelArg<cl_mem>(kernel, arg++, args.C);

  setKernelArg<int>(kernel, arg++, lda);
  setKernelArg<int>(kernel, arg++, ldb);
  setKernelArg<int>(kernel, arg++, ldc);

  setKernelArg<int>(kernel, arg++, offsetA);
  setKernelArg<int>(kernel, arg++, offsetB);
  setKernelArg<int>(kernel, arg++, offsetC);

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


clblasZgemmFunctorGCN * 
  clblasZgemmFunctorGCN::provide(clblasZgemmFunctor::Args & args, const char* DevName) 
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

  const Variant * variant = select_variant( args, DevName, bitness ) ;
  if ( variant == NULL )  
    return NULL ; 



  Cache::Lookup lookup(cache, ctxt, dev, variant) ;

  if ( lookup.ok() )
  {
    clblasZgemmFunctorGCN * functor = lookup.get();
    functor->retain(); // increment the reference counter to avoid deletion while it is still being used
    return functor;
  }

  clblasZgemmFunctorGCN * functor = new clblasZgemmFunctorGCN(args, variant, err);
  if (err != CL_SUCCESS)
  {
    return NULL;
  }

  lookup.set(functor) ;

  return functor;

}

