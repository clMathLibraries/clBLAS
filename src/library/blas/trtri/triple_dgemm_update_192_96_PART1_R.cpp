/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_TRIPLE_DGEMM_UPDATE_192_96_PART1_R_SRC_CPP
#define KERNEL_TRIPLE_DGEMM_UPDATE_192_96_PART1_R_SRC_CPP

#ifndef STRINGIFY
#define STRINGIFY2(...) #__VA_ARGS__
#define STRINGIFY(...) STRINGIFY2(__VA_ARGS__)
#endif

unsigned char *triple_dgemm_update_192_96_PART1_R_bin = 0;
size_t triple_dgemm_update_192_96_PART1_R_binSize = 0;

const char * const triple_dgemm_update_192_96_PART1_R_src = STRINGIFY(
#define NB 192\n
	__kernel void TRIPLE_DGEMM_UPDATE_192_96_PART1_R(__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)\n
{
	// Ain is the non inverse matrix; the size of Ain is lda * na
	// offAin is the offset of Ain
	// d_dinvA is the inversed matrix. the size of d_invA is NB * (na-1)/NB + 1
	// blk is subblock size, which is 96 here.
	// lda in leading dimension. Column major here
	// npages = (na-1)/12*2 + 1; for 192 this is 1 for 384 this is 2

	//Work group size is [24, 2]
	//global work size is [96*number of blocks, 8]
	//each work item in each work group is responsible for 12 elements (1/8) in that row
	//each work group is responsible for 24 by 24 macro tile;

	////////////// A12*invA22
	const uint gidx = get_group_id(0);\n
	const uint gidy = get_group_id(1); \n
	const uint idx = get_local_id(0); \n
	const uint idy = get_local_id(1); \n

	//uint page = gidx / 2;//0-1 for 192; 0 for 96
	//const uint page = (gidx/4)%1;//index of page within a page_block; 1 pages per page_block
	const uint page_block = gidx / 4; \n//#index of page_block; 4 WG per page; 4 WG per page_block


	__global double *B, *C; \n
	__local double lA[24][48]; \n
	__local double lB[48][24]; \n
	double privateC[12] = { (double)0 }; \n

	//decide A12 location for each page
	//each workgroup loads 1/4 of A (left or right)
	Ain = Ain + offAin; \n
	Ain += page_block*NB*lda + page_block*NB + blk*lda + gidx % 4 * (blk / 4); \n

	//decide invA22 (B) location for each page
	//each workgroup loads 1/4 of B (up or down)
	B = d_dinvA + page_block*NB*NB + blk*NB + blk + gidy*(blk / 4)*NB; \n

	//decide invA12 location for each page;
	//Actually this will be stored in invA21 temporarily
	//each workgroup writes 1/4*1/4 of C
	C = d_dinvA + page_block*NB*NB + blk*NB + gidx % 4 * (blk / 4) + gidy*(blk / 4)*NB; \n

	//read A and B into LDS no transpose operated here
	//each work item loads a half row of A and half column of B
	//each loop loads 1/4 row of A and 1/4 column of B
	//idx 0-23 idy 0-1

	uint block_k = blk / 48; \n //thus we need 2 iterations here
	do{\n
		barrier(CLK_LOCAL_MEM_FENCE); \n
		lA[idx][0 + idy * 24] = Ain[idx + idy * 24 * lda]; \n
		lA[idx][1 + idy * 24] = Ain[idx + lda + idy * 24 * lda]; \n
		lA[idx][2 + idy * 24] = Ain[idx + lda * 2 + idy * 24 * lda]; \n
		lA[idx][3 + idy * 24] = Ain[idx + lda * 3 + idy * 24 * lda]; \n
		lA[idx][4 + idy * 24] = Ain[idx + lda * 4 + idy * 24 * lda]; \n
		lA[idx][5 + idy * 24] = Ain[idx + lda * 5 + idy * 24 * lda]; \n
		lA[idx][6 + idy * 24] = Ain[idx + lda * 6 + idy * 24 * lda]; \n
		lA[idx][7 + idy * 24] = Ain[idx + lda * 7 + idy * 24 * lda]; \n
		lA[idx][8 + idy * 24] = Ain[idx + lda * 8 + idy * 24 * lda]; \n
		lA[idx][9 + idy * 24] = Ain[idx + lda * 9 + idy * 24 * lda]; \n
		lA[idx][10 + idy * 24] = Ain[idx + lda * 10 + idy * 24 * lda];\n
		lA[idx][11 + idy * 24] = Ain[idx + lda * 11 + idy * 24 * lda];\n
		lA[idx][12 + idy * 24] = Ain[idx + lda * 12 + idy * 24 * lda];\n
		lA[idx][13 + idy * 24] = Ain[idx + lda * 13 + idy * 24 * lda];\n
		lA[idx][14 + idy * 24] = Ain[idx + lda * 14 + idy * 24 * lda];\n
		lA[idx][15 + idy * 24] = Ain[idx + lda * 15 + idy * 24 * lda];\n
		lA[idx][16 + idy * 24] = Ain[idx + lda * 16 + idy * 24 * lda];\n
		lA[idx][17 + idy * 24] = Ain[idx + lda * 17 + idy * 24 * lda];\n
		lA[idx][18 + idy * 24] = Ain[idx + lda * 18 + idy * 24 * lda];\n
		lA[idx][19 + idy * 24] = Ain[idx + lda * 19 + idy * 24 * lda];\n
		lA[idx][20 + idy * 24] = Ain[idx + lda * 20 + idy * 24 * lda];\n
		lA[idx][21 + idy * 24] = Ain[idx + lda * 21 + idy * 24 * lda];\n
		lA[idx][22 + idy * 24] = Ain[idx + lda * 22 + idy * 24 * lda];\n
		lA[idx][23 + idy * 24] = Ain[idx + lda * 23 + idy * 24 * lda];\n

		lB[0 + idy * 24][idx] = B[idx*NB + idy * 24]; \n
		lB[1 + idy * 24][idx] = B[idx*NB + idy * 24 + 1];\n
		lB[2 + idy * 24][idx] = B[idx*NB + idy * 24 + 2];\n
		lB[3 + idy * 24][idx] = B[idx*NB + idy * 24 + 3];\n
		lB[4 + idy * 24][idx] = B[idx*NB + idy * 24 + 4];\n
		lB[5 + idy * 24][idx] = B[idx*NB + idy * 24 + 5];\n
		lB[6 + idy * 24][idx] = B[idx*NB + idy * 24 + 6];\n
		lB[7 + idy * 24][idx] = B[idx*NB + idy * 24 + 7];\n
		lB[8 + idy * 24][idx] = B[idx*NB + idy * 24 + 8];\n
		lB[9 + idy * 24][idx] = B[idx*NB + idy * 24 + 9];\n
		lB[10 + idy * 24][idx] = B[idx*NB + idy * 24 + 10];\n
		lB[11 + idy * 24][idx] = B[idx*NB + idy * 24 + 11];\n
		lB[12 + idy * 24][idx] = B[idx*NB + idy * 24 + 12];\n
		lB[13 + idy * 24][idx] = B[idx*NB + idy * 24 + 13];\n
		lB[14 + idy * 24][idx] = B[idx*NB + idy * 24 + 14];\n
		lB[15 + idy * 24][idx] = B[idx*NB + idy * 24 + 15];\n
		lB[16 + idy * 24][idx] = B[idx*NB + idy * 24 + 16];\n
		lB[17 + idy * 24][idx] = B[idx*NB + idy * 24 + 17];\n
		lB[18 + idy * 24][idx] = B[idx*NB + idy * 24 + 18];\n
		lB[19 + idy * 24][idx] = B[idx*NB + idy * 24 + 19];\n
		lB[20 + idy * 24][idx] = B[idx*NB + idy * 24 + 20];\n
		lB[21 + idy * 24][idx] = B[idx*NB + idy * 24 + 21];\n
		lB[22 + idy * 24][idx] = B[idx*NB + idy * 24 + 22];\n
		lB[23 + idy * 24][idx] = B[idx*NB + idy * 24 + 23];\n
		barrier(CLK_LOCAL_MEM_FENCE); \n

		//do math

		uint i = 0; \n

		do{\n
			privateC[0] = mad(lA[idx][i], lB[i][0 + idy * 12], privateC[0]); \n
			privateC[1] = mad(lA[idx][i], lB[i][1 + idy * 12], privateC[1]); \n
			privateC[2] = mad(lA[idx][i], lB[i][2 + idy * 12], privateC[2]); \n
			privateC[3] = mad(lA[idx][i], lB[i][3 + idy * 12], privateC[3]); \n
			privateC[4] = mad(lA[idx][i], lB[i][4 + idy * 12], privateC[4]); \n
			privateC[5] = mad(lA[idx][i], lB[i][5 + idy * 12], privateC[5]); \n
			privateC[6] = mad(lA[idx][i], lB[i][6 + idy * 12], privateC[6]); \n
			privateC[7] = mad(lA[idx][i], lB[i][7 + idy * 12], privateC[7]); \n
			privateC[8] = mad(lA[idx][i], lB[i][8 + idy * 12], privateC[8]); \n
			privateC[9] = mad(lA[idx][i], lB[i][9 + idy * 12], privateC[9]); \n
			privateC[10] = mad(lA[idx][i], lB[i][10 + idy * 12], privateC[10]); \n
			privateC[11] = mad(lA[idx][i], lB[i][11 + idy * 12], privateC[11]); \n
			i = i + 1; \n
		} while (i < 48); \n

		Ain += 48 * lda; \n
		B += 48; \n
	} while (--block_k>0); \n

	uint i = 0; \n
	do{\n
		C[NB*idy * 12 + NB*i + idx] = privateC[i]; \n
		i = i + 1; \n
	} while (i < 12); \n


}\n
// end of kernel
);
#endif
