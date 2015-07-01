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

#ifndef _CLBLAS_FUNCTOR_SELECTOR_H_
#define _CLBLAS_FUNCTOR_SELECTOR_H_

#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

#include <stdio.h>
#include <map>
#include <devinfo.h>
#include <functor.h>
#include <functor_xgemm.h>
#include <functor_xscal.h>
#include <functor_xtrsm.h>
#include <functor_fill.h>

//
// The purpose of clblasFunctorSelector is to provide some selection functions to  
// choose amongst all functors available for a given task.
//
// Each BLAS function xxxx is typically associated to at least two virtual methods: 
//
//   - select_xxxx_generic() to select a generic functor applicable to all 
//     possible arguments.
//
//   - select_xxxx_specific(...) to select the most optimized functor for the 
//     specified arguments.
//
// A user willing to obtain a functor using one of those functions shall typically 
// query the most appropriate selector using one of the static find() functions. 
//
// There is only one instance of the default clblasFunctorSelector that is used for 
// devices without a specialized version. 
//
// So the clblasFunctorSelector is supposed to be derived once for each supported 
// device architecture (e.g. FunctorSelectorTahiti for the AMD Tahiti GPU). Each 
// of those derived class shall define a single global instance of itself that 
// will register itself in a global table of all known functor selectors. 
//
// The specialized selector class shall then provide its own select virtual 
// methods for which it exists a specialized implementation. Those specialized 
// selection methods may fall back on the default method if they do not provide 
// an optimized functor in all cases 
//
class clblasFunctorSelector 
{
protected:

    // Constructor for the non-default instances specialized for a given device.     
    clblasFunctorSelector(DeviceChip chip);

private:

    // This constructor is only for the default_instance
    clblasFunctorSelector();    

    // The selector default use when no specialized version exists
    // for the current device 
    static clblasFunctorSelector default_instance ;

public:
  
    // Find the suitable functor selector for the specified queue  
    static clblasFunctorSelector * find(cl_command_queue queue);

    // Find the suitable functor selector for the specified device  
    static clblasFunctorSelector * find(cl_device_id device);

    // Find the suitable functor selector for the specified device architecture  
    static clblasFunctorSelector * find(DeviceChip arch) ;

    // Find if the device is a FirePro one. If not we will return the default functor which won't use the fast kernel for GCN
    static int FindFirePro(cl_device_id device);

public:

    // Provide a XGEMM Functor usable in all cases 

    virtual clblasSgemmFunctor * select_sgemm_generic();
    virtual clblasDgemmFunctor * select_dgemm_generic();
    virtual clblasCgemmFunctor * select_cgemm_generic();
    virtual clblasZgemmFunctor * select_zgemm_generic();

    // Provide XGEMM functors optimized for specific arguments

    virtual clblasSgemmFunctor * select_sgemm_specific(clblasSgemmFunctor::Args & args);
    virtual clblasDgemmFunctor * select_dgemm_specific(clblasDgemmFunctor::Args & args);
    virtual clblasCgemmFunctor * select_cgemm_specific(clblasCgemmFunctor::Args & args);
    virtual clblasZgemmFunctor * select_zgemm_specific(clblasZgemmFunctor::Args & args);


    // Provide a XSCAL Functor usable in all cases 

    virtual clblasSscalFunctor  * select_sscal_generic(clblasSscalFunctor::Args & args);
    virtual clblasDscalFunctor  * select_dscal_generic(clblasDscalFunctor::Args & args);
    virtual clblasCscalFunctor  * select_cscal_generic(clblasCscalFunctor::Args & args);
    virtual clblasZscalFunctor  * select_zscal_generic(clblasZscalFunctor::Args & args);
    virtual clblasCsscalFunctor * select_csscal_generic(clblasCsscalFunctor::Args & args);
    virtual clblasZdscalFunctor * select_zdscal_generic(clblasZdscalFunctor::Args & args);

    // Provide XSCAL functors optimized for specific arguments

    virtual clblasSscalFunctor  * select_sscal_specific(clblasSscalFunctor::Args & args);
    virtual clblasDscalFunctor  * select_dscal_specific(clblasDscalFunctor::Args & args);
    virtual clblasCscalFunctor  * select_cscal_specific(clblasCscalFunctor::Args & args);
    virtual clblasZscalFunctor  * select_zscal_specific(clblasZscalFunctor::Args & args);
    virtual clblasCsscalFunctor * select_csscal_specific(clblasCsscalFunctor::Args & args);
    virtual clblasZdscalFunctor * select_zdscal_specific(clblasZdscalFunctor::Args & args);

        // Provide a XGEMM Functor usable in all cases 

    virtual clblasStrsmFunctor * select_strsm_generic();
    virtual clblasDtrsmFunctor * select_dtrsm_generic();
    virtual clblasCtrsmFunctor * select_ctrsm_generic();
    virtual clblasZtrsmFunctor * select_ztrsm_generic();

    // Provide XTRSM functors optimized for specific arguments

    virtual clblasStrsmFunctor * select_strsm_specific(clblasStrsmFunctor::Args & args);
    virtual clblasDtrsmFunctor * select_dtrsm_specific(clblasDtrsmFunctor::Args & args);
    virtual clblasCtrsmFunctor * select_ctrsm_specific(clblasCtrsmFunctor::Args & args);
    virtual clblasZtrsmFunctor * select_ztrsm_specific(clblasZtrsmFunctor::Args & args);

    // Provide functor to perform non-contiguous fill in a 2D matrix
    virtual clblasFill2DFunctor * select_fill2d_specific(clblasFill2DFunctor::Args & args);

};



#endif // _CLBLAS_FUNCTOR_SELECTOR_H_
