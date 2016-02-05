/*******************************************************************************
 * Hand-tuned kernel
 
 * B21 = -inv(A11)*A12*inv(A22)
 * 16 to 32
 
 ******************************************************************************/

#ifndef KERNEL_TRIPLE_DGEMM_UPDATE_128_16_R_SRC_CPP
#define KERNEL_TRIPLE_DGEMM_UPDATE_128_16_R_SRC_CPP
#pragma message("#define KERNEL_TRIPLE_DGEMM_UPDATE_128_16_R_SRC_CPP.")

#ifndef STRINGIFY
#define STRINGIFY2(...) #__VA_ARGS__
#define STRINGIFY(...) STRINGIFY2(__VA_ARGS__)
#endif

unsigned char *triple_dgemm_update_128_16_R_bin = 0;
size_t triple_dgemm_update_128_16_R_binSize = 0;

const char * const triple_dgemm_update_128_16_R_src = STRINGIFY(
static void daxpy(
double alpha, 
__local const double * __restrict__ b, 
double * __restrict__ c)
{ 
	c[0] += alpha * b[0]; 
	c[1] += alpha * b[1]; 
	c[2] += alpha * b[2]; 
	c[3] += alpha * b[3]; 
	c[4] += alpha * b[4]; 
	c[5] += alpha * b[5]; 
	c[6] += alpha * b[6]; 
	c[7] += alpha * b[7]; 
	c[8] += alpha * b[8]; 
	c[9] += alpha * b[9]; 
	c[10] += alpha * b[10]; 
	c[11] += alpha * b[11]; 
	c[12] += alpha * b[12]; 
	c[13] += alpha * b[13]; 
	c[14] += alpha * b[14]; 
	c[15] += alpha * b[15]; 
}
#define NB 128


	__kernel void TRIPLE_DGEMM_UPDATE_128_16_R(__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, uint lda, int npages, int na)
{
const int bIdy = get_group_id(1) / npages;
//const int page = (blockIdx.y)%(npages);
const int page = (get_group_id(1) * npages);
const int inx = get_local_id(0); 
const int iny = get_local_id(1); 
const int ibx = get_group_id(0) * (get_local_size(0)*get_local_size(1)); 
const int iby = bIdy * 16; 
const int id = inx + iny*get_local_size(0); 
__local double bs[16][17]; 

Ain = Ain + offAin; 

int PagesPerNB = NB / (blk * 2); 
//--------------------------part one---------------------------//
{ 
	// A12*inv(A22) -> A12
	// A=A12, B=inv(A22), C=A12(d_dinvA)
	__global const double *A; 
	__global double *B, *C; 
	int ldb = NB; 
	int ldc = NB; 

	d_dinvA += NB*NB*(page / PagesPerNB)
		+ ((page % PagesPerNB))*(blk * 2)*NB
		+ ((page % PagesPerNB))*(blk * 2); 

	int xa = page*blk * 2 + ibx + id; 
	int ya = page*blk * 2 + blk; 
	int incA = ya * lda + xa; 

	// maxA will be used to detect overflow on all subsequent accesses on A(xa, ya:ya+???) 

	int maxA; 
	if (xa < na)
		maxA = lda*na;  // macro READA will detect overflow on y dimension 
	else
		maxA = 0;  // there is already an overflow on xa 

#define READA ( (incA < maxA ) ? Ain[incA] : 0 )  

	B = d_dinvA + blk*NB + blk; 
	C = d_dinvA + blk*NB; 

	B += inx + ((iby + iny) * ldb); 
	C += ibx + id + (iby * ldc); 

	__global double *Blast = B + blk; 

	double c[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; 

	do {
		double a[4]; 
		a[0] = ((incA < maxA) ? Ain[incA] : 0); incA += lda; 
		a[1] = ((incA < maxA) ? Ain[incA] : 0); incA += lda; 
		a[2] = ((incA < maxA) ? Ain[incA] : 0); incA += lda; 
		a[3] = ((incA < maxA) ? Ain[incA] : 0); incA += lda; 

		bs[inx][iny] = B[0 * ldb]; 
		bs[inx][iny + 4] = B[4 * ldb]; 
		bs[inx][iny + 8] = B[8 * ldb]; 
		bs[inx][iny + 12] = B[12 * ldb]; 
		bs[inx + 4][iny] = B[4 + 0 * ldb]; 
		bs[inx + 4][iny + 4] = B[4 + 4 * ldb]; 
		bs[inx + 4][iny + 8] = B[4 + 8 * ldb]; 
		bs[inx + 4][iny + 12] = B[4 + 12 * ldb]; 
		bs[inx + 8][iny] = B[8 + 0 * ldb]; 
		bs[inx + 8][iny + 4] = B[8 + 4 * ldb]; 
		bs[inx + 8][iny + 8] = B[8 + 8 * ldb]; 
		bs[inx + 8][iny + 12] = B[8 + 12 * ldb]; 
		bs[inx + 12][iny] = B[12 + 0 * ldb]; 
		bs[inx + 12][iny + 4] = B[12 + 4 * ldb]; 
		bs[inx + 12][iny + 8] = B[12 + 8 * ldb]; 
		bs[inx + 12][iny + 12] = B[12 + 12 * ldb]; 
		//__syncthreads();
		barrier(CLK_LOCAL_MEM_FENCE); 

		daxpy(a[0], &bs[0][0], c);  a[0] = ((incA < maxA) ? Ain[incA] : 0); incA += lda; 
		daxpy(a[1], &bs[1][0], c);  a[1] = ((incA < maxA) ? Ain[incA] : 0); incA += lda; 
		daxpy(a[2], &bs[2][0], c);  a[2] = ((incA < maxA) ? Ain[incA] : 0); incA += lda; 
		daxpy(a[3], &bs[3][0], c);  a[3] = ((incA < maxA) ? Ain[incA] : 0); incA += lda; 

		daxpy(a[0], &bs[4][0], c);  a[0] = ((incA < maxA) ? Ain[incA] : 0); incA += lda; 
		daxpy(a[1], &bs[5][0], c);  a[1] = ((incA < maxA) ? Ain[incA] : 0); incA += lda; 
		daxpy(a[2], &bs[6][0], c);  a[2] = ((incA < maxA) ? Ain[incA] : 0); incA += lda; 
		daxpy(a[3], &bs[7][0], c);  a[3] = ((incA < maxA) ? Ain[incA] : 0); incA += lda; 

		daxpy(a[0], &bs[8][0], c);  a[0] = ((incA < maxA) ? Ain[incA] : 0); incA += lda; 
		daxpy(a[1], &bs[9][0], c);  a[1] = ((incA < maxA) ? Ain[incA] : 0); incA += lda; 
		daxpy(a[2], &bs[10][0], c);  a[2] = ((incA < maxA) ? Ain[incA] : 0); incA += lda; 
		daxpy(a[3], &bs[11][0], c);  a[3] = ((incA < maxA) ? Ain[incA] : 0); incA += lda; 

		daxpy(a[0], &bs[12][0], c); 
		daxpy(a[1], &bs[13][0], c); 
		daxpy(a[2], &bs[14][0], c); 
		daxpy(a[3], &bs[15][0], c); 

		B += 16; 
		//__syncthreads();
		barrier(CLK_LOCAL_MEM_FENCE); 
	} while (B < Blast); 

	for (int i = 0; i < 16; i++) {
		C[0] = c[i]; 
		C += ldc; 
	}
}
//__syncthreads();
barrier(CLK_LOCAL_MEM_FENCE); 

#undef READA

//--------------------------part two---------------------------//
{
	// -inv(A11)*A12 -> A12
	// A=inv(A11), B=A12, C=A12
	__global double *A, *B, *C; 
	int lda = NB; 
	int ldb = NB; 
	int ldc = NB; 

	A = d_dinvA; 
	B = C = d_dinvA + blk*NB; 

	A += ibx + id; 
	B += inx + ((iby + iny) * ldb); 
	C += ibx + id + (iby * ldc); 

	__global double *Blast = B + blk; 

	double c[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; 

	do {
		double a[4] = { A[0 * lda], A[1 * lda], A[2 * lda], A[3 * lda] }; 

		bs[inx][iny] = B[0 * ldb]; 
		bs[inx][iny + 4] = B[4 * ldb]; 
		bs[inx][iny + 8] = B[8 * ldb]; 
		bs[inx][iny + 12] = B[12 * ldb]; 
		bs[inx + 4][iny] = B[4 + 0 * ldb]; 
		bs[inx + 4][iny + 4] = B[4 + 4 * ldb]; 
		bs[inx + 4][iny + 8] = B[4 + 8 * ldb]; 
		bs[inx + 4][iny + 12] = B[4 + 12 * ldb]; 
		bs[inx + 8][iny] = B[8 + 0 * ldb]; 
		bs[inx + 8][iny + 4] = B[8 + 4 * ldb]; 
		bs[inx + 8][iny + 8] = B[8 + 8 * ldb]; 
		bs[inx + 8][iny + 12] = B[8 + 12 * ldb]; 
		bs[inx + 12][iny] = B[12 + 0 * ldb]; 
		bs[inx + 12][iny + 4] = B[12 + 4 * ldb]; 
		bs[inx + 12][iny + 8] = B[12 + 8 * ldb]; 
		bs[inx + 12][iny + 12] = B[12 + 12 * ldb]; 
		//__syncthreads();
		barrier(CLK_LOCAL_MEM_FENCE); 

		A += 4 * lda; 
		daxpy(a[0], &bs[0][0], c);  a[0] = A[0 * lda]; 
		daxpy(a[1], &bs[1][0], c);  a[1] = A[1 * lda]; 
		daxpy(a[2], &bs[2][0], c);  a[2] = A[2 * lda]; 
		daxpy(a[3], &bs[3][0], c);  a[3] = A[3 * lda]; 

		A += 4 * lda; 
		daxpy(a[0], &bs[4][0], c);  a[0] = A[0 * lda]; 
		daxpy(a[1], &bs[5][0], c);  a[1] = A[1 * lda]; 
		daxpy(a[2], &bs[6][0], c);  a[2] = A[2 * lda]; 
		daxpy(a[3], &bs[7][0], c);  a[3] = A[3 * lda]; 

		A += 4 * lda; 
		daxpy(a[0], &bs[8][0], c);  a[0] = A[0 * lda]; 
		daxpy(a[1], &bs[9][0], c);  a[1] = A[1 * lda]; 
		daxpy(a[2], &bs[10][0], c);  a[2] = A[2 * lda]; 
		daxpy(a[3], &bs[11][0], c);  a[3] = A[3 * lda]; 

		A += 4 * lda; 
		daxpy(a[0], &bs[12][0], c); 
		daxpy(a[1], &bs[13][0], c); 
		daxpy(a[2], &bs[14][0], c); 
		daxpy(a[3], &bs[15][0], c); 

		B += 16; 
		//__syncthreads();
		barrier(CLK_LOCAL_MEM_FENCE); 
	} while (B < Blast); 

	for (int i = 0; i < 16; i++) {
		C[0] = (-1)*c[i]; 
		C += ldc; 
	}
}
}
// end of kernel
);
#endif
