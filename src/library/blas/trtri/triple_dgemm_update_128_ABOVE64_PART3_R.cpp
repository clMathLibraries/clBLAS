/*******************************************************************************
 * Hand-tuned kernel
 *
 *
 * part 3, copy data into position
 *
 ******************************************************************************/

#ifndef KERNEL_TRIPLE_DGEMM_UPDATE_128_ABOVE64_PART3_R_SRC_CPP
#define KERNEL_TRIPLE_DGEMM_UPDATE_128_ABOVE64_PART3_R_SRC_CPP
#pragma message("#define KERNEL_TRIPLE_DGEMM_UPDATE_128_ABOVE64_PART3_R_SRC_CPP.")

#ifndef STRINGIFY
#define STRINGIFY2(...) #__VA_ARGS__
#define STRINGIFY(...) STRINGIFY2(__VA_ARGS__)
#endif

unsigned char *triple_dgemm_update_128_ABOVE64_PART3_R_bin = 0;
size_t triple_dgemm_update_128_ABOVE64_PART3_R_binSize = 0;

const char * const triple_dgemm_update_128_ABOVE64_PART3_R_src = STRINGIFY(
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
#define ZERO			  ( 0.0) 
#define ONE			   ( 1.0) 

__kernel void TRIPLE_DGEMM_UPDATE_128_ABOVE64_PART3_R(__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
const int bIdy = get_group_id(1) / npages;
const int page = (get_group_id(1) % npages); 
const int inx = get_local_id(0); 
const int iny = get_local_id(1); 
const int ibx = get_group_id(0) * 64;
const int iby = bIdy * 16; 
const int id = inx + iny * 16; 

Ain = Ain + offAin; 

int PagesPerNB = NB / (blk * 2); 

//--------------------------part two---------------------------//
{
	// -inv(A11)*A12 -> A12
	// A=inv(A11), B=A12, C=A12
	__global double *C_temp, *C_real; 
	int ldc = NB; 

	C_temp = d_dinvA + NB*NB*(page / PagesPerNB)
		+ ((page % PagesPerNB))*(blk * 2)*NB
		+ ((page % PagesPerNB))*(blk * 2)
		+ blk; 

	C_real = d_dinvA + NB*NB*(page / PagesPerNB)
		+ ((page % PagesPerNB))*(blk * 2)*NB
		+ blk*NB
		+ ((page % PagesPerNB))*(blk * 2); 

	C_temp += ibx + id + (iby * ldc); 
	C_real += ibx + id + (iby * ldc); 

	for (int i = 0; i < 16; i++) {
		C_real[0] = C_temp[0]; 
		C_temp[0] = ZERO; 
		C_temp += ldc; 
		C_real += ldc; 
	}
}

}
// end of kernel
);
#endif
