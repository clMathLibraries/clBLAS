 /************************************************************************
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

#include <map>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <clBLAS.h>

#include <functor.h>
#include <functor_selector.h>

#include <devinfo.h>
#include "clblas-internal.h"
#include "solution_seq.h"

#include "TrtriClKernels.h"
#include "TrtriKernelSourceIncludes.h"
#include <iostream>


// Transform a trsm in clblasRowMajor into a trsm in clblasColumnMajor:
//
// The idea is basically that
//   B = A*X
// can be computed as
//   B' = (A*X)'
//      = X'*A'
// And since changing the order is basically a transpose on each matrix,
// the formula becomes with the new order
//   B = X*A (so only the side, the uplo must be changed and the M and N sizes swapped)
//
// When enabled, only the ColumnMajor kernels need to be implemented
// for all TRSM
//

#define FORCE_COLUMN_MAJOR 1

#if FORCE_COLUMN_MAJOR
template <typename Args>
static void force_trsm_column_major(Args & args)
{
    if (args.order == clblasRowMajor)
    {
      std::swap(args.M, args.N);
      args.side = (args.side == clblasLeft ) ? clblasRight : clblasLeft  ;
      args.uplo = (args.uplo == clblasUpper) ? clblasLower : clblasUpper ;
      args.order = clblasColumnMajor;
    }
}
#endif

//
// This file provide the public clBLAS API for
//
//   clblasStrsm()
//   clblasDtrsm()
//   clblasCtrsm()
//   clblasZtrsm()
//
// using functors
//
// Potential optimizations:
////
//  - Get rid of the 'order' argument assuming that
//    row-major is equivalent to the transpose of column-major.
//    That is
//
//       B = A*X
//
//    is equivalent to
//
//       B' = X'*A'
//
//    and, when considering the opposite order, is equivalent to
//
//       B = X*A (with A swap between upper and lower)
//
//    By applying that transformation early, the functors implementing
//    the TRSMs only have to consider one of the two cases.
//

//
// Common part of all XTRSM implementations using the old Solver infrastructure
//

#define CL_CHECK(RET) \
  if(RET != CL_SUCCESS) { \
    printf("OpenCL error %i on line %u\n", RET, __LINE__); \
    assert(false); \
      }

#define min(x,y) ((x)<(y)?(x):(y))

static char *getKernelName(cl_kernel clKernel)
{
  cl_int err;
  // get kernel name
  size_t kernelNameLength;
  err = clGetKernelInfo(
    clKernel,
    CL_KERNEL_FUNCTION_NAME,
    sizeof(kernelNameLength),
    NULL,
    &kernelNameLength);

  // Do not check this error because of an nvidia bug.
  // The kernelNameLength turns out to be of proper length.
  // CL_CHECK(err)

  char *kernelName = new char[kernelNameLength];
  err = clGetKernelInfo(
    clKernel,
    CL_KERNEL_FUNCTION_NAME,
    kernelNameLength*sizeof(char),
    kernelName,
    NULL );
  CL_CHECK(err)

  return kernelName;
}

//FIXME: This function should be returning an error.
void makeKernel(
  cl_kernel *clKernel,
  cl_command_queue clQueue,
  const char *kernelSource,
  const char *sourceBuildOptions,
  const unsigned char **kernelBinary,
  size_t *kernelBinarySize,
  const char *binaryBuildOptions)
{
  //TODO: This will need to be converted to thread local when making clBLAS thread safe
  typedef std::map<std::string, cl_kernel> kernel_map_t;
  static kernel_map_t kernel_map;

  cl_context clContext;
  cl_device_id clDevice;
  cl_int err;

  err = clGetCommandQueueInfo( clQueue, CL_QUEUE_CONTEXT, sizeof(clContext), &clContext, NULL);
  CL_CHECK(err)
  err = clGetCommandQueueInfo( clQueue, CL_QUEUE_DEVICE, sizeof(clDevice), &clDevice, NULL);
  CL_CHECK(err)

  std::stringstream ss;
  ss << clDevice << "_" << clContext;
  std::string prefix = ss.str();

  if (*clKernel) {
    char *kernelName = getKernelName(*clKernel);
    // kernel has already been built, return
#ifdef AUTOGEMM_PRINT_DEBUG
    printf("makeKernel: \"%s\" already built; returning.\n", kernelName);
#endif

    // Check if kernel exists for this device
    std::string key = prefix + "_" + kernelName;
    kernel_map_t::iterator idx = kernel_map.find(key);

    // If kernel not found for this device, set to NULL
    if (idx == kernel_map.end()) {
        *clKernel = NULL;
    } else {
        *clKernel = idx->second;
    }

    delete[] kernelName;
  }

  if (!*clKernel) {
    // kernel has not been built, so build it (from binary, preferably)
    cl_program clProgram;
    cl_int clBinaryStatus;
    if (*kernelBinary) {
#ifdef AUTOGEMM_PRINT_DEBUG
      printf("makeKernel: pre-compiled binary found: %llu bytes\n", *kernelBinarySize);
      printf("makeKernel: Creating program from binary\n");
#endif
      clProgram = clCreateProgramWithBinary(
        clContext,
        1, &clDevice,
        kernelBinarySize, kernelBinary,
        &clBinaryStatus, &err );
#ifdef AUTOGEMM_PRINT_DEBUG
      if (err != CL_SUCCESS) {
          printf("makeKernel: Failed to create program with binary\n");
      }
#endif
      err = clBuildProgram(
        clProgram,
        1, &clDevice,
        binaryBuildOptions, NULL, NULL );
#ifdef AUTOGEMM_PRINT_DEBUG
      if (err != CL_SUCCESS) {
          printf("makeKernel: Failed to build program from binary\n");
      }
#endif
    }

    if (!*kernelBinary || err != CL_SUCCESS) {
#ifdef AUTOGEMM_PRINT_DEBUG
      printf("makeKernel: Creating program from source\n");
#endif
      clProgram = clCreateProgramWithSource(
        clContext,
        1, &kernelSource,
        NULL, &err );
      CL_CHECK(err)
      err = clBuildProgram(
        clProgram,
        1, &clDevice,
        sourceBuildOptions, NULL, NULL );
      CL_CHECK(err)
    }

    // print build failure
    if (err != CL_SUCCESS) {
      printf("clBuildProgram Failed\n");
      printf("err = %d\n", err);

      size_t len = 0;
      clGetProgramBuildInfo(clProgram, clDevice, CL_PROGRAM_BUILD_LOG, 0, NULL, &len);
      char* buildLog = new char[len];

      printf("Error: Failed to build program executable!\n");
      clGetProgramBuildInfo(clProgram, clDevice, CL_PROGRAM_BUILD_LOG, len*sizeof(char), buildLog, 0);
      printf("\nBuild Log:\n\n");
      printf("%s\n", buildLog);
      //printf("\n\nKernel String:\n\n");
      //printf("%s\n", kernelSource);
      //FIXME: The function should be exiting at this point
    }

    err = clCreateKernelsInProgram(
      clProgram,
      1, clKernel,
      NULL );
    CL_CHECK(err)
	err = clReleaseProgram(clProgram);
	CL_CHECK(err)

    char *kernelName = getKernelName(*clKernel);

#ifdef AUTOGEMM_PRINT_DEBUG
    printf("makeKernel: \"%s\" now built; returning.\n", kernelName);
#endif

    std::string key = prefix + "_" + kernelName;
    kernel_map[key] = *clKernel;

    delete[] kernelName;
  }

  return;
}

static cl_int clearBuffer(cl_command_queue  queue,
	cl_mem  buffer,
	size_t  buffer_size)
{

	cl_int err = 0;
	cl_event  event;
	// Hummm clEnqueueFillBuffer is OpenCL 1.2 !!!
	double zero = 0.0;
	err = clEnqueueFillBuffer(queue,
		buffer,
		&zero,
		sizeof(double),
		0,  // offset
		buffer_size,
		0,
		NULL,
		&event
		);

	return err;

}
// Compute the number of blocks of the specified 'size' to fully cover 'n'
// Simply speaking, this is n/size rounded up.
#define BLOCKS(n,size) ( ( (n) / size ) + ( (n) % (size) != 0 ) )

cl_int call_kernel_triple_update192(
	cl_kernel *kernel,
	const char *kernelSource,
	const char *sourceBuildOptions,
	const unsigned char **kernelBinary,
	size_t *kernelBinarySize,
	const char *binaryBuildOptions,
	const cl_command_queue queue,
	cl_mem A,
	unsigned int offA,
	cl_mem d_dinvA,
	int i,
	unsigned int lda,
	int M,
	cl_event *event)
{
	cl_int err = 0;

	unsigned int m = M;

	int npages = M / (i * 2) + (M % (i * 2) != 0);


	size_t globalLocal[2];
	size_t globalThreads[2];
	switch (i)
	{
	case 12:
		globalLocal[0] = 12;
		globalLocal[1] = 1;
		globalThreads[0] = npages * 12;
		globalThreads[1] = 1;
		break;
	case 24:
		globalLocal[0] = 24;
		globalLocal[1] = 2;
		globalThreads[0] = npages * 24;
		globalThreads[1] = 2;
		break;
	case 48:
		globalLocal[0] = 24;
		globalLocal[1] = 2;
		globalThreads[0] = npages * 48;
		globalThreads[1] = 4;
		break;
	case 96:
		globalLocal[0] = 24;
		globalLocal[1] = 2;
		globalThreads[0] = npages * 96;
		globalThreads[1] = 8;
		break;
	default:
		break;
	}

	makeKernel(kernel,
		queue,
		kernelSource,
		sourceBuildOptions,
		kernelBinary,
		kernelBinarySize,
		binaryBuildOptions);
	/*
	if (err != CL_SUCCESS) {
		//printf( "create kernel %s failed with %d\n", kernel_name, err );
		return err;
	}
	*/
	clSetKernelArg(*kernel, 0, sizeof(cl_mem), &A);
	clSetKernelArg(*kernel, 1, sizeof(unsigned int), &offA);
	clSetKernelArg(*kernel, 2, sizeof(cl_mem), &d_dinvA);
	clSetKernelArg(*kernel, 3, sizeof(int), &i);
	clSetKernelArg(*kernel, 4, sizeof(unsigned int), &lda);
	clSetKernelArg(*kernel, 5, sizeof(int), &npages);
	clSetKernelArg(*kernel, 6, sizeof(unsigned int), &m);

	err = clEnqueueNDRangeKernel(queue, *kernel, 2, NULL,
		globalThreads, globalLocal,
		0, NULL, event);


	return err;

}

cl_int diag_dtrtri192(
	cl_command_queue queue,
	int M,
	clblasUplo uplo,
	clblasDiag diag,
	cl_mem A,
	size_t offA,
	cl_mem d_dinvA,
	size_t lda,
	int inner_block_size,
	int outer_block_size,
	cl_event *event)
{

	const char *diag_dtrtri_kernel_upper_KernelSource = NULL;
	cl_kernel  *diag_dtrtri_kernel_upper_ClKernel = NULL;
	size_t diag_dtrtri_kernel_upper_KernelBinarySize = 0;
	const unsigned char *diag_dtrtri_kernel_upper_KernelBinary = NULL;
	cl_int err;

	/*
	This routine is used in dtrsm
	*/

	//For side==right, M is actually N here
	int nthreads = (M / inner_block_size + (M % inner_block_size != 0)) * inner_block_size;
	unsigned int m = M;

	if (uplo == clblasLower) {

		//lower is not supported yet
	}
	else {
		diag_dtrtri_kernel_upper_KernelSource = diag_dtrtri_upper_192_12_src;
		diag_dtrtri_kernel_upper_ClKernel = &diag_dtrtri_upper_192_12_clKernel;
		diag_dtrtri_kernel_upper_KernelBinary = diag_dtrtri_upper_192_12_bin;
		diag_dtrtri_kernel_upper_KernelBinarySize = diag_dtrtri_upper_192_12_binSize;

		//cl_kernel diag_dtrtri_kernel_upper = clCreateKernel(prg, "DIAG_DTRTRI_KERNEL_UPPER", &err);
		makeKernel(diag_dtrtri_kernel_upper_ClKernel,
			       queue,
				   diag_dtrtri_kernel_upper_KernelSource,
				   TrtriBuildOptions,
				   &diag_dtrtri_kernel_upper_KernelBinary,
				   &diag_dtrtri_kernel_upper_KernelBinarySize,
				   TrtribinBuildOptions);


		int isDiagUnit = (diag == clblasUnit);
		err = clSetKernelArg(*diag_dtrtri_kernel_upper_ClKernel, 0, sizeof(int), &isDiagUnit);
		CL_CHECK(err);
		err = clSetKernelArg(*diag_dtrtri_kernel_upper_ClKernel, 1, sizeof(cl_mem), &A);
		CL_CHECK(err);
		err = clSetKernelArg(*diag_dtrtri_kernel_upper_ClKernel, 2, sizeof(unsigned int), &offA);
		CL_CHECK(err);
		err = clSetKernelArg(*diag_dtrtri_kernel_upper_ClKernel, 3, sizeof(cl_mem), &d_dinvA);
		CL_CHECK(err);
		err = clSetKernelArg(*diag_dtrtri_kernel_upper_ClKernel, 4, sizeof(unsigned int), &lda);
		CL_CHECK(err);
		err = clSetKernelArg(*diag_dtrtri_kernel_upper_ClKernel, 5, sizeof(unsigned int), &m);
		CL_CHECK(err);

		size_t globalThreads[1] = { nthreads };
		size_t globalLocal[1] = { inner_block_size };

		err = clEnqueueNDRangeKernel(queue, *diag_dtrtri_kernel_upper_ClKernel, 1, NULL,
			globalThreads, globalLocal,
			0, NULL, event);

		if (err != CL_SUCCESS) {
			//printf( "kernel -diag_dtrtri_kernel_upper- failed with %d\n", err );
			return err;
		}

		//clReleaseKernel(diag_dtrtri_kernel_upper);
		if (err != CL_SUCCESS) {
			return err;
		}

		// update the inverse up to the size of BLOCK_SIZE

		for (int i = inner_block_size; i < outer_block_size; i *= 2) {

			switch (i) {
			case 12:
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_12_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				err = call_kernel_triple_update192(&triple_dgemm_update_192_12_R_clKernel,
					  triple_dgemm_update_192_12_R_src,
					  TrtriBuildOptions,
					  (const unsigned char **)&triple_dgemm_update_192_12_R_bin,
					  &triple_dgemm_update_192_12_R_binSize,
					  TrtribinBuildOptions,
					  queue,
					  A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				break;

			case 24:
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_24_PART1_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_24_PART2_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				err = call_kernel_triple_update192(&triple_dgemm_update_192_24_PART1_R_clKernel,
					  triple_dgemm_update_192_24_PART1_R_src,
					  TrtriBuildOptions,
					  (const unsigned char **)&triple_dgemm_update_192_24_PART1_R_bin,
					  &triple_dgemm_update_192_24_PART1_R_binSize,
					  TrtribinBuildOptions,
					  queue,
					  A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				err = call_kernel_triple_update192(&triple_dgemm_update_192_24_PART2_R_clKernel,
					  triple_dgemm_update_192_24_PART2_R_src,
					  TrtriBuildOptions,
					  (const unsigned char **)&triple_dgemm_update_192_24_PART2_R_bin,
					  &triple_dgemm_update_192_24_PART2_R_binSize,
					  TrtribinBuildOptions,
					  queue,
					  A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				break;

			case 48:
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_48_PART1_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_48_PART2_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				err = call_kernel_triple_update192(&triple_dgemm_update_192_48_PART1_R_clKernel,
					  triple_dgemm_update_192_48_PART1_R_src,
					  TrtriBuildOptions,
					  (const unsigned char **)&triple_dgemm_update_192_48_PART1_R_bin,
					  &triple_dgemm_update_192_48_PART1_R_binSize,
					  TrtribinBuildOptions,
					  queue,
					  A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				err = call_kernel_triple_update192(&triple_dgemm_update_192_48_PART2_R_clKernel,
					  triple_dgemm_update_192_48_PART2_R_src,
					  TrtriBuildOptions,
					  (const unsigned char **)&triple_dgemm_update_192_48_PART2_R_bin,
					  &triple_dgemm_update_192_48_PART2_R_binSize,
					  TrtribinBuildOptions,
					  queue,
					  A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				break;

			case 96:
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_96_PART1_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_96_PART2_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				err = call_kernel_triple_update192(&triple_dgemm_update_192_96_PART1_R_clKernel,
					  triple_dgemm_update_192_96_PART1_R_src,
					  TrtriBuildOptions,
					  (const unsigned char **)&triple_dgemm_update_192_96_PART1_R_bin,
					  &triple_dgemm_update_192_96_PART1_R_binSize,
					  TrtribinBuildOptions,
					  queue,
					  A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				err = call_kernel_triple_update192(&triple_dgemm_update_192_96_PART2_R_clKernel,
					  triple_dgemm_update_192_96_PART2_R_src,
					  TrtriBuildOptions,
					  (const unsigned char **)&triple_dgemm_update_192_96_PART2_R_bin,
					  &triple_dgemm_update_192_96_PART2_R_binSize,
					  TrtribinBuildOptions,
					  queue,
					  A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				break;

			default:

				break;
			}

			if (i * 2 >= M) break;

		}

	}

	return err;

}

static clblasStatus gpu_dtrsm192(
	clblasOrder order,
	clblasSide side,
	clblasUplo uplo,
	clblasTranspose transA,
	clblasDiag diag,
	size_t M,
	size_t N,
	double alpha,
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
	cl_event *events,
	bool &specialCaseHandled)
{
	if (order != clblasColumnMajor)
		return clblasNotImplemented;

	if ((M % 192 == 0) && (N % 192 == 0))
	{
		//TODO: the implementation of sub block being 192 only supports
		//side == right
		//uplo == upper
		//trans == notrans
		//M and N need to be mod192
		//subblock being 192 is prefered over 128 on Hawaii device since
		//it does not create "boundary" in DGEMM calls
		//Hawaii DGEMM calls have better performance when M N K are mod48
		if ((side == clblasRight) && (uplo == clblasUpper) && (transA == clblasNoTrans))
		{
			int inner_block_size = 12; // inner blocking size, <=32
			int outer_block_size = 192;// outer blocking size, >BLOCK_SIZE
			cl_int err = 0;

			int i;
			cl_context context;
			err = getQueueContext(commandQueues[0], &context);
			CL_CHECK(err);

			/* quick return on wrong size */
			if (M <= 0 || N <= 0)
				return clblasInvalidDim;

			double neg_one = -1.0;
			double one = 1.0;
			double zero = 0.0;

			cl_mem InvA = 0;
			cl_mem X = 0;
			// X of size mxn  will contain the result
			size_t ldX = M;
			size_t offX = 0; //must be 0: needed by the _(X,i,j) macro
			size_t size_X = N*ldX * sizeof(double);
			X = clCreateBuffer(context, CL_MEM_READ_WRITE, size_X, NULL, &err);
			CL_CHECK(err);
			err = clearBuffer(commandQueues[0], X, size_X);
			CL_CHECK(err);

			// side=R
			/* invert the diagonals
			* Allocate device memory for the inverted diagonal blocks, size=n*BLOCK_SIZE
			*/

			/* invert the diagonals
			* Allocate device memory for the inverted diagonal blocks, size=m*nb
			*/
			size_t ldInvA = outer_block_size;
			size_t offInvA = 0; //must be 0: needed by the _(X,i,j) macro
			size_t size_InvA = ldInvA * BLOCKS(N, outer_block_size) * outer_block_size *sizeof(double);
			InvA = clCreateBuffer(context, CL_MEM_READ_WRITE, size_InvA, NULL, &err);
			CL_CHECK(err);
			err = clearBuffer(commandQueues[0], InvA, size_InvA);
			CL_CHECK(err);

			diag_dtrtri192(commandQueues[0], N, uplo, diag, A, offA, InvA, lda, inner_block_size, outer_block_size, events);

			if (transA == clblasNoTrans)
			{
				/* the non-transpose case */
				if (uplo == clblasLower)
				{
					/* the lower case */
					/* handle the first block seperately with alpha */
					// lower is not implemented yet


				}
				else
				{
					/* the upper case */
					/* handle the first block seperately with alpha */
					int nn = min(outer_block_size, (int)N);
					//DGEMM_RIGHT(  M, nn, nn, alpha, _(B,0,0), _(InvA,0,0), zero, _(X,0,0) );
					err = clblasDgemm(clblasColumnMajor, clblasNoTrans, clblasNoTrans, M, nn, nn, alpha, B, offB, ldb, InvA, offInvA, ldInvA, zero, X, offX, ldX, 1, commandQueues, 0, NULL, events);
					CL_CHECK(err);

					if (outer_block_size < N)
					{

						//DGEMM_RIGHT(  M, N-nb, nb, neg_one, _(X,0,0), _(A,0,nb), alpha, _(B,0,nb)  );
						err = clblasDgemm(clblasColumnMajor, clblasNoTrans, clblasNoTrans, M, N - outer_block_size, outer_block_size, neg_one, X, offX, ldX, A, offA + lda*outer_block_size, lda, alpha, B, offB + outer_block_size*ldb, ldb, 1, commandQueues, 0, NULL, events);
						assert(err == CL_SUCCESS);

						/* the rest blocks */
						for (i = outer_block_size; i < N; i += outer_block_size)
						{
							nn = min(outer_block_size, (int)N - i);
							//DGEMM_RIGHT(  M, nn, nn, one, _(B,0,i), _(InvA,0,i), zero, _(X,0,i) );
							err = clblasDgemm(clblasColumnMajor, clblasNoTrans, clblasNoTrans, M, nn, nn, one, B, offB + i*ldb, ldb, InvA, offInvA + i*outer_block_size, ldInvA, zero, X, offX + i*ldX, ldX, 1, commandQueues, 0, NULL, events);
							assert(err == CL_SUCCESS);

							if (i + outer_block_size >= N)
								break;

							//DGEMM_RIGHT(  M, N-i-nb, nb, neg_one, _(X,0,i),   _(A,i,i+nb), one, _(B,0,i+nb)  );
							err = clblasDgemm(clblasColumnMajor, clblasNoTrans, clblasNoTrans, M, N - i - outer_block_size, outer_block_size, neg_one, X, offX + i*ldX, ldX, A, offA + i + (outer_block_size + i)*lda, lda, one, B, offB + (i + outer_block_size)*ldb, ldb, 1, commandQueues, 0, NULL, events);
							assert(err == CL_SUCCESS);
						}
					}
				}
			}
			else
			{

				/* the transpose case */
				// trans is not implemented yet
			}

			  {
				  size_t src_origin[3] = { 0, 0, 0 };
				  size_t dst_origin[3] = { offB*sizeof(double), 0, 0 };
				  size_t region[3] = { M*sizeof(double), N, 1 };


				  err = clEnqueueCopyBufferRect(commandQueues[0],
					  X,
					  B,
					  src_origin,
					  dst_origin,
					  region,
					  ldX*sizeof(double), 0,
					  ldb*sizeof(double), 0,
					  0, NULL,
					  events);
				  CL_CHECK(err);

				  clReleaseMemObject(InvA);
				  clReleaseMemObject(X);

			  }

			specialCaseHandled = true;
			return clblasSuccess;

		}
	}



	return clblasNotImplemented;
}

cl_int call_kernel_triple_update128(
	cl_kernel *kernel,
	const char *kernelSource,
	const char *sourceBuildOptions,
	const unsigned char **kernelBinary,
	size_t *kernelBinarySize,
	const char *binaryBuildOptions,
	const cl_command_queue queue,
	cl_mem A,
	unsigned int offA,
	cl_mem d_dinvA,
	int i,
	unsigned int lda,
	int M,
	cl_event *event)
{
	cl_int err = 0;

	unsigned int m = M;

	int npages = M / (i * 2) + (M % (i * 2) != 0);
	size_t globalLocal[2] = { (i <= 32) ? (i / 4) : 16, 4 };
	size_t globalThreads[2] = { (i / (globalLocal[0] * globalLocal[1]))* globalLocal[0],
		npages*(i / 16) * globalLocal[1] };

	makeKernel(kernel,
		queue,
		kernelSource,
		sourceBuildOptions,
		kernelBinary,
		kernelBinarySize,
		binaryBuildOptions);
	/*
	if (err != CL_SUCCESS) {
	//printf( "create kernel %s failed with %d\n", kernel_name, err );
	return err;
	}
	*/

	clSetKernelArg(*kernel, 0, sizeof(cl_mem), &A);
	clSetKernelArg(*kernel, 1, sizeof(unsigned int), &offA);
	clSetKernelArg(*kernel, 2, sizeof(cl_mem), &d_dinvA);
	clSetKernelArg(*kernel, 3, sizeof(int), &i);
	clSetKernelArg(*kernel, 4, sizeof(unsigned int), &lda);
	clSetKernelArg(*kernel, 5, sizeof(int), &npages);
	clSetKernelArg(*kernel, 6, sizeof(unsigned int), &m);

	err = clEnqueueNDRangeKernel(queue, *kernel, 2, NULL,
		globalThreads, globalLocal,
		0, NULL, event);


	return err;
}


cl_int diag_dtrtri128(
	cl_command_queue queue,
	int M,
	clblasUplo uplo,
	clblasDiag diag,
	cl_mem A,
	size_t offA,
	cl_mem d_dinvA,
	size_t lda,
	int inner_block_size,
	int outer_block_size,
	cl_event *event)
{
	const char *diag_dtrtri_kernel_upper_KernelSource = NULL;
	cl_kernel  *diag_dtrtri_kernel_upper_ClKernel = NULL;
	size_t diag_dtrtri_kernel_upper_KernelBinarySize = 0;
	const unsigned char *diag_dtrtri_kernel_upper_KernelBinary = NULL;

	const char *diag_dtrtri_kernel_lower_KernelSource = NULL;
	cl_kernel  *diag_dtrtri_kernel_lower_ClKernel = NULL;
	size_t diag_dtrtri_kernel_lower_KernelBinarySize = 0;
	const unsigned char *diag_dtrtri_kernel_lower_KernelBinary = NULL;

	cl_int err = 0;

	/*
	This routine is used in dtrsm
	*/


	int nthreads = (M / inner_block_size + (M % inner_block_size != 0)) * inner_block_size;
	unsigned int m = M;

	if (uplo == clblasLower) {


		diag_dtrtri_kernel_lower_KernelSource = diag_dtrtri_lower_128_16_src;
		diag_dtrtri_kernel_lower_ClKernel = &diag_dtrtri_lower_128_16_clKernel;
		diag_dtrtri_kernel_lower_KernelBinary = diag_dtrtri_lower_128_16_bin;
		diag_dtrtri_kernel_lower_KernelBinarySize = diag_dtrtri_lower_128_16_binSize;

		makeKernel(diag_dtrtri_kernel_lower_ClKernel,
			queue,
			diag_dtrtri_kernel_lower_KernelSource,
			TrtriBuildOptions,
			&diag_dtrtri_kernel_lower_KernelBinary,
			&diag_dtrtri_kernel_lower_KernelBinarySize,
			TrtribinBuildOptions);

		int isDiagUnit = (diag == clblasUnit);
		clSetKernelArg(*diag_dtrtri_kernel_lower_ClKernel, 0, sizeof(int), &isDiagUnit);
		clSetKernelArg(*diag_dtrtri_kernel_lower_ClKernel, 1, sizeof(cl_mem), &A);
		clSetKernelArg(*diag_dtrtri_kernel_lower_ClKernel, 2, sizeof(unsigned int), &offA);
		clSetKernelArg(*diag_dtrtri_kernel_lower_ClKernel, 3, sizeof(cl_mem), &d_dinvA);
		clSetKernelArg(*diag_dtrtri_kernel_lower_ClKernel, 4, sizeof(unsigned int), &lda);
		clSetKernelArg(*diag_dtrtri_kernel_lower_ClKernel, 5, sizeof(unsigned int), &m);


		size_t globalThreads[1] = { nthreads };
		size_t globalLocal[1] = { inner_block_size };

		err = clEnqueueNDRangeKernel(queue, *diag_dtrtri_kernel_lower_ClKernel, 1, NULL,
			globalThreads, globalLocal,
			0, NULL, event);

		if (err != CL_SUCCESS) {
			//printf( "kernel -diag_dtrtri_kernel_lower- failed with %d\n", err );
			return err;
		}



		// update the inverse up to the size of BLOCK_SIZE
		for (int i = inner_block_size; i < outer_block_size; i *= 2) {

			switch (i) {
			case 16:
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_16_PART1_L", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_16_PART2_L", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				err = call_kernel_triple_update128(&triple_dgemm_update_128_16_PART1_L_clKernel,
					triple_dgemm_update_128_16_PART1_L_src,
					TrtriBuildOptions,
					(const unsigned char **)&triple_dgemm_update_128_16_PART1_L_bin,
					&triple_dgemm_update_128_16_PART1_L_binSize,
					TrtribinBuildOptions,
					queue,
					A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				err = call_kernel_triple_update128(&triple_dgemm_update_128_16_PART2_L_clKernel,
					triple_dgemm_update_128_16_PART2_L_src,
					TrtriBuildOptions,
					(const unsigned char **)&triple_dgemm_update_128_16_PART2_L_bin,
					&triple_dgemm_update_128_16_PART2_L_binSize,
					TrtribinBuildOptions,
					queue,
					A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				break;

			case 32:
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_32_PART1_L", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_32_PART2_L", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				err = call_kernel_triple_update128(&triple_dgemm_update_128_32_PART1_L_clKernel,
					triple_dgemm_update_128_32_PART1_L_src,
					TrtriBuildOptions,
					(const unsigned char **)&triple_dgemm_update_128_32_PART1_L_bin,
					&triple_dgemm_update_128_32_PART1_L_binSize,
					TrtribinBuildOptions,
					queue,
					A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				err = call_kernel_triple_update128(&triple_dgemm_update_128_32_PART2_L_clKernel,
					triple_dgemm_update_128_32_PART2_L_src,
					TrtriBuildOptions,
					(const unsigned char **)&triple_dgemm_update_128_32_PART2_L_bin,
					&triple_dgemm_update_128_32_PART2_L_binSize,
					TrtribinBuildOptions,
					queue,
					A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				break;

			case 64:
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_64_PART1_L", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_64_PART2_L", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				err = call_kernel_triple_update128(&triple_dgemm_update_128_64_PART1_L_clKernel,
					triple_dgemm_update_128_64_PART1_L_src,
					TrtriBuildOptions,
					(const unsigned char **)&triple_dgemm_update_128_64_PART1_L_bin,
					&triple_dgemm_update_128_64_PART1_L_binSize,
					TrtribinBuildOptions,
					queue,
					A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				err = call_kernel_triple_update128(&triple_dgemm_update_128_64_PART2_L_clKernel,
					triple_dgemm_update_128_64_PART2_L_src,
					TrtriBuildOptions,
					(const unsigned char **)&triple_dgemm_update_128_64_PART2_L_bin,
					&triple_dgemm_update_128_64_PART2_L_binSize,
					TrtribinBuildOptions,
					queue,
					A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				break;

			default:
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_ABOVE64_PART1_L", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_ABOVE64_PART2_L", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_ABOVE64_PART3_L", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				err = call_kernel_triple_update128(&triple_dgemm_update_128_ABOVE64_PART1_L_clKernel,
					triple_dgemm_update_128_ABOVE64_PART1_L_src,
					TrtriBuildOptions,
					(const unsigned char **)&triple_dgemm_update_128_ABOVE64_PART1_L_bin,
					&triple_dgemm_update_128_ABOVE64_PART1_L_binSize,
					TrtribinBuildOptions,
					queue,
					A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				err = call_kernel_triple_update128(&triple_dgemm_update_128_ABOVE64_PART2_L_clKernel,
					triple_dgemm_update_128_ABOVE64_PART2_L_src,
					TrtriBuildOptions,
					(const unsigned char **)&triple_dgemm_update_128_ABOVE64_PART2_L_bin,
					&triple_dgemm_update_128_ABOVE64_PART2_L_binSize,
					TrtribinBuildOptions,
					queue,
					A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				err = call_kernel_triple_update128(&triple_dgemm_update_128_ABOVE64_PART3_L_clKernel,
					triple_dgemm_update_128_ABOVE64_PART3_L_src,
					TrtriBuildOptions,
					(const unsigned char **)&triple_dgemm_update_128_ABOVE64_PART3_L_bin,
					&triple_dgemm_update_128_ABOVE64_PART3_L_binSize,
					TrtribinBuildOptions,
					queue,
					A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				break;

			}
			if (i * 2 >= M) break;
		}

	}
	else {

		diag_dtrtri_kernel_upper_KernelSource = diag_dtrtri_upper_128_16_src;
		diag_dtrtri_kernel_upper_ClKernel = &diag_dtrtri_upper_128_16_clKernel;
		diag_dtrtri_kernel_upper_KernelBinary = diag_dtrtri_upper_128_16_bin;
		diag_dtrtri_kernel_upper_KernelBinarySize = diag_dtrtri_upper_128_16_binSize;

		makeKernel(diag_dtrtri_kernel_upper_ClKernel,
			queue,
			diag_dtrtri_kernel_upper_KernelSource,
			TrtriBuildOptions,
			&diag_dtrtri_kernel_upper_KernelBinary,
			&diag_dtrtri_kernel_upper_KernelBinarySize,
			TrtribinBuildOptions);

		int isDiagUnit = (diag == clblasUnit);
		err = clSetKernelArg(*diag_dtrtri_kernel_upper_ClKernel, 0, sizeof(int), &isDiagUnit);
		CL_CHECK(err);
		err = clSetKernelArg(*diag_dtrtri_kernel_upper_ClKernel, 1, sizeof(cl_mem), &A);
		CL_CHECK(err);
		err = clSetKernelArg(*diag_dtrtri_kernel_upper_ClKernel, 2, sizeof(unsigned int), &offA);
		CL_CHECK(err);
		err = clSetKernelArg(*diag_dtrtri_kernel_upper_ClKernel, 3, sizeof(cl_mem), &d_dinvA);
		CL_CHECK(err);
		err = clSetKernelArg(*diag_dtrtri_kernel_upper_ClKernel, 4, sizeof(unsigned int), &lda);
		CL_CHECK(err);
		err = clSetKernelArg(*diag_dtrtri_kernel_upper_ClKernel, 5, sizeof(unsigned int), &m);
		CL_CHECK(err);

		size_t globalThreads[1] = { nthreads };
		size_t globalLocal[1] = { inner_block_size };

		err = clEnqueueNDRangeKernel(queue, *diag_dtrtri_kernel_upper_ClKernel, 1, NULL,
			globalThreads, globalLocal,
			0, NULL, NULL);
		CL_CHECK(err);
		//err = clFinish(queue);
		//CL_CHECK(err);

		if (err != CL_SUCCESS) {
			//printf( "kernel -diag_dtrtri_kernel_upper- failed with %d\n", err );
			return err;
		}

		//clReleaseKernel(diag_dtrtri_kernel_upper);
		//if (err != CL_SUCCESS) {
		//	return err;
		//}

		// update the inverse up to the size of BLOCK_SIZE

		for (int i = inner_block_size; i < outer_block_size; i *= 2) {

			switch (i) {
			case 16:
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_16_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);

				err = call_kernel_triple_update128(&triple_dgemm_update_128_16_R_clKernel,
					triple_dgemm_update_128_16_R_src,
					TrtriBuildOptions,
					(const unsigned char **)&triple_dgemm_update_128_16_R_bin,
					&triple_dgemm_update_128_16_R_binSize,
					TrtribinBuildOptions,
					queue,
					A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				//err = clFinish(queue);
				//CL_CHECK(err);
				break;

			case 32:
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_32_PART1_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_32_PART2_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);

				err = call_kernel_triple_update128(&triple_dgemm_update_128_32_PART1_R_clKernel,
					triple_dgemm_update_128_32_PART1_R_src,
					TrtriBuildOptions,
					(const unsigned char **)&triple_dgemm_update_128_32_PART1_R_bin,
					&triple_dgemm_update_128_32_PART1_R_binSize,
					TrtribinBuildOptions,
					queue,
					A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				err = call_kernel_triple_update128(&triple_dgemm_update_128_32_PART2_R_clKernel,
					triple_dgemm_update_128_32_PART2_R_src,
					TrtriBuildOptions,
					(const unsigned char **)&triple_dgemm_update_128_32_PART2_R_bin,
					&triple_dgemm_update_128_32_PART2_R_binSize,
					TrtribinBuildOptions,
					queue,
					A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);

				break;

			case 64:
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_64_PART1_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_64_PART2_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);

				err = call_kernel_triple_update128(&triple_dgemm_update_128_64_PART1_R_clKernel,
					triple_dgemm_update_128_64_PART1_R_src,
					TrtriBuildOptions,
					(const unsigned char **)&triple_dgemm_update_128_64_PART1_R_bin,
					&triple_dgemm_update_128_64_PART1_R_binSize,
					TrtribinBuildOptions,
					queue,
					A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				err = call_kernel_triple_update128(&triple_dgemm_update_128_64_PART2_R_clKernel,
					triple_dgemm_update_128_64_PART2_R_src,
					TrtriBuildOptions,
					(const unsigned char **)&triple_dgemm_update_128_64_PART2_R_bin,
					&triple_dgemm_update_128_64_PART2_R_binSize,
					TrtribinBuildOptions,
					queue,
					A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);

				break;

			default:
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_ABOVE64_PART1_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_ABOVE64_PART2_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				//CALL_KERNEL_TRIPLE_UPDATE("TRIPLE_DGEMM_UPDATE_ABOVE64_PART3_R", prg, queue, A, offA, d_dinvA, i, lda, M, event);
				err = call_kernel_triple_update128(&triple_dgemm_update_128_ABOVE64_PART1_R_clKernel,
					triple_dgemm_update_128_ABOVE64_PART1_R_src,
					TrtriBuildOptions,
					(const unsigned char **)&triple_dgemm_update_128_ABOVE64_PART1_R_bin,
					&triple_dgemm_update_128_ABOVE64_PART1_R_binSize,
					TrtribinBuildOptions,
					queue,
					A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				err = call_kernel_triple_update128(&triple_dgemm_update_128_ABOVE64_PART2_R_clKernel,
					triple_dgemm_update_128_ABOVE64_PART2_R_src,
					TrtriBuildOptions,
					(const unsigned char **)&triple_dgemm_update_128_ABOVE64_PART2_R_bin,
					&triple_dgemm_update_128_ABOVE64_PART2_R_binSize,
					TrtribinBuildOptions,
					queue,
					A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				err = call_kernel_triple_update128(&triple_dgemm_update_128_ABOVE64_PART3_R_clKernel,
					triple_dgemm_update_128_ABOVE64_PART3_R_src,
					TrtriBuildOptions,
					(const unsigned char **)&triple_dgemm_update_128_ABOVE64_PART3_R_bin,
					&triple_dgemm_update_128_ABOVE64_PART3_R_binSize,
					TrtribinBuildOptions,
					queue,
					A, offA, d_dinvA, i, lda, M, event);
				CL_CHECK(err);
				break;
			}

			if (i * 2 >= M) break;
		}

	}

	return err;

}

static clblasStatus gpu_dtrsm128(
	clblasOrder order,
	clblasSide side,
	clblasUplo uplo,
	clblasTranspose transA,
	clblasDiag diag,
	size_t M,
	size_t N,
	double alpha,
	const cl_mem A,
	size_t offA,
	size_t ldA,
	cl_mem B,
	size_t offB,
	size_t ldB,
	cl_uint numCommandQueues,
	cl_command_queue *commandQueues,
	cl_uint numEventsInWaitList,
	const cl_event *eventWaitList,
	cl_event *events,
	bool &specialCaseHandled)
{
	if (order != clblasColumnMajor)
		return clblasNotImplemented;


	int inner_block_size = 16; // inner blocking size, <=32
	int outer_block_size = 128;// outer blocking size, >BLOCK_SIZE

	cl_int err = 0;

	int i;
	cl_context context;
	err = getQueueContext(commandQueues[0], &context);
	CL_CHECK(err);

	/* quick return on wrong size */
	if (M <= 0 || N <= 0)
		return clblasInvalidDim;

	double neg_one = -1.0;
	double one = 1.0;
	double zero = 0.0;

	// Helper to compute pass the 3 arguments describing a (sub)-matrix to clblasDgemm
#define _(M,i,j)       M    , (off##M + ((i)+(j)*ld##M) ) , ld##M

	cl_mem InvA = 0;
	cl_mem X = 0;
	// X of size mxn  will contain the result
	size_t ldX = M;
	size_t offX = 0; //must be 0: needed by the _(X,i,j) macro
	size_t size_X = N*ldX * sizeof(double);
	X = clCreateBuffer(context, CL_MEM_READ_WRITE, size_X, NULL, &err);
	CL_CHECK(err);
	err = clearBuffer(commandQueues[0], X, size_X);
	CL_CHECK(err);

	if (side == clblasLeft)
	{
		// side=L
		/* invert the diagonals
		* Allocate device memory for the inverted diagonal blocks, size=m*nb
		*/
		size_t ldInvA = outer_block_size;
		size_t offInvA = 0; //must be 0: needed by the _(X,i,j) macro
		size_t size_InvA = ldInvA * BLOCKS(M, outer_block_size) * outer_block_size *sizeof(double);
		InvA = clCreateBuffer(context, CL_MEM_READ_WRITE, size_InvA, NULL, &err);

		CL_CHECK(err);
		err = clearBuffer(commandQueues[0], InvA, size_InvA);
		CL_CHECK(err);

		err = diag_dtrtri128(commandQueues[0], M, uplo, diag, A, offA, InvA, ldA, inner_block_size, outer_block_size, events);
		CL_CHECK(err);

		//
		// Helper for C = alpha * transp(A) * B + beta * C
		//
		// In the calls below:
		//   - the 1st matrix shall be either A or InvA transposed according to transA.
		//   - the 2nd and 3rd matrices are either B and X
		//
#define DGEMM_LEFT(m, n, k, alpha, A,  B, beta,  C) \
    do { \
        err = clblasDgemm(clblasColumnMajor, transA, clblasNoTrans , m, n, k, alpha, A, B, beta, C , 1, commandQueues, 0, NULL, events ) ; \
        CL_CHECK(err); \
	    } while(0)


		if (transA == clblasNoTrans)
		{
			/* the non-transpose case */
			if (uplo == clblasLower)
			{

				/* the lower case */
				/* handle the first block seperately with alpha */

				int mm = min(outer_block_size, (int)M);
				DGEMM_LEFT(mm, N, mm, alpha, _(InvA, 0, 0), _(B, 0, 0), zero, _(X, 0, 0));

				if (outer_block_size < M)
				{
					DGEMM_LEFT(M - outer_block_size, N, outer_block_size, neg_one, _(A, outer_block_size, 0), _(X, 0, 0), alpha, _(B, outer_block_size, 0));

					/* the rest blocks */
					for (i = outer_block_size; i < M; i += outer_block_size) {
						mm = min((int)M - i, outer_block_size);
						DGEMM_LEFT(mm, N, mm, one, _(InvA, 0, i), _(B, i, 0), zero, _(X, i, 0));

						if (i + outer_block_size >= M)
							break;

						DGEMM_LEFT(M - i - outer_block_size, N, outer_block_size, neg_one, _(A, i + outer_block_size, i), _(X, i, 0), one, _(B, i + outer_block_size, 0));
					}

					//check_last_error() ;
				}


			}
			else // if ( uplo == clblasUpper)
			{
				/* the upper case */
				/* handle the first block seperately with alpha */
				int mm = (M % outer_block_size == 0) ? outer_block_size : (M % outer_block_size);
				i = M - mm;
				DGEMM_LEFT(mm, N, mm, alpha, _(InvA, 0, i), _(B, i, 0), zero, _(X, i, 0));

				if (i - outer_block_size >= 0)
				{
					DGEMM_LEFT(i, N, mm, neg_one, _(A, 0, i), _(X, i, 0), alpha, _(B, 0, 0));

					/* the rest blocks */
					for (i = M - mm - outer_block_size; i >= 0; i -= outer_block_size) {
						DGEMM_LEFT(outer_block_size, N, outer_block_size, one, _(InvA, 0, i), _(B, i, 0), zero, _(X, i, 0));

						if (i - outer_block_size < 0)
							break;

						DGEMM_LEFT(i, N, outer_block_size, neg_one, _(A, 0, i), _(X, i, 0), one, _(B, 0, 0));
					}
				}
			}
		}
		else
		{
			/* the transpose case */
			if (uplo == clblasLower)
			{
				/* the lower case */
				/* handle the first block seperately with alpha */

				int mm = (M % outer_block_size == 0) ? outer_block_size : (M % outer_block_size);
				i = M - mm;
				DGEMM_LEFT(mm, N, mm, alpha, _(InvA, 0, i), _(B, i, 0), zero, _(X, i, 0));

				if (i - outer_block_size >= 0)
				{
					DGEMM_LEFT(i, N, mm, neg_one, _(A, i, 0), _(X, i, 0), alpha, _(B, 0, 0));

					/* the rest blocks */
					for (i = M - mm - outer_block_size; i >= 0; i -= outer_block_size) {
						DGEMM_LEFT(outer_block_size, N, outer_block_size, one, _(InvA, 0, i), _(B, i, 0), zero, _(X, i, 0));

						if (i - outer_block_size < 0)
							break;

						DGEMM_LEFT(i, N, outer_block_size, neg_one, _(A, i, 0), _(X, i, 0), one, _(B, 0, 0));
					}
				}
			}
			else
			{
				/* the upper case */
				/* handle the first block seperately with alpha */
				int mm = min(outer_block_size, (int)M);
				DGEMM_LEFT(mm, N, mm, alpha, _(InvA, 0, 0), _(B, 0, 0), zero, _(X, 0, 0));

				if (outer_block_size < M)
				{

					DGEMM_LEFT(M - outer_block_size, N, outer_block_size, neg_one, _(A, 0, outer_block_size), _(X, 0, 0), alpha, _(B, outer_block_size, 0));

					/* the rest blocks */
					for (i = outer_block_size; i < M; i += outer_block_size) {
						mm = min((int)M - i, outer_block_size);
						DGEMM_LEFT(mm, N, mm, one, _(InvA, 0, i), _(B, i, 0), zero, _(X, i, 0));

						if (i + outer_block_size >= M)
							break;

						DGEMM_LEFT(M - i - outer_block_size, N, outer_block_size, neg_one, _(A, i, i + outer_block_size), _(X, i, 0), one, _(B, i + outer_block_size, 0));
					}
				}
			}
		}
	}
	else
	{
		//
		// Helper for C = alpha * B * A + beta * C
		//
		// In the calls below
		//  - the 2nd matrix shall be either A or InvA transposed according to transA
		//  - the 1st and 3rd matrices are either B and X
		//
#define DGEMM_RIGHT(m,n,k, alpha,  B, A, beta, C )   \
    do { \
      err = clblasDgemm(clblasColumnMajor, clblasNoTrans, transA , m, n, k, alpha, B, A, beta, C , 1, commandQueues, 0, NULL, events ) ; \
      CL_CHECK(err); \
	    } while(0)


		// side=R
		/* invert the diagonals
		* Allocate device memory for the inverted diagonal blocks, size=n*BLOCK_SIZE
		*/

		/* invert the diagonals
		* Allocate device memory for the inverted diagonal blocks, size=m*nb
		*/
		size_t ldInvA = outer_block_size;
		size_t offInvA = 0; //must be 0: needed by the _(X,i,j) macro
		size_t size_InvA = ldInvA * BLOCKS(N, outer_block_size) * outer_block_size *sizeof(double);
		InvA = clCreateBuffer(context, CL_MEM_READ_WRITE, size_InvA, NULL, &err);
		CL_CHECK(err);
		err = clearBuffer(commandQueues[0], InvA, size_InvA);
		CL_CHECK(err);

		err = diag_dtrtri128(commandQueues[0], N, uplo, diag, A, offA, InvA, ldA, inner_block_size, outer_block_size, events);
		CL_CHECK(err);


		if (transA == clblasNoTrans)
		{
			/* the non-transpose case */
			if (uplo == clblasLower)
			{
				/* the lower case */
				/* handle the first block seperately with alpha */

				int nn = (N % outer_block_size == 0) ? outer_block_size : (N % outer_block_size);
				i = N - nn;
				DGEMM_RIGHT(M, nn, nn, alpha, _(B, 0, i), _(InvA, 0, i), zero, _(X, 0, i));

				if (i - outer_block_size >= 0)
				{

					DGEMM_RIGHT(M, i, nn, neg_one, _(X, 0, i), _(A, i, 0), alpha, _(B, 0, 0));

					/* the rest blocks */
					for (i = N - nn - outer_block_size; i >= 0; i -= outer_block_size) {
						DGEMM_RIGHT(M, outer_block_size, outer_block_size, one, _(B, 0, i), _(InvA, 0, i), zero, _(X, 0, i));

						if (i - outer_block_size < 0)
							break;

						DGEMM_RIGHT(M, i, outer_block_size, neg_one, _(X, 0, i), _(A, i, 0), one, _(B, 0, 0));
					}
				}
			}
			else
			{
				/* the upper case */
				/* handle the first block seperately with alpha */
				int nn = min(outer_block_size, (int)N);
				DGEMM_RIGHT(M, nn, nn, alpha, _(B, 0, 0), _(InvA, 0, 0), zero, _(X, 0, 0));

				if (outer_block_size < N)
				{

					DGEMM_RIGHT(M, N - outer_block_size, outer_block_size, neg_one, _(X, 0, 0), _(A, 0, outer_block_size), alpha, _(B, 0, outer_block_size));

					/* the rest blocks */
					for (i = outer_block_size; i < N; i += outer_block_size) {
						nn = min(outer_block_size, (int)N - i);
						DGEMM_RIGHT(M, nn, nn, one, _(B, 0, i), _(InvA, 0, i), zero, _(X, 0, i));

						if (i + outer_block_size >= N)
							break;

						DGEMM_RIGHT(M, N - i - outer_block_size, outer_block_size, neg_one, _(X, 0, i), _(A, i, i + outer_block_size), one, _(B, 0, i + outer_block_size));
					}
				}
			}
		}
		else
		{

			/* the transpose case */
			if (uplo == clblasLower)
			{
				/* the lower case */
				/* handle the first block seperately with alpha */

				int nn = min(outer_block_size, (int)N);
				DGEMM_RIGHT(M, nn, nn, alpha, _(B, 0, 0), _(InvA, 0, 0), zero, _(X, 0, 0));

				if (outer_block_size < N)
				{

					DGEMM_RIGHT(M, N - outer_block_size, outer_block_size, neg_one, _(X, 0, 0), _(A, outer_block_size, 0), alpha, _(B, 0, outer_block_size));

					/* the rest blocks */
					for (i = outer_block_size; i < N; i += outer_block_size) {
						nn = min(outer_block_size, (int)N - i);
						DGEMM_RIGHT(M, nn, nn, one, _(B, 0, i), _(InvA, 0, i), zero, _(X, 0, i));

						if (i + outer_block_size >= N)
							break;

						DGEMM_RIGHT(M, N - i - outer_block_size, outer_block_size, neg_one, _(X, 0, i), _(A, outer_block_size + i, i), one, _(B, 0, i + outer_block_size));
					}
				}
			}
			else
			{
				/* the upper case */
				/* handle the first block seperately with alpha */
				int nn = (N % outer_block_size == 0) ? outer_block_size : (N % outer_block_size);
				i = N - nn;
				DGEMM_RIGHT(M, nn, nn, alpha, _(B, 0, i), _(InvA, 0, i), zero, _(X, 0, i));

				if (i - outer_block_size >= 0)
				{

					DGEMM_RIGHT(M, i, nn, neg_one, _(X, 0, i), _(A, 0, i), alpha, _(B, 0, 0));

					/* the rest blocks */
					for (i = N - nn - outer_block_size; i >= 0; i -= outer_block_size) {
						DGEMM_RIGHT(M, outer_block_size, outer_block_size, one, _(B, 0, i), _(InvA, 0, i), zero, _(X, 0, i));

						if (i - outer_block_size < 0)
							break;

						DGEMM_RIGHT(M, i, outer_block_size, neg_one, _(X, 0, i), _(A, 0, i), one, _(B, 0, 0));
					}
				}
			}
		}
	}

	// Copy X(m,n) to B(m,n)
  {
	  size_t src_origin[3] = { 0, 0, 0 };
	  size_t dst_origin[3] = { offB*sizeof(double), 0, 0 };
	  size_t region[3] = { M*sizeof(double), N, 1 };


	  err = clEnqueueCopyBufferRect(commandQueues[0],
		  X,
		  B,
		  src_origin,
		  dst_origin,
		  region,
		  ldX*sizeof(double), 0,
		  ldB*sizeof(double), 0,
		  0, NULL,
		  events);
	  CL_CHECK(err);

	  clReleaseMemObject(InvA);
	  clReleaseMemObject(X);

	  specialCaseHandled = true;
	  return clblasSuccess;
  }

	return clblasNotImplemented;
}

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

	if ((retCode = checkMemObjects(A, B, NULL, false, A_MAT_ERRSET, B_MAT_ERRSET, END_ERRSET))) {
		return retCode;
	}
	msize = (side == clblasLeft) ? M : N;

	if ((retCode = checkMatrixSizes(kargs->dtype, order, transA, msize, msize,
		A, offA, lda, A_MAT_ERRSET))) {
		return retCode;
	}
	if ((retCode = checkMatrixSizes(kargs->dtype, order, clblasNoTrans, M, N,
		B, offB, ldb, B_MAT_ERRSET))) {
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

extern "C"
clblasStatus
clblasStrsm(
    clblasOrder order,
    clblasSide side,
    clblasUplo uplo,
    clblasTranspose transA,
    clblasDiag diag,
    size_t M,
    size_t N,
    cl_float alpha,
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
   CHECK_QUEUES(numCommandQueues, commandQueues);
   CHECK_EVENTS(numEventsInWaitList, eventWaitList);

   if ( numCommandQueues>1 )
   {
       numCommandQueues = 1 ;  // No support for multi-device (yet)
   }

   cl_command_queue queue = commandQueues[0];

   clblasStrsmFunctor::Args args(order,
                                 side,
                                 uplo,
                                 transA,
                                 diag,
                                 M, N,
                                 alpha,
                                 A, offA, lda,
                                 B, offB, ldb,
                                 queue,
                                 numEventsInWaitList,
                                 eventWaitList,
                                 events);


#if FORCE_COLUMN_MAJOR
   force_trsm_column_major(args);
#endif

   clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);

   clblasStrsmFunctor * functor = fselector->select_strsm_specific(args);

   clblasStatus res = functor->execute(args);

   functor->release();

   return res;
}

extern "C"
clblasStatus
clblasDtrsm(
    clblasOrder order,
    clblasSide side,
    clblasUplo uplo,
    clblasTranspose transA,
    clblasDiag diag,
    size_t M,
    size_t N,
    cl_double alpha,
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
#if 0
   CHECK_QUEUES(numCommandQueues, commandQueues);
   CHECK_EVENTS(numEventsInWaitList, eventWaitList);

   if ( numCommandQueues>1 )
   {
       numCommandQueues = 1 ;  // No support for multi-device (yet)
   }

   cl_command_queue queue = commandQueues[0];

   clblasDtrsmFunctor::Args args(order,
                                 side,
                                 uplo,
                                 transA,
                                 diag,
                                 M, N,
                                 alpha,
                                 A, offA, lda,
                                 B, offB, ldb,
                                 queue,
                                 numEventsInWaitList,
                                 eventWaitList,
                                 events);


   clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);

   clblasDtrsmFunctor * functor = fselector->select_dtrsm_specific(args);

   clblasStatus res = functor->execute(args);

   functor->release();

   return res;

#else
	bool specialCaseHandled = false;

	//outer block size = 192
	//inner block size = 12
	clblasStatus SpecialCaseStatus;
	SpecialCaseStatus = gpu_dtrsm192(order,
		side,
		uplo,
		transA,
		diag,
		M, N,
		alpha,
		A, offA, lda,
		B, offB, ldb,
		numCommandQueues, commandQueues,
		numEventsInWaitList,
		eventWaitList,
		events,
		specialCaseHandled);

	if (specialCaseHandled)
		return SpecialCaseStatus;

	SpecialCaseStatus = gpu_dtrsm128(order,
		side,
		uplo,
		transA,
		diag,
		M, N,
		alpha,
		A, offA, lda,
		B, offB, ldb,
		numCommandQueues, commandQueues,
		numEventsInWaitList,
		eventWaitList,
		events,
		specialCaseHandled);

	if (specialCaseHandled)
		return SpecialCaseStatus;


   CLBlasKargs kargs;

   memset(&kargs, 0, sizeof(kargs));
   kargs.dtype = TYPE_DOUBLE;
   kargs.alpha.argDouble = alpha;

   return doTrsm(&kargs,
	   order,
	   side,
	   uplo,
	   transA,
	   diag,
	   M, N,
	   A, offA, lda,
	   B, offB, ldb,
	   numCommandQueues, commandQueues,
	   numEventsInWaitList,
	   eventWaitList,
	   events);
#endif
}

extern "C"
clblasStatus
clblasCtrsm(
    clblasOrder order,
    clblasSide side,
    clblasUplo uplo,
    clblasTranspose transA,
    clblasDiag diag,
    size_t M,
    size_t N,
    FloatComplex alpha,
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
   CHECK_QUEUES(numCommandQueues, commandQueues);
   CHECK_EVENTS(numEventsInWaitList, eventWaitList);

   if ( numCommandQueues>1 )
   {
       numCommandQueues = 1 ;  // No support for multi-device (yet)
   }

   cl_command_queue queue = commandQueues[0];

   clblasCtrsmFunctor::Args args(order,
                                 side,
                                 uplo,
                                 transA,
                                 diag,
                                 M, N,
                                 alpha,
                                 A, offA, lda,
                                 B, offB, ldb,
                                 queue,
                                 numEventsInWaitList,
                                 eventWaitList,
                                 events);


#if FORCE_COLUMN_MAJOR
   force_trsm_column_major(args);
#endif

   clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);

   clblasCtrsmFunctor * functor = fselector->select_ctrsm_specific(args);

   clblasStatus res = functor->execute(args);

   functor->release();

   return res;
}

extern "C"
clblasStatus
clblasZtrsm(
    clblasOrder order,
    clblasSide side,
    clblasUplo uplo,
    clblasTranspose transA,
    clblasDiag diag,
    size_t M,
    size_t N,
    DoubleComplex alpha,
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
   CHECK_QUEUES(numCommandQueues, commandQueues);
   CHECK_EVENTS(numEventsInWaitList, eventWaitList);

   if ( numCommandQueues>1 )
   {
       numCommandQueues = 1 ;  // No support for multi-device (yet)
   }

   cl_command_queue queue = commandQueues[0];

   clblasZtrsmFunctor::Args args(order,
                                 side,
                                 uplo,
                                 transA,
                                 diag,
                                 M, N,
                                 alpha,
                                 A, offA, lda,
                                 B, offB, ldb,
                                 queue,
                                 numEventsInWaitList,
                                 eventWaitList,
                                 events);


#if FORCE_COLUMN_MAJOR
   force_trsm_column_major(args);
#endif

   clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);

   clblasZtrsmFunctor * functor = fselector->select_ztrsm_specific(args);

   clblasStatus res = functor->execute(args);

   functor->release();

   return res;
}
