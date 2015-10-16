#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string>
//#include <Windows.h>
#include <CL/cl.h>
//#include "library/tools/ktest/naive/naive_blas.cpp"
//using namespace NaiveBlas;
#include "AutoGemmIncludes/AutoGemmKernelSelection.h"
#include "AutoGemmIncludes/AutoGemmKernelSelectionSpecific.h"
#include "AutoGemmIncludes/AutoGemmKernelEnumeration.h"

#include "AutoGemmUtil.h"

#if 0
// from clBLAS.h
typedef enum clblasOrder_ {
    clblasRowMajor,   
    clblasColumnMajor 
} clblasOrder;

typedef enum clblasTranspose_ {
    clblasNoTrans,  
    clblasTrans,    
    clblasConjTrans 
                    
} clblasTranspose;
#endif

#define SGEMM 0
#define DGEMM 1
#define CGEMM 0
#define ZGEMM 0

#define RANDOM_DATA   1
#define DO_VALIDATION 1

#if SGEMM
#define DATA_TYPE float
#define DATA_TYPE_CONSTRUCTOR(X,Y) X
const unsigned int numTiles = sgemmNumTiles;
const unsigned int numNonTiles = sgemmNumNonTiles;
const unsigned int numKernels = sgemmNumKernels;
#endif

#if DGEMM
#define DATA_TYPE double
#define DATA_TYPE_CONSTRUCTOR(X,Y) X
const unsigned int numTiles = dgemmNumTiles;
const unsigned int numNonTiles = dgemmNumNonTiles;
const unsigned int numKernels = dgemmNumKernels;
#endif

#if CGEMM
#define DATA_TYPE FloatComplex
#define DATA_TYPE_CONSTRUCTOR floatComplex
const unsigned int numTiles = cgemmNumTiles;
const unsigned int numNonTiles = cgemmNumNonTiles;
const unsigned int numKernels = cgemmNumKernels;
#endif

#if ZGEMM
#define DATA_TYPE DoubleComplex
#define DATA_TYPE_CONSTRUCTOR doubleComplex
const unsigned int numTiles = zgemmNumTiles;
const unsigned int numNonTiles = zgemmNumNonTiles;
const unsigned int numKernels = zgemmNumKernels;
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#define CL_CHECK(RET) \
  if(RET != CL_SUCCESS) { \
    printf("OpenCL error %i on line %u\n", RET, __LINE__); \
    assert(false); \
  }


template<typename T>
void
randomMatrix(
    clblasOrder order,
    size_t rows,
    size_t columns,
    T *A,
    size_t lda)
{
    size_t r, c;
    MatrixAccessor<T> a(A, order, clblasNoTrans, rows, columns, lda);

    for (r = 0; r < rows; r++) {
        for (c = 0; c < columns; c++) {
#if RANDOM_DATA
            a[r][c] = random<T>();
#else
            a[r][c] = DATA_TYPE_CONSTRUCTOR(1, 0);
#endif
        }
    }
}

template<typename T>
bool
compareMatrices(
    clblasOrder order,
    size_t rows,
    size_t columns,
    T *blasMatrix,
    T *naiveMatrix,
    size_t ld)
{
    size_t r, c;
    MatrixAccessor<T> blas(blasMatrix, order, clblasNoTrans, rows, columns, ld);
    MatrixAccessor<T> naive(naiveMatrix, order, clblasNoTrans, rows, columns, ld);
    T blasVal, naiveVal;
    int numPrint = 96*96;
    bool equal = true;
    for (r = 0; r < rows; r++) {
        for (c = 0; c < columns; c++) {
            blasVal = blas[r][c];
            naiveVal = naive[r][c];
            if (isNAN(blasVal) && isNAN(naiveVal)) {
                continue;
            }
            if (blasVal != naiveVal) {
              equal = false;
            }
            
            if (blasVal != naiveVal) {
              if (numPrint-- > 0) {
#if CGEMM || ZGEMM
                printf("MISMATCH C[%u][%u]: gpu= %4.1f + %4.1fi, cpu= %4.1f + %4.1fi\n",
                  r, c,
                  blasVal.s[0], blasVal.s[1],
                  naiveVal.s[0], naiveVal.s[1] );
#else
                printf("MISMATCH C[%u][%u]: gpu= %4.1f, cpu= %4.1f\n",
                  r, c,
                  blasVal,
                  naiveVal );
#endif
              } else {
                return equal;
              }
            }
        }
    }
    return equal;
}


const char PLATFORM_NAME[] = "AMD Accelerated Parallel Processing";
const char DEVICE_NAME[] = "Hawaii";
#if SGEMM || CGEMM
const float peakGflops = 5.24e3; // sp for W9100
#else
const float peakGflops = 2.62e3; // dp for W9100
#endif
//const float peakGflops = 696; // for R9 290 "Hawaii"


const cl_uint offsetM = 0;
const cl_uint offsetN = 0;
const cl_uint offsetK = 0;
cl_uint offA = 0;
cl_uint offB = 0;
cl_uint offC = 0;
DATA_TYPE alpha = DATA_TYPE_CONSTRUCTOR(1, 0);
cl_mem bufA = NULL;
cl_mem bufB = NULL;
cl_mem bufC = NULL;
DATA_TYPE* A = NULL;
DATA_TYPE* B = NULL;
DATA_TYPE* C = NULL;
DATA_TYPE* naiveC = NULL;

const cl_uint workDim = 2;

#if DO_VALIDATION
const unsigned int numEnqueuesPerFlush = 1;
const unsigned int numFlushesPerFinish = 1;
const unsigned int numFinishes = 1;
#else
const unsigned int numEnqueuesPerFlush = 2;
const unsigned int numFlushesPerFinish = 2;
const unsigned int numFinishes = 2;
#endif

cl_platform_id getPlatform(const char *name);
cl_device_id getDevice(cl_platform_id platform, const char *name);
cl_kernel createKernel(const char *source, cl_context context,
    const char* options, cl_int *error);



void testKernelParameterCombination(
  unsigned int columnMajorInt,
  unsigned int transAInt,
  unsigned int transBInt,
  unsigned int betaNonZero,
  unsigned int macroTileNumRows,
  unsigned int macroTileNumCols,
  unsigned int unroll,
  unsigned int mSpill,
  unsigned int nSpill ) {

    
  DATA_TYPE beta;
  if (betaNonZero) {
    beta = DATA_TYPE_CONSTRUCTOR(1, 0);
  } else {
    beta = DATA_TYPE_CONSTRUCTOR(0, 0);
  }
  

  // how large of a matrix to test?
#if DO_VALIDATION
  size_t M = 16*macroTileNumRows;
  size_t N = 16*macroTileNumCols;
  size_t K = 16*unroll;
#else
  //if (mSpill || nSpill || unroll==1 || transAInt==1 || transBInt==0) return;
  
  if (mSpill || nSpill || unroll==1 ) return;

  size_t M = 22*macroTileNumRows;
  size_t N = 24*macroTileNumCols;
  size_t K = 2*64*90+unroll;
#endif
  if (mSpill) {
    M += 1;
  }
  if (nSpill) {
    N += 1;
  }

  
#if 1
  printf("Testing: %sgemm_%s%s_B%u_MX%03u_NX%03u_KX%02u\n",
#if SGEMM
    "s",
#elif DGEMM
    "d",
#elif CGEMM
    "c",
#else
    "z",
#endif
    transAInt ? "T" : "N",
    transBInt ? "T" : "N",
    betaNonZero ? 1 : 0,
    macroTileNumRows,
    macroTileNumCols,
    unroll );
#endif

  //printf("M=%u, N=%u, K=%u\n", M, N, K);
  // matrix A parameters
  clblasTranspose transA;
  cl_uint numRowsA;
  cl_uint numColsA;
  if (transAInt) {
    transA = clblasTrans;
    numRowsA = K;
    numColsA = M;
  } else {
    transA = clblasNoTrans;
    numRowsA = M;
    numColsA = K;
  }

  // matrix B parameters
  clblasTranspose transB;
  cl_uint numRowsB;
  cl_uint numColsB;
  if (transBInt) {
    transB = clblasTrans;
    numRowsB = N;
    numColsB = K;
  } else {
    transB = clblasNoTrans;
    numRowsB = K;
    numColsB = N;
  }

  // Matrix C
  cl_uint numRowsC = M;
  cl_uint numColsC = N;

// leading dimension
  clblasOrder order;
  cl_uint lda;
  cl_uint ldb;
  cl_uint ldc;
  if (columnMajorInt) {
    order = clblasColumnMajor;
    lda = numRowsA;
    ldb = numRowsB;
    ldc = numRowsC;
  } else {
    order = clblasRowMajor;
    lda = numColsA;
    ldb = numColsB;
    ldc = numColsC;
  }

    cl_int err;
    cl_platform_id platform;
    cl_device_id device;
    cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
    cl_context context;
    cl_command_queue queue;

    platform = getPlatform(PLATFORM_NAME);
    assert(platform != NULL);
    device = getDevice(platform, DEVICE_NAME);
    assert(device != NULL);
    props[1] = (cl_context_properties)platform;
    context = clCreateContext(props, 1, &device, NULL, NULL, &err);
    assert(context != NULL);
    queue = clCreateCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, &err);
    assert(queue != NULL);

    //printf("Allocating matrices.\n");
    A = (DATA_TYPE*)malloc((offA + numRowsA * numColsA) * sizeof(*A));
    assert(A != NULL);
    randomMatrix(order, numRowsA, numColsA, A + offA, lda);
    B = (DATA_TYPE*)malloc((offB + numRowsB * numColsB) * sizeof(*B));
    assert(B != NULL);
    randomMatrix(order, numRowsB, numColsB, B + offB, ldb);
    C = (DATA_TYPE*)malloc((offC + numRowsC * numColsC) * sizeof(*C));
    assert(C != NULL);
    randomMatrix(order, numRowsC, numColsC, C + offC, ldc);
    naiveC = (DATA_TYPE*)malloc((offC + numRowsC * numColsC) * sizeof(*naiveC));
    assert(naiveC != NULL);
    memcpy(naiveC, C, (offC + numRowsC * numColsC) * sizeof(*C));

#if DO_VALIDATION
    //printf("Running naive gemm.\n");
    gemm(order, transA, transB, M, N, K, alpha, A + offA, lda, B + offB, ldb, beta, naiveC + offC, ldc);
#endif
    bufA = clCreateBuffer(context, CL_MEM_READ_ONLY,
        (offA + numRowsA * numColsA) * sizeof(*A), NULL, &err);
    CL_CHECK(err);
    assert(bufA != NULL);
    err = clEnqueueWriteBuffer(queue, bufA, CL_TRUE, 0,
        (offA + numRowsA * numColsA) * sizeof(*A), A,
        0, NULL, NULL);
    CL_CHECK(err);
    assert(err == CL_SUCCESS);
    bufB = clCreateBuffer(context, CL_MEM_READ_ONLY,
        (offB + numRowsB * numColsB) * sizeof(*B), NULL, &err);
    CL_CHECK(err);
    assert(bufB != NULL);
    err = clEnqueueWriteBuffer(queue, bufB, CL_TRUE, 0,
        (offB + numRowsB * numColsB) * sizeof(*B), B,
        0, NULL, NULL);
    CL_CHECK(err);
    assert(err == CL_SUCCESS);

    //printf("Writing to gpu buffers.\n");
    bufC = clCreateBuffer(context, CL_MEM_READ_WRITE,
        (offC + numRowsC * numColsC) * sizeof(*C), NULL, &err);
    CL_CHECK(err);
    assert(bufC != NULL);
    err = clEnqueueWriteBuffer(queue, bufC, CL_TRUE, 0,
        (offC + numRowsC * numColsC) * sizeof(*C), C,
        0, NULL, NULL);
    CL_CHECK(err);
    assert(err == CL_SUCCESS);

  float optimalNumElementsPerWorkItem = 1;

  const char *tileKernelSource;
  const char *rowKernelSource;
  const char *colKernelSource;
  const char *cornerKernelSource;
  const char *sourceBuildOptions;
  const unsigned char *tileKernelBinary;
  const unsigned char *rowKernelBinary;
  const unsigned char *colKernelBinary;
  const unsigned char *cornerKernelBinary;
  size_t *tileKernelBinarySize = 0;
  size_t *rowKernelBinarySize = 0;
  size_t *colKernelBinarySize = 0;
  size_t *cornerKernelBinarySize = 0;
  const char *binaryBuildOptions;
  cl_kernel  *tileClKernel;
  cl_kernel  *rowClKernel;
  cl_kernel  *colClKernel;
  cl_kernel  *cornerClKernel;
  unsigned int workGroupNumRows;
  unsigned int workGroupNumCols;
  unsigned int microTileNumRows;
  unsigned int microTileNumCols;
  unsigned int retUnroll;

#if 0
    //printf("Creating kernel.\n");
  gemmSelectKernel<DATA_TYPE>(
    order,
    transA,
    transB,
    M,
    N,
    K,
    betaNonZero==1,
    optimalNumElementsPerWorkItem,
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
    &tileClKernel,
    &rowClKernel,
    &colClKernel,
    &cornerClKernel,
    &workGroupNumRows,
    &workGroupNumCols,
    &microTileNumRows,
    &microTileNumCols,
    &retUnroll
  );
  bool kernelFound = tileKernelSource != NULL;
#else
  bool kernelFound = gemmSelectKernelSpecific<DATA_TYPE>(
    order,
    transA,
    transB,
    betaNonZero==1,
    macroTileNumRows,
    macroTileNumCols,
    unroll,
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
    &tileClKernel,
    &rowClKernel,
    &colClKernel,
    &cornerClKernel,
    &workGroupNumRows,
    &workGroupNumCols,
    &microTileNumRows,
    &microTileNumCols
    );
#endif

  if ( !kernelFound ) {
      printf("ERROR: selected kernel doesn't match desired kernel: %u, %u, %u, %u, %u\n",
         workGroupNumRows,
         workGroupNumCols,
         microTileNumRows,
         microTileNumCols,
         unroll
    );
  }

  /****************************************************************************
   * Tile Kernel
   ***************************************************************************/
  //printf("%s", tileKernelSource);
  assert(tileKernelSource != NULL);
  *tileClKernel = createKernel(tileKernelSource, context, sourceBuildOptions, &err);
  assert(tileClKernel != NULL);
  err = clSetKernelArg(*tileClKernel,  0, sizeof(cl_mem),    &bufA);   CL_CHECK(err);
  err = clSetKernelArg(*tileClKernel,  1, sizeof(cl_mem),    &bufB);   CL_CHECK(err);
  err = clSetKernelArg(*tileClKernel,  2, sizeof(cl_mem),    &bufC);   CL_CHECK(err);
  err = clSetKernelArg(*tileClKernel,  3, sizeof(DATA_TYPE), &alpha);  CL_CHECK(err);
  err = clSetKernelArg(*tileClKernel,  4, sizeof(DATA_TYPE), &beta);   CL_CHECK(err);
  err = clSetKernelArg(*tileClKernel,  5, sizeof(cl_uint),   &M);      CL_CHECK(err);
  err = clSetKernelArg(*tileClKernel,  6, sizeof(cl_uint),   &N);      CL_CHECK(err);
  err = clSetKernelArg(*tileClKernel,  7, sizeof(cl_uint),   &K);      CL_CHECK(err);
  err = clSetKernelArg(*tileClKernel,  8, sizeof(cl_uint),   &lda);    CL_CHECK(err);
  err = clSetKernelArg(*tileClKernel,  9, sizeof(cl_uint),   &ldb);    CL_CHECK(err);
  err = clSetKernelArg(*tileClKernel, 10, sizeof(cl_uint),   &ldc);    CL_CHECK(err);
  err = clSetKernelArg(*tileClKernel, 11, sizeof(cl_uint),   &offA);   CL_CHECK(err);
  err = clSetKernelArg(*tileClKernel, 12, sizeof(cl_uint),   &offB);   CL_CHECK(err);
  err = clSetKernelArg(*tileClKernel, 13, sizeof(cl_uint),   &offC);   CL_CHECK(err);
  // kernel dimensions
  const size_t localWorkSize[2] = { workGroupNumRows, workGroupNumCols };
  size_t tileKernelGlobalWorkSize[2] = { (M/(macroTileNumRows))*workGroupNumRows, (N/(macroTileNumCols))*workGroupNumCols };
  size_t rowKernelGlobalWorkSize[2] = { 1*workGroupNumRows, (N/(macroTileNumCols))*workGroupNumCols };
  size_t colKernelGlobalWorkSize[2] = { (M/(macroTileNumRows))*workGroupNumRows, 1*workGroupNumCols };
  size_t cornerKernelGlobalWorkSize[2] = { 1*workGroupNumRows, 1*workGroupNumCols };
  
  /****************************************************************************
   * Row Kernel (along bottom of matrix)
   ***************************************************************************/
  if (mSpill) {
    assert(rowKernelSource != NULL);
    *rowClKernel = createKernel(rowKernelSource, context, sourceBuildOptions, &err);
    assert(rowClKernel != NULL);
    err = clSetKernelArg(*rowClKernel,  0, sizeof(cl_mem),    &bufA);   CL_CHECK(err);
    err = clSetKernelArg(*rowClKernel,  1, sizeof(cl_mem),    &bufB);   CL_CHECK(err);
    err = clSetKernelArg(*rowClKernel,  2, sizeof(cl_mem),    &bufC);   CL_CHECK(err);
    err = clSetKernelArg(*rowClKernel,  3, sizeof(DATA_TYPE), &alpha);  CL_CHECK(err);
    err = clSetKernelArg(*rowClKernel,  4, sizeof(DATA_TYPE), &beta);   CL_CHECK(err);
    err = clSetKernelArg(*rowClKernel,  5, sizeof(cl_uint),   &M);      CL_CHECK(err);
    err = clSetKernelArg(*rowClKernel,  6, sizeof(cl_uint),   &N);      CL_CHECK(err);
    err = clSetKernelArg(*rowClKernel,  7, sizeof(cl_uint),   &K);      CL_CHECK(err);
    err = clSetKernelArg(*rowClKernel,  8, sizeof(cl_uint),   &lda);    CL_CHECK(err);
    err = clSetKernelArg(*rowClKernel,  9, sizeof(cl_uint),   &ldb);    CL_CHECK(err);
    err = clSetKernelArg(*rowClKernel, 10, sizeof(cl_uint),   &ldc);    CL_CHECK(err);
    err = clSetKernelArg(*rowClKernel, 11, sizeof(cl_uint),   &offA);   CL_CHECK(err);
    err = clSetKernelArg(*rowClKernel, 12, sizeof(cl_uint),   &offB);   CL_CHECK(err);
    err = clSetKernelArg(*rowClKernel, 13, sizeof(cl_uint),   &offC);   CL_CHECK(err);
    // kernel dimensions
  }
  
  /****************************************************************************
   * Col Kernel (along side of kernel)
   ***************************************************************************/
  if (nSpill) {
    assert(colKernelSource != NULL);
    *colClKernel = createKernel(colKernelSource, context, sourceBuildOptions, &err);
    assert(colClKernel != NULL);
    err = clSetKernelArg(*colClKernel,  0, sizeof(cl_mem),    &bufA);   CL_CHECK(err);
    err = clSetKernelArg(*colClKernel,  1, sizeof(cl_mem),    &bufB);   CL_CHECK(err);
    err = clSetKernelArg(*colClKernel,  2, sizeof(cl_mem),    &bufC);   CL_CHECK(err);
    err = clSetKernelArg(*colClKernel,  3, sizeof(DATA_TYPE), &alpha);  CL_CHECK(err);
    err = clSetKernelArg(*colClKernel,  4, sizeof(DATA_TYPE), &beta);   CL_CHECK(err);
    err = clSetKernelArg(*colClKernel,  5, sizeof(cl_uint),   &M);      CL_CHECK(err);
    err = clSetKernelArg(*colClKernel,  6, sizeof(cl_uint),   &N);      CL_CHECK(err);
    err = clSetKernelArg(*colClKernel,  7, sizeof(cl_uint),   &K);      CL_CHECK(err);
    err = clSetKernelArg(*colClKernel,  8, sizeof(cl_uint),   &lda);    CL_CHECK(err);
    err = clSetKernelArg(*colClKernel,  9, sizeof(cl_uint),   &ldb);    CL_CHECK(err);
    err = clSetKernelArg(*colClKernel, 10, sizeof(cl_uint),   &ldc);    CL_CHECK(err);
    err = clSetKernelArg(*colClKernel, 11, sizeof(cl_uint),   &offA);   CL_CHECK(err);
    err = clSetKernelArg(*colClKernel, 12, sizeof(cl_uint),   &offB);   CL_CHECK(err);
    err = clSetKernelArg(*colClKernel, 13, sizeof(cl_uint),   &offC);   CL_CHECK(err);
    // kernel dimensions
  }
  
  /****************************************************************************
   * Corner Kernel (lower left corder of kernel)
   ***************************************************************************/
  if (mSpill && nSpill) {
    assert(cornerKernelSource != NULL);
    *cornerClKernel = createKernel(cornerKernelSource, context, sourceBuildOptions, &err);
    assert(cornerClKernel != NULL);
    err = clSetKernelArg(*cornerClKernel,  0, sizeof(cl_mem),    &bufA);   CL_CHECK(err);
    err = clSetKernelArg(*cornerClKernel,  1, sizeof(cl_mem),    &bufB);   CL_CHECK(err);
    err = clSetKernelArg(*cornerClKernel,  2, sizeof(cl_mem),    &bufC);   CL_CHECK(err);
    err = clSetKernelArg(*cornerClKernel,  3, sizeof(DATA_TYPE), &alpha);  CL_CHECK(err);
    err = clSetKernelArg(*cornerClKernel,  4, sizeof(DATA_TYPE), &beta);   CL_CHECK(err);
    err = clSetKernelArg(*cornerClKernel,  5, sizeof(cl_uint),   &M);      CL_CHECK(err);
    err = clSetKernelArg(*cornerClKernel,  6, sizeof(cl_uint),   &N);      CL_CHECK(err);
    err = clSetKernelArg(*cornerClKernel,  7, sizeof(cl_uint),   &K);      CL_CHECK(err);
    err = clSetKernelArg(*cornerClKernel,  8, sizeof(cl_uint),   &lda);    CL_CHECK(err);
    err = clSetKernelArg(*cornerClKernel,  9, sizeof(cl_uint),   &ldb);    CL_CHECK(err);
    err = clSetKernelArg(*cornerClKernel, 10, sizeof(cl_uint),   &ldc);    CL_CHECK(err);
    err = clSetKernelArg(*cornerClKernel, 11, sizeof(cl_uint),   &offA);   CL_CHECK(err);
    err = clSetKernelArg(*cornerClKernel, 12, sizeof(cl_uint),   &offB);   CL_CHECK(err);
    err = clSetKernelArg(*cornerClKernel, 13, sizeof(cl_uint),   &offC);   CL_CHECK(err);
    // kernel dimensions
  }

  unsigned int totalEnqueues = numEnqueuesPerFlush * numFlushesPerFinish * numFinishes;
  if (mSpill || nSpill) {
    totalEnqueues *= 2;
  }
  if (mSpill && nSpill) {
    totalEnqueues *= 2;
  }
  cl_event kernelEvents[numEnqueuesPerFlush * numFlushesPerFinish * numFinishes * 4];
  unsigned int kernelIdx = 0;
  //printf("Launching %u kernels of %u x %u threads\n", totalEnqueues, globalWorkSize[0], globalWorkSize[1]);
  for (unsigned int finishIdx = 0; finishIdx < numFinishes; finishIdx++) {
    for (unsigned int flushIdx = 0; flushIdx < numFlushesPerFinish; flushIdx++) {
      for (unsigned int enqIdx = 0; enqIdx < numEnqueuesPerFlush; enqIdx++) {
        // tile kernel
        err = clEnqueueNDRangeKernel(queue, *tileClKernel, workDim, NULL,
            tileKernelGlobalWorkSize, localWorkSize, 0, NULL, &kernelEvents[kernelIdx]);
        CL_CHECK(err);
        kernelIdx++;
#if 1
        // row kernel
        if (mSpill) {
          printf("launching rowKernel %ux%u threads b/c M=%u\n", rowKernelGlobalWorkSize[0], rowKernelGlobalWorkSize[1], M);
          err = clEnqueueNDRangeKernel(queue, *rowClKernel, workDim, NULL,
              rowKernelGlobalWorkSize, localWorkSize, 0, NULL, &kernelEvents[kernelIdx]);
          CL_CHECK(err);
          kernelIdx++;
        }
        // col kernel
        if (nSpill) {
          printf("launching colKernel %ux%u threads b/c N=%u\n", colKernelGlobalWorkSize[0], colKernelGlobalWorkSize[1], N);
          err = clEnqueueNDRangeKernel(queue, *colClKernel, workDim, NULL,
              colKernelGlobalWorkSize, localWorkSize, 0, NULL, &kernelEvents[kernelIdx]);
          CL_CHECK(err);
          kernelIdx++;
        }
        // corner kernel
        if (mSpill && nSpill) {
          printf("launching crnKernel %ux%u threads b/c M=%u, N=%u\n", cornerKernelGlobalWorkSize[0], cornerKernelGlobalWorkSize[1], M, N);
          err = clEnqueueNDRangeKernel(queue, *cornerClKernel, workDim, NULL,
              cornerKernelGlobalWorkSize, localWorkSize, 0, NULL, &kernelEvents[kernelIdx]);
          CL_CHECK(err);
          kernelIdx++;
        }
#endif
      }
      err = clFlush(queue);
      CL_CHECK(err);
    }
    err = clFinish(queue);
    CL_CHECK(err);
  }

#if DO_VALIDATION
#else
    cl_ulong start, end;
    for (kernelIdx = 0; kernelIdx < totalEnqueues; kernelIdx++) {
      err = clGetEventProfilingInfo(kernelEvents[kernelIdx], CL_PROFILING_COMMAND_START,
        sizeof(start), &start, NULL);
      CL_CHECK(err);
      err = clGetEventProfilingInfo(kernelEvents[kernelIdx], CL_PROFILING_COMMAND_END,
        sizeof(end), &end, NULL);
      CL_CHECK(err);
      cl_ulong timeNs = end - start;
      cl_ulong totalFlops;
      if (!mSpill && !nSpill) {
        totalFlops = 2*((cl_ulong)M)*N*K;
      } else if (mSpill && !nSpill) {
        if (kernelIdx%2==0) {
          totalFlops = 2*((cl_ulong)M)*N*K;
        } else {
          totalFlops = 2*((cl_ulong)macroTileNumRows)*N*K;
        }
      } else if (nSpill && !mSpill) {
        if (kernelIdx%2==0) {
          totalFlops = 2*((cl_ulong)M)*N*K;
        } else {
          totalFlops = 2*((cl_ulong)M)*macroTileNumCols*K;
        }
      } else {
        if (kernelIdx%4==0) {
          totalFlops = 2*((cl_ulong)M)*N*K;
        } else if (kernelIdx%4==1) {
          totalFlops = 2*((cl_ulong)macroTileNumRows)*N*K;
        } else if (kernelIdx%4==2) {
          totalFlops = 2*((cl_ulong)M)*macroTileNumCols*K;
        } else {
          totalFlops = 2*((cl_ulong)macroTileNumRows)*macroTileNumCols*K;
        }
      }
#if CGEMM || ZGEMM
      // complex
      totalFlops *= 4;
#endif
      double gFlops = (1.0*totalFlops) / (1.0*timeNs);
      printf("%12llu flops in %12llu ns = %7.1f Gflop/s (%5.1f%% of peak)\n", totalFlops, timeNs, gFlops, 100*gFlops/peakGflops);
    }
#endif

    err = clEnqueueReadBuffer(queue, bufC, CL_TRUE, 0,
        (offC + numRowsC * numColsC) * sizeof(*C), C,
        0, NULL, NULL);
    CL_CHECK(err);

#if DO_VALIDATION
    bool equal = compareMatrices(order, numRowsC, numColsC, C + offC, naiveC + offC, ldc);

    printf("%s_%s%s_%03u_%03u_%u_%02ux%02u_%ux%u%s%s%s%s",
#if SGEMM
      "sgemm",
#endif
#if DGEMM
      "dgemm",
#endif
#if CGEMM
      "cgemm",
#endif
#if ZGEMM
      "zgemm",
#endif
    transAInt ? "T" : "N",
    transBInt ? "T" : "N",
    macroTileNumRows,
    macroTileNumCols,
    unroll,
    workGroupNumRows,
    workGroupNumCols,
    microTileNumRows,
    microTileNumCols,
    columnMajorInt ? "_ColumnMajor" : "_RowMajor",
    mSpill ? "_1" : "_0",
    nSpill ? "_1" : "_0",
    betaNonZero ? "_BETA" : "" );

    if (equal) {
        printf(" - passed\n\n");
    }
    else {
        printf(" - failed\n\n");
        printf("%s", tileKernelSource );
    }
    fflush(stdout);
    system("PAUSE");
#endif

    err = clReleaseMemObject(bufA); CL_CHECK(err);
    err = clReleaseMemObject(bufB); CL_CHECK(err);
    err = clReleaseMemObject(bufC); CL_CHECK(err);
    //err = clReleaseKernel(kernel); CL_CHECK(err);
    err = clReleaseCommandQueue(queue); CL_CHECK(err);
    err = clReleaseContext(context); CL_CHECK(err);

    free(A);
    free(B);
    free(C);
    free(naiveC);
    //free(source);
}



int main(void) {

#if 0
  srand((unsigned int)time(NULL));

  unsigned int **kernels = new unsigned int*[numKernels];
  for (unsigned int i = 0; i < numKernels; i++) {
    kernels[i] = 
#if SGEMM
          sgemmKernelEnumeration[i];
#elif DGEMM
          dgemmKernelEnumeration[i];
#elif CGEMM
          cgemmKernelEnumeration[i];
#elif ZGEMM
          zgemmKernelEnumeration[i];
#endif
  }


  for (unsigned int kernelIdx = 0; kernelIdx < numKernels; kernelIdx++) {
    printf("kernelIdx = %u\n", kernelIdx);
    /* {isColumnMajor, transA, transB, betaNonZero, wgNumRows, wgNumCols, mtNumRows, mtNumCols, }*/
    unsigned int *kernelParameters = kernels[kernelIdx];

    unsigned int columnMajor = kernelParameters[0];
    unsigned int transA = kernelParameters[1];
    unsigned int transB = kernelParameters[2];
    unsigned int betaNonZero = kernelParameters[3];
    unsigned int macroTileNumRows = kernelParameters[4];
    unsigned int macroTileNumCols = kernelParameters[5];
    unsigned int unroll = kernelParameters[6];
    unsigned int mSpill = kernelParameters[7];
    unsigned int nSpill = kernelParameters[8];

    testKernelParameterCombination(
      columnMajor,
      transA,
      transB,
      betaNonZero,
      macroTileNumRows,
      macroTileNumCols,
      unroll,
      mSpill,
      nSpill );
  } // end for
#else
  
    unsigned int columnMajor = 1;
    unsigned int transA = 0;
    unsigned int transB = 1;
    unsigned int beta = 0;
    unsigned int macroTileNumRows = 16*4;
    unsigned int macroTileNumCols = 16*4;
    unsigned int unroll = 8;
    unsigned int mSpill = 0;
    unsigned int nSpill = 0;

    
    testKernelParameterCombination(
      columnMajor,
      transA,
      transB,
      true,
      macroTileNumRows,
      macroTileNumCols,
      unroll,
      mSpill,
      nSpill );

#endif

  
    //system("PAUSE");
    //Sleep(5000); // ms
    exit(EXIT_SUCCESS);
};


cl_platform_id
getPlatform(const char *name)
{
    cl_int err;
    cl_uint nrPlatforms, i;
    cl_platform_id *list, platform;
    char platformName[64];

    err = clGetPlatformIDs(0, NULL, &nrPlatforms);
    assert(err == CL_SUCCESS);
    if (err != CL_SUCCESS) {
        return NULL;
    }

    list = (cl_platform_id*)malloc(nrPlatforms * sizeof(*list));
    if (list == NULL) {
        return NULL;
    }

    err = clGetPlatformIDs(nrPlatforms, list, NULL);
    assert(err == CL_SUCCESS);
    if (err != CL_SUCCESS) {
        free(list);
        return NULL;
    }

    platform = NULL;
    for (i = 0; i < nrPlatforms; i++) {
        err = clGetPlatformInfo(list[i], CL_PLATFORM_NAME,
            sizeof(platformName), platformName, NULL);
        assert(err == CL_SUCCESS);
        if ((err == CL_SUCCESS) && (strcmp(platformName, name) == 0)) {
            platform = list[i];
            break;
        }
    }

    free(list);
    return platform;
}

cl_device_id
getDevice(
    cl_platform_id platform,
    const char *name)
{

    cl_int err;
    cl_uint nrDevices, i;
    cl_device_id *list, device;
    char deviceName[64];

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, NULL, &nrDevices);
    assert(err == CL_SUCCESS);
    if (err != CL_SUCCESS) {
        return NULL;
    }
    list = (cl_device_id*)malloc(nrDevices * sizeof(*list));
    assert(list);
    if (list == NULL) {
        return NULL;
    }

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, nrDevices, list, NULL);
    assert(err == CL_SUCCESS);
    if (err != CL_SUCCESS) {
        free(list);
        return NULL;
    }

    device = NULL;
    for (i = 0; i < nrDevices; i++) {
        err = clGetDeviceInfo(list[i], CL_DEVICE_NAME,
            sizeof(deviceName), deviceName, NULL);
        assert(err == CL_SUCCESS);
        if ((err == CL_SUCCESS) && (strcmp(deviceName, name) == 0)) {
            device = list[i];
            break;
        }
    }

    free(list);
    return device;
}

cl_kernel
createKernel(
    const char* source,
    cl_context context,
    const char* options,
    cl_int* error)
{

  printf("BuildOptions: %s\n", options );

  //printf("Kernel Source:\n%s", source );
  cl_int err;
  cl_device_id device;
  cl_program program;
  cl_kernel kernel;
  size_t logSize;
  char *log;

    err = clGetContextInfo(context, CL_CONTEXT_DEVICES, sizeof(device), &device, NULL);
    assert(err == CL_SUCCESS);
    if (err != CL_SUCCESS) {
        if (error != NULL) {
            *error = err;
        }
        return NULL;
    }

    program = clCreateProgramWithSource(context, 1, &source, NULL, &err);
    assert(err == CL_SUCCESS);
    assert(program != NULL);
    if (program == NULL) {
      if (error != NULL) {
            *error = err;
      }
      return NULL;
    }

    err = clBuildProgram(program, 1, &device, options, NULL, NULL);
    if (err != CL_SUCCESS) {
        logSize = 0;
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
        log = (char*)malloc(logSize + 1);
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, logSize, log, NULL);
        printf("=== Build Log [%lu]===\n%s\n", logSize, log);
        free(log);
    }
    assert(err == CL_SUCCESS);
    if (err != CL_SUCCESS) {
        clReleaseProgram(program);
        if (error != NULL) {
            *error = err;
        }
        return NULL;
    }

    kernel = NULL;
    cl_uint num_kernels_ret;
    err = clCreateKernelsInProgram(program, 0, NULL, &num_kernels_ret);
    err = clCreateKernelsInProgram(program, 1, &kernel, NULL);
    assert(err == CL_SUCCESS);
    assert(kernel != NULL);
    clReleaseProgram(program);

    // kernel name
    size_t length;
    char kernelName[64];
    err = clGetKernelInfo(
      kernel,
      CL_KERNEL_FUNCTION_NAME,
      64,
      kernelName,
      &length );
    printf("KernelName[%lu]: %s\n", length, kernelName);

    // kernel arguments
    cl_uint numArguments;
    err = clGetKernelInfo(
      kernel,
      CL_KERNEL_NUM_ARGS,
      sizeof(numArguments),
      &numArguments,
      NULL );

    if (error != NULL) {
        *error = err;
    }
    return kernel;
}

