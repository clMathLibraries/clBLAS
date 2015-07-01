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

#ifndef _CLBLAS_FUNCTOR_XSCAL_H_
#define _CLBLAS_FUNCTOR_XSCAL_H_

//
// This file provides the declarations of all XSCAL functors and related classes.
//
//
//


#include <functor.h>


//
// Base class for all XSCAL functors (DSCAL, SSCAL, ...) 
//
template<typename TX, typename Talpha> 
class clblasXscalFunctor : public clblasFunctor 
{
public:

  // Structure used to store all XSCAL arguments
  struct Args
  {
    size_t           N;
    Talpha           alpha;
    cl_mem           X;
    size_t           offx;
    int              incx;
    cl_command_queue queue;
    cl_uint          numEventsInWaitList;
    const cl_event * eventWaitList;
    cl_event *       events;
  
    Args(size_t N,
         Talpha alpha,
         cl_mem X,
         size_t offx,
         int    incx,
         cl_command_queue queue,
         cl_uint          numEventsInWaitList,
         const cl_event * eventWaitList,
         cl_event *       events) 
      : N(N),
        alpha(alpha),
        X(X),
        offx(offx),
        incx(incx),
        queue(queue),
        numEventsInWaitList(numEventsInWaitList),
        eventWaitList(eventWaitList),
        events(events)
    {
    }
  };

  virtual clblasStatus execute(Args & args) = 0;
};



//
// Base class for all functors providing a SSCAL implementation
//
class clblasSscalFunctor: public clblasXscalFunctor<cl_float, cl_float>
{
};

//
// Base class for all functors providing a DSCAL implementation
//
class clblasDscalFunctor: public clblasXscalFunctor<cl_double, cl_double>
{
};

//
// Base class for all functors providing a CSCAL implementation
//
class clblasCscalFunctor: public clblasXscalFunctor<cl_float2, cl_float2>
{
};

//
// Base class for all functors providing a ZSCAL implementation
//
class clblasZscalFunctor: public clblasXscalFunctor<cl_double2, cl_double2>
{
};

//
// Base class for all functors providing a CSSCAL implementation
//
class clblasCsscalFunctor: public clblasXscalFunctor<cl_float2, cl_float>
{
};

//
// Base class for all functors providing a ZDSCAL implementation
//
class clblasZdscalFunctor: public clblasXscalFunctor<cl_double2, cl_double>
{
};



//
// Fallback functor for SSCAL : implement the sscal using the old solver mechanism
//
class clblasSscalFunctorFallback : public clblasSscalFunctor 
{
  public:   // Inherited members from clblasFunctor 
    virtual void retain();  
    virtual void release();
  public:  // Inherited members from clblasSscalFunctor 
    virtual clblasStatus execute(Args & a);
  public:
    static clblasSscalFunctorFallback * provide ();
};

//
// Fallback functor for DSCAL : implement the dscal using the old solver mechanism
//
class clblasDscalFunctorFallback : public clblasDscalFunctor 
{
  public:   // Inherited members from clblasFunctor 
    virtual void retain();  
    virtual void release();
  public:  // Inherited members from clblasDscalFunctor 
    virtual clblasStatus execute(Args & a);
  public:
    static clblasDscalFunctorFallback * provide ();
};

//
// Fallback functor for CSCAL : implement the Cscal using the old solver mechanism
//
class clblasCscalFunctorFallback : public clblasCscalFunctor 
{
  public:   // Inherited members from clblasFunctor 
    virtual void retain();  
    virtual void release();
  public:  // Inherited members from clblasCscalFunctor 
    virtual clblasStatus execute(Args & a);
  public:
    static clblasCscalFunctorFallback * provide ();
};

//
// Fallback functor for ZSCAL : implement the zscal using the old solver mechanism
//
class clblasZscalFunctorFallback : public clblasZscalFunctor 
{
  public:   // Inherited members from clblasFunctor 
    virtual void retain();  
    virtual void release();
  public:  // Inherited members from clblasZscalFunctor 
    virtual clblasStatus execute(Args & a);
  public:
    static clblasZscalFunctorFallback * provide ();
};

//
// Fallback functor for CSSCAL : implement the Csscal using the old solver mechanism
//
class clblasCsscalFunctorFallback : public clblasCsscalFunctor 
{
  public:   // Inherited members from clblasFunctor 
    virtual void retain();  
    virtual void release();
  public:  // Inherited members from clblasCsscalFunctor 
    virtual clblasStatus execute(Args & a);
  public:
    static clblasCsscalFunctorFallback * provide ();
};

//
// Fallback functor for ZDSCAL : implement the zdscal using the old solver mechanism
//
class clblasZdscalFunctorFallback : public clblasZdscalFunctor 
{
  public:   // Inherited members from clblasFunctor 
    virtual void retain();  
    virtual void release();
  public:  // Inherited members from clblasZdscalFunctor 
    virtual clblasStatus execute(Args & a);
  public:
    static clblasZdscalFunctorFallback * provide ();
};


#endif // _CLBLAS_FUNCTOR_XSCAL_H_
