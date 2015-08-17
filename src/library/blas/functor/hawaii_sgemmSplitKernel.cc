#if !defined CLBLAS_HAWAII_DYNAMIC_KERNEL || !defined CLBLAS_BONAIRE_DYNAMIC_KERNEL
//this split kernel algorithm solves the main matrix with 96x96 micro tile size
//solves the row boundry with 16x96 micro tile size
//solves the column boundry with 96x16 micro tile size
//solves the rest boundry with 16x16 micro tile size
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
#include "hawaii_sgemmSplitKernel.h"


#if BUILD_KERNEL_FROM_STRING
#include "sgemm_hawaiiSplitKernel.clT"
#else 

#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
#include "sgemm_hawaiiSplitKernel.clHawaii_64.bin.clT"
#endif//CLBLAS_HAWAII_DYNAMIC_KERNEL

#ifndef CLBLAS_BONAIRE_DYNAMIC_KERNEL
#include "sgemm_hawaiiSplitKernel.clBonaire_64.bin.clT"
#endif //CLBLAS_BONAIRE_DYNAMIC_KERNEL

#endif //BUILD_KERNEL_FROM_STRING

// Just because the full name is too long
typedef clBlashawaiiSgemmSplitKernelFunctor::Variant Variant ; 

//define the string name of the soure/binary code
#define SGEMM_SRC_NAME(TA,TB, DIVK, MULT)    sgemm_##TA##TB##_##DIVK##_SPLIT##MULT
#define SGEMM_SRC_NAME_HAWAII(TA,TB, DIVK, MULT, BITS)   sgemm_##TA##TB##_##DIVK##_SPLIT##MULT##_##BITS##_bin_Hawaii
#define SGEMM_SRC_NAME_BONAIRE(TA,TB, DIVK, MULT, BITS)   sgemm_##TA##TB##_##DIVK##_SPLIT##MULT##_##BITS##_bin_Bonaire
#define SGEMM_SRC_NAME_BIN(TA,TB, DIVK, MULT, BITS, DEVICE)   SGEMM_SRC_NAME##_##DEVICE(TA,TB, DIVK, MULT, BITS)


//variant name used to differentiate the different ones
#define SGEMM_VARIANT_NAME(TA,TB, DIVK, MULT) "sgemm_" #TA #TB "_" #DIVK "_SPLIT" #MULT
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

typedef clblasFunctorCache<clBlashawaiiSgemmSplitKernelFunctor,const Variant *> CacheSplit ;
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
      // return NULL;
      const char* KName_NNMain = SGEMM_KERNEL_NAME(N, N, 96, 96, 16, 16, 16, 6, 6, __ALPHABETA, MAIN) ;
      const char* KName_NNRow = SGEMM_KERNEL_NAME(N, N, 1, 96, 16, 16, 16, 6, 6, __ALPHABETA, ROW) ;
      const char* KName_NNColumn = SGEMM_KERNEL_NAME(N, N, 96, 1, 16, 16, 16, 6, 6, __ALPHABETA, COLUMN) ;
      const char* KName_NNSingleWave = SGEMM_KERNEL_NAME(N, N, 1, 1, 16, 16, 16, 6, 6, __ALPHABETA, SINGLE) ;

      const char* KName_NNMainAlpha = SGEMM_KERNEL_NAME(N, N, 96, 96, 16, 16, 16, 6, 6, __ALPHA, MAIN) ;
      const char* KName_NNRowAlpha = SGEMM_KERNEL_NAME(N, N, 1, 96, 16, 16, 16, 6, 6, __ALPHA, ROW) ;
      const char* KName_NNColumnAlpha = SGEMM_KERNEL_NAME(N, N, 96, 1, 16, 16, 16, 6, 6, __ALPHA, COLUMN) ;
      const char* KName_NNSingleWaveAlpha = SGEMM_KERNEL_NAME(N, N, 1, 1, 16, 16, 16, 6, 6, __ALPHA, SINGLE) ;

      const char* KName_NNMainK1 = SGEMM_KERNEL_NAME(N, N, 96, 96, 1, 16, 16, 6, 6, __ALPHABETA, MAIN) ;
      const char* KName_NNRowK1 = SGEMM_KERNEL_NAME(N, N, 1, 96, 1, 16, 16, 6, 6, __ALPHABETA, ROW) ;
      const char* KName_NNColumnK1 = SGEMM_KERNEL_NAME(N, N, 96, 1, 1, 16, 16, 6, 6, __ALPHABETA, COLUMN) ;
      const char* KName_NNSingleWaveK1 = SGEMM_KERNEL_NAME(N, N, 1, 1, 1, 16, 16, 6, 6, __ALPHABETA, SINGLE) ;

      const char* KName_NNMainK1Alpha = SGEMM_KERNEL_NAME(N, N, 96, 96, 1, 16, 16, 6, 6, __ALPHA, MAIN) ;
      const char* KName_NNRowK1Alpha = SGEMM_KERNEL_NAME(N, N, 1, 96, 1, 16, 16, 6, 6, __ALPHA, ROW) ;
      const char* KName_NNColumnK1Alpha = SGEMM_KERNEL_NAME(N, N, 96, 1, 1, 16, 16, 6, 6, __ALPHA, COLUMN) ;
      const char* KName_NNSingleWaveK1Alpha = SGEMM_KERNEL_NAME(N, N, 1, 1, 1, 16, 16, 6, 6, __ALPHA, SINGLE) ;

#if BUILD_KERNEL_FROM_STRING
      const char* KSrc_NTMain = SGEMM_SRC_NAME(N, N, 48, 48, 8, 8, 8, 6, 6, __ALPHABETA) ;
      const char* KSrc_NTRow = SGEMM_SRC_NAME(N, N, 1, 48, 8,8, 8, 6, 6, __ALPHABETA) ;
      const char* KSrc_NTColumn = SGEMM_SRC_NAME(N, N, 48, 1, 8, 8, 8, 6, 6, __ALPHABETA) ;
      const char* KSrc_NTSingleWave = SGEMM_SRC_NAME(N, N, 1, 1, 8, 8, 8, 6, 6, __ALPHABETA) ;
#else

      const char* KBin_NNMain64 ;           
      size_t KBin_NNMainSize64 = 0;       

      const char* KBin_NNMainAlpha64  ;     
      size_t KBin_NNMainAlphaSize64 = 0;    

      const char* KBin_NNMainK164   ;       
      size_t KBin_NNMainK1Size64 = 0;       

      const char* KBin_NNMainK1Alpha64 ;    
      size_t KBin_NNMainK1AlphaSize64 = 0; 

      if (!strcmp(DevName, "Hawaii"))
      {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        KBin_NNMain64             = SGEMM_SRC_NAME_BIN(N, N, 16, __ALPHABETA,  64, HAWAII) ;
        KBin_NNMainSize64        = sizeof(SGEMM_SRC_NAME_BIN(N, N, 16, __ALPHABETA,  64, HAWAII)) ;

        KBin_NNMainAlpha64        = SGEMM_SRC_NAME_BIN(N, N, 16, __ALPHA,  64, HAWAII) ;
        KBin_NNMainAlphaSize64   = sizeof(SGEMM_SRC_NAME_BIN(N, N, 16, __ALPHA,  64, HAWAII)) ;

        KBin_NNMainK164           = SGEMM_SRC_NAME_BIN(N, N, 1, __ALPHABETA,  64, HAWAII) ;
        KBin_NNMainK1Size64      = sizeof(SGEMM_SRC_NAME_BIN(N, N, 1, __ALPHABETA,  64, HAWAII)) ;

        KBin_NNMainK1Alpha64      = SGEMM_SRC_NAME_BIN(N, N, 1, __ALPHA,  64, HAWAII) ;
        KBin_NNMainK1AlphaSize64 = sizeof(SGEMM_SRC_NAME_BIN(N, N, 1, __ALPHA,  64, HAWAII)) ;
      
#endif //CLBLAS_HAWAII_DYNAMIC_KERNEL
      }
      
      else if (!strcmp(DevName, "Bonaire"))
      {
#ifndef CLBLAS_BONAIRE_DYNAMIC_KERNEL
        KBin_NNMain64             = SGEMM_SRC_NAME_BIN(N, N, 16, __ALPHABETA,  64, BONAIRE) ;
        KBin_NNMainSize64        = sizeof(SGEMM_SRC_NAME_BIN(N, N, 16, __ALPHABETA,  64, BONAIRE)) ;

        KBin_NNMainAlpha64        = SGEMM_SRC_NAME_BIN(N, N, 16, __ALPHA,  64, BONAIRE) ;
        KBin_NNMainAlphaSize64   = sizeof(SGEMM_SRC_NAME_BIN(N, T, 16, __ALPHA,  64, BONAIRE)) ;

        KBin_NNMainK164           = SGEMM_SRC_NAME_BIN(N, N, 1, __ALPHABETA,  64, BONAIRE) ;
        KBin_NNMainK1Size64      = sizeof(SGEMM_SRC_NAME_BIN(N, N, 1, __ALPHABETA,  64, BONAIRE)) ;

        KBin_NNMainK1Alpha64      = SGEMM_SRC_NAME_BIN(N, N, 1, __ALPHA,  64, BONAIRE) ;
        KBin_NNMainK1AlphaSize64 = sizeof(SGEMM_SRC_NAME_BIN(N, N, 1, __ALPHA,  64, BONAIRE)) ;
#endif //#ifndef CLBLAS_BONAIRE_DYNAMIC_KERNEL
      }
#endif
      if(args.K%16==0)
      {
        if (args.beta!=0)
        {

          if(_64BitsUse==64)
          {
            static const Variant variant = SGEMM_VARIANT_OBJ(N,N,16,16,16,6,6,64,__ALPHABETA, 
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
          }   
        }
        else
        {
            static const Variant variant = SGEMM_VARIANT_OBJ(N,N,16,16,16,6,6,64,__ALPHA,
              KName_NNMainAlpha,KName_NNRowAlpha, KName_NNColumnAlpha, KName_NNSingleWaveAlpha ,
              NULL,
              NULL,
              KBin_NNMainAlpha64,
              KBin_NNMainAlphaSize64) ;

            return &variant ; 
        }
      }
      else
      {
        if (args.beta!=0)
        {

            static const Variant variant = SGEMM_VARIANT_OBJ(N,N,1,16,16,6,6,64,__ALPHABETA, 
              KName_NNMainK1,KName_NNRowK1, KName_NNColumnK1, KName_NNSingleWaveK1 ,
              NULL,
              NULL,
              KBin_NNMainK164,
              KBin_NNMainK1Size64) ;

            return &variant ; 
        }
        else
        {
            static const Variant variant = SGEMM_VARIANT_OBJ(N,N,1,16,16,6,6,64,__ALPHA,
              KName_NNMainK1Alpha,KName_NNRowK1Alpha, KName_NNColumnK1Alpha, KName_NNSingleWaveK1Alpha ,
              NULL,
              NULL,
              KBin_NNMainK1Alpha64,
              KBin_NNMainK1AlphaSize64) ;

            return &variant ; 
        }
      }


    }
    if (args.transB == clblasTrans)
    {

      const char* KName_NTMain = SGEMM_KERNEL_NAME(N, T, 96, 96, 16, 16, 16, 6, 6, __ALPHABETA, MAIN) ;
      const char* KName_NTRow = SGEMM_KERNEL_NAME(N, T, 1, 96, 16, 16, 16, 6, 6, __ALPHABETA, ROW) ;
      const char* KName_NTColumn = SGEMM_KERNEL_NAME(N, T, 96, 1, 16, 16, 16, 6, 6, __ALPHABETA, COLUMN) ;
      const char* KName_NTSingleWave = SGEMM_KERNEL_NAME(N, T, 1, 1, 16, 16, 16, 6, 6, __ALPHABETA, SINGLE) ;

      const char* KName_NTMainAlpha = SGEMM_KERNEL_NAME(N, T, 96, 96, 16, 16, 16, 6, 6, __ALPHA, MAIN) ;
      const char* KName_NTRowAlpha = SGEMM_KERNEL_NAME(N, T, 1, 96, 16, 16, 16, 6, 6, __ALPHA, ROW) ;
      const char* KName_NTColumnAlpha = SGEMM_KERNEL_NAME(N, T, 96, 1, 16, 16, 16, 6, 6, __ALPHA, COLUMN) ;
      const char* KName_NTSingleWaveAlpha = SGEMM_KERNEL_NAME(N, T, 1, 1, 16, 16, 16, 6, 6, __ALPHA, SINGLE) ;

      const char* KName_NTMainK1 = SGEMM_KERNEL_NAME(N, T, 96, 96, 1, 16, 16, 6, 6, __ALPHABETA, MAIN) ;
      const char* KName_NTRowK1 = SGEMM_KERNEL_NAME(N, T, 1, 96, 1, 16, 16, 6, 6, __ALPHABETA, ROW) ;
      const char* KName_NTColumnK1 = SGEMM_KERNEL_NAME(N, T, 96, 1, 1, 16, 16, 6, 6, __ALPHABETA, COLUMN) ;
      const char* KName_NTSingleWaveK1 = SGEMM_KERNEL_NAME(N, T, 1, 1, 1, 16, 16, 6, 6, __ALPHABETA, SINGLE) ;

      const char* KName_NTMainK1Alpha = SGEMM_KERNEL_NAME(N, T, 96, 96, 1, 16, 16, 6, 6, __ALPHA, MAIN) ;
      const char* KName_NTRowK1Alpha = SGEMM_KERNEL_NAME(N, T, 1, 96, 1, 16, 16, 6, 6, __ALPHA, ROW) ;
      const char* KName_NTColumnK1Alpha = SGEMM_KERNEL_NAME(N, T, 96, 1, 1, 16, 16, 6, 6, __ALPHA, COLUMN) ;
      const char* KName_NTSingleWaveK1Alpha = SGEMM_KERNEL_NAME(N, T, 1, 1, 1, 16, 16, 6, 6, __ALPHA, SINGLE) ;

      const char* KBin_NTMain64 ;           
      size_t KBin_NTMainSize64 = 0;       

      const char* KBin_NTMainAlpha64  ;     
      size_t KBin_NTMainAlphaSize64 = 0;    

      const char* KBin_NTMainK164   ;       
      size_t KBin_NTMainK1Size64 = 0;       

      const char* KBin_NTMainK1Alpha64 ;    
      size_t KBin_NTMainK1AlphaSize64 = 0;   

#if BUILD_KERNEL_FROM_STRING
      const char* KSrc_NTMain = SGEMM_SRC_NAME(N, T, 96, 96, 16, 16, 16, 6, 6, __ALPHABETA) ;
      const char* KSrc_NTRow = SGEMM_SRC_NAME(N, T, 1, 96, 16,16, 16, 6, 6, __ALPHABETA) ;
      const char* KSrc_NTColumn = SGEMM_SRC_NAME(N, T, 96, 1, 16, 16, 16, 6, 6, __ALPHABETA) ;
      const char* KSrc_NTSingleWave = SGEMM_SRC_NAME(N, T, 1, 1, 16, 16, 16, 6, 6, __ALPHABETA) ;
#else


      if (!strcmp(DevName, "Hawaii"))
      {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        KBin_NTMain64             = SGEMM_SRC_NAME_BIN(N, T, 16, __ALPHABETA,  64, HAWAII) ;
        KBin_NTMainSize64        = sizeof(SGEMM_SRC_NAME_BIN(N, T, 16, __ALPHABETA,  64, HAWAII)) ;

        KBin_NTMainAlpha64        = SGEMM_SRC_NAME_BIN(N, T, 16, __ALPHA,  64, HAWAII) ;
        KBin_NTMainAlphaSize64   = sizeof(SGEMM_SRC_NAME_BIN(N, T, 16, __ALPHA,  64, HAWAII)) ;

        KBin_NTMainK164           = SGEMM_SRC_NAME_BIN(N, T, 1, __ALPHABETA,  64, HAWAII) ;
        KBin_NTMainK1Size64      = sizeof(SGEMM_SRC_NAME_BIN(N, T, 1, __ALPHABETA,  64, HAWAII)) ;

        KBin_NTMainK1Alpha64      = SGEMM_SRC_NAME_BIN(N, T, 1, __ALPHA,  64, HAWAII) ;
        KBin_NTMainK1AlphaSize64 = sizeof(SGEMM_SRC_NAME_BIN(N, T, 1, __ALPHA,  64, HAWAII)) ;
#endif //CLBLAS_HAWAII_DYNAMIC_KERNEL
      }

      else if (!strcmp(DevName, "Bonaire"))
      {
#ifndef CLBLAS_BONAIRE_DYNAMIC_KERNEL
        KBin_NTMain64             = SGEMM_SRC_NAME_BIN(N, T, 16, __ALPHABETA,  64, BONAIRE) ;
        KBin_NTMainSize64        = sizeof(SGEMM_SRC_NAME_BIN(N, T, 16, __ALPHABETA,  64, BONAIRE)) ;

        KBin_NTMainAlpha64        = SGEMM_SRC_NAME_BIN(N, T, 16, __ALPHA,  64, BONAIRE) ;
        KBin_NTMainAlphaSize64   = sizeof(SGEMM_SRC_NAME_BIN(N, T, 16, __ALPHA,  64, BONAIRE)) ;

        KBin_NTMainK164           = SGEMM_SRC_NAME_BIN(N, T, 1, __ALPHABETA,  64, BONAIRE) ;
        KBin_NTMainK1Size64      = sizeof(SGEMM_SRC_NAME_BIN(N, T, 1, __ALPHABETA,  64, BONAIRE)) ;

        KBin_NTMainK1Alpha64      = SGEMM_SRC_NAME_BIN(N, T, 1, __ALPHA,  64, BONAIRE) ;
        KBin_NTMainK1AlphaSize64 = sizeof(SGEMM_SRC_NAME_BIN(N, T, 1, __ALPHA,  64, BONAIRE)) ;
#endif //#ifndef CLBLAS_BONAIRE_DYNAMIC_KERNEL
      }
#endif

      // ===== SGEMM NT ======
      if(args.K%16==0)
      {
        if (args.beta!=0)
        {

          static const Variant variant = SGEMM_VARIANT_OBJ(N,T,16,16,16,6,6,64,__ALPHABETA, 
            KName_NTMain,KName_NTRow, KName_NTColumn, KName_NTSingleWave ,
            NULL,
            NULL,
            KBin_NTMain64,
            KBin_NTMainSize64) ;

          return &variant ; 
        }
        else
        {
          static const Variant variant = SGEMM_VARIANT_OBJ(N,T,16,16,16,6,6,64,__ALPHA,
            KName_NTMainAlpha,KName_NTRowAlpha, KName_NTColumnAlpha, KName_NTSingleWaveAlpha ,
            NULL,
            NULL,
            KBin_NTMainAlpha64,
            KBin_NTMainAlphaSize64) ;

          return &variant ; 
        }
      }
      else
      {
        if (args.beta!=0)
        {

          static const Variant variant = SGEMM_VARIANT_OBJ(N,T,1,16,16,6,6,64,__ALPHABETA, 
            KName_NTMainK1,KName_NTRowK1, KName_NTColumnK1, KName_NTSingleWaveK1 ,
            NULL,
            NULL,
            KBin_NTMainK164,
            KBin_NTMainK1Size64) ;

          return &variant ; 
        }
        else
        {
          static const Variant variant = SGEMM_VARIANT_OBJ(N,T,1,16,16,6,6,64,__ALPHA,
            KName_NTMainK1Alpha,KName_NTRowK1Alpha, KName_NTColumnK1Alpha, KName_NTSingleWaveK1Alpha ,
            NULL,
            NULL,
            KBin_NTMainK1Alpha64,
            KBin_NTMainK1AlphaSize64) ;

          return &variant ; 
        }
      }

    }
  }
  else
  {
    if ( args.transB == clblasNoTrans ) 
    {

      // ===== sgemm TN ======
      // return NULL;
      const char* KName_TNMain = SGEMM_KERNEL_NAME(T, N, 96, 96, 16, 16, 16, 6, 6, __ALPHABETA, MAIN) ;
      const char* KName_TNRow = SGEMM_KERNEL_NAME(T, N, 1, 96, 16, 16, 16, 6, 6, __ALPHABETA, ROW) ;
      const char* KName_TNColumn = SGEMM_KERNEL_NAME(T, N, 96, 1, 16, 16, 16, 6, 6, __ALPHABETA, COLUMN) ;
      const char* KName_TNSingleWave = SGEMM_KERNEL_NAME(T, N, 1, 1, 16, 16, 16, 6, 6, __ALPHABETA, SINGLE) ;

      const char* KName_TNMainAlpha = SGEMM_KERNEL_NAME(T, N, 96, 96, 16, 16, 16, 6, 6, __ALPHA, MAIN) ;
      const char* KName_TNRowAlpha = SGEMM_KERNEL_NAME(T, N, 1, 96, 16, 16, 16, 6, 6, __ALPHA, ROW) ;
      const char* KName_TNColumnAlpha = SGEMM_KERNEL_NAME(T, N, 96, 1, 16, 16, 16, 6, 6, __ALPHA, COLUMN) ;
      const char* KName_TNSingleWaveAlpha = SGEMM_KERNEL_NAME(T, N, 1, 1, 16, 16, 16, 6, 6, __ALPHA, SINGLE) ;

      //const char* KName_TNMainK1 = SGEMM_KERNEL_NAME(N, N, 96, 96, 1, 16, 16, 6, 6, __ALPHABETA, MAIN) ;
      //const char* KName_TNRowK1 = SGEMM_KERNEL_NAME(N, N, 1, 96, 1, 16, 16, 6, 6, __ALPHABETA, ROW) ;
      //const char* KName_TNColumnK1 = SGEMM_KERNEL_NAME(N, N, 96, 1, 1, 16, 16, 6, 6, __ALPHABETA, COLUMN) ;
      //const char* KName_TNSingleWaveK1 = SGEMM_KERNEL_NAME(N, N, 1, 1, 1, 16, 16, 6, 6, __ALPHABETA, SINGLE) ;
      //                   
      //const char* KName_TNMainK1Alpha = SGEMM_KERNEL_NAME(N, N, 96, 96, 1, 16, 16, 6, 6, __ALPHA, MAIN) ;
      //const char* KName_TNRowK1Alpha = SGEMM_KERNEL_NAME(N, N, 1, 96, 1, 16, 16, 6, 6, __ALPHA, ROW) ;
      //const char* KName_TNColumnK1Alpha = SGEMM_KERNEL_NAME(N, N, 96, 1, 1, 16, 16, 6, 6, __ALPHA, COLUMN) ;
      //const char* KName_TNSingleWaveK1Alpha = SGEMM_KERNEL_NAME(N, N, 1, 1, 1, 16, 16, 6, 6, __ALPHA, SINGLE) ;

#if BUILD_KERNEL_FROM_STRING
      const char* KSrc_TNMain = SGEMM_SRC_NAME(T, N, 48, 48, 8, 8, 8, 6, 6, __ALPHABETA) ;
      const char* KSrc_TNRow = SGEMM_SRC_NAME(T, N, 1, 48, 8,8, 8, 6, 6, __ALPHABETA) ;
      const char* KSrc_TNColumn = SGEMM_SRC_NAME(T, N, 48, 1, 8, 8, 8, 6, 6, __ALPHABETA) ;
      const char* KSrc_TNSingleWave = SGEMM_SRC_NAME(T, N, 1, 1, 8, 8, 8, 6, 6, __ALPHABETA) ;
#else

      const char* KBin_TNMain64 ;           
      size_t KBin_TNMainSize64 = 0;       

      const char* KBin_TNMainAlpha64  ;     
      size_t KBin_TNMainAlphaSize64 = 0;    

      //const char* KBin_NNMainK164   ;       
      //size_t KBin_NNMainK1Size64 = 0;       

      //const char* KBin_NNMainK1Alpha64 ;    
      //size_t KBin_NNMainK1AlphaSize64 = 0;  

      if (!strcmp(DevName, "Hawaii"))
      {
#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
        KBin_TNMain64             = SGEMM_SRC_NAME_BIN(T, N, 16, __ALPHABETA,  64, HAWAII) ;
        KBin_TNMainSize64        = sizeof(SGEMM_SRC_NAME_BIN(T, N, 16, __ALPHABETA,  64, HAWAII)) ;
             
        KBin_TNMainAlpha64        = SGEMM_SRC_NAME_BIN(T, N, 16, __ALPHA,  64, HAWAII) ;
        KBin_TNMainAlphaSize64   = sizeof(SGEMM_SRC_NAME_BIN(T, N, 16, __ALPHA,  64, HAWAII)) ;

        //KBin_NNMainK164           = SGEMM_SRC_NAME_BIN(N, N, 1, __ALPHABETA,  64, HAWAII) ;
        //KBin_NNMainK1Size64      = sizeof(SGEMM_SRC_NAME_BIN(N, N, 1, __ALPHABETA,  64, HAWAII)) ;

        //KBin_NNMainK1Alpha64      = SGEMM_SRC_NAME_BIN(N, N, 1, __ALPHA,  64, HAWAII) ;
        //KBin_NNMainK1AlphaSize64 = sizeof(SGEMM_SRC_NAME_BIN(N, N, 1, __ALPHA,  64, HAWAII)) ;
#endif  //CLBLAS_HAWAII_DYNAMIC_KERNEL
      }

      else if (!strcmp(DevName, "Bonaire"))
      {
#ifndef CLBLAS_BONAIRE_DYNAMIC_KERNEL
        KBin_TNMain64             = SGEMM_SRC_NAME_BIN(T, N, 16, __ALPHABETA,  64, BONAIRE) ;
        KBin_TNMainSize64         = sizeof(SGEMM_SRC_NAME_BIN(T, N, 16, __ALPHABETA,  64, BONAIRE)) ;
             
        KBin_TNMainAlpha64        = SGEMM_SRC_NAME_BIN(T, N, 16, __ALPHA,  64, BONAIRE) ;
        KBin_TNMainAlphaSize64    = sizeof(SGEMM_SRC_NAME_BIN(T, N, 16, __ALPHA,  64, BONAIRE)) ;

        //KBin_NNMainK164           = SGEMM_SRC_NAME_BIN(N, N, 1, __ALPHABETA,  64, BONAIRE) ;
        //KBin_NNMainK1Size64      = sizeof(SGEMM_SRC_NAME_BIN(N, N, 1, __ALPHABETA,  64, BONAIRE)) ;

        //KBin_NNMainK1Alpha64      = SGEMM_SRC_NAME_BIN(N, N, 1, __ALPHA,  64, BONAIRE) ;
        //KBin_NNMainK1AlphaSize64 = sizeof(SGEMM_SRC_NAME_BIN(N, N, 1, __ALPHA,  64, BONAIRE)) ;
#endif  //#ifndef CLBLAS_BONAIRE_DYNAMIC_KERNEL
      }
#endif
      if(args.K%16==0)
      {
        if (args.beta!=0)
        {

          
            static const Variant variant = SGEMM_VARIANT_OBJ(T,N,16,16,16,6,6,64,__ALPHABETA, 
              KName_TNMain,KName_TNRow, KName_TNColumn, KName_TNSingleWave ,
              NULL,
              NULL,
              KBin_TNMain64,
              KBin_TNMainSize64) ;

            return &variant ; 
        }
        else
        {
            static const Variant variant = SGEMM_VARIANT_OBJ(T,N,16,16,16,6,6,64,__ALPHA,
              KName_TNMainAlpha,KName_TNRowAlpha, KName_TNColumnAlpha, KName_TNSingleWaveAlpha ,
              NULL,
              NULL,
              KBin_TNMainAlpha64,
              KBin_TNMainAlphaSize64) ;

            return &variant ; 
        }
      }
     /* else
      {
        if (args.beta!=0)
        {

          if(_64BitsUse==64)
          {
            static const Variant variant = SGEMM_VARIANT_OBJ(N,N,1,16,16,6,6,64,__ALPHABETA, 
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
          }   
        }
        else
        {
          if(_64BitsUse==64)
          {
            static const Variant variant = SGEMM_VARIANT_OBJ(N,N,1,16,16,6,6,64,__ALPHA,
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
          }   
        }
      }*/


    }
  }

  return NULL;
}

clBlashawaiiSgemmSplitKernelFunctor::clBlashawaiiSgemmSplitKernelFunctor(Args & args, const Variant * variant, cl_int & err)
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



clBlashawaiiSgemmSplitKernelFunctor * 
  clBlashawaiiSgemmSplitKernelFunctor::provide(clblasSgemmFunctor::Args & args, char* DevName) 
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
    clBlashawaiiSgemmSplitKernelFunctor * functor = lookup.get();
    functor->retain(); // increment the reference counter to avoid deletion while it is still beeing used
    return functor;
  }

  clBlashawaiiSgemmSplitKernelFunctor * functor = new clBlashawaiiSgemmSplitKernelFunctor(args, variant, err);
  if (err != CL_SUCCESS)
  {
    return NULL;
  }

  lookup.set(functor) ;

  return functor;

}


cl_int clBlashawaiiSgemmSplitKernelFunctor::KernelsLaunch(cl_command_queue queue, cl_kernel Kernel[4], Args &args)
{
  size_t GlobalX =args.M/m_variantSplit->bwi[0];
  GlobalX-=GlobalX%m_variantSplit->ls[0];
  //

  size_t GlobalY = args.N/m_variantSplit->bwi[1];
  GlobalY-=GlobalY%m_variantSplit->ls[1];


  std::size_t gs[2] = {GlobalX, GlobalY};
  cl_int error = 0;
  
  //deals with square matrix sizes where K is mod 16 for now
  if (args.lda == args.ldb)
  {
	  if ((args.K % 16 == 0) && (args.lda >= 6144) && (args.ldb >= 6144))
	  {
		  if ((args.lda % 1024 == 0) && (args.ldb % 1024 == 0) && (args.transA == clblasNoTrans) && (args.transB == clblasTrans))
		  {
			  //handles special cases where a direct call to "sgemm_NT_96_96_16..." causes perf drop due to cache miss/thrashing
			  //this special cases is: sgemm column major NT / sgemm row major TN; lda and ldb are big multiples of 1024 such as 4096 and 6144
			  //K is bigger than a threshold: 1536 for lda=ldb=6144

			  //
			  int K_block_size;
              if (args.lda == 6144)
			  {
				  K_block_size = 1536;
			  }
			  else
			  {
				  K_block_size = 128;
			  }

			  if (args.M % 96 == 0 && args.N % 96 == 0)
			  {
				  if (VERB) printf(" ===> EXECUTE KERNEL 0 \n");
				  if (args.K > K_block_size)
				  {
					  //split into many GEMM calls with K = K_block_size
					  //there are at least 2 GEMM calls
					  int num_of_gemm = ((args.K - 1) / K_block_size) + 1;

					  //call first GEMM
					  unsigned int small_K = K_block_size;
					  setKernelArg<int>(Kernel[0], 5, small_K);
					  error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList, NULL);

					  //call middle GEMMs
					  unsigned beta_one = 1.0f;
					  setKernelArg<int>(Kernel[0], 7, beta_one);
					  for (int i = 1; i < num_of_gemm - 1; i++)
					  {
						  unsigned offa_i = args.lda * (args.K / num_of_gemm) * i + args.offA;
						  unsigned offb_i = args.ldb * (args.K / num_of_gemm) * i + args.offB;
						  setKernelArg<int>(Kernel[0], 11, offa_i);
						  setKernelArg<int>(Kernel[0], 12, offb_i);
						  error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantSplit->ls, 0, NULL, NULL);
					  }
					  //call last GEMM
					  //the last GEMM's K might be smaller than small_K
					  unsigned int residue_K = args.K % small_K;
					  if (residue_K == 0)
						  residue_K = small_K;
					  unsigned offa_i = args.lda * (args.K / num_of_gemm) * (num_of_gemm - 1) + args.offA;
					  unsigned offb_i = args.ldb * (args.K / num_of_gemm) * (num_of_gemm - 1) + args.offB;
					  setKernelArg<int>(Kernel[0], 5, residue_K);
					  setKernelArg<int>(Kernel[0], 11, offa_i);
					  setKernelArg<int>(Kernel[0], 12, offb_i);
					  error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantSplit->ls, 0, NULL, args.events);
					  return error;
				  }
			  }

			  if (args.M % 96 != 0 && args.N % 96 != 0 && args.M >= 96 && args.N >= 96)
			  {
				  if (VERB) printf(" ===> EXECUTE KERNEL 0, 1, 2, 3 \n");

				  if (args.K > K_block_size)
				  {
					  int num_of_gemm = ((args.K - 1) / K_block_size) + 1;

					  //first 4 GEMMs
					  unsigned int small_K = K_block_size;
					  setKernelArg<int>(Kernel[0], 5, small_K);

					  error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList, NULL);

					  gs[0] = 16;
					  error |= clEnqueueNDRangeKernel(queue, Kernel[1], 2, NULL, gs, m_variantSplit->ls, 0, NULL, NULL);

					  gs[1] = 16;
					  gs[0] = GlobalX;
					  error |= clEnqueueNDRangeKernel(queue, Kernel[2], 2, NULL, gs, m_variantSplit->ls, 0, NULL, NULL);

					  gs[0] = 16; gs[1] = 16;
					  error |= clEnqueueNDRangeKernel(queue, Kernel[3], 2, NULL, gs, m_variantSplit->ls, 0, NULL, NULL);

					  //middle GEMMs
					  unsigned beta_one = 1.0f;
					  setKernelArg<int>(Kernel[0], 7, beta_one);
					  for (int i = 1; i < num_of_gemm - 1; i++)
					  {
						  unsigned offa_i = args.lda * (args.K / num_of_gemm) * i + args.offA;
						  unsigned offb_i = args.ldb * (args.K / num_of_gemm) * i + args.offB;
						  setKernelArg<int>(Kernel[0], 11, offa_i);
						  setKernelArg<int>(Kernel[0], 12, offb_i);
						  //gs[2] = {GlobalX, GlobalY};
						  gs[0] = GlobalX;
						  gs[1] = GlobalY;

						  error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantSplit->ls, 0, NULL, NULL);

						  gs[0] = 16;
						  error |= clEnqueueNDRangeKernel(queue, Kernel[1], 2, NULL, gs, m_variantSplit->ls, 0, NULL, NULL);

						  gs[1] = 16;
						  gs[0] = GlobalX;
						  error |= clEnqueueNDRangeKernel(queue, Kernel[2], 2, NULL, gs, m_variantSplit->ls, 0, NULL, NULL);

						  gs[0] = 16; gs[1] = 16;
						  error |= clEnqueueNDRangeKernel(queue, Kernel[3], 2, NULL, gs, m_variantSplit->ls, 0, NULL, NULL);
					  }
					  //last 4 GEMMs
					  unsigned int residue_K = args.K % small_K;
					  if (residue_K == 0)
						  residue_K = small_K;
					  unsigned offa_i = args.lda * (args.K / num_of_gemm) * (num_of_gemm - 1) + args.offA;
					  unsigned offb_i = args.ldb * (args.K / num_of_gemm) * (num_of_gemm - 1) + args.offB;
					  setKernelArg<int>(Kernel[0], 5, residue_K);
					  setKernelArg<int>(Kernel[0], 11, offa_i);
					  setKernelArg<int>(Kernel[0], 12, offb_i);

					  gs[0] = GlobalX;
					  gs[1] = GlobalY;

					  error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantSplit->ls, 0, NULL, NULL);

					  gs[0] = 16;
					  error |= clEnqueueNDRangeKernel(queue, Kernel[1], 2, NULL, gs, m_variantSplit->ls, 0, NULL, NULL);

					  gs[1] = 16;
					  gs[0] = GlobalX;
					  error |= clEnqueueNDRangeKernel(queue, Kernel[2], 2, NULL, gs, m_variantSplit->ls, 0, NULL, NULL);

					  gs[0] = 16; gs[1] = 16;
					  error |= clEnqueueNDRangeKernel(queue, Kernel[3], 2, NULL, gs, m_variantSplit->ls, 0, NULL, args.events);


					  return error;
				  }
			  }


		  }
	  }
  }


  if (args.M%96==0 && args.N%96==0)
  {
    if (VERB) printf(" ===> EXECUTE KERNEL 0 \n") ;
    error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList,args.events);
    return error;
  }

  if (args.M%96!=0 && args.N%96!=0 && args.M>=96 && args.N>=96 )
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
  if (args.M%96==0 && args.N%96!=0 &&  args.N>96 )
  {
    if (VERB) printf(" ===> EXECUTE KERNEL 0, 2, \n") ;

    error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList,NULL);
    gs[1] = 16;
	error |= clEnqueueNDRangeKernel(queue, Kernel[2], 2, NULL, gs, m_variantSplit->ls, 0, NULL, args.events);

    return error;
  }
  if (args.N%96==0 && args.M%96!=0 &&  args.M>96 )
  {
    if (VERB) printf(" ===> EXECUTE KERNEL 0, 1 \n") ;

    error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList,NULL);
    gs[0] = 16;
	error |= clEnqueueNDRangeKernel(queue, Kernel[1], 2, NULL, gs, m_variantSplit->ls, 0, NULL, args.events);

    return error;
  }
  if(args.M<96 && args.N%96==0)
  {
    if (VERB) printf(" ===> EXECUTE KERNEL 1, \n") ;

    gs[0] = 16;
    error |= clEnqueueNDRangeKernel(queue, Kernel[1], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList, args.events);
    return error;
  }
  if(args.M<96 && args.N%96!=0 && args.N>=96)
  {
    if (VERB) printf(" ===> EXECUTE KERNEL  1, 3 \n") ;

    gs[0] = 16;
    error |= clEnqueueNDRangeKernel(queue, Kernel[1], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList, NULL);
    gs[1] = 16;
    error |= clEnqueueNDRangeKernel(queue, Kernel[3], 2, NULL, gs, m_variantSplit->ls, 0, NULL,args.events);
    return error;
  }
  if(args.N<96 && args.M%96==0)
  {
    if (VERB) printf(" ===> EXECUTE KERNEL  2 \n") ;

    gs[1] = 16;  
    error |= clEnqueueNDRangeKernel(queue, Kernel[2], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList, args.events);
    return error;
  }
  if(args.N<96 && args.M%96!=0&& args.M>=96)
  {
    if (VERB) printf(" ===> EXECUTE KERNEL 2, 3 \n") ;

    gs[1] = 16;  
    error |= clEnqueueNDRangeKernel(queue, Kernel[2], 2, NULL, gs, m_variantSplit->ls, args.numEventsInWaitList, args.eventWaitList, NULL);

    gs[0] = 16;
    error |= clEnqueueNDRangeKernel(queue, Kernel[3], 2, NULL, gs, m_variantSplit->ls, 0, NULL,args.events);
    return error;
  }
  if (args.N<96 && args.M<96)
  {
    if (VERB) printf(" ===> EXECUTE KERNEL  3 \n") ;
    gs[0] = 16; gs[1] = 16;
    error |= clEnqueueNDRangeKernel(queue, Kernel[3], 2, NULL, gs, m_variantSplit->ls,args.numEventsInWaitList, args.eventWaitList, args.events);
    return error;
  }

  return clblasNotImplemented;
}



clblasStatus clBlashawaiiSgemmSplitKernelFunctor::execute(Args &args)
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
    if (args.beta!=0 && this->m_variantSplit->mult.compare("__ALPHA")!=0)
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
