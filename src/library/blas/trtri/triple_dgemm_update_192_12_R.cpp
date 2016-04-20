/*******************************************************************************
 * Hand-tuned kernel

 * B21 = -inv(A11)*A12*inv(A22)
 * 12 to 24

 ******************************************************************************/

#ifndef KERNEL_TRIPLE_DGEMM_UPDATE_192_12_R_SRC_CPP
#define KERNEL_TRIPLE_DGEMM_UPDATE_192_12_R_SRC_CPP

#ifndef STRINGIFY
#define STRINGIFY2(...) #__VA_ARGS__
#define STRINGIFY(...) STRINGIFY2(__VA_ARGS__)
#endif

unsigned char *triple_dgemm_update_192_12_R_bin = 0;
size_t triple_dgemm_update_192_12_R_binSize = 0;

const char * const triple_dgemm_update_192_12_R_src = STRINGIFY(
#define NB 192\n
	__kernel void TRIPLE_DGEMM_UPDATE_192_12_R(__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, uint lda, int npages, int na)\n
{\n
	// Ain is the non inverse matrix; the size of Ain is lda * na
	// offAin is the offset of Ain
	// d_dinvA is the inversed matrix. the size of d_invA is NB * (na-1)/NB + 1
	// blk is subblock size, which is 12 here.
	// lda in leading dimension. Column major here
	// npages = (na-1)/12*2 + 1; for 96 this is 4 for 192 this is 8

	//Work group size is [12]
	//global work size is [96*number of blocks]
	//each work item in each work group is responsible for every element in that row
	//each work group is responsible for one gemm;\


	////////////// A12*invA22
	const uint gidx = get_group_id(0);\n
	const uint idx = get_local_id(0);\n

	const uint page = gidx % npages;\n
	const uint page_block = page / 8;\n//8 pages per page block
	const uint page_index_in_block = page % 8;\n


	__global double *B, *C;\n
	__local double lA[12][12];\n
	__local double lB[12][12];\n
	double privateC[12] = { (double)0 };\n

	//decide A12 location for each page
	Ain = Ain + offAin;\n
	Ain += (page*blk * 2 + blk) * lda + page * 2 * blk;\n

	//decide invA22 (B) location for each page
	B = d_dinvA + page_block*NB*NB + (page_index_in_block*blk * 2 + blk) * NB + page_index_in_block * 2 * blk + blk;\n

	//decide invA12 location for each page
	C = d_dinvA + page_block*NB*NB + (page_index_in_block*blk * 2 + blk) * NB + page_index_in_block * 2 * blk;\n

	//read A and B into LDS no transpose operated here
	lA[idx][0] = Ain[idx];\n
	lA[idx][1] = Ain[idx + lda];\n
	lA[idx][2] = Ain[idx + lda * 2];\n
	lA[idx][3] = Ain[idx + lda * 3];\n
	lA[idx][4] = Ain[idx + lda * 4];\n
	lA[idx][5] = Ain[idx + lda * 5];\n
	lA[idx][6] = Ain[idx + lda * 6];\n
	lA[idx][7] = Ain[idx + lda * 7];\n
	lA[idx][8] = Ain[idx + lda * 8];\n
	lA[idx][9] = Ain[idx + lda * 9];\n
	lA[idx][10] = Ain[idx + lda * 10];\n
	lA[idx][11] = Ain[idx + lda * 11];\n

	lB[idx][0] = B[idx];\n
	lB[idx][1] = B[idx + NB];\n
	lB[idx][2] = B[idx + NB * 2];\n
	lB[idx][3] = B[idx + NB * 3];\n
	lB[idx][4] = B[idx + NB * 4];\n
	lB[idx][5] = B[idx + NB * 5];\n
	lB[idx][6] = B[idx + NB * 6];\n
	lB[idx][7] = B[idx + NB * 7];\n
	lB[idx][8] = B[idx + NB * 8];\n
	lB[idx][9] = B[idx + NB * 9];\n
	lB[idx][10] = B[idx + NB * 10];\n
	lB[idx][11] = B[idx + NB * 11];\n
	barrier(CLK_LOCAL_MEM_FENCE);\n

	//do math

	uint i = 0;\n

	do{\n
		privateC[0] = mad(lA[idx][i], lB[i][0], privateC[0]);\n
		privateC[1] = mad(lA[idx][i], lB[i][1], privateC[1]);\n
		privateC[2] = mad(lA[idx][i], lB[i][2], privateC[2]);\n
		privateC[3] = mad(lA[idx][i], lB[i][3], privateC[3]);\n
		privateC[4] = mad(lA[idx][i], lB[i][4], privateC[4]);\n
		privateC[5] = mad(lA[idx][i], lB[i][5], privateC[5]);\n
		privateC[6] = mad(lA[idx][i], lB[i][6], privateC[6]);\n
		privateC[7] = mad(lA[idx][i], lB[i][7], privateC[7]);\n
		privateC[8] = mad(lA[idx][i], lB[i][8], privateC[8]);\n
		privateC[9] = mad(lA[idx][i], lB[i][9], privateC[9]);\n
		privateC[10] = mad(lA[idx][i], lB[i][10], privateC[10]);\n
		privateC[11] = mad(lA[idx][i], lB[i][11], privateC[11]);\n
		//mem_fence(CLK_LOCAL_MEM_FENCE);
		i = i + 1;\n
	} while (i < 12);\n

	i = 0;\n
	do{\n
		C[NB*i + idx] = privateC[i];\n
		i = i + 1;\n
	} while (i < 12);\n

	////////////// -invA11*invA12
	barrier(CLK_GLOBAL_MEM_FENCE);\n
	//A is moving to invA11
	__global double *A;\n
	A = d_dinvA + page_block*NB*NB + ((page % 4)*blk * 2) * NB + (page % 4) * 2 * blk;\n
	//both B and C are pointing at invA12
	B = C;\n

	//read A and B into LDS no transpose operated here
	lA[idx][0] = A[idx];\n
	lA[idx][1] = A[idx + NB];\n
	lA[idx][2] = A[idx + NB * 2];\n
	lA[idx][3] = A[idx + NB * 3];\n
	lA[idx][4] = A[idx + NB * 4];\n
	lA[idx][5] = A[idx + NB * 5];\n
	lA[idx][6] = A[idx + NB * 6];\n
	lA[idx][7] = A[idx + NB * 7];\n
	lA[idx][8] = A[idx + NB * 8];\n
	lA[idx][9] = A[idx + NB * 9];\n
	lA[idx][10] = A[idx + NB * 10];\n
	lA[idx][11] = A[idx + NB * 11];\n

	lB[idx][0] = B[idx];\n
	lB[idx][1] = B[idx + NB];\n
	lB[idx][2] = B[idx + NB * 2];\n
	lB[idx][3] = B[idx + NB * 3];\n
	lB[idx][4] = B[idx + NB * 4];\n
	lB[idx][5] = B[idx + NB * 5];\n
	lB[idx][6] = B[idx + NB * 6];\n
	lB[idx][7] = B[idx + NB * 7];\n
	lB[idx][8] = B[idx + NB * 8];\n
	lB[idx][9] = B[idx + NB * 9];\n
	lB[idx][10] = B[idx + NB * 10];\n
	lB[idx][11] = B[idx + NB * 11];\n
	barrier(CLK_LOCAL_MEM_FENCE);\n

	//do math

	i = 0;\n
	privateC[0] = 0;\n
	privateC[1] = 0;\n
	privateC[2] = 0;\n
	privateC[3] = 0;\n
	privateC[4] = 0;\n
	privateC[5] = 0;\n
	privateC[6] = 0;\n
	privateC[7] = 0;\n
	privateC[8] = 0;\n
	privateC[9] = 0;\n
	privateC[10] = 0;\n
	privateC[11] = 0;\n
	do{\n
		privateC[0] = mad(lA[idx][i], lB[i][0], privateC[0]);\n
		privateC[1] = mad(lA[idx][i], lB[i][1], privateC[1]);\n
		privateC[2] = mad(lA[idx][i], lB[i][2], privateC[2]);\n
		privateC[3] = mad(lA[idx][i], lB[i][3], privateC[3]);\n
		privateC[4] = mad(lA[idx][i], lB[i][4], privateC[4]);\n
		privateC[5] = mad(lA[idx][i], lB[i][5], privateC[5]);\n
		privateC[6] = mad(lA[idx][i], lB[i][6], privateC[6]);\n
		privateC[7] = mad(lA[idx][i], lB[i][7], privateC[7]);\n
		privateC[8] = mad(lA[idx][i], lB[i][8], privateC[8]);\n
		privateC[9] = mad(lA[idx][i], lB[i][9], privateC[9]);\n
		privateC[10] = mad(lA[idx][i], lB[i][10], privateC[10]);\n
		privateC[11] = mad(lA[idx][i], lB[i][11], privateC[11]);\n
		//mem_fence(CLK_LOCAL_MEM_FENCE);
		i = i + 1;\n
	} while (i < 12);\n

	i = 0;\n
	do{\n
		C[NB*i + idx] = -1 * privateC[i];\n
		i = i + 1;\n
	} while (i < 12);\n

}\n
// end of kernel
);
#endif
