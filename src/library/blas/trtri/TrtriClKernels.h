
#ifndef TRTRI_CL_KERNELS_H
#define TRTRI_CL_KERNELS_H
#include "CL/cl.h"

static cl_kernel diag_dtrtri_upper_192_12_clKernel = NULL;
static cl_kernel triple_dgemm_update_192_12_R = NULL;
static cl_kernel triple_dgemm_update_192_24_PART1_R = NULL;
static cl_kernel triple_dgemm_update_192_24_PART2_R = NULL;
static cl_kernel triple_dgemm_update_192_48_PART1_R = NULL;
static cl_kernel triple_dgemm_update_192_48_PART2_R = NULL;
static cl_kernel triple_dgemm_update_192_96_PART1_R = NULL;
static cl_kernel triple_dgemm_update_192_96_PART2_R = NULL;


#endif