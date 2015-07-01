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

#include <functor_xgemm.h>

//
// Common part of all XGEMM implementations using the old Solver infrastructure 
//
static clblasStatus
doGemm(
    CLBlasKargs *kargs,
    clblasOrder order,
    clblasTranspose transA,
    clblasTranspose transB,
    size_t M,
    size_t N,
    size_t K,
    const cl_mem A,
    size_t offA,
    size_t lda,
    const cl_mem B,
    size_t offB,
    size_t ldb,
    cl_mem C,
    size_t offC,
    size_t ldc,
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

    if ((retCode = checkMemObjects(A, B, C, true, A_MAT_ERRSET, B_MAT_ERRSET, C_MAT_ERRSET))) {
        return retCode;
    }
    if (K != 0) {
        if ((retCode = checkMatrixSizes(kargs->dtype, order, transA, M,
                                        K, A, offA, lda, A_MAT_ERRSET ))) {
            return retCode;
        }
        if ((retCode = checkMatrixSizes(kargs->dtype, order, transB,
                                        K, N, B, offB, ldb, B_MAT_ERRSET ))) {
            return retCode;
        }
    }
    if ((retCode = checkMatrixSizes(kargs->dtype, order, clblasNoTrans,
                                    M, N, C, offC, ldc, C_MAT_ERRSET ))) {
            return retCode;
    }

	#ifdef DEBUG_2
	printf("DoGemm being called...\n");
	#endif
    kargs->order = order;
    kargs->transA = transA;
    kargs->transB = transB;
    kargs->M = M;
    kargs->N = N;
    kargs->K = K;
    kargs->A = A;
    kargs->offA = offA;
    kargs->lda.matrix = lda;
    kargs->B = B;
    kargs->offBX = offB;
    kargs->ldb.matrix = ldb;
    kargs->C = C;
    kargs->offCY = offC;
    kargs->ldc.matrix = ldc;

    kargs->offsetM = 0;
    kargs->offsetN = 0;
    kargs->scimage[0] = 0;
    kargs->scimage[1] = 0;

    listInitHead(&seq);
    err = makeSolutionSeq(CLBLAS_GEMM, kargs, numCommandQueues, commandQueues,
        numEventsInWaitList, eventWaitList, events, &seq);
    if (err == CL_SUCCESS) {
        err = executeSolutionSeq(&seq);
    }

    freeSolutionSeq(&seq);

    return (clblasStatus)err;
}



// =================================================================================
//
// class clblasSgemmFunctorFallback
//
// =================================================================================

clblasStatus 
clblasSgemmFunctorFallback::execute(Args & args)
{
  CLBlasKargs kargs;

  memset(&kargs, 0, sizeof(kargs));
  kargs.dtype = TYPE_FLOAT;
  kargs.alpha.argFloat = args.alpha;
  kargs.beta.argFloat  = args.beta;
  
  return doGemm(&kargs, 
                args.order, 
                args.transA, args.transB, 
                args.M, args.N, args.K, 
                args.A, args.offA, args.lda,
                args.B, args.offB, args.ldb, 
                args.C, args.offC, args.ldc, 
                1, &args.queue,
                args.numEventsInWaitList, 
                args.eventWaitList, 
                args.events);
}

clblasSgemmFunctorFallback * 
clblasSgemmFunctorFallback::provide ()
{
    static clblasSgemmFunctorFallback sgemm_fallback; // The unique instance of clblasSgemmFunctorFallback
    return & sgemm_fallback;
}


void 
clblasSgemmFunctorFallback::retain()
{
  // clblasSgemmFunctorFallback has a single global instance 
  // and shall never be freed 
}

void 
clblasSgemmFunctorFallback::release()
{
  // clblasSgemmFunctorFallback has a single global instance 
  // and shall never be freed
}


// =================================================================================
//
// class clblasDgemmFunctorFallback
//
// =================================================================================

clblasStatus 
clblasDgemmFunctorFallback::execute(Args & args)
{
  CLBlasKargs kargs;

  memset(&kargs, 0, sizeof(kargs));
  kargs.dtype = TYPE_DOUBLE;
  kargs.alpha.argDouble = args.alpha;
  kargs.beta.argDouble  = args.beta;
  
  return doGemm(&kargs, 
                args.order, 
                args.transA, args.transB, 
                args.M, args.N, args.K, 
                args.A, args.offA, args.lda,
                args.B, args.offB, args.ldb, 
                args.C, args.offC, args.ldc, 
                1, &args.queue,
                args.numEventsInWaitList, 
                args.eventWaitList, 
                args.events);
}

clblasDgemmFunctorFallback * 
clblasDgemmFunctorFallback::provide ()
{
  static clblasDgemmFunctorFallback dgemm_fallback;   // The unique instance of clblasDgemmFunctorFallback
  return & dgemm_fallback;
}


void 
clblasDgemmFunctorFallback::retain()
{
  // clblasDgemmFunctorFallback has a single global instance 
  // and shall never be freed 
}

void 
clblasDgemmFunctorFallback::release()
{
  // clblasDgemmFunctorFallback has a single global instance 
  // and shall never be freed
}

// =================================================================================
//
// class clblasCgemmFunctorFallback
//
// =================================================================================

clblasStatus 
clblasCgemmFunctorFallback::execute(Args & args)
{
  CLBlasKargs kargs;

  memset(&kargs, 0, sizeof(kargs));
  kargs.dtype = TYPE_COMPLEX_FLOAT;
  kargs.alpha.argFloatComplex = args.alpha;
  kargs.beta.argFloatComplex  = args.beta;
  
  return doGemm(&kargs, 
                args.order, 
                args.transA, args.transB, 
                args.M, args.N, args.K, 
                args.A, args.offA, args.lda,
                args.B, args.offB, args.ldb, 
                args.C, args.offC, args.ldc, 
                1, &args.queue,
                args.numEventsInWaitList, 
                args.eventWaitList, 
                args.events);
}

clblasCgemmFunctorFallback * 
clblasCgemmFunctorFallback::provide ()
{
  static clblasCgemmFunctorFallback cgemm_fallback;   // The unique instance of clblasCgemmFunctorFallback
  return & cgemm_fallback;
}


void 
clblasCgemmFunctorFallback::retain()
{
  // clblasCgemmFunctorFallback has a single global instance 
  // and shall never be freed 
}

void 
clblasCgemmFunctorFallback::release()
{
  // clblasCgemmFunctorFallback has a single global instance 
  // and shall never be freed
}

// =================================================================================
//
// class clblasZgemmFunctorFallback
//
// =================================================================================

clblasStatus 
clblasZgemmFunctorFallback::execute(Args & args)
{
  CLBlasKargs kargs;

  memset(&kargs, 0, sizeof(kargs));
  kargs.dtype = TYPE_COMPLEX_DOUBLE;
  kargs.alpha.argDoubleComplex = args.alpha;
  kargs.beta.argDoubleComplex  = args.beta;
  
  return doGemm(&kargs, 
                args.order, 
                args.transA, args.transB, 
                args.M, args.N, args.K, 
                args.A, args.offA, args.lda,
                args.B, args.offB, args.ldb, 
                args.C, args.offC, args.ldc, 
                1, &args.queue,
                args.numEventsInWaitList, 
                args.eventWaitList, 
                args.events);
}

clblasZgemmFunctorFallback * 
clblasZgemmFunctorFallback::provide ()
{
  static clblasZgemmFunctorFallback cgemm_fallback;   // The unique instance of clblasZgemmFunctorFallback
  return & cgemm_fallback;
}


void 
clblasZgemmFunctorFallback::retain()
{
  // clblasZgemmFunctorFallback has a single global instance 
  // and shall never be freed 
}

void 
clblasZgemmFunctorFallback::release()
{
  // clblasZgemmFunctorFallback has a single global instance 
  // and shall never be freed
}
