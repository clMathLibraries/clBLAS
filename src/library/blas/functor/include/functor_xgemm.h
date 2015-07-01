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

#ifndef _CLBLAS_FUNCTOR_XGEMM_H_
#define _CLBLAS_FUNCTOR_XGEMM_H_

//
// This file provides the declarations of all XGEMM functors and related classes.
//
//
//


#include "functor.h"


//
// Base class for all XGEMM functors (DGEMM, SGEMM, ...) 
//
template <class T>
class clblasXgemmFunctor : public clblasFunctor 
{
  public:

    // Structure used to store all XGEMM arguments
    struct Args
    {
        clblasOrder      order;
        clblasTranspose  transA;
        clblasTranspose  transB;
        size_t           M;
        size_t           N;
        size_t           K;
        T                alpha;
        cl_mem           A;
        size_t           offA;
        size_t           lda;
        cl_mem           B;
        size_t           offB;
        size_t           ldb;
        T                beta;
        cl_mem           C;
        size_t           offC;
        size_t           ldc;
        cl_command_queue queue;
        cl_uint          numEventsInWaitList;
        const cl_event * eventWaitList;
        cl_event *       events;

        Args(clblasOrder order,
             clblasTranspose transA,
             clblasTranspose transB,
             size_t M,
             size_t N,
             size_t K,
             T alpha,
             cl_mem A,
             size_t offA,
             size_t lda,
             cl_mem B,
             size_t offB,
             size_t ldb,
             T beta,
             cl_mem C,
             size_t offC,
             size_t ldc,
             cl_command_queue queue,
             cl_uint numEventsInWaitList,
             const cl_event *eventWaitList,
             cl_event *events)
            : order(order),
              transA(transA),
              transB(transB),
              M(M),
              N(N),
              K(K),
              alpha(alpha),
              A(A),
              offA(offA),
              lda(lda),
              B(B),
              offB(offB),
              ldb(ldb),
              beta(beta),
              C(C),
              offC(offC),
              ldc(ldc),
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

// ================  SGEMM ==================

//
// Base class for all functors providing a SGEMM implementation
//
class clblasSgemmFunctor : public clblasXgemmFunctor<cl_float>
{
};

//
// Fallback functor for SGEMM using the original solver mechanism
//
class clblasSgemmFunctorFallback : public clblasSgemmFunctor 
{
public:   // Inherited members from clblasFunctor 
    virtual void retain();  
    virtual void release();
 public:  // Inherited members from clblasSgemmFunctor 
    virtual clblasStatus execute(Args & a);
 public:
    static clblasSgemmFunctorFallback * provide ();
};



// ================  DGEMM ==================

//
//
// Base class for all functors providing a DGEMM implementation
//
class clblasDgemmFunctor : public clblasXgemmFunctor<cl_double>
{
};

//
// Fallback functor for DGEMM using the original solver mechanism
//
class clblasDgemmFunctorFallback : public clblasDgemmFunctor 
{
public:   // Inherited members from clblasFunctor 
    virtual void retain();  
    virtual void release();
 public:  // Inherited members from clblasDgemmFunctor 
    virtual clblasStatus execute(Args & a);
 public:
    static clblasDgemmFunctorFallback * provide ();
};


// ================  CGEMM ==================

//
// Base class for all functors providing a CGEMM implementation
//
class clblasCgemmFunctor : public clblasXgemmFunctor<FloatComplex>
{
};

//
// Fallback functor for CGEMM using the original solver mechanism
//
class clblasCgemmFunctorFallback : public clblasCgemmFunctor 
{
public:   // Inherited members from clblasFunctor 
    virtual void retain();  
    virtual void release();
 public:  // Inherited members from clblasCgemmFunctor 
    virtual clblasStatus execute(Args & a);
 public:
    static clblasCgemmFunctorFallback * provide ();
};


// ================  ZGEMM ==================

//
// Base class for all functors providing a ZGEMM implementation
//
class clblasZgemmFunctor : public clblasXgemmFunctor<DoubleComplex>
{
};

//
// Fallback functor for ZGEMM using the original solver mechanism
//
class clblasZgemmFunctorFallback : public clblasZgemmFunctor 
{
public:   // Inherited members from clblasFunctor 
    virtual void retain();  
    virtual void release();
 public:  // Inherited members from clblasZgemmFunctor 
    virtual clblasStatus execute(Args & a);
 public:
    static clblasZgemmFunctorFallback * provide ();
};


#endif // _CLBLAS_FUNCTOR_XGEMM_H_
