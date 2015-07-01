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

#include <bonaire.h>

#include "math.h"

#include "hawaii_sgemmSplitKernel.h"
#include "gcn_sgemmSmallMatrices.h"

FunctorSelectorBonaire FunctorSelectorBonaire::instance ;


FunctorSelectorBonaire::FunctorSelectorBonaire()
    : clblasFunctorSelector(BONAIRE)
{
    
}

//
// The selector function for DGEMM on hawaii 
//
//



// The selector function for SGEMM on bonaire 
clblasSgemmFunctor * FunctorSelectorBonaire::select_sgemm_specific(clblasSgemmFunctor::Args & args)
{
#ifdef CLBLAS_BONAIRE_DYNAMIC_KERNEL
	return this->clblasFunctorSelector::select_sgemm_specific(args);
#else
  clblasSgemmFunctor * functor;
  bool Not_TT = ((args.transA==clblasNoTrans && args.transB==clblasTrans ) || ( args.transA==clblasNoTrans && args.transB==clblasNoTrans ) || ( args.transA==clblasTrans && args.transB==clblasNoTrans ));

  bool SmallMatrices = args.M*args.N<256*256 || ((args.M%64!=0 && args.N%64!=0 && args.M<1900 &&args.N<1900 ) && (args.M%96!=0 && args.N%96!=0 && args.M<1900 &&args.N<1900 ));
  SmallMatrices= (SmallMatrices && (args.M%32==0&&args.N%32==0)) ;
  SmallMatrices=SmallMatrices&&Not_TT&&args.K%16==0;
 // SmallMatrices= false;

  bool useSpliKernel=((args.M%96==0 && args.N%96==0) ||!(args.M%64==0 && args.N%64==0&& args.M<4000 &&args.N<4000)) &&args.K%16==0;
  useSpliKernel=useSpliKernel&&Not_TT;

  if (args.alpha!=0 )
  {
        if (SmallMatrices)
    {
      functor = clBlasGCNSgemmSmallMatricesFunctor::provide(args, "Bonaire");
      if (functor) 
        return functor;
    }
    if ( useSpliKernel) 
    {

    functor = clBlashawaiiSgemmSplitKernelFunctor::provide(args, "Bonaire");
    if (functor)
      return functor;

    }
    else
    {
      functor = clblasSgemmFunctorGCN::provide(args, "Bonaire");
      if (functor) 
        return functor;
    }
  }

  // else use the fallback implementation
  return this->clblasFunctorSelector::select_sgemm_specific(args);
#endif
}






