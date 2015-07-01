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


#ifndef _CLBLAS_FUNCTION_SELECTOR_BONAIRE_
#define _CLBLAS_FUNCTION_SELECTOR_BONAIRE_

#include <functor_selector.h>
//#include <functor_hawaii_dgemm_NT_MN48.h>

class FunctorSelectorBonaire : public clblasFunctorSelector
{
private:
    FunctorSelectorBonaire();

    static FunctorSelectorBonaire instance;

public:

    // we don't want to provide any DP algorithm as DP is slow on bonaire  
    //virtual clblasDgemmFunctor * select_dgemm_specific(clblasDgemmFunctor::Args & args);
	  virtual clblasSgemmFunctor * select_sgemm_specific(clblasSgemmFunctor::Args & args);
  //  virtual clblasDtrsmFunctor * select_dtrsm_specific(clblasDtrsmFunctor::Args & args);

};


#endif // _CLBLAS_FUNCTION_SELECTOR_BONAIRE_
