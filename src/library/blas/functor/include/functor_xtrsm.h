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

#ifndef _CLBLAS_FUNCTOR_XTRSM_H_
#define _CLBLAS_FUNCTOR_XTRSM_H_

//
// This file provides the declarations of all XTRSM functors and related classes.
//
//
//


#include "functor.h"


//
// Base class for all XTRSM functors (DTRSM, STRSM, ...) 
//
template <class T>
class clblasXtrsmFunctor : public clblasFunctor 
{
  public:

    // Structure used to store all XTRSM arguments
    struct Args
    {

      clblasOrder order;
      clblasSide side;
      clblasUplo uplo;
      clblasTranspose transA;
      clblasDiag diag;
      size_t M;
      size_t N;
      T alpha;
      cl_mem A;
      size_t offA;
      size_t lda;
      cl_mem B;
      size_t offB;
      size_t ldb;
      cl_command_queue queue;
      cl_uint          numEventsInWaitList;
      const cl_event * eventWaitList;
      cl_event *       events;

      Args(clblasOrder order,
           clblasSide side,
           clblasUplo uplo,
           clblasTranspose transA,
           clblasDiag diag,
           size_t M,
           size_t N,
           T alpha,
           cl_mem A,
           size_t offA,
           size_t lda,
           cl_mem B,
           size_t offB,
           size_t ldb,
           cl_command_queue queue,
           cl_uint          numEventsInWaitList,
           const cl_event * eventWaitList,
           cl_event *       events)
         : order(order),
           side(side),
           uplo(uplo),
           transA(transA),
           diag(diag),
           M(M),
           N(N),
           alpha(alpha),
           A(A),
           offA(offA),
           lda(lda),
           B(B),
           offB(offB),
           ldb(ldb),
           queue(queue),
           numEventsInWaitList(numEventsInWaitList),
           eventWaitList(eventWaitList),
           events(events)
           
        {
        }
    };

public:

    virtual clblasStatus execute(Args &args) = 0;

} ;

// ================  STRSM ==================

//
// Base class for all functors providing a STRSM implementation
//
class clblasStrsmFunctor : public clblasXtrsmFunctor<cl_float>
{
};

//
// Fallback functor for STRSM using the original solver mechanism
//
class clblasStrsmFunctorFallback : public clblasStrsmFunctor 
{
public:   // Inherited members from clblasFunctor 
    virtual void retain();  
    virtual void release();
 public:  // Inherited members from clblasStrsmFunctor 
    virtual clblasStatus execute(Args & a);
 public:
    static clblasStrsmFunctorFallback * provide ();
};


// ================  DTRSM ==================

//
// Base class for all functors providing a DTRSM implementation
//
class clblasDtrsmFunctor : public clblasXtrsmFunctor<cl_double>
{
};

//
// Fallback functor for DTRSM using the original solver mechanism
//
class clblasDtrsmFunctorFallback : public clblasDtrsmFunctor 
{
public:   // Inherited members from clblasFunctor 
    virtual void retain();  
    virtual void release();
 public:  // Inherited members from clblasDtrsmFunctor 
    virtual clblasStatus execute(Args & a);
 public:
    static clblasDtrsmFunctorFallback * provide ();
};


// ================  CTRSM ==================

//
// Base class for all functors providing a CTRSM implementation
//
class clblasCtrsmFunctor : public clblasXtrsmFunctor<FloatComplex>
{
};

//
// Fallback functor for CTRSM using the original solver mechanism
//
class clblasCtrsmFunctorFallback : public clblasCtrsmFunctor 
{
public:   // Inherited members from clblasFunctor 
    virtual void retain();  
    virtual void release();
 public:  // Inherited members from clblasCtrsmFunctor 
    virtual clblasStatus execute(Args & a);
 public:
    static clblasCtrsmFunctorFallback * provide ();
};

// ================  ZTRSM ==================

//
// Base class for all functors providing a ZTRSM implementation
//
class clblasZtrsmFunctor : public clblasXtrsmFunctor<DoubleComplex>
{
};

//
// Fallback functor for ZTRSM using the original solver mechanism
//
class clblasZtrsmFunctorFallback : public clblasZtrsmFunctor 
{
public:   // Inherited members from clblasFunctor 
    virtual void retain();  
    virtual void release();
 public:  // Inherited members from clblasZtrsmFunctor 
    virtual clblasStatus execute(Args & a);
 public:
    static clblasZtrsmFunctorFallback * provide ();
};


#endif // _CLBLAS_FUNCTOR_XTRSM_H_
