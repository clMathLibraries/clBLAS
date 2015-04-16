/* ************************************************************************
 * Copyright 2013 Advanced Micro Devices, Inc.
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

#include <stdio.h>
#include <string.h>
#include <clBLAS.h>

#include <devinfo.h>
#include "clblas-internal.h"
#include "solution_seq.h"

#include <functor_xscal_generic.h>
#include <binary_lookup.h>

#include <kprintf.hpp>
#include <scal.clT>


template <class FUNCTOR>
static cl_program xcalCreateProgram(cl_context ctxt, 
                                    cl_device_id dev,
                                    char type,
                                    const char* functorName,
                                    const typename FUNCTOR::Data & data,
                                    cl_int & err)
{
  BinaryLookup bl(ctxt, dev, functorName);

  bl.variantInt(data.vecLen);
  bl.variantInt(data.doVLOAD);
  bl.variantInt(data.noUnity);

  if ( bl.found() ) // may create empty file or may wait until file is ready  
  {
    return bl.getProgram();
  }
  else
  {
    char tempTemplate[32*1024];
    char buf         [32*1024];
    cl_program scalProgram;

    strcpy( tempTemplate, (char*)scal_kernel );
    kprintf kobj( type, data.vecLen, data.doVLOAD, data.doVLOAD);
    kobj.spit((char*)buf, tempTemplate);

    const char * options;
    if(data.noUnity)
    {
      options = "-DINCX_NONUNITY";
    }else{
      options = "";
    }

    scalProgram = BinaryLookup::buildProgramFromSource(buf, ctxt, dev, err , options);
    
    if(scalProgram)
    {
      bl.setProgram(scalProgram);
      bl.populateCache();
    }
    
    return scalProgram;
  }

}


template <typename TA>
static clblasStatus xscalExecute(cl_command_queue queue, 
                                 cl_program program, 
                                 const char * kernelName, 
                                 TA alpha, 
                                 cl_mem X, 
                                 unsigned int N, 
                                 unsigned int offx, 
                                 int incx,
                                 size_t nThreads,
                                 cl_uint numEventsInWaitList,
                                 const cl_event *eventWaitList,
                                 cl_event *events)
{
  cl_int err;
  cl_kernel kernel = clCreateKernel( program, kernelName,  &err);
  if (err != CL_SUCCESS) return clblasStatus(err) ; 

  clblasFunctor::setKernelArg<TA>     (kernel, 0, alpha);
  clblasFunctor::setKernelArg<cl_mem> (kernel, 1, X);
  clblasFunctor::setKernelArg<unsigned int>   (kernel, 2, N);
  clblasFunctor::setKernelArg<unsigned int>   (kernel, 3, offx);
  clblasFunctor::setKernelArg<int>    (kernel, 4, incx);
  
  size_t globalThreads[1] = { nThreads };

  err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL,
                               globalThreads, NULL , 
                               numEventsInWaitList, eventWaitList, events);

  clReleaseKernel(kernel) ;
  return clblasStatus(err) ;
}


template <class FUNCTOR>
static FUNCTOR * xscalProvide(typename FUNCTOR::Args & args)
{
  cl_device_id dev;
  cl_context   ctxt;
  cl_int err = clblasFunctor::getDeviceAndContext(args.queue, dev, ctxt);

  if (err != CL_SUCCESS)
  {
      return NULL;
  }

  unsigned int vecLen  = 1 ;      //to customize according to the device and args
  bool         doVLOAD = false ;  //TO DO (see scal_reg.cpp)
  bool         noUnity = (args.incx != 1) ;


  typename FUNCTOR::Data data = { vecLen , doVLOAD , noUnity};

  typename FUNCTOR::Cache::Lookup lookup(FUNCTOR::cache, ctxt, dev, data ) ;

  if ( lookup.ok() ){
    FUNCTOR * functor = lookup.get();
    functor->retain(); // increment the reference counter to avoid deletion while it is still beeing used
    return functor;
  }
 
  FUNCTOR * functor = new FUNCTOR(ctxt, dev, data, err);
  if (err != CL_SUCCESS)
  {
      return NULL;
  }

  lookup.set(functor) ;

  return functor;
}


// =================================================================================
//
// class clblasSscalFunctorGeneric
//
// =================================================================================

clblasSscalFunctorGeneric::clblasSscalFunctorGeneric(cl_context ctxt, 
                                                     cl_device_id dev,
                                                     const Data & data,
                                                     cl_int & err) : program(0)
{
  this->program = xcalCreateProgram<clblasSscalFunctorGeneric>(ctxt, dev, 'S', "clblasSscalFunctorGeneric", data, err);
}

clblasSscalFunctorGeneric::~clblasSscalFunctorGeneric()
{
  if (this->program) {
    clReleaseProgram( this->program ) ; 
  } 
}

clblasStatus clblasSscalFunctorGeneric::execute(Args & args)
{
  size_t nThreads = args.N; //to customize according to the device, data and args
  return xscalExecute<cl_float>(args.queue, 
                                this->program, 
                                "Sscal_kernel",
                                args.alpha, 
                                args.X, 
                                args.N, 
                                args.offx, 
                                args.incx,
                                nThreads,
                                args.numEventsInWaitList,
                                args.eventWaitList,
                                args.events);
}

clblasSscalFunctorGeneric::Cache clblasSscalFunctorGeneric::cache;

clblasSscalFunctorGeneric * clblasSscalFunctorGeneric::provide (clblasSscalFunctor::Args & args)
{
  return xscalProvide<clblasSscalFunctorGeneric>(args);
}



// =================================================================================
//
// class clblasDscalFunctorGeneric
//
// =================================================================================

clblasDscalFunctorGeneric::clblasDscalFunctorGeneric(cl_context ctxt, 
                                                     cl_device_id dev,
                                                     const Data & data,
                                                     cl_int & err) : program(0)
{
  this->program = xcalCreateProgram<clblasDscalFunctorGeneric>(ctxt, dev, 'D', "clblasDscalFunctorGeneric", data, err);
}

clblasDscalFunctorGeneric::~clblasDscalFunctorGeneric()
{
  if (this->program) {
    clReleaseProgram( this->program ) ; 
  } 
}

clblasStatus clblasDscalFunctorGeneric::execute(Args & args)
{
  size_t nThreads = args.N; //to customize according to the device, data and args
  return xscalExecute<cl_double>(args.queue, 
                                 this->program, 
                                 "Dscal_kernel",
                                 args.alpha, 
                                 args.X, 
                                 args.N, 
                                 args.offx, 
                                 args.incx,
                                 nThreads,
                                 args.numEventsInWaitList,
                                 args.eventWaitList,
                                 args.events);
}

clblasDscalFunctorGeneric::Cache clblasDscalFunctorGeneric::cache;

clblasDscalFunctorGeneric * clblasDscalFunctorGeneric::provide (clblasDscalFunctor::Args & args)
{
  return xscalProvide<clblasDscalFunctorGeneric>(args);
}


// =================================================================================
//
// class clblasCscalFunctorGeneric
//
// =================================================================================

clblasCscalFunctorGeneric::clblasCscalFunctorGeneric(cl_context ctxt, 
                                                     cl_device_id dev,
                                                     const Data & data,
                                                     cl_int & err) : program(0)
{
  this->program = xcalCreateProgram<clblasCscalFunctorGeneric>(ctxt, dev, 'C', "clblasCscalFunctorGeneric", data, err);
}

clblasCscalFunctorGeneric::~clblasCscalFunctorGeneric()
{
  if (this->program) {
    clReleaseProgram( this->program ) ; 
  } 
}

clblasStatus clblasCscalFunctorGeneric::execute(Args & args)
{
  size_t nThreads = args.N; //to customize according to the device, data and args
  return xscalExecute<cl_float2>(args.queue, 
                                 this->program, 
                                 "Cscal_kernel",
                                 args.alpha, 
                                 args.X, 
                                 args.N, 
                                 args.offx, 
                                 args.incx,
                                 nThreads,
                                 args.numEventsInWaitList,
                                 args.eventWaitList,
                                 args.events);
}

clblasCscalFunctorGeneric::Cache clblasCscalFunctorGeneric::cache;

clblasCscalFunctorGeneric * clblasCscalFunctorGeneric::provide (clblasCscalFunctor::Args & args)
{
  return xscalProvide<clblasCscalFunctorGeneric>(args);
}


// =================================================================================
//
// class clblasZscalFunctorGeneric
//
// =================================================================================

clblasZscalFunctorGeneric::clblasZscalFunctorGeneric(cl_context ctxt, 
                                                     cl_device_id dev,
                                                     const Data & data,
                                                     cl_int & err) : program(0)
{
  this->program = xcalCreateProgram<clblasZscalFunctorGeneric>(ctxt, dev, 'Z', "clblasZscalFunctorGeneric", data, err);
}

clblasZscalFunctorGeneric::~clblasZscalFunctorGeneric()
{
  if (this->program) {
    clReleaseProgram( this->program ) ; 
  } 
}

clblasStatus clblasZscalFunctorGeneric::execute(Args & args)
{
  size_t nThreads = args.N; //to customize according to the device, data and args
  return xscalExecute<cl_double2>(args.queue, 
                                  this->program, 
                                  "Zscal_kernel",
                                  args.alpha, 
                                  args.X, 
                                  args.N, 
                                  args.offx, 
                                  args.incx,
                                  nThreads,
                                  args.numEventsInWaitList,
                                  args.eventWaitList,
                                  args.events);
}

clblasZscalFunctorGeneric::Cache clblasZscalFunctorGeneric::cache;

clblasZscalFunctorGeneric * clblasZscalFunctorGeneric::provide (clblasZscalFunctor::Args & args)
{
  return xscalProvide<clblasZscalFunctorGeneric>(args);
}

// =================================================================================
//
// class clblasCsscalFunctorGeneric
//
// =================================================================================

clblasCsscalFunctorGeneric::clblasCsscalFunctorGeneric(cl_context ctxt, 
                                                     cl_device_id dev,
                                                     const Data & data,
                                                     cl_int & err) : program(0)
{
  this->program = xcalCreateProgram<clblasCsscalFunctorGeneric>(ctxt, dev, 'C', "clblasCsscalFunctorGeneric", data, err);
}

clblasCsscalFunctorGeneric::~clblasCsscalFunctorGeneric()
{
  if (this->program) {
    clReleaseProgram( this->program ) ; 
  } 
}

clblasStatus clblasCsscalFunctorGeneric::execute(Args & args)
{
  size_t nThreads = args.N; //to customize according to the device, data and args

  cl_float2 l_alpha;
  l_alpha.s[0] = args.alpha ;
  l_alpha.s[1] = 0.f ;

  return xscalExecute<cl_float2>(args.queue, 
                                 this->program, 
                                 "Cscal_kernel",
                                 l_alpha, 
                                 args.X, 
                                 args.N, 
                                 args.offx, 
                                 args.incx,
                                 nThreads,
                                 args.numEventsInWaitList,
                                 args.eventWaitList,
                                 args.events);
}

clblasCsscalFunctorGeneric::Cache clblasCsscalFunctorGeneric::cache;

clblasCsscalFunctorGeneric * clblasCsscalFunctorGeneric::provide (clblasCsscalFunctor::Args & args)
{
  return xscalProvide<clblasCsscalFunctorGeneric>(args);
}


// =================================================================================
//
// class clblasZdscalFunctorGeneric
//
// =================================================================================

clblasZdscalFunctorGeneric::clblasZdscalFunctorGeneric(cl_context ctxt, 
                                                     cl_device_id dev,
                                                     const Data & data,
                                                     cl_int & err) : program(0)
{
  this->program = xcalCreateProgram<clblasZdscalFunctorGeneric>(ctxt, dev, 'Z', "clblasZdscalFunctorGeneric", data, err);
}

clblasZdscalFunctorGeneric::~clblasZdscalFunctorGeneric()
{
  if (this->program) {
    clReleaseProgram( this->program ) ; 
  } 
}

clblasStatus clblasZdscalFunctorGeneric::execute(Args & args)
{
  size_t nThreads = args.N; //to customize according to the device, data and args

  cl_double2 l_alpha;
  l_alpha.s[0] = args.alpha ;
  l_alpha.s[1] = 0.f ;

  return xscalExecute<cl_double2>(args.queue, 
                                  this->program, 
                                  "Zscal_kernel",
                                  l_alpha, 
                                  args.X, 
                                  args.N, 
                                  args.offx, 
                                  args.incx,
                                  nThreads,
                                  args.numEventsInWaitList,
                                  args.eventWaitList,
                                  args.events);
}

clblasZdscalFunctorGeneric::Cache clblasZdscalFunctorGeneric::cache;

clblasZdscalFunctorGeneric * clblasZdscalFunctorGeneric::provide (clblasZdscalFunctor::Args & args)
{
  return xscalProvide<clblasZdscalFunctorGeneric>(args);
}
