/*******************************************************************************
 * This file was auto-generated using the AutoGemm.py python script.
 * DO NOT modify this file! Instead, make changes to
 *   clBLAS/src/scripts/AutoGemm/AutoGemm.py then re-generate files
 *   (otherwise local changes will be lost after re-generation).
 * - David Tanner
 ******************************************************************************/

#include "UserGemmKernelSourceIncludes.h"
#include "AutoGemmKernelSourceIncludes.h"
#if USE_GEMM_KERNEL_BINARIES
#include "AutoGemmKernelBinaryIncludes.h"
#else
#include "AutoGemmKernelBinaryNulls.h"
#endif
#include "AutoGemmKernelSourceBuildOptions.h"
#include "AutoGemmKernelBinaryBuildOptions.h"
#include "AutoGemmClKernels.h"

// kernel selection specific template
template<typename Precision>
bool gemmSelectKernelSpecific(
  clblasOrder order,
  clblasTranspose transA,
  clblasTranspose transB,
  bool betaNonZero,
  unsigned int workGroupNumRows,
  unsigned int workGroupNumCols,
  unsigned int microTileNumRows,
  unsigned int microTileNumCols,
  unsigned int unroll,
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
  cl_kernel  **cornerClKernel
);

  // sgemm kernel selection specific
template<>
bool gemmSelectKernelSpecific<float>(
  clblasOrder order,
  clblasTranspose transA,
  clblasTranspose transB,
  bool betaNonZero,
  unsigned int workGroupNumRows,
  unsigned int workGroupNumCols,
  unsigned int microTileNumRows,
  unsigned int microTileNumCols,
  unsigned int unroll,
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
  cl_kernel  **cornerClKernel
) {
  if (order == clblasColumnMajor) {
    if (transA == clblasNoTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NN_B0_096_096_08_16x16_06x06_src;
          *rowKernelSource    = sgemm_Col_NN_B0_001_096_08_16x16_06x06_src;
          *colKernelSource    = sgemm_Col_NN_B0_096_001_08_16x16_06x06_src;
          *cornerKernelSource = sgemm_Col_NN_B0_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = sgemm_Col_NN_B0_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B0_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = sgemm_Col_NN_B0_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = sgemm_Col_NN_B0_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = sgemm_Col_NN_B0_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = sgemm_Col_NN_B0_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NN_B0_096_096_01_16x16_06x06_src;
          *rowKernelSource    = sgemm_Col_NN_B0_001_096_01_16x16_06x06_src;
          *colKernelSource    = sgemm_Col_NN_B0_096_001_01_16x16_06x06_src;
          *cornerKernelSource = sgemm_Col_NN_B0_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = sgemm_Col_NN_B0_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B0_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = sgemm_Col_NN_B0_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = sgemm_Col_NN_B0_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = sgemm_Col_NN_B0_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = sgemm_Col_NN_B0_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 8 && microTileNumCols == 8 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NN_B0_128_128_08_16x16_08x08_src;
          *rowKernelSource    = sgemm_Col_NN_B0_001_128_08_16x16_08x08_src;
          *colKernelSource    = sgemm_Col_NN_B0_128_001_08_16x16_08x08_src;
          *cornerKernelSource = sgemm_Col_NN_B0_001_001_08_16x16_08x08_src;
          *sourceBuildOptions = sgemm_Col_NN_B0_128_128_08_16x16_08x08_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B0_128_128_08_16x16_08x08_bin;
          *rowKernelBinary    = sgemm_Col_NN_B0_001_128_08_16x16_08x08_bin;
          *colKernelBinary    = sgemm_Col_NN_B0_128_001_08_16x16_08x08_bin;
          *cornerKernelBinary = sgemm_Col_NN_B0_001_001_08_16x16_08x08_bin;
          *binaryBuildOptions = sgemm_Col_NN_B0_128_128_08_16x16_08x08_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_128_128_08_16x16_08x08_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_001_128_08_16x16_08x08_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_128_001_08_16x16_08x08_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_001_001_08_16x16_08x08_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 8 && microTileNumCols == 8 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NN_B0_128_128_01_16x16_08x08_src;
          *rowKernelSource    = sgemm_Col_NN_B0_001_128_01_16x16_08x08_src;
          *colKernelSource    = sgemm_Col_NN_B0_128_001_01_16x16_08x08_src;
          *cornerKernelSource = sgemm_Col_NN_B0_001_001_01_16x16_08x08_src;
          *sourceBuildOptions = sgemm_Col_NN_B0_128_128_01_16x16_08x08_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B0_128_128_01_16x16_08x08_bin;
          *rowKernelBinary    = sgemm_Col_NN_B0_001_128_01_16x16_08x08_bin;
          *colKernelBinary    = sgemm_Col_NN_B0_128_001_01_16x16_08x08_bin;
          *cornerKernelBinary = sgemm_Col_NN_B0_001_001_01_16x16_08x08_bin;
          *binaryBuildOptions = sgemm_Col_NN_B0_128_128_01_16x16_08x08_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_128_128_01_16x16_08x08_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_001_128_01_16x16_08x08_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_128_001_01_16x16_08x08_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_001_001_01_16x16_08x08_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NN_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = sgemm_Col_NN_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = sgemm_Col_NN_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = sgemm_Col_NN_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = sgemm_Col_NN_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = sgemm_Col_NN_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = sgemm_Col_NN_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = sgemm_Col_NN_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = sgemm_Col_NN_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NN_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = sgemm_Col_NN_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = sgemm_Col_NN_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = sgemm_Col_NN_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = sgemm_Col_NN_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = sgemm_Col_NN_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = sgemm_Col_NN_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = sgemm_Col_NN_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = sgemm_Col_NN_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NN_B0_080_080_08_16x16_05x05_src;
          *rowKernelSource    = sgemm_Col_NN_B0_001_080_08_16x16_05x05_src;
          *colKernelSource    = sgemm_Col_NN_B0_080_001_08_16x16_05x05_src;
          *cornerKernelSource = sgemm_Col_NN_B0_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = sgemm_Col_NN_B0_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B0_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = sgemm_Col_NN_B0_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = sgemm_Col_NN_B0_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = sgemm_Col_NN_B0_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = sgemm_Col_NN_B0_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NN_B0_080_080_01_16x16_05x05_src;
          *rowKernelSource    = sgemm_Col_NN_B0_001_080_01_16x16_05x05_src;
          *colKernelSource    = sgemm_Col_NN_B0_080_001_01_16x16_05x05_src;
          *cornerKernelSource = sgemm_Col_NN_B0_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = sgemm_Col_NN_B0_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B0_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = sgemm_Col_NN_B0_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = sgemm_Col_NN_B0_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = sgemm_Col_NN_B0_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = sgemm_Col_NN_B0_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NN_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = sgemm_Col_NN_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = sgemm_Col_NN_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = sgemm_Col_NN_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = sgemm_Col_NN_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = sgemm_Col_NN_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = sgemm_Col_NN_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = sgemm_Col_NN_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = sgemm_Col_NN_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NN_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = sgemm_Col_NN_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = sgemm_Col_NN_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = sgemm_Col_NN_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = sgemm_Col_NN_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = sgemm_Col_NN_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = sgemm_Col_NN_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = sgemm_Col_NN_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = sgemm_Col_NN_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 7 && microTileNumCols == 7 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NN_B0_112_112_08_16x16_07x07_src;
          *rowKernelSource    = sgemm_Col_NN_B0_001_112_08_16x16_07x07_src;
          *colKernelSource    = sgemm_Col_NN_B0_112_001_08_16x16_07x07_src;
          *cornerKernelSource = sgemm_Col_NN_B0_001_001_08_16x16_07x07_src;
          *sourceBuildOptions = sgemm_Col_NN_B0_112_112_08_16x16_07x07_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B0_112_112_08_16x16_07x07_bin;
          *rowKernelBinary    = sgemm_Col_NN_B0_001_112_08_16x16_07x07_bin;
          *colKernelBinary    = sgemm_Col_NN_B0_112_001_08_16x16_07x07_bin;
          *cornerKernelBinary = sgemm_Col_NN_B0_001_001_08_16x16_07x07_bin;
          *binaryBuildOptions = sgemm_Col_NN_B0_112_112_08_16x16_07x07_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_112_112_08_16x16_07x07_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_001_112_08_16x16_07x07_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_112_001_08_16x16_07x07_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_001_001_08_16x16_07x07_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 7 && microTileNumCols == 7 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NN_B0_112_112_01_16x16_07x07_src;
          *rowKernelSource    = sgemm_Col_NN_B0_001_112_01_16x16_07x07_src;
          *colKernelSource    = sgemm_Col_NN_B0_112_001_01_16x16_07x07_src;
          *cornerKernelSource = sgemm_Col_NN_B0_001_001_01_16x16_07x07_src;
          *sourceBuildOptions = sgemm_Col_NN_B0_112_112_01_16x16_07x07_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B0_112_112_01_16x16_07x07_bin;
          *rowKernelBinary    = sgemm_Col_NN_B0_001_112_01_16x16_07x07_bin;
          *colKernelBinary    = sgemm_Col_NN_B0_112_001_01_16x16_07x07_bin;
          *cornerKernelBinary = sgemm_Col_NN_B0_001_001_01_16x16_07x07_bin;
          *binaryBuildOptions = sgemm_Col_NN_B0_112_112_01_16x16_07x07_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_112_112_01_16x16_07x07_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_001_112_01_16x16_07x07_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_112_001_01_16x16_07x07_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_001_001_01_16x16_07x07_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NN_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = sgemm_Col_NN_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = sgemm_Col_NN_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = sgemm_Col_NN_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = sgemm_Col_NN_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = sgemm_Col_NN_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = sgemm_Col_NN_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = sgemm_Col_NN_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = sgemm_Col_NN_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NN_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = sgemm_Col_NN_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = sgemm_Col_NN_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = sgemm_Col_NN_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = sgemm_Col_NN_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = sgemm_Col_NN_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = sgemm_Col_NN_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = sgemm_Col_NN_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = sgemm_Col_NN_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NN_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = sgemm_Col_NN_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = sgemm_Col_NN_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = sgemm_Col_NN_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = sgemm_Col_NN_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = sgemm_Col_NN_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = sgemm_Col_NN_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = sgemm_Col_NN_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = sgemm_Col_NN_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NN_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = sgemm_Col_NN_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = sgemm_Col_NN_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = sgemm_Col_NN_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = sgemm_Col_NN_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = sgemm_Col_NN_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = sgemm_Col_NN_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = sgemm_Col_NN_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = sgemm_Col_NN_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NN_B1_096_096_08_16x16_06x06_src;
          *rowKernelSource    = sgemm_Col_NN_B1_001_096_08_16x16_06x06_src;
          *colKernelSource    = sgemm_Col_NN_B1_096_001_08_16x16_06x06_src;
          *cornerKernelSource = sgemm_Col_NN_B1_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = sgemm_Col_NN_B1_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B1_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = sgemm_Col_NN_B1_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = sgemm_Col_NN_B1_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = sgemm_Col_NN_B1_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = sgemm_Col_NN_B1_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NN_B1_096_096_01_16x16_06x06_src;
          *rowKernelSource    = sgemm_Col_NN_B1_001_096_01_16x16_06x06_src;
          *colKernelSource    = sgemm_Col_NN_B1_096_001_01_16x16_06x06_src;
          *cornerKernelSource = sgemm_Col_NN_B1_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = sgemm_Col_NN_B1_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B1_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = sgemm_Col_NN_B1_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = sgemm_Col_NN_B1_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = sgemm_Col_NN_B1_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = sgemm_Col_NN_B1_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 8 && microTileNumCols == 8 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NN_B1_128_128_08_16x16_08x08_src;
          *rowKernelSource    = sgemm_Col_NN_B1_001_128_08_16x16_08x08_src;
          *colKernelSource    = sgemm_Col_NN_B1_128_001_08_16x16_08x08_src;
          *cornerKernelSource = sgemm_Col_NN_B1_001_001_08_16x16_08x08_src;
          *sourceBuildOptions = sgemm_Col_NN_B1_128_128_08_16x16_08x08_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B1_128_128_08_16x16_08x08_bin;
          *rowKernelBinary    = sgemm_Col_NN_B1_001_128_08_16x16_08x08_bin;
          *colKernelBinary    = sgemm_Col_NN_B1_128_001_08_16x16_08x08_bin;
          *cornerKernelBinary = sgemm_Col_NN_B1_001_001_08_16x16_08x08_bin;
          *binaryBuildOptions = sgemm_Col_NN_B1_128_128_08_16x16_08x08_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_128_128_08_16x16_08x08_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_001_128_08_16x16_08x08_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_128_001_08_16x16_08x08_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_001_001_08_16x16_08x08_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 8 && microTileNumCols == 8 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NN_B1_128_128_01_16x16_08x08_src;
          *rowKernelSource    = sgemm_Col_NN_B1_001_128_01_16x16_08x08_src;
          *colKernelSource    = sgemm_Col_NN_B1_128_001_01_16x16_08x08_src;
          *cornerKernelSource = sgemm_Col_NN_B1_001_001_01_16x16_08x08_src;
          *sourceBuildOptions = sgemm_Col_NN_B1_128_128_01_16x16_08x08_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B1_128_128_01_16x16_08x08_bin;
          *rowKernelBinary    = sgemm_Col_NN_B1_001_128_01_16x16_08x08_bin;
          *colKernelBinary    = sgemm_Col_NN_B1_128_001_01_16x16_08x08_bin;
          *cornerKernelBinary = sgemm_Col_NN_B1_001_001_01_16x16_08x08_bin;
          *binaryBuildOptions = sgemm_Col_NN_B1_128_128_01_16x16_08x08_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_128_128_01_16x16_08x08_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_001_128_01_16x16_08x08_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_128_001_01_16x16_08x08_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_001_001_01_16x16_08x08_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NN_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = sgemm_Col_NN_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = sgemm_Col_NN_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = sgemm_Col_NN_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = sgemm_Col_NN_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = sgemm_Col_NN_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = sgemm_Col_NN_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = sgemm_Col_NN_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = sgemm_Col_NN_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NN_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = sgemm_Col_NN_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = sgemm_Col_NN_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = sgemm_Col_NN_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = sgemm_Col_NN_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = sgemm_Col_NN_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = sgemm_Col_NN_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = sgemm_Col_NN_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = sgemm_Col_NN_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NN_B1_080_080_08_16x16_05x05_src;
          *rowKernelSource    = sgemm_Col_NN_B1_001_080_08_16x16_05x05_src;
          *colKernelSource    = sgemm_Col_NN_B1_080_001_08_16x16_05x05_src;
          *cornerKernelSource = sgemm_Col_NN_B1_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = sgemm_Col_NN_B1_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B1_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = sgemm_Col_NN_B1_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = sgemm_Col_NN_B1_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = sgemm_Col_NN_B1_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = sgemm_Col_NN_B1_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NN_B1_080_080_01_16x16_05x05_src;
          *rowKernelSource    = sgemm_Col_NN_B1_001_080_01_16x16_05x05_src;
          *colKernelSource    = sgemm_Col_NN_B1_080_001_01_16x16_05x05_src;
          *cornerKernelSource = sgemm_Col_NN_B1_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = sgemm_Col_NN_B1_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B1_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = sgemm_Col_NN_B1_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = sgemm_Col_NN_B1_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = sgemm_Col_NN_B1_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = sgemm_Col_NN_B1_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NN_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = sgemm_Col_NN_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = sgemm_Col_NN_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = sgemm_Col_NN_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = sgemm_Col_NN_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = sgemm_Col_NN_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = sgemm_Col_NN_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = sgemm_Col_NN_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = sgemm_Col_NN_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NN_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = sgemm_Col_NN_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = sgemm_Col_NN_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = sgemm_Col_NN_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = sgemm_Col_NN_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = sgemm_Col_NN_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = sgemm_Col_NN_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = sgemm_Col_NN_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = sgemm_Col_NN_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 7 && microTileNumCols == 7 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NN_B1_112_112_08_16x16_07x07_src;
          *rowKernelSource    = sgemm_Col_NN_B1_001_112_08_16x16_07x07_src;
          *colKernelSource    = sgemm_Col_NN_B1_112_001_08_16x16_07x07_src;
          *cornerKernelSource = sgemm_Col_NN_B1_001_001_08_16x16_07x07_src;
          *sourceBuildOptions = sgemm_Col_NN_B1_112_112_08_16x16_07x07_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B1_112_112_08_16x16_07x07_bin;
          *rowKernelBinary    = sgemm_Col_NN_B1_001_112_08_16x16_07x07_bin;
          *colKernelBinary    = sgemm_Col_NN_B1_112_001_08_16x16_07x07_bin;
          *cornerKernelBinary = sgemm_Col_NN_B1_001_001_08_16x16_07x07_bin;
          *binaryBuildOptions = sgemm_Col_NN_B1_112_112_08_16x16_07x07_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_112_112_08_16x16_07x07_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_001_112_08_16x16_07x07_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_112_001_08_16x16_07x07_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_001_001_08_16x16_07x07_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 7 && microTileNumCols == 7 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NN_B1_112_112_01_16x16_07x07_src;
          *rowKernelSource    = sgemm_Col_NN_B1_001_112_01_16x16_07x07_src;
          *colKernelSource    = sgemm_Col_NN_B1_112_001_01_16x16_07x07_src;
          *cornerKernelSource = sgemm_Col_NN_B1_001_001_01_16x16_07x07_src;
          *sourceBuildOptions = sgemm_Col_NN_B1_112_112_01_16x16_07x07_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B1_112_112_01_16x16_07x07_bin;
          *rowKernelBinary    = sgemm_Col_NN_B1_001_112_01_16x16_07x07_bin;
          *colKernelBinary    = sgemm_Col_NN_B1_112_001_01_16x16_07x07_bin;
          *cornerKernelBinary = sgemm_Col_NN_B1_001_001_01_16x16_07x07_bin;
          *binaryBuildOptions = sgemm_Col_NN_B1_112_112_01_16x16_07x07_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_112_112_01_16x16_07x07_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_001_112_01_16x16_07x07_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_112_001_01_16x16_07x07_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_001_001_01_16x16_07x07_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NN_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = sgemm_Col_NN_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = sgemm_Col_NN_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = sgemm_Col_NN_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = sgemm_Col_NN_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = sgemm_Col_NN_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = sgemm_Col_NN_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = sgemm_Col_NN_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = sgemm_Col_NN_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NN_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = sgemm_Col_NN_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = sgemm_Col_NN_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = sgemm_Col_NN_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = sgemm_Col_NN_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = sgemm_Col_NN_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = sgemm_Col_NN_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = sgemm_Col_NN_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = sgemm_Col_NN_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NN_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = sgemm_Col_NN_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = sgemm_Col_NN_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = sgemm_Col_NN_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = sgemm_Col_NN_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = sgemm_Col_NN_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = sgemm_Col_NN_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = sgemm_Col_NN_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = sgemm_Col_NN_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NN_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = sgemm_Col_NN_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = sgemm_Col_NN_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = sgemm_Col_NN_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = sgemm_Col_NN_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NN_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = sgemm_Col_NN_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = sgemm_Col_NN_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = sgemm_Col_NN_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = sgemm_Col_NN_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      }
    } else if (transA == clblasNoTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NT_B0_096_096_08_16x16_06x06_src;
          *rowKernelSource    = sgemm_Col_NT_B0_001_096_08_16x16_06x06_src;
          *colKernelSource    = sgemm_Col_NT_B0_096_001_08_16x16_06x06_src;
          *cornerKernelSource = sgemm_Col_NT_B0_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = sgemm_Col_NT_B0_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B0_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = sgemm_Col_NT_B0_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = sgemm_Col_NT_B0_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = sgemm_Col_NT_B0_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = sgemm_Col_NT_B0_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NT_B0_096_096_01_16x16_06x06_src;
          *rowKernelSource    = sgemm_Col_NT_B0_001_096_01_16x16_06x06_src;
          *colKernelSource    = sgemm_Col_NT_B0_096_001_01_16x16_06x06_src;
          *cornerKernelSource = sgemm_Col_NT_B0_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = sgemm_Col_NT_B0_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B0_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = sgemm_Col_NT_B0_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = sgemm_Col_NT_B0_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = sgemm_Col_NT_B0_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = sgemm_Col_NT_B0_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 8 && microTileNumCols == 8 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NT_B0_128_128_08_16x16_08x08_src;
          *rowKernelSource    = sgemm_Col_NT_B0_001_128_08_16x16_08x08_src;
          *colKernelSource    = sgemm_Col_NT_B0_128_001_08_16x16_08x08_src;
          *cornerKernelSource = sgemm_Col_NT_B0_001_001_08_16x16_08x08_src;
          *sourceBuildOptions = sgemm_Col_NT_B0_128_128_08_16x16_08x08_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B0_128_128_08_16x16_08x08_bin;
          *rowKernelBinary    = sgemm_Col_NT_B0_001_128_08_16x16_08x08_bin;
          *colKernelBinary    = sgemm_Col_NT_B0_128_001_08_16x16_08x08_bin;
          *cornerKernelBinary = sgemm_Col_NT_B0_001_001_08_16x16_08x08_bin;
          *binaryBuildOptions = sgemm_Col_NT_B0_128_128_08_16x16_08x08_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_128_128_08_16x16_08x08_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_001_128_08_16x16_08x08_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_128_001_08_16x16_08x08_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_001_001_08_16x16_08x08_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 8 && microTileNumCols == 8 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NT_B0_128_128_01_16x16_08x08_src;
          *rowKernelSource    = sgemm_Col_NT_B0_001_128_01_16x16_08x08_src;
          *colKernelSource    = sgemm_Col_NT_B0_128_001_01_16x16_08x08_src;
          *cornerKernelSource = sgemm_Col_NT_B0_001_001_01_16x16_08x08_src;
          *sourceBuildOptions = sgemm_Col_NT_B0_128_128_01_16x16_08x08_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B0_128_128_01_16x16_08x08_bin;
          *rowKernelBinary    = sgemm_Col_NT_B0_001_128_01_16x16_08x08_bin;
          *colKernelBinary    = sgemm_Col_NT_B0_128_001_01_16x16_08x08_bin;
          *cornerKernelBinary = sgemm_Col_NT_B0_001_001_01_16x16_08x08_bin;
          *binaryBuildOptions = sgemm_Col_NT_B0_128_128_01_16x16_08x08_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_128_128_01_16x16_08x08_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_001_128_01_16x16_08x08_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_128_001_01_16x16_08x08_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_001_001_01_16x16_08x08_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NT_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = sgemm_Col_NT_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = sgemm_Col_NT_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = sgemm_Col_NT_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = sgemm_Col_NT_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = sgemm_Col_NT_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = sgemm_Col_NT_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = sgemm_Col_NT_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = sgemm_Col_NT_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NT_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = sgemm_Col_NT_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = sgemm_Col_NT_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = sgemm_Col_NT_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = sgemm_Col_NT_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = sgemm_Col_NT_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = sgemm_Col_NT_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = sgemm_Col_NT_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = sgemm_Col_NT_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NT_B0_080_080_08_16x16_05x05_src;
          *rowKernelSource    = sgemm_Col_NT_B0_001_080_08_16x16_05x05_src;
          *colKernelSource    = sgemm_Col_NT_B0_080_001_08_16x16_05x05_src;
          *cornerKernelSource = sgemm_Col_NT_B0_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = sgemm_Col_NT_B0_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B0_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = sgemm_Col_NT_B0_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = sgemm_Col_NT_B0_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = sgemm_Col_NT_B0_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = sgemm_Col_NT_B0_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NT_B0_080_080_01_16x16_05x05_src;
          *rowKernelSource    = sgemm_Col_NT_B0_001_080_01_16x16_05x05_src;
          *colKernelSource    = sgemm_Col_NT_B0_080_001_01_16x16_05x05_src;
          *cornerKernelSource = sgemm_Col_NT_B0_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = sgemm_Col_NT_B0_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B0_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = sgemm_Col_NT_B0_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = sgemm_Col_NT_B0_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = sgemm_Col_NT_B0_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = sgemm_Col_NT_B0_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NT_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = sgemm_Col_NT_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = sgemm_Col_NT_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = sgemm_Col_NT_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = sgemm_Col_NT_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = sgemm_Col_NT_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = sgemm_Col_NT_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = sgemm_Col_NT_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = sgemm_Col_NT_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NT_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = sgemm_Col_NT_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = sgemm_Col_NT_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = sgemm_Col_NT_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = sgemm_Col_NT_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = sgemm_Col_NT_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = sgemm_Col_NT_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = sgemm_Col_NT_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = sgemm_Col_NT_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 7 && microTileNumCols == 7 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NT_B0_112_112_08_16x16_07x07_src;
          *rowKernelSource    = sgemm_Col_NT_B0_001_112_08_16x16_07x07_src;
          *colKernelSource    = sgemm_Col_NT_B0_112_001_08_16x16_07x07_src;
          *cornerKernelSource = sgemm_Col_NT_B0_001_001_08_16x16_07x07_src;
          *sourceBuildOptions = sgemm_Col_NT_B0_112_112_08_16x16_07x07_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B0_112_112_08_16x16_07x07_bin;
          *rowKernelBinary    = sgemm_Col_NT_B0_001_112_08_16x16_07x07_bin;
          *colKernelBinary    = sgemm_Col_NT_B0_112_001_08_16x16_07x07_bin;
          *cornerKernelBinary = sgemm_Col_NT_B0_001_001_08_16x16_07x07_bin;
          *binaryBuildOptions = sgemm_Col_NT_B0_112_112_08_16x16_07x07_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_112_112_08_16x16_07x07_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_001_112_08_16x16_07x07_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_112_001_08_16x16_07x07_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_001_001_08_16x16_07x07_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 7 && microTileNumCols == 7 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NT_B0_112_112_01_16x16_07x07_src;
          *rowKernelSource    = sgemm_Col_NT_B0_001_112_01_16x16_07x07_src;
          *colKernelSource    = sgemm_Col_NT_B0_112_001_01_16x16_07x07_src;
          *cornerKernelSource = sgemm_Col_NT_B0_001_001_01_16x16_07x07_src;
          *sourceBuildOptions = sgemm_Col_NT_B0_112_112_01_16x16_07x07_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B0_112_112_01_16x16_07x07_bin;
          *rowKernelBinary    = sgemm_Col_NT_B0_001_112_01_16x16_07x07_bin;
          *colKernelBinary    = sgemm_Col_NT_B0_112_001_01_16x16_07x07_bin;
          *cornerKernelBinary = sgemm_Col_NT_B0_001_001_01_16x16_07x07_bin;
          *binaryBuildOptions = sgemm_Col_NT_B0_112_112_01_16x16_07x07_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_112_112_01_16x16_07x07_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_001_112_01_16x16_07x07_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_112_001_01_16x16_07x07_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_001_001_01_16x16_07x07_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NT_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = sgemm_Col_NT_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = sgemm_Col_NT_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = sgemm_Col_NT_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = sgemm_Col_NT_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = sgemm_Col_NT_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = sgemm_Col_NT_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = sgemm_Col_NT_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = sgemm_Col_NT_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NT_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = sgemm_Col_NT_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = sgemm_Col_NT_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = sgemm_Col_NT_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = sgemm_Col_NT_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = sgemm_Col_NT_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = sgemm_Col_NT_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = sgemm_Col_NT_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = sgemm_Col_NT_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NT_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = sgemm_Col_NT_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = sgemm_Col_NT_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = sgemm_Col_NT_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = sgemm_Col_NT_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = sgemm_Col_NT_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = sgemm_Col_NT_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = sgemm_Col_NT_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = sgemm_Col_NT_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NT_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = sgemm_Col_NT_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = sgemm_Col_NT_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = sgemm_Col_NT_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = sgemm_Col_NT_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = sgemm_Col_NT_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = sgemm_Col_NT_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = sgemm_Col_NT_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = sgemm_Col_NT_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NT_B1_096_096_08_16x16_06x06_src;
          *rowKernelSource    = sgemm_Col_NT_B1_001_096_08_16x16_06x06_src;
          *colKernelSource    = sgemm_Col_NT_B1_096_001_08_16x16_06x06_src;
          *cornerKernelSource = sgemm_Col_NT_B1_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = sgemm_Col_NT_B1_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B1_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = sgemm_Col_NT_B1_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = sgemm_Col_NT_B1_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = sgemm_Col_NT_B1_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = sgemm_Col_NT_B1_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NT_B1_096_096_01_16x16_06x06_src;
          *rowKernelSource    = sgemm_Col_NT_B1_001_096_01_16x16_06x06_src;
          *colKernelSource    = sgemm_Col_NT_B1_096_001_01_16x16_06x06_src;
          *cornerKernelSource = sgemm_Col_NT_B1_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = sgemm_Col_NT_B1_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B1_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = sgemm_Col_NT_B1_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = sgemm_Col_NT_B1_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = sgemm_Col_NT_B1_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = sgemm_Col_NT_B1_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 8 && microTileNumCols == 8 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NT_B1_128_128_08_16x16_08x08_src;
          *rowKernelSource    = sgemm_Col_NT_B1_001_128_08_16x16_08x08_src;
          *colKernelSource    = sgemm_Col_NT_B1_128_001_08_16x16_08x08_src;
          *cornerKernelSource = sgemm_Col_NT_B1_001_001_08_16x16_08x08_src;
          *sourceBuildOptions = sgemm_Col_NT_B1_128_128_08_16x16_08x08_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B1_128_128_08_16x16_08x08_bin;
          *rowKernelBinary    = sgemm_Col_NT_B1_001_128_08_16x16_08x08_bin;
          *colKernelBinary    = sgemm_Col_NT_B1_128_001_08_16x16_08x08_bin;
          *cornerKernelBinary = sgemm_Col_NT_B1_001_001_08_16x16_08x08_bin;
          *binaryBuildOptions = sgemm_Col_NT_B1_128_128_08_16x16_08x08_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_128_128_08_16x16_08x08_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_001_128_08_16x16_08x08_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_128_001_08_16x16_08x08_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_001_001_08_16x16_08x08_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 8 && microTileNumCols == 8 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NT_B1_128_128_01_16x16_08x08_src;
          *rowKernelSource    = sgemm_Col_NT_B1_001_128_01_16x16_08x08_src;
          *colKernelSource    = sgemm_Col_NT_B1_128_001_01_16x16_08x08_src;
          *cornerKernelSource = sgemm_Col_NT_B1_001_001_01_16x16_08x08_src;
          *sourceBuildOptions = sgemm_Col_NT_B1_128_128_01_16x16_08x08_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B1_128_128_01_16x16_08x08_bin;
          *rowKernelBinary    = sgemm_Col_NT_B1_001_128_01_16x16_08x08_bin;
          *colKernelBinary    = sgemm_Col_NT_B1_128_001_01_16x16_08x08_bin;
          *cornerKernelBinary = sgemm_Col_NT_B1_001_001_01_16x16_08x08_bin;
          *binaryBuildOptions = sgemm_Col_NT_B1_128_128_01_16x16_08x08_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_128_128_01_16x16_08x08_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_001_128_01_16x16_08x08_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_128_001_01_16x16_08x08_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_001_001_01_16x16_08x08_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NT_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = sgemm_Col_NT_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = sgemm_Col_NT_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = sgemm_Col_NT_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = sgemm_Col_NT_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = sgemm_Col_NT_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = sgemm_Col_NT_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = sgemm_Col_NT_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = sgemm_Col_NT_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NT_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = sgemm_Col_NT_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = sgemm_Col_NT_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = sgemm_Col_NT_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = sgemm_Col_NT_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = sgemm_Col_NT_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = sgemm_Col_NT_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = sgemm_Col_NT_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = sgemm_Col_NT_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NT_B1_080_080_08_16x16_05x05_src;
          *rowKernelSource    = sgemm_Col_NT_B1_001_080_08_16x16_05x05_src;
          *colKernelSource    = sgemm_Col_NT_B1_080_001_08_16x16_05x05_src;
          *cornerKernelSource = sgemm_Col_NT_B1_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = sgemm_Col_NT_B1_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B1_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = sgemm_Col_NT_B1_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = sgemm_Col_NT_B1_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = sgemm_Col_NT_B1_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = sgemm_Col_NT_B1_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NT_B1_080_080_01_16x16_05x05_src;
          *rowKernelSource    = sgemm_Col_NT_B1_001_080_01_16x16_05x05_src;
          *colKernelSource    = sgemm_Col_NT_B1_080_001_01_16x16_05x05_src;
          *cornerKernelSource = sgemm_Col_NT_B1_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = sgemm_Col_NT_B1_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B1_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = sgemm_Col_NT_B1_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = sgemm_Col_NT_B1_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = sgemm_Col_NT_B1_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = sgemm_Col_NT_B1_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NT_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = sgemm_Col_NT_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = sgemm_Col_NT_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = sgemm_Col_NT_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = sgemm_Col_NT_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = sgemm_Col_NT_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = sgemm_Col_NT_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = sgemm_Col_NT_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = sgemm_Col_NT_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NT_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = sgemm_Col_NT_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = sgemm_Col_NT_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = sgemm_Col_NT_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = sgemm_Col_NT_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = sgemm_Col_NT_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = sgemm_Col_NT_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = sgemm_Col_NT_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = sgemm_Col_NT_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 7 && microTileNumCols == 7 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NT_B1_112_112_08_16x16_07x07_src;
          *rowKernelSource    = sgemm_Col_NT_B1_001_112_08_16x16_07x07_src;
          *colKernelSource    = sgemm_Col_NT_B1_112_001_08_16x16_07x07_src;
          *cornerKernelSource = sgemm_Col_NT_B1_001_001_08_16x16_07x07_src;
          *sourceBuildOptions = sgemm_Col_NT_B1_112_112_08_16x16_07x07_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B1_112_112_08_16x16_07x07_bin;
          *rowKernelBinary    = sgemm_Col_NT_B1_001_112_08_16x16_07x07_bin;
          *colKernelBinary    = sgemm_Col_NT_B1_112_001_08_16x16_07x07_bin;
          *cornerKernelBinary = sgemm_Col_NT_B1_001_001_08_16x16_07x07_bin;
          *binaryBuildOptions = sgemm_Col_NT_B1_112_112_08_16x16_07x07_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_112_112_08_16x16_07x07_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_001_112_08_16x16_07x07_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_112_001_08_16x16_07x07_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_001_001_08_16x16_07x07_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 7 && microTileNumCols == 7 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NT_B1_112_112_01_16x16_07x07_src;
          *rowKernelSource    = sgemm_Col_NT_B1_001_112_01_16x16_07x07_src;
          *colKernelSource    = sgemm_Col_NT_B1_112_001_01_16x16_07x07_src;
          *cornerKernelSource = sgemm_Col_NT_B1_001_001_01_16x16_07x07_src;
          *sourceBuildOptions = sgemm_Col_NT_B1_112_112_01_16x16_07x07_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B1_112_112_01_16x16_07x07_bin;
          *rowKernelBinary    = sgemm_Col_NT_B1_001_112_01_16x16_07x07_bin;
          *colKernelBinary    = sgemm_Col_NT_B1_112_001_01_16x16_07x07_bin;
          *cornerKernelBinary = sgemm_Col_NT_B1_001_001_01_16x16_07x07_bin;
          *binaryBuildOptions = sgemm_Col_NT_B1_112_112_01_16x16_07x07_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_112_112_01_16x16_07x07_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_001_112_01_16x16_07x07_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_112_001_01_16x16_07x07_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_001_001_01_16x16_07x07_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NT_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = sgemm_Col_NT_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = sgemm_Col_NT_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = sgemm_Col_NT_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = sgemm_Col_NT_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = sgemm_Col_NT_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = sgemm_Col_NT_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = sgemm_Col_NT_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = sgemm_Col_NT_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NT_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = sgemm_Col_NT_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = sgemm_Col_NT_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = sgemm_Col_NT_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = sgemm_Col_NT_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = sgemm_Col_NT_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = sgemm_Col_NT_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = sgemm_Col_NT_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = sgemm_Col_NT_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_NT_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = sgemm_Col_NT_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = sgemm_Col_NT_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = sgemm_Col_NT_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = sgemm_Col_NT_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = sgemm_Col_NT_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = sgemm_Col_NT_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = sgemm_Col_NT_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = sgemm_Col_NT_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_NT_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = sgemm_Col_NT_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = sgemm_Col_NT_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = sgemm_Col_NT_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = sgemm_Col_NT_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_NT_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = sgemm_Col_NT_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = sgemm_Col_NT_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = sgemm_Col_NT_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = sgemm_Col_NT_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TN_B0_096_096_08_16x16_06x06_src;
          *rowKernelSource    = sgemm_Col_TN_B0_001_096_08_16x16_06x06_src;
          *colKernelSource    = sgemm_Col_TN_B0_096_001_08_16x16_06x06_src;
          *cornerKernelSource = sgemm_Col_TN_B0_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = sgemm_Col_TN_B0_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B0_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = sgemm_Col_TN_B0_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = sgemm_Col_TN_B0_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = sgemm_Col_TN_B0_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = sgemm_Col_TN_B0_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TN_B0_096_096_01_16x16_06x06_src;
          *rowKernelSource    = sgemm_Col_TN_B0_001_096_01_16x16_06x06_src;
          *colKernelSource    = sgemm_Col_TN_B0_096_001_01_16x16_06x06_src;
          *cornerKernelSource = sgemm_Col_TN_B0_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = sgemm_Col_TN_B0_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B0_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = sgemm_Col_TN_B0_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = sgemm_Col_TN_B0_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = sgemm_Col_TN_B0_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = sgemm_Col_TN_B0_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 8 && microTileNumCols == 8 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TN_B0_128_128_08_16x16_08x08_src;
          *rowKernelSource    = sgemm_Col_TN_B0_001_128_08_16x16_08x08_src;
          *colKernelSource    = sgemm_Col_TN_B0_128_001_08_16x16_08x08_src;
          *cornerKernelSource = sgemm_Col_TN_B0_001_001_08_16x16_08x08_src;
          *sourceBuildOptions = sgemm_Col_TN_B0_128_128_08_16x16_08x08_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B0_128_128_08_16x16_08x08_bin;
          *rowKernelBinary    = sgemm_Col_TN_B0_001_128_08_16x16_08x08_bin;
          *colKernelBinary    = sgemm_Col_TN_B0_128_001_08_16x16_08x08_bin;
          *cornerKernelBinary = sgemm_Col_TN_B0_001_001_08_16x16_08x08_bin;
          *binaryBuildOptions = sgemm_Col_TN_B0_128_128_08_16x16_08x08_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_128_128_08_16x16_08x08_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_001_128_08_16x16_08x08_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_128_001_08_16x16_08x08_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_001_001_08_16x16_08x08_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 8 && microTileNumCols == 8 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TN_B0_128_128_01_16x16_08x08_src;
          *rowKernelSource    = sgemm_Col_TN_B0_001_128_01_16x16_08x08_src;
          *colKernelSource    = sgemm_Col_TN_B0_128_001_01_16x16_08x08_src;
          *cornerKernelSource = sgemm_Col_TN_B0_001_001_01_16x16_08x08_src;
          *sourceBuildOptions = sgemm_Col_TN_B0_128_128_01_16x16_08x08_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B0_128_128_01_16x16_08x08_bin;
          *rowKernelBinary    = sgemm_Col_TN_B0_001_128_01_16x16_08x08_bin;
          *colKernelBinary    = sgemm_Col_TN_B0_128_001_01_16x16_08x08_bin;
          *cornerKernelBinary = sgemm_Col_TN_B0_001_001_01_16x16_08x08_bin;
          *binaryBuildOptions = sgemm_Col_TN_B0_128_128_01_16x16_08x08_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_128_128_01_16x16_08x08_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_001_128_01_16x16_08x08_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_128_001_01_16x16_08x08_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_001_001_01_16x16_08x08_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TN_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = sgemm_Col_TN_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = sgemm_Col_TN_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = sgemm_Col_TN_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = sgemm_Col_TN_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = sgemm_Col_TN_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = sgemm_Col_TN_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = sgemm_Col_TN_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = sgemm_Col_TN_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TN_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = sgemm_Col_TN_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = sgemm_Col_TN_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = sgemm_Col_TN_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = sgemm_Col_TN_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = sgemm_Col_TN_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = sgemm_Col_TN_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = sgemm_Col_TN_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = sgemm_Col_TN_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TN_B0_080_080_08_16x16_05x05_src;
          *rowKernelSource    = sgemm_Col_TN_B0_001_080_08_16x16_05x05_src;
          *colKernelSource    = sgemm_Col_TN_B0_080_001_08_16x16_05x05_src;
          *cornerKernelSource = sgemm_Col_TN_B0_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = sgemm_Col_TN_B0_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B0_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = sgemm_Col_TN_B0_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = sgemm_Col_TN_B0_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = sgemm_Col_TN_B0_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = sgemm_Col_TN_B0_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TN_B0_080_080_01_16x16_05x05_src;
          *rowKernelSource    = sgemm_Col_TN_B0_001_080_01_16x16_05x05_src;
          *colKernelSource    = sgemm_Col_TN_B0_080_001_01_16x16_05x05_src;
          *cornerKernelSource = sgemm_Col_TN_B0_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = sgemm_Col_TN_B0_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B0_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = sgemm_Col_TN_B0_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = sgemm_Col_TN_B0_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = sgemm_Col_TN_B0_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = sgemm_Col_TN_B0_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TN_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = sgemm_Col_TN_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = sgemm_Col_TN_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = sgemm_Col_TN_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = sgemm_Col_TN_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = sgemm_Col_TN_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = sgemm_Col_TN_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = sgemm_Col_TN_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = sgemm_Col_TN_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TN_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = sgemm_Col_TN_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = sgemm_Col_TN_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = sgemm_Col_TN_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = sgemm_Col_TN_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = sgemm_Col_TN_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = sgemm_Col_TN_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = sgemm_Col_TN_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = sgemm_Col_TN_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 7 && microTileNumCols == 7 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TN_B0_112_112_08_16x16_07x07_src;
          *rowKernelSource    = sgemm_Col_TN_B0_001_112_08_16x16_07x07_src;
          *colKernelSource    = sgemm_Col_TN_B0_112_001_08_16x16_07x07_src;
          *cornerKernelSource = sgemm_Col_TN_B0_001_001_08_16x16_07x07_src;
          *sourceBuildOptions = sgemm_Col_TN_B0_112_112_08_16x16_07x07_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B0_112_112_08_16x16_07x07_bin;
          *rowKernelBinary    = sgemm_Col_TN_B0_001_112_08_16x16_07x07_bin;
          *colKernelBinary    = sgemm_Col_TN_B0_112_001_08_16x16_07x07_bin;
          *cornerKernelBinary = sgemm_Col_TN_B0_001_001_08_16x16_07x07_bin;
          *binaryBuildOptions = sgemm_Col_TN_B0_112_112_08_16x16_07x07_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_112_112_08_16x16_07x07_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_001_112_08_16x16_07x07_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_112_001_08_16x16_07x07_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_001_001_08_16x16_07x07_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 7 && microTileNumCols == 7 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TN_B0_112_112_01_16x16_07x07_src;
          *rowKernelSource    = sgemm_Col_TN_B0_001_112_01_16x16_07x07_src;
          *colKernelSource    = sgemm_Col_TN_B0_112_001_01_16x16_07x07_src;
          *cornerKernelSource = sgemm_Col_TN_B0_001_001_01_16x16_07x07_src;
          *sourceBuildOptions = sgemm_Col_TN_B0_112_112_01_16x16_07x07_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B0_112_112_01_16x16_07x07_bin;
          *rowKernelBinary    = sgemm_Col_TN_B0_001_112_01_16x16_07x07_bin;
          *colKernelBinary    = sgemm_Col_TN_B0_112_001_01_16x16_07x07_bin;
          *cornerKernelBinary = sgemm_Col_TN_B0_001_001_01_16x16_07x07_bin;
          *binaryBuildOptions = sgemm_Col_TN_B0_112_112_01_16x16_07x07_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_112_112_01_16x16_07x07_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_001_112_01_16x16_07x07_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_112_001_01_16x16_07x07_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_001_001_01_16x16_07x07_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TN_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = sgemm_Col_TN_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = sgemm_Col_TN_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = sgemm_Col_TN_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = sgemm_Col_TN_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = sgemm_Col_TN_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = sgemm_Col_TN_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = sgemm_Col_TN_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = sgemm_Col_TN_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TN_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = sgemm_Col_TN_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = sgemm_Col_TN_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = sgemm_Col_TN_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = sgemm_Col_TN_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = sgemm_Col_TN_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = sgemm_Col_TN_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = sgemm_Col_TN_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = sgemm_Col_TN_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TN_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = sgemm_Col_TN_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = sgemm_Col_TN_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = sgemm_Col_TN_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = sgemm_Col_TN_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = sgemm_Col_TN_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = sgemm_Col_TN_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = sgemm_Col_TN_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = sgemm_Col_TN_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TN_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = sgemm_Col_TN_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = sgemm_Col_TN_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = sgemm_Col_TN_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = sgemm_Col_TN_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = sgemm_Col_TN_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = sgemm_Col_TN_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = sgemm_Col_TN_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = sgemm_Col_TN_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TN_B1_096_096_08_16x16_06x06_src;
          *rowKernelSource    = sgemm_Col_TN_B1_001_096_08_16x16_06x06_src;
          *colKernelSource    = sgemm_Col_TN_B1_096_001_08_16x16_06x06_src;
          *cornerKernelSource = sgemm_Col_TN_B1_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = sgemm_Col_TN_B1_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B1_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = sgemm_Col_TN_B1_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = sgemm_Col_TN_B1_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = sgemm_Col_TN_B1_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = sgemm_Col_TN_B1_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TN_B1_096_096_01_16x16_06x06_src;
          *rowKernelSource    = sgemm_Col_TN_B1_001_096_01_16x16_06x06_src;
          *colKernelSource    = sgemm_Col_TN_B1_096_001_01_16x16_06x06_src;
          *cornerKernelSource = sgemm_Col_TN_B1_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = sgemm_Col_TN_B1_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B1_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = sgemm_Col_TN_B1_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = sgemm_Col_TN_B1_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = sgemm_Col_TN_B1_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = sgemm_Col_TN_B1_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 8 && microTileNumCols == 8 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TN_B1_128_128_08_16x16_08x08_src;
          *rowKernelSource    = sgemm_Col_TN_B1_001_128_08_16x16_08x08_src;
          *colKernelSource    = sgemm_Col_TN_B1_128_001_08_16x16_08x08_src;
          *cornerKernelSource = sgemm_Col_TN_B1_001_001_08_16x16_08x08_src;
          *sourceBuildOptions = sgemm_Col_TN_B1_128_128_08_16x16_08x08_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B1_128_128_08_16x16_08x08_bin;
          *rowKernelBinary    = sgemm_Col_TN_B1_001_128_08_16x16_08x08_bin;
          *colKernelBinary    = sgemm_Col_TN_B1_128_001_08_16x16_08x08_bin;
          *cornerKernelBinary = sgemm_Col_TN_B1_001_001_08_16x16_08x08_bin;
          *binaryBuildOptions = sgemm_Col_TN_B1_128_128_08_16x16_08x08_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_128_128_08_16x16_08x08_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_001_128_08_16x16_08x08_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_128_001_08_16x16_08x08_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_001_001_08_16x16_08x08_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 8 && microTileNumCols == 8 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TN_B1_128_128_01_16x16_08x08_src;
          *rowKernelSource    = sgemm_Col_TN_B1_001_128_01_16x16_08x08_src;
          *colKernelSource    = sgemm_Col_TN_B1_128_001_01_16x16_08x08_src;
          *cornerKernelSource = sgemm_Col_TN_B1_001_001_01_16x16_08x08_src;
          *sourceBuildOptions = sgemm_Col_TN_B1_128_128_01_16x16_08x08_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B1_128_128_01_16x16_08x08_bin;
          *rowKernelBinary    = sgemm_Col_TN_B1_001_128_01_16x16_08x08_bin;
          *colKernelBinary    = sgemm_Col_TN_B1_128_001_01_16x16_08x08_bin;
          *cornerKernelBinary = sgemm_Col_TN_B1_001_001_01_16x16_08x08_bin;
          *binaryBuildOptions = sgemm_Col_TN_B1_128_128_01_16x16_08x08_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_128_128_01_16x16_08x08_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_001_128_01_16x16_08x08_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_128_001_01_16x16_08x08_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_001_001_01_16x16_08x08_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TN_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = sgemm_Col_TN_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = sgemm_Col_TN_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = sgemm_Col_TN_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = sgemm_Col_TN_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = sgemm_Col_TN_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = sgemm_Col_TN_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = sgemm_Col_TN_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = sgemm_Col_TN_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TN_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = sgemm_Col_TN_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = sgemm_Col_TN_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = sgemm_Col_TN_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = sgemm_Col_TN_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = sgemm_Col_TN_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = sgemm_Col_TN_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = sgemm_Col_TN_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = sgemm_Col_TN_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TN_B1_080_080_08_16x16_05x05_src;
          *rowKernelSource    = sgemm_Col_TN_B1_001_080_08_16x16_05x05_src;
          *colKernelSource    = sgemm_Col_TN_B1_080_001_08_16x16_05x05_src;
          *cornerKernelSource = sgemm_Col_TN_B1_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = sgemm_Col_TN_B1_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B1_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = sgemm_Col_TN_B1_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = sgemm_Col_TN_B1_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = sgemm_Col_TN_B1_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = sgemm_Col_TN_B1_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TN_B1_080_080_01_16x16_05x05_src;
          *rowKernelSource    = sgemm_Col_TN_B1_001_080_01_16x16_05x05_src;
          *colKernelSource    = sgemm_Col_TN_B1_080_001_01_16x16_05x05_src;
          *cornerKernelSource = sgemm_Col_TN_B1_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = sgemm_Col_TN_B1_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B1_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = sgemm_Col_TN_B1_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = sgemm_Col_TN_B1_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = sgemm_Col_TN_B1_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = sgemm_Col_TN_B1_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TN_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = sgemm_Col_TN_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = sgemm_Col_TN_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = sgemm_Col_TN_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = sgemm_Col_TN_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = sgemm_Col_TN_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = sgemm_Col_TN_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = sgemm_Col_TN_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = sgemm_Col_TN_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TN_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = sgemm_Col_TN_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = sgemm_Col_TN_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = sgemm_Col_TN_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = sgemm_Col_TN_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = sgemm_Col_TN_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = sgemm_Col_TN_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = sgemm_Col_TN_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = sgemm_Col_TN_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 7 && microTileNumCols == 7 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TN_B1_112_112_08_16x16_07x07_src;
          *rowKernelSource    = sgemm_Col_TN_B1_001_112_08_16x16_07x07_src;
          *colKernelSource    = sgemm_Col_TN_B1_112_001_08_16x16_07x07_src;
          *cornerKernelSource = sgemm_Col_TN_B1_001_001_08_16x16_07x07_src;
          *sourceBuildOptions = sgemm_Col_TN_B1_112_112_08_16x16_07x07_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B1_112_112_08_16x16_07x07_bin;
          *rowKernelBinary    = sgemm_Col_TN_B1_001_112_08_16x16_07x07_bin;
          *colKernelBinary    = sgemm_Col_TN_B1_112_001_08_16x16_07x07_bin;
          *cornerKernelBinary = sgemm_Col_TN_B1_001_001_08_16x16_07x07_bin;
          *binaryBuildOptions = sgemm_Col_TN_B1_112_112_08_16x16_07x07_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_112_112_08_16x16_07x07_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_001_112_08_16x16_07x07_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_112_001_08_16x16_07x07_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_001_001_08_16x16_07x07_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 7 && microTileNumCols == 7 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TN_B1_112_112_01_16x16_07x07_src;
          *rowKernelSource    = sgemm_Col_TN_B1_001_112_01_16x16_07x07_src;
          *colKernelSource    = sgemm_Col_TN_B1_112_001_01_16x16_07x07_src;
          *cornerKernelSource = sgemm_Col_TN_B1_001_001_01_16x16_07x07_src;
          *sourceBuildOptions = sgemm_Col_TN_B1_112_112_01_16x16_07x07_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B1_112_112_01_16x16_07x07_bin;
          *rowKernelBinary    = sgemm_Col_TN_B1_001_112_01_16x16_07x07_bin;
          *colKernelBinary    = sgemm_Col_TN_B1_112_001_01_16x16_07x07_bin;
          *cornerKernelBinary = sgemm_Col_TN_B1_001_001_01_16x16_07x07_bin;
          *binaryBuildOptions = sgemm_Col_TN_B1_112_112_01_16x16_07x07_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_112_112_01_16x16_07x07_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_001_112_01_16x16_07x07_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_112_001_01_16x16_07x07_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_001_001_01_16x16_07x07_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TN_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = sgemm_Col_TN_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = sgemm_Col_TN_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = sgemm_Col_TN_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = sgemm_Col_TN_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = sgemm_Col_TN_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = sgemm_Col_TN_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = sgemm_Col_TN_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = sgemm_Col_TN_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TN_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = sgemm_Col_TN_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = sgemm_Col_TN_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = sgemm_Col_TN_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = sgemm_Col_TN_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = sgemm_Col_TN_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = sgemm_Col_TN_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = sgemm_Col_TN_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = sgemm_Col_TN_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TN_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = sgemm_Col_TN_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = sgemm_Col_TN_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = sgemm_Col_TN_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = sgemm_Col_TN_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = sgemm_Col_TN_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = sgemm_Col_TN_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = sgemm_Col_TN_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = sgemm_Col_TN_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TN_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = sgemm_Col_TN_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = sgemm_Col_TN_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = sgemm_Col_TN_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = sgemm_Col_TN_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TN_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = sgemm_Col_TN_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = sgemm_Col_TN_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = sgemm_Col_TN_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = sgemm_Col_TN_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TT_B0_096_096_08_16x16_06x06_src;
          *rowKernelSource    = sgemm_Col_TT_B0_001_096_08_16x16_06x06_src;
          *colKernelSource    = sgemm_Col_TT_B0_096_001_08_16x16_06x06_src;
          *cornerKernelSource = sgemm_Col_TT_B0_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = sgemm_Col_TT_B0_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B0_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = sgemm_Col_TT_B0_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = sgemm_Col_TT_B0_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = sgemm_Col_TT_B0_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = sgemm_Col_TT_B0_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TT_B0_096_096_01_16x16_06x06_src;
          *rowKernelSource    = sgemm_Col_TT_B0_001_096_01_16x16_06x06_src;
          *colKernelSource    = sgemm_Col_TT_B0_096_001_01_16x16_06x06_src;
          *cornerKernelSource = sgemm_Col_TT_B0_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = sgemm_Col_TT_B0_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B0_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = sgemm_Col_TT_B0_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = sgemm_Col_TT_B0_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = sgemm_Col_TT_B0_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = sgemm_Col_TT_B0_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 8 && microTileNumCols == 8 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TT_B0_128_128_08_16x16_08x08_src;
          *rowKernelSource    = sgemm_Col_TT_B0_001_128_08_16x16_08x08_src;
          *colKernelSource    = sgemm_Col_TT_B0_128_001_08_16x16_08x08_src;
          *cornerKernelSource = sgemm_Col_TT_B0_001_001_08_16x16_08x08_src;
          *sourceBuildOptions = sgemm_Col_TT_B0_128_128_08_16x16_08x08_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B0_128_128_08_16x16_08x08_bin;
          *rowKernelBinary    = sgemm_Col_TT_B0_001_128_08_16x16_08x08_bin;
          *colKernelBinary    = sgemm_Col_TT_B0_128_001_08_16x16_08x08_bin;
          *cornerKernelBinary = sgemm_Col_TT_B0_001_001_08_16x16_08x08_bin;
          *binaryBuildOptions = sgemm_Col_TT_B0_128_128_08_16x16_08x08_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_128_128_08_16x16_08x08_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_001_128_08_16x16_08x08_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_128_001_08_16x16_08x08_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_001_001_08_16x16_08x08_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 8 && microTileNumCols == 8 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TT_B0_128_128_01_16x16_08x08_src;
          *rowKernelSource    = sgemm_Col_TT_B0_001_128_01_16x16_08x08_src;
          *colKernelSource    = sgemm_Col_TT_B0_128_001_01_16x16_08x08_src;
          *cornerKernelSource = sgemm_Col_TT_B0_001_001_01_16x16_08x08_src;
          *sourceBuildOptions = sgemm_Col_TT_B0_128_128_01_16x16_08x08_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B0_128_128_01_16x16_08x08_bin;
          *rowKernelBinary    = sgemm_Col_TT_B0_001_128_01_16x16_08x08_bin;
          *colKernelBinary    = sgemm_Col_TT_B0_128_001_01_16x16_08x08_bin;
          *cornerKernelBinary = sgemm_Col_TT_B0_001_001_01_16x16_08x08_bin;
          *binaryBuildOptions = sgemm_Col_TT_B0_128_128_01_16x16_08x08_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_128_128_01_16x16_08x08_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_001_128_01_16x16_08x08_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_128_001_01_16x16_08x08_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_001_001_01_16x16_08x08_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TT_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = sgemm_Col_TT_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = sgemm_Col_TT_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = sgemm_Col_TT_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = sgemm_Col_TT_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = sgemm_Col_TT_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = sgemm_Col_TT_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = sgemm_Col_TT_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = sgemm_Col_TT_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TT_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = sgemm_Col_TT_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = sgemm_Col_TT_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = sgemm_Col_TT_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = sgemm_Col_TT_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = sgemm_Col_TT_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = sgemm_Col_TT_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = sgemm_Col_TT_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = sgemm_Col_TT_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TT_B0_080_080_08_16x16_05x05_src;
          *rowKernelSource    = sgemm_Col_TT_B0_001_080_08_16x16_05x05_src;
          *colKernelSource    = sgemm_Col_TT_B0_080_001_08_16x16_05x05_src;
          *cornerKernelSource = sgemm_Col_TT_B0_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = sgemm_Col_TT_B0_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B0_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = sgemm_Col_TT_B0_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = sgemm_Col_TT_B0_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = sgemm_Col_TT_B0_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = sgemm_Col_TT_B0_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TT_B0_080_080_01_16x16_05x05_src;
          *rowKernelSource    = sgemm_Col_TT_B0_001_080_01_16x16_05x05_src;
          *colKernelSource    = sgemm_Col_TT_B0_080_001_01_16x16_05x05_src;
          *cornerKernelSource = sgemm_Col_TT_B0_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = sgemm_Col_TT_B0_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B0_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = sgemm_Col_TT_B0_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = sgemm_Col_TT_B0_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = sgemm_Col_TT_B0_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = sgemm_Col_TT_B0_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TT_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = sgemm_Col_TT_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = sgemm_Col_TT_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = sgemm_Col_TT_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = sgemm_Col_TT_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = sgemm_Col_TT_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = sgemm_Col_TT_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = sgemm_Col_TT_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = sgemm_Col_TT_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TT_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = sgemm_Col_TT_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = sgemm_Col_TT_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = sgemm_Col_TT_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = sgemm_Col_TT_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = sgemm_Col_TT_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = sgemm_Col_TT_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = sgemm_Col_TT_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = sgemm_Col_TT_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 7 && microTileNumCols == 7 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TT_B0_112_112_08_16x16_07x07_src;
          *rowKernelSource    = sgemm_Col_TT_B0_001_112_08_16x16_07x07_src;
          *colKernelSource    = sgemm_Col_TT_B0_112_001_08_16x16_07x07_src;
          *cornerKernelSource = sgemm_Col_TT_B0_001_001_08_16x16_07x07_src;
          *sourceBuildOptions = sgemm_Col_TT_B0_112_112_08_16x16_07x07_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B0_112_112_08_16x16_07x07_bin;
          *rowKernelBinary    = sgemm_Col_TT_B0_001_112_08_16x16_07x07_bin;
          *colKernelBinary    = sgemm_Col_TT_B0_112_001_08_16x16_07x07_bin;
          *cornerKernelBinary = sgemm_Col_TT_B0_001_001_08_16x16_07x07_bin;
          *binaryBuildOptions = sgemm_Col_TT_B0_112_112_08_16x16_07x07_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_112_112_08_16x16_07x07_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_001_112_08_16x16_07x07_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_112_001_08_16x16_07x07_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_001_001_08_16x16_07x07_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 7 && microTileNumCols == 7 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TT_B0_112_112_01_16x16_07x07_src;
          *rowKernelSource    = sgemm_Col_TT_B0_001_112_01_16x16_07x07_src;
          *colKernelSource    = sgemm_Col_TT_B0_112_001_01_16x16_07x07_src;
          *cornerKernelSource = sgemm_Col_TT_B0_001_001_01_16x16_07x07_src;
          *sourceBuildOptions = sgemm_Col_TT_B0_112_112_01_16x16_07x07_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B0_112_112_01_16x16_07x07_bin;
          *rowKernelBinary    = sgemm_Col_TT_B0_001_112_01_16x16_07x07_bin;
          *colKernelBinary    = sgemm_Col_TT_B0_112_001_01_16x16_07x07_bin;
          *cornerKernelBinary = sgemm_Col_TT_B0_001_001_01_16x16_07x07_bin;
          *binaryBuildOptions = sgemm_Col_TT_B0_112_112_01_16x16_07x07_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_112_112_01_16x16_07x07_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_001_112_01_16x16_07x07_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_112_001_01_16x16_07x07_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_001_001_01_16x16_07x07_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TT_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = sgemm_Col_TT_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = sgemm_Col_TT_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = sgemm_Col_TT_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = sgemm_Col_TT_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = sgemm_Col_TT_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = sgemm_Col_TT_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = sgemm_Col_TT_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = sgemm_Col_TT_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TT_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = sgemm_Col_TT_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = sgemm_Col_TT_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = sgemm_Col_TT_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = sgemm_Col_TT_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = sgemm_Col_TT_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = sgemm_Col_TT_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = sgemm_Col_TT_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = sgemm_Col_TT_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TT_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = sgemm_Col_TT_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = sgemm_Col_TT_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = sgemm_Col_TT_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = sgemm_Col_TT_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = sgemm_Col_TT_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = sgemm_Col_TT_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = sgemm_Col_TT_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = sgemm_Col_TT_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TT_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = sgemm_Col_TT_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = sgemm_Col_TT_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = sgemm_Col_TT_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = sgemm_Col_TT_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = sgemm_Col_TT_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = sgemm_Col_TT_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = sgemm_Col_TT_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = sgemm_Col_TT_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TT_B1_096_096_08_16x16_06x06_src;
          *rowKernelSource    = sgemm_Col_TT_B1_001_096_08_16x16_06x06_src;
          *colKernelSource    = sgemm_Col_TT_B1_096_001_08_16x16_06x06_src;
          *cornerKernelSource = sgemm_Col_TT_B1_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = sgemm_Col_TT_B1_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B1_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = sgemm_Col_TT_B1_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = sgemm_Col_TT_B1_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = sgemm_Col_TT_B1_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = sgemm_Col_TT_B1_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TT_B1_096_096_01_16x16_06x06_src;
          *rowKernelSource    = sgemm_Col_TT_B1_001_096_01_16x16_06x06_src;
          *colKernelSource    = sgemm_Col_TT_B1_096_001_01_16x16_06x06_src;
          *cornerKernelSource = sgemm_Col_TT_B1_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = sgemm_Col_TT_B1_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B1_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = sgemm_Col_TT_B1_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = sgemm_Col_TT_B1_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = sgemm_Col_TT_B1_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = sgemm_Col_TT_B1_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 8 && microTileNumCols == 8 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TT_B1_128_128_08_16x16_08x08_src;
          *rowKernelSource    = sgemm_Col_TT_B1_001_128_08_16x16_08x08_src;
          *colKernelSource    = sgemm_Col_TT_B1_128_001_08_16x16_08x08_src;
          *cornerKernelSource = sgemm_Col_TT_B1_001_001_08_16x16_08x08_src;
          *sourceBuildOptions = sgemm_Col_TT_B1_128_128_08_16x16_08x08_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B1_128_128_08_16x16_08x08_bin;
          *rowKernelBinary    = sgemm_Col_TT_B1_001_128_08_16x16_08x08_bin;
          *colKernelBinary    = sgemm_Col_TT_B1_128_001_08_16x16_08x08_bin;
          *cornerKernelBinary = sgemm_Col_TT_B1_001_001_08_16x16_08x08_bin;
          *binaryBuildOptions = sgemm_Col_TT_B1_128_128_08_16x16_08x08_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_128_128_08_16x16_08x08_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_001_128_08_16x16_08x08_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_128_001_08_16x16_08x08_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_001_001_08_16x16_08x08_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 8 && microTileNumCols == 8 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TT_B1_128_128_01_16x16_08x08_src;
          *rowKernelSource    = sgemm_Col_TT_B1_001_128_01_16x16_08x08_src;
          *colKernelSource    = sgemm_Col_TT_B1_128_001_01_16x16_08x08_src;
          *cornerKernelSource = sgemm_Col_TT_B1_001_001_01_16x16_08x08_src;
          *sourceBuildOptions = sgemm_Col_TT_B1_128_128_01_16x16_08x08_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B1_128_128_01_16x16_08x08_bin;
          *rowKernelBinary    = sgemm_Col_TT_B1_001_128_01_16x16_08x08_bin;
          *colKernelBinary    = sgemm_Col_TT_B1_128_001_01_16x16_08x08_bin;
          *cornerKernelBinary = sgemm_Col_TT_B1_001_001_01_16x16_08x08_bin;
          *binaryBuildOptions = sgemm_Col_TT_B1_128_128_01_16x16_08x08_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_128_128_01_16x16_08x08_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_001_128_01_16x16_08x08_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_128_001_01_16x16_08x08_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_001_001_01_16x16_08x08_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TT_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = sgemm_Col_TT_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = sgemm_Col_TT_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = sgemm_Col_TT_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = sgemm_Col_TT_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = sgemm_Col_TT_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = sgemm_Col_TT_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = sgemm_Col_TT_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = sgemm_Col_TT_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TT_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = sgemm_Col_TT_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = sgemm_Col_TT_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = sgemm_Col_TT_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = sgemm_Col_TT_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = sgemm_Col_TT_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = sgemm_Col_TT_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = sgemm_Col_TT_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = sgemm_Col_TT_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TT_B1_080_080_08_16x16_05x05_src;
          *rowKernelSource    = sgemm_Col_TT_B1_001_080_08_16x16_05x05_src;
          *colKernelSource    = sgemm_Col_TT_B1_080_001_08_16x16_05x05_src;
          *cornerKernelSource = sgemm_Col_TT_B1_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = sgemm_Col_TT_B1_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B1_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = sgemm_Col_TT_B1_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = sgemm_Col_TT_B1_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = sgemm_Col_TT_B1_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = sgemm_Col_TT_B1_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TT_B1_080_080_01_16x16_05x05_src;
          *rowKernelSource    = sgemm_Col_TT_B1_001_080_01_16x16_05x05_src;
          *colKernelSource    = sgemm_Col_TT_B1_080_001_01_16x16_05x05_src;
          *cornerKernelSource = sgemm_Col_TT_B1_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = sgemm_Col_TT_B1_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B1_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = sgemm_Col_TT_B1_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = sgemm_Col_TT_B1_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = sgemm_Col_TT_B1_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = sgemm_Col_TT_B1_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TT_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = sgemm_Col_TT_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = sgemm_Col_TT_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = sgemm_Col_TT_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = sgemm_Col_TT_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = sgemm_Col_TT_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = sgemm_Col_TT_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = sgemm_Col_TT_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = sgemm_Col_TT_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TT_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = sgemm_Col_TT_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = sgemm_Col_TT_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = sgemm_Col_TT_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = sgemm_Col_TT_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = sgemm_Col_TT_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = sgemm_Col_TT_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = sgemm_Col_TT_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = sgemm_Col_TT_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 7 && microTileNumCols == 7 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TT_B1_112_112_08_16x16_07x07_src;
          *rowKernelSource    = sgemm_Col_TT_B1_001_112_08_16x16_07x07_src;
          *colKernelSource    = sgemm_Col_TT_B1_112_001_08_16x16_07x07_src;
          *cornerKernelSource = sgemm_Col_TT_B1_001_001_08_16x16_07x07_src;
          *sourceBuildOptions = sgemm_Col_TT_B1_112_112_08_16x16_07x07_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B1_112_112_08_16x16_07x07_bin;
          *rowKernelBinary    = sgemm_Col_TT_B1_001_112_08_16x16_07x07_bin;
          *colKernelBinary    = sgemm_Col_TT_B1_112_001_08_16x16_07x07_bin;
          *cornerKernelBinary = sgemm_Col_TT_B1_001_001_08_16x16_07x07_bin;
          *binaryBuildOptions = sgemm_Col_TT_B1_112_112_08_16x16_07x07_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_112_112_08_16x16_07x07_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_001_112_08_16x16_07x07_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_112_001_08_16x16_07x07_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_001_001_08_16x16_07x07_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 7 && microTileNumCols == 7 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TT_B1_112_112_01_16x16_07x07_src;
          *rowKernelSource    = sgemm_Col_TT_B1_001_112_01_16x16_07x07_src;
          *colKernelSource    = sgemm_Col_TT_B1_112_001_01_16x16_07x07_src;
          *cornerKernelSource = sgemm_Col_TT_B1_001_001_01_16x16_07x07_src;
          *sourceBuildOptions = sgemm_Col_TT_B1_112_112_01_16x16_07x07_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B1_112_112_01_16x16_07x07_bin;
          *rowKernelBinary    = sgemm_Col_TT_B1_001_112_01_16x16_07x07_bin;
          *colKernelBinary    = sgemm_Col_TT_B1_112_001_01_16x16_07x07_bin;
          *cornerKernelBinary = sgemm_Col_TT_B1_001_001_01_16x16_07x07_bin;
          *binaryBuildOptions = sgemm_Col_TT_B1_112_112_01_16x16_07x07_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_112_112_01_16x16_07x07_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_001_112_01_16x16_07x07_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_112_001_01_16x16_07x07_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_001_001_01_16x16_07x07_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TT_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = sgemm_Col_TT_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = sgemm_Col_TT_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = sgemm_Col_TT_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = sgemm_Col_TT_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = sgemm_Col_TT_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = sgemm_Col_TT_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = sgemm_Col_TT_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = sgemm_Col_TT_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TT_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = sgemm_Col_TT_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = sgemm_Col_TT_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = sgemm_Col_TT_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = sgemm_Col_TT_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = sgemm_Col_TT_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = sgemm_Col_TT_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = sgemm_Col_TT_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = sgemm_Col_TT_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = sgemm_Col_TT_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = sgemm_Col_TT_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = sgemm_Col_TT_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = sgemm_Col_TT_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = sgemm_Col_TT_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = sgemm_Col_TT_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = sgemm_Col_TT_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = sgemm_Col_TT_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = sgemm_Col_TT_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = sgemm_Col_TT_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = sgemm_Col_TT_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = sgemm_Col_TT_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = sgemm_Col_TT_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = sgemm_Col_TT_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = sgemm_Col_TT_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = sgemm_Col_TT_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = sgemm_Col_TT_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = sgemm_Col_TT_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = sgemm_Col_TT_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      }
    }
  }
  return false; // didn't find a match
}

// dgemm kernel selection specific
template<>
bool gemmSelectKernelSpecific<double>(
  clblasOrder order,
  clblasTranspose transA,
  clblasTranspose transB,
  bool betaNonZero,
  unsigned int workGroupNumRows,
  unsigned int workGroupNumCols,
  unsigned int microTileNumRows,
  unsigned int microTileNumCols,
  unsigned int unroll,
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
  cl_kernel  **cornerClKernel
) {
  if (order == clblasColumnMajor) {
    if (transA == clblasNoTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NN_B0_096_096_08_16x16_06x06_src;
          *rowKernelSource    = dgemm_Col_NN_B0_001_096_08_16x16_06x06_src;
          *colKernelSource    = dgemm_Col_NN_B0_096_001_08_16x16_06x06_src;
          *cornerKernelSource = dgemm_Col_NN_B0_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = dgemm_Col_NN_B0_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B0_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = dgemm_Col_NN_B0_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = dgemm_Col_NN_B0_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = dgemm_Col_NN_B0_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = dgemm_Col_NN_B0_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NN_B0_096_096_01_16x16_06x06_src;
          *rowKernelSource    = dgemm_Col_NN_B0_001_096_01_16x16_06x06_src;
          *colKernelSource    = dgemm_Col_NN_B0_096_001_01_16x16_06x06_src;
          *cornerKernelSource = dgemm_Col_NN_B0_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = dgemm_Col_NN_B0_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B0_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = dgemm_Col_NN_B0_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = dgemm_Col_NN_B0_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = dgemm_Col_NN_B0_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = dgemm_Col_NN_B0_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NN_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = dgemm_Col_NN_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = dgemm_Col_NN_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = dgemm_Col_NN_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = dgemm_Col_NN_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = dgemm_Col_NN_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = dgemm_Col_NN_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = dgemm_Col_NN_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = dgemm_Col_NN_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NN_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = dgemm_Col_NN_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = dgemm_Col_NN_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = dgemm_Col_NN_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = dgemm_Col_NN_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = dgemm_Col_NN_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = dgemm_Col_NN_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = dgemm_Col_NN_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = dgemm_Col_NN_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NN_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = dgemm_Col_NN_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = dgemm_Col_NN_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = dgemm_Col_NN_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = dgemm_Col_NN_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = dgemm_Col_NN_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = dgemm_Col_NN_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = dgemm_Col_NN_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = dgemm_Col_NN_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NN_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = dgemm_Col_NN_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = dgemm_Col_NN_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = dgemm_Col_NN_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = dgemm_Col_NN_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = dgemm_Col_NN_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = dgemm_Col_NN_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = dgemm_Col_NN_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = dgemm_Col_NN_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NN_B0_080_080_08_16x16_05x05_src;
          *rowKernelSource    = dgemm_Col_NN_B0_001_080_08_16x16_05x05_src;
          *colKernelSource    = dgemm_Col_NN_B0_080_001_08_16x16_05x05_src;
          *cornerKernelSource = dgemm_Col_NN_B0_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = dgemm_Col_NN_B0_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B0_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = dgemm_Col_NN_B0_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = dgemm_Col_NN_B0_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = dgemm_Col_NN_B0_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = dgemm_Col_NN_B0_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NN_B0_080_080_01_16x16_05x05_src;
          *rowKernelSource    = dgemm_Col_NN_B0_001_080_01_16x16_05x05_src;
          *colKernelSource    = dgemm_Col_NN_B0_080_001_01_16x16_05x05_src;
          *cornerKernelSource = dgemm_Col_NN_B0_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = dgemm_Col_NN_B0_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B0_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = dgemm_Col_NN_B0_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = dgemm_Col_NN_B0_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = dgemm_Col_NN_B0_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = dgemm_Col_NN_B0_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NN_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = dgemm_Col_NN_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = dgemm_Col_NN_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = dgemm_Col_NN_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = dgemm_Col_NN_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = dgemm_Col_NN_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = dgemm_Col_NN_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = dgemm_Col_NN_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = dgemm_Col_NN_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NN_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = dgemm_Col_NN_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = dgemm_Col_NN_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = dgemm_Col_NN_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = dgemm_Col_NN_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = dgemm_Col_NN_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = dgemm_Col_NN_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = dgemm_Col_NN_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = dgemm_Col_NN_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NN_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = dgemm_Col_NN_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = dgemm_Col_NN_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = dgemm_Col_NN_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = dgemm_Col_NN_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = dgemm_Col_NN_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = dgemm_Col_NN_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = dgemm_Col_NN_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = dgemm_Col_NN_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NN_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = dgemm_Col_NN_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = dgemm_Col_NN_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = dgemm_Col_NN_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = dgemm_Col_NN_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = dgemm_Col_NN_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = dgemm_Col_NN_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = dgemm_Col_NN_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = dgemm_Col_NN_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NN_B1_096_096_08_16x16_06x06_src;
          *rowKernelSource    = dgemm_Col_NN_B1_001_096_08_16x16_06x06_src;
          *colKernelSource    = dgemm_Col_NN_B1_096_001_08_16x16_06x06_src;
          *cornerKernelSource = dgemm_Col_NN_B1_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = dgemm_Col_NN_B1_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B1_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = dgemm_Col_NN_B1_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = dgemm_Col_NN_B1_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = dgemm_Col_NN_B1_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = dgemm_Col_NN_B1_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NN_B1_096_096_01_16x16_06x06_src;
          *rowKernelSource    = dgemm_Col_NN_B1_001_096_01_16x16_06x06_src;
          *colKernelSource    = dgemm_Col_NN_B1_096_001_01_16x16_06x06_src;
          *cornerKernelSource = dgemm_Col_NN_B1_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = dgemm_Col_NN_B1_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B1_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = dgemm_Col_NN_B1_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = dgemm_Col_NN_B1_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = dgemm_Col_NN_B1_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = dgemm_Col_NN_B1_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NN_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = dgemm_Col_NN_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = dgemm_Col_NN_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = dgemm_Col_NN_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = dgemm_Col_NN_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = dgemm_Col_NN_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = dgemm_Col_NN_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = dgemm_Col_NN_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = dgemm_Col_NN_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NN_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = dgemm_Col_NN_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = dgemm_Col_NN_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = dgemm_Col_NN_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = dgemm_Col_NN_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = dgemm_Col_NN_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = dgemm_Col_NN_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = dgemm_Col_NN_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = dgemm_Col_NN_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NN_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = dgemm_Col_NN_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = dgemm_Col_NN_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = dgemm_Col_NN_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = dgemm_Col_NN_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = dgemm_Col_NN_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = dgemm_Col_NN_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = dgemm_Col_NN_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = dgemm_Col_NN_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NN_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = dgemm_Col_NN_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = dgemm_Col_NN_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = dgemm_Col_NN_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = dgemm_Col_NN_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = dgemm_Col_NN_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = dgemm_Col_NN_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = dgemm_Col_NN_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = dgemm_Col_NN_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NN_B1_080_080_08_16x16_05x05_src;
          *rowKernelSource    = dgemm_Col_NN_B1_001_080_08_16x16_05x05_src;
          *colKernelSource    = dgemm_Col_NN_B1_080_001_08_16x16_05x05_src;
          *cornerKernelSource = dgemm_Col_NN_B1_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = dgemm_Col_NN_B1_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B1_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = dgemm_Col_NN_B1_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = dgemm_Col_NN_B1_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = dgemm_Col_NN_B1_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = dgemm_Col_NN_B1_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NN_B1_080_080_01_16x16_05x05_src;
          *rowKernelSource    = dgemm_Col_NN_B1_001_080_01_16x16_05x05_src;
          *colKernelSource    = dgemm_Col_NN_B1_080_001_01_16x16_05x05_src;
          *cornerKernelSource = dgemm_Col_NN_B1_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = dgemm_Col_NN_B1_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B1_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = dgemm_Col_NN_B1_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = dgemm_Col_NN_B1_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = dgemm_Col_NN_B1_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = dgemm_Col_NN_B1_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NN_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = dgemm_Col_NN_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = dgemm_Col_NN_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = dgemm_Col_NN_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = dgemm_Col_NN_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = dgemm_Col_NN_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = dgemm_Col_NN_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = dgemm_Col_NN_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = dgemm_Col_NN_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NN_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = dgemm_Col_NN_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = dgemm_Col_NN_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = dgemm_Col_NN_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = dgemm_Col_NN_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = dgemm_Col_NN_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = dgemm_Col_NN_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = dgemm_Col_NN_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = dgemm_Col_NN_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NN_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = dgemm_Col_NN_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = dgemm_Col_NN_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = dgemm_Col_NN_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = dgemm_Col_NN_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = dgemm_Col_NN_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = dgemm_Col_NN_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = dgemm_Col_NN_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = dgemm_Col_NN_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NN_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = dgemm_Col_NN_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = dgemm_Col_NN_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = dgemm_Col_NN_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = dgemm_Col_NN_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NN_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = dgemm_Col_NN_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = dgemm_Col_NN_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = dgemm_Col_NN_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = dgemm_Col_NN_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      }
    } else if (transA == clblasNoTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NT_B0_096_096_08_16x16_06x06_src;
          *rowKernelSource    = dgemm_Col_NT_B0_001_096_08_16x16_06x06_src;
          *colKernelSource    = dgemm_Col_NT_B0_096_001_08_16x16_06x06_src;
          *cornerKernelSource = dgemm_Col_NT_B0_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = dgemm_Col_NT_B0_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B0_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = dgemm_Col_NT_B0_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = dgemm_Col_NT_B0_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = dgemm_Col_NT_B0_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = dgemm_Col_NT_B0_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NT_B0_096_096_01_16x16_06x06_src;
          *rowKernelSource    = dgemm_Col_NT_B0_001_096_01_16x16_06x06_src;
          *colKernelSource    = dgemm_Col_NT_B0_096_001_01_16x16_06x06_src;
          *cornerKernelSource = dgemm_Col_NT_B0_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = dgemm_Col_NT_B0_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B0_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = dgemm_Col_NT_B0_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = dgemm_Col_NT_B0_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = dgemm_Col_NT_B0_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = dgemm_Col_NT_B0_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NT_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = dgemm_Col_NT_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = dgemm_Col_NT_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = dgemm_Col_NT_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = dgemm_Col_NT_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = dgemm_Col_NT_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = dgemm_Col_NT_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = dgemm_Col_NT_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = dgemm_Col_NT_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NT_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = dgemm_Col_NT_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = dgemm_Col_NT_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = dgemm_Col_NT_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = dgemm_Col_NT_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = dgemm_Col_NT_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = dgemm_Col_NT_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = dgemm_Col_NT_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = dgemm_Col_NT_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NT_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = dgemm_Col_NT_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = dgemm_Col_NT_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = dgemm_Col_NT_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = dgemm_Col_NT_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = dgemm_Col_NT_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = dgemm_Col_NT_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = dgemm_Col_NT_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = dgemm_Col_NT_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NT_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = dgemm_Col_NT_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = dgemm_Col_NT_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = dgemm_Col_NT_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = dgemm_Col_NT_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = dgemm_Col_NT_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = dgemm_Col_NT_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = dgemm_Col_NT_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = dgemm_Col_NT_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NT_B0_080_080_08_16x16_05x05_src;
          *rowKernelSource    = dgemm_Col_NT_B0_001_080_08_16x16_05x05_src;
          *colKernelSource    = dgemm_Col_NT_B0_080_001_08_16x16_05x05_src;
          *cornerKernelSource = dgemm_Col_NT_B0_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = dgemm_Col_NT_B0_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B0_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = dgemm_Col_NT_B0_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = dgemm_Col_NT_B0_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = dgemm_Col_NT_B0_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = dgemm_Col_NT_B0_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NT_B0_080_080_01_16x16_05x05_src;
          *rowKernelSource    = dgemm_Col_NT_B0_001_080_01_16x16_05x05_src;
          *colKernelSource    = dgemm_Col_NT_B0_080_001_01_16x16_05x05_src;
          *cornerKernelSource = dgemm_Col_NT_B0_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = dgemm_Col_NT_B0_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B0_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = dgemm_Col_NT_B0_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = dgemm_Col_NT_B0_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = dgemm_Col_NT_B0_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = dgemm_Col_NT_B0_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NT_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = dgemm_Col_NT_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = dgemm_Col_NT_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = dgemm_Col_NT_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = dgemm_Col_NT_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = dgemm_Col_NT_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = dgemm_Col_NT_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = dgemm_Col_NT_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = dgemm_Col_NT_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NT_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = dgemm_Col_NT_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = dgemm_Col_NT_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = dgemm_Col_NT_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = dgemm_Col_NT_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = dgemm_Col_NT_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = dgemm_Col_NT_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = dgemm_Col_NT_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = dgemm_Col_NT_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NT_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = dgemm_Col_NT_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = dgemm_Col_NT_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = dgemm_Col_NT_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = dgemm_Col_NT_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = dgemm_Col_NT_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = dgemm_Col_NT_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = dgemm_Col_NT_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = dgemm_Col_NT_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NT_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = dgemm_Col_NT_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = dgemm_Col_NT_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = dgemm_Col_NT_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = dgemm_Col_NT_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = dgemm_Col_NT_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = dgemm_Col_NT_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = dgemm_Col_NT_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = dgemm_Col_NT_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NT_B1_096_096_08_16x16_06x06_src;
          *rowKernelSource    = dgemm_Col_NT_B1_001_096_08_16x16_06x06_src;
          *colKernelSource    = dgemm_Col_NT_B1_096_001_08_16x16_06x06_src;
          *cornerKernelSource = dgemm_Col_NT_B1_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = dgemm_Col_NT_B1_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B1_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = dgemm_Col_NT_B1_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = dgemm_Col_NT_B1_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = dgemm_Col_NT_B1_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = dgemm_Col_NT_B1_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NT_B1_096_096_01_16x16_06x06_src;
          *rowKernelSource    = dgemm_Col_NT_B1_001_096_01_16x16_06x06_src;
          *colKernelSource    = dgemm_Col_NT_B1_096_001_01_16x16_06x06_src;
          *cornerKernelSource = dgemm_Col_NT_B1_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = dgemm_Col_NT_B1_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B1_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = dgemm_Col_NT_B1_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = dgemm_Col_NT_B1_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = dgemm_Col_NT_B1_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = dgemm_Col_NT_B1_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NT_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = dgemm_Col_NT_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = dgemm_Col_NT_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = dgemm_Col_NT_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = dgemm_Col_NT_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = dgemm_Col_NT_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = dgemm_Col_NT_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = dgemm_Col_NT_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = dgemm_Col_NT_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NT_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = dgemm_Col_NT_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = dgemm_Col_NT_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = dgemm_Col_NT_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = dgemm_Col_NT_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = dgemm_Col_NT_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = dgemm_Col_NT_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = dgemm_Col_NT_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = dgemm_Col_NT_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NT_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = dgemm_Col_NT_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = dgemm_Col_NT_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = dgemm_Col_NT_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = dgemm_Col_NT_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = dgemm_Col_NT_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = dgemm_Col_NT_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = dgemm_Col_NT_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = dgemm_Col_NT_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NT_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = dgemm_Col_NT_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = dgemm_Col_NT_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = dgemm_Col_NT_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = dgemm_Col_NT_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = dgemm_Col_NT_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = dgemm_Col_NT_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = dgemm_Col_NT_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = dgemm_Col_NT_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NT_B1_080_080_08_16x16_05x05_src;
          *rowKernelSource    = dgemm_Col_NT_B1_001_080_08_16x16_05x05_src;
          *colKernelSource    = dgemm_Col_NT_B1_080_001_08_16x16_05x05_src;
          *cornerKernelSource = dgemm_Col_NT_B1_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = dgemm_Col_NT_B1_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B1_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = dgemm_Col_NT_B1_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = dgemm_Col_NT_B1_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = dgemm_Col_NT_B1_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = dgemm_Col_NT_B1_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NT_B1_080_080_01_16x16_05x05_src;
          *rowKernelSource    = dgemm_Col_NT_B1_001_080_01_16x16_05x05_src;
          *colKernelSource    = dgemm_Col_NT_B1_080_001_01_16x16_05x05_src;
          *cornerKernelSource = dgemm_Col_NT_B1_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = dgemm_Col_NT_B1_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B1_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = dgemm_Col_NT_B1_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = dgemm_Col_NT_B1_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = dgemm_Col_NT_B1_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = dgemm_Col_NT_B1_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NT_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = dgemm_Col_NT_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = dgemm_Col_NT_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = dgemm_Col_NT_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = dgemm_Col_NT_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = dgemm_Col_NT_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = dgemm_Col_NT_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = dgemm_Col_NT_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = dgemm_Col_NT_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NT_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = dgemm_Col_NT_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = dgemm_Col_NT_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = dgemm_Col_NT_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = dgemm_Col_NT_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = dgemm_Col_NT_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = dgemm_Col_NT_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = dgemm_Col_NT_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = dgemm_Col_NT_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_NT_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = dgemm_Col_NT_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = dgemm_Col_NT_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = dgemm_Col_NT_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = dgemm_Col_NT_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = dgemm_Col_NT_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = dgemm_Col_NT_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = dgemm_Col_NT_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = dgemm_Col_NT_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_NT_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = dgemm_Col_NT_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = dgemm_Col_NT_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = dgemm_Col_NT_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = dgemm_Col_NT_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_NT_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = dgemm_Col_NT_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = dgemm_Col_NT_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = dgemm_Col_NT_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = dgemm_Col_NT_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TN_B0_096_096_08_16x16_06x06_src;
          *rowKernelSource    = dgemm_Col_TN_B0_001_096_08_16x16_06x06_src;
          *colKernelSource    = dgemm_Col_TN_B0_096_001_08_16x16_06x06_src;
          *cornerKernelSource = dgemm_Col_TN_B0_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = dgemm_Col_TN_B0_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B0_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = dgemm_Col_TN_B0_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = dgemm_Col_TN_B0_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = dgemm_Col_TN_B0_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = dgemm_Col_TN_B0_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TN_B0_096_096_01_16x16_06x06_src;
          *rowKernelSource    = dgemm_Col_TN_B0_001_096_01_16x16_06x06_src;
          *colKernelSource    = dgemm_Col_TN_B0_096_001_01_16x16_06x06_src;
          *cornerKernelSource = dgemm_Col_TN_B0_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = dgemm_Col_TN_B0_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B0_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = dgemm_Col_TN_B0_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = dgemm_Col_TN_B0_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = dgemm_Col_TN_B0_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = dgemm_Col_TN_B0_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TN_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = dgemm_Col_TN_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = dgemm_Col_TN_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = dgemm_Col_TN_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = dgemm_Col_TN_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = dgemm_Col_TN_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = dgemm_Col_TN_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = dgemm_Col_TN_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = dgemm_Col_TN_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TN_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = dgemm_Col_TN_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = dgemm_Col_TN_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = dgemm_Col_TN_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = dgemm_Col_TN_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = dgemm_Col_TN_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = dgemm_Col_TN_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = dgemm_Col_TN_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = dgemm_Col_TN_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TN_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = dgemm_Col_TN_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = dgemm_Col_TN_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = dgemm_Col_TN_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = dgemm_Col_TN_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = dgemm_Col_TN_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = dgemm_Col_TN_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = dgemm_Col_TN_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = dgemm_Col_TN_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TN_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = dgemm_Col_TN_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = dgemm_Col_TN_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = dgemm_Col_TN_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = dgemm_Col_TN_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = dgemm_Col_TN_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = dgemm_Col_TN_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = dgemm_Col_TN_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = dgemm_Col_TN_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TN_B0_080_080_08_16x16_05x05_src;
          *rowKernelSource    = dgemm_Col_TN_B0_001_080_08_16x16_05x05_src;
          *colKernelSource    = dgemm_Col_TN_B0_080_001_08_16x16_05x05_src;
          *cornerKernelSource = dgemm_Col_TN_B0_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = dgemm_Col_TN_B0_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B0_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = dgemm_Col_TN_B0_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = dgemm_Col_TN_B0_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = dgemm_Col_TN_B0_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = dgemm_Col_TN_B0_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TN_B0_080_080_01_16x16_05x05_src;
          *rowKernelSource    = dgemm_Col_TN_B0_001_080_01_16x16_05x05_src;
          *colKernelSource    = dgemm_Col_TN_B0_080_001_01_16x16_05x05_src;
          *cornerKernelSource = dgemm_Col_TN_B0_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = dgemm_Col_TN_B0_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B0_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = dgemm_Col_TN_B0_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = dgemm_Col_TN_B0_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = dgemm_Col_TN_B0_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = dgemm_Col_TN_B0_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TN_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = dgemm_Col_TN_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = dgemm_Col_TN_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = dgemm_Col_TN_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = dgemm_Col_TN_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = dgemm_Col_TN_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = dgemm_Col_TN_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = dgemm_Col_TN_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = dgemm_Col_TN_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TN_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = dgemm_Col_TN_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = dgemm_Col_TN_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = dgemm_Col_TN_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = dgemm_Col_TN_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = dgemm_Col_TN_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = dgemm_Col_TN_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = dgemm_Col_TN_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = dgemm_Col_TN_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TN_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = dgemm_Col_TN_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = dgemm_Col_TN_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = dgemm_Col_TN_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = dgemm_Col_TN_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = dgemm_Col_TN_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = dgemm_Col_TN_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = dgemm_Col_TN_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = dgemm_Col_TN_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TN_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = dgemm_Col_TN_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = dgemm_Col_TN_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = dgemm_Col_TN_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = dgemm_Col_TN_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = dgemm_Col_TN_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = dgemm_Col_TN_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = dgemm_Col_TN_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = dgemm_Col_TN_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TN_B1_096_096_08_16x16_06x06_src;
          *rowKernelSource    = dgemm_Col_TN_B1_001_096_08_16x16_06x06_src;
          *colKernelSource    = dgemm_Col_TN_B1_096_001_08_16x16_06x06_src;
          *cornerKernelSource = dgemm_Col_TN_B1_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = dgemm_Col_TN_B1_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B1_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = dgemm_Col_TN_B1_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = dgemm_Col_TN_B1_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = dgemm_Col_TN_B1_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = dgemm_Col_TN_B1_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TN_B1_096_096_01_16x16_06x06_src;
          *rowKernelSource    = dgemm_Col_TN_B1_001_096_01_16x16_06x06_src;
          *colKernelSource    = dgemm_Col_TN_B1_096_001_01_16x16_06x06_src;
          *cornerKernelSource = dgemm_Col_TN_B1_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = dgemm_Col_TN_B1_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B1_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = dgemm_Col_TN_B1_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = dgemm_Col_TN_B1_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = dgemm_Col_TN_B1_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = dgemm_Col_TN_B1_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TN_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = dgemm_Col_TN_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = dgemm_Col_TN_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = dgemm_Col_TN_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = dgemm_Col_TN_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = dgemm_Col_TN_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = dgemm_Col_TN_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = dgemm_Col_TN_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = dgemm_Col_TN_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TN_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = dgemm_Col_TN_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = dgemm_Col_TN_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = dgemm_Col_TN_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = dgemm_Col_TN_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = dgemm_Col_TN_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = dgemm_Col_TN_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = dgemm_Col_TN_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = dgemm_Col_TN_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TN_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = dgemm_Col_TN_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = dgemm_Col_TN_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = dgemm_Col_TN_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = dgemm_Col_TN_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = dgemm_Col_TN_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = dgemm_Col_TN_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = dgemm_Col_TN_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = dgemm_Col_TN_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TN_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = dgemm_Col_TN_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = dgemm_Col_TN_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = dgemm_Col_TN_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = dgemm_Col_TN_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = dgemm_Col_TN_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = dgemm_Col_TN_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = dgemm_Col_TN_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = dgemm_Col_TN_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TN_B1_080_080_08_16x16_05x05_src;
          *rowKernelSource    = dgemm_Col_TN_B1_001_080_08_16x16_05x05_src;
          *colKernelSource    = dgemm_Col_TN_B1_080_001_08_16x16_05x05_src;
          *cornerKernelSource = dgemm_Col_TN_B1_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = dgemm_Col_TN_B1_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B1_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = dgemm_Col_TN_B1_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = dgemm_Col_TN_B1_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = dgemm_Col_TN_B1_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = dgemm_Col_TN_B1_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TN_B1_080_080_01_16x16_05x05_src;
          *rowKernelSource    = dgemm_Col_TN_B1_001_080_01_16x16_05x05_src;
          *colKernelSource    = dgemm_Col_TN_B1_080_001_01_16x16_05x05_src;
          *cornerKernelSource = dgemm_Col_TN_B1_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = dgemm_Col_TN_B1_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B1_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = dgemm_Col_TN_B1_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = dgemm_Col_TN_B1_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = dgemm_Col_TN_B1_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = dgemm_Col_TN_B1_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TN_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = dgemm_Col_TN_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = dgemm_Col_TN_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = dgemm_Col_TN_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = dgemm_Col_TN_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = dgemm_Col_TN_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = dgemm_Col_TN_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = dgemm_Col_TN_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = dgemm_Col_TN_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TN_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = dgemm_Col_TN_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = dgemm_Col_TN_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = dgemm_Col_TN_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = dgemm_Col_TN_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = dgemm_Col_TN_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = dgemm_Col_TN_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = dgemm_Col_TN_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = dgemm_Col_TN_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TN_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = dgemm_Col_TN_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = dgemm_Col_TN_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = dgemm_Col_TN_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = dgemm_Col_TN_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = dgemm_Col_TN_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = dgemm_Col_TN_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = dgemm_Col_TN_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = dgemm_Col_TN_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TN_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = dgemm_Col_TN_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = dgemm_Col_TN_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = dgemm_Col_TN_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = dgemm_Col_TN_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TN_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = dgemm_Col_TN_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = dgemm_Col_TN_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = dgemm_Col_TN_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = dgemm_Col_TN_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TT_B0_096_096_08_16x16_06x06_src;
          *rowKernelSource    = dgemm_Col_TT_B0_001_096_08_16x16_06x06_src;
          *colKernelSource    = dgemm_Col_TT_B0_096_001_08_16x16_06x06_src;
          *cornerKernelSource = dgemm_Col_TT_B0_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = dgemm_Col_TT_B0_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B0_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = dgemm_Col_TT_B0_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = dgemm_Col_TT_B0_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = dgemm_Col_TT_B0_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = dgemm_Col_TT_B0_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TT_B0_096_096_01_16x16_06x06_src;
          *rowKernelSource    = dgemm_Col_TT_B0_001_096_01_16x16_06x06_src;
          *colKernelSource    = dgemm_Col_TT_B0_096_001_01_16x16_06x06_src;
          *cornerKernelSource = dgemm_Col_TT_B0_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = dgemm_Col_TT_B0_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B0_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = dgemm_Col_TT_B0_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = dgemm_Col_TT_B0_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = dgemm_Col_TT_B0_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = dgemm_Col_TT_B0_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TT_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = dgemm_Col_TT_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = dgemm_Col_TT_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = dgemm_Col_TT_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = dgemm_Col_TT_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = dgemm_Col_TT_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = dgemm_Col_TT_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = dgemm_Col_TT_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = dgemm_Col_TT_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TT_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = dgemm_Col_TT_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = dgemm_Col_TT_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = dgemm_Col_TT_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = dgemm_Col_TT_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = dgemm_Col_TT_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = dgemm_Col_TT_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = dgemm_Col_TT_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = dgemm_Col_TT_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TT_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = dgemm_Col_TT_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = dgemm_Col_TT_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = dgemm_Col_TT_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = dgemm_Col_TT_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = dgemm_Col_TT_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = dgemm_Col_TT_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = dgemm_Col_TT_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = dgemm_Col_TT_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TT_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = dgemm_Col_TT_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = dgemm_Col_TT_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = dgemm_Col_TT_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = dgemm_Col_TT_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = dgemm_Col_TT_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = dgemm_Col_TT_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = dgemm_Col_TT_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = dgemm_Col_TT_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TT_B0_080_080_08_16x16_05x05_src;
          *rowKernelSource    = dgemm_Col_TT_B0_001_080_08_16x16_05x05_src;
          *colKernelSource    = dgemm_Col_TT_B0_080_001_08_16x16_05x05_src;
          *cornerKernelSource = dgemm_Col_TT_B0_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = dgemm_Col_TT_B0_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B0_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = dgemm_Col_TT_B0_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = dgemm_Col_TT_B0_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = dgemm_Col_TT_B0_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = dgemm_Col_TT_B0_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TT_B0_080_080_01_16x16_05x05_src;
          *rowKernelSource    = dgemm_Col_TT_B0_001_080_01_16x16_05x05_src;
          *colKernelSource    = dgemm_Col_TT_B0_080_001_01_16x16_05x05_src;
          *cornerKernelSource = dgemm_Col_TT_B0_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = dgemm_Col_TT_B0_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B0_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = dgemm_Col_TT_B0_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = dgemm_Col_TT_B0_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = dgemm_Col_TT_B0_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = dgemm_Col_TT_B0_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TT_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = dgemm_Col_TT_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = dgemm_Col_TT_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = dgemm_Col_TT_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = dgemm_Col_TT_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = dgemm_Col_TT_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = dgemm_Col_TT_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = dgemm_Col_TT_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = dgemm_Col_TT_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TT_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = dgemm_Col_TT_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = dgemm_Col_TT_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = dgemm_Col_TT_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = dgemm_Col_TT_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = dgemm_Col_TT_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = dgemm_Col_TT_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = dgemm_Col_TT_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = dgemm_Col_TT_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TT_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = dgemm_Col_TT_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = dgemm_Col_TT_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = dgemm_Col_TT_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = dgemm_Col_TT_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = dgemm_Col_TT_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = dgemm_Col_TT_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = dgemm_Col_TT_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = dgemm_Col_TT_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TT_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = dgemm_Col_TT_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = dgemm_Col_TT_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = dgemm_Col_TT_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = dgemm_Col_TT_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = dgemm_Col_TT_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = dgemm_Col_TT_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = dgemm_Col_TT_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = dgemm_Col_TT_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TT_B1_096_096_08_16x16_06x06_src;
          *rowKernelSource    = dgemm_Col_TT_B1_001_096_08_16x16_06x06_src;
          *colKernelSource    = dgemm_Col_TT_B1_096_001_08_16x16_06x06_src;
          *cornerKernelSource = dgemm_Col_TT_B1_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = dgemm_Col_TT_B1_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B1_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = dgemm_Col_TT_B1_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = dgemm_Col_TT_B1_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = dgemm_Col_TT_B1_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = dgemm_Col_TT_B1_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TT_B1_096_096_01_16x16_06x06_src;
          *rowKernelSource    = dgemm_Col_TT_B1_001_096_01_16x16_06x06_src;
          *colKernelSource    = dgemm_Col_TT_B1_096_001_01_16x16_06x06_src;
          *cornerKernelSource = dgemm_Col_TT_B1_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = dgemm_Col_TT_B1_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B1_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = dgemm_Col_TT_B1_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = dgemm_Col_TT_B1_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = dgemm_Col_TT_B1_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = dgemm_Col_TT_B1_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TT_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = dgemm_Col_TT_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = dgemm_Col_TT_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = dgemm_Col_TT_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = dgemm_Col_TT_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = dgemm_Col_TT_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = dgemm_Col_TT_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = dgemm_Col_TT_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = dgemm_Col_TT_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TT_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = dgemm_Col_TT_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = dgemm_Col_TT_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = dgemm_Col_TT_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = dgemm_Col_TT_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = dgemm_Col_TT_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = dgemm_Col_TT_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = dgemm_Col_TT_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = dgemm_Col_TT_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TT_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = dgemm_Col_TT_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = dgemm_Col_TT_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = dgemm_Col_TT_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = dgemm_Col_TT_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = dgemm_Col_TT_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = dgemm_Col_TT_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = dgemm_Col_TT_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = dgemm_Col_TT_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TT_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = dgemm_Col_TT_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = dgemm_Col_TT_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = dgemm_Col_TT_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = dgemm_Col_TT_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = dgemm_Col_TT_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = dgemm_Col_TT_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = dgemm_Col_TT_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = dgemm_Col_TT_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TT_B1_080_080_08_16x16_05x05_src;
          *rowKernelSource    = dgemm_Col_TT_B1_001_080_08_16x16_05x05_src;
          *colKernelSource    = dgemm_Col_TT_B1_080_001_08_16x16_05x05_src;
          *cornerKernelSource = dgemm_Col_TT_B1_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = dgemm_Col_TT_B1_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B1_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = dgemm_Col_TT_B1_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = dgemm_Col_TT_B1_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = dgemm_Col_TT_B1_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = dgemm_Col_TT_B1_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TT_B1_080_080_01_16x16_05x05_src;
          *rowKernelSource    = dgemm_Col_TT_B1_001_080_01_16x16_05x05_src;
          *colKernelSource    = dgemm_Col_TT_B1_080_001_01_16x16_05x05_src;
          *cornerKernelSource = dgemm_Col_TT_B1_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = dgemm_Col_TT_B1_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B1_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = dgemm_Col_TT_B1_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = dgemm_Col_TT_B1_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = dgemm_Col_TT_B1_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = dgemm_Col_TT_B1_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TT_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = dgemm_Col_TT_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = dgemm_Col_TT_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = dgemm_Col_TT_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = dgemm_Col_TT_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = dgemm_Col_TT_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = dgemm_Col_TT_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = dgemm_Col_TT_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = dgemm_Col_TT_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TT_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = dgemm_Col_TT_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = dgemm_Col_TT_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = dgemm_Col_TT_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = dgemm_Col_TT_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = dgemm_Col_TT_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = dgemm_Col_TT_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = dgemm_Col_TT_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = dgemm_Col_TT_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = dgemm_Col_TT_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = dgemm_Col_TT_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = dgemm_Col_TT_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = dgemm_Col_TT_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = dgemm_Col_TT_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = dgemm_Col_TT_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = dgemm_Col_TT_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = dgemm_Col_TT_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = dgemm_Col_TT_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = dgemm_Col_TT_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = dgemm_Col_TT_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = dgemm_Col_TT_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = dgemm_Col_TT_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = dgemm_Col_TT_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = dgemm_Col_TT_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = dgemm_Col_TT_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = dgemm_Col_TT_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = dgemm_Col_TT_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = dgemm_Col_TT_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      }
    }
  }
  return false; // didn't find a match
}

// cgemm kernel selection specific
template<>
bool gemmSelectKernelSpecific<FloatComplex>(
  clblasOrder order,
  clblasTranspose transA,
  clblasTranspose transB,
  bool betaNonZero,
  unsigned int workGroupNumRows,
  unsigned int workGroupNumCols,
  unsigned int microTileNumRows,
  unsigned int microTileNumCols,
  unsigned int unroll,
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
  cl_kernel  **cornerClKernel
) {
  if (order == clblasColumnMajor) {
    if (transA == clblasNoTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NN_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_NN_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_NN_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_NN_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_NN_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_NN_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_NN_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_NN_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_NN_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NN_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_NN_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_NN_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_NN_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_NN_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_NN_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_NN_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_NN_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_NN_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NN_B0_096_096_08_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_NN_B0_001_096_08_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_NN_B0_096_001_08_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_NN_B0_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_NN_B0_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B0_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_NN_B0_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_NN_B0_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_NN_B0_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_NN_B0_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NN_B0_096_096_01_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_NN_B0_001_096_01_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_NN_B0_096_001_01_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_NN_B0_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_NN_B0_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B0_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_NN_B0_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_NN_B0_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_NN_B0_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_NN_B0_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NN_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_NN_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_NN_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_NN_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_NN_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_NN_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_NN_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_NN_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_NN_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NN_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_NN_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_NN_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_NN_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_NN_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_NN_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_NN_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_NN_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_NN_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NN_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_NN_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_NN_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_NN_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_NN_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_NN_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_NN_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_NN_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_NN_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NN_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_NN_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_NN_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_NN_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_NN_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_NN_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_NN_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_NN_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_NN_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NN_B0_080_080_08_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_NN_B0_001_080_08_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_NN_B0_080_001_08_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_NN_B0_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_NN_B0_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B0_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_NN_B0_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_NN_B0_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_NN_B0_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_NN_B0_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NN_B0_080_080_01_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_NN_B0_001_080_01_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_NN_B0_080_001_01_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_NN_B0_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_NN_B0_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B0_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_NN_B0_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_NN_B0_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_NN_B0_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_NN_B0_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NN_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_NN_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_NN_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_NN_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_NN_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_NN_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_NN_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_NN_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_NN_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NN_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_NN_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_NN_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_NN_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_NN_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_NN_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_NN_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_NN_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_NN_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NN_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_NN_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_NN_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_NN_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_NN_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_NN_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_NN_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_NN_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_NN_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NN_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_NN_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_NN_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_NN_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_NN_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_NN_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_NN_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_NN_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_NN_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NN_B1_096_096_08_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_NN_B1_001_096_08_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_NN_B1_096_001_08_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_NN_B1_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_NN_B1_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B1_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_NN_B1_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_NN_B1_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_NN_B1_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_NN_B1_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NN_B1_096_096_01_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_NN_B1_001_096_01_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_NN_B1_096_001_01_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_NN_B1_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_NN_B1_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B1_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_NN_B1_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_NN_B1_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_NN_B1_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_NN_B1_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NN_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_NN_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_NN_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_NN_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_NN_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_NN_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_NN_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_NN_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_NN_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NN_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_NN_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_NN_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_NN_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_NN_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_NN_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_NN_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_NN_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_NN_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NN_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_NN_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_NN_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_NN_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_NN_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_NN_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_NN_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_NN_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_NN_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NN_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_NN_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_NN_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_NN_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_NN_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_NN_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_NN_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_NN_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_NN_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NN_B1_080_080_08_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_NN_B1_001_080_08_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_NN_B1_080_001_08_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_NN_B1_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_NN_B1_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B1_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_NN_B1_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_NN_B1_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_NN_B1_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_NN_B1_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NN_B1_080_080_01_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_NN_B1_001_080_01_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_NN_B1_080_001_01_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_NN_B1_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_NN_B1_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B1_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_NN_B1_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_NN_B1_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_NN_B1_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_NN_B1_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NN_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_NN_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_NN_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_NN_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_NN_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_NN_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_NN_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_NN_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_NN_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NN_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_NN_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_NN_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_NN_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_NN_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NN_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_NN_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_NN_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_NN_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_NN_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      }
    } else if (transA == clblasNoTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NT_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_NT_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_NT_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_NT_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_NT_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_NT_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_NT_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_NT_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_NT_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NT_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_NT_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_NT_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_NT_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_NT_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_NT_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_NT_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_NT_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_NT_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NT_B0_096_096_08_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_NT_B0_001_096_08_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_NT_B0_096_001_08_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_NT_B0_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_NT_B0_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B0_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_NT_B0_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_NT_B0_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_NT_B0_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_NT_B0_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NT_B0_096_096_01_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_NT_B0_001_096_01_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_NT_B0_096_001_01_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_NT_B0_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_NT_B0_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B0_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_NT_B0_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_NT_B0_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_NT_B0_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_NT_B0_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NT_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_NT_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_NT_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_NT_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_NT_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_NT_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_NT_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_NT_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_NT_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NT_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_NT_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_NT_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_NT_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_NT_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_NT_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_NT_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_NT_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_NT_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NT_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_NT_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_NT_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_NT_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_NT_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_NT_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_NT_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_NT_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_NT_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NT_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_NT_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_NT_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_NT_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_NT_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_NT_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_NT_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_NT_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_NT_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NT_B0_080_080_08_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_NT_B0_001_080_08_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_NT_B0_080_001_08_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_NT_B0_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_NT_B0_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B0_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_NT_B0_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_NT_B0_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_NT_B0_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_NT_B0_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NT_B0_080_080_01_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_NT_B0_001_080_01_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_NT_B0_080_001_01_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_NT_B0_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_NT_B0_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B0_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_NT_B0_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_NT_B0_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_NT_B0_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_NT_B0_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NT_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_NT_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_NT_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_NT_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_NT_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_NT_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_NT_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_NT_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_NT_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NT_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_NT_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_NT_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_NT_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_NT_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_NT_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_NT_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_NT_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_NT_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NT_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_NT_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_NT_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_NT_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_NT_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_NT_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_NT_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_NT_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_NT_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NT_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_NT_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_NT_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_NT_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_NT_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_NT_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_NT_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_NT_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_NT_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NT_B1_096_096_08_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_NT_B1_001_096_08_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_NT_B1_096_001_08_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_NT_B1_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_NT_B1_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B1_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_NT_B1_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_NT_B1_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_NT_B1_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_NT_B1_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NT_B1_096_096_01_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_NT_B1_001_096_01_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_NT_B1_096_001_01_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_NT_B1_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_NT_B1_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B1_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_NT_B1_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_NT_B1_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_NT_B1_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_NT_B1_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NT_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_NT_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_NT_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_NT_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_NT_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_NT_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_NT_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_NT_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_NT_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NT_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_NT_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_NT_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_NT_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_NT_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_NT_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_NT_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_NT_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_NT_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NT_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_NT_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_NT_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_NT_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_NT_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_NT_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_NT_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_NT_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_NT_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NT_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_NT_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_NT_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_NT_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_NT_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_NT_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_NT_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_NT_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_NT_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NT_B1_080_080_08_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_NT_B1_001_080_08_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_NT_B1_080_001_08_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_NT_B1_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_NT_B1_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B1_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_NT_B1_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_NT_B1_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_NT_B1_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_NT_B1_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NT_B1_080_080_01_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_NT_B1_001_080_01_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_NT_B1_080_001_01_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_NT_B1_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_NT_B1_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B1_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_NT_B1_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_NT_B1_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_NT_B1_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_NT_B1_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NT_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_NT_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_NT_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_NT_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_NT_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_NT_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_NT_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_NT_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_NT_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NT_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_NT_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_NT_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_NT_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_NT_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NT_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_NT_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_NT_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_NT_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_NT_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      }
    } else if (transA == clblasNoTrans && transB == clblasConjTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NC_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_NC_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_NC_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_NC_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_NC_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_NC_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_NC_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_NC_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_NC_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NC_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_NC_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_NC_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_NC_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_NC_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_NC_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_NC_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_NC_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_NC_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NC_B0_096_096_08_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_NC_B0_001_096_08_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_NC_B0_096_001_08_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_NC_B0_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_NC_B0_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B0_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_NC_B0_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_NC_B0_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_NC_B0_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_NC_B0_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NC_B0_096_096_01_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_NC_B0_001_096_01_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_NC_B0_096_001_01_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_NC_B0_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_NC_B0_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B0_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_NC_B0_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_NC_B0_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_NC_B0_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_NC_B0_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NC_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_NC_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_NC_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_NC_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_NC_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_NC_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_NC_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_NC_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_NC_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NC_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_NC_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_NC_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_NC_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_NC_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_NC_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_NC_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_NC_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_NC_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NC_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_NC_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_NC_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_NC_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_NC_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_NC_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_NC_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_NC_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_NC_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NC_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_NC_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_NC_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_NC_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_NC_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_NC_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_NC_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_NC_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_NC_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NC_B0_080_080_08_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_NC_B0_001_080_08_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_NC_B0_080_001_08_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_NC_B0_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_NC_B0_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B0_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_NC_B0_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_NC_B0_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_NC_B0_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_NC_B0_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NC_B0_080_080_01_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_NC_B0_001_080_01_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_NC_B0_080_001_01_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_NC_B0_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_NC_B0_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B0_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_NC_B0_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_NC_B0_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_NC_B0_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_NC_B0_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NC_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_NC_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_NC_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_NC_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_NC_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_NC_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_NC_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_NC_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_NC_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NC_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_NC_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_NC_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_NC_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_NC_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_NC_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_NC_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_NC_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_NC_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NC_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_NC_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_NC_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_NC_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_NC_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_NC_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_NC_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_NC_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_NC_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NC_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_NC_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_NC_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_NC_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_NC_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_NC_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_NC_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_NC_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_NC_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NC_B1_096_096_08_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_NC_B1_001_096_08_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_NC_B1_096_001_08_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_NC_B1_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_NC_B1_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B1_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_NC_B1_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_NC_B1_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_NC_B1_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_NC_B1_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NC_B1_096_096_01_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_NC_B1_001_096_01_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_NC_B1_096_001_01_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_NC_B1_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_NC_B1_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B1_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_NC_B1_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_NC_B1_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_NC_B1_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_NC_B1_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NC_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_NC_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_NC_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_NC_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_NC_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_NC_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_NC_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_NC_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_NC_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NC_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_NC_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_NC_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_NC_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_NC_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_NC_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_NC_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_NC_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_NC_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NC_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_NC_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_NC_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_NC_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_NC_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_NC_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_NC_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_NC_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_NC_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NC_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_NC_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_NC_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_NC_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_NC_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_NC_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_NC_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_NC_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_NC_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NC_B1_080_080_08_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_NC_B1_001_080_08_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_NC_B1_080_001_08_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_NC_B1_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_NC_B1_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B1_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_NC_B1_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_NC_B1_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_NC_B1_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_NC_B1_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NC_B1_080_080_01_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_NC_B1_001_080_01_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_NC_B1_080_001_01_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_NC_B1_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_NC_B1_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B1_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_NC_B1_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_NC_B1_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_NC_B1_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_NC_B1_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_NC_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_NC_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_NC_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_NC_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_NC_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_NC_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_NC_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_NC_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_NC_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_NC_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_NC_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_NC_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_NC_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_NC_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_NC_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_NC_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_NC_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_NC_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_NC_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TN_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_TN_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_TN_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_TN_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_TN_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_TN_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_TN_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_TN_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_TN_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TN_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_TN_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_TN_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_TN_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_TN_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_TN_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_TN_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_TN_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_TN_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TN_B0_096_096_08_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_TN_B0_001_096_08_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_TN_B0_096_001_08_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_TN_B0_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_TN_B0_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B0_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_TN_B0_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_TN_B0_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_TN_B0_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_TN_B0_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TN_B0_096_096_01_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_TN_B0_001_096_01_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_TN_B0_096_001_01_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_TN_B0_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_TN_B0_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B0_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_TN_B0_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_TN_B0_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_TN_B0_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_TN_B0_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TN_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_TN_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_TN_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_TN_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_TN_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_TN_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_TN_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_TN_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_TN_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TN_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_TN_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_TN_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_TN_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_TN_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_TN_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_TN_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_TN_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_TN_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TN_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_TN_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_TN_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_TN_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_TN_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_TN_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_TN_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_TN_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_TN_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TN_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_TN_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_TN_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_TN_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_TN_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_TN_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_TN_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_TN_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_TN_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TN_B0_080_080_08_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_TN_B0_001_080_08_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_TN_B0_080_001_08_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_TN_B0_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_TN_B0_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B0_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_TN_B0_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_TN_B0_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_TN_B0_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_TN_B0_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TN_B0_080_080_01_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_TN_B0_001_080_01_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_TN_B0_080_001_01_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_TN_B0_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_TN_B0_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B0_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_TN_B0_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_TN_B0_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_TN_B0_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_TN_B0_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TN_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_TN_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_TN_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_TN_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_TN_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_TN_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_TN_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_TN_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_TN_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TN_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_TN_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_TN_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_TN_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_TN_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_TN_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_TN_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_TN_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_TN_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TN_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_TN_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_TN_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_TN_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_TN_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_TN_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_TN_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_TN_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_TN_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TN_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_TN_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_TN_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_TN_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_TN_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_TN_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_TN_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_TN_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_TN_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TN_B1_096_096_08_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_TN_B1_001_096_08_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_TN_B1_096_001_08_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_TN_B1_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_TN_B1_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B1_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_TN_B1_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_TN_B1_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_TN_B1_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_TN_B1_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TN_B1_096_096_01_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_TN_B1_001_096_01_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_TN_B1_096_001_01_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_TN_B1_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_TN_B1_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B1_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_TN_B1_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_TN_B1_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_TN_B1_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_TN_B1_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TN_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_TN_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_TN_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_TN_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_TN_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_TN_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_TN_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_TN_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_TN_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TN_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_TN_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_TN_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_TN_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_TN_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_TN_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_TN_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_TN_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_TN_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TN_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_TN_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_TN_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_TN_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_TN_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_TN_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_TN_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_TN_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_TN_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TN_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_TN_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_TN_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_TN_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_TN_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_TN_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_TN_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_TN_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_TN_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TN_B1_080_080_08_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_TN_B1_001_080_08_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_TN_B1_080_001_08_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_TN_B1_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_TN_B1_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B1_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_TN_B1_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_TN_B1_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_TN_B1_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_TN_B1_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TN_B1_080_080_01_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_TN_B1_001_080_01_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_TN_B1_080_001_01_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_TN_B1_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_TN_B1_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B1_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_TN_B1_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_TN_B1_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_TN_B1_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_TN_B1_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TN_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_TN_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_TN_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_TN_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_TN_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_TN_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_TN_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_TN_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_TN_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TN_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_TN_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_TN_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_TN_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_TN_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TN_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_TN_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_TN_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_TN_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_TN_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TT_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_TT_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_TT_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_TT_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_TT_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_TT_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_TT_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_TT_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_TT_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TT_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_TT_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_TT_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_TT_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_TT_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_TT_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_TT_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_TT_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_TT_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TT_B0_096_096_08_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_TT_B0_001_096_08_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_TT_B0_096_001_08_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_TT_B0_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_TT_B0_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B0_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_TT_B0_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_TT_B0_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_TT_B0_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_TT_B0_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TT_B0_096_096_01_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_TT_B0_001_096_01_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_TT_B0_096_001_01_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_TT_B0_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_TT_B0_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B0_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_TT_B0_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_TT_B0_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_TT_B0_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_TT_B0_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TT_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_TT_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_TT_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_TT_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_TT_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_TT_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_TT_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_TT_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_TT_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TT_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_TT_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_TT_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_TT_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_TT_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_TT_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_TT_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_TT_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_TT_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TT_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_TT_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_TT_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_TT_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_TT_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_TT_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_TT_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_TT_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_TT_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TT_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_TT_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_TT_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_TT_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_TT_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_TT_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_TT_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_TT_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_TT_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TT_B0_080_080_08_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_TT_B0_001_080_08_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_TT_B0_080_001_08_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_TT_B0_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_TT_B0_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B0_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_TT_B0_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_TT_B0_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_TT_B0_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_TT_B0_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TT_B0_080_080_01_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_TT_B0_001_080_01_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_TT_B0_080_001_01_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_TT_B0_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_TT_B0_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B0_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_TT_B0_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_TT_B0_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_TT_B0_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_TT_B0_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TT_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_TT_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_TT_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_TT_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_TT_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_TT_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_TT_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_TT_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_TT_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TT_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_TT_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_TT_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_TT_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_TT_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_TT_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_TT_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_TT_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_TT_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TT_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_TT_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_TT_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_TT_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_TT_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_TT_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_TT_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_TT_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_TT_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TT_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_TT_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_TT_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_TT_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_TT_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_TT_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_TT_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_TT_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_TT_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TT_B1_096_096_08_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_TT_B1_001_096_08_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_TT_B1_096_001_08_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_TT_B1_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_TT_B1_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B1_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_TT_B1_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_TT_B1_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_TT_B1_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_TT_B1_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TT_B1_096_096_01_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_TT_B1_001_096_01_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_TT_B1_096_001_01_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_TT_B1_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_TT_B1_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B1_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_TT_B1_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_TT_B1_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_TT_B1_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_TT_B1_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TT_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_TT_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_TT_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_TT_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_TT_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_TT_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_TT_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_TT_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_TT_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TT_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_TT_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_TT_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_TT_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_TT_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_TT_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_TT_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_TT_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_TT_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TT_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_TT_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_TT_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_TT_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_TT_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_TT_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_TT_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_TT_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_TT_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TT_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_TT_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_TT_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_TT_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_TT_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_TT_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_TT_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_TT_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_TT_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TT_B1_080_080_08_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_TT_B1_001_080_08_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_TT_B1_080_001_08_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_TT_B1_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_TT_B1_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B1_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_TT_B1_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_TT_B1_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_TT_B1_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_TT_B1_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TT_B1_080_080_01_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_TT_B1_001_080_01_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_TT_B1_080_001_01_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_TT_B1_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_TT_B1_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B1_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_TT_B1_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_TT_B1_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_TT_B1_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_TT_B1_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TT_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_TT_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_TT_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_TT_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_TT_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_TT_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_TT_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_TT_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_TT_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TT_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_TT_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_TT_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_TT_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_TT_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TT_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_TT_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_TT_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_TT_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_TT_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasConjTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TC_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_TC_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_TC_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_TC_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_TC_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_TC_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_TC_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_TC_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_TC_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TC_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_TC_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_TC_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_TC_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_TC_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_TC_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_TC_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_TC_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_TC_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TC_B0_096_096_08_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_TC_B0_001_096_08_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_TC_B0_096_001_08_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_TC_B0_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_TC_B0_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B0_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_TC_B0_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_TC_B0_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_TC_B0_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_TC_B0_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TC_B0_096_096_01_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_TC_B0_001_096_01_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_TC_B0_096_001_01_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_TC_B0_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_TC_B0_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B0_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_TC_B0_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_TC_B0_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_TC_B0_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_TC_B0_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TC_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_TC_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_TC_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_TC_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_TC_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_TC_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_TC_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_TC_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_TC_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TC_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_TC_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_TC_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_TC_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_TC_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_TC_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_TC_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_TC_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_TC_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TC_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_TC_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_TC_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_TC_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_TC_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_TC_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_TC_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_TC_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_TC_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TC_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_TC_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_TC_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_TC_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_TC_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_TC_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_TC_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_TC_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_TC_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TC_B0_080_080_08_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_TC_B0_001_080_08_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_TC_B0_080_001_08_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_TC_B0_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_TC_B0_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B0_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_TC_B0_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_TC_B0_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_TC_B0_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_TC_B0_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TC_B0_080_080_01_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_TC_B0_001_080_01_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_TC_B0_080_001_01_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_TC_B0_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_TC_B0_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B0_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_TC_B0_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_TC_B0_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_TC_B0_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_TC_B0_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TC_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_TC_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_TC_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_TC_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_TC_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_TC_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_TC_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_TC_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_TC_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TC_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_TC_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_TC_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_TC_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_TC_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_TC_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_TC_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_TC_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_TC_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TC_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_TC_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_TC_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_TC_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_TC_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_TC_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_TC_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_TC_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_TC_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TC_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_TC_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_TC_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_TC_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_TC_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_TC_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_TC_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_TC_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_TC_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TC_B1_096_096_08_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_TC_B1_001_096_08_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_TC_B1_096_001_08_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_TC_B1_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_TC_B1_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B1_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_TC_B1_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_TC_B1_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_TC_B1_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_TC_B1_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TC_B1_096_096_01_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_TC_B1_001_096_01_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_TC_B1_096_001_01_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_TC_B1_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_TC_B1_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B1_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_TC_B1_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_TC_B1_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_TC_B1_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_TC_B1_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TC_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_TC_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_TC_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_TC_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_TC_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_TC_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_TC_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_TC_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_TC_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TC_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_TC_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_TC_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_TC_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_TC_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_TC_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_TC_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_TC_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_TC_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TC_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_TC_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_TC_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_TC_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_TC_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_TC_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_TC_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_TC_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_TC_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TC_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_TC_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_TC_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_TC_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_TC_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_TC_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_TC_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_TC_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_TC_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TC_B1_080_080_08_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_TC_B1_001_080_08_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_TC_B1_080_001_08_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_TC_B1_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_TC_B1_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B1_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_TC_B1_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_TC_B1_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_TC_B1_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_TC_B1_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TC_B1_080_080_01_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_TC_B1_001_080_01_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_TC_B1_080_001_01_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_TC_B1_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_TC_B1_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B1_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_TC_B1_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_TC_B1_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_TC_B1_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_TC_B1_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_TC_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_TC_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_TC_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_TC_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_TC_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_TC_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_TC_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_TC_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_TC_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_TC_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_TC_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_TC_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_TC_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_TC_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_TC_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_TC_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_TC_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_TC_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_TC_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      }
    } else if (transA == clblasConjTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CN_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_CN_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_CN_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_CN_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_CN_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_CN_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_CN_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_CN_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_CN_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CN_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_CN_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_CN_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_CN_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_CN_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_CN_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_CN_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_CN_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_CN_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CN_B0_096_096_08_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_CN_B0_001_096_08_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_CN_B0_096_001_08_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_CN_B0_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_CN_B0_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B0_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_CN_B0_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_CN_B0_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_CN_B0_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_CN_B0_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CN_B0_096_096_01_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_CN_B0_001_096_01_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_CN_B0_096_001_01_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_CN_B0_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_CN_B0_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B0_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_CN_B0_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_CN_B0_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_CN_B0_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_CN_B0_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CN_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_CN_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_CN_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_CN_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_CN_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_CN_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_CN_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_CN_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_CN_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CN_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_CN_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_CN_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_CN_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_CN_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_CN_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_CN_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_CN_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_CN_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CN_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_CN_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_CN_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_CN_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_CN_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_CN_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_CN_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_CN_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_CN_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CN_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_CN_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_CN_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_CN_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_CN_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_CN_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_CN_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_CN_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_CN_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CN_B0_080_080_08_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_CN_B0_001_080_08_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_CN_B0_080_001_08_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_CN_B0_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_CN_B0_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B0_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_CN_B0_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_CN_B0_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_CN_B0_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_CN_B0_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CN_B0_080_080_01_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_CN_B0_001_080_01_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_CN_B0_080_001_01_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_CN_B0_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_CN_B0_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B0_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_CN_B0_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_CN_B0_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_CN_B0_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_CN_B0_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CN_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_CN_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_CN_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_CN_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_CN_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_CN_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_CN_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_CN_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_CN_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CN_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_CN_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_CN_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_CN_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_CN_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_CN_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_CN_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_CN_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_CN_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CN_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_CN_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_CN_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_CN_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_CN_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_CN_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_CN_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_CN_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_CN_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CN_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_CN_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_CN_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_CN_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_CN_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_CN_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_CN_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_CN_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_CN_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CN_B1_096_096_08_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_CN_B1_001_096_08_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_CN_B1_096_001_08_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_CN_B1_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_CN_B1_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B1_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_CN_B1_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_CN_B1_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_CN_B1_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_CN_B1_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CN_B1_096_096_01_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_CN_B1_001_096_01_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_CN_B1_096_001_01_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_CN_B1_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_CN_B1_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B1_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_CN_B1_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_CN_B1_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_CN_B1_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_CN_B1_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CN_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_CN_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_CN_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_CN_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_CN_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_CN_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_CN_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_CN_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_CN_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CN_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_CN_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_CN_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_CN_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_CN_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_CN_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_CN_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_CN_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_CN_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CN_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_CN_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_CN_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_CN_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_CN_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_CN_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_CN_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_CN_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_CN_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CN_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_CN_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_CN_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_CN_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_CN_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_CN_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_CN_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_CN_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_CN_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CN_B1_080_080_08_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_CN_B1_001_080_08_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_CN_B1_080_001_08_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_CN_B1_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_CN_B1_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B1_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_CN_B1_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_CN_B1_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_CN_B1_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_CN_B1_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CN_B1_080_080_01_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_CN_B1_001_080_01_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_CN_B1_080_001_01_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_CN_B1_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_CN_B1_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B1_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_CN_B1_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_CN_B1_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_CN_B1_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_CN_B1_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CN_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_CN_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_CN_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_CN_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_CN_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_CN_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_CN_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_CN_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_CN_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CN_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_CN_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_CN_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_CN_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_CN_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CN_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_CN_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_CN_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_CN_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_CN_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      }
    } else if (transA == clblasConjTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CT_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_CT_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_CT_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_CT_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_CT_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_CT_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_CT_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_CT_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_CT_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CT_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_CT_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_CT_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_CT_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_CT_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_CT_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_CT_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_CT_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_CT_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CT_B0_096_096_08_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_CT_B0_001_096_08_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_CT_B0_096_001_08_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_CT_B0_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_CT_B0_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B0_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_CT_B0_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_CT_B0_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_CT_B0_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_CT_B0_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CT_B0_096_096_01_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_CT_B0_001_096_01_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_CT_B0_096_001_01_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_CT_B0_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_CT_B0_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B0_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_CT_B0_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_CT_B0_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_CT_B0_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_CT_B0_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CT_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_CT_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_CT_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_CT_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_CT_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_CT_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_CT_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_CT_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_CT_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CT_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_CT_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_CT_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_CT_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_CT_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_CT_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_CT_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_CT_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_CT_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CT_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_CT_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_CT_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_CT_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_CT_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_CT_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_CT_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_CT_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_CT_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CT_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_CT_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_CT_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_CT_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_CT_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_CT_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_CT_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_CT_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_CT_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CT_B0_080_080_08_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_CT_B0_001_080_08_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_CT_B0_080_001_08_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_CT_B0_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_CT_B0_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B0_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_CT_B0_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_CT_B0_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_CT_B0_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_CT_B0_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CT_B0_080_080_01_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_CT_B0_001_080_01_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_CT_B0_080_001_01_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_CT_B0_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_CT_B0_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B0_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_CT_B0_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_CT_B0_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_CT_B0_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_CT_B0_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CT_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_CT_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_CT_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_CT_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_CT_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_CT_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_CT_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_CT_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_CT_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CT_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_CT_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_CT_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_CT_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_CT_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_CT_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_CT_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_CT_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_CT_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CT_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_CT_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_CT_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_CT_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_CT_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_CT_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_CT_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_CT_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_CT_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CT_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_CT_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_CT_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_CT_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_CT_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_CT_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_CT_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_CT_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_CT_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CT_B1_096_096_08_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_CT_B1_001_096_08_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_CT_B1_096_001_08_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_CT_B1_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_CT_B1_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B1_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_CT_B1_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_CT_B1_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_CT_B1_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_CT_B1_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CT_B1_096_096_01_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_CT_B1_001_096_01_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_CT_B1_096_001_01_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_CT_B1_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_CT_B1_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B1_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_CT_B1_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_CT_B1_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_CT_B1_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_CT_B1_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CT_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_CT_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_CT_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_CT_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_CT_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_CT_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_CT_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_CT_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_CT_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CT_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_CT_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_CT_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_CT_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_CT_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_CT_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_CT_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_CT_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_CT_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CT_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_CT_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_CT_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_CT_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_CT_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_CT_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_CT_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_CT_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_CT_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CT_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_CT_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_CT_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_CT_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_CT_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_CT_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_CT_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_CT_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_CT_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CT_B1_080_080_08_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_CT_B1_001_080_08_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_CT_B1_080_001_08_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_CT_B1_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_CT_B1_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B1_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_CT_B1_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_CT_B1_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_CT_B1_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_CT_B1_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CT_B1_080_080_01_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_CT_B1_001_080_01_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_CT_B1_080_001_01_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_CT_B1_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_CT_B1_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B1_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_CT_B1_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_CT_B1_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_CT_B1_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_CT_B1_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CT_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_CT_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_CT_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_CT_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_CT_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_CT_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_CT_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_CT_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_CT_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CT_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_CT_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_CT_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_CT_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_CT_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CT_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_CT_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_CT_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_CT_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_CT_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      }
    } else if (transA == clblasConjTrans && transB == clblasConjTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CC_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_CC_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_CC_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_CC_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_CC_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_CC_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_CC_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_CC_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_CC_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CC_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_CC_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_CC_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_CC_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_CC_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_CC_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_CC_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_CC_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_CC_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CC_B0_096_096_08_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_CC_B0_001_096_08_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_CC_B0_096_001_08_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_CC_B0_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_CC_B0_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B0_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_CC_B0_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_CC_B0_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_CC_B0_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_CC_B0_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CC_B0_096_096_01_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_CC_B0_001_096_01_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_CC_B0_096_001_01_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_CC_B0_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_CC_B0_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B0_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_CC_B0_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_CC_B0_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_CC_B0_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_CC_B0_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CC_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_CC_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_CC_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_CC_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_CC_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_CC_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_CC_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_CC_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_CC_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CC_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_CC_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_CC_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_CC_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_CC_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_CC_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_CC_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_CC_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_CC_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CC_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_CC_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_CC_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_CC_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_CC_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_CC_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_CC_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_CC_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_CC_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CC_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_CC_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_CC_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_CC_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_CC_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_CC_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_CC_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_CC_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_CC_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CC_B0_080_080_08_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_CC_B0_001_080_08_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_CC_B0_080_001_08_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_CC_B0_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_CC_B0_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B0_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_CC_B0_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_CC_B0_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_CC_B0_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_CC_B0_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CC_B0_080_080_01_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_CC_B0_001_080_01_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_CC_B0_080_001_01_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_CC_B0_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_CC_B0_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B0_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_CC_B0_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_CC_B0_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_CC_B0_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_CC_B0_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CC_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_CC_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_CC_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_CC_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_CC_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_CC_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_CC_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_CC_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_CC_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CC_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_CC_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_CC_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_CC_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_CC_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_CC_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_CC_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_CC_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_CC_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CC_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_CC_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_CC_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_CC_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_CC_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_CC_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_CC_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_CC_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_CC_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CC_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = cgemm_Col_CC_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = cgemm_Col_CC_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = cgemm_Col_CC_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = cgemm_Col_CC_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = cgemm_Col_CC_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = cgemm_Col_CC_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = cgemm_Col_CC_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = cgemm_Col_CC_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CC_B1_096_096_08_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_CC_B1_001_096_08_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_CC_B1_096_001_08_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_CC_B1_001_001_08_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_CC_B1_096_096_08_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B1_096_096_08_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_CC_B1_001_096_08_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_CC_B1_096_001_08_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_CC_B1_001_001_08_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_CC_B1_096_096_08_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_096_096_08_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_001_096_08_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_096_001_08_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_001_001_08_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 6 && microTileNumCols == 6 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CC_B1_096_096_01_16x16_06x06_src;
          *rowKernelSource    = cgemm_Col_CC_B1_001_096_01_16x16_06x06_src;
          *colKernelSource    = cgemm_Col_CC_B1_096_001_01_16x16_06x06_src;
          *cornerKernelSource = cgemm_Col_CC_B1_001_001_01_16x16_06x06_src;
          *sourceBuildOptions = cgemm_Col_CC_B1_096_096_01_16x16_06x06_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B1_096_096_01_16x16_06x06_bin;
          *rowKernelBinary    = cgemm_Col_CC_B1_001_096_01_16x16_06x06_bin;
          *colKernelBinary    = cgemm_Col_CC_B1_096_001_01_16x16_06x06_bin;
          *cornerKernelBinary = cgemm_Col_CC_B1_001_001_01_16x16_06x06_bin;
          *binaryBuildOptions = cgemm_Col_CC_B1_096_096_01_16x16_06x06_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_096_096_01_16x16_06x06_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_001_096_01_16x16_06x06_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_096_001_01_16x16_06x06_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_001_001_01_16x16_06x06_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CC_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_CC_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_CC_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_CC_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_CC_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_CC_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_CC_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_CC_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_CC_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CC_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = cgemm_Col_CC_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = cgemm_Col_CC_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = cgemm_Col_CC_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = cgemm_Col_CC_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = cgemm_Col_CC_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = cgemm_Col_CC_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = cgemm_Col_CC_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = cgemm_Col_CC_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CC_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_CC_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_CC_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_CC_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_CC_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_CC_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_CC_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_CC_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_CC_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CC_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = cgemm_Col_CC_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = cgemm_Col_CC_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = cgemm_Col_CC_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = cgemm_Col_CC_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = cgemm_Col_CC_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = cgemm_Col_CC_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = cgemm_Col_CC_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = cgemm_Col_CC_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CC_B1_080_080_08_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_CC_B1_001_080_08_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_CC_B1_080_001_08_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_CC_B1_001_001_08_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_CC_B1_080_080_08_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B1_080_080_08_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_CC_B1_001_080_08_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_CC_B1_080_001_08_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_CC_B1_001_001_08_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_CC_B1_080_080_08_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_080_080_08_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_001_080_08_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_080_001_08_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_001_001_08_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 5 && microTileNumCols == 5 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CC_B1_080_080_01_16x16_05x05_src;
          *rowKernelSource    = cgemm_Col_CC_B1_001_080_01_16x16_05x05_src;
          *colKernelSource    = cgemm_Col_CC_B1_080_001_01_16x16_05x05_src;
          *cornerKernelSource = cgemm_Col_CC_B1_001_001_01_16x16_05x05_src;
          *sourceBuildOptions = cgemm_Col_CC_B1_080_080_01_16x16_05x05_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B1_080_080_01_16x16_05x05_bin;
          *rowKernelBinary    = cgemm_Col_CC_B1_001_080_01_16x16_05x05_bin;
          *colKernelBinary    = cgemm_Col_CC_B1_080_001_01_16x16_05x05_bin;
          *cornerKernelBinary = cgemm_Col_CC_B1_001_001_01_16x16_05x05_bin;
          *binaryBuildOptions = cgemm_Col_CC_B1_080_080_01_16x16_05x05_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_080_080_01_16x16_05x05_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_001_080_01_16x16_05x05_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_080_001_01_16x16_05x05_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_001_001_01_16x16_05x05_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = cgemm_Col_CC_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_CC_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_CC_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_CC_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_CC_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_CC_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_CC_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_CC_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_CC_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = cgemm_Col_CC_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = cgemm_Col_CC_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = cgemm_Col_CC_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = cgemm_Col_CC_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = cgemm_Col_CC_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = cgemm_Col_CC_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = cgemm_Col_CC_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = cgemm_Col_CC_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = cgemm_Col_CC_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = cgemm_Col_CC_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
      }
    }
  }
  return false; // didn't find a match
}

// zgemm kernel selection specific
template<>
bool gemmSelectKernelSpecific<DoubleComplex>(
  clblasOrder order,
  clblasTranspose transA,
  clblasTranspose transB,
  bool betaNonZero,
  unsigned int workGroupNumRows,
  unsigned int workGroupNumCols,
  unsigned int microTileNumRows,
  unsigned int microTileNumCols,
  unsigned int unroll,
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
  cl_kernel  **cornerClKernel
) {
  if (order == clblasColumnMajor) {
    if (transA == clblasNoTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NN_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_NN_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_NN_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_NN_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_NN_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NN_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_NN_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_NN_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_NN_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_NN_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_NN_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NN_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_NN_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_NN_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_NN_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_NN_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NN_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_NN_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_NN_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_NN_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_NN_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_NN_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NN_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_NN_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_NN_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_NN_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_NN_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NN_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_NN_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_NN_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_NN_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_NN_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_NN_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NN_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_NN_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_NN_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_NN_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_NN_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NN_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_NN_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_NN_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_NN_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_NN_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_NN_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NN_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_NN_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_NN_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_NN_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_NN_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NN_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_NN_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_NN_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_NN_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_NN_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_NN_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NN_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_NN_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_NN_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_NN_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_NN_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NN_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_NN_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_NN_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_NN_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_NN_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_NN_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NN_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_NN_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_NN_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_NN_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_NN_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NN_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_NN_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_NN_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_NN_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_NN_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_NN_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NN_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_NN_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_NN_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_NN_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_NN_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NN_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_NN_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_NN_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_NN_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_NN_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_NN_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NN_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_NN_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_NN_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_NN_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_NN_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NN_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_NN_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_NN_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_NN_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_NN_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_NN_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NN_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_NN_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_NN_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_NN_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_NN_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NN_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_NN_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_NN_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_NN_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_NN_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_NN_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NN_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_NN_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_NN_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_NN_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_NN_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NN_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_NN_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_NN_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_NN_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_NN_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_NN_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NN_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_NN_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_NN_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_NN_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_NN_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NN_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_NN_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_NN_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_NN_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_NN_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_NN_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NN_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_NN_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_NN_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_NN_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_NN_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NN_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_NN_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_NN_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_NN_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_NN_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_NN_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NN_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_NN_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_NN_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_NN_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_NN_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NN_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_NN_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_NN_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_NN_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_NN_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_NN_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NN_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_NN_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_NN_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_NN_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_NN_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NN_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_NN_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_NN_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_NN_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_NN_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_NN_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NN_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_NN_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_NN_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_NN_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_NN_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NN_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_NN_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_NN_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_NN_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_NN_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_NN_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
      }
    } else if (transA == clblasNoTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NT_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_NT_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_NT_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_NT_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_NT_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NT_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_NT_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_NT_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_NT_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_NT_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_NT_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NT_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_NT_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_NT_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_NT_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_NT_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NT_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_NT_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_NT_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_NT_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_NT_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_NT_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NT_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_NT_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_NT_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_NT_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_NT_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NT_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_NT_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_NT_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_NT_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_NT_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_NT_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NT_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_NT_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_NT_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_NT_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_NT_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NT_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_NT_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_NT_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_NT_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_NT_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_NT_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NT_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_NT_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_NT_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_NT_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_NT_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NT_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_NT_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_NT_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_NT_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_NT_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_NT_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NT_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_NT_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_NT_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_NT_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_NT_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NT_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_NT_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_NT_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_NT_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_NT_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_NT_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NT_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_NT_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_NT_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_NT_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_NT_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NT_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_NT_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_NT_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_NT_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_NT_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_NT_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NT_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_NT_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_NT_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_NT_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_NT_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NT_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_NT_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_NT_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_NT_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_NT_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_NT_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NT_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_NT_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_NT_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_NT_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_NT_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NT_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_NT_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_NT_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_NT_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_NT_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_NT_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NT_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_NT_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_NT_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_NT_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_NT_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NT_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_NT_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_NT_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_NT_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_NT_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_NT_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NT_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_NT_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_NT_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_NT_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_NT_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NT_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_NT_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_NT_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_NT_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_NT_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_NT_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NT_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_NT_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_NT_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_NT_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_NT_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NT_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_NT_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_NT_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_NT_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_NT_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_NT_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NT_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_NT_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_NT_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_NT_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_NT_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NT_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_NT_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_NT_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_NT_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_NT_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_NT_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NT_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_NT_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_NT_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_NT_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_NT_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NT_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_NT_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_NT_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_NT_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_NT_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_NT_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NT_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_NT_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_NT_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_NT_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_NT_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NT_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_NT_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_NT_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_NT_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_NT_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_NT_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NT_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_NT_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_NT_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_NT_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_NT_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NT_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_NT_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_NT_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_NT_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_NT_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_NT_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
      }
    } else if (transA == clblasNoTrans && transB == clblasConjTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NC_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_NC_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_NC_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_NC_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_NC_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NC_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_NC_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_NC_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_NC_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_NC_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_NC_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NC_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_NC_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_NC_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_NC_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_NC_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NC_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_NC_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_NC_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_NC_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_NC_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_NC_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NC_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_NC_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_NC_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_NC_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_NC_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NC_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_NC_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_NC_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_NC_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_NC_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_NC_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NC_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_NC_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_NC_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_NC_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_NC_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NC_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_NC_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_NC_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_NC_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_NC_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_NC_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NC_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_NC_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_NC_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_NC_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_NC_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NC_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_NC_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_NC_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_NC_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_NC_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_NC_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NC_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_NC_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_NC_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_NC_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_NC_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NC_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_NC_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_NC_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_NC_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_NC_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_NC_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NC_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_NC_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_NC_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_NC_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_NC_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NC_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_NC_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_NC_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_NC_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_NC_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_NC_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NC_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_NC_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_NC_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_NC_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_NC_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NC_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_NC_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_NC_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_NC_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_NC_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_NC_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NC_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_NC_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_NC_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_NC_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_NC_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NC_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_NC_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_NC_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_NC_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_NC_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_NC_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NC_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_NC_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_NC_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_NC_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_NC_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NC_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_NC_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_NC_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_NC_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_NC_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_NC_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NC_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_NC_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_NC_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_NC_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_NC_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NC_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_NC_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_NC_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_NC_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_NC_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_NC_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NC_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_NC_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_NC_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_NC_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_NC_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NC_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_NC_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_NC_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_NC_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_NC_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_NC_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NC_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_NC_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_NC_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_NC_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_NC_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NC_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_NC_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_NC_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_NC_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_NC_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_NC_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NC_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_NC_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_NC_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_NC_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_NC_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NC_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_NC_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_NC_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_NC_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_NC_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_NC_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_NC_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_NC_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_NC_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_NC_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_NC_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NC_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_NC_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_NC_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_NC_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_NC_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_NC_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_NC_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_NC_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_NC_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_NC_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_NC_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_NC_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_NC_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_NC_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_NC_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_NC_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_NC_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TN_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_TN_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_TN_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_TN_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_TN_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TN_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_TN_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_TN_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_TN_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_TN_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_TN_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TN_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_TN_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_TN_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_TN_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_TN_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TN_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_TN_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_TN_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_TN_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_TN_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_TN_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TN_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_TN_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_TN_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_TN_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_TN_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TN_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_TN_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_TN_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_TN_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_TN_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_TN_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TN_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_TN_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_TN_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_TN_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_TN_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TN_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_TN_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_TN_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_TN_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_TN_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_TN_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TN_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_TN_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_TN_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_TN_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_TN_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TN_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_TN_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_TN_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_TN_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_TN_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_TN_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TN_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_TN_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_TN_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_TN_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_TN_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TN_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_TN_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_TN_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_TN_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_TN_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_TN_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TN_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_TN_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_TN_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_TN_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_TN_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TN_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_TN_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_TN_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_TN_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_TN_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_TN_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TN_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_TN_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_TN_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_TN_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_TN_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TN_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_TN_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_TN_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_TN_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_TN_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_TN_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TN_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_TN_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_TN_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_TN_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_TN_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TN_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_TN_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_TN_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_TN_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_TN_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_TN_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TN_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_TN_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_TN_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_TN_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_TN_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TN_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_TN_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_TN_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_TN_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_TN_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_TN_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TN_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_TN_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_TN_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_TN_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_TN_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TN_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_TN_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_TN_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_TN_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_TN_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_TN_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TN_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_TN_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_TN_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_TN_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_TN_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TN_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_TN_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_TN_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_TN_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_TN_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_TN_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TN_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_TN_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_TN_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_TN_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_TN_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TN_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_TN_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_TN_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_TN_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_TN_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_TN_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TN_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_TN_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_TN_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_TN_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_TN_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TN_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_TN_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_TN_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_TN_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_TN_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_TN_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TN_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_TN_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_TN_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_TN_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_TN_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TN_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_TN_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_TN_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_TN_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_TN_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_TN_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TN_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_TN_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_TN_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_TN_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_TN_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TN_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_TN_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_TN_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_TN_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_TN_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_TN_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TT_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_TT_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_TT_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_TT_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_TT_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TT_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_TT_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_TT_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_TT_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_TT_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_TT_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TT_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_TT_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_TT_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_TT_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_TT_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TT_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_TT_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_TT_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_TT_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_TT_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_TT_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TT_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_TT_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_TT_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_TT_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_TT_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TT_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_TT_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_TT_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_TT_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_TT_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_TT_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TT_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_TT_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_TT_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_TT_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_TT_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TT_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_TT_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_TT_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_TT_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_TT_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_TT_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TT_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_TT_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_TT_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_TT_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_TT_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TT_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_TT_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_TT_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_TT_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_TT_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_TT_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TT_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_TT_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_TT_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_TT_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_TT_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TT_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_TT_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_TT_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_TT_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_TT_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_TT_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TT_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_TT_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_TT_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_TT_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_TT_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TT_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_TT_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_TT_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_TT_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_TT_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_TT_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TT_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_TT_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_TT_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_TT_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_TT_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TT_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_TT_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_TT_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_TT_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_TT_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_TT_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TT_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_TT_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_TT_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_TT_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_TT_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TT_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_TT_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_TT_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_TT_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_TT_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_TT_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TT_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_TT_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_TT_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_TT_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_TT_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TT_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_TT_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_TT_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_TT_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_TT_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_TT_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TT_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_TT_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_TT_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_TT_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_TT_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TT_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_TT_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_TT_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_TT_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_TT_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_TT_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TT_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_TT_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_TT_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_TT_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_TT_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TT_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_TT_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_TT_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_TT_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_TT_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_TT_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TT_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_TT_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_TT_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_TT_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_TT_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TT_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_TT_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_TT_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_TT_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_TT_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_TT_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TT_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_TT_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_TT_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_TT_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_TT_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TT_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_TT_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_TT_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_TT_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_TT_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_TT_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TT_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_TT_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_TT_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_TT_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_TT_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TT_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_TT_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_TT_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_TT_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_TT_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_TT_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TT_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_TT_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_TT_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_TT_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_TT_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TT_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_TT_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_TT_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_TT_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_TT_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_TT_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasConjTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TC_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_TC_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_TC_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_TC_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_TC_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TC_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_TC_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_TC_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_TC_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_TC_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_TC_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TC_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_TC_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_TC_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_TC_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_TC_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TC_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_TC_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_TC_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_TC_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_TC_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_TC_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TC_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_TC_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_TC_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_TC_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_TC_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TC_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_TC_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_TC_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_TC_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_TC_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_TC_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TC_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_TC_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_TC_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_TC_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_TC_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TC_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_TC_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_TC_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_TC_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_TC_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_TC_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TC_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_TC_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_TC_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_TC_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_TC_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TC_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_TC_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_TC_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_TC_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_TC_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_TC_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TC_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_TC_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_TC_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_TC_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_TC_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TC_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_TC_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_TC_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_TC_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_TC_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_TC_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TC_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_TC_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_TC_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_TC_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_TC_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TC_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_TC_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_TC_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_TC_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_TC_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_TC_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TC_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_TC_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_TC_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_TC_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_TC_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TC_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_TC_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_TC_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_TC_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_TC_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_TC_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TC_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_TC_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_TC_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_TC_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_TC_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TC_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_TC_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_TC_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_TC_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_TC_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_TC_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TC_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_TC_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_TC_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_TC_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_TC_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TC_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_TC_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_TC_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_TC_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_TC_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_TC_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TC_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_TC_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_TC_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_TC_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_TC_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TC_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_TC_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_TC_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_TC_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_TC_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_TC_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TC_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_TC_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_TC_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_TC_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_TC_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TC_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_TC_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_TC_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_TC_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_TC_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_TC_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TC_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_TC_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_TC_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_TC_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_TC_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TC_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_TC_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_TC_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_TC_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_TC_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_TC_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TC_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_TC_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_TC_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_TC_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_TC_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TC_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_TC_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_TC_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_TC_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_TC_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_TC_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_TC_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_TC_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_TC_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_TC_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_TC_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TC_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_TC_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_TC_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_TC_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_TC_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_TC_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_TC_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_TC_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_TC_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_TC_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_TC_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_TC_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_TC_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_TC_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_TC_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_TC_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_TC_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
      }
    } else if (transA == clblasConjTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CN_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_CN_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_CN_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_CN_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_CN_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CN_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_CN_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_CN_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_CN_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_CN_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_CN_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CN_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_CN_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_CN_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_CN_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_CN_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CN_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_CN_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_CN_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_CN_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_CN_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_CN_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CN_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_CN_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_CN_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_CN_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_CN_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CN_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_CN_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_CN_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_CN_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_CN_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_CN_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CN_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_CN_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_CN_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_CN_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_CN_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CN_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_CN_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_CN_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_CN_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_CN_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_CN_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CN_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_CN_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_CN_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_CN_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_CN_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CN_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_CN_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_CN_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_CN_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_CN_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_CN_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CN_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_CN_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_CN_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_CN_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_CN_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CN_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_CN_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_CN_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_CN_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_CN_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_CN_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CN_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_CN_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_CN_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_CN_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_CN_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CN_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_CN_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_CN_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_CN_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_CN_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_CN_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CN_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_CN_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_CN_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_CN_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_CN_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CN_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_CN_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_CN_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_CN_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_CN_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_CN_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CN_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_CN_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_CN_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_CN_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_CN_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CN_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_CN_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_CN_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_CN_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_CN_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_CN_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CN_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_CN_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_CN_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_CN_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_CN_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CN_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_CN_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_CN_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_CN_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_CN_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_CN_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CN_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_CN_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_CN_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_CN_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_CN_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CN_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_CN_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_CN_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_CN_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_CN_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_CN_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CN_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_CN_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_CN_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_CN_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_CN_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CN_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_CN_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_CN_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_CN_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_CN_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_CN_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CN_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_CN_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_CN_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_CN_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_CN_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CN_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_CN_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_CN_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_CN_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_CN_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_CN_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CN_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_CN_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_CN_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_CN_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_CN_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CN_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_CN_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_CN_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_CN_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_CN_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_CN_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CN_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_CN_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_CN_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_CN_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_CN_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CN_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_CN_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_CN_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_CN_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_CN_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_CN_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CN_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_CN_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_CN_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_CN_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_CN_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CN_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_CN_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_CN_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_CN_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_CN_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_CN_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
      }
    } else if (transA == clblasConjTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CT_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_CT_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_CT_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_CT_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_CT_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CT_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_CT_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_CT_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_CT_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_CT_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_CT_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CT_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_CT_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_CT_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_CT_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_CT_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CT_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_CT_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_CT_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_CT_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_CT_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_CT_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CT_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_CT_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_CT_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_CT_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_CT_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CT_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_CT_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_CT_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_CT_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_CT_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_CT_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CT_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_CT_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_CT_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_CT_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_CT_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CT_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_CT_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_CT_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_CT_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_CT_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_CT_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CT_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_CT_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_CT_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_CT_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_CT_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CT_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_CT_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_CT_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_CT_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_CT_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_CT_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CT_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_CT_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_CT_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_CT_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_CT_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CT_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_CT_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_CT_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_CT_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_CT_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_CT_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CT_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_CT_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_CT_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_CT_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_CT_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CT_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_CT_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_CT_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_CT_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_CT_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_CT_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CT_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_CT_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_CT_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_CT_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_CT_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CT_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_CT_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_CT_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_CT_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_CT_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_CT_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CT_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_CT_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_CT_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_CT_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_CT_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CT_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_CT_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_CT_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_CT_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_CT_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_CT_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CT_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_CT_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_CT_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_CT_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_CT_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CT_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_CT_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_CT_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_CT_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_CT_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_CT_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CT_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_CT_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_CT_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_CT_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_CT_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CT_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_CT_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_CT_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_CT_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_CT_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_CT_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CT_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_CT_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_CT_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_CT_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_CT_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CT_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_CT_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_CT_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_CT_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_CT_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_CT_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CT_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_CT_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_CT_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_CT_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_CT_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CT_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_CT_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_CT_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_CT_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_CT_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_CT_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CT_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_CT_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_CT_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_CT_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_CT_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CT_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_CT_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_CT_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_CT_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_CT_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_CT_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CT_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_CT_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_CT_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_CT_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_CT_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CT_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_CT_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_CT_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_CT_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_CT_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_CT_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CT_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_CT_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_CT_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_CT_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_CT_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CT_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_CT_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_CT_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_CT_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_CT_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_CT_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
      }
    } else if (transA == clblasConjTrans && transB == clblasConjTrans) {
      if ( !betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CC_B0_048_048_08_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_CC_B0_001_048_08_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_CC_B0_048_001_08_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_CC_B0_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_CC_B0_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CC_B0_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_CC_B0_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_CC_B0_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_CC_B0_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_CC_B0_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B0_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B0_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_CC_B0_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B0_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CC_B0_048_048_01_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_CC_B0_001_048_01_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_CC_B0_048_001_01_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_CC_B0_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_CC_B0_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CC_B0_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_CC_B0_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_CC_B0_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_CC_B0_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_CC_B0_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B0_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B0_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_CC_B0_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B0_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CC_B0_016_016_01_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_CC_B0_001_016_01_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_CC_B0_016_001_01_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_CC_B0_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_CC_B0_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CC_B0_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_CC_B0_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_CC_B0_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_CC_B0_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_CC_B0_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B0_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B0_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_CC_B0_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B0_001_001_01_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CC_B0_064_064_08_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_CC_B0_001_064_08_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_CC_B0_064_001_08_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_CC_B0_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_CC_B0_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CC_B0_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_CC_B0_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_CC_B0_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_CC_B0_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_CC_B0_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B0_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B0_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_CC_B0_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B0_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CC_B0_064_064_01_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_CC_B0_001_064_01_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_CC_B0_064_001_01_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_CC_B0_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_CC_B0_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CC_B0_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_CC_B0_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_CC_B0_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_CC_B0_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_CC_B0_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B0_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B0_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_CC_B0_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B0_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CC_B0_016_016_08_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_CC_B0_001_016_08_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_CC_B0_016_001_08_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_CC_B0_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_CC_B0_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CC_B0_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_CC_B0_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_CC_B0_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_CC_B0_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_CC_B0_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B0_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B0_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_CC_B0_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B0_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CC_B0_032_032_08_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_CC_B0_001_032_08_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_CC_B0_032_001_08_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_CC_B0_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_CC_B0_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CC_B0_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_CC_B0_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_CC_B0_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_CC_B0_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_CC_B0_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B0_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B0_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_CC_B0_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B0_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CC_B0_032_032_01_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_CC_B0_001_032_01_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_CC_B0_032_001_01_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_CC_B0_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_CC_B0_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CC_B0_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_CC_B0_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_CC_B0_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_CC_B0_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_CC_B0_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B0_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B0_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_CC_B0_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B0_001_001_01_16x16_02x02_clKernel;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CC_B1_048_048_08_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_CC_B1_001_048_08_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_CC_B1_048_001_08_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_CC_B1_001_001_08_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_CC_B1_048_048_08_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CC_B1_048_048_08_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_CC_B1_001_048_08_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_CC_B1_048_001_08_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_CC_B1_001_001_08_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_CC_B1_048_048_08_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B1_048_048_08_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B1_001_048_08_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_CC_B1_048_001_08_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B1_001_001_08_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 3 && microTileNumCols == 3 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CC_B1_048_048_01_16x16_03x03_src;
          *rowKernelSource    = zgemm_Col_CC_B1_001_048_01_16x16_03x03_src;
          *colKernelSource    = zgemm_Col_CC_B1_048_001_01_16x16_03x03_src;
          *cornerKernelSource = zgemm_Col_CC_B1_001_001_01_16x16_03x03_src;
          *sourceBuildOptions = zgemm_Col_CC_B1_048_048_01_16x16_03x03_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CC_B1_048_048_01_16x16_03x03_bin;
          *rowKernelBinary    = zgemm_Col_CC_B1_001_048_01_16x16_03x03_bin;
          *colKernelBinary    = zgemm_Col_CC_B1_048_001_01_16x16_03x03_bin;
          *cornerKernelBinary = zgemm_Col_CC_B1_001_001_01_16x16_03x03_bin;
          *binaryBuildOptions = zgemm_Col_CC_B1_048_048_01_16x16_03x03_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B1_048_048_01_16x16_03x03_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B1_001_048_01_16x16_03x03_clKernel;
          *colClKernel        = &zgemm_Col_CC_B1_048_001_01_16x16_03x03_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B1_001_001_01_16x16_03x03_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CC_B1_016_016_01_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_CC_B1_001_016_01_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_CC_B1_016_001_01_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_CC_B1_001_001_01_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_CC_B1_016_016_01_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CC_B1_016_016_01_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_CC_B1_001_016_01_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_CC_B1_016_001_01_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_CC_B1_001_001_01_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_CC_B1_016_016_01_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B1_016_016_01_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B1_001_016_01_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_CC_B1_016_001_01_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B1_001_001_01_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CC_B1_064_064_08_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_CC_B1_001_064_08_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_CC_B1_064_001_08_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_CC_B1_001_001_08_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_CC_B1_064_064_08_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CC_B1_064_064_08_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_CC_B1_001_064_08_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_CC_B1_064_001_08_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_CC_B1_001_001_08_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_CC_B1_064_064_08_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B1_064_064_08_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B1_001_064_08_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_CC_B1_064_001_08_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B1_001_001_08_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 4 && microTileNumCols == 4 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CC_B1_064_064_01_16x16_04x04_src;
          *rowKernelSource    = zgemm_Col_CC_B1_001_064_01_16x16_04x04_src;
          *colKernelSource    = zgemm_Col_CC_B1_064_001_01_16x16_04x04_src;
          *cornerKernelSource = zgemm_Col_CC_B1_001_001_01_16x16_04x04_src;
          *sourceBuildOptions = zgemm_Col_CC_B1_064_064_01_16x16_04x04_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CC_B1_064_064_01_16x16_04x04_bin;
          *rowKernelBinary    = zgemm_Col_CC_B1_001_064_01_16x16_04x04_bin;
          *colKernelBinary    = zgemm_Col_CC_B1_064_001_01_16x16_04x04_bin;
          *cornerKernelBinary = zgemm_Col_CC_B1_001_001_01_16x16_04x04_bin;
          *binaryBuildOptions = zgemm_Col_CC_B1_064_064_01_16x16_04x04_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B1_064_064_01_16x16_04x04_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B1_001_064_01_16x16_04x04_clKernel;
          *colClKernel        = &zgemm_Col_CC_B1_064_001_01_16x16_04x04_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B1_001_001_01_16x16_04x04_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 1 && microTileNumCols == 1 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CC_B1_016_016_08_16x16_01x01_src;
          *rowKernelSource    = zgemm_Col_CC_B1_001_016_08_16x16_01x01_src;
          *colKernelSource    = zgemm_Col_CC_B1_016_001_08_16x16_01x01_src;
          *cornerKernelSource = zgemm_Col_CC_B1_001_001_08_16x16_01x01_src;
          *sourceBuildOptions = zgemm_Col_CC_B1_016_016_08_16x16_01x01_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CC_B1_016_016_08_16x16_01x01_bin;
          *rowKernelBinary    = zgemm_Col_CC_B1_001_016_08_16x16_01x01_bin;
          *colKernelBinary    = zgemm_Col_CC_B1_016_001_08_16x16_01x01_bin;
          *cornerKernelBinary = zgemm_Col_CC_B1_001_001_08_16x16_01x01_bin;
          *binaryBuildOptions = zgemm_Col_CC_B1_016_016_08_16x16_01x01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B1_016_016_08_16x16_01x01_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B1_001_016_08_16x16_01x01_clKernel;
          *colClKernel        = &zgemm_Col_CC_B1_016_001_08_16x16_01x01_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B1_001_001_08_16x16_01x01_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 8) {
          *tileKernelSource   = zgemm_Col_CC_B1_032_032_08_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_CC_B1_001_032_08_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_CC_B1_032_001_08_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_CC_B1_001_001_08_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_CC_B1_032_032_08_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CC_B1_032_032_08_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_CC_B1_001_032_08_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_CC_B1_032_001_08_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_CC_B1_001_001_08_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_CC_B1_032_032_08_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B1_032_032_08_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B1_001_032_08_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_CC_B1_032_001_08_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B1_001_001_08_16x16_02x02_clKernel;
          return true;
        }
        if ( workGroupNumRows == 16 && workGroupNumCols == 16 && microTileNumRows == 2 && microTileNumCols == 2 && unroll == 1) {
          *tileKernelSource   = zgemm_Col_CC_B1_032_032_01_16x16_02x02_src;
          *rowKernelSource    = zgemm_Col_CC_B1_001_032_01_16x16_02x02_src;
          *colKernelSource    = zgemm_Col_CC_B1_032_001_01_16x16_02x02_src;
          *cornerKernelSource = zgemm_Col_CC_B1_001_001_01_16x16_02x02_src;
          *sourceBuildOptions = zgemm_Col_CC_B1_032_032_01_16x16_02x02_srcBuildOptions;
          *tileKernelBinary   = zgemm_Col_CC_B1_032_032_01_16x16_02x02_bin;
          *rowKernelBinary    = zgemm_Col_CC_B1_001_032_01_16x16_02x02_bin;
          *colKernelBinary    = zgemm_Col_CC_B1_032_001_01_16x16_02x02_bin;
          *cornerKernelBinary = zgemm_Col_CC_B1_001_001_01_16x16_02x02_bin;
          *binaryBuildOptions = zgemm_Col_CC_B1_032_032_01_16x16_02x02_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B1_032_032_01_16x16_02x02_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B1_001_032_01_16x16_02x02_clKernel;
          *colClKernel        = &zgemm_Col_CC_B1_032_001_01_16x16_02x02_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B1_001_001_01_16x16_02x02_clKernel;
          return true;
        }
      }
    }
  }
  return false; // didn't find a match
}

