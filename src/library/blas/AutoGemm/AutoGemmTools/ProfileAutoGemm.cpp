#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#if defined( __APPLE__ ) || defined( __MACOSX )
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif
//#include "library/tools/ktest/naive/naive_blas.cpp"
//using namespace NaiveBlas;
#include "AutoGemmTools/AutoGemmUtil.h"

#include "AutoGemmIncludes/AutoGemmKernelSelection.h"
#include "AutoGemmIncludes/AutoGemmKernelSelectionSpecific.h"
#include "AutoGemmIncludes/AutoGemmKernelEnumeration.h"

#define SGEMM 1
#define DGEMM 0
#define CGEMM 0
#define ZGEMM 0

#define RANDOM_DATA   1
#define DO_VALIDATION 0

#if SGEMM
#define DATA_TYPE float
#define DATA_TYPE_CONSTRUCTOR(X,Y) X
const unsigned int numTiles = sgemmNumTiles;
const unsigned int numNonTiles = sgemmNumNonTiles;
const unsigned int numKernels = sgemmNumKernels;
#ifdef USER_KERNELS
const char * const ksrFileName = "prof_user_sgemm_ksr.txt";
const char * const rawFileName = "prof_user_sgemm_raw.csv";
#else
const char * const ksrFileName = "prof_sgemm_ksr.txt";
const char * const rawFileName = "prof_sgemm_raw.csv";
#endif
unsigned int systemSizeMax = 1000;
#endif

#if DGEMM
#define DATA_TYPE double
#define DATA_TYPE_CONSTRUCTOR(X,Y) X
const unsigned int numTiles = dgemmNumTiles;
const unsigned int numNonTiles = dgemmNumNonTiles;
const unsigned int numKernels = dgemmNumKernels;
#ifdef USER_KERNELS
const char * const ksrFileName = "prof_user_dgemm_ksr.txt";
const char * const rawFileName = "prof_user_dgemm_raw.csv";
#else
const char * const ksrFileName = "prof_dgemm_ksr.txt";
const char * const rawFileName = "prof_dgemm_raw.csv";
#endif
unsigned int systemSizeMax = 6000;
#endif

#if CGEMM
#define DATA_TYPE FloatComplex
#define DATA_TYPE_CONSTRUCTOR floatComplex
const unsigned int numTiles = cgemmNumTiles;
const unsigned int numNonTiles = cgemmNumNonTiles;
const unsigned int numKernels = cgemmNumKernels;
#ifdef USER_KERNELS
const char * const ksrFileName = "prof_user_cgemm_ksr.txt";
const char * const rawFileName = "prof_user_cgemm_raw.csv";
#else
const char * const ksrFileName = "prof_cgemm_ksr.txt";
const char * const rawFileName = "prof_cgemm_raw.csv";
#endif
unsigned int systemSizeMax = 5500;
#endif

#if ZGEMM
#define DATA_TYPE DoubleComplex
#define DATA_TYPE_CONSTRUCTOR doubleComplex
const unsigned int numTiles = zgemmNumTiles;
const unsigned int numNonTiles = zgemmNumNonTiles;
const unsigned int numKernels = zgemmNumKernels;
#ifdef USER_KERNELS
const char * const ksrFileName = "prof_user_zgemm_ksr.txt";
const char * const rawFileName = "prof_user_zgemm_raw.csv";
#else
const char * const ksrFileName = "prof_zgemm_ksr.txt";
const char * const rawFileName = "prof_zgemm_raw.csv";
#endif
unsigned int systemSizeMax = 5000;
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#define CL_CHECK(RET) \
  if(RET != CL_SUCCESS) { \
    printf("OpenCL error %i on line %u\n", RET, __LINE__); \
    assert(false); \
  }


unsigned int **tiles;

typedef struct _RuleStack {
  unsigned int startSize;
  unsigned int validTileIndices[numTiles];
  unsigned int numValidTiles;
  int fallbackTileIndex;
  _RuleStack() : numValidTiles(0), fallbackTileIndex(-1) {}
} RuleStack;

class KernelSelectionRules {
public:
  RuleStack rule;
  RuleStack history[1024];
  unsigned int numRulesInHistory;
  std::ostream & out;

  //constructor
  KernelSelectionRules( std::ostream & file) : numRulesInHistory(0), out(file) {
  }

  int getFastestValidTileIndex( unsigned int M, unsigned int N) {
    for (unsigned int i = 0; i < rule.numValidTiles; i++) {
      if ( M%tiles[rule.validTileIndices[i]][0]==0
        && N%tiles[rule.validTileIndices[i]][1]==0) {
          return rule.validTileIndices[i];
      }
    }
    return -1;
  }

  void removeTileFromRule( unsigned int tileIdx ) {
    int idx = -1;
    for ( int i = 0; i < rule.numValidTiles; i++) {
      if (rule.validTileIndices[i] == tileIdx) {
        idx = i;
        break;
      }
    }
    if (idx >= 0) {
      for ( int i = idx; i < rule.numValidTiles-1; i++) {
        rule.validTileIndices[i] = rule.validTileIndices[i+1];
      }
      rule.numValidTiles--;
    }
  }

  void addTileToRule( unsigned int tileIdx ) {
    for (int i = rule.numValidTiles; i > 0; i--) {
      rule.validTileIndices[i] = rule.validTileIndices[i-1];
    }
    rule.validTileIndices[0] = tileIdx;
    rule.numValidTiles++;
  }

  bool add(
    unsigned int M,
    unsigned int N,
    unsigned int *validTileIndices,
    unsigned int numValidTiles,
    unsigned int fallbackTileIndex ) {


    // print rule
    printf("rule[%4u+]: ", rule.startSize );
    for (unsigned int i = 0; i < rule.numValidTiles; i++) {
      printf("%ux%u, ", tiles[rule.validTileIndices[i]][0], tiles[rule.validTileIndices[i]][1]);
    }
    if (rule.fallbackTileIndex>=0) {
      printf("; %ux%u", tiles[rule.fallbackTileIndex][0], tiles[rule.fallbackTileIndex][1]);
    }
    printf("\n");

    // print add
    printf("check[%4u,%4u]: ", M, N );
    for (unsigned int i = 0; i < numValidTiles; i++) {
      printf("%ux%u, ", tiles[validTileIndices[i]][0], tiles[validTileIndices[i]][1]);
    }
    printf("; fallback = %ux%u\n", tiles[fallbackTileIndex][0], tiles[fallbackTileIndex][1]);


    bool mismatch = false;

    // compare fallbacks
    if (rule.fallbackTileIndex < 0) {
      mismatch = true;
      printf("mismatch:no fallback tile\n" );
      rule.fallbackTileIndex = fallbackTileIndex;
    } else {
      if (rule.fallbackTileIndex != fallbackTileIndex) {
        mismatch = true;
        printf("mismatch:rule fallback was %ux%u, whereas new fallback is %ux%u\n",
          tiles[rule.fallbackTileIndex][0], tiles[rule.fallbackTileIndex][1],
          tiles[fallbackTileIndex][0], tiles[fallbackTileIndex][1]
          );
        rule.fallbackTileIndex = fallbackTileIndex;
      }
    }

    // compare fastest valid tile
    if (numValidTiles > 0) {
      int ruleFastestValidTileIndex = getFastestValidTileIndex(M,N);
      if (ruleFastestValidTileIndex < 0) {
        // no valid tile for this M,N
        mismatch = true;
        printf("mismatch:no valid tile for size=%u,%u\n", M, N);
        rule.validTileIndices[rule.numValidTiles] = validTileIndices[0];
        rule.numValidTiles++;
      } else {
        if (ruleFastestValidTileIndex != validTileIndices[0]) {
          // there is a valid tile for this M,N but it mismatches
          mismatch = true;
          printf("mismatch:rule tile was %ux%u, whereas fastest is %ux%u\n",
            tiles[ruleFastestValidTileIndex][0], tiles[ruleFastestValidTileIndex][1],
            tiles[validTileIndices[0]][0], tiles[validTileIndices[0]][1]
            );
          removeTileFromRule(validTileIndices[0]); // if it existed elsewhere in the rule stack
          addTileToRule(validTileIndices[0]);
        }
      }
    }

    // remove retired tiles
    for (unsigned int i = 0; i < rule.numValidTiles; i++) {
      if ( M%tiles[rule.validTileIndices[i]][0]==0
          && N%tiles[rule.validTileIndices[i]][1]==0) {

        bool tileIsValid = false;
        for (unsigned int j = 0; j < numValidTiles; j++) {
          if (validTileIndices[j] == rule.validTileIndices[i]) {
            tileIsValid = true;
            break;
          }
        }
        if (!tileIsValid) {
          mismatch = true;
          printf("mismatch:tile %ux%u no longer valid\n", tiles[rule.validTileIndices[i]][0], tiles[rule.validTileIndices[i]][1]);
              removeTileFromRule( rule.validTileIndices[i] );
        }
       }
    }

    // if new rule, add it to history
    if (mismatch) {
      // update history
      rule.startSize = sqrt(M*N)+0.5;
      history[numRulesInHistory] = rule;
      numRulesInHistory++;

      // print what we added
      printf("new[%4u+]: ", rule.startSize);
      for (unsigned int i = 0; i < rule.numValidTiles; i++) {
        printf("%ux%u, ", tiles[rule.validTileIndices[i]][0], tiles[rule.validTileIndices[i]][1]);
      }
      printf("; fallback = %ux%u\n", tiles[rule.fallbackTileIndex][0], tiles[rule.fallbackTileIndex][1]);

      // write size event
      out << "    [ " << std::setw(4) << rule.startSize;
      // write fallback
      out << ", [ " << std::setw(2) << tiles[rule.fallbackTileIndex][0] << ", " << std::setw(2) << tiles[rule.fallbackTileIndex][1] << "]";
      out << ", [ ";
      if (rule.numValidTiles >= 0) {
        out << "[ " << std::setw(2) << tiles[rule.validTileIndices[0]][0] << ", " << std::setw(2) << tiles[rule.validTileIndices[0]][1] << "]";
      }
      for (unsigned int i = 1; i < rule.numValidTiles; i++) {
        out << ", [ " << std::setw(2) << tiles[rule.validTileIndices[i]][0] << ", " << std::setw(2) << tiles[rule.validTileIndices[i]][1] << "]";
      }
      out << " ] ], \n";
      out.flush();

    }
    printf("\n");
    return mismatch;
  } // end add
};









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

/******************************************************************************
 * Make Gemm Kernel
 *****************************************************************************/
void makeGemmKernel(
  cl_kernel *clKernel,
  cl_command_queue clQueue,
  const char *kernelSource,
  const char *sourceBuildOptions,
  const unsigned char **kernelBinary,
  const char *binaryBuildOptions)
{
  cl_int err;
  if (*clKernel) {
    // kernel has already been built, return
#if 0
    // get kernel name
    size_t kernelNameLength;
    err = clGetKernelInfo(
      *clKernel,
      CL_KERNEL_FUNCTION_NAME,
      sizeof(kernelNameLength),
      NULL,
      &kernelNameLength );
    CL_CHECK(err)
    char *kernelName = new char[kernelNameLength];
    err = clGetKernelInfo(
      *clKernel,
      CL_KERNEL_FUNCTION_NAME,
      kernelNameLength*sizeof(char),
      kernelName,
      NULL );
    CL_CHECK(err)
    printf("makeGemmKernel: \"%s\" already built; returning.\n", kernelName);
    delete[] kernelName;
#endif
    return;
  } else {
    // kernel has not been built, so build it (from binary, preferably)
    cl_context clContext;
    cl_device_id clDevice;
    err = clGetCommandQueueInfo( clQueue, CL_QUEUE_CONTEXT, sizeof(clContext), &clContext, NULL);
    CL_CHECK(err)
    err = clGetCommandQueueInfo( clQueue, CL_QUEUE_DEVICE, sizeof(clDevice), &clDevice, NULL);
    CL_CHECK(err)
    cl_program clProgram;
    cl_int clBinaryStatus;
    if (*kernelBinary) {
    size_t kernelBinarySize = strlen((char *)*kernelBinary);
      clProgram = clCreateProgramWithBinary(
        clContext,
        1, &clDevice,
        &kernelBinarySize, kernelBinary,
        &clBinaryStatus, &err );
    CL_CHECK(err)
      err = clBuildProgram(
        clProgram,
        1, &clDevice,
        binaryBuildOptions, NULL, NULL );
    CL_CHECK(err)
    } else {
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
    err = clCreateKernelsInProgram(
      clProgram,
      1, clKernel,
      NULL );
    CL_CHECK(err)

#if 0
    // get kernel name
    size_t kernelNameLength;
    err = clGetKernelInfo(
      *clKernel,
      CL_KERNEL_FUNCTION_NAME,
      sizeof(kernelNameLength),
      NULL,
      &kernelNameLength );
    CL_CHECK(err)
    char *kernelName = new char[kernelNameLength];
    err = clGetKernelInfo(
      *clKernel,
      CL_KERNEL_FUNCTION_NAME,
      kernelNameLength*sizeof(char),
      kernelName,
      NULL );
    CL_CHECK(err)
    printf("makeGemmKernel: \"%s\" built; returning.\n", kernelName);
    delete[] kernelName;
#endif
  }
}


/****************************************************************************
 * Compare Matrices
 ***************************************************************************/
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
//const char DEVICE_NAME[] = "Hawaii";
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

std::ofstream file;
std::ofstream ksrFile;

#if DO_VALIDATION
const unsigned int numEnqueuesPerFlush = 1;
const unsigned int numFlushesPerFinish = 1;
const unsigned int numFinishes = 1;
#else
const unsigned int numEnqueuesPerFlush = 10;
const unsigned int numFlushesPerFinish = 1;
const unsigned int numFinishes = 1;
#endif

char* loadFile(const char* path);
cl_platform_id getPlatform(const char *name);
cl_device_id getDevice(cl_platform_id platform);
cl_kernel createKernel(const char *source, cl_context context,
    const char* options, cl_int *error);


cl_int err;
cl_platform_id platform;
cl_device_id device;
cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
cl_context context;
cl_command_queue queue;


/****************************************************************************
 * Benchmark Kernel
 ***************************************************************************/
float benchmarkKernel(
  clblasOrder order,
  clblasTranspose transA,
  clblasTranspose transB,
  bool betaNonZero,
  unsigned int macroTileNumRows,
  unsigned int macroTileNumCols,
  unsigned int unroll,
  size_t M,
  size_t N,
  size_t K
  ) {


  DATA_TYPE beta;
  if (betaNonZero) {
    beta = DATA_TYPE_CONSTRUCTOR(1, 0);
  } else {
    beta = DATA_TYPE_CONSTRUCTOR(0, 0);
  }

  bool needTileKernel = M/macroTileNumRows > 0 && N/macroTileNumCols > 0;
  bool needRowKernel = M%macroTileNumRows > 0 && N/macroTileNumCols > 0;
  bool needColKernel = N%macroTileNumCols > 0 && M/macroTileNumRows > 0;
  bool needCornerKernel = M%macroTileNumRows > 0 && N%macroTileNumCols > 0;


#if 0
  printf("Testing: %sgemm_%s_%s%s_%s_%03u_%03u_%02u\n",
#if SGEMM
    "s",
#elif DGEMM
    "d",
#elif CGEMM
    "c",
#else
    "z",
#endif
    order==clblasColumnMajor ? "Col" : "Row",
    transA==clblasTrans ? "T" : "N",
    transB==clblasTrans ? "T" : "N",
    betaNonZero ? "_B1" : "_B0",
    macroTileNumRows,
    macroTileNumCols,
    unroll
    );
#endif

  //printf("M=%u, N=%u, K=%u\n", M, N, K);
  // matrix A parameters
  cl_uint numRowsA;
  cl_uint numColsA;
  if (transA == clblasTrans) {
    numRowsA = K;
    numColsA = M;
  } else {
    numRowsA = M;
    numColsA = K;
  }

  // matrix B parameters
  cl_uint numRowsB;
  cl_uint numColsB;
  if (transB == clblasTrans) {
    numRowsB = N;
    numColsB = K;
  } else {
    numRowsB = K;
    numColsB = N;
  }

  // Matrix C
  cl_uint numRowsC = M;
  cl_uint numColsC = N;

// leading dimension
  cl_uint lda;
  cl_uint ldb;
  cl_uint ldc;
  if (order == clblasColumnMajor) {
    lda = numRowsA;
    ldb = numRowsB;
    ldc = numRowsC;
  } else {
    lda = numColsA;
    ldb = numColsB;
    ldc = numColsC;
  }

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

    //printf("Creating kernel.\n");
  bool kernelFound =
  gemmSelectKernelSpecific<DATA_TYPE>(
    order,
    transA,
    transB,
    betaNonZero,
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



  if ( !kernelFound ) {
      printf("ERROR: couldn't find kernel\n" );
  }

  if (needTileKernel)   makeGemmKernel(  tileClKernel, queue,   tileKernelSource, sourceBuildOptions,   &tileKernelBinary, binaryBuildOptions);
  if (needRowKernel)    makeGemmKernel(   rowClKernel, queue,    rowKernelSource, sourceBuildOptions,    &rowKernelBinary, binaryBuildOptions);
  if (needColKernel)    makeGemmKernel(   colClKernel, queue,    colKernelSource, sourceBuildOptions,    &colKernelBinary, binaryBuildOptions);
  if (needCornerKernel) makeGemmKernel(cornerClKernel, queue, cornerKernelSource, sourceBuildOptions, &cornerKernelBinary, binaryBuildOptions);

  /****************************************************************************
   * Tile Kernel
   ***************************************************************************/
  //printf("%s", tileKernelSource);
  unsigned int totalEnqueues = 0;
  if (needTileKernel) {
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
    totalEnqueues++;
  }
  // kernel dimensions
  const size_t localWorkSize[2] = { workGroupNumRows, workGroupNumCols };
  size_t tileKernelGlobalWorkSize[2] = { (M/(macroTileNumRows))*workGroupNumRows, (N/(macroTileNumCols))*workGroupNumCols };
  size_t rowKernelGlobalWorkSize[2] = { 1*workGroupNumRows, (N/(macroTileNumCols))*workGroupNumCols };
  size_t colKernelGlobalWorkSize[2] = { (M/(macroTileNumRows))*workGroupNumRows, 1*workGroupNumCols };
  size_t cornerKernelGlobalWorkSize[2] = { 1*workGroupNumRows, 1*workGroupNumCols };

  /****************************************************************************
   * Row Kernel (along bottom of matrix)
   ***************************************************************************/
  if (needRowKernel) {
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
    totalEnqueues++;
    // kernel dimensions
  }

  /****************************************************************************
   * Col Kernel (along side of kernel)
   ***************************************************************************/
  if (needColKernel) {
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
    totalEnqueues++;
    // kernel dimensions
  }

  /****************************************************************************
   * Corner Kernel (lower left corder of kernel)
   ***************************************************************************/
  if (needCornerKernel) {
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
    totalEnqueues++;
    // kernel dimensions
  }

  totalEnqueues *= numEnqueuesPerFlush * numFlushesPerFinish * numFinishes;

  cl_event kernelEvents[numEnqueuesPerFlush * numFlushesPerFinish * numFinishes * 4];
  unsigned int kernelIdx = 0;
  //printf("Launching %u kernels of %u x %u threads\n", totalEnqueues, globalWorkSize[0], globalWorkSize[1]);
  for (unsigned int finishIdx = 0; finishIdx < numFinishes; finishIdx++) {
    for (unsigned int flushIdx = 0; flushIdx < numFlushesPerFinish; flushIdx++) {
      for (unsigned int enqIdx = 0; enqIdx < numEnqueuesPerFlush; enqIdx++) {
        // tile kernel
        if (needTileKernel) {
          err = clEnqueueNDRangeKernel(queue, *tileClKernel, workDim, NULL,
              tileKernelGlobalWorkSize, localWorkSize, 0, NULL, &kernelEvents[kernelIdx]);
          CL_CHECK(err);
          kernelIdx++;
        }
        // row kernel
        if (needRowKernel) {
          //printf("launching rowKernel %ux%u threads b/c M=%u\n", rowKernelGlobalWorkSize[0], rowKernelGlobalWorkSize[1], M);
          err = clEnqueueNDRangeKernel(queue, *rowClKernel, workDim, NULL,
              rowKernelGlobalWorkSize, localWorkSize, 0, NULL, &kernelEvents[kernelIdx]);
          CL_CHECK(err);
          kernelIdx++;
        }
        // col kernel
        if (needColKernel) {
          //printf("launching colKernel %ux%u threads b/c N=%u\n", colKernelGlobalWorkSize[0], colKernelGlobalWorkSize[1], N);
          err = clEnqueueNDRangeKernel(queue, *colClKernel, workDim, NULL,
              colKernelGlobalWorkSize, localWorkSize, 0, NULL, &kernelEvents[kernelIdx]);
          CL_CHECK(err);
          kernelIdx++;
        }
        // corner kernel
        if (needCornerKernel) {
          //printf("launching crnKernel %ux%u threads b/c M=%u, N=%u\n", cornerKernelGlobalWorkSize[0], cornerKernelGlobalWorkSize[1], M, N);
          err = clEnqueueNDRangeKernel(queue, *cornerClKernel, workDim, NULL,
              cornerKernelGlobalWorkSize, localWorkSize, 0, NULL, &kernelEvents[kernelIdx]);
          CL_CHECK(err);
          kernelIdx++;
        }
      }
      err = clFlush(queue);
      CL_CHECK(err);
    }
    err = clFinish(queue);
    CL_CHECK(err);
  }

  cl_ulong totalNs = 0;
  cl_ulong totalFlops = (size_t) numEnqueuesPerFlush * numFlushesPerFinish * numFinishes * (2 * M * N * K);
#if CGEMM || ZGEMM
      // complex
      totalFlops *= 4;
#endif

    cl_ulong start, end;
    for (kernelIdx = 0; kernelIdx < totalEnqueues; kernelIdx++) {
      err = clGetEventProfilingInfo(kernelEvents[kernelIdx], CL_PROFILING_COMMAND_START,
        sizeof(start), &start, NULL);
      CL_CHECK(err);
      err = clGetEventProfilingInfo(kernelEvents[kernelIdx], CL_PROFILING_COMMAND_END,
        sizeof(end), &end, NULL);
      CL_CHECK(err);
      cl_ulong timeNs = end - start;
      totalNs += timeNs;
    }
    double gFlops = (1.0*totalFlops) / (1.0*totalNs);
    return gFlops;
}



/****************************************************************************
 * Main
 ***************************************************************************/
int main(void) {
  file.open(rawFileName, std::ios_base::out); // or ::app for append
  file << "M, N, ";
  bool printDetails = true;
  // load tiles for precision
  tiles = new unsigned int*[numTiles];
  for (unsigned int i = 0; i < numTiles; i++) {
    tiles[i] =
#if SGEMM
          sgemmTileEnumeration[i];
#elif DGEMM
          dgemmTileEnumeration[i];
#elif CGEMM
          cgemmTileEnumeration[i];
#elif ZGEMM
          zgemmTileEnumeration[i];
#endif
  }

  for (unsigned int tileIdx = 0; tileIdx < numTiles; tileIdx++) {
    unsigned int *tile = tiles[tileIdx];
    file << tile[0] << "x" << tile[1] << ", ";
  }
  file << "<-F|T->, ";
  for (unsigned int tileIdx = 0; tileIdx < numTiles; tileIdx++) {
    unsigned int *tile = tiles[tileIdx];
    file << tile[0] << "x" << tile[1] << ", ";
  }
  file << "fallback, fastest, would-be valid tiles\n";


  int *fallbackBegin = new int[numTiles]; // size at which tile starts being fallback
  int   *fallbackEnd = new int[numTiles]; // size at which tile stops being fallback
  int    *validBegin = new int[numTiles]; // size at which tile starts being valid
  int      *validEnd = new int[numTiles]; // size at which tile stops being valid
  float *fallbackScore = new float[numTiles]; // fallback score for a size
  float     *tileScore = new float[numTiles]; // tile score for a size
  unsigned int *validTiles = new unsigned int[numTiles];
  for (unsigned int i = 0; i < numTiles; i++) {
    fallbackBegin[i] = -1;
      fallbackEnd[i] = -1;
       validBegin[i] = -1;
         validEnd[i] = -1;
  }

  platform = getPlatform(PLATFORM_NAME);
  assert(platform != NULL);
  device = getDevice(platform);
  assert(device != NULL);
  props[1] = (cl_context_properties)platform;
  context = clCreateContext(props, 1, &device, NULL, NULL, &err);
  assert(context != NULL);
  queue = clCreateCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, &err);
  assert(queue != NULL);


  clblasOrder order = clblasColumnMajor;
  clblasTranspose transA = clblasNoTrans;
  clblasTranspose transB = clblasTrans;
  bool beta = false;

  unsigned int systemSizeMin = 16;
  unsigned int systemSizeStep = 16;

  //unsigned int kValues[] = {64, 512, 2048};
  //unsigned int numKValues = 3;
  unsigned int kValues[] = {0};
  unsigned int numKValues = 1;
  //unsigned int kValues[] = {4032};
  //unsigned int numKValues = 1;
  unsigned int kMax;
  if (kValues[numKValues-1] > 0) {
    kMax = kValues[numKValues-1];
  } else {
    kMax = systemSizeMax;
  }


  /******************************************************************
   * Largest Matrix Dimension
   *****************************************************************/
  cl_uint numRowsA;
  cl_uint numColsA;
  if (transA == clblasTrans) {
    numRowsA = kMax;
    numColsA = systemSizeMax;
  } else {
    numRowsA = systemSizeMax;
    numColsA = kMax;
  }

  // matrix B parameters
  cl_uint numRowsB;
  cl_uint numColsB;
  if (transB == clblasTrans) {
    numRowsB = systemSizeMax;
    numColsB = kMax;
  } else {
    numRowsB = systemSizeMax;
    numColsB = kMax;
  }

  // Matrix C
  cl_uint numRowsC = systemSizeMax;
  cl_uint numColsC = systemSizeMax;

// leading dimension
  cl_uint lda;
  cl_uint ldb;
  cl_uint ldc;
  if (order == clblasColumnMajor) {
    lda = numRowsA;
    ldb = numRowsB;
    ldc = numRowsC;
  } else {
    lda = numColsA;
    ldb = numColsB;
    ldc = numColsC;
  }

  /******************************************************************
   * Allocate Matrices
   *****************************************************************/
  A = (DATA_TYPE*)malloc((offA + numRowsA * numColsA) * sizeof(*A));
  assert(A != NULL);
  randomMatrix(order, numRowsA, numColsA, A + offA, lda);
  B = (DATA_TYPE*)malloc((offB + numRowsB * numColsB) * sizeof(*B));
  assert(B != NULL);
  randomMatrix(order, numRowsB, numColsB, B + offB, ldb);
  C = (DATA_TYPE*)malloc((offC + numRowsC * numColsC) * sizeof(*C));
  assert(C != NULL);
  randomMatrix(order, numRowsC, numColsC, C + offC, ldc);
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

  // (0) for each precision

  // (1) for each system size
  ksrFile.open( ksrFileName, std::ios_base::out); // or ::app for append
  KernelSelectionRules ksr(ksrFile);
  for (unsigned int systemSize = systemSizeMin; systemSize <= systemSizeMax; systemSize += systemSizeStep) {

    unsigned int M = systemSize;
    unsigned int N = systemSize;
    file << M << ", " << N << ", ";

    // reset scores for this system size
    for (unsigned int i = 0; i < numTiles; i++) {
      fallbackScore[i] = 0.f;
      tileScore[i] = 0.f;
    }

    // (2) for each k size
    for (unsigned int kIdx = 0; kIdx < numKValues; kIdx++) {
      unsigned int K = kValues[kIdx];
      if (K == 0) K = systemSize;

      // (3) for each tile
      for (unsigned int tileIdx = 0; tileIdx < numTiles; tileIdx++) {
        unsigned int *tile = tiles[tileIdx];
        unsigned int macroTileNumRows = tile[0];
        unsigned int macroTileNumCols = tile[1];
        unsigned int unroll = tile[2];
        //if (printDetails) printf("%4ux%4ux%4u; %ux%u; ", M, N, K, macroTileNumRows, macroTileNumCols );

        /******************************************************************
         * (4) fallback speed
         *****************************************************************/
        float fallbackSpeed = benchmarkKernel(
            // non-tile
            order, transA, transB, false,
            // tile
            macroTileNumRows, macroTileNumCols,
            unroll,
            // system
            M-1, N-1, K
            );
        fallbackScore[tileIdx] += fallbackSpeed;

        /******************************************************************
         * (5) tile speed
         *****************************************************************/
        float tileSpeed = 0.f;
        if (M%macroTileNumRows==0 && N%macroTileNumCols==0) {
          tileSpeed = benchmarkKernel(
              // non-tile
              order, transA, transB, false,
              // tile
              macroTileNumRows, macroTileNumCols,
              unroll,
              // system
              M, N, K
              );
          tileScore[tileIdx] += tileSpeed;
        }

        //if (printDetails) printf("fs=%8.3f, ts=%8.3f\n", fallbackSpeed, tileSpeed );
      } // tile sizes

    } // for k

      /**************************************************************
       * (6) score is gbps averaged over k values
       *************************************************************/
      for (unsigned int tileIdx = 0; tileIdx < numTiles; tileIdx++) {
        fallbackScore[tileIdx] /= numKValues;
        file << fallbackScore[tileIdx] << ", ";
      }
      file << "<-F|T->, ";
      for (unsigned int tileIdx = 0; tileIdx < numTiles; tileIdx++) {
        tileScore[tileIdx] /= numKValues;
        file << tileScore[tileIdx] << ", ";
      }


      /**************************************************************
       * (7) get fastest fallback speed for this system size
       *************************************************************/
      float fastestFallbackScore = 0;
      unsigned int fastestFallbackIdx = 0;
      for (unsigned int tileIdx = 0; tileIdx < numTiles; tileIdx++) {
        if (fallbackScore[tileIdx] > fastestFallbackScore) {
          fastestFallbackScore = fallbackScore[tileIdx];
          fastestFallbackIdx = tileIdx;
        }
      }
      file << tiles[fastestFallbackIdx][0] << "x" << tiles[fastestFallbackIdx][1] << ", ";

      /**************************************************************
       * (8) ensure fallback tile has begun/ended
       *************************************************************/
      //if (fallbackBegin[fastestFallbackIdx] == -1) {
      //  fallbackBegin[fastestFallbackIdx] = static_cast<int>(systemSize);
      //}
      //fallbackEnd[fastestFallbackIdx] = static_cast<int>(systemSize); // push the end back farther


      /**************************************************************
       * (9) which tiles are valid for this system size
       * - tile must be faster than fallback
       * - there must not exist a faster tile which covers the same multiples
       *************************************************************/
      unsigned int numValidTiles = 0;
      float priorFastestTileScore = 99999999;
      for (unsigned int checkIter = 0; checkIter < numTiles; checkIter++) {
        // find the next fastest tile
        float fastestTileScore = -1.f;
        int fastestTileIdx = -1;
        for (unsigned int tileIdx = 0; tileIdx < numTiles; tileIdx++) {
          if (tileScore[tileIdx] > fastestTileScore && (tileScore[tileIdx] < priorFastestTileScore || priorFastestTileScore < 0) ) {
            fastestTileScore = tileScore[tileIdx];
            fastestTileIdx = tileIdx;
          }
        }
        priorFastestTileScore = fastestTileScore;

        // if next fastest tile isn't faster than fallback, then quit
        if (fastestTileScore < fastestFallbackScore-1) break;

        // if the coverage of this tile is already handled by prior (faster) valid tiles, then skip it
        bool uniqueCoverage = true;
        for (unsigned int i = 0; i < numValidTiles; i++) {
          if ( tiles[fastestTileIdx][0] % tiles[ validTiles[i] ][0] == 0
            && tiles[fastestTileIdx][1] % tiles[ validTiles[i] ][1] == 0 )
          {
            uniqueCoverage = false;
            break;
          }
        }
        if (!uniqueCoverage) continue;

        // this tile valid
        validTiles[numValidTiles] = fastestTileIdx;
        numValidTiles++;
      }
      for (unsigned int i = 0; i < numValidTiles; i++) {
        file << tiles[validTiles[i]][0] << "x" << tiles[validTiles[i]][1] << ", ";
      }

      ksr.add(M, N, validTiles, numValidTiles, fastestFallbackIdx );

      // for now, just pay attention to the fastest tile
      //if (numValidTiles > 1) {
      //  numValidTiles = 1;
      //}

      /**************************************************************
       * (10) ensure valid tiles have begun/ended
       *************************************************************/
      //for (unsigned int i = 0; i < numValidTiles; i++) {
      //  if (validBegin[ validTiles[i] ] == -1) {
      //    validBegin[ validTiles[i] ] = static_cast<int>(systemSize);
      //  }
      //  validEnd[ validTiles[i] ] = static_cast<int>(systemSize); // push the end back farther
      //}

      // print valid tiles
      //printf("%4ux%4u; fallback = %ux%u; validTiles = ", M, N, tiles[fastestFallbackIdx][2], tiles[fastestFallbackIdx][3]);
      //for (unsigned int i = 0; i < numValidTiles; i++) {
      //  printf("%ux%u, ", tiles[ validTiles[i] ][2], tiles[ validTiles[i] ][3]);
      //}
      //printf("\n");

      // print tile ranges
      //for (unsigned int i = 0; i < numTiles; i++) {
      //  printf("%4u; %ux%u fallback=[%4i, %4i] tile=[%4i, %4i]\n",
      //    systemSize, tiles[i][2], tiles[i][3],
      //    fallbackBegin[i], fallbackEnd[i],
      //    validBegin[i], validEnd[i] );
      //}
      //printf("\n");
      file << "\n";


  } // for system size

  file.close();
  ksrFile.close();
    //err = clReleaseMemObject(bufA); CL_CHECK(err);
    //err = clReleaseMemObject(bufB); CL_CHECK(err);
    //err = clReleaseMemObject(bufC); CL_CHECK(err);
    //err = clReleaseKernel(kernel); CL_CHECK(err);
    //err = clReleaseCommandQueue(queue); CL_CHECK(err);
    //err = clReleaseContext(context); CL_CHECK(err);

    //free(A);
    //free(B);
    //free(C);
    //free(naiveC);
    //free(source);

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
    CL_CHECK(err);
    assert(err == CL_SUCCESS);
    if (err != CL_SUCCESS) {
        return NULL;
    }

    list = (cl_platform_id*)malloc(nrPlatforms * sizeof(*list));
    if (list == NULL) {
        return NULL;
    }

    err = clGetPlatformIDs(nrPlatforms, list, NULL);
    CL_CHECK(err);
    assert(err == CL_SUCCESS);
    if (err != CL_SUCCESS) {
        free(list);
        return NULL;
    }

    platform = NULL;
    for (i = 0; i < nrPlatforms; i++) {
        err = clGetPlatformInfo(list[i], CL_PLATFORM_NAME,
            sizeof(platformName), platformName, NULL);
    CL_CHECK(err);
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
    cl_platform_id platform)
{

    cl_int err;
    cl_uint nrDevices, i;
    cl_device_id *list, device;
    char deviceName[64];

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, NULL, &nrDevices);
    CL_CHECK(err);
    assert(err == CL_SUCCESS);
    if (err != CL_SUCCESS) {
        return NULL;
    }
    assert( nrDevices > 0 );
    list = (cl_device_id*)malloc(nrDevices * sizeof(*list));
    assert(list);
    if (list == NULL) {
      printf("Error: malloc device list\n");
        return NULL;
    }

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, nrDevices, list, NULL);
    CL_CHECK(err);
    assert(err == CL_SUCCESS);
    if (err != CL_SUCCESS) {
        free(list);
        return NULL;
    }

    device = NULL;
    for (i = 0; i < nrDevices; i++) {
        err = clGetDeviceInfo(list[i], CL_DEVICE_NAME,
            sizeof(deviceName), deviceName, NULL);
        CL_CHECK(err);
        assert(err == CL_SUCCESS);
        if ((err == CL_SUCCESS) ) {
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
    //printf("KernelName[%lu]: %s\n", length, kernelName);

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
