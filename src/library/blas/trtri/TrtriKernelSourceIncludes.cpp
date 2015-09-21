/*******************************************************************************
 * This file is NOT auto-generated; populate it with hand-written kernels
 ******************************************************************************/


#ifndef TRTRI_SOURCE_INCLUDES_CPP
#define TRTRI_SOURCE_INCLUDES_CPP

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
#include "diag_dtrtri_upper_128_16.cpp"
#include "triple_dgemm_update_128_16_R.cpp"
#include "triple_dgemm_update_128_32_PART1_R.cpp"
#include "triple_dgemm_update_128_32_PART2_R.cpp"
#include "triple_dgemm_update_128_64_PART1_R.cpp"
#include "triple_dgemm_update_128_64_PART2_R.cpp"
#include "triple_dgemm_update_128_ABOVE64_PART1_R.cpp"
#include "triple_dgemm_update_128_ABOVE64_PART2_R.cpp"
#include "triple_dgemm_update_128_ABOVE64_PART3_R.cpp"

#endif
