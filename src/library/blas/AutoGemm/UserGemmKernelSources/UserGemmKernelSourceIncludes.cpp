/*******************************************************************************
 * This file is NOT auto-generated; populate it with hand-written kernels
 * - David Tanner
 ******************************************************************************/


#ifndef USER_GEMM_SOURCE_INCLUDES_CPP
#define USER_GEMM_SOURCE_INCLUDES_CPP

//**** Kernels to replace auto-generated versions
#include "UserGemmKernelSources/sgemm_Col_NN_B0_MX032_NX032_KX16_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_NN_B0_MX064_NX064_KX16_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_NN_B0_MX096_NX096_KX16_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_NN_B1_MX032_NX032_KX16_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_NN_B1_MX064_NX064_KX16_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_NN_B1_MX096_NX096_KX16_src.cpp"
																	 
#include "UserGemmKernelSources/sgemm_Col_NT_B0_MX032_NX032_KX16_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_NT_B0_MX064_NX064_KX16_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_NT_B0_MX096_NX096_KX16_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_NT_B1_MX032_NX032_KX16_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_NT_B1_MX064_NX064_KX16_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_NT_B1_MX096_NX096_KX16_src.cpp"
																	 
#include "UserGemmKernelSources/sgemm_Col_TN_B0_MX032_NX032_KX16_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_TN_B0_MX064_NX064_KX16_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_TN_B0_MX096_NX096_KX16_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_TN_B1_MX032_NX032_KX16_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_TN_B1_MX064_NX064_KX16_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_TN_B1_MX096_NX096_KX16_src.cpp"
																	 
#include "UserGemmKernelSources/dgemm_Col_NN_B0_MX048_NX048_KX08_src.cpp"
#include "UserGemmKernelSources/dgemm_Col_NN_B1_MX048_NX048_KX08_src.cpp"
#include "UserGemmKernelSources/dgemm_Col_NT_B0_MX048_NX048_KX08_src.cpp"
#include "UserGemmKernelSources/dgemm_Col_NT_B1_MX048_NX048_KX08_src.cpp"
#include "UserGemmKernelSources/dgemm_Col_TN_B0_MX048_NX048_KX08_src.cpp"
#include "UserGemmKernelSources/dgemm_Col_TN_B1_MX048_NX048_KX08_src.cpp"

//**** Special kernels without auto-generated counterparts
//**** micro tile size 8x8 kernel
#include "UserGemmKernelSources/sgemm_Col_NT_B1_MX128_NX128_KX16_src.cpp"
//**** mod32 but not mod64 kernels
#include "UserGemmKernelSources/sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_NT_B1_MX064_NX032_KX16_COL_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_src.cpp"
//**** branch kernels with 32x32 macro tile size
#include "UserGemmKernelSources/sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_src.cpp"
#include "UserGemmKernelSources/sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_src.cpp"

//**** Special kernels for vega20 from tensile lib
#include "UserGemmKernelSources/dgemm_NN_gfx906_tensile_src.cpp"
#include "UserGemmKernelSources/dgemm_NT_gfx906_tensile_src.cpp"
#include "UserGemmKernelSources/dgemm_TN_gfx906_tensile_src.cpp"
#include "UserGemmKernelSources/dgemm_TT_gfx906_tensile_src.cpp"

//**** compiler flags
//**** online compilation flags
//const char * const User_srcBuildOptions = "-cl-std=CL2.0";
//const char * const User_binBuildOptions = " ";

#endif
