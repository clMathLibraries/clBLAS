// GENERATED using create_user_gemm_cl_kernels.py

#if defined( __APPLE__ ) || defined( __MACOSX )
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

cl_kernel sgemm_Col_NT_B1_MX128_NX128_KX16_clKernel = NULL;
cl_kernel sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_clKernel = NULL;
cl_kernel sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_clKernel = NULL;
cl_kernel sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_clKernel = NULL;
cl_kernel sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_clKernel = NULL;
cl_kernel sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_clKernel = NULL;
cl_kernel sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_clKernel = NULL;

#ifdef __cplusplus
extern "C" {
#endif
    void initUserGemmClKernels(void);
#ifdef __cplusplus
}
#endif

void initUserGemmClKernels(void) {
    if(sgemm_Col_NT_B1_MX128_NX128_KX16_clKernel != NULL) {
        clReleaseKernel(sgemm_Col_NT_B1_MX128_NX128_KX16_clKernel);
        sgemm_Col_NT_B1_MX128_NX128_KX16_clKernel = NULL;
    }
    if(sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_clKernel != NULL) {
        clReleaseKernel(sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_clKernel);
        sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_clKernel = NULL;
    }
    if(sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_clKernel != NULL) {
        clReleaseKernel(sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_clKernel);
        sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_clKernel = NULL;
    }
    if(sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_clKernel != NULL) {
        clReleaseKernel(sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_clKernel);
        sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_clKernel = NULL;
    }
    if(sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_clKernel != NULL) {
        clReleaseKernel(sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_clKernel);
        sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_clKernel = NULL;
    }
    if(sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_clKernel != NULL) {
        clReleaseKernel(sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_clKernel);
        sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_clKernel = NULL;
    }
    if(sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_clKernel != NULL) {
        clReleaseKernel(sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_clKernel);
        sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_clKernel = NULL;
    }
}
