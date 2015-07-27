/*******************************************************************************
 * This file was auto-generated using the auto-gemm.py python script.
 * NO NOT modify this file! Instead, make changes to
 *   clBLAS/src/scripts/auto-gemm/auto-gemm.py then re-generate files
 *   (otherwise local changes will be lost after re-generation).
 * - David Tanner
 ******************************************************************************/

#include "GemmSourceIncludes.h"
#if USE_GEMM_KERNEL_BINARIES
#include "GemmBinaryIncludes.h"
#else
#include "GemmBinaryNulls.h"
#endif
#include "GemmKernelSourceBuildOptions.h"
#include "GemmKernelBinaryBuildOptions.h"
#include "GemmClKernels.h"

#define EXACT_MULTIPLES(MULTIPLE_STR) MULTIPLE_STR

// kernel selection logic template
template<typename Precision>
void gemmSelectKernel(
  clblasOrder order,
  clblasTranspose transA,
  clblasTranspose transB,
  size_t M,
  size_t N,
  size_t K,
  bool betaNonZero,
  float optimalNumElementsPerWorkItem,
  const char **tileKernelSource,
  const char **rowKernelSource,
  const char **colKernelSource,
  const char **cornerKernelSource,
  const char **sourceBuildOptions,
  const unsigned char **tileKernelBinary,
  const unsigned char **rowKernelBinary,
  const unsigned char **colKernelBinary,
  const unsigned char **cornerKernelBinary,
  const char **binaryBuildOptions,
  cl_kernel  **tileClKernel,
  cl_kernel  **rowClKernel,
  cl_kernel  **colClKernel,
  cl_kernel  **cornerClKernel,
  unsigned int *workGroupNumRows,
  unsigned int *workGroupNumCols,
  unsigned int *microTileNumRows,
  unsigned int *microTileNumCols,
  unsigned int *unroll
);

  // sgemm kernel selection logic
template<>
void gemmSelectKernel<float>(
  clblasOrder order,
  clblasTranspose transA,
  clblasTranspose transB,
  size_t M,
  size_t N,
  size_t K,
  bool betaNonZero,
  float optimalNumElementsPerWorkItem,
  const char **tileKernelSource,
  const char **rowKernelSource,
  const char **colKernelSource,
  const char **cornerKernelSource,
  const char **sourceBuildOptions,
  const unsigned char **tileKernelBinary,
  const unsigned char **rowKernelBinary,
  const unsigned char **colKernelBinary,
  const unsigned char **cornerKernelBinary,
  const char **binaryBuildOptions,
  cl_kernel  **tileClKernel,
  cl_kernel  **rowClKernel,
  cl_kernel  **colClKernel,
  cl_kernel  **cornerClKernel,
  unsigned int *workGroupNumRows,
  unsigned int *workGroupNumCols,
  unsigned int *microTileNumRows,
  unsigned int *microTileNumCols,
  unsigned int *unroll
) {
  if (order == clblasColumnMajor) {
    if (transA == clblasNoTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 32) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B0_096_096_08_16x16_6x6_src;
            *rowKernelSource    = sgemm_Col_NN_B0_001_096_08_16x16_6x6_src;
            *colKernelSource    = sgemm_Col_NN_B0_096_001_08_16x16_6x6_src;
            *cornerKernelSource = sgemm_Col_NN_B0_001_001_08_16x16_6x6_src;
            *sourceBuildOptions = sgemm_Col_NN_B0_096_096_08_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B0_096_096_08_16x16_6x6_bin;
            *rowKernelBinary    = sgemm_Col_NN_B0_001_096_08_16x16_6x6_bin;
            *colKernelBinary    = sgemm_Col_NN_B0_096_001_08_16x16_6x6_bin;
            *cornerKernelBinary = sgemm_Col_NN_B0_001_001_08_16x16_6x6_bin;
            *binaryBuildOptions = sgemm_Col_NN_B0_096_096_08_16x16_6x6_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B0_096_096_08_16x16_6x6_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B0_001_096_08_16x16_6x6_clKernel;
            *colClKernel        = &sgemm_Col_NN_B0_096_001_08_16x16_6x6_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B0_001_001_08_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B0_096_096_01_16x16_6x6_src;
            *rowKernelSource    = sgemm_Col_NN_B0_001_096_01_16x16_6x6_src;
            *colKernelSource    = sgemm_Col_NN_B0_096_001_01_16x16_6x6_src;
            *cornerKernelSource = sgemm_Col_NN_B0_001_001_01_16x16_6x6_src;
            *sourceBuildOptions = sgemm_Col_NN_B0_096_096_01_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B0_096_096_01_16x16_6x6_bin;
            *rowKernelBinary    = sgemm_Col_NN_B0_001_096_01_16x16_6x6_bin;
            *colKernelBinary    = sgemm_Col_NN_B0_096_001_01_16x16_6x6_bin;
            *cornerKernelBinary = sgemm_Col_NN_B0_001_001_01_16x16_6x6_bin;
            *binaryBuildOptions = sgemm_Col_NN_B0_096_096_01_16x16_6x6_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B0_096_096_01_16x16_6x6_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B0_001_096_01_16x16_6x6_clKernel;
            *colClKernel        = &sgemm_Col_NN_B0_096_001_01_16x16_6x6_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B0_001_001_01_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B0_128_064_08_16x16_8x4_src;
            *rowKernelSource    = sgemm_Col_NN_B0_001_064_08_16x16_8x4_src;
            *colKernelSource    = sgemm_Col_NN_B0_128_001_08_16x16_8x4_src;
            *cornerKernelSource = sgemm_Col_NN_B0_001_001_08_16x16_8x4_src;
            *sourceBuildOptions = sgemm_Col_NN_B0_128_064_08_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B0_128_064_08_16x16_8x4_bin;
            *rowKernelBinary    = sgemm_Col_NN_B0_001_064_08_16x16_8x4_bin;
            *colKernelBinary    = sgemm_Col_NN_B0_128_001_08_16x16_8x4_bin;
            *cornerKernelBinary = sgemm_Col_NN_B0_001_001_08_16x16_8x4_bin;
            *binaryBuildOptions = sgemm_Col_NN_B0_128_064_08_16x16_8x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B0_128_064_08_16x16_8x4_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B0_001_064_08_16x16_8x4_clKernel;
            *colClKernel        = &sgemm_Col_NN_B0_128_001_08_16x16_8x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B0_001_001_08_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B0_128_064_01_16x16_8x4_src;
            *rowKernelSource    = sgemm_Col_NN_B0_001_064_01_16x16_8x4_src;
            *colKernelSource    = sgemm_Col_NN_B0_128_001_01_16x16_8x4_src;
            *cornerKernelSource = sgemm_Col_NN_B0_001_001_01_16x16_8x4_src;
            *sourceBuildOptions = sgemm_Col_NN_B0_128_064_01_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B0_128_064_01_16x16_8x4_bin;
            *rowKernelBinary    = sgemm_Col_NN_B0_001_064_01_16x16_8x4_bin;
            *colKernelBinary    = sgemm_Col_NN_B0_128_001_01_16x16_8x4_bin;
            *cornerKernelBinary = sgemm_Col_NN_B0_001_001_01_16x16_8x4_bin;
            *binaryBuildOptions = sgemm_Col_NN_B0_128_064_01_16x16_8x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B0_128_064_01_16x16_8x4_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B0_001_064_01_16x16_8x4_clKernel;
            *colClKernel        = &sgemm_Col_NN_B0_128_001_01_16x16_8x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B0_001_001_01_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B0_096_064_08_16x16_6x4_src;
            *rowKernelSource    = sgemm_Col_NN_B0_001_064_08_16x16_6x4_src;
            *colKernelSource    = sgemm_Col_NN_B0_096_001_08_16x16_6x4_src;
            *cornerKernelSource = sgemm_Col_NN_B0_001_001_08_16x16_6x4_src;
            *sourceBuildOptions = sgemm_Col_NN_B0_096_064_08_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B0_096_064_08_16x16_6x4_bin;
            *rowKernelBinary    = sgemm_Col_NN_B0_001_064_08_16x16_6x4_bin;
            *colKernelBinary    = sgemm_Col_NN_B0_096_001_08_16x16_6x4_bin;
            *cornerKernelBinary = sgemm_Col_NN_B0_001_001_08_16x16_6x4_bin;
            *binaryBuildOptions = sgemm_Col_NN_B0_096_064_08_16x16_6x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B0_096_064_08_16x16_6x4_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B0_001_064_08_16x16_6x4_clKernel;
            *colClKernel        = &sgemm_Col_NN_B0_096_001_08_16x16_6x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B0_001_001_08_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B0_096_064_01_16x16_6x4_src;
            *rowKernelSource    = sgemm_Col_NN_B0_001_064_01_16x16_6x4_src;
            *colKernelSource    = sgemm_Col_NN_B0_096_001_01_16x16_6x4_src;
            *cornerKernelSource = sgemm_Col_NN_B0_001_001_01_16x16_6x4_src;
            *sourceBuildOptions = sgemm_Col_NN_B0_096_064_01_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B0_096_064_01_16x16_6x4_bin;
            *rowKernelBinary    = sgemm_Col_NN_B0_001_064_01_16x16_6x4_bin;
            *colKernelBinary    = sgemm_Col_NN_B0_096_001_01_16x16_6x4_bin;
            *cornerKernelBinary = sgemm_Col_NN_B0_001_001_01_16x16_6x4_bin;
            *binaryBuildOptions = sgemm_Col_NN_B0_096_064_01_16x16_6x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B0_096_064_01_16x16_6x4_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B0_001_064_01_16x16_6x4_clKernel;
            *colClKernel        = &sgemm_Col_NN_B0_096_001_01_16x16_6x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B0_001_001_01_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B0_064_064_08_16x16_4x4_src;
            *rowKernelSource    = sgemm_Col_NN_B0_001_064_08_16x16_4x4_src;
            *colKernelSource    = sgemm_Col_NN_B0_064_001_08_16x16_4x4_src;
            *cornerKernelSource = sgemm_Col_NN_B0_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = sgemm_Col_NN_B0_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B0_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = sgemm_Col_NN_B0_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = sgemm_Col_NN_B0_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = sgemm_Col_NN_B0_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = sgemm_Col_NN_B0_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B0_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B0_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &sgemm_Col_NN_B0_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B0_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B0_064_064_01_16x16_4x4_src;
            *rowKernelSource    = sgemm_Col_NN_B0_001_064_01_16x16_4x4_src;
            *colKernelSource    = sgemm_Col_NN_B0_064_001_01_16x16_4x4_src;
            *cornerKernelSource = sgemm_Col_NN_B0_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = sgemm_Col_NN_B0_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B0_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = sgemm_Col_NN_B0_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = sgemm_Col_NN_B0_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = sgemm_Col_NN_B0_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = sgemm_Col_NN_B0_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B0_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B0_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &sgemm_Col_NN_B0_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B0_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = sgemm_Col_NN_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = sgemm_Col_NN_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = sgemm_Col_NN_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = sgemm_Col_NN_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = sgemm_Col_NN_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = sgemm_Col_NN_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = sgemm_Col_NN_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = sgemm_Col_NN_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &sgemm_Col_NN_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = sgemm_Col_NN_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = sgemm_Col_NN_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = sgemm_Col_NN_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = sgemm_Col_NN_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = sgemm_Col_NN_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = sgemm_Col_NN_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = sgemm_Col_NN_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = sgemm_Col_NN_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &sgemm_Col_NN_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = sgemm_Col_NN_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = sgemm_Col_NN_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = sgemm_Col_NN_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = sgemm_Col_NN_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = sgemm_Col_NN_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = sgemm_Col_NN_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = sgemm_Col_NN_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = sgemm_Col_NN_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &sgemm_Col_NN_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = sgemm_Col_NN_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = sgemm_Col_NN_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = sgemm_Col_NN_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = sgemm_Col_NN_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = sgemm_Col_NN_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = sgemm_Col_NN_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = sgemm_Col_NN_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = sgemm_Col_NN_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &sgemm_Col_NN_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = sgemm_Col_NN_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = sgemm_Col_NN_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = sgemm_Col_NN_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = sgemm_Col_NN_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = sgemm_Col_NN_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = sgemm_Col_NN_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = sgemm_Col_NN_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = sgemm_Col_NN_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &sgemm_Col_NN_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = sgemm_Col_NN_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = sgemm_Col_NN_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = sgemm_Col_NN_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = sgemm_Col_NN_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = sgemm_Col_NN_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = sgemm_Col_NN_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = sgemm_Col_NN_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = sgemm_Col_NN_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &sgemm_Col_NN_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = sgemm_Col_NN_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = sgemm_Col_NN_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = sgemm_Col_NN_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = sgemm_Col_NN_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = sgemm_Col_NN_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = sgemm_Col_NN_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = sgemm_Col_NN_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = sgemm_Col_NN_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &sgemm_Col_NN_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = sgemm_Col_NN_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = sgemm_Col_NN_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = sgemm_Col_NN_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = sgemm_Col_NN_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = sgemm_Col_NN_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = sgemm_Col_NN_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = sgemm_Col_NN_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = sgemm_Col_NN_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &sgemm_Col_NN_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 32) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B1_096_096_08_16x16_6x6_src;
            *rowKernelSource    = sgemm_Col_NN_B1_001_096_08_16x16_6x6_src;
            *colKernelSource    = sgemm_Col_NN_B1_096_001_08_16x16_6x6_src;
            *cornerKernelSource = sgemm_Col_NN_B1_001_001_08_16x16_6x6_src;
            *sourceBuildOptions = sgemm_Col_NN_B1_096_096_08_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B1_096_096_08_16x16_6x6_bin;
            *rowKernelBinary    = sgemm_Col_NN_B1_001_096_08_16x16_6x6_bin;
            *colKernelBinary    = sgemm_Col_NN_B1_096_001_08_16x16_6x6_bin;
            *cornerKernelBinary = sgemm_Col_NN_B1_001_001_08_16x16_6x6_bin;
            *binaryBuildOptions = sgemm_Col_NN_B1_096_096_08_16x16_6x6_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B1_096_096_08_16x16_6x6_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B1_001_096_08_16x16_6x6_clKernel;
            *colClKernel        = &sgemm_Col_NN_B1_096_001_08_16x16_6x6_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B1_001_001_08_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B1_096_096_01_16x16_6x6_src;
            *rowKernelSource    = sgemm_Col_NN_B1_001_096_01_16x16_6x6_src;
            *colKernelSource    = sgemm_Col_NN_B1_096_001_01_16x16_6x6_src;
            *cornerKernelSource = sgemm_Col_NN_B1_001_001_01_16x16_6x6_src;
            *sourceBuildOptions = sgemm_Col_NN_B1_096_096_01_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B1_096_096_01_16x16_6x6_bin;
            *rowKernelBinary    = sgemm_Col_NN_B1_001_096_01_16x16_6x6_bin;
            *colKernelBinary    = sgemm_Col_NN_B1_096_001_01_16x16_6x6_bin;
            *cornerKernelBinary = sgemm_Col_NN_B1_001_001_01_16x16_6x6_bin;
            *binaryBuildOptions = sgemm_Col_NN_B1_096_096_01_16x16_6x6_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B1_096_096_01_16x16_6x6_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B1_001_096_01_16x16_6x6_clKernel;
            *colClKernel        = &sgemm_Col_NN_B1_096_001_01_16x16_6x6_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B1_001_001_01_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B1_128_064_08_16x16_8x4_src;
            *rowKernelSource    = sgemm_Col_NN_B1_001_064_08_16x16_8x4_src;
            *colKernelSource    = sgemm_Col_NN_B1_128_001_08_16x16_8x4_src;
            *cornerKernelSource = sgemm_Col_NN_B1_001_001_08_16x16_8x4_src;
            *sourceBuildOptions = sgemm_Col_NN_B1_128_064_08_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B1_128_064_08_16x16_8x4_bin;
            *rowKernelBinary    = sgemm_Col_NN_B1_001_064_08_16x16_8x4_bin;
            *colKernelBinary    = sgemm_Col_NN_B1_128_001_08_16x16_8x4_bin;
            *cornerKernelBinary = sgemm_Col_NN_B1_001_001_08_16x16_8x4_bin;
            *binaryBuildOptions = sgemm_Col_NN_B1_128_064_08_16x16_8x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B1_128_064_08_16x16_8x4_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B1_001_064_08_16x16_8x4_clKernel;
            *colClKernel        = &sgemm_Col_NN_B1_128_001_08_16x16_8x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B1_001_001_08_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B1_128_064_01_16x16_8x4_src;
            *rowKernelSource    = sgemm_Col_NN_B1_001_064_01_16x16_8x4_src;
            *colKernelSource    = sgemm_Col_NN_B1_128_001_01_16x16_8x4_src;
            *cornerKernelSource = sgemm_Col_NN_B1_001_001_01_16x16_8x4_src;
            *sourceBuildOptions = sgemm_Col_NN_B1_128_064_01_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B1_128_064_01_16x16_8x4_bin;
            *rowKernelBinary    = sgemm_Col_NN_B1_001_064_01_16x16_8x4_bin;
            *colKernelBinary    = sgemm_Col_NN_B1_128_001_01_16x16_8x4_bin;
            *cornerKernelBinary = sgemm_Col_NN_B1_001_001_01_16x16_8x4_bin;
            *binaryBuildOptions = sgemm_Col_NN_B1_128_064_01_16x16_8x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B1_128_064_01_16x16_8x4_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B1_001_064_01_16x16_8x4_clKernel;
            *colClKernel        = &sgemm_Col_NN_B1_128_001_01_16x16_8x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B1_001_001_01_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B1_096_064_08_16x16_6x4_src;
            *rowKernelSource    = sgemm_Col_NN_B1_001_064_08_16x16_6x4_src;
            *colKernelSource    = sgemm_Col_NN_B1_096_001_08_16x16_6x4_src;
            *cornerKernelSource = sgemm_Col_NN_B1_001_001_08_16x16_6x4_src;
            *sourceBuildOptions = sgemm_Col_NN_B1_096_064_08_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B1_096_064_08_16x16_6x4_bin;
            *rowKernelBinary    = sgemm_Col_NN_B1_001_064_08_16x16_6x4_bin;
            *colKernelBinary    = sgemm_Col_NN_B1_096_001_08_16x16_6x4_bin;
            *cornerKernelBinary = sgemm_Col_NN_B1_001_001_08_16x16_6x4_bin;
            *binaryBuildOptions = sgemm_Col_NN_B1_096_064_08_16x16_6x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B1_096_064_08_16x16_6x4_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B1_001_064_08_16x16_6x4_clKernel;
            *colClKernel        = &sgemm_Col_NN_B1_096_001_08_16x16_6x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B1_001_001_08_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B1_096_064_01_16x16_6x4_src;
            *rowKernelSource    = sgemm_Col_NN_B1_001_064_01_16x16_6x4_src;
            *colKernelSource    = sgemm_Col_NN_B1_096_001_01_16x16_6x4_src;
            *cornerKernelSource = sgemm_Col_NN_B1_001_001_01_16x16_6x4_src;
            *sourceBuildOptions = sgemm_Col_NN_B1_096_064_01_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B1_096_064_01_16x16_6x4_bin;
            *rowKernelBinary    = sgemm_Col_NN_B1_001_064_01_16x16_6x4_bin;
            *colKernelBinary    = sgemm_Col_NN_B1_096_001_01_16x16_6x4_bin;
            *cornerKernelBinary = sgemm_Col_NN_B1_001_001_01_16x16_6x4_bin;
            *binaryBuildOptions = sgemm_Col_NN_B1_096_064_01_16x16_6x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B1_096_064_01_16x16_6x4_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B1_001_064_01_16x16_6x4_clKernel;
            *colClKernel        = &sgemm_Col_NN_B1_096_001_01_16x16_6x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B1_001_001_01_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B1_064_064_08_16x16_4x4_src;
            *rowKernelSource    = sgemm_Col_NN_B1_001_064_08_16x16_4x4_src;
            *colKernelSource    = sgemm_Col_NN_B1_064_001_08_16x16_4x4_src;
            *cornerKernelSource = sgemm_Col_NN_B1_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = sgemm_Col_NN_B1_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B1_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = sgemm_Col_NN_B1_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = sgemm_Col_NN_B1_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = sgemm_Col_NN_B1_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = sgemm_Col_NN_B1_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B1_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B1_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &sgemm_Col_NN_B1_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B1_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B1_064_064_01_16x16_4x4_src;
            *rowKernelSource    = sgemm_Col_NN_B1_001_064_01_16x16_4x4_src;
            *colKernelSource    = sgemm_Col_NN_B1_064_001_01_16x16_4x4_src;
            *cornerKernelSource = sgemm_Col_NN_B1_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = sgemm_Col_NN_B1_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B1_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = sgemm_Col_NN_B1_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = sgemm_Col_NN_B1_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = sgemm_Col_NN_B1_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = sgemm_Col_NN_B1_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B1_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B1_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &sgemm_Col_NN_B1_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B1_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = sgemm_Col_NN_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = sgemm_Col_NN_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = sgemm_Col_NN_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = sgemm_Col_NN_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = sgemm_Col_NN_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = sgemm_Col_NN_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = sgemm_Col_NN_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = sgemm_Col_NN_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &sgemm_Col_NN_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = sgemm_Col_NN_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = sgemm_Col_NN_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = sgemm_Col_NN_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = sgemm_Col_NN_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = sgemm_Col_NN_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = sgemm_Col_NN_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = sgemm_Col_NN_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = sgemm_Col_NN_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &sgemm_Col_NN_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = sgemm_Col_NN_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = sgemm_Col_NN_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = sgemm_Col_NN_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = sgemm_Col_NN_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = sgemm_Col_NN_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = sgemm_Col_NN_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = sgemm_Col_NN_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = sgemm_Col_NN_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &sgemm_Col_NN_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = sgemm_Col_NN_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = sgemm_Col_NN_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = sgemm_Col_NN_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = sgemm_Col_NN_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = sgemm_Col_NN_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = sgemm_Col_NN_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = sgemm_Col_NN_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = sgemm_Col_NN_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &sgemm_Col_NN_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = sgemm_Col_NN_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = sgemm_Col_NN_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = sgemm_Col_NN_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = sgemm_Col_NN_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = sgemm_Col_NN_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = sgemm_Col_NN_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = sgemm_Col_NN_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = sgemm_Col_NN_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &sgemm_Col_NN_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = sgemm_Col_NN_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = sgemm_Col_NN_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = sgemm_Col_NN_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = sgemm_Col_NN_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = sgemm_Col_NN_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = sgemm_Col_NN_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = sgemm_Col_NN_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = sgemm_Col_NN_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &sgemm_Col_NN_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = sgemm_Col_NN_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = sgemm_Col_NN_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = sgemm_Col_NN_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = sgemm_Col_NN_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = sgemm_Col_NN_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = sgemm_Col_NN_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = sgemm_Col_NN_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = sgemm_Col_NN_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &sgemm_Col_NN_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NN_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = sgemm_Col_NN_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = sgemm_Col_NN_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = sgemm_Col_NN_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = sgemm_Col_NN_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NN_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = sgemm_Col_NN_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = sgemm_Col_NN_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = sgemm_Col_NN_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = sgemm_Col_NN_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NN_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &sgemm_Col_NN_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &sgemm_Col_NN_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &sgemm_Col_NN_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasNoTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 32) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B0_096_096_08_16x16_6x6_src;
            *rowKernelSource    = sgemm_Col_NT_B0_001_096_08_16x16_6x6_src;
            *colKernelSource    = sgemm_Col_NT_B0_096_001_08_16x16_6x6_src;
            *cornerKernelSource = sgemm_Col_NT_B0_001_001_08_16x16_6x6_src;
            *sourceBuildOptions = sgemm_Col_NT_B0_096_096_08_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B0_096_096_08_16x16_6x6_bin;
            *rowKernelBinary    = sgemm_Col_NT_B0_001_096_08_16x16_6x6_bin;
            *colKernelBinary    = sgemm_Col_NT_B0_096_001_08_16x16_6x6_bin;
            *cornerKernelBinary = sgemm_Col_NT_B0_001_001_08_16x16_6x6_bin;
            *binaryBuildOptions = sgemm_Col_NT_B0_096_096_08_16x16_6x6_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B0_096_096_08_16x16_6x6_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B0_001_096_08_16x16_6x6_clKernel;
            *colClKernel        = &sgemm_Col_NT_B0_096_001_08_16x16_6x6_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B0_001_001_08_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B0_096_096_01_16x16_6x6_src;
            *rowKernelSource    = sgemm_Col_NT_B0_001_096_01_16x16_6x6_src;
            *colKernelSource    = sgemm_Col_NT_B0_096_001_01_16x16_6x6_src;
            *cornerKernelSource = sgemm_Col_NT_B0_001_001_01_16x16_6x6_src;
            *sourceBuildOptions = sgemm_Col_NT_B0_096_096_01_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B0_096_096_01_16x16_6x6_bin;
            *rowKernelBinary    = sgemm_Col_NT_B0_001_096_01_16x16_6x6_bin;
            *colKernelBinary    = sgemm_Col_NT_B0_096_001_01_16x16_6x6_bin;
            *cornerKernelBinary = sgemm_Col_NT_B0_001_001_01_16x16_6x6_bin;
            *binaryBuildOptions = sgemm_Col_NT_B0_096_096_01_16x16_6x6_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B0_096_096_01_16x16_6x6_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B0_001_096_01_16x16_6x6_clKernel;
            *colClKernel        = &sgemm_Col_NT_B0_096_001_01_16x16_6x6_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B0_001_001_01_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B0_128_064_08_16x16_8x4_src;
            *rowKernelSource    = sgemm_Col_NT_B0_001_064_08_16x16_8x4_src;
            *colKernelSource    = sgemm_Col_NT_B0_128_001_08_16x16_8x4_src;
            *cornerKernelSource = sgemm_Col_NT_B0_001_001_08_16x16_8x4_src;
            *sourceBuildOptions = sgemm_Col_NT_B0_128_064_08_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B0_128_064_08_16x16_8x4_bin;
            *rowKernelBinary    = sgemm_Col_NT_B0_001_064_08_16x16_8x4_bin;
            *colKernelBinary    = sgemm_Col_NT_B0_128_001_08_16x16_8x4_bin;
            *cornerKernelBinary = sgemm_Col_NT_B0_001_001_08_16x16_8x4_bin;
            *binaryBuildOptions = sgemm_Col_NT_B0_128_064_08_16x16_8x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B0_128_064_08_16x16_8x4_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B0_001_064_08_16x16_8x4_clKernel;
            *colClKernel        = &sgemm_Col_NT_B0_128_001_08_16x16_8x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B0_001_001_08_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B0_128_064_01_16x16_8x4_src;
            *rowKernelSource    = sgemm_Col_NT_B0_001_064_01_16x16_8x4_src;
            *colKernelSource    = sgemm_Col_NT_B0_128_001_01_16x16_8x4_src;
            *cornerKernelSource = sgemm_Col_NT_B0_001_001_01_16x16_8x4_src;
            *sourceBuildOptions = sgemm_Col_NT_B0_128_064_01_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B0_128_064_01_16x16_8x4_bin;
            *rowKernelBinary    = sgemm_Col_NT_B0_001_064_01_16x16_8x4_bin;
            *colKernelBinary    = sgemm_Col_NT_B0_128_001_01_16x16_8x4_bin;
            *cornerKernelBinary = sgemm_Col_NT_B0_001_001_01_16x16_8x4_bin;
            *binaryBuildOptions = sgemm_Col_NT_B0_128_064_01_16x16_8x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B0_128_064_01_16x16_8x4_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B0_001_064_01_16x16_8x4_clKernel;
            *colClKernel        = &sgemm_Col_NT_B0_128_001_01_16x16_8x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B0_001_001_01_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B0_096_064_08_16x16_6x4_src;
            *rowKernelSource    = sgemm_Col_NT_B0_001_064_08_16x16_6x4_src;
            *colKernelSource    = sgemm_Col_NT_B0_096_001_08_16x16_6x4_src;
            *cornerKernelSource = sgemm_Col_NT_B0_001_001_08_16x16_6x4_src;
            *sourceBuildOptions = sgemm_Col_NT_B0_096_064_08_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B0_096_064_08_16x16_6x4_bin;
            *rowKernelBinary    = sgemm_Col_NT_B0_001_064_08_16x16_6x4_bin;
            *colKernelBinary    = sgemm_Col_NT_B0_096_001_08_16x16_6x4_bin;
            *cornerKernelBinary = sgemm_Col_NT_B0_001_001_08_16x16_6x4_bin;
            *binaryBuildOptions = sgemm_Col_NT_B0_096_064_08_16x16_6x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B0_096_064_08_16x16_6x4_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B0_001_064_08_16x16_6x4_clKernel;
            *colClKernel        = &sgemm_Col_NT_B0_096_001_08_16x16_6x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B0_001_001_08_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B0_096_064_01_16x16_6x4_src;
            *rowKernelSource    = sgemm_Col_NT_B0_001_064_01_16x16_6x4_src;
            *colKernelSource    = sgemm_Col_NT_B0_096_001_01_16x16_6x4_src;
            *cornerKernelSource = sgemm_Col_NT_B0_001_001_01_16x16_6x4_src;
            *sourceBuildOptions = sgemm_Col_NT_B0_096_064_01_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B0_096_064_01_16x16_6x4_bin;
            *rowKernelBinary    = sgemm_Col_NT_B0_001_064_01_16x16_6x4_bin;
            *colKernelBinary    = sgemm_Col_NT_B0_096_001_01_16x16_6x4_bin;
            *cornerKernelBinary = sgemm_Col_NT_B0_001_001_01_16x16_6x4_bin;
            *binaryBuildOptions = sgemm_Col_NT_B0_096_064_01_16x16_6x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B0_096_064_01_16x16_6x4_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B0_001_064_01_16x16_6x4_clKernel;
            *colClKernel        = &sgemm_Col_NT_B0_096_001_01_16x16_6x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B0_001_001_01_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B0_064_064_08_16x16_4x4_src;
            *rowKernelSource    = sgemm_Col_NT_B0_001_064_08_16x16_4x4_src;
            *colKernelSource    = sgemm_Col_NT_B0_064_001_08_16x16_4x4_src;
            *cornerKernelSource = sgemm_Col_NT_B0_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = sgemm_Col_NT_B0_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B0_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = sgemm_Col_NT_B0_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = sgemm_Col_NT_B0_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = sgemm_Col_NT_B0_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = sgemm_Col_NT_B0_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B0_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B0_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &sgemm_Col_NT_B0_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B0_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B0_064_064_01_16x16_4x4_src;
            *rowKernelSource    = sgemm_Col_NT_B0_001_064_01_16x16_4x4_src;
            *colKernelSource    = sgemm_Col_NT_B0_064_001_01_16x16_4x4_src;
            *cornerKernelSource = sgemm_Col_NT_B0_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = sgemm_Col_NT_B0_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B0_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = sgemm_Col_NT_B0_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = sgemm_Col_NT_B0_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = sgemm_Col_NT_B0_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = sgemm_Col_NT_B0_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B0_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B0_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &sgemm_Col_NT_B0_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B0_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = sgemm_Col_NT_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = sgemm_Col_NT_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = sgemm_Col_NT_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = sgemm_Col_NT_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = sgemm_Col_NT_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = sgemm_Col_NT_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = sgemm_Col_NT_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = sgemm_Col_NT_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &sgemm_Col_NT_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = sgemm_Col_NT_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = sgemm_Col_NT_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = sgemm_Col_NT_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = sgemm_Col_NT_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = sgemm_Col_NT_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = sgemm_Col_NT_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = sgemm_Col_NT_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = sgemm_Col_NT_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &sgemm_Col_NT_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = sgemm_Col_NT_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = sgemm_Col_NT_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = sgemm_Col_NT_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = sgemm_Col_NT_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = sgemm_Col_NT_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = sgemm_Col_NT_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = sgemm_Col_NT_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = sgemm_Col_NT_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &sgemm_Col_NT_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = sgemm_Col_NT_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = sgemm_Col_NT_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = sgemm_Col_NT_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = sgemm_Col_NT_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = sgemm_Col_NT_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = sgemm_Col_NT_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = sgemm_Col_NT_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = sgemm_Col_NT_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &sgemm_Col_NT_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = sgemm_Col_NT_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = sgemm_Col_NT_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = sgemm_Col_NT_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = sgemm_Col_NT_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = sgemm_Col_NT_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = sgemm_Col_NT_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = sgemm_Col_NT_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = sgemm_Col_NT_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &sgemm_Col_NT_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = sgemm_Col_NT_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = sgemm_Col_NT_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = sgemm_Col_NT_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = sgemm_Col_NT_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = sgemm_Col_NT_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = sgemm_Col_NT_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = sgemm_Col_NT_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = sgemm_Col_NT_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &sgemm_Col_NT_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = sgemm_Col_NT_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = sgemm_Col_NT_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = sgemm_Col_NT_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = sgemm_Col_NT_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = sgemm_Col_NT_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = sgemm_Col_NT_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = sgemm_Col_NT_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = sgemm_Col_NT_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &sgemm_Col_NT_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = sgemm_Col_NT_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = sgemm_Col_NT_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = sgemm_Col_NT_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = sgemm_Col_NT_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = sgemm_Col_NT_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = sgemm_Col_NT_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = sgemm_Col_NT_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = sgemm_Col_NT_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &sgemm_Col_NT_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 32) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B1_096_096_08_16x16_6x6_src;
            *rowKernelSource    = sgemm_Col_NT_B1_001_096_08_16x16_6x6_src;
            *colKernelSource    = sgemm_Col_NT_B1_096_001_08_16x16_6x6_src;
            *cornerKernelSource = sgemm_Col_NT_B1_001_001_08_16x16_6x6_src;
            *sourceBuildOptions = sgemm_Col_NT_B1_096_096_08_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B1_096_096_08_16x16_6x6_bin;
            *rowKernelBinary    = sgemm_Col_NT_B1_001_096_08_16x16_6x6_bin;
            *colKernelBinary    = sgemm_Col_NT_B1_096_001_08_16x16_6x6_bin;
            *cornerKernelBinary = sgemm_Col_NT_B1_001_001_08_16x16_6x6_bin;
            *binaryBuildOptions = sgemm_Col_NT_B1_096_096_08_16x16_6x6_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B1_096_096_08_16x16_6x6_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B1_001_096_08_16x16_6x6_clKernel;
            *colClKernel        = &sgemm_Col_NT_B1_096_001_08_16x16_6x6_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B1_001_001_08_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B1_096_096_01_16x16_6x6_src;
            *rowKernelSource    = sgemm_Col_NT_B1_001_096_01_16x16_6x6_src;
            *colKernelSource    = sgemm_Col_NT_B1_096_001_01_16x16_6x6_src;
            *cornerKernelSource = sgemm_Col_NT_B1_001_001_01_16x16_6x6_src;
            *sourceBuildOptions = sgemm_Col_NT_B1_096_096_01_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B1_096_096_01_16x16_6x6_bin;
            *rowKernelBinary    = sgemm_Col_NT_B1_001_096_01_16x16_6x6_bin;
            *colKernelBinary    = sgemm_Col_NT_B1_096_001_01_16x16_6x6_bin;
            *cornerKernelBinary = sgemm_Col_NT_B1_001_001_01_16x16_6x6_bin;
            *binaryBuildOptions = sgemm_Col_NT_B1_096_096_01_16x16_6x6_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B1_096_096_01_16x16_6x6_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B1_001_096_01_16x16_6x6_clKernel;
            *colClKernel        = &sgemm_Col_NT_B1_096_001_01_16x16_6x6_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B1_001_001_01_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B1_128_064_08_16x16_8x4_src;
            *rowKernelSource    = sgemm_Col_NT_B1_001_064_08_16x16_8x4_src;
            *colKernelSource    = sgemm_Col_NT_B1_128_001_08_16x16_8x4_src;
            *cornerKernelSource = sgemm_Col_NT_B1_001_001_08_16x16_8x4_src;
            *sourceBuildOptions = sgemm_Col_NT_B1_128_064_08_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B1_128_064_08_16x16_8x4_bin;
            *rowKernelBinary    = sgemm_Col_NT_B1_001_064_08_16x16_8x4_bin;
            *colKernelBinary    = sgemm_Col_NT_B1_128_001_08_16x16_8x4_bin;
            *cornerKernelBinary = sgemm_Col_NT_B1_001_001_08_16x16_8x4_bin;
            *binaryBuildOptions = sgemm_Col_NT_B1_128_064_08_16x16_8x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B1_128_064_08_16x16_8x4_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B1_001_064_08_16x16_8x4_clKernel;
            *colClKernel        = &sgemm_Col_NT_B1_128_001_08_16x16_8x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B1_001_001_08_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B1_128_064_01_16x16_8x4_src;
            *rowKernelSource    = sgemm_Col_NT_B1_001_064_01_16x16_8x4_src;
            *colKernelSource    = sgemm_Col_NT_B1_128_001_01_16x16_8x4_src;
            *cornerKernelSource = sgemm_Col_NT_B1_001_001_01_16x16_8x4_src;
            *sourceBuildOptions = sgemm_Col_NT_B1_128_064_01_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B1_128_064_01_16x16_8x4_bin;
            *rowKernelBinary    = sgemm_Col_NT_B1_001_064_01_16x16_8x4_bin;
            *colKernelBinary    = sgemm_Col_NT_B1_128_001_01_16x16_8x4_bin;
            *cornerKernelBinary = sgemm_Col_NT_B1_001_001_01_16x16_8x4_bin;
            *binaryBuildOptions = sgemm_Col_NT_B1_128_064_01_16x16_8x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B1_128_064_01_16x16_8x4_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B1_001_064_01_16x16_8x4_clKernel;
            *colClKernel        = &sgemm_Col_NT_B1_128_001_01_16x16_8x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B1_001_001_01_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B1_096_064_08_16x16_6x4_src;
            *rowKernelSource    = sgemm_Col_NT_B1_001_064_08_16x16_6x4_src;
            *colKernelSource    = sgemm_Col_NT_B1_096_001_08_16x16_6x4_src;
            *cornerKernelSource = sgemm_Col_NT_B1_001_001_08_16x16_6x4_src;
            *sourceBuildOptions = sgemm_Col_NT_B1_096_064_08_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B1_096_064_08_16x16_6x4_bin;
            *rowKernelBinary    = sgemm_Col_NT_B1_001_064_08_16x16_6x4_bin;
            *colKernelBinary    = sgemm_Col_NT_B1_096_001_08_16x16_6x4_bin;
            *cornerKernelBinary = sgemm_Col_NT_B1_001_001_08_16x16_6x4_bin;
            *binaryBuildOptions = sgemm_Col_NT_B1_096_064_08_16x16_6x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B1_096_064_08_16x16_6x4_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B1_001_064_08_16x16_6x4_clKernel;
            *colClKernel        = &sgemm_Col_NT_B1_096_001_08_16x16_6x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B1_001_001_08_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B1_096_064_01_16x16_6x4_src;
            *rowKernelSource    = sgemm_Col_NT_B1_001_064_01_16x16_6x4_src;
            *colKernelSource    = sgemm_Col_NT_B1_096_001_01_16x16_6x4_src;
            *cornerKernelSource = sgemm_Col_NT_B1_001_001_01_16x16_6x4_src;
            *sourceBuildOptions = sgemm_Col_NT_B1_096_064_01_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B1_096_064_01_16x16_6x4_bin;
            *rowKernelBinary    = sgemm_Col_NT_B1_001_064_01_16x16_6x4_bin;
            *colKernelBinary    = sgemm_Col_NT_B1_096_001_01_16x16_6x4_bin;
            *cornerKernelBinary = sgemm_Col_NT_B1_001_001_01_16x16_6x4_bin;
            *binaryBuildOptions = sgemm_Col_NT_B1_096_064_01_16x16_6x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B1_096_064_01_16x16_6x4_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B1_001_064_01_16x16_6x4_clKernel;
            *colClKernel        = &sgemm_Col_NT_B1_096_001_01_16x16_6x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B1_001_001_01_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B1_064_064_08_16x16_4x4_src;
            *rowKernelSource    = sgemm_Col_NT_B1_001_064_08_16x16_4x4_src;
            *colKernelSource    = sgemm_Col_NT_B1_064_001_08_16x16_4x4_src;
            *cornerKernelSource = sgemm_Col_NT_B1_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = sgemm_Col_NT_B1_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B1_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = sgemm_Col_NT_B1_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = sgemm_Col_NT_B1_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = sgemm_Col_NT_B1_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = sgemm_Col_NT_B1_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B1_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B1_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &sgemm_Col_NT_B1_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B1_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B1_064_064_01_16x16_4x4_src;
            *rowKernelSource    = sgemm_Col_NT_B1_001_064_01_16x16_4x4_src;
            *colKernelSource    = sgemm_Col_NT_B1_064_001_01_16x16_4x4_src;
            *cornerKernelSource = sgemm_Col_NT_B1_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = sgemm_Col_NT_B1_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B1_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = sgemm_Col_NT_B1_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = sgemm_Col_NT_B1_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = sgemm_Col_NT_B1_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = sgemm_Col_NT_B1_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B1_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B1_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &sgemm_Col_NT_B1_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B1_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = sgemm_Col_NT_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = sgemm_Col_NT_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = sgemm_Col_NT_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = sgemm_Col_NT_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = sgemm_Col_NT_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = sgemm_Col_NT_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = sgemm_Col_NT_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = sgemm_Col_NT_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &sgemm_Col_NT_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = sgemm_Col_NT_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = sgemm_Col_NT_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = sgemm_Col_NT_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = sgemm_Col_NT_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = sgemm_Col_NT_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = sgemm_Col_NT_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = sgemm_Col_NT_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = sgemm_Col_NT_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &sgemm_Col_NT_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = sgemm_Col_NT_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = sgemm_Col_NT_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = sgemm_Col_NT_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = sgemm_Col_NT_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = sgemm_Col_NT_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = sgemm_Col_NT_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = sgemm_Col_NT_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = sgemm_Col_NT_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &sgemm_Col_NT_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = sgemm_Col_NT_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = sgemm_Col_NT_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = sgemm_Col_NT_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = sgemm_Col_NT_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = sgemm_Col_NT_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = sgemm_Col_NT_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = sgemm_Col_NT_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = sgemm_Col_NT_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &sgemm_Col_NT_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = sgemm_Col_NT_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = sgemm_Col_NT_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = sgemm_Col_NT_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = sgemm_Col_NT_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = sgemm_Col_NT_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = sgemm_Col_NT_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = sgemm_Col_NT_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = sgemm_Col_NT_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &sgemm_Col_NT_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = sgemm_Col_NT_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = sgemm_Col_NT_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = sgemm_Col_NT_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = sgemm_Col_NT_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = sgemm_Col_NT_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = sgemm_Col_NT_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = sgemm_Col_NT_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = sgemm_Col_NT_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &sgemm_Col_NT_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = sgemm_Col_NT_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = sgemm_Col_NT_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = sgemm_Col_NT_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = sgemm_Col_NT_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = sgemm_Col_NT_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = sgemm_Col_NT_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = sgemm_Col_NT_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = sgemm_Col_NT_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &sgemm_Col_NT_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_NT_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = sgemm_Col_NT_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = sgemm_Col_NT_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = sgemm_Col_NT_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = sgemm_Col_NT_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_NT_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = sgemm_Col_NT_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = sgemm_Col_NT_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = sgemm_Col_NT_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = sgemm_Col_NT_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_NT_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &sgemm_Col_NT_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &sgemm_Col_NT_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &sgemm_Col_NT_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 32) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B0_096_096_08_16x16_6x6_src;
            *rowKernelSource    = sgemm_Col_TN_B0_001_096_08_16x16_6x6_src;
            *colKernelSource    = sgemm_Col_TN_B0_096_001_08_16x16_6x6_src;
            *cornerKernelSource = sgemm_Col_TN_B0_001_001_08_16x16_6x6_src;
            *sourceBuildOptions = sgemm_Col_TN_B0_096_096_08_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B0_096_096_08_16x16_6x6_bin;
            *rowKernelBinary    = sgemm_Col_TN_B0_001_096_08_16x16_6x6_bin;
            *colKernelBinary    = sgemm_Col_TN_B0_096_001_08_16x16_6x6_bin;
            *cornerKernelBinary = sgemm_Col_TN_B0_001_001_08_16x16_6x6_bin;
            *binaryBuildOptions = sgemm_Col_TN_B0_096_096_08_16x16_6x6_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B0_096_096_08_16x16_6x6_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B0_001_096_08_16x16_6x6_clKernel;
            *colClKernel        = &sgemm_Col_TN_B0_096_001_08_16x16_6x6_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B0_001_001_08_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B0_096_096_01_16x16_6x6_src;
            *rowKernelSource    = sgemm_Col_TN_B0_001_096_01_16x16_6x6_src;
            *colKernelSource    = sgemm_Col_TN_B0_096_001_01_16x16_6x6_src;
            *cornerKernelSource = sgemm_Col_TN_B0_001_001_01_16x16_6x6_src;
            *sourceBuildOptions = sgemm_Col_TN_B0_096_096_01_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B0_096_096_01_16x16_6x6_bin;
            *rowKernelBinary    = sgemm_Col_TN_B0_001_096_01_16x16_6x6_bin;
            *colKernelBinary    = sgemm_Col_TN_B0_096_001_01_16x16_6x6_bin;
            *cornerKernelBinary = sgemm_Col_TN_B0_001_001_01_16x16_6x6_bin;
            *binaryBuildOptions = sgemm_Col_TN_B0_096_096_01_16x16_6x6_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B0_096_096_01_16x16_6x6_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B0_001_096_01_16x16_6x6_clKernel;
            *colClKernel        = &sgemm_Col_TN_B0_096_001_01_16x16_6x6_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B0_001_001_01_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B0_128_064_08_16x16_8x4_src;
            *rowKernelSource    = sgemm_Col_TN_B0_001_064_08_16x16_8x4_src;
            *colKernelSource    = sgemm_Col_TN_B0_128_001_08_16x16_8x4_src;
            *cornerKernelSource = sgemm_Col_TN_B0_001_001_08_16x16_8x4_src;
            *sourceBuildOptions = sgemm_Col_TN_B0_128_064_08_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B0_128_064_08_16x16_8x4_bin;
            *rowKernelBinary    = sgemm_Col_TN_B0_001_064_08_16x16_8x4_bin;
            *colKernelBinary    = sgemm_Col_TN_B0_128_001_08_16x16_8x4_bin;
            *cornerKernelBinary = sgemm_Col_TN_B0_001_001_08_16x16_8x4_bin;
            *binaryBuildOptions = sgemm_Col_TN_B0_128_064_08_16x16_8x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B0_128_064_08_16x16_8x4_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B0_001_064_08_16x16_8x4_clKernel;
            *colClKernel        = &sgemm_Col_TN_B0_128_001_08_16x16_8x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B0_001_001_08_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B0_128_064_01_16x16_8x4_src;
            *rowKernelSource    = sgemm_Col_TN_B0_001_064_01_16x16_8x4_src;
            *colKernelSource    = sgemm_Col_TN_B0_128_001_01_16x16_8x4_src;
            *cornerKernelSource = sgemm_Col_TN_B0_001_001_01_16x16_8x4_src;
            *sourceBuildOptions = sgemm_Col_TN_B0_128_064_01_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B0_128_064_01_16x16_8x4_bin;
            *rowKernelBinary    = sgemm_Col_TN_B0_001_064_01_16x16_8x4_bin;
            *colKernelBinary    = sgemm_Col_TN_B0_128_001_01_16x16_8x4_bin;
            *cornerKernelBinary = sgemm_Col_TN_B0_001_001_01_16x16_8x4_bin;
            *binaryBuildOptions = sgemm_Col_TN_B0_128_064_01_16x16_8x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B0_128_064_01_16x16_8x4_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B0_001_064_01_16x16_8x4_clKernel;
            *colClKernel        = &sgemm_Col_TN_B0_128_001_01_16x16_8x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B0_001_001_01_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B0_096_064_08_16x16_6x4_src;
            *rowKernelSource    = sgemm_Col_TN_B0_001_064_08_16x16_6x4_src;
            *colKernelSource    = sgemm_Col_TN_B0_096_001_08_16x16_6x4_src;
            *cornerKernelSource = sgemm_Col_TN_B0_001_001_08_16x16_6x4_src;
            *sourceBuildOptions = sgemm_Col_TN_B0_096_064_08_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B0_096_064_08_16x16_6x4_bin;
            *rowKernelBinary    = sgemm_Col_TN_B0_001_064_08_16x16_6x4_bin;
            *colKernelBinary    = sgemm_Col_TN_B0_096_001_08_16x16_6x4_bin;
            *cornerKernelBinary = sgemm_Col_TN_B0_001_001_08_16x16_6x4_bin;
            *binaryBuildOptions = sgemm_Col_TN_B0_096_064_08_16x16_6x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B0_096_064_08_16x16_6x4_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B0_001_064_08_16x16_6x4_clKernel;
            *colClKernel        = &sgemm_Col_TN_B0_096_001_08_16x16_6x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B0_001_001_08_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B0_096_064_01_16x16_6x4_src;
            *rowKernelSource    = sgemm_Col_TN_B0_001_064_01_16x16_6x4_src;
            *colKernelSource    = sgemm_Col_TN_B0_096_001_01_16x16_6x4_src;
            *cornerKernelSource = sgemm_Col_TN_B0_001_001_01_16x16_6x4_src;
            *sourceBuildOptions = sgemm_Col_TN_B0_096_064_01_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B0_096_064_01_16x16_6x4_bin;
            *rowKernelBinary    = sgemm_Col_TN_B0_001_064_01_16x16_6x4_bin;
            *colKernelBinary    = sgemm_Col_TN_B0_096_001_01_16x16_6x4_bin;
            *cornerKernelBinary = sgemm_Col_TN_B0_001_001_01_16x16_6x4_bin;
            *binaryBuildOptions = sgemm_Col_TN_B0_096_064_01_16x16_6x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B0_096_064_01_16x16_6x4_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B0_001_064_01_16x16_6x4_clKernel;
            *colClKernel        = &sgemm_Col_TN_B0_096_001_01_16x16_6x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B0_001_001_01_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B0_064_064_08_16x16_4x4_src;
            *rowKernelSource    = sgemm_Col_TN_B0_001_064_08_16x16_4x4_src;
            *colKernelSource    = sgemm_Col_TN_B0_064_001_08_16x16_4x4_src;
            *cornerKernelSource = sgemm_Col_TN_B0_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = sgemm_Col_TN_B0_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B0_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = sgemm_Col_TN_B0_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = sgemm_Col_TN_B0_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = sgemm_Col_TN_B0_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = sgemm_Col_TN_B0_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B0_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B0_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &sgemm_Col_TN_B0_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B0_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B0_064_064_01_16x16_4x4_src;
            *rowKernelSource    = sgemm_Col_TN_B0_001_064_01_16x16_4x4_src;
            *colKernelSource    = sgemm_Col_TN_B0_064_001_01_16x16_4x4_src;
            *cornerKernelSource = sgemm_Col_TN_B0_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = sgemm_Col_TN_B0_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B0_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = sgemm_Col_TN_B0_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = sgemm_Col_TN_B0_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = sgemm_Col_TN_B0_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = sgemm_Col_TN_B0_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B0_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B0_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &sgemm_Col_TN_B0_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B0_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = sgemm_Col_TN_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = sgemm_Col_TN_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = sgemm_Col_TN_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = sgemm_Col_TN_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = sgemm_Col_TN_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = sgemm_Col_TN_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = sgemm_Col_TN_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = sgemm_Col_TN_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &sgemm_Col_TN_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = sgemm_Col_TN_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = sgemm_Col_TN_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = sgemm_Col_TN_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = sgemm_Col_TN_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = sgemm_Col_TN_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = sgemm_Col_TN_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = sgemm_Col_TN_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = sgemm_Col_TN_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &sgemm_Col_TN_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = sgemm_Col_TN_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = sgemm_Col_TN_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = sgemm_Col_TN_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = sgemm_Col_TN_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = sgemm_Col_TN_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = sgemm_Col_TN_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = sgemm_Col_TN_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = sgemm_Col_TN_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &sgemm_Col_TN_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = sgemm_Col_TN_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = sgemm_Col_TN_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = sgemm_Col_TN_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = sgemm_Col_TN_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = sgemm_Col_TN_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = sgemm_Col_TN_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = sgemm_Col_TN_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = sgemm_Col_TN_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &sgemm_Col_TN_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = sgemm_Col_TN_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = sgemm_Col_TN_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = sgemm_Col_TN_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = sgemm_Col_TN_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = sgemm_Col_TN_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = sgemm_Col_TN_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = sgemm_Col_TN_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = sgemm_Col_TN_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &sgemm_Col_TN_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = sgemm_Col_TN_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = sgemm_Col_TN_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = sgemm_Col_TN_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = sgemm_Col_TN_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = sgemm_Col_TN_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = sgemm_Col_TN_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = sgemm_Col_TN_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = sgemm_Col_TN_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &sgemm_Col_TN_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = sgemm_Col_TN_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = sgemm_Col_TN_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = sgemm_Col_TN_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = sgemm_Col_TN_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = sgemm_Col_TN_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = sgemm_Col_TN_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = sgemm_Col_TN_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = sgemm_Col_TN_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &sgemm_Col_TN_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = sgemm_Col_TN_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = sgemm_Col_TN_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = sgemm_Col_TN_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = sgemm_Col_TN_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = sgemm_Col_TN_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = sgemm_Col_TN_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = sgemm_Col_TN_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = sgemm_Col_TN_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &sgemm_Col_TN_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 32) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B1_096_096_08_16x16_6x6_src;
            *rowKernelSource    = sgemm_Col_TN_B1_001_096_08_16x16_6x6_src;
            *colKernelSource    = sgemm_Col_TN_B1_096_001_08_16x16_6x6_src;
            *cornerKernelSource = sgemm_Col_TN_B1_001_001_08_16x16_6x6_src;
            *sourceBuildOptions = sgemm_Col_TN_B1_096_096_08_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B1_096_096_08_16x16_6x6_bin;
            *rowKernelBinary    = sgemm_Col_TN_B1_001_096_08_16x16_6x6_bin;
            *colKernelBinary    = sgemm_Col_TN_B1_096_001_08_16x16_6x6_bin;
            *cornerKernelBinary = sgemm_Col_TN_B1_001_001_08_16x16_6x6_bin;
            *binaryBuildOptions = sgemm_Col_TN_B1_096_096_08_16x16_6x6_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B1_096_096_08_16x16_6x6_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B1_001_096_08_16x16_6x6_clKernel;
            *colClKernel        = &sgemm_Col_TN_B1_096_001_08_16x16_6x6_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B1_001_001_08_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B1_096_096_01_16x16_6x6_src;
            *rowKernelSource    = sgemm_Col_TN_B1_001_096_01_16x16_6x6_src;
            *colKernelSource    = sgemm_Col_TN_B1_096_001_01_16x16_6x6_src;
            *cornerKernelSource = sgemm_Col_TN_B1_001_001_01_16x16_6x6_src;
            *sourceBuildOptions = sgemm_Col_TN_B1_096_096_01_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B1_096_096_01_16x16_6x6_bin;
            *rowKernelBinary    = sgemm_Col_TN_B1_001_096_01_16x16_6x6_bin;
            *colKernelBinary    = sgemm_Col_TN_B1_096_001_01_16x16_6x6_bin;
            *cornerKernelBinary = sgemm_Col_TN_B1_001_001_01_16x16_6x6_bin;
            *binaryBuildOptions = sgemm_Col_TN_B1_096_096_01_16x16_6x6_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B1_096_096_01_16x16_6x6_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B1_001_096_01_16x16_6x6_clKernel;
            *colClKernel        = &sgemm_Col_TN_B1_096_001_01_16x16_6x6_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B1_001_001_01_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B1_128_064_08_16x16_8x4_src;
            *rowKernelSource    = sgemm_Col_TN_B1_001_064_08_16x16_8x4_src;
            *colKernelSource    = sgemm_Col_TN_B1_128_001_08_16x16_8x4_src;
            *cornerKernelSource = sgemm_Col_TN_B1_001_001_08_16x16_8x4_src;
            *sourceBuildOptions = sgemm_Col_TN_B1_128_064_08_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B1_128_064_08_16x16_8x4_bin;
            *rowKernelBinary    = sgemm_Col_TN_B1_001_064_08_16x16_8x4_bin;
            *colKernelBinary    = sgemm_Col_TN_B1_128_001_08_16x16_8x4_bin;
            *cornerKernelBinary = sgemm_Col_TN_B1_001_001_08_16x16_8x4_bin;
            *binaryBuildOptions = sgemm_Col_TN_B1_128_064_08_16x16_8x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B1_128_064_08_16x16_8x4_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B1_001_064_08_16x16_8x4_clKernel;
            *colClKernel        = &sgemm_Col_TN_B1_128_001_08_16x16_8x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B1_001_001_08_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B1_128_064_01_16x16_8x4_src;
            *rowKernelSource    = sgemm_Col_TN_B1_001_064_01_16x16_8x4_src;
            *colKernelSource    = sgemm_Col_TN_B1_128_001_01_16x16_8x4_src;
            *cornerKernelSource = sgemm_Col_TN_B1_001_001_01_16x16_8x4_src;
            *sourceBuildOptions = sgemm_Col_TN_B1_128_064_01_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B1_128_064_01_16x16_8x4_bin;
            *rowKernelBinary    = sgemm_Col_TN_B1_001_064_01_16x16_8x4_bin;
            *colKernelBinary    = sgemm_Col_TN_B1_128_001_01_16x16_8x4_bin;
            *cornerKernelBinary = sgemm_Col_TN_B1_001_001_01_16x16_8x4_bin;
            *binaryBuildOptions = sgemm_Col_TN_B1_128_064_01_16x16_8x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B1_128_064_01_16x16_8x4_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B1_001_064_01_16x16_8x4_clKernel;
            *colClKernel        = &sgemm_Col_TN_B1_128_001_01_16x16_8x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B1_001_001_01_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B1_096_064_08_16x16_6x4_src;
            *rowKernelSource    = sgemm_Col_TN_B1_001_064_08_16x16_6x4_src;
            *colKernelSource    = sgemm_Col_TN_B1_096_001_08_16x16_6x4_src;
            *cornerKernelSource = sgemm_Col_TN_B1_001_001_08_16x16_6x4_src;
            *sourceBuildOptions = sgemm_Col_TN_B1_096_064_08_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B1_096_064_08_16x16_6x4_bin;
            *rowKernelBinary    = sgemm_Col_TN_B1_001_064_08_16x16_6x4_bin;
            *colKernelBinary    = sgemm_Col_TN_B1_096_001_08_16x16_6x4_bin;
            *cornerKernelBinary = sgemm_Col_TN_B1_001_001_08_16x16_6x4_bin;
            *binaryBuildOptions = sgemm_Col_TN_B1_096_064_08_16x16_6x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B1_096_064_08_16x16_6x4_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B1_001_064_08_16x16_6x4_clKernel;
            *colClKernel        = &sgemm_Col_TN_B1_096_001_08_16x16_6x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B1_001_001_08_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B1_096_064_01_16x16_6x4_src;
            *rowKernelSource    = sgemm_Col_TN_B1_001_064_01_16x16_6x4_src;
            *colKernelSource    = sgemm_Col_TN_B1_096_001_01_16x16_6x4_src;
            *cornerKernelSource = sgemm_Col_TN_B1_001_001_01_16x16_6x4_src;
            *sourceBuildOptions = sgemm_Col_TN_B1_096_064_01_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B1_096_064_01_16x16_6x4_bin;
            *rowKernelBinary    = sgemm_Col_TN_B1_001_064_01_16x16_6x4_bin;
            *colKernelBinary    = sgemm_Col_TN_B1_096_001_01_16x16_6x4_bin;
            *cornerKernelBinary = sgemm_Col_TN_B1_001_001_01_16x16_6x4_bin;
            *binaryBuildOptions = sgemm_Col_TN_B1_096_064_01_16x16_6x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B1_096_064_01_16x16_6x4_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B1_001_064_01_16x16_6x4_clKernel;
            *colClKernel        = &sgemm_Col_TN_B1_096_001_01_16x16_6x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B1_001_001_01_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B1_064_064_08_16x16_4x4_src;
            *rowKernelSource    = sgemm_Col_TN_B1_001_064_08_16x16_4x4_src;
            *colKernelSource    = sgemm_Col_TN_B1_064_001_08_16x16_4x4_src;
            *cornerKernelSource = sgemm_Col_TN_B1_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = sgemm_Col_TN_B1_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B1_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = sgemm_Col_TN_B1_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = sgemm_Col_TN_B1_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = sgemm_Col_TN_B1_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = sgemm_Col_TN_B1_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B1_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B1_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &sgemm_Col_TN_B1_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B1_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B1_064_064_01_16x16_4x4_src;
            *rowKernelSource    = sgemm_Col_TN_B1_001_064_01_16x16_4x4_src;
            *colKernelSource    = sgemm_Col_TN_B1_064_001_01_16x16_4x4_src;
            *cornerKernelSource = sgemm_Col_TN_B1_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = sgemm_Col_TN_B1_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B1_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = sgemm_Col_TN_B1_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = sgemm_Col_TN_B1_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = sgemm_Col_TN_B1_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = sgemm_Col_TN_B1_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B1_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B1_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &sgemm_Col_TN_B1_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B1_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = sgemm_Col_TN_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = sgemm_Col_TN_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = sgemm_Col_TN_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = sgemm_Col_TN_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = sgemm_Col_TN_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = sgemm_Col_TN_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = sgemm_Col_TN_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = sgemm_Col_TN_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &sgemm_Col_TN_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = sgemm_Col_TN_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = sgemm_Col_TN_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = sgemm_Col_TN_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = sgemm_Col_TN_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = sgemm_Col_TN_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = sgemm_Col_TN_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = sgemm_Col_TN_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = sgemm_Col_TN_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &sgemm_Col_TN_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = sgemm_Col_TN_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = sgemm_Col_TN_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = sgemm_Col_TN_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = sgemm_Col_TN_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = sgemm_Col_TN_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = sgemm_Col_TN_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = sgemm_Col_TN_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = sgemm_Col_TN_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &sgemm_Col_TN_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = sgemm_Col_TN_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = sgemm_Col_TN_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = sgemm_Col_TN_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = sgemm_Col_TN_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = sgemm_Col_TN_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = sgemm_Col_TN_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = sgemm_Col_TN_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = sgemm_Col_TN_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &sgemm_Col_TN_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = sgemm_Col_TN_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = sgemm_Col_TN_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = sgemm_Col_TN_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = sgemm_Col_TN_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = sgemm_Col_TN_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = sgemm_Col_TN_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = sgemm_Col_TN_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = sgemm_Col_TN_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &sgemm_Col_TN_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = sgemm_Col_TN_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = sgemm_Col_TN_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = sgemm_Col_TN_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = sgemm_Col_TN_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = sgemm_Col_TN_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = sgemm_Col_TN_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = sgemm_Col_TN_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = sgemm_Col_TN_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &sgemm_Col_TN_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = sgemm_Col_TN_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = sgemm_Col_TN_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = sgemm_Col_TN_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = sgemm_Col_TN_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = sgemm_Col_TN_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = sgemm_Col_TN_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = sgemm_Col_TN_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = sgemm_Col_TN_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &sgemm_Col_TN_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TN_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = sgemm_Col_TN_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = sgemm_Col_TN_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = sgemm_Col_TN_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = sgemm_Col_TN_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TN_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = sgemm_Col_TN_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = sgemm_Col_TN_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = sgemm_Col_TN_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = sgemm_Col_TN_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TN_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &sgemm_Col_TN_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &sgemm_Col_TN_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &sgemm_Col_TN_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 32) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B0_096_096_08_16x16_6x6_src;
            *rowKernelSource    = sgemm_Col_TT_B0_001_096_08_16x16_6x6_src;
            *colKernelSource    = sgemm_Col_TT_B0_096_001_08_16x16_6x6_src;
            *cornerKernelSource = sgemm_Col_TT_B0_001_001_08_16x16_6x6_src;
            *sourceBuildOptions = sgemm_Col_TT_B0_096_096_08_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B0_096_096_08_16x16_6x6_bin;
            *rowKernelBinary    = sgemm_Col_TT_B0_001_096_08_16x16_6x6_bin;
            *colKernelBinary    = sgemm_Col_TT_B0_096_001_08_16x16_6x6_bin;
            *cornerKernelBinary = sgemm_Col_TT_B0_001_001_08_16x16_6x6_bin;
            *binaryBuildOptions = sgemm_Col_TT_B0_096_096_08_16x16_6x6_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B0_096_096_08_16x16_6x6_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B0_001_096_08_16x16_6x6_clKernel;
            *colClKernel        = &sgemm_Col_TT_B0_096_001_08_16x16_6x6_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B0_001_001_08_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B0_096_096_01_16x16_6x6_src;
            *rowKernelSource    = sgemm_Col_TT_B0_001_096_01_16x16_6x6_src;
            *colKernelSource    = sgemm_Col_TT_B0_096_001_01_16x16_6x6_src;
            *cornerKernelSource = sgemm_Col_TT_B0_001_001_01_16x16_6x6_src;
            *sourceBuildOptions = sgemm_Col_TT_B0_096_096_01_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B0_096_096_01_16x16_6x6_bin;
            *rowKernelBinary    = sgemm_Col_TT_B0_001_096_01_16x16_6x6_bin;
            *colKernelBinary    = sgemm_Col_TT_B0_096_001_01_16x16_6x6_bin;
            *cornerKernelBinary = sgemm_Col_TT_B0_001_001_01_16x16_6x6_bin;
            *binaryBuildOptions = sgemm_Col_TT_B0_096_096_01_16x16_6x6_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B0_096_096_01_16x16_6x6_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B0_001_096_01_16x16_6x6_clKernel;
            *colClKernel        = &sgemm_Col_TT_B0_096_001_01_16x16_6x6_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B0_001_001_01_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B0_128_064_08_16x16_8x4_src;
            *rowKernelSource    = sgemm_Col_TT_B0_001_064_08_16x16_8x4_src;
            *colKernelSource    = sgemm_Col_TT_B0_128_001_08_16x16_8x4_src;
            *cornerKernelSource = sgemm_Col_TT_B0_001_001_08_16x16_8x4_src;
            *sourceBuildOptions = sgemm_Col_TT_B0_128_064_08_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B0_128_064_08_16x16_8x4_bin;
            *rowKernelBinary    = sgemm_Col_TT_B0_001_064_08_16x16_8x4_bin;
            *colKernelBinary    = sgemm_Col_TT_B0_128_001_08_16x16_8x4_bin;
            *cornerKernelBinary = sgemm_Col_TT_B0_001_001_08_16x16_8x4_bin;
            *binaryBuildOptions = sgemm_Col_TT_B0_128_064_08_16x16_8x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B0_128_064_08_16x16_8x4_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B0_001_064_08_16x16_8x4_clKernel;
            *colClKernel        = &sgemm_Col_TT_B0_128_001_08_16x16_8x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B0_001_001_08_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B0_128_064_01_16x16_8x4_src;
            *rowKernelSource    = sgemm_Col_TT_B0_001_064_01_16x16_8x4_src;
            *colKernelSource    = sgemm_Col_TT_B0_128_001_01_16x16_8x4_src;
            *cornerKernelSource = sgemm_Col_TT_B0_001_001_01_16x16_8x4_src;
            *sourceBuildOptions = sgemm_Col_TT_B0_128_064_01_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B0_128_064_01_16x16_8x4_bin;
            *rowKernelBinary    = sgemm_Col_TT_B0_001_064_01_16x16_8x4_bin;
            *colKernelBinary    = sgemm_Col_TT_B0_128_001_01_16x16_8x4_bin;
            *cornerKernelBinary = sgemm_Col_TT_B0_001_001_01_16x16_8x4_bin;
            *binaryBuildOptions = sgemm_Col_TT_B0_128_064_01_16x16_8x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B0_128_064_01_16x16_8x4_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B0_001_064_01_16x16_8x4_clKernel;
            *colClKernel        = &sgemm_Col_TT_B0_128_001_01_16x16_8x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B0_001_001_01_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B0_096_064_08_16x16_6x4_src;
            *rowKernelSource    = sgemm_Col_TT_B0_001_064_08_16x16_6x4_src;
            *colKernelSource    = sgemm_Col_TT_B0_096_001_08_16x16_6x4_src;
            *cornerKernelSource = sgemm_Col_TT_B0_001_001_08_16x16_6x4_src;
            *sourceBuildOptions = sgemm_Col_TT_B0_096_064_08_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B0_096_064_08_16x16_6x4_bin;
            *rowKernelBinary    = sgemm_Col_TT_B0_001_064_08_16x16_6x4_bin;
            *colKernelBinary    = sgemm_Col_TT_B0_096_001_08_16x16_6x4_bin;
            *cornerKernelBinary = sgemm_Col_TT_B0_001_001_08_16x16_6x4_bin;
            *binaryBuildOptions = sgemm_Col_TT_B0_096_064_08_16x16_6x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B0_096_064_08_16x16_6x4_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B0_001_064_08_16x16_6x4_clKernel;
            *colClKernel        = &sgemm_Col_TT_B0_096_001_08_16x16_6x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B0_001_001_08_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B0_096_064_01_16x16_6x4_src;
            *rowKernelSource    = sgemm_Col_TT_B0_001_064_01_16x16_6x4_src;
            *colKernelSource    = sgemm_Col_TT_B0_096_001_01_16x16_6x4_src;
            *cornerKernelSource = sgemm_Col_TT_B0_001_001_01_16x16_6x4_src;
            *sourceBuildOptions = sgemm_Col_TT_B0_096_064_01_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B0_096_064_01_16x16_6x4_bin;
            *rowKernelBinary    = sgemm_Col_TT_B0_001_064_01_16x16_6x4_bin;
            *colKernelBinary    = sgemm_Col_TT_B0_096_001_01_16x16_6x4_bin;
            *cornerKernelBinary = sgemm_Col_TT_B0_001_001_01_16x16_6x4_bin;
            *binaryBuildOptions = sgemm_Col_TT_B0_096_064_01_16x16_6x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B0_096_064_01_16x16_6x4_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B0_001_064_01_16x16_6x4_clKernel;
            *colClKernel        = &sgemm_Col_TT_B0_096_001_01_16x16_6x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B0_001_001_01_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B0_064_064_08_16x16_4x4_src;
            *rowKernelSource    = sgemm_Col_TT_B0_001_064_08_16x16_4x4_src;
            *colKernelSource    = sgemm_Col_TT_B0_064_001_08_16x16_4x4_src;
            *cornerKernelSource = sgemm_Col_TT_B0_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = sgemm_Col_TT_B0_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B0_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = sgemm_Col_TT_B0_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = sgemm_Col_TT_B0_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = sgemm_Col_TT_B0_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = sgemm_Col_TT_B0_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B0_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B0_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &sgemm_Col_TT_B0_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B0_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B0_064_064_01_16x16_4x4_src;
            *rowKernelSource    = sgemm_Col_TT_B0_001_064_01_16x16_4x4_src;
            *colKernelSource    = sgemm_Col_TT_B0_064_001_01_16x16_4x4_src;
            *cornerKernelSource = sgemm_Col_TT_B0_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = sgemm_Col_TT_B0_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B0_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = sgemm_Col_TT_B0_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = sgemm_Col_TT_B0_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = sgemm_Col_TT_B0_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = sgemm_Col_TT_B0_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B0_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B0_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &sgemm_Col_TT_B0_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B0_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = sgemm_Col_TT_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = sgemm_Col_TT_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = sgemm_Col_TT_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = sgemm_Col_TT_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = sgemm_Col_TT_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = sgemm_Col_TT_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = sgemm_Col_TT_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = sgemm_Col_TT_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &sgemm_Col_TT_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = sgemm_Col_TT_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = sgemm_Col_TT_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = sgemm_Col_TT_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = sgemm_Col_TT_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = sgemm_Col_TT_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = sgemm_Col_TT_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = sgemm_Col_TT_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = sgemm_Col_TT_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &sgemm_Col_TT_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = sgemm_Col_TT_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = sgemm_Col_TT_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = sgemm_Col_TT_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = sgemm_Col_TT_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = sgemm_Col_TT_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = sgemm_Col_TT_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = sgemm_Col_TT_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = sgemm_Col_TT_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &sgemm_Col_TT_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = sgemm_Col_TT_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = sgemm_Col_TT_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = sgemm_Col_TT_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = sgemm_Col_TT_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = sgemm_Col_TT_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = sgemm_Col_TT_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = sgemm_Col_TT_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = sgemm_Col_TT_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &sgemm_Col_TT_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = sgemm_Col_TT_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = sgemm_Col_TT_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = sgemm_Col_TT_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = sgemm_Col_TT_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = sgemm_Col_TT_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = sgemm_Col_TT_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = sgemm_Col_TT_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = sgemm_Col_TT_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &sgemm_Col_TT_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = sgemm_Col_TT_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = sgemm_Col_TT_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = sgemm_Col_TT_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = sgemm_Col_TT_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = sgemm_Col_TT_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = sgemm_Col_TT_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = sgemm_Col_TT_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = sgemm_Col_TT_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &sgemm_Col_TT_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = sgemm_Col_TT_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = sgemm_Col_TT_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = sgemm_Col_TT_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = sgemm_Col_TT_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = sgemm_Col_TT_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = sgemm_Col_TT_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = sgemm_Col_TT_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = sgemm_Col_TT_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &sgemm_Col_TT_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = sgemm_Col_TT_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = sgemm_Col_TT_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = sgemm_Col_TT_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = sgemm_Col_TT_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = sgemm_Col_TT_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = sgemm_Col_TT_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = sgemm_Col_TT_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = sgemm_Col_TT_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &sgemm_Col_TT_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 32) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B1_096_096_08_16x16_6x6_src;
            *rowKernelSource    = sgemm_Col_TT_B1_001_096_08_16x16_6x6_src;
            *colKernelSource    = sgemm_Col_TT_B1_096_001_08_16x16_6x6_src;
            *cornerKernelSource = sgemm_Col_TT_B1_001_001_08_16x16_6x6_src;
            *sourceBuildOptions = sgemm_Col_TT_B1_096_096_08_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B1_096_096_08_16x16_6x6_bin;
            *rowKernelBinary    = sgemm_Col_TT_B1_001_096_08_16x16_6x6_bin;
            *colKernelBinary    = sgemm_Col_TT_B1_096_001_08_16x16_6x6_bin;
            *cornerKernelBinary = sgemm_Col_TT_B1_001_001_08_16x16_6x6_bin;
            *binaryBuildOptions = sgemm_Col_TT_B1_096_096_08_16x16_6x6_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B1_096_096_08_16x16_6x6_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B1_001_096_08_16x16_6x6_clKernel;
            *colClKernel        = &sgemm_Col_TT_B1_096_001_08_16x16_6x6_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B1_001_001_08_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B1_096_096_01_16x16_6x6_src;
            *rowKernelSource    = sgemm_Col_TT_B1_001_096_01_16x16_6x6_src;
            *colKernelSource    = sgemm_Col_TT_B1_096_001_01_16x16_6x6_src;
            *cornerKernelSource = sgemm_Col_TT_B1_001_001_01_16x16_6x6_src;
            *sourceBuildOptions = sgemm_Col_TT_B1_096_096_01_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B1_096_096_01_16x16_6x6_bin;
            *rowKernelBinary    = sgemm_Col_TT_B1_001_096_01_16x16_6x6_bin;
            *colKernelBinary    = sgemm_Col_TT_B1_096_001_01_16x16_6x6_bin;
            *cornerKernelBinary = sgemm_Col_TT_B1_001_001_01_16x16_6x6_bin;
            *binaryBuildOptions = sgemm_Col_TT_B1_096_096_01_16x16_6x6_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B1_096_096_01_16x16_6x6_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B1_001_096_01_16x16_6x6_clKernel;
            *colClKernel        = &sgemm_Col_TT_B1_096_001_01_16x16_6x6_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B1_001_001_01_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B1_128_064_08_16x16_8x4_src;
            *rowKernelSource    = sgemm_Col_TT_B1_001_064_08_16x16_8x4_src;
            *colKernelSource    = sgemm_Col_TT_B1_128_001_08_16x16_8x4_src;
            *cornerKernelSource = sgemm_Col_TT_B1_001_001_08_16x16_8x4_src;
            *sourceBuildOptions = sgemm_Col_TT_B1_128_064_08_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B1_128_064_08_16x16_8x4_bin;
            *rowKernelBinary    = sgemm_Col_TT_B1_001_064_08_16x16_8x4_bin;
            *colKernelBinary    = sgemm_Col_TT_B1_128_001_08_16x16_8x4_bin;
            *cornerKernelBinary = sgemm_Col_TT_B1_001_001_08_16x16_8x4_bin;
            *binaryBuildOptions = sgemm_Col_TT_B1_128_064_08_16x16_8x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B1_128_064_08_16x16_8x4_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B1_001_064_08_16x16_8x4_clKernel;
            *colClKernel        = &sgemm_Col_TT_B1_128_001_08_16x16_8x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B1_001_001_08_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B1_128_064_01_16x16_8x4_src;
            *rowKernelSource    = sgemm_Col_TT_B1_001_064_01_16x16_8x4_src;
            *colKernelSource    = sgemm_Col_TT_B1_128_001_01_16x16_8x4_src;
            *cornerKernelSource = sgemm_Col_TT_B1_001_001_01_16x16_8x4_src;
            *sourceBuildOptions = sgemm_Col_TT_B1_128_064_01_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B1_128_064_01_16x16_8x4_bin;
            *rowKernelBinary    = sgemm_Col_TT_B1_001_064_01_16x16_8x4_bin;
            *colKernelBinary    = sgemm_Col_TT_B1_128_001_01_16x16_8x4_bin;
            *cornerKernelBinary = sgemm_Col_TT_B1_001_001_01_16x16_8x4_bin;
            *binaryBuildOptions = sgemm_Col_TT_B1_128_064_01_16x16_8x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B1_128_064_01_16x16_8x4_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B1_001_064_01_16x16_8x4_clKernel;
            *colClKernel        = &sgemm_Col_TT_B1_128_001_01_16x16_8x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B1_001_001_01_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B1_096_064_08_16x16_6x4_src;
            *rowKernelSource    = sgemm_Col_TT_B1_001_064_08_16x16_6x4_src;
            *colKernelSource    = sgemm_Col_TT_B1_096_001_08_16x16_6x4_src;
            *cornerKernelSource = sgemm_Col_TT_B1_001_001_08_16x16_6x4_src;
            *sourceBuildOptions = sgemm_Col_TT_B1_096_064_08_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B1_096_064_08_16x16_6x4_bin;
            *rowKernelBinary    = sgemm_Col_TT_B1_001_064_08_16x16_6x4_bin;
            *colKernelBinary    = sgemm_Col_TT_B1_096_001_08_16x16_6x4_bin;
            *cornerKernelBinary = sgemm_Col_TT_B1_001_001_08_16x16_6x4_bin;
            *binaryBuildOptions = sgemm_Col_TT_B1_096_064_08_16x16_6x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B1_096_064_08_16x16_6x4_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B1_001_064_08_16x16_6x4_clKernel;
            *colClKernel        = &sgemm_Col_TT_B1_096_001_08_16x16_6x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B1_001_001_08_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B1_096_064_01_16x16_6x4_src;
            *rowKernelSource    = sgemm_Col_TT_B1_001_064_01_16x16_6x4_src;
            *colKernelSource    = sgemm_Col_TT_B1_096_001_01_16x16_6x4_src;
            *cornerKernelSource = sgemm_Col_TT_B1_001_001_01_16x16_6x4_src;
            *sourceBuildOptions = sgemm_Col_TT_B1_096_064_01_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B1_096_064_01_16x16_6x4_bin;
            *rowKernelBinary    = sgemm_Col_TT_B1_001_064_01_16x16_6x4_bin;
            *colKernelBinary    = sgemm_Col_TT_B1_096_001_01_16x16_6x4_bin;
            *cornerKernelBinary = sgemm_Col_TT_B1_001_001_01_16x16_6x4_bin;
            *binaryBuildOptions = sgemm_Col_TT_B1_096_064_01_16x16_6x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B1_096_064_01_16x16_6x4_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B1_001_064_01_16x16_6x4_clKernel;
            *colClKernel        = &sgemm_Col_TT_B1_096_001_01_16x16_6x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B1_001_001_01_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B1_064_064_08_16x16_4x4_src;
            *rowKernelSource    = sgemm_Col_TT_B1_001_064_08_16x16_4x4_src;
            *colKernelSource    = sgemm_Col_TT_B1_064_001_08_16x16_4x4_src;
            *cornerKernelSource = sgemm_Col_TT_B1_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = sgemm_Col_TT_B1_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B1_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = sgemm_Col_TT_B1_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = sgemm_Col_TT_B1_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = sgemm_Col_TT_B1_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = sgemm_Col_TT_B1_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B1_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B1_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &sgemm_Col_TT_B1_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B1_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B1_064_064_01_16x16_4x4_src;
            *rowKernelSource    = sgemm_Col_TT_B1_001_064_01_16x16_4x4_src;
            *colKernelSource    = sgemm_Col_TT_B1_064_001_01_16x16_4x4_src;
            *cornerKernelSource = sgemm_Col_TT_B1_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = sgemm_Col_TT_B1_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B1_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = sgemm_Col_TT_B1_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = sgemm_Col_TT_B1_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = sgemm_Col_TT_B1_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = sgemm_Col_TT_B1_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B1_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B1_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &sgemm_Col_TT_B1_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B1_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = sgemm_Col_TT_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = sgemm_Col_TT_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = sgemm_Col_TT_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = sgemm_Col_TT_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = sgemm_Col_TT_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = sgemm_Col_TT_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = sgemm_Col_TT_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = sgemm_Col_TT_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &sgemm_Col_TT_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = sgemm_Col_TT_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = sgemm_Col_TT_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = sgemm_Col_TT_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = sgemm_Col_TT_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = sgemm_Col_TT_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = sgemm_Col_TT_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = sgemm_Col_TT_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = sgemm_Col_TT_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &sgemm_Col_TT_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = sgemm_Col_TT_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = sgemm_Col_TT_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = sgemm_Col_TT_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = sgemm_Col_TT_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = sgemm_Col_TT_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = sgemm_Col_TT_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = sgemm_Col_TT_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = sgemm_Col_TT_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &sgemm_Col_TT_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = sgemm_Col_TT_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = sgemm_Col_TT_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = sgemm_Col_TT_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = sgemm_Col_TT_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = sgemm_Col_TT_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = sgemm_Col_TT_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = sgemm_Col_TT_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = sgemm_Col_TT_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &sgemm_Col_TT_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = sgemm_Col_TT_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = sgemm_Col_TT_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = sgemm_Col_TT_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = sgemm_Col_TT_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = sgemm_Col_TT_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = sgemm_Col_TT_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = sgemm_Col_TT_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = sgemm_Col_TT_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &sgemm_Col_TT_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = sgemm_Col_TT_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = sgemm_Col_TT_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = sgemm_Col_TT_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = sgemm_Col_TT_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = sgemm_Col_TT_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = sgemm_Col_TT_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = sgemm_Col_TT_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = sgemm_Col_TT_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &sgemm_Col_TT_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = sgemm_Col_TT_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = sgemm_Col_TT_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = sgemm_Col_TT_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = sgemm_Col_TT_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = sgemm_Col_TT_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = sgemm_Col_TT_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = sgemm_Col_TT_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = sgemm_Col_TT_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &sgemm_Col_TT_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = sgemm_Col_TT_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = sgemm_Col_TT_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = sgemm_Col_TT_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = sgemm_Col_TT_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = sgemm_Col_TT_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = sgemm_Col_TT_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = sgemm_Col_TT_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = sgemm_Col_TT_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = sgemm_Col_TT_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = sgemm_Col_TT_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &sgemm_Col_TT_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &sgemm_Col_TT_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &sgemm_Col_TT_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &sgemm_Col_TT_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    }
  }
}

// dgemm kernel selection logic
template<>
void gemmSelectKernel<double>(
  clblasOrder order,
  clblasTranspose transA,
  clblasTranspose transB,
  size_t M,
  size_t N,
  size_t K,
  bool betaNonZero,
  float optimalNumElementsPerWorkItem,
  const char **tileKernelSource,
  const char **rowKernelSource,
  const char **colKernelSource,
  const char **cornerKernelSource,
  const char **sourceBuildOptions,
  const unsigned char **tileKernelBinary,
  const unsigned char **rowKernelBinary,
  const unsigned char **colKernelBinary,
  const unsigned char **cornerKernelBinary,
  const char **binaryBuildOptions,
  cl_kernel  **tileClKernel,
  cl_kernel  **rowClKernel,
  cl_kernel  **colClKernel,
  cl_kernel  **cornerClKernel,
  unsigned int *workGroupNumRows,
  unsigned int *workGroupNumCols,
  unsigned int *microTileNumRows,
  unsigned int *microTileNumCols,
  unsigned int *unroll
) {
  if (order == clblasColumnMajor) {
    if (transA == clblasNoTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 32) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B0_096_096_08_16x16_6x6_src;
            *rowKernelSource    = dgemm_Col_NN_B0_001_096_08_16x16_6x6_src;
            *colKernelSource    = dgemm_Col_NN_B0_096_001_08_16x16_6x6_src;
            *cornerKernelSource = dgemm_Col_NN_B0_001_001_08_16x16_6x6_src;
            *sourceBuildOptions = dgemm_Col_NN_B0_096_096_08_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B0_096_096_08_16x16_6x6_bin;
            *rowKernelBinary    = dgemm_Col_NN_B0_001_096_08_16x16_6x6_bin;
            *colKernelBinary    = dgemm_Col_NN_B0_096_001_08_16x16_6x6_bin;
            *cornerKernelBinary = dgemm_Col_NN_B0_001_001_08_16x16_6x6_bin;
            *binaryBuildOptions = dgemm_Col_NN_B0_096_096_08_16x16_6x6_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B0_096_096_08_16x16_6x6_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B0_001_096_08_16x16_6x6_clKernel;
            *colClKernel        = &dgemm_Col_NN_B0_096_001_08_16x16_6x6_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B0_001_001_08_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B0_096_096_01_16x16_6x6_src;
            *rowKernelSource    = dgemm_Col_NN_B0_001_096_01_16x16_6x6_src;
            *colKernelSource    = dgemm_Col_NN_B0_096_001_01_16x16_6x6_src;
            *cornerKernelSource = dgemm_Col_NN_B0_001_001_01_16x16_6x6_src;
            *sourceBuildOptions = dgemm_Col_NN_B0_096_096_01_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B0_096_096_01_16x16_6x6_bin;
            *rowKernelBinary    = dgemm_Col_NN_B0_001_096_01_16x16_6x6_bin;
            *colKernelBinary    = dgemm_Col_NN_B0_096_001_01_16x16_6x6_bin;
            *cornerKernelBinary = dgemm_Col_NN_B0_001_001_01_16x16_6x6_bin;
            *binaryBuildOptions = dgemm_Col_NN_B0_096_096_01_16x16_6x6_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B0_096_096_01_16x16_6x6_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B0_001_096_01_16x16_6x6_clKernel;
            *colClKernel        = &dgemm_Col_NN_B0_096_001_01_16x16_6x6_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B0_001_001_01_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B0_128_064_08_16x16_8x4_src;
            *rowKernelSource    = dgemm_Col_NN_B0_001_064_08_16x16_8x4_src;
            *colKernelSource    = dgemm_Col_NN_B0_128_001_08_16x16_8x4_src;
            *cornerKernelSource = dgemm_Col_NN_B0_001_001_08_16x16_8x4_src;
            *sourceBuildOptions = dgemm_Col_NN_B0_128_064_08_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B0_128_064_08_16x16_8x4_bin;
            *rowKernelBinary    = dgemm_Col_NN_B0_001_064_08_16x16_8x4_bin;
            *colKernelBinary    = dgemm_Col_NN_B0_128_001_08_16x16_8x4_bin;
            *cornerKernelBinary = dgemm_Col_NN_B0_001_001_08_16x16_8x4_bin;
            *binaryBuildOptions = dgemm_Col_NN_B0_128_064_08_16x16_8x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B0_128_064_08_16x16_8x4_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B0_001_064_08_16x16_8x4_clKernel;
            *colClKernel        = &dgemm_Col_NN_B0_128_001_08_16x16_8x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B0_001_001_08_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B0_128_064_01_16x16_8x4_src;
            *rowKernelSource    = dgemm_Col_NN_B0_001_064_01_16x16_8x4_src;
            *colKernelSource    = dgemm_Col_NN_B0_128_001_01_16x16_8x4_src;
            *cornerKernelSource = dgemm_Col_NN_B0_001_001_01_16x16_8x4_src;
            *sourceBuildOptions = dgemm_Col_NN_B0_128_064_01_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B0_128_064_01_16x16_8x4_bin;
            *rowKernelBinary    = dgemm_Col_NN_B0_001_064_01_16x16_8x4_bin;
            *colKernelBinary    = dgemm_Col_NN_B0_128_001_01_16x16_8x4_bin;
            *cornerKernelBinary = dgemm_Col_NN_B0_001_001_01_16x16_8x4_bin;
            *binaryBuildOptions = dgemm_Col_NN_B0_128_064_01_16x16_8x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B0_128_064_01_16x16_8x4_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B0_001_064_01_16x16_8x4_clKernel;
            *colClKernel        = &dgemm_Col_NN_B0_128_001_01_16x16_8x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B0_001_001_01_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B0_096_064_08_16x16_6x4_src;
            *rowKernelSource    = dgemm_Col_NN_B0_001_064_08_16x16_6x4_src;
            *colKernelSource    = dgemm_Col_NN_B0_096_001_08_16x16_6x4_src;
            *cornerKernelSource = dgemm_Col_NN_B0_001_001_08_16x16_6x4_src;
            *sourceBuildOptions = dgemm_Col_NN_B0_096_064_08_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B0_096_064_08_16x16_6x4_bin;
            *rowKernelBinary    = dgemm_Col_NN_B0_001_064_08_16x16_6x4_bin;
            *colKernelBinary    = dgemm_Col_NN_B0_096_001_08_16x16_6x4_bin;
            *cornerKernelBinary = dgemm_Col_NN_B0_001_001_08_16x16_6x4_bin;
            *binaryBuildOptions = dgemm_Col_NN_B0_096_064_08_16x16_6x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B0_096_064_08_16x16_6x4_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B0_001_064_08_16x16_6x4_clKernel;
            *colClKernel        = &dgemm_Col_NN_B0_096_001_08_16x16_6x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B0_001_001_08_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B0_096_064_01_16x16_6x4_src;
            *rowKernelSource    = dgemm_Col_NN_B0_001_064_01_16x16_6x4_src;
            *colKernelSource    = dgemm_Col_NN_B0_096_001_01_16x16_6x4_src;
            *cornerKernelSource = dgemm_Col_NN_B0_001_001_01_16x16_6x4_src;
            *sourceBuildOptions = dgemm_Col_NN_B0_096_064_01_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B0_096_064_01_16x16_6x4_bin;
            *rowKernelBinary    = dgemm_Col_NN_B0_001_064_01_16x16_6x4_bin;
            *colKernelBinary    = dgemm_Col_NN_B0_096_001_01_16x16_6x4_bin;
            *cornerKernelBinary = dgemm_Col_NN_B0_001_001_01_16x16_6x4_bin;
            *binaryBuildOptions = dgemm_Col_NN_B0_096_064_01_16x16_6x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B0_096_064_01_16x16_6x4_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B0_001_064_01_16x16_6x4_clKernel;
            *colClKernel        = &dgemm_Col_NN_B0_096_001_01_16x16_6x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B0_001_001_01_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B0_064_064_08_16x16_4x4_src;
            *rowKernelSource    = dgemm_Col_NN_B0_001_064_08_16x16_4x4_src;
            *colKernelSource    = dgemm_Col_NN_B0_064_001_08_16x16_4x4_src;
            *cornerKernelSource = dgemm_Col_NN_B0_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = dgemm_Col_NN_B0_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B0_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = dgemm_Col_NN_B0_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = dgemm_Col_NN_B0_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = dgemm_Col_NN_B0_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = dgemm_Col_NN_B0_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B0_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B0_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &dgemm_Col_NN_B0_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B0_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B0_064_064_01_16x16_4x4_src;
            *rowKernelSource    = dgemm_Col_NN_B0_001_064_01_16x16_4x4_src;
            *colKernelSource    = dgemm_Col_NN_B0_064_001_01_16x16_4x4_src;
            *cornerKernelSource = dgemm_Col_NN_B0_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = dgemm_Col_NN_B0_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B0_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = dgemm_Col_NN_B0_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = dgemm_Col_NN_B0_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = dgemm_Col_NN_B0_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = dgemm_Col_NN_B0_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B0_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B0_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &dgemm_Col_NN_B0_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B0_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = dgemm_Col_NN_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = dgemm_Col_NN_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = dgemm_Col_NN_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = dgemm_Col_NN_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = dgemm_Col_NN_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = dgemm_Col_NN_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = dgemm_Col_NN_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = dgemm_Col_NN_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &dgemm_Col_NN_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = dgemm_Col_NN_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = dgemm_Col_NN_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = dgemm_Col_NN_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = dgemm_Col_NN_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = dgemm_Col_NN_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = dgemm_Col_NN_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = dgemm_Col_NN_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = dgemm_Col_NN_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &dgemm_Col_NN_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = dgemm_Col_NN_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = dgemm_Col_NN_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = dgemm_Col_NN_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = dgemm_Col_NN_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = dgemm_Col_NN_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = dgemm_Col_NN_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = dgemm_Col_NN_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = dgemm_Col_NN_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &dgemm_Col_NN_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = dgemm_Col_NN_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = dgemm_Col_NN_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = dgemm_Col_NN_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = dgemm_Col_NN_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = dgemm_Col_NN_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = dgemm_Col_NN_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = dgemm_Col_NN_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = dgemm_Col_NN_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &dgemm_Col_NN_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = dgemm_Col_NN_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = dgemm_Col_NN_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = dgemm_Col_NN_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = dgemm_Col_NN_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = dgemm_Col_NN_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = dgemm_Col_NN_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = dgemm_Col_NN_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = dgemm_Col_NN_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &dgemm_Col_NN_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = dgemm_Col_NN_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = dgemm_Col_NN_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = dgemm_Col_NN_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = dgemm_Col_NN_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = dgemm_Col_NN_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = dgemm_Col_NN_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = dgemm_Col_NN_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = dgemm_Col_NN_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &dgemm_Col_NN_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = dgemm_Col_NN_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = dgemm_Col_NN_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = dgemm_Col_NN_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = dgemm_Col_NN_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = dgemm_Col_NN_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = dgemm_Col_NN_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = dgemm_Col_NN_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = dgemm_Col_NN_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &dgemm_Col_NN_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = dgemm_Col_NN_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = dgemm_Col_NN_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = dgemm_Col_NN_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = dgemm_Col_NN_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = dgemm_Col_NN_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = dgemm_Col_NN_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = dgemm_Col_NN_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = dgemm_Col_NN_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &dgemm_Col_NN_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 32) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B1_096_096_08_16x16_6x6_src;
            *rowKernelSource    = dgemm_Col_NN_B1_001_096_08_16x16_6x6_src;
            *colKernelSource    = dgemm_Col_NN_B1_096_001_08_16x16_6x6_src;
            *cornerKernelSource = dgemm_Col_NN_B1_001_001_08_16x16_6x6_src;
            *sourceBuildOptions = dgemm_Col_NN_B1_096_096_08_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B1_096_096_08_16x16_6x6_bin;
            *rowKernelBinary    = dgemm_Col_NN_B1_001_096_08_16x16_6x6_bin;
            *colKernelBinary    = dgemm_Col_NN_B1_096_001_08_16x16_6x6_bin;
            *cornerKernelBinary = dgemm_Col_NN_B1_001_001_08_16x16_6x6_bin;
            *binaryBuildOptions = dgemm_Col_NN_B1_096_096_08_16x16_6x6_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B1_096_096_08_16x16_6x6_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B1_001_096_08_16x16_6x6_clKernel;
            *colClKernel        = &dgemm_Col_NN_B1_096_001_08_16x16_6x6_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B1_001_001_08_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B1_096_096_01_16x16_6x6_src;
            *rowKernelSource    = dgemm_Col_NN_B1_001_096_01_16x16_6x6_src;
            *colKernelSource    = dgemm_Col_NN_B1_096_001_01_16x16_6x6_src;
            *cornerKernelSource = dgemm_Col_NN_B1_001_001_01_16x16_6x6_src;
            *sourceBuildOptions = dgemm_Col_NN_B1_096_096_01_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B1_096_096_01_16x16_6x6_bin;
            *rowKernelBinary    = dgemm_Col_NN_B1_001_096_01_16x16_6x6_bin;
            *colKernelBinary    = dgemm_Col_NN_B1_096_001_01_16x16_6x6_bin;
            *cornerKernelBinary = dgemm_Col_NN_B1_001_001_01_16x16_6x6_bin;
            *binaryBuildOptions = dgemm_Col_NN_B1_096_096_01_16x16_6x6_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B1_096_096_01_16x16_6x6_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B1_001_096_01_16x16_6x6_clKernel;
            *colClKernel        = &dgemm_Col_NN_B1_096_001_01_16x16_6x6_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B1_001_001_01_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B1_128_064_08_16x16_8x4_src;
            *rowKernelSource    = dgemm_Col_NN_B1_001_064_08_16x16_8x4_src;
            *colKernelSource    = dgemm_Col_NN_B1_128_001_08_16x16_8x4_src;
            *cornerKernelSource = dgemm_Col_NN_B1_001_001_08_16x16_8x4_src;
            *sourceBuildOptions = dgemm_Col_NN_B1_128_064_08_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B1_128_064_08_16x16_8x4_bin;
            *rowKernelBinary    = dgemm_Col_NN_B1_001_064_08_16x16_8x4_bin;
            *colKernelBinary    = dgemm_Col_NN_B1_128_001_08_16x16_8x4_bin;
            *cornerKernelBinary = dgemm_Col_NN_B1_001_001_08_16x16_8x4_bin;
            *binaryBuildOptions = dgemm_Col_NN_B1_128_064_08_16x16_8x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B1_128_064_08_16x16_8x4_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B1_001_064_08_16x16_8x4_clKernel;
            *colClKernel        = &dgemm_Col_NN_B1_128_001_08_16x16_8x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B1_001_001_08_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B1_128_064_01_16x16_8x4_src;
            *rowKernelSource    = dgemm_Col_NN_B1_001_064_01_16x16_8x4_src;
            *colKernelSource    = dgemm_Col_NN_B1_128_001_01_16x16_8x4_src;
            *cornerKernelSource = dgemm_Col_NN_B1_001_001_01_16x16_8x4_src;
            *sourceBuildOptions = dgemm_Col_NN_B1_128_064_01_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B1_128_064_01_16x16_8x4_bin;
            *rowKernelBinary    = dgemm_Col_NN_B1_001_064_01_16x16_8x4_bin;
            *colKernelBinary    = dgemm_Col_NN_B1_128_001_01_16x16_8x4_bin;
            *cornerKernelBinary = dgemm_Col_NN_B1_001_001_01_16x16_8x4_bin;
            *binaryBuildOptions = dgemm_Col_NN_B1_128_064_01_16x16_8x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B1_128_064_01_16x16_8x4_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B1_001_064_01_16x16_8x4_clKernel;
            *colClKernel        = &dgemm_Col_NN_B1_128_001_01_16x16_8x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B1_001_001_01_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B1_096_064_08_16x16_6x4_src;
            *rowKernelSource    = dgemm_Col_NN_B1_001_064_08_16x16_6x4_src;
            *colKernelSource    = dgemm_Col_NN_B1_096_001_08_16x16_6x4_src;
            *cornerKernelSource = dgemm_Col_NN_B1_001_001_08_16x16_6x4_src;
            *sourceBuildOptions = dgemm_Col_NN_B1_096_064_08_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B1_096_064_08_16x16_6x4_bin;
            *rowKernelBinary    = dgemm_Col_NN_B1_001_064_08_16x16_6x4_bin;
            *colKernelBinary    = dgemm_Col_NN_B1_096_001_08_16x16_6x4_bin;
            *cornerKernelBinary = dgemm_Col_NN_B1_001_001_08_16x16_6x4_bin;
            *binaryBuildOptions = dgemm_Col_NN_B1_096_064_08_16x16_6x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B1_096_064_08_16x16_6x4_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B1_001_064_08_16x16_6x4_clKernel;
            *colClKernel        = &dgemm_Col_NN_B1_096_001_08_16x16_6x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B1_001_001_08_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B1_096_064_01_16x16_6x4_src;
            *rowKernelSource    = dgemm_Col_NN_B1_001_064_01_16x16_6x4_src;
            *colKernelSource    = dgemm_Col_NN_B1_096_001_01_16x16_6x4_src;
            *cornerKernelSource = dgemm_Col_NN_B1_001_001_01_16x16_6x4_src;
            *sourceBuildOptions = dgemm_Col_NN_B1_096_064_01_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B1_096_064_01_16x16_6x4_bin;
            *rowKernelBinary    = dgemm_Col_NN_B1_001_064_01_16x16_6x4_bin;
            *colKernelBinary    = dgemm_Col_NN_B1_096_001_01_16x16_6x4_bin;
            *cornerKernelBinary = dgemm_Col_NN_B1_001_001_01_16x16_6x4_bin;
            *binaryBuildOptions = dgemm_Col_NN_B1_096_064_01_16x16_6x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B1_096_064_01_16x16_6x4_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B1_001_064_01_16x16_6x4_clKernel;
            *colClKernel        = &dgemm_Col_NN_B1_096_001_01_16x16_6x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B1_001_001_01_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B1_064_064_08_16x16_4x4_src;
            *rowKernelSource    = dgemm_Col_NN_B1_001_064_08_16x16_4x4_src;
            *colKernelSource    = dgemm_Col_NN_B1_064_001_08_16x16_4x4_src;
            *cornerKernelSource = dgemm_Col_NN_B1_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = dgemm_Col_NN_B1_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B1_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = dgemm_Col_NN_B1_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = dgemm_Col_NN_B1_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = dgemm_Col_NN_B1_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = dgemm_Col_NN_B1_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B1_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B1_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &dgemm_Col_NN_B1_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B1_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B1_064_064_01_16x16_4x4_src;
            *rowKernelSource    = dgemm_Col_NN_B1_001_064_01_16x16_4x4_src;
            *colKernelSource    = dgemm_Col_NN_B1_064_001_01_16x16_4x4_src;
            *cornerKernelSource = dgemm_Col_NN_B1_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = dgemm_Col_NN_B1_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B1_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = dgemm_Col_NN_B1_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = dgemm_Col_NN_B1_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = dgemm_Col_NN_B1_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = dgemm_Col_NN_B1_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B1_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B1_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &dgemm_Col_NN_B1_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B1_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = dgemm_Col_NN_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = dgemm_Col_NN_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = dgemm_Col_NN_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = dgemm_Col_NN_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = dgemm_Col_NN_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = dgemm_Col_NN_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = dgemm_Col_NN_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = dgemm_Col_NN_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &dgemm_Col_NN_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = dgemm_Col_NN_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = dgemm_Col_NN_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = dgemm_Col_NN_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = dgemm_Col_NN_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = dgemm_Col_NN_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = dgemm_Col_NN_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = dgemm_Col_NN_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = dgemm_Col_NN_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &dgemm_Col_NN_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = dgemm_Col_NN_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = dgemm_Col_NN_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = dgemm_Col_NN_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = dgemm_Col_NN_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = dgemm_Col_NN_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = dgemm_Col_NN_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = dgemm_Col_NN_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = dgemm_Col_NN_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &dgemm_Col_NN_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = dgemm_Col_NN_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = dgemm_Col_NN_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = dgemm_Col_NN_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = dgemm_Col_NN_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = dgemm_Col_NN_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = dgemm_Col_NN_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = dgemm_Col_NN_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = dgemm_Col_NN_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &dgemm_Col_NN_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = dgemm_Col_NN_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = dgemm_Col_NN_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = dgemm_Col_NN_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = dgemm_Col_NN_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = dgemm_Col_NN_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = dgemm_Col_NN_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = dgemm_Col_NN_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = dgemm_Col_NN_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &dgemm_Col_NN_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = dgemm_Col_NN_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = dgemm_Col_NN_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = dgemm_Col_NN_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = dgemm_Col_NN_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = dgemm_Col_NN_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = dgemm_Col_NN_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = dgemm_Col_NN_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = dgemm_Col_NN_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &dgemm_Col_NN_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = dgemm_Col_NN_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = dgemm_Col_NN_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = dgemm_Col_NN_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = dgemm_Col_NN_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = dgemm_Col_NN_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = dgemm_Col_NN_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = dgemm_Col_NN_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = dgemm_Col_NN_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &dgemm_Col_NN_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NN_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = dgemm_Col_NN_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = dgemm_Col_NN_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = dgemm_Col_NN_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = dgemm_Col_NN_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NN_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = dgemm_Col_NN_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = dgemm_Col_NN_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = dgemm_Col_NN_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = dgemm_Col_NN_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NN_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &dgemm_Col_NN_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &dgemm_Col_NN_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &dgemm_Col_NN_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasNoTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 32) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B0_096_096_08_16x16_6x6_src;
            *rowKernelSource    = dgemm_Col_NT_B0_001_096_08_16x16_6x6_src;
            *colKernelSource    = dgemm_Col_NT_B0_096_001_08_16x16_6x6_src;
            *cornerKernelSource = dgemm_Col_NT_B0_001_001_08_16x16_6x6_src;
            *sourceBuildOptions = dgemm_Col_NT_B0_096_096_08_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B0_096_096_08_16x16_6x6_bin;
            *rowKernelBinary    = dgemm_Col_NT_B0_001_096_08_16x16_6x6_bin;
            *colKernelBinary    = dgemm_Col_NT_B0_096_001_08_16x16_6x6_bin;
            *cornerKernelBinary = dgemm_Col_NT_B0_001_001_08_16x16_6x6_bin;
            *binaryBuildOptions = dgemm_Col_NT_B0_096_096_08_16x16_6x6_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B0_096_096_08_16x16_6x6_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B0_001_096_08_16x16_6x6_clKernel;
            *colClKernel        = &dgemm_Col_NT_B0_096_001_08_16x16_6x6_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B0_001_001_08_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B0_096_096_01_16x16_6x6_src;
            *rowKernelSource    = dgemm_Col_NT_B0_001_096_01_16x16_6x6_src;
            *colKernelSource    = dgemm_Col_NT_B0_096_001_01_16x16_6x6_src;
            *cornerKernelSource = dgemm_Col_NT_B0_001_001_01_16x16_6x6_src;
            *sourceBuildOptions = dgemm_Col_NT_B0_096_096_01_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B0_096_096_01_16x16_6x6_bin;
            *rowKernelBinary    = dgemm_Col_NT_B0_001_096_01_16x16_6x6_bin;
            *colKernelBinary    = dgemm_Col_NT_B0_096_001_01_16x16_6x6_bin;
            *cornerKernelBinary = dgemm_Col_NT_B0_001_001_01_16x16_6x6_bin;
            *binaryBuildOptions = dgemm_Col_NT_B0_096_096_01_16x16_6x6_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B0_096_096_01_16x16_6x6_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B0_001_096_01_16x16_6x6_clKernel;
            *colClKernel        = &dgemm_Col_NT_B0_096_001_01_16x16_6x6_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B0_001_001_01_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B0_128_064_08_16x16_8x4_src;
            *rowKernelSource    = dgemm_Col_NT_B0_001_064_08_16x16_8x4_src;
            *colKernelSource    = dgemm_Col_NT_B0_128_001_08_16x16_8x4_src;
            *cornerKernelSource = dgemm_Col_NT_B0_001_001_08_16x16_8x4_src;
            *sourceBuildOptions = dgemm_Col_NT_B0_128_064_08_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B0_128_064_08_16x16_8x4_bin;
            *rowKernelBinary    = dgemm_Col_NT_B0_001_064_08_16x16_8x4_bin;
            *colKernelBinary    = dgemm_Col_NT_B0_128_001_08_16x16_8x4_bin;
            *cornerKernelBinary = dgemm_Col_NT_B0_001_001_08_16x16_8x4_bin;
            *binaryBuildOptions = dgemm_Col_NT_B0_128_064_08_16x16_8x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B0_128_064_08_16x16_8x4_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B0_001_064_08_16x16_8x4_clKernel;
            *colClKernel        = &dgemm_Col_NT_B0_128_001_08_16x16_8x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B0_001_001_08_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B0_128_064_01_16x16_8x4_src;
            *rowKernelSource    = dgemm_Col_NT_B0_001_064_01_16x16_8x4_src;
            *colKernelSource    = dgemm_Col_NT_B0_128_001_01_16x16_8x4_src;
            *cornerKernelSource = dgemm_Col_NT_B0_001_001_01_16x16_8x4_src;
            *sourceBuildOptions = dgemm_Col_NT_B0_128_064_01_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B0_128_064_01_16x16_8x4_bin;
            *rowKernelBinary    = dgemm_Col_NT_B0_001_064_01_16x16_8x4_bin;
            *colKernelBinary    = dgemm_Col_NT_B0_128_001_01_16x16_8x4_bin;
            *cornerKernelBinary = dgemm_Col_NT_B0_001_001_01_16x16_8x4_bin;
            *binaryBuildOptions = dgemm_Col_NT_B0_128_064_01_16x16_8x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B0_128_064_01_16x16_8x4_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B0_001_064_01_16x16_8x4_clKernel;
            *colClKernel        = &dgemm_Col_NT_B0_128_001_01_16x16_8x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B0_001_001_01_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B0_096_064_08_16x16_6x4_src;
            *rowKernelSource    = dgemm_Col_NT_B0_001_064_08_16x16_6x4_src;
            *colKernelSource    = dgemm_Col_NT_B0_096_001_08_16x16_6x4_src;
            *cornerKernelSource = dgemm_Col_NT_B0_001_001_08_16x16_6x4_src;
            *sourceBuildOptions = dgemm_Col_NT_B0_096_064_08_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B0_096_064_08_16x16_6x4_bin;
            *rowKernelBinary    = dgemm_Col_NT_B0_001_064_08_16x16_6x4_bin;
            *colKernelBinary    = dgemm_Col_NT_B0_096_001_08_16x16_6x4_bin;
            *cornerKernelBinary = dgemm_Col_NT_B0_001_001_08_16x16_6x4_bin;
            *binaryBuildOptions = dgemm_Col_NT_B0_096_064_08_16x16_6x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B0_096_064_08_16x16_6x4_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B0_001_064_08_16x16_6x4_clKernel;
            *colClKernel        = &dgemm_Col_NT_B0_096_001_08_16x16_6x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B0_001_001_08_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B0_096_064_01_16x16_6x4_src;
            *rowKernelSource    = dgemm_Col_NT_B0_001_064_01_16x16_6x4_src;
            *colKernelSource    = dgemm_Col_NT_B0_096_001_01_16x16_6x4_src;
            *cornerKernelSource = dgemm_Col_NT_B0_001_001_01_16x16_6x4_src;
            *sourceBuildOptions = dgemm_Col_NT_B0_096_064_01_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B0_096_064_01_16x16_6x4_bin;
            *rowKernelBinary    = dgemm_Col_NT_B0_001_064_01_16x16_6x4_bin;
            *colKernelBinary    = dgemm_Col_NT_B0_096_001_01_16x16_6x4_bin;
            *cornerKernelBinary = dgemm_Col_NT_B0_001_001_01_16x16_6x4_bin;
            *binaryBuildOptions = dgemm_Col_NT_B0_096_064_01_16x16_6x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B0_096_064_01_16x16_6x4_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B0_001_064_01_16x16_6x4_clKernel;
            *colClKernel        = &dgemm_Col_NT_B0_096_001_01_16x16_6x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B0_001_001_01_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B0_064_064_08_16x16_4x4_src;
            *rowKernelSource    = dgemm_Col_NT_B0_001_064_08_16x16_4x4_src;
            *colKernelSource    = dgemm_Col_NT_B0_064_001_08_16x16_4x4_src;
            *cornerKernelSource = dgemm_Col_NT_B0_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = dgemm_Col_NT_B0_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B0_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = dgemm_Col_NT_B0_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = dgemm_Col_NT_B0_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = dgemm_Col_NT_B0_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = dgemm_Col_NT_B0_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B0_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B0_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &dgemm_Col_NT_B0_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B0_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B0_064_064_01_16x16_4x4_src;
            *rowKernelSource    = dgemm_Col_NT_B0_001_064_01_16x16_4x4_src;
            *colKernelSource    = dgemm_Col_NT_B0_064_001_01_16x16_4x4_src;
            *cornerKernelSource = dgemm_Col_NT_B0_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = dgemm_Col_NT_B0_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B0_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = dgemm_Col_NT_B0_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = dgemm_Col_NT_B0_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = dgemm_Col_NT_B0_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = dgemm_Col_NT_B0_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B0_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B0_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &dgemm_Col_NT_B0_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B0_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = dgemm_Col_NT_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = dgemm_Col_NT_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = dgemm_Col_NT_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = dgemm_Col_NT_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = dgemm_Col_NT_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = dgemm_Col_NT_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = dgemm_Col_NT_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = dgemm_Col_NT_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &dgemm_Col_NT_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = dgemm_Col_NT_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = dgemm_Col_NT_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = dgemm_Col_NT_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = dgemm_Col_NT_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = dgemm_Col_NT_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = dgemm_Col_NT_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = dgemm_Col_NT_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = dgemm_Col_NT_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &dgemm_Col_NT_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = dgemm_Col_NT_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = dgemm_Col_NT_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = dgemm_Col_NT_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = dgemm_Col_NT_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = dgemm_Col_NT_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = dgemm_Col_NT_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = dgemm_Col_NT_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = dgemm_Col_NT_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &dgemm_Col_NT_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = dgemm_Col_NT_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = dgemm_Col_NT_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = dgemm_Col_NT_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = dgemm_Col_NT_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = dgemm_Col_NT_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = dgemm_Col_NT_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = dgemm_Col_NT_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = dgemm_Col_NT_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &dgemm_Col_NT_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = dgemm_Col_NT_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = dgemm_Col_NT_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = dgemm_Col_NT_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = dgemm_Col_NT_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = dgemm_Col_NT_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = dgemm_Col_NT_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = dgemm_Col_NT_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = dgemm_Col_NT_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &dgemm_Col_NT_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = dgemm_Col_NT_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = dgemm_Col_NT_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = dgemm_Col_NT_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = dgemm_Col_NT_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = dgemm_Col_NT_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = dgemm_Col_NT_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = dgemm_Col_NT_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = dgemm_Col_NT_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &dgemm_Col_NT_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = dgemm_Col_NT_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = dgemm_Col_NT_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = dgemm_Col_NT_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = dgemm_Col_NT_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = dgemm_Col_NT_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = dgemm_Col_NT_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = dgemm_Col_NT_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = dgemm_Col_NT_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &dgemm_Col_NT_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = dgemm_Col_NT_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = dgemm_Col_NT_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = dgemm_Col_NT_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = dgemm_Col_NT_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = dgemm_Col_NT_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = dgemm_Col_NT_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = dgemm_Col_NT_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = dgemm_Col_NT_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &dgemm_Col_NT_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 32) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B1_096_096_08_16x16_6x6_src;
            *rowKernelSource    = dgemm_Col_NT_B1_001_096_08_16x16_6x6_src;
            *colKernelSource    = dgemm_Col_NT_B1_096_001_08_16x16_6x6_src;
            *cornerKernelSource = dgemm_Col_NT_B1_001_001_08_16x16_6x6_src;
            *sourceBuildOptions = dgemm_Col_NT_B1_096_096_08_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B1_096_096_08_16x16_6x6_bin;
            *rowKernelBinary    = dgemm_Col_NT_B1_001_096_08_16x16_6x6_bin;
            *colKernelBinary    = dgemm_Col_NT_B1_096_001_08_16x16_6x6_bin;
            *cornerKernelBinary = dgemm_Col_NT_B1_001_001_08_16x16_6x6_bin;
            *binaryBuildOptions = dgemm_Col_NT_B1_096_096_08_16x16_6x6_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B1_096_096_08_16x16_6x6_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B1_001_096_08_16x16_6x6_clKernel;
            *colClKernel        = &dgemm_Col_NT_B1_096_001_08_16x16_6x6_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B1_001_001_08_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B1_096_096_01_16x16_6x6_src;
            *rowKernelSource    = dgemm_Col_NT_B1_001_096_01_16x16_6x6_src;
            *colKernelSource    = dgemm_Col_NT_B1_096_001_01_16x16_6x6_src;
            *cornerKernelSource = dgemm_Col_NT_B1_001_001_01_16x16_6x6_src;
            *sourceBuildOptions = dgemm_Col_NT_B1_096_096_01_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B1_096_096_01_16x16_6x6_bin;
            *rowKernelBinary    = dgemm_Col_NT_B1_001_096_01_16x16_6x6_bin;
            *colKernelBinary    = dgemm_Col_NT_B1_096_001_01_16x16_6x6_bin;
            *cornerKernelBinary = dgemm_Col_NT_B1_001_001_01_16x16_6x6_bin;
            *binaryBuildOptions = dgemm_Col_NT_B1_096_096_01_16x16_6x6_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B1_096_096_01_16x16_6x6_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B1_001_096_01_16x16_6x6_clKernel;
            *colClKernel        = &dgemm_Col_NT_B1_096_001_01_16x16_6x6_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B1_001_001_01_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B1_128_064_08_16x16_8x4_src;
            *rowKernelSource    = dgemm_Col_NT_B1_001_064_08_16x16_8x4_src;
            *colKernelSource    = dgemm_Col_NT_B1_128_001_08_16x16_8x4_src;
            *cornerKernelSource = dgemm_Col_NT_B1_001_001_08_16x16_8x4_src;
            *sourceBuildOptions = dgemm_Col_NT_B1_128_064_08_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B1_128_064_08_16x16_8x4_bin;
            *rowKernelBinary    = dgemm_Col_NT_B1_001_064_08_16x16_8x4_bin;
            *colKernelBinary    = dgemm_Col_NT_B1_128_001_08_16x16_8x4_bin;
            *cornerKernelBinary = dgemm_Col_NT_B1_001_001_08_16x16_8x4_bin;
            *binaryBuildOptions = dgemm_Col_NT_B1_128_064_08_16x16_8x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B1_128_064_08_16x16_8x4_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B1_001_064_08_16x16_8x4_clKernel;
            *colClKernel        = &dgemm_Col_NT_B1_128_001_08_16x16_8x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B1_001_001_08_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B1_128_064_01_16x16_8x4_src;
            *rowKernelSource    = dgemm_Col_NT_B1_001_064_01_16x16_8x4_src;
            *colKernelSource    = dgemm_Col_NT_B1_128_001_01_16x16_8x4_src;
            *cornerKernelSource = dgemm_Col_NT_B1_001_001_01_16x16_8x4_src;
            *sourceBuildOptions = dgemm_Col_NT_B1_128_064_01_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B1_128_064_01_16x16_8x4_bin;
            *rowKernelBinary    = dgemm_Col_NT_B1_001_064_01_16x16_8x4_bin;
            *colKernelBinary    = dgemm_Col_NT_B1_128_001_01_16x16_8x4_bin;
            *cornerKernelBinary = dgemm_Col_NT_B1_001_001_01_16x16_8x4_bin;
            *binaryBuildOptions = dgemm_Col_NT_B1_128_064_01_16x16_8x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B1_128_064_01_16x16_8x4_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B1_001_064_01_16x16_8x4_clKernel;
            *colClKernel        = &dgemm_Col_NT_B1_128_001_01_16x16_8x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B1_001_001_01_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B1_096_064_08_16x16_6x4_src;
            *rowKernelSource    = dgemm_Col_NT_B1_001_064_08_16x16_6x4_src;
            *colKernelSource    = dgemm_Col_NT_B1_096_001_08_16x16_6x4_src;
            *cornerKernelSource = dgemm_Col_NT_B1_001_001_08_16x16_6x4_src;
            *sourceBuildOptions = dgemm_Col_NT_B1_096_064_08_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B1_096_064_08_16x16_6x4_bin;
            *rowKernelBinary    = dgemm_Col_NT_B1_001_064_08_16x16_6x4_bin;
            *colKernelBinary    = dgemm_Col_NT_B1_096_001_08_16x16_6x4_bin;
            *cornerKernelBinary = dgemm_Col_NT_B1_001_001_08_16x16_6x4_bin;
            *binaryBuildOptions = dgemm_Col_NT_B1_096_064_08_16x16_6x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B1_096_064_08_16x16_6x4_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B1_001_064_08_16x16_6x4_clKernel;
            *colClKernel        = &dgemm_Col_NT_B1_096_001_08_16x16_6x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B1_001_001_08_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B1_096_064_01_16x16_6x4_src;
            *rowKernelSource    = dgemm_Col_NT_B1_001_064_01_16x16_6x4_src;
            *colKernelSource    = dgemm_Col_NT_B1_096_001_01_16x16_6x4_src;
            *cornerKernelSource = dgemm_Col_NT_B1_001_001_01_16x16_6x4_src;
            *sourceBuildOptions = dgemm_Col_NT_B1_096_064_01_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B1_096_064_01_16x16_6x4_bin;
            *rowKernelBinary    = dgemm_Col_NT_B1_001_064_01_16x16_6x4_bin;
            *colKernelBinary    = dgemm_Col_NT_B1_096_001_01_16x16_6x4_bin;
            *cornerKernelBinary = dgemm_Col_NT_B1_001_001_01_16x16_6x4_bin;
            *binaryBuildOptions = dgemm_Col_NT_B1_096_064_01_16x16_6x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B1_096_064_01_16x16_6x4_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B1_001_064_01_16x16_6x4_clKernel;
            *colClKernel        = &dgemm_Col_NT_B1_096_001_01_16x16_6x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B1_001_001_01_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B1_064_064_08_16x16_4x4_src;
            *rowKernelSource    = dgemm_Col_NT_B1_001_064_08_16x16_4x4_src;
            *colKernelSource    = dgemm_Col_NT_B1_064_001_08_16x16_4x4_src;
            *cornerKernelSource = dgemm_Col_NT_B1_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = dgemm_Col_NT_B1_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B1_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = dgemm_Col_NT_B1_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = dgemm_Col_NT_B1_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = dgemm_Col_NT_B1_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = dgemm_Col_NT_B1_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B1_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B1_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &dgemm_Col_NT_B1_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B1_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B1_064_064_01_16x16_4x4_src;
            *rowKernelSource    = dgemm_Col_NT_B1_001_064_01_16x16_4x4_src;
            *colKernelSource    = dgemm_Col_NT_B1_064_001_01_16x16_4x4_src;
            *cornerKernelSource = dgemm_Col_NT_B1_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = dgemm_Col_NT_B1_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B1_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = dgemm_Col_NT_B1_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = dgemm_Col_NT_B1_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = dgemm_Col_NT_B1_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = dgemm_Col_NT_B1_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B1_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B1_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &dgemm_Col_NT_B1_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B1_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = dgemm_Col_NT_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = dgemm_Col_NT_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = dgemm_Col_NT_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = dgemm_Col_NT_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = dgemm_Col_NT_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = dgemm_Col_NT_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = dgemm_Col_NT_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = dgemm_Col_NT_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &dgemm_Col_NT_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = dgemm_Col_NT_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = dgemm_Col_NT_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = dgemm_Col_NT_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = dgemm_Col_NT_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = dgemm_Col_NT_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = dgemm_Col_NT_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = dgemm_Col_NT_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = dgemm_Col_NT_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &dgemm_Col_NT_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = dgemm_Col_NT_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = dgemm_Col_NT_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = dgemm_Col_NT_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = dgemm_Col_NT_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = dgemm_Col_NT_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = dgemm_Col_NT_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = dgemm_Col_NT_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = dgemm_Col_NT_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &dgemm_Col_NT_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = dgemm_Col_NT_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = dgemm_Col_NT_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = dgemm_Col_NT_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = dgemm_Col_NT_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = dgemm_Col_NT_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = dgemm_Col_NT_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = dgemm_Col_NT_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = dgemm_Col_NT_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &dgemm_Col_NT_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = dgemm_Col_NT_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = dgemm_Col_NT_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = dgemm_Col_NT_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = dgemm_Col_NT_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = dgemm_Col_NT_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = dgemm_Col_NT_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = dgemm_Col_NT_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = dgemm_Col_NT_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &dgemm_Col_NT_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = dgemm_Col_NT_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = dgemm_Col_NT_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = dgemm_Col_NT_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = dgemm_Col_NT_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = dgemm_Col_NT_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = dgemm_Col_NT_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = dgemm_Col_NT_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = dgemm_Col_NT_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &dgemm_Col_NT_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = dgemm_Col_NT_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = dgemm_Col_NT_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = dgemm_Col_NT_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = dgemm_Col_NT_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = dgemm_Col_NT_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = dgemm_Col_NT_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = dgemm_Col_NT_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = dgemm_Col_NT_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &dgemm_Col_NT_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_NT_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = dgemm_Col_NT_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = dgemm_Col_NT_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = dgemm_Col_NT_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = dgemm_Col_NT_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_NT_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = dgemm_Col_NT_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = dgemm_Col_NT_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = dgemm_Col_NT_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = dgemm_Col_NT_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_NT_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &dgemm_Col_NT_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &dgemm_Col_NT_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &dgemm_Col_NT_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 32) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B0_096_096_08_16x16_6x6_src;
            *rowKernelSource    = dgemm_Col_TN_B0_001_096_08_16x16_6x6_src;
            *colKernelSource    = dgemm_Col_TN_B0_096_001_08_16x16_6x6_src;
            *cornerKernelSource = dgemm_Col_TN_B0_001_001_08_16x16_6x6_src;
            *sourceBuildOptions = dgemm_Col_TN_B0_096_096_08_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B0_096_096_08_16x16_6x6_bin;
            *rowKernelBinary    = dgemm_Col_TN_B0_001_096_08_16x16_6x6_bin;
            *colKernelBinary    = dgemm_Col_TN_B0_096_001_08_16x16_6x6_bin;
            *cornerKernelBinary = dgemm_Col_TN_B0_001_001_08_16x16_6x6_bin;
            *binaryBuildOptions = dgemm_Col_TN_B0_096_096_08_16x16_6x6_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B0_096_096_08_16x16_6x6_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B0_001_096_08_16x16_6x6_clKernel;
            *colClKernel        = &dgemm_Col_TN_B0_096_001_08_16x16_6x6_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B0_001_001_08_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B0_096_096_01_16x16_6x6_src;
            *rowKernelSource    = dgemm_Col_TN_B0_001_096_01_16x16_6x6_src;
            *colKernelSource    = dgemm_Col_TN_B0_096_001_01_16x16_6x6_src;
            *cornerKernelSource = dgemm_Col_TN_B0_001_001_01_16x16_6x6_src;
            *sourceBuildOptions = dgemm_Col_TN_B0_096_096_01_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B0_096_096_01_16x16_6x6_bin;
            *rowKernelBinary    = dgemm_Col_TN_B0_001_096_01_16x16_6x6_bin;
            *colKernelBinary    = dgemm_Col_TN_B0_096_001_01_16x16_6x6_bin;
            *cornerKernelBinary = dgemm_Col_TN_B0_001_001_01_16x16_6x6_bin;
            *binaryBuildOptions = dgemm_Col_TN_B0_096_096_01_16x16_6x6_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B0_096_096_01_16x16_6x6_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B0_001_096_01_16x16_6x6_clKernel;
            *colClKernel        = &dgemm_Col_TN_B0_096_001_01_16x16_6x6_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B0_001_001_01_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B0_128_064_08_16x16_8x4_src;
            *rowKernelSource    = dgemm_Col_TN_B0_001_064_08_16x16_8x4_src;
            *colKernelSource    = dgemm_Col_TN_B0_128_001_08_16x16_8x4_src;
            *cornerKernelSource = dgemm_Col_TN_B0_001_001_08_16x16_8x4_src;
            *sourceBuildOptions = dgemm_Col_TN_B0_128_064_08_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B0_128_064_08_16x16_8x4_bin;
            *rowKernelBinary    = dgemm_Col_TN_B0_001_064_08_16x16_8x4_bin;
            *colKernelBinary    = dgemm_Col_TN_B0_128_001_08_16x16_8x4_bin;
            *cornerKernelBinary = dgemm_Col_TN_B0_001_001_08_16x16_8x4_bin;
            *binaryBuildOptions = dgemm_Col_TN_B0_128_064_08_16x16_8x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B0_128_064_08_16x16_8x4_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B0_001_064_08_16x16_8x4_clKernel;
            *colClKernel        = &dgemm_Col_TN_B0_128_001_08_16x16_8x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B0_001_001_08_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B0_128_064_01_16x16_8x4_src;
            *rowKernelSource    = dgemm_Col_TN_B0_001_064_01_16x16_8x4_src;
            *colKernelSource    = dgemm_Col_TN_B0_128_001_01_16x16_8x4_src;
            *cornerKernelSource = dgemm_Col_TN_B0_001_001_01_16x16_8x4_src;
            *sourceBuildOptions = dgemm_Col_TN_B0_128_064_01_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B0_128_064_01_16x16_8x4_bin;
            *rowKernelBinary    = dgemm_Col_TN_B0_001_064_01_16x16_8x4_bin;
            *colKernelBinary    = dgemm_Col_TN_B0_128_001_01_16x16_8x4_bin;
            *cornerKernelBinary = dgemm_Col_TN_B0_001_001_01_16x16_8x4_bin;
            *binaryBuildOptions = dgemm_Col_TN_B0_128_064_01_16x16_8x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B0_128_064_01_16x16_8x4_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B0_001_064_01_16x16_8x4_clKernel;
            *colClKernel        = &dgemm_Col_TN_B0_128_001_01_16x16_8x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B0_001_001_01_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B0_096_064_08_16x16_6x4_src;
            *rowKernelSource    = dgemm_Col_TN_B0_001_064_08_16x16_6x4_src;
            *colKernelSource    = dgemm_Col_TN_B0_096_001_08_16x16_6x4_src;
            *cornerKernelSource = dgemm_Col_TN_B0_001_001_08_16x16_6x4_src;
            *sourceBuildOptions = dgemm_Col_TN_B0_096_064_08_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B0_096_064_08_16x16_6x4_bin;
            *rowKernelBinary    = dgemm_Col_TN_B0_001_064_08_16x16_6x4_bin;
            *colKernelBinary    = dgemm_Col_TN_B0_096_001_08_16x16_6x4_bin;
            *cornerKernelBinary = dgemm_Col_TN_B0_001_001_08_16x16_6x4_bin;
            *binaryBuildOptions = dgemm_Col_TN_B0_096_064_08_16x16_6x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B0_096_064_08_16x16_6x4_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B0_001_064_08_16x16_6x4_clKernel;
            *colClKernel        = &dgemm_Col_TN_B0_096_001_08_16x16_6x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B0_001_001_08_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B0_096_064_01_16x16_6x4_src;
            *rowKernelSource    = dgemm_Col_TN_B0_001_064_01_16x16_6x4_src;
            *colKernelSource    = dgemm_Col_TN_B0_096_001_01_16x16_6x4_src;
            *cornerKernelSource = dgemm_Col_TN_B0_001_001_01_16x16_6x4_src;
            *sourceBuildOptions = dgemm_Col_TN_B0_096_064_01_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B0_096_064_01_16x16_6x4_bin;
            *rowKernelBinary    = dgemm_Col_TN_B0_001_064_01_16x16_6x4_bin;
            *colKernelBinary    = dgemm_Col_TN_B0_096_001_01_16x16_6x4_bin;
            *cornerKernelBinary = dgemm_Col_TN_B0_001_001_01_16x16_6x4_bin;
            *binaryBuildOptions = dgemm_Col_TN_B0_096_064_01_16x16_6x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B0_096_064_01_16x16_6x4_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B0_001_064_01_16x16_6x4_clKernel;
            *colClKernel        = &dgemm_Col_TN_B0_096_001_01_16x16_6x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B0_001_001_01_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B0_064_064_08_16x16_4x4_src;
            *rowKernelSource    = dgemm_Col_TN_B0_001_064_08_16x16_4x4_src;
            *colKernelSource    = dgemm_Col_TN_B0_064_001_08_16x16_4x4_src;
            *cornerKernelSource = dgemm_Col_TN_B0_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = dgemm_Col_TN_B0_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B0_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = dgemm_Col_TN_B0_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = dgemm_Col_TN_B0_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = dgemm_Col_TN_B0_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = dgemm_Col_TN_B0_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B0_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B0_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &dgemm_Col_TN_B0_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B0_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B0_064_064_01_16x16_4x4_src;
            *rowKernelSource    = dgemm_Col_TN_B0_001_064_01_16x16_4x4_src;
            *colKernelSource    = dgemm_Col_TN_B0_064_001_01_16x16_4x4_src;
            *cornerKernelSource = dgemm_Col_TN_B0_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = dgemm_Col_TN_B0_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B0_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = dgemm_Col_TN_B0_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = dgemm_Col_TN_B0_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = dgemm_Col_TN_B0_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = dgemm_Col_TN_B0_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B0_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B0_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &dgemm_Col_TN_B0_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B0_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = dgemm_Col_TN_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = dgemm_Col_TN_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = dgemm_Col_TN_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = dgemm_Col_TN_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = dgemm_Col_TN_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = dgemm_Col_TN_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = dgemm_Col_TN_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = dgemm_Col_TN_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &dgemm_Col_TN_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = dgemm_Col_TN_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = dgemm_Col_TN_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = dgemm_Col_TN_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = dgemm_Col_TN_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = dgemm_Col_TN_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = dgemm_Col_TN_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = dgemm_Col_TN_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = dgemm_Col_TN_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &dgemm_Col_TN_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = dgemm_Col_TN_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = dgemm_Col_TN_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = dgemm_Col_TN_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = dgemm_Col_TN_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = dgemm_Col_TN_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = dgemm_Col_TN_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = dgemm_Col_TN_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = dgemm_Col_TN_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &dgemm_Col_TN_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = dgemm_Col_TN_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = dgemm_Col_TN_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = dgemm_Col_TN_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = dgemm_Col_TN_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = dgemm_Col_TN_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = dgemm_Col_TN_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = dgemm_Col_TN_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = dgemm_Col_TN_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &dgemm_Col_TN_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = dgemm_Col_TN_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = dgemm_Col_TN_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = dgemm_Col_TN_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = dgemm_Col_TN_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = dgemm_Col_TN_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = dgemm_Col_TN_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = dgemm_Col_TN_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = dgemm_Col_TN_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &dgemm_Col_TN_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = dgemm_Col_TN_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = dgemm_Col_TN_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = dgemm_Col_TN_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = dgemm_Col_TN_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = dgemm_Col_TN_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = dgemm_Col_TN_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = dgemm_Col_TN_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = dgemm_Col_TN_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &dgemm_Col_TN_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = dgemm_Col_TN_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = dgemm_Col_TN_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = dgemm_Col_TN_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = dgemm_Col_TN_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = dgemm_Col_TN_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = dgemm_Col_TN_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = dgemm_Col_TN_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = dgemm_Col_TN_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &dgemm_Col_TN_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = dgemm_Col_TN_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = dgemm_Col_TN_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = dgemm_Col_TN_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = dgemm_Col_TN_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = dgemm_Col_TN_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = dgemm_Col_TN_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = dgemm_Col_TN_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = dgemm_Col_TN_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &dgemm_Col_TN_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 32) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B1_096_096_08_16x16_6x6_src;
            *rowKernelSource    = dgemm_Col_TN_B1_001_096_08_16x16_6x6_src;
            *colKernelSource    = dgemm_Col_TN_B1_096_001_08_16x16_6x6_src;
            *cornerKernelSource = dgemm_Col_TN_B1_001_001_08_16x16_6x6_src;
            *sourceBuildOptions = dgemm_Col_TN_B1_096_096_08_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B1_096_096_08_16x16_6x6_bin;
            *rowKernelBinary    = dgemm_Col_TN_B1_001_096_08_16x16_6x6_bin;
            *colKernelBinary    = dgemm_Col_TN_B1_096_001_08_16x16_6x6_bin;
            *cornerKernelBinary = dgemm_Col_TN_B1_001_001_08_16x16_6x6_bin;
            *binaryBuildOptions = dgemm_Col_TN_B1_096_096_08_16x16_6x6_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B1_096_096_08_16x16_6x6_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B1_001_096_08_16x16_6x6_clKernel;
            *colClKernel        = &dgemm_Col_TN_B1_096_001_08_16x16_6x6_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B1_001_001_08_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B1_096_096_01_16x16_6x6_src;
            *rowKernelSource    = dgemm_Col_TN_B1_001_096_01_16x16_6x6_src;
            *colKernelSource    = dgemm_Col_TN_B1_096_001_01_16x16_6x6_src;
            *cornerKernelSource = dgemm_Col_TN_B1_001_001_01_16x16_6x6_src;
            *sourceBuildOptions = dgemm_Col_TN_B1_096_096_01_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B1_096_096_01_16x16_6x6_bin;
            *rowKernelBinary    = dgemm_Col_TN_B1_001_096_01_16x16_6x6_bin;
            *colKernelBinary    = dgemm_Col_TN_B1_096_001_01_16x16_6x6_bin;
            *cornerKernelBinary = dgemm_Col_TN_B1_001_001_01_16x16_6x6_bin;
            *binaryBuildOptions = dgemm_Col_TN_B1_096_096_01_16x16_6x6_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B1_096_096_01_16x16_6x6_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B1_001_096_01_16x16_6x6_clKernel;
            *colClKernel        = &dgemm_Col_TN_B1_096_001_01_16x16_6x6_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B1_001_001_01_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B1_128_064_08_16x16_8x4_src;
            *rowKernelSource    = dgemm_Col_TN_B1_001_064_08_16x16_8x4_src;
            *colKernelSource    = dgemm_Col_TN_B1_128_001_08_16x16_8x4_src;
            *cornerKernelSource = dgemm_Col_TN_B1_001_001_08_16x16_8x4_src;
            *sourceBuildOptions = dgemm_Col_TN_B1_128_064_08_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B1_128_064_08_16x16_8x4_bin;
            *rowKernelBinary    = dgemm_Col_TN_B1_001_064_08_16x16_8x4_bin;
            *colKernelBinary    = dgemm_Col_TN_B1_128_001_08_16x16_8x4_bin;
            *cornerKernelBinary = dgemm_Col_TN_B1_001_001_08_16x16_8x4_bin;
            *binaryBuildOptions = dgemm_Col_TN_B1_128_064_08_16x16_8x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B1_128_064_08_16x16_8x4_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B1_001_064_08_16x16_8x4_clKernel;
            *colClKernel        = &dgemm_Col_TN_B1_128_001_08_16x16_8x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B1_001_001_08_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B1_128_064_01_16x16_8x4_src;
            *rowKernelSource    = dgemm_Col_TN_B1_001_064_01_16x16_8x4_src;
            *colKernelSource    = dgemm_Col_TN_B1_128_001_01_16x16_8x4_src;
            *cornerKernelSource = dgemm_Col_TN_B1_001_001_01_16x16_8x4_src;
            *sourceBuildOptions = dgemm_Col_TN_B1_128_064_01_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B1_128_064_01_16x16_8x4_bin;
            *rowKernelBinary    = dgemm_Col_TN_B1_001_064_01_16x16_8x4_bin;
            *colKernelBinary    = dgemm_Col_TN_B1_128_001_01_16x16_8x4_bin;
            *cornerKernelBinary = dgemm_Col_TN_B1_001_001_01_16x16_8x4_bin;
            *binaryBuildOptions = dgemm_Col_TN_B1_128_064_01_16x16_8x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B1_128_064_01_16x16_8x4_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B1_001_064_01_16x16_8x4_clKernel;
            *colClKernel        = &dgemm_Col_TN_B1_128_001_01_16x16_8x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B1_001_001_01_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B1_096_064_08_16x16_6x4_src;
            *rowKernelSource    = dgemm_Col_TN_B1_001_064_08_16x16_6x4_src;
            *colKernelSource    = dgemm_Col_TN_B1_096_001_08_16x16_6x4_src;
            *cornerKernelSource = dgemm_Col_TN_B1_001_001_08_16x16_6x4_src;
            *sourceBuildOptions = dgemm_Col_TN_B1_096_064_08_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B1_096_064_08_16x16_6x4_bin;
            *rowKernelBinary    = dgemm_Col_TN_B1_001_064_08_16x16_6x4_bin;
            *colKernelBinary    = dgemm_Col_TN_B1_096_001_08_16x16_6x4_bin;
            *cornerKernelBinary = dgemm_Col_TN_B1_001_001_08_16x16_6x4_bin;
            *binaryBuildOptions = dgemm_Col_TN_B1_096_064_08_16x16_6x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B1_096_064_08_16x16_6x4_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B1_001_064_08_16x16_6x4_clKernel;
            *colClKernel        = &dgemm_Col_TN_B1_096_001_08_16x16_6x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B1_001_001_08_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B1_096_064_01_16x16_6x4_src;
            *rowKernelSource    = dgemm_Col_TN_B1_001_064_01_16x16_6x4_src;
            *colKernelSource    = dgemm_Col_TN_B1_096_001_01_16x16_6x4_src;
            *cornerKernelSource = dgemm_Col_TN_B1_001_001_01_16x16_6x4_src;
            *sourceBuildOptions = dgemm_Col_TN_B1_096_064_01_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B1_096_064_01_16x16_6x4_bin;
            *rowKernelBinary    = dgemm_Col_TN_B1_001_064_01_16x16_6x4_bin;
            *colKernelBinary    = dgemm_Col_TN_B1_096_001_01_16x16_6x4_bin;
            *cornerKernelBinary = dgemm_Col_TN_B1_001_001_01_16x16_6x4_bin;
            *binaryBuildOptions = dgemm_Col_TN_B1_096_064_01_16x16_6x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B1_096_064_01_16x16_6x4_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B1_001_064_01_16x16_6x4_clKernel;
            *colClKernel        = &dgemm_Col_TN_B1_096_001_01_16x16_6x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B1_001_001_01_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B1_064_064_08_16x16_4x4_src;
            *rowKernelSource    = dgemm_Col_TN_B1_001_064_08_16x16_4x4_src;
            *colKernelSource    = dgemm_Col_TN_B1_064_001_08_16x16_4x4_src;
            *cornerKernelSource = dgemm_Col_TN_B1_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = dgemm_Col_TN_B1_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B1_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = dgemm_Col_TN_B1_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = dgemm_Col_TN_B1_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = dgemm_Col_TN_B1_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = dgemm_Col_TN_B1_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B1_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B1_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &dgemm_Col_TN_B1_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B1_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B1_064_064_01_16x16_4x4_src;
            *rowKernelSource    = dgemm_Col_TN_B1_001_064_01_16x16_4x4_src;
            *colKernelSource    = dgemm_Col_TN_B1_064_001_01_16x16_4x4_src;
            *cornerKernelSource = dgemm_Col_TN_B1_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = dgemm_Col_TN_B1_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B1_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = dgemm_Col_TN_B1_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = dgemm_Col_TN_B1_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = dgemm_Col_TN_B1_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = dgemm_Col_TN_B1_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B1_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B1_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &dgemm_Col_TN_B1_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B1_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = dgemm_Col_TN_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = dgemm_Col_TN_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = dgemm_Col_TN_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = dgemm_Col_TN_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = dgemm_Col_TN_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = dgemm_Col_TN_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = dgemm_Col_TN_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = dgemm_Col_TN_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &dgemm_Col_TN_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = dgemm_Col_TN_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = dgemm_Col_TN_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = dgemm_Col_TN_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = dgemm_Col_TN_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = dgemm_Col_TN_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = dgemm_Col_TN_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = dgemm_Col_TN_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = dgemm_Col_TN_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &dgemm_Col_TN_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = dgemm_Col_TN_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = dgemm_Col_TN_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = dgemm_Col_TN_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = dgemm_Col_TN_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = dgemm_Col_TN_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = dgemm_Col_TN_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = dgemm_Col_TN_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = dgemm_Col_TN_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &dgemm_Col_TN_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = dgemm_Col_TN_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = dgemm_Col_TN_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = dgemm_Col_TN_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = dgemm_Col_TN_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = dgemm_Col_TN_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = dgemm_Col_TN_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = dgemm_Col_TN_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = dgemm_Col_TN_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &dgemm_Col_TN_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = dgemm_Col_TN_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = dgemm_Col_TN_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = dgemm_Col_TN_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = dgemm_Col_TN_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = dgemm_Col_TN_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = dgemm_Col_TN_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = dgemm_Col_TN_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = dgemm_Col_TN_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &dgemm_Col_TN_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = dgemm_Col_TN_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = dgemm_Col_TN_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = dgemm_Col_TN_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = dgemm_Col_TN_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = dgemm_Col_TN_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = dgemm_Col_TN_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = dgemm_Col_TN_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = dgemm_Col_TN_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &dgemm_Col_TN_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = dgemm_Col_TN_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = dgemm_Col_TN_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = dgemm_Col_TN_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = dgemm_Col_TN_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = dgemm_Col_TN_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = dgemm_Col_TN_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = dgemm_Col_TN_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = dgemm_Col_TN_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &dgemm_Col_TN_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TN_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = dgemm_Col_TN_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = dgemm_Col_TN_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = dgemm_Col_TN_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = dgemm_Col_TN_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TN_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = dgemm_Col_TN_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = dgemm_Col_TN_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = dgemm_Col_TN_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = dgemm_Col_TN_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TN_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &dgemm_Col_TN_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &dgemm_Col_TN_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &dgemm_Col_TN_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 32) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B0_096_096_08_16x16_6x6_src;
            *rowKernelSource    = dgemm_Col_TT_B0_001_096_08_16x16_6x6_src;
            *colKernelSource    = dgemm_Col_TT_B0_096_001_08_16x16_6x6_src;
            *cornerKernelSource = dgemm_Col_TT_B0_001_001_08_16x16_6x6_src;
            *sourceBuildOptions = dgemm_Col_TT_B0_096_096_08_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B0_096_096_08_16x16_6x6_bin;
            *rowKernelBinary    = dgemm_Col_TT_B0_001_096_08_16x16_6x6_bin;
            *colKernelBinary    = dgemm_Col_TT_B0_096_001_08_16x16_6x6_bin;
            *cornerKernelBinary = dgemm_Col_TT_B0_001_001_08_16x16_6x6_bin;
            *binaryBuildOptions = dgemm_Col_TT_B0_096_096_08_16x16_6x6_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B0_096_096_08_16x16_6x6_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B0_001_096_08_16x16_6x6_clKernel;
            *colClKernel        = &dgemm_Col_TT_B0_096_001_08_16x16_6x6_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B0_001_001_08_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B0_096_096_01_16x16_6x6_src;
            *rowKernelSource    = dgemm_Col_TT_B0_001_096_01_16x16_6x6_src;
            *colKernelSource    = dgemm_Col_TT_B0_096_001_01_16x16_6x6_src;
            *cornerKernelSource = dgemm_Col_TT_B0_001_001_01_16x16_6x6_src;
            *sourceBuildOptions = dgemm_Col_TT_B0_096_096_01_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B0_096_096_01_16x16_6x6_bin;
            *rowKernelBinary    = dgemm_Col_TT_B0_001_096_01_16x16_6x6_bin;
            *colKernelBinary    = dgemm_Col_TT_B0_096_001_01_16x16_6x6_bin;
            *cornerKernelBinary = dgemm_Col_TT_B0_001_001_01_16x16_6x6_bin;
            *binaryBuildOptions = dgemm_Col_TT_B0_096_096_01_16x16_6x6_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B0_096_096_01_16x16_6x6_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B0_001_096_01_16x16_6x6_clKernel;
            *colClKernel        = &dgemm_Col_TT_B0_096_001_01_16x16_6x6_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B0_001_001_01_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B0_128_064_08_16x16_8x4_src;
            *rowKernelSource    = dgemm_Col_TT_B0_001_064_08_16x16_8x4_src;
            *colKernelSource    = dgemm_Col_TT_B0_128_001_08_16x16_8x4_src;
            *cornerKernelSource = dgemm_Col_TT_B0_001_001_08_16x16_8x4_src;
            *sourceBuildOptions = dgemm_Col_TT_B0_128_064_08_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B0_128_064_08_16x16_8x4_bin;
            *rowKernelBinary    = dgemm_Col_TT_B0_001_064_08_16x16_8x4_bin;
            *colKernelBinary    = dgemm_Col_TT_B0_128_001_08_16x16_8x4_bin;
            *cornerKernelBinary = dgemm_Col_TT_B0_001_001_08_16x16_8x4_bin;
            *binaryBuildOptions = dgemm_Col_TT_B0_128_064_08_16x16_8x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B0_128_064_08_16x16_8x4_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B0_001_064_08_16x16_8x4_clKernel;
            *colClKernel        = &dgemm_Col_TT_B0_128_001_08_16x16_8x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B0_001_001_08_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B0_128_064_01_16x16_8x4_src;
            *rowKernelSource    = dgemm_Col_TT_B0_001_064_01_16x16_8x4_src;
            *colKernelSource    = dgemm_Col_TT_B0_128_001_01_16x16_8x4_src;
            *cornerKernelSource = dgemm_Col_TT_B0_001_001_01_16x16_8x4_src;
            *sourceBuildOptions = dgemm_Col_TT_B0_128_064_01_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B0_128_064_01_16x16_8x4_bin;
            *rowKernelBinary    = dgemm_Col_TT_B0_001_064_01_16x16_8x4_bin;
            *colKernelBinary    = dgemm_Col_TT_B0_128_001_01_16x16_8x4_bin;
            *cornerKernelBinary = dgemm_Col_TT_B0_001_001_01_16x16_8x4_bin;
            *binaryBuildOptions = dgemm_Col_TT_B0_128_064_01_16x16_8x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B0_128_064_01_16x16_8x4_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B0_001_064_01_16x16_8x4_clKernel;
            *colClKernel        = &dgemm_Col_TT_B0_128_001_01_16x16_8x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B0_001_001_01_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B0_096_064_08_16x16_6x4_src;
            *rowKernelSource    = dgemm_Col_TT_B0_001_064_08_16x16_6x4_src;
            *colKernelSource    = dgemm_Col_TT_B0_096_001_08_16x16_6x4_src;
            *cornerKernelSource = dgemm_Col_TT_B0_001_001_08_16x16_6x4_src;
            *sourceBuildOptions = dgemm_Col_TT_B0_096_064_08_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B0_096_064_08_16x16_6x4_bin;
            *rowKernelBinary    = dgemm_Col_TT_B0_001_064_08_16x16_6x4_bin;
            *colKernelBinary    = dgemm_Col_TT_B0_096_001_08_16x16_6x4_bin;
            *cornerKernelBinary = dgemm_Col_TT_B0_001_001_08_16x16_6x4_bin;
            *binaryBuildOptions = dgemm_Col_TT_B0_096_064_08_16x16_6x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B0_096_064_08_16x16_6x4_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B0_001_064_08_16x16_6x4_clKernel;
            *colClKernel        = &dgemm_Col_TT_B0_096_001_08_16x16_6x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B0_001_001_08_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B0_096_064_01_16x16_6x4_src;
            *rowKernelSource    = dgemm_Col_TT_B0_001_064_01_16x16_6x4_src;
            *colKernelSource    = dgemm_Col_TT_B0_096_001_01_16x16_6x4_src;
            *cornerKernelSource = dgemm_Col_TT_B0_001_001_01_16x16_6x4_src;
            *sourceBuildOptions = dgemm_Col_TT_B0_096_064_01_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B0_096_064_01_16x16_6x4_bin;
            *rowKernelBinary    = dgemm_Col_TT_B0_001_064_01_16x16_6x4_bin;
            *colKernelBinary    = dgemm_Col_TT_B0_096_001_01_16x16_6x4_bin;
            *cornerKernelBinary = dgemm_Col_TT_B0_001_001_01_16x16_6x4_bin;
            *binaryBuildOptions = dgemm_Col_TT_B0_096_064_01_16x16_6x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B0_096_064_01_16x16_6x4_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B0_001_064_01_16x16_6x4_clKernel;
            *colClKernel        = &dgemm_Col_TT_B0_096_001_01_16x16_6x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B0_001_001_01_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B0_064_064_08_16x16_4x4_src;
            *rowKernelSource    = dgemm_Col_TT_B0_001_064_08_16x16_4x4_src;
            *colKernelSource    = dgemm_Col_TT_B0_064_001_08_16x16_4x4_src;
            *cornerKernelSource = dgemm_Col_TT_B0_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = dgemm_Col_TT_B0_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B0_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = dgemm_Col_TT_B0_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = dgemm_Col_TT_B0_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = dgemm_Col_TT_B0_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = dgemm_Col_TT_B0_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B0_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B0_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &dgemm_Col_TT_B0_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B0_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B0_064_064_01_16x16_4x4_src;
            *rowKernelSource    = dgemm_Col_TT_B0_001_064_01_16x16_4x4_src;
            *colKernelSource    = dgemm_Col_TT_B0_064_001_01_16x16_4x4_src;
            *cornerKernelSource = dgemm_Col_TT_B0_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = dgemm_Col_TT_B0_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B0_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = dgemm_Col_TT_B0_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = dgemm_Col_TT_B0_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = dgemm_Col_TT_B0_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = dgemm_Col_TT_B0_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B0_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B0_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &dgemm_Col_TT_B0_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B0_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = dgemm_Col_TT_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = dgemm_Col_TT_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = dgemm_Col_TT_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = dgemm_Col_TT_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = dgemm_Col_TT_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = dgemm_Col_TT_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = dgemm_Col_TT_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = dgemm_Col_TT_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &dgemm_Col_TT_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = dgemm_Col_TT_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = dgemm_Col_TT_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = dgemm_Col_TT_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = dgemm_Col_TT_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = dgemm_Col_TT_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = dgemm_Col_TT_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = dgemm_Col_TT_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = dgemm_Col_TT_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &dgemm_Col_TT_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = dgemm_Col_TT_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = dgemm_Col_TT_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = dgemm_Col_TT_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = dgemm_Col_TT_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = dgemm_Col_TT_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = dgemm_Col_TT_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = dgemm_Col_TT_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = dgemm_Col_TT_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &dgemm_Col_TT_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = dgemm_Col_TT_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = dgemm_Col_TT_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = dgemm_Col_TT_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = dgemm_Col_TT_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = dgemm_Col_TT_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = dgemm_Col_TT_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = dgemm_Col_TT_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = dgemm_Col_TT_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &dgemm_Col_TT_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = dgemm_Col_TT_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = dgemm_Col_TT_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = dgemm_Col_TT_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = dgemm_Col_TT_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = dgemm_Col_TT_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = dgemm_Col_TT_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = dgemm_Col_TT_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = dgemm_Col_TT_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &dgemm_Col_TT_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = dgemm_Col_TT_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = dgemm_Col_TT_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = dgemm_Col_TT_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = dgemm_Col_TT_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = dgemm_Col_TT_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = dgemm_Col_TT_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = dgemm_Col_TT_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = dgemm_Col_TT_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &dgemm_Col_TT_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = dgemm_Col_TT_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = dgemm_Col_TT_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = dgemm_Col_TT_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = dgemm_Col_TT_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = dgemm_Col_TT_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = dgemm_Col_TT_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = dgemm_Col_TT_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = dgemm_Col_TT_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &dgemm_Col_TT_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = dgemm_Col_TT_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = dgemm_Col_TT_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = dgemm_Col_TT_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = dgemm_Col_TT_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = dgemm_Col_TT_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = dgemm_Col_TT_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = dgemm_Col_TT_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = dgemm_Col_TT_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &dgemm_Col_TT_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 32) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B1_096_096_08_16x16_6x6_src;
            *rowKernelSource    = dgemm_Col_TT_B1_001_096_08_16x16_6x6_src;
            *colKernelSource    = dgemm_Col_TT_B1_096_001_08_16x16_6x6_src;
            *cornerKernelSource = dgemm_Col_TT_B1_001_001_08_16x16_6x6_src;
            *sourceBuildOptions = dgemm_Col_TT_B1_096_096_08_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B1_096_096_08_16x16_6x6_bin;
            *rowKernelBinary    = dgemm_Col_TT_B1_001_096_08_16x16_6x6_bin;
            *colKernelBinary    = dgemm_Col_TT_B1_096_001_08_16x16_6x6_bin;
            *cornerKernelBinary = dgemm_Col_TT_B1_001_001_08_16x16_6x6_bin;
            *binaryBuildOptions = dgemm_Col_TT_B1_096_096_08_16x16_6x6_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B1_096_096_08_16x16_6x6_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B1_001_096_08_16x16_6x6_clKernel;
            *colClKernel        = &dgemm_Col_TT_B1_096_001_08_16x16_6x6_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B1_001_001_08_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%96 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B1_096_096_01_16x16_6x6_src;
            *rowKernelSource    = dgemm_Col_TT_B1_001_096_01_16x16_6x6_src;
            *colKernelSource    = dgemm_Col_TT_B1_096_001_01_16x16_6x6_src;
            *cornerKernelSource = dgemm_Col_TT_B1_001_001_01_16x16_6x6_src;
            *sourceBuildOptions = dgemm_Col_TT_B1_096_096_01_16x16_6x6_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B1_096_096_01_16x16_6x6_bin;
            *rowKernelBinary    = dgemm_Col_TT_B1_001_096_01_16x16_6x6_bin;
            *colKernelBinary    = dgemm_Col_TT_B1_096_001_01_16x16_6x6_bin;
            *cornerKernelBinary = dgemm_Col_TT_B1_001_001_01_16x16_6x6_bin;
            *binaryBuildOptions = dgemm_Col_TT_B1_096_096_01_16x16_6x6_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B1_096_096_01_16x16_6x6_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B1_001_096_01_16x16_6x6_clKernel;
            *colClKernel        = &dgemm_Col_TT_B1_096_001_01_16x16_6x6_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B1_001_001_01_16x16_6x6_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B1_128_064_08_16x16_8x4_src;
            *rowKernelSource    = dgemm_Col_TT_B1_001_064_08_16x16_8x4_src;
            *colKernelSource    = dgemm_Col_TT_B1_128_001_08_16x16_8x4_src;
            *cornerKernelSource = dgemm_Col_TT_B1_001_001_08_16x16_8x4_src;
            *sourceBuildOptions = dgemm_Col_TT_B1_128_064_08_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B1_128_064_08_16x16_8x4_bin;
            *rowKernelBinary    = dgemm_Col_TT_B1_001_064_08_16x16_8x4_bin;
            *colKernelBinary    = dgemm_Col_TT_B1_128_001_08_16x16_8x4_bin;
            *cornerKernelBinary = dgemm_Col_TT_B1_001_001_08_16x16_8x4_bin;
            *binaryBuildOptions = dgemm_Col_TT_B1_128_064_08_16x16_8x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B1_128_064_08_16x16_8x4_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B1_001_064_08_16x16_8x4_clKernel;
            *colClKernel        = &dgemm_Col_TT_B1_128_001_08_16x16_8x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B1_001_001_08_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%128 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B1_128_064_01_16x16_8x4_src;
            *rowKernelSource    = dgemm_Col_TT_B1_001_064_01_16x16_8x4_src;
            *colKernelSource    = dgemm_Col_TT_B1_128_001_01_16x16_8x4_src;
            *cornerKernelSource = dgemm_Col_TT_B1_001_001_01_16x16_8x4_src;
            *sourceBuildOptions = dgemm_Col_TT_B1_128_064_01_16x16_8x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B1_128_064_01_16x16_8x4_bin;
            *rowKernelBinary    = dgemm_Col_TT_B1_001_064_01_16x16_8x4_bin;
            *colKernelBinary    = dgemm_Col_TT_B1_128_001_01_16x16_8x4_bin;
            *cornerKernelBinary = dgemm_Col_TT_B1_001_001_01_16x16_8x4_bin;
            *binaryBuildOptions = dgemm_Col_TT_B1_128_064_01_16x16_8x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B1_128_064_01_16x16_8x4_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B1_001_064_01_16x16_8x4_clKernel;
            *colClKernel        = &dgemm_Col_TT_B1_128_001_01_16x16_8x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B1_001_001_01_16x16_8x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B1_096_064_08_16x16_6x4_src;
            *rowKernelSource    = dgemm_Col_TT_B1_001_064_08_16x16_6x4_src;
            *colKernelSource    = dgemm_Col_TT_B1_096_001_08_16x16_6x4_src;
            *cornerKernelSource = dgemm_Col_TT_B1_001_001_08_16x16_6x4_src;
            *sourceBuildOptions = dgemm_Col_TT_B1_096_064_08_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B1_096_064_08_16x16_6x4_bin;
            *rowKernelBinary    = dgemm_Col_TT_B1_001_064_08_16x16_6x4_bin;
            *colKernelBinary    = dgemm_Col_TT_B1_096_001_08_16x16_6x4_bin;
            *cornerKernelBinary = dgemm_Col_TT_B1_001_001_08_16x16_6x4_bin;
            *binaryBuildOptions = dgemm_Col_TT_B1_096_064_08_16x16_6x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B1_096_064_08_16x16_6x4_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B1_001_064_08_16x16_6x4_clKernel;
            *colClKernel        = &dgemm_Col_TT_B1_096_001_08_16x16_6x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B1_001_001_08_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%96 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B1_096_064_01_16x16_6x4_src;
            *rowKernelSource    = dgemm_Col_TT_B1_001_064_01_16x16_6x4_src;
            *colKernelSource    = dgemm_Col_TT_B1_096_001_01_16x16_6x4_src;
            *cornerKernelSource = dgemm_Col_TT_B1_001_001_01_16x16_6x4_src;
            *sourceBuildOptions = dgemm_Col_TT_B1_096_064_01_16x16_6x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B1_096_064_01_16x16_6x4_bin;
            *rowKernelBinary    = dgemm_Col_TT_B1_001_064_01_16x16_6x4_bin;
            *colKernelBinary    = dgemm_Col_TT_B1_096_001_01_16x16_6x4_bin;
            *cornerKernelBinary = dgemm_Col_TT_B1_001_001_01_16x16_6x4_bin;
            *binaryBuildOptions = dgemm_Col_TT_B1_096_064_01_16x16_6x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B1_096_064_01_16x16_6x4_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B1_001_064_01_16x16_6x4_clKernel;
            *colClKernel        = &dgemm_Col_TT_B1_096_001_01_16x16_6x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B1_001_001_01_16x16_6x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B1_064_064_08_16x16_4x4_src;
            *rowKernelSource    = dgemm_Col_TT_B1_001_064_08_16x16_4x4_src;
            *colKernelSource    = dgemm_Col_TT_B1_064_001_08_16x16_4x4_src;
            *cornerKernelSource = dgemm_Col_TT_B1_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = dgemm_Col_TT_B1_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B1_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = dgemm_Col_TT_B1_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = dgemm_Col_TT_B1_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = dgemm_Col_TT_B1_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = dgemm_Col_TT_B1_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B1_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B1_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &dgemm_Col_TT_B1_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B1_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B1_064_064_01_16x16_4x4_src;
            *rowKernelSource    = dgemm_Col_TT_B1_001_064_01_16x16_4x4_src;
            *colKernelSource    = dgemm_Col_TT_B1_064_001_01_16x16_4x4_src;
            *cornerKernelSource = dgemm_Col_TT_B1_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = dgemm_Col_TT_B1_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B1_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = dgemm_Col_TT_B1_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = dgemm_Col_TT_B1_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = dgemm_Col_TT_B1_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = dgemm_Col_TT_B1_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B1_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B1_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &dgemm_Col_TT_B1_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B1_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = dgemm_Col_TT_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = dgemm_Col_TT_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = dgemm_Col_TT_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = dgemm_Col_TT_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = dgemm_Col_TT_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = dgemm_Col_TT_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = dgemm_Col_TT_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = dgemm_Col_TT_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &dgemm_Col_TT_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = dgemm_Col_TT_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = dgemm_Col_TT_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = dgemm_Col_TT_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = dgemm_Col_TT_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = dgemm_Col_TT_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = dgemm_Col_TT_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = dgemm_Col_TT_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = dgemm_Col_TT_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &dgemm_Col_TT_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = dgemm_Col_TT_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = dgemm_Col_TT_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = dgemm_Col_TT_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = dgemm_Col_TT_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = dgemm_Col_TT_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = dgemm_Col_TT_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = dgemm_Col_TT_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = dgemm_Col_TT_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &dgemm_Col_TT_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = dgemm_Col_TT_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = dgemm_Col_TT_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = dgemm_Col_TT_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = dgemm_Col_TT_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = dgemm_Col_TT_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = dgemm_Col_TT_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = dgemm_Col_TT_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = dgemm_Col_TT_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &dgemm_Col_TT_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = dgemm_Col_TT_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = dgemm_Col_TT_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = dgemm_Col_TT_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = dgemm_Col_TT_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = dgemm_Col_TT_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = dgemm_Col_TT_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = dgemm_Col_TT_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = dgemm_Col_TT_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &dgemm_Col_TT_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = dgemm_Col_TT_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = dgemm_Col_TT_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = dgemm_Col_TT_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = dgemm_Col_TT_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = dgemm_Col_TT_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = dgemm_Col_TT_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = dgemm_Col_TT_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = dgemm_Col_TT_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &dgemm_Col_TT_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = dgemm_Col_TT_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = dgemm_Col_TT_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = dgemm_Col_TT_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = dgemm_Col_TT_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = dgemm_Col_TT_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = dgemm_Col_TT_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = dgemm_Col_TT_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = dgemm_Col_TT_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &dgemm_Col_TT_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = dgemm_Col_TT_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = dgemm_Col_TT_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = dgemm_Col_TT_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = dgemm_Col_TT_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = dgemm_Col_TT_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = dgemm_Col_TT_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = dgemm_Col_TT_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = dgemm_Col_TT_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = dgemm_Col_TT_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = dgemm_Col_TT_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &dgemm_Col_TT_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &dgemm_Col_TT_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &dgemm_Col_TT_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &dgemm_Col_TT_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    }
  }
}

// cgemm kernel selection logic
template<>
void gemmSelectKernel<FloatComplex>(
  clblasOrder order,
  clblasTranspose transA,
  clblasTranspose transB,
  size_t M,
  size_t N,
  size_t K,
  bool betaNonZero,
  float optimalNumElementsPerWorkItem,
  const char **tileKernelSource,
  const char **rowKernelSource,
  const char **colKernelSource,
  const char **cornerKernelSource,
  const char **sourceBuildOptions,
  const unsigned char **tileKernelBinary,
  const unsigned char **rowKernelBinary,
  const unsigned char **colKernelBinary,
  const unsigned char **cornerKernelBinary,
  const char **binaryBuildOptions,
  cl_kernel  **tileClKernel,
  cl_kernel  **rowClKernel,
  cl_kernel  **colClKernel,
  cl_kernel  **cornerClKernel,
  unsigned int *workGroupNumRows,
  unsigned int *workGroupNumCols,
  unsigned int *microTileNumRows,
  unsigned int *microTileNumCols,
  unsigned int *unroll
) {
  if (order == clblasColumnMajor) {
    if (transA == clblasNoTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B0_064_064_08_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_NN_B0_001_064_08_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_NN_B0_064_001_08_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_NN_B0_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_NN_B0_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B0_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_NN_B0_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_NN_B0_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_NN_B0_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_NN_B0_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B0_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B0_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_NN_B0_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B0_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B0_064_064_01_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_NN_B0_001_064_01_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_NN_B0_064_001_01_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_NN_B0_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_NN_B0_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B0_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_NN_B0_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_NN_B0_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_NN_B0_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_NN_B0_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B0_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B0_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_NN_B0_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B0_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_NN_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_NN_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_NN_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_NN_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_NN_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_NN_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_NN_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_NN_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_NN_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_NN_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_NN_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_NN_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_NN_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_NN_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_NN_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_NN_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_NN_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_NN_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_NN_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_NN_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_NN_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_NN_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_NN_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_NN_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_NN_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_NN_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_NN_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_NN_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_NN_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_NN_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_NN_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_NN_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_NN_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_NN_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_NN_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_NN_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_NN_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_NN_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_NN_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_NN_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_NN_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_NN_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_NN_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_NN_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_NN_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_NN_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_NN_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_NN_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_NN_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_NN_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_NN_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_NN_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_NN_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_NN_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_NN_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_NN_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_NN_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_NN_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_NN_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_NN_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_NN_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_NN_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_NN_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_NN_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_NN_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_NN_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_NN_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_NN_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_NN_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_NN_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_NN_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_NN_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B1_064_064_08_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_NN_B1_001_064_08_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_NN_B1_064_001_08_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_NN_B1_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_NN_B1_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B1_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_NN_B1_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_NN_B1_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_NN_B1_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_NN_B1_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B1_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B1_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_NN_B1_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B1_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B1_064_064_01_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_NN_B1_001_064_01_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_NN_B1_064_001_01_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_NN_B1_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_NN_B1_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B1_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_NN_B1_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_NN_B1_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_NN_B1_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_NN_B1_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B1_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B1_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_NN_B1_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B1_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_NN_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_NN_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_NN_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_NN_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_NN_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_NN_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_NN_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_NN_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_NN_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_NN_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_NN_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_NN_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_NN_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_NN_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_NN_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_NN_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_NN_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_NN_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_NN_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_NN_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_NN_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_NN_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_NN_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_NN_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_NN_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_NN_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_NN_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_NN_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_NN_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_NN_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_NN_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_NN_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_NN_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_NN_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_NN_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_NN_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_NN_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_NN_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_NN_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_NN_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_NN_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_NN_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_NN_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_NN_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_NN_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_NN_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_NN_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_NN_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_NN_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_NN_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_NN_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_NN_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_NN_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_NN_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_NN_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_NN_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_NN_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_NN_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_NN_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_NN_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_NN_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_NN_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_NN_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NN_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_NN_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_NN_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_NN_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_NN_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NN_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_NN_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_NN_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_NN_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_NN_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NN_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_NN_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_NN_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NN_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasNoTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B0_064_064_08_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_NT_B0_001_064_08_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_NT_B0_064_001_08_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_NT_B0_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_NT_B0_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B0_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_NT_B0_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_NT_B0_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_NT_B0_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_NT_B0_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B0_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B0_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_NT_B0_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B0_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B0_064_064_01_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_NT_B0_001_064_01_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_NT_B0_064_001_01_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_NT_B0_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_NT_B0_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B0_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_NT_B0_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_NT_B0_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_NT_B0_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_NT_B0_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B0_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B0_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_NT_B0_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B0_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_NT_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_NT_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_NT_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_NT_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_NT_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_NT_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_NT_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_NT_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_NT_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_NT_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_NT_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_NT_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_NT_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_NT_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_NT_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_NT_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_NT_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_NT_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_NT_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_NT_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_NT_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_NT_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_NT_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_NT_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_NT_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_NT_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_NT_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_NT_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_NT_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_NT_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_NT_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_NT_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_NT_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_NT_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_NT_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_NT_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_NT_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_NT_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_NT_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_NT_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_NT_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_NT_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_NT_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_NT_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_NT_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_NT_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_NT_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_NT_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_NT_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_NT_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_NT_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_NT_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_NT_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_NT_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_NT_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_NT_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_NT_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_NT_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_NT_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_NT_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_NT_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_NT_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_NT_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_NT_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_NT_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_NT_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_NT_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_NT_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_NT_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_NT_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_NT_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_NT_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B1_064_064_08_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_NT_B1_001_064_08_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_NT_B1_064_001_08_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_NT_B1_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_NT_B1_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B1_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_NT_B1_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_NT_B1_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_NT_B1_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_NT_B1_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B1_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B1_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_NT_B1_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B1_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B1_064_064_01_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_NT_B1_001_064_01_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_NT_B1_064_001_01_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_NT_B1_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_NT_B1_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B1_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_NT_B1_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_NT_B1_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_NT_B1_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_NT_B1_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B1_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B1_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_NT_B1_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B1_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_NT_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_NT_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_NT_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_NT_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_NT_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_NT_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_NT_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_NT_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_NT_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_NT_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_NT_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_NT_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_NT_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_NT_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_NT_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_NT_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_NT_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_NT_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_NT_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_NT_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_NT_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_NT_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_NT_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_NT_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_NT_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_NT_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_NT_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_NT_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_NT_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_NT_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_NT_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_NT_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_NT_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_NT_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_NT_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_NT_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_NT_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_NT_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_NT_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_NT_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_NT_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_NT_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_NT_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_NT_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_NT_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_NT_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_NT_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_NT_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_NT_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_NT_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_NT_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_NT_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_NT_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_NT_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_NT_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_NT_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_NT_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_NT_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_NT_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_NT_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_NT_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_NT_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_NT_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NT_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_NT_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_NT_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_NT_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_NT_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NT_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_NT_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_NT_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_NT_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_NT_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NT_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_NT_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_NT_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NT_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasNoTrans && transB == clblasConjTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B0_064_064_08_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_NC_B0_001_064_08_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_NC_B0_064_001_08_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_NC_B0_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_NC_B0_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B0_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_NC_B0_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_NC_B0_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_NC_B0_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_NC_B0_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B0_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B0_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_NC_B0_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B0_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B0_064_064_01_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_NC_B0_001_064_01_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_NC_B0_064_001_01_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_NC_B0_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_NC_B0_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B0_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_NC_B0_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_NC_B0_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_NC_B0_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_NC_B0_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B0_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B0_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_NC_B0_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B0_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_NC_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_NC_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_NC_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_NC_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_NC_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_NC_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_NC_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_NC_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_NC_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_NC_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_NC_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_NC_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_NC_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_NC_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_NC_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_NC_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_NC_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_NC_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_NC_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_NC_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_NC_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_NC_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_NC_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_NC_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_NC_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_NC_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_NC_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_NC_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_NC_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_NC_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_NC_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_NC_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_NC_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_NC_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_NC_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_NC_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_NC_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_NC_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_NC_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_NC_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_NC_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_NC_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_NC_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_NC_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_NC_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_NC_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_NC_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_NC_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_NC_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_NC_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_NC_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_NC_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_NC_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_NC_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_NC_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_NC_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_NC_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_NC_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_NC_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_NC_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_NC_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_NC_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_NC_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_NC_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_NC_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_NC_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_NC_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_NC_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_NC_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_NC_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_NC_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_NC_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B1_064_064_08_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_NC_B1_001_064_08_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_NC_B1_064_001_08_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_NC_B1_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_NC_B1_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B1_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_NC_B1_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_NC_B1_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_NC_B1_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_NC_B1_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B1_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B1_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_NC_B1_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B1_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B1_064_064_01_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_NC_B1_001_064_01_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_NC_B1_064_001_01_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_NC_B1_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_NC_B1_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B1_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_NC_B1_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_NC_B1_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_NC_B1_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_NC_B1_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B1_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B1_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_NC_B1_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B1_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_NC_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_NC_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_NC_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_NC_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_NC_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_NC_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_NC_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_NC_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_NC_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_NC_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_NC_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_NC_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_NC_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_NC_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_NC_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_NC_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_NC_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_NC_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_NC_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_NC_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_NC_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_NC_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_NC_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_NC_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_NC_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_NC_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_NC_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_NC_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_NC_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_NC_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_NC_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_NC_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_NC_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_NC_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_NC_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_NC_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_NC_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_NC_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_NC_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_NC_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_NC_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_NC_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_NC_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_NC_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_NC_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_NC_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_NC_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_NC_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_NC_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_NC_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_NC_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_NC_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_NC_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_NC_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_NC_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_NC_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_NC_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_NC_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_NC_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_NC_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_NC_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_NC_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_NC_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_NC_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_NC_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_NC_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_NC_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_NC_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_NC_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_NC_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_NC_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_NC_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_NC_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_NC_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_NC_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_NC_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_NC_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B0_064_064_08_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_TN_B0_001_064_08_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_TN_B0_064_001_08_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_TN_B0_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_TN_B0_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B0_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_TN_B0_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_TN_B0_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_TN_B0_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_TN_B0_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B0_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B0_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_TN_B0_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B0_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B0_064_064_01_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_TN_B0_001_064_01_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_TN_B0_064_001_01_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_TN_B0_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_TN_B0_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B0_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_TN_B0_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_TN_B0_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_TN_B0_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_TN_B0_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B0_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B0_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_TN_B0_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B0_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_TN_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_TN_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_TN_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_TN_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_TN_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_TN_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_TN_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_TN_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_TN_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_TN_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_TN_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_TN_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_TN_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_TN_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_TN_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_TN_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_TN_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_TN_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_TN_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_TN_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_TN_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_TN_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_TN_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_TN_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_TN_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_TN_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_TN_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_TN_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_TN_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_TN_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_TN_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_TN_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_TN_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_TN_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_TN_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_TN_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_TN_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_TN_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_TN_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_TN_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_TN_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_TN_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_TN_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_TN_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_TN_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_TN_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_TN_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_TN_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_TN_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_TN_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_TN_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_TN_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_TN_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_TN_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_TN_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_TN_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_TN_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_TN_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_TN_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_TN_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_TN_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_TN_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_TN_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_TN_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_TN_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_TN_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_TN_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_TN_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_TN_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_TN_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_TN_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_TN_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B1_064_064_08_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_TN_B1_001_064_08_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_TN_B1_064_001_08_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_TN_B1_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_TN_B1_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B1_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_TN_B1_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_TN_B1_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_TN_B1_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_TN_B1_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B1_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B1_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_TN_B1_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B1_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B1_064_064_01_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_TN_B1_001_064_01_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_TN_B1_064_001_01_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_TN_B1_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_TN_B1_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B1_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_TN_B1_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_TN_B1_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_TN_B1_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_TN_B1_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B1_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B1_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_TN_B1_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B1_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_TN_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_TN_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_TN_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_TN_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_TN_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_TN_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_TN_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_TN_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_TN_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_TN_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_TN_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_TN_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_TN_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_TN_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_TN_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_TN_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_TN_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_TN_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_TN_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_TN_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_TN_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_TN_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_TN_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_TN_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_TN_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_TN_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_TN_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_TN_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_TN_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_TN_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_TN_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_TN_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_TN_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_TN_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_TN_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_TN_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_TN_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_TN_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_TN_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_TN_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_TN_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_TN_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_TN_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_TN_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_TN_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_TN_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_TN_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_TN_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_TN_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_TN_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_TN_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_TN_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_TN_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_TN_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_TN_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_TN_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_TN_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_TN_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_TN_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_TN_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_TN_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_TN_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_TN_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TN_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_TN_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_TN_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_TN_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_TN_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TN_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_TN_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_TN_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_TN_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_TN_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TN_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_TN_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_TN_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TN_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B0_064_064_08_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_TT_B0_001_064_08_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_TT_B0_064_001_08_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_TT_B0_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_TT_B0_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B0_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_TT_B0_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_TT_B0_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_TT_B0_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_TT_B0_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B0_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B0_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_TT_B0_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B0_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B0_064_064_01_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_TT_B0_001_064_01_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_TT_B0_064_001_01_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_TT_B0_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_TT_B0_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B0_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_TT_B0_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_TT_B0_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_TT_B0_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_TT_B0_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B0_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B0_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_TT_B0_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B0_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_TT_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_TT_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_TT_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_TT_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_TT_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_TT_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_TT_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_TT_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_TT_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_TT_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_TT_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_TT_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_TT_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_TT_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_TT_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_TT_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_TT_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_TT_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_TT_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_TT_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_TT_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_TT_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_TT_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_TT_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_TT_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_TT_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_TT_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_TT_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_TT_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_TT_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_TT_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_TT_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_TT_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_TT_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_TT_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_TT_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_TT_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_TT_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_TT_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_TT_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_TT_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_TT_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_TT_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_TT_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_TT_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_TT_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_TT_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_TT_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_TT_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_TT_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_TT_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_TT_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_TT_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_TT_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_TT_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_TT_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_TT_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_TT_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_TT_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_TT_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_TT_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_TT_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_TT_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_TT_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_TT_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_TT_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_TT_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_TT_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_TT_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_TT_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_TT_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_TT_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B1_064_064_08_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_TT_B1_001_064_08_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_TT_B1_064_001_08_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_TT_B1_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_TT_B1_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B1_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_TT_B1_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_TT_B1_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_TT_B1_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_TT_B1_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B1_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B1_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_TT_B1_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B1_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B1_064_064_01_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_TT_B1_001_064_01_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_TT_B1_064_001_01_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_TT_B1_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_TT_B1_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B1_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_TT_B1_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_TT_B1_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_TT_B1_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_TT_B1_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B1_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B1_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_TT_B1_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B1_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_TT_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_TT_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_TT_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_TT_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_TT_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_TT_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_TT_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_TT_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_TT_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_TT_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_TT_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_TT_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_TT_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_TT_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_TT_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_TT_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_TT_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_TT_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_TT_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_TT_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_TT_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_TT_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_TT_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_TT_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_TT_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_TT_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_TT_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_TT_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_TT_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_TT_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_TT_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_TT_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_TT_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_TT_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_TT_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_TT_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_TT_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_TT_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_TT_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_TT_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_TT_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_TT_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_TT_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_TT_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_TT_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_TT_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_TT_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_TT_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_TT_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_TT_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_TT_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_TT_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_TT_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_TT_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_TT_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_TT_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_TT_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_TT_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_TT_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_TT_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_TT_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_TT_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_TT_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TT_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_TT_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_TT_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_TT_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_TT_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TT_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_TT_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_TT_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_TT_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_TT_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TT_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_TT_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_TT_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TT_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasTrans && transB == clblasConjTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B0_064_064_08_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_TC_B0_001_064_08_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_TC_B0_064_001_08_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_TC_B0_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_TC_B0_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B0_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_TC_B0_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_TC_B0_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_TC_B0_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_TC_B0_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B0_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B0_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_TC_B0_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B0_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B0_064_064_01_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_TC_B0_001_064_01_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_TC_B0_064_001_01_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_TC_B0_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_TC_B0_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B0_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_TC_B0_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_TC_B0_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_TC_B0_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_TC_B0_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B0_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B0_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_TC_B0_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B0_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_TC_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_TC_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_TC_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_TC_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_TC_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_TC_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_TC_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_TC_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_TC_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_TC_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_TC_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_TC_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_TC_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_TC_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_TC_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_TC_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_TC_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_TC_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_TC_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_TC_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_TC_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_TC_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_TC_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_TC_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_TC_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_TC_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_TC_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_TC_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_TC_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_TC_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_TC_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_TC_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_TC_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_TC_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_TC_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_TC_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_TC_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_TC_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_TC_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_TC_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_TC_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_TC_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_TC_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_TC_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_TC_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_TC_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_TC_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_TC_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_TC_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_TC_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_TC_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_TC_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_TC_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_TC_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_TC_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_TC_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_TC_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_TC_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_TC_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_TC_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_TC_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_TC_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_TC_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_TC_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_TC_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_TC_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_TC_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_TC_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_TC_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_TC_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_TC_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_TC_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B1_064_064_08_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_TC_B1_001_064_08_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_TC_B1_064_001_08_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_TC_B1_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_TC_B1_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B1_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_TC_B1_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_TC_B1_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_TC_B1_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_TC_B1_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B1_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B1_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_TC_B1_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B1_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B1_064_064_01_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_TC_B1_001_064_01_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_TC_B1_064_001_01_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_TC_B1_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_TC_B1_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B1_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_TC_B1_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_TC_B1_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_TC_B1_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_TC_B1_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B1_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B1_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_TC_B1_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B1_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_TC_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_TC_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_TC_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_TC_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_TC_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_TC_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_TC_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_TC_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_TC_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_TC_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_TC_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_TC_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_TC_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_TC_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_TC_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_TC_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_TC_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_TC_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_TC_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_TC_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_TC_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_TC_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_TC_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_TC_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_TC_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_TC_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_TC_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_TC_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_TC_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_TC_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_TC_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_TC_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_TC_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_TC_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_TC_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_TC_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_TC_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_TC_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_TC_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_TC_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_TC_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_TC_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_TC_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_TC_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_TC_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_TC_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_TC_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_TC_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_TC_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_TC_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_TC_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_TC_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_TC_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_TC_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_TC_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_TC_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_TC_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_TC_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_TC_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_TC_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_TC_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_TC_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_TC_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_TC_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_TC_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_TC_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_TC_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_TC_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_TC_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_TC_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_TC_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_TC_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_TC_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_TC_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_TC_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_TC_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_TC_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasConjTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B0_064_064_08_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_CN_B0_001_064_08_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_CN_B0_064_001_08_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_CN_B0_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_CN_B0_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B0_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_CN_B0_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_CN_B0_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_CN_B0_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_CN_B0_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B0_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B0_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_CN_B0_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B0_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B0_064_064_01_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_CN_B0_001_064_01_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_CN_B0_064_001_01_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_CN_B0_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_CN_B0_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B0_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_CN_B0_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_CN_B0_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_CN_B0_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_CN_B0_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B0_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B0_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_CN_B0_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B0_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_CN_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_CN_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_CN_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_CN_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_CN_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_CN_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_CN_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_CN_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_CN_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_CN_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_CN_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_CN_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_CN_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_CN_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_CN_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_CN_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_CN_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_CN_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_CN_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_CN_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_CN_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_CN_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_CN_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_CN_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_CN_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_CN_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_CN_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_CN_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_CN_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_CN_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_CN_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_CN_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_CN_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_CN_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_CN_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_CN_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_CN_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_CN_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_CN_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_CN_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_CN_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_CN_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_CN_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_CN_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_CN_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_CN_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_CN_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_CN_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_CN_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_CN_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_CN_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_CN_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_CN_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_CN_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_CN_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_CN_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_CN_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_CN_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_CN_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_CN_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_CN_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_CN_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_CN_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_CN_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_CN_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_CN_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_CN_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_CN_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_CN_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_CN_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_CN_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_CN_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B1_064_064_08_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_CN_B1_001_064_08_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_CN_B1_064_001_08_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_CN_B1_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_CN_B1_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B1_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_CN_B1_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_CN_B1_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_CN_B1_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_CN_B1_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B1_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B1_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_CN_B1_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B1_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B1_064_064_01_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_CN_B1_001_064_01_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_CN_B1_064_001_01_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_CN_B1_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_CN_B1_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B1_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_CN_B1_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_CN_B1_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_CN_B1_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_CN_B1_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B1_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B1_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_CN_B1_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B1_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_CN_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_CN_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_CN_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_CN_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_CN_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_CN_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_CN_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_CN_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_CN_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_CN_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_CN_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_CN_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_CN_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_CN_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_CN_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_CN_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_CN_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_CN_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_CN_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_CN_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_CN_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_CN_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_CN_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_CN_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_CN_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_CN_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_CN_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_CN_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_CN_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_CN_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_CN_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_CN_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_CN_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_CN_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_CN_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_CN_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_CN_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_CN_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_CN_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_CN_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_CN_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_CN_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_CN_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_CN_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_CN_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_CN_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_CN_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_CN_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_CN_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_CN_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_CN_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_CN_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_CN_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_CN_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_CN_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_CN_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_CN_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_CN_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_CN_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_CN_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_CN_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_CN_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_CN_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CN_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_CN_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_CN_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_CN_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_CN_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CN_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_CN_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_CN_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_CN_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_CN_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CN_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_CN_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_CN_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CN_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasConjTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B0_064_064_08_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_CT_B0_001_064_08_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_CT_B0_064_001_08_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_CT_B0_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_CT_B0_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B0_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_CT_B0_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_CT_B0_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_CT_B0_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_CT_B0_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B0_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B0_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_CT_B0_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B0_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B0_064_064_01_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_CT_B0_001_064_01_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_CT_B0_064_001_01_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_CT_B0_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_CT_B0_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B0_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_CT_B0_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_CT_B0_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_CT_B0_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_CT_B0_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B0_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B0_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_CT_B0_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B0_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_CT_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_CT_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_CT_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_CT_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_CT_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_CT_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_CT_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_CT_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_CT_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_CT_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_CT_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_CT_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_CT_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_CT_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_CT_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_CT_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_CT_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_CT_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_CT_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_CT_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_CT_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_CT_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_CT_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_CT_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_CT_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_CT_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_CT_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_CT_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_CT_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_CT_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_CT_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_CT_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_CT_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_CT_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_CT_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_CT_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_CT_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_CT_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_CT_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_CT_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_CT_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_CT_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_CT_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_CT_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_CT_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_CT_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_CT_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_CT_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_CT_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_CT_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_CT_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_CT_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_CT_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_CT_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_CT_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_CT_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_CT_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_CT_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_CT_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_CT_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_CT_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_CT_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_CT_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_CT_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_CT_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_CT_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_CT_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_CT_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_CT_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_CT_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_CT_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_CT_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B1_064_064_08_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_CT_B1_001_064_08_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_CT_B1_064_001_08_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_CT_B1_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_CT_B1_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B1_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_CT_B1_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_CT_B1_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_CT_B1_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_CT_B1_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B1_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B1_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_CT_B1_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B1_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B1_064_064_01_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_CT_B1_001_064_01_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_CT_B1_064_001_01_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_CT_B1_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_CT_B1_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B1_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_CT_B1_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_CT_B1_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_CT_B1_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_CT_B1_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B1_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B1_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_CT_B1_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B1_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_CT_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_CT_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_CT_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_CT_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_CT_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_CT_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_CT_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_CT_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_CT_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_CT_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_CT_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_CT_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_CT_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_CT_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_CT_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_CT_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_CT_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_CT_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_CT_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_CT_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_CT_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_CT_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_CT_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_CT_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_CT_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_CT_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_CT_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_CT_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_CT_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_CT_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_CT_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_CT_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_CT_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_CT_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_CT_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_CT_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_CT_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_CT_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_CT_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_CT_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_CT_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_CT_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_CT_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_CT_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_CT_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_CT_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_CT_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_CT_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_CT_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_CT_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_CT_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_CT_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_CT_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_CT_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_CT_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_CT_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_CT_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_CT_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_CT_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_CT_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_CT_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_CT_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_CT_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CT_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_CT_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_CT_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_CT_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_CT_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CT_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_CT_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_CT_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_CT_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_CT_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CT_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_CT_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_CT_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CT_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasConjTrans && transB == clblasConjTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B0_064_064_08_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_CC_B0_001_064_08_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_CC_B0_064_001_08_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_CC_B0_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_CC_B0_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B0_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_CC_B0_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_CC_B0_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_CC_B0_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_CC_B0_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B0_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B0_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_CC_B0_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B0_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B0_064_064_01_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_CC_B0_001_064_01_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_CC_B0_064_001_01_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_CC_B0_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_CC_B0_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B0_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_CC_B0_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_CC_B0_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_CC_B0_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_CC_B0_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B0_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B0_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_CC_B0_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B0_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_CC_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_CC_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_CC_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_CC_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_CC_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_CC_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_CC_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_CC_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_CC_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_CC_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_CC_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_CC_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_CC_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_CC_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_CC_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_CC_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_CC_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_CC_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_CC_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_CC_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_CC_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_CC_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_CC_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_CC_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_CC_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_CC_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_CC_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_CC_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_CC_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_CC_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_CC_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_CC_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_CC_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_CC_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_CC_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_CC_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_CC_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_CC_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_CC_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_CC_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_CC_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_CC_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_CC_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_CC_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_CC_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_CC_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_CC_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_CC_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_CC_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_CC_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_CC_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_CC_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_CC_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_CC_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_CC_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_CC_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_CC_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_CC_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_CC_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_CC_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_CC_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_CC_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_CC_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_CC_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_CC_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_CC_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_CC_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_CC_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_CC_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_CC_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_CC_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_CC_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 8) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B1_064_064_08_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_CC_B1_001_064_08_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_CC_B1_064_001_08_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_CC_B1_001_001_08_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_CC_B1_064_064_08_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B1_064_064_08_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_CC_B1_001_064_08_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_CC_B1_064_001_08_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_CC_B1_001_001_08_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_CC_B1_064_064_08_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B1_064_064_08_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B1_001_064_08_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_CC_B1_064_001_08_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B1_001_001_08_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%64 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B1_064_064_01_16x16_4x4_src;
            *rowKernelSource    = cgemm_Col_CC_B1_001_064_01_16x16_4x4_src;
            *colKernelSource    = cgemm_Col_CC_B1_064_001_01_16x16_4x4_src;
            *cornerKernelSource = cgemm_Col_CC_B1_001_001_01_16x16_4x4_src;
            *sourceBuildOptions = cgemm_Col_CC_B1_064_064_01_16x16_4x4_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B1_064_064_01_16x16_4x4_bin;
            *rowKernelBinary    = cgemm_Col_CC_B1_001_064_01_16x16_4x4_bin;
            *colKernelBinary    = cgemm_Col_CC_B1_064_001_01_16x16_4x4_bin;
            *cornerKernelBinary = cgemm_Col_CC_B1_001_001_01_16x16_4x4_bin;
            *binaryBuildOptions = cgemm_Col_CC_B1_064_064_01_16x16_4x4_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B1_064_064_01_16x16_4x4_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B1_001_064_01_16x16_4x4_clKernel;
            *colClKernel        = &cgemm_Col_CC_B1_064_001_01_16x16_4x4_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B1_001_001_01_16x16_4x4_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_CC_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_CC_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_CC_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_CC_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_CC_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_CC_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_CC_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_CC_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_CC_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = cgemm_Col_CC_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = cgemm_Col_CC_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = cgemm_Col_CC_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = cgemm_Col_CC_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = cgemm_Col_CC_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = cgemm_Col_CC_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = cgemm_Col_CC_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = cgemm_Col_CC_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &cgemm_Col_CC_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_CC_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_CC_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_CC_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_CC_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_CC_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_CC_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_CC_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_CC_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_CC_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = cgemm_Col_CC_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = cgemm_Col_CC_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = cgemm_Col_CC_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = cgemm_Col_CC_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = cgemm_Col_CC_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = cgemm_Col_CC_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = cgemm_Col_CC_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = cgemm_Col_CC_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &cgemm_Col_CC_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_CC_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_CC_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_CC_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_CC_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_CC_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_CC_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_CC_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_CC_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_CC_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = cgemm_Col_CC_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = cgemm_Col_CC_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = cgemm_Col_CC_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = cgemm_Col_CC_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = cgemm_Col_CC_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = cgemm_Col_CC_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = cgemm_Col_CC_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = cgemm_Col_CC_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &cgemm_Col_CC_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_CC_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_CC_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_CC_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_CC_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_CC_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_CC_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_CC_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_CC_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_CC_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = cgemm_Col_CC_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = cgemm_Col_CC_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = cgemm_Col_CC_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = cgemm_Col_CC_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = cgemm_Col_CC_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = cgemm_Col_CC_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = cgemm_Col_CC_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = cgemm_Col_CC_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = cgemm_Col_CC_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = cgemm_Col_CC_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &cgemm_Col_CC_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &cgemm_Col_CC_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &cgemm_Col_CC_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &cgemm_Col_CC_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    }
  }
}

// zgemm kernel selection logic
template<>
void gemmSelectKernel<DoubleComplex>(
  clblasOrder order,
  clblasTranspose transA,
  clblasTranspose transB,
  size_t M,
  size_t N,
  size_t K,
  bool betaNonZero,
  float optimalNumElementsPerWorkItem,
  const char **tileKernelSource,
  const char **rowKernelSource,
  const char **colKernelSource,
  const char **cornerKernelSource,
  const char **sourceBuildOptions,
  const unsigned char **tileKernelBinary,
  const unsigned char **rowKernelBinary,
  const unsigned char **colKernelBinary,
  const unsigned char **cornerKernelBinary,
  const char **binaryBuildOptions,
  cl_kernel  **tileClKernel,
  cl_kernel  **rowClKernel,
  cl_kernel  **colClKernel,
  cl_kernel  **cornerClKernel,
  unsigned int *workGroupNumRows,
  unsigned int *workGroupNumCols,
  unsigned int *microTileNumRows,
  unsigned int *microTileNumCols,
  unsigned int *unroll
) {
  if (order == clblasColumnMajor) {
    if (transA == clblasNoTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NN_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_NN_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_NN_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_NN_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_NN_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NN_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_NN_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_NN_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_NN_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_NN_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NN_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_NN_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_NN_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NN_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NN_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_NN_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_NN_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_NN_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_NN_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NN_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_NN_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_NN_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_NN_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_NN_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NN_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_NN_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_NN_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NN_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NN_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_NN_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_NN_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_NN_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_NN_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NN_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_NN_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_NN_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_NN_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_NN_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NN_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_NN_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_NN_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NN_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NN_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_NN_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_NN_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_NN_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_NN_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NN_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_NN_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_NN_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_NN_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_NN_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NN_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_NN_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_NN_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NN_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NN_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_NN_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_NN_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_NN_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_NN_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NN_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_NN_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_NN_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_NN_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_NN_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NN_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_NN_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_NN_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NN_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NN_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_NN_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_NN_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_NN_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_NN_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NN_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_NN_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_NN_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_NN_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_NN_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NN_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_NN_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_NN_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NN_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NN_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_NN_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_NN_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_NN_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_NN_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NN_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_NN_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_NN_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_NN_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_NN_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NN_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_NN_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_NN_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NN_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NN_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_NN_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_NN_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_NN_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_NN_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NN_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_NN_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_NN_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_NN_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_NN_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NN_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_NN_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_NN_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NN_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NN_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_NN_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_NN_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_NN_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_NN_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NN_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_NN_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_NN_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_NN_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_NN_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NN_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_NN_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_NN_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NN_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NN_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_NN_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_NN_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_NN_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_NN_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NN_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_NN_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_NN_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_NN_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_NN_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NN_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_NN_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_NN_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NN_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NN_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_NN_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_NN_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_NN_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_NN_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NN_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_NN_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_NN_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_NN_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_NN_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NN_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_NN_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_NN_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NN_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NN_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_NN_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_NN_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_NN_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_NN_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NN_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_NN_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_NN_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_NN_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_NN_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NN_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_NN_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_NN_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NN_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NN_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_NN_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_NN_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_NN_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_NN_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NN_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_NN_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_NN_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_NN_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_NN_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NN_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_NN_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_NN_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NN_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NN_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_NN_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_NN_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_NN_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_NN_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NN_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_NN_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_NN_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_NN_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_NN_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NN_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_NN_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_NN_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NN_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NN_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_NN_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_NN_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_NN_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_NN_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NN_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_NN_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_NN_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_NN_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_NN_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NN_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_NN_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_NN_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NN_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NN_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_NN_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_NN_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_NN_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_NN_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NN_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_NN_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_NN_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_NN_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_NN_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NN_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_NN_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_NN_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NN_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasNoTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NT_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_NT_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_NT_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_NT_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_NT_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NT_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_NT_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_NT_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_NT_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_NT_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NT_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_NT_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_NT_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NT_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NT_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_NT_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_NT_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_NT_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_NT_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NT_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_NT_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_NT_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_NT_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_NT_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NT_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_NT_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_NT_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NT_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NT_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_NT_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_NT_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_NT_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_NT_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NT_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_NT_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_NT_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_NT_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_NT_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NT_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_NT_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_NT_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NT_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NT_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_NT_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_NT_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_NT_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_NT_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NT_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_NT_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_NT_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_NT_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_NT_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NT_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_NT_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_NT_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NT_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NT_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_NT_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_NT_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_NT_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_NT_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NT_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_NT_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_NT_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_NT_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_NT_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NT_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_NT_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_NT_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NT_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NT_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_NT_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_NT_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_NT_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_NT_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NT_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_NT_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_NT_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_NT_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_NT_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NT_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_NT_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_NT_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NT_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NT_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_NT_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_NT_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_NT_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_NT_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NT_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_NT_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_NT_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_NT_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_NT_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NT_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_NT_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_NT_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NT_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NT_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_NT_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_NT_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_NT_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_NT_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NT_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_NT_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_NT_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_NT_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_NT_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NT_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_NT_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_NT_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NT_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NT_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_NT_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_NT_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_NT_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_NT_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NT_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_NT_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_NT_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_NT_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_NT_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NT_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_NT_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_NT_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NT_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NT_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_NT_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_NT_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_NT_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_NT_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NT_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_NT_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_NT_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_NT_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_NT_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NT_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_NT_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_NT_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NT_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NT_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_NT_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_NT_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_NT_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_NT_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NT_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_NT_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_NT_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_NT_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_NT_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NT_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_NT_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_NT_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NT_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NT_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_NT_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_NT_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_NT_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_NT_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NT_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_NT_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_NT_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_NT_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_NT_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NT_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_NT_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_NT_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NT_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NT_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_NT_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_NT_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_NT_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_NT_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NT_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_NT_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_NT_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_NT_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_NT_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NT_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_NT_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_NT_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NT_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NT_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_NT_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_NT_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_NT_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_NT_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NT_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_NT_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_NT_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_NT_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_NT_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NT_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_NT_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_NT_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NT_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NT_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_NT_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_NT_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_NT_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_NT_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NT_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_NT_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_NT_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_NT_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_NT_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NT_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_NT_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_NT_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NT_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NT_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_NT_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_NT_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_NT_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_NT_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NT_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_NT_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_NT_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_NT_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_NT_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NT_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_NT_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_NT_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NT_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasNoTrans && transB == clblasConjTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NC_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_NC_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_NC_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_NC_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_NC_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NC_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_NC_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_NC_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_NC_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_NC_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NC_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_NC_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_NC_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NC_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NC_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_NC_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_NC_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_NC_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_NC_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NC_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_NC_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_NC_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_NC_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_NC_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NC_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_NC_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_NC_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NC_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NC_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_NC_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_NC_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_NC_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_NC_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NC_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_NC_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_NC_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_NC_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_NC_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NC_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_NC_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_NC_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NC_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NC_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_NC_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_NC_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_NC_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_NC_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NC_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_NC_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_NC_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_NC_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_NC_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NC_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_NC_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_NC_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NC_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NC_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_NC_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_NC_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_NC_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_NC_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NC_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_NC_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_NC_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_NC_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_NC_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NC_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_NC_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_NC_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NC_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NC_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_NC_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_NC_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_NC_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_NC_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NC_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_NC_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_NC_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_NC_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_NC_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NC_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_NC_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_NC_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NC_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NC_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_NC_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_NC_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_NC_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_NC_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NC_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_NC_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_NC_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_NC_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_NC_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NC_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_NC_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_NC_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NC_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NC_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_NC_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_NC_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_NC_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_NC_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NC_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_NC_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_NC_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_NC_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_NC_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NC_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_NC_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_NC_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NC_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NC_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_NC_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_NC_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_NC_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_NC_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NC_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_NC_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_NC_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_NC_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_NC_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NC_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_NC_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_NC_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NC_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NC_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_NC_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_NC_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_NC_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_NC_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NC_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_NC_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_NC_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_NC_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_NC_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NC_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_NC_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_NC_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NC_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NC_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_NC_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_NC_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_NC_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_NC_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NC_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_NC_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_NC_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_NC_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_NC_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NC_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_NC_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_NC_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NC_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NC_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_NC_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_NC_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_NC_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_NC_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NC_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_NC_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_NC_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_NC_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_NC_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NC_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_NC_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_NC_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_NC_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NC_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_NC_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_NC_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_NC_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_NC_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NC_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_NC_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_NC_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_NC_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_NC_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NC_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_NC_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_NC_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NC_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NC_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_NC_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_NC_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_NC_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_NC_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NC_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_NC_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_NC_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_NC_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_NC_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NC_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_NC_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_NC_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NC_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_NC_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_NC_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_NC_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_NC_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_NC_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NC_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_NC_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_NC_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_NC_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_NC_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NC_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_NC_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_NC_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NC_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_NC_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_NC_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_NC_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_NC_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_NC_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_NC_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_NC_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_NC_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_NC_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_NC_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_NC_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_NC_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_NC_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_NC_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TN_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_TN_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_TN_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_TN_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_TN_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TN_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_TN_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_TN_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_TN_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_TN_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TN_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_TN_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_TN_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TN_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TN_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_TN_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_TN_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_TN_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_TN_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TN_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_TN_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_TN_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_TN_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_TN_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TN_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_TN_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_TN_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TN_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TN_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_TN_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_TN_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_TN_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_TN_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TN_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_TN_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_TN_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_TN_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_TN_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TN_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_TN_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_TN_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TN_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TN_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_TN_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_TN_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_TN_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_TN_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TN_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_TN_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_TN_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_TN_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_TN_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TN_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_TN_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_TN_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TN_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TN_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_TN_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_TN_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_TN_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_TN_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TN_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_TN_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_TN_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_TN_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_TN_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TN_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_TN_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_TN_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TN_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TN_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_TN_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_TN_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_TN_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_TN_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TN_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_TN_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_TN_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_TN_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_TN_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TN_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_TN_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_TN_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TN_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TN_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_TN_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_TN_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_TN_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_TN_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TN_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_TN_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_TN_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_TN_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_TN_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TN_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_TN_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_TN_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TN_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TN_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_TN_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_TN_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_TN_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_TN_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TN_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_TN_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_TN_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_TN_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_TN_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TN_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_TN_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_TN_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TN_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TN_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_TN_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_TN_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_TN_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_TN_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TN_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_TN_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_TN_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_TN_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_TN_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TN_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_TN_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_TN_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TN_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TN_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_TN_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_TN_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_TN_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_TN_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TN_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_TN_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_TN_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_TN_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_TN_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TN_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_TN_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_TN_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TN_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TN_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_TN_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_TN_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_TN_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_TN_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TN_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_TN_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_TN_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_TN_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_TN_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TN_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_TN_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_TN_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TN_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TN_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_TN_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_TN_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_TN_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_TN_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TN_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_TN_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_TN_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_TN_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_TN_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TN_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_TN_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_TN_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TN_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TN_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_TN_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_TN_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_TN_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_TN_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TN_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_TN_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_TN_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_TN_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_TN_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TN_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_TN_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_TN_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TN_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TN_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_TN_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_TN_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_TN_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_TN_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TN_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_TN_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_TN_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_TN_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_TN_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TN_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_TN_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_TN_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TN_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TN_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_TN_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_TN_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_TN_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_TN_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TN_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_TN_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_TN_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_TN_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_TN_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TN_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_TN_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_TN_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TN_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TN_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_TN_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_TN_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_TN_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_TN_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TN_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_TN_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_TN_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_TN_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_TN_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TN_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_TN_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_TN_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TN_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TT_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_TT_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_TT_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_TT_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_TT_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TT_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_TT_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_TT_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_TT_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_TT_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TT_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_TT_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_TT_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TT_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TT_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_TT_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_TT_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_TT_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_TT_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TT_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_TT_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_TT_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_TT_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_TT_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TT_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_TT_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_TT_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TT_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TT_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_TT_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_TT_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_TT_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_TT_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TT_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_TT_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_TT_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_TT_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_TT_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TT_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_TT_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_TT_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TT_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TT_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_TT_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_TT_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_TT_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_TT_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TT_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_TT_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_TT_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_TT_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_TT_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TT_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_TT_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_TT_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TT_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TT_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_TT_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_TT_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_TT_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_TT_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TT_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_TT_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_TT_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_TT_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_TT_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TT_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_TT_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_TT_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TT_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TT_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_TT_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_TT_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_TT_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_TT_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TT_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_TT_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_TT_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_TT_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_TT_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TT_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_TT_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_TT_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TT_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TT_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_TT_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_TT_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_TT_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_TT_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TT_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_TT_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_TT_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_TT_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_TT_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TT_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_TT_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_TT_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TT_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TT_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_TT_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_TT_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_TT_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_TT_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TT_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_TT_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_TT_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_TT_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_TT_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TT_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_TT_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_TT_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TT_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TT_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_TT_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_TT_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_TT_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_TT_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TT_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_TT_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_TT_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_TT_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_TT_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TT_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_TT_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_TT_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TT_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TT_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_TT_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_TT_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_TT_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_TT_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TT_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_TT_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_TT_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_TT_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_TT_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TT_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_TT_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_TT_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TT_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TT_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_TT_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_TT_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_TT_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_TT_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TT_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_TT_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_TT_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_TT_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_TT_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TT_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_TT_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_TT_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TT_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TT_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_TT_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_TT_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_TT_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_TT_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TT_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_TT_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_TT_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_TT_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_TT_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TT_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_TT_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_TT_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TT_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TT_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_TT_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_TT_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_TT_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_TT_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TT_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_TT_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_TT_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_TT_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_TT_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TT_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_TT_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_TT_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TT_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TT_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_TT_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_TT_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_TT_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_TT_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TT_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_TT_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_TT_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_TT_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_TT_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TT_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_TT_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_TT_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TT_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TT_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_TT_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_TT_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_TT_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_TT_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TT_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_TT_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_TT_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_TT_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_TT_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TT_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_TT_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_TT_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TT_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TT_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_TT_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_TT_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_TT_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_TT_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TT_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_TT_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_TT_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_TT_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_TT_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TT_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_TT_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_TT_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TT_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasTrans && transB == clblasConjTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TC_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_TC_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_TC_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_TC_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_TC_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TC_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_TC_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_TC_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_TC_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_TC_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TC_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_TC_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_TC_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TC_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TC_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_TC_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_TC_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_TC_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_TC_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TC_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_TC_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_TC_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_TC_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_TC_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TC_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_TC_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_TC_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TC_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TC_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_TC_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_TC_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_TC_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_TC_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TC_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_TC_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_TC_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_TC_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_TC_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TC_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_TC_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_TC_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TC_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TC_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_TC_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_TC_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_TC_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_TC_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TC_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_TC_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_TC_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_TC_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_TC_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TC_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_TC_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_TC_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TC_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TC_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_TC_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_TC_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_TC_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_TC_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TC_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_TC_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_TC_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_TC_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_TC_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TC_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_TC_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_TC_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TC_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TC_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_TC_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_TC_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_TC_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_TC_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TC_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_TC_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_TC_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_TC_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_TC_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TC_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_TC_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_TC_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TC_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TC_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_TC_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_TC_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_TC_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_TC_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TC_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_TC_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_TC_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_TC_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_TC_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TC_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_TC_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_TC_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TC_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TC_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_TC_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_TC_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_TC_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_TC_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TC_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_TC_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_TC_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_TC_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_TC_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TC_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_TC_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_TC_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TC_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TC_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_TC_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_TC_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_TC_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_TC_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TC_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_TC_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_TC_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_TC_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_TC_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TC_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_TC_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_TC_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TC_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TC_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_TC_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_TC_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_TC_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_TC_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TC_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_TC_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_TC_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_TC_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_TC_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TC_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_TC_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_TC_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TC_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TC_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_TC_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_TC_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_TC_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_TC_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TC_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_TC_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_TC_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_TC_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_TC_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TC_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_TC_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_TC_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TC_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TC_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_TC_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_TC_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_TC_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_TC_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TC_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_TC_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_TC_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_TC_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_TC_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TC_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_TC_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_TC_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_TC_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TC_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_TC_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_TC_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_TC_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_TC_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TC_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_TC_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_TC_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_TC_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_TC_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TC_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_TC_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_TC_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TC_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TC_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_TC_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_TC_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_TC_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_TC_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TC_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_TC_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_TC_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_TC_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_TC_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TC_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_TC_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_TC_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TC_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_TC_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_TC_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_TC_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_TC_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_TC_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TC_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_TC_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_TC_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_TC_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_TC_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TC_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_TC_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_TC_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TC_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_TC_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_TC_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_TC_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_TC_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_TC_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_TC_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_TC_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_TC_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_TC_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_TC_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_TC_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_TC_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_TC_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_TC_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasConjTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CN_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_CN_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_CN_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_CN_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_CN_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CN_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_CN_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_CN_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_CN_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_CN_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CN_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_CN_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_CN_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CN_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CN_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_CN_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_CN_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_CN_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_CN_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CN_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_CN_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_CN_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_CN_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_CN_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CN_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_CN_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_CN_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CN_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CN_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_CN_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_CN_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_CN_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_CN_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CN_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_CN_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_CN_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_CN_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_CN_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CN_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_CN_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_CN_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CN_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CN_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_CN_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_CN_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_CN_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_CN_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CN_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_CN_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_CN_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_CN_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_CN_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CN_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_CN_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_CN_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CN_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CN_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_CN_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_CN_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_CN_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_CN_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CN_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_CN_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_CN_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_CN_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_CN_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CN_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_CN_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_CN_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CN_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CN_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_CN_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_CN_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_CN_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_CN_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CN_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_CN_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_CN_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_CN_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_CN_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CN_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_CN_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_CN_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CN_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CN_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_CN_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_CN_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_CN_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_CN_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CN_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_CN_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_CN_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_CN_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_CN_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CN_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_CN_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_CN_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CN_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CN_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_CN_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_CN_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_CN_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_CN_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CN_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_CN_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_CN_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_CN_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_CN_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CN_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_CN_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_CN_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CN_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CN_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_CN_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_CN_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_CN_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_CN_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CN_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_CN_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_CN_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_CN_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_CN_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CN_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_CN_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_CN_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CN_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CN_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_CN_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_CN_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_CN_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_CN_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CN_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_CN_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_CN_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_CN_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_CN_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CN_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_CN_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_CN_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CN_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CN_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_CN_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_CN_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_CN_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_CN_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CN_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_CN_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_CN_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_CN_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_CN_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CN_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_CN_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_CN_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CN_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CN_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_CN_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_CN_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_CN_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_CN_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CN_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_CN_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_CN_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_CN_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_CN_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CN_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_CN_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_CN_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CN_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CN_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_CN_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_CN_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_CN_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_CN_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CN_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_CN_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_CN_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_CN_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_CN_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CN_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_CN_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_CN_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CN_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CN_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_CN_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_CN_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_CN_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_CN_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CN_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_CN_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_CN_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_CN_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_CN_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CN_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_CN_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_CN_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CN_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CN_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_CN_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_CN_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_CN_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_CN_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CN_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_CN_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_CN_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_CN_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_CN_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CN_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_CN_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_CN_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CN_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CN_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_CN_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_CN_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_CN_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_CN_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CN_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_CN_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_CN_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_CN_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_CN_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CN_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_CN_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_CN_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CN_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasConjTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CT_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_CT_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_CT_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_CT_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_CT_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CT_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_CT_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_CT_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_CT_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_CT_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CT_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_CT_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_CT_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CT_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CT_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_CT_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_CT_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_CT_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_CT_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CT_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_CT_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_CT_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_CT_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_CT_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CT_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_CT_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_CT_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CT_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CT_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_CT_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_CT_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_CT_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_CT_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CT_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_CT_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_CT_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_CT_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_CT_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CT_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_CT_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_CT_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CT_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CT_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_CT_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_CT_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_CT_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_CT_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CT_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_CT_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_CT_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_CT_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_CT_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CT_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_CT_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_CT_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CT_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CT_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_CT_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_CT_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_CT_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_CT_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CT_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_CT_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_CT_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_CT_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_CT_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CT_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_CT_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_CT_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CT_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CT_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_CT_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_CT_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_CT_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_CT_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CT_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_CT_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_CT_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_CT_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_CT_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CT_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_CT_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_CT_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CT_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CT_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_CT_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_CT_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_CT_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_CT_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CT_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_CT_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_CT_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_CT_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_CT_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CT_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_CT_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_CT_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CT_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CT_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_CT_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_CT_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_CT_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_CT_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CT_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_CT_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_CT_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_CT_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_CT_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CT_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_CT_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_CT_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CT_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CT_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_CT_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_CT_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_CT_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_CT_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CT_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_CT_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_CT_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_CT_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_CT_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CT_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_CT_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_CT_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CT_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CT_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_CT_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_CT_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_CT_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_CT_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CT_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_CT_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_CT_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_CT_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_CT_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CT_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_CT_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_CT_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CT_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CT_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_CT_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_CT_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_CT_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_CT_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CT_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_CT_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_CT_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_CT_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_CT_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CT_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_CT_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_CT_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CT_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CT_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_CT_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_CT_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_CT_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_CT_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CT_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_CT_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_CT_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_CT_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_CT_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CT_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_CT_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_CT_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CT_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CT_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_CT_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_CT_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_CT_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_CT_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CT_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_CT_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_CT_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_CT_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_CT_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CT_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_CT_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_CT_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CT_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CT_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_CT_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_CT_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_CT_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_CT_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CT_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_CT_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_CT_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_CT_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_CT_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CT_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_CT_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_CT_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CT_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CT_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_CT_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_CT_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_CT_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_CT_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CT_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_CT_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_CT_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_CT_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_CT_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CT_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_CT_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_CT_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CT_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CT_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_CT_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_CT_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_CT_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_CT_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CT_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_CT_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_CT_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_CT_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_CT_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CT_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_CT_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_CT_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CT_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    } else if (transA == clblasConjTrans && transB == clblasConjTrans) {
      if ( !betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CC_B0_064_032_08_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_CC_B0_001_032_08_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_CC_B0_064_001_08_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_CC_B0_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_CC_B0_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CC_B0_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_CC_B0_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_CC_B0_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_CC_B0_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_CC_B0_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CC_B0_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_CC_B0_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_CC_B0_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CC_B0_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CC_B0_064_032_01_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_CC_B0_001_032_01_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_CC_B0_064_001_01_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_CC_B0_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_CC_B0_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CC_B0_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_CC_B0_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_CC_B0_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_CC_B0_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_CC_B0_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CC_B0_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_CC_B0_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_CC_B0_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CC_B0_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CC_B0_032_032_08_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_CC_B0_001_032_08_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_CC_B0_032_001_08_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_CC_B0_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_CC_B0_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CC_B0_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_CC_B0_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_CC_B0_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_CC_B0_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_CC_B0_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CC_B0_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_CC_B0_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_CC_B0_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CC_B0_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CC_B0_032_032_01_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_CC_B0_001_032_01_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_CC_B0_032_001_01_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_CC_B0_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_CC_B0_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CC_B0_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_CC_B0_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_CC_B0_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_CC_B0_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_CC_B0_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CC_B0_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_CC_B0_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_CC_B0_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CC_B0_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CC_B0_032_016_08_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_CC_B0_001_016_08_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_CC_B0_032_001_08_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_CC_B0_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_CC_B0_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CC_B0_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_CC_B0_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_CC_B0_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_CC_B0_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_CC_B0_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CC_B0_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_CC_B0_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_CC_B0_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CC_B0_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CC_B0_032_016_01_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_CC_B0_001_016_01_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_CC_B0_032_001_01_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_CC_B0_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_CC_B0_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CC_B0_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_CC_B0_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_CC_B0_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_CC_B0_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_CC_B0_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CC_B0_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_CC_B0_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_CC_B0_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CC_B0_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CC_B0_016_016_08_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_CC_B0_001_016_08_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_CC_B0_016_001_08_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_CC_B0_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_CC_B0_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CC_B0_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_CC_B0_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_CC_B0_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_CC_B0_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_CC_B0_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CC_B0_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_CC_B0_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_CC_B0_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CC_B0_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CC_B0_016_016_01_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_CC_B0_001_016_01_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_CC_B0_016_001_01_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_CC_B0_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_CC_B0_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CC_B0_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_CC_B0_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_CC_B0_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_CC_B0_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_CC_B0_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CC_B0_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_CC_B0_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_CC_B0_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CC_B0_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      } else if ( betaNonZero ) {
        if (optimalNumElementsPerWorkItem > 4) {
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CC_B1_064_032_08_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_CC_B1_001_032_08_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_CC_B1_064_001_08_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_CC_B1_001_001_08_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_CC_B1_064_032_08_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CC_B1_064_032_08_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_CC_B1_001_032_08_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_CC_B1_064_001_08_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_CC_B1_001_001_08_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_CC_B1_064_032_08_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CC_B1_064_032_08_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_CC_B1_001_032_08_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_CC_B1_064_001_08_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CC_B1_001_001_08_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%64 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CC_B1_064_032_01_16x16_4x2_src;
            *rowKernelSource    = zgemm_Col_CC_B1_001_032_01_16x16_4x2_src;
            *colKernelSource    = zgemm_Col_CC_B1_064_001_01_16x16_4x2_src;
            *cornerKernelSource = zgemm_Col_CC_B1_001_001_01_16x16_4x2_src;
            *sourceBuildOptions = zgemm_Col_CC_B1_064_032_01_16x16_4x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CC_B1_064_032_01_16x16_4x2_bin;
            *rowKernelBinary    = zgemm_Col_CC_B1_001_032_01_16x16_4x2_bin;
            *colKernelBinary    = zgemm_Col_CC_B1_064_001_01_16x16_4x2_bin;
            *cornerKernelBinary = zgemm_Col_CC_B1_001_001_01_16x16_4x2_bin;
            *binaryBuildOptions = zgemm_Col_CC_B1_064_032_01_16x16_4x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CC_B1_064_032_01_16x16_4x2_clKernel;
            *rowClKernel        = &zgemm_Col_CC_B1_001_032_01_16x16_4x2_clKernel;
            *colClKernel        = &zgemm_Col_CC_B1_064_001_01_16x16_4x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CC_B1_001_001_01_16x16_4x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CC_B1_032_032_08_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_CC_B1_001_032_08_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_CC_B1_032_001_08_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_CC_B1_001_001_08_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_CC_B1_032_032_08_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CC_B1_032_032_08_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_CC_B1_001_032_08_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_CC_B1_032_001_08_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_CC_B1_001_001_08_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_CC_B1_032_032_08_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CC_B1_032_032_08_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_CC_B1_001_032_08_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_CC_B1_032_001_08_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CC_B1_001_001_08_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%32 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CC_B1_032_032_01_16x16_2x2_src;
            *rowKernelSource    = zgemm_Col_CC_B1_001_032_01_16x16_2x2_src;
            *colKernelSource    = zgemm_Col_CC_B1_032_001_01_16x16_2x2_src;
            *cornerKernelSource = zgemm_Col_CC_B1_001_001_01_16x16_2x2_src;
            *sourceBuildOptions = zgemm_Col_CC_B1_032_032_01_16x16_2x2_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CC_B1_032_032_01_16x16_2x2_bin;
            *rowKernelBinary    = zgemm_Col_CC_B1_001_032_01_16x16_2x2_bin;
            *colKernelBinary    = zgemm_Col_CC_B1_032_001_01_16x16_2x2_bin;
            *cornerKernelBinary = zgemm_Col_CC_B1_001_001_01_16x16_2x2_bin;
            *binaryBuildOptions = zgemm_Col_CC_B1_032_032_01_16x16_2x2_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CC_B1_032_032_01_16x16_2x2_clKernel;
            *rowClKernel        = &zgemm_Col_CC_B1_001_032_01_16x16_2x2_clKernel;
            *colClKernel        = &zgemm_Col_CC_B1_032_001_01_16x16_2x2_clKernel;
            *cornerClKernel     = &zgemm_Col_CC_B1_001_001_01_16x16_2x2_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CC_B1_032_016_08_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_CC_B1_001_016_08_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_CC_B1_032_001_08_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_CC_B1_001_001_08_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_CC_B1_032_016_08_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CC_B1_032_016_08_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_CC_B1_001_016_08_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_CC_B1_032_001_08_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_CC_B1_001_001_08_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_CC_B1_032_016_08_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CC_B1_032_016_08_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_CC_B1_001_016_08_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_CC_B1_032_001_08_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CC_B1_001_001_08_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%32 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CC_B1_032_016_01_16x16_2x1_src;
            *rowKernelSource    = zgemm_Col_CC_B1_001_016_01_16x16_2x1_src;
            *colKernelSource    = zgemm_Col_CC_B1_032_001_01_16x16_2x1_src;
            *cornerKernelSource = zgemm_Col_CC_B1_001_001_01_16x16_2x1_src;
            *sourceBuildOptions = zgemm_Col_CC_B1_032_016_01_16x16_2x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CC_B1_032_016_01_16x16_2x1_bin;
            *rowKernelBinary    = zgemm_Col_CC_B1_001_016_01_16x16_2x1_bin;
            *colKernelBinary    = zgemm_Col_CC_B1_032_001_01_16x16_2x1_bin;
            *cornerKernelBinary = zgemm_Col_CC_B1_001_001_01_16x16_2x1_bin;
            *binaryBuildOptions = zgemm_Col_CC_B1_032_016_01_16x16_2x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CC_B1_032_016_01_16x16_2x1_clKernel;
            *rowClKernel        = &zgemm_Col_CC_B1_001_016_01_16x16_2x1_clKernel;
            *colClKernel        = &zgemm_Col_CC_B1_032_001_01_16x16_2x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CC_B1_001_001_01_16x16_2x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%8 == 0) {
            *tileKernelSource   = zgemm_Col_CC_B1_016_016_08_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_CC_B1_001_016_08_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_CC_B1_016_001_08_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_CC_B1_001_001_08_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_CC_B1_016_016_08_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CC_B1_016_016_08_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_CC_B1_001_016_08_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_CC_B1_016_001_08_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_CC_B1_001_001_08_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_CC_B1_016_016_08_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CC_B1_016_016_08_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_CC_B1_001_016_08_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_CC_B1_016_001_08_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CC_B1_001_001_08_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( EXACT_MULTIPLES(M%16 == 0 && N%16 == 0 &&) K%1 == 0) {
            *tileKernelSource   = zgemm_Col_CC_B1_016_016_01_16x16_1x1_src;
            *rowKernelSource    = zgemm_Col_CC_B1_001_016_01_16x16_1x1_src;
            *colKernelSource    = zgemm_Col_CC_B1_016_001_01_16x16_1x1_src;
            *cornerKernelSource = zgemm_Col_CC_B1_001_001_01_16x16_1x1_src;
            *sourceBuildOptions = zgemm_Col_CC_B1_016_016_01_16x16_1x1_srcBuildOptions;
            *tileKernelBinary   = zgemm_Col_CC_B1_016_016_01_16x16_1x1_bin;
            *rowKernelBinary    = zgemm_Col_CC_B1_001_016_01_16x16_1x1_bin;
            *colKernelBinary    = zgemm_Col_CC_B1_016_001_01_16x16_1x1_bin;
            *cornerKernelBinary = zgemm_Col_CC_B1_001_001_01_16x16_1x1_bin;
            *binaryBuildOptions = zgemm_Col_CC_B1_016_016_01_16x16_1x1_binBuildOptions;
            *tileClKernel       = &zgemm_Col_CC_B1_016_016_01_16x16_1x1_clKernel;
            *rowClKernel        = &zgemm_Col_CC_B1_001_016_01_16x16_1x1_clKernel;
            *colClKernel        = &zgemm_Col_CC_B1_016_001_01_16x16_1x1_clKernel;
            *cornerClKernel     = &zgemm_Col_CC_B1_001_001_01_16x16_1x1_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
      }
    }
  }
}

