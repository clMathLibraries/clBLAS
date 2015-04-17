
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

#include <clblas-internal.h>
#include <functor_selector.h>
#include <cassert>

#include <functor_xscal_generic.h>

// This is the selector used by default for 'unknown' targets 
clblasFunctorSelector clblasFunctorSelector::default_instance ;

typedef std::map<DeviceChip, clblasFunctorSelector*> clblasFunctorSelectorMap ;

//
// Provide a global map in which all clblasFunctorSelector will register during 
// their constructor (with the exception of the default one). 
// 
// Remark: For that, we use the "construct on first use" idiom, to avoid the 
//         infamous "static initialization order fiasco".
//         See for example  http://www.parashift.com/c++-faq/static-init-order.html
//
static clblasFunctorSelectorMap & 
getMap() 
{
  static clblasFunctorSelectorMap * the_map = new clblasFunctorSelectorMap ;
  return * the_map ;
}


// Constructor for the non-default selector 
clblasFunctorSelector::clblasFunctorSelector(DeviceChip chip)
{
    clblasFunctorSelectorMap::iterator it = getMap().find(chip);

    if (it != getMap().end())
    {
       assert(false);
    }

    getMap()[chip] = this;
}

// Constructor for the default selector 
clblasFunctorSelector::clblasFunctorSelector()
{
}

clblasFunctorSelector * 
clblasFunctorSelector::find(cl_command_queue queue) 
{
    cl_device_id device;
    cl_int status = getQueueDevice(queue, &device);
    assert( status == CL_SUCCESS );
    return clblasFunctorSelector::find(device);
}

clblasFunctorSelector * 
clblasFunctorSelector::find(cl_device_id device) 
{
    TargetDevice td;
    td.id = device;
    cl_int status = identifyDevice(&td);
    assert( status == CL_SUCCESS );
    return clblasFunctorSelector::find(td.ident.chip);
}

clblasFunctorSelector * 
clblasFunctorSelector::find(DeviceChip chip) 
{
    clblasFunctorSelectorMap & the_map = getMap();
    clblasFunctorSelectorMap::iterator it = the_map.find(chip);
    if (it != the_map.end())
    {
        return it->second;
    }
    else 
    {
        return &default_instance ;
    }
}

int clblasFunctorSelector::FindFirePro(cl_device_id device)
{
  return 1;
  /*char cardName [1024];
  cl_int error = clGetDeviceInfo(device, CL_DEVICE_BOARD_NAME_AMD, sizeof(cardName), cardName, NULL);
  if (error!=CL_SUCCESS)
    return 0;
  else if (strstr (cardName, "FirePro"))
    return 1;
  else
    return 0;
  */
}

// =================================================================================
//
// XGEMM
//
// =================================================================================


clblasSgemmFunctor * 
clblasFunctorSelector::select_sgemm_generic()  
{ 
    return clblasSgemmFunctorFallback::provide();
}  

clblasDgemmFunctor * 
clblasFunctorSelector::select_dgemm_generic()  
{ 
    return clblasDgemmFunctorFallback::provide();
}  


clblasCgemmFunctor * 
clblasFunctorSelector::select_cgemm_generic()  
{ 
    return clblasCgemmFunctorFallback::provide();
}  

clblasZgemmFunctor * 
clblasFunctorSelector::select_zgemm_generic()  
{ 
    return clblasZgemmFunctorFallback::provide();
}  


clblasSgemmFunctor * 
clblasFunctorSelector::select_sgemm_specific(clblasSgemmFunctor::Args &)
{ 
    return this->select_sgemm_generic() ;
}

clblasDgemmFunctor * 
clblasFunctorSelector::select_dgemm_specific(clblasDgemmFunctor::Args &)
{ 
    return this->select_dgemm_generic() ;
}

clblasCgemmFunctor * 
clblasFunctorSelector::select_cgemm_specific(clblasCgemmFunctor::Args &)
{ 
    return this->select_cgemm_generic() ;
}

clblasZgemmFunctor * 
clblasFunctorSelector::select_zgemm_specific(clblasZgemmFunctor::Args &)
{ 
    return this->select_zgemm_generic() ;
}


// =================================================================================
//
// XTRSM
//
// =================================================================================


clblasStrsmFunctor * 
clblasFunctorSelector::select_strsm_generic()  
{ 
    return clblasStrsmFunctorFallback::provide();
}  

clblasDtrsmFunctor * 
clblasFunctorSelector::select_dtrsm_generic()  
{ 
    return clblasDtrsmFunctorFallback::provide();
}  


clblasCtrsmFunctor * 
clblasFunctorSelector::select_ctrsm_generic()  
{ 
    return clblasCtrsmFunctorFallback::provide();
}  

clblasZtrsmFunctor * 
clblasFunctorSelector::select_ztrsm_generic()  
{ 
    return clblasZtrsmFunctorFallback::provide();
}  


clblasStrsmFunctor * 
clblasFunctorSelector::select_strsm_specific(clblasStrsmFunctor::Args &)
{ 
    return this->select_strsm_generic() ;
}

clblasDtrsmFunctor * 
clblasFunctorSelector::select_dtrsm_specific(clblasDtrsmFunctor::Args &)
{ 
    return this->select_dtrsm_generic() ;
}

clblasCtrsmFunctor * 
clblasFunctorSelector::select_ctrsm_specific(clblasCtrsmFunctor::Args &)
{ 
    return this->select_ctrsm_generic() ;
}

clblasZtrsmFunctor * 
clblasFunctorSelector::select_ztrsm_specific(clblasZtrsmFunctor::Args &)
{ 
    return this->select_ztrsm_generic() ;
}


// =================================================================================
//
// XSCAL
//
// =================================================================================


clblasSscalFunctor * 
clblasFunctorSelector::select_sscal_generic(clblasSscalFunctor::Args & args)  
{ 
  clblasSscalFunctor * functor;
  functor = clblasSscalFunctorGeneric::provide(args);
  if(functor) return functor;

  return clblasSscalFunctorFallback::provide();
}  

clblasDscalFunctor * 
clblasFunctorSelector::select_dscal_generic(clblasDscalFunctor::Args & args)  
{ 
  clblasDscalFunctor * functor;
  functor = clblasDscalFunctorGeneric::provide(args);
  if(functor) return functor;

  return clblasDscalFunctorFallback::provide();
}  


clblasCscalFunctor * 
clblasFunctorSelector::select_cscal_generic(clblasCscalFunctor::Args & args)  
{ 
  clblasCscalFunctor * functor;
  functor = clblasCscalFunctorGeneric::provide(args);
  if(functor) return functor;

  return clblasCscalFunctorFallback::provide();
}  

clblasZscalFunctor * 
clblasFunctorSelector::select_zscal_generic(clblasZscalFunctor::Args & args)  
{ 
  clblasZscalFunctor * functor;
  functor = clblasZscalFunctorGeneric::provide(args);
  if(functor) return functor;

  return clblasZscalFunctorFallback::provide();
}

clblasCsscalFunctor * 
clblasFunctorSelector::select_csscal_generic(clblasCsscalFunctor::Args & args)  
{ 
  clblasCsscalFunctor * functor;
  functor = clblasCsscalFunctorGeneric::provide(args);
  if(functor) return functor;
  
  return clblasCsscalFunctorFallback::provide();
}  

clblasZdscalFunctor * 
clblasFunctorSelector::select_zdscal_generic(clblasZdscalFunctor::Args & args)  
{ 
  clblasZdscalFunctor * functor;
  functor = clblasZdscalFunctorGeneric::provide(args);
  if(functor) return functor;

  return clblasZdscalFunctorFallback::provide();
}


clblasSscalFunctor * 
clblasFunctorSelector::select_sscal_specific(clblasSscalFunctor::Args & args)
{ 
    return this->select_sscal_generic(args) ;
}

clblasDscalFunctor * 
clblasFunctorSelector::select_dscal_specific(clblasDscalFunctor::Args & args)
{ 
    return this->select_dscal_generic(args) ;
}

clblasCscalFunctor * 
clblasFunctorSelector::select_cscal_specific(clblasCscalFunctor::Args & args)
{ 
    return this->select_cscal_generic(args) ;
}

clblasZscalFunctor * 
clblasFunctorSelector::select_zscal_specific(clblasZscalFunctor::Args & args)
{ 
    return this->select_zscal_generic(args) ;
}

clblasCsscalFunctor * 
clblasFunctorSelector::select_csscal_specific(clblasCsscalFunctor::Args & args)
{ 
    return this->select_csscal_generic(args) ;
}

clblasZdscalFunctor * 
clblasFunctorSelector::select_zdscal_specific(clblasZdscalFunctor::Args & args)
{ 
    return this->select_zdscal_generic(args) ;
}


// =================================================================================
//
// FILL2D
//
// =================================================================================


clblasFill2DFunctor * 
clblasFunctorSelector::select_fill2d_specific(clblasFill2DFunctor::Args & args)
{ 
  return clblasFill2DFunctorDefault::provide(args);
}
