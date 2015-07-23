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
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NN_096_096_8_16x16_6x6_ColMajor_src;
            *rowKernelSource    = sgemm_NN_001_096_8_16x16_6x6_ColMajor_src;
            *colKernelSource    = sgemm_NN_096_001_8_16x16_6x6_ColMajor_src;
            *cornerKernelSource = sgemm_NN_001_001_8_16x16_6x6_ColMajor_src;
            *sourceBuildOptions = sgemm_NN_096_096_8_16x16_6x6_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_096_096_8_16x16_6x6_ColMajor_bin;
            *rowKernelBinary    = sgemm_NN_001_096_8_16x16_6x6_ColMajor_bin;
            *colKernelBinary    = sgemm_NN_096_001_8_16x16_6x6_ColMajor_bin;
            *cornerKernelBinary = sgemm_NN_001_001_8_16x16_6x6_ColMajor_bin;
            *binaryBuildOptions = sgemm_NN_096_096_8_16x16_6x6_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NN_096_096_8_16x16_6x6_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NN_001_096_8_16x16_6x6_ColMajor_clKernel;
            *colClKernel        = &sgemm_NN_096_001_8_16x16_6x6_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_8_16x16_6x6_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NN_096_096_1_16x16_6x6_ColMajor_src;
            *rowKernelSource    = sgemm_NN_001_096_1_16x16_6x6_ColMajor_src;
            *colKernelSource    = sgemm_NN_096_001_1_16x16_6x6_ColMajor_src;
            *cornerKernelSource = sgemm_NN_001_001_1_16x16_6x6_ColMajor_src;
            *sourceBuildOptions = sgemm_NN_096_096_1_16x16_6x6_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_096_096_1_16x16_6x6_ColMajor_bin;
            *rowKernelBinary    = sgemm_NN_001_096_1_16x16_6x6_ColMajor_bin;
            *colKernelBinary    = sgemm_NN_096_001_1_16x16_6x6_ColMajor_bin;
            *cornerKernelBinary = sgemm_NN_001_001_1_16x16_6x6_ColMajor_bin;
            *binaryBuildOptions = sgemm_NN_096_096_1_16x16_6x6_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NN_096_096_1_16x16_6x6_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NN_001_096_1_16x16_6x6_ColMajor_clKernel;
            *colClKernel        = &sgemm_NN_096_001_1_16x16_6x6_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_1_16x16_6x6_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NN_128_064_8_16x16_8x4_ColMajor_src;
            *rowKernelSource    = sgemm_NN_001_064_8_16x16_8x4_ColMajor_src;
            *colKernelSource    = sgemm_NN_128_001_8_16x16_8x4_ColMajor_src;
            *cornerKernelSource = sgemm_NN_001_001_8_16x16_8x4_ColMajor_src;
            *sourceBuildOptions = sgemm_NN_128_064_8_16x16_8x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_128_064_8_16x16_8x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_NN_001_064_8_16x16_8x4_ColMajor_bin;
            *colKernelBinary    = sgemm_NN_128_001_8_16x16_8x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_NN_001_001_8_16x16_8x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_NN_128_064_8_16x16_8x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NN_128_064_8_16x16_8x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NN_001_064_8_16x16_8x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_NN_128_001_8_16x16_8x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_8_16x16_8x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NN_128_064_1_16x16_8x4_ColMajor_src;
            *rowKernelSource    = sgemm_NN_001_064_1_16x16_8x4_ColMajor_src;
            *colKernelSource    = sgemm_NN_128_001_1_16x16_8x4_ColMajor_src;
            *cornerKernelSource = sgemm_NN_001_001_1_16x16_8x4_ColMajor_src;
            *sourceBuildOptions = sgemm_NN_128_064_1_16x16_8x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_128_064_1_16x16_8x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_NN_001_064_1_16x16_8x4_ColMajor_bin;
            *colKernelBinary    = sgemm_NN_128_001_1_16x16_8x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_NN_001_001_1_16x16_8x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_NN_128_064_1_16x16_8x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NN_128_064_1_16x16_8x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NN_001_064_1_16x16_8x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_NN_128_001_1_16x16_8x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_1_16x16_8x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NN_096_064_8_16x16_6x4_ColMajor_src;
            *rowKernelSource    = sgemm_NN_001_064_8_16x16_6x4_ColMajor_src;
            *colKernelSource    = sgemm_NN_096_001_8_16x16_6x4_ColMajor_src;
            *cornerKernelSource = sgemm_NN_001_001_8_16x16_6x4_ColMajor_src;
            *sourceBuildOptions = sgemm_NN_096_064_8_16x16_6x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_096_064_8_16x16_6x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_NN_001_064_8_16x16_6x4_ColMajor_bin;
            *colKernelBinary    = sgemm_NN_096_001_8_16x16_6x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_NN_001_001_8_16x16_6x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_NN_096_064_8_16x16_6x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NN_096_064_8_16x16_6x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NN_001_064_8_16x16_6x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_NN_096_001_8_16x16_6x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_8_16x16_6x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NN_096_064_1_16x16_6x4_ColMajor_src;
            *rowKernelSource    = sgemm_NN_001_064_1_16x16_6x4_ColMajor_src;
            *colKernelSource    = sgemm_NN_096_001_1_16x16_6x4_ColMajor_src;
            *cornerKernelSource = sgemm_NN_001_001_1_16x16_6x4_ColMajor_src;
            *sourceBuildOptions = sgemm_NN_096_064_1_16x16_6x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_096_064_1_16x16_6x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_NN_001_064_1_16x16_6x4_ColMajor_bin;
            *colKernelBinary    = sgemm_NN_096_001_1_16x16_6x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_NN_001_001_1_16x16_6x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_NN_096_064_1_16x16_6x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NN_096_064_1_16x16_6x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NN_001_064_1_16x16_6x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_NN_096_001_1_16x16_6x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_1_16x16_6x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NN_064_064_8_16x16_4x4_ColMajor_src;
            *rowKernelSource    = sgemm_NN_001_064_8_16x16_4x4_ColMajor_src;
            *colKernelSource    = sgemm_NN_064_001_8_16x16_4x4_ColMajor_src;
            *cornerKernelSource = sgemm_NN_001_001_8_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = sgemm_NN_064_064_8_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_064_064_8_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_NN_001_064_8_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = sgemm_NN_064_001_8_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_NN_001_001_8_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_NN_064_064_8_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NN_064_064_8_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NN_001_064_8_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_NN_064_001_8_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_8_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NN_064_064_1_16x16_4x4_ColMajor_src;
            *rowKernelSource    = sgemm_NN_001_064_1_16x16_4x4_ColMajor_src;
            *colKernelSource    = sgemm_NN_064_001_1_16x16_4x4_ColMajor_src;
            *cornerKernelSource = sgemm_NN_001_001_1_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = sgemm_NN_064_064_1_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_064_064_1_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_NN_001_064_1_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = sgemm_NN_064_001_1_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_NN_001_001_1_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_NN_064_064_1_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NN_064_064_1_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NN_001_064_1_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_NN_064_001_1_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_1_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NN_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = sgemm_NN_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = sgemm_NN_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = sgemm_NN_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = sgemm_NN_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = sgemm_NN_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = sgemm_NN_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = sgemm_NN_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = sgemm_NN_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NN_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NN_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &sgemm_NN_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NN_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = sgemm_NN_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = sgemm_NN_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = sgemm_NN_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = sgemm_NN_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = sgemm_NN_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = sgemm_NN_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = sgemm_NN_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = sgemm_NN_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NN_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NN_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &sgemm_NN_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NN_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = sgemm_NN_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = sgemm_NN_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = sgemm_NN_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = sgemm_NN_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = sgemm_NN_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = sgemm_NN_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = sgemm_NN_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = sgemm_NN_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NN_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NN_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &sgemm_NN_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NN_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = sgemm_NN_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = sgemm_NN_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = sgemm_NN_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = sgemm_NN_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = sgemm_NN_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = sgemm_NN_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = sgemm_NN_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = sgemm_NN_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NN_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NN_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &sgemm_NN_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NN_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = sgemm_NN_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = sgemm_NN_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = sgemm_NN_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = sgemm_NN_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = sgemm_NN_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = sgemm_NN_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = sgemm_NN_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = sgemm_NN_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NN_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NN_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &sgemm_NN_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NN_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = sgemm_NN_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = sgemm_NN_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = sgemm_NN_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = sgemm_NN_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = sgemm_NN_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = sgemm_NN_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = sgemm_NN_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = sgemm_NN_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NN_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NN_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &sgemm_NN_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NN_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = sgemm_NN_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = sgemm_NN_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = sgemm_NN_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = sgemm_NN_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = sgemm_NN_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = sgemm_NN_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = sgemm_NN_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = sgemm_NN_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NN_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NN_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &sgemm_NN_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NN_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = sgemm_NN_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = sgemm_NN_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = sgemm_NN_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = sgemm_NN_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = sgemm_NN_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = sgemm_NN_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = sgemm_NN_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = sgemm_NN_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NN_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NN_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &sgemm_NN_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NN_096_096_8_16x16_6x6_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NN_001_096_8_16x16_6x6_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NN_096_001_8_16x16_6x6_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NN_001_001_8_16x16_6x6_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NN_096_096_8_16x16_6x6_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_096_096_8_16x16_6x6_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NN_001_096_8_16x16_6x6_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NN_096_001_8_16x16_6x6_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NN_001_001_8_16x16_6x6_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NN_096_096_8_16x16_6x6_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NN_096_096_8_16x16_6x6_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NN_001_096_8_16x16_6x6_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NN_096_001_8_16x16_6x6_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_8_16x16_6x6_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NN_096_096_1_16x16_6x6_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NN_001_096_1_16x16_6x6_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NN_096_001_1_16x16_6x6_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NN_001_001_1_16x16_6x6_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NN_096_096_1_16x16_6x6_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_096_096_1_16x16_6x6_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NN_001_096_1_16x16_6x6_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NN_096_001_1_16x16_6x6_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NN_001_001_1_16x16_6x6_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NN_096_096_1_16x16_6x6_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NN_096_096_1_16x16_6x6_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NN_001_096_1_16x16_6x6_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NN_096_001_1_16x16_6x6_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_1_16x16_6x6_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NN_128_064_8_16x16_8x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NN_001_064_8_16x16_8x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NN_128_001_8_16x16_8x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NN_001_001_8_16x16_8x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NN_128_064_8_16x16_8x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_128_064_8_16x16_8x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NN_001_064_8_16x16_8x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NN_128_001_8_16x16_8x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NN_001_001_8_16x16_8x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NN_128_064_8_16x16_8x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NN_128_064_8_16x16_8x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NN_001_064_8_16x16_8x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NN_128_001_8_16x16_8x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_8_16x16_8x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NN_128_064_1_16x16_8x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NN_001_064_1_16x16_8x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NN_128_001_1_16x16_8x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NN_001_001_1_16x16_8x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NN_128_064_1_16x16_8x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_128_064_1_16x16_8x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NN_001_064_1_16x16_8x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NN_128_001_1_16x16_8x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NN_001_001_1_16x16_8x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NN_128_064_1_16x16_8x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NN_128_064_1_16x16_8x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NN_001_064_1_16x16_8x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NN_128_001_1_16x16_8x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_1_16x16_8x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NN_096_064_8_16x16_6x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NN_001_064_8_16x16_6x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NN_096_001_8_16x16_6x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NN_001_001_8_16x16_6x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NN_096_064_8_16x16_6x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_096_064_8_16x16_6x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NN_001_064_8_16x16_6x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NN_096_001_8_16x16_6x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NN_001_001_8_16x16_6x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NN_096_064_8_16x16_6x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NN_096_064_8_16x16_6x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NN_001_064_8_16x16_6x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NN_096_001_8_16x16_6x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_8_16x16_6x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NN_096_064_1_16x16_6x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NN_001_064_1_16x16_6x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NN_096_001_1_16x16_6x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NN_001_001_1_16x16_6x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NN_096_064_1_16x16_6x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_096_064_1_16x16_6x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NN_001_064_1_16x16_6x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NN_096_001_1_16x16_6x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NN_001_001_1_16x16_6x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NN_096_064_1_16x16_6x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NN_096_064_1_16x16_6x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NN_001_064_1_16x16_6x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NN_096_001_1_16x16_6x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_1_16x16_6x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NN_064_064_8_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NN_001_064_8_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NN_064_001_8_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NN_001_001_8_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NN_064_064_8_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_064_064_8_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NN_001_064_8_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NN_064_001_8_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NN_001_001_8_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NN_064_064_8_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NN_064_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NN_001_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NN_064_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NN_064_064_1_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NN_001_064_1_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NN_064_001_1_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NN_001_001_1_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NN_064_064_1_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_064_064_1_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NN_001_064_1_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NN_064_001_1_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NN_001_001_1_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NN_064_064_1_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NN_064_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NN_001_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NN_064_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NN_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NN_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NN_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NN_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NN_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NN_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NN_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NN_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NN_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NN_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NN_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NN_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NN_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NN_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NN_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NN_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NN_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NN_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NN_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NN_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NN_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NN_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NN_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NN_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NN_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NN_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NN_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NN_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NN_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NN_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NN_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NN_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NN_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NN_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NN_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NN_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NN_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NN_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NN_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NN_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NN_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NN_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NN_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NN_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NN_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NN_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NN_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NN_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NN_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NN_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NN_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NN_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NN_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NN_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NN_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NN_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NN_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NN_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NN_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NN_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NN_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NN_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NN_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NN_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NN_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NT_096_096_8_16x16_6x6_ColMajor_src;
            *rowKernelSource    = sgemm_NT_001_096_8_16x16_6x6_ColMajor_src;
            *colKernelSource    = sgemm_NT_096_001_8_16x16_6x6_ColMajor_src;
            *cornerKernelSource = sgemm_NT_001_001_8_16x16_6x6_ColMajor_src;
            *sourceBuildOptions = sgemm_NT_096_096_8_16x16_6x6_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_096_096_8_16x16_6x6_ColMajor_bin;
            *rowKernelBinary    = sgemm_NT_001_096_8_16x16_6x6_ColMajor_bin;
            *colKernelBinary    = sgemm_NT_096_001_8_16x16_6x6_ColMajor_bin;
            *cornerKernelBinary = sgemm_NT_001_001_8_16x16_6x6_ColMajor_bin;
            *binaryBuildOptions = sgemm_NT_096_096_8_16x16_6x6_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NT_096_096_8_16x16_6x6_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NT_001_096_8_16x16_6x6_ColMajor_clKernel;
            *colClKernel        = &sgemm_NT_096_001_8_16x16_6x6_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_8_16x16_6x6_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NT_096_096_1_16x16_6x6_ColMajor_src;
            *rowKernelSource    = sgemm_NT_001_096_1_16x16_6x6_ColMajor_src;
            *colKernelSource    = sgemm_NT_096_001_1_16x16_6x6_ColMajor_src;
            *cornerKernelSource = sgemm_NT_001_001_1_16x16_6x6_ColMajor_src;
            *sourceBuildOptions = sgemm_NT_096_096_1_16x16_6x6_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_096_096_1_16x16_6x6_ColMajor_bin;
            *rowKernelBinary    = sgemm_NT_001_096_1_16x16_6x6_ColMajor_bin;
            *colKernelBinary    = sgemm_NT_096_001_1_16x16_6x6_ColMajor_bin;
            *cornerKernelBinary = sgemm_NT_001_001_1_16x16_6x6_ColMajor_bin;
            *binaryBuildOptions = sgemm_NT_096_096_1_16x16_6x6_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NT_096_096_1_16x16_6x6_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NT_001_096_1_16x16_6x6_ColMajor_clKernel;
            *colClKernel        = &sgemm_NT_096_001_1_16x16_6x6_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_1_16x16_6x6_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NT_128_064_8_16x16_8x4_ColMajor_src;
            *rowKernelSource    = sgemm_NT_001_064_8_16x16_8x4_ColMajor_src;
            *colKernelSource    = sgemm_NT_128_001_8_16x16_8x4_ColMajor_src;
            *cornerKernelSource = sgemm_NT_001_001_8_16x16_8x4_ColMajor_src;
            *sourceBuildOptions = sgemm_NT_128_064_8_16x16_8x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_128_064_8_16x16_8x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_NT_001_064_8_16x16_8x4_ColMajor_bin;
            *colKernelBinary    = sgemm_NT_128_001_8_16x16_8x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_NT_001_001_8_16x16_8x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_NT_128_064_8_16x16_8x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NT_128_064_8_16x16_8x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NT_001_064_8_16x16_8x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_NT_128_001_8_16x16_8x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_8_16x16_8x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NT_128_064_1_16x16_8x4_ColMajor_src;
            *rowKernelSource    = sgemm_NT_001_064_1_16x16_8x4_ColMajor_src;
            *colKernelSource    = sgemm_NT_128_001_1_16x16_8x4_ColMajor_src;
            *cornerKernelSource = sgemm_NT_001_001_1_16x16_8x4_ColMajor_src;
            *sourceBuildOptions = sgemm_NT_128_064_1_16x16_8x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_128_064_1_16x16_8x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_NT_001_064_1_16x16_8x4_ColMajor_bin;
            *colKernelBinary    = sgemm_NT_128_001_1_16x16_8x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_NT_001_001_1_16x16_8x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_NT_128_064_1_16x16_8x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NT_128_064_1_16x16_8x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NT_001_064_1_16x16_8x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_NT_128_001_1_16x16_8x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_1_16x16_8x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NT_096_064_8_16x16_6x4_ColMajor_src;
            *rowKernelSource    = sgemm_NT_001_064_8_16x16_6x4_ColMajor_src;
            *colKernelSource    = sgemm_NT_096_001_8_16x16_6x4_ColMajor_src;
            *cornerKernelSource = sgemm_NT_001_001_8_16x16_6x4_ColMajor_src;
            *sourceBuildOptions = sgemm_NT_096_064_8_16x16_6x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_096_064_8_16x16_6x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_NT_001_064_8_16x16_6x4_ColMajor_bin;
            *colKernelBinary    = sgemm_NT_096_001_8_16x16_6x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_NT_001_001_8_16x16_6x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_NT_096_064_8_16x16_6x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NT_096_064_8_16x16_6x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NT_001_064_8_16x16_6x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_NT_096_001_8_16x16_6x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_8_16x16_6x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NT_096_064_1_16x16_6x4_ColMajor_src;
            *rowKernelSource    = sgemm_NT_001_064_1_16x16_6x4_ColMajor_src;
            *colKernelSource    = sgemm_NT_096_001_1_16x16_6x4_ColMajor_src;
            *cornerKernelSource = sgemm_NT_001_001_1_16x16_6x4_ColMajor_src;
            *sourceBuildOptions = sgemm_NT_096_064_1_16x16_6x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_096_064_1_16x16_6x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_NT_001_064_1_16x16_6x4_ColMajor_bin;
            *colKernelBinary    = sgemm_NT_096_001_1_16x16_6x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_NT_001_001_1_16x16_6x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_NT_096_064_1_16x16_6x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NT_096_064_1_16x16_6x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NT_001_064_1_16x16_6x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_NT_096_001_1_16x16_6x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_1_16x16_6x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NT_064_064_8_16x16_4x4_ColMajor_src;
            *rowKernelSource    = sgemm_NT_001_064_8_16x16_4x4_ColMajor_src;
            *colKernelSource    = sgemm_NT_064_001_8_16x16_4x4_ColMajor_src;
            *cornerKernelSource = sgemm_NT_001_001_8_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = sgemm_NT_064_064_8_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_064_064_8_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_NT_001_064_8_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = sgemm_NT_064_001_8_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_NT_001_001_8_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_NT_064_064_8_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NT_064_064_8_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NT_001_064_8_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_NT_064_001_8_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_8_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NT_064_064_1_16x16_4x4_ColMajor_src;
            *rowKernelSource    = sgemm_NT_001_064_1_16x16_4x4_ColMajor_src;
            *colKernelSource    = sgemm_NT_064_001_1_16x16_4x4_ColMajor_src;
            *cornerKernelSource = sgemm_NT_001_001_1_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = sgemm_NT_064_064_1_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_064_064_1_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_NT_001_064_1_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = sgemm_NT_064_001_1_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_NT_001_001_1_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_NT_064_064_1_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NT_064_064_1_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NT_001_064_1_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_NT_064_001_1_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_1_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NT_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = sgemm_NT_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = sgemm_NT_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = sgemm_NT_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = sgemm_NT_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = sgemm_NT_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = sgemm_NT_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = sgemm_NT_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = sgemm_NT_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NT_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NT_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &sgemm_NT_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NT_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = sgemm_NT_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = sgemm_NT_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = sgemm_NT_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = sgemm_NT_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = sgemm_NT_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = sgemm_NT_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = sgemm_NT_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = sgemm_NT_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NT_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NT_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &sgemm_NT_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NT_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = sgemm_NT_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = sgemm_NT_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = sgemm_NT_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = sgemm_NT_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = sgemm_NT_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = sgemm_NT_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = sgemm_NT_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = sgemm_NT_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NT_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NT_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &sgemm_NT_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NT_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = sgemm_NT_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = sgemm_NT_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = sgemm_NT_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = sgemm_NT_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = sgemm_NT_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = sgemm_NT_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = sgemm_NT_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = sgemm_NT_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NT_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NT_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &sgemm_NT_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NT_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = sgemm_NT_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = sgemm_NT_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = sgemm_NT_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = sgemm_NT_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = sgemm_NT_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = sgemm_NT_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = sgemm_NT_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = sgemm_NT_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NT_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NT_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &sgemm_NT_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NT_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = sgemm_NT_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = sgemm_NT_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = sgemm_NT_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = sgemm_NT_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = sgemm_NT_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = sgemm_NT_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = sgemm_NT_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = sgemm_NT_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NT_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NT_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &sgemm_NT_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NT_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = sgemm_NT_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = sgemm_NT_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = sgemm_NT_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = sgemm_NT_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = sgemm_NT_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = sgemm_NT_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = sgemm_NT_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = sgemm_NT_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NT_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NT_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &sgemm_NT_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NT_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = sgemm_NT_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = sgemm_NT_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = sgemm_NT_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = sgemm_NT_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = sgemm_NT_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = sgemm_NT_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = sgemm_NT_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = sgemm_NT_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_NT_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &sgemm_NT_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &sgemm_NT_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NT_096_096_8_16x16_6x6_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NT_001_096_8_16x16_6x6_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NT_096_001_8_16x16_6x6_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NT_001_001_8_16x16_6x6_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NT_096_096_8_16x16_6x6_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_096_096_8_16x16_6x6_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NT_001_096_8_16x16_6x6_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NT_096_001_8_16x16_6x6_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NT_001_001_8_16x16_6x6_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NT_096_096_8_16x16_6x6_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NT_096_096_8_16x16_6x6_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NT_001_096_8_16x16_6x6_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NT_096_001_8_16x16_6x6_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_8_16x16_6x6_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NT_096_096_1_16x16_6x6_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NT_001_096_1_16x16_6x6_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NT_096_001_1_16x16_6x6_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NT_001_001_1_16x16_6x6_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NT_096_096_1_16x16_6x6_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_096_096_1_16x16_6x6_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NT_001_096_1_16x16_6x6_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NT_096_001_1_16x16_6x6_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NT_001_001_1_16x16_6x6_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NT_096_096_1_16x16_6x6_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NT_096_096_1_16x16_6x6_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NT_001_096_1_16x16_6x6_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NT_096_001_1_16x16_6x6_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_1_16x16_6x6_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NT_128_064_8_16x16_8x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NT_001_064_8_16x16_8x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NT_128_001_8_16x16_8x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NT_001_001_8_16x16_8x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NT_128_064_8_16x16_8x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_128_064_8_16x16_8x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NT_001_064_8_16x16_8x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NT_128_001_8_16x16_8x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NT_001_001_8_16x16_8x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NT_128_064_8_16x16_8x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NT_128_064_8_16x16_8x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NT_001_064_8_16x16_8x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NT_128_001_8_16x16_8x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_8_16x16_8x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NT_128_064_1_16x16_8x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NT_001_064_1_16x16_8x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NT_128_001_1_16x16_8x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NT_001_001_1_16x16_8x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NT_128_064_1_16x16_8x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_128_064_1_16x16_8x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NT_001_064_1_16x16_8x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NT_128_001_1_16x16_8x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NT_001_001_1_16x16_8x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NT_128_064_1_16x16_8x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NT_128_064_1_16x16_8x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NT_001_064_1_16x16_8x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NT_128_001_1_16x16_8x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_1_16x16_8x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NT_096_064_8_16x16_6x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NT_001_064_8_16x16_6x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NT_096_001_8_16x16_6x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NT_001_001_8_16x16_6x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NT_096_064_8_16x16_6x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_096_064_8_16x16_6x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NT_001_064_8_16x16_6x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NT_096_001_8_16x16_6x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NT_001_001_8_16x16_6x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NT_096_064_8_16x16_6x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NT_096_064_8_16x16_6x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NT_001_064_8_16x16_6x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NT_096_001_8_16x16_6x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_8_16x16_6x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NT_096_064_1_16x16_6x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NT_001_064_1_16x16_6x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NT_096_001_1_16x16_6x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NT_001_001_1_16x16_6x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NT_096_064_1_16x16_6x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_096_064_1_16x16_6x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NT_001_064_1_16x16_6x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NT_096_001_1_16x16_6x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NT_001_001_1_16x16_6x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NT_096_064_1_16x16_6x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NT_096_064_1_16x16_6x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NT_001_064_1_16x16_6x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NT_096_001_1_16x16_6x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_1_16x16_6x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NT_064_064_8_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NT_001_064_8_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NT_064_001_8_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NT_001_001_8_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NT_064_064_8_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_064_064_8_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NT_001_064_8_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NT_064_001_8_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NT_001_001_8_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NT_064_064_8_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NT_064_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NT_001_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NT_064_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NT_064_064_1_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NT_001_064_1_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NT_064_001_1_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NT_001_001_1_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NT_064_064_1_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_064_064_1_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NT_001_064_1_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NT_064_001_1_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NT_001_001_1_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NT_064_064_1_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NT_064_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NT_001_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NT_064_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NT_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NT_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NT_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NT_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NT_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NT_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NT_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NT_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NT_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NT_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NT_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NT_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NT_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NT_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NT_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NT_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NT_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NT_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NT_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NT_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NT_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NT_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NT_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NT_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NT_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NT_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NT_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NT_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NT_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NT_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NT_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NT_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NT_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NT_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NT_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NT_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NT_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NT_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NT_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NT_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NT_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NT_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NT_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NT_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NT_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NT_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NT_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NT_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NT_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NT_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NT_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NT_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NT_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NT_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NT_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NT_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_NT_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = sgemm_NT_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_NT_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_NT_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_NT_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_NT_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_NT_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_NT_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_NT_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TN_096_096_8_16x16_6x6_ColMajor_src;
            *rowKernelSource    = sgemm_TN_001_096_8_16x16_6x6_ColMajor_src;
            *colKernelSource    = sgemm_TN_096_001_8_16x16_6x6_ColMajor_src;
            *cornerKernelSource = sgemm_TN_001_001_8_16x16_6x6_ColMajor_src;
            *sourceBuildOptions = sgemm_TN_096_096_8_16x16_6x6_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_096_096_8_16x16_6x6_ColMajor_bin;
            *rowKernelBinary    = sgemm_TN_001_096_8_16x16_6x6_ColMajor_bin;
            *colKernelBinary    = sgemm_TN_096_001_8_16x16_6x6_ColMajor_bin;
            *cornerKernelBinary = sgemm_TN_001_001_8_16x16_6x6_ColMajor_bin;
            *binaryBuildOptions = sgemm_TN_096_096_8_16x16_6x6_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TN_096_096_8_16x16_6x6_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TN_001_096_8_16x16_6x6_ColMajor_clKernel;
            *colClKernel        = &sgemm_TN_096_001_8_16x16_6x6_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_8_16x16_6x6_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TN_096_096_1_16x16_6x6_ColMajor_src;
            *rowKernelSource    = sgemm_TN_001_096_1_16x16_6x6_ColMajor_src;
            *colKernelSource    = sgemm_TN_096_001_1_16x16_6x6_ColMajor_src;
            *cornerKernelSource = sgemm_TN_001_001_1_16x16_6x6_ColMajor_src;
            *sourceBuildOptions = sgemm_TN_096_096_1_16x16_6x6_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_096_096_1_16x16_6x6_ColMajor_bin;
            *rowKernelBinary    = sgemm_TN_001_096_1_16x16_6x6_ColMajor_bin;
            *colKernelBinary    = sgemm_TN_096_001_1_16x16_6x6_ColMajor_bin;
            *cornerKernelBinary = sgemm_TN_001_001_1_16x16_6x6_ColMajor_bin;
            *binaryBuildOptions = sgemm_TN_096_096_1_16x16_6x6_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TN_096_096_1_16x16_6x6_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TN_001_096_1_16x16_6x6_ColMajor_clKernel;
            *colClKernel        = &sgemm_TN_096_001_1_16x16_6x6_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_1_16x16_6x6_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TN_128_064_8_16x16_8x4_ColMajor_src;
            *rowKernelSource    = sgemm_TN_001_064_8_16x16_8x4_ColMajor_src;
            *colKernelSource    = sgemm_TN_128_001_8_16x16_8x4_ColMajor_src;
            *cornerKernelSource = sgemm_TN_001_001_8_16x16_8x4_ColMajor_src;
            *sourceBuildOptions = sgemm_TN_128_064_8_16x16_8x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_128_064_8_16x16_8x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_TN_001_064_8_16x16_8x4_ColMajor_bin;
            *colKernelBinary    = sgemm_TN_128_001_8_16x16_8x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_TN_001_001_8_16x16_8x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_TN_128_064_8_16x16_8x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TN_128_064_8_16x16_8x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TN_001_064_8_16x16_8x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_TN_128_001_8_16x16_8x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_8_16x16_8x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TN_128_064_1_16x16_8x4_ColMajor_src;
            *rowKernelSource    = sgemm_TN_001_064_1_16x16_8x4_ColMajor_src;
            *colKernelSource    = sgemm_TN_128_001_1_16x16_8x4_ColMajor_src;
            *cornerKernelSource = sgemm_TN_001_001_1_16x16_8x4_ColMajor_src;
            *sourceBuildOptions = sgemm_TN_128_064_1_16x16_8x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_128_064_1_16x16_8x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_TN_001_064_1_16x16_8x4_ColMajor_bin;
            *colKernelBinary    = sgemm_TN_128_001_1_16x16_8x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_TN_001_001_1_16x16_8x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_TN_128_064_1_16x16_8x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TN_128_064_1_16x16_8x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TN_001_064_1_16x16_8x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_TN_128_001_1_16x16_8x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_1_16x16_8x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TN_096_064_8_16x16_6x4_ColMajor_src;
            *rowKernelSource    = sgemm_TN_001_064_8_16x16_6x4_ColMajor_src;
            *colKernelSource    = sgemm_TN_096_001_8_16x16_6x4_ColMajor_src;
            *cornerKernelSource = sgemm_TN_001_001_8_16x16_6x4_ColMajor_src;
            *sourceBuildOptions = sgemm_TN_096_064_8_16x16_6x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_096_064_8_16x16_6x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_TN_001_064_8_16x16_6x4_ColMajor_bin;
            *colKernelBinary    = sgemm_TN_096_001_8_16x16_6x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_TN_001_001_8_16x16_6x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_TN_096_064_8_16x16_6x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TN_096_064_8_16x16_6x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TN_001_064_8_16x16_6x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_TN_096_001_8_16x16_6x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_8_16x16_6x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TN_096_064_1_16x16_6x4_ColMajor_src;
            *rowKernelSource    = sgemm_TN_001_064_1_16x16_6x4_ColMajor_src;
            *colKernelSource    = sgemm_TN_096_001_1_16x16_6x4_ColMajor_src;
            *cornerKernelSource = sgemm_TN_001_001_1_16x16_6x4_ColMajor_src;
            *sourceBuildOptions = sgemm_TN_096_064_1_16x16_6x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_096_064_1_16x16_6x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_TN_001_064_1_16x16_6x4_ColMajor_bin;
            *colKernelBinary    = sgemm_TN_096_001_1_16x16_6x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_TN_001_001_1_16x16_6x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_TN_096_064_1_16x16_6x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TN_096_064_1_16x16_6x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TN_001_064_1_16x16_6x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_TN_096_001_1_16x16_6x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_1_16x16_6x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TN_064_064_8_16x16_4x4_ColMajor_src;
            *rowKernelSource    = sgemm_TN_001_064_8_16x16_4x4_ColMajor_src;
            *colKernelSource    = sgemm_TN_064_001_8_16x16_4x4_ColMajor_src;
            *cornerKernelSource = sgemm_TN_001_001_8_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = sgemm_TN_064_064_8_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_064_064_8_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_TN_001_064_8_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = sgemm_TN_064_001_8_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_TN_001_001_8_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_TN_064_064_8_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TN_064_064_8_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TN_001_064_8_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_TN_064_001_8_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_8_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TN_064_064_1_16x16_4x4_ColMajor_src;
            *rowKernelSource    = sgemm_TN_001_064_1_16x16_4x4_ColMajor_src;
            *colKernelSource    = sgemm_TN_064_001_1_16x16_4x4_ColMajor_src;
            *cornerKernelSource = sgemm_TN_001_001_1_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = sgemm_TN_064_064_1_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_064_064_1_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_TN_001_064_1_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = sgemm_TN_064_001_1_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_TN_001_001_1_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_TN_064_064_1_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TN_064_064_1_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TN_001_064_1_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_TN_064_001_1_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_1_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TN_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = sgemm_TN_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = sgemm_TN_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = sgemm_TN_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = sgemm_TN_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = sgemm_TN_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = sgemm_TN_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = sgemm_TN_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = sgemm_TN_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TN_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TN_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &sgemm_TN_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TN_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = sgemm_TN_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = sgemm_TN_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = sgemm_TN_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = sgemm_TN_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = sgemm_TN_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = sgemm_TN_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = sgemm_TN_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = sgemm_TN_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TN_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TN_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &sgemm_TN_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TN_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = sgemm_TN_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = sgemm_TN_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = sgemm_TN_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = sgemm_TN_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = sgemm_TN_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = sgemm_TN_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = sgemm_TN_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = sgemm_TN_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TN_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TN_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &sgemm_TN_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TN_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = sgemm_TN_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = sgemm_TN_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = sgemm_TN_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = sgemm_TN_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = sgemm_TN_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = sgemm_TN_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = sgemm_TN_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = sgemm_TN_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TN_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TN_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &sgemm_TN_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TN_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = sgemm_TN_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = sgemm_TN_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = sgemm_TN_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = sgemm_TN_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = sgemm_TN_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = sgemm_TN_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = sgemm_TN_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = sgemm_TN_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TN_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TN_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &sgemm_TN_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TN_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = sgemm_TN_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = sgemm_TN_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = sgemm_TN_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = sgemm_TN_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = sgemm_TN_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = sgemm_TN_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = sgemm_TN_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = sgemm_TN_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TN_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TN_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &sgemm_TN_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TN_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = sgemm_TN_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = sgemm_TN_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = sgemm_TN_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = sgemm_TN_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = sgemm_TN_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = sgemm_TN_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = sgemm_TN_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = sgemm_TN_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TN_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TN_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &sgemm_TN_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TN_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = sgemm_TN_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = sgemm_TN_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = sgemm_TN_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = sgemm_TN_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = sgemm_TN_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = sgemm_TN_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = sgemm_TN_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = sgemm_TN_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TN_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TN_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &sgemm_TN_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TN_096_096_8_16x16_6x6_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TN_001_096_8_16x16_6x6_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TN_096_001_8_16x16_6x6_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TN_001_001_8_16x16_6x6_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TN_096_096_8_16x16_6x6_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_096_096_8_16x16_6x6_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TN_001_096_8_16x16_6x6_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TN_096_001_8_16x16_6x6_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TN_001_001_8_16x16_6x6_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TN_096_096_8_16x16_6x6_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TN_096_096_8_16x16_6x6_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TN_001_096_8_16x16_6x6_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TN_096_001_8_16x16_6x6_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_8_16x16_6x6_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TN_096_096_1_16x16_6x6_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TN_001_096_1_16x16_6x6_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TN_096_001_1_16x16_6x6_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TN_001_001_1_16x16_6x6_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TN_096_096_1_16x16_6x6_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_096_096_1_16x16_6x6_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TN_001_096_1_16x16_6x6_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TN_096_001_1_16x16_6x6_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TN_001_001_1_16x16_6x6_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TN_096_096_1_16x16_6x6_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TN_096_096_1_16x16_6x6_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TN_001_096_1_16x16_6x6_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TN_096_001_1_16x16_6x6_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_1_16x16_6x6_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TN_128_064_8_16x16_8x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TN_001_064_8_16x16_8x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TN_128_001_8_16x16_8x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TN_001_001_8_16x16_8x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TN_128_064_8_16x16_8x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_128_064_8_16x16_8x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TN_001_064_8_16x16_8x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TN_128_001_8_16x16_8x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TN_001_001_8_16x16_8x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TN_128_064_8_16x16_8x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TN_128_064_8_16x16_8x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TN_001_064_8_16x16_8x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TN_128_001_8_16x16_8x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_8_16x16_8x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TN_128_064_1_16x16_8x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TN_001_064_1_16x16_8x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TN_128_001_1_16x16_8x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TN_001_001_1_16x16_8x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TN_128_064_1_16x16_8x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_128_064_1_16x16_8x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TN_001_064_1_16x16_8x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TN_128_001_1_16x16_8x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TN_001_001_1_16x16_8x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TN_128_064_1_16x16_8x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TN_128_064_1_16x16_8x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TN_001_064_1_16x16_8x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TN_128_001_1_16x16_8x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_1_16x16_8x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TN_096_064_8_16x16_6x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TN_001_064_8_16x16_6x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TN_096_001_8_16x16_6x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TN_001_001_8_16x16_6x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TN_096_064_8_16x16_6x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_096_064_8_16x16_6x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TN_001_064_8_16x16_6x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TN_096_001_8_16x16_6x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TN_001_001_8_16x16_6x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TN_096_064_8_16x16_6x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TN_096_064_8_16x16_6x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TN_001_064_8_16x16_6x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TN_096_001_8_16x16_6x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_8_16x16_6x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TN_096_064_1_16x16_6x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TN_001_064_1_16x16_6x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TN_096_001_1_16x16_6x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TN_001_001_1_16x16_6x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TN_096_064_1_16x16_6x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_096_064_1_16x16_6x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TN_001_064_1_16x16_6x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TN_096_001_1_16x16_6x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TN_001_001_1_16x16_6x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TN_096_064_1_16x16_6x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TN_096_064_1_16x16_6x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TN_001_064_1_16x16_6x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TN_096_001_1_16x16_6x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_1_16x16_6x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TN_064_064_8_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TN_001_064_8_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TN_064_001_8_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TN_001_001_8_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TN_064_064_8_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_064_064_8_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TN_001_064_8_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TN_064_001_8_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TN_001_001_8_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TN_064_064_8_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TN_064_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TN_001_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TN_064_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TN_064_064_1_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TN_001_064_1_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TN_064_001_1_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TN_001_001_1_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TN_064_064_1_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_064_064_1_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TN_001_064_1_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TN_064_001_1_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TN_001_001_1_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TN_064_064_1_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TN_064_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TN_001_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TN_064_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TN_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TN_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TN_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TN_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TN_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TN_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TN_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TN_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TN_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TN_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TN_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TN_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TN_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TN_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TN_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TN_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TN_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TN_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TN_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TN_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TN_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TN_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TN_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TN_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TN_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TN_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TN_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TN_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TN_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TN_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TN_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TN_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TN_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TN_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TN_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TN_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TN_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TN_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TN_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TN_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TN_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TN_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TN_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TN_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TN_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TN_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TN_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TN_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TN_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TN_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TN_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TN_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TN_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TN_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TN_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TN_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TN_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TN_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TN_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TN_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TN_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TN_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TN_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TN_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TN_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TT_096_096_8_16x16_6x6_ColMajor_src;
            *rowKernelSource    = sgemm_TT_001_096_8_16x16_6x6_ColMajor_src;
            *colKernelSource    = sgemm_TT_096_001_8_16x16_6x6_ColMajor_src;
            *cornerKernelSource = sgemm_TT_001_001_8_16x16_6x6_ColMajor_src;
            *sourceBuildOptions = sgemm_TT_096_096_8_16x16_6x6_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_096_096_8_16x16_6x6_ColMajor_bin;
            *rowKernelBinary    = sgemm_TT_001_096_8_16x16_6x6_ColMajor_bin;
            *colKernelBinary    = sgemm_TT_096_001_8_16x16_6x6_ColMajor_bin;
            *cornerKernelBinary = sgemm_TT_001_001_8_16x16_6x6_ColMajor_bin;
            *binaryBuildOptions = sgemm_TT_096_096_8_16x16_6x6_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TT_096_096_8_16x16_6x6_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TT_001_096_8_16x16_6x6_ColMajor_clKernel;
            *colClKernel        = &sgemm_TT_096_001_8_16x16_6x6_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_8_16x16_6x6_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TT_096_096_1_16x16_6x6_ColMajor_src;
            *rowKernelSource    = sgemm_TT_001_096_1_16x16_6x6_ColMajor_src;
            *colKernelSource    = sgemm_TT_096_001_1_16x16_6x6_ColMajor_src;
            *cornerKernelSource = sgemm_TT_001_001_1_16x16_6x6_ColMajor_src;
            *sourceBuildOptions = sgemm_TT_096_096_1_16x16_6x6_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_096_096_1_16x16_6x6_ColMajor_bin;
            *rowKernelBinary    = sgemm_TT_001_096_1_16x16_6x6_ColMajor_bin;
            *colKernelBinary    = sgemm_TT_096_001_1_16x16_6x6_ColMajor_bin;
            *cornerKernelBinary = sgemm_TT_001_001_1_16x16_6x6_ColMajor_bin;
            *binaryBuildOptions = sgemm_TT_096_096_1_16x16_6x6_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TT_096_096_1_16x16_6x6_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TT_001_096_1_16x16_6x6_ColMajor_clKernel;
            *colClKernel        = &sgemm_TT_096_001_1_16x16_6x6_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_1_16x16_6x6_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TT_128_064_8_16x16_8x4_ColMajor_src;
            *rowKernelSource    = sgemm_TT_001_064_8_16x16_8x4_ColMajor_src;
            *colKernelSource    = sgemm_TT_128_001_8_16x16_8x4_ColMajor_src;
            *cornerKernelSource = sgemm_TT_001_001_8_16x16_8x4_ColMajor_src;
            *sourceBuildOptions = sgemm_TT_128_064_8_16x16_8x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_128_064_8_16x16_8x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_TT_001_064_8_16x16_8x4_ColMajor_bin;
            *colKernelBinary    = sgemm_TT_128_001_8_16x16_8x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_TT_001_001_8_16x16_8x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_TT_128_064_8_16x16_8x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TT_128_064_8_16x16_8x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TT_001_064_8_16x16_8x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_TT_128_001_8_16x16_8x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_8_16x16_8x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TT_128_064_1_16x16_8x4_ColMajor_src;
            *rowKernelSource    = sgemm_TT_001_064_1_16x16_8x4_ColMajor_src;
            *colKernelSource    = sgemm_TT_128_001_1_16x16_8x4_ColMajor_src;
            *cornerKernelSource = sgemm_TT_001_001_1_16x16_8x4_ColMajor_src;
            *sourceBuildOptions = sgemm_TT_128_064_1_16x16_8x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_128_064_1_16x16_8x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_TT_001_064_1_16x16_8x4_ColMajor_bin;
            *colKernelBinary    = sgemm_TT_128_001_1_16x16_8x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_TT_001_001_1_16x16_8x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_TT_128_064_1_16x16_8x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TT_128_064_1_16x16_8x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TT_001_064_1_16x16_8x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_TT_128_001_1_16x16_8x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_1_16x16_8x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TT_096_064_8_16x16_6x4_ColMajor_src;
            *rowKernelSource    = sgemm_TT_001_064_8_16x16_6x4_ColMajor_src;
            *colKernelSource    = sgemm_TT_096_001_8_16x16_6x4_ColMajor_src;
            *cornerKernelSource = sgemm_TT_001_001_8_16x16_6x4_ColMajor_src;
            *sourceBuildOptions = sgemm_TT_096_064_8_16x16_6x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_096_064_8_16x16_6x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_TT_001_064_8_16x16_6x4_ColMajor_bin;
            *colKernelBinary    = sgemm_TT_096_001_8_16x16_6x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_TT_001_001_8_16x16_6x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_TT_096_064_8_16x16_6x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TT_096_064_8_16x16_6x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TT_001_064_8_16x16_6x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_TT_096_001_8_16x16_6x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_8_16x16_6x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TT_096_064_1_16x16_6x4_ColMajor_src;
            *rowKernelSource    = sgemm_TT_001_064_1_16x16_6x4_ColMajor_src;
            *colKernelSource    = sgemm_TT_096_001_1_16x16_6x4_ColMajor_src;
            *cornerKernelSource = sgemm_TT_001_001_1_16x16_6x4_ColMajor_src;
            *sourceBuildOptions = sgemm_TT_096_064_1_16x16_6x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_096_064_1_16x16_6x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_TT_001_064_1_16x16_6x4_ColMajor_bin;
            *colKernelBinary    = sgemm_TT_096_001_1_16x16_6x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_TT_001_001_1_16x16_6x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_TT_096_064_1_16x16_6x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TT_096_064_1_16x16_6x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TT_001_064_1_16x16_6x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_TT_096_001_1_16x16_6x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_1_16x16_6x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TT_064_064_8_16x16_4x4_ColMajor_src;
            *rowKernelSource    = sgemm_TT_001_064_8_16x16_4x4_ColMajor_src;
            *colKernelSource    = sgemm_TT_064_001_8_16x16_4x4_ColMajor_src;
            *cornerKernelSource = sgemm_TT_001_001_8_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = sgemm_TT_064_064_8_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_064_064_8_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_TT_001_064_8_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = sgemm_TT_064_001_8_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_TT_001_001_8_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_TT_064_064_8_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TT_064_064_8_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TT_001_064_8_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_TT_064_001_8_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_8_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TT_064_064_1_16x16_4x4_ColMajor_src;
            *rowKernelSource    = sgemm_TT_001_064_1_16x16_4x4_ColMajor_src;
            *colKernelSource    = sgemm_TT_064_001_1_16x16_4x4_ColMajor_src;
            *cornerKernelSource = sgemm_TT_001_001_1_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = sgemm_TT_064_064_1_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_064_064_1_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = sgemm_TT_001_064_1_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = sgemm_TT_064_001_1_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = sgemm_TT_001_001_1_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = sgemm_TT_064_064_1_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TT_064_064_1_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TT_001_064_1_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &sgemm_TT_064_001_1_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_1_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TT_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = sgemm_TT_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = sgemm_TT_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = sgemm_TT_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = sgemm_TT_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = sgemm_TT_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = sgemm_TT_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = sgemm_TT_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = sgemm_TT_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TT_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TT_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &sgemm_TT_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TT_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = sgemm_TT_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = sgemm_TT_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = sgemm_TT_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = sgemm_TT_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = sgemm_TT_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = sgemm_TT_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = sgemm_TT_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = sgemm_TT_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TT_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TT_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &sgemm_TT_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TT_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = sgemm_TT_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = sgemm_TT_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = sgemm_TT_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = sgemm_TT_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = sgemm_TT_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = sgemm_TT_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = sgemm_TT_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = sgemm_TT_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TT_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TT_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &sgemm_TT_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TT_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = sgemm_TT_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = sgemm_TT_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = sgemm_TT_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = sgemm_TT_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = sgemm_TT_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = sgemm_TT_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = sgemm_TT_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = sgemm_TT_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TT_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TT_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &sgemm_TT_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TT_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = sgemm_TT_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = sgemm_TT_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = sgemm_TT_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = sgemm_TT_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = sgemm_TT_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = sgemm_TT_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = sgemm_TT_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = sgemm_TT_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TT_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TT_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &sgemm_TT_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TT_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = sgemm_TT_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = sgemm_TT_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = sgemm_TT_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = sgemm_TT_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = sgemm_TT_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = sgemm_TT_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = sgemm_TT_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = sgemm_TT_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TT_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TT_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &sgemm_TT_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TT_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = sgemm_TT_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = sgemm_TT_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = sgemm_TT_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = sgemm_TT_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = sgemm_TT_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = sgemm_TT_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = sgemm_TT_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = sgemm_TT_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TT_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TT_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &sgemm_TT_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TT_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = sgemm_TT_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = sgemm_TT_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = sgemm_TT_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = sgemm_TT_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = sgemm_TT_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = sgemm_TT_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = sgemm_TT_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = sgemm_TT_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &sgemm_TT_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &sgemm_TT_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &sgemm_TT_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TT_096_096_8_16x16_6x6_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TT_001_096_8_16x16_6x6_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TT_096_001_8_16x16_6x6_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TT_001_001_8_16x16_6x6_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TT_096_096_8_16x16_6x6_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_096_096_8_16x16_6x6_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TT_001_096_8_16x16_6x6_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TT_096_001_8_16x16_6x6_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TT_001_001_8_16x16_6x6_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TT_096_096_8_16x16_6x6_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TT_096_096_8_16x16_6x6_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TT_001_096_8_16x16_6x6_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TT_096_001_8_16x16_6x6_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_8_16x16_6x6_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TT_096_096_1_16x16_6x6_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TT_001_096_1_16x16_6x6_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TT_096_001_1_16x16_6x6_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TT_001_001_1_16x16_6x6_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TT_096_096_1_16x16_6x6_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_096_096_1_16x16_6x6_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TT_001_096_1_16x16_6x6_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TT_096_001_1_16x16_6x6_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TT_001_001_1_16x16_6x6_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TT_096_096_1_16x16_6x6_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TT_096_096_1_16x16_6x6_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TT_001_096_1_16x16_6x6_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TT_096_001_1_16x16_6x6_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_1_16x16_6x6_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TT_128_064_8_16x16_8x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TT_001_064_8_16x16_8x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TT_128_001_8_16x16_8x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TT_001_001_8_16x16_8x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TT_128_064_8_16x16_8x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_128_064_8_16x16_8x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TT_001_064_8_16x16_8x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TT_128_001_8_16x16_8x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TT_001_001_8_16x16_8x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TT_128_064_8_16x16_8x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TT_128_064_8_16x16_8x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TT_001_064_8_16x16_8x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TT_128_001_8_16x16_8x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_8_16x16_8x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TT_128_064_1_16x16_8x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TT_001_064_1_16x16_8x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TT_128_001_1_16x16_8x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TT_001_001_1_16x16_8x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TT_128_064_1_16x16_8x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_128_064_1_16x16_8x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TT_001_064_1_16x16_8x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TT_128_001_1_16x16_8x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TT_001_001_1_16x16_8x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TT_128_064_1_16x16_8x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TT_128_064_1_16x16_8x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TT_001_064_1_16x16_8x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TT_128_001_1_16x16_8x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_1_16x16_8x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TT_096_064_8_16x16_6x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TT_001_064_8_16x16_6x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TT_096_001_8_16x16_6x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TT_001_001_8_16x16_6x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TT_096_064_8_16x16_6x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_096_064_8_16x16_6x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TT_001_064_8_16x16_6x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TT_096_001_8_16x16_6x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TT_001_001_8_16x16_6x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TT_096_064_8_16x16_6x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TT_096_064_8_16x16_6x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TT_001_064_8_16x16_6x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TT_096_001_8_16x16_6x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_8_16x16_6x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TT_096_064_1_16x16_6x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TT_001_064_1_16x16_6x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TT_096_001_1_16x16_6x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TT_001_001_1_16x16_6x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TT_096_064_1_16x16_6x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_096_064_1_16x16_6x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TT_001_064_1_16x16_6x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TT_096_001_1_16x16_6x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TT_001_001_1_16x16_6x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TT_096_064_1_16x16_6x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TT_096_064_1_16x16_6x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TT_001_064_1_16x16_6x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TT_096_001_1_16x16_6x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_1_16x16_6x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TT_064_064_8_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TT_001_064_8_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TT_064_001_8_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TT_001_001_8_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TT_064_064_8_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_064_064_8_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TT_001_064_8_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TT_064_001_8_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TT_001_001_8_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TT_064_064_8_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TT_064_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TT_001_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TT_064_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TT_064_064_1_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TT_001_064_1_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TT_064_001_1_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TT_001_001_1_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TT_064_064_1_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_064_064_1_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TT_001_064_1_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TT_064_001_1_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TT_001_001_1_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TT_064_064_1_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TT_064_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TT_001_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TT_064_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TT_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TT_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TT_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TT_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TT_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TT_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TT_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TT_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TT_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TT_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TT_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TT_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TT_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TT_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TT_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TT_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TT_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TT_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TT_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TT_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TT_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TT_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TT_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TT_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TT_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TT_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TT_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TT_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TT_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TT_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TT_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TT_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TT_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TT_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TT_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TT_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TT_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TT_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TT_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TT_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TT_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TT_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TT_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TT_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TT_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TT_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TT_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TT_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = sgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TT_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TT_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TT_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TT_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TT_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TT_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TT_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TT_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = sgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = sgemm_TT_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = sgemm_TT_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = sgemm_TT_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = sgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = sgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = sgemm_TT_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = sgemm_TT_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = sgemm_TT_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = sgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &sgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &sgemm_TT_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &sgemm_TT_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &sgemm_TT_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NN_096_096_8_16x16_6x6_ColMajor_src;
            *rowKernelSource    = dgemm_NN_001_096_8_16x16_6x6_ColMajor_src;
            *colKernelSource    = dgemm_NN_096_001_8_16x16_6x6_ColMajor_src;
            *cornerKernelSource = dgemm_NN_001_001_8_16x16_6x6_ColMajor_src;
            *sourceBuildOptions = dgemm_NN_096_096_8_16x16_6x6_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_096_096_8_16x16_6x6_ColMajor_bin;
            *rowKernelBinary    = dgemm_NN_001_096_8_16x16_6x6_ColMajor_bin;
            *colKernelBinary    = dgemm_NN_096_001_8_16x16_6x6_ColMajor_bin;
            *cornerKernelBinary = dgemm_NN_001_001_8_16x16_6x6_ColMajor_bin;
            *binaryBuildOptions = dgemm_NN_096_096_8_16x16_6x6_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NN_096_096_8_16x16_6x6_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NN_001_096_8_16x16_6x6_ColMajor_clKernel;
            *colClKernel        = &dgemm_NN_096_001_8_16x16_6x6_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_8_16x16_6x6_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NN_096_096_1_16x16_6x6_ColMajor_src;
            *rowKernelSource    = dgemm_NN_001_096_1_16x16_6x6_ColMajor_src;
            *colKernelSource    = dgemm_NN_096_001_1_16x16_6x6_ColMajor_src;
            *cornerKernelSource = dgemm_NN_001_001_1_16x16_6x6_ColMajor_src;
            *sourceBuildOptions = dgemm_NN_096_096_1_16x16_6x6_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_096_096_1_16x16_6x6_ColMajor_bin;
            *rowKernelBinary    = dgemm_NN_001_096_1_16x16_6x6_ColMajor_bin;
            *colKernelBinary    = dgemm_NN_096_001_1_16x16_6x6_ColMajor_bin;
            *cornerKernelBinary = dgemm_NN_001_001_1_16x16_6x6_ColMajor_bin;
            *binaryBuildOptions = dgemm_NN_096_096_1_16x16_6x6_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NN_096_096_1_16x16_6x6_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NN_001_096_1_16x16_6x6_ColMajor_clKernel;
            *colClKernel        = &dgemm_NN_096_001_1_16x16_6x6_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_1_16x16_6x6_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NN_128_064_8_16x16_8x4_ColMajor_src;
            *rowKernelSource    = dgemm_NN_001_064_8_16x16_8x4_ColMajor_src;
            *colKernelSource    = dgemm_NN_128_001_8_16x16_8x4_ColMajor_src;
            *cornerKernelSource = dgemm_NN_001_001_8_16x16_8x4_ColMajor_src;
            *sourceBuildOptions = dgemm_NN_128_064_8_16x16_8x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_128_064_8_16x16_8x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_NN_001_064_8_16x16_8x4_ColMajor_bin;
            *colKernelBinary    = dgemm_NN_128_001_8_16x16_8x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_NN_001_001_8_16x16_8x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_NN_128_064_8_16x16_8x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NN_128_064_8_16x16_8x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NN_001_064_8_16x16_8x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_NN_128_001_8_16x16_8x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_8_16x16_8x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NN_128_064_1_16x16_8x4_ColMajor_src;
            *rowKernelSource    = dgemm_NN_001_064_1_16x16_8x4_ColMajor_src;
            *colKernelSource    = dgemm_NN_128_001_1_16x16_8x4_ColMajor_src;
            *cornerKernelSource = dgemm_NN_001_001_1_16x16_8x4_ColMajor_src;
            *sourceBuildOptions = dgemm_NN_128_064_1_16x16_8x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_128_064_1_16x16_8x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_NN_001_064_1_16x16_8x4_ColMajor_bin;
            *colKernelBinary    = dgemm_NN_128_001_1_16x16_8x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_NN_001_001_1_16x16_8x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_NN_128_064_1_16x16_8x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NN_128_064_1_16x16_8x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NN_001_064_1_16x16_8x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_NN_128_001_1_16x16_8x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_1_16x16_8x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NN_096_064_8_16x16_6x4_ColMajor_src;
            *rowKernelSource    = dgemm_NN_001_064_8_16x16_6x4_ColMajor_src;
            *colKernelSource    = dgemm_NN_096_001_8_16x16_6x4_ColMajor_src;
            *cornerKernelSource = dgemm_NN_001_001_8_16x16_6x4_ColMajor_src;
            *sourceBuildOptions = dgemm_NN_096_064_8_16x16_6x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_096_064_8_16x16_6x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_NN_001_064_8_16x16_6x4_ColMajor_bin;
            *colKernelBinary    = dgemm_NN_096_001_8_16x16_6x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_NN_001_001_8_16x16_6x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_NN_096_064_8_16x16_6x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NN_096_064_8_16x16_6x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NN_001_064_8_16x16_6x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_NN_096_001_8_16x16_6x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_8_16x16_6x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NN_096_064_1_16x16_6x4_ColMajor_src;
            *rowKernelSource    = dgemm_NN_001_064_1_16x16_6x4_ColMajor_src;
            *colKernelSource    = dgemm_NN_096_001_1_16x16_6x4_ColMajor_src;
            *cornerKernelSource = dgemm_NN_001_001_1_16x16_6x4_ColMajor_src;
            *sourceBuildOptions = dgemm_NN_096_064_1_16x16_6x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_096_064_1_16x16_6x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_NN_001_064_1_16x16_6x4_ColMajor_bin;
            *colKernelBinary    = dgemm_NN_096_001_1_16x16_6x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_NN_001_001_1_16x16_6x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_NN_096_064_1_16x16_6x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NN_096_064_1_16x16_6x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NN_001_064_1_16x16_6x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_NN_096_001_1_16x16_6x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_1_16x16_6x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NN_064_064_8_16x16_4x4_ColMajor_src;
            *rowKernelSource    = dgemm_NN_001_064_8_16x16_4x4_ColMajor_src;
            *colKernelSource    = dgemm_NN_064_001_8_16x16_4x4_ColMajor_src;
            *cornerKernelSource = dgemm_NN_001_001_8_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = dgemm_NN_064_064_8_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_064_064_8_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_NN_001_064_8_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = dgemm_NN_064_001_8_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_NN_001_001_8_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_NN_064_064_8_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NN_064_064_8_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NN_001_064_8_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_NN_064_001_8_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_8_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NN_064_064_1_16x16_4x4_ColMajor_src;
            *rowKernelSource    = dgemm_NN_001_064_1_16x16_4x4_ColMajor_src;
            *colKernelSource    = dgemm_NN_064_001_1_16x16_4x4_ColMajor_src;
            *cornerKernelSource = dgemm_NN_001_001_1_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = dgemm_NN_064_064_1_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_064_064_1_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_NN_001_064_1_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = dgemm_NN_064_001_1_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_NN_001_001_1_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_NN_064_064_1_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NN_064_064_1_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NN_001_064_1_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_NN_064_001_1_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_1_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NN_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = dgemm_NN_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = dgemm_NN_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = dgemm_NN_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = dgemm_NN_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = dgemm_NN_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = dgemm_NN_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = dgemm_NN_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = dgemm_NN_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NN_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NN_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &dgemm_NN_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NN_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = dgemm_NN_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = dgemm_NN_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = dgemm_NN_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = dgemm_NN_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = dgemm_NN_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = dgemm_NN_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = dgemm_NN_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = dgemm_NN_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NN_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NN_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &dgemm_NN_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NN_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = dgemm_NN_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = dgemm_NN_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = dgemm_NN_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = dgemm_NN_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = dgemm_NN_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = dgemm_NN_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = dgemm_NN_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = dgemm_NN_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NN_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NN_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &dgemm_NN_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NN_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = dgemm_NN_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = dgemm_NN_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = dgemm_NN_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = dgemm_NN_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = dgemm_NN_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = dgemm_NN_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = dgemm_NN_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = dgemm_NN_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NN_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NN_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &dgemm_NN_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NN_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = dgemm_NN_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = dgemm_NN_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = dgemm_NN_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = dgemm_NN_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = dgemm_NN_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = dgemm_NN_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = dgemm_NN_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = dgemm_NN_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NN_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NN_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &dgemm_NN_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NN_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = dgemm_NN_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = dgemm_NN_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = dgemm_NN_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = dgemm_NN_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = dgemm_NN_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = dgemm_NN_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = dgemm_NN_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = dgemm_NN_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NN_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NN_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &dgemm_NN_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NN_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = dgemm_NN_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = dgemm_NN_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = dgemm_NN_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = dgemm_NN_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = dgemm_NN_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = dgemm_NN_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = dgemm_NN_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = dgemm_NN_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NN_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NN_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &dgemm_NN_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NN_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = dgemm_NN_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = dgemm_NN_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = dgemm_NN_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = dgemm_NN_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = dgemm_NN_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = dgemm_NN_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = dgemm_NN_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = dgemm_NN_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NN_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NN_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &dgemm_NN_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NN_096_096_8_16x16_6x6_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NN_001_096_8_16x16_6x6_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NN_096_001_8_16x16_6x6_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NN_001_001_8_16x16_6x6_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NN_096_096_8_16x16_6x6_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_096_096_8_16x16_6x6_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NN_001_096_8_16x16_6x6_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NN_096_001_8_16x16_6x6_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NN_001_001_8_16x16_6x6_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NN_096_096_8_16x16_6x6_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NN_096_096_8_16x16_6x6_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NN_001_096_8_16x16_6x6_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NN_096_001_8_16x16_6x6_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_8_16x16_6x6_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NN_096_096_1_16x16_6x6_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NN_001_096_1_16x16_6x6_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NN_096_001_1_16x16_6x6_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NN_001_001_1_16x16_6x6_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NN_096_096_1_16x16_6x6_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_096_096_1_16x16_6x6_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NN_001_096_1_16x16_6x6_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NN_096_001_1_16x16_6x6_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NN_001_001_1_16x16_6x6_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NN_096_096_1_16x16_6x6_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NN_096_096_1_16x16_6x6_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NN_001_096_1_16x16_6x6_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NN_096_001_1_16x16_6x6_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_1_16x16_6x6_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NN_128_064_8_16x16_8x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NN_001_064_8_16x16_8x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NN_128_001_8_16x16_8x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NN_001_001_8_16x16_8x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NN_128_064_8_16x16_8x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_128_064_8_16x16_8x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NN_001_064_8_16x16_8x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NN_128_001_8_16x16_8x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NN_001_001_8_16x16_8x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NN_128_064_8_16x16_8x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NN_128_064_8_16x16_8x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NN_001_064_8_16x16_8x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NN_128_001_8_16x16_8x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_8_16x16_8x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NN_128_064_1_16x16_8x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NN_001_064_1_16x16_8x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NN_128_001_1_16x16_8x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NN_001_001_1_16x16_8x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NN_128_064_1_16x16_8x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_128_064_1_16x16_8x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NN_001_064_1_16x16_8x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NN_128_001_1_16x16_8x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NN_001_001_1_16x16_8x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NN_128_064_1_16x16_8x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NN_128_064_1_16x16_8x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NN_001_064_1_16x16_8x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NN_128_001_1_16x16_8x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_1_16x16_8x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NN_096_064_8_16x16_6x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NN_001_064_8_16x16_6x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NN_096_001_8_16x16_6x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NN_001_001_8_16x16_6x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NN_096_064_8_16x16_6x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_096_064_8_16x16_6x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NN_001_064_8_16x16_6x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NN_096_001_8_16x16_6x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NN_001_001_8_16x16_6x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NN_096_064_8_16x16_6x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NN_096_064_8_16x16_6x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NN_001_064_8_16x16_6x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NN_096_001_8_16x16_6x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_8_16x16_6x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NN_096_064_1_16x16_6x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NN_001_064_1_16x16_6x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NN_096_001_1_16x16_6x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NN_001_001_1_16x16_6x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NN_096_064_1_16x16_6x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_096_064_1_16x16_6x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NN_001_064_1_16x16_6x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NN_096_001_1_16x16_6x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NN_001_001_1_16x16_6x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NN_096_064_1_16x16_6x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NN_096_064_1_16x16_6x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NN_001_064_1_16x16_6x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NN_096_001_1_16x16_6x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_1_16x16_6x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NN_064_064_8_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NN_001_064_8_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NN_064_001_8_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NN_001_001_8_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NN_064_064_8_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_064_064_8_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NN_001_064_8_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NN_064_001_8_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NN_001_001_8_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NN_064_064_8_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NN_064_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NN_001_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NN_064_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NN_064_064_1_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NN_001_064_1_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NN_064_001_1_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NN_001_001_1_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NN_064_064_1_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_064_064_1_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NN_001_064_1_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NN_064_001_1_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NN_001_001_1_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NN_064_064_1_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NN_064_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NN_001_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NN_064_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NN_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NN_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NN_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NN_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NN_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NN_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NN_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NN_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NN_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NN_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NN_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NN_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NN_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NN_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NN_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NN_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NN_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NN_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NN_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NN_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NN_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NN_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NN_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NN_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NN_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NN_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NN_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NN_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NN_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NN_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NN_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NN_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NN_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NN_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NN_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NN_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NN_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NN_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NN_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NN_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NN_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NN_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NN_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NN_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NN_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NN_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NN_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NN_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NN_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NN_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NN_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NN_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NN_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NN_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NN_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NN_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NN_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NN_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NN_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NN_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NN_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NN_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NN_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NN_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NN_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NT_096_096_8_16x16_6x6_ColMajor_src;
            *rowKernelSource    = dgemm_NT_001_096_8_16x16_6x6_ColMajor_src;
            *colKernelSource    = dgemm_NT_096_001_8_16x16_6x6_ColMajor_src;
            *cornerKernelSource = dgemm_NT_001_001_8_16x16_6x6_ColMajor_src;
            *sourceBuildOptions = dgemm_NT_096_096_8_16x16_6x6_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_096_096_8_16x16_6x6_ColMajor_bin;
            *rowKernelBinary    = dgemm_NT_001_096_8_16x16_6x6_ColMajor_bin;
            *colKernelBinary    = dgemm_NT_096_001_8_16x16_6x6_ColMajor_bin;
            *cornerKernelBinary = dgemm_NT_001_001_8_16x16_6x6_ColMajor_bin;
            *binaryBuildOptions = dgemm_NT_096_096_8_16x16_6x6_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NT_096_096_8_16x16_6x6_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NT_001_096_8_16x16_6x6_ColMajor_clKernel;
            *colClKernel        = &dgemm_NT_096_001_8_16x16_6x6_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_8_16x16_6x6_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NT_096_096_1_16x16_6x6_ColMajor_src;
            *rowKernelSource    = dgemm_NT_001_096_1_16x16_6x6_ColMajor_src;
            *colKernelSource    = dgemm_NT_096_001_1_16x16_6x6_ColMajor_src;
            *cornerKernelSource = dgemm_NT_001_001_1_16x16_6x6_ColMajor_src;
            *sourceBuildOptions = dgemm_NT_096_096_1_16x16_6x6_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_096_096_1_16x16_6x6_ColMajor_bin;
            *rowKernelBinary    = dgemm_NT_001_096_1_16x16_6x6_ColMajor_bin;
            *colKernelBinary    = dgemm_NT_096_001_1_16x16_6x6_ColMajor_bin;
            *cornerKernelBinary = dgemm_NT_001_001_1_16x16_6x6_ColMajor_bin;
            *binaryBuildOptions = dgemm_NT_096_096_1_16x16_6x6_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NT_096_096_1_16x16_6x6_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NT_001_096_1_16x16_6x6_ColMajor_clKernel;
            *colClKernel        = &dgemm_NT_096_001_1_16x16_6x6_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_1_16x16_6x6_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NT_128_064_8_16x16_8x4_ColMajor_src;
            *rowKernelSource    = dgemm_NT_001_064_8_16x16_8x4_ColMajor_src;
            *colKernelSource    = dgemm_NT_128_001_8_16x16_8x4_ColMajor_src;
            *cornerKernelSource = dgemm_NT_001_001_8_16x16_8x4_ColMajor_src;
            *sourceBuildOptions = dgemm_NT_128_064_8_16x16_8x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_128_064_8_16x16_8x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_NT_001_064_8_16x16_8x4_ColMajor_bin;
            *colKernelBinary    = dgemm_NT_128_001_8_16x16_8x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_NT_001_001_8_16x16_8x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_NT_128_064_8_16x16_8x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NT_128_064_8_16x16_8x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NT_001_064_8_16x16_8x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_NT_128_001_8_16x16_8x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_8_16x16_8x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NT_128_064_1_16x16_8x4_ColMajor_src;
            *rowKernelSource    = dgemm_NT_001_064_1_16x16_8x4_ColMajor_src;
            *colKernelSource    = dgemm_NT_128_001_1_16x16_8x4_ColMajor_src;
            *cornerKernelSource = dgemm_NT_001_001_1_16x16_8x4_ColMajor_src;
            *sourceBuildOptions = dgemm_NT_128_064_1_16x16_8x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_128_064_1_16x16_8x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_NT_001_064_1_16x16_8x4_ColMajor_bin;
            *colKernelBinary    = dgemm_NT_128_001_1_16x16_8x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_NT_001_001_1_16x16_8x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_NT_128_064_1_16x16_8x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NT_128_064_1_16x16_8x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NT_001_064_1_16x16_8x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_NT_128_001_1_16x16_8x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_1_16x16_8x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NT_096_064_8_16x16_6x4_ColMajor_src;
            *rowKernelSource    = dgemm_NT_001_064_8_16x16_6x4_ColMajor_src;
            *colKernelSource    = dgemm_NT_096_001_8_16x16_6x4_ColMajor_src;
            *cornerKernelSource = dgemm_NT_001_001_8_16x16_6x4_ColMajor_src;
            *sourceBuildOptions = dgemm_NT_096_064_8_16x16_6x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_096_064_8_16x16_6x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_NT_001_064_8_16x16_6x4_ColMajor_bin;
            *colKernelBinary    = dgemm_NT_096_001_8_16x16_6x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_NT_001_001_8_16x16_6x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_NT_096_064_8_16x16_6x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NT_096_064_8_16x16_6x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NT_001_064_8_16x16_6x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_NT_096_001_8_16x16_6x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_8_16x16_6x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NT_096_064_1_16x16_6x4_ColMajor_src;
            *rowKernelSource    = dgemm_NT_001_064_1_16x16_6x4_ColMajor_src;
            *colKernelSource    = dgemm_NT_096_001_1_16x16_6x4_ColMajor_src;
            *cornerKernelSource = dgemm_NT_001_001_1_16x16_6x4_ColMajor_src;
            *sourceBuildOptions = dgemm_NT_096_064_1_16x16_6x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_096_064_1_16x16_6x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_NT_001_064_1_16x16_6x4_ColMajor_bin;
            *colKernelBinary    = dgemm_NT_096_001_1_16x16_6x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_NT_001_001_1_16x16_6x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_NT_096_064_1_16x16_6x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NT_096_064_1_16x16_6x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NT_001_064_1_16x16_6x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_NT_096_001_1_16x16_6x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_1_16x16_6x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NT_064_064_8_16x16_4x4_ColMajor_src;
            *rowKernelSource    = dgemm_NT_001_064_8_16x16_4x4_ColMajor_src;
            *colKernelSource    = dgemm_NT_064_001_8_16x16_4x4_ColMajor_src;
            *cornerKernelSource = dgemm_NT_001_001_8_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = dgemm_NT_064_064_8_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_064_064_8_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_NT_001_064_8_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = dgemm_NT_064_001_8_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_NT_001_001_8_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_NT_064_064_8_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NT_064_064_8_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NT_001_064_8_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_NT_064_001_8_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_8_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NT_064_064_1_16x16_4x4_ColMajor_src;
            *rowKernelSource    = dgemm_NT_001_064_1_16x16_4x4_ColMajor_src;
            *colKernelSource    = dgemm_NT_064_001_1_16x16_4x4_ColMajor_src;
            *cornerKernelSource = dgemm_NT_001_001_1_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = dgemm_NT_064_064_1_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_064_064_1_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_NT_001_064_1_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = dgemm_NT_064_001_1_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_NT_001_001_1_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_NT_064_064_1_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NT_064_064_1_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NT_001_064_1_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_NT_064_001_1_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_1_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NT_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = dgemm_NT_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = dgemm_NT_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = dgemm_NT_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = dgemm_NT_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = dgemm_NT_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = dgemm_NT_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = dgemm_NT_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = dgemm_NT_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NT_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NT_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &dgemm_NT_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NT_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = dgemm_NT_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = dgemm_NT_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = dgemm_NT_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = dgemm_NT_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = dgemm_NT_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = dgemm_NT_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = dgemm_NT_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = dgemm_NT_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NT_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NT_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &dgemm_NT_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NT_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = dgemm_NT_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = dgemm_NT_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = dgemm_NT_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = dgemm_NT_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = dgemm_NT_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = dgemm_NT_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = dgemm_NT_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = dgemm_NT_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NT_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NT_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &dgemm_NT_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NT_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = dgemm_NT_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = dgemm_NT_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = dgemm_NT_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = dgemm_NT_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = dgemm_NT_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = dgemm_NT_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = dgemm_NT_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = dgemm_NT_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NT_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NT_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &dgemm_NT_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NT_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = dgemm_NT_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = dgemm_NT_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = dgemm_NT_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = dgemm_NT_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = dgemm_NT_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = dgemm_NT_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = dgemm_NT_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = dgemm_NT_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NT_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NT_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &dgemm_NT_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NT_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = dgemm_NT_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = dgemm_NT_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = dgemm_NT_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = dgemm_NT_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = dgemm_NT_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = dgemm_NT_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = dgemm_NT_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = dgemm_NT_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NT_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NT_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &dgemm_NT_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NT_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = dgemm_NT_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = dgemm_NT_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = dgemm_NT_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = dgemm_NT_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = dgemm_NT_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = dgemm_NT_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = dgemm_NT_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = dgemm_NT_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NT_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NT_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &dgemm_NT_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NT_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = dgemm_NT_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = dgemm_NT_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = dgemm_NT_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = dgemm_NT_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = dgemm_NT_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = dgemm_NT_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = dgemm_NT_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = dgemm_NT_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_NT_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &dgemm_NT_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &dgemm_NT_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NT_096_096_8_16x16_6x6_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NT_001_096_8_16x16_6x6_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NT_096_001_8_16x16_6x6_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NT_001_001_8_16x16_6x6_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NT_096_096_8_16x16_6x6_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_096_096_8_16x16_6x6_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NT_001_096_8_16x16_6x6_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NT_096_001_8_16x16_6x6_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NT_001_001_8_16x16_6x6_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NT_096_096_8_16x16_6x6_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NT_096_096_8_16x16_6x6_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NT_001_096_8_16x16_6x6_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NT_096_001_8_16x16_6x6_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_8_16x16_6x6_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NT_096_096_1_16x16_6x6_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NT_001_096_1_16x16_6x6_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NT_096_001_1_16x16_6x6_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NT_001_001_1_16x16_6x6_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NT_096_096_1_16x16_6x6_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_096_096_1_16x16_6x6_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NT_001_096_1_16x16_6x6_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NT_096_001_1_16x16_6x6_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NT_001_001_1_16x16_6x6_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NT_096_096_1_16x16_6x6_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NT_096_096_1_16x16_6x6_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NT_001_096_1_16x16_6x6_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NT_096_001_1_16x16_6x6_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_1_16x16_6x6_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NT_128_064_8_16x16_8x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NT_001_064_8_16x16_8x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NT_128_001_8_16x16_8x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NT_001_001_8_16x16_8x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NT_128_064_8_16x16_8x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_128_064_8_16x16_8x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NT_001_064_8_16x16_8x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NT_128_001_8_16x16_8x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NT_001_001_8_16x16_8x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NT_128_064_8_16x16_8x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NT_128_064_8_16x16_8x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NT_001_064_8_16x16_8x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NT_128_001_8_16x16_8x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_8_16x16_8x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NT_128_064_1_16x16_8x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NT_001_064_1_16x16_8x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NT_128_001_1_16x16_8x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NT_001_001_1_16x16_8x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NT_128_064_1_16x16_8x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_128_064_1_16x16_8x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NT_001_064_1_16x16_8x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NT_128_001_1_16x16_8x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NT_001_001_1_16x16_8x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NT_128_064_1_16x16_8x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NT_128_064_1_16x16_8x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NT_001_064_1_16x16_8x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NT_128_001_1_16x16_8x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_1_16x16_8x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NT_096_064_8_16x16_6x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NT_001_064_8_16x16_6x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NT_096_001_8_16x16_6x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NT_001_001_8_16x16_6x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NT_096_064_8_16x16_6x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_096_064_8_16x16_6x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NT_001_064_8_16x16_6x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NT_096_001_8_16x16_6x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NT_001_001_8_16x16_6x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NT_096_064_8_16x16_6x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NT_096_064_8_16x16_6x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NT_001_064_8_16x16_6x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NT_096_001_8_16x16_6x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_8_16x16_6x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NT_096_064_1_16x16_6x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NT_001_064_1_16x16_6x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NT_096_001_1_16x16_6x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NT_001_001_1_16x16_6x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NT_096_064_1_16x16_6x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_096_064_1_16x16_6x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NT_001_064_1_16x16_6x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NT_096_001_1_16x16_6x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NT_001_001_1_16x16_6x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NT_096_064_1_16x16_6x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NT_096_064_1_16x16_6x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NT_001_064_1_16x16_6x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NT_096_001_1_16x16_6x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_1_16x16_6x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NT_064_064_8_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NT_001_064_8_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NT_064_001_8_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NT_001_001_8_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NT_064_064_8_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_064_064_8_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NT_001_064_8_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NT_064_001_8_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NT_001_001_8_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NT_064_064_8_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NT_064_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NT_001_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NT_064_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NT_064_064_1_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NT_001_064_1_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NT_064_001_1_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NT_001_001_1_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NT_064_064_1_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_064_064_1_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NT_001_064_1_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NT_064_001_1_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NT_001_001_1_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NT_064_064_1_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NT_064_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NT_001_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NT_064_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NT_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NT_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NT_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NT_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NT_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NT_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NT_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NT_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NT_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NT_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NT_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NT_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NT_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NT_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NT_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NT_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NT_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NT_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NT_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NT_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NT_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NT_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NT_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NT_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NT_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NT_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NT_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NT_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NT_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NT_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NT_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NT_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NT_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NT_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NT_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NT_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NT_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NT_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NT_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NT_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NT_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NT_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NT_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NT_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NT_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NT_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NT_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NT_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NT_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NT_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NT_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NT_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NT_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NT_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NT_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NT_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_NT_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = dgemm_NT_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_NT_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_NT_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_NT_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_NT_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_NT_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_NT_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_NT_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TN_096_096_8_16x16_6x6_ColMajor_src;
            *rowKernelSource    = dgemm_TN_001_096_8_16x16_6x6_ColMajor_src;
            *colKernelSource    = dgemm_TN_096_001_8_16x16_6x6_ColMajor_src;
            *cornerKernelSource = dgemm_TN_001_001_8_16x16_6x6_ColMajor_src;
            *sourceBuildOptions = dgemm_TN_096_096_8_16x16_6x6_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_096_096_8_16x16_6x6_ColMajor_bin;
            *rowKernelBinary    = dgemm_TN_001_096_8_16x16_6x6_ColMajor_bin;
            *colKernelBinary    = dgemm_TN_096_001_8_16x16_6x6_ColMajor_bin;
            *cornerKernelBinary = dgemm_TN_001_001_8_16x16_6x6_ColMajor_bin;
            *binaryBuildOptions = dgemm_TN_096_096_8_16x16_6x6_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TN_096_096_8_16x16_6x6_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TN_001_096_8_16x16_6x6_ColMajor_clKernel;
            *colClKernel        = &dgemm_TN_096_001_8_16x16_6x6_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_8_16x16_6x6_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TN_096_096_1_16x16_6x6_ColMajor_src;
            *rowKernelSource    = dgemm_TN_001_096_1_16x16_6x6_ColMajor_src;
            *colKernelSource    = dgemm_TN_096_001_1_16x16_6x6_ColMajor_src;
            *cornerKernelSource = dgemm_TN_001_001_1_16x16_6x6_ColMajor_src;
            *sourceBuildOptions = dgemm_TN_096_096_1_16x16_6x6_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_096_096_1_16x16_6x6_ColMajor_bin;
            *rowKernelBinary    = dgemm_TN_001_096_1_16x16_6x6_ColMajor_bin;
            *colKernelBinary    = dgemm_TN_096_001_1_16x16_6x6_ColMajor_bin;
            *cornerKernelBinary = dgemm_TN_001_001_1_16x16_6x6_ColMajor_bin;
            *binaryBuildOptions = dgemm_TN_096_096_1_16x16_6x6_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TN_096_096_1_16x16_6x6_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TN_001_096_1_16x16_6x6_ColMajor_clKernel;
            *colClKernel        = &dgemm_TN_096_001_1_16x16_6x6_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_1_16x16_6x6_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TN_128_064_8_16x16_8x4_ColMajor_src;
            *rowKernelSource    = dgemm_TN_001_064_8_16x16_8x4_ColMajor_src;
            *colKernelSource    = dgemm_TN_128_001_8_16x16_8x4_ColMajor_src;
            *cornerKernelSource = dgemm_TN_001_001_8_16x16_8x4_ColMajor_src;
            *sourceBuildOptions = dgemm_TN_128_064_8_16x16_8x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_128_064_8_16x16_8x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_TN_001_064_8_16x16_8x4_ColMajor_bin;
            *colKernelBinary    = dgemm_TN_128_001_8_16x16_8x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_TN_001_001_8_16x16_8x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_TN_128_064_8_16x16_8x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TN_128_064_8_16x16_8x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TN_001_064_8_16x16_8x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_TN_128_001_8_16x16_8x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_8_16x16_8x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TN_128_064_1_16x16_8x4_ColMajor_src;
            *rowKernelSource    = dgemm_TN_001_064_1_16x16_8x4_ColMajor_src;
            *colKernelSource    = dgemm_TN_128_001_1_16x16_8x4_ColMajor_src;
            *cornerKernelSource = dgemm_TN_001_001_1_16x16_8x4_ColMajor_src;
            *sourceBuildOptions = dgemm_TN_128_064_1_16x16_8x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_128_064_1_16x16_8x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_TN_001_064_1_16x16_8x4_ColMajor_bin;
            *colKernelBinary    = dgemm_TN_128_001_1_16x16_8x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_TN_001_001_1_16x16_8x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_TN_128_064_1_16x16_8x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TN_128_064_1_16x16_8x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TN_001_064_1_16x16_8x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_TN_128_001_1_16x16_8x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_1_16x16_8x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TN_096_064_8_16x16_6x4_ColMajor_src;
            *rowKernelSource    = dgemm_TN_001_064_8_16x16_6x4_ColMajor_src;
            *colKernelSource    = dgemm_TN_096_001_8_16x16_6x4_ColMajor_src;
            *cornerKernelSource = dgemm_TN_001_001_8_16x16_6x4_ColMajor_src;
            *sourceBuildOptions = dgemm_TN_096_064_8_16x16_6x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_096_064_8_16x16_6x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_TN_001_064_8_16x16_6x4_ColMajor_bin;
            *colKernelBinary    = dgemm_TN_096_001_8_16x16_6x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_TN_001_001_8_16x16_6x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_TN_096_064_8_16x16_6x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TN_096_064_8_16x16_6x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TN_001_064_8_16x16_6x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_TN_096_001_8_16x16_6x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_8_16x16_6x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TN_096_064_1_16x16_6x4_ColMajor_src;
            *rowKernelSource    = dgemm_TN_001_064_1_16x16_6x4_ColMajor_src;
            *colKernelSource    = dgemm_TN_096_001_1_16x16_6x4_ColMajor_src;
            *cornerKernelSource = dgemm_TN_001_001_1_16x16_6x4_ColMajor_src;
            *sourceBuildOptions = dgemm_TN_096_064_1_16x16_6x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_096_064_1_16x16_6x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_TN_001_064_1_16x16_6x4_ColMajor_bin;
            *colKernelBinary    = dgemm_TN_096_001_1_16x16_6x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_TN_001_001_1_16x16_6x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_TN_096_064_1_16x16_6x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TN_096_064_1_16x16_6x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TN_001_064_1_16x16_6x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_TN_096_001_1_16x16_6x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_1_16x16_6x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TN_064_064_8_16x16_4x4_ColMajor_src;
            *rowKernelSource    = dgemm_TN_001_064_8_16x16_4x4_ColMajor_src;
            *colKernelSource    = dgemm_TN_064_001_8_16x16_4x4_ColMajor_src;
            *cornerKernelSource = dgemm_TN_001_001_8_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = dgemm_TN_064_064_8_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_064_064_8_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_TN_001_064_8_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = dgemm_TN_064_001_8_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_TN_001_001_8_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_TN_064_064_8_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TN_064_064_8_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TN_001_064_8_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_TN_064_001_8_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_8_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TN_064_064_1_16x16_4x4_ColMajor_src;
            *rowKernelSource    = dgemm_TN_001_064_1_16x16_4x4_ColMajor_src;
            *colKernelSource    = dgemm_TN_064_001_1_16x16_4x4_ColMajor_src;
            *cornerKernelSource = dgemm_TN_001_001_1_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = dgemm_TN_064_064_1_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_064_064_1_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_TN_001_064_1_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = dgemm_TN_064_001_1_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_TN_001_001_1_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_TN_064_064_1_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TN_064_064_1_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TN_001_064_1_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_TN_064_001_1_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_1_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TN_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = dgemm_TN_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = dgemm_TN_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = dgemm_TN_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = dgemm_TN_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = dgemm_TN_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = dgemm_TN_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = dgemm_TN_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = dgemm_TN_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TN_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TN_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &dgemm_TN_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TN_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = dgemm_TN_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = dgemm_TN_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = dgemm_TN_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = dgemm_TN_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = dgemm_TN_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = dgemm_TN_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = dgemm_TN_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = dgemm_TN_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TN_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TN_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &dgemm_TN_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TN_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = dgemm_TN_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = dgemm_TN_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = dgemm_TN_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = dgemm_TN_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = dgemm_TN_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = dgemm_TN_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = dgemm_TN_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = dgemm_TN_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TN_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TN_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &dgemm_TN_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TN_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = dgemm_TN_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = dgemm_TN_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = dgemm_TN_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = dgemm_TN_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = dgemm_TN_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = dgemm_TN_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = dgemm_TN_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = dgemm_TN_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TN_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TN_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &dgemm_TN_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TN_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = dgemm_TN_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = dgemm_TN_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = dgemm_TN_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = dgemm_TN_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = dgemm_TN_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = dgemm_TN_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = dgemm_TN_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = dgemm_TN_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TN_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TN_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &dgemm_TN_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TN_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = dgemm_TN_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = dgemm_TN_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = dgemm_TN_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = dgemm_TN_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = dgemm_TN_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = dgemm_TN_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = dgemm_TN_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = dgemm_TN_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TN_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TN_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &dgemm_TN_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TN_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = dgemm_TN_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = dgemm_TN_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = dgemm_TN_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = dgemm_TN_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = dgemm_TN_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = dgemm_TN_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = dgemm_TN_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = dgemm_TN_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TN_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TN_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &dgemm_TN_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TN_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = dgemm_TN_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = dgemm_TN_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = dgemm_TN_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = dgemm_TN_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = dgemm_TN_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = dgemm_TN_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = dgemm_TN_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = dgemm_TN_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TN_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TN_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &dgemm_TN_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TN_096_096_8_16x16_6x6_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TN_001_096_8_16x16_6x6_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TN_096_001_8_16x16_6x6_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TN_001_001_8_16x16_6x6_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TN_096_096_8_16x16_6x6_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_096_096_8_16x16_6x6_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TN_001_096_8_16x16_6x6_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TN_096_001_8_16x16_6x6_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TN_001_001_8_16x16_6x6_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TN_096_096_8_16x16_6x6_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TN_096_096_8_16x16_6x6_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TN_001_096_8_16x16_6x6_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TN_096_001_8_16x16_6x6_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_8_16x16_6x6_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TN_096_096_1_16x16_6x6_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TN_001_096_1_16x16_6x6_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TN_096_001_1_16x16_6x6_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TN_001_001_1_16x16_6x6_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TN_096_096_1_16x16_6x6_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_096_096_1_16x16_6x6_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TN_001_096_1_16x16_6x6_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TN_096_001_1_16x16_6x6_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TN_001_001_1_16x16_6x6_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TN_096_096_1_16x16_6x6_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TN_096_096_1_16x16_6x6_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TN_001_096_1_16x16_6x6_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TN_096_001_1_16x16_6x6_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_1_16x16_6x6_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TN_128_064_8_16x16_8x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TN_001_064_8_16x16_8x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TN_128_001_8_16x16_8x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TN_001_001_8_16x16_8x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TN_128_064_8_16x16_8x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_128_064_8_16x16_8x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TN_001_064_8_16x16_8x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TN_128_001_8_16x16_8x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TN_001_001_8_16x16_8x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TN_128_064_8_16x16_8x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TN_128_064_8_16x16_8x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TN_001_064_8_16x16_8x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TN_128_001_8_16x16_8x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_8_16x16_8x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TN_128_064_1_16x16_8x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TN_001_064_1_16x16_8x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TN_128_001_1_16x16_8x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TN_001_001_1_16x16_8x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TN_128_064_1_16x16_8x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_128_064_1_16x16_8x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TN_001_064_1_16x16_8x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TN_128_001_1_16x16_8x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TN_001_001_1_16x16_8x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TN_128_064_1_16x16_8x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TN_128_064_1_16x16_8x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TN_001_064_1_16x16_8x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TN_128_001_1_16x16_8x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_1_16x16_8x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TN_096_064_8_16x16_6x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TN_001_064_8_16x16_6x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TN_096_001_8_16x16_6x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TN_001_001_8_16x16_6x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TN_096_064_8_16x16_6x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_096_064_8_16x16_6x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TN_001_064_8_16x16_6x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TN_096_001_8_16x16_6x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TN_001_001_8_16x16_6x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TN_096_064_8_16x16_6x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TN_096_064_8_16x16_6x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TN_001_064_8_16x16_6x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TN_096_001_8_16x16_6x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_8_16x16_6x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TN_096_064_1_16x16_6x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TN_001_064_1_16x16_6x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TN_096_001_1_16x16_6x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TN_001_001_1_16x16_6x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TN_096_064_1_16x16_6x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_096_064_1_16x16_6x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TN_001_064_1_16x16_6x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TN_096_001_1_16x16_6x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TN_001_001_1_16x16_6x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TN_096_064_1_16x16_6x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TN_096_064_1_16x16_6x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TN_001_064_1_16x16_6x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TN_096_001_1_16x16_6x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_1_16x16_6x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TN_064_064_8_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TN_001_064_8_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TN_064_001_8_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TN_001_001_8_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TN_064_064_8_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_064_064_8_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TN_001_064_8_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TN_064_001_8_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TN_001_001_8_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TN_064_064_8_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TN_064_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TN_001_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TN_064_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TN_064_064_1_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TN_001_064_1_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TN_064_001_1_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TN_001_001_1_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TN_064_064_1_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_064_064_1_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TN_001_064_1_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TN_064_001_1_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TN_001_001_1_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TN_064_064_1_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TN_064_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TN_001_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TN_064_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TN_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TN_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TN_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TN_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TN_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TN_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TN_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TN_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TN_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TN_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TN_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TN_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TN_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TN_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TN_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TN_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TN_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TN_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TN_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TN_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TN_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TN_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TN_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TN_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TN_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TN_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TN_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TN_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TN_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TN_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TN_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TN_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TN_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TN_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TN_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TN_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TN_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TN_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TN_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TN_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TN_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TN_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TN_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TN_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TN_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TN_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TN_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TN_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TN_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TN_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TN_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TN_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TN_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TN_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TN_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TN_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TN_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TN_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TN_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TN_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TN_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TN_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TN_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TN_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TN_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TT_096_096_8_16x16_6x6_ColMajor_src;
            *rowKernelSource    = dgemm_TT_001_096_8_16x16_6x6_ColMajor_src;
            *colKernelSource    = dgemm_TT_096_001_8_16x16_6x6_ColMajor_src;
            *cornerKernelSource = dgemm_TT_001_001_8_16x16_6x6_ColMajor_src;
            *sourceBuildOptions = dgemm_TT_096_096_8_16x16_6x6_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_096_096_8_16x16_6x6_ColMajor_bin;
            *rowKernelBinary    = dgemm_TT_001_096_8_16x16_6x6_ColMajor_bin;
            *colKernelBinary    = dgemm_TT_096_001_8_16x16_6x6_ColMajor_bin;
            *cornerKernelBinary = dgemm_TT_001_001_8_16x16_6x6_ColMajor_bin;
            *binaryBuildOptions = dgemm_TT_096_096_8_16x16_6x6_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TT_096_096_8_16x16_6x6_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TT_001_096_8_16x16_6x6_ColMajor_clKernel;
            *colClKernel        = &dgemm_TT_096_001_8_16x16_6x6_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_8_16x16_6x6_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TT_096_096_1_16x16_6x6_ColMajor_src;
            *rowKernelSource    = dgemm_TT_001_096_1_16x16_6x6_ColMajor_src;
            *colKernelSource    = dgemm_TT_096_001_1_16x16_6x6_ColMajor_src;
            *cornerKernelSource = dgemm_TT_001_001_1_16x16_6x6_ColMajor_src;
            *sourceBuildOptions = dgemm_TT_096_096_1_16x16_6x6_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_096_096_1_16x16_6x6_ColMajor_bin;
            *rowKernelBinary    = dgemm_TT_001_096_1_16x16_6x6_ColMajor_bin;
            *colKernelBinary    = dgemm_TT_096_001_1_16x16_6x6_ColMajor_bin;
            *cornerKernelBinary = dgemm_TT_001_001_1_16x16_6x6_ColMajor_bin;
            *binaryBuildOptions = dgemm_TT_096_096_1_16x16_6x6_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TT_096_096_1_16x16_6x6_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TT_001_096_1_16x16_6x6_ColMajor_clKernel;
            *colClKernel        = &dgemm_TT_096_001_1_16x16_6x6_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_1_16x16_6x6_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TT_128_064_8_16x16_8x4_ColMajor_src;
            *rowKernelSource    = dgemm_TT_001_064_8_16x16_8x4_ColMajor_src;
            *colKernelSource    = dgemm_TT_128_001_8_16x16_8x4_ColMajor_src;
            *cornerKernelSource = dgemm_TT_001_001_8_16x16_8x4_ColMajor_src;
            *sourceBuildOptions = dgemm_TT_128_064_8_16x16_8x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_128_064_8_16x16_8x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_TT_001_064_8_16x16_8x4_ColMajor_bin;
            *colKernelBinary    = dgemm_TT_128_001_8_16x16_8x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_TT_001_001_8_16x16_8x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_TT_128_064_8_16x16_8x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TT_128_064_8_16x16_8x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TT_001_064_8_16x16_8x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_TT_128_001_8_16x16_8x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_8_16x16_8x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TT_128_064_1_16x16_8x4_ColMajor_src;
            *rowKernelSource    = dgemm_TT_001_064_1_16x16_8x4_ColMajor_src;
            *colKernelSource    = dgemm_TT_128_001_1_16x16_8x4_ColMajor_src;
            *cornerKernelSource = dgemm_TT_001_001_1_16x16_8x4_ColMajor_src;
            *sourceBuildOptions = dgemm_TT_128_064_1_16x16_8x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_128_064_1_16x16_8x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_TT_001_064_1_16x16_8x4_ColMajor_bin;
            *colKernelBinary    = dgemm_TT_128_001_1_16x16_8x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_TT_001_001_1_16x16_8x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_TT_128_064_1_16x16_8x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TT_128_064_1_16x16_8x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TT_001_064_1_16x16_8x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_TT_128_001_1_16x16_8x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_1_16x16_8x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TT_096_064_8_16x16_6x4_ColMajor_src;
            *rowKernelSource    = dgemm_TT_001_064_8_16x16_6x4_ColMajor_src;
            *colKernelSource    = dgemm_TT_096_001_8_16x16_6x4_ColMajor_src;
            *cornerKernelSource = dgemm_TT_001_001_8_16x16_6x4_ColMajor_src;
            *sourceBuildOptions = dgemm_TT_096_064_8_16x16_6x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_096_064_8_16x16_6x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_TT_001_064_8_16x16_6x4_ColMajor_bin;
            *colKernelBinary    = dgemm_TT_096_001_8_16x16_6x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_TT_001_001_8_16x16_6x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_TT_096_064_8_16x16_6x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TT_096_064_8_16x16_6x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TT_001_064_8_16x16_6x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_TT_096_001_8_16x16_6x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_8_16x16_6x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TT_096_064_1_16x16_6x4_ColMajor_src;
            *rowKernelSource    = dgemm_TT_001_064_1_16x16_6x4_ColMajor_src;
            *colKernelSource    = dgemm_TT_096_001_1_16x16_6x4_ColMajor_src;
            *cornerKernelSource = dgemm_TT_001_001_1_16x16_6x4_ColMajor_src;
            *sourceBuildOptions = dgemm_TT_096_064_1_16x16_6x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_096_064_1_16x16_6x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_TT_001_064_1_16x16_6x4_ColMajor_bin;
            *colKernelBinary    = dgemm_TT_096_001_1_16x16_6x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_TT_001_001_1_16x16_6x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_TT_096_064_1_16x16_6x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TT_096_064_1_16x16_6x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TT_001_064_1_16x16_6x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_TT_096_001_1_16x16_6x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_1_16x16_6x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TT_064_064_8_16x16_4x4_ColMajor_src;
            *rowKernelSource    = dgemm_TT_001_064_8_16x16_4x4_ColMajor_src;
            *colKernelSource    = dgemm_TT_064_001_8_16x16_4x4_ColMajor_src;
            *cornerKernelSource = dgemm_TT_001_001_8_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = dgemm_TT_064_064_8_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_064_064_8_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_TT_001_064_8_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = dgemm_TT_064_001_8_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_TT_001_001_8_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_TT_064_064_8_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TT_064_064_8_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TT_001_064_8_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_TT_064_001_8_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_8_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TT_064_064_1_16x16_4x4_ColMajor_src;
            *rowKernelSource    = dgemm_TT_001_064_1_16x16_4x4_ColMajor_src;
            *colKernelSource    = dgemm_TT_064_001_1_16x16_4x4_ColMajor_src;
            *cornerKernelSource = dgemm_TT_001_001_1_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = dgemm_TT_064_064_1_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_064_064_1_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = dgemm_TT_001_064_1_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = dgemm_TT_064_001_1_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = dgemm_TT_001_001_1_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = dgemm_TT_064_064_1_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TT_064_064_1_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TT_001_064_1_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &dgemm_TT_064_001_1_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_1_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TT_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = dgemm_TT_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = dgemm_TT_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = dgemm_TT_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = dgemm_TT_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = dgemm_TT_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = dgemm_TT_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = dgemm_TT_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = dgemm_TT_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TT_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TT_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &dgemm_TT_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TT_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = dgemm_TT_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = dgemm_TT_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = dgemm_TT_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = dgemm_TT_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = dgemm_TT_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = dgemm_TT_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = dgemm_TT_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = dgemm_TT_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TT_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TT_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &dgemm_TT_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TT_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = dgemm_TT_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = dgemm_TT_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = dgemm_TT_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = dgemm_TT_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = dgemm_TT_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = dgemm_TT_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = dgemm_TT_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = dgemm_TT_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TT_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TT_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &dgemm_TT_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TT_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = dgemm_TT_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = dgemm_TT_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = dgemm_TT_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = dgemm_TT_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = dgemm_TT_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = dgemm_TT_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = dgemm_TT_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = dgemm_TT_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TT_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TT_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &dgemm_TT_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TT_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = dgemm_TT_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = dgemm_TT_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = dgemm_TT_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = dgemm_TT_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = dgemm_TT_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = dgemm_TT_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = dgemm_TT_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = dgemm_TT_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TT_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TT_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &dgemm_TT_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TT_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = dgemm_TT_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = dgemm_TT_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = dgemm_TT_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = dgemm_TT_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = dgemm_TT_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = dgemm_TT_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = dgemm_TT_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = dgemm_TT_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TT_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TT_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &dgemm_TT_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TT_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = dgemm_TT_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = dgemm_TT_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = dgemm_TT_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = dgemm_TT_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = dgemm_TT_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = dgemm_TT_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = dgemm_TT_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = dgemm_TT_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TT_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TT_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &dgemm_TT_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TT_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = dgemm_TT_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = dgemm_TT_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = dgemm_TT_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = dgemm_TT_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = dgemm_TT_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = dgemm_TT_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = dgemm_TT_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = dgemm_TT_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &dgemm_TT_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &dgemm_TT_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &dgemm_TT_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TT_096_096_8_16x16_6x6_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TT_001_096_8_16x16_6x6_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TT_096_001_8_16x16_6x6_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TT_001_001_8_16x16_6x6_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TT_096_096_8_16x16_6x6_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_096_096_8_16x16_6x6_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TT_001_096_8_16x16_6x6_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TT_096_001_8_16x16_6x6_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TT_001_001_8_16x16_6x6_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TT_096_096_8_16x16_6x6_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TT_096_096_8_16x16_6x6_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TT_001_096_8_16x16_6x6_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TT_096_001_8_16x16_6x6_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_8_16x16_6x6_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%96 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TT_096_096_1_16x16_6x6_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TT_001_096_1_16x16_6x6_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TT_096_001_1_16x16_6x6_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TT_001_001_1_16x16_6x6_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TT_096_096_1_16x16_6x6_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_096_096_1_16x16_6x6_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TT_001_096_1_16x16_6x6_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TT_096_001_1_16x16_6x6_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TT_001_001_1_16x16_6x6_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TT_096_096_1_16x16_6x6_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TT_096_096_1_16x16_6x6_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TT_001_096_1_16x16_6x6_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TT_096_001_1_16x16_6x6_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_1_16x16_6x6_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 6;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 24) {
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TT_128_064_8_16x16_8x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TT_001_064_8_16x16_8x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TT_128_001_8_16x16_8x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TT_001_001_8_16x16_8x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TT_128_064_8_16x16_8x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_128_064_8_16x16_8x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TT_001_064_8_16x16_8x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TT_128_001_8_16x16_8x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TT_001_001_8_16x16_8x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TT_128_064_8_16x16_8x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TT_128_064_8_16x16_8x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TT_001_064_8_16x16_8x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TT_128_001_8_16x16_8x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_8_16x16_8x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%128 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TT_128_064_1_16x16_8x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TT_001_064_1_16x16_8x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TT_128_001_1_16x16_8x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TT_001_001_1_16x16_8x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TT_128_064_1_16x16_8x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_128_064_1_16x16_8x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TT_001_064_1_16x16_8x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TT_128_001_1_16x16_8x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TT_001_001_1_16x16_8x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TT_128_064_1_16x16_8x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TT_128_064_1_16x16_8x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TT_001_064_1_16x16_8x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TT_128_001_1_16x16_8x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_1_16x16_8x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 8;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 16) {
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TT_096_064_8_16x16_6x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TT_001_064_8_16x16_6x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TT_096_001_8_16x16_6x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TT_001_001_8_16x16_6x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TT_096_064_8_16x16_6x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_096_064_8_16x16_6x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TT_001_064_8_16x16_6x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TT_096_001_8_16x16_6x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TT_001_001_8_16x16_6x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TT_096_064_8_16x16_6x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TT_096_064_8_16x16_6x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TT_001_064_8_16x16_6x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TT_096_001_8_16x16_6x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_8_16x16_6x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%96 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TT_096_064_1_16x16_6x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TT_001_064_1_16x16_6x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TT_096_001_1_16x16_6x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TT_001_001_1_16x16_6x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TT_096_064_1_16x16_6x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_096_064_1_16x16_6x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TT_001_064_1_16x16_6x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TT_096_001_1_16x16_6x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TT_001_001_1_16x16_6x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TT_096_064_1_16x16_6x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TT_096_064_1_16x16_6x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TT_001_064_1_16x16_6x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TT_096_001_1_16x16_6x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_1_16x16_6x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 6;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 8) {
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TT_064_064_8_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TT_001_064_8_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TT_064_001_8_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TT_001_001_8_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TT_064_064_8_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_064_064_8_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TT_001_064_8_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TT_064_001_8_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TT_001_001_8_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TT_064_064_8_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TT_064_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TT_001_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TT_064_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TT_064_064_1_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TT_001_064_1_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TT_064_001_1_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TT_001_001_1_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TT_064_064_1_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_064_064_1_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TT_001_064_1_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TT_064_001_1_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TT_001_001_1_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TT_064_064_1_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TT_064_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TT_001_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TT_064_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TT_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TT_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TT_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TT_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TT_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TT_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TT_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TT_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TT_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TT_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TT_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TT_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TT_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TT_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TT_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TT_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TT_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TT_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TT_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TT_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TT_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TT_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TT_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TT_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TT_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TT_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TT_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TT_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TT_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TT_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TT_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TT_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TT_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TT_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TT_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TT_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TT_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TT_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TT_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TT_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TT_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TT_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TT_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TT_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TT_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TT_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TT_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TT_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = dgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TT_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TT_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TT_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TT_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TT_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TT_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TT_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TT_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = dgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = dgemm_TT_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = dgemm_TT_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = dgemm_TT_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = dgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = dgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = dgemm_TT_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = dgemm_TT_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = dgemm_TT_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = dgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &dgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &dgemm_TT_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &dgemm_TT_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &dgemm_TT_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NN_064_064_8_16x16_4x4_ColMajor_src;
            *rowKernelSource    = cgemm_NN_001_064_8_16x16_4x4_ColMajor_src;
            *colKernelSource    = cgemm_NN_064_001_8_16x16_4x4_ColMajor_src;
            *cornerKernelSource = cgemm_NN_001_001_8_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = cgemm_NN_064_064_8_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_064_064_8_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = cgemm_NN_001_064_8_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = cgemm_NN_064_001_8_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = cgemm_NN_001_001_8_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = cgemm_NN_064_064_8_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NN_064_064_8_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NN_001_064_8_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &cgemm_NN_064_001_8_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_8_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NN_064_064_1_16x16_4x4_ColMajor_src;
            *rowKernelSource    = cgemm_NN_001_064_1_16x16_4x4_ColMajor_src;
            *colKernelSource    = cgemm_NN_064_001_1_16x16_4x4_ColMajor_src;
            *cornerKernelSource = cgemm_NN_001_001_1_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = cgemm_NN_064_064_1_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_064_064_1_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = cgemm_NN_001_064_1_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = cgemm_NN_064_001_1_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = cgemm_NN_001_001_1_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = cgemm_NN_064_064_1_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NN_064_064_1_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NN_001_064_1_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &cgemm_NN_064_001_1_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_1_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NN_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = cgemm_NN_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = cgemm_NN_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = cgemm_NN_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = cgemm_NN_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_NN_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = cgemm_NN_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_NN_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_NN_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NN_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NN_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_NN_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NN_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = cgemm_NN_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = cgemm_NN_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = cgemm_NN_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = cgemm_NN_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_NN_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = cgemm_NN_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_NN_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_NN_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NN_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NN_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_NN_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NN_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = cgemm_NN_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = cgemm_NN_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = cgemm_NN_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = cgemm_NN_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_NN_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = cgemm_NN_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_NN_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_NN_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NN_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NN_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_NN_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NN_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = cgemm_NN_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = cgemm_NN_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = cgemm_NN_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = cgemm_NN_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_NN_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = cgemm_NN_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_NN_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_NN_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NN_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NN_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_NN_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NN_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = cgemm_NN_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = cgemm_NN_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = cgemm_NN_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = cgemm_NN_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_NN_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = cgemm_NN_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_NN_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_NN_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NN_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NN_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_NN_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NN_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = cgemm_NN_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = cgemm_NN_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = cgemm_NN_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = cgemm_NN_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_NN_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = cgemm_NN_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_NN_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_NN_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NN_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NN_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_NN_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NN_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = cgemm_NN_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = cgemm_NN_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = cgemm_NN_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = cgemm_NN_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_NN_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = cgemm_NN_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_NN_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_NN_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NN_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NN_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_NN_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NN_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = cgemm_NN_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = cgemm_NN_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = cgemm_NN_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = cgemm_NN_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_NN_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = cgemm_NN_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_NN_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_NN_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NN_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NN_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_NN_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NN_064_064_8_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NN_001_064_8_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NN_064_001_8_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NN_001_001_8_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NN_064_064_8_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_064_064_8_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NN_001_064_8_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NN_064_001_8_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NN_001_001_8_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NN_064_064_8_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NN_064_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NN_001_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NN_064_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NN_064_064_1_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NN_001_064_1_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NN_064_001_1_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NN_001_001_1_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NN_064_064_1_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_064_064_1_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NN_001_064_1_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NN_064_001_1_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NN_001_001_1_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NN_064_064_1_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NN_064_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NN_001_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NN_064_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NN_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NN_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NN_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NN_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NN_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NN_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NN_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NN_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NN_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NN_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NN_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NN_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NN_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NN_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NN_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NN_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NN_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NN_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NN_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NN_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NN_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NN_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NN_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NN_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NN_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NN_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NN_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NN_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NN_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NN_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NN_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NN_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NN_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NN_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NN_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NN_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NN_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NN_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NN_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NN_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NN_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NN_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NN_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NN_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NN_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NN_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NN_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NN_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NN_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NN_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NN_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NN_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NN_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NN_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NN_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NN_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NN_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NN_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NN_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NN_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NN_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NN_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NN_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NN_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NN_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NT_064_064_8_16x16_4x4_ColMajor_src;
            *rowKernelSource    = cgemm_NT_001_064_8_16x16_4x4_ColMajor_src;
            *colKernelSource    = cgemm_NT_064_001_8_16x16_4x4_ColMajor_src;
            *cornerKernelSource = cgemm_NT_001_001_8_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = cgemm_NT_064_064_8_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_064_064_8_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = cgemm_NT_001_064_8_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = cgemm_NT_064_001_8_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = cgemm_NT_001_001_8_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = cgemm_NT_064_064_8_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NT_064_064_8_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NT_001_064_8_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &cgemm_NT_064_001_8_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_8_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NT_064_064_1_16x16_4x4_ColMajor_src;
            *rowKernelSource    = cgemm_NT_001_064_1_16x16_4x4_ColMajor_src;
            *colKernelSource    = cgemm_NT_064_001_1_16x16_4x4_ColMajor_src;
            *cornerKernelSource = cgemm_NT_001_001_1_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = cgemm_NT_064_064_1_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_064_064_1_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = cgemm_NT_001_064_1_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = cgemm_NT_064_001_1_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = cgemm_NT_001_001_1_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = cgemm_NT_064_064_1_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NT_064_064_1_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NT_001_064_1_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &cgemm_NT_064_001_1_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_1_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NT_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = cgemm_NT_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = cgemm_NT_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = cgemm_NT_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = cgemm_NT_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_NT_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = cgemm_NT_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_NT_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_NT_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NT_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NT_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_NT_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NT_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = cgemm_NT_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = cgemm_NT_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = cgemm_NT_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = cgemm_NT_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_NT_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = cgemm_NT_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_NT_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_NT_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NT_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NT_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_NT_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NT_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = cgemm_NT_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = cgemm_NT_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = cgemm_NT_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = cgemm_NT_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_NT_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = cgemm_NT_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_NT_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_NT_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NT_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NT_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_NT_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NT_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = cgemm_NT_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = cgemm_NT_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = cgemm_NT_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = cgemm_NT_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_NT_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = cgemm_NT_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_NT_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_NT_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NT_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NT_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_NT_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NT_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = cgemm_NT_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = cgemm_NT_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = cgemm_NT_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = cgemm_NT_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_NT_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = cgemm_NT_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_NT_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_NT_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NT_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NT_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_NT_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NT_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = cgemm_NT_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = cgemm_NT_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = cgemm_NT_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = cgemm_NT_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_NT_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = cgemm_NT_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_NT_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_NT_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NT_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NT_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_NT_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NT_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = cgemm_NT_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = cgemm_NT_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = cgemm_NT_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = cgemm_NT_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_NT_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = cgemm_NT_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_NT_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_NT_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NT_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NT_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_NT_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NT_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = cgemm_NT_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = cgemm_NT_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = cgemm_NT_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = cgemm_NT_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_NT_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = cgemm_NT_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_NT_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_NT_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NT_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NT_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_NT_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NT_064_064_8_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NT_001_064_8_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NT_064_001_8_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NT_001_001_8_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NT_064_064_8_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_064_064_8_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NT_001_064_8_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NT_064_001_8_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NT_001_001_8_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NT_064_064_8_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NT_064_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NT_001_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NT_064_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NT_064_064_1_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NT_001_064_1_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NT_064_001_1_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NT_001_001_1_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NT_064_064_1_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_064_064_1_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NT_001_064_1_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NT_064_001_1_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NT_001_001_1_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NT_064_064_1_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NT_064_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NT_001_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NT_064_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NT_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NT_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NT_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NT_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NT_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NT_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NT_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NT_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NT_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NT_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NT_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NT_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NT_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NT_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NT_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NT_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NT_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NT_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NT_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NT_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NT_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NT_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NT_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NT_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NT_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NT_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NT_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NT_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NT_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NT_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NT_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NT_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NT_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NT_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NT_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NT_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NT_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NT_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NT_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NT_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NT_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NT_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NT_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NT_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NT_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NT_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NT_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NT_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NT_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NT_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NT_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NT_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NT_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NT_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NT_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NT_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NT_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NT_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NT_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NT_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NT_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NT_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NT_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NT_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NT_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NC_064_064_8_16x16_4x4_ColMajor_src;
            *rowKernelSource    = cgemm_NC_001_064_8_16x16_4x4_ColMajor_src;
            *colKernelSource    = cgemm_NC_064_001_8_16x16_4x4_ColMajor_src;
            *cornerKernelSource = cgemm_NC_001_001_8_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = cgemm_NC_064_064_8_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_064_064_8_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = cgemm_NC_001_064_8_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = cgemm_NC_064_001_8_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = cgemm_NC_001_001_8_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = cgemm_NC_064_064_8_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NC_064_064_8_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NC_001_064_8_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &cgemm_NC_064_001_8_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_8_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NC_064_064_1_16x16_4x4_ColMajor_src;
            *rowKernelSource    = cgemm_NC_001_064_1_16x16_4x4_ColMajor_src;
            *colKernelSource    = cgemm_NC_064_001_1_16x16_4x4_ColMajor_src;
            *cornerKernelSource = cgemm_NC_001_001_1_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = cgemm_NC_064_064_1_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_064_064_1_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = cgemm_NC_001_064_1_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = cgemm_NC_064_001_1_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = cgemm_NC_001_001_1_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = cgemm_NC_064_064_1_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NC_064_064_1_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NC_001_064_1_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &cgemm_NC_064_001_1_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_1_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NC_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = cgemm_NC_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = cgemm_NC_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = cgemm_NC_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = cgemm_NC_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_NC_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = cgemm_NC_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_NC_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_NC_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NC_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NC_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_NC_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NC_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = cgemm_NC_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = cgemm_NC_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = cgemm_NC_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = cgemm_NC_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_NC_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = cgemm_NC_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_NC_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_NC_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NC_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NC_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_NC_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NC_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = cgemm_NC_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = cgemm_NC_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = cgemm_NC_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = cgemm_NC_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_NC_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = cgemm_NC_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_NC_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_NC_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NC_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NC_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_NC_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NC_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = cgemm_NC_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = cgemm_NC_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = cgemm_NC_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = cgemm_NC_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_NC_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = cgemm_NC_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_NC_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_NC_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NC_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NC_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_NC_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NC_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = cgemm_NC_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = cgemm_NC_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = cgemm_NC_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = cgemm_NC_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_NC_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = cgemm_NC_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_NC_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_NC_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NC_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NC_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_NC_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NC_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = cgemm_NC_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = cgemm_NC_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = cgemm_NC_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = cgemm_NC_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_NC_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = cgemm_NC_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_NC_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_NC_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NC_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NC_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_NC_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NC_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = cgemm_NC_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = cgemm_NC_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = cgemm_NC_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = cgemm_NC_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_NC_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = cgemm_NC_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_NC_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_NC_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NC_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NC_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_NC_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NC_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = cgemm_NC_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = cgemm_NC_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = cgemm_NC_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = cgemm_NC_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_NC_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = cgemm_NC_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_NC_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_NC_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_NC_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_NC_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_NC_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NC_064_064_8_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NC_001_064_8_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NC_064_001_8_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NC_001_001_8_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NC_064_064_8_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_064_064_8_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NC_001_064_8_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NC_064_001_8_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NC_001_001_8_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NC_064_064_8_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NC_064_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NC_001_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NC_064_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NC_064_064_1_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NC_001_064_1_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NC_064_001_1_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NC_001_001_1_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NC_064_064_1_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_064_064_1_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NC_001_064_1_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NC_064_001_1_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NC_001_001_1_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NC_064_064_1_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NC_064_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NC_001_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NC_064_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NC_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NC_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NC_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NC_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NC_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NC_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NC_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NC_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NC_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NC_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NC_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NC_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NC_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NC_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NC_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NC_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NC_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NC_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NC_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NC_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NC_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NC_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NC_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NC_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NC_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NC_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NC_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NC_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NC_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NC_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NC_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NC_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NC_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NC_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NC_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NC_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NC_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NC_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NC_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NC_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NC_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NC_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NC_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NC_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NC_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NC_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NC_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NC_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NC_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NC_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NC_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NC_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NC_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NC_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NC_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NC_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NC_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NC_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NC_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NC_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NC_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NC_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NC_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NC_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NC_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NC_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NC_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NC_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NC_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NC_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NC_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NC_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_NC_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NC_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NC_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NC_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NC_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NC_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NC_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NC_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NC_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NC_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NC_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NC_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_NC_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_NC_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_NC_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_NC_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_NC_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_NC_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_NC_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_NC_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_NC_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_NC_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_NC_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_NC_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_NC_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_NC_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TN_064_064_8_16x16_4x4_ColMajor_src;
            *rowKernelSource    = cgemm_TN_001_064_8_16x16_4x4_ColMajor_src;
            *colKernelSource    = cgemm_TN_064_001_8_16x16_4x4_ColMajor_src;
            *cornerKernelSource = cgemm_TN_001_001_8_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = cgemm_TN_064_064_8_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_064_064_8_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = cgemm_TN_001_064_8_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = cgemm_TN_064_001_8_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = cgemm_TN_001_001_8_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = cgemm_TN_064_064_8_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TN_064_064_8_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TN_001_064_8_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &cgemm_TN_064_001_8_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_8_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TN_064_064_1_16x16_4x4_ColMajor_src;
            *rowKernelSource    = cgemm_TN_001_064_1_16x16_4x4_ColMajor_src;
            *colKernelSource    = cgemm_TN_064_001_1_16x16_4x4_ColMajor_src;
            *cornerKernelSource = cgemm_TN_001_001_1_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = cgemm_TN_064_064_1_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_064_064_1_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = cgemm_TN_001_064_1_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = cgemm_TN_064_001_1_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = cgemm_TN_001_001_1_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = cgemm_TN_064_064_1_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TN_064_064_1_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TN_001_064_1_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &cgemm_TN_064_001_1_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_1_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TN_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = cgemm_TN_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = cgemm_TN_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = cgemm_TN_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = cgemm_TN_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_TN_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = cgemm_TN_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_TN_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_TN_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TN_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TN_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_TN_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TN_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = cgemm_TN_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = cgemm_TN_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = cgemm_TN_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = cgemm_TN_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_TN_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = cgemm_TN_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_TN_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_TN_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TN_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TN_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_TN_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TN_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = cgemm_TN_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = cgemm_TN_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = cgemm_TN_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = cgemm_TN_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_TN_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = cgemm_TN_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_TN_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_TN_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TN_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TN_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_TN_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TN_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = cgemm_TN_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = cgemm_TN_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = cgemm_TN_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = cgemm_TN_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_TN_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = cgemm_TN_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_TN_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_TN_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TN_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TN_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_TN_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TN_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = cgemm_TN_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = cgemm_TN_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = cgemm_TN_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = cgemm_TN_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_TN_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = cgemm_TN_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_TN_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_TN_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TN_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TN_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_TN_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TN_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = cgemm_TN_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = cgemm_TN_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = cgemm_TN_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = cgemm_TN_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_TN_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = cgemm_TN_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_TN_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_TN_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TN_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TN_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_TN_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TN_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = cgemm_TN_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = cgemm_TN_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = cgemm_TN_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = cgemm_TN_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_TN_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = cgemm_TN_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_TN_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_TN_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TN_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TN_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_TN_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TN_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = cgemm_TN_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = cgemm_TN_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = cgemm_TN_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = cgemm_TN_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_TN_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = cgemm_TN_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_TN_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_TN_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TN_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TN_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_TN_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TN_064_064_8_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TN_001_064_8_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TN_064_001_8_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TN_001_001_8_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TN_064_064_8_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_064_064_8_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TN_001_064_8_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TN_064_001_8_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TN_001_001_8_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TN_064_064_8_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TN_064_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TN_001_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TN_064_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TN_064_064_1_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TN_001_064_1_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TN_064_001_1_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TN_001_001_1_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TN_064_064_1_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_064_064_1_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TN_001_064_1_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TN_064_001_1_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TN_001_001_1_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TN_064_064_1_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TN_064_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TN_001_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TN_064_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TN_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TN_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TN_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TN_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TN_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TN_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TN_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TN_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TN_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TN_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TN_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TN_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TN_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TN_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TN_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TN_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TN_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TN_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TN_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TN_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TN_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TN_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TN_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TN_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TN_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TN_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TN_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TN_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TN_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TN_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TN_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TN_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TN_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TN_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TN_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TN_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TN_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TN_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TN_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TN_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TN_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TN_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TN_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TN_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TN_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TN_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TN_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TN_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TN_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TN_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TN_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TN_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TN_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TN_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TN_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TN_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TN_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TN_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TN_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TN_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TN_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TN_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TN_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TN_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TN_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TT_064_064_8_16x16_4x4_ColMajor_src;
            *rowKernelSource    = cgemm_TT_001_064_8_16x16_4x4_ColMajor_src;
            *colKernelSource    = cgemm_TT_064_001_8_16x16_4x4_ColMajor_src;
            *cornerKernelSource = cgemm_TT_001_001_8_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = cgemm_TT_064_064_8_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_064_064_8_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = cgemm_TT_001_064_8_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = cgemm_TT_064_001_8_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = cgemm_TT_001_001_8_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = cgemm_TT_064_064_8_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TT_064_064_8_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TT_001_064_8_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &cgemm_TT_064_001_8_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_8_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TT_064_064_1_16x16_4x4_ColMajor_src;
            *rowKernelSource    = cgemm_TT_001_064_1_16x16_4x4_ColMajor_src;
            *colKernelSource    = cgemm_TT_064_001_1_16x16_4x4_ColMajor_src;
            *cornerKernelSource = cgemm_TT_001_001_1_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = cgemm_TT_064_064_1_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_064_064_1_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = cgemm_TT_001_064_1_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = cgemm_TT_064_001_1_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = cgemm_TT_001_001_1_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = cgemm_TT_064_064_1_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TT_064_064_1_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TT_001_064_1_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &cgemm_TT_064_001_1_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_1_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TT_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = cgemm_TT_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = cgemm_TT_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = cgemm_TT_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = cgemm_TT_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_TT_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = cgemm_TT_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_TT_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_TT_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TT_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TT_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_TT_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TT_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = cgemm_TT_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = cgemm_TT_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = cgemm_TT_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = cgemm_TT_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_TT_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = cgemm_TT_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_TT_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_TT_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TT_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TT_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_TT_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TT_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = cgemm_TT_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = cgemm_TT_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = cgemm_TT_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = cgemm_TT_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_TT_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = cgemm_TT_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_TT_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_TT_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TT_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TT_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_TT_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TT_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = cgemm_TT_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = cgemm_TT_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = cgemm_TT_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = cgemm_TT_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_TT_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = cgemm_TT_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_TT_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_TT_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TT_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TT_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_TT_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TT_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = cgemm_TT_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = cgemm_TT_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = cgemm_TT_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = cgemm_TT_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_TT_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = cgemm_TT_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_TT_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_TT_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TT_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TT_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_TT_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TT_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = cgemm_TT_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = cgemm_TT_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = cgemm_TT_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = cgemm_TT_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_TT_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = cgemm_TT_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_TT_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_TT_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TT_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TT_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_TT_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TT_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = cgemm_TT_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = cgemm_TT_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = cgemm_TT_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = cgemm_TT_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_TT_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = cgemm_TT_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_TT_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_TT_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TT_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TT_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_TT_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TT_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = cgemm_TT_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = cgemm_TT_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = cgemm_TT_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = cgemm_TT_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_TT_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = cgemm_TT_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_TT_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_TT_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TT_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TT_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_TT_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TT_064_064_8_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TT_001_064_8_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TT_064_001_8_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TT_001_001_8_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TT_064_064_8_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_064_064_8_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TT_001_064_8_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TT_064_001_8_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TT_001_001_8_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TT_064_064_8_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TT_064_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TT_001_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TT_064_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TT_064_064_1_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TT_001_064_1_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TT_064_001_1_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TT_001_001_1_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TT_064_064_1_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_064_064_1_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TT_001_064_1_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TT_064_001_1_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TT_001_001_1_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TT_064_064_1_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TT_064_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TT_001_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TT_064_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TT_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TT_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TT_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TT_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TT_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TT_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TT_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TT_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TT_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TT_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TT_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TT_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TT_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TT_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TT_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TT_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TT_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TT_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TT_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TT_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TT_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TT_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TT_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TT_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TT_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TT_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TT_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TT_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TT_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TT_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TT_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TT_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TT_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TT_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TT_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TT_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TT_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TT_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TT_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TT_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TT_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TT_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TT_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TT_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TT_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TT_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TT_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TT_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TT_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TT_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TT_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TT_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TT_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TT_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TT_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TT_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TT_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TT_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TT_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TT_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TT_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TT_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TT_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TT_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TT_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TC_064_064_8_16x16_4x4_ColMajor_src;
            *rowKernelSource    = cgemm_TC_001_064_8_16x16_4x4_ColMajor_src;
            *colKernelSource    = cgemm_TC_064_001_8_16x16_4x4_ColMajor_src;
            *cornerKernelSource = cgemm_TC_001_001_8_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = cgemm_TC_064_064_8_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_064_064_8_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = cgemm_TC_001_064_8_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = cgemm_TC_064_001_8_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = cgemm_TC_001_001_8_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = cgemm_TC_064_064_8_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TC_064_064_8_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TC_001_064_8_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &cgemm_TC_064_001_8_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_8_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TC_064_064_1_16x16_4x4_ColMajor_src;
            *rowKernelSource    = cgemm_TC_001_064_1_16x16_4x4_ColMajor_src;
            *colKernelSource    = cgemm_TC_064_001_1_16x16_4x4_ColMajor_src;
            *cornerKernelSource = cgemm_TC_001_001_1_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = cgemm_TC_064_064_1_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_064_064_1_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = cgemm_TC_001_064_1_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = cgemm_TC_064_001_1_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = cgemm_TC_001_001_1_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = cgemm_TC_064_064_1_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TC_064_064_1_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TC_001_064_1_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &cgemm_TC_064_001_1_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_1_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TC_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = cgemm_TC_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = cgemm_TC_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = cgemm_TC_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = cgemm_TC_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_TC_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = cgemm_TC_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_TC_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_TC_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TC_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TC_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_TC_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TC_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = cgemm_TC_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = cgemm_TC_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = cgemm_TC_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = cgemm_TC_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_TC_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = cgemm_TC_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_TC_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_TC_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TC_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TC_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_TC_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TC_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = cgemm_TC_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = cgemm_TC_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = cgemm_TC_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = cgemm_TC_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_TC_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = cgemm_TC_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_TC_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_TC_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TC_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TC_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_TC_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TC_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = cgemm_TC_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = cgemm_TC_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = cgemm_TC_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = cgemm_TC_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_TC_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = cgemm_TC_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_TC_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_TC_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TC_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TC_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_TC_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TC_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = cgemm_TC_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = cgemm_TC_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = cgemm_TC_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = cgemm_TC_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_TC_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = cgemm_TC_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_TC_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_TC_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TC_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TC_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_TC_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TC_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = cgemm_TC_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = cgemm_TC_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = cgemm_TC_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = cgemm_TC_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_TC_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = cgemm_TC_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_TC_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_TC_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TC_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TC_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_TC_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TC_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = cgemm_TC_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = cgemm_TC_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = cgemm_TC_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = cgemm_TC_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_TC_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = cgemm_TC_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_TC_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_TC_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TC_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TC_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_TC_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TC_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = cgemm_TC_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = cgemm_TC_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = cgemm_TC_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = cgemm_TC_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_TC_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = cgemm_TC_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_TC_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_TC_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_TC_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_TC_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_TC_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TC_064_064_8_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TC_001_064_8_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TC_064_001_8_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TC_001_001_8_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TC_064_064_8_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_064_064_8_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TC_001_064_8_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TC_064_001_8_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TC_001_001_8_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TC_064_064_8_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TC_064_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TC_001_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TC_064_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TC_064_064_1_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TC_001_064_1_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TC_064_001_1_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TC_001_001_1_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TC_064_064_1_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_064_064_1_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TC_001_064_1_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TC_064_001_1_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TC_001_001_1_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TC_064_064_1_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TC_064_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TC_001_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TC_064_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TC_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TC_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TC_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TC_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TC_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TC_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TC_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TC_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TC_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TC_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TC_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TC_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TC_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TC_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TC_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TC_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TC_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TC_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TC_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TC_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TC_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TC_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TC_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TC_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TC_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TC_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TC_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TC_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TC_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TC_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TC_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TC_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TC_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TC_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TC_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TC_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TC_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TC_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TC_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TC_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TC_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TC_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TC_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TC_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TC_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TC_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TC_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TC_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TC_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TC_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TC_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TC_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TC_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TC_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TC_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TC_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TC_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TC_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TC_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TC_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TC_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TC_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TC_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TC_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TC_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TC_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TC_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TC_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TC_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TC_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TC_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TC_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_TC_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TC_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TC_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TC_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TC_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TC_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TC_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TC_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TC_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TC_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TC_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TC_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_TC_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_TC_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_TC_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_TC_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_TC_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_TC_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_TC_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_TC_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_TC_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_TC_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_TC_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_TC_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_TC_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_TC_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CN_064_064_8_16x16_4x4_ColMajor_src;
            *rowKernelSource    = cgemm_CN_001_064_8_16x16_4x4_ColMajor_src;
            *colKernelSource    = cgemm_CN_064_001_8_16x16_4x4_ColMajor_src;
            *cornerKernelSource = cgemm_CN_001_001_8_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = cgemm_CN_064_064_8_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_064_064_8_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = cgemm_CN_001_064_8_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = cgemm_CN_064_001_8_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = cgemm_CN_001_001_8_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = cgemm_CN_064_064_8_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CN_064_064_8_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CN_001_064_8_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &cgemm_CN_064_001_8_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_8_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CN_064_064_1_16x16_4x4_ColMajor_src;
            *rowKernelSource    = cgemm_CN_001_064_1_16x16_4x4_ColMajor_src;
            *colKernelSource    = cgemm_CN_064_001_1_16x16_4x4_ColMajor_src;
            *cornerKernelSource = cgemm_CN_001_001_1_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = cgemm_CN_064_064_1_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_064_064_1_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = cgemm_CN_001_064_1_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = cgemm_CN_064_001_1_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = cgemm_CN_001_001_1_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = cgemm_CN_064_064_1_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CN_064_064_1_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CN_001_064_1_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &cgemm_CN_064_001_1_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_1_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CN_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = cgemm_CN_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = cgemm_CN_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = cgemm_CN_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = cgemm_CN_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_CN_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = cgemm_CN_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_CN_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_CN_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CN_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CN_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_CN_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CN_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = cgemm_CN_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = cgemm_CN_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = cgemm_CN_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = cgemm_CN_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_CN_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = cgemm_CN_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_CN_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_CN_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CN_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CN_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_CN_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CN_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = cgemm_CN_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = cgemm_CN_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = cgemm_CN_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = cgemm_CN_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_CN_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = cgemm_CN_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_CN_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_CN_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CN_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CN_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_CN_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CN_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = cgemm_CN_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = cgemm_CN_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = cgemm_CN_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = cgemm_CN_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_CN_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = cgemm_CN_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_CN_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_CN_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CN_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CN_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_CN_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CN_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = cgemm_CN_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = cgemm_CN_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = cgemm_CN_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = cgemm_CN_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_CN_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = cgemm_CN_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_CN_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_CN_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CN_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CN_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_CN_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CN_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = cgemm_CN_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = cgemm_CN_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = cgemm_CN_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = cgemm_CN_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_CN_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = cgemm_CN_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_CN_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_CN_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CN_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CN_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_CN_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CN_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = cgemm_CN_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = cgemm_CN_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = cgemm_CN_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = cgemm_CN_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_CN_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = cgemm_CN_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_CN_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_CN_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CN_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CN_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_CN_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CN_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = cgemm_CN_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = cgemm_CN_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = cgemm_CN_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = cgemm_CN_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_CN_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = cgemm_CN_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_CN_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_CN_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CN_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CN_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_CN_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CN_064_064_8_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CN_001_064_8_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CN_064_001_8_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CN_001_001_8_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CN_064_064_8_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_064_064_8_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CN_001_064_8_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CN_064_001_8_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CN_001_001_8_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CN_064_064_8_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CN_064_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CN_001_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CN_064_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CN_064_064_1_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CN_001_064_1_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CN_064_001_1_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CN_001_001_1_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CN_064_064_1_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_064_064_1_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CN_001_064_1_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CN_064_001_1_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CN_001_001_1_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CN_064_064_1_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CN_064_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CN_001_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CN_064_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CN_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CN_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CN_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CN_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CN_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CN_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CN_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CN_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CN_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CN_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CN_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CN_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CN_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CN_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CN_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CN_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CN_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CN_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CN_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CN_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CN_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CN_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CN_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CN_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CN_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CN_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CN_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CN_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CN_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CN_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CN_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CN_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CN_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CN_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CN_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CN_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CN_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CN_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CN_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CN_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CN_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CN_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CN_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CN_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CN_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CN_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CN_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CN_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CN_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CN_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CN_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CN_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CN_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CN_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CN_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CN_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CN_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CN_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CN_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CN_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CN_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CN_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CN_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CN_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CN_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CN_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CN_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CN_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CN_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CN_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CN_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CN_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CN_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CN_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CN_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CN_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CN_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CN_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CN_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CN_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CN_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CN_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CN_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CN_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CN_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CN_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CN_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CN_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CN_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CN_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CN_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CN_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CN_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CN_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CN_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CN_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CN_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CN_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CT_064_064_8_16x16_4x4_ColMajor_src;
            *rowKernelSource    = cgemm_CT_001_064_8_16x16_4x4_ColMajor_src;
            *colKernelSource    = cgemm_CT_064_001_8_16x16_4x4_ColMajor_src;
            *cornerKernelSource = cgemm_CT_001_001_8_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = cgemm_CT_064_064_8_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_064_064_8_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = cgemm_CT_001_064_8_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = cgemm_CT_064_001_8_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = cgemm_CT_001_001_8_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = cgemm_CT_064_064_8_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CT_064_064_8_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CT_001_064_8_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &cgemm_CT_064_001_8_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_8_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CT_064_064_1_16x16_4x4_ColMajor_src;
            *rowKernelSource    = cgemm_CT_001_064_1_16x16_4x4_ColMajor_src;
            *colKernelSource    = cgemm_CT_064_001_1_16x16_4x4_ColMajor_src;
            *cornerKernelSource = cgemm_CT_001_001_1_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = cgemm_CT_064_064_1_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_064_064_1_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = cgemm_CT_001_064_1_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = cgemm_CT_064_001_1_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = cgemm_CT_001_001_1_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = cgemm_CT_064_064_1_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CT_064_064_1_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CT_001_064_1_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &cgemm_CT_064_001_1_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_1_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CT_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = cgemm_CT_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = cgemm_CT_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = cgemm_CT_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = cgemm_CT_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_CT_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = cgemm_CT_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_CT_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_CT_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CT_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CT_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_CT_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CT_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = cgemm_CT_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = cgemm_CT_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = cgemm_CT_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = cgemm_CT_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_CT_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = cgemm_CT_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_CT_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_CT_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CT_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CT_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_CT_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CT_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = cgemm_CT_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = cgemm_CT_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = cgemm_CT_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = cgemm_CT_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_CT_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = cgemm_CT_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_CT_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_CT_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CT_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CT_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_CT_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CT_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = cgemm_CT_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = cgemm_CT_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = cgemm_CT_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = cgemm_CT_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_CT_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = cgemm_CT_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_CT_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_CT_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CT_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CT_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_CT_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CT_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = cgemm_CT_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = cgemm_CT_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = cgemm_CT_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = cgemm_CT_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_CT_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = cgemm_CT_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_CT_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_CT_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CT_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CT_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_CT_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CT_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = cgemm_CT_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = cgemm_CT_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = cgemm_CT_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = cgemm_CT_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_CT_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = cgemm_CT_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_CT_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_CT_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CT_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CT_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_CT_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CT_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = cgemm_CT_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = cgemm_CT_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = cgemm_CT_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = cgemm_CT_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_CT_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = cgemm_CT_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_CT_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_CT_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CT_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CT_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_CT_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CT_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = cgemm_CT_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = cgemm_CT_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = cgemm_CT_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = cgemm_CT_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_CT_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = cgemm_CT_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_CT_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_CT_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CT_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CT_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_CT_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CT_064_064_8_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CT_001_064_8_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CT_064_001_8_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CT_001_001_8_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CT_064_064_8_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_064_064_8_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CT_001_064_8_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CT_064_001_8_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CT_001_001_8_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CT_064_064_8_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CT_064_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CT_001_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CT_064_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CT_064_064_1_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CT_001_064_1_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CT_064_001_1_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CT_001_001_1_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CT_064_064_1_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_064_064_1_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CT_001_064_1_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CT_064_001_1_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CT_001_001_1_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CT_064_064_1_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CT_064_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CT_001_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CT_064_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CT_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CT_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CT_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CT_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CT_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CT_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CT_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CT_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CT_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CT_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CT_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CT_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CT_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CT_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CT_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CT_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CT_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CT_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CT_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CT_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CT_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CT_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CT_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CT_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CT_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CT_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CT_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CT_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CT_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CT_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CT_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CT_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CT_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CT_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CT_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CT_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CT_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CT_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CT_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CT_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CT_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CT_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CT_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CT_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CT_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CT_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CT_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CT_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CT_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CT_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CT_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CT_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CT_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CT_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CT_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CT_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CT_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CT_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CT_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CT_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CT_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CT_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CT_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CT_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CT_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CT_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CT_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CT_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CT_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CT_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CT_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CT_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CT_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CT_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CT_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CT_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CT_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CT_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CT_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CT_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CT_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CT_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CT_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CT_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CT_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CT_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CT_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CT_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CT_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CT_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CT_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CT_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CT_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CT_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CT_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CT_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CT_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CT_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CC_064_064_8_16x16_4x4_ColMajor_src;
            *rowKernelSource    = cgemm_CC_001_064_8_16x16_4x4_ColMajor_src;
            *colKernelSource    = cgemm_CC_064_001_8_16x16_4x4_ColMajor_src;
            *cornerKernelSource = cgemm_CC_001_001_8_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = cgemm_CC_064_064_8_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_064_064_8_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = cgemm_CC_001_064_8_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = cgemm_CC_064_001_8_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = cgemm_CC_001_001_8_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = cgemm_CC_064_064_8_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CC_064_064_8_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CC_001_064_8_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &cgemm_CC_064_001_8_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_8_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CC_064_064_1_16x16_4x4_ColMajor_src;
            *rowKernelSource    = cgemm_CC_001_064_1_16x16_4x4_ColMajor_src;
            *colKernelSource    = cgemm_CC_064_001_1_16x16_4x4_ColMajor_src;
            *cornerKernelSource = cgemm_CC_001_001_1_16x16_4x4_ColMajor_src;
            *sourceBuildOptions = cgemm_CC_064_064_1_16x16_4x4_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_064_064_1_16x16_4x4_ColMajor_bin;
            *rowKernelBinary    = cgemm_CC_001_064_1_16x16_4x4_ColMajor_bin;
            *colKernelBinary    = cgemm_CC_064_001_1_16x16_4x4_ColMajor_bin;
            *cornerKernelBinary = cgemm_CC_001_001_1_16x16_4x4_ColMajor_bin;
            *binaryBuildOptions = cgemm_CC_064_064_1_16x16_4x4_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CC_064_064_1_16x16_4x4_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CC_001_064_1_16x16_4x4_ColMajor_clKernel;
            *colClKernel        = &cgemm_CC_064_001_1_16x16_4x4_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_1_16x16_4x4_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CC_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = cgemm_CC_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = cgemm_CC_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = cgemm_CC_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = cgemm_CC_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_CC_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = cgemm_CC_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_CC_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_CC_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CC_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CC_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_CC_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CC_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = cgemm_CC_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = cgemm_CC_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = cgemm_CC_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = cgemm_CC_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_CC_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = cgemm_CC_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_CC_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_CC_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CC_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CC_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_CC_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CC_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = cgemm_CC_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = cgemm_CC_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = cgemm_CC_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = cgemm_CC_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_CC_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = cgemm_CC_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_CC_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_CC_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CC_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CC_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_CC_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CC_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = cgemm_CC_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = cgemm_CC_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = cgemm_CC_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = cgemm_CC_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = cgemm_CC_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = cgemm_CC_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = cgemm_CC_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = cgemm_CC_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CC_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CC_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &cgemm_CC_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CC_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = cgemm_CC_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = cgemm_CC_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = cgemm_CC_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = cgemm_CC_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_CC_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = cgemm_CC_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_CC_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_CC_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CC_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CC_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_CC_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CC_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = cgemm_CC_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = cgemm_CC_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = cgemm_CC_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = cgemm_CC_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_CC_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = cgemm_CC_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_CC_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_CC_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CC_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CC_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_CC_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CC_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = cgemm_CC_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = cgemm_CC_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = cgemm_CC_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = cgemm_CC_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_CC_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = cgemm_CC_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_CC_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_CC_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CC_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CC_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_CC_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CC_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = cgemm_CC_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = cgemm_CC_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = cgemm_CC_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = cgemm_CC_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = cgemm_CC_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = cgemm_CC_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = cgemm_CC_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = cgemm_CC_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &cgemm_CC_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &cgemm_CC_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &cgemm_CC_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CC_064_064_8_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CC_001_064_8_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CC_064_001_8_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CC_001_001_8_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CC_064_064_8_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_064_064_8_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CC_001_064_8_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CC_064_001_8_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CC_001_001_8_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CC_064_064_8_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CC_064_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CC_001_064_8_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CC_064_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_8_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%64 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CC_064_064_1_16x16_4x4_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CC_001_064_1_16x16_4x4_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CC_064_001_1_16x16_4x4_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CC_001_001_1_16x16_4x4_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CC_064_064_1_16x16_4x4_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_064_064_1_16x16_4x4_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CC_001_064_1_16x16_4x4_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CC_064_001_1_16x16_4x4_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CC_001_001_1_16x16_4x4_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CC_064_064_1_16x16_4x4_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CC_064_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CC_001_064_1_16x16_4x4_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CC_064_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_1_16x16_4x4_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 4;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 4) {
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CC_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CC_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CC_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CC_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CC_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CC_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CC_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CC_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CC_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CC_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CC_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CC_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CC_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CC_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CC_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CC_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CC_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CC_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CC_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CC_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CC_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CC_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CC_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CC_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CC_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CC_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CC_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CC_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CC_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CC_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CC_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CC_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CC_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CC_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CC_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CC_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CC_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CC_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CC_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CC_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CC_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CC_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CC_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CC_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CC_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CC_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CC_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CC_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CC_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CC_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CC_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CC_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CC_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CC_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CC_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CC_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CC_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CC_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CC_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CC_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CC_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CC_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CC_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CC_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CC_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CC_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CC_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CC_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CC_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CC_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CC_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CC_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = cgemm_CC_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CC_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CC_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CC_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CC_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CC_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CC_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CC_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CC_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CC_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CC_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CC_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = cgemm_CC_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = cgemm_CC_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = cgemm_CC_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = cgemm_CC_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = cgemm_CC_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = cgemm_CC_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = cgemm_CC_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = cgemm_CC_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = cgemm_CC_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = cgemm_CC_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &cgemm_CC_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &cgemm_CC_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &cgemm_CC_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &cgemm_CC_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NN_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = zgemm_NN_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = zgemm_NN_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = zgemm_NN_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = zgemm_NN_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NN_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_NN_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = zgemm_NN_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_NN_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_NN_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NN_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NN_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_NN_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NN_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NN_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = zgemm_NN_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = zgemm_NN_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = zgemm_NN_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = zgemm_NN_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NN_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_NN_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = zgemm_NN_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_NN_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_NN_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NN_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NN_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_NN_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NN_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NN_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = zgemm_NN_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = zgemm_NN_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = zgemm_NN_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = zgemm_NN_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NN_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_NN_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = zgemm_NN_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_NN_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_NN_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NN_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NN_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_NN_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NN_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NN_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = zgemm_NN_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = zgemm_NN_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = zgemm_NN_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = zgemm_NN_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NN_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_NN_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = zgemm_NN_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_NN_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_NN_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NN_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NN_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_NN_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NN_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NN_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = zgemm_NN_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = zgemm_NN_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = zgemm_NN_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = zgemm_NN_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NN_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_NN_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = zgemm_NN_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_NN_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_NN_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NN_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NN_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_NN_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NN_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NN_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = zgemm_NN_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = zgemm_NN_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = zgemm_NN_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = zgemm_NN_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NN_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_NN_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = zgemm_NN_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_NN_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_NN_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NN_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NN_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_NN_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NN_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NN_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = zgemm_NN_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = zgemm_NN_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = zgemm_NN_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = zgemm_NN_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NN_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_NN_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = zgemm_NN_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_NN_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_NN_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NN_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NN_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_NN_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NN_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NN_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = zgemm_NN_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = zgemm_NN_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = zgemm_NN_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = zgemm_NN_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NN_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_NN_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = zgemm_NN_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_NN_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_NN_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NN_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NN_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_NN_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NN_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NN_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NN_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NN_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NN_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NN_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NN_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NN_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NN_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NN_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NN_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NN_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NN_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NN_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NN_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NN_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NN_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NN_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NN_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NN_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NN_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NN_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NN_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NN_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NN_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NN_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NN_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NN_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NN_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NN_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NN_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NN_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NN_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NN_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NN_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NN_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NN_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NN_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NN_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NN_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NN_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NN_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NN_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NN_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NN_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NN_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NN_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NN_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NN_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NN_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NN_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NN_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NN_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NN_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NN_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NN_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NN_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NN_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NN_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NN_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NN_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NN_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NN_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NN_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NN_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NN_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NN_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NN_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NN_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NN_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NN_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NN_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NN_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NN_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NN_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NN_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NN_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NN_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NN_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NN_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NN_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NT_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = zgemm_NT_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = zgemm_NT_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = zgemm_NT_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = zgemm_NT_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NT_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_NT_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = zgemm_NT_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_NT_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_NT_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NT_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NT_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_NT_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NT_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NT_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = zgemm_NT_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = zgemm_NT_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = zgemm_NT_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = zgemm_NT_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NT_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_NT_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = zgemm_NT_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_NT_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_NT_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NT_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NT_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_NT_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NT_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NT_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = zgemm_NT_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = zgemm_NT_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = zgemm_NT_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = zgemm_NT_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NT_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_NT_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = zgemm_NT_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_NT_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_NT_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NT_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NT_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_NT_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NT_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NT_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = zgemm_NT_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = zgemm_NT_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = zgemm_NT_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = zgemm_NT_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NT_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_NT_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = zgemm_NT_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_NT_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_NT_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NT_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NT_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_NT_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NT_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NT_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = zgemm_NT_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = zgemm_NT_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = zgemm_NT_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = zgemm_NT_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NT_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_NT_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = zgemm_NT_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_NT_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_NT_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NT_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NT_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_NT_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NT_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NT_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = zgemm_NT_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = zgemm_NT_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = zgemm_NT_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = zgemm_NT_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NT_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_NT_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = zgemm_NT_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_NT_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_NT_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NT_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NT_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_NT_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NT_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NT_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = zgemm_NT_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = zgemm_NT_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = zgemm_NT_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = zgemm_NT_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NT_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_NT_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = zgemm_NT_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_NT_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_NT_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NT_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NT_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_NT_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NT_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NT_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = zgemm_NT_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = zgemm_NT_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = zgemm_NT_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = zgemm_NT_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NT_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_NT_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = zgemm_NT_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_NT_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_NT_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NT_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NT_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_NT_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NT_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NT_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NT_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NT_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NT_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NT_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NT_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NT_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NT_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NT_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NT_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NT_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NT_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NT_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NT_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NT_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NT_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NT_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NT_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NT_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NT_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NT_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NT_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NT_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NT_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NT_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NT_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NT_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NT_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NT_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NT_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NT_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NT_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NT_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NT_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NT_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NT_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NT_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NT_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NT_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NT_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NT_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NT_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NT_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NT_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NT_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NT_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NT_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NT_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NT_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NT_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NT_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NT_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NT_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NT_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NT_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NT_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NT_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NT_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NT_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NT_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NT_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NT_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NT_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NT_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NT_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NT_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NT_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NT_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NT_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NT_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NT_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NT_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NT_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NT_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NT_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NT_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NT_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NT_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NT_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NT_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NC_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = zgemm_NC_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = zgemm_NC_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = zgemm_NC_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = zgemm_NC_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NC_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_NC_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = zgemm_NC_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_NC_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_NC_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NC_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NC_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_NC_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NC_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NC_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = zgemm_NC_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = zgemm_NC_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = zgemm_NC_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = zgemm_NC_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NC_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_NC_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = zgemm_NC_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_NC_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_NC_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NC_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NC_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_NC_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NC_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NC_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = zgemm_NC_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = zgemm_NC_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = zgemm_NC_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = zgemm_NC_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NC_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_NC_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = zgemm_NC_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_NC_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_NC_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NC_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NC_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_NC_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NC_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NC_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = zgemm_NC_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = zgemm_NC_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = zgemm_NC_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = zgemm_NC_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NC_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_NC_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = zgemm_NC_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_NC_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_NC_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NC_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NC_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_NC_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NC_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NC_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = zgemm_NC_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = zgemm_NC_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = zgemm_NC_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = zgemm_NC_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NC_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_NC_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = zgemm_NC_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_NC_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_NC_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NC_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NC_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_NC_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NC_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NC_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = zgemm_NC_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = zgemm_NC_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = zgemm_NC_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = zgemm_NC_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NC_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_NC_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = zgemm_NC_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_NC_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_NC_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NC_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NC_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_NC_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NC_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NC_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = zgemm_NC_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = zgemm_NC_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = zgemm_NC_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = zgemm_NC_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NC_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_NC_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = zgemm_NC_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_NC_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_NC_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NC_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NC_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_NC_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NC_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NC_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = zgemm_NC_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = zgemm_NC_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = zgemm_NC_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = zgemm_NC_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_NC_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_NC_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = zgemm_NC_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_NC_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_NC_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_NC_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_NC_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_NC_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_NC_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NC_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NC_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NC_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NC_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NC_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NC_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NC_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NC_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NC_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NC_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NC_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NC_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NC_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NC_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NC_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NC_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NC_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NC_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NC_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NC_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NC_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NC_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NC_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NC_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NC_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NC_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NC_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NC_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NC_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NC_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NC_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NC_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NC_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NC_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NC_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NC_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NC_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NC_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NC_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NC_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NC_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NC_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NC_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NC_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NC_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NC_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NC_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NC_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NC_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NC_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NC_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NC_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NC_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NC_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NC_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NC_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NC_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NC_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NC_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NC_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NC_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NC_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NC_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NC_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NC_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NC_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NC_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NC_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NC_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NC_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NC_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NC_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NC_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NC_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NC_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NC_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NC_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NC_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NC_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NC_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NC_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NC_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NC_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NC_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_NC_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NC_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NC_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NC_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NC_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NC_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NC_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NC_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NC_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NC_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NC_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NC_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NC_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NC_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_NC_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_NC_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_NC_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_NC_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_NC_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_NC_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_NC_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_NC_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_NC_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_NC_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_NC_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_NC_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_NC_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_NC_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TN_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = zgemm_TN_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = zgemm_TN_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = zgemm_TN_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = zgemm_TN_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TN_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_TN_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = zgemm_TN_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_TN_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_TN_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TN_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TN_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_TN_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TN_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TN_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = zgemm_TN_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = zgemm_TN_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = zgemm_TN_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = zgemm_TN_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TN_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_TN_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = zgemm_TN_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_TN_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_TN_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TN_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TN_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_TN_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TN_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TN_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = zgemm_TN_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = zgemm_TN_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = zgemm_TN_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = zgemm_TN_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TN_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_TN_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = zgemm_TN_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_TN_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_TN_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TN_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TN_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_TN_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TN_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TN_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = zgemm_TN_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = zgemm_TN_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = zgemm_TN_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = zgemm_TN_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TN_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_TN_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = zgemm_TN_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_TN_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_TN_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TN_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TN_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_TN_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TN_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TN_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = zgemm_TN_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = zgemm_TN_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = zgemm_TN_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = zgemm_TN_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TN_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_TN_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = zgemm_TN_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_TN_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_TN_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TN_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TN_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_TN_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TN_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TN_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = zgemm_TN_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = zgemm_TN_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = zgemm_TN_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = zgemm_TN_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TN_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_TN_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = zgemm_TN_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_TN_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_TN_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TN_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TN_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_TN_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TN_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TN_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = zgemm_TN_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = zgemm_TN_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = zgemm_TN_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = zgemm_TN_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TN_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_TN_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = zgemm_TN_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_TN_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_TN_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TN_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TN_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_TN_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TN_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TN_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = zgemm_TN_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = zgemm_TN_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = zgemm_TN_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = zgemm_TN_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TN_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_TN_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = zgemm_TN_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_TN_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_TN_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TN_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TN_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_TN_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TN_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TN_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TN_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TN_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TN_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TN_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TN_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TN_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TN_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TN_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TN_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TN_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TN_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TN_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TN_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TN_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TN_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TN_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TN_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TN_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TN_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TN_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TN_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TN_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TN_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TN_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TN_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TN_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TN_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TN_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TN_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TN_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TN_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TN_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TN_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TN_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TN_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TN_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TN_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TN_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TN_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TN_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TN_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TN_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TN_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TN_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TN_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TN_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TN_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TN_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TN_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TN_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TN_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TN_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TN_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TN_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TN_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TN_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TN_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TN_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TN_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TN_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TN_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TN_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TN_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TN_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TN_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TN_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TN_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TN_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TN_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TN_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TN_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TN_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TN_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TN_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TN_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TN_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TN_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TN_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TN_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TT_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = zgemm_TT_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = zgemm_TT_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = zgemm_TT_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = zgemm_TT_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TT_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_TT_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = zgemm_TT_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_TT_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_TT_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TT_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TT_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_TT_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TT_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TT_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = zgemm_TT_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = zgemm_TT_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = zgemm_TT_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = zgemm_TT_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TT_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_TT_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = zgemm_TT_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_TT_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_TT_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TT_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TT_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_TT_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TT_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TT_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = zgemm_TT_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = zgemm_TT_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = zgemm_TT_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = zgemm_TT_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TT_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_TT_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = zgemm_TT_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_TT_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_TT_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TT_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TT_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_TT_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TT_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TT_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = zgemm_TT_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = zgemm_TT_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = zgemm_TT_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = zgemm_TT_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TT_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_TT_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = zgemm_TT_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_TT_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_TT_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TT_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TT_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_TT_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TT_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TT_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = zgemm_TT_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = zgemm_TT_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = zgemm_TT_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = zgemm_TT_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TT_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_TT_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = zgemm_TT_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_TT_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_TT_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TT_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TT_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_TT_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TT_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TT_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = zgemm_TT_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = zgemm_TT_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = zgemm_TT_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = zgemm_TT_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TT_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_TT_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = zgemm_TT_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_TT_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_TT_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TT_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TT_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_TT_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TT_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TT_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = zgemm_TT_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = zgemm_TT_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = zgemm_TT_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = zgemm_TT_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TT_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_TT_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = zgemm_TT_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_TT_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_TT_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TT_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TT_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_TT_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TT_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TT_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = zgemm_TT_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = zgemm_TT_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = zgemm_TT_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = zgemm_TT_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TT_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_TT_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = zgemm_TT_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_TT_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_TT_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TT_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TT_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_TT_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TT_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TT_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TT_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TT_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TT_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TT_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TT_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TT_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TT_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TT_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TT_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TT_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TT_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TT_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TT_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TT_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TT_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TT_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TT_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TT_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TT_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TT_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TT_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TT_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TT_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TT_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TT_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TT_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TT_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TT_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TT_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TT_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TT_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TT_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TT_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TT_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TT_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TT_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TT_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TT_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TT_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TT_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TT_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TT_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TT_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TT_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TT_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TT_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TT_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TT_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TT_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TT_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TT_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TT_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TT_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TT_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TT_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TT_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TT_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TT_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TT_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TT_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TT_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TT_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TT_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TT_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TT_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TT_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TT_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TT_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TT_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TT_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TT_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TT_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TT_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TT_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TT_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TT_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TT_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TT_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TT_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TC_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = zgemm_TC_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = zgemm_TC_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = zgemm_TC_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = zgemm_TC_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TC_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_TC_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = zgemm_TC_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_TC_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_TC_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TC_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TC_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_TC_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TC_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TC_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = zgemm_TC_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = zgemm_TC_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = zgemm_TC_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = zgemm_TC_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TC_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_TC_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = zgemm_TC_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_TC_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_TC_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TC_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TC_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_TC_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TC_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TC_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = zgemm_TC_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = zgemm_TC_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = zgemm_TC_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = zgemm_TC_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TC_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_TC_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = zgemm_TC_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_TC_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_TC_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TC_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TC_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_TC_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TC_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TC_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = zgemm_TC_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = zgemm_TC_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = zgemm_TC_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = zgemm_TC_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TC_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_TC_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = zgemm_TC_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_TC_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_TC_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TC_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TC_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_TC_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TC_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TC_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = zgemm_TC_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = zgemm_TC_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = zgemm_TC_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = zgemm_TC_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TC_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_TC_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = zgemm_TC_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_TC_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_TC_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TC_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TC_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_TC_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TC_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TC_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = zgemm_TC_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = zgemm_TC_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = zgemm_TC_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = zgemm_TC_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TC_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_TC_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = zgemm_TC_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_TC_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_TC_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TC_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TC_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_TC_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TC_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TC_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = zgemm_TC_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = zgemm_TC_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = zgemm_TC_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = zgemm_TC_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TC_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_TC_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = zgemm_TC_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_TC_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_TC_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TC_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TC_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_TC_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TC_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TC_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = zgemm_TC_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = zgemm_TC_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = zgemm_TC_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = zgemm_TC_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_TC_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_TC_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = zgemm_TC_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_TC_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_TC_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_TC_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_TC_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_TC_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_TC_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TC_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TC_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TC_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TC_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TC_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TC_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TC_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TC_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TC_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TC_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TC_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TC_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TC_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TC_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TC_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TC_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TC_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TC_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TC_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TC_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TC_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TC_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TC_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TC_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TC_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TC_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TC_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TC_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TC_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TC_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TC_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TC_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TC_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TC_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TC_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TC_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TC_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TC_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TC_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TC_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TC_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TC_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TC_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TC_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TC_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TC_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TC_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TC_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TC_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TC_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TC_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TC_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TC_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TC_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TC_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TC_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TC_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TC_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TC_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TC_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TC_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TC_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TC_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TC_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TC_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TC_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TC_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TC_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TC_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TC_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TC_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TC_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TC_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TC_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TC_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TC_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TC_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TC_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TC_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TC_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TC_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TC_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TC_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TC_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_TC_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TC_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TC_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TC_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TC_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TC_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TC_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TC_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TC_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TC_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TC_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TC_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TC_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TC_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_TC_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_TC_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_TC_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_TC_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_TC_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_TC_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_TC_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_TC_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_TC_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_TC_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_TC_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_TC_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_TC_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_TC_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CN_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = zgemm_CN_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = zgemm_CN_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = zgemm_CN_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = zgemm_CN_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CN_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_CN_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = zgemm_CN_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_CN_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_CN_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CN_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CN_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_CN_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CN_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CN_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = zgemm_CN_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = zgemm_CN_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = zgemm_CN_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = zgemm_CN_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CN_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_CN_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = zgemm_CN_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_CN_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_CN_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CN_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CN_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_CN_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CN_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CN_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = zgemm_CN_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = zgemm_CN_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = zgemm_CN_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = zgemm_CN_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CN_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_CN_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = zgemm_CN_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_CN_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_CN_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CN_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CN_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_CN_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CN_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CN_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = zgemm_CN_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = zgemm_CN_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = zgemm_CN_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = zgemm_CN_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CN_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_CN_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = zgemm_CN_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_CN_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_CN_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CN_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CN_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_CN_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CN_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CN_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = zgemm_CN_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = zgemm_CN_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = zgemm_CN_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = zgemm_CN_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CN_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_CN_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = zgemm_CN_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_CN_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_CN_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CN_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CN_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_CN_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CN_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CN_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = zgemm_CN_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = zgemm_CN_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = zgemm_CN_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = zgemm_CN_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CN_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_CN_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = zgemm_CN_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_CN_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_CN_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CN_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CN_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_CN_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CN_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CN_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = zgemm_CN_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = zgemm_CN_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = zgemm_CN_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = zgemm_CN_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CN_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_CN_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = zgemm_CN_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_CN_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_CN_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CN_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CN_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_CN_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CN_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CN_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = zgemm_CN_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = zgemm_CN_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = zgemm_CN_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = zgemm_CN_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CN_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_CN_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = zgemm_CN_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_CN_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_CN_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CN_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CN_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_CN_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CN_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CN_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CN_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CN_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CN_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CN_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CN_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CN_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CN_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CN_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CN_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CN_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CN_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CN_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CN_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CN_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CN_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CN_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CN_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CN_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CN_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CN_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CN_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CN_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CN_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CN_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CN_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CN_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CN_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CN_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CN_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CN_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CN_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CN_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CN_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CN_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CN_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CN_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CN_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CN_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CN_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CN_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CN_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CN_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CN_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CN_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CN_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CN_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CN_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CN_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CN_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CN_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CN_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CN_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CN_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CN_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CN_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CN_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CN_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CN_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CN_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CN_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CN_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CN_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CN_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CN_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CN_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CN_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CN_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CN_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CN_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CN_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CN_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CN_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CN_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CN_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CN_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CN_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CN_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CN_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CN_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CN_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CN_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CN_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CN_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CN_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CN_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CN_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CN_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CN_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CN_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CN_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CN_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CN_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CN_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CN_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CN_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CN_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CN_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CN_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CN_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CN_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CN_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CN_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CN_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CN_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CN_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CN_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CN_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CN_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CN_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CN_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CN_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CT_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = zgemm_CT_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = zgemm_CT_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = zgemm_CT_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = zgemm_CT_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CT_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_CT_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = zgemm_CT_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_CT_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_CT_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CT_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CT_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_CT_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CT_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CT_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = zgemm_CT_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = zgemm_CT_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = zgemm_CT_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = zgemm_CT_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CT_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_CT_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = zgemm_CT_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_CT_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_CT_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CT_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CT_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_CT_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CT_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CT_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = zgemm_CT_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = zgemm_CT_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = zgemm_CT_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = zgemm_CT_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CT_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_CT_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = zgemm_CT_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_CT_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_CT_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CT_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CT_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_CT_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CT_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CT_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = zgemm_CT_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = zgemm_CT_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = zgemm_CT_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = zgemm_CT_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CT_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_CT_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = zgemm_CT_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_CT_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_CT_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CT_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CT_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_CT_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CT_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CT_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = zgemm_CT_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = zgemm_CT_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = zgemm_CT_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = zgemm_CT_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CT_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_CT_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = zgemm_CT_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_CT_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_CT_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CT_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CT_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_CT_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CT_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CT_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = zgemm_CT_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = zgemm_CT_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = zgemm_CT_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = zgemm_CT_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CT_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_CT_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = zgemm_CT_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_CT_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_CT_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CT_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CT_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_CT_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CT_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CT_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = zgemm_CT_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = zgemm_CT_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = zgemm_CT_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = zgemm_CT_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CT_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_CT_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = zgemm_CT_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_CT_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_CT_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CT_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CT_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_CT_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CT_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CT_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = zgemm_CT_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = zgemm_CT_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = zgemm_CT_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = zgemm_CT_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CT_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_CT_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = zgemm_CT_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_CT_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_CT_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CT_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CT_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_CT_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CT_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CT_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CT_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CT_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CT_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CT_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CT_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CT_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CT_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CT_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CT_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CT_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CT_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CT_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CT_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CT_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CT_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CT_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CT_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CT_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CT_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CT_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CT_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CT_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CT_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CT_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CT_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CT_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CT_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CT_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CT_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CT_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CT_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CT_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CT_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CT_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CT_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CT_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CT_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CT_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CT_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CT_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CT_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CT_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CT_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CT_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CT_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CT_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CT_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CT_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CT_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CT_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CT_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CT_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CT_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CT_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CT_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CT_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CT_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CT_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CT_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CT_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CT_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CT_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CT_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CT_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CT_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CT_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CT_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CT_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CT_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CT_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CT_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CT_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CT_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CT_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CT_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CT_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CT_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CT_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CT_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CT_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CT_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CT_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CT_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CT_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CT_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CT_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CT_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CT_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CT_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CT_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CT_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CT_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CT_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CT_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CT_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CT_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CT_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CT_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CT_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CT_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CT_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CT_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CT_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CT_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CT_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CT_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CT_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CT_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CT_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CT_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CT_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CC_064_032_8_16x16_4x2_ColMajor_src;
            *rowKernelSource    = zgemm_CC_001_032_8_16x16_4x2_ColMajor_src;
            *colKernelSource    = zgemm_CC_064_001_8_16x16_4x2_ColMajor_src;
            *cornerKernelSource = zgemm_CC_001_001_8_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = zgemm_CC_064_032_8_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CC_064_032_8_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_CC_001_032_8_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = zgemm_CC_064_001_8_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_CC_001_001_8_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_CC_064_032_8_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CC_064_032_8_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CC_001_032_8_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_CC_064_001_8_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CC_001_001_8_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CC_064_032_1_16x16_4x2_ColMajor_src;
            *rowKernelSource    = zgemm_CC_001_032_1_16x16_4x2_ColMajor_src;
            *colKernelSource    = zgemm_CC_064_001_1_16x16_4x2_ColMajor_src;
            *cornerKernelSource = zgemm_CC_001_001_1_16x16_4x2_ColMajor_src;
            *sourceBuildOptions = zgemm_CC_064_032_1_16x16_4x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CC_064_032_1_16x16_4x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_CC_001_032_1_16x16_4x2_ColMajor_bin;
            *colKernelBinary    = zgemm_CC_064_001_1_16x16_4x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_CC_001_001_1_16x16_4x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_CC_064_032_1_16x16_4x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CC_064_032_1_16x16_4x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CC_001_032_1_16x16_4x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_CC_064_001_1_16x16_4x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CC_001_001_1_16x16_4x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CC_032_032_8_16x16_2x2_ColMajor_src;
            *rowKernelSource    = zgemm_CC_001_032_8_16x16_2x2_ColMajor_src;
            *colKernelSource    = zgemm_CC_032_001_8_16x16_2x2_ColMajor_src;
            *cornerKernelSource = zgemm_CC_001_001_8_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = zgemm_CC_032_032_8_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CC_032_032_8_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_CC_001_032_8_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = zgemm_CC_032_001_8_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_CC_001_001_8_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_CC_032_032_8_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CC_032_032_8_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CC_001_032_8_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_CC_032_001_8_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CC_001_001_8_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CC_032_032_1_16x16_2x2_ColMajor_src;
            *rowKernelSource    = zgemm_CC_001_032_1_16x16_2x2_ColMajor_src;
            *colKernelSource    = zgemm_CC_032_001_1_16x16_2x2_ColMajor_src;
            *cornerKernelSource = zgemm_CC_001_001_1_16x16_2x2_ColMajor_src;
            *sourceBuildOptions = zgemm_CC_032_032_1_16x16_2x2_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CC_032_032_1_16x16_2x2_ColMajor_bin;
            *rowKernelBinary    = zgemm_CC_001_032_1_16x16_2x2_ColMajor_bin;
            *colKernelBinary    = zgemm_CC_032_001_1_16x16_2x2_ColMajor_bin;
            *cornerKernelBinary = zgemm_CC_001_001_1_16x16_2x2_ColMajor_bin;
            *binaryBuildOptions = zgemm_CC_032_032_1_16x16_2x2_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CC_032_032_1_16x16_2x2_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CC_001_032_1_16x16_2x2_ColMajor_clKernel;
            *colClKernel        = &zgemm_CC_032_001_1_16x16_2x2_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CC_001_001_1_16x16_2x2_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CC_032_016_8_16x16_2x1_ColMajor_src;
            *rowKernelSource    = zgemm_CC_001_016_8_16x16_2x1_ColMajor_src;
            *colKernelSource    = zgemm_CC_032_001_8_16x16_2x1_ColMajor_src;
            *cornerKernelSource = zgemm_CC_001_001_8_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = zgemm_CC_032_016_8_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CC_032_016_8_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_CC_001_016_8_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = zgemm_CC_032_001_8_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_CC_001_001_8_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_CC_032_016_8_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CC_032_016_8_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CC_001_016_8_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_CC_032_001_8_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CC_001_001_8_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CC_032_016_1_16x16_2x1_ColMajor_src;
            *rowKernelSource    = zgemm_CC_001_016_1_16x16_2x1_ColMajor_src;
            *colKernelSource    = zgemm_CC_032_001_1_16x16_2x1_ColMajor_src;
            *cornerKernelSource = zgemm_CC_001_001_1_16x16_2x1_ColMajor_src;
            *sourceBuildOptions = zgemm_CC_032_016_1_16x16_2x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CC_032_016_1_16x16_2x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_CC_001_016_1_16x16_2x1_ColMajor_bin;
            *colKernelBinary    = zgemm_CC_032_001_1_16x16_2x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_CC_001_001_1_16x16_2x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_CC_032_016_1_16x16_2x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CC_032_016_1_16x16_2x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CC_001_016_1_16x16_2x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_CC_032_001_1_16x16_2x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CC_001_001_1_16x16_2x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CC_016_016_8_16x16_1x1_ColMajor_src;
            *rowKernelSource    = zgemm_CC_001_016_8_16x16_1x1_ColMajor_src;
            *colKernelSource    = zgemm_CC_016_001_8_16x16_1x1_ColMajor_src;
            *cornerKernelSource = zgemm_CC_001_001_8_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = zgemm_CC_016_016_8_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CC_016_016_8_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_CC_001_016_8_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = zgemm_CC_016_001_8_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_CC_001_001_8_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_CC_016_016_8_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CC_016_016_8_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CC_001_016_8_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_CC_016_001_8_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CC_001_001_8_16x16_1x1_ColMajor_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CC_016_016_1_16x16_1x1_ColMajor_src;
            *rowKernelSource    = zgemm_CC_001_016_1_16x16_1x1_ColMajor_src;
            *colKernelSource    = zgemm_CC_016_001_1_16x16_1x1_ColMajor_src;
            *cornerKernelSource = zgemm_CC_001_001_1_16x16_1x1_ColMajor_src;
            *sourceBuildOptions = zgemm_CC_016_016_1_16x16_1x1_ColMajor_srcBuildOptions;
            *tileKernelBinary   = zgemm_CC_016_016_1_16x16_1x1_ColMajor_bin;
            *rowKernelBinary    = zgemm_CC_001_016_1_16x16_1x1_ColMajor_bin;
            *colKernelBinary    = zgemm_CC_016_001_1_16x16_1x1_ColMajor_bin;
            *cornerKernelBinary = zgemm_CC_001_001_1_16x16_1x1_ColMajor_bin;
            *binaryBuildOptions = zgemm_CC_016_016_1_16x16_1x1_ColMajor_binBuildOptions;
            *tileClKernel       = &zgemm_CC_016_016_1_16x16_1x1_ColMajor_clKernel;
            *rowClKernel        = &zgemm_CC_001_016_1_16x16_1x1_ColMajor_clKernel;
            *colClKernel        = &zgemm_CC_016_001_1_16x16_1x1_ColMajor_clKernel;
            *cornerClKernel     = &zgemm_CC_001_001_1_16x16_1x1_ColMajor_clKernel;
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
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CC_064_032_8_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CC_001_032_8_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CC_064_001_8_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CC_001_001_8_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CC_064_032_8_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CC_064_032_8_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CC_001_032_8_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CC_064_001_8_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CC_001_001_8_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CC_064_032_8_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CC_064_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CC_001_032_8_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CC_064_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CC_001_001_8_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%64 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CC_064_032_1_16x16_4x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CC_001_032_1_16x16_4x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CC_064_001_1_16x16_4x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CC_001_001_1_16x16_4x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CC_064_032_1_16x16_4x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CC_064_032_1_16x16_4x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CC_001_032_1_16x16_4x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CC_064_001_1_16x16_4x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CC_001_001_1_16x16_4x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CC_064_032_1_16x16_4x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CC_064_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CC_001_032_1_16x16_4x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CC_064_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CC_001_001_1_16x16_4x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 4;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 2) {
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CC_032_032_8_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CC_001_032_8_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CC_032_001_8_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CC_001_001_8_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CC_032_032_8_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CC_032_032_8_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CC_001_032_8_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CC_032_001_8_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CC_001_001_8_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CC_032_032_8_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CC_032_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CC_001_032_8_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CC_032_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CC_001_001_8_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%32 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CC_032_032_1_16x16_2x2_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CC_001_032_1_16x16_2x2_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CC_032_001_1_16x16_2x2_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CC_001_001_1_16x16_2x2_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CC_032_032_1_16x16_2x2_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CC_032_032_1_16x16_2x2_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CC_001_032_1_16x16_2x2_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CC_032_001_1_16x16_2x2_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CC_001_001_1_16x16_2x2_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CC_032_032_1_16x16_2x2_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CC_032_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CC_001_032_1_16x16_2x2_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CC_032_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CC_001_001_1_16x16_2x2_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 2;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 1) {
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CC_032_016_8_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CC_001_016_8_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CC_032_001_8_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CC_001_001_8_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CC_032_016_8_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CC_032_016_8_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CC_001_016_8_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CC_032_001_8_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CC_001_001_8_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CC_032_016_8_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CC_032_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CC_001_016_8_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CC_032_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CC_001_001_8_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%32 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CC_032_016_1_16x16_2x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CC_001_016_1_16x16_2x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CC_032_001_1_16x16_2x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CC_001_001_1_16x16_2x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CC_032_016_1_16x16_2x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CC_032_016_1_16x16_2x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CC_001_016_1_16x16_2x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CC_032_001_1_16x16_2x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CC_001_001_1_16x16_2x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CC_032_016_1_16x16_2x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CC_032_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CC_001_016_1_16x16_2x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CC_032_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CC_001_001_1_16x16_2x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 2;
            *microTileNumCols   = 1;
            *unroll             = 1;
            return;
          }
        }
        if (optimalNumElementsPerWorkItem > 0) {
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%8 == 0) {
            *tileKernelSource   = zgemm_CC_016_016_8_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CC_001_016_8_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CC_016_001_8_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CC_001_001_8_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CC_016_016_8_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CC_016_016_8_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CC_001_016_8_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CC_016_001_8_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CC_001_001_8_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CC_016_016_8_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CC_016_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CC_001_016_8_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CC_016_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CC_001_001_8_16x16_1x1_ColMajor_BETA_clKernel;
            *workGroupNumRows   = 16;
            *workGroupNumCols   = 16;
            *microTileNumRows   = 1;
            *microTileNumCols   = 1;
            *unroll             = 8;
            return;
          }
          if ( /*M%16 == 0 && N%16 == 0 &&*/ K%1 == 0) {
            *tileKernelSource   = zgemm_CC_016_016_1_16x16_1x1_ColMajor_BETA_src;
            *rowKernelSource    = zgemm_CC_001_016_1_16x16_1x1_ColMajor_BETA_src;
            *colKernelSource    = zgemm_CC_016_001_1_16x16_1x1_ColMajor_BETA_src;
            *cornerKernelSource = zgemm_CC_001_001_1_16x16_1x1_ColMajor_BETA_src;
            *sourceBuildOptions = zgemm_CC_016_016_1_16x16_1x1_ColMajor_BETA_srcBuildOptions;
            *tileKernelBinary   = zgemm_CC_016_016_1_16x16_1x1_ColMajor_BETA_bin;
            *rowKernelBinary    = zgemm_CC_001_016_1_16x16_1x1_ColMajor_BETA_bin;
            *colKernelBinary    = zgemm_CC_016_001_1_16x16_1x1_ColMajor_BETA_bin;
            *cornerKernelBinary = zgemm_CC_001_001_1_16x16_1x1_ColMajor_BETA_bin;
            *binaryBuildOptions = zgemm_CC_016_016_1_16x16_1x1_ColMajor_BETA_binBuildOptions;
            *tileClKernel       = &zgemm_CC_016_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *rowClKernel        = &zgemm_CC_001_016_1_16x16_1x1_ColMajor_BETA_clKernel;
            *colClKernel        = &zgemm_CC_016_001_1_16x16_1x1_ColMajor_BETA_clKernel;
            *cornerClKernel     = &zgemm_CC_001_001_1_16x16_1x1_ColMajor_BETA_clKernel;
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

