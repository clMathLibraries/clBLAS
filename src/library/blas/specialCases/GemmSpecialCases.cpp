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

#include <algorithm>
#include <iostream>

#include "GemmSpecialCases.h"
#include "UserGemmKernelSources/UserGemmKernelSourceIncludes.h"
#include "UserGemmKernelSources/UserGemmClKernels.h"
#include "xgemm.h" //helper functions defined in xgemm.cpp
#include "AutoGemmIncludes/AutoGemmClKernels.h"
#include "AutoGemmIncludes/AutoGemmKernelSources.h"
#include "AutoGemmIncludes/AutoGemmKernelBinaries.h"

/******************************************************************************
* Check OpenCL Errors
*****************************************************************************/
#define CL_CHECK(RET) \
  if(RET != CL_SUCCESS) { \
    printf("OpenCL error %i on line %u\n", RET, __LINE__); \
    assert(false); \
    }
/*
template<typename precision>
clblasStatus SGEMM_SPLIT_CALLS(
	cl_kernel *ClKernel, clblasOrder order,
	unsigned int tile_size, unsigned int WG_size,
	unsigned int M_split_factor,
	unsigned int N_split_factor,
	unsigned int K_split_factor,
	clblasTranspose transA,
	clblasTranspose transB,
	cl_uint M, cl_uint N, cl_uint K,
	precision alpha,
	cl_mem A, cl_uint offA, cl_uint lda,
	cl_mem B, cl_uint offB, cl_uint ldb,
	precision beta,
	cl_mem C, cl_uint offC, cl_uint ldc,
	cl_uint numCommandQueues,
	cl_command_queue *commandQueues,
	cl_uint numEventsInWaitList,
	const cl_event *eventWaitList,
	cl_event *events);
*/
template<typename precision>
clblasStatus GEMM_SPLIT_CALLS(
	cl_kernel *ClKernel, clblasOrder order,
	unsigned int tile_size, unsigned int WG_size,
	unsigned int M_split_factor,
	unsigned int N_split_factor,
	unsigned int K_split_factor,
	clblasTranspose transA,
	clblasTranspose transB,
	cl_uint M, cl_uint N, cl_uint K,
	precision alpha,
	cl_mem A, cl_uint offA, cl_uint lda,
	cl_mem B, cl_uint offB, cl_uint ldb,
	precision beta,
	cl_mem C, cl_uint offC, cl_uint ldc,
	cl_uint numCommandQueues,
	cl_command_queue *commandQueues,
	cl_uint numEventsInWaitList,
	const cl_event *eventWaitList,
	cl_event *events)
{
	//for example, when M=N=K=8192 in GEMM col NT
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

	if (transA == clblasNoTrans && transB == clblasTrans)
	{

		unsigned int small_M = M / M_split_factor;
		unsigned int small_N = N / N_split_factor;
		unsigned int small_K = K / K_split_factor;

		size_t GlobalX = ((small_M - 1) / tile_size + 1) * WG_size;
		size_t GlobalY = ((small_N - 1) / tile_size + 1) * WG_size;
		size_t gs[2] = { GlobalX, GlobalY };
		size_t wgsize[2] = { WG_size, WG_size };
		cl_int error = 0;

		precision betaone = 1;

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
						error = clSetKernelArg(*ClKernel, 4, sizeof(precision), &(beta));
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
						error = clSetKernelArg(*ClKernel, 4, sizeof(precision), &betaone);
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
	return clblasNotImplemented;
}

clblasStatus SGEMM_mod1024(
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
	size_t tileKernelBinarySize = 0;
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
					tileKernelBinary = sgemm_Col_NT_B1_MX128_NX128_KX16_bin;
					tileKernelBinarySize = sgemm_Col_NT_B1_MX128_NX128_KX16_binSize;

					makeGemmKernel(tileClKernel, commandQueues[0], tileKernelSource, User_srcBuildOptions, &tileKernelBinary, &tileKernelBinarySize, User_binBuildOptions);

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

					status = GEMM_SPLIT_CALLS(
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
					tileKernelBinary = sgemm_Col_NT_B1_MX096_NX096_KX16_bin;
					tileKernelBinarySize = sgemm_Col_NT_B1_MX096_NX096_KX16_binSize;

					makeGemmKernel(tileClKernel, commandQueues[0], tileKernelSource, User_srcBuildOptions, &tileKernelBinary, &tileKernelBinarySize, User_binBuildOptions);

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


					status = GEMM_SPLIT_CALLS(
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

#define CL_DEVICE_GFXIP_MAJOR_AMD 0x404A
#define CL_DEVICE_GFXIP_MINOR_AMD 0x404B
#define GFXIP_MAJOR_VEGA 9
#define GFXIP_MINOR_VEGA_20 6

clblasStatus DGEMM_tensile(
	clblasOrder order,
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
	const char *kernelSource = NULL;
	cl_kernel  *clKernel = NULL;
	const unsigned char *kernelBinary = NULL;
	size_t kernelBinarySize = 0;

	cl_int err;

	// query device
	cl_device_id device;
	err = clGetCommandQueueInfo(commandQueues[0], CL_QUEUE_DEVICE, sizeof(device), &device, NULL);
	CL_CHECK(err);

	cl_uint gfxipMajor = 0;
	err = clGetDeviceInfo(device, CL_DEVICE_GFXIP_MAJOR_AMD, sizeof(gfxipMajor), &gfxipMajor, NULL);
	CL_CHECK(err);

	cl_uint gfxipMinor = 0;
	err = clGetDeviceInfo(device, CL_DEVICE_GFXIP_MINOR_AMD, sizeof(gfxipMinor), &gfxipMinor, NULL);
	CL_CHECK(err);

	if (gfxipMajor == GFXIP_MAJOR_VEGA && gfxipMinor == GFXIP_MINOR_VEGA_20)
	{
		int M_divisible_by_64 = (M % 64) ? 0 : 1; // M is divisible by 64
		int N_divisible_by_64 = (N % 64) ? 0 : 1; // N is divisible by 64
		int K_divisible_by_64 = (K % 64) ? 0 : 1; // K is divisible by 64
		int mask = (M_divisible_by_64 << 2) | (N_divisible_by_64 << 1) | (K_divisible_by_64 << 0); // 3bit divisibility mask

		enum
		{
			NONE,   // none of M,N,K is divisible by 64
			K64,    // only K is divisible by 64
			N64,    // only N is divisible by 64
			NK64,   // N and K are both divisible, and M is not divisible by 64
			M64,    // only M is divisible by 64
			MK64,   // M and K are both divisible, and N is not divisible by 64
			MN64,   // M and N are both divisible, and K is not divisible by 64
			MNK64,  // all of M,N,K are divisible by 64
		};

		assert(mask >= NONE && mask <= MNK64);

		// decide if we execute Tensile kernel or fallback to original clBLAS implementation
		bool fallback = false;
		if (order == clblasRowMajor)
		{
			if (transA == clblasNoTrans && transB == clblasNoTrans)
			{
				switch (mask)
				{
				case NONE : break;
				case K64  : break;
				case N64  : break;
				case NK64 : fallback = true; break;
				case M64  : break;
				case MK64 : fallback = (M > 1280) || (K < 128) || (M + N < 1150) || (M + N > 4574) || (M + K > 7168) || (M + N + K < 1424) || (M + N + K > 8338); break;
				case MN64 : break;
				case MNK64: fallback = true; break;
				}
			}
			else if (transA == clblasNoTrans && transB == clblasTrans)
			{
				switch (mask)
				{
				case NONE : break;
				case K64  : break;
				case N64  : break;
				case NK64 : fallback = (K < 128) || (M + N + K < 1040); break;
				case M64  : break;
				case MK64 : break;
				case MN64 : break;
				case MNK64: fallback = true; break;
				}
			}
			else if (transA == clblasTrans && transB == clblasNoTrans)
			{
				switch (mask)
				{
				case NONE : break;
				case K64  : break;
				case N64  : break;
				case NK64 : fallback = (M + N > 4987) || (M + N + K > 10176); break;
				case M64  : fallback = (M > 3072) || (M + N > 4539) || (M + K > 6500) || (M + N + K > 8077); break;
				case MK64 : fallback = (M > 128) || (N > 894) || (K < 256) || (M + N > 1680) || (M + K > 2112) || (N + K > 3376) || (M + N + K > 3606); break;
				case MN64 : fallback = (M + N > 3840) || (M + N + K > 7076); break;
				case MNK64: fallback = (M > 64) || (N > 64) || (K < 768) || (K > 2048) || (M + N > 640) || (M + K > 1408) || (N + K > 1152) || (M + N + K < 576) || (M + N + K > 2048); break;
				}
			}
			else // (transA == clblasTrans && transB == clblasTrans)
			{
				switch (mask)
				{
				case NONE : break;
				case K64  : break;
				case N64  : break;
				case NK64 : fallback = (M > 3340) || (N < 128) || (N > 2560) || (K < 1536) || (M + N < 1558) || (M + N > 3888) || (M + K < 790) || (N + K < 1536) || (M + N + K < 2639); break;
				case M64  : break;
				case MK64 : fallback = (M < 128) || (K < 128) || (M + N < 1558) || (N + K < 1022) || (M + N + K < 2326); break;
				case MN64 : break;
				case MNK64: fallback = true; break;
				}
			}
		}
		else // (order == clblasColumnMajor)
		{
			if (transA == clblasNoTrans && transB == clblasNoTrans)
			{
				switch (mask)
				{
				case NONE : break;
				case K64  : break;
				case N64  : break;
				case NK64 : fallback = (N > 2048) || (M + N < 1168) || ( M + N > 4731) ||(M + N + K < 1534) || (M + N + K > 8635);break;
				case M64  : break;
				case MK64 : fallback = true; break;
				case MN64 : break;
				case MNK64: fallback = true; break;
				}
			}
			else if (transA == clblasNoTrans && transB == clblasTrans)
			{
				switch (mask)
				{
				case NONE : break;
				case K64  : break;
				case N64  : fallback = (N > 3072) || (M + N > 4539) || (N + K > 6500) || (M + N + K > 8077); break;
				case NK64 : fallback = (M > 894) || (N > 128) || (M + N > 1814) || (M + K > 3454) || (N + K > 2112) || (M + N + K > 3696); break;
				case M64  : break;
				case MK64 : fallback = (M + N > 4987) || (M + N + K > 9996); break;
				case MN64 : fallback = (M + N > 4160) || (M + N + K > 7076); break;
				case MNK64: fallback = true; break;
				}
			}
			else if (transA == clblasTrans && transB == clblasNoTrans)
			{
				switch (mask)
				{
				case NONE : break;
				case K64  : break;
				case N64  : break;
				case NK64 : fallback = (M + N + K < 854); break;
				case M64  : break;
				case MK64 : break;
				case MN64 : break;
				case MNK64: fallback = true; break;
				}
			}
			else // (transA == clblasTrans && transB == clblasTrans)
			{
				switch (mask)
				{
				case NONE : break;
				case K64  : break;
				case N64  : break;
				case NK64 : fallback = (N < 128) || (M + N < 1615) || (M + K < 790) || (N + K < 384) || (M + N + K < 2383); break;
				case M64  : break;
				case MK64 : fallback = (M < 128) || (N > 3474) || (K < 1280) || (M + N < 1615) || (M + N > 3966) || (M + K < 1536) || (N + K < 1046) || (M + N + K < 2686); break;
				case MN64 : break;
				case MNK64: fallback = true; break;
				}
			}
		}

		if (fallback)
			return clblasNotImplemented;

		// pick kernel
		cl_uint threadTile[2] = { 4, 4 };
		cl_uint groupSize[2] = { 8, 8 };
		if (transA == clblasNoTrans && transB == clblasNoTrans)
		{
			kernelSource     =  dgemm_NN_gfx906_tensile_src;
			clKernel         = &dgemm_NN_gfx906_tensile_clKernel;
			kernelBinary     =  dgemm_NN_gfx906_tensile_bin;
			kernelBinarySize =  dgemm_NN_gfx906_tensile_binSize;

			threadTile[0] = dgemm_NN_gfx906_tensile_microTileNumRows;
			threadTile[1] = dgemm_NN_gfx906_tensile_microTileNumCols;
			groupSize[0]  = dgemm_NN_gfx906_tensile_workGroupNumRows;
			groupSize[1]  = dgemm_NN_gfx906_tensile_workGroupNumCols;
		}
		else if (transA == clblasNoTrans && transB == clblasTrans)
		{
			kernelSource     =  dgemm_NT_gfx906_tensile_src;
			clKernel         = &dgemm_NT_gfx906_tensile_clKernel;
			kernelBinary     =  dgemm_NT_gfx906_tensile_bin;
			kernelBinarySize =  dgemm_NT_gfx906_tensile_binSize;

			threadTile[0] = dgemm_NT_gfx906_tensile_microTileNumRows;
			threadTile[1] = dgemm_NT_gfx906_tensile_microTileNumCols;
			groupSize[0]  = dgemm_NT_gfx906_tensile_workGroupNumRows;
			groupSize[1]  = dgemm_NT_gfx906_tensile_workGroupNumCols;
		}
		else if (transA == clblasTrans && transB == clblasNoTrans)
		{
			kernelSource     =  dgemm_TN_gfx906_tensile_src;
			clKernel         = &dgemm_TN_gfx906_tensile_clKernel;
			kernelBinary     =  dgemm_TN_gfx906_tensile_bin;
			kernelBinarySize =  dgemm_TN_gfx906_tensile_binSize;

			threadTile[0] = dgemm_TN_gfx906_tensile_microTileNumRows;
			threadTile[1] = dgemm_TN_gfx906_tensile_microTileNumCols;
			groupSize[0]  = dgemm_TN_gfx906_tensile_workGroupNumRows;
			groupSize[1]  = dgemm_TN_gfx906_tensile_workGroupNumCols;
		}
		else // (transA == clblasTrans && transB == clblasTrans)
		{
			kernelSource     =  dgemm_TT_gfx906_tensile_src;
			clKernel         = &dgemm_TT_gfx906_tensile_clKernel;
			kernelBinary     =  dgemm_TT_gfx906_tensile_bin;
			kernelBinarySize =  dgemm_TT_gfx906_tensile_binSize;

			threadTile[0] = dgemm_TT_gfx906_tensile_microTileNumRows;
			threadTile[1] = dgemm_TT_gfx906_tensile_microTileNumCols;
			groupSize[0]  = dgemm_TT_gfx906_tensile_workGroupNumRows;
			groupSize[1]  = dgemm_TT_gfx906_tensile_workGroupNumCols;
		}

		specialCaseHandled = true;
		makeGemmKernel(clKernel, commandQueues[0], kernelSource, User_srcBuildOptions, &kernelBinary, &kernelBinarySize, User_binBuildOptions);

		// convert clBLAS args to Tensile args
		cl_uint sizeI = M;
		cl_uint sizeJ = N;
		cl_uint sizeK = 1;
		cl_uint sizeL = K;

		cl_uint strideC1 = std::max(sizeI, ldc);
		cl_uint strideC2 = strideC1 * sizeJ;

		cl_uint strideA1 = std::max(transA == clblasNoTrans ? sizeI : sizeL, lda);
		cl_uint strideA2 = strideA1 * (transA == clblasNoTrans ? sizeL : sizeJ);

		cl_uint strideB1 = std::max(transB == clblasNoTrans ? sizeL : sizeJ, ldb);
		cl_uint strideB2 = strideB1 * (transB == clblasNoTrans ? sizeJ : sizeL);

		// grid sizes
		const cl_uint workDim = 3;
		size_t localWorkSize[3] = { 256, 1, 1 };
		size_t globalWorkSize[3];
		globalWorkSize[2] = 1 * sizeK;
		cl_uint macroTile0 = groupSize[0] * threadTile[0];
		cl_uint macroTile1 = groupSize[1] * threadTile[1];
		cl_uint totalWorkGroups0 = sizeI / macroTile0;
		cl_uint totalWorkGroups1 = sizeJ / macroTile1;

		// b/c single kernel, add extra work-group here if edge needed
		if (totalWorkGroups0*macroTile0 < sizeI)
			totalWorkGroups0++;
		if (totalWorkGroups1*macroTile1 < sizeJ)
			totalWorkGroups1++;
		globalWorkSize[0] = totalWorkGroups0*localWorkSize[0];
		globalWorkSize[1] = totalWorkGroups1*localWorkSize[1];

		// setup args
		err = clSetKernelArg(*clKernel,  0, sizeof(C), &C);
		CL_CHECK(err);
		err = clSetKernelArg(*clKernel,  1, sizeof(A), &A);
		CL_CHECK(err);
		err = clSetKernelArg(*clKernel,  2, sizeof(B), &B);
		CL_CHECK(err);
		err = clSetKernelArg(*clKernel,  3, sizeof(alpha), &alpha);
		CL_CHECK(err);
		err = clSetKernelArg(*clKernel,  4, sizeof(beta),  &beta);
		CL_CHECK(err);
		err = clSetKernelArg(*clKernel,  5, sizeof(offC), &offC);
		CL_CHECK(err);
		err = clSetKernelArg(*clKernel,  6, sizeof(offA), &offA);
		CL_CHECK(err);
		err = clSetKernelArg(*clKernel,  7, sizeof(offB), &offB);
		CL_CHECK(err);
		err = clSetKernelArg(*clKernel,  8, sizeof(strideC1), &strideC1);
		CL_CHECK(err);
		err = clSetKernelArg(*clKernel,  9, sizeof(strideC2), &strideC2);
		CL_CHECK(err);
		err = clSetKernelArg(*clKernel, 10, sizeof(strideA1), &strideA1);
		CL_CHECK(err);
		err = clSetKernelArg(*clKernel, 11, sizeof(strideA2), &strideA2);
		CL_CHECK(err);
		err = clSetKernelArg(*clKernel, 12, sizeof(strideB1), &strideB1);
		CL_CHECK(err);
		err = clSetKernelArg(*clKernel, 13, sizeof(strideB2), &strideB2);
		CL_CHECK(err);
		err = clSetKernelArg(*clKernel, 14, sizeof(sizeI), &sizeI);
		CL_CHECK(err);
		err = clSetKernelArg(*clKernel, 15, sizeof(sizeJ), &sizeJ);
		CL_CHECK(err);
		err = clSetKernelArg(*clKernel, 16, sizeof(sizeK), &sizeK);
		CL_CHECK(err);
		err = clSetKernelArg(*clKernel, 17, sizeof(sizeL), &sizeL);
		CL_CHECK(err);

		err = clEnqueueNDRangeKernel(commandQueues[0], *clKernel, workDim, NULL, globalWorkSize, localWorkSize, numEventsInWaitList, eventWaitList, &events[0] );
		CL_CHECK(err);
		if (err == CL_SUCCESS)
		{
			return clblasSuccess;
		}
	}

	return clblasNotImplemented;
}

clblasStatus SGEMM_SPLIT64_32(
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

	size_t tileKernelBinarySize = 0;
	size_t rowKernelBinarySize = 0;
	size_t columnKernelBinarySize = 0;
	size_t singleKernelBinarySize = 0;

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
			tileKernelBinary = sgemm_Col_NT_B1_MX064_NX064_KX16_bin;
			tileKernelBinarySize = sgemm_Col_NT_B1_MX064_NX064_KX16_binSize;

			rowKernelSource = sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_src;
			rowClKernel = &sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_clKernel;
			rowKernelBinary = sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_bin;
			rowKernelBinarySize = sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_binSize;

			columnKernelSource = sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_src;
			columnClKernel = &sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_clKernel;
			columnKernelBinary = sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_bin;
			columnKernelBinarySize = sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_binSize;

			singleKernelSource = sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_src;
			singleClKernel = &sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_clKernel;
			singleKernelBinary = sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_bin;
			singleKernelBinarySize = sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_binSize;

			cl_kernel * Kernels[4] = { tileClKernel, rowClKernel, columnClKernel, singleClKernel };


			makeGemmKernel(tileClKernel, commandQueues[0], tileKernelSource, User_srcBuildOptions, &tileKernelBinary, &tileKernelBinarySize, User_binBuildOptions);
			makeGemmKernel(rowClKernel, commandQueues[0], rowKernelSource, User_srcBuildOptions, &rowKernelBinary, &rowKernelBinarySize, User_binBuildOptions);
			makeGemmKernel(columnClKernel, commandQueues[0], columnKernelSource, User_srcBuildOptions, &columnKernelBinary, &columnKernelBinarySize, User_binBuildOptions);
			makeGemmKernel(singleClKernel, commandQueues[0], singleKernelSource, User_srcBuildOptions, &singleKernelBinary, &singleKernelBinarySize, User_binBuildOptions);

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

clblasStatus SGEMM_BRANCH_32(
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
	size_t tileKernelBinarySize = 0;
	cl_int err;


	const unsigned char *tileKernelBinary = NULL;

	clblasStatus status;

	if ((M * N < 1080 * 1080) && (M % 32 != 0 || N % 32 != 0) && (K%16==0))
	{
		// ((Mvalue - 1) / 32 + 1) * 16
		size_t GlobalX = ((M - 1) / 32 + 1) * 16;
		size_t GlobalY = ((N - 1) / 32 + 1) * 16;
		size_t gs[2] = { GlobalX, GlobalY };
		size_t wgsize[2] = { 16, 16 };

		if (transA == clblasNoTrans && transB == clblasNoTrans)
		{
			specialCaseHandled = true;
			tileKernelSource = sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_src;
			tileClKernel = &sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_clKernel;
			tileKernelBinary = sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_bin;
			tileKernelBinarySize = sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_binSize;

			makeGemmKernel(tileClKernel, commandQueues[0], tileKernelSource, User_srcBuildOptions, &tileKernelBinary, &tileKernelBinarySize, User_binBuildOptions);

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

			err = clEnqueueNDRangeKernel(commandQueues[0], *tileClKernel, 2, NULL,
				gs, wgsize, numEventsInWaitList, eventWaitList, &events[0]);

			if (err == 0)
				return clblasSuccess;
		}
		if (transA == clblasNoTrans && transB == clblasTrans)
		{
			specialCaseHandled = true;
			tileKernelSource = sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_src;
			tileClKernel = &sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_clKernel;
			tileKernelBinary = sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_bin;
			tileKernelBinarySize = sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_binSize;

			makeGemmKernel(tileClKernel, commandQueues[0], tileKernelSource, User_srcBuildOptions, &tileKernelBinary, &tileKernelBinarySize, User_binBuildOptions);

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

			err = clEnqueueNDRangeKernel(commandQueues[0], *tileClKernel, 2, NULL,
				gs, wgsize, numEventsInWaitList, eventWaitList, &events[0]);

			if (err == 0)
				return clblasSuccess;
		}
		if (transA == clblasTrans && transB == clblasNoTrans)
		{
			specialCaseHandled = true;
			tileKernelSource = sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_src;
			tileClKernel = &sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_clKernel;
			tileKernelBinary = sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_bin;
			tileKernelBinarySize = sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_binSize;

			makeGemmKernel(tileClKernel, commandQueues[0], tileKernelSource, User_srcBuildOptions, &tileKernelBinary, &tileKernelBinarySize, User_binBuildOptions);

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

			err = clEnqueueNDRangeKernel(commandQueues[0], *tileClKernel, 2, NULL,
				gs, wgsize, numEventsInWaitList, eventWaitList, &events[0]);

			if (err == 0)
				return clblasSuccess;
		}
	}

	return clblasNotImplemented;
}

clblasStatus DGEMM_BIG_MOD48(
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
	const char *tileKernelSource = NULL;
	cl_kernel  *tileClKernel = NULL;
	size_t tileKernelBinarySize = 0;
	cl_int err;


	const unsigned char *tileKernelBinary = NULL;

	clblasStatus status;
	//split the kernel calls to handle dgemm NT perf drop when matrix sizes are big
	if ((lda == ldb) && (lda >= 18000) && (lda <= 36000)) // between 18000 and 36000 for now
	{
		if (!((transA == clblasNoTrans) && (transB == clblasTrans)))
			return clblasNotImplemented;

		unsigned int M_split_factor;
		unsigned int N_split_factor;
		unsigned int K_split_factor;
		if ((M % 192 == 0) && (N % 192 == 0) && (K % 192 == 0) && (K > lda / 4))
		{
			M_split_factor = 4;
			N_split_factor = 4;
			K_split_factor = 4;
		}
		else if ((M % 96 == 0) && (N % 96 == 0) && (K % 96 == 0) && (K > lda / 4))
		{
			M_split_factor = 2;
			N_split_factor = 2;
			K_split_factor = 2;
		}
		else
		{
			return clblasNotImplemented;
		}

		tileKernelSource = dgemm_Col_NT_B1_MX048_NX048_KX08_src;
		tileClKernel = &dgemm_Col_NT_B1_MX048_NX048_KX08_clKernel;
		tileKernelBinary = dgemm_Col_NT_B1_MX048_NX048_KX08_bin;
		tileKernelBinarySize = dgemm_Col_NT_B1_MX048_NX048_KX08_binSize;

		makeGemmKernel(tileClKernel, commandQueues[0], tileKernelSource, User_srcBuildOptions, &tileKernelBinary, &tileKernelBinarySize, User_binBuildOptions);

		err = clSetKernelArg(*tileClKernel, 0, sizeof(cl_mem), &A);
		CL_CHECK(err);
		err = clSetKernelArg(*tileClKernel, 1, sizeof(cl_mem), &B);
		CL_CHECK(err);
		err = clSetKernelArg(*tileClKernel, 2, sizeof(cl_mem), &C);
		CL_CHECK(err);
		err = clSetKernelArg(*tileClKernel, 3, sizeof(cl_double), &alpha);
		CL_CHECK(err);
		err = clSetKernelArg(*tileClKernel, 4, sizeof(cl_double), &beta);
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

		status = GEMM_SPLIT_CALLS(
			tileClKernel, clblasColumnMajor,
			48, 8,
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
		if (status == clblasSuccess)
			specialCaseHandled = true;

		return status;
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
	clblasStatus status;

	//handles big multiples of 1024
	status = SGEMM_mod1024(transA,
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

	//handles mod32 but not mod64
	status = SGEMM_SPLIT64_32(transA,
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

	//handles middle range sgemm (M*N<1080*1080) that are not mod32 (M%32!=0 || N%32!=0)
	//use 32x32 micro tile kernels with branch statement within kernels
	status = SGEMM_BRANCH_32(transA,
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
	clblasStatus status;

	// handle specific hardware
	status = DGEMM_tensile(order,
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
		events,
		specialCaseHandled);
	if (specialCaseHandled)
		return status;

	if (order == clblasRowMajor)
		return clblasNotImplemented;

	status = DGEMM_BIG_MOD48(transA,
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
