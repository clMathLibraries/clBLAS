/*******************************************************************************
 * This file is NOT auto-generated; populate it with hand-written kernels
 ******************************************************************************/


#ifndef TRTRI_SOURCE_INCLUDES_CPP
#define TRTRI_SOURCE_INCLUDES_CPP

#ifndef CLBLAS_OFFLINE_COMPILE_DTRSM
/*mod 192 dtrsm*/
#include "diag_dtrtri_upper_192_12.cpp"
#include "triple_dgemm_update_192_12_R.cpp"
#include "triple_dgemm_update_192_24_PART1_R.cpp"
#include "triple_dgemm_update_192_24_PART2_R.cpp"
#include "triple_dgemm_update_192_48_PART1_R.cpp"
#include "triple_dgemm_update_192_48_PART2_R.cpp"
#include "triple_dgemm_update_192_96_PART1_R.cpp"
#include "triple_dgemm_update_192_96_PART2_R.cpp"

/*mod 128 dtrsm*/
/*upper*/
#include "diag_dtrtri_upper_128_16.cpp"
#include "triple_dgemm_update_128_16_R.cpp"
#include "triple_dgemm_update_128_32_PART1_R.cpp"
#include "triple_dgemm_update_128_32_PART2_R.cpp"
#include "triple_dgemm_update_128_64_PART1_R.cpp"
#include "triple_dgemm_update_128_64_PART2_R.cpp"
#include "triple_dgemm_update_128_ABOVE64_PART1_R.cpp"
#include "triple_dgemm_update_128_ABOVE64_PART2_R.cpp"
#include "triple_dgemm_update_128_ABOVE64_PART3_R.cpp"

/*lower*/
#include "diag_dtrtri_lower_128_16.cpp"
#include "triple_dgemm_update_128_16_PART1_L.cpp"
#include "triple_dgemm_update_128_16_PART2_L.cpp"
#include "triple_dgemm_update_128_32_PART1_L.cpp"
#include "triple_dgemm_update_128_32_PART2_L.cpp"
#include "triple_dgemm_update_128_64_PART1_L.cpp"
#include "triple_dgemm_update_128_64_PART2_L.cpp"
#include "triple_dgemm_update_128_ABOVE64_PART1_L.cpp"
#include "triple_dgemm_update_128_ABOVE64_PART2_L.cpp"
#include "triple_dgemm_update_128_ABOVE64_PART3_L.cpp"

#else
/*mod 192 dtrsm*/
#include "diag_dtrtri_upper_192_12_bin.cpp"
#include "triple_dgemm_update_192_12_R_bin.cpp"
#include "triple_dgemm_update_192_24_PART1_R_bin.cpp"
#include "triple_dgemm_update_192_24_PART2_R_bin.cpp"
#include "triple_dgemm_update_192_48_PART1_R_bin.cpp"
#include "triple_dgemm_update_192_48_PART2_R_bin.cpp"
#include "triple_dgemm_update_192_96_PART1_R_bin.cpp"
#include "triple_dgemm_update_192_96_PART2_R_bin.cpp"

/*mod 128 dtrsm*/
/*upper*/
#include "diag_dtrtri_upper_128_16_bin.cpp"
#include "triple_dgemm_update_128_16_R_bin.cpp"
#include "triple_dgemm_update_128_32_PART1_R_bin.cpp"
#include "triple_dgemm_update_128_32_PART2_R_bin.cpp"
#include "triple_dgemm_update_128_64_PART1_R_bin.cpp"
#include "triple_dgemm_update_128_64_PART2_R_bin.cpp"
#include "triple_dgemm_update_128_ABOVE64_PART1_R_bin.cpp"
#include "triple_dgemm_update_128_ABOVE64_PART2_R_bin.cpp"
#include "triple_dgemm_update_128_ABOVE64_PART3_R_bin.cpp"

/*lower*/
#include "diag_dtrtri_lower_128_16_bin.cpp"
#include "triple_dgemm_update_128_16_PART1_L_bin.cpp"
#include "triple_dgemm_update_128_16_PART2_L_bin.cpp"
#include "triple_dgemm_update_128_32_PART1_L_bin.cpp"
#include "triple_dgemm_update_128_32_PART2_L_bin.cpp"
#include "triple_dgemm_update_128_64_PART1_L_bin.cpp"
#include "triple_dgemm_update_128_64_PART2_L_bin.cpp"
#include "triple_dgemm_update_128_ABOVE64_PART1_L_bin.cpp"
#include "triple_dgemm_update_128_ABOVE64_PART2_L_bin.cpp"
#include "triple_dgemm_update_128_ABOVE64_PART3_L_bin.cpp"

#endif //CLBLAS_OFFLINE_COMPILE_DTRSM

#endif
