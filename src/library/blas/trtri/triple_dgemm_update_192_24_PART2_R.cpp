/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_TRIPLE_DGEMM_UPDATE_192_24_PART2_R_SRC_CPP
#define KERNEL_TRIPLE_DGEMM_UPDATE_192_24_PART2_R_SRC_CPP

#ifndef STRINGIFY
#define STRINGIFY2(...) #__VA_ARGS__
#define STRINGIFY(...) STRINGIFY2(__VA_ARGS__)
#endif

unsigned char *triple_dgemm_update_192_24_PART2_R_bin = 0;
size_t triple_dgemm_update_192_24_PART2_R_binSize = 0;

const char * const triple_dgemm_update_192_24_PART2_R_src = STRINGIFY(
#define NB 192\n
	__kernel void TRIPLE_DGEMM_UPDATE_192_24_PART2_R(__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)\n
{\n
	// Ain is the non inverse matrix; the size of Ain is lda * na
	// offAin is the offset of Ain
	// d_dinvA is the inversed matrix. the size of d_invA is NB * (na-1)/NB + 1
	// blk is subblock size, which is 24 here.
	// lda in leading dimension. Column major here
	// npages = (na-1)/12*2 + 1; for 96 this is 2 for 192 this is 4

	//Work group size is [24, 2]
	//global work size is [96*number of blocks, 2]
	//each work item in each work group is responsible for 12 elements (half) in that row
	//each work group is responsible for one gemm;


	////////////// -invA11*invA12
	const uint gidx = get_group_id(0);\n
	const uint gidy = get_group_id(1);\n
	const uint idx = get_local_id(0);\n
	const uint idy = get_local_id(1);\n

	const uint page = gidx % npages; \n//0-3 for 192; 0-1 for 96
	const uint page_block = page / 4; \n//4 pages per page block

	__global double *A, *B, *C; \n
	__local double lA[24][24]; \n
	__local double lB[24][24]; \n
	double privateC[12] = { (double)0 }; \n

	//decide invA11 location for each page
	A = d_dinvA + page_block*NB*NB + (page % 4)*blk * 2 * NB + (page % 4) * 2 * blk; \n
	//decide invA12 location for each page
	B = d_dinvA + page_block*NB*NB + ((page % 4)*blk * 2 + blk) * NB + (page % 4) * 2 * blk; \n
	C = B;
	//C = d_dinvA + page_block*NB*NB + ((page%4)*blk*2) * NB + (page%4) * 2 * blk + blk;

	//read A and B into LDS no transpose operated here
	//each work iteam loads half a row
    lA[idx][0 + idy * 12] = A[idx + idy * 12 * NB]; \n
    lA[idx][1 + idy * 12] = A[idx + NB + idy * 12 * NB]; \n
	lA[idx][2 + idy * 12] = A[idx + NB * 2 + idy * 12 * NB];\n
	lA[idx][3 + idy * 12] = A[idx + NB * 3 + idy * 12 * NB];\n
	lA[idx][4 + idy * 12] = A[idx + NB * 4 + idy * 12 * NB];\n
	lA[idx][5 + idy * 12] = A[idx + NB * 5 + idy * 12 * NB];\n
	lA[idx][6 + idy * 12] = A[idx + NB * 6 + idy * 12 * NB];\n
	lA[idx][7 + idy * 12] = A[idx + NB * 7 + idy * 12 * NB];\n
	lA[idx][8 + idy * 12] = A[idx + NB * 8 + idy * 12 * NB];\n
	lA[idx][9 + idy * 12] = A[idx + NB * 9 + idy * 12 * NB];\n
	lA[idx][10 + idy * 12] = A[idx + NB * 10 + idy * 12 * NB];\n
	lA[idx][11 + idy * 12] = A[idx + NB * 11 + idy * 12 * NB];\n

	lB[idx][0 + idy * 12] = B[idx + idy * 12 * NB];\n
	lB[idx][1 + idy * 12] = B[idx + NB + idy * 12 * NB];\n
	lB[idx][2 + idy * 12] = B[idx + NB * 2 + idy * 12 * NB];\n
	lB[idx][3 + idy * 12] = B[idx + NB * 3 + idy * 12 * NB];\n
	lB[idx][4 + idy * 12] = B[idx + NB * 4 + idy * 12 * NB];\n
	lB[idx][5 + idy * 12] = B[idx + NB * 5 + idy * 12 * NB];\n
	lB[idx][6 + idy * 12] = B[idx + NB * 6 + idy * 12 * NB];\n
	lB[idx][7 + idy * 12] = B[idx + NB * 7 + idy * 12 * NB];\n
	lB[idx][8 + idy * 12] = B[idx + NB * 8 + idy * 12 * NB];\n
	lB[idx][9 + idy * 12] = B[idx + NB * 9 + idy * 12 * NB];\n
	lB[idx][10 + idy * 12] = B[idx + NB * 10 + idy * 12 * NB];\n
	lB[idx][11 + idy * 12] = B[idx + NB * 11 + idy * 12 * NB];\n
	barrier(CLK_LOCAL_MEM_FENCE);\n
	//do math

	uint i = 0;\n

	do{\n
		privateC[0] = mad(lA[idx][i], lB[i][0 + idy * 12], privateC[0]);\n
		privateC[1] = mad(lA[idx][i], lB[i][1 + idy * 12], privateC[1]);\n
		privateC[2] = mad(lA[idx][i], lB[i][2 + idy * 12], privateC[2]);\n
		privateC[3] = mad(lA[idx][i], lB[i][3 + idy * 12], privateC[3]);\n
		privateC[4] = mad(lA[idx][i], lB[i][4 + idy * 12], privateC[4]);\n
		privateC[5] = mad(lA[idx][i], lB[i][5 + idy * 12], privateC[5]);\n
		privateC[6] = mad(lA[idx][i], lB[i][6 + idy * 12], privateC[6]);\n
		privateC[7] = mad(lA[idx][i], lB[i][7 + idy * 12], privateC[7]);\n
		privateC[8] = mad(lA[idx][i], lB[i][8 + idy * 12], privateC[8]);\n
		privateC[9] = mad(lA[idx][i], lB[i][9 + idy * 12], privateC[9]);\n
		privateC[10] = mad(lA[idx][i], lB[i][10 + idy * 12], privateC[10]);\n
		privateC[11] = mad(lA[idx][i], lB[i][11 + idy * 12], privateC[11]);\n
		i = i + 1;\n
	} while (i < 24);\n

	i = 0;\n
	do{\n
		C[NB*idy * 12 + NB*i + idx] = -1 * privateC[i];\n
		i = i + 1;\n
	} while (i < 12);\n

}\n
// end of kernel
);
#endif
