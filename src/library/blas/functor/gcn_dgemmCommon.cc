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
#include "gcn_dgemmCommon.h"



#if BUILD_KERNEL_FROM_STRING
#include "dgemm_hawai.clT"
#else 

#include "dgemm_hawai.clHawaii_64.bin.clT"


#include "dgemm_hawai.clTahiti_64.bin.clT"
#endif

//cl_uint  _64Bits  = 32;
//dgemm_NT_48_48_8_8x8_6x6_ALPHA_32_bin_Tahiti
//
// The name of the 'const char *' providing the kernel OpenCL source
//
//  dgemm_TATB_DIVN_DIVM_DIVK_BS0xBS1_NV0xNV1
//
// For instance, DGEMM_SRC_NAME(N,T,32,64,8,8,8,4,8) is dgemm_NT_32_64_8_8x8_4x8
//
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


// Make it 1 to enable additional debug 'print' 
#define VERB 0

// Just because the full name is too long
typedef clblasDgemmFunctorGCN::Variant Variant ; 

//
// The static cache used to store all instances of clblasDgemmFunctorTahiti 
//
typedef clblasFunctorCache<clBlasGCNdgemmCommonFunctor,const Variant *> Cache ;
static Cache cache  ;


// return true iff a kernel variant is applicable to the specified args
static bool applicable( const Variant & var, clblasDgemmFunctor::Args & args ) 
{
#if 0
  // Transpose values are tested in select_variant
  if ( args.transA != var.transA ) return false ;
  if ( args.transB != var.transB ) return false ;
#endif
  if ( args.N % var.divN != 0 ) 
    return false ; 
  if ( args.M % var.divM != 0 ) 
    return false ; 
  if ( args.K % var.divK != 0 ) 
    return false ;
  if ( args.beta==0 && var.mult.compare("__ALPHA")!=0)
    return false ;
  return true ;
}

//
// The goal of this function is to return the Variant to be used 
// for the DGEMM specified by 'args'. 
//
// The variants are typically tested sequentially from the more 
// specific to the more generic. Additional conditions can be 
// placed into the surrounding 'if' (typically that would be 
// to perform additional tests on M, N and K).
// 
//
static const Variant * select_variant( clblasDgemmFunctor::Args & args, const char* DevName, cl_uint _64BitsUse )
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

      // ===== dgemm NN ======

      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(N,N,48,48,8,8,8,6,6,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ; 

        static const Variant variantA = DGEMM_VARIANT_SRC(N,N,48,48,8,8,8,6,6,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ; 

#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,N,48,48,8,8,8,6,6,64,TAHITI,__ALPHABETA ) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          //const char * test = DGEMM_KERNEL_NAME(N,N,48,48,8,8,8,6,6, __ALPHA);
          // test
          static const Variant variantA = DGEMM_VARIANT_BIN(N,N,48,48,8,8,8,6,6,64,TAHITI,__ALPHA ) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,N,48,48,8,8,8,6,6,64,HAWAII,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,N,48,48,8,8,8,6,6,64,HAWAII,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }
#endif
      } 

      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(N,N,32,32,8,8,8,4,4,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ; 

        static const Variant variantA = DGEMM_VARIANT_SRC(N,N,32,32,8,8,8,4,4,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ; 
#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,N,32,32,8,8,8,4,4,64,TAHITI,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,N,32,32,8,8,8,4,4,64,TAHITI,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,N,32,32,8,8,8,4,4,64,HAWAII,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,N,32,32,8,8,8,4,4,64,HAWAII,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }
#endif

      } 

      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(N,N,40,40,8,8,8,5,5,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ;

        static const Variant variantA = DGEMM_VARIANT_SRC(N,N,40,40,8,8,8,5,5,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ;
#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,N,40,40,8,8,8,5,5,64,TAHITI,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,N,40,40,8,8,8,5,5,64,TAHITI,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,N,40,40,8,8,8,5,5,64,HAWAII,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 
          static const Variant variantA = DGEMM_VARIANT_BIN(N,N,40,40,8,8,8,5,5,64,HAWAII,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        } 
#endif

      }

      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(N,N,32,32,1,8,8,4,4,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ; 

        static const Variant variantA = DGEMM_VARIANT_SRC(N,N,32,32,1,8,8,4,4,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ; 
#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,N,32,32,1,8,8,4,4,64,TAHITI,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,N,32,32,1,8,8,4,4,64,TAHITI,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,N,32,32,1,8,8,4,4,64,HAWAII,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,N,32,32,1,8,8,4,4,64,HAWAII,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }
#endif       
      } 

      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(N,N,1,1,8,8,8,4,4,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ;

        static const Variant variantA = DGEMM_VARIANT_SRC(N,N,1,1,8,8,8,4,4,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ;
#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,N,1,1,8,8,8,4,4,64,TAHITI,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,N,1,1,8,8,8,4,4,64,TAHITI,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,N,1,1,8,8,8,4,4,64,HAWAII,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,N,1,1,8,8,8,4,4,64,HAWAII,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }
#endif

      } 

      // The generic version shall be last
      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(N,N,1,1,1,8,8,4,4,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ; 

        static const Variant variantA = DGEMM_VARIANT_SRC(N,N,1,1,1,8,8,4,4,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ; 
#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,N,1,1,1,8,8,4,4,64,TAHITI,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,N,1,1,1,8,8,4,4,64,TAHITI,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,N,1,1,1,8,8,4,4,64,HAWAII,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,N,1,1,1,8,8,4,4,64,HAWAII,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ;
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }
#endif

      }        
    } 
    else  
    {
      // ===== dgemm NT ======

      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(N,T,48,48,8,8,8,6,6,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ;

        static const Variant variantA = DGEMM_VARIANT_SRC(N,T,48,48,8,8,8,6,6, __ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ;
#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,T,48,48,8,8,8,6,6,64,TAHITI,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,T,48,48,8,8,8,6,6,64,TAHITI,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,T,48,48,8,8,8,6,6,64,HAWAII,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,T,48,48,8,8,8,6,6,64,HAWAII,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }
#endif

      } 

      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(N,T,32,32,8,8,8,4,4,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ;

        static const Variant variantA = DGEMM_VARIANT_SRC(N,T,32,32,8,8,8,4,4,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ;
#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,T,32,32,8,8,8,4,4,64,TAHITI,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,T,32,32,8,8,8,4,4,64,TAHITI,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,T,32,32,8,8,8,4,4,64,HAWAII,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,T,32,32,8,8,8,4,4,64,HAWAII,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }
#endif

      } 

      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(N,T,40,40,8,8,8,5,5,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ;

        static const Variant variantA = DGEMM_VARIANT_SRC(N,T,40,40,8,8,8,5,5,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ;
#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,T,40,40,8,8,8,5,5,64,TAHITI,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,T,40,40,8,8,8,5,5,64,TAHITI,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,T,40,40,8,8,8,5,5,64,HAWAII,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,T,40,40,8,8,8,5,5,64,HAWAII,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        } 
#endif

      }

      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(N,T,32,32,1,8,8,4,4,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ;

        static const Variant variantA = DGEMM_VARIANT_SRC(N,T,32,32,1,8,8,4,4,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ;
#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,T,32,32,1,8,8,4,4,64,TAHITI,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,T,32,32,1,8,8,4,4,64,TAHITI, __ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,T,32,32,1,8,8,4,4,64,HAWAII,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,T,32,32,1,8,8,4,4,64,HAWAII,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }
#endif

      } 

      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(N,T,1,1,8,8,8,4,4,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ; 

        static const Variant variantA = DGEMM_VARIANT_SRC(N,T,1,1,8,8,8,4,4,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ; 
#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,T,1,1,8,8,8,4,4,64,TAHITI,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,T,1,1,8,8,8,4,4,64,TAHITI,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,T,1,1,8,8,8,4,4,64,HAWAII,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,T,1,1,8,8,8,4,4,64,HAWAII,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }
#endif

      } 

      // The generic version shall be last
      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(N,T,1,1,1,8,8,4,4,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ; 

        static const Variant variantA = DGEMM_VARIANT_SRC(N,T,1,1,1,8,8,4,4,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ; 
#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,T,1,1,1,8,8,4,4,64,TAHITI,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,T,1,1,1,8,8,4,4,64,TAHITI,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif

        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(N,T,1,1,1,8,8,4,4,64,HAWAII,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(N,T,1,1,1,8,8,4,4,64,HAWAII,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL


        }
#endif

      } 
    }
  }
  else 
  {
    if ( args.transB == clblasNoTrans ) 
    {
      // ===== dgemm TN ======

      if ( args.M >= 2000 && args.N >= 2000 ) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(T,N,48,48,16,8,8,6,6,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ;

        static const Variant variantA = DGEMM_VARIANT_SRC(T,N,48,48,16,8,8,6,6,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ;
#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(T,N,48,48,16,8,8,6,6,64,TAHITI,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(T,N,48,48,16,8,8,6,6,64,TAHITI,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif

        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(T,N,48,48,16,8,8,6,6,64,HAWAII,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ;

          static const Variant variantA = DGEMM_VARIANT_BIN(T,N,48,48,16,8,8,6,6,64,HAWAII,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ;
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }
#endif

      } 

      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(T,N,48,48,8,8,8,6,6,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ;

        static const Variant variantA = DGEMM_VARIANT_SRC(T,N,48,48,8,8,8,6,6,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ;
#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(T,N,48,48,8,8,8,6,6,64,TAHITI,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(T,N,48,48,8,8,8,6,6,64,TAHITI,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(T,N,48,48,8,8,8,6,6,64,HAWAII,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(T,N,48,48,8,8,8,6,6,64,HAWAII, __ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }
#endif

      } 

      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(T,N,32,32,16,8,16,4,2,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ;

        static const Variant variantA = DGEMM_VARIANT_SRC(T,N,32,32,16,8,16,4,2,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ;
#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(T,N,32,32,16,8,16,4,2,64,TAHITI,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(T,N,32,32,16,8,16,4,2,64,TAHITI,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(T,N,32,32,16,8,16,4,2,64,HAWAII,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(T,N,32,32,16,8,16,4,2,64,HAWAII,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ;
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }
#endif       
      } 

      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(T,N,32,32,1,8,16,4,2,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ; 

        static const Variant variantA = DGEMM_VARIANT_SRC(T,N,32,32,1,8,16,4,2,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ; 
#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(T,N,32,32,1,8,16,4,2,64,TAHITI,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(T,N,32,32,1,8,16,4,2,64,TAHITI,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(T,N,32,32,1,8,16,4,2,64,HAWAII,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ;

          static const Variant variantA = DGEMM_VARIANT_BIN(T,N,32,32,1,8,16,4,2,64,HAWAII,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ;
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }
#endif

      } 

      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(T,N,1,1,16,8,16,4,2,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ; 

        static const Variant variantA = DGEMM_VARIANT_SRC(T,N,1,1,16,8,16,4,2,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ; 
#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(T,N,1,1,16,8,16,4,2,64,TAHITI,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(T,N,1,1,16,8,16,4,2,64,TAHITI,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ;
#endif
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(T,N,1,1,16,8,16,4,2,64,HAWAII,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(T,N,1,1,16,8,16,4,2,64,HAWAII, __ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif //#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        }

#endif

      } 

      // The generic version shall be last
      if (true) 
      {
#if BUILD_KERNEL_FROM_STRING
        static const Variant variant = DGEMM_VARIANT_SRC(T,N,1,1,1,8,16,4,2,__ALPHABETA) ;
        if ( applicable(variant,args) ) 
          return &variant ; 

        static const Variant variantA = DGEMM_VARIANT_SRC(T,N,1,1,1,8,16,4,2,__ALPHA) ;
        if ( applicable(variantA,args) ) 
          return &variantA ;
#else 
        if(!strcmp(DevName, "Tahiti"))
        {
#ifndef CLBLAS_TAHITI_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(T,N,1,1,1,8,16,4,2,64,TAHITI,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(T,N,1,1,1,8,16,4,2,64,TAHITI,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif //CLBLAS_TAHITI_DYNAMIC_KERNEL
        }
        else if(!strcmp(DevName, "Hawaii"))
        {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
          static const Variant variant = DGEMM_VARIANT_BIN(T,N,1,1,1,8,16,4,2,64,HAWAII,__ALPHABETA) ;
          if ( applicable(variant,args) ) 
            return &variant ; 

          static const Variant variantA = DGEMM_VARIANT_BIN(T,N,1,1,1,8,16,4,2,64,HAWAII,__ALPHA) ;
          if ( applicable(variantA,args) ) 
            return &variantA ; 
#endif //CLBLAS_HAWAII_DYNAMIC_KERNEL
        }

#endif

      } 


    }
    else
    {
      // ===== dgemm TT ======

      // TODO 
    }
  }


  return NULL ; // No suitable variant ... will use the fallback

}  



clBlasGCNdgemmCommonFunctor::clBlasGCNdgemmCommonFunctor(Args & args, const Variant * variant, cl_int & err)

{

  cl_device_id device;
  cl_context context;


  m_program = NULL;
  m_variant = variant;

  cl_command_queue queue = args.queue;
  err = getDeviceAndContext(queue, device, context);
  if( err != CL_SUCCESS )
  {
    return;
  }

  if (VERB) printf(" ===> GET KERNEL %s\n", this->m_variant->kernel_name) ;

  //Ben do I use the correct "kernel_name"?
  BinaryLookup bl(context, device, "clBlasGCNdgemmCommonFunctor");

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



clBlasGCNdgemmCommonFunctor * 
  clBlasGCNdgemmCommonFunctor::provide(clblasDgemmFunctor::Args & args, const char* DevName) 
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

  if ( lookup.ok() ){
    clBlasGCNdgemmCommonFunctor * functor = lookup.get();
    functor->retain(); // increment the reference counter to avoid deletion while it is still beeing used
    return functor;
  }

  clBlasGCNdgemmCommonFunctor * functor = new clBlasGCNdgemmCommonFunctor(args, variant, err);
  if (err != CL_SUCCESS)
  {
    return NULL;
  }

  lookup.set(functor) ;

  return functor;

}
