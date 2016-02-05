/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_TRIPLE_DGEMM_UPDATE_192_24_PART1_R_SRC_CPP
#define KERNEL_TRIPLE_DGEMM_UPDATE_192_24_PART1_R_SRC_CPP
#pragma message("#define KERNEL_TRIPLE_DGEMM_UPDATE_192_24_PART1_R_SRC_CPP.")

#ifndef STRINGIFY
#define STRINGIFY2(...) #__VA_ARGS__
#define STRINGIFY(...) STRINGIFY2(__VA_ARGS__)
#endif

unsigned char *triple_dgemm_update_192_24_PART1_R_bin = 0;
size_t triple_dgemm_update_192_24_PART1_R_binSize = 0;

const char * const triple_dgemm_update_192_24_PART1_R_src = STRINGIFY(
#define NB 192
	__kernel void TRIPLE_DGEMM_UPDATE_192_24_PART1_R(__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, uint lda, int npages, int na)
{ 
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


	////////////// A12*invA22
	const uint gidx = get_group_id(0); 
	const uint gidy = get_group_id(1); 
	const uint idx = get_local_id(0); 
	const uint idy = get_local_id(1); 

	const uint page = gidx % npages; //0-3 for 192; 0-1 for 96
	const uint page_block = page / 4; //4 pages per page block



	__global double *B, *C; 
	__local double lA[24][24]; 
	__local double lB[24][24]; 
	double privateC[12] = { (double)0 }; 

	//decide A12 location for each page
	Ain = Ain + offAin; 
	Ain += (page*blk * 2 + blk) * lda + page * 2 * blk; 

	//decide invA22 (B) location for each page
	B = d_dinvA + page_block*NB*NB + ((page % 4)*blk * 2 + blk) * NB + (page % 4) * 2 * blk + blk; 

	//decide invA12 location for each page
	C = d_dinvA + page_block*NB*NB + ((page % 4)*blk * 2 + blk) * NB + (page % 4) * 2 * blk; 

	//read A and B into LDS no transpose operated here
	//each work iteam loads half a row
	lA[idx][0 + idy * 12] = Ain[idx + idy * 12 * lda]; 
	lA[idx][1 + idy * 12] = Ain[idx + lda + idy * 12 * lda]; 
	lA[idx][2 + idy * 12] = Ain[idx + lda * 2 + idy * 12 * lda]; 
	lA[idx][3 + idy * 12] = Ain[idx + lda * 3 + idy * 12 * lda]; 
	lA[idx][4 + idy * 12] = Ain[idx + lda * 4 + idy * 12 * lda]; 
	lA[idx][5 + idy * 12] = Ain[idx + lda * 5 + idy * 12 * lda]; 
	lA[idx][6 + idy * 12] = Ain[idx + lda * 6 + idy * 12 * lda]; 
	lA[idx][7 + idy * 12] = Ain[idx + lda * 7 + idy * 12 * lda]; 
	lA[idx][8 + idy * 12] = Ain[idx + lda * 8 + idy * 12 * lda]; 
	lA[idx][9 + idy * 12] = Ain[idx + lda * 9 + idy * 12 * lda]; 
	lA[idx][10 + idy * 12] = Ain[idx + lda * 10 + idy * 12 * lda]; 
	lA[idx][11 + idy * 12] = Ain[idx + lda * 11 + idy * 12 * lda]; 

	lB[idx][0 + idy * 12] = B[idx + idy * 12 * NB]; 
	lB[idx][1 + idy * 12] = B[idx + NB + idy * 12 * NB]; 
	lB[idx][2 + idy * 12] = B[idx + NB * 2 + idy * 12 * NB]; 
	lB[idx][3 + idy * 12] = B[idx + NB * 3 + idy * 12 * NB]; 
	lB[idx][4 + idy * 12] = B[idx + NB * 4 + idy * 12 * NB]; 
	lB[idx][5 + idy * 12] = B[idx + NB * 5 + idy * 12 * NB]; 
	lB[idx][6 + idy * 12] = B[idx + NB * 6 + idy * 12 * NB]; 
	lB[idx][7 + idy * 12] = B[idx + NB * 7 + idy * 12 * NB]; 
	lB[idx][8 + idy * 12] = B[idx + NB * 8 + idy * 12 * NB]; 
	lB[idx][9 + idy * 12] = B[idx + NB * 9 + idy * 12 * NB]; 
	lB[idx][10 + idy * 12] = B[idx + NB * 10 + idy * 12 * NB]; 
	lB[idx][11 + idy * 12] = B[idx + NB * 11 + idy * 12 * NB]; 
	barrier(CLK_LOCAL_MEM_FENCE); 

	//do math

	uint i = 0; 

	do{ 
		privateC[0] = mad(lA[idx][i], lB[i][0 + idy * 12], privateC[0]); 
		privateC[1] = mad(lA[idx][i], lB[i][1 + idy * 12], privateC[1]); 
		privateC[2] = mad(lA[idx][i], lB[i][2 + idy * 12], privateC[2]); 
		privateC[3] = mad(lA[idx][i], lB[i][3 + idy * 12], privateC[3]); 
		privateC[4] = mad(lA[idx][i], lB[i][4 + idy * 12], privateC[4]); 
		privateC[5] = mad(lA[idx][i], lB[i][5 + idy * 12], privateC[5]); 
		privateC[6] = mad(lA[idx][i], lB[i][6 + idy * 12], privateC[6]); 
		privateC[7] = mad(lA[idx][i], lB[i][7 + idy * 12], privateC[7]); 
		privateC[8] = mad(lA[idx][i], lB[i][8 + idy * 12], privateC[8]); 
		privateC[9] = mad(lA[idx][i], lB[i][9 + idy * 12], privateC[9]); 
		privateC[10] = mad(lA[idx][i], lB[i][10 + idy * 12], privateC[10]); 
		privateC[11] = mad(lA[idx][i], lB[i][11 + idy * 12], privateC[11]); 
		i = i + 1; 
	} while (i < 24); 

	i = 0; 
	do{ 
		C[NB*idy * 12 + NB*i + idx] = privateC[i]; 
		i = i + 1; 
	} while (i < 12); 
}
// end of kernel
);
#endif
