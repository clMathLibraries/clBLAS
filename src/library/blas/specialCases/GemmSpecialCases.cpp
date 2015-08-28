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
#include "UserGemmKernelSources/UserGemmClKernels.h"
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
	//for example, when M=N=K=8192
	//we are gonna call 16 GEMMs 
	//each GEMM has M=N=K=4096
	//note are direct GEMM call has a 0.7 TFLOPS performance

	//     [ A11 | A12 | A13 | A14 ]      [ B11 | B12 | B13 | B14 ]      [ C11 | C12 ]
	// A = [ A21 | A22 | A23 | A24 ]  B = [ B21 | B22 | B23 | B24 ]  C = [ C21 | C22 ] 

	// 16 GEMMs are
	// #01: C11 = a*A11*B11 + b*C11
	// #02: C11 = a*A12*B12 + 1*C11
	// #03: C11 = a*A13*B13 + 1*C11
	// #04: C11 = a*A14*B14 + 1*C11 now we are done with C11

	// #05: C12 = a*A11*B21 + b*C12
	// #06: C12 = a*A12*B22 + 1*C12
	// #07: C12 = a*A12*B22 + 1*C12
	// #08: C12 = a*A12*B22 + 1*C12 now we are done with C12

	// #09: C21 = a*A21*B11 + b*C21
	// #10: C21 = a*A22*B12 + 1*C21
	// #11: C21 = a*A23*B13 + 1*C21
	// #12: C21 = a*A24*B14 + 1*C21 now we are done with C21

	// #13: C22 = a*A21*B21 + b*C22
	// #14: C22 = a*A22*B22 + 1*C22
	// #15: C22 = a*A23*B23 + 1*C22
	// #16: C22 = a*A24*B24 + 1*C22 now we are done with C22

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

clblasStatus GEMM_mod1024(
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
					if (!((transA == clblasNoTrans) && (transB == clblasTrans)))
						return clblasNotImplemented;

					specialCaseHandled = true;
					unsigned int M_split_factor;
					unsigned int N_split_factor;
					unsigned int K_split_factor;

					if (lda < 7168)
					{
						M_split_factor = 1;
						N_split_factor = 1;
						K_split_factor = 1;
					}
					else
					{
						//7168, 8192
						M_split_factor = 2;
						N_split_factor = 2;
						K_split_factor = 4;
					}

					tileKernelSource = sgemm_Col_NT_B1_MX128_NX128_KX16_src;
					tileClKernel = &sgemm_Col_NT_B1_MX128_NX128_KX16_clKernel;
					//tileClKernel = &sgemm_Col_NT_B1_MX096_NX096_KX16_clKernel;

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
						tileClKernel, clblasColumnMajor,
						128, 16,
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
						tileClKernel, clblasColumnMajor,
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


clblasStatus GEMM_SPLIT64_32(
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
	//all the mod32 sizes that is not mod64 or mod96 ranging from 1184 to 3872 
	//non mod32 cases are not implemented in this approach and are of less interest
	const char *tileKernelSource = NULL;
	const char *rowKernelSource = NULL;
	const char *columnKernelSource = NULL;
	const char *singleKernelSource = NULL;

	cl_kernel  *tileClKernel = NULL;
	cl_kernel  *rowClKernel = NULL;
	cl_kernel  *columnClKernel = NULL;
	cl_kernel  *singleClKernel = NULL;

	const unsigned char *tileKernelBinary = NULL;
	const unsigned char *rowKernelBinary = NULL;
	const unsigned char *columnKernelBinary = NULL;
	const unsigned char *singleKernelBinary = NULL;

	size_t *tileKernelBinarySize = 0;
	size_t *rowKernelBinarySize = 0;
	size_t *columnKernelBinarySize = 0;
	size_t *singleKernelBinarySize = 0;

	cl_int err;
	
	if ((M >= 1184 && N >= 1184) && (M <= 3872 && N <= 3872) && (M % 64 != 0 && N % 64 != 0) && (M % 96 != 0 && N % 96 != 0) && (K % 16 == 0))
	{
		if ((M % 32 == 0 && N % 32 == 0) && (transA == clblasNoTrans && transB == clblasTrans))
		{
			specialCaseHandled = true;
			//execute the kernels

			//GlobalX = ((Mvalue - 1) / 64) * 16
			//GlobalY = ((Nvalue - 1) / 64) * 16
			size_t GlobalX = ((M - 1) / 64) * 16;
			size_t GlobalY = ((N - 1) / 64) * 16;
			size_t gs[2] = { GlobalX, GlobalY };
			size_t wgsize[2] = { 16, 16 };

			tileKernelSource = sgemm_Col_NT_B1_MX064_NX064_KX16_src;
			tileClKernel = &sgemm_Col_NT_B1_MX064_NX064_KX16_clKernel;

			rowKernelSource = sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_src;
			rowClKernel = &sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_clKernel;

			columnKernelSource = sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_src;
			columnClKernel = &sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_clKernel;

			singleKernelSource = sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_src;
			singleClKernel = &sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_clKernel;

			cl_kernel * Kernels[4] = { tileClKernel, rowClKernel, columnClKernel, singleClKernel };


			makeGemmKernel(tileClKernel, commandQueues[0], tileKernelSource, User_srcBuildOptions, &tileKernelBinary, tileKernelBinarySize, User_binBuildOptions);
			makeGemmKernel(rowClKernel, commandQueues[0], rowKernelSource, User_srcBuildOptions, &rowKernelBinary, rowKernelBinarySize, User_binBuildOptions);
			makeGemmKernel(columnClKernel, commandQueues[0], columnKernelSource, User_srcBuildOptions, &columnKernelBinary, columnKernelBinarySize, User_binBuildOptions);
			makeGemmKernel(singleClKernel, commandQueues[0], singleKernelSource, User_srcBuildOptions, &singleKernelBinary, singleKernelBinarySize, User_binBuildOptions);

			for (int i = 0; i < 4; i++)
			{
				err = clSetKernelArg(*Kernels[i], 0, sizeof(cl_mem), &A);
				CL_CHECK(err);
				err = clSetKernelArg(*Kernels[i], 1, sizeof(cl_mem), &B);
				CL_CHECK(err);
				err = clSetKernelArg(*Kernels[i], 2, sizeof(cl_mem), &C);
				CL_CHECK(err);
				err = clSetKernelArg(*Kernels[i], 3, sizeof(cl_float), &alpha);
				CL_CHECK(err);
				err = clSetKernelArg(*Kernels[i], 4, sizeof(cl_float), &beta);
				CL_CHECK(err);
				err = clSetKernelArg(*Kernels[i], 5, sizeof(cl_uint), &M);
				CL_CHECK(err);
				err = clSetKernelArg(*Kernels[i], 6, sizeof(cl_uint), &N);
				CL_CHECK(err);
				err = clSetKernelArg(*Kernels[i], 7, sizeof(cl_uint), &K);
				CL_CHECK(err);
				err = clSetKernelArg(*Kernels[i], 8, sizeof(cl_uint), &lda);
				CL_CHECK(err);
				err = clSetKernelArg(*Kernels[i], 9, sizeof(cl_uint), &ldb);
				CL_CHECK(err);
				err = clSetKernelArg(*Kernels[i], 10, sizeof(cl_uint), &ldc);
				CL_CHECK(err);
				err = clSetKernelArg(*Kernels[i], 11, sizeof(cl_uint), &offA);
				CL_CHECK(err);
				err = clSetKernelArg(*Kernels[i], 12, sizeof(cl_uint), &offB);
				CL_CHECK(err);
				err = clSetKernelArg(*Kernels[i], 13, sizeof(cl_uint), &offC);
				CL_CHECK(err);
			}

			err = clEnqueueNDRangeKernel(commandQueues[0], *Kernels[0], 2, NULL, gs, wgsize, numEventsInWaitList, eventWaitList, NULL);

			gs[0] = 16;
			err |= clEnqueueNDRangeKernel(commandQueues[0], *Kernels[1], 2, NULL, gs, wgsize, 0, NULL, NULL);

			gs[1] = 16;
			gs[0] = GlobalX;
			err |= clEnqueueNDRangeKernel(commandQueues[0], *Kernels[2], 2, NULL, gs, wgsize, 0, NULL, NULL);

			gs[0] = 16; gs[1] = 16;
			err |= clEnqueueNDRangeKernel(commandQueues[0], *Kernels[3], 2, NULL, gs, wgsize, 0, NULL, events);

			if (err == 0)
				return clblasSuccess;

		}
	}
	
	return clblasNotImplemented;
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

	clblasStatus status;

	//handles big multiples of 1024
	status = GEMM_mod1024(transA,
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
		events,
		specialCaseHandled);
	if (specialCaseHandled)
		return status;

	//handles mod32 but not mod 64
	status = GEMM_SPLIT64_32(transA,
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
		events,
		specialCaseHandled);
	if (specialCaseHandled)
		return status;


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