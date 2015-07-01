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


#include <string.h>
#include <clBLAS.h>

#include <functor.h>
#include <functor_selector.h>

// Transform a gemm in clblasRowMajor into a gemm in clblasColumnMajor:
//
// The idea is basically that
//   C = A*B + C
// can be computed as 
//   C' = (A*B + C)'
//      = B'*A' + C'
// And since changing the order is basically a transpose on each matrix,
// the formula becomes with the new order
//   C = B*A + C
//
// When enabled, only the ColumnMajor kernels need to be implemented
// for all GEMM 
//

#define FORCE_COLUMN_MAJOR 1

#if FORCE_COLUMN_MAJOR
template <typename Args>
static void force_gemm_column_major(Args & args)
{
    if (args.order == clblasRowMajor)
    {
        std::swap(args.transA , args.transB);
        std::swap(args.M      , args.N);
        std::swap(args.offA   , args.offB);
        std::swap(args.lda    , args.ldb);
        std::swap(args.A      , args.B);
        args.order = clblasColumnMajor;
    }
}
#endif

//
// This file provide the public clBLAS API for
//
//   clblasSgemm() 
//   clblasDgemm() 
//   clblasCgemm() 
//   clblasZgemm() 
//
// using functors 
// 
// Potential optimizations: 
//
//  - Check the values of alpha, beta, M, N and K to 
//    transform the gemm into an equivalent but cheaper 
//    scal or gemv where possible.
//
//  - Get rid of the 'order' argument assuming that 
//    row-major is equivalent to the transpose of column-major.
//    That is  
//
//       C  = alpha * A * B + beta * C 
//
//    is equivalent to 
//
//       C' = alpha * B' * A' + beta * C'  
//
//    and, when considering the opposite order, is equivalent to   
//
//       C  = alpha * B * A + beta * C  
//
//    By applying that transformation early, the functors implementing 
//    the GEMMs only have to consider one of the two cases. 
//


extern "C" 
clblasStatus 
clblasSgemm( clblasOrder order,
             clblasTranspose transA,
             clblasTranspose transB,
             size_t M, size_t N, size_t K,
             cl_float alpha,
             const cl_mem A, size_t offA, size_t lda,
             const cl_mem B, size_t offB, size_t ldb,
             cl_float beta,
             cl_mem C, size_t offC,  size_t ldc,
             cl_uint numCommandQueues,
             cl_command_queue *commandQueues,
             cl_uint numEventsInWaitList,
             const cl_event *eventWaitList,
             cl_event *events)
{
   CHECK_QUEUES(numCommandQueues, commandQueues);
   CHECK_EVENTS(numEventsInWaitList, eventWaitList);
   CHECK_MATRIX_A(TYPE_FLOAT, order, transA, A, M, K, offA, lda);
   CHECK_MATRIX_B(TYPE_FLOAT, order, transB, B, K, N, offB, ldb);
   CHECK_MATRIX_C(TYPE_FLOAT, order, clblasNoTrans, C, M, N, offC, ldc);

   if ( numCommandQueues>1 ) 
   {
       numCommandQueues = 1 ;  // No support for multi-device (yet)
   }

   cl_command_queue queue = commandQueues[0]; 

   clblasSgemmFunctor::Args args(order,
                                 transA,
                                 transB,
                                 M, N, K,
                                 alpha,
                                 A, offA, lda,
                                 B, offB, ldb,
                                 beta,
                                 C, offC, ldc,
                                 queue,
                                 numEventsInWaitList,
                                 eventWaitList,
                                 events);

#if FORCE_COLUMN_MAJOR
   force_gemm_column_major(args);
#endif

   clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);

   clblasSgemmFunctor * functor = fselector->select_sgemm_specific(args);

   clblasStatus res = functor->execute(args);

   functor->release();

   return res;
}

extern "C" 
clblasStatus
clblasDgemm( clblasOrder order,
             clblasTranspose transA,
             clblasTranspose transB,
             size_t M, size_t N,  size_t K,
             cl_double alpha,
             const cl_mem A, size_t offA, size_t lda,
             const cl_mem B, size_t offB, size_t ldb,
             cl_double beta,
             cl_mem C, size_t offC, size_t ldc,
             cl_uint numCommandQueues,
             cl_command_queue *commandQueues,
             cl_uint numEventsInWaitList,
             const cl_event *eventWaitList,
             cl_event *events)
{
   CHECK_QUEUES(numCommandQueues, commandQueues);
   CHECK_EVENTS(numEventsInWaitList, eventWaitList);
   CHECK_MATRIX_A(TYPE_DOUBLE, order, transA, A, M, K, offA, lda);
   CHECK_MATRIX_B(TYPE_DOUBLE, order, transB, B, K, N, offB, ldb);
   CHECK_MATRIX_C(TYPE_DOUBLE, order, clblasNoTrans, C, M, N, offC, ldc);

   if ( numCommandQueues>1 ) 
   {
       numCommandQueues = 1 ;  // No support for multi-device (yet)
   }

   cl_command_queue queue = commandQueues[0]; 

   clblasDgemmFunctor::Args args(order,
                                 transA,
                                 transB,
                                 M, N, K,
                                 alpha,
                                 A, offA, lda,
                                 B, offB, ldb,
                                 beta,
                                 C, offC, ldc,
                                 queue,
                                 numEventsInWaitList,
                                 eventWaitList,
                                 events);

#if FORCE_COLUMN_MAJOR
   force_gemm_column_major(args);
#endif

   clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);

   clblasDgemmFunctor * functor = fselector->select_dgemm_specific(args);

   clblasStatus res = functor->execute(args);

   functor->release();

   return res;
}

extern "C" 
clblasStatus
clblasCgemm(
    clblasOrder order,
    clblasTranspose transA,
    clblasTranspose transB,
    size_t M, size_t N, size_t K,
    FloatComplex alpha,
    const cl_mem A, size_t offA, size_t lda,
    const cl_mem B, size_t offB, size_t ldb,
    FloatComplex beta,
    cl_mem C, size_t offC, size_t ldc,
    cl_uint numCommandQueues,
    cl_command_queue *commandQueues,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
   CHECK_QUEUES(numCommandQueues, commandQueues);
   CHECK_EVENTS(numEventsInWaitList, eventWaitList);
   CHECK_MATRIX_A(TYPE_COMPLEX_FLOAT, order, transA, A, M, K, offA, lda);
   CHECK_MATRIX_B(TYPE_COMPLEX_FLOAT, order, transB, B, K, N, offB, ldb);
   CHECK_MATRIX_C(TYPE_COMPLEX_FLOAT, order, clblasNoTrans, C, M, N, offC, ldc);

   if ( numCommandQueues>1 ) 
   {
       numCommandQueues = 1 ;  // No support for multi-device (yet)
   }

   cl_command_queue queue = commandQueues[0]; 

   clblasCgemmFunctor::Args args(order,
                                 transA,
                                 transB,
                                 M, N, K,
                                 alpha,
                                 A, offA, lda,
                                 B, offB, ldb,
                                 beta,
                                 C, offC, ldc,
                                 queue,
                                 numEventsInWaitList,
                                 eventWaitList,
                                 events);

#if FORCE_COLUMN_MAJOR
   force_gemm_column_major(args);
#endif

   clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);

   clblasCgemmFunctor * functor = fselector->select_cgemm_specific(args);

   clblasStatus res = functor->execute(args);

   functor->release();

   return res;
}

extern "C" 
clblasStatus
clblasZgemm(
    clblasOrder order,
    clblasTranspose transA,
    clblasTranspose transB,
    size_t M, size_t N, size_t K,
    DoubleComplex alpha,
    const cl_mem A, size_t offA, size_t lda,
    const cl_mem B, size_t offB, size_t ldb,
    DoubleComplex beta,
    cl_mem C, size_t offC, size_t ldc,
    cl_uint numCommandQueues,
    cl_command_queue *commandQueues,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
   CHECK_QUEUES(numCommandQueues, commandQueues);
   CHECK_EVENTS(numEventsInWaitList, eventWaitList);
   CHECK_MATRIX_A(TYPE_COMPLEX_DOUBLE, order, transA, A, M, K, offA, lda);
   CHECK_MATRIX_B(TYPE_COMPLEX_DOUBLE, order, transB, B, K, N, offB, ldb);
   CHECK_MATRIX_C(TYPE_COMPLEX_DOUBLE, order, clblasNoTrans, C, M, N, offC, ldc);

   if ( numCommandQueues>1 ) 
   {
       numCommandQueues = 1 ;  // No support for multi-device (yet)
   }

   cl_command_queue queue = commandQueues[0]; 

   clblasZgemmFunctor::Args args(order,
                                 transA,
                                 transB,
                                 M, N, K,
                                 alpha,
                                 A, offA, lda,
                                 B, offB, ldb,
                                 beta,
                                 C, offC, ldc,
                                 queue,
                                 numEventsInWaitList,
                                 eventWaitList,
                                 events);

#if FORCE_COLUMN_MAJOR
   force_gemm_column_major(args);
#endif

   clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);

   clblasZgemmFunctor * functor = fselector->select_zgemm_specific(args);

   clblasStatus res = functor->execute(args);

   functor->release();

   return res;
}
