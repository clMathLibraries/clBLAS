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


#include <stdlib.h>             // srand()
#include <string.h>             // memcpy()
#include <gtest/gtest.h>
#include <clBLAS.h>

#include <common.h>
#include <blas-internal.h>
#include <blas-wrapper.h>
#include <clBLAS-wrapper.h>
#include <BlasBase.h>
#include <blas-random.h>
#include <gemm.h>

#include "tcase-filter.h"

static void
releaseMemObjects(cl_mem objA, cl_mem objB, cl_mem objC)
{
    clReleaseMemObject(objA);
    clReleaseMemObject(objB);
    clReleaseMemObject(objC);
}

template <typename T> static void
deleteBuffers(T *A, T *B, T *blasC, T *clblasC)
{
    delete[] A;
    delete[] B;
    delete[] blasC;
    delete[] clblasC;
}

template <typename T>
void
gemmCorrectnessTest(TestParams *params)
{
    cl_int err;
    T *A, *B, *blasC, *clblasC;
    T alpha, beta;
    cl_mem bufA, bufB, bufC;
    clMath::BlasBase *base;
    bool useAlpha;
    bool useBeta;
    cl_event *events;
    bool isComplex;

    base = clMath::BlasBase::getInstance();
    if ((typeid(T) == typeid(cl_double) ||
         typeid(T) == typeid(DoubleComplex)) &&
        !base->isDevSupportDoublePrecision()) {

        std::cerr << ">> WARNING: The target device doesn't support native "
                     "double precision floating point arithmetic" <<
                     std::endl << ">> Test skipped" << std::endl;
        SUCCEED();
        return;
    }

    isComplex = ((typeid(T) == typeid(FloatComplex)) ||
                 (typeid(T) == typeid(DoubleComplex)));

    if (canCaseBeSkipped(params, isComplex)) {
        std::cerr << ">> Test is skipped because it has no importance for this "
                     "level of coverage" << std::endl;
        SUCCEED();
        return;
    }

    useAlpha = base->useAlpha();
    useBeta = base->useBeta();
    alpha = ZERO<T>();
    beta = ZERO<T>();

    events = new cl_event[params->numCommandQueues];
    memset(events, 0, params->numCommandQueues * sizeof(cl_event));

    A = new T[params->rowsA * params->columnsA];
    B = new T[params->rowsB * params->columnsB];
    blasC = new T[params->rowsC * params->columnsC];
    clblasC = new T[params->rowsC * params->columnsC];

    srand(params->seed);
    if (useAlpha) {
        alpha = convertMultiplier<T>(params->alpha);
    }
    if (useBeta) {
        beta = convertMultiplier<T>(params->beta);
    }

    //::std::cerr << "Generating input data... ";
    randomGemmMatrices<T>(params->order, params->transA, params->transB,
        params->M, params->N, params->K, useAlpha, &alpha, A, params->lda,
        B, params->ldb, useBeta, &beta, blasC, params->ldc);
    memcpy(clblasC, blasC, params->rowsC * params->columnsC * sizeof(*blasC));
    //::std::cerr << "Done" << ::std::endl;

    //::std::cerr << "Calling reference xGEMM routine... ";
    if (params->order == clblasColumnMajor) {
        ::clMath::blas::gemm(clblasColumnMajor, params->transA, params->transB,
                          params->M, params->N, params->K, alpha, A,
                          params->lda, B, params->ldb, beta, blasC, params->ldc);
    }
    else {
        T *reorderedA = new T[params->rowsA * params->columnsA];
        T *reorderedB = new T[params->rowsB * params->columnsB];
        T *reorderedC = new T[params->rowsC * params->columnsC];

        reorderMatrix<T>(clblasRowMajor, params->rowsA, params->columnsA,
                         A, reorderedA);
        reorderMatrix<T>(clblasRowMajor, params->rowsB, params->columnsB,
                         B, reorderedB);
        reorderMatrix<T>(clblasRowMajor, params->rowsC, params->columnsC,
                         blasC, reorderedC);
        ::clMath::blas::gemm(clblasColumnMajor, params->transA, params->transB,
                          params->M, params->N, params->K, alpha, reorderedA,
                          params->rowsA, reorderedB, params->rowsB,
                          beta, reorderedC, params->rowsC);
        reorderMatrix<T>(clblasColumnMajor, params->rowsC, params->columnsC,
                         reorderedC, blasC);

        delete[] reorderedC;
        delete[] reorderedB;
        delete[] reorderedA;
    }
    //::std::cerr << "Done" << ::std::endl;

    bufA = base->createEnqueueBuffer(A, params->rowsA * params->columnsA *
                                        sizeof(*A), params->offA * sizeof(*A),
                                     CL_MEM_READ_ONLY);
    bufB = base->createEnqueueBuffer(B, params->rowsB * params->columnsB *
                                        sizeof(*B), params->offBX * sizeof(*B),
                                     CL_MEM_READ_ONLY);
    bufC = base->createEnqueueBuffer(clblasC, params->rowsC * params->columnsC *
                                              sizeof(*clblasC),
                                     params->offCY * sizeof(*clblasC),
                                     CL_MEM_READ_WRITE);
    if ((bufA == NULL) || (bufB == NULL) || (bufC == NULL)) {
        /* Skip the test, the most probable reason is
         *     matrix too big for a device.
         */
        releaseMemObjects(bufA, bufB, bufC);
        deleteBuffers<T>(A, B, blasC, clblasC);
        delete[] events;
        ::std::cerr << ">> Failed to create/enqueue buffer for a matrix."
            << ::std::endl
            << ">> Can't execute the test, because data is not transfered to GPU."
            << ::std::endl
            << ">> Test skipped." << ::std::endl;
        SUCCEED();
        return;
    }

    //::std::cerr << "Calling clblas xGEMM routine... ";
    err = (cl_int)::clMath::clblas::gemm(params->order, params->transA,
        params->transB, params->M, params->N, params->K, alpha, bufA,
        params->offA, params->lda, bufB, params->offBX, params->ldb, beta,
        bufC, params->offCY, params->ldc, params->numCommandQueues,
        base->commandQueues(), 0, NULL, events);
    if (err != CL_SUCCESS) {
        releaseMemObjects(bufA, bufB, bufC);
        deleteBuffers<T>(A, B, blasC, clblasC);
        delete[] events;
        ASSERT_EQ(CL_SUCCESS, err) << "::clMath::clblas::GEMM() failed";
    }

    err = waitForSuccessfulFinish(params->numCommandQueues,
        base->commandQueues(), events);
    if (err != CL_SUCCESS) {
        releaseMemObjects(bufA, bufB, bufC);
        deleteBuffers<T>(A, B, blasC, clblasC);
        delete[] events;
        ASSERT_EQ(CL_SUCCESS, err) << "waitForSuccessfulFinish()";
    }
    //::std::cerr << "Done" << ::std::endl;

    clEnqueueReadBuffer(base->commandQueues()[0], bufC, CL_TRUE,
                        params->offCY * sizeof(*clblasC),
                        params->rowsC * params->columnsC * sizeof(*clblasC),
                        clblasC, 0, NULL, NULL);

    releaseMemObjects(bufA, bufB, bufC);
    compareMatrices<T>(params->order, params->M, params->N, blasC, clblasC,
                       params->ldc);
    deleteBuffers<T>(A, B, blasC, clblasC);
    delete[] events;
}

// Instantiate the test

TEST_P(GEMM, sgemm) {
    TestParams params;

    getParams(&params);
    gemmCorrectnessTest<cl_float>(&params);
}

TEST_P(GEMM, dgemm) {
    TestParams params;

    getParams(&params);
    gemmCorrectnessTest<cl_double>(&params);
}

TEST_P(GEMM, cgemm) {
    TestParams params;

    getParams(&params);
    gemmCorrectnessTest<FloatComplex>(&params);
}

TEST_P(GEMM, zgemm) {
    TestParams params;

    getParams(&params);
    gemmCorrectnessTest<DoubleComplex>(&params);
}
