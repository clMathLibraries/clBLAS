 /************************************************************************
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


// Transform a trsm in clblasRowMajor into a trsm in clblasColumnMajor:
//
// The idea is basically that
//   B = A*X
// can be computed as 
//   B' = (A*X)'
//      = X'*A'
// And since changing the order is basically a transpose on each matrix,
// the formula becomes with the new order
//   B = X*A (so only the side, the uplo must be changed and the M and N sizes swapped)
//
// When enabled, only the ColumnMajor kernels need to be implemented
// for all TRSM 
//

#define FORCE_COLUMN_MAJOR 1

#if FORCE_COLUMN_MAJOR
template <typename Args>
static void force_trsm_column_major(Args & args)
{
    if (args.order == clblasRowMajor)
    {
      std::swap(args.M, args.N);
      args.side = (args.side == clblasLeft ) ? clblasRight : clblasLeft  ;
      args.uplo = (args.uplo == clblasUpper) ? clblasLower : clblasUpper ;
      args.order = clblasColumnMajor;
    }
}
#endif

//
// This file provide the public clBLAS API for
//
//   clblasStrsm() 
//   clblasDtrsm() 
//   clblasCtrsm() 
//   clblasZtrsm() 
//
// using functors 
// 
// Potential optimizations: 
////
//  - Get rid of the 'order' argument assuming that 
//    row-major is equivalent to the transpose of column-major.
//    That is  
//
//       B = A*X
//
//    is equivalent to 
//
//       B' = X'*A'
//
//    and, when considering the opposite order, is equivalent to   
//
//       B = X*A (with A swap between upper and lower)
//
//    By applying that transformation early, the functors implementing 
//    the TRSMs only have to consider one of the two cases. 
//


extern "C" 
clblasStatus 
clblasStrsm(
    clblasOrder order,
    clblasSide side,
    clblasUplo uplo,
    clblasTranspose transA,
    clblasDiag diag,
    size_t M,
    size_t N,
    cl_float alpha,
    const cl_mem A,
    size_t offA,
    size_t lda,
    cl_mem B,
    size_t offB,
    size_t ldb,
    cl_uint numCommandQueues,
    cl_command_queue *commandQueues,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
   CHECK_QUEUES(numCommandQueues, commandQueues);
   CHECK_EVENTS(numEventsInWaitList, eventWaitList);

   if ( numCommandQueues>1 ) 
   {
       numCommandQueues = 1 ;  // No support for multi-device (yet)
   }

   cl_command_queue queue = commandQueues[0]; 

   clblasStrsmFunctor::Args args(order, 
                                 side, 
                                 uplo, 
                                 transA, 
                                 diag, 
                                 M, N, 
                                 alpha,
                                 A, offA, lda,
                                 B, offB, ldb, 
                                 queue,
                                 numEventsInWaitList, 
                                 eventWaitList, 
                                 events);


#if FORCE_COLUMN_MAJOR
   force_trsm_column_major(args);
#endif

   clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);

   clblasStrsmFunctor * functor = fselector->select_strsm_specific(args);

   clblasStatus res = functor->execute(args);

   functor->release();

   return res;
}

extern "C" 
clblasStatus 
clblasDtrsm(
    clblasOrder order,
    clblasSide side,
    clblasUplo uplo,
    clblasTranspose transA,
    clblasDiag diag,
    size_t M,
    size_t N,
    cl_double alpha,
    const cl_mem A,
    size_t offA,
    size_t lda,
    cl_mem B,
    size_t offB,
    size_t ldb,
    cl_uint numCommandQueues,
    cl_command_queue *commandQueues,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
   CHECK_QUEUES(numCommandQueues, commandQueues);
   CHECK_EVENTS(numEventsInWaitList, eventWaitList);

   if ( numCommandQueues>1 ) 
   {
       numCommandQueues = 1 ;  // No support for multi-device (yet)
   }

   cl_command_queue queue = commandQueues[0]; 

   clblasDtrsmFunctor::Args args(order, 
                                 side, 
                                 uplo, 
                                 transA, 
                                 diag, 
                                 M, N, 
                                 alpha,
                                 A, offA, lda,
                                 B, offB, ldb, 
                                 queue,
                                 numEventsInWaitList, 
                                 eventWaitList, 
                                 events);


   clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);

   clblasDtrsmFunctor * functor = fselector->select_dtrsm_specific(args);

   clblasStatus res = functor->execute(args);

   functor->release();

   return res;
}

extern "C" 
clblasStatus 
clblasCtrsm(
    clblasOrder order,
    clblasSide side,
    clblasUplo uplo,
    clblasTranspose transA,
    clblasDiag diag,
    size_t M,
    size_t N,
    FloatComplex alpha,
    const cl_mem A,
    size_t offA,
    size_t lda,
    cl_mem B,
    size_t offB,
    size_t ldb,
    cl_uint numCommandQueues,
    cl_command_queue *commandQueues,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
   CHECK_QUEUES(numCommandQueues, commandQueues);
   CHECK_EVENTS(numEventsInWaitList, eventWaitList);

   if ( numCommandQueues>1 ) 
   {
       numCommandQueues = 1 ;  // No support for multi-device (yet)
   }

   cl_command_queue queue = commandQueues[0]; 

   clblasCtrsmFunctor::Args args(order, 
                                 side, 
                                 uplo, 
                                 transA, 
                                 diag, 
                                 M, N, 
                                 alpha,
                                 A, offA, lda,
                                 B, offB, ldb, 
                                 queue,
                                 numEventsInWaitList, 
                                 eventWaitList, 
                                 events);


#if FORCE_COLUMN_MAJOR
   force_trsm_column_major(args);
#endif

   clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);

   clblasCtrsmFunctor * functor = fselector->select_ctrsm_specific(args);

   clblasStatus res = functor->execute(args);

   functor->release();

   return res;
}

extern "C" 
clblasStatus 
clblasZtrsm(
    clblasOrder order,
    clblasSide side,
    clblasUplo uplo,
    clblasTranspose transA,
    clblasDiag diag,
    size_t M,
    size_t N,
    DoubleComplex alpha,
    const cl_mem A,
    size_t offA,
    size_t lda,
    cl_mem B,
    size_t offB,
    size_t ldb,
    cl_uint numCommandQueues,
    cl_command_queue *commandQueues,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
   CHECK_QUEUES(numCommandQueues, commandQueues);
   CHECK_EVENTS(numEventsInWaitList, eventWaitList);

   if ( numCommandQueues>1 ) 
   {
       numCommandQueues = 1 ;  // No support for multi-device (yet)
   }

   cl_command_queue queue = commandQueues[0]; 

   clblasZtrsmFunctor::Args args(order, 
                                 side, 
                                 uplo, 
                                 transA, 
                                 diag, 
                                 M, N, 
                                 alpha,
                                 A, offA, lda,
                                 B, offB, ldb, 
                                 queue,
                                 numEventsInWaitList, 
                                 eventWaitList, 
                                 events);


#if FORCE_COLUMN_MAJOR
   force_trsm_column_major(args);
#endif

   clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);

   clblasZtrsmFunctor * functor = fselector->select_ztrsm_specific(args);

   clblasStatus res = functor->execute(args);

   functor->release();

   return res;
}
