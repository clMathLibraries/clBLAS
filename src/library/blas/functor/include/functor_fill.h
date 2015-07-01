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

#ifndef _CLBLAS_FUNCTOR_FILL_H_
#define _CLBLAS_FUNCTOR_FILL_H_

#include "functor.h"

//
// The clblasFill2DFunctor provides a method to fill a rectangular part or a 
// 2D matrix with a single element value.
//
// The element size shall be 1, 2, 4, 8 or 16. Other values are not (yet) supported
//
// The functor operates in ColumnMajor mode 
//
class clblasFill2DFunctor : public clblasFunctor 
{
public:

  struct Args
  {
    cl_mem           A;
    size_t           offA;         // offset in A (in elements) 
    size_t           m ;           // number of rows
    size_t           n ;           // number of columns
    size_t           ldA ;         // distance between two columns (in elements)
    int              elemsize ; 
    const void *     value ;  
    cl_command_queue queue;    
    cl_uint          numEventsInWaitList;
    const cl_event * eventWaitList;
    cl_event *       events;

    Args(cl_mem  A,
         size_t  offA,   
         size_t  m,
         size_t  n,
         size_t  ldA,          // distance between two columns (in elements)
         int     elemsize, 
         const void *  value,       // The fill value (elemsize bytes)
         cl_command_queue queue,
         cl_uint          numEventsInWaitList,
         const cl_event * eventWaitList,
         cl_event *       events) 
      : A(A),
        offA(offA),
        m(m),
        n(n),
        ldA(ldA),
        elemsize(elemsize),
        value(value),
        queue(queue),
        numEventsInWaitList(numEventsInWaitList),
        eventWaitList(eventWaitList),
        events(events)        
    {
    }
  } ;


  virtual clblasStatus execute(Args & args) = 0;
 
} ;

//
// A default portable implementation of clblasFill2DFunctor
//
class clblasFill2DFunctorDefault : public clblasFill2DFunctor
{
private:
  clblasFill2DFunctorDefault(cl_context ctxt, 
                             cl_device_id dev,
                             int elemsize, 
                             cl_int & err) ;
  ~clblasFill2DFunctorDefault() ;
public:  
  static clblasFill2DFunctorDefault * provide(Args & args) ;  
public:  
  clblasStatus execute(Args & args) ;
private:  
  int        m_elemsize ;  // the element size. Will also be used as key in the cache
  cl_program m_program ;   
} ;

#endif
