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

#include <tahiti.h>
#include "gpu_dtrsm.h"
//#include "gcn_dgemm.h"
#include "gcn_dgemmCommon.h"
#include "gcn_dgemmSmallMatrices.h"
#include "gcn_sgemmSmallMatrices.h"


FunctorSelectorTahiti FunctorSelectorTahiti::instance ;


FunctorSelectorTahiti::FunctorSelectorTahiti()
    : clblasFunctorSelector(TAHITI)
{
    
}

//
// The selector function for DGEMM on tahiti 
//
//
clblasDgemmFunctor * FunctorSelectorTahiti::select_dgemm_specific(clblasDgemmFunctor::Args & args)
{
#ifdef CLBLAS_TAHITI_DYNAMIC_KERNEL
	return this->clblasFunctorSelector::select_dgemm_specific(args);
#else
  clblasDgemmFunctor * functor;

    bool NN_NT = ((args.transA==clblasNoTrans && args.transB==clblasTrans ) || ( args.transA==clblasNoTrans && args.transB==clblasNoTrans ));
  bool SmallMatrices = args.M/6*args.N/6<85*85;
  SmallMatrices= SmallMatrices && ((args.M%24==0&&args.N%24==0)||(args.M%16==0&&args.N%16==0))&&args.K%8==0 &&NN_NT;


  if (args.alpha!=0)
  {
    if (SmallMatrices)
    {
      functor = clBlasGCNDgemmSmallMatricesFunctor::provide(args,  "Tahiti");
      if (functor) 
        return functor;
    }
    

    functor = clBlasGCNdgemmCommonFunctor::provide(args, "Tahiti");
    if (functor) 
      return functor;
    
  }
  // else use the fallback implementation
  return this->clblasFunctorSelector::select_dgemm_specific(args);
#endif

}


// The selector function for DTRSM on tahiti 
//
clblasDtrsmFunctor * FunctorSelectorTahiti::select_dtrsm_specific(clblasDtrsmFunctor::Args & args)
{
#ifdef CLBLAS_TAHITI_DYNAMIC_KERNEL
	return this->clblasFunctorSelector::select_dtrsm_specific(args);
#else
  clblasDtrsmFunctor * functor;
  
  functor = clblasDtrsmFunctorGpu::provide(args, "Tahiti");
  if (functor) return functor;
  
  // else use the fallback implementation
  return this->clblasFunctorSelector::select_dtrsm_specific(args);
#endif

}

clblasSgemmFunctor * FunctorSelectorTahiti::select_sgemm_specific(clblasSgemmFunctor::Args & args)
{
#ifdef CLBLAS_TAHITI_DYNAMIC_KERNEL
	return this->clblasFunctorSelector::select_sgemm_specific(args);
#else
  clblasSgemmFunctor * functor;
  bool Not_TT = ((args.transA==clblasNoTrans && args.transB==clblasTrans ) || ( args.transA==clblasNoTrans && args.transB==clblasNoTrans ) || ( args.transA==clblasTrans && args.transB==clblasNoTrans ));
  bool SmallMatrices = args.M/6*args.N/6<100*100 || ((args.M%64!=0 && args.N%64!=0 && args.M<1900 &&args.N<1900 ) && (args.M%96!=0 && args.N%96!=0 && args.M<1900 &&args.N<1900 ));
  SmallMatrices= (SmallMatrices && (args.M%32==0&&args.N%32==0)) ;
  SmallMatrices=SmallMatrices&&Not_TT&&args.K%16==0;


  if (args.alpha!=0)
  {
    if (SmallMatrices)
    {
      functor = clBlasGCNSgemmSmallMatricesFunctor::provide(args,  "Tahiti");
      if (functor) 
        return functor;
    }
    

    functor = clblasSgemmFunctorGCN::provide(args, "Tahiti");
    if (functor) 
      return functor;
    
  }
  // else use the fallback implementation
  return this->clblasFunctorSelector::select_sgemm_specific(args);
#endif
}