
#ifndef USERGEMM_CL_KERNELS_H
#define USERGEMM_CL_KERNELS_H

#if defined( __APPLE__ ) || defined( __MACOSX )
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

extern cl_kernel sgemm_Col_NT_B1_MX128_NX128_KX16_clKernel;

extern cl_kernel sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_clKernel;
extern cl_kernel sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_clKernel;
extern cl_kernel sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_clKernel;

extern cl_kernel sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_clKernel;
extern cl_kernel sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_clKernel;
extern cl_kernel sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_clKernel;

extern cl_kernel dgemm_NN_gfx906_tensile_clKernel;
extern cl_kernel dgemm_NT_gfx906_tensile_clKernel;
extern cl_kernel dgemm_TN_gfx906_tensile_clKernel;
extern cl_kernel dgemm_TT_gfx906_tensile_clKernel;

static const int user_kernel_count = 11;

#ifdef __cplusplus
extern "C" {
#endif
    void initUserGemmClKernels(void);
#ifdef __cplusplus
}
#endif

#endif
