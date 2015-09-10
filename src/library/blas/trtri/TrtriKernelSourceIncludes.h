
#ifndef TRTRI_SOURCE_INCLUDES_H
#define TRTRI_SOURCE_INCLUDES_H
#include <cstddef>
#include "TrtriKernelSourceIncludes.cpp"

//**** compiler flags
//**** online compilation flags
const char * const TrtriBuildOptions = "-cl-std=CL2.0";
const char * const TrtribinBuildOptions = "-cl-std=CL2.0";


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

#endif
