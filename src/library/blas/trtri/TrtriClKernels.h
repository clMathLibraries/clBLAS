
#ifndef TRTRI_CL_KERNELS_H
#define TRTRI_CL_KERNELS_H
#include "CL/cl.h"

/*mod 192 dtrsm*/
static cl_kernel diag_dtrtri_upper_192_12_clKernel = NULL;
static cl_kernel triple_dgemm_update_192_12_R_clKernel = NULL;
static cl_kernel triple_dgemm_update_192_24_PART1_R_clKernel = NULL;
static cl_kernel triple_dgemm_update_192_24_PART2_R_clKernel = NULL;
static cl_kernel triple_dgemm_update_192_48_PART1_R_clKernel = NULL;
static cl_kernel triple_dgemm_update_192_48_PART2_R_clKernel = NULL;
static cl_kernel triple_dgemm_update_192_96_PART1_R_clKernel = NULL;
static cl_kernel triple_dgemm_update_192_96_PART2_R_clKernel = NULL;

/*mod 128 dtrsm*/
static cl_kernel diag_dtrtri_upper_128_16_clKernel = NULL;
static cl_kernel triple_dgemm_update_128_16_R_clKernel = NULL;
static cl_kernel triple_dgemm_update_128_32_PART1_R_clKernel = NULL;
static cl_kernel triple_dgemm_update_128_32_PART2_R_clKernel = NULL;
static cl_kernel triple_dgemm_update_128_64_PART1_R_clKernel = NULL;
static cl_kernel triple_dgemm_update_128_64_PART2_R_clKernel = NULL;
static cl_kernel triple_dgemm_update_128_ABOVE64_PART1_R_clKernel = NULL;
static cl_kernel triple_dgemm_update_128_ABOVE64_PART2_R_clKernel = NULL;
static cl_kernel triple_dgemm_update_128_ABOVE64_PART3_R_clKernel = NULL;

#endif