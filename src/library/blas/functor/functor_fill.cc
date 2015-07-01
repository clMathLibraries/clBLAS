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
#include <string>

#include <stdio.h>
#include <string.h>
#include <clBLAS.h>

#include <devinfo.h>
#include "clblas-internal.h"
#include "solution_seq.h"

#include <functor_fill.h>
#include <binary_lookup.h>

// The internal cache of clblasFill2DFunctorFallback
typedef clblasFunctorCache<clblasFill2DFunctorDefault, int> Cache;
static Cache cache ; 

// Generic fill kernel: require macro TYPE to be defined to an element type
static const char FILL2D_KERNEL_SRC[] = "\n\
__kernel void fill2d( __global TYPE * A, int offA, int ldA, TYPE value) \n\
{\n\
  A[ offA + get_global_id(0) + get_global_id(1) * ldA ] = value ; \n\
}\n\
" ;



clblasFill2DFunctorDefault::clblasFill2DFunctorDefault(cl_context ctxt, 
                                                       cl_device_id dev,
                                                       int elemsize, 
                                                       cl_int & err) :  m_elemsize(elemsize), m_program(0)
{

  BinaryLookup bl(ctxt, dev, "clblasFill2DFunctorDefault");
  bl.variantInt(elemsize);
  
  if ( bl.found() ) // may create empty file or may wait until file is ready  
  {
    m_program =  bl.getProgram();
  }
  else
  {

    const char * options;
    switch( elemsize ) 
    {
    case 1:  options = "-DTYPE=char";     break ;
    case 2:  options = "-DTYPE=short";    break ; 
    case 4:  options = "-DTYPE=int";      break ;  //  or  'float'
    case 8:  options = "-DTYPE=long";     break ;  //  or  'double' or 'complex float'
    case 16: options = "-DTYPE=float4";   break ;  //  or  'complex float'
    default: options = NULL ; // shall never happen  
    }

    m_program = BinaryLookup::buildProgramFromSource(FILL2D_KERNEL_SRC, ctxt, dev, err, options);
    
    if (m_program)
    {
      bl.setProgram(m_program);
      bl.populateCache();
    }
    
  }

}


clblasFill2DFunctorDefault::~clblasFill2DFunctorDefault()
{
  if (this->m_program) {
    clReleaseProgram( this->m_program ) ; 
  } 
}

clblasStatus 
clblasFill2DFunctorDefault::execute(Args & args)
{
  cl_int err;
  cl_kernel kernel = clCreateKernel( this->m_program, "fill2d",  &err);
  if (err != CL_SUCCESS) return clblasStatus(err) ; 
  clblasFunctor::setKernelArg<cl_mem> (kernel, 0, args.A);
  clblasFunctor::setKernelArg<int> (kernel, 1, args.offA);
  clblasFunctor::setKernelArg<int> (kernel, 2, args.ldA);
  clblasFunctor::setKernelArgPtr      (kernel, 3, args.elemsize, args.value);
  
  size_t globalThreads[2] = { args.m , args.n };

  err = clEnqueueNDRangeKernel(args.queue, kernel, 2, NULL,
                               globalThreads, NULL , 
                               args.numEventsInWaitList, args.eventWaitList, args.events);

  clReleaseKernel(kernel) ;
  return clblasStatus(err) ;
}


clblasFill2DFunctorDefault * 
clblasFill2DFunctorDefault::provide(Args & args)
{
  // The current implementation only support the common scalar data 
  // sizes from 'char' (1) to 'double complex' 16 
  switch(args.elemsize) 
    {
    case 1:  
    case 2:  
    case 4:   
    case 8:   
    case 16:  
      break ;
    default:
      return NULL ;
    }

  cl_device_id dev;
  cl_context   ctxt;
  cl_int err = clblasFunctor::getDeviceAndContext(args.queue, dev, ctxt);

  if (err != CL_SUCCESS)
  {
      return NULL;
  }

  Cache::Lookup lookup(cache, ctxt, dev, args.elemsize ) ;

  if ( lookup.ok() ) {
    clblasFill2DFunctorDefault * functor = lookup.get();
    functor->retain(); // increment the reference counter to avoid deletion while it is still beeing used
    return functor;
  }
 
  clblasFill2DFunctorDefault * functor = new clblasFill2DFunctorDefault(ctxt, dev, args.elemsize, err);
  if (err != CL_SUCCESS)
  {
      return NULL;
  }

  lookup.set(functor) ;

  return functor;
    
}
