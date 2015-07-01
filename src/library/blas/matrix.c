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

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<clBLAS.h>

#define SWAP(TYPE,a,b)  do { TYPE swap_tmp_ = a ; a = b ; b = swap_tmp_ ; } while(0) 

// Return true if the area starting from pint (x,y) and of size (w,h) is 
// within the array of size d1 x d2
static int inside2d( size_t d1, size_t d2, int x, int y, size_t w, size_t h ) 
{
  // Very very large dimensions are likely a bug
  size_t MAXDIM = ((size_t)INT_MAX)  ;
  size_t max_w = (size_t)(d1-x) ;
  size_t max_h = (size_t)(d2-y) ;

  if ( d1 >= MAXDIM ) return 0 ; 
  if ( d2 >= MAXDIM ) return 0 ;
  if ( w  >= MAXDIM ) return 0 ; 
  if ( h  >= MAXDIM ) return 0 ;

  if ( x < 0 || x >= (int)d1 ) return 0 ;
  if ( w > max_w ) return 0 ;

  if ( y < 0 || y >= (int)d2 ) return 0 ;
  if ( h > max_h ) return 0 ;
       
  return 1 ;
}

clblasStatus clblasMatrixSizeInfo(clblasOrder order,
                                  size_t rows,
                                  size_t columns,
                                  size_t elemsize,
                                  size_t padding,
                                  size_t * ld,
                                  size_t * fullsize)
{
  size_t x;
  size_t y;

  if( order == clblasRowMajor )
  {
    x = columns;
    y = rows;
  }
  else 
  {
    x = rows;
    y = columns;
  }

  // set if not NULL
  if( ld ) *ld = x + padding;
  if( fullsize ) *fullsize = (size_t) ( (x + padding) * y * elemsize );

  return clblasSuccess; 
}


cl_mem clblasCreateMatrix(
    cl_context context,
    clblasOrder order,
    size_t rows,
    size_t columns,
    size_t elemsize,
    size_t padding,
    size_t * ld,
    size_t * fullsize,
    cl_int * err)
{
  size_t tmp_fullsize;
  cl_mem_flags flags = CL_MEM_READ_WRITE;

  clblasMatrixSizeInfo(
      order,
      rows,
      columns,
      elemsize,
      padding,
      ld,
      &tmp_fullsize);

  // set if not NULL
  if(fullsize != NULL) *fullsize = tmp_fullsize;

  return clCreateBuffer(
      context,
      flags,
      tmp_fullsize,
      NULL,
      err);
}

/*
 * Internal function: 
 *  see clblasCreateMatrix()
 */
cl_mem clblasCreateMatrixWithLd(
    cl_context context,
    clblasOrder order,
    size_t rows,
    size_t columns,
    size_t elemsize,
    size_t ld,
    size_t * fullsize,
    cl_int * err)
{
  int nbelem;
  cl_mem_flags flags = CL_MEM_READ_WRITE;

  // compute number of elements
  if( order == clblasRowMajor  )
  {
    // check ld
    if( ld < columns )
    {
      *err = clblasInvalidValue;
      return 0;
    }

    nbelem = rows * ld; 
  }
  else if( order == clblasColumnMajor )
  {
    // check ld
    if( ld < rows )
    {
      *err = clblasInvalidValue;
      return 0;
    }

    nbelem = ld * columns; 
  }

  // set if not NULL
  if( fullsize ) *fullsize = (size_t) (nbelem * elemsize );

  // allocate
  return clCreateBuffer(
      context,
      flags,
      *fullsize,
      NULL,
      err);
}


cl_mem clblasCreateMatrixFromHost(
    cl_context context, 
    clblasOrder order,
    size_t rows,
    size_t columns, 
    size_t elemsize,
    size_t ld,
    void * host,
    size_t off_host, 
    size_t ld_host,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,  
    cl_int * err)
{
  size_t fullsize;
  cl_mem out;
  size_t i;

  out = clblasCreateMatrixWithLd(
      context,
      order,
      rows,
      columns,
      elemsize,
      ld,
      &fullsize,
      err);

  if( ! *err )
  {
    printf("ok\n");
    // TODO use ReadMatrix instead ?
    if( order == clblasRowMajor )
    {
      for( i = 0; i < rows; i++ )
      {
        const size_t host_orig[3] = {off_host, off_host, 0};
        const size_t buff_orig[3] = {0, 0, 0};
        const size_t region[3] = {columns*elemsize, rows, 1};
        *err = clEnqueueWriteBufferRect(
            command_queue,
            out,
            CL_TRUE,
            buff_orig,
            host_orig,
            region,
            columns * elemsize,
            0,
            ld_host * elemsize,
            0,
            host,
            numEventsInWaitList,
            eventWaitList,
            NULL);
      }
    }
  }

  return out;
}

/*
 * Internal function: 
 *  enqueue event in list and wait for it if blocking
 */
static clblasStatus emptyAction(
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *event,
    cl_bool blocking)
{
  cl_int err ; 

  err = clEnqueueBarrierWithWaitList(
      command_queue, 
      numEventsInWaitList,
      eventWaitList, 
      event);

  if (err != clblasSuccess) 
    return  (clblasStatus)err;

  if(blocking) 
    return  (clblasStatus)clWaitForEvents(1, event);
  else 
    return (clblasStatus)err;
}

/*
 * Internal function:
 *  Generic version of clblasWriteSubMatrix with blocking arg
 *  event must be non-NULL if blocking is set to CL_TRUE
 */
static clblasStatus _clblasWriteSubMatrix(
    clblasOrder order,
    size_t element_size,
    const void *A, size_t offA, size_t ldA,
    size_t nrA, size_t ncA,
    size_t xA, size_t yA,
    cl_mem B, size_t offB, size_t ldB,
    size_t nrB, size_t ncB,
    size_t xB, size_t yB,
    size_t nx, size_t ny,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *event,
    cl_bool blocking)
{
  
  if( order == clblasRowMajor )
  {
    SWAP(size_t, xA, yA);
    SWAP(size_t, nrA, ncA);
    SWAP(size_t, xB, yB);
    SWAP(size_t, nrB, ncB);
    SWAP(size_t, nx, ny);
  }

  // Check that the specified area is within the array A
  if ( !inside2d( nrA,ncA, xA,yA , nx,ny ) ) {
    return clblasInvalidValue ;
  }

  // Check that the specified area is within the array B 
  if ( !inside2d( nrB,ncB, xB,yB , nx,ny ) ) {
    return clblasInvalidValue ;
  }


  if( nx == 0 || ny == 0 )
  { 
    return emptyAction(
        command_queue,
        numEventsInWaitList, 
        eventWaitList, 
        event,
        blocking);  
  } 

  {
    const size_t origA[3] = { (xA+offA)*element_size, yA, 0 };
    const size_t origB[3] = { (xB+offB)*element_size, yB, 0 };
    const size_t region[3] = { nx * element_size, ny, 1 };

    return (clblasStatus) clEnqueueWriteBufferRect(
        command_queue,
        B,
        blocking,
        origB,
        origA,
        region,
        ldB * element_size,
        0,
        ldA * element_size,
        0,
        A,
        numEventsInWaitList,
        eventWaitList,
        event);
  }
}

clblasStatus clblasWriteSubMatrix(
    clblasOrder order,
    size_t element_size,
    const void *A, size_t offA, size_t ldA,
    size_t nrA, size_t ncA,
    size_t xA, size_t yA,
    cl_mem B, size_t offB, size_t ldB,
    size_t nrB, size_t ncB,
    size_t xB, size_t yB,
    size_t nx, size_t ny,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList)
{
  cl_event evt;

  return _clblasWriteSubMatrix(
      order,
      element_size,
      A, offA, ldA,
      nrA, ncA,
      xA, yA,
      B, offB, ldB,
      nrB, ncB,
      xB, yB,
      nx, ny,
      command_queue,
      numEventsInWaitList,
      eventWaitList,
      &evt,
      CL_TRUE);
}

clblasStatus clblasWriteSubMatrixAsync(
    clblasOrder order,
    size_t element_size,
    const void *A, size_t offA, size_t ldA,
    size_t nrA, size_t ncA,
    size_t xA, size_t yA,
    cl_mem B, size_t offB, size_t ldB,
    size_t nrB, size_t ncB,
    size_t xB, size_t yB,
    size_t nx, size_t ny,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *event)
{
  return _clblasWriteSubMatrix(
      order,
      element_size,
      A, offA, ldA,
      nrA, ncA,
      xA, yA,
      B, offB, ldB,
      nrB, ncB,
      xB, yB,
      nx, ny,
      command_queue,
      numEventsInWaitList,
      eventWaitList,
      event,
      CL_FALSE);
}


/*
 * Internal function:
 *  Generic version of clblasReadSubMatrix with blocking arg
 *  event must be non-NULL if blocking is set to CL_TRUE
 */
static clblasStatus _clblasReadSubMatrix(
    clblasOrder order,
    size_t element_size,
    const cl_mem A, size_t offA, size_t ldA,
    size_t nrA, size_t ncA,
    size_t xA, size_t yA,
    void *B, size_t offB, size_t ldB,
    size_t nrB, size_t ncB,
    size_t xB, size_t yB,
    size_t nx, size_t ny,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *event,
    cl_bool blocking)
{

  if( order == clblasRowMajor )
  {
    SWAP(size_t, xA, yA);
    SWAP(size_t, nrA, ncA);
    SWAP(size_t, xB, yB);
    SWAP(size_t, nrB, ncB);
    SWAP(size_t, nx, ny);
  }

  if( nx == 0 || ny == 0 )
  { 
    return emptyAction(
        command_queue,
        numEventsInWaitList, 
        eventWaitList, 
        event,
        blocking);  
  } 

  // Check that the specified area is within the array A
  if ( !inside2d( nrA,ncA, xA,yA , nx,ny ) ) {
    return clblasInvalidValue ;
  }

  // Check that the specified area is within the array B 
  if ( !inside2d( nrB,ncB, xB,yB , nx,ny ) ) {
    return clblasInvalidValue ;
  }

  {
    const size_t origA[3] = { (xA+offA)*element_size, yA, 0 };
    const size_t origB[3] = { (xB+offB)*element_size, yB, 0 };
    const size_t region[3] = { nx * element_size, ny, 1 };

    return (clblasStatus) clEnqueueReadBufferRect(
        command_queue,
        A,
        blocking,
        origA,
        origB,
        region,
        ldA * element_size,
        0,
        ldB * element_size,
        0,
        B,
        numEventsInWaitList,
        eventWaitList,
        event);
  }
}


clblasStatus clblasReadSubMatrix(
    clblasOrder order,
    size_t element_size,
    const cl_mem A, size_t offA, size_t ldA,
    size_t nrA, size_t ncA,
    size_t xA, size_t yA,
    void *B, size_t offB, size_t ldB,
    size_t nrB, size_t ncB,
    size_t xB, size_t yB,
    size_t nx, size_t ny,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList)
{
  cl_event evt;

  return _clblasReadSubMatrix(
      order,
      element_size,
      A, offA, ldA,
      nrA, ncA,
      xA, yA,
      B, offB, ldB,
      nrB, ncB,
      xB, yB,
      nx, ny,
      command_queue,
      numEventsInWaitList,
      eventWaitList,
      &evt,
      CL_TRUE);
}


clblasStatus clblasReadSubMatrixAsync(
    clblasOrder order,
    size_t element_size,
    const cl_mem A, size_t offA, size_t ldA,
    size_t nrA, size_t ncA,
    size_t xA, size_t yA,
    void *B, size_t offB, size_t ldB,
    size_t nrB, size_t ncB,
    size_t xB, size_t yB,
    size_t nx, size_t ny,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *event)
{
  return _clblasReadSubMatrix(
      order,
      element_size,
      A, offA, ldA,
      nrA, ncA,
      xA, yA,
      B, offB, ldB,
      nrB, ncB,
      xB, yB,
      nx, ny,
      command_queue,
      numEventsInWaitList,
      eventWaitList,
      event,
      CL_TRUE);
}


/*
 * Internal function:
 *  Generic version of clblasCopySubMatrix with blocking arg
 *  event must be non-NULL if blocking is set to CL_TRUE
 */
static clblasStatus _clblasCopySubMatrix(
    clblasOrder order,
    size_t element_size,
    const cl_mem A, size_t offA, size_t ldA,
    size_t nrA, size_t ncA,
    size_t xA, size_t yA,
    cl_mem B, size_t offB, size_t ldB,
    size_t nrB, size_t ncB,
    size_t xB, size_t yB,
    size_t nx, size_t ny,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *event,
    cl_bool blocking)
{
  cl_int err;
  if( order == clblasRowMajor )
  {
    SWAP(size_t, xA, yA);
    SWAP(size_t, nrA, ncA);
    SWAP(size_t, xB, yB);
    SWAP(size_t, nrB, ncB);
    SWAP(size_t, nx, ny);
  }

  if( nx == 0 || ny == 0 )
  { 
    return emptyAction(
        command_queue,
        numEventsInWaitList, 
        eventWaitList, 
        event,
        CL_FALSE);  
  } 

  // Check that the specified area is within the array A
  if ( !inside2d( nrA,ncA, xA,yA , nx,ny ) ) {
    return clblasInvalidValue ;
  }

  // Check that the specified area is within the array B 
  if ( !inside2d( nrB,ncB, xB,yB , nx,ny ) ) {
    return clblasInvalidValue ;
  }

  {
    const size_t origA[3] = { (xA+offA)*element_size, yA, 0 };
    const size_t origB[3] = { (xB+offB)*element_size, yB, 0 };
    const size_t region[3] = { nx * element_size, ny, 1 };

    err = clEnqueueCopyBufferRect(
                                  command_queue,
                                  A,
                                  B,
                                  origA,
                                  origB,
                                  region,
                                  ldA * element_size,
                                  0,
                                  ldB * element_size,
                                  0,
                                  numEventsInWaitList,
                                  eventWaitList,
                                  event);
  }

  if (err != clblasSuccess) 
    return  (clblasStatus)err;

  if(blocking) 
    return  (clblasStatus)clWaitForEvents(1, event);
  else 
    return (clblasStatus)err;
}


clblasStatus clblasCopySubMatrix(
    clblasOrder order,
    size_t element_size,
    const cl_mem A, size_t offA, size_t ldA,
    size_t nrA, size_t ncA,
    size_t xA, size_t yA,
    cl_mem B, size_t offB, size_t ldB,
    size_t nrB, size_t ncB,
    size_t xB, size_t yB,
    size_t nx, size_t ny,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList)
{
  cl_event evt;

  return (clblasStatus) _clblasCopySubMatrix(
      order,
      element_size,
      A, offA, ldA,
      nrA, ncA,
      xA, yA,
      B, offB, ldB,
      nrB, ncB,
      xB, yB,
      nx, ny,
      command_queue,
      numEventsInWaitList,
      eventWaitList,
      &evt,      
      CL_TRUE);
}


clblasStatus clblasCopySubMatrixAsync(
    clblasOrder order,
    size_t element_size,
    const cl_mem A, size_t offA, size_t ldA,
    size_t nrA, size_t ncA,
    size_t xA, size_t yA,
    cl_mem B, size_t offB, size_t ldB,
    size_t nrB, size_t ncB,
    size_t xB, size_t yB,
    size_t nx, size_t ny,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *event)
{
  return (clblasStatus) _clblasCopySubMatrix(
      order,
      element_size,
      A, offA, ldA,
      nrA, ncA,
      xA, yA,
      B, offB, ldB,
      nrB, ncB,
      xB, yB,
      nx, ny,
      command_queue,
      numEventsInWaitList,
      eventWaitList,
      event,
      CL_FALSE);
}


clblasStatus clblasWriteVector(
    size_t nb_elem,
    size_t element_size,
    const void *A, size_t offA,
    cl_mem B, size_t offB,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList)
{
  return clblasWriteMatrix(
      clblasColumnMajor,
      nb_elem, 1,
      element_size,
      A, offA, nb_elem,
      B, offB, nb_elem,
      command_queue,
      numEventsInWaitList,
      eventWaitList);
}


clblasStatus clblasWriteVectorAsync(
    size_t nb_elem,
    size_t element_size,
    const void *A, size_t offA,
    cl_mem B, size_t offB,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
  return clblasWriteMatrixAsync(
      clblasColumnMajor,
      nb_elem, 1,
      element_size,
      A, offA, nb_elem,
      B, offB, nb_elem,
      command_queue,
      numEventsInWaitList,
      eventWaitList,
      events);
}


clblasStatus clblasReadVector(
    size_t nb_elem,
    size_t element_size,
    const cl_mem A, size_t offA,
    void * B, size_t offB,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList)
{
  return clblasReadMatrix(
      clblasColumnMajor,
      nb_elem, 1,
      element_size,
      A, offA, nb_elem,
      B, offB, nb_elem,
      command_queue,
      numEventsInWaitList,
      eventWaitList);
}


clblasStatus clblasReadVectorAsync(
    size_t nb_elem,
    size_t element_size,
    const cl_mem A, size_t offA,
    void * B, size_t offB,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
  return clblasReadMatrixAsync(
      clblasColumnMajor,
      nb_elem, 1,
      element_size,
      A, offA, nb_elem,
      B, offB, nb_elem,
      command_queue,
      numEventsInWaitList,
      eventWaitList,
      events);
}


clblasStatus clblasCopyVector(
    size_t nb_elem,
    size_t element_size,
    const cl_mem A, size_t offA,
    cl_mem B, size_t offB,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList)
{
  return clblasCopyMatrix(
      clblasColumnMajor,
      nb_elem, 1,
      element_size,
      A, offA, nb_elem,
      B, offB, nb_elem,
      command_queue,
      numEventsInWaitList,
      eventWaitList);
}


clblasStatus clblasCopyVectorAsync(
    size_t nb_elem,
    size_t element_size,
    const cl_mem A, size_t offA,
    cl_mem B, size_t offB,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
  return clblasCopyMatrixAsync(
      clblasColumnMajor,
      nb_elem, 1,
      element_size,
      A, offA, nb_elem,
      B, offB, nb_elem,
      command_queue,
      numEventsInWaitList,
      eventWaitList,
      events);
}


clblasStatus clblasWriteMatrix(
    clblasOrder order,
    size_t sx, size_t sy,
    size_t element_size,
    const void *A, size_t offA, size_t ldA,
    cl_mem B, size_t offB, size_t ldB,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList)
{
  return clblasWriteSubMatrix(
      order,
      element_size,
      A, offA, ldA,
      sx, sy,
      0, 0,
      B, offB, ldB,
      sx, sy,
      0, 0,
      sx, sy,
      command_queue,
      numEventsInWaitList,
      eventWaitList);		
}


clblasStatus clblasWriteMatrixAsync(
    clblasOrder order,
    size_t sx, size_t sy,
    size_t element_size,
    const void *A, size_t offA, size_t ldA,
    cl_mem B, size_t offB, size_t ldB,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
  return clblasWriteSubMatrixAsync(
      order,
      element_size,
      A, offA, ldA,
      sx, sy,
      0, 0,
      B, offB, ldB,
      sx, sy,
      0, 0,
      sx, sy,
      command_queue,
      numEventsInWaitList,
      eventWaitList,
      events);	
}


clblasStatus clblasReadMatrix(
    clblasOrder order,
    size_t sx, size_t sy,
    size_t element_size,
    const cl_mem A, size_t offA, size_t ldA,
    void * B, size_t offB, size_t ldB,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList)
{
  return clblasReadSubMatrix(
      order,
      element_size,
      A, offA, ldA,
      sx, sy,
      0, 0,
      B, offB, ldB,
      sx, sy,
      0, 0,
      sx, sy,
      command_queue,
      numEventsInWaitList,
      eventWaitList);
}


clblasStatus clblasReadMatrixAsync(
    clblasOrder order,
    size_t sx, size_t sy,
    size_t element_size,
    const cl_mem A, size_t offA, size_t ldA,
    void * B, size_t offB, size_t ldB,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
  return clblasReadSubMatrixAsync(
      order,
      element_size,
      A, offA, ldA,
      sx, sy,
      0, 0,
      B, offB, ldB,
      sx, sy,
      0, 0,
      sx, sy,
      command_queue,
      numEventsInWaitList,
      eventWaitList,
      events);
}


clblasStatus clblasCopyMatrix(
    clblasOrder order,
    size_t sx, size_t sy,
    size_t element_size,
    const cl_mem A, size_t offA, size_t ldA,
    cl_mem B, size_t offB, size_t ldB,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList)
{
  return clblasCopySubMatrix(
      order,
      element_size,
      A, offA, ldA,
      sx, sy,
      0, 0,
      B, offB, ldB,
      sx, sy,
      0, 0,
      sx, sy,
      command_queue,
      numEventsInWaitList,
      eventWaitList);
}


clblasStatus clblasCopyMatrixAsync(
    clblasOrder order,
    size_t sx, size_t sy,
    size_t element_size,
    const cl_mem A, size_t offA, size_t ldA,
    cl_mem B, size_t offB, size_t ldB,
    cl_command_queue command_queue,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
  return clblasCopySubMatrixAsync(
      order,
      element_size,
      A, offA, ldA,
      sx, sy,
      0, 0,
      B, offB, ldB,
      sx, sy,
      0, 0,
      sx, sy,
      command_queue,
      numEventsInWaitList,
      eventWaitList,
      events);
}

