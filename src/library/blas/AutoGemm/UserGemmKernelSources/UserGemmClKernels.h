
#ifndef USERGEMM_CL_KERNELS_H
#define USERGEMM_CL_KERNELS_H
#include "CL/cl.h"

static cl_kernel sgemm_Col_NT_B1_MX128_NX128_KX16_clKernel = NULL;

static cl_kernel sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_clKernel = NULL;
static cl_kernel sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_clKernel = NULL;
static cl_kernel sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_clKernel = NULL;

static cl_kernel sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_clKernel = NULL;
static cl_kernel sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_clKernel = NULL;
static cl_kernel sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_clKernel = NULL;

#endif