/************************************************************************
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

#include <string.h>
#include <clBLAS.h>
#include <limits.h>

#include <functor.h>
#include <functor_selector.h>


#define SWAP(TYPE,a,b)  do { TYPE swap_tmp_ = a ; a = b ; b = swap_tmp_ ; } while(0) 

// Return true if the area starting from pint (x,y) and of size (w,h) is 
// within the array of size d1 x d2
static int inside2d( size_t d1, size_t d2, int x, int y, size_t w, size_t h ) 
{
  // Very very large dimensions are likely a bug
  size_t MAXDIM = ((size_t)INT_MAX)  ;
  if ( d1 >= MAXDIM ) return 0 ; 
  if ( d2 >= MAXDIM ) return 0 ;
  if ( w  >= MAXDIM ) return 0 ; 
  if ( h  >= MAXDIM ) return 0 ;

  if ( x < 0 || x >= (int)d1 ) return 0 ;
  size_t max_w = (size_t)(d1-x) ;
  if ( w > max_w ) return 0 ;

  if ( y < 0 || y >= (int)d2 ) return 0 ;
  size_t max_h = (size_t)(d2-y) ;
  if ( h > max_h ) return 0 ;
       
  return 1 ;
}

extern "C" 
clblasStatus clblasFillVectorAsync( size_t nb_elem,
    size_t element_size,
    cl_mem A, size_t offA,
    const void * host,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *event)
{

  return (clblasStatus) clEnqueueFillBuffer(command_queue, 
                                            A,
                                            host,
                                            element_size,
                                            offA*element_size,
                                            nb_elem*element_size,
                                            numEventsInWaitList,
                                            eventWaitList,
                                            event);
}



extern "C" 
clblasStatus clblasFillVector(
    size_t nb_elem,
    size_t element_size,
    cl_mem A, size_t offA,
    const void * host,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList)
{
  cl_event event ;
  cl_int err = clblasFillVectorAsync( 
      nb_elem, 
      element_size, 
      A, offA, 
      host, 
      command_queue, 
      numEventsInWaitList, eventWaitList,
      &event) ;

  if (err == clblasSuccess)  {
    err = clWaitForEvents(1,&event) ; 
  }

  return (clblasStatus)  err ; 
}

extern "C" 
clblasStatus clblasFillSubMatrixAsync(
    clblasOrder order,
    size_t element_size,
    cl_mem A, size_t offA, size_t ldA,
    size_t nrA, size_t ncA,
    int xA, int yA,
    size_t nx, size_t ny,
    const void *host,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *event)
{
  // Transform Row-major into equivalent ColumnMajor so X becomes the contiguous dimension.  
  if( order == clblasRowMajor )
  {
    SWAP(size_t, nrA, ncA);
    SWAP(int,    xA,  yA);
    SWAP(size_t, nx,  ny);
  }

  // Check that the specified area is within the array
  if ( !inside2d( nrA,ncA, xA,yA , nx,  ny ) ) {
    return clblasInvalidValue ;
  }

  // If the area to fill is contiguous then use clblasFillVector 
  if ( nx==ldA || ny==1 ) 
  {
    return clblasFillVectorAsync( nx*ny, 
                                  element_size, 
                                  A,
                                  offA + xA + yA*ldA, 
                                  host,
                                  command_queue,
                                  numEventsInWaitList,
                                  eventWaitList,
                                  event) ;
  }
  else if (1) 
  {
    
    clblasFill2DFunctor::Args args(A,
                                   offA + xA + yA*ldA,  
                                   nx,ny,
                                   ldA,
                                   element_size, 
                                   host, 
                                   command_queue,
                                   numEventsInWaitList,
                                   eventWaitList,
                                   event) ;
    
    clblasFunctorSelector  * fselector = clblasFunctorSelector::find(command_queue);

    clblasFill2DFunctor * functor = fselector->select_fill2d_specific(args);

    if (!functor) 
      return clblasInvalidValue ;
    
    cl_int err = functor->execute(args);
    
    functor->release();
    return (clblasStatus) err ; 
  } 
  else
  {
    // Temporary: perform one fill per row
    cl_int err ;
    for( size_t i=0; i<ny ; i++ ) 
      {
          err =  clblasFillVectorAsync( nx , 
                                       element_size, 
                                       A,
                                       offA + xA + (yA+i)*ldA, 
                                       host,
                                       command_queue,
                                       numEventsInWaitList,
                                       eventWaitList,
                                       event) ;
         if (err!=clblasSuccess) 
           return (clblasStatus) err ;
      }
    return clblasSuccess ; 
  }
}

extern "C" 
clblasStatus clblasFillSubMatrix(
    clblasOrder order,
    size_t element_size,
    cl_mem A, size_t offA, size_t ldA,
    size_t nrA, size_t ncA,
    size_t xA, size_t yA,
    size_t nx, size_t ny,
    const void *host,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList)
{
  cl_event event ;
  cl_int err = clblasFillSubMatrixAsync(order,
                                        element_size,
                                        A, offA, ldA,
                                        nrA, ncA,
                                        xA, yA,
                                        nx, ny,
                                        host,
                                        command_queue,
                                        numEventsInWaitList,
                                        eventWaitList,
                                        &event
                                   ) ;

  if (err == clblasSuccess) 
  {
    err = clWaitForEvents(1,&event) ; 
  }

  return (clblasStatus)err ; 
}


extern "C" 
clblasStatus clblasFillMatrix( clblasOrder order,
                               size_t element_size,
                               cl_mem A, size_t offA, size_t ldA,
                               size_t sxA, size_t syA,
                               const void *host,
                               cl_command_queue command_queue,
                               cl_uint numEventsInWaitList,
                               const cl_event *eventWaitList)
{
  return  clblasFillSubMatrix( order,
                               element_size,
                               A, offA, ldA,
                               sxA, syA,
                               0, 0,
                               sxA, syA,
                               host,
                               command_queue,
                               numEventsInWaitList,
                               eventWaitList) ;
}


extern "C" 
clblasStatus clblasFillMatrixAsync( clblasOrder order,
                                    size_t element_size,
                                    cl_mem A, size_t offA, size_t ldA,
                                    size_t sxA, size_t syA,
                                    const void *host,
                                    cl_command_queue command_queue,
                                    cl_uint numEventsInWaitList,
                                    const cl_event *eventWaitList,
                                    cl_event *event)
{
  
  return clblasFillSubMatrixAsync( order,
                                   element_size,
                                   A, offA, ldA,
                                   sxA, syA,
                                   0, 0,
                                   sxA, syA,
                                   host,
                                   command_queue,
                                   numEventsInWaitList,
                                   eventWaitList,
                                   event) ;
  
}

