/*******************************************************************************
 * Hand-tuned kernel
 * part 3: copy data back to position
 *
 ******************************************************************************/

#ifndef KERNEL_TRIPLE_DGEMM_UPDATE_128_ABOVE64_PART3_L_SRC_CPP
#define KERNEL_TRIPLE_DGEMM_UPDATE_128_ABOVE64_PART3_L_SRC_CPP
#pragma message("#define KERNEL_TRIPLE_DGEMM_UPDATE_128_ABOVE64_PART3_L_SRC_CPP.")

#ifndef STRINGIFY
#define STRINGIFY2(...) #__VA_ARGS__
#define STRINGIFY(...) STRINGIFY2(__VA_ARGS__)
#endif

unsigned char *triple_dgemm_update_128_ABOVE64_PART3_L_bin = 0;
size_t triple_dgemm_update_128_ABOVE64_PART3_L_binSize = 0;

const char * const triple_dgemm_update_128_ABOVE64_PART3_L_src = STRINGIFY(
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

__kernel void TRIPLE_DGEMM_UPDATE_128_ABOVE64_PART3_L(__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
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

//--------------------------part three---------------------------//
{
	// -inv(A22)*A21 -> A21
	// A=inv(A22), B=A21, C=A21
	__global double *C_temp, *C_real; 
	int ldc = NB; 

	d_dinvA += NB*NB*(page / PagesPerNB)
		+ ((page % PagesPerNB))*(blk * 2)*NB
		+ ((page % PagesPerNB))*(blk * 2); 

	C_real = d_dinvA + blk;

	C_temp = d_dinvA + blk*NB; 

	C_temp += ibx + id + (iby * ldc); 
	C_real += ibx + id + (iby * ldc); 

	for (int i = 0; i < 16; i++) {
		C_real[0] = C_temp[0]; 
		C_temp[0] = ZERO; 
		C_real += ldc; 
		C_temp += ldc; 
	}
}
//__syncthreads();
barrier(CLK_LOCAL_MEM_FENCE); 
}
// end of kernel
);
#endif
