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
  bool SmallMatrices = args.M/6*args.N/6<200*200 || ((args.M%64!=0 && args.N%64!=0 && args.M<1900 &&args.N<1900 ) && (args.M%96!=0 && args.N%96!=0 && args.M<1900 &&args.N<1900 ));
  bool SmallMatricesMod32= (SmallMatrices && (args.M%32==0&&args.N%32==0)) ;
  SmallMatricesMod32 = SmallMatricesMod32&&Not_TT&&args.K % 16 == 0;
  //SmallMatrices= false;
  
  bool useSpliKernel=((args.M%96==0 && args.N%96==0) || !(args.M%64==0 && args.N%64==0&& args.M<4000 &&args.N<4000)) /*&&args.K%16==0*/;
  useSpliKernel=useSpliKernel&&Not_TT;
  
  //the English translation of below is: if small matrix that is not mod32 and NT and K has to be mod 16
  if (SmallMatrices && (!SmallMatricesMod32) && (args.transA == clblasNoTrans && args.transB == clblasTrans) && (args.K%16 == 0))
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


// The selector function for DTRSM on hawaii
//
clblasDtrsmFunctor * FunctorSelectorHawaii::select_dtrsm_specific(clblasDtrsmFunctor::Args & args)
{
#ifdef CLBLAS_HAWAII_DYNAMIC_KERNEL
	return this->clblasFunctorSelector::select_dtrsm_specific(args);
#else
  clblasDtrsmFunctor * functor;
  
  functor = clblasDtrsmFunctorGpu::provide(args, "Hawaii");
  if (functor) 
    return functor;
  
  // else use the fallback implementation
  return this->clblasFunctorSelector::select_dtrsm_specific(args);
#endif
}



