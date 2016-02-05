/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_TRIPLE_DGEMM_UPDATE_192_96_PART2_R_SRC_CPP
#define KERNEL_TRIPLE_DGEMM_UPDATE_192_96_PART2_R_SRC_CPP
#pragma message("#define KERNEL_TRIPLE_DGEMM_UPDATE_192_96_PART2_R_SRC_CPP.")

#ifndef STRINGIFY
#define STRINGIFY2(...) #__VA_ARGS__
#define STRINGIFY(...) STRINGIFY2(__VA_ARGS__)
#endif

unsigned char *triple_dgemm_update_192_96_PART2_R_bin = 0;
size_t triple_dgemm_update_192_96_PART2_R_binSize = 0;

const char * const triple_dgemm_update_192_96_PART2_R_src = STRINGIFY(
#define NB 192
	__kernel void TRIPLE_DGEMM_UPDATE_192_96_PART2_R(__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{ 
	// Ain is the non inverse matrix; the size of Ain is lda * na
	// offAin is the offset of Ain
	// d_dinvA is the inversed matrix. the size of d_invA is NB * (na-1)/NB + 1
	// blk is subblock size, which is 48 here.
	// lda in leading dimension. Column major here
	// npages = (na-1)/12*2 + 1; for 96 this is 1 for 192 this is 2

	//Work group size is [24, 2]
	//global work size is [48*number of blocks, 4]
	//each work item in each work group is responsible for 12 elements (1/4) in that row
	//each work group is responsible for 24 by 24 macro tile;

	////////////// -invA11*invA12
	const uint gidx = get_group_id(0); 
	const uint gidy = get_group_id(1); 
	const uint idx = get_local_id(0); 
	const uint idy = get_local_id(1); 

	//uint page = gidx / 2;//0-1 for 192; 0 for 96
	//const uint page = (gidx/2)%2;//index of page within a page_block; 1 pages per page_block
	const uint page_block = gidx / 4; //#index of page_block; 4 WG per page; 4 WG per page_block

	__global double *A, *B, *C; 
	__local double lA[24][48]; 
	__local double lB[48][24]; 
	double privateC[12] = { (double)0 }; 

	//decide invA11 location for each page
	//each workgroup loads half of A (left or right)
	//A = d_dinvA + page*NB*NB + gidx%2*(blk/2);
	A = d_dinvA + page_block*NB*NB + gidx % 4 * (blk / 4); 

	//decide invA12 (B) location for each page
	//actually it was saved in invA21 from last kernel
	//each workgroup loads half of B (up or down)
	//B = d_dinvA + page*NB*NB + blk*NB + gidy*(blk/2)*NB;
	B = d_dinvA + page_block*NB*NB + blk*NB + gidy*(blk / 4)*NB; 

	//decide invA12 location for each page
	//each workgroup writes 1/4 of C
	//C = d_dinvA + page*NB*NB + blk * NB + gidx%2*(blk/2) + gidy*(blk/2)*NB;
	C = d_dinvA + page_block*NB*NB + blk*NB + gidx % 4 * (blk / 4) + gidy*(blk / 4)*NB; 

	//read A and B into LDS no transpose operated here
	//each work item loads a half row of A and half column of B
	//idx 0-23 idy 0-1

	uint block_k = blk / 48;  //thus we need 2 iterations here
	do{
		barrier(CLK_LOCAL_MEM_FENCE); 
		lA[idx][0 + idy * 24] = A[idx + idy * 24 * NB]; 
		lA[idx][1 + idy * 24] = A[idx + NB + idy * 24 * NB]; 
		lA[idx][2 + idy * 24] = A[idx + NB * 2 + idy * 24 * NB];
		lA[idx][3 + idy * 24] = A[idx + NB * 3 + idy * 24 * NB];
		lA[idx][4 + idy * 24] = A[idx + NB * 4 + idy * 24 * NB];
		lA[idx][5 + idy * 24] = A[idx + NB * 5 + idy * 24 * NB];
		lA[idx][6 + idy * 24] = A[idx + NB * 6 + idy * 24 * NB];
		lA[idx][7 + idy * 24] = A[idx + NB * 7 + idy * 24 * NB];
		lA[idx][8 + idy * 24] = A[idx + NB * 8 + idy * 24 * NB];
		lA[idx][9 + idy * 24] = A[idx + NB * 9 + idy * 24 * NB];
		lA[idx][10 + idy * 24] = A[idx + NB * 10 + idy * 24 * NB];
		lA[idx][11 + idy * 24] = A[idx + NB * 11 + idy * 24 * NB];
		lA[idx][12 + idy * 24] = A[idx + NB * 12 + idy * 24 * NB];
		lA[idx][13 + idy * 24] = A[idx + NB * 13 + idy * 24 * NB];
		lA[idx][14 + idy * 24] = A[idx + NB * 14 + idy * 24 * NB];
		lA[idx][15 + idy * 24] = A[idx + NB * 15 + idy * 24 * NB];
		lA[idx][16 + idy * 24] = A[idx + NB * 16 + idy * 24 * NB];
		lA[idx][17 + idy * 24] = A[idx + NB * 17 + idy * 24 * NB];
		lA[idx][18 + idy * 24] = A[idx + NB * 18 + idy * 24 * NB];
		lA[idx][19 + idy * 24] = A[idx + NB * 19 + idy * 24 * NB];
		lA[idx][20 + idy * 24] = A[idx + NB * 20 + idy * 24 * NB];
		lA[idx][21 + idy * 24] = A[idx + NB * 21 + idy * 24 * NB];
		lA[idx][22 + idy * 24] = A[idx + NB * 22 + idy * 24 * NB];
		lA[idx][23 + idy * 24] = A[idx + NB * 23 + idy * 24 * NB];

		lB[0 + idy * 24][idx] = B[idx*NB + idy * 24]; 
		lB[1 + idy * 24][idx] = B[idx*NB + idy * 24 + 1]; 
		lB[2 + idy * 24][idx] = B[idx*NB + idy * 24 + 2];
		lB[3 + idy * 24][idx] = B[idx*NB + idy * 24 + 3];
		lB[4 + idy * 24][idx] = B[idx*NB + idy * 24 + 4];
		lB[5 + idy * 24][idx] = B[idx*NB + idy * 24 + 5];
		lB[6 + idy * 24][idx] = B[idx*NB + idy * 24 + 6];
		lB[7 + idy * 24][idx] = B[idx*NB + idy * 24 + 7];
		lB[8 + idy * 24][idx] = B[idx*NB + idy * 24 + 8];
		lB[9 + idy * 24][idx] = B[idx*NB + idy * 24 + 9];
		lB[10 + idy * 24][idx] = B[idx*NB + idy * 24 + 10];
		lB[11 + idy * 24][idx] = B[idx*NB + idy * 24 + 11];
		lB[12 + idy * 24][idx] = B[idx*NB + idy * 24 + 12];
		lB[13 + idy * 24][idx] = B[idx*NB + idy * 24 + 13];
		lB[14 + idy * 24][idx] = B[idx*NB + idy * 24 + 14];
		lB[15 + idy * 24][idx] = B[idx*NB + idy * 24 + 15];
		lB[16 + idy * 24][idx] = B[idx*NB + idy * 24 + 16];
		lB[17 + idy * 24][idx] = B[idx*NB + idy * 24 + 17];
		lB[18 + idy * 24][idx] = B[idx*NB + idy * 24 + 18];
		lB[19 + idy * 24][idx] = B[idx*NB + idy * 24 + 19];
		lB[20 + idy * 24][idx] = B[idx*NB + idy * 24 + 20];
		lB[21 + idy * 24][idx] = B[idx*NB + idy * 24 + 21];
		lB[22 + idy * 24][idx] = B[idx*NB + idy * 24 + 22];
		lB[23 + idy * 24][idx] = B[idx*NB + idy * 24 + 23];
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
		} while (i < 48); 

		A += 48 * NB; 
		B += 48; 

	} while (--block_k>0); 

	uint i = 0; 
	do{
		C[NB*idy * 12 + NB*i + idx] = -1 * privateC[i]; 
		i = i + 1; 
	} while (i < 12); 


}
// end of kernel
);
#endif
