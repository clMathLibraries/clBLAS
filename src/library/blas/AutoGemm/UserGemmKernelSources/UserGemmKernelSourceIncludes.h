/*******************************************************************************
 * This file is NOT auto-generated; populate it with hand-written kernels
 * - David Tanner
 ******************************************************************************/

#ifndef USER_GEMM_SOURCE_INCLUDES_H
#define USER_GEMM_SOURCE_INCLUDES_H

//**** Kernels to replace auto-generated versions
#include "UserGemmKernelSources/sgemm_Col_NN_B0_MX032_NX032_KX16_src.h"
#include "UserGemmKernelSources/sgemm_Col_NN_B0_MX064_NX064_KX16_src.h"
#include "UserGemmKernelSources/sgemm_Col_NN_B0_MX096_NX096_KX16_src.h"
#include "UserGemmKernelSources/sgemm_Col_NN_B1_MX032_NX032_KX16_src.h"
#include "UserGemmKernelSources/sgemm_Col_NN_B1_MX064_NX064_KX16_src.h"
#include "UserGemmKernelSources/sgemm_Col_NN_B1_MX096_NX096_KX16_src.h"

#include "UserGemmKernelSources/sgemm_Col_NT_B0_MX032_NX032_KX16_src.h"
#include "UserGemmKernelSources/sgemm_Col_NT_B0_MX064_NX064_KX16_src.h"
#include "UserGemmKernelSources/sgemm_Col_NT_B0_MX096_NX096_KX16_src.h"
#include "UserGemmKernelSources/sgemm_Col_NT_B1_MX032_NX032_KX16_src.h"
#include "UserGemmKernelSources/sgemm_Col_NT_B1_MX064_NX064_KX16_src.h"
#include "UserGemmKernelSources/sgemm_Col_NT_B1_MX096_NX096_KX16_src.h"

#include "UserGemmKernelSources/sgemm_Col_TN_B0_MX032_NX032_KX16_src.h"
#include "UserGemmKernelSources/sgemm_Col_TN_B0_MX064_NX064_KX16_src.h"
#include "UserGemmKernelSources/sgemm_Col_TN_B0_MX096_NX096_KX16_src.h"
#include "UserGemmKernelSources/sgemm_Col_TN_B1_MX032_NX032_KX16_src.h"
#include "UserGemmKernelSources/sgemm_Col_TN_B1_MX064_NX064_KX16_src.h"
#include "UserGemmKernelSources/sgemm_Col_TN_B1_MX096_NX096_KX16_src.h"

#include "UserGemmKernelSources/dgemm_Col_NN_B0_MX048_NX048_KX08_src.h"
#include "UserGemmKernelSources/dgemm_Col_NN_B1_MX048_NX048_KX08_src.h"
#include "UserGemmKernelSources/dgemm_Col_NT_B0_MX048_NX048_KX08_src.h"
#include "UserGemmKernelSources/dgemm_Col_NT_B1_MX048_NX048_KX08_src.h"
#include "UserGemmKernelSources/dgemm_Col_TN_B0_MX048_NX048_KX08_src.h"
#include "UserGemmKernelSources/dgemm_Col_TN_B1_MX048_NX048_KX08_src.h"

//**** Special kernels without auto-generated counterparts
//**** micro tile size 8x8 kernel
#include "UserGemmKernelSources/sgemm_Col_NT_B1_MX128_NX128_KX16_src.h"
//**** mod32 but not mod64 kernels
#include "UserGemmKernelSources/sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_src.h"
#include "UserGemmKernelSources/sgemm_Col_NT_B1_MX064_NX032_KX16_COL_src.h"
#include "UserGemmKernelSources/sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_src.h"


//**** compiler flags
//**** online compilation flags
const char * const User_srcBuildOptions = "-cl-std=CL2.0";
const char * const User_binBuildOptions = " ";

#endif
