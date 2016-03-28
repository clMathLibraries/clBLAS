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

#include <map>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <clBLAS.h>
#include "mutex.h"
#include "AutoGemmIncludes/AutoGemmKernelSelection.h"
#include "GemmSpecialCases.h"

 #include <functor.h>
// #include <functor_selector.h>
#include "xgemm.h"

#ifdef _WIN32
//#include <thread>
#else
#include <pthread.h>
#endif

/******************************************************************************
 * Row major -> column major
 *****************************************************************************/
static void force_gemm_column_major(
  clblasOrder &order,
  clblasTranspose &transA,
  clblasTranspose &transB,
  cl_uint &M,
  cl_uint &N,
  cl_uint &offA,
  cl_uint &offB,
  cl_uint &lda,
  cl_uint &ldb,
  cl_mem &A,
  cl_mem &B )
{
  if (order == clblasRowMajor) {
    std::swap(transA , transB);
    std::swap(M      , N);
    std::swap(offA   , offB);
    std::swap(lda    , ldb);
    std::swap(A      , B);
    order = clblasColumnMajor;
  }
}

/******************************************************************************
 * Check OpenCL Errors
 *****************************************************************************/
#define CL_CHECK(RET) \
  if(RET != CL_SUCCESS) { \
    printf("OpenCL error %i on line %u of %s\n", RET, __LINE__, __FILE__); \
    assert(false); \
  }
#define returnIfErr(err) \
	if (err != CL_SUCCESS)\
		return static_cast<clblasStatus>(err);

const static unsigned int numGemmKernelArgs = 14;
void *gemmKernelArgs[numGemmKernelArgs];
size_t gemmKernelArgSizes[numGemmKernelArgs];


/******************************************************************************
 * Is beta zero for optimization
 *****************************************************************************/
template <typename Precision>
bool isZero(Precision value);
template<>
bool isZero<float>( float value ) {
  return value == 0;
};
template<>
bool isZero<double>( double value ) {
  return value == 0;
};
template<>
bool isZero<FloatComplex>( FloatComplex value ) {
  return CREAL(value) == 0 && CIMAG(value) == 0;
};
template<>
bool isZero<DoubleComplex>( DoubleComplex value ) {
  return CREAL(value) == 0 && CIMAG(value) == 0;
};

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

typedef struct kernel_map_key_ {
  cl_context context; // address of context
  cl_device_id device; // address of device
  const char *kernelSource; // address of kernel source
} kernel_map_key;

bool operator<(const kernel_map_key & l, const kernel_map_key & r) {
  if (l.context < r.context) {
    return true;
  } else if (r.context < l.context) {
    return false;
  }
  if (l.device < r.device) {
    return true;
  } else if (r.device < l.device) {
    return false;
  }
  if (l.kernelSource < r.kernelSource) {
    return true;
  } else if (r.kernelSource < l.kernelSource) {
    return false;
  }
  return false;
}


/******************************************************************************
 * Make Gemm Kernel
 *****************************************************************************/
//FIXME: This function should be returning an error.
void makeGemmKernel(
  cl_kernel *clKernel, // ignored as input; returns as output only
  cl_command_queue clQueue,
  const char *kernelSource,
  const char *sourceBuildOptions,
  const unsigned char **kernelBinary,
  size_t *kernelBinarySize,
  const char *binaryBuildOptions)
{
  typedef std::map<kernel_map_key, cl_kernel> kernel_map_t;
  #if defined( _WIN32 )
  __declspec( thread ) static kernel_map_t *kernel_map = 0;
#else
  __thread static kernel_map_t *kernel_map = 0;
#endif
  if (!kernel_map) {
    kernel_map = new kernel_map_t();
  }

  cl_context clContext;
  cl_device_id clDevice;
  cl_int err;

  err = clGetCommandQueueInfo( clQueue, CL_QUEUE_CONTEXT, sizeof(clContext), &clContext, NULL);
  CL_CHECK(err)
  err = clGetCommandQueueInfo( clQueue, CL_QUEUE_DEVICE, sizeof(clDevice), &clDevice, NULL);
  CL_CHECK(err)

  // is kernel already compiled?
  kernel_map_key key;
  key.kernelSource = kernelSource;
  key.context = clContext;
  key.device = clDevice;
  kernel_map_t::iterator idx = kernel_map->find(key);
  if (idx == kernel_map->end()) {
    *clKernel = NULL;
  } else {
    *clKernel = idx->second;
    return;
  }

  if (true /*!*clKernel*/) { // since kernel wasn't found in map
    // kernel has not been built, so build it (from binary, preferably)
    cl_program clProgram;
    cl_int clBinaryStatus;
    if (*kernelBinary) {
#ifdef AUTOGEMM_PRINT_DEBUG
      printf("makeGemmKernel: pre-compiled binary found: %llu bytes\n", *kernelBinarySize);
      printf("makeGemmKernel: Creating program from binary\n");
#endif
      clProgram = clCreateProgramWithBinary(
        clContext,
        1, &clDevice,
        kernelBinarySize, kernelBinary,
        &clBinaryStatus, &err );
#ifdef AUTOGEMM_PRINT_DEBUG
      if (err != CL_SUCCESS) {
          printf("makeGemmKernel: Failed to create program with binary\n");
      }
#endif
      err = clBuildProgram(
        clProgram,
        1, &clDevice,
        binaryBuildOptions, NULL, NULL );
#ifdef AUTOGEMM_PRINT_DEBUG
      if (err != CL_SUCCESS) {
          printf("makeGemmKernel: Failed to build program from binary\n");
      }
#endif
    }

    if (!*kernelBinary || err != CL_SUCCESS) {
#ifdef AUTOGEMM_PRINT_DEBUG
      printf("makeGemmKernel: Creating program from source\n");
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

#ifdef AUTOGEMM_PRINT_DEBUG
    printf("makeGemmKernel now built; returning.\n");
#endif

    //put kernel in map
    (*kernel_map)[key] = *clKernel;
  }
  return;
}

/******************************************************************************
 * Enqueue Gemm Kernel
 *****************************************************************************/
 cl_int enqueueGemmKernel(
   cl_command_queue clQueue,
   cl_kernel clKernel,
   void **kernelArgs,
   size_t *kernelArgSizes,
   unsigned int numKernelArgs,
   const size_t *globalWorkSize,
   const size_t *localWorkSize,
   cl_uint numEventsInWaitList,
   const cl_event *eventWaitList,
   cl_event *clEvent)
 {
   for (unsigned int i = 0; i < numKernelArgs; i++) {
	   cl_int err = clSetKernelArg(clKernel, i, kernelArgSizes[i], kernelArgs[i]);
	   if (err != CL_SUCCESS)
		   return err;
   }
   /*printf("global={%llu, %llu} local={%llu, %llu}\n",
     globalWorkSize[0], globalWorkSize[1],
     localWorkSize[0], localWorkSize[1] );*/
   cl_uint err = clEnqueueNDRangeKernel(clQueue, clKernel,
	   2, NULL, globalWorkSize, localWorkSize,
	   numEventsInWaitList, eventWaitList, clEvent);
   if (err != CL_SUCCESS)
	   return err;

   return CL_SUCCESS;
 }


/******************************************************************************
 * get precision string
 *****************************************************************************/
template<typename Precision>
char * getPrecision();
template<> char * getPrecision<float>() { return "s"; }
template<> char * getPrecision<double>() { return "d"; }
template<> char * getPrecision<FloatComplex>()  { return "c"; }
template<> char * getPrecision<DoubleComplex>() { return "z"; }


/******************************************************************************
 * convert ConjTrans -> Trans for real
 *****************************************************************************/
template<typename Precision>
clblasTranspose correctTranspose(clblasTranspose trans);
template<> clblasTranspose correctTranspose<float>( clblasTranspose trans)  { return (trans==clblasConjTrans) ? clblasTrans : trans; }
template<> clblasTranspose correctTranspose<double>( clblasTranspose trans) { return (trans==clblasConjTrans) ? clblasTrans : trans; }
template<> clblasTranspose correctTranspose<FloatComplex>( clblasTranspose trans)  { return trans; }
template<> clblasTranspose correctTranspose<DoubleComplex>( clblasTranspose trans) { return trans; }


/******************************************************************************
 * templated Gemm
 *****************************************************************************/
template<typename Precision>
clblasStatus
clblasGemm(
    clblasOrder order,
    clblasTranspose transA,
    clblasTranspose transB,
    size_t iM, size_t iN, size_t iK,
    Precision alpha,
    const cl_mem iA, size_t iOffA, size_t iLda,
    const cl_mem iB, size_t iOffB, size_t iLdb,
    Precision beta,
    cl_mem C, size_t iOffC,  size_t iLdc,
    cl_uint numCommandQueues,
    cl_command_queue *commandQueues,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{


  // cast types to opencl types
  cl_mem A = iA;
  cl_mem B = iB;
  cl_uint M = static_cast<cl_uint>( iM );
  cl_uint N = static_cast<cl_uint>( iN );
  cl_uint K = static_cast<cl_uint>( iK );
  cl_uint offA = static_cast<cl_uint>( iOffA );
  cl_uint offB = static_cast<cl_uint>( iOffB );
  cl_uint offC = static_cast<cl_uint>( iOffC );
  cl_uint lda = static_cast<cl_uint>( iLda );
  cl_uint ldb = static_cast<cl_uint>( iLdb );
  cl_uint ldc = static_cast<cl_uint>( iLdc );

  transA = correctTranspose<Precision>(transA);
  transB = correctTranspose<Precision>(transB);
  // if debug build, validate input
  // CHECK_QUEUES(numCommandQueues, commandQueues);
  // CHECK_EVENTS(numEventsInWaitList, eventWaitList);
  // CHECK_MATRIX_A(Precision, order, transA, A, M, K, offA, lda);
  // CHECK_MATRIX_B(Precision, order, transB, B, K, N, offB, ldb);
  // CHECK_MATRIX_C(Precision, order, clblasNoTrans, C, M, N, offC, ldc);
  force_gemm_column_major( order, transA, transB,
    M, N, offA, offB, lda, ldb, A, B );



/******************************************************************************
 * Handle Special Cases
 *
 * 1) sgemm NT where lda, ldb are big multiples of 1024 starting from 4096
 *
 * 2) sgemm NT where M and N are within middle range
 * and are mod32 but not mod96 or mod64
 *
 *****************************************************************************/

  bool specialCaseHandled = false;

  clblasStatus SpecialCaseStatus = GemmSpecialCases<Precision>(order,
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
	  return SpecialCaseStatus;


/******************************************************************************
 * Optimal num elements per thread
 *****************************************************************************/
  cl_int err;
  cl_device_id clDevice;
  err = clGetCommandQueueInfo( commandQueues[0], CL_QUEUE_DEVICE, sizeof(clDevice), &clDevice, NULL);
  //CL_CHECK(err)
  returnIfErr(err);

  cl_uint clDeviceNumCUs;
  err = clGetDeviceInfo( clDevice, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(clDeviceNumCUs), &clDeviceNumCUs, NULL);
  //CL_CHECK(err)
  returnIfErr(err);
  unsigned int deviceIdealNumThreads = (8 /*waves per CU*/)*(64 /*threads per wave*/)*clDeviceNumCUs;
  float optimalNumElementsPerThread = ((float)M*N) / deviceIdealNumThreads;
  //optimalNumElementsPerThread = 32;
  bool betaNonZero = !isZero(beta);

#ifdef AUTOGEMM_PRINT_DEBUG
  printf("%sgemm_%3s_%s%s_B%u_%llux%llux%llu\n",
      getPrecision<Precision>(),
      order==clblasColumnMajor ? "Col" : "Row",
      transA==clblasNoTrans ? "N" : transA==clblasTrans ? "T" : "C",
      transB==clblasNoTrans ? "N" : transB==clblasTrans ? "T" : "C",
      betaNonZero ? 1 : 0,
      iM, iN, iK );
#endif

/******************************************************************************
 * Select kernel
 *****************************************************************************/
  const char *tileKernelSource   = NULL;
  const char *rowKernelSource    = NULL;
  const char *colKernelSource    = NULL;
  const char *cornerKernelSource = NULL;
  const char *sourceBuildOptions = NULL;
  const unsigned char *tileKernelBinary   = NULL;
  const unsigned char *rowKernelBinary    = NULL;
  const unsigned char *colKernelBinary    = NULL;
  const unsigned char *cornerKernelBinary = NULL;
  size_t *tileKernelBinarySize   = 0;
  size_t *rowKernelBinarySize    = 0;
  size_t *colKernelBinarySize    = 0;
  size_t *cornerKernelBinarySize = 0;
  const char *binaryBuildOptions = NULL;
  cl_kernel  *tileClKernelDummy       = NULL; // no longer used; broke thread safety
  cl_kernel  *rowClKernelDummy        = NULL; // no longer used; broke thread safety
  cl_kernel  *colClKernelDummy        = NULL; // no longer used; broke thread safety
  cl_kernel  *cornerClKernelDummy     = NULL; // no longer used; broke thread safety
  unsigned int workGroupNumRows;
  unsigned int workGroupNumCols;
  unsigned int microTileNumRows;
  unsigned int microTileNumCols;
  unsigned int unroll;
  gemmSelectKernel<Precision>(
    order, transA, transB,
    iM, iN, iK,
    betaNonZero,
    optimalNumElementsPerThread,
    &tileKernelSource,
    &rowKernelSource,
    &colKernelSource,
    &cornerKernelSource,
    &sourceBuildOptions,
    &tileKernelBinary,
    &rowKernelBinary,
    &colKernelBinary,
    &cornerKernelBinary,
    &tileKernelBinarySize,
    &rowKernelBinarySize,
    &colKernelBinarySize,
    &cornerKernelBinarySize,
    &binaryBuildOptions,
    &tileClKernelDummy,
    &rowClKernelDummy,
    &colClKernelDummy,
    &cornerClKernelDummy,
    &workGroupNumRows,
    &workGroupNumCols,
    &microTileNumRows,
    &microTileNumCols,
    &unroll);
  // make sure gemmSelectKernel found a valid kernel
  if (!tileKernelSource) {
    printf("ERROR: gemmSelectKernel() couldn't find kernel(s) for { order=%s, transA=%s, transB=%s, M=%llu, N=%llu, K=%llu, beta=%u, onept=%f }\n",
      order==clblasColumnMajor ? "ColMajor" : "RowMajor",
      transA==clblasNoTrans ? "N" : transA==clblasTrans ? "T" : "C",
      transB==clblasNoTrans ? "N" : transB==clblasTrans ? "T" : "C",
      M, N, K,
      betaNonZero ? 1 : 0,
      optimalNumElementsPerThread );
      gemmSelectKernel<Precision>(
          order,
          transA,
          transB,
          M,
          N,
          K,
          betaNonZero,
          optimalNumElementsPerThread,
          &tileKernelSource,
          &rowKernelSource,
          &colKernelSource,
          &cornerKernelSource,
          &sourceBuildOptions,
          &tileKernelBinary,
          &rowKernelBinary,
          &colKernelBinary,
          &cornerKernelBinary,
          &tileKernelBinarySize,
          &rowKernelBinarySize,
          &colKernelBinarySize,
          &cornerKernelBinarySize,
          &binaryBuildOptions,
          &tileClKernelDummy,
          &rowClKernelDummy,
          &colClKernelDummy,
          &cornerClKernelDummy,
          &workGroupNumRows,
          &workGroupNumCols,
          &microTileNumRows,
          &microTileNumCols,
          &unroll);
    return clblasNotImplemented;
  }


  unsigned int macroTileNumRows = workGroupNumRows*microTileNumRows;
  unsigned int macroTileNumCols = workGroupNumCols*microTileNumCols;
  bool needTileKernel = M/macroTileNumRows > 0
    && N/macroTileNumCols > 0;
  bool needRowKernel = M%macroTileNumRows > 0 && N/macroTileNumCols > 0;
  bool needColKernel = N%macroTileNumCols > 0 && M/macroTileNumRows > 0;
  bool needCornerKernel = M%macroTileNumRows > 0 && N%macroTileNumCols > 0;
#if 0
  printf("For M,N,K = %u,%u,%u and %u CUs selected tile is wg=%ux%u, microTile=%ux%u, macroTile=%ux%u kernelsNeeded=%u,%u,%u,%u\n",
    M, N, K, clDeviceNumCUs,
    workGroupNumRows, workGroupNumCols,
    microTileNumRows, microTileNumCols,
    macroTileNumRows, macroTileNumCols,
    needTileKernel ? 1 : 0,
    needRowKernel ? 1 : 0,
    needColKernel ? 1 : 0,
    needCornerKernel ? 1 : 0
    );
#endif

/******************************************************************************
 * Build kernels
 *****************************************************************************/
  
  
  cl_kernel  tileClKernel       = NULL;
  cl_kernel  rowClKernel        = NULL;
  cl_kernel  colClKernel        = NULL;
  cl_kernel  cornerClKernel     = NULL;
  if (needTileKernel)   makeGemmKernel(  &tileClKernel, commandQueues[0],   tileKernelSource, sourceBuildOptions,   &tileKernelBinary,   tileKernelBinarySize, binaryBuildOptions);
  if (needRowKernel)    makeGemmKernel(   &rowClKernel, commandQueues[0],    rowKernelSource, sourceBuildOptions,    &rowKernelBinary,    rowKernelBinarySize, binaryBuildOptions);
  if (needColKernel)    makeGemmKernel(   &colClKernel, commandQueues[0],    colKernelSource, sourceBuildOptions,    &colKernelBinary,    colKernelBinarySize, binaryBuildOptions);
  if (needCornerKernel) makeGemmKernel(&cornerClKernel, commandQueues[0], cornerKernelSource, sourceBuildOptions, &cornerKernelBinary, cornerKernelBinarySize, binaryBuildOptions);
  const size_t localWorkSize[2] = { workGroupNumRows, workGroupNumCols };
  unsigned int numKernelsEnqueued = 0;

/******************************************************************************
 * Gather kernel arguments
 *****************************************************************************/
  gemmKernelArgs[ 0] = &A;     gemmKernelArgSizes[ 0] = sizeof(cl_mem);
  gemmKernelArgs[ 1] = &B;     gemmKernelArgSizes[ 1] = sizeof(cl_mem);
  gemmKernelArgs[ 2] = &C;     gemmKernelArgSizes[ 2] = sizeof(cl_mem);
  gemmKernelArgs[ 3] = &alpha; gemmKernelArgSizes[ 3] = sizeof(Precision);
  gemmKernelArgs[ 4] = &beta;  gemmKernelArgSizes[ 4] = sizeof(Precision);
  gemmKernelArgs[ 5] = &M;     gemmKernelArgSizes[ 5] = sizeof(cl_uint);
  gemmKernelArgs[ 6] = &N;     gemmKernelArgSizes[ 6] = sizeof(cl_uint);
  gemmKernelArgs[ 7] = &K;     gemmKernelArgSizes[ 7] = sizeof(cl_uint);
  gemmKernelArgs[ 8] = &lda;   gemmKernelArgSizes[ 8] = sizeof(cl_uint);
  gemmKernelArgs[ 9] = &ldb;   gemmKernelArgSizes[ 9] = sizeof(cl_uint);
  gemmKernelArgs[10] = &ldc;   gemmKernelArgSizes[10] = sizeof(cl_uint);
  gemmKernelArgs[11] = &offA;  gemmKernelArgSizes[11] = sizeof(cl_uint);
  gemmKernelArgs[12] = &offB;  gemmKernelArgSizes[12] = sizeof(cl_uint);
  gemmKernelArgs[13] = &offC;  gemmKernelArgSizes[13] = sizeof(cl_uint);


/******************************************************************************
 * Enqueue Tile kernel
 *****************************************************************************/
  if (needTileKernel) {
    //printf("enqueueing tile kernel\n");
    size_t globalWorkSize[2] = {(M/macroTileNumRows)*workGroupNumRows, (N/macroTileNumCols)*workGroupNumCols };
    err = enqueueGemmKernel( commandQueues[numKernelsEnqueued%numCommandQueues], tileClKernel,
      gemmKernelArgs, gemmKernelArgSizes, numGemmKernelArgs,
      globalWorkSize, localWorkSize,
      numEventsInWaitList, eventWaitList,
      &events[numKernelsEnqueued%numCommandQueues] );
	returnIfErr(err);
    numKernelsEnqueued++;
  }

/******************************************************************************
 * Enqueue Row kernel
 *****************************************************************************/
  if (needRowKernel) {
    //printf("enqueueing row kernel\n");
    size_t globalWorkSize[2] = {1*workGroupNumRows, (N/macroTileNumCols)*workGroupNumCols };
    err = enqueueGemmKernel( commandQueues[numKernelsEnqueued%numCommandQueues], rowClKernel,
      gemmKernelArgs, gemmKernelArgSizes, numGemmKernelArgs,
      globalWorkSize, localWorkSize,
      numEventsInWaitList, eventWaitList,
      &events[numKernelsEnqueued%numCommandQueues] );
	returnIfErr(err);
    numKernelsEnqueued++;
  }

/******************************************************************************
 * Enqueue Col kernel
 *****************************************************************************/
  if (needColKernel) {
    //printf("enqueueing col kernel\n");
    size_t globalWorkSize[2] = { (M/macroTileNumRows)*workGroupNumRows, 1*workGroupNumCols };
    err = enqueueGemmKernel( commandQueues[numKernelsEnqueued%numCommandQueues], colClKernel,
      gemmKernelArgs, gemmKernelArgSizes, numGemmKernelArgs,
      globalWorkSize, localWorkSize,
      numEventsInWaitList, eventWaitList,
      &events[numKernelsEnqueued%numCommandQueues] );
	returnIfErr(err);
    numKernelsEnqueued++;
  }

/******************************************************************************
 * Enqueue Corner kernel
 *****************************************************************************/
  if (needCornerKernel) {
    //printf("enqueueing corner kernel\n");
    size_t globalWorkSize[2] = { 1*workGroupNumRows, 1*workGroupNumCols };
    err = enqueueGemmKernel( commandQueues[numKernelsEnqueued%numCommandQueues], cornerClKernel,
      gemmKernelArgs, gemmKernelArgSizes, numGemmKernelArgs,
      globalWorkSize, localWorkSize,
      numEventsInWaitList, eventWaitList,
      &events[numKernelsEnqueued%numCommandQueues] );
	returnIfErr(err);
    numKernelsEnqueued++;
  }

  return clblasSuccess;
}


/******************************************************************************
 * SGEMM API call
 *****************************************************************************/
extern "C"
clblasStatus
clblasSgemm(
    clblasOrder order,
    clblasTranspose transA,
    clblasTranspose transB,
    size_t M, size_t N, size_t K,
    cl_float alpha,
    const cl_mem A, size_t offA, size_t lda,
    const cl_mem B, size_t offB, size_t ldb,
    cl_float beta,
    cl_mem C, size_t offC,  size_t ldc,
    cl_uint numCommandQueues,
    cl_command_queue *commandQueues,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
  // check if memory objects are valid
  clblasStatus clblasErr = clblasSuccess;
  clblasErr = checkMemObjects(A, B, C, true, A_MAT_ERRSET, B_MAT_ERRSET, C_MAT_ERRSET);
  if (clblasErr != clblasSuccess)
  	  return clblasErr;
  
  if (K != 0)
  {
  	//check matrix A
  	clblasErr = checkMatrixSizes(TYPE_FLOAT, order, transA, M, K, A, offA, lda, A_MAT_ERRSET);
  	if (clblasErr != clblasSuccess)
  		return clblasErr;
  
  	//check matrix B
	clblasErr = checkMatrixSizes(TYPE_FLOAT, order, transB, K, N, B, offB, ldb, B_MAT_ERRSET);
	if (clblasErr != clblasSuccess)
		return clblasErr;
  }
  //check matrix C
  clblasErr = checkMatrixSizes(TYPE_FLOAT, order, clblasNoTrans, M, N, C, offC, ldc, C_MAT_ERRSET);
  if (clblasErr != clblasSuccess)
      return clblasErr;

  return clblasGemm(
       order,
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
}

/******************************************************************************
 * DGEMM API call
 *****************************************************************************/
extern "C"
clblasStatus
clblasDgemm( clblasOrder order,
             clblasTranspose transA,
             clblasTranspose transB,
             size_t M, size_t N,  size_t K,
             cl_double alpha,
             const cl_mem A, size_t offA, size_t lda,
             const cl_mem B, size_t offB, size_t ldb,
             cl_double beta,
             cl_mem C, size_t offC, size_t ldc,
             cl_uint numCommandQueues,
             cl_command_queue *commandQueues,
             cl_uint numEventsInWaitList,
             const cl_event *eventWaitList,
             cl_event *events)
{
  // check if memory objects are valid
  clblasStatus clblasErr = clblasSuccess;
  clblasErr = checkMemObjects(A, B, C, true, A_MAT_ERRSET, B_MAT_ERRSET, C_MAT_ERRSET);
  if (clblasErr != clblasSuccess)
  	  return clblasErr;
  
  if (K != 0)
  {
  	//check matrix A
  	clblasErr = checkMatrixSizes(TYPE_DOUBLE, order, transA, M, K, A, offA, lda, A_MAT_ERRSET);
  	if (clblasErr != clblasSuccess)
  		return clblasErr;
  
  	//check matrix B
  	clblasErr = checkMatrixSizes(TYPE_DOUBLE, order, transB, K, N, B, offB, ldb, B_MAT_ERRSET);
  	if (clblasErr != clblasSuccess)
  		return clblasErr;
  }
  //check matrix C
  clblasErr = checkMatrixSizes(TYPE_DOUBLE, order, clblasNoTrans, M, N, C, offC, ldc, C_MAT_ERRSET);
  if (clblasErr != clblasSuccess)
      return clblasErr;

   return clblasGemm(
       order,
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
}

/******************************************************************************
 * CGEMM API call
 *****************************************************************************/
extern "C"
clblasStatus
clblasCgemm(
    clblasOrder order,
    clblasTranspose transA,
    clblasTranspose transB,
    size_t M, size_t N, size_t K,
    FloatComplex alpha,
    const cl_mem A, size_t offA, size_t lda,
    const cl_mem B, size_t offB, size_t ldb,
    FloatComplex beta,
    cl_mem C, size_t offC, size_t ldc,
    cl_uint numCommandQueues,
    cl_command_queue *commandQueues,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
  // check if memory objects are valid
  clblasStatus clblasErr = clblasSuccess;
  clblasErr = checkMemObjects(A, B, C, true, A_MAT_ERRSET, B_MAT_ERRSET, C_MAT_ERRSET);
  if (clblasErr != clblasSuccess)
  	return clblasErr;
  
  if (K != 0)
  {
  	//check matrix A
  	clblasErr = checkMatrixSizes(TYPE_COMPLEX_FLOAT, order, transA, M, K, A, offA, lda, A_MAT_ERRSET);
  	if (clblasErr != clblasSuccess)
  		return clblasErr;
  
  	//check matrix B
  	clblasErr = checkMatrixSizes(TYPE_COMPLEX_FLOAT, order, transB, K, N, B, offB, ldb, B_MAT_ERRSET);
  	if (clblasErr != clblasSuccess)
  		return clblasErr;
  }
  //check matrix C
  clblasErr = checkMatrixSizes(TYPE_COMPLEX_FLOAT, order, clblasNoTrans, M, N, C, offC, ldc, C_MAT_ERRSET);
  if (clblasErr != clblasSuccess)
  	  return clblasErr;

   return clblasGemm(
       order,
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
}

/******************************************************************************
 * ZGEMM API
 *****************************************************************************/
extern "C"
clblasStatus
clblasZgemm(
    clblasOrder order,
    clblasTranspose transA,
    clblasTranspose transB,
    size_t M, size_t N, size_t K,
    DoubleComplex alpha,
    const cl_mem A, size_t offA, size_t lda,
    const cl_mem B, size_t offB, size_t ldb,
    DoubleComplex beta,
    cl_mem C, size_t offC, size_t ldc,
    cl_uint numCommandQueues,
    cl_command_queue *commandQueues,
    cl_uint numEventsInWaitList,
    const cl_event *eventWaitList,
    cl_event *events)
{
  // check if memory objects are valid
  clblasStatus clblasErr = clblasSuccess;
  clblasErr = checkMemObjects(A, B, C, true, A_MAT_ERRSET, B_MAT_ERRSET, C_MAT_ERRSET);
  if (clblasErr != clblasSuccess)
  	  return clblasErr;
  
  if (K != 0)
  {
  	//check matrix A
  	clblasErr = checkMatrixSizes(TYPE_COMPLEX_DOUBLE, order, transA, M, K, A, offA, lda, A_MAT_ERRSET);
  	if (clblasErr != clblasSuccess)
  		return clblasErr;
  
  	//check matrix B
  	clblasErr = checkMatrixSizes(TYPE_COMPLEX_DOUBLE, order, transB, K, N, B, offB, ldb, B_MAT_ERRSET);
  	if (clblasErr != clblasSuccess)
  		return clblasErr;
  }
  //check matrix C
  clblasErr = checkMatrixSizes(TYPE_COMPLEX_DOUBLE, order, clblasNoTrans, M, N, C, offC, ldc, C_MAT_ERRSET);
  if (clblasErr != clblasSuccess)
  	  return clblasErr;

   return clblasGemm(
       order,
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
}
