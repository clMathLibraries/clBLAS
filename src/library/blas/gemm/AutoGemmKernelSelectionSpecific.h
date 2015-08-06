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
  unsigned int macroTileNumRows,
  unsigned int macroTileNumCols,
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
  cl_kernel  **cornerClKernel,
  unsigned int *workGroupNumRows,
  unsigned int *workGroupNumCols,
  unsigned int *microTileNumRows,
  unsigned int *microTileNumCols
);

  // sgemm kernel selection specific
template<>
bool gemmSelectKernelSpecific<float>(
  clblasOrder order,
  clblasTranspose transA,
  clblasTranspose transB,
  bool betaNonZero,
  unsigned int macroTileNumRows,
  unsigned int macroTileNumCols,
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
  cl_kernel  **cornerClKernel,
  unsigned int *workGroupNumRows,
  unsigned int *workGroupNumCols,
  unsigned int *microTileNumRows,
  unsigned int *microTileNumCols
) {
  if (order == clblasColumnMajor) {
    if (transA == clblasNoTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NN_B0_MX096_NX096_KX16_src;
          *rowKernelSource    =  sgemm_Col_NN_B0_ML096_NX096_KX16_src;
          *colKernelSource    =  sgemm_Col_NN_B0_MX096_NL096_KX16_src;
          *cornerKernelSource =  sgemm_Col_NN_B0_ML096_NL096_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NN_B0_MX096_NX096_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B0_MX096_NX096_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B0_ML096_NX096_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NN_B0_MX096_NL096_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B0_ML096_NL096_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B0_MX096_NX096_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_MX096_NX096_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_ML096_NX096_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_MX096_NL096_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_ML096_NL096_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B0_MX096_NX096_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B0_MX096_NX096_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B0_MX096_NX096_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B0_MX096_NX096_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NN_B0_MX096_NX096_KX01_src;
          *rowKernelSource    =  sgemm_Col_NN_B0_ML096_NX096_KX01_src;
          *colKernelSource    =  sgemm_Col_NN_B0_MX096_NL096_KX01_src;
          *cornerKernelSource =  sgemm_Col_NN_B0_ML096_NL096_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NN_B0_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B0_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B0_ML096_NX096_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NN_B0_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B0_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B0_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_ML096_NX096_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B0_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B0_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B0_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B0_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 128 && macroTileNumCols == 128 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NN_B0_MX128_NX128_KX16_src;
          *rowKernelSource    =  sgemm_Col_NN_B0_ML128_NX128_KX16_src;
          *colKernelSource    =  sgemm_Col_NN_B0_MX128_NL128_KX16_src;
          *cornerKernelSource =  sgemm_Col_NN_B0_ML128_NL128_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NN_B0_MX128_NX128_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B0_MX128_NX128_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B0_ML128_NX128_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NN_B0_MX128_NL128_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B0_ML128_NL128_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B0_MX128_NX128_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_MX128_NX128_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_ML128_NX128_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_MX128_NL128_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_ML128_NL128_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B0_MX128_NX128_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B0_MX128_NX128_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B0_MX128_NX128_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B0_MX128_NX128_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 128 && macroTileNumCols == 128 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NN_B0_MX128_NX128_KX01_src;
          *rowKernelSource    =  sgemm_Col_NN_B0_ML128_NX128_KX01_src;
          *colKernelSource    =  sgemm_Col_NN_B0_MX128_NL128_KX01_src;
          *cornerKernelSource =  sgemm_Col_NN_B0_ML128_NL128_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NN_B0_MX128_NX128_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B0_MX128_NX128_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B0_ML128_NX128_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NN_B0_MX128_NL128_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B0_ML128_NL128_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B0_MX128_NX128_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_MX128_NX128_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_ML128_NX128_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_MX128_NL128_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_ML128_NL128_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B0_MX128_NX128_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B0_MX128_NX128_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B0_MX128_NX128_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B0_MX128_NX128_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NN_B0_MX064_NX064_KX16_src;
          *rowKernelSource    =  sgemm_Col_NN_B0_ML064_NX064_KX16_src;
          *colKernelSource    =  sgemm_Col_NN_B0_MX064_NL064_KX16_src;
          *cornerKernelSource =  sgemm_Col_NN_B0_ML064_NL064_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NN_B0_MX064_NX064_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B0_MX064_NX064_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B0_ML064_NX064_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NN_B0_MX064_NL064_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B0_ML064_NL064_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B0_MX064_NX064_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_MX064_NX064_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_ML064_NX064_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_MX064_NL064_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_ML064_NL064_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B0_MX064_NX064_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B0_MX064_NX064_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B0_MX064_NX064_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B0_MX064_NX064_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NN_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  sgemm_Col_NN_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  sgemm_Col_NN_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  sgemm_Col_NN_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NN_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NN_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NN_B0_MX080_NX080_KX16_src;
          *rowKernelSource    =  sgemm_Col_NN_B0_ML080_NX080_KX16_src;
          *colKernelSource    =  sgemm_Col_NN_B0_MX080_NL080_KX16_src;
          *cornerKernelSource =  sgemm_Col_NN_B0_ML080_NL080_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NN_B0_MX080_NX080_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B0_MX080_NX080_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B0_ML080_NX080_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NN_B0_MX080_NL080_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B0_ML080_NL080_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B0_MX080_NX080_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_MX080_NX080_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_ML080_NX080_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_MX080_NL080_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_ML080_NL080_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B0_MX080_NX080_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B0_MX080_NX080_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B0_MX080_NX080_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B0_MX080_NX080_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NN_B0_MX080_NX080_KX01_src;
          *rowKernelSource    =  sgemm_Col_NN_B0_ML080_NX080_KX01_src;
          *colKernelSource    =  sgemm_Col_NN_B0_MX080_NL080_KX01_src;
          *cornerKernelSource =  sgemm_Col_NN_B0_ML080_NL080_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NN_B0_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B0_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B0_ML080_NX080_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NN_B0_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B0_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B0_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_ML080_NX080_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B0_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B0_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B0_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B0_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NN_B0_MX048_NX048_KX16_src;
          *rowKernelSource    =  sgemm_Col_NN_B0_ML048_NX048_KX16_src;
          *colKernelSource    =  sgemm_Col_NN_B0_MX048_NL048_KX16_src;
          *cornerKernelSource =  sgemm_Col_NN_B0_ML048_NL048_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NN_B0_MX048_NX048_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B0_MX048_NX048_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B0_ML048_NX048_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NN_B0_MX048_NL048_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B0_ML048_NL048_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B0_MX048_NX048_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_MX048_NX048_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_ML048_NX048_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_MX048_NL048_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_ML048_NL048_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B0_MX048_NX048_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B0_MX048_NX048_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B0_MX048_NX048_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B0_MX048_NX048_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NN_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  sgemm_Col_NN_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  sgemm_Col_NN_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  sgemm_Col_NN_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NN_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NN_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 112 && macroTileNumCols == 112 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NN_B0_MX112_NX112_KX16_src;
          *rowKernelSource    =  sgemm_Col_NN_B0_ML112_NX112_KX16_src;
          *colKernelSource    =  sgemm_Col_NN_B0_MX112_NL112_KX16_src;
          *cornerKernelSource =  sgemm_Col_NN_B0_ML112_NL112_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NN_B0_MX112_NX112_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B0_MX112_NX112_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B0_ML112_NX112_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NN_B0_MX112_NL112_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B0_ML112_NL112_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B0_MX112_NX112_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_MX112_NX112_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_ML112_NX112_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_MX112_NL112_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_ML112_NL112_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B0_MX112_NX112_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B0_MX112_NX112_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B0_MX112_NX112_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B0_MX112_NX112_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 112 && macroTileNumCols == 112 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NN_B0_MX112_NX112_KX01_src;
          *rowKernelSource    =  sgemm_Col_NN_B0_ML112_NX112_KX01_src;
          *colKernelSource    =  sgemm_Col_NN_B0_MX112_NL112_KX01_src;
          *cornerKernelSource =  sgemm_Col_NN_B0_ML112_NL112_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NN_B0_MX112_NX112_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B0_MX112_NX112_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B0_ML112_NX112_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NN_B0_MX112_NL112_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B0_ML112_NL112_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B0_MX112_NX112_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_MX112_NX112_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_ML112_NX112_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_MX112_NL112_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_ML112_NL112_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B0_MX112_NX112_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B0_MX112_NX112_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B0_MX112_NX112_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B0_MX112_NX112_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NN_B0_MX032_NX032_KX16_src;
          *rowKernelSource    =  sgemm_Col_NN_B0_ML032_NX032_KX16_src;
          *colKernelSource    =  sgemm_Col_NN_B0_MX032_NL032_KX16_src;
          *cornerKernelSource =  sgemm_Col_NN_B0_ML032_NL032_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NN_B0_MX032_NX032_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B0_MX032_NX032_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B0_ML032_NX032_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NN_B0_MX032_NL032_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B0_ML032_NL032_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B0_MX032_NX032_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_MX032_NX032_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_ML032_NX032_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_MX032_NL032_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_ML032_NL032_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B0_MX032_NX032_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B0_MX032_NX032_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B0_MX032_NX032_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B0_MX032_NX032_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NN_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  sgemm_Col_NN_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  sgemm_Col_NN_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  sgemm_Col_NN_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NN_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NN_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NN_B0_MX016_NX016_KX16_src;
          *rowKernelSource    =  sgemm_Col_NN_B0_ML016_NX016_KX16_src;
          *colKernelSource    =  sgemm_Col_NN_B0_MX016_NL016_KX16_src;
          *cornerKernelSource =  sgemm_Col_NN_B0_ML016_NL016_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NN_B0_MX016_NX016_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B0_MX016_NX016_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B0_ML016_NX016_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NN_B0_MX016_NL016_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B0_ML016_NL016_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B0_MX016_NX016_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_MX016_NX016_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_ML016_NX016_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_MX016_NL016_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_ML016_NL016_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B0_MX016_NX016_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B0_MX016_NX016_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B0_MX016_NX016_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B0_MX016_NX016_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NN_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  sgemm_Col_NN_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  sgemm_Col_NN_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  sgemm_Col_NN_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NN_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NN_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NN_B1_MX096_NX096_KX16_src;
          *rowKernelSource    =  sgemm_Col_NN_B1_ML096_NX096_KX16_src;
          *colKernelSource    =  sgemm_Col_NN_B1_MX096_NL096_KX16_src;
          *cornerKernelSource =  sgemm_Col_NN_B1_ML096_NL096_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NN_B1_MX096_NX096_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B1_MX096_NX096_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B1_ML096_NX096_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NN_B1_MX096_NL096_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B1_ML096_NL096_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B1_MX096_NX096_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_MX096_NX096_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_ML096_NX096_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_MX096_NL096_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_ML096_NL096_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B1_MX096_NX096_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B1_MX096_NX096_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B1_MX096_NX096_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B1_MX096_NX096_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NN_B1_MX096_NX096_KX01_src;
          *rowKernelSource    =  sgemm_Col_NN_B1_ML096_NX096_KX01_src;
          *colKernelSource    =  sgemm_Col_NN_B1_MX096_NL096_KX01_src;
          *cornerKernelSource =  sgemm_Col_NN_B1_ML096_NL096_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NN_B1_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B1_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B1_ML096_NX096_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NN_B1_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B1_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B1_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_ML096_NX096_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B1_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B1_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B1_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B1_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 128 && macroTileNumCols == 128 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NN_B1_MX128_NX128_KX16_src;
          *rowKernelSource    =  sgemm_Col_NN_B1_ML128_NX128_KX16_src;
          *colKernelSource    =  sgemm_Col_NN_B1_MX128_NL128_KX16_src;
          *cornerKernelSource =  sgemm_Col_NN_B1_ML128_NL128_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NN_B1_MX128_NX128_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B1_MX128_NX128_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B1_ML128_NX128_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NN_B1_MX128_NL128_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B1_ML128_NL128_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B1_MX128_NX128_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_MX128_NX128_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_ML128_NX128_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_MX128_NL128_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_ML128_NL128_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B1_MX128_NX128_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B1_MX128_NX128_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B1_MX128_NX128_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B1_MX128_NX128_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 128 && macroTileNumCols == 128 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NN_B1_MX128_NX128_KX01_src;
          *rowKernelSource    =  sgemm_Col_NN_B1_ML128_NX128_KX01_src;
          *colKernelSource    =  sgemm_Col_NN_B1_MX128_NL128_KX01_src;
          *cornerKernelSource =  sgemm_Col_NN_B1_ML128_NL128_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NN_B1_MX128_NX128_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B1_MX128_NX128_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B1_ML128_NX128_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NN_B1_MX128_NL128_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B1_ML128_NL128_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B1_MX128_NX128_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_MX128_NX128_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_ML128_NX128_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_MX128_NL128_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_ML128_NL128_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B1_MX128_NX128_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B1_MX128_NX128_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B1_MX128_NX128_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B1_MX128_NX128_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NN_B1_MX064_NX064_KX16_src;
          *rowKernelSource    =  sgemm_Col_NN_B1_ML064_NX064_KX16_src;
          *colKernelSource    =  sgemm_Col_NN_B1_MX064_NL064_KX16_src;
          *cornerKernelSource =  sgemm_Col_NN_B1_ML064_NL064_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NN_B1_MX064_NX064_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B1_MX064_NX064_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B1_ML064_NX064_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NN_B1_MX064_NL064_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B1_ML064_NL064_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B1_MX064_NX064_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_MX064_NX064_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_ML064_NX064_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_MX064_NL064_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_ML064_NL064_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B1_MX064_NX064_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B1_MX064_NX064_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B1_MX064_NX064_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B1_MX064_NX064_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NN_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  sgemm_Col_NN_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  sgemm_Col_NN_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  sgemm_Col_NN_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NN_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NN_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NN_B1_MX080_NX080_KX16_src;
          *rowKernelSource    =  sgemm_Col_NN_B1_ML080_NX080_KX16_src;
          *colKernelSource    =  sgemm_Col_NN_B1_MX080_NL080_KX16_src;
          *cornerKernelSource =  sgemm_Col_NN_B1_ML080_NL080_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NN_B1_MX080_NX080_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B1_MX080_NX080_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B1_ML080_NX080_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NN_B1_MX080_NL080_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B1_ML080_NL080_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B1_MX080_NX080_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_MX080_NX080_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_ML080_NX080_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_MX080_NL080_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_ML080_NL080_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B1_MX080_NX080_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B1_MX080_NX080_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B1_MX080_NX080_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B1_MX080_NX080_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NN_B1_MX080_NX080_KX01_src;
          *rowKernelSource    =  sgemm_Col_NN_B1_ML080_NX080_KX01_src;
          *colKernelSource    =  sgemm_Col_NN_B1_MX080_NL080_KX01_src;
          *cornerKernelSource =  sgemm_Col_NN_B1_ML080_NL080_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NN_B1_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B1_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B1_ML080_NX080_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NN_B1_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B1_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B1_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_ML080_NX080_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B1_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B1_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B1_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B1_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NN_B1_MX048_NX048_KX16_src;
          *rowKernelSource    =  sgemm_Col_NN_B1_ML048_NX048_KX16_src;
          *colKernelSource    =  sgemm_Col_NN_B1_MX048_NL048_KX16_src;
          *cornerKernelSource =  sgemm_Col_NN_B1_ML048_NL048_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NN_B1_MX048_NX048_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B1_MX048_NX048_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B1_ML048_NX048_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NN_B1_MX048_NL048_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B1_ML048_NL048_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B1_MX048_NX048_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_MX048_NX048_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_ML048_NX048_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_MX048_NL048_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_ML048_NL048_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B1_MX048_NX048_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B1_MX048_NX048_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B1_MX048_NX048_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B1_MX048_NX048_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NN_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  sgemm_Col_NN_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  sgemm_Col_NN_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  sgemm_Col_NN_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NN_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NN_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 112 && macroTileNumCols == 112 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NN_B1_MX112_NX112_KX16_src;
          *rowKernelSource    =  sgemm_Col_NN_B1_ML112_NX112_KX16_src;
          *colKernelSource    =  sgemm_Col_NN_B1_MX112_NL112_KX16_src;
          *cornerKernelSource =  sgemm_Col_NN_B1_ML112_NL112_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NN_B1_MX112_NX112_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B1_MX112_NX112_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B1_ML112_NX112_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NN_B1_MX112_NL112_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B1_ML112_NL112_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B1_MX112_NX112_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_MX112_NX112_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_ML112_NX112_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_MX112_NL112_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_ML112_NL112_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B1_MX112_NX112_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B1_MX112_NX112_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B1_MX112_NX112_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B1_MX112_NX112_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 112 && macroTileNumCols == 112 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NN_B1_MX112_NX112_KX01_src;
          *rowKernelSource    =  sgemm_Col_NN_B1_ML112_NX112_KX01_src;
          *colKernelSource    =  sgemm_Col_NN_B1_MX112_NL112_KX01_src;
          *cornerKernelSource =  sgemm_Col_NN_B1_ML112_NL112_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NN_B1_MX112_NX112_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B1_MX112_NX112_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B1_ML112_NX112_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NN_B1_MX112_NL112_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B1_ML112_NL112_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B1_MX112_NX112_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_MX112_NX112_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_ML112_NX112_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_MX112_NL112_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_ML112_NL112_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B1_MX112_NX112_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B1_MX112_NX112_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B1_MX112_NX112_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B1_MX112_NX112_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NN_B1_MX032_NX032_KX16_src;
          *rowKernelSource    =  sgemm_Col_NN_B1_ML032_NX032_KX16_src;
          *colKernelSource    =  sgemm_Col_NN_B1_MX032_NL032_KX16_src;
          *cornerKernelSource =  sgemm_Col_NN_B1_ML032_NL032_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NN_B1_MX032_NX032_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B1_MX032_NX032_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B1_ML032_NX032_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NN_B1_MX032_NL032_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B1_ML032_NL032_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B1_MX032_NX032_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_MX032_NX032_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_ML032_NX032_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_MX032_NL032_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_ML032_NL032_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B1_MX032_NX032_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B1_MX032_NX032_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B1_MX032_NX032_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B1_MX032_NX032_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NN_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  sgemm_Col_NN_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  sgemm_Col_NN_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  sgemm_Col_NN_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NN_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NN_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NN_B1_MX016_NX016_KX16_src;
          *rowKernelSource    =  sgemm_Col_NN_B1_ML016_NX016_KX16_src;
          *colKernelSource    =  sgemm_Col_NN_B1_MX016_NL016_KX16_src;
          *cornerKernelSource =  sgemm_Col_NN_B1_ML016_NL016_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NN_B1_MX016_NX016_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B1_MX016_NX016_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B1_ML016_NX016_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NN_B1_MX016_NL016_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B1_ML016_NL016_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B1_MX016_NX016_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_MX016_NX016_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_ML016_NX016_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_MX016_NL016_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_ML016_NL016_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B1_MX016_NX016_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B1_MX016_NX016_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B1_MX016_NX016_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B1_MX016_NX016_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NN_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  sgemm_Col_NN_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  sgemm_Col_NN_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  sgemm_Col_NN_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NN_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NN_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NN_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NN_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NN_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NN_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NN_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NN_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NN_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NN_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NN_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NN_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NN_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NN_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasNoTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NT_B0_MX096_NX096_KX16_src;
          *rowKernelSource    =  sgemm_Col_NT_B0_ML096_NX096_KX16_src;
          *colKernelSource    =  sgemm_Col_NT_B0_MX096_NL096_KX16_src;
          *cornerKernelSource =  sgemm_Col_NT_B0_ML096_NL096_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NT_B0_MX096_NX096_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B0_MX096_NX096_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B0_ML096_NX096_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NT_B0_MX096_NL096_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B0_ML096_NL096_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B0_MX096_NX096_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_MX096_NX096_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_ML096_NX096_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_MX096_NL096_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_ML096_NL096_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B0_MX096_NX096_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B0_MX096_NX096_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B0_MX096_NX096_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B0_MX096_NX096_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NT_B0_MX096_NX096_KX01_src;
          *rowKernelSource    =  sgemm_Col_NT_B0_ML096_NX096_KX01_src;
          *colKernelSource    =  sgemm_Col_NT_B0_MX096_NL096_KX01_src;
          *cornerKernelSource =  sgemm_Col_NT_B0_ML096_NL096_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NT_B0_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B0_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B0_ML096_NX096_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NT_B0_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B0_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B0_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_ML096_NX096_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B0_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B0_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B0_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B0_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 128 && macroTileNumCols == 128 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NT_B0_MX128_NX128_KX16_src;
          *rowKernelSource    =  sgemm_Col_NT_B0_ML128_NX128_KX16_src;
          *colKernelSource    =  sgemm_Col_NT_B0_MX128_NL128_KX16_src;
          *cornerKernelSource =  sgemm_Col_NT_B0_ML128_NL128_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NT_B0_MX128_NX128_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B0_MX128_NX128_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B0_ML128_NX128_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NT_B0_MX128_NL128_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B0_ML128_NL128_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B0_MX128_NX128_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_MX128_NX128_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_ML128_NX128_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_MX128_NL128_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_ML128_NL128_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B0_MX128_NX128_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B0_MX128_NX128_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B0_MX128_NX128_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B0_MX128_NX128_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 128 && macroTileNumCols == 128 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NT_B0_MX128_NX128_KX01_src;
          *rowKernelSource    =  sgemm_Col_NT_B0_ML128_NX128_KX01_src;
          *colKernelSource    =  sgemm_Col_NT_B0_MX128_NL128_KX01_src;
          *cornerKernelSource =  sgemm_Col_NT_B0_ML128_NL128_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NT_B0_MX128_NX128_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B0_MX128_NX128_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B0_ML128_NX128_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NT_B0_MX128_NL128_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B0_ML128_NL128_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B0_MX128_NX128_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_MX128_NX128_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_ML128_NX128_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_MX128_NL128_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_ML128_NL128_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B0_MX128_NX128_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B0_MX128_NX128_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B0_MX128_NX128_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B0_MX128_NX128_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NT_B0_MX064_NX064_KX16_src;
          *rowKernelSource    =  sgemm_Col_NT_B0_ML064_NX064_KX16_src;
          *colKernelSource    =  sgemm_Col_NT_B0_MX064_NL064_KX16_src;
          *cornerKernelSource =  sgemm_Col_NT_B0_ML064_NL064_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NT_B0_MX064_NX064_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B0_MX064_NX064_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B0_ML064_NX064_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NT_B0_MX064_NL064_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B0_ML064_NL064_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B0_MX064_NX064_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_MX064_NX064_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_ML064_NX064_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_MX064_NL064_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_ML064_NL064_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B0_MX064_NX064_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B0_MX064_NX064_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B0_MX064_NX064_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B0_MX064_NX064_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NT_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  sgemm_Col_NT_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  sgemm_Col_NT_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  sgemm_Col_NT_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NT_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NT_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NT_B0_MX080_NX080_KX16_src;
          *rowKernelSource    =  sgemm_Col_NT_B0_ML080_NX080_KX16_src;
          *colKernelSource    =  sgemm_Col_NT_B0_MX080_NL080_KX16_src;
          *cornerKernelSource =  sgemm_Col_NT_B0_ML080_NL080_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NT_B0_MX080_NX080_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B0_MX080_NX080_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B0_ML080_NX080_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NT_B0_MX080_NL080_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B0_ML080_NL080_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B0_MX080_NX080_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_MX080_NX080_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_ML080_NX080_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_MX080_NL080_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_ML080_NL080_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B0_MX080_NX080_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B0_MX080_NX080_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B0_MX080_NX080_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B0_MX080_NX080_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NT_B0_MX080_NX080_KX01_src;
          *rowKernelSource    =  sgemm_Col_NT_B0_ML080_NX080_KX01_src;
          *colKernelSource    =  sgemm_Col_NT_B0_MX080_NL080_KX01_src;
          *cornerKernelSource =  sgemm_Col_NT_B0_ML080_NL080_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NT_B0_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B0_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B0_ML080_NX080_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NT_B0_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B0_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B0_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_ML080_NX080_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B0_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B0_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B0_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B0_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NT_B0_MX048_NX048_KX16_src;
          *rowKernelSource    =  sgemm_Col_NT_B0_ML048_NX048_KX16_src;
          *colKernelSource    =  sgemm_Col_NT_B0_MX048_NL048_KX16_src;
          *cornerKernelSource =  sgemm_Col_NT_B0_ML048_NL048_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NT_B0_MX048_NX048_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B0_MX048_NX048_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B0_ML048_NX048_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NT_B0_MX048_NL048_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B0_ML048_NL048_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B0_MX048_NX048_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_MX048_NX048_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_ML048_NX048_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_MX048_NL048_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_ML048_NL048_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B0_MX048_NX048_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B0_MX048_NX048_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B0_MX048_NX048_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B0_MX048_NX048_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NT_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  sgemm_Col_NT_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  sgemm_Col_NT_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  sgemm_Col_NT_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NT_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NT_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 112 && macroTileNumCols == 112 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NT_B0_MX112_NX112_KX16_src;
          *rowKernelSource    =  sgemm_Col_NT_B0_ML112_NX112_KX16_src;
          *colKernelSource    =  sgemm_Col_NT_B0_MX112_NL112_KX16_src;
          *cornerKernelSource =  sgemm_Col_NT_B0_ML112_NL112_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NT_B0_MX112_NX112_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B0_MX112_NX112_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B0_ML112_NX112_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NT_B0_MX112_NL112_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B0_ML112_NL112_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B0_MX112_NX112_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_MX112_NX112_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_ML112_NX112_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_MX112_NL112_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_ML112_NL112_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B0_MX112_NX112_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B0_MX112_NX112_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B0_MX112_NX112_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B0_MX112_NX112_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 112 && macroTileNumCols == 112 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NT_B0_MX112_NX112_KX01_src;
          *rowKernelSource    =  sgemm_Col_NT_B0_ML112_NX112_KX01_src;
          *colKernelSource    =  sgemm_Col_NT_B0_MX112_NL112_KX01_src;
          *cornerKernelSource =  sgemm_Col_NT_B0_ML112_NL112_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NT_B0_MX112_NX112_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B0_MX112_NX112_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B0_ML112_NX112_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NT_B0_MX112_NL112_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B0_ML112_NL112_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B0_MX112_NX112_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_MX112_NX112_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_ML112_NX112_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_MX112_NL112_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_ML112_NL112_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B0_MX112_NX112_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B0_MX112_NX112_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B0_MX112_NX112_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B0_MX112_NX112_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NT_B0_MX032_NX032_KX16_src;
          *rowKernelSource    =  sgemm_Col_NT_B0_ML032_NX032_KX16_src;
          *colKernelSource    =  sgemm_Col_NT_B0_MX032_NL032_KX16_src;
          *cornerKernelSource =  sgemm_Col_NT_B0_ML032_NL032_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NT_B0_MX032_NX032_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B0_MX032_NX032_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B0_ML032_NX032_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NT_B0_MX032_NL032_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B0_ML032_NL032_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B0_MX032_NX032_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_MX032_NX032_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_ML032_NX032_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_MX032_NL032_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_ML032_NL032_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B0_MX032_NX032_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B0_MX032_NX032_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B0_MX032_NX032_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B0_MX032_NX032_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NT_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  sgemm_Col_NT_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  sgemm_Col_NT_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  sgemm_Col_NT_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NT_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NT_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NT_B0_MX016_NX016_KX16_src;
          *rowKernelSource    =  sgemm_Col_NT_B0_ML016_NX016_KX16_src;
          *colKernelSource    =  sgemm_Col_NT_B0_MX016_NL016_KX16_src;
          *cornerKernelSource =  sgemm_Col_NT_B0_ML016_NL016_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NT_B0_MX016_NX016_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B0_MX016_NX016_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B0_ML016_NX016_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NT_B0_MX016_NL016_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B0_ML016_NL016_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B0_MX016_NX016_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_MX016_NX016_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_ML016_NX016_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_MX016_NL016_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_ML016_NL016_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B0_MX016_NX016_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B0_MX016_NX016_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B0_MX016_NX016_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B0_MX016_NX016_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NT_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  sgemm_Col_NT_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  sgemm_Col_NT_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  sgemm_Col_NT_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NT_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NT_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NT_B1_MX096_NX096_KX16_src;
          *rowKernelSource    =  sgemm_Col_NT_B1_ML096_NX096_KX16_src;
          *colKernelSource    =  sgemm_Col_NT_B1_MX096_NL096_KX16_src;
          *cornerKernelSource =  sgemm_Col_NT_B1_ML096_NL096_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NT_B1_MX096_NX096_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B1_MX096_NX096_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B1_ML096_NX096_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NT_B1_MX096_NL096_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B1_ML096_NL096_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B1_MX096_NX096_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_MX096_NX096_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_ML096_NX096_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_MX096_NL096_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_ML096_NL096_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B1_MX096_NX096_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B1_MX096_NX096_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B1_MX096_NX096_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B1_MX096_NX096_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NT_B1_MX096_NX096_KX01_src;
          *rowKernelSource    =  sgemm_Col_NT_B1_ML096_NX096_KX01_src;
          *colKernelSource    =  sgemm_Col_NT_B1_MX096_NL096_KX01_src;
          *cornerKernelSource =  sgemm_Col_NT_B1_ML096_NL096_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NT_B1_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B1_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B1_ML096_NX096_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NT_B1_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B1_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B1_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_ML096_NX096_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B1_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B1_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B1_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B1_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 128 && macroTileNumCols == 128 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NT_B1_MX128_NX128_KX16_src;
          *rowKernelSource    =  sgemm_Col_NT_B1_ML128_NX128_KX16_src;
          *colKernelSource    =  sgemm_Col_NT_B1_MX128_NL128_KX16_src;
          *cornerKernelSource =  sgemm_Col_NT_B1_ML128_NL128_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NT_B1_MX128_NX128_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B1_MX128_NX128_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B1_ML128_NX128_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NT_B1_MX128_NL128_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B1_ML128_NL128_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B1_MX128_NX128_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_MX128_NX128_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_ML128_NX128_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_MX128_NL128_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_ML128_NL128_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B1_MX128_NX128_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B1_MX128_NX128_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B1_MX128_NX128_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B1_MX128_NX128_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 128 && macroTileNumCols == 128 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NT_B1_MX128_NX128_KX01_src;
          *rowKernelSource    =  sgemm_Col_NT_B1_ML128_NX128_KX01_src;
          *colKernelSource    =  sgemm_Col_NT_B1_MX128_NL128_KX01_src;
          *cornerKernelSource =  sgemm_Col_NT_B1_ML128_NL128_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NT_B1_MX128_NX128_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B1_MX128_NX128_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B1_ML128_NX128_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NT_B1_MX128_NL128_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B1_ML128_NL128_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B1_MX128_NX128_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_MX128_NX128_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_ML128_NX128_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_MX128_NL128_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_ML128_NL128_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B1_MX128_NX128_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B1_MX128_NX128_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B1_MX128_NX128_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B1_MX128_NX128_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NT_B1_MX064_NX064_KX16_src;
          *rowKernelSource    =  sgemm_Col_NT_B1_ML064_NX064_KX16_src;
          *colKernelSource    =  sgemm_Col_NT_B1_MX064_NL064_KX16_src;
          *cornerKernelSource =  sgemm_Col_NT_B1_ML064_NL064_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NT_B1_MX064_NX064_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B1_MX064_NX064_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B1_ML064_NX064_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NT_B1_MX064_NL064_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B1_ML064_NL064_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B1_MX064_NX064_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_MX064_NX064_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_ML064_NX064_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_MX064_NL064_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_ML064_NL064_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B1_MX064_NX064_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B1_MX064_NX064_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B1_MX064_NX064_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B1_MX064_NX064_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NT_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  sgemm_Col_NT_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  sgemm_Col_NT_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  sgemm_Col_NT_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NT_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NT_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NT_B1_MX080_NX080_KX16_src;
          *rowKernelSource    =  sgemm_Col_NT_B1_ML080_NX080_KX16_src;
          *colKernelSource    =  sgemm_Col_NT_B1_MX080_NL080_KX16_src;
          *cornerKernelSource =  sgemm_Col_NT_B1_ML080_NL080_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NT_B1_MX080_NX080_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B1_MX080_NX080_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B1_ML080_NX080_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NT_B1_MX080_NL080_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B1_ML080_NL080_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B1_MX080_NX080_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_MX080_NX080_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_ML080_NX080_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_MX080_NL080_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_ML080_NL080_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B1_MX080_NX080_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B1_MX080_NX080_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B1_MX080_NX080_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B1_MX080_NX080_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NT_B1_MX080_NX080_KX01_src;
          *rowKernelSource    =  sgemm_Col_NT_B1_ML080_NX080_KX01_src;
          *colKernelSource    =  sgemm_Col_NT_B1_MX080_NL080_KX01_src;
          *cornerKernelSource =  sgemm_Col_NT_B1_ML080_NL080_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NT_B1_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B1_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B1_ML080_NX080_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NT_B1_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B1_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B1_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_ML080_NX080_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B1_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B1_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B1_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B1_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NT_B1_MX048_NX048_KX16_src;
          *rowKernelSource    =  sgemm_Col_NT_B1_ML048_NX048_KX16_src;
          *colKernelSource    =  sgemm_Col_NT_B1_MX048_NL048_KX16_src;
          *cornerKernelSource =  sgemm_Col_NT_B1_ML048_NL048_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NT_B1_MX048_NX048_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B1_MX048_NX048_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B1_ML048_NX048_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NT_B1_MX048_NL048_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B1_ML048_NL048_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B1_MX048_NX048_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_MX048_NX048_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_ML048_NX048_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_MX048_NL048_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_ML048_NL048_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B1_MX048_NX048_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B1_MX048_NX048_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B1_MX048_NX048_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B1_MX048_NX048_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NT_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  sgemm_Col_NT_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  sgemm_Col_NT_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  sgemm_Col_NT_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NT_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NT_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 112 && macroTileNumCols == 112 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NT_B1_MX112_NX112_KX16_src;
          *rowKernelSource    =  sgemm_Col_NT_B1_ML112_NX112_KX16_src;
          *colKernelSource    =  sgemm_Col_NT_B1_MX112_NL112_KX16_src;
          *cornerKernelSource =  sgemm_Col_NT_B1_ML112_NL112_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NT_B1_MX112_NX112_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B1_MX112_NX112_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B1_ML112_NX112_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NT_B1_MX112_NL112_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B1_ML112_NL112_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B1_MX112_NX112_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_MX112_NX112_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_ML112_NX112_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_MX112_NL112_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_ML112_NL112_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B1_MX112_NX112_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B1_MX112_NX112_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B1_MX112_NX112_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B1_MX112_NX112_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 112 && macroTileNumCols == 112 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NT_B1_MX112_NX112_KX01_src;
          *rowKernelSource    =  sgemm_Col_NT_B1_ML112_NX112_KX01_src;
          *colKernelSource    =  sgemm_Col_NT_B1_MX112_NL112_KX01_src;
          *cornerKernelSource =  sgemm_Col_NT_B1_ML112_NL112_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NT_B1_MX112_NX112_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B1_MX112_NX112_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B1_ML112_NX112_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NT_B1_MX112_NL112_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B1_ML112_NL112_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B1_MX112_NX112_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_MX112_NX112_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_ML112_NX112_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_MX112_NL112_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_ML112_NL112_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B1_MX112_NX112_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B1_MX112_NX112_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B1_MX112_NX112_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B1_MX112_NX112_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NT_B1_MX032_NX032_KX16_src;
          *rowKernelSource    =  sgemm_Col_NT_B1_ML032_NX032_KX16_src;
          *colKernelSource    =  sgemm_Col_NT_B1_MX032_NL032_KX16_src;
          *cornerKernelSource =  sgemm_Col_NT_B1_ML032_NL032_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NT_B1_MX032_NX032_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B1_MX032_NX032_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B1_ML032_NX032_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NT_B1_MX032_NL032_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B1_ML032_NL032_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B1_MX032_NX032_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_MX032_NX032_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_ML032_NX032_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_MX032_NL032_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_ML032_NL032_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B1_MX032_NX032_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B1_MX032_NX032_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B1_MX032_NX032_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B1_MX032_NX032_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NT_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  sgemm_Col_NT_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  sgemm_Col_NT_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  sgemm_Col_NT_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NT_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NT_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_NT_B1_MX016_NX016_KX16_src;
          *rowKernelSource    =  sgemm_Col_NT_B1_ML016_NX016_KX16_src;
          *colKernelSource    =  sgemm_Col_NT_B1_MX016_NL016_KX16_src;
          *cornerKernelSource =  sgemm_Col_NT_B1_ML016_NL016_KX16_src;
          *sourceBuildOptions =  sgemm_Col_NT_B1_MX016_NX016_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B1_MX016_NX016_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B1_ML016_NX016_KX16_bin;
          *colKernelBinary    =  sgemm_Col_NT_B1_MX016_NL016_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B1_ML016_NL016_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B1_MX016_NX016_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_MX016_NX016_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_ML016_NX016_KX16_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_MX016_NL016_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_ML016_NL016_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B1_MX016_NX016_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B1_MX016_NX016_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B1_MX016_NX016_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B1_MX016_NX016_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_NT_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  sgemm_Col_NT_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  sgemm_Col_NT_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  sgemm_Col_NT_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  sgemm_Col_NT_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_NT_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_NT_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  sgemm_Col_NT_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_NT_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_NT_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_NT_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_NT_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &sgemm_Col_NT_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_NT_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_NT_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_NT_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_NT_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_NT_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TN_B0_MX096_NX096_KX16_src;
          *rowKernelSource    =  sgemm_Col_TN_B0_ML096_NX096_KX16_src;
          *colKernelSource    =  sgemm_Col_TN_B0_MX096_NL096_KX16_src;
          *cornerKernelSource =  sgemm_Col_TN_B0_ML096_NL096_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TN_B0_MX096_NX096_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B0_MX096_NX096_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B0_ML096_NX096_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TN_B0_MX096_NL096_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B0_ML096_NL096_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B0_MX096_NX096_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_MX096_NX096_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_ML096_NX096_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_MX096_NL096_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_ML096_NL096_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B0_MX096_NX096_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B0_MX096_NX096_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B0_MX096_NX096_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B0_MX096_NX096_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TN_B0_MX096_NX096_KX01_src;
          *rowKernelSource    =  sgemm_Col_TN_B0_ML096_NX096_KX01_src;
          *colKernelSource    =  sgemm_Col_TN_B0_MX096_NL096_KX01_src;
          *cornerKernelSource =  sgemm_Col_TN_B0_ML096_NL096_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TN_B0_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B0_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B0_ML096_NX096_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TN_B0_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B0_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B0_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_ML096_NX096_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B0_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B0_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B0_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B0_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 128 && macroTileNumCols == 128 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TN_B0_MX128_NX128_KX16_src;
          *rowKernelSource    =  sgemm_Col_TN_B0_ML128_NX128_KX16_src;
          *colKernelSource    =  sgemm_Col_TN_B0_MX128_NL128_KX16_src;
          *cornerKernelSource =  sgemm_Col_TN_B0_ML128_NL128_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TN_B0_MX128_NX128_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B0_MX128_NX128_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B0_ML128_NX128_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TN_B0_MX128_NL128_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B0_ML128_NL128_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B0_MX128_NX128_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_MX128_NX128_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_ML128_NX128_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_MX128_NL128_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_ML128_NL128_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B0_MX128_NX128_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B0_MX128_NX128_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B0_MX128_NX128_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B0_MX128_NX128_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 128 && macroTileNumCols == 128 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TN_B0_MX128_NX128_KX01_src;
          *rowKernelSource    =  sgemm_Col_TN_B0_ML128_NX128_KX01_src;
          *colKernelSource    =  sgemm_Col_TN_B0_MX128_NL128_KX01_src;
          *cornerKernelSource =  sgemm_Col_TN_B0_ML128_NL128_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TN_B0_MX128_NX128_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B0_MX128_NX128_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B0_ML128_NX128_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TN_B0_MX128_NL128_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B0_ML128_NL128_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B0_MX128_NX128_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_MX128_NX128_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_ML128_NX128_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_MX128_NL128_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_ML128_NL128_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B0_MX128_NX128_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B0_MX128_NX128_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B0_MX128_NX128_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B0_MX128_NX128_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TN_B0_MX064_NX064_KX16_src;
          *rowKernelSource    =  sgemm_Col_TN_B0_ML064_NX064_KX16_src;
          *colKernelSource    =  sgemm_Col_TN_B0_MX064_NL064_KX16_src;
          *cornerKernelSource =  sgemm_Col_TN_B0_ML064_NL064_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TN_B0_MX064_NX064_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B0_MX064_NX064_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B0_ML064_NX064_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TN_B0_MX064_NL064_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B0_ML064_NL064_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B0_MX064_NX064_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_MX064_NX064_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_ML064_NX064_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_MX064_NL064_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_ML064_NL064_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B0_MX064_NX064_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B0_MX064_NX064_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B0_MX064_NX064_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B0_MX064_NX064_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TN_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  sgemm_Col_TN_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  sgemm_Col_TN_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  sgemm_Col_TN_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TN_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TN_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TN_B0_MX080_NX080_KX16_src;
          *rowKernelSource    =  sgemm_Col_TN_B0_ML080_NX080_KX16_src;
          *colKernelSource    =  sgemm_Col_TN_B0_MX080_NL080_KX16_src;
          *cornerKernelSource =  sgemm_Col_TN_B0_ML080_NL080_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TN_B0_MX080_NX080_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B0_MX080_NX080_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B0_ML080_NX080_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TN_B0_MX080_NL080_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B0_ML080_NL080_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B0_MX080_NX080_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_MX080_NX080_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_ML080_NX080_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_MX080_NL080_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_ML080_NL080_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B0_MX080_NX080_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B0_MX080_NX080_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B0_MX080_NX080_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B0_MX080_NX080_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TN_B0_MX080_NX080_KX01_src;
          *rowKernelSource    =  sgemm_Col_TN_B0_ML080_NX080_KX01_src;
          *colKernelSource    =  sgemm_Col_TN_B0_MX080_NL080_KX01_src;
          *cornerKernelSource =  sgemm_Col_TN_B0_ML080_NL080_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TN_B0_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B0_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B0_ML080_NX080_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TN_B0_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B0_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B0_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_ML080_NX080_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B0_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B0_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B0_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B0_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TN_B0_MX048_NX048_KX16_src;
          *rowKernelSource    =  sgemm_Col_TN_B0_ML048_NX048_KX16_src;
          *colKernelSource    =  sgemm_Col_TN_B0_MX048_NL048_KX16_src;
          *cornerKernelSource =  sgemm_Col_TN_B0_ML048_NL048_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TN_B0_MX048_NX048_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B0_MX048_NX048_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B0_ML048_NX048_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TN_B0_MX048_NL048_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B0_ML048_NL048_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B0_MX048_NX048_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_MX048_NX048_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_ML048_NX048_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_MX048_NL048_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_ML048_NL048_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B0_MX048_NX048_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B0_MX048_NX048_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B0_MX048_NX048_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B0_MX048_NX048_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TN_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  sgemm_Col_TN_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  sgemm_Col_TN_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  sgemm_Col_TN_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TN_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TN_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 112 && macroTileNumCols == 112 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TN_B0_MX112_NX112_KX16_src;
          *rowKernelSource    =  sgemm_Col_TN_B0_ML112_NX112_KX16_src;
          *colKernelSource    =  sgemm_Col_TN_B0_MX112_NL112_KX16_src;
          *cornerKernelSource =  sgemm_Col_TN_B0_ML112_NL112_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TN_B0_MX112_NX112_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B0_MX112_NX112_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B0_ML112_NX112_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TN_B0_MX112_NL112_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B0_ML112_NL112_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B0_MX112_NX112_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_MX112_NX112_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_ML112_NX112_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_MX112_NL112_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_ML112_NL112_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B0_MX112_NX112_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B0_MX112_NX112_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B0_MX112_NX112_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B0_MX112_NX112_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 112 && macroTileNumCols == 112 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TN_B0_MX112_NX112_KX01_src;
          *rowKernelSource    =  sgemm_Col_TN_B0_ML112_NX112_KX01_src;
          *colKernelSource    =  sgemm_Col_TN_B0_MX112_NL112_KX01_src;
          *cornerKernelSource =  sgemm_Col_TN_B0_ML112_NL112_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TN_B0_MX112_NX112_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B0_MX112_NX112_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B0_ML112_NX112_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TN_B0_MX112_NL112_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B0_ML112_NL112_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B0_MX112_NX112_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_MX112_NX112_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_ML112_NX112_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_MX112_NL112_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_ML112_NL112_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B0_MX112_NX112_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B0_MX112_NX112_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B0_MX112_NX112_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B0_MX112_NX112_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TN_B0_MX032_NX032_KX16_src;
          *rowKernelSource    =  sgemm_Col_TN_B0_ML032_NX032_KX16_src;
          *colKernelSource    =  sgemm_Col_TN_B0_MX032_NL032_KX16_src;
          *cornerKernelSource =  sgemm_Col_TN_B0_ML032_NL032_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TN_B0_MX032_NX032_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B0_MX032_NX032_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B0_ML032_NX032_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TN_B0_MX032_NL032_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B0_ML032_NL032_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B0_MX032_NX032_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_MX032_NX032_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_ML032_NX032_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_MX032_NL032_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_ML032_NL032_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B0_MX032_NX032_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B0_MX032_NX032_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B0_MX032_NX032_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B0_MX032_NX032_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TN_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  sgemm_Col_TN_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  sgemm_Col_TN_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  sgemm_Col_TN_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TN_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TN_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TN_B0_MX016_NX016_KX16_src;
          *rowKernelSource    =  sgemm_Col_TN_B0_ML016_NX016_KX16_src;
          *colKernelSource    =  sgemm_Col_TN_B0_MX016_NL016_KX16_src;
          *cornerKernelSource =  sgemm_Col_TN_B0_ML016_NL016_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TN_B0_MX016_NX016_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B0_MX016_NX016_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B0_ML016_NX016_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TN_B0_MX016_NL016_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B0_ML016_NL016_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B0_MX016_NX016_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_MX016_NX016_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_ML016_NX016_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_MX016_NL016_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_ML016_NL016_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B0_MX016_NX016_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B0_MX016_NX016_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B0_MX016_NX016_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B0_MX016_NX016_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TN_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  sgemm_Col_TN_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  sgemm_Col_TN_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  sgemm_Col_TN_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TN_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TN_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TN_B1_MX096_NX096_KX16_src;
          *rowKernelSource    =  sgemm_Col_TN_B1_ML096_NX096_KX16_src;
          *colKernelSource    =  sgemm_Col_TN_B1_MX096_NL096_KX16_src;
          *cornerKernelSource =  sgemm_Col_TN_B1_ML096_NL096_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TN_B1_MX096_NX096_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B1_MX096_NX096_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B1_ML096_NX096_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TN_B1_MX096_NL096_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B1_ML096_NL096_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B1_MX096_NX096_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_MX096_NX096_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_ML096_NX096_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_MX096_NL096_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_ML096_NL096_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B1_MX096_NX096_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B1_MX096_NX096_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B1_MX096_NX096_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B1_MX096_NX096_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TN_B1_MX096_NX096_KX01_src;
          *rowKernelSource    =  sgemm_Col_TN_B1_ML096_NX096_KX01_src;
          *colKernelSource    =  sgemm_Col_TN_B1_MX096_NL096_KX01_src;
          *cornerKernelSource =  sgemm_Col_TN_B1_ML096_NL096_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TN_B1_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B1_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B1_ML096_NX096_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TN_B1_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B1_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B1_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_ML096_NX096_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B1_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B1_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B1_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B1_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 128 && macroTileNumCols == 128 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TN_B1_MX128_NX128_KX16_src;
          *rowKernelSource    =  sgemm_Col_TN_B1_ML128_NX128_KX16_src;
          *colKernelSource    =  sgemm_Col_TN_B1_MX128_NL128_KX16_src;
          *cornerKernelSource =  sgemm_Col_TN_B1_ML128_NL128_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TN_B1_MX128_NX128_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B1_MX128_NX128_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B1_ML128_NX128_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TN_B1_MX128_NL128_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B1_ML128_NL128_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B1_MX128_NX128_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_MX128_NX128_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_ML128_NX128_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_MX128_NL128_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_ML128_NL128_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B1_MX128_NX128_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B1_MX128_NX128_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B1_MX128_NX128_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B1_MX128_NX128_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 128 && macroTileNumCols == 128 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TN_B1_MX128_NX128_KX01_src;
          *rowKernelSource    =  sgemm_Col_TN_B1_ML128_NX128_KX01_src;
          *colKernelSource    =  sgemm_Col_TN_B1_MX128_NL128_KX01_src;
          *cornerKernelSource =  sgemm_Col_TN_B1_ML128_NL128_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TN_B1_MX128_NX128_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B1_MX128_NX128_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B1_ML128_NX128_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TN_B1_MX128_NL128_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B1_ML128_NL128_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B1_MX128_NX128_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_MX128_NX128_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_ML128_NX128_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_MX128_NL128_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_ML128_NL128_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B1_MX128_NX128_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B1_MX128_NX128_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B1_MX128_NX128_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B1_MX128_NX128_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TN_B1_MX064_NX064_KX16_src;
          *rowKernelSource    =  sgemm_Col_TN_B1_ML064_NX064_KX16_src;
          *colKernelSource    =  sgemm_Col_TN_B1_MX064_NL064_KX16_src;
          *cornerKernelSource =  sgemm_Col_TN_B1_ML064_NL064_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TN_B1_MX064_NX064_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B1_MX064_NX064_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B1_ML064_NX064_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TN_B1_MX064_NL064_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B1_ML064_NL064_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B1_MX064_NX064_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_MX064_NX064_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_ML064_NX064_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_MX064_NL064_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_ML064_NL064_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B1_MX064_NX064_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B1_MX064_NX064_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B1_MX064_NX064_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B1_MX064_NX064_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TN_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  sgemm_Col_TN_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  sgemm_Col_TN_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  sgemm_Col_TN_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TN_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TN_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TN_B1_MX080_NX080_KX16_src;
          *rowKernelSource    =  sgemm_Col_TN_B1_ML080_NX080_KX16_src;
          *colKernelSource    =  sgemm_Col_TN_B1_MX080_NL080_KX16_src;
          *cornerKernelSource =  sgemm_Col_TN_B1_ML080_NL080_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TN_B1_MX080_NX080_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B1_MX080_NX080_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B1_ML080_NX080_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TN_B1_MX080_NL080_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B1_ML080_NL080_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B1_MX080_NX080_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_MX080_NX080_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_ML080_NX080_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_MX080_NL080_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_ML080_NL080_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B1_MX080_NX080_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B1_MX080_NX080_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B1_MX080_NX080_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B1_MX080_NX080_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TN_B1_MX080_NX080_KX01_src;
          *rowKernelSource    =  sgemm_Col_TN_B1_ML080_NX080_KX01_src;
          *colKernelSource    =  sgemm_Col_TN_B1_MX080_NL080_KX01_src;
          *cornerKernelSource =  sgemm_Col_TN_B1_ML080_NL080_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TN_B1_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B1_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B1_ML080_NX080_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TN_B1_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B1_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B1_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_ML080_NX080_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B1_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B1_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B1_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B1_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TN_B1_MX048_NX048_KX16_src;
          *rowKernelSource    =  sgemm_Col_TN_B1_ML048_NX048_KX16_src;
          *colKernelSource    =  sgemm_Col_TN_B1_MX048_NL048_KX16_src;
          *cornerKernelSource =  sgemm_Col_TN_B1_ML048_NL048_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TN_B1_MX048_NX048_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B1_MX048_NX048_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B1_ML048_NX048_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TN_B1_MX048_NL048_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B1_ML048_NL048_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B1_MX048_NX048_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_MX048_NX048_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_ML048_NX048_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_MX048_NL048_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_ML048_NL048_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B1_MX048_NX048_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B1_MX048_NX048_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B1_MX048_NX048_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B1_MX048_NX048_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TN_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  sgemm_Col_TN_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  sgemm_Col_TN_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  sgemm_Col_TN_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TN_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TN_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 112 && macroTileNumCols == 112 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TN_B1_MX112_NX112_KX16_src;
          *rowKernelSource    =  sgemm_Col_TN_B1_ML112_NX112_KX16_src;
          *colKernelSource    =  sgemm_Col_TN_B1_MX112_NL112_KX16_src;
          *cornerKernelSource =  sgemm_Col_TN_B1_ML112_NL112_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TN_B1_MX112_NX112_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B1_MX112_NX112_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B1_ML112_NX112_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TN_B1_MX112_NL112_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B1_ML112_NL112_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B1_MX112_NX112_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_MX112_NX112_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_ML112_NX112_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_MX112_NL112_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_ML112_NL112_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B1_MX112_NX112_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B1_MX112_NX112_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B1_MX112_NX112_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B1_MX112_NX112_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 112 && macroTileNumCols == 112 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TN_B1_MX112_NX112_KX01_src;
          *rowKernelSource    =  sgemm_Col_TN_B1_ML112_NX112_KX01_src;
          *colKernelSource    =  sgemm_Col_TN_B1_MX112_NL112_KX01_src;
          *cornerKernelSource =  sgemm_Col_TN_B1_ML112_NL112_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TN_B1_MX112_NX112_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B1_MX112_NX112_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B1_ML112_NX112_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TN_B1_MX112_NL112_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B1_ML112_NL112_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B1_MX112_NX112_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_MX112_NX112_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_ML112_NX112_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_MX112_NL112_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_ML112_NL112_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B1_MX112_NX112_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B1_MX112_NX112_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B1_MX112_NX112_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B1_MX112_NX112_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TN_B1_MX032_NX032_KX16_src;
          *rowKernelSource    =  sgemm_Col_TN_B1_ML032_NX032_KX16_src;
          *colKernelSource    =  sgemm_Col_TN_B1_MX032_NL032_KX16_src;
          *cornerKernelSource =  sgemm_Col_TN_B1_ML032_NL032_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TN_B1_MX032_NX032_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B1_MX032_NX032_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B1_ML032_NX032_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TN_B1_MX032_NL032_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B1_ML032_NL032_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B1_MX032_NX032_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_MX032_NX032_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_ML032_NX032_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_MX032_NL032_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_ML032_NL032_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B1_MX032_NX032_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B1_MX032_NX032_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B1_MX032_NX032_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B1_MX032_NX032_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TN_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  sgemm_Col_TN_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  sgemm_Col_TN_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  sgemm_Col_TN_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TN_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TN_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TN_B1_MX016_NX016_KX16_src;
          *rowKernelSource    =  sgemm_Col_TN_B1_ML016_NX016_KX16_src;
          *colKernelSource    =  sgemm_Col_TN_B1_MX016_NL016_KX16_src;
          *cornerKernelSource =  sgemm_Col_TN_B1_ML016_NL016_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TN_B1_MX016_NX016_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B1_MX016_NX016_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B1_ML016_NX016_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TN_B1_MX016_NL016_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B1_ML016_NL016_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B1_MX016_NX016_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_MX016_NX016_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_ML016_NX016_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_MX016_NL016_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_ML016_NL016_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B1_MX016_NX016_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B1_MX016_NX016_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B1_MX016_NX016_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B1_MX016_NX016_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TN_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  sgemm_Col_TN_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  sgemm_Col_TN_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  sgemm_Col_TN_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TN_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TN_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TN_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TN_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TN_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TN_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TN_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TN_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TN_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TN_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TN_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TN_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TN_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TN_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TT_B0_MX096_NX096_KX16_src;
          *rowKernelSource    =  sgemm_Col_TT_B0_ML096_NX096_KX16_src;
          *colKernelSource    =  sgemm_Col_TT_B0_MX096_NL096_KX16_src;
          *cornerKernelSource =  sgemm_Col_TT_B0_ML096_NL096_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TT_B0_MX096_NX096_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B0_MX096_NX096_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B0_ML096_NX096_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TT_B0_MX096_NL096_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B0_ML096_NL096_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B0_MX096_NX096_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_MX096_NX096_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_ML096_NX096_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_MX096_NL096_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_ML096_NL096_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B0_MX096_NX096_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B0_MX096_NX096_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B0_MX096_NX096_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B0_MX096_NX096_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TT_B0_MX096_NX096_KX01_src;
          *rowKernelSource    =  sgemm_Col_TT_B0_ML096_NX096_KX01_src;
          *colKernelSource    =  sgemm_Col_TT_B0_MX096_NL096_KX01_src;
          *cornerKernelSource =  sgemm_Col_TT_B0_ML096_NL096_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TT_B0_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B0_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B0_ML096_NX096_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TT_B0_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B0_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B0_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_ML096_NX096_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B0_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B0_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B0_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B0_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 128 && macroTileNumCols == 128 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TT_B0_MX128_NX128_KX16_src;
          *rowKernelSource    =  sgemm_Col_TT_B0_ML128_NX128_KX16_src;
          *colKernelSource    =  sgemm_Col_TT_B0_MX128_NL128_KX16_src;
          *cornerKernelSource =  sgemm_Col_TT_B0_ML128_NL128_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TT_B0_MX128_NX128_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B0_MX128_NX128_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B0_ML128_NX128_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TT_B0_MX128_NL128_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B0_ML128_NL128_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B0_MX128_NX128_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_MX128_NX128_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_ML128_NX128_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_MX128_NL128_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_ML128_NL128_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B0_MX128_NX128_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B0_MX128_NX128_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B0_MX128_NX128_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B0_MX128_NX128_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 128 && macroTileNumCols == 128 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TT_B0_MX128_NX128_KX01_src;
          *rowKernelSource    =  sgemm_Col_TT_B0_ML128_NX128_KX01_src;
          *colKernelSource    =  sgemm_Col_TT_B0_MX128_NL128_KX01_src;
          *cornerKernelSource =  sgemm_Col_TT_B0_ML128_NL128_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TT_B0_MX128_NX128_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B0_MX128_NX128_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B0_ML128_NX128_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TT_B0_MX128_NL128_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B0_ML128_NL128_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B0_MX128_NX128_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_MX128_NX128_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_ML128_NX128_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_MX128_NL128_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_ML128_NL128_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B0_MX128_NX128_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B0_MX128_NX128_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B0_MX128_NX128_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B0_MX128_NX128_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TT_B0_MX064_NX064_KX16_src;
          *rowKernelSource    =  sgemm_Col_TT_B0_ML064_NX064_KX16_src;
          *colKernelSource    =  sgemm_Col_TT_B0_MX064_NL064_KX16_src;
          *cornerKernelSource =  sgemm_Col_TT_B0_ML064_NL064_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TT_B0_MX064_NX064_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B0_MX064_NX064_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B0_ML064_NX064_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TT_B0_MX064_NL064_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B0_ML064_NL064_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B0_MX064_NX064_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_MX064_NX064_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_ML064_NX064_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_MX064_NL064_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_ML064_NL064_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B0_MX064_NX064_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B0_MX064_NX064_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B0_MX064_NX064_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B0_MX064_NX064_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TT_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  sgemm_Col_TT_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  sgemm_Col_TT_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  sgemm_Col_TT_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TT_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TT_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TT_B0_MX080_NX080_KX16_src;
          *rowKernelSource    =  sgemm_Col_TT_B0_ML080_NX080_KX16_src;
          *colKernelSource    =  sgemm_Col_TT_B0_MX080_NL080_KX16_src;
          *cornerKernelSource =  sgemm_Col_TT_B0_ML080_NL080_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TT_B0_MX080_NX080_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B0_MX080_NX080_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B0_ML080_NX080_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TT_B0_MX080_NL080_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B0_ML080_NL080_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B0_MX080_NX080_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_MX080_NX080_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_ML080_NX080_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_MX080_NL080_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_ML080_NL080_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B0_MX080_NX080_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B0_MX080_NX080_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B0_MX080_NX080_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B0_MX080_NX080_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TT_B0_MX080_NX080_KX01_src;
          *rowKernelSource    =  sgemm_Col_TT_B0_ML080_NX080_KX01_src;
          *colKernelSource    =  sgemm_Col_TT_B0_MX080_NL080_KX01_src;
          *cornerKernelSource =  sgemm_Col_TT_B0_ML080_NL080_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TT_B0_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B0_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B0_ML080_NX080_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TT_B0_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B0_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B0_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_ML080_NX080_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B0_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B0_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B0_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B0_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TT_B0_MX048_NX048_KX16_src;
          *rowKernelSource    =  sgemm_Col_TT_B0_ML048_NX048_KX16_src;
          *colKernelSource    =  sgemm_Col_TT_B0_MX048_NL048_KX16_src;
          *cornerKernelSource =  sgemm_Col_TT_B0_ML048_NL048_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TT_B0_MX048_NX048_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B0_MX048_NX048_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B0_ML048_NX048_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TT_B0_MX048_NL048_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B0_ML048_NL048_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B0_MX048_NX048_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_MX048_NX048_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_ML048_NX048_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_MX048_NL048_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_ML048_NL048_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B0_MX048_NX048_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B0_MX048_NX048_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B0_MX048_NX048_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B0_MX048_NX048_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TT_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  sgemm_Col_TT_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  sgemm_Col_TT_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  sgemm_Col_TT_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TT_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TT_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 112 && macroTileNumCols == 112 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TT_B0_MX112_NX112_KX16_src;
          *rowKernelSource    =  sgemm_Col_TT_B0_ML112_NX112_KX16_src;
          *colKernelSource    =  sgemm_Col_TT_B0_MX112_NL112_KX16_src;
          *cornerKernelSource =  sgemm_Col_TT_B0_ML112_NL112_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TT_B0_MX112_NX112_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B0_MX112_NX112_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B0_ML112_NX112_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TT_B0_MX112_NL112_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B0_ML112_NL112_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B0_MX112_NX112_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_MX112_NX112_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_ML112_NX112_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_MX112_NL112_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_ML112_NL112_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B0_MX112_NX112_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B0_MX112_NX112_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B0_MX112_NX112_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B0_MX112_NX112_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 112 && macroTileNumCols == 112 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TT_B0_MX112_NX112_KX01_src;
          *rowKernelSource    =  sgemm_Col_TT_B0_ML112_NX112_KX01_src;
          *colKernelSource    =  sgemm_Col_TT_B0_MX112_NL112_KX01_src;
          *cornerKernelSource =  sgemm_Col_TT_B0_ML112_NL112_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TT_B0_MX112_NX112_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B0_MX112_NX112_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B0_ML112_NX112_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TT_B0_MX112_NL112_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B0_ML112_NL112_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B0_MX112_NX112_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_MX112_NX112_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_ML112_NX112_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_MX112_NL112_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_ML112_NL112_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B0_MX112_NX112_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B0_MX112_NX112_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B0_MX112_NX112_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B0_MX112_NX112_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TT_B0_MX032_NX032_KX16_src;
          *rowKernelSource    =  sgemm_Col_TT_B0_ML032_NX032_KX16_src;
          *colKernelSource    =  sgemm_Col_TT_B0_MX032_NL032_KX16_src;
          *cornerKernelSource =  sgemm_Col_TT_B0_ML032_NL032_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TT_B0_MX032_NX032_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B0_MX032_NX032_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B0_ML032_NX032_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TT_B0_MX032_NL032_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B0_ML032_NL032_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B0_MX032_NX032_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_MX032_NX032_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_ML032_NX032_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_MX032_NL032_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_ML032_NL032_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B0_MX032_NX032_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B0_MX032_NX032_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B0_MX032_NX032_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B0_MX032_NX032_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TT_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  sgemm_Col_TT_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  sgemm_Col_TT_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  sgemm_Col_TT_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TT_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TT_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TT_B0_MX016_NX016_KX16_src;
          *rowKernelSource    =  sgemm_Col_TT_B0_ML016_NX016_KX16_src;
          *colKernelSource    =  sgemm_Col_TT_B0_MX016_NL016_KX16_src;
          *cornerKernelSource =  sgemm_Col_TT_B0_ML016_NL016_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TT_B0_MX016_NX016_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B0_MX016_NX016_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B0_ML016_NX016_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TT_B0_MX016_NL016_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B0_ML016_NL016_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B0_MX016_NX016_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_MX016_NX016_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_ML016_NX016_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_MX016_NL016_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_ML016_NL016_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B0_MX016_NX016_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B0_MX016_NX016_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B0_MX016_NX016_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B0_MX016_NX016_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TT_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  sgemm_Col_TT_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  sgemm_Col_TT_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  sgemm_Col_TT_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TT_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TT_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TT_B1_MX096_NX096_KX16_src;
          *rowKernelSource    =  sgemm_Col_TT_B1_ML096_NX096_KX16_src;
          *colKernelSource    =  sgemm_Col_TT_B1_MX096_NL096_KX16_src;
          *cornerKernelSource =  sgemm_Col_TT_B1_ML096_NL096_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TT_B1_MX096_NX096_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B1_MX096_NX096_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B1_ML096_NX096_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TT_B1_MX096_NL096_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B1_ML096_NL096_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B1_MX096_NX096_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_MX096_NX096_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_ML096_NX096_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_MX096_NL096_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_ML096_NL096_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B1_MX096_NX096_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B1_MX096_NX096_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B1_MX096_NX096_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B1_MX096_NX096_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TT_B1_MX096_NX096_KX01_src;
          *rowKernelSource    =  sgemm_Col_TT_B1_ML096_NX096_KX01_src;
          *colKernelSource    =  sgemm_Col_TT_B1_MX096_NL096_KX01_src;
          *cornerKernelSource =  sgemm_Col_TT_B1_ML096_NL096_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TT_B1_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B1_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B1_ML096_NX096_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TT_B1_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B1_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B1_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_ML096_NX096_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B1_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B1_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B1_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B1_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 128 && macroTileNumCols == 128 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TT_B1_MX128_NX128_KX16_src;
          *rowKernelSource    =  sgemm_Col_TT_B1_ML128_NX128_KX16_src;
          *colKernelSource    =  sgemm_Col_TT_B1_MX128_NL128_KX16_src;
          *cornerKernelSource =  sgemm_Col_TT_B1_ML128_NL128_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TT_B1_MX128_NX128_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B1_MX128_NX128_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B1_ML128_NX128_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TT_B1_MX128_NL128_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B1_ML128_NL128_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B1_MX128_NX128_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_MX128_NX128_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_ML128_NX128_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_MX128_NL128_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_ML128_NL128_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B1_MX128_NX128_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B1_MX128_NX128_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B1_MX128_NX128_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B1_MX128_NX128_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 128 && macroTileNumCols == 128 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TT_B1_MX128_NX128_KX01_src;
          *rowKernelSource    =  sgemm_Col_TT_B1_ML128_NX128_KX01_src;
          *colKernelSource    =  sgemm_Col_TT_B1_MX128_NL128_KX01_src;
          *cornerKernelSource =  sgemm_Col_TT_B1_ML128_NL128_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TT_B1_MX128_NX128_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B1_MX128_NX128_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B1_ML128_NX128_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TT_B1_MX128_NL128_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B1_ML128_NL128_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B1_MX128_NX128_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_MX128_NX128_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_ML128_NX128_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_MX128_NL128_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_ML128_NL128_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B1_MX128_NX128_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B1_MX128_NX128_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B1_MX128_NX128_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B1_MX128_NX128_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TT_B1_MX064_NX064_KX16_src;
          *rowKernelSource    =  sgemm_Col_TT_B1_ML064_NX064_KX16_src;
          *colKernelSource    =  sgemm_Col_TT_B1_MX064_NL064_KX16_src;
          *cornerKernelSource =  sgemm_Col_TT_B1_ML064_NL064_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TT_B1_MX064_NX064_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B1_MX064_NX064_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B1_ML064_NX064_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TT_B1_MX064_NL064_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B1_ML064_NL064_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B1_MX064_NX064_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_MX064_NX064_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_ML064_NX064_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_MX064_NL064_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_ML064_NL064_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B1_MX064_NX064_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B1_MX064_NX064_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B1_MX064_NX064_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B1_MX064_NX064_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TT_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  sgemm_Col_TT_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  sgemm_Col_TT_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  sgemm_Col_TT_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TT_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TT_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TT_B1_MX080_NX080_KX16_src;
          *rowKernelSource    =  sgemm_Col_TT_B1_ML080_NX080_KX16_src;
          *colKernelSource    =  sgemm_Col_TT_B1_MX080_NL080_KX16_src;
          *cornerKernelSource =  sgemm_Col_TT_B1_ML080_NL080_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TT_B1_MX080_NX080_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B1_MX080_NX080_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B1_ML080_NX080_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TT_B1_MX080_NL080_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B1_ML080_NL080_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B1_MX080_NX080_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_MX080_NX080_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_ML080_NX080_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_MX080_NL080_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_ML080_NL080_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B1_MX080_NX080_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B1_MX080_NX080_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B1_MX080_NX080_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B1_MX080_NX080_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TT_B1_MX080_NX080_KX01_src;
          *rowKernelSource    =  sgemm_Col_TT_B1_ML080_NX080_KX01_src;
          *colKernelSource    =  sgemm_Col_TT_B1_MX080_NL080_KX01_src;
          *cornerKernelSource =  sgemm_Col_TT_B1_ML080_NL080_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TT_B1_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B1_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B1_ML080_NX080_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TT_B1_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B1_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B1_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_ML080_NX080_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B1_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B1_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B1_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B1_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TT_B1_MX048_NX048_KX16_src;
          *rowKernelSource    =  sgemm_Col_TT_B1_ML048_NX048_KX16_src;
          *colKernelSource    =  sgemm_Col_TT_B1_MX048_NL048_KX16_src;
          *cornerKernelSource =  sgemm_Col_TT_B1_ML048_NL048_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TT_B1_MX048_NX048_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B1_MX048_NX048_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B1_ML048_NX048_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TT_B1_MX048_NL048_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B1_ML048_NL048_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B1_MX048_NX048_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_MX048_NX048_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_ML048_NX048_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_MX048_NL048_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_ML048_NL048_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B1_MX048_NX048_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B1_MX048_NX048_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B1_MX048_NX048_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B1_MX048_NX048_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TT_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  sgemm_Col_TT_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  sgemm_Col_TT_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  sgemm_Col_TT_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TT_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TT_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 112 && macroTileNumCols == 112 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TT_B1_MX112_NX112_KX16_src;
          *rowKernelSource    =  sgemm_Col_TT_B1_ML112_NX112_KX16_src;
          *colKernelSource    =  sgemm_Col_TT_B1_MX112_NL112_KX16_src;
          *cornerKernelSource =  sgemm_Col_TT_B1_ML112_NL112_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TT_B1_MX112_NX112_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B1_MX112_NX112_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B1_ML112_NX112_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TT_B1_MX112_NL112_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B1_ML112_NL112_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B1_MX112_NX112_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_MX112_NX112_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_ML112_NX112_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_MX112_NL112_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_ML112_NL112_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B1_MX112_NX112_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B1_MX112_NX112_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B1_MX112_NX112_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B1_MX112_NX112_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 112 && macroTileNumCols == 112 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TT_B1_MX112_NX112_KX01_src;
          *rowKernelSource    =  sgemm_Col_TT_B1_ML112_NX112_KX01_src;
          *colKernelSource    =  sgemm_Col_TT_B1_MX112_NL112_KX01_src;
          *cornerKernelSource =  sgemm_Col_TT_B1_ML112_NL112_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TT_B1_MX112_NX112_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B1_MX112_NX112_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B1_ML112_NX112_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TT_B1_MX112_NL112_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B1_ML112_NL112_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B1_MX112_NX112_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_MX112_NX112_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_ML112_NX112_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_MX112_NL112_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_ML112_NL112_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B1_MX112_NX112_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B1_MX112_NX112_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B1_MX112_NX112_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B1_MX112_NX112_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TT_B1_MX032_NX032_KX16_src;
          *rowKernelSource    =  sgemm_Col_TT_B1_ML032_NX032_KX16_src;
          *colKernelSource    =  sgemm_Col_TT_B1_MX032_NL032_KX16_src;
          *cornerKernelSource =  sgemm_Col_TT_B1_ML032_NL032_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TT_B1_MX032_NX032_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B1_MX032_NX032_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B1_ML032_NX032_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TT_B1_MX032_NL032_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B1_ML032_NL032_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B1_MX032_NX032_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_MX032_NX032_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_ML032_NX032_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_MX032_NL032_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_ML032_NL032_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B1_MX032_NX032_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B1_MX032_NX032_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B1_MX032_NX032_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B1_MX032_NX032_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TT_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  sgemm_Col_TT_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  sgemm_Col_TT_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  sgemm_Col_TT_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TT_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TT_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 16) {
          *tileKernelSource   =  sgemm_Col_TT_B1_MX016_NX016_KX16_src;
          *rowKernelSource    =  sgemm_Col_TT_B1_ML016_NX016_KX16_src;
          *colKernelSource    =  sgemm_Col_TT_B1_MX016_NL016_KX16_src;
          *cornerKernelSource =  sgemm_Col_TT_B1_ML016_NL016_KX16_src;
          *sourceBuildOptions =  sgemm_Col_TT_B1_MX016_NX016_KX16_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B1_MX016_NX016_KX16_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B1_ML016_NX016_KX16_bin;
          *colKernelBinary    =  sgemm_Col_TT_B1_MX016_NL016_KX16_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B1_ML016_NL016_KX16_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B1_MX016_NX016_KX16_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_MX016_NX016_KX16_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_ML016_NX016_KX16_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_MX016_NL016_KX16_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_ML016_NL016_KX16_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B1_MX016_NX016_KX16_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B1_MX016_NX016_KX16_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B1_MX016_NX016_KX16_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B1_MX016_NX016_KX16_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  sgemm_Col_TT_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  sgemm_Col_TT_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  sgemm_Col_TT_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  sgemm_Col_TT_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  sgemm_Col_TT_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  sgemm_Col_TT_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  sgemm_Col_TT_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  sgemm_Col_TT_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  sgemm_Col_TT_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  sgemm_Col_TT_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &sgemm_Col_TT_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &sgemm_Col_TT_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &sgemm_Col_TT_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &sgemm_Col_TT_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  sgemm_Col_TT_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  sgemm_Col_TT_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  sgemm_Col_TT_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  sgemm_Col_TT_B1_MX016_NX016_KX01_microTileNumCols;
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
  unsigned int macroTileNumRows,
  unsigned int macroTileNumCols,
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
  cl_kernel  **cornerClKernel,
  unsigned int *workGroupNumRows,
  unsigned int *workGroupNumCols,
  unsigned int *microTileNumRows,
  unsigned int *microTileNumCols
) {
  if (order == clblasColumnMajor) {
    if (transA == clblasNoTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NN_B0_MX096_NX096_KX01_src;
          *rowKernelSource    =  dgemm_Col_NN_B0_ML096_NX096_KX01_src;
          *colKernelSource    =  dgemm_Col_NN_B0_MX096_NL096_KX01_src;
          *cornerKernelSource =  dgemm_Col_NN_B0_ML096_NL096_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NN_B0_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B0_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B0_ML096_NX096_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NN_B0_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B0_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B0_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_ML096_NX096_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B0_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B0_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B0_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B0_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NN_B0_MX096_NX096_KX08_src;
          *rowKernelSource    =  dgemm_Col_NN_B0_ML096_NX096_KX08_src;
          *colKernelSource    =  dgemm_Col_NN_B0_MX096_NL096_KX08_src;
          *cornerKernelSource =  dgemm_Col_NN_B0_ML096_NL096_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NN_B0_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B0_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B0_ML096_NX096_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NN_B0_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B0_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B0_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_ML096_NX096_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B0_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B0_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B0_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B0_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NN_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  dgemm_Col_NN_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  dgemm_Col_NN_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  dgemm_Col_NN_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NN_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NN_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NN_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  dgemm_Col_NN_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  dgemm_Col_NN_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  dgemm_Col_NN_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NN_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NN_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NN_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  dgemm_Col_NN_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  dgemm_Col_NN_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  dgemm_Col_NN_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NN_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NN_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NN_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  dgemm_Col_NN_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  dgemm_Col_NN_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  dgemm_Col_NN_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NN_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NN_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NN_B0_MX080_NX080_KX08_src;
          *rowKernelSource    =  dgemm_Col_NN_B0_ML080_NX080_KX08_src;
          *colKernelSource    =  dgemm_Col_NN_B0_MX080_NL080_KX08_src;
          *cornerKernelSource =  dgemm_Col_NN_B0_ML080_NL080_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NN_B0_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B0_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B0_ML080_NX080_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NN_B0_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B0_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B0_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_ML080_NX080_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B0_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B0_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B0_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B0_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NN_B0_MX080_NX080_KX01_src;
          *rowKernelSource    =  dgemm_Col_NN_B0_ML080_NX080_KX01_src;
          *colKernelSource    =  dgemm_Col_NN_B0_MX080_NL080_KX01_src;
          *cornerKernelSource =  dgemm_Col_NN_B0_ML080_NL080_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NN_B0_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B0_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B0_ML080_NX080_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NN_B0_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B0_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B0_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_ML080_NX080_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B0_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B0_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B0_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B0_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NN_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  dgemm_Col_NN_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  dgemm_Col_NN_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  dgemm_Col_NN_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NN_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NN_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NN_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  dgemm_Col_NN_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  dgemm_Col_NN_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  dgemm_Col_NN_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NN_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NN_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NN_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  dgemm_Col_NN_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  dgemm_Col_NN_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  dgemm_Col_NN_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NN_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NN_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NN_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  dgemm_Col_NN_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  dgemm_Col_NN_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  dgemm_Col_NN_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NN_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NN_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NN_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NN_B1_MX096_NX096_KX01_src;
          *rowKernelSource    =  dgemm_Col_NN_B1_ML096_NX096_KX01_src;
          *colKernelSource    =  dgemm_Col_NN_B1_MX096_NL096_KX01_src;
          *cornerKernelSource =  dgemm_Col_NN_B1_ML096_NL096_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NN_B1_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B1_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B1_ML096_NX096_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NN_B1_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B1_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B1_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_ML096_NX096_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B1_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B1_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B1_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B1_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NN_B1_MX096_NX096_KX08_src;
          *rowKernelSource    =  dgemm_Col_NN_B1_ML096_NX096_KX08_src;
          *colKernelSource    =  dgemm_Col_NN_B1_MX096_NL096_KX08_src;
          *cornerKernelSource =  dgemm_Col_NN_B1_ML096_NL096_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NN_B1_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B1_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B1_ML096_NX096_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NN_B1_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B1_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B1_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_ML096_NX096_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B1_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B1_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B1_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B1_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NN_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  dgemm_Col_NN_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  dgemm_Col_NN_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  dgemm_Col_NN_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NN_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NN_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NN_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  dgemm_Col_NN_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  dgemm_Col_NN_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  dgemm_Col_NN_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NN_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NN_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NN_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  dgemm_Col_NN_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  dgemm_Col_NN_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  dgemm_Col_NN_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NN_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NN_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NN_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  dgemm_Col_NN_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  dgemm_Col_NN_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  dgemm_Col_NN_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NN_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NN_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NN_B1_MX080_NX080_KX08_src;
          *rowKernelSource    =  dgemm_Col_NN_B1_ML080_NX080_KX08_src;
          *colKernelSource    =  dgemm_Col_NN_B1_MX080_NL080_KX08_src;
          *cornerKernelSource =  dgemm_Col_NN_B1_ML080_NL080_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NN_B1_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B1_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B1_ML080_NX080_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NN_B1_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B1_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B1_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_ML080_NX080_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B1_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B1_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B1_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B1_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NN_B1_MX080_NX080_KX01_src;
          *rowKernelSource    =  dgemm_Col_NN_B1_ML080_NX080_KX01_src;
          *colKernelSource    =  dgemm_Col_NN_B1_MX080_NL080_KX01_src;
          *cornerKernelSource =  dgemm_Col_NN_B1_ML080_NL080_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NN_B1_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B1_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B1_ML080_NX080_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NN_B1_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B1_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B1_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_ML080_NX080_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B1_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B1_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B1_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B1_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NN_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  dgemm_Col_NN_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  dgemm_Col_NN_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  dgemm_Col_NN_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NN_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NN_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NN_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  dgemm_Col_NN_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  dgemm_Col_NN_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  dgemm_Col_NN_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NN_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NN_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NN_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  dgemm_Col_NN_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  dgemm_Col_NN_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  dgemm_Col_NN_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NN_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NN_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NN_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  dgemm_Col_NN_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  dgemm_Col_NN_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  dgemm_Col_NN_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NN_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NN_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NN_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NN_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NN_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NN_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NN_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NN_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NN_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NN_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NN_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NN_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NN_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NN_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasNoTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NT_B0_MX096_NX096_KX01_src;
          *rowKernelSource    =  dgemm_Col_NT_B0_ML096_NX096_KX01_src;
          *colKernelSource    =  dgemm_Col_NT_B0_MX096_NL096_KX01_src;
          *cornerKernelSource =  dgemm_Col_NT_B0_ML096_NL096_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NT_B0_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B0_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B0_ML096_NX096_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NT_B0_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B0_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B0_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_ML096_NX096_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B0_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B0_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B0_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B0_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NT_B0_MX096_NX096_KX08_src;
          *rowKernelSource    =  dgemm_Col_NT_B0_ML096_NX096_KX08_src;
          *colKernelSource    =  dgemm_Col_NT_B0_MX096_NL096_KX08_src;
          *cornerKernelSource =  dgemm_Col_NT_B0_ML096_NL096_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NT_B0_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B0_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B0_ML096_NX096_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NT_B0_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B0_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B0_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_ML096_NX096_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B0_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B0_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B0_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B0_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NT_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  dgemm_Col_NT_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  dgemm_Col_NT_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  dgemm_Col_NT_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NT_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NT_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NT_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  dgemm_Col_NT_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  dgemm_Col_NT_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  dgemm_Col_NT_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NT_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NT_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NT_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  dgemm_Col_NT_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  dgemm_Col_NT_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  dgemm_Col_NT_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NT_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NT_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NT_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  dgemm_Col_NT_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  dgemm_Col_NT_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  dgemm_Col_NT_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NT_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NT_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NT_B0_MX080_NX080_KX08_src;
          *rowKernelSource    =  dgemm_Col_NT_B0_ML080_NX080_KX08_src;
          *colKernelSource    =  dgemm_Col_NT_B0_MX080_NL080_KX08_src;
          *cornerKernelSource =  dgemm_Col_NT_B0_ML080_NL080_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NT_B0_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B0_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B0_ML080_NX080_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NT_B0_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B0_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B0_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_ML080_NX080_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B0_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B0_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B0_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B0_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NT_B0_MX080_NX080_KX01_src;
          *rowKernelSource    =  dgemm_Col_NT_B0_ML080_NX080_KX01_src;
          *colKernelSource    =  dgemm_Col_NT_B0_MX080_NL080_KX01_src;
          *cornerKernelSource =  dgemm_Col_NT_B0_ML080_NL080_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NT_B0_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B0_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B0_ML080_NX080_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NT_B0_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B0_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B0_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_ML080_NX080_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B0_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B0_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B0_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B0_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NT_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  dgemm_Col_NT_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  dgemm_Col_NT_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  dgemm_Col_NT_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NT_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NT_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NT_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  dgemm_Col_NT_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  dgemm_Col_NT_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  dgemm_Col_NT_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NT_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NT_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NT_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  dgemm_Col_NT_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  dgemm_Col_NT_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  dgemm_Col_NT_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NT_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NT_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NT_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  dgemm_Col_NT_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  dgemm_Col_NT_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  dgemm_Col_NT_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NT_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NT_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NT_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NT_B1_MX096_NX096_KX01_src;
          *rowKernelSource    =  dgemm_Col_NT_B1_ML096_NX096_KX01_src;
          *colKernelSource    =  dgemm_Col_NT_B1_MX096_NL096_KX01_src;
          *cornerKernelSource =  dgemm_Col_NT_B1_ML096_NL096_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NT_B1_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B1_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B1_ML096_NX096_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NT_B1_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B1_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B1_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_ML096_NX096_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B1_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B1_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B1_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B1_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NT_B1_MX096_NX096_KX08_src;
          *rowKernelSource    =  dgemm_Col_NT_B1_ML096_NX096_KX08_src;
          *colKernelSource    =  dgemm_Col_NT_B1_MX096_NL096_KX08_src;
          *cornerKernelSource =  dgemm_Col_NT_B1_ML096_NL096_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NT_B1_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B1_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B1_ML096_NX096_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NT_B1_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B1_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B1_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_ML096_NX096_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B1_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B1_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B1_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B1_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NT_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  dgemm_Col_NT_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  dgemm_Col_NT_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  dgemm_Col_NT_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NT_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NT_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NT_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  dgemm_Col_NT_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  dgemm_Col_NT_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  dgemm_Col_NT_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NT_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NT_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NT_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  dgemm_Col_NT_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  dgemm_Col_NT_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  dgemm_Col_NT_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NT_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NT_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NT_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  dgemm_Col_NT_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  dgemm_Col_NT_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  dgemm_Col_NT_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NT_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NT_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NT_B1_MX080_NX080_KX08_src;
          *rowKernelSource    =  dgemm_Col_NT_B1_ML080_NX080_KX08_src;
          *colKernelSource    =  dgemm_Col_NT_B1_MX080_NL080_KX08_src;
          *cornerKernelSource =  dgemm_Col_NT_B1_ML080_NL080_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NT_B1_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B1_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B1_ML080_NX080_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NT_B1_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B1_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B1_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_ML080_NX080_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B1_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B1_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B1_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B1_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NT_B1_MX080_NX080_KX01_src;
          *rowKernelSource    =  dgemm_Col_NT_B1_ML080_NX080_KX01_src;
          *colKernelSource    =  dgemm_Col_NT_B1_MX080_NL080_KX01_src;
          *cornerKernelSource =  dgemm_Col_NT_B1_ML080_NL080_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NT_B1_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B1_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B1_ML080_NX080_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NT_B1_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B1_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B1_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_ML080_NX080_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B1_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B1_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B1_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B1_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NT_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  dgemm_Col_NT_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  dgemm_Col_NT_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  dgemm_Col_NT_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NT_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NT_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NT_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  dgemm_Col_NT_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  dgemm_Col_NT_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  dgemm_Col_NT_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NT_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NT_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_NT_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  dgemm_Col_NT_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  dgemm_Col_NT_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  dgemm_Col_NT_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  dgemm_Col_NT_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  dgemm_Col_NT_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_NT_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  dgemm_Col_NT_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  dgemm_Col_NT_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  dgemm_Col_NT_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  dgemm_Col_NT_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_NT_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_NT_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  dgemm_Col_NT_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_NT_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_NT_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_NT_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_NT_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &dgemm_Col_NT_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_NT_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_NT_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_NT_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_NT_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_NT_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TN_B0_MX096_NX096_KX01_src;
          *rowKernelSource    =  dgemm_Col_TN_B0_ML096_NX096_KX01_src;
          *colKernelSource    =  dgemm_Col_TN_B0_MX096_NL096_KX01_src;
          *cornerKernelSource =  dgemm_Col_TN_B0_ML096_NL096_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TN_B0_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B0_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B0_ML096_NX096_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TN_B0_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B0_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B0_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_ML096_NX096_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B0_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B0_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B0_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B0_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TN_B0_MX096_NX096_KX08_src;
          *rowKernelSource    =  dgemm_Col_TN_B0_ML096_NX096_KX08_src;
          *colKernelSource    =  dgemm_Col_TN_B0_MX096_NL096_KX08_src;
          *cornerKernelSource =  dgemm_Col_TN_B0_ML096_NL096_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TN_B0_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B0_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B0_ML096_NX096_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TN_B0_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B0_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B0_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_ML096_NX096_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B0_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B0_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B0_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B0_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TN_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  dgemm_Col_TN_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  dgemm_Col_TN_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  dgemm_Col_TN_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TN_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TN_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TN_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  dgemm_Col_TN_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  dgemm_Col_TN_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  dgemm_Col_TN_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TN_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TN_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TN_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  dgemm_Col_TN_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  dgemm_Col_TN_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  dgemm_Col_TN_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TN_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TN_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TN_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  dgemm_Col_TN_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  dgemm_Col_TN_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  dgemm_Col_TN_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TN_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TN_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TN_B0_MX080_NX080_KX08_src;
          *rowKernelSource    =  dgemm_Col_TN_B0_ML080_NX080_KX08_src;
          *colKernelSource    =  dgemm_Col_TN_B0_MX080_NL080_KX08_src;
          *cornerKernelSource =  dgemm_Col_TN_B0_ML080_NL080_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TN_B0_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B0_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B0_ML080_NX080_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TN_B0_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B0_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B0_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_ML080_NX080_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B0_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B0_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B0_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B0_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TN_B0_MX080_NX080_KX01_src;
          *rowKernelSource    =  dgemm_Col_TN_B0_ML080_NX080_KX01_src;
          *colKernelSource    =  dgemm_Col_TN_B0_MX080_NL080_KX01_src;
          *cornerKernelSource =  dgemm_Col_TN_B0_ML080_NL080_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TN_B0_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B0_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B0_ML080_NX080_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TN_B0_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B0_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B0_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_ML080_NX080_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B0_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B0_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B0_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B0_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TN_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  dgemm_Col_TN_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  dgemm_Col_TN_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  dgemm_Col_TN_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TN_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TN_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TN_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  dgemm_Col_TN_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  dgemm_Col_TN_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  dgemm_Col_TN_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TN_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TN_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TN_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  dgemm_Col_TN_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  dgemm_Col_TN_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  dgemm_Col_TN_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TN_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TN_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TN_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  dgemm_Col_TN_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  dgemm_Col_TN_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  dgemm_Col_TN_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TN_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TN_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TN_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TN_B1_MX096_NX096_KX01_src;
          *rowKernelSource    =  dgemm_Col_TN_B1_ML096_NX096_KX01_src;
          *colKernelSource    =  dgemm_Col_TN_B1_MX096_NL096_KX01_src;
          *cornerKernelSource =  dgemm_Col_TN_B1_ML096_NL096_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TN_B1_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B1_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B1_ML096_NX096_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TN_B1_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B1_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B1_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_ML096_NX096_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B1_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B1_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B1_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B1_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TN_B1_MX096_NX096_KX08_src;
          *rowKernelSource    =  dgemm_Col_TN_B1_ML096_NX096_KX08_src;
          *colKernelSource    =  dgemm_Col_TN_B1_MX096_NL096_KX08_src;
          *cornerKernelSource =  dgemm_Col_TN_B1_ML096_NL096_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TN_B1_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B1_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B1_ML096_NX096_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TN_B1_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B1_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B1_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_ML096_NX096_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B1_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B1_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B1_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B1_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TN_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  dgemm_Col_TN_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  dgemm_Col_TN_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  dgemm_Col_TN_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TN_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TN_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TN_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  dgemm_Col_TN_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  dgemm_Col_TN_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  dgemm_Col_TN_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TN_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TN_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TN_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  dgemm_Col_TN_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  dgemm_Col_TN_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  dgemm_Col_TN_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TN_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TN_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TN_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  dgemm_Col_TN_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  dgemm_Col_TN_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  dgemm_Col_TN_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TN_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TN_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TN_B1_MX080_NX080_KX08_src;
          *rowKernelSource    =  dgemm_Col_TN_B1_ML080_NX080_KX08_src;
          *colKernelSource    =  dgemm_Col_TN_B1_MX080_NL080_KX08_src;
          *cornerKernelSource =  dgemm_Col_TN_B1_ML080_NL080_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TN_B1_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B1_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B1_ML080_NX080_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TN_B1_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B1_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B1_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_ML080_NX080_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B1_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B1_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B1_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B1_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TN_B1_MX080_NX080_KX01_src;
          *rowKernelSource    =  dgemm_Col_TN_B1_ML080_NX080_KX01_src;
          *colKernelSource    =  dgemm_Col_TN_B1_MX080_NL080_KX01_src;
          *cornerKernelSource =  dgemm_Col_TN_B1_ML080_NL080_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TN_B1_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B1_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B1_ML080_NX080_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TN_B1_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B1_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B1_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_ML080_NX080_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B1_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B1_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B1_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B1_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TN_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  dgemm_Col_TN_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  dgemm_Col_TN_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  dgemm_Col_TN_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TN_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TN_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TN_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  dgemm_Col_TN_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  dgemm_Col_TN_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  dgemm_Col_TN_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TN_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TN_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TN_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  dgemm_Col_TN_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  dgemm_Col_TN_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  dgemm_Col_TN_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TN_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TN_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TN_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  dgemm_Col_TN_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  dgemm_Col_TN_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  dgemm_Col_TN_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TN_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TN_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TN_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TN_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TN_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TN_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TN_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TN_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TN_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TN_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TN_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TN_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TN_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TN_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TT_B0_MX096_NX096_KX01_src;
          *rowKernelSource    =  dgemm_Col_TT_B0_ML096_NX096_KX01_src;
          *colKernelSource    =  dgemm_Col_TT_B0_MX096_NL096_KX01_src;
          *cornerKernelSource =  dgemm_Col_TT_B0_ML096_NL096_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TT_B0_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B0_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B0_ML096_NX096_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TT_B0_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B0_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B0_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_ML096_NX096_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B0_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B0_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B0_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B0_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TT_B0_MX096_NX096_KX08_src;
          *rowKernelSource    =  dgemm_Col_TT_B0_ML096_NX096_KX08_src;
          *colKernelSource    =  dgemm_Col_TT_B0_MX096_NL096_KX08_src;
          *cornerKernelSource =  dgemm_Col_TT_B0_ML096_NL096_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TT_B0_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B0_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B0_ML096_NX096_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TT_B0_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B0_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B0_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_ML096_NX096_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B0_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B0_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B0_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B0_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TT_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  dgemm_Col_TT_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  dgemm_Col_TT_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  dgemm_Col_TT_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TT_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TT_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TT_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  dgemm_Col_TT_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  dgemm_Col_TT_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  dgemm_Col_TT_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TT_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TT_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TT_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  dgemm_Col_TT_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  dgemm_Col_TT_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  dgemm_Col_TT_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TT_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TT_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TT_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  dgemm_Col_TT_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  dgemm_Col_TT_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  dgemm_Col_TT_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TT_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TT_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TT_B0_MX080_NX080_KX08_src;
          *rowKernelSource    =  dgemm_Col_TT_B0_ML080_NX080_KX08_src;
          *colKernelSource    =  dgemm_Col_TT_B0_MX080_NL080_KX08_src;
          *cornerKernelSource =  dgemm_Col_TT_B0_ML080_NL080_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TT_B0_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B0_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B0_ML080_NX080_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TT_B0_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B0_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B0_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_ML080_NX080_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B0_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B0_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B0_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B0_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TT_B0_MX080_NX080_KX01_src;
          *rowKernelSource    =  dgemm_Col_TT_B0_ML080_NX080_KX01_src;
          *colKernelSource    =  dgemm_Col_TT_B0_MX080_NL080_KX01_src;
          *cornerKernelSource =  dgemm_Col_TT_B0_ML080_NL080_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TT_B0_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B0_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B0_ML080_NX080_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TT_B0_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B0_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B0_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_ML080_NX080_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B0_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B0_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B0_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B0_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TT_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  dgemm_Col_TT_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  dgemm_Col_TT_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  dgemm_Col_TT_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TT_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TT_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TT_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  dgemm_Col_TT_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  dgemm_Col_TT_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  dgemm_Col_TT_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TT_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TT_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TT_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  dgemm_Col_TT_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  dgemm_Col_TT_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  dgemm_Col_TT_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TT_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TT_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TT_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  dgemm_Col_TT_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  dgemm_Col_TT_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  dgemm_Col_TT_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TT_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TT_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TT_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TT_B1_MX096_NX096_KX01_src;
          *rowKernelSource    =  dgemm_Col_TT_B1_ML096_NX096_KX01_src;
          *colKernelSource    =  dgemm_Col_TT_B1_MX096_NL096_KX01_src;
          *cornerKernelSource =  dgemm_Col_TT_B1_ML096_NL096_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TT_B1_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B1_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B1_ML096_NX096_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TT_B1_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B1_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B1_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_ML096_NX096_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B1_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B1_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B1_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B1_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TT_B1_MX096_NX096_KX08_src;
          *rowKernelSource    =  dgemm_Col_TT_B1_ML096_NX096_KX08_src;
          *colKernelSource    =  dgemm_Col_TT_B1_MX096_NL096_KX08_src;
          *cornerKernelSource =  dgemm_Col_TT_B1_ML096_NL096_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TT_B1_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B1_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B1_ML096_NX096_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TT_B1_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B1_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B1_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_ML096_NX096_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B1_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B1_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B1_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B1_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TT_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  dgemm_Col_TT_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  dgemm_Col_TT_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  dgemm_Col_TT_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TT_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TT_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TT_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  dgemm_Col_TT_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  dgemm_Col_TT_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  dgemm_Col_TT_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TT_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TT_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TT_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  dgemm_Col_TT_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  dgemm_Col_TT_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  dgemm_Col_TT_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TT_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TT_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TT_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  dgemm_Col_TT_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  dgemm_Col_TT_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  dgemm_Col_TT_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TT_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TT_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TT_B1_MX080_NX080_KX08_src;
          *rowKernelSource    =  dgemm_Col_TT_B1_ML080_NX080_KX08_src;
          *colKernelSource    =  dgemm_Col_TT_B1_MX080_NL080_KX08_src;
          *cornerKernelSource =  dgemm_Col_TT_B1_ML080_NL080_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TT_B1_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B1_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B1_ML080_NX080_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TT_B1_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B1_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B1_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_ML080_NX080_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B1_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B1_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B1_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B1_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TT_B1_MX080_NX080_KX01_src;
          *rowKernelSource    =  dgemm_Col_TT_B1_ML080_NX080_KX01_src;
          *colKernelSource    =  dgemm_Col_TT_B1_MX080_NL080_KX01_src;
          *cornerKernelSource =  dgemm_Col_TT_B1_ML080_NL080_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TT_B1_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B1_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B1_ML080_NX080_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TT_B1_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B1_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B1_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_ML080_NX080_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B1_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B1_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B1_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B1_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TT_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  dgemm_Col_TT_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  dgemm_Col_TT_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  dgemm_Col_TT_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TT_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TT_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TT_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  dgemm_Col_TT_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  dgemm_Col_TT_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  dgemm_Col_TT_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TT_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TT_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  dgemm_Col_TT_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  dgemm_Col_TT_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  dgemm_Col_TT_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  dgemm_Col_TT_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  dgemm_Col_TT_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  dgemm_Col_TT_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  dgemm_Col_TT_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  dgemm_Col_TT_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  dgemm_Col_TT_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  dgemm_Col_TT_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  dgemm_Col_TT_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  dgemm_Col_TT_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  dgemm_Col_TT_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  dgemm_Col_TT_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  dgemm_Col_TT_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  dgemm_Col_TT_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &dgemm_Col_TT_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &dgemm_Col_TT_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &dgemm_Col_TT_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &dgemm_Col_TT_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  dgemm_Col_TT_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  dgemm_Col_TT_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  dgemm_Col_TT_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  dgemm_Col_TT_B1_MX016_NX016_KX01_microTileNumCols;
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
  unsigned int macroTileNumRows,
  unsigned int macroTileNumCols,
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
  cl_kernel  **cornerClKernel,
  unsigned int *workGroupNumRows,
  unsigned int *workGroupNumCols,
  unsigned int *microTileNumRows,
  unsigned int *microTileNumCols
) {
  if (order == clblasColumnMajor) {
    if (transA == clblasNoTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NN_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  cgemm_Col_NN_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  cgemm_Col_NN_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  cgemm_Col_NN_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NN_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NN_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NN_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  cgemm_Col_NN_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  cgemm_Col_NN_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  cgemm_Col_NN_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NN_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NN_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NN_B0_MX096_NX096_KX08_src;
          *rowKernelSource    =  cgemm_Col_NN_B0_ML096_NX096_KX08_src;
          *colKernelSource    =  cgemm_Col_NN_B0_MX096_NL096_KX08_src;
          *cornerKernelSource =  cgemm_Col_NN_B0_ML096_NL096_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NN_B0_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B0_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B0_ML096_NX096_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NN_B0_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B0_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B0_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_ML096_NX096_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B0_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B0_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B0_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B0_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NN_B0_MX096_NX096_KX01_src;
          *rowKernelSource    =  cgemm_Col_NN_B0_ML096_NX096_KX01_src;
          *colKernelSource    =  cgemm_Col_NN_B0_MX096_NL096_KX01_src;
          *cornerKernelSource =  cgemm_Col_NN_B0_ML096_NL096_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NN_B0_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B0_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B0_ML096_NX096_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NN_B0_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B0_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B0_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_ML096_NX096_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B0_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B0_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B0_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B0_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NN_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  cgemm_Col_NN_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  cgemm_Col_NN_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  cgemm_Col_NN_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NN_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NN_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NN_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  cgemm_Col_NN_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  cgemm_Col_NN_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  cgemm_Col_NN_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NN_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NN_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NN_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  cgemm_Col_NN_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  cgemm_Col_NN_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  cgemm_Col_NN_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NN_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NN_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NN_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  cgemm_Col_NN_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  cgemm_Col_NN_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  cgemm_Col_NN_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NN_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NN_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NN_B0_MX080_NX080_KX08_src;
          *rowKernelSource    =  cgemm_Col_NN_B0_ML080_NX080_KX08_src;
          *colKernelSource    =  cgemm_Col_NN_B0_MX080_NL080_KX08_src;
          *cornerKernelSource =  cgemm_Col_NN_B0_ML080_NL080_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NN_B0_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B0_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B0_ML080_NX080_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NN_B0_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B0_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B0_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_ML080_NX080_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B0_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B0_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B0_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B0_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NN_B0_MX080_NX080_KX01_src;
          *rowKernelSource    =  cgemm_Col_NN_B0_ML080_NX080_KX01_src;
          *colKernelSource    =  cgemm_Col_NN_B0_MX080_NL080_KX01_src;
          *cornerKernelSource =  cgemm_Col_NN_B0_ML080_NL080_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NN_B0_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B0_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B0_ML080_NX080_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NN_B0_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B0_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B0_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_ML080_NX080_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B0_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B0_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B0_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B0_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NN_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  cgemm_Col_NN_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  cgemm_Col_NN_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  cgemm_Col_NN_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NN_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NN_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NN_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  cgemm_Col_NN_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  cgemm_Col_NN_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  cgemm_Col_NN_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NN_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NN_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NN_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NN_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  cgemm_Col_NN_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  cgemm_Col_NN_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  cgemm_Col_NN_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NN_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NN_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NN_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  cgemm_Col_NN_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  cgemm_Col_NN_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  cgemm_Col_NN_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NN_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NN_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NN_B1_MX096_NX096_KX08_src;
          *rowKernelSource    =  cgemm_Col_NN_B1_ML096_NX096_KX08_src;
          *colKernelSource    =  cgemm_Col_NN_B1_MX096_NL096_KX08_src;
          *cornerKernelSource =  cgemm_Col_NN_B1_ML096_NL096_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NN_B1_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B1_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B1_ML096_NX096_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NN_B1_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B1_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B1_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_ML096_NX096_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B1_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B1_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B1_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B1_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NN_B1_MX096_NX096_KX01_src;
          *rowKernelSource    =  cgemm_Col_NN_B1_ML096_NX096_KX01_src;
          *colKernelSource    =  cgemm_Col_NN_B1_MX096_NL096_KX01_src;
          *cornerKernelSource =  cgemm_Col_NN_B1_ML096_NL096_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NN_B1_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B1_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B1_ML096_NX096_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NN_B1_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B1_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B1_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_ML096_NX096_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B1_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B1_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B1_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B1_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NN_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  cgemm_Col_NN_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  cgemm_Col_NN_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  cgemm_Col_NN_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NN_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NN_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NN_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  cgemm_Col_NN_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  cgemm_Col_NN_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  cgemm_Col_NN_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NN_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NN_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NN_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  cgemm_Col_NN_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  cgemm_Col_NN_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  cgemm_Col_NN_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NN_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NN_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NN_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  cgemm_Col_NN_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  cgemm_Col_NN_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  cgemm_Col_NN_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NN_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NN_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NN_B1_MX080_NX080_KX08_src;
          *rowKernelSource    =  cgemm_Col_NN_B1_ML080_NX080_KX08_src;
          *colKernelSource    =  cgemm_Col_NN_B1_MX080_NL080_KX08_src;
          *cornerKernelSource =  cgemm_Col_NN_B1_ML080_NL080_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NN_B1_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B1_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B1_ML080_NX080_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NN_B1_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B1_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B1_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_ML080_NX080_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B1_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B1_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B1_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B1_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NN_B1_MX080_NX080_KX01_src;
          *rowKernelSource    =  cgemm_Col_NN_B1_ML080_NX080_KX01_src;
          *colKernelSource    =  cgemm_Col_NN_B1_MX080_NL080_KX01_src;
          *cornerKernelSource =  cgemm_Col_NN_B1_ML080_NL080_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NN_B1_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B1_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B1_ML080_NX080_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NN_B1_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B1_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B1_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_ML080_NX080_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B1_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B1_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B1_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B1_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NN_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  cgemm_Col_NN_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  cgemm_Col_NN_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  cgemm_Col_NN_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NN_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NN_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NN_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  cgemm_Col_NN_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  cgemm_Col_NN_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  cgemm_Col_NN_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NN_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NN_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NN_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NN_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NN_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NN_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NN_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NN_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NN_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NN_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NN_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NN_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NN_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NN_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasNoTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NT_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  cgemm_Col_NT_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  cgemm_Col_NT_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  cgemm_Col_NT_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NT_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NT_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NT_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  cgemm_Col_NT_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  cgemm_Col_NT_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  cgemm_Col_NT_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NT_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NT_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NT_B0_MX096_NX096_KX08_src;
          *rowKernelSource    =  cgemm_Col_NT_B0_ML096_NX096_KX08_src;
          *colKernelSource    =  cgemm_Col_NT_B0_MX096_NL096_KX08_src;
          *cornerKernelSource =  cgemm_Col_NT_B0_ML096_NL096_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NT_B0_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B0_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B0_ML096_NX096_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NT_B0_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B0_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B0_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_ML096_NX096_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B0_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B0_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B0_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B0_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NT_B0_MX096_NX096_KX01_src;
          *rowKernelSource    =  cgemm_Col_NT_B0_ML096_NX096_KX01_src;
          *colKernelSource    =  cgemm_Col_NT_B0_MX096_NL096_KX01_src;
          *cornerKernelSource =  cgemm_Col_NT_B0_ML096_NL096_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NT_B0_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B0_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B0_ML096_NX096_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NT_B0_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B0_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B0_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_ML096_NX096_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B0_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B0_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B0_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B0_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NT_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  cgemm_Col_NT_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  cgemm_Col_NT_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  cgemm_Col_NT_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NT_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NT_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NT_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  cgemm_Col_NT_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  cgemm_Col_NT_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  cgemm_Col_NT_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NT_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NT_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NT_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  cgemm_Col_NT_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  cgemm_Col_NT_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  cgemm_Col_NT_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NT_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NT_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NT_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  cgemm_Col_NT_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  cgemm_Col_NT_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  cgemm_Col_NT_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NT_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NT_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NT_B0_MX080_NX080_KX08_src;
          *rowKernelSource    =  cgemm_Col_NT_B0_ML080_NX080_KX08_src;
          *colKernelSource    =  cgemm_Col_NT_B0_MX080_NL080_KX08_src;
          *cornerKernelSource =  cgemm_Col_NT_B0_ML080_NL080_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NT_B0_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B0_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B0_ML080_NX080_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NT_B0_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B0_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B0_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_ML080_NX080_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B0_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B0_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B0_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B0_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NT_B0_MX080_NX080_KX01_src;
          *rowKernelSource    =  cgemm_Col_NT_B0_ML080_NX080_KX01_src;
          *colKernelSource    =  cgemm_Col_NT_B0_MX080_NL080_KX01_src;
          *cornerKernelSource =  cgemm_Col_NT_B0_ML080_NL080_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NT_B0_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B0_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B0_ML080_NX080_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NT_B0_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B0_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B0_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_ML080_NX080_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B0_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B0_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B0_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B0_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NT_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  cgemm_Col_NT_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  cgemm_Col_NT_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  cgemm_Col_NT_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NT_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NT_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NT_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  cgemm_Col_NT_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  cgemm_Col_NT_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  cgemm_Col_NT_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NT_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NT_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NT_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NT_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  cgemm_Col_NT_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  cgemm_Col_NT_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  cgemm_Col_NT_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NT_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NT_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NT_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  cgemm_Col_NT_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  cgemm_Col_NT_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  cgemm_Col_NT_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NT_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NT_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NT_B1_MX096_NX096_KX08_src;
          *rowKernelSource    =  cgemm_Col_NT_B1_ML096_NX096_KX08_src;
          *colKernelSource    =  cgemm_Col_NT_B1_MX096_NL096_KX08_src;
          *cornerKernelSource =  cgemm_Col_NT_B1_ML096_NL096_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NT_B1_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B1_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B1_ML096_NX096_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NT_B1_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B1_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B1_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_ML096_NX096_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B1_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B1_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B1_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B1_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NT_B1_MX096_NX096_KX01_src;
          *rowKernelSource    =  cgemm_Col_NT_B1_ML096_NX096_KX01_src;
          *colKernelSource    =  cgemm_Col_NT_B1_MX096_NL096_KX01_src;
          *cornerKernelSource =  cgemm_Col_NT_B1_ML096_NL096_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NT_B1_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B1_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B1_ML096_NX096_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NT_B1_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B1_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B1_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_ML096_NX096_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B1_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B1_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B1_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B1_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NT_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  cgemm_Col_NT_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  cgemm_Col_NT_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  cgemm_Col_NT_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NT_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NT_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NT_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  cgemm_Col_NT_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  cgemm_Col_NT_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  cgemm_Col_NT_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NT_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NT_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NT_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  cgemm_Col_NT_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  cgemm_Col_NT_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  cgemm_Col_NT_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NT_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NT_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NT_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  cgemm_Col_NT_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  cgemm_Col_NT_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  cgemm_Col_NT_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NT_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NT_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NT_B1_MX080_NX080_KX08_src;
          *rowKernelSource    =  cgemm_Col_NT_B1_ML080_NX080_KX08_src;
          *colKernelSource    =  cgemm_Col_NT_B1_MX080_NL080_KX08_src;
          *cornerKernelSource =  cgemm_Col_NT_B1_ML080_NL080_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NT_B1_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B1_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B1_ML080_NX080_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NT_B1_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B1_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B1_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_ML080_NX080_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B1_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B1_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B1_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B1_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NT_B1_MX080_NX080_KX01_src;
          *rowKernelSource    =  cgemm_Col_NT_B1_ML080_NX080_KX01_src;
          *colKernelSource    =  cgemm_Col_NT_B1_MX080_NL080_KX01_src;
          *cornerKernelSource =  cgemm_Col_NT_B1_ML080_NL080_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NT_B1_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B1_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B1_ML080_NX080_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NT_B1_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B1_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B1_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_ML080_NX080_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B1_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B1_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B1_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B1_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NT_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  cgemm_Col_NT_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  cgemm_Col_NT_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  cgemm_Col_NT_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NT_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NT_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NT_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  cgemm_Col_NT_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  cgemm_Col_NT_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  cgemm_Col_NT_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NT_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NT_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NT_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NT_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NT_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NT_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NT_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NT_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NT_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NT_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NT_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NT_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NT_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NT_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasNoTrans && transB == clblasConjTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NC_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  cgemm_Col_NC_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  cgemm_Col_NC_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  cgemm_Col_NC_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NC_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NC_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NC_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  cgemm_Col_NC_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  cgemm_Col_NC_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  cgemm_Col_NC_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NC_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NC_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NC_B0_MX096_NX096_KX08_src;
          *rowKernelSource    =  cgemm_Col_NC_B0_ML096_NX096_KX08_src;
          *colKernelSource    =  cgemm_Col_NC_B0_MX096_NL096_KX08_src;
          *cornerKernelSource =  cgemm_Col_NC_B0_ML096_NL096_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NC_B0_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B0_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B0_ML096_NX096_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NC_B0_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B0_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B0_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_ML096_NX096_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B0_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B0_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B0_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B0_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NC_B0_MX096_NX096_KX01_src;
          *rowKernelSource    =  cgemm_Col_NC_B0_ML096_NX096_KX01_src;
          *colKernelSource    =  cgemm_Col_NC_B0_MX096_NL096_KX01_src;
          *cornerKernelSource =  cgemm_Col_NC_B0_ML096_NL096_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NC_B0_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B0_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B0_ML096_NX096_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NC_B0_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B0_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B0_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_ML096_NX096_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B0_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B0_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B0_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B0_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NC_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  cgemm_Col_NC_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  cgemm_Col_NC_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  cgemm_Col_NC_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NC_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NC_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NC_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  cgemm_Col_NC_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  cgemm_Col_NC_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  cgemm_Col_NC_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NC_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NC_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NC_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  cgemm_Col_NC_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  cgemm_Col_NC_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  cgemm_Col_NC_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NC_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NC_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NC_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  cgemm_Col_NC_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  cgemm_Col_NC_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  cgemm_Col_NC_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NC_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NC_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NC_B0_MX080_NX080_KX08_src;
          *rowKernelSource    =  cgemm_Col_NC_B0_ML080_NX080_KX08_src;
          *colKernelSource    =  cgemm_Col_NC_B0_MX080_NL080_KX08_src;
          *cornerKernelSource =  cgemm_Col_NC_B0_ML080_NL080_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NC_B0_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B0_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B0_ML080_NX080_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NC_B0_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B0_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B0_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_ML080_NX080_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B0_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B0_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B0_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B0_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NC_B0_MX080_NX080_KX01_src;
          *rowKernelSource    =  cgemm_Col_NC_B0_ML080_NX080_KX01_src;
          *colKernelSource    =  cgemm_Col_NC_B0_MX080_NL080_KX01_src;
          *cornerKernelSource =  cgemm_Col_NC_B0_ML080_NL080_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NC_B0_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B0_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B0_ML080_NX080_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NC_B0_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B0_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B0_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_ML080_NX080_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B0_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B0_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B0_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B0_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NC_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  cgemm_Col_NC_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  cgemm_Col_NC_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  cgemm_Col_NC_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NC_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NC_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NC_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  cgemm_Col_NC_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  cgemm_Col_NC_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  cgemm_Col_NC_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NC_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NC_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NC_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NC_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  cgemm_Col_NC_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  cgemm_Col_NC_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  cgemm_Col_NC_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NC_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NC_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NC_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  cgemm_Col_NC_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  cgemm_Col_NC_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  cgemm_Col_NC_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NC_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NC_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NC_B1_MX096_NX096_KX08_src;
          *rowKernelSource    =  cgemm_Col_NC_B1_ML096_NX096_KX08_src;
          *colKernelSource    =  cgemm_Col_NC_B1_MX096_NL096_KX08_src;
          *cornerKernelSource =  cgemm_Col_NC_B1_ML096_NL096_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NC_B1_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B1_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B1_ML096_NX096_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NC_B1_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B1_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B1_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_ML096_NX096_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B1_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B1_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B1_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B1_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NC_B1_MX096_NX096_KX01_src;
          *rowKernelSource    =  cgemm_Col_NC_B1_ML096_NX096_KX01_src;
          *colKernelSource    =  cgemm_Col_NC_B1_MX096_NL096_KX01_src;
          *cornerKernelSource =  cgemm_Col_NC_B1_ML096_NL096_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NC_B1_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B1_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B1_ML096_NX096_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NC_B1_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B1_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B1_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_ML096_NX096_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B1_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B1_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B1_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B1_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NC_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  cgemm_Col_NC_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  cgemm_Col_NC_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  cgemm_Col_NC_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NC_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NC_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NC_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  cgemm_Col_NC_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  cgemm_Col_NC_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  cgemm_Col_NC_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NC_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NC_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NC_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  cgemm_Col_NC_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  cgemm_Col_NC_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  cgemm_Col_NC_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NC_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NC_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NC_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  cgemm_Col_NC_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  cgemm_Col_NC_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  cgemm_Col_NC_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NC_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NC_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NC_B1_MX080_NX080_KX08_src;
          *rowKernelSource    =  cgemm_Col_NC_B1_ML080_NX080_KX08_src;
          *colKernelSource    =  cgemm_Col_NC_B1_MX080_NL080_KX08_src;
          *cornerKernelSource =  cgemm_Col_NC_B1_ML080_NL080_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NC_B1_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B1_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B1_ML080_NX080_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NC_B1_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B1_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B1_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_ML080_NX080_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B1_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B1_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B1_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B1_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NC_B1_MX080_NX080_KX01_src;
          *rowKernelSource    =  cgemm_Col_NC_B1_ML080_NX080_KX01_src;
          *colKernelSource    =  cgemm_Col_NC_B1_MX080_NL080_KX01_src;
          *cornerKernelSource =  cgemm_Col_NC_B1_ML080_NL080_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NC_B1_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B1_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B1_ML080_NX080_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NC_B1_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B1_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B1_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_ML080_NX080_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B1_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B1_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B1_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B1_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_NC_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  cgemm_Col_NC_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  cgemm_Col_NC_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  cgemm_Col_NC_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  cgemm_Col_NC_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  cgemm_Col_NC_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_NC_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  cgemm_Col_NC_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  cgemm_Col_NC_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  cgemm_Col_NC_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  cgemm_Col_NC_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_NC_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_NC_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  cgemm_Col_NC_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_NC_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_NC_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_NC_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_NC_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &cgemm_Col_NC_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_NC_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_NC_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_NC_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_NC_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_NC_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TN_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  cgemm_Col_TN_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  cgemm_Col_TN_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  cgemm_Col_TN_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TN_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TN_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TN_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  cgemm_Col_TN_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  cgemm_Col_TN_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  cgemm_Col_TN_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TN_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TN_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TN_B0_MX096_NX096_KX08_src;
          *rowKernelSource    =  cgemm_Col_TN_B0_ML096_NX096_KX08_src;
          *colKernelSource    =  cgemm_Col_TN_B0_MX096_NL096_KX08_src;
          *cornerKernelSource =  cgemm_Col_TN_B0_ML096_NL096_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TN_B0_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B0_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B0_ML096_NX096_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TN_B0_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B0_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B0_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_ML096_NX096_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B0_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B0_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B0_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B0_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TN_B0_MX096_NX096_KX01_src;
          *rowKernelSource    =  cgemm_Col_TN_B0_ML096_NX096_KX01_src;
          *colKernelSource    =  cgemm_Col_TN_B0_MX096_NL096_KX01_src;
          *cornerKernelSource =  cgemm_Col_TN_B0_ML096_NL096_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TN_B0_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B0_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B0_ML096_NX096_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TN_B0_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B0_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B0_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_ML096_NX096_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B0_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B0_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B0_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B0_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TN_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  cgemm_Col_TN_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  cgemm_Col_TN_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  cgemm_Col_TN_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TN_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TN_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TN_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  cgemm_Col_TN_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  cgemm_Col_TN_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  cgemm_Col_TN_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TN_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TN_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TN_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  cgemm_Col_TN_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  cgemm_Col_TN_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  cgemm_Col_TN_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TN_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TN_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TN_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  cgemm_Col_TN_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  cgemm_Col_TN_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  cgemm_Col_TN_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TN_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TN_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TN_B0_MX080_NX080_KX08_src;
          *rowKernelSource    =  cgemm_Col_TN_B0_ML080_NX080_KX08_src;
          *colKernelSource    =  cgemm_Col_TN_B0_MX080_NL080_KX08_src;
          *cornerKernelSource =  cgemm_Col_TN_B0_ML080_NL080_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TN_B0_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B0_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B0_ML080_NX080_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TN_B0_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B0_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B0_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_ML080_NX080_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B0_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B0_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B0_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B0_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TN_B0_MX080_NX080_KX01_src;
          *rowKernelSource    =  cgemm_Col_TN_B0_ML080_NX080_KX01_src;
          *colKernelSource    =  cgemm_Col_TN_B0_MX080_NL080_KX01_src;
          *cornerKernelSource =  cgemm_Col_TN_B0_ML080_NL080_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TN_B0_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B0_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B0_ML080_NX080_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TN_B0_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B0_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B0_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_ML080_NX080_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B0_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B0_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B0_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B0_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TN_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  cgemm_Col_TN_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  cgemm_Col_TN_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  cgemm_Col_TN_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TN_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TN_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TN_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  cgemm_Col_TN_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  cgemm_Col_TN_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  cgemm_Col_TN_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TN_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TN_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TN_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TN_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  cgemm_Col_TN_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  cgemm_Col_TN_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  cgemm_Col_TN_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TN_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TN_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TN_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  cgemm_Col_TN_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  cgemm_Col_TN_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  cgemm_Col_TN_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TN_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TN_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TN_B1_MX096_NX096_KX08_src;
          *rowKernelSource    =  cgemm_Col_TN_B1_ML096_NX096_KX08_src;
          *colKernelSource    =  cgemm_Col_TN_B1_MX096_NL096_KX08_src;
          *cornerKernelSource =  cgemm_Col_TN_B1_ML096_NL096_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TN_B1_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B1_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B1_ML096_NX096_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TN_B1_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B1_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B1_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_ML096_NX096_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B1_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B1_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B1_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B1_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TN_B1_MX096_NX096_KX01_src;
          *rowKernelSource    =  cgemm_Col_TN_B1_ML096_NX096_KX01_src;
          *colKernelSource    =  cgemm_Col_TN_B1_MX096_NL096_KX01_src;
          *cornerKernelSource =  cgemm_Col_TN_B1_ML096_NL096_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TN_B1_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B1_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B1_ML096_NX096_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TN_B1_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B1_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B1_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_ML096_NX096_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B1_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B1_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B1_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B1_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TN_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  cgemm_Col_TN_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  cgemm_Col_TN_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  cgemm_Col_TN_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TN_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TN_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TN_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  cgemm_Col_TN_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  cgemm_Col_TN_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  cgemm_Col_TN_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TN_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TN_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TN_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  cgemm_Col_TN_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  cgemm_Col_TN_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  cgemm_Col_TN_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TN_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TN_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TN_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  cgemm_Col_TN_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  cgemm_Col_TN_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  cgemm_Col_TN_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TN_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TN_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TN_B1_MX080_NX080_KX08_src;
          *rowKernelSource    =  cgemm_Col_TN_B1_ML080_NX080_KX08_src;
          *colKernelSource    =  cgemm_Col_TN_B1_MX080_NL080_KX08_src;
          *cornerKernelSource =  cgemm_Col_TN_B1_ML080_NL080_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TN_B1_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B1_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B1_ML080_NX080_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TN_B1_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B1_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B1_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_ML080_NX080_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B1_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B1_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B1_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B1_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TN_B1_MX080_NX080_KX01_src;
          *rowKernelSource    =  cgemm_Col_TN_B1_ML080_NX080_KX01_src;
          *colKernelSource    =  cgemm_Col_TN_B1_MX080_NL080_KX01_src;
          *cornerKernelSource =  cgemm_Col_TN_B1_ML080_NL080_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TN_B1_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B1_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B1_ML080_NX080_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TN_B1_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B1_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B1_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_ML080_NX080_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B1_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B1_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B1_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B1_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TN_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  cgemm_Col_TN_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  cgemm_Col_TN_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  cgemm_Col_TN_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TN_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TN_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TN_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  cgemm_Col_TN_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  cgemm_Col_TN_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  cgemm_Col_TN_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TN_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TN_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TN_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TN_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TN_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TN_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TN_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TN_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TN_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TN_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TN_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TN_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TN_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TN_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TT_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  cgemm_Col_TT_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  cgemm_Col_TT_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  cgemm_Col_TT_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TT_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TT_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TT_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  cgemm_Col_TT_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  cgemm_Col_TT_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  cgemm_Col_TT_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TT_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TT_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TT_B0_MX096_NX096_KX08_src;
          *rowKernelSource    =  cgemm_Col_TT_B0_ML096_NX096_KX08_src;
          *colKernelSource    =  cgemm_Col_TT_B0_MX096_NL096_KX08_src;
          *cornerKernelSource =  cgemm_Col_TT_B0_ML096_NL096_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TT_B0_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B0_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B0_ML096_NX096_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TT_B0_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B0_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B0_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_ML096_NX096_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B0_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B0_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B0_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B0_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TT_B0_MX096_NX096_KX01_src;
          *rowKernelSource    =  cgemm_Col_TT_B0_ML096_NX096_KX01_src;
          *colKernelSource    =  cgemm_Col_TT_B0_MX096_NL096_KX01_src;
          *cornerKernelSource =  cgemm_Col_TT_B0_ML096_NL096_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TT_B0_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B0_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B0_ML096_NX096_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TT_B0_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B0_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B0_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_ML096_NX096_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B0_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B0_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B0_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B0_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TT_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  cgemm_Col_TT_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  cgemm_Col_TT_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  cgemm_Col_TT_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TT_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TT_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TT_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  cgemm_Col_TT_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  cgemm_Col_TT_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  cgemm_Col_TT_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TT_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TT_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TT_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  cgemm_Col_TT_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  cgemm_Col_TT_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  cgemm_Col_TT_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TT_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TT_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TT_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  cgemm_Col_TT_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  cgemm_Col_TT_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  cgemm_Col_TT_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TT_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TT_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TT_B0_MX080_NX080_KX08_src;
          *rowKernelSource    =  cgemm_Col_TT_B0_ML080_NX080_KX08_src;
          *colKernelSource    =  cgemm_Col_TT_B0_MX080_NL080_KX08_src;
          *cornerKernelSource =  cgemm_Col_TT_B0_ML080_NL080_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TT_B0_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B0_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B0_ML080_NX080_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TT_B0_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B0_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B0_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_ML080_NX080_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B0_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B0_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B0_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B0_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TT_B0_MX080_NX080_KX01_src;
          *rowKernelSource    =  cgemm_Col_TT_B0_ML080_NX080_KX01_src;
          *colKernelSource    =  cgemm_Col_TT_B0_MX080_NL080_KX01_src;
          *cornerKernelSource =  cgemm_Col_TT_B0_ML080_NL080_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TT_B0_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B0_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B0_ML080_NX080_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TT_B0_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B0_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B0_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_ML080_NX080_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B0_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B0_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B0_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B0_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TT_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  cgemm_Col_TT_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  cgemm_Col_TT_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  cgemm_Col_TT_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TT_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TT_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TT_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  cgemm_Col_TT_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  cgemm_Col_TT_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  cgemm_Col_TT_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TT_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TT_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TT_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TT_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  cgemm_Col_TT_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  cgemm_Col_TT_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  cgemm_Col_TT_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TT_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TT_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TT_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  cgemm_Col_TT_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  cgemm_Col_TT_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  cgemm_Col_TT_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TT_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TT_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TT_B1_MX096_NX096_KX08_src;
          *rowKernelSource    =  cgemm_Col_TT_B1_ML096_NX096_KX08_src;
          *colKernelSource    =  cgemm_Col_TT_B1_MX096_NL096_KX08_src;
          *cornerKernelSource =  cgemm_Col_TT_B1_ML096_NL096_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TT_B1_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B1_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B1_ML096_NX096_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TT_B1_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B1_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B1_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_ML096_NX096_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B1_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B1_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B1_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B1_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TT_B1_MX096_NX096_KX01_src;
          *rowKernelSource    =  cgemm_Col_TT_B1_ML096_NX096_KX01_src;
          *colKernelSource    =  cgemm_Col_TT_B1_MX096_NL096_KX01_src;
          *cornerKernelSource =  cgemm_Col_TT_B1_ML096_NL096_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TT_B1_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B1_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B1_ML096_NX096_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TT_B1_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B1_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B1_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_ML096_NX096_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B1_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B1_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B1_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B1_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TT_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  cgemm_Col_TT_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  cgemm_Col_TT_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  cgemm_Col_TT_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TT_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TT_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TT_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  cgemm_Col_TT_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  cgemm_Col_TT_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  cgemm_Col_TT_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TT_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TT_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TT_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  cgemm_Col_TT_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  cgemm_Col_TT_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  cgemm_Col_TT_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TT_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TT_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TT_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  cgemm_Col_TT_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  cgemm_Col_TT_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  cgemm_Col_TT_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TT_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TT_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TT_B1_MX080_NX080_KX08_src;
          *rowKernelSource    =  cgemm_Col_TT_B1_ML080_NX080_KX08_src;
          *colKernelSource    =  cgemm_Col_TT_B1_MX080_NL080_KX08_src;
          *cornerKernelSource =  cgemm_Col_TT_B1_ML080_NL080_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TT_B1_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B1_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B1_ML080_NX080_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TT_B1_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B1_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B1_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_ML080_NX080_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B1_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B1_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B1_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B1_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TT_B1_MX080_NX080_KX01_src;
          *rowKernelSource    =  cgemm_Col_TT_B1_ML080_NX080_KX01_src;
          *colKernelSource    =  cgemm_Col_TT_B1_MX080_NL080_KX01_src;
          *cornerKernelSource =  cgemm_Col_TT_B1_ML080_NL080_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TT_B1_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B1_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B1_ML080_NX080_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TT_B1_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B1_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B1_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_ML080_NX080_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B1_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B1_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B1_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B1_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TT_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  cgemm_Col_TT_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  cgemm_Col_TT_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  cgemm_Col_TT_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TT_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TT_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TT_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  cgemm_Col_TT_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  cgemm_Col_TT_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  cgemm_Col_TT_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TT_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TT_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TT_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TT_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TT_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TT_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TT_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TT_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TT_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TT_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TT_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TT_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TT_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TT_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasConjTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TC_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  cgemm_Col_TC_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  cgemm_Col_TC_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  cgemm_Col_TC_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TC_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TC_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TC_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  cgemm_Col_TC_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  cgemm_Col_TC_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  cgemm_Col_TC_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TC_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TC_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TC_B0_MX096_NX096_KX08_src;
          *rowKernelSource    =  cgemm_Col_TC_B0_ML096_NX096_KX08_src;
          *colKernelSource    =  cgemm_Col_TC_B0_MX096_NL096_KX08_src;
          *cornerKernelSource =  cgemm_Col_TC_B0_ML096_NL096_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TC_B0_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B0_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B0_ML096_NX096_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TC_B0_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B0_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B0_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_ML096_NX096_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B0_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B0_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B0_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B0_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TC_B0_MX096_NX096_KX01_src;
          *rowKernelSource    =  cgemm_Col_TC_B0_ML096_NX096_KX01_src;
          *colKernelSource    =  cgemm_Col_TC_B0_MX096_NL096_KX01_src;
          *cornerKernelSource =  cgemm_Col_TC_B0_ML096_NL096_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TC_B0_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B0_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B0_ML096_NX096_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TC_B0_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B0_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B0_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_ML096_NX096_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B0_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B0_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B0_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B0_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TC_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  cgemm_Col_TC_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  cgemm_Col_TC_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  cgemm_Col_TC_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TC_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TC_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TC_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  cgemm_Col_TC_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  cgemm_Col_TC_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  cgemm_Col_TC_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TC_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TC_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TC_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  cgemm_Col_TC_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  cgemm_Col_TC_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  cgemm_Col_TC_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TC_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TC_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TC_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  cgemm_Col_TC_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  cgemm_Col_TC_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  cgemm_Col_TC_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TC_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TC_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TC_B0_MX080_NX080_KX08_src;
          *rowKernelSource    =  cgemm_Col_TC_B0_ML080_NX080_KX08_src;
          *colKernelSource    =  cgemm_Col_TC_B0_MX080_NL080_KX08_src;
          *cornerKernelSource =  cgemm_Col_TC_B0_ML080_NL080_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TC_B0_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B0_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B0_ML080_NX080_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TC_B0_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B0_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B0_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_ML080_NX080_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B0_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B0_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B0_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B0_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TC_B0_MX080_NX080_KX01_src;
          *rowKernelSource    =  cgemm_Col_TC_B0_ML080_NX080_KX01_src;
          *colKernelSource    =  cgemm_Col_TC_B0_MX080_NL080_KX01_src;
          *cornerKernelSource =  cgemm_Col_TC_B0_ML080_NL080_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TC_B0_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B0_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B0_ML080_NX080_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TC_B0_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B0_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B0_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_ML080_NX080_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B0_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B0_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B0_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B0_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TC_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  cgemm_Col_TC_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  cgemm_Col_TC_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  cgemm_Col_TC_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TC_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TC_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TC_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  cgemm_Col_TC_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  cgemm_Col_TC_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  cgemm_Col_TC_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TC_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TC_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TC_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TC_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  cgemm_Col_TC_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  cgemm_Col_TC_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  cgemm_Col_TC_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TC_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TC_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TC_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  cgemm_Col_TC_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  cgemm_Col_TC_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  cgemm_Col_TC_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TC_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TC_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TC_B1_MX096_NX096_KX08_src;
          *rowKernelSource    =  cgemm_Col_TC_B1_ML096_NX096_KX08_src;
          *colKernelSource    =  cgemm_Col_TC_B1_MX096_NL096_KX08_src;
          *cornerKernelSource =  cgemm_Col_TC_B1_ML096_NL096_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TC_B1_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B1_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B1_ML096_NX096_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TC_B1_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B1_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B1_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_ML096_NX096_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B1_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B1_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B1_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B1_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TC_B1_MX096_NX096_KX01_src;
          *rowKernelSource    =  cgemm_Col_TC_B1_ML096_NX096_KX01_src;
          *colKernelSource    =  cgemm_Col_TC_B1_MX096_NL096_KX01_src;
          *cornerKernelSource =  cgemm_Col_TC_B1_ML096_NL096_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TC_B1_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B1_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B1_ML096_NX096_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TC_B1_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B1_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B1_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_ML096_NX096_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B1_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B1_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B1_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B1_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TC_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  cgemm_Col_TC_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  cgemm_Col_TC_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  cgemm_Col_TC_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TC_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TC_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TC_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  cgemm_Col_TC_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  cgemm_Col_TC_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  cgemm_Col_TC_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TC_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TC_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TC_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  cgemm_Col_TC_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  cgemm_Col_TC_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  cgemm_Col_TC_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TC_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TC_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TC_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  cgemm_Col_TC_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  cgemm_Col_TC_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  cgemm_Col_TC_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TC_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TC_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TC_B1_MX080_NX080_KX08_src;
          *rowKernelSource    =  cgemm_Col_TC_B1_ML080_NX080_KX08_src;
          *colKernelSource    =  cgemm_Col_TC_B1_MX080_NL080_KX08_src;
          *cornerKernelSource =  cgemm_Col_TC_B1_ML080_NL080_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TC_B1_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B1_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B1_ML080_NX080_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TC_B1_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B1_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B1_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_ML080_NX080_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B1_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B1_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B1_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B1_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TC_B1_MX080_NX080_KX01_src;
          *rowKernelSource    =  cgemm_Col_TC_B1_ML080_NX080_KX01_src;
          *colKernelSource    =  cgemm_Col_TC_B1_MX080_NL080_KX01_src;
          *cornerKernelSource =  cgemm_Col_TC_B1_ML080_NL080_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TC_B1_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B1_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B1_ML080_NX080_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TC_B1_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B1_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B1_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_ML080_NX080_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B1_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B1_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B1_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B1_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_TC_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  cgemm_Col_TC_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  cgemm_Col_TC_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  cgemm_Col_TC_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  cgemm_Col_TC_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  cgemm_Col_TC_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_TC_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  cgemm_Col_TC_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  cgemm_Col_TC_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  cgemm_Col_TC_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  cgemm_Col_TC_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_TC_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_TC_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  cgemm_Col_TC_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_TC_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_TC_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_TC_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_TC_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &cgemm_Col_TC_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_TC_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_TC_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_TC_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_TC_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_TC_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasConjTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CN_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  cgemm_Col_CN_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  cgemm_Col_CN_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  cgemm_Col_CN_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CN_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CN_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CN_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  cgemm_Col_CN_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  cgemm_Col_CN_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  cgemm_Col_CN_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CN_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CN_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CN_B0_MX096_NX096_KX08_src;
          *rowKernelSource    =  cgemm_Col_CN_B0_ML096_NX096_KX08_src;
          *colKernelSource    =  cgemm_Col_CN_B0_MX096_NL096_KX08_src;
          *cornerKernelSource =  cgemm_Col_CN_B0_ML096_NL096_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CN_B0_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B0_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B0_ML096_NX096_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CN_B0_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B0_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B0_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_ML096_NX096_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B0_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B0_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B0_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B0_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CN_B0_MX096_NX096_KX01_src;
          *rowKernelSource    =  cgemm_Col_CN_B0_ML096_NX096_KX01_src;
          *colKernelSource    =  cgemm_Col_CN_B0_MX096_NL096_KX01_src;
          *cornerKernelSource =  cgemm_Col_CN_B0_ML096_NL096_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CN_B0_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B0_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B0_ML096_NX096_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CN_B0_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B0_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B0_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_ML096_NX096_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B0_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B0_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B0_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B0_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CN_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  cgemm_Col_CN_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  cgemm_Col_CN_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  cgemm_Col_CN_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CN_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CN_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CN_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  cgemm_Col_CN_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  cgemm_Col_CN_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  cgemm_Col_CN_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CN_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CN_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CN_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  cgemm_Col_CN_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  cgemm_Col_CN_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  cgemm_Col_CN_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CN_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CN_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CN_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  cgemm_Col_CN_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  cgemm_Col_CN_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  cgemm_Col_CN_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CN_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CN_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CN_B0_MX080_NX080_KX08_src;
          *rowKernelSource    =  cgemm_Col_CN_B0_ML080_NX080_KX08_src;
          *colKernelSource    =  cgemm_Col_CN_B0_MX080_NL080_KX08_src;
          *cornerKernelSource =  cgemm_Col_CN_B0_ML080_NL080_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CN_B0_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B0_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B0_ML080_NX080_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CN_B0_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B0_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B0_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_ML080_NX080_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B0_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B0_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B0_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B0_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CN_B0_MX080_NX080_KX01_src;
          *rowKernelSource    =  cgemm_Col_CN_B0_ML080_NX080_KX01_src;
          *colKernelSource    =  cgemm_Col_CN_B0_MX080_NL080_KX01_src;
          *cornerKernelSource =  cgemm_Col_CN_B0_ML080_NL080_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CN_B0_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B0_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B0_ML080_NX080_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CN_B0_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B0_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B0_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_ML080_NX080_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B0_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B0_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B0_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B0_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CN_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  cgemm_Col_CN_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  cgemm_Col_CN_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  cgemm_Col_CN_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CN_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CN_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CN_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  cgemm_Col_CN_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  cgemm_Col_CN_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  cgemm_Col_CN_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CN_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CN_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CN_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CN_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  cgemm_Col_CN_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  cgemm_Col_CN_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  cgemm_Col_CN_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CN_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CN_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CN_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  cgemm_Col_CN_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  cgemm_Col_CN_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  cgemm_Col_CN_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CN_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CN_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CN_B1_MX096_NX096_KX08_src;
          *rowKernelSource    =  cgemm_Col_CN_B1_ML096_NX096_KX08_src;
          *colKernelSource    =  cgemm_Col_CN_B1_MX096_NL096_KX08_src;
          *cornerKernelSource =  cgemm_Col_CN_B1_ML096_NL096_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CN_B1_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B1_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B1_ML096_NX096_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CN_B1_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B1_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B1_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_ML096_NX096_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B1_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B1_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B1_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B1_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CN_B1_MX096_NX096_KX01_src;
          *rowKernelSource    =  cgemm_Col_CN_B1_ML096_NX096_KX01_src;
          *colKernelSource    =  cgemm_Col_CN_B1_MX096_NL096_KX01_src;
          *cornerKernelSource =  cgemm_Col_CN_B1_ML096_NL096_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CN_B1_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B1_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B1_ML096_NX096_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CN_B1_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B1_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B1_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_ML096_NX096_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B1_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B1_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B1_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B1_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CN_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  cgemm_Col_CN_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  cgemm_Col_CN_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  cgemm_Col_CN_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CN_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CN_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CN_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  cgemm_Col_CN_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  cgemm_Col_CN_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  cgemm_Col_CN_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CN_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CN_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CN_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  cgemm_Col_CN_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  cgemm_Col_CN_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  cgemm_Col_CN_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CN_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CN_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CN_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  cgemm_Col_CN_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  cgemm_Col_CN_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  cgemm_Col_CN_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CN_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CN_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CN_B1_MX080_NX080_KX08_src;
          *rowKernelSource    =  cgemm_Col_CN_B1_ML080_NX080_KX08_src;
          *colKernelSource    =  cgemm_Col_CN_B1_MX080_NL080_KX08_src;
          *cornerKernelSource =  cgemm_Col_CN_B1_ML080_NL080_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CN_B1_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B1_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B1_ML080_NX080_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CN_B1_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B1_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B1_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_ML080_NX080_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B1_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B1_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B1_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B1_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CN_B1_MX080_NX080_KX01_src;
          *rowKernelSource    =  cgemm_Col_CN_B1_ML080_NX080_KX01_src;
          *colKernelSource    =  cgemm_Col_CN_B1_MX080_NL080_KX01_src;
          *cornerKernelSource =  cgemm_Col_CN_B1_ML080_NL080_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CN_B1_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B1_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B1_ML080_NX080_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CN_B1_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B1_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B1_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_ML080_NX080_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B1_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B1_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B1_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B1_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CN_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  cgemm_Col_CN_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  cgemm_Col_CN_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  cgemm_Col_CN_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CN_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CN_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CN_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  cgemm_Col_CN_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  cgemm_Col_CN_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  cgemm_Col_CN_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CN_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CN_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CN_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CN_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CN_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CN_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CN_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CN_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CN_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CN_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CN_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CN_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CN_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CN_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasConjTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CT_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  cgemm_Col_CT_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  cgemm_Col_CT_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  cgemm_Col_CT_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CT_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CT_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CT_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  cgemm_Col_CT_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  cgemm_Col_CT_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  cgemm_Col_CT_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CT_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CT_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CT_B0_MX096_NX096_KX08_src;
          *rowKernelSource    =  cgemm_Col_CT_B0_ML096_NX096_KX08_src;
          *colKernelSource    =  cgemm_Col_CT_B0_MX096_NL096_KX08_src;
          *cornerKernelSource =  cgemm_Col_CT_B0_ML096_NL096_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CT_B0_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B0_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B0_ML096_NX096_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CT_B0_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B0_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B0_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_ML096_NX096_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B0_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B0_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B0_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B0_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CT_B0_MX096_NX096_KX01_src;
          *rowKernelSource    =  cgemm_Col_CT_B0_ML096_NX096_KX01_src;
          *colKernelSource    =  cgemm_Col_CT_B0_MX096_NL096_KX01_src;
          *cornerKernelSource =  cgemm_Col_CT_B0_ML096_NL096_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CT_B0_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B0_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B0_ML096_NX096_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CT_B0_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B0_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B0_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_ML096_NX096_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B0_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B0_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B0_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B0_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CT_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  cgemm_Col_CT_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  cgemm_Col_CT_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  cgemm_Col_CT_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CT_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CT_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CT_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  cgemm_Col_CT_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  cgemm_Col_CT_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  cgemm_Col_CT_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CT_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CT_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CT_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  cgemm_Col_CT_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  cgemm_Col_CT_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  cgemm_Col_CT_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CT_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CT_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CT_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  cgemm_Col_CT_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  cgemm_Col_CT_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  cgemm_Col_CT_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CT_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CT_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CT_B0_MX080_NX080_KX08_src;
          *rowKernelSource    =  cgemm_Col_CT_B0_ML080_NX080_KX08_src;
          *colKernelSource    =  cgemm_Col_CT_B0_MX080_NL080_KX08_src;
          *cornerKernelSource =  cgemm_Col_CT_B0_ML080_NL080_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CT_B0_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B0_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B0_ML080_NX080_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CT_B0_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B0_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B0_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_ML080_NX080_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B0_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B0_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B0_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B0_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CT_B0_MX080_NX080_KX01_src;
          *rowKernelSource    =  cgemm_Col_CT_B0_ML080_NX080_KX01_src;
          *colKernelSource    =  cgemm_Col_CT_B0_MX080_NL080_KX01_src;
          *cornerKernelSource =  cgemm_Col_CT_B0_ML080_NL080_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CT_B0_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B0_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B0_ML080_NX080_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CT_B0_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B0_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B0_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_ML080_NX080_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B0_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B0_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B0_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B0_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CT_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  cgemm_Col_CT_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  cgemm_Col_CT_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  cgemm_Col_CT_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CT_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CT_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CT_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  cgemm_Col_CT_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  cgemm_Col_CT_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  cgemm_Col_CT_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CT_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CT_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CT_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CT_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  cgemm_Col_CT_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  cgemm_Col_CT_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  cgemm_Col_CT_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CT_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CT_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CT_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  cgemm_Col_CT_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  cgemm_Col_CT_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  cgemm_Col_CT_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CT_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CT_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CT_B1_MX096_NX096_KX08_src;
          *rowKernelSource    =  cgemm_Col_CT_B1_ML096_NX096_KX08_src;
          *colKernelSource    =  cgemm_Col_CT_B1_MX096_NL096_KX08_src;
          *cornerKernelSource =  cgemm_Col_CT_B1_ML096_NL096_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CT_B1_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B1_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B1_ML096_NX096_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CT_B1_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B1_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B1_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_ML096_NX096_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B1_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B1_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B1_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B1_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CT_B1_MX096_NX096_KX01_src;
          *rowKernelSource    =  cgemm_Col_CT_B1_ML096_NX096_KX01_src;
          *colKernelSource    =  cgemm_Col_CT_B1_MX096_NL096_KX01_src;
          *cornerKernelSource =  cgemm_Col_CT_B1_ML096_NL096_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CT_B1_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B1_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B1_ML096_NX096_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CT_B1_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B1_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B1_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_ML096_NX096_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B1_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B1_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B1_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B1_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CT_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  cgemm_Col_CT_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  cgemm_Col_CT_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  cgemm_Col_CT_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CT_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CT_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CT_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  cgemm_Col_CT_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  cgemm_Col_CT_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  cgemm_Col_CT_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CT_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CT_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CT_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  cgemm_Col_CT_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  cgemm_Col_CT_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  cgemm_Col_CT_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CT_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CT_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CT_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  cgemm_Col_CT_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  cgemm_Col_CT_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  cgemm_Col_CT_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CT_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CT_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CT_B1_MX080_NX080_KX08_src;
          *rowKernelSource    =  cgemm_Col_CT_B1_ML080_NX080_KX08_src;
          *colKernelSource    =  cgemm_Col_CT_B1_MX080_NL080_KX08_src;
          *cornerKernelSource =  cgemm_Col_CT_B1_ML080_NL080_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CT_B1_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B1_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B1_ML080_NX080_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CT_B1_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B1_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B1_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_ML080_NX080_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B1_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B1_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B1_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B1_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CT_B1_MX080_NX080_KX01_src;
          *rowKernelSource    =  cgemm_Col_CT_B1_ML080_NX080_KX01_src;
          *colKernelSource    =  cgemm_Col_CT_B1_MX080_NL080_KX01_src;
          *cornerKernelSource =  cgemm_Col_CT_B1_ML080_NL080_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CT_B1_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B1_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B1_ML080_NX080_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CT_B1_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B1_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B1_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_ML080_NX080_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B1_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B1_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B1_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B1_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CT_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  cgemm_Col_CT_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  cgemm_Col_CT_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  cgemm_Col_CT_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CT_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CT_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CT_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  cgemm_Col_CT_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  cgemm_Col_CT_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  cgemm_Col_CT_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CT_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CT_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CT_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CT_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CT_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CT_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CT_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CT_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CT_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CT_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CT_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CT_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CT_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CT_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasConjTrans && transB == clblasConjTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CC_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  cgemm_Col_CC_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  cgemm_Col_CC_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  cgemm_Col_CC_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CC_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CC_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CC_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  cgemm_Col_CC_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  cgemm_Col_CC_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  cgemm_Col_CC_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CC_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CC_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CC_B0_MX096_NX096_KX08_src;
          *rowKernelSource    =  cgemm_Col_CC_B0_ML096_NX096_KX08_src;
          *colKernelSource    =  cgemm_Col_CC_B0_MX096_NL096_KX08_src;
          *cornerKernelSource =  cgemm_Col_CC_B0_ML096_NL096_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CC_B0_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B0_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B0_ML096_NX096_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CC_B0_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B0_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B0_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_ML096_NX096_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B0_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B0_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B0_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B0_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CC_B0_MX096_NX096_KX01_src;
          *rowKernelSource    =  cgemm_Col_CC_B0_ML096_NX096_KX01_src;
          *colKernelSource    =  cgemm_Col_CC_B0_MX096_NL096_KX01_src;
          *cornerKernelSource =  cgemm_Col_CC_B0_ML096_NL096_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CC_B0_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B0_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B0_ML096_NX096_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CC_B0_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B0_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B0_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_ML096_NX096_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B0_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B0_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B0_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B0_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CC_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  cgemm_Col_CC_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  cgemm_Col_CC_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  cgemm_Col_CC_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CC_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CC_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CC_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  cgemm_Col_CC_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  cgemm_Col_CC_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  cgemm_Col_CC_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CC_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CC_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CC_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  cgemm_Col_CC_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  cgemm_Col_CC_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  cgemm_Col_CC_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CC_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CC_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CC_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  cgemm_Col_CC_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  cgemm_Col_CC_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  cgemm_Col_CC_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CC_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CC_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CC_B0_MX080_NX080_KX08_src;
          *rowKernelSource    =  cgemm_Col_CC_B0_ML080_NX080_KX08_src;
          *colKernelSource    =  cgemm_Col_CC_B0_MX080_NL080_KX08_src;
          *cornerKernelSource =  cgemm_Col_CC_B0_ML080_NL080_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CC_B0_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B0_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B0_ML080_NX080_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CC_B0_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B0_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B0_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_ML080_NX080_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B0_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B0_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B0_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B0_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CC_B0_MX080_NX080_KX01_src;
          *rowKernelSource    =  cgemm_Col_CC_B0_ML080_NX080_KX01_src;
          *colKernelSource    =  cgemm_Col_CC_B0_MX080_NL080_KX01_src;
          *cornerKernelSource =  cgemm_Col_CC_B0_ML080_NL080_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CC_B0_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B0_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B0_ML080_NX080_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CC_B0_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B0_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B0_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_ML080_NX080_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B0_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B0_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B0_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B0_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CC_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  cgemm_Col_CC_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  cgemm_Col_CC_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  cgemm_Col_CC_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CC_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CC_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CC_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  cgemm_Col_CC_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  cgemm_Col_CC_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  cgemm_Col_CC_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CC_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CC_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CC_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CC_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  cgemm_Col_CC_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  cgemm_Col_CC_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  cgemm_Col_CC_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CC_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CC_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CC_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  cgemm_Col_CC_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  cgemm_Col_CC_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  cgemm_Col_CC_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CC_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CC_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CC_B1_MX096_NX096_KX08_src;
          *rowKernelSource    =  cgemm_Col_CC_B1_ML096_NX096_KX08_src;
          *colKernelSource    =  cgemm_Col_CC_B1_MX096_NL096_KX08_src;
          *cornerKernelSource =  cgemm_Col_CC_B1_ML096_NL096_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CC_B1_MX096_NX096_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B1_MX096_NX096_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B1_ML096_NX096_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CC_B1_MX096_NL096_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B1_ML096_NL096_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B1_MX096_NX096_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_MX096_NX096_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_ML096_NX096_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_MX096_NL096_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_ML096_NL096_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B1_MX096_NX096_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B1_MX096_NX096_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B1_MX096_NX096_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B1_MX096_NX096_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 96 && macroTileNumCols == 96 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CC_B1_MX096_NX096_KX01_src;
          *rowKernelSource    =  cgemm_Col_CC_B1_ML096_NX096_KX01_src;
          *colKernelSource    =  cgemm_Col_CC_B1_MX096_NL096_KX01_src;
          *cornerKernelSource =  cgemm_Col_CC_B1_ML096_NL096_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CC_B1_MX096_NX096_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B1_MX096_NX096_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B1_ML096_NX096_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CC_B1_MX096_NL096_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B1_ML096_NL096_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B1_MX096_NX096_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_MX096_NX096_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_ML096_NX096_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_MX096_NL096_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_ML096_NL096_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B1_MX096_NX096_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B1_MX096_NX096_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B1_MX096_NX096_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B1_MX096_NX096_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CC_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  cgemm_Col_CC_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  cgemm_Col_CC_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  cgemm_Col_CC_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CC_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CC_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CC_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  cgemm_Col_CC_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  cgemm_Col_CC_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  cgemm_Col_CC_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CC_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CC_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CC_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  cgemm_Col_CC_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  cgemm_Col_CC_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  cgemm_Col_CC_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CC_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CC_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CC_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  cgemm_Col_CC_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  cgemm_Col_CC_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  cgemm_Col_CC_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CC_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CC_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CC_B1_MX080_NX080_KX08_src;
          *rowKernelSource    =  cgemm_Col_CC_B1_ML080_NX080_KX08_src;
          *colKernelSource    =  cgemm_Col_CC_B1_MX080_NL080_KX08_src;
          *cornerKernelSource =  cgemm_Col_CC_B1_ML080_NL080_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CC_B1_MX080_NX080_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B1_MX080_NX080_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B1_ML080_NX080_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CC_B1_MX080_NL080_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B1_ML080_NL080_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B1_MX080_NX080_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_MX080_NX080_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_ML080_NX080_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_MX080_NL080_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_ML080_NL080_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B1_MX080_NX080_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B1_MX080_NX080_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B1_MX080_NX080_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B1_MX080_NX080_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 80 && macroTileNumCols == 80 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CC_B1_MX080_NX080_KX01_src;
          *rowKernelSource    =  cgemm_Col_CC_B1_ML080_NX080_KX01_src;
          *colKernelSource    =  cgemm_Col_CC_B1_MX080_NL080_KX01_src;
          *cornerKernelSource =  cgemm_Col_CC_B1_ML080_NL080_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CC_B1_MX080_NX080_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B1_MX080_NX080_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B1_ML080_NX080_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CC_B1_MX080_NL080_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B1_ML080_NL080_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B1_MX080_NX080_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_MX080_NX080_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_ML080_NX080_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_MX080_NL080_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_ML080_NL080_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B1_MX080_NX080_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B1_MX080_NX080_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B1_MX080_NX080_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B1_MX080_NX080_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  cgemm_Col_CC_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  cgemm_Col_CC_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  cgemm_Col_CC_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  cgemm_Col_CC_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  cgemm_Col_CC_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  cgemm_Col_CC_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  cgemm_Col_CC_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  cgemm_Col_CC_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  cgemm_Col_CC_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  cgemm_Col_CC_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  cgemm_Col_CC_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  cgemm_Col_CC_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  cgemm_Col_CC_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  cgemm_Col_CC_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  cgemm_Col_CC_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  cgemm_Col_CC_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &cgemm_Col_CC_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &cgemm_Col_CC_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &cgemm_Col_CC_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &cgemm_Col_CC_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  cgemm_Col_CC_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  cgemm_Col_CC_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  cgemm_Col_CC_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  cgemm_Col_CC_B1_MX016_NX016_KX01_microTileNumCols;
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
  unsigned int macroTileNumRows,
  unsigned int macroTileNumCols,
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
  cl_kernel  **cornerClKernel,
  unsigned int *workGroupNumRows,
  unsigned int *workGroupNumCols,
  unsigned int *microTileNumRows,
  unsigned int *microTileNumCols
) {
  if (order == clblasColumnMajor) {
    if (transA == clblasNoTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NN_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  zgemm_Col_NN_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  zgemm_Col_NN_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  zgemm_Col_NN_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NN_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NN_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NN_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NN_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NN_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NN_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NN_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NN_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NN_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NN_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NN_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NN_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  zgemm_Col_NN_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  zgemm_Col_NN_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  zgemm_Col_NN_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NN_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NN_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NN_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NN_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NN_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NN_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NN_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NN_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NN_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NN_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NN_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NN_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  zgemm_Col_NN_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  zgemm_Col_NN_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  zgemm_Col_NN_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NN_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NN_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NN_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NN_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NN_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NN_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NN_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NN_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NN_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NN_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NN_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NN_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  zgemm_Col_NN_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  zgemm_Col_NN_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  zgemm_Col_NN_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NN_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NN_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NN_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NN_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NN_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NN_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NN_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NN_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NN_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NN_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NN_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NN_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  zgemm_Col_NN_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  zgemm_Col_NN_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  zgemm_Col_NN_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NN_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NN_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NN_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NN_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NN_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NN_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NN_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NN_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NN_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NN_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NN_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NN_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  zgemm_Col_NN_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  zgemm_Col_NN_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  zgemm_Col_NN_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NN_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NN_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NN_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NN_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NN_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NN_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NN_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NN_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NN_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NN_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NN_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NN_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  zgemm_Col_NN_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  zgemm_Col_NN_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  zgemm_Col_NN_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NN_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NN_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NN_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NN_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NN_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NN_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NN_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NN_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NN_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NN_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NN_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NN_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  zgemm_Col_NN_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  zgemm_Col_NN_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  zgemm_Col_NN_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NN_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NN_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NN_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NN_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NN_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NN_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NN_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NN_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NN_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NN_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NN_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NN_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  zgemm_Col_NN_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  zgemm_Col_NN_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  zgemm_Col_NN_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NN_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NN_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NN_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NN_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NN_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NN_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NN_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NN_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NN_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NN_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NN_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NN_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  zgemm_Col_NN_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  zgemm_Col_NN_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  zgemm_Col_NN_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NN_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NN_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NN_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NN_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NN_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NN_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NN_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NN_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NN_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NN_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NN_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NN_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  zgemm_Col_NN_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  zgemm_Col_NN_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  zgemm_Col_NN_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NN_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NN_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NN_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NN_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NN_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NN_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NN_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NN_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NN_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NN_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NN_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NN_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  zgemm_Col_NN_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  zgemm_Col_NN_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  zgemm_Col_NN_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NN_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NN_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NN_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NN_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NN_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NN_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NN_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NN_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NN_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NN_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NN_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NN_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  zgemm_Col_NN_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  zgemm_Col_NN_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  zgemm_Col_NN_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NN_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NN_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NN_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NN_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NN_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NN_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NN_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NN_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NN_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NN_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NN_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NN_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  zgemm_Col_NN_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  zgemm_Col_NN_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  zgemm_Col_NN_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NN_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NN_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NN_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NN_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NN_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NN_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NN_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NN_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NN_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NN_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NN_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NN_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  zgemm_Col_NN_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  zgemm_Col_NN_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  zgemm_Col_NN_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NN_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NN_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NN_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NN_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NN_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NN_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NN_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NN_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NN_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NN_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NN_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NN_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  zgemm_Col_NN_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  zgemm_Col_NN_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  zgemm_Col_NN_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NN_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NN_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NN_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NN_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NN_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NN_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NN_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NN_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NN_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NN_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NN_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NN_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NN_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NN_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasNoTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NT_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  zgemm_Col_NT_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  zgemm_Col_NT_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  zgemm_Col_NT_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NT_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NT_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NT_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NT_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NT_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NT_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NT_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NT_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NT_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NT_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NT_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NT_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  zgemm_Col_NT_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  zgemm_Col_NT_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  zgemm_Col_NT_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NT_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NT_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NT_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NT_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NT_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NT_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NT_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NT_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NT_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NT_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NT_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NT_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  zgemm_Col_NT_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  zgemm_Col_NT_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  zgemm_Col_NT_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NT_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NT_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NT_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NT_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NT_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NT_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NT_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NT_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NT_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NT_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NT_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NT_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  zgemm_Col_NT_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  zgemm_Col_NT_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  zgemm_Col_NT_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NT_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NT_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NT_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NT_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NT_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NT_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NT_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NT_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NT_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NT_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NT_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NT_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  zgemm_Col_NT_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  zgemm_Col_NT_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  zgemm_Col_NT_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NT_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NT_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NT_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NT_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NT_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NT_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NT_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NT_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NT_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NT_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NT_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NT_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  zgemm_Col_NT_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  zgemm_Col_NT_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  zgemm_Col_NT_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NT_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NT_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NT_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NT_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NT_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NT_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NT_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NT_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NT_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NT_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NT_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NT_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  zgemm_Col_NT_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  zgemm_Col_NT_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  zgemm_Col_NT_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NT_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NT_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NT_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NT_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NT_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NT_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NT_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NT_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NT_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NT_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NT_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NT_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  zgemm_Col_NT_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  zgemm_Col_NT_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  zgemm_Col_NT_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NT_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NT_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NT_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NT_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NT_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NT_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NT_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NT_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NT_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NT_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NT_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NT_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  zgemm_Col_NT_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  zgemm_Col_NT_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  zgemm_Col_NT_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NT_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NT_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NT_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NT_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NT_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NT_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NT_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NT_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NT_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NT_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NT_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NT_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  zgemm_Col_NT_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  zgemm_Col_NT_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  zgemm_Col_NT_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NT_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NT_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NT_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NT_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NT_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NT_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NT_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NT_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NT_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NT_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NT_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NT_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  zgemm_Col_NT_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  zgemm_Col_NT_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  zgemm_Col_NT_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NT_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NT_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NT_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NT_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NT_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NT_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NT_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NT_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NT_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NT_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NT_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NT_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  zgemm_Col_NT_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  zgemm_Col_NT_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  zgemm_Col_NT_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NT_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NT_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NT_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NT_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NT_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NT_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NT_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NT_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NT_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NT_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NT_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NT_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  zgemm_Col_NT_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  zgemm_Col_NT_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  zgemm_Col_NT_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NT_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NT_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NT_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NT_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NT_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NT_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NT_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NT_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NT_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NT_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NT_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NT_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  zgemm_Col_NT_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  zgemm_Col_NT_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  zgemm_Col_NT_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NT_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NT_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NT_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NT_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NT_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NT_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NT_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NT_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NT_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NT_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NT_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NT_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  zgemm_Col_NT_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  zgemm_Col_NT_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  zgemm_Col_NT_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NT_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NT_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NT_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NT_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NT_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NT_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NT_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NT_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NT_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NT_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NT_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NT_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  zgemm_Col_NT_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  zgemm_Col_NT_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  zgemm_Col_NT_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NT_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NT_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NT_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NT_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NT_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NT_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NT_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NT_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NT_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NT_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NT_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NT_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NT_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NT_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasNoTrans && transB == clblasConjTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NC_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  zgemm_Col_NC_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  zgemm_Col_NC_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  zgemm_Col_NC_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NC_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NC_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NC_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NC_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NC_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NC_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NC_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NC_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NC_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NC_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NC_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NC_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  zgemm_Col_NC_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  zgemm_Col_NC_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  zgemm_Col_NC_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NC_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NC_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NC_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NC_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NC_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NC_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NC_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NC_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NC_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NC_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NC_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NC_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  zgemm_Col_NC_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  zgemm_Col_NC_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  zgemm_Col_NC_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NC_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NC_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NC_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NC_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NC_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NC_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NC_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NC_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NC_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NC_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NC_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NC_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  zgemm_Col_NC_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  zgemm_Col_NC_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  zgemm_Col_NC_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NC_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NC_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NC_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NC_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NC_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NC_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NC_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NC_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NC_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NC_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NC_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NC_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  zgemm_Col_NC_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  zgemm_Col_NC_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  zgemm_Col_NC_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NC_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NC_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NC_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NC_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NC_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NC_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NC_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NC_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NC_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NC_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NC_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NC_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  zgemm_Col_NC_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  zgemm_Col_NC_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  zgemm_Col_NC_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NC_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NC_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NC_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NC_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NC_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NC_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NC_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NC_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NC_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NC_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NC_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NC_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  zgemm_Col_NC_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  zgemm_Col_NC_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  zgemm_Col_NC_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NC_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NC_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NC_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NC_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NC_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NC_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NC_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NC_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NC_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NC_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NC_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NC_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  zgemm_Col_NC_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  zgemm_Col_NC_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  zgemm_Col_NC_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NC_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NC_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NC_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NC_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NC_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NC_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NC_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NC_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NC_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NC_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NC_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NC_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  zgemm_Col_NC_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  zgemm_Col_NC_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  zgemm_Col_NC_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NC_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NC_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NC_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NC_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NC_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NC_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NC_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NC_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NC_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NC_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NC_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NC_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  zgemm_Col_NC_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  zgemm_Col_NC_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  zgemm_Col_NC_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NC_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NC_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NC_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NC_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NC_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NC_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NC_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NC_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NC_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NC_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NC_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NC_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  zgemm_Col_NC_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  zgemm_Col_NC_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  zgemm_Col_NC_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NC_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NC_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NC_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NC_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NC_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NC_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NC_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NC_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NC_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NC_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NC_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NC_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  zgemm_Col_NC_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  zgemm_Col_NC_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  zgemm_Col_NC_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NC_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NC_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NC_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NC_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NC_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NC_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NC_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NC_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NC_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NC_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NC_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NC_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  zgemm_Col_NC_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  zgemm_Col_NC_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  zgemm_Col_NC_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NC_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NC_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NC_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NC_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NC_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NC_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NC_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NC_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NC_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NC_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NC_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_NC_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  zgemm_Col_NC_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  zgemm_Col_NC_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  zgemm_Col_NC_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  zgemm_Col_NC_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NC_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_NC_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  zgemm_Col_NC_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_NC_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_NC_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &zgemm_Col_NC_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_NC_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NC_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NC_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NC_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NC_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  zgemm_Col_NC_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  zgemm_Col_NC_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  zgemm_Col_NC_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NC_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NC_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NC_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NC_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NC_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NC_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NC_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NC_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NC_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NC_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NC_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_NC_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  zgemm_Col_NC_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  zgemm_Col_NC_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  zgemm_Col_NC_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  zgemm_Col_NC_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_NC_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_NC_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  zgemm_Col_NC_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_NC_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_NC_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_NC_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_NC_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &zgemm_Col_NC_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_NC_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_NC_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_NC_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_NC_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_NC_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TN_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  zgemm_Col_TN_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  zgemm_Col_TN_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  zgemm_Col_TN_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TN_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TN_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TN_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TN_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TN_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TN_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TN_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TN_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TN_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TN_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TN_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TN_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  zgemm_Col_TN_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  zgemm_Col_TN_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  zgemm_Col_TN_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TN_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TN_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TN_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TN_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TN_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TN_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TN_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TN_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TN_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TN_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TN_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TN_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  zgemm_Col_TN_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  zgemm_Col_TN_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  zgemm_Col_TN_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TN_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TN_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TN_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TN_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TN_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TN_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TN_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TN_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TN_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TN_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TN_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TN_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  zgemm_Col_TN_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  zgemm_Col_TN_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  zgemm_Col_TN_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TN_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TN_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TN_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TN_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TN_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TN_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TN_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TN_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TN_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TN_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TN_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TN_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  zgemm_Col_TN_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  zgemm_Col_TN_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  zgemm_Col_TN_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TN_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TN_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TN_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TN_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TN_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TN_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TN_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TN_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TN_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TN_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TN_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TN_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  zgemm_Col_TN_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  zgemm_Col_TN_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  zgemm_Col_TN_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TN_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TN_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TN_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TN_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TN_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TN_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TN_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TN_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TN_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TN_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TN_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TN_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  zgemm_Col_TN_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  zgemm_Col_TN_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  zgemm_Col_TN_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TN_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TN_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TN_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TN_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TN_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TN_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TN_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TN_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TN_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TN_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TN_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TN_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  zgemm_Col_TN_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  zgemm_Col_TN_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  zgemm_Col_TN_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TN_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TN_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TN_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TN_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TN_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TN_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TN_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TN_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TN_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TN_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TN_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TN_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  zgemm_Col_TN_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  zgemm_Col_TN_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  zgemm_Col_TN_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TN_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TN_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TN_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TN_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TN_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TN_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TN_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TN_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TN_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TN_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TN_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TN_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  zgemm_Col_TN_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  zgemm_Col_TN_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  zgemm_Col_TN_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TN_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TN_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TN_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TN_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TN_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TN_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TN_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TN_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TN_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TN_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TN_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TN_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  zgemm_Col_TN_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  zgemm_Col_TN_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  zgemm_Col_TN_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TN_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TN_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TN_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TN_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TN_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TN_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TN_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TN_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TN_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TN_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TN_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TN_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  zgemm_Col_TN_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  zgemm_Col_TN_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  zgemm_Col_TN_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TN_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TN_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TN_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TN_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TN_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TN_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TN_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TN_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TN_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TN_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TN_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TN_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  zgemm_Col_TN_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  zgemm_Col_TN_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  zgemm_Col_TN_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TN_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TN_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TN_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TN_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TN_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TN_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TN_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TN_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TN_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TN_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TN_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TN_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  zgemm_Col_TN_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  zgemm_Col_TN_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  zgemm_Col_TN_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TN_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TN_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TN_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TN_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TN_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TN_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TN_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TN_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TN_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TN_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TN_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TN_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  zgemm_Col_TN_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  zgemm_Col_TN_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  zgemm_Col_TN_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TN_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TN_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TN_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TN_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TN_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TN_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TN_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TN_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TN_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TN_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TN_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TN_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  zgemm_Col_TN_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  zgemm_Col_TN_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  zgemm_Col_TN_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TN_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TN_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TN_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TN_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TN_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TN_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TN_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TN_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TN_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TN_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TN_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TN_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TN_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TN_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TT_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  zgemm_Col_TT_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  zgemm_Col_TT_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  zgemm_Col_TT_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TT_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TT_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TT_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TT_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TT_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TT_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TT_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TT_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TT_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TT_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TT_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TT_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  zgemm_Col_TT_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  zgemm_Col_TT_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  zgemm_Col_TT_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TT_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TT_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TT_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TT_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TT_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TT_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TT_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TT_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TT_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TT_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TT_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TT_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  zgemm_Col_TT_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  zgemm_Col_TT_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  zgemm_Col_TT_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TT_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TT_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TT_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TT_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TT_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TT_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TT_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TT_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TT_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TT_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TT_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TT_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  zgemm_Col_TT_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  zgemm_Col_TT_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  zgemm_Col_TT_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TT_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TT_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TT_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TT_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TT_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TT_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TT_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TT_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TT_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TT_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TT_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TT_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  zgemm_Col_TT_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  zgemm_Col_TT_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  zgemm_Col_TT_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TT_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TT_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TT_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TT_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TT_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TT_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TT_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TT_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TT_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TT_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TT_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TT_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  zgemm_Col_TT_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  zgemm_Col_TT_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  zgemm_Col_TT_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TT_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TT_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TT_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TT_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TT_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TT_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TT_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TT_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TT_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TT_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TT_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TT_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  zgemm_Col_TT_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  zgemm_Col_TT_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  zgemm_Col_TT_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TT_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TT_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TT_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TT_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TT_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TT_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TT_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TT_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TT_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TT_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TT_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TT_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  zgemm_Col_TT_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  zgemm_Col_TT_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  zgemm_Col_TT_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TT_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TT_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TT_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TT_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TT_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TT_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TT_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TT_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TT_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TT_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TT_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TT_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  zgemm_Col_TT_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  zgemm_Col_TT_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  zgemm_Col_TT_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TT_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TT_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TT_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TT_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TT_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TT_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TT_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TT_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TT_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TT_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TT_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TT_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  zgemm_Col_TT_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  zgemm_Col_TT_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  zgemm_Col_TT_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TT_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TT_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TT_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TT_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TT_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TT_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TT_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TT_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TT_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TT_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TT_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TT_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  zgemm_Col_TT_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  zgemm_Col_TT_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  zgemm_Col_TT_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TT_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TT_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TT_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TT_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TT_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TT_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TT_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TT_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TT_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TT_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TT_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TT_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  zgemm_Col_TT_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  zgemm_Col_TT_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  zgemm_Col_TT_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TT_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TT_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TT_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TT_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TT_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TT_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TT_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TT_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TT_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TT_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TT_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TT_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  zgemm_Col_TT_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  zgemm_Col_TT_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  zgemm_Col_TT_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TT_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TT_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TT_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TT_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TT_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TT_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TT_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TT_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TT_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TT_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TT_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TT_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  zgemm_Col_TT_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  zgemm_Col_TT_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  zgemm_Col_TT_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TT_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TT_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TT_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TT_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TT_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TT_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TT_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TT_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TT_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TT_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TT_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TT_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  zgemm_Col_TT_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  zgemm_Col_TT_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  zgemm_Col_TT_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TT_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TT_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TT_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TT_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TT_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TT_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TT_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TT_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TT_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TT_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TT_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TT_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  zgemm_Col_TT_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  zgemm_Col_TT_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  zgemm_Col_TT_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TT_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TT_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TT_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TT_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TT_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TT_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TT_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TT_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TT_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TT_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TT_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TT_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TT_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TT_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasTrans && transB == clblasConjTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TC_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  zgemm_Col_TC_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  zgemm_Col_TC_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  zgemm_Col_TC_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TC_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TC_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TC_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TC_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TC_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TC_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TC_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TC_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TC_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TC_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TC_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TC_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  zgemm_Col_TC_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  zgemm_Col_TC_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  zgemm_Col_TC_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TC_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TC_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TC_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TC_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TC_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TC_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TC_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TC_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TC_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TC_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TC_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TC_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  zgemm_Col_TC_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  zgemm_Col_TC_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  zgemm_Col_TC_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TC_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TC_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TC_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TC_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TC_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TC_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TC_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TC_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TC_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TC_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TC_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TC_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  zgemm_Col_TC_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  zgemm_Col_TC_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  zgemm_Col_TC_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TC_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TC_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TC_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TC_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TC_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TC_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TC_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TC_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TC_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TC_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TC_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TC_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  zgemm_Col_TC_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  zgemm_Col_TC_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  zgemm_Col_TC_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TC_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TC_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TC_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TC_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TC_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TC_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TC_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TC_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TC_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TC_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TC_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TC_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  zgemm_Col_TC_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  zgemm_Col_TC_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  zgemm_Col_TC_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TC_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TC_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TC_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TC_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TC_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TC_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TC_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TC_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TC_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TC_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TC_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TC_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  zgemm_Col_TC_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  zgemm_Col_TC_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  zgemm_Col_TC_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TC_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TC_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TC_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TC_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TC_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TC_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TC_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TC_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TC_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TC_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TC_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TC_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  zgemm_Col_TC_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  zgemm_Col_TC_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  zgemm_Col_TC_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TC_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TC_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TC_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TC_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TC_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TC_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TC_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TC_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TC_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TC_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TC_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TC_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  zgemm_Col_TC_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  zgemm_Col_TC_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  zgemm_Col_TC_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TC_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TC_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TC_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TC_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TC_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TC_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TC_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TC_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TC_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TC_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TC_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TC_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  zgemm_Col_TC_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  zgemm_Col_TC_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  zgemm_Col_TC_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TC_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TC_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TC_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TC_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TC_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TC_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TC_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TC_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TC_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TC_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TC_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TC_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  zgemm_Col_TC_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  zgemm_Col_TC_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  zgemm_Col_TC_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TC_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TC_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TC_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TC_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TC_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TC_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TC_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TC_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TC_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TC_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TC_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TC_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  zgemm_Col_TC_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  zgemm_Col_TC_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  zgemm_Col_TC_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TC_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TC_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TC_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TC_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TC_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TC_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TC_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TC_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TC_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TC_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TC_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TC_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  zgemm_Col_TC_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  zgemm_Col_TC_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  zgemm_Col_TC_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TC_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TC_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TC_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TC_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TC_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TC_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TC_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TC_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TC_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TC_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TC_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_TC_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  zgemm_Col_TC_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  zgemm_Col_TC_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  zgemm_Col_TC_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  zgemm_Col_TC_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TC_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_TC_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  zgemm_Col_TC_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_TC_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_TC_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &zgemm_Col_TC_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_TC_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TC_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TC_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TC_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TC_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  zgemm_Col_TC_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  zgemm_Col_TC_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  zgemm_Col_TC_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TC_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TC_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TC_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TC_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TC_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TC_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TC_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TC_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TC_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TC_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TC_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_TC_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  zgemm_Col_TC_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  zgemm_Col_TC_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  zgemm_Col_TC_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  zgemm_Col_TC_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_TC_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_TC_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  zgemm_Col_TC_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_TC_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_TC_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_TC_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_TC_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &zgemm_Col_TC_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_TC_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_TC_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_TC_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_TC_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_TC_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasConjTrans && transB == clblasNoTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CN_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  zgemm_Col_CN_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  zgemm_Col_CN_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  zgemm_Col_CN_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CN_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CN_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CN_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CN_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CN_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CN_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CN_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CN_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CN_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CN_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CN_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CN_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  zgemm_Col_CN_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  zgemm_Col_CN_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  zgemm_Col_CN_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CN_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CN_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CN_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CN_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CN_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CN_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CN_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CN_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CN_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CN_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CN_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CN_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  zgemm_Col_CN_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  zgemm_Col_CN_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  zgemm_Col_CN_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CN_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CN_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CN_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CN_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CN_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CN_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CN_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CN_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CN_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CN_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CN_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CN_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  zgemm_Col_CN_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  zgemm_Col_CN_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  zgemm_Col_CN_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CN_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CN_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CN_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CN_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CN_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CN_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CN_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CN_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CN_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CN_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CN_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CN_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  zgemm_Col_CN_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  zgemm_Col_CN_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  zgemm_Col_CN_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CN_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CN_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CN_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CN_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CN_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CN_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CN_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CN_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CN_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CN_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CN_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CN_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  zgemm_Col_CN_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  zgemm_Col_CN_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  zgemm_Col_CN_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CN_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CN_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CN_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CN_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CN_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CN_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CN_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CN_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CN_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CN_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CN_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CN_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  zgemm_Col_CN_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  zgemm_Col_CN_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  zgemm_Col_CN_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CN_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CN_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CN_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CN_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CN_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CN_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CN_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CN_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CN_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CN_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CN_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CN_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  zgemm_Col_CN_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  zgemm_Col_CN_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  zgemm_Col_CN_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CN_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CN_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CN_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CN_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CN_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CN_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CN_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CN_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CN_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CN_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CN_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CN_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  zgemm_Col_CN_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  zgemm_Col_CN_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  zgemm_Col_CN_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CN_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CN_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CN_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CN_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CN_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CN_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CN_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CN_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CN_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CN_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CN_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CN_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  zgemm_Col_CN_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  zgemm_Col_CN_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  zgemm_Col_CN_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CN_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CN_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CN_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CN_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CN_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CN_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CN_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CN_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CN_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CN_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CN_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CN_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  zgemm_Col_CN_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  zgemm_Col_CN_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  zgemm_Col_CN_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CN_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CN_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CN_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CN_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CN_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CN_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CN_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CN_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CN_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CN_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CN_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CN_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  zgemm_Col_CN_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  zgemm_Col_CN_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  zgemm_Col_CN_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CN_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CN_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CN_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CN_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CN_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CN_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CN_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CN_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CN_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CN_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CN_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CN_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  zgemm_Col_CN_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  zgemm_Col_CN_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  zgemm_Col_CN_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CN_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CN_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CN_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CN_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CN_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CN_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CN_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CN_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CN_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CN_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CN_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CN_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  zgemm_Col_CN_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  zgemm_Col_CN_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  zgemm_Col_CN_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CN_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CN_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CN_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CN_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CN_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CN_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CN_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CN_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CN_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CN_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CN_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CN_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  zgemm_Col_CN_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  zgemm_Col_CN_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  zgemm_Col_CN_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CN_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CN_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CN_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CN_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CN_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CN_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CN_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CN_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CN_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CN_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CN_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CN_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  zgemm_Col_CN_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  zgemm_Col_CN_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  zgemm_Col_CN_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CN_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CN_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CN_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CN_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CN_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CN_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CN_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CN_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CN_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CN_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CN_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CN_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CN_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CN_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasConjTrans && transB == clblasTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CT_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  zgemm_Col_CT_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  zgemm_Col_CT_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  zgemm_Col_CT_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CT_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CT_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CT_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CT_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CT_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CT_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CT_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CT_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CT_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CT_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CT_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CT_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  zgemm_Col_CT_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  zgemm_Col_CT_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  zgemm_Col_CT_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CT_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CT_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CT_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CT_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CT_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CT_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CT_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CT_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CT_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CT_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CT_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CT_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  zgemm_Col_CT_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  zgemm_Col_CT_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  zgemm_Col_CT_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CT_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CT_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CT_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CT_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CT_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CT_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CT_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CT_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CT_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CT_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CT_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CT_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  zgemm_Col_CT_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  zgemm_Col_CT_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  zgemm_Col_CT_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CT_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CT_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CT_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CT_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CT_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CT_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CT_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CT_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CT_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CT_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CT_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CT_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  zgemm_Col_CT_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  zgemm_Col_CT_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  zgemm_Col_CT_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CT_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CT_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CT_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CT_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CT_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CT_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CT_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CT_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CT_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CT_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CT_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CT_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  zgemm_Col_CT_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  zgemm_Col_CT_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  zgemm_Col_CT_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CT_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CT_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CT_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CT_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CT_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CT_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CT_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CT_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CT_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CT_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CT_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CT_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  zgemm_Col_CT_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  zgemm_Col_CT_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  zgemm_Col_CT_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CT_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CT_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CT_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CT_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CT_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CT_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CT_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CT_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CT_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CT_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CT_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CT_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  zgemm_Col_CT_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  zgemm_Col_CT_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  zgemm_Col_CT_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CT_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CT_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CT_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CT_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CT_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CT_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CT_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CT_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CT_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CT_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CT_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CT_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  zgemm_Col_CT_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  zgemm_Col_CT_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  zgemm_Col_CT_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CT_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CT_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CT_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CT_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CT_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CT_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CT_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CT_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CT_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CT_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CT_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CT_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  zgemm_Col_CT_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  zgemm_Col_CT_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  zgemm_Col_CT_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CT_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CT_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CT_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CT_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CT_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CT_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CT_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CT_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CT_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CT_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CT_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CT_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  zgemm_Col_CT_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  zgemm_Col_CT_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  zgemm_Col_CT_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CT_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CT_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CT_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CT_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CT_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CT_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CT_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CT_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CT_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CT_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CT_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CT_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  zgemm_Col_CT_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  zgemm_Col_CT_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  zgemm_Col_CT_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CT_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CT_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CT_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CT_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CT_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CT_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CT_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CT_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CT_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CT_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CT_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CT_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  zgemm_Col_CT_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  zgemm_Col_CT_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  zgemm_Col_CT_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CT_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CT_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CT_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CT_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CT_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CT_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CT_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CT_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CT_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CT_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CT_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CT_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  zgemm_Col_CT_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  zgemm_Col_CT_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  zgemm_Col_CT_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CT_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CT_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CT_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CT_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CT_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CT_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CT_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CT_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CT_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CT_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CT_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CT_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  zgemm_Col_CT_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  zgemm_Col_CT_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  zgemm_Col_CT_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CT_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CT_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CT_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CT_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CT_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CT_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CT_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CT_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CT_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CT_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CT_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CT_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  zgemm_Col_CT_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  zgemm_Col_CT_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  zgemm_Col_CT_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CT_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CT_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CT_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CT_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CT_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CT_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CT_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CT_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CT_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CT_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CT_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CT_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CT_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CT_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
      }
    } else if (transA == clblasConjTrans && transB == clblasConjTrans) {
      if ( !betaNonZero ) {
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CC_B0_MX048_NX048_KX08_src;
          *rowKernelSource    =  zgemm_Col_CC_B0_ML048_NX048_KX08_src;
          *colKernelSource    =  zgemm_Col_CC_B0_MX048_NL048_KX08_src;
          *cornerKernelSource =  zgemm_Col_CC_B0_ML048_NL048_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CC_B0_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CC_B0_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CC_B0_ML048_NX048_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CC_B0_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CC_B0_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CC_B0_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B0_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B0_ML048_NX048_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CC_B0_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B0_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CC_B0_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CC_B0_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CC_B0_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CC_B0_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CC_B0_MX048_NX048_KX01_src;
          *rowKernelSource    =  zgemm_Col_CC_B0_ML048_NX048_KX01_src;
          *colKernelSource    =  zgemm_Col_CC_B0_MX048_NL048_KX01_src;
          *cornerKernelSource =  zgemm_Col_CC_B0_ML048_NL048_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CC_B0_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CC_B0_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CC_B0_ML048_NX048_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CC_B0_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CC_B0_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CC_B0_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B0_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B0_ML048_NX048_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CC_B0_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B0_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CC_B0_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CC_B0_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CC_B0_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CC_B0_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CC_B0_MX064_NX064_KX08_src;
          *rowKernelSource    =  zgemm_Col_CC_B0_ML064_NX064_KX08_src;
          *colKernelSource    =  zgemm_Col_CC_B0_MX064_NL064_KX08_src;
          *cornerKernelSource =  zgemm_Col_CC_B0_ML064_NL064_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CC_B0_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CC_B0_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CC_B0_ML064_NX064_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CC_B0_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CC_B0_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CC_B0_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B0_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B0_ML064_NX064_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CC_B0_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B0_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CC_B0_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CC_B0_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CC_B0_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CC_B0_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CC_B0_MX064_NX064_KX01_src;
          *rowKernelSource    =  zgemm_Col_CC_B0_ML064_NX064_KX01_src;
          *colKernelSource    =  zgemm_Col_CC_B0_MX064_NL064_KX01_src;
          *cornerKernelSource =  zgemm_Col_CC_B0_ML064_NL064_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CC_B0_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CC_B0_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CC_B0_ML064_NX064_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CC_B0_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CC_B0_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CC_B0_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B0_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B0_ML064_NX064_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CC_B0_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B0_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CC_B0_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CC_B0_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CC_B0_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CC_B0_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CC_B0_MX016_NX016_KX08_src;
          *rowKernelSource    =  zgemm_Col_CC_B0_ML016_NX016_KX08_src;
          *colKernelSource    =  zgemm_Col_CC_B0_MX016_NL016_KX08_src;
          *cornerKernelSource =  zgemm_Col_CC_B0_ML016_NL016_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CC_B0_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CC_B0_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CC_B0_ML016_NX016_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CC_B0_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CC_B0_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CC_B0_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B0_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B0_ML016_NX016_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CC_B0_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B0_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CC_B0_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CC_B0_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CC_B0_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CC_B0_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CC_B0_MX032_NX032_KX08_src;
          *rowKernelSource    =  zgemm_Col_CC_B0_ML032_NX032_KX08_src;
          *colKernelSource    =  zgemm_Col_CC_B0_MX032_NL032_KX08_src;
          *cornerKernelSource =  zgemm_Col_CC_B0_ML032_NL032_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CC_B0_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CC_B0_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CC_B0_ML032_NX032_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CC_B0_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CC_B0_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CC_B0_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B0_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B0_ML032_NX032_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CC_B0_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B0_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CC_B0_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CC_B0_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CC_B0_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CC_B0_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CC_B0_MX016_NX016_KX01_src;
          *rowKernelSource    =  zgemm_Col_CC_B0_ML016_NX016_KX01_src;
          *colKernelSource    =  zgemm_Col_CC_B0_MX016_NL016_KX01_src;
          *cornerKernelSource =  zgemm_Col_CC_B0_ML016_NL016_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CC_B0_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CC_B0_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CC_B0_ML016_NX016_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CC_B0_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CC_B0_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CC_B0_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B0_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B0_ML016_NX016_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CC_B0_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B0_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CC_B0_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CC_B0_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CC_B0_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CC_B0_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CC_B0_MX032_NX032_KX01_src;
          *rowKernelSource    =  zgemm_Col_CC_B0_ML032_NX032_KX01_src;
          *colKernelSource    =  zgemm_Col_CC_B0_MX032_NL032_KX01_src;
          *cornerKernelSource =  zgemm_Col_CC_B0_ML032_NL032_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CC_B0_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CC_B0_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CC_B0_ML032_NX032_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CC_B0_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CC_B0_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CC_B0_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B0_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B0_ML032_NX032_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CC_B0_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B0_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CC_B0_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CC_B0_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CC_B0_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CC_B0_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
      } else if ( betaNonZero ) {
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CC_B1_MX048_NX048_KX08_src;
          *rowKernelSource    =  zgemm_Col_CC_B1_ML048_NX048_KX08_src;
          *colKernelSource    =  zgemm_Col_CC_B1_MX048_NL048_KX08_src;
          *cornerKernelSource =  zgemm_Col_CC_B1_ML048_NL048_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CC_B1_MX048_NX048_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CC_B1_MX048_NX048_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CC_B1_ML048_NX048_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CC_B1_MX048_NL048_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CC_B1_ML048_NL048_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CC_B1_MX048_NX048_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B1_MX048_NX048_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B1_ML048_NX048_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CC_B1_MX048_NL048_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B1_ML048_NL048_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CC_B1_MX048_NX048_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CC_B1_MX048_NX048_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CC_B1_MX048_NX048_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CC_B1_MX048_NX048_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 48 && macroTileNumCols == 48 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CC_B1_MX048_NX048_KX01_src;
          *rowKernelSource    =  zgemm_Col_CC_B1_ML048_NX048_KX01_src;
          *colKernelSource    =  zgemm_Col_CC_B1_MX048_NL048_KX01_src;
          *cornerKernelSource =  zgemm_Col_CC_B1_ML048_NL048_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CC_B1_MX048_NX048_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CC_B1_MX048_NX048_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CC_B1_ML048_NX048_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CC_B1_MX048_NL048_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CC_B1_ML048_NL048_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CC_B1_MX048_NX048_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B1_MX048_NX048_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B1_ML048_NX048_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CC_B1_MX048_NL048_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B1_ML048_NL048_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CC_B1_MX048_NX048_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CC_B1_MX048_NX048_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CC_B1_MX048_NX048_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CC_B1_MX048_NX048_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CC_B1_MX064_NX064_KX08_src;
          *rowKernelSource    =  zgemm_Col_CC_B1_ML064_NX064_KX08_src;
          *colKernelSource    =  zgemm_Col_CC_B1_MX064_NL064_KX08_src;
          *cornerKernelSource =  zgemm_Col_CC_B1_ML064_NL064_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CC_B1_MX064_NX064_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CC_B1_MX064_NX064_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CC_B1_ML064_NX064_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CC_B1_MX064_NL064_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CC_B1_ML064_NL064_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CC_B1_MX064_NX064_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B1_MX064_NX064_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B1_ML064_NX064_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CC_B1_MX064_NL064_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B1_ML064_NL064_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CC_B1_MX064_NX064_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CC_B1_MX064_NX064_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CC_B1_MX064_NX064_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CC_B1_MX064_NX064_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 64 && macroTileNumCols == 64 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CC_B1_MX064_NX064_KX01_src;
          *rowKernelSource    =  zgemm_Col_CC_B1_ML064_NX064_KX01_src;
          *colKernelSource    =  zgemm_Col_CC_B1_MX064_NL064_KX01_src;
          *cornerKernelSource =  zgemm_Col_CC_B1_ML064_NL064_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CC_B1_MX064_NX064_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CC_B1_MX064_NX064_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CC_B1_ML064_NX064_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CC_B1_MX064_NL064_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CC_B1_ML064_NL064_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CC_B1_MX064_NX064_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B1_MX064_NX064_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B1_ML064_NX064_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CC_B1_MX064_NL064_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B1_ML064_NL064_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CC_B1_MX064_NX064_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CC_B1_MX064_NX064_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CC_B1_MX064_NX064_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CC_B1_MX064_NX064_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CC_B1_MX016_NX016_KX08_src;
          *rowKernelSource    =  zgemm_Col_CC_B1_ML016_NX016_KX08_src;
          *colKernelSource    =  zgemm_Col_CC_B1_MX016_NL016_KX08_src;
          *cornerKernelSource =  zgemm_Col_CC_B1_ML016_NL016_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CC_B1_MX016_NX016_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CC_B1_MX016_NX016_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CC_B1_ML016_NX016_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CC_B1_MX016_NL016_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CC_B1_ML016_NL016_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CC_B1_MX016_NX016_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B1_MX016_NX016_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B1_ML016_NX016_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CC_B1_MX016_NL016_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B1_ML016_NL016_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CC_B1_MX016_NX016_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CC_B1_MX016_NX016_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CC_B1_MX016_NX016_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CC_B1_MX016_NX016_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 8) {
          *tileKernelSource   =  zgemm_Col_CC_B1_MX032_NX032_KX08_src;
          *rowKernelSource    =  zgemm_Col_CC_B1_ML032_NX032_KX08_src;
          *colKernelSource    =  zgemm_Col_CC_B1_MX032_NL032_KX08_src;
          *cornerKernelSource =  zgemm_Col_CC_B1_ML032_NL032_KX08_src;
          *sourceBuildOptions =  zgemm_Col_CC_B1_MX032_NX032_KX08_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CC_B1_MX032_NX032_KX08_bin;
          *rowKernelBinary    =  zgemm_Col_CC_B1_ML032_NX032_KX08_bin;
          *colKernelBinary    =  zgemm_Col_CC_B1_MX032_NL032_KX08_bin;
          *cornerKernelBinary =  zgemm_Col_CC_B1_ML032_NL032_KX08_bin;
          *binaryBuildOptions =  zgemm_Col_CC_B1_MX032_NX032_KX08_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B1_MX032_NX032_KX08_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B1_ML032_NX032_KX08_clKernel;
          *colClKernel        = &zgemm_Col_CC_B1_MX032_NL032_KX08_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B1_ML032_NL032_KX08_clKernel;
          *workGroupNumRows   =  zgemm_Col_CC_B1_MX032_NX032_KX08_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CC_B1_MX032_NX032_KX08_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CC_B1_MX032_NX032_KX08_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CC_B1_MX032_NX032_KX08_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 16 && macroTileNumCols == 16 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CC_B1_MX016_NX016_KX01_src;
          *rowKernelSource    =  zgemm_Col_CC_B1_ML016_NX016_KX01_src;
          *colKernelSource    =  zgemm_Col_CC_B1_MX016_NL016_KX01_src;
          *cornerKernelSource =  zgemm_Col_CC_B1_ML016_NL016_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CC_B1_MX016_NX016_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CC_B1_MX016_NX016_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CC_B1_ML016_NX016_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CC_B1_MX016_NL016_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CC_B1_ML016_NL016_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CC_B1_MX016_NX016_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B1_MX016_NX016_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B1_ML016_NX016_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CC_B1_MX016_NL016_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B1_ML016_NL016_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CC_B1_MX016_NX016_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CC_B1_MX016_NX016_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CC_B1_MX016_NX016_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CC_B1_MX016_NX016_KX01_microTileNumCols;
          return true;
        }
        if ( macroTileNumRows == 32 && macroTileNumCols == 32 && unroll == 1) {
          *tileKernelSource   =  zgemm_Col_CC_B1_MX032_NX032_KX01_src;
          *rowKernelSource    =  zgemm_Col_CC_B1_ML032_NX032_KX01_src;
          *colKernelSource    =  zgemm_Col_CC_B1_MX032_NL032_KX01_src;
          *cornerKernelSource =  zgemm_Col_CC_B1_ML032_NL032_KX01_src;
          *sourceBuildOptions =  zgemm_Col_CC_B1_MX032_NX032_KX01_srcBuildOptions;
          *tileKernelBinary   =  zgemm_Col_CC_B1_MX032_NX032_KX01_bin;
          *rowKernelBinary    =  zgemm_Col_CC_B1_ML032_NX032_KX01_bin;
          *colKernelBinary    =  zgemm_Col_CC_B1_MX032_NL032_KX01_bin;
          *cornerKernelBinary =  zgemm_Col_CC_B1_ML032_NL032_KX01_bin;
          *binaryBuildOptions =  zgemm_Col_CC_B1_MX032_NX032_KX01_binBuildOptions;
          *tileClKernel       = &zgemm_Col_CC_B1_MX032_NX032_KX01_clKernel;
          *rowClKernel        = &zgemm_Col_CC_B1_ML032_NX032_KX01_clKernel;
          *colClKernel        = &zgemm_Col_CC_B1_MX032_NL032_KX01_clKernel;
          *cornerClKernel     = &zgemm_Col_CC_B1_ML032_NL032_KX01_clKernel;
          *workGroupNumRows   =  zgemm_Col_CC_B1_MX032_NX032_KX01_workGroupNumRows;
          *workGroupNumCols   =  zgemm_Col_CC_B1_MX032_NX032_KX01_workGroupNumCols;
          *microTileNumRows   =  zgemm_Col_CC_B1_MX032_NX032_KX01_microTileNumRows;
          *microTileNumCols   =  zgemm_Col_CC_B1_MX032_NX032_KX01_microTileNumCols;
          return true;
        }
      }
    }
  }
  return false; // didn't find a match
}

