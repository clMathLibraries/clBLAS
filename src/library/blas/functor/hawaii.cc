/* ************************************************************************
 * Copyright 2014 Advanced Micro Devices, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ************************************************************************/

#include <hawaii.h>
#include "gpu_dtrsm.h"
#include "gcn_dgemmCommon.h"
#include "math.h"
//#include "hawaii_dgemmChannelConflict.h"
#include "hawaii_dgemmSplitKernel.h"
#include "hawaii_sgemmSplitKernel.h"
#include "gcn_dgemmSmallMatrices.h"
#include "gcn_sgemmSmallMatrices.h"
#include "hawaii_sgemmBranchKernel.h"
#include "hawaii_sgemmSplit64_32.h"
#include "gcn_zgemm.h"
#include "gpu_dtrsm192.h"
#include "hawaii_sgemmBig1024Kernel.h"

FunctorSelectorHawaii FunctorSelectorHawaii::instance ;


FunctorSelectorHawaii::FunctorSelectorHawaii()
    : clblasFunctorSelector(HAWAII)
{
    
}

//
// The selector function for DGEMM on hawaii 
//
//
clblasDgemmFunctor * FunctorSelectorHawaii::select_dgemm_specific(clblasDgemmFunctor::Args & args)
{
#ifdef CLBLAS_HAWAII_DYNAMIC_KERNEL
	return this->clblasFunctorSelector::select_dgemm_specific(args);
#else
  clblasDgemmFunctor * functor;

  bool NN_NT = ((args.transA==clblasNoTrans && args.transB==clblasTrans ) || ( args.transA==clblasNoTrans && args.transB==clblasNoTrans ));
  bool SmallMatrices = args.M/6*args.N/6<85*85;
  SmallMatrices= SmallMatrices && ((args.M%24==0&&args.N%24==0)||(args.M%16==0&&args.N%16==0))&&args.K%8==0 && (args.transA==clblasNoTrans && args.transB==clblasTrans );//*/&&NN_NT;
  
  
  
  bool BestPerf= (args.M%48==0 && args.N%48==0) ||
                 (args.M%32==0 && args.M>4000 && args.N%32==0 && args.N>4000) || (args.M%40==0 && args.M>4000 && args.N%40==0 && args.N>4000) ||
                  ((args.M%32!=0 && args.M>1000) || (args.N%32!=0 && args.N>1000)) || ((args.M%40!=0 && args.M>1000) || (args.N%40!=0 && args.N>1000)) ;

  bool useSpliKernel = (NN_NT &&  BestPerf);

  if (args.alpha!=0)
  {
    if (SmallMatrices)
    {
      functor = clBlasGCNDgemmSmallMatricesFunctor::provide(args, "Hawaii");
      if (functor) 
        return functor;
    }
    else if ( useSpliKernel) 
    {
      functor = clBlashawaiiDgemmSplitKernelFunctor::provide(args);
      if (functor) 
        return functor;
    }

    functor = clBlasGCNdgemmCommonFunctor::provide(args, "Hawaii");
    if (functor) 
      return functor;



    //{
    //  functor = clBlashawaiiDgemmChannelConflictFunctor::provide(args);
    //  if (functor) 
    //    return functor;

    //}
  }
   
  // else use the fallback implementation
  return this->clblasFunctorSelector::select_dgemm_specific(args);
#endif
}


// The selector function for SGEMM on hawaii
clblasSgemmFunctor * FunctorSelectorHawaii::select_sgemm_specific(clblasSgemmFunctor::Args & args)
{
#ifdef CLBLAS_HAWAII_DYNAMIC_KERNEL
	return this->clblasFunctorSelector::select_sgemm_specific(args);
#else
  //TODO: the logic below is complicated; Needs cleanup;
  clblasSgemmFunctor * functor;
  bool Not_TT = ((args.transA==clblasNoTrans && args.transB==clblasTrans ) || ( args.transA==clblasNoTrans && args.transB==clblasNoTrans ) || ( args.transA==clblasTrans && args.transB==clblasNoTrans ));
  bool SmallMatrices = (args.M / 6 * args.N / 6 < 100 * 100) || (args.M / 6 * args.N / 6 < 180 * 180 && (args.M % 32 != 0 || args.N % 32 != 0)) || ((args.M % 64 != 0 && args.N % 64 != 0 && args.M < 1900 && args.N < 1900) && (args.M % 96 != 0 && args.N % 96 != 0 && args.M < 1900 && args.N < 1900));
  bool SmallMatricesMod32= (SmallMatrices && (args.M%32==0&&args.N%32==0)) ;
  SmallMatricesMod32 = SmallMatricesMod32&&Not_TT&&args.K % 16 == 0;
  //SmallMatrices= false;
  
  bool useSpliKernel=((args.M%96==0 && args.N%96==0) || !(args.M%64==0 && args.N%64==0&& args.M<4000 &&args.N<4000)) ;
  useSpliKernel=useSpliKernel&&Not_TT;

  //functor = clBlashawaiiSgemmSplit64_32Functor::provide(args, "Hawaii");
  //if (functor)
  //  return functor;

  if ((args.lda % 1024 == 0) && (args.ldb % 1024 == 0) && (args.K > args.lda / 4))
  {
	  if ((args.lda == args.ldb) && (args.lda >= 4096) && (args.lda <= 8192)) // between 4096 and 8192 for now
	  {
		  if (args.lda != 6144)// 6144 is handled by a special case split
		  {
			  // we are going to call 16 GEMMs with M=M/2, N=N/2, K=K/4
			  // each GEMM requires M%128 == 0, N%128 == 0, K%16 == 0
			  if (args.M % 256 == 0 && args.N % 256 == 0 && args.K % 64 == 0)
			  {
				  functor = clBlashawaiiSgemmBig1024KernelFunctor::provide(args, "Hawaii");
				  if (functor)
					  return functor;
			  }
		  }
	  }
  }

  if ((args.M >= 1184 && args.N >= 1184) && (args.M <= 3872 && args.N <= 3872) && (args.M % 64 != 0 && args.N % 64 != 0) && (args.M % 96 != 0 && args.N % 96 != 0) && (args.K % 16 == 0))
  {
	  //all the mod32 sizes that is not mod64 or mod96 ranging from 1184 to 3872 
	  //non mod32 cases are not implemented in this approach and are of less interest
	  if ((args.M % 32 == 0 && args.N % 32 == 0) && (args.transA == clblasNoTrans && args.transB == clblasTrans))
	  {
		  functor = clBlashawaiiSgemmSplit64_32Functor::provide(args, "Hawaii");
		  if (functor)
			  return functor;
	  }
  }
  
  //the English translation of below is: if small matrix that is (not mod32) and (not_TT) and K has to be mod 16
  if (SmallMatrices && (!SmallMatricesMod32) && (Not_TT) && (args.K%16 == 0))
  {
	  functor = clBlashawaiiSgemmBranchKernelFunctor::provide(args, "Hawaii");
	  if (functor)
		  return functor;
  }

  if (args.alpha!=0 )
  {
	  if (SmallMatricesMod32)
    {
      functor = clBlasGCNSgemmSmallMatricesFunctor::provide(args, "Hawaii");
      if (functor) 
        return functor;
    }
    if ( useSpliKernel) 
    {
      functor = clBlashawaiiSgemmSplitKernelFunctor::provide(args, "Hawaii");
      if (functor) 
        return functor;
    }
    else
    {
      functor = clblasSgemmFunctorGCN::provide(args, "Hawaii");
      if (functor) 
        return functor;
    }
  }
  
  // else use the fallback implementation
  return this->clblasFunctorSelector::select_sgemm_specific(args);
  
#endif
}


// The selector function for ZGEMM on hawaii
clblasZgemmFunctor * FunctorSelectorHawaii::select_zgemm_specific(clblasZgemmFunctor::Args & args)
{

  if ( args.M%32==0
    && args.N%64==0
    && args.K%8==0
    && args.transA==clblasNoTrans
    && args.transB==clblasTrans
    && args.order==clblasColumnMajor) {
    return clblasZgemmFunctorGCN::provide(args, "Hawaii");
  } else {
    return this->clblasFunctorSelector::select_zgemm_specific(args);
  }

}

// The selector function for DTRSM on hawaii
//
clblasDtrsmFunctor * FunctorSelectorHawaii::select_dtrsm_specific(clblasDtrsmFunctor::Args & args)
{
#ifdef CLBLAS_HAWAII_DYNAMIC_KERNEL
	return this->clblasFunctorSelector::select_dtrsm_specific(args);
#else
  clblasDtrsmFunctor * functor;
  
  
  if ((args.M % 192 == 0) && (args.N % 192 == 0))
  {
	  //TODO: the implementation of sub block being 192 only supports 
	  //side == right
	  //uplo == upper
	  //trans == notrans
	  //M and N need to be mod192
	  //subblock being 192 is prefered over 128 on Hawaii device since
	  //it does not create "boundary" in DGEMM calls
	  //Hawaii DGEMM calls have better performance when M N K are mod48
	  if ((args.side == clblasRight) && (args.uplo == clblasUpper) && (args.transA == clblasNoTrans))
	  {
		  functor = clblasDtrsm192FunctorGpu::provide(args, "Hawaii");
		  if (functor)
			  return functor;
	  }
  }
  //sub block is 128 here
  functor = clblasDtrsmFunctorGpu::provide(args, "Hawaii");
  if (functor) 
    return functor;
  
  // else use the fallback implementation
  return this->clblasFunctorSelector::select_dtrsm_specific(args);
#endif
}



