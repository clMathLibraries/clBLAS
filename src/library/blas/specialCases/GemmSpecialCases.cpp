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

#include "GemmSpecialCases.h"
#include "UserGemmKernelSources/UserGemmKernelSourceIncludes.h"
#include "xgemm.h" //helper functions defined in xgemm.cpp
#include "AutoGemmIncludes/AutoGemmClKernels.h"

/******************************************************************************
* Check OpenCL Errors
*****************************************************************************/
#define CL_CHECK(RET) \
  if(RET != CL_SUCCESS) { \
    printf("OpenCL error %i on line %u\n", RET, __LINE__); \
    assert(false); \
    }

clblasStatus SGEMM_SPLIT_CALLS(
	cl_kernel *ClKernel, clblasOrder order,
	unsigned int tile_size, unsigned int WG_size,
	unsigned int M_split_factor,
	unsigned int N_split_factor,
	unsigned int K_split_factor,
	clblasTranspose transA,
	clblasTranspose transB,
	cl_uint M, cl_uint N, cl_uint K,
	float alpha,
	cl_mem A, cl_uint offA, cl_uint lda,
	cl_mem B, cl_uint offB, cl_uint ldb,
	float beta,
	cl_mem C, cl_uint offC, cl_uint ldc,
	cl_uint numCommandQueues,
	cl_command_queue *commandQueues,
	cl_uint numEventsInWaitList,
	const cl_event *eventWaitList,
	cl_event *events)
{
	unsigned int small_M = M / M_split_factor;
	unsigned int small_N = N / N_split_factor;
	unsigned int small_K = K / K_split_factor;

	size_t GlobalX = ((small_M - 1) / tile_size + 1) * WG_size;
	size_t GlobalY = ((small_N - 1) / tile_size + 1) * WG_size;
	size_t gs[2] = { GlobalX, GlobalY };
	size_t wgsize[2] = { WG_size, WG_size };
	cl_int error = 0;

	cl_float betaone = 1;

	error = clSetKernelArg(*ClKernel, 5, sizeof(cl_uint), &small_M);
	assert(error == CL_SUCCESS);
	error = clSetKernelArg(*ClKernel, 6, sizeof(cl_uint), &small_N);
	assert(error == CL_SUCCESS);
	error = clSetKernelArg(*ClKernel, 7, sizeof(cl_uint), &small_K);
	assert(error == CL_SUCCESS);

	for (int M_split_index = 0; M_split_index < M_split_factor; M_split_index++)
	{
		for (int N_split_index = 0; N_split_index < N_split_factor; N_split_index++)
		{
			unsigned int offc_C = ldc*N / N_split_factor * N_split_index + M / M_split_factor * M_split_index + offC;
			error = clSetKernelArg(*ClKernel, 13, sizeof(cl_uint), &offc_C);
			assert(error == CL_SUCCESS);

			for (int K_split_index = 0; K_split_index < K_split_factor; K_split_index++)
			{
				unsigned int offa_A = (M / M_split_factor * M_split_index) + (lda * K / K_split_factor * K_split_index) + offA;
				unsigned int offb_B = (N / N_split_factor * N_split_index) + (ldb * K / K_split_factor * K_split_index) + offB;
				error = clSetKernelArg(*ClKernel, 11, sizeof(cl_uint), &offa_A);
				assert(error == CL_SUCCESS);
				error = clSetKernelArg(*ClKernel, 12, sizeof(cl_uint), &offb_B);
				assert(error == CL_SUCCESS);

				if (K_split_index == 0)
				{
					error = clSetKernelArg(*ClKernel, 4, sizeof(cl_float), &(beta));
					assert(error == CL_SUCCESS);

					if (M_split_index == 0 && N_split_index == 0)
					{
						//very first GEMM call
						if ((M_split_factor == 1) && (N_split_factor == 1) && (K_split_factor == 1))
						{
							//also very last GEMM call
							error = clEnqueueNDRangeKernel(commandQueues[0], *ClKernel, 2, NULL,
								gs, wgsize, numEventsInWaitList, eventWaitList, &events[0]);
							assert(error == CL_SUCCESS);
						}
						else
						{
							error = clEnqueueNDRangeKernel(commandQueues[0], *ClKernel, 2, NULL,
								gs, wgsize, numEventsInWaitList, eventWaitList, NULL);
							assert(error == CL_SUCCESS);
						}
					}
					else
					{
						error = clEnqueueNDRangeKernel(commandQueues[0], *ClKernel, 2, NULL,
							gs, wgsize, 0, NULL, NULL);
						assert(error == CL_SUCCESS);
					}
				}
				else
				{
					error = clSetKernelArg(*ClKernel, 4, sizeof(cl_float), &betaone);
					assert(error == CL_SUCCESS);

					if ((M_split_index == (M_split_factor - 1)) && (N_split_index == (N_split_factor - 1)) && (K_split_index == (K_split_factor - 1)))
					{
						//very last GEMM call
						error = clEnqueueNDRangeKernel(commandQueues[0], *ClKernel, 2, NULL,
							gs, wgsize, 0, NULL, events);
						assert(error == CL_SUCCESS);
					}
					else
					{
						error = clEnqueueNDRangeKernel(commandQueues[0], *ClKernel, 2, NULL,
							gs, wgsize, 0, NULL, NULL);
						assert(error == CL_SUCCESS);
					}
				}
			}
		}
	}

	return clblasSuccess;
}

template<>
clblasStatus
GemmSpecialCases<float>(clblasOrder order,
clblasTranspose transA,
clblasTranspose transB,
cl_uint M, cl_uint N, cl_uint K,
float alpha,
cl_mem A, cl_uint offA, cl_uint lda,
cl_mem B, cl_uint offB, cl_uint ldb,
float beta,
cl_mem C, cl_uint offC, cl_uint ldc,
cl_uint numCommandQueues,
cl_command_queue *commandQueues,
cl_uint numEventsInWaitList,
const cl_event *eventWaitList,
cl_event *events,
bool &specialCaseHandled)
{

	if (order == clblasRowMajor)
		return clblasNotImplemented;



	const char *tileKernelSource = NULL;
	cl_kernel  *tileClKernel = NULL;
	size_t *tileKernelBinarySize = 0;
	cl_int err;


	const unsigned char *tileKernelBinary = NULL;

	clblasStatus status;


	//split the kernel calls to handle sgemm NT perf drop at big multiples of 1024
	if ((lda % 1024 == 0) && (ldb % 1024 == 0) && (K > lda / 4))
	{
		if ((lda == ldb) && (lda >= 4096) && (lda <= 8192)) // between 4096 and 8192 for now
		{
			if (lda != 6144)// 6144 is handled by 96 x 96 kernel
			{
				// we are going to call 16 GEMMs with M=M/2, N=N/2, K=K/4
				// each GEMM requires M%128 == 0, N%128 == 0, K%16 == 0
				if (M % 256 == 0 && N % 256 == 0 && K % 64 == 0)
				{
					return clblasNotImplemented;
				}
			}
			else
			{
				// lda == ldb == 6144
				// we are going to call 4 GEMMs each with K = K/4
				if (M % 96 == 0 && N % 96 == 0 && K % 64 == 0)
				{
					if (!((transA == clblasNoTrans) && (transB == clblasTrans)))
						return clblasNotImplemented;

					specialCaseHandled = true;
					unsigned int M_split_factor = 1;
					unsigned int N_split_factor = 1;
					unsigned int K_split_factor = 4;
					

					tileKernelSource = sgemm_Col_NT_B1_MX096_NX096_KX16_src;
					tileClKernel = &sgemm_Col_NT_B1_MX096_NX096_KX16_clKernel;

					makeGemmKernel(tileClKernel, commandQueues[0], tileKernelSource, User_srcBuildOptions, &tileKernelBinary, tileKernelBinarySize, User_binBuildOptions);
					
					err = clSetKernelArg(*tileClKernel, 0, sizeof(cl_mem), &A);
					CL_CHECK(err);
					err = clSetKernelArg(*tileClKernel, 1, sizeof(cl_mem), &B);
					CL_CHECK(err);
					err = clSetKernelArg(*tileClKernel, 2, sizeof(cl_mem), &C);
					CL_CHECK(err);
					err = clSetKernelArg(*tileClKernel, 3, sizeof(cl_float), &alpha);
					CL_CHECK(err);
					err = clSetKernelArg(*tileClKernel, 4, sizeof(cl_float), &beta);
					CL_CHECK(err);
					err = clSetKernelArg(*tileClKernel, 5, sizeof(cl_uint), &M);
					CL_CHECK(err);
					err = clSetKernelArg(*tileClKernel, 6, sizeof(cl_uint), &N);
					CL_CHECK(err);
					err = clSetKernelArg(*tileClKernel, 7, sizeof(cl_uint), &K);
					CL_CHECK(err);
					err = clSetKernelArg(*tileClKernel, 8, sizeof(cl_uint), &lda);
					CL_CHECK(err);
					err = clSetKernelArg(*tileClKernel, 9, sizeof(cl_uint), &ldb);
					CL_CHECK(err);
					err = clSetKernelArg(*tileClKernel, 10, sizeof(cl_uint), &ldc);
					CL_CHECK(err);
					err = clSetKernelArg(*tileClKernel, 11, sizeof(cl_uint), &offA);
					CL_CHECK(err);
					err = clSetKernelArg(*tileClKernel, 12, sizeof(cl_uint), &offB);
					CL_CHECK(err);
					err = clSetKernelArg(*tileClKernel, 13, sizeof(cl_uint), &offC);
					CL_CHECK(err);


					status = SGEMM_SPLIT_CALLS(
						tileClKernel, order, 
						96, 16,
						M_split_factor,
						N_split_factor, K_split_factor,
						transA,
						transB,
						M, N, K,
						alpha,
						A, offA, lda,
						B, offB, ldb,
						beta,
						C, offC, ldc,
						numCommandQueues,
						commandQueues,
						numEventsInWaitList,
						eventWaitList,
						events);


					return status;
				}
			}
		}
	}

	return clblasNotImplemented;
}

template<>
clblasStatus
GemmSpecialCases<double>(clblasOrder order,
clblasTranspose transA,
clblasTranspose transB,
cl_uint M, cl_uint N, cl_uint K,
double alpha,
cl_mem A, cl_uint offA, cl_uint lda,
cl_mem B, cl_uint offB, cl_uint ldb,
double beta,
cl_mem C, cl_uint offC, cl_uint ldc,
cl_uint numCommandQueues,
cl_command_queue *commandQueues,
cl_uint numEventsInWaitList,
const cl_event *eventWaitList,
cl_event *events,
bool &specialCaseHandled)
{
	return clblasNotImplemented;
}

template<>
clblasStatus
GemmSpecialCases<FloatComplex>(clblasOrder order,
clblasTranspose transA,
clblasTranspose transB,
cl_uint M, cl_uint N, cl_uint K,
FloatComplex alpha,
cl_mem A, cl_uint offA, cl_uint lda,
cl_mem B, cl_uint offB, cl_uint ldb,
FloatComplex beta,
cl_mem C, cl_uint offC, cl_uint ldc,
cl_uint numCommandQueues,
cl_command_queue *commandQueues,
cl_uint numEventsInWaitList,
const cl_event *eventWaitList,
cl_event *events,
bool &specialCaseHandled)
{
	return clblasNotImplemented;
}

template<>
clblasStatus
GemmSpecialCases<DoubleComplex>(clblasOrder order,
clblasTranspose transA,
clblasTranspose transB,
cl_uint M, cl_uint N, cl_uint K,
DoubleComplex alpha,
cl_mem A, cl_uint offA, cl_uint lda,
cl_mem B, cl_uint offB, cl_uint ldb,
DoubleComplex beta,
cl_mem C, cl_uint offC, cl_uint ldc,
cl_uint numCommandQueues,
cl_command_queue *commandQueues,
cl_uint numEventsInWaitList,
const cl_event *eventWaitList,
cl_event *events,
bool &specialCaseHandled)
{
	return clblasNotImplemented;
}