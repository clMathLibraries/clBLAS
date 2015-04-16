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

#include <functor.h>
#include <functor_selector.h>

//
// This file provide the functor based public clBLAS API for
//
//   clblasSscal() 
//   clblasDscal() 
//   clblasCscal() 
//   clblasZscal() 
//   clblasCsscal() 
//   clblasZdscal() 
//


extern "C" 
clblasStatus
clblasSscal(
    size_t N,
    float alpha,
    cl_mem X,
    size_t offx,
    int incx,
    cl_uint numCommandQueues,
    cl_command_queue *commandQueues,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
  CHECK_QUEUES(numCommandQueues, commandQueues);
  CHECK_EVENTS(numEventsInWaitList, eventWaitList);
  CHECK_VECTOR_X(TYPE_FLOAT, N, X, offx, incx);

  clblasSscalFunctor * functor ;

  if ( numCommandQueues>1 ) 
  {
    numCommandQueues = 1 ;  // No support for multi-device (yet)
  }

  cl_command_queue queue = commandQueues[0]; 


  clblasSscalFunctor::Args args(N,
                                alpha,
                                X,
                                offx,
                                incx,
                                queue,
                                numEventsInWaitList,
                                eventWaitList,
                                events);
  
   clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);
   
   functor = fselector->select_sscal_specific(args);

   clblasStatus res = functor->execute(args);

   functor->release();

   return res;
}



extern "C" 
clblasStatus
clblasDscal(
    size_t N,
    double alpha,
    cl_mem X,
    size_t offx,
    int incx,
    cl_uint numCommandQueues,
    cl_command_queue *commandQueues,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
  CHECK_QUEUES(numCommandQueues, commandQueues);
  CHECK_EVENTS(numEventsInWaitList, eventWaitList);
  CHECK_VECTOR_X(TYPE_DOUBLE, N, X, offx, incx);

  clblasDscalFunctor * functor ;

  if ( numCommandQueues>1 ) 
  {
    numCommandQueues = 1 ;  // No support for multi-device (yet)
  }

  cl_command_queue queue = commandQueues[0]; 


  clblasDscalFunctor::Args args(N,
                                alpha,
                                X,
                                offx,
                                incx,
                                queue,
                                numEventsInWaitList,
                                eventWaitList,
                                events);
  
   clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);
   
   functor = fselector->select_dscal_specific(args);

   clblasStatus res = functor->execute(args);

   functor->release();

   return res;
	
}





extern "C" 
clblasStatus
clblasCscal(
    size_t N,
    cl_float2 alpha,
    cl_mem X,
    size_t offx,
    int incx,
    cl_uint numCommandQueues,
    cl_command_queue *commandQueues,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
  CHECK_QUEUES(numCommandQueues, commandQueues);
  CHECK_EVENTS(numEventsInWaitList, eventWaitList);
  CHECK_VECTOR_X(TYPE_COMPLEX_FLOAT, N, X, offx, incx);

  clblasCscalFunctor * functor ;

  if ( numCommandQueues>1 ) 
  {
    numCommandQueues = 1 ;  // No support for multi-device (yet)
  }

  cl_command_queue queue = commandQueues[0]; 


  clblasCscalFunctor::Args args(N,
                                alpha,
                                X,
                                offx,
                                incx,
                                queue,
                                numEventsInWaitList,
                                eventWaitList,
                                events);
  
   clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);
   
   functor = fselector->select_cscal_specific(args);

   clblasStatus res = functor->execute(args);

   functor->release();

   return res;
}


extern "C" 
clblasStatus
clblasZscal(
    size_t N,
    cl_double2 alpha,
    cl_mem X,
    size_t offx,
    int incx,
    cl_uint numCommandQueues,
    cl_command_queue *commandQueues,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
  CHECK_QUEUES(numCommandQueues, commandQueues);
  CHECK_EVENTS(numEventsInWaitList, eventWaitList);
  CHECK_VECTOR_X(TYPE_COMPLEX_DOUBLE, N, X, offx, incx);

  clblasZscalFunctor * functor ;

  if ( numCommandQueues>1 ) 
  {
    numCommandQueues = 1 ;  // No support for multi-device (yet)
  }

  cl_command_queue queue = commandQueues[0]; 


  clblasZscalFunctor::Args args(N,
                                alpha,
                                X,
                                offx,
                                incx,
                                queue,
                                numEventsInWaitList,
                                eventWaitList,
                                events);
  
   clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);
   
   functor = fselector->select_zscal_specific(args);

   clblasStatus res = functor->execute(args);

   functor->release();

   return res;	
}


extern "C" 
clblasStatus
clblasCsscal(
    size_t N,
    float alpha,
    cl_mem X,
    size_t offx,
    int incx,
    cl_uint numCommandQueues,
    cl_command_queue *commandQueues,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
  CHECK_QUEUES(numCommandQueues, commandQueues);
  CHECK_EVENTS(numEventsInWaitList, eventWaitList);
  CHECK_VECTOR_X(TYPE_COMPLEX_FLOAT, N, X, offx, incx);

  clblasCsscalFunctor * functor ;
  
  if ( numCommandQueues>1 ) 
  {
    numCommandQueues = 1 ;  // No support for multi-device (yet)
  }

  cl_command_queue queue = commandQueues[0]; 


  clblasCsscalFunctor::Args args(N,
                                alpha,
                                X,
                                offx,
                                incx,
                                queue,
                                numEventsInWaitList,
                                eventWaitList,
                                events);
  
   clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);
   
   functor = fselector->select_csscal_specific(args);

   clblasStatus res = functor->execute(args);

   functor->release();

   return res;
}


extern "C" 
clblasStatus
clblasZdscal(
    size_t N,
    double alpha,
    cl_mem X,
    size_t offx,
    int incx,
    cl_uint numCommandQueues,
    cl_command_queue *commandQueues,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
  CHECK_QUEUES(numCommandQueues, commandQueues);
  CHECK_EVENTS(numEventsInWaitList, eventWaitList);
  CHECK_VECTOR_X(TYPE_COMPLEX_DOUBLE, N, X, offx, incx);

  clblasZdscalFunctor * functor ;

  if ( numCommandQueues>1 ) 
  {
    numCommandQueues = 1 ;  // No support for multi-device (yet)
  }

  cl_command_queue queue = commandQueues[0]; 


  clblasZdscalFunctor::Args args(N,
                                alpha,
                                X,
                                offx,
                                incx,
                                queue,
                                numEventsInWaitList,
                                eventWaitList,
                                events);
  
   clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);
   
   functor = fselector->select_zdscal_specific(args);

   clblasStatus res = functor->execute(args);

   functor->release();

   return res;	
}

