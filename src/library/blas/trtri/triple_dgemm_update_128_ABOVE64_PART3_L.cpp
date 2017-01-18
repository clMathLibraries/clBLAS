/*******************************************************************************
 * Hand-tuned kernel
 * part 3: copy data back to position
 *
 ******************************************************************************/

#ifndef KERNEL_TRIPLE_DGEMM_UPDATE_128_ABOVE64_PART3_L_SRC_CPP
#define KERNEL_TRIPLE_DGEMM_UPDATE_128_ABOVE64_PART3_L_SRC_CPP

#ifndef STRINGIFY
#define STRINGIFY2(...) #__VA_ARGS__
#define STRINGIFY(...) STRINGIFY2(__VA_ARGS__)
#endif

unsigned char *triple_dgemm_update_128_ABOVE64_PART3_L_bin = 0;
size_t triple_dgemm_update_128_ABOVE64_PART3_L_binSize = 0;

const char * const triple_dgemm_update_128_ABOVE64_PART3_L_src = STRINGIFY(
	static void daxpy(\n
double alpha, \n
__local const double * __restrict__ b, \n
double * __restrict__ c)\n
{ \n
    c[0] += alpha * b[0]; \n
    c[1] += alpha * b[1]; \n
    c[2] += alpha * b[2]; \n
    c[3] += alpha * b[3]; \n
	c[4] += alpha * b[4]; \n
	c[5] += alpha * b[5]; \n
	c[6] += alpha * b[6]; \n
	c[7] += alpha * b[7]; \n
	c[8] += alpha * b[8]; \n
	c[9] += alpha * b[9]; \n
	c[10] += alpha * b[10]; \n
	c[11] += alpha * b[11]; \n
	c[12] += alpha * b[12]; \n
	c[13] += alpha * b[13]; \n
	c[14] += alpha * b[14]; \n
	c[15] += alpha * b[15]; \n
}\n
#define NB 128\n
#define ZERO              ( 0.0) \n
#define ONE               ( 1.0) \n
#define __mul(i,j) ((i)*(j))\n
#define qmod(a, b) ((a)%(b))\n
__kernel void TRIPLE_DGEMM_UPDATE_128_ABOVE64_PART3_L(__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)\n
{\n
const int bIdy = get_group_id(1) / npages; \n
const int page = qmod(get_group_id(1), npages); \n
const int inx = get_local_id(0); \n
const int iny = get_local_id(1); \n
const int ibx = get_group_id(0) * 64; \n
const int iby = bIdy * 16; \n
const int id = inx + iny * 16; \n

Ain = Ain + offAin; \n

int PagesPerNB = NB / (blk * 2); \n

//--------------------------part three---------------------------//
{
	// -inv(A22)*A21 -> A21
	// A=inv(A22), B=A21, C=A21
	__global double *C_temp, *C_real; \n
	int ldc = NB; \n

	d_dinvA += NB*NB*(page / PagesPerNB)
		+ (qmod(page, PagesPerNB))*(blk * 2)*NB
		+ (qmod(page, PagesPerNB))*(blk * 2); \n

	C_real = d_dinvA + blk;\n

	C_temp = d_dinvA + blk*NB; \n

	C_temp += ibx + id + __mul(iby, ldc); \n
	C_real += ibx + id + __mul(iby, ldc); \n

	for (int i = 0; i < 16; i++) {\n
		C_real[0] = C_temp[0]; \n
		C_temp[0] = ZERO; \n
		C_real += ldc; \n
		C_temp += ldc; \n
	}\n
}\n
//__syncthreads();
barrier(CLK_LOCAL_MEM_FENCE); \n
}\n
// end of kernel
);
#endif
