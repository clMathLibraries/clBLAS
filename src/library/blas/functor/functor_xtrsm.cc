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

#include <devinfo.h>
#include "clblas-internal.h"
#include "solution_seq.h"

#include <functor_xtrsm.h>

//
// Common part of all XTRSM implementations using the old Solver infrastructure 
//
static clblasStatus
doTrsm(
    CLBlasKargs *kargs,
    clblasOrder order,
    clblasSide side,
    clblasUplo uplo,
    clblasTranspose transA,
    clblasDiag diag,
    size_t M,
    size_t N,
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
    cl_int err;
    ListHead seq;
    size_t msize;
    clblasStatus retCode = clblasSuccess;

    if (!clblasInitialized) {
        return clblasNotInitialized;
    }

    /* Validate arguments */

    if ((retCode = checkMemObjects(A, B, NULL, false, A_MAT_ERRSET, B_MAT_ERRSET, END_ERRSET ))) {
        return retCode;
    }
    msize = (side == clblasLeft) ? M : N;

    if ((retCode = checkMatrixSizes(kargs->dtype, order, transA, msize, msize,
                                    A, offA, lda, A_MAT_ERRSET ))) {
        return retCode;
    }
    if ((retCode = checkMatrixSizes(kargs->dtype, order, clblasNoTrans, M, N,
                                    B, offB, ldb, B_MAT_ERRSET ))) {
        return retCode;
    }

    kargs->order = order;
    kargs->side = side;
    kargs->uplo = uplo;
    kargs->transA = transA;
    kargs->diag = diag;
    kargs->M = M;
    kargs->N = N;
    kargs->A = A;
    kargs->offA = offA;
    kargs->lda.matrix = lda;
    kargs->B = B;
    kargs->offBX = offB;
    kargs->ldb.matrix = ldb;
    // Store original problem size in K, this is used to know it while
    // calculating result by parts using M or N as part size
    if (side == clblasLeft) {
        kargs->K = M;
    }
    else {
        kargs->K = N;
    }

    kargs->offsetM = 0;
    kargs->offsetN = 0;
    kargs->scimage[0] = 0;

#ifndef TRXM_MULTIPLE_QUEUES
    if (numCommandQueues != 0) {
        numCommandQueues = 1;
    }
#endif

    listInitHead(&seq);
    err = makeSolutionSeq(CLBLAS_TRSM, kargs, numCommandQueues, commandQueues,
        numEventsInWaitList, eventWaitList, events, &seq);
    if (err == CL_SUCCESS) {
        err = executeSolutionSeq(&seq);
    }

    freeSolutionSeq(&seq);

    return (clblasStatus)err;
}



// =================================================================================
//
// class clblasStrsmFunctorFallback
//
// =================================================================================

clblasStatus 
clblasStrsmFunctorFallback::execute(Args & args)
{
  CLBlasKargs kargs;

  memset(&kargs, 0, sizeof(kargs));
  kargs.dtype = TYPE_FLOAT;
  kargs.alpha.argFloat = args.alpha;
  
  return doTrsm(&kargs, 
                args.order, 
                args.side, 
                args.uplo, 
                args.transA, 
                args.diag, 
                args.M, args.N, 
                args.A, args.offA, args.lda,
                args.B, args.offB, args.ldb, 
                1, &args.queue,
                args.numEventsInWaitList, 
                args.eventWaitList, 
                args.events);

}

clblasStrsmFunctorFallback * 
clblasStrsmFunctorFallback::provide ()
{
    static clblasStrsmFunctorFallback strsm_fallback; // The unique instance of clblasStrsmFunctorFallback
    return & strsm_fallback;
}


void 
clblasStrsmFunctorFallback::retain()
{
  // clblasStrsmFunctorFallback has a single global instance 
  // and shall never be freed 
}

void 
clblasStrsmFunctorFallback::release()
{
  // clblasStrsmFunctorFallback has a single global instance 
  // and shall never be freed
}


// =================================================================================
//
// class clblasDtrsmFunctorFallback
//
// =================================================================================

clblasStatus 
clblasDtrsmFunctorFallback::execute(Args & args)
{
  CLBlasKargs kargs;

  memset(&kargs, 0, sizeof(kargs));
  kargs.dtype = TYPE_DOUBLE;
  kargs.alpha.argDouble = args.alpha;
  
  return doTrsm(&kargs, 
                args.order, 
                args.side, 
                args.uplo, 
                args.transA, 
                args.diag, 
                args.M, args.N, 
                args.A, args.offA, args.lda,
                args.B, args.offB, args.ldb, 
                1, &args.queue,
                args.numEventsInWaitList, 
                args.eventWaitList, 
                args.events);

}

clblasDtrsmFunctorFallback * 
clblasDtrsmFunctorFallback::provide ()
{
    static clblasDtrsmFunctorFallback dtrsm_fallback; // The unique instance of clblasDtrsmFunctorFallback
    return & dtrsm_fallback;
}


void 
clblasDtrsmFunctorFallback::retain()
{
  // clblasDtrsmFunctorFallback has a single global instance 
  // and shall never be freed 
}

void 
clblasDtrsmFunctorFallback::release()
{
  // clblasDtrsmFunctorFallback has a single global instance 
  // and shall never be freed
}


// =================================================================================
//
// class clblasCtrsmFunctorFallback
//
// =================================================================================

clblasStatus 
clblasCtrsmFunctorFallback::execute(Args & args)
{
  CLBlasKargs kargs;

  memset(&kargs, 0, sizeof(kargs));
  kargs.dtype = TYPE_COMPLEX_FLOAT;
  kargs.alpha.argFloatComplex = args.alpha;
  
  return doTrsm(&kargs, 
                args.order, 
                args.side, 
                args.uplo, 
                args.transA, 
                args.diag, 
                args.M, args.N, 
                args.A, args.offA, args.lda,
                args.B, args.offB, args.ldb, 
                1, &args.queue,
                args.numEventsInWaitList, 
                args.eventWaitList, 
                args.events);

}

clblasCtrsmFunctorFallback * 
clblasCtrsmFunctorFallback::provide ()
{
    static clblasCtrsmFunctorFallback ctrsm_fallback; // The unique instance of clblasCtrsmFunctorFallback
    return & ctrsm_fallback;
}


void 
clblasCtrsmFunctorFallback::retain()
{
  // clblasCtrsmFunctorFallback has a single global instance 
  // and shall never be freed 
}

void 
clblasCtrsmFunctorFallback::release()
{
  // clblasCtrsmFunctorFallback has a single global instance 
  // and shall never be freed
}


// =================================================================================
//
// class clblasZtrsmFunctorFallback
//
// =================================================================================

clblasStatus 
clblasZtrsmFunctorFallback::execute(Args & args)
{
  CLBlasKargs kargs;

  memset(&kargs, 0, sizeof(kargs));
  kargs.dtype = TYPE_COMPLEX_DOUBLE;
  kargs.alpha.argDoubleComplex = args.alpha;
  
  return doTrsm(&kargs, 
                args.order, 
                args.side, 
                args.uplo, 
                args.transA, 
                args.diag, 
                args.M, args.N, 
                args.A, args.offA, args.lda,
                args.B, args.offB, args.ldb, 
                1, &args.queue,
                args.numEventsInWaitList, 
                args.eventWaitList, 
                args.events);

}

clblasZtrsmFunctorFallback * 
clblasZtrsmFunctorFallback::provide ()
{
    static clblasZtrsmFunctorFallback ztrsm_fallback; // The unique instance of clblasZtrsmFunctorFallback
    return & ztrsm_fallback;
}


void 
clblasZtrsmFunctorFallback::retain()
{
  // clblasZtrsmFunctorFallback has a single global instance 
  // and shall never be freed 
}

void 
clblasZtrsmFunctorFallback::release()
{
  // clblasZtrsmFunctorFallback has a single global instance 
  // and shall never be freed
}
