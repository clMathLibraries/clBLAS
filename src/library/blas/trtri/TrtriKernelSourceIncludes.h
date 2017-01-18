
#ifndef TRTRI_SOURCE_INCLUDES_H
#define TRTRI_SOURCE_INCLUDES_H
#include <cstddef>
#include "TrtriKernelSourceIncludes.cpp"

//**** compiler flags
//**** online compilation flags
const char * const TrtriBuildOptions = "-cl-std=CL" OPENCL_VERSION;
const char * const TrtribinBuildOptions = "-cl-std=CL" OPENCL_VERSION;

/*mod 192 dtrsm*/
extern const char * const diag_dtrtri_upper_192_12_src;
extern unsigned char *diag_dtrtri_upper_192_12_bin;
extern size_t diag_dtrtri_upper_192_12_binSize;

extern const char * const triple_dgemm_update_192_12_R_src;
extern unsigned char *triple_dgemm_update_192_12_R_bin;
extern size_t triple_dgemm_update_192_12_R_binSize;

extern const char * const triple_dgemm_update_192_24_PART1_R_src;
extern unsigned char *triple_dgemm_update_192_24_PART1_R_bin;
extern size_t triple_dgemm_update_192_24_PART1_R_binSize;

extern const char * const triple_dgemm_update_192_24_PART2_R_src;
extern unsigned char *triple_dgemm_update_192_24_PART2_R_bin;
extern size_t triple_dgemm_update_192_24_PART2_R_binSize;

extern const char * const triple_dgemm_update_192_48_PART1_R_src;
extern unsigned char *triple_dgemm_update_192_48_PART1_R_bin;
extern size_t triple_dgemm_update_192_48_PART1_R_binSize;

extern const char * const triple_dgemm_update_192_48_PART2_R_src;
extern unsigned char *triple_dgemm_update_192_48_PART2_R_bin;
extern size_t triple_dgemm_update_192_48_PART2_R_binSize;

extern const char * const triple_dgemm_update_192_96_PART1_R_src;
extern unsigned char *triple_dgemm_update_192_96_PART1_R_bin;
extern size_t triple_dgemm_update_192_96_PART1_R_binSize;

extern const char * const triple_dgemm_update_192_96_PART2_R_src;
extern unsigned char *triple_dgemm_update_192_96_PART2_R_bin;
extern size_t triple_dgemm_update_192_96_PART2_R_binSize;

/*mod 128 dtrsm*/
/*upper*/
extern const char * const  diag_dtrtri_upper_128_16_src;
extern unsigned char *diag_dtrtri_upper_128_16_bin;
extern size_t diag_dtrtri_upper_128_16_binSize;

extern const char * const  triple_dgemm_update_128_16_R_src;
extern unsigned char *triple_dgemm_update_128_16_R_bin;
extern size_t triple_dgemm_update_128_16_R_binSize;

extern const char * const  triple_dgemm_update_128_32_PART1_R_src;
extern unsigned char *triple_dgemm_update_128_32_PART1_R_bin;
extern size_t triple_dgemm_update_128_32_PART1_R_binSize;

extern const char * const  triple_dgemm_update_128_32_PART2_R_src;
extern unsigned char *triple_dgemm_update_128_32_PART2_R_bin;
extern size_t triple_dgemm_update_128_32_PART2_R_binSize;

extern const char * const  triple_dgemm_update_128_64_PART1_R_src;
extern unsigned char *triple_dgemm_update_128_64_PART1_R_bin;
extern size_t triple_dgemm_update_128_64_PART1_R_binSize;

extern const char * const  triple_dgemm_update_128_64_PART2_R_src;
extern unsigned char *triple_dgemm_update_128_64_PART2_R_bin;
extern size_t triple_dgemm_update_128_64_PART2_R_binSize;

extern const char * const  triple_dgemm_update_128_ABOVE64_PART1_R_src;
extern unsigned char *triple_dgemm_update_128_ABOVE64_PART1_R_bin;
extern size_t triple_dgemm_update_128_ABOVE64_PART1_R_binSize;

extern const char * const  triple_dgemm_update_128_ABOVE64_PART2_R_src;
extern unsigned char *triple_dgemm_update_128_ABOVE64_PART2_R_bin;
extern size_t triple_dgemm_update_128_ABOVE64_PART2_R_binSize;

extern const char * const  triple_dgemm_update_128_ABOVE64_PART3_R_src;
extern unsigned char *triple_dgemm_update_128_ABOVE64_PART3_R_bin;
extern size_t triple_dgemm_update_128_ABOVE64_PART3_R_binSize;

/*lower*/
extern const char * const  diag_dtrtri_lower_128_16_src;
extern unsigned char *diag_dtrtri_lower_128_16_bin;
extern size_t diag_dtrtri_lower_128_16_binSize;

extern const char * const  triple_dgemm_update_128_16_PART1_L_src;
extern unsigned char *triple_dgemm_update_128_16_PART1_L_bin;
extern size_t triple_dgemm_update_128_16_PART1_L_binSize;

extern const char * const  triple_dgemm_update_128_16_PART2_L_src;
extern unsigned char *triple_dgemm_update_128_16_PART2_L_bin;
extern size_t triple_dgemm_update_128_16_PART2_L_binSize;

extern const char * const  triple_dgemm_update_128_32_PART1_L_src;
extern unsigned char *triple_dgemm_update_128_32_PART1_L_bin;
extern size_t triple_dgemm_update_128_32_PART1_L_binSize;

extern const char * const  triple_dgemm_update_128_32_PART2_L_src;
extern unsigned char *triple_dgemm_update_128_32_PART2_L_bin;
extern size_t triple_dgemm_update_128_32_PART2_L_binSize;

extern const char * const  triple_dgemm_update_128_64_PART1_L_src;
extern unsigned char *triple_dgemm_update_128_64_PART1_L_bin;
extern size_t triple_dgemm_update_128_64_PART1_L_binSize;

extern const char * const  triple_dgemm_update_128_64_PART2_L_src;
extern unsigned char *triple_dgemm_update_128_64_PART2_L_bin;
extern size_t triple_dgemm_update_128_64_PART2_L_binSize;

extern const char * const  triple_dgemm_update_128_ABOVE64_PART1_L_src;
extern unsigned char *triple_dgemm_update_128_ABOVE64_PART1_L_bin;
extern size_t triple_dgemm_update_128_ABOVE64_PART1_L_binSize;

extern const char * const  triple_dgemm_update_128_ABOVE64_PART2_L_src;
extern unsigned char *triple_dgemm_update_128_ABOVE64_PART2_L_bin;
extern size_t triple_dgemm_update_128_ABOVE64_PART2_L_binSize;

extern const char * const  triple_dgemm_update_128_ABOVE64_PART3_L_src;
extern unsigned char *triple_dgemm_update_128_ABOVE64_PART3_L_bin;
extern size_t triple_dgemm_update_128_ABOVE64_PART3_L_binSize;

#endif
