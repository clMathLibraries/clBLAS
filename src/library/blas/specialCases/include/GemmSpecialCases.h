/* ************************************************************************
* Copyright 2015 Advanced Micro Devices, Inc.
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

#ifndef CLBLAS_GEMM_SPECIAL_CASES_H
#define CLBLAS_GEMM_SPECIAL_CASES_H

#include <clBLAS.h>
#include <stdio.h>
#include <assert.h>

template<typename Precision>
clblasStatus
GemmSpecialCases(clblasOrder order,
                 clblasTranspose transA,
				 clblasTranspose transB,
				 cl_uint M, cl_uint N, cl_uint K,
				 Precision alpha,
				 cl_mem A, cl_uint offA, cl_uint lda,
				 cl_mem B, cl_uint offB, cl_uint ldb,
				 Precision beta,
				 cl_mem C, cl_uint offC, cl_uint ldc,
				 cl_uint numCommandQueues,
				 cl_command_queue *commandQueues,
                 cl_uint numEventsInWaitList,
				 const cl_event *eventWaitList,
				 cl_event *events,
                 bool &specialCaseHandled);

#endif