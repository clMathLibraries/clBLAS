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

#include <devinfo.h>
#include "clblas-internal.h"
#include "solution_seq.h"

#include <functor_xscal.h>

static clblasStatus
doScal(
       CLBlasKargs *kargs,
       size_t N,
       cl_mem X,
       size_t offx,
       int incx,
       cl_uint numCommandQueues,
       cl_command_queue *commandQueues,
       cl_uint numEventsInWaitList,
       const cl_event *eventWaitList,
       cl_event *events)
{
  cl_int err;
  ListHead seq;
  clblasStatus retCode = clblasSuccess;

  if (!clblasInitialized) {
    return clblasNotInitialized;
  }

  /* Validate arguments */

  retCode = checkMemObjects(X, X, X, false, X_VEC_ERRSET, X_VEC_ERRSET, X_VEC_ERRSET );
  if (retCode) {
    printf("Invalid mem object..\n");
    return retCode;
  }

  // Check wheather enough memory was allocated

  if ((retCode = checkVectorSizes(kargs->dtype, N, X, offx, incx, X_VEC_ERRSET))) {
    printf("Invalid Size for X\n");
    return retCode;
  }
  ///////////////////////////////////////////////////////////////

  if ((commandQueues == NULL) || (numCommandQueues == 0))
    {
      return clblasInvalidValue;
    }

  /* numCommandQueues will be hardcoded to 1 as of now. No multi-gpu support */
  numCommandQueues = 1;
  if (commandQueues[0] == NULL)
    {
      return clblasInvalidCommandQueue;
    }

  if ((numEventsInWaitList !=0) && (eventWaitList == NULL))
    {
      return clblasInvalidEventWaitList;
    }

  kargs->N = N;
  kargs->A = X;
  kargs->offBX = offx;
  kargs->ldb.Vector = incx;	// Will be using this as incx

  if(incx < 0) {    // According to Netlib - return for negative incx
    return clblasSuccess;
  }

  listInitHead(&seq);
  err = makeSolutionSeq(CLBLAS_SCAL, kargs, numCommandQueues, commandQueues,
                        numEventsInWaitList, eventWaitList, events, &seq);
  if (err == CL_SUCCESS) {
    err = executeSolutionSeq(&seq);
  }

  freeSolutionSeq(&seq);

  return (clblasStatus)err;
}


// =================================================================================
//
// class clblasSscalFunctorFallback
//
// =================================================================================

static clblasSscalFunctorFallback sscal_fallback;

clblasStatus clblasSscalFunctorFallback::execute(Args & args)
{
  CLBlasKargs kargs;
  memset(&kargs, 0, sizeof(kargs));
  kargs.dtype = TYPE_FLOAT;
  kargs.alpha.argFloat = args.alpha;

  return doScal(&kargs,
                args.N,
                args.X,
                args.offx,
                args.incx,
                1,
                &args.queue,
                args.numEventsInWaitList,
                args.eventWaitList,
                args.events);

}


clblasSscalFunctorFallback * clblasSscalFunctorFallback::provide ()
{
    static clblasSscalFunctorFallback sscal_fallback;
    return & sscal_fallback;
}


void clblasSscalFunctorFallback::retain()
{
  // clblasSscalFunctorFallback has a single global instance
  // and shall never be freed
}


void clblasSscalFunctorFallback::release()
{
  // clblasDscalFunctorFallback has a single global instance
  // and shall never be freed
}




// =================================================================================
//
// class clblasDscalFunctorFallback
//
// =================================================================================

static clblasDscalFunctorFallback dscal_fallback;

clblasStatus clblasDscalFunctorFallback::execute(Args & args)
{
  CLBlasKargs kargs;
  memset(&kargs, 0, sizeof(kargs));
  kargs.dtype = TYPE_DOUBLE;
  kargs.alpha.argDouble = args.alpha;

  return doScal(&kargs,
                args.N,
                args.X,
                args.offx,
                args.incx,
                1,
                &args.queue,
                args.numEventsInWaitList,
                args.eventWaitList,
                args.events);

}


clblasDscalFunctorFallback * clblasDscalFunctorFallback::provide ()
{
    static clblasDscalFunctorFallback dscal_fallback;
    return & dscal_fallback;
}


void clblasDscalFunctorFallback::retain()
{
  // clblasDscalFunctorFallback has a single global instance
  // and shall never be freed
}


void clblasDscalFunctorFallback::release()
{
  // clblasDscalFunctorFallback has a single global instance
  // and shall never be freed
}


// =================================================================================
//
// class clblasCscalFunctorFallback
//
// =================================================================================

static clblasCscalFunctorFallback cscal_fallback;

clblasStatus clblasCscalFunctorFallback::execute(Args & args)
{
  CLBlasKargs kargs;
  memset(&kargs, 0, sizeof(kargs));
  kargs.dtype = TYPE_COMPLEX_FLOAT;
  kargs.alpha.argFloatComplex = args.alpha;

  return doScal(&kargs,
                args.N,
                args.X,
                args.offx,
                args.incx,
                1,
                &args.queue,
                args.numEventsInWaitList,
                args.eventWaitList,
                args.events);

}


clblasCscalFunctorFallback * clblasCscalFunctorFallback::provide ()
{
    static clblasCscalFunctorFallback cscal_fallback;
    return & cscal_fallback;
}


void clblasCscalFunctorFallback::retain()
{
  // clblasCscalFunctorFallback has a single global instance
  // and shall never be freed
}


void clblasCscalFunctorFallback::release()
{
  // clblasCscalFunctorFallback has a single global instance
  // and shall never be freed
}


// =================================================================================
//
// class clblasZscalFunctorFallback
//
// =================================================================================

static clblasZscalFunctorFallback zscal_fallback;

clblasStatus clblasZscalFunctorFallback::execute(Args & args)
{
  CLBlasKargs kargs;
  memset(&kargs, 0, sizeof(kargs));
  kargs.dtype = TYPE_COMPLEX_DOUBLE;
  kargs.alpha.argDoubleComplex = args.alpha;

  return doScal(&kargs,
                args.N,
                args.X,
                args.offx,
                args.incx,
                1,
                &args.queue,
                args.numEventsInWaitList,
                args.eventWaitList,
                args.events);

}


clblasZscalFunctorFallback * clblasZscalFunctorFallback::provide ()
{
    static clblasZscalFunctorFallback zscal_fallback;
    return & zscal_fallback;
}


void clblasZscalFunctorFallback::retain()
{
  // clblasZscalFunctorFallback has a single global instance
  // and shall never be freed
}


void clblasZscalFunctorFallback::release()
{
  // clblasZscalFunctorFallback has a single global instance
  // and shall never be freed
}


// =================================================================================
//
// class clblasCsscalFunctorFallback
//
// =================================================================================

static clblasCsscalFunctorFallback csscal_fallback;

clblasStatus clblasCsscalFunctorFallback::execute(Args & args)
{
  CLBlasKargs kargs;
  FloatComplex fAlpha;
  CREAL(fAlpha) = args.alpha;
  CIMAG(fAlpha) = 0.0f;

  memset(&kargs, 0, sizeof(kargs));
  kargs.alpha.argFloatComplex = fAlpha;
  kargs.dtype = TYPE_COMPLEX_FLOAT;

  return doScal(&kargs,
                args.N,
                args.X,
                args.offx,
                args.incx,
                1,
                &args.queue,
                args.numEventsInWaitList,
                args.eventWaitList,
                args.events);

}


clblasCsscalFunctorFallback * clblasCsscalFunctorFallback::provide ()
{
    static clblasCsscalFunctorFallback csscal_fallback;
    return & csscal_fallback;
}


void clblasCsscalFunctorFallback::retain()
{
  // clblasCsscalFunctorFallback has a single global instance
  // and shall never be freed
}


void clblasCsscalFunctorFallback::release()
{
  // clblasCsscalFunctorFallback has a single global instance
  // and shall never be freed
}


// =================================================================================
//
// class clblasZdscalFunctorFallback
//
// =================================================================================

static clblasZdscalFunctorFallback zdscal_fallback;

clblasStatus clblasZdscalFunctorFallback::execute(Args & args)
{
  CLBlasKargs kargs;
  DoubleComplex fAlpha;
  CREAL(fAlpha) = args.alpha;
  CIMAG(fAlpha) = 0.0f;

  memset(&kargs, 0, sizeof(kargs));
  kargs.alpha.argDoubleComplex = fAlpha;
  kargs.dtype = TYPE_COMPLEX_DOUBLE;

  return doScal(&kargs,
                args.N,
                args.X,
                args.offx,
                args.incx,
                1,
                &args.queue,
                args.numEventsInWaitList,
                args.eventWaitList,
                args.events);

}


clblasZdscalFunctorFallback * clblasZdscalFunctorFallback::provide ()
{
    static clblasZdscalFunctorFallback zdscal_fallback;
    return & zdscal_fallback;
}


void clblasZdscalFunctorFallback::retain()
{
  // clblasZdscalFunctorFallback has a single global instance
  // and shall never be freed
}


void clblasZdscalFunctorFallback::release()
{
  // clblasZdscalFunctorFallback has a single global instance
  // and shall never be freed
}
