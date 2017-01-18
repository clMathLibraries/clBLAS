/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_SGEMM_COL_NT_B1_MX128_NX128_KX16_SRC_H
#define KERNEL_SGEMM_COL_NT_B1_MX128_NX128_KX16_SRC_H
// #pragma message("AutoGemm's sgemm_Col_NT_B1_MX128_NX128_KX16_src (if exists) overriden by user.")

#include "UserGemmKernelSourceIncludes.h"

#ifndef STRINGIFY
#define STRINGIFY(S) STRINGIFY2(S)
#define STRINGIFY2(S) #S
#endif

const unsigned int sgemm_Col_NT_B1_MX128_NX128_KX16_workGroupNumRows = 16;
const unsigned int sgemm_Col_NT_B1_MX128_NX128_KX16_workGroupNumCols = 16;
const unsigned int sgemm_Col_NT_B1_MX128_NX128_KX16_microTileNumRows = 8;
const unsigned int sgemm_Col_NT_B1_MX128_NX128_KX16_microTileNumCols = 8;
const unsigned int sgemm_Col_NT_B1_MX128_NX128_KX16_unroll = 16;

//if precompiled is enabled. All hand tuned kerenls should be precompiled.
#ifndef AUTOGEMM_USE_PRE_COMPILED_KERNELS
unsigned char *sgemm_Col_NT_B1_MX128_NX128_KX16_bin = 0;
size_t sgemm_Col_NT_B1_MX128_NX128_KX16_binSize = 0;
#endif

const char * const sgemm_Col_NT_B1_MX128_NX128_KX16_src = STRINGIFY(

#define  M8x8 \
            rA[0][0] = lA[offA + 0];				  \
            rA[0][1] = lA[offA + 16];				  \
            rA[0][2] = lA[offA + 32];				  \
            rA[0][3] = lA[offA + 48];				  \
            rA[0][4] = lA[offA + 64];				  \
            rA[0][5] = lA[offA + 80];				  \
            rA[0][6] = lA[offA + 96];				  \
            rA[0][7] = lA[offA + 112];				  \
            rB[0][0] = lB[offB + 0];				  \
            rB[0][1] = lB[offB + 16];				  \
            rB[0][2] = lB[offB + 32];				  \
            rB[0][3] = lB[offB + 48];				  \
            rB[0][4] = lB[offB + 64];				  \
            rB[0][5] = lB[offB + 80];				  \
            rB[0][6] = lB[offB + 96];				  \
            rB[0][7] = lB[offB + 112];				  \
            offA += 129;							  \
            offB += 129;							  \
            rC[0][0] = mad(rA[0][0],rB[0][0],rC[0][0]); \
            rC[1][0] = mad(rA[0][1],rB[0][0],rC[1][0]); \
            rC[2][0] = mad(rA[0][2],rB[0][0],rC[2][0]); \
            rC[3][0] = mad(rA[0][3],rB[0][0],rC[3][0]); \
            rC[4][0] = mad(rA[0][4],rB[0][0],rC[4][0]); \
            rC[5][0] = mad(rA[0][5],rB[0][0],rC[5][0]); \
            rC[6][0] = mad(rA[0][6],rB[0][0],rC[6][0]); \
            rC[7][0] = mad(rA[0][7],rB[0][0],rC[7][0]); \
            rC[0][1] = mad(rA[0][0], rB[0][1], rC[0][1]); \
            rC[1][1] = mad(rA[0][1], rB[0][1], rC[1][1]); \
            rC[2][1] = mad(rA[0][2], rB[0][1], rC[2][1]); \
            rC[3][1] = mad(rA[0][3], rB[0][1], rC[3][1]); \
            rC[4][1] = mad(rA[0][4], rB[0][1], rC[4][1]); \
            rC[5][1] = mad(rA[0][5], rB[0][1], rC[5][1]); \
            rC[6][1] = mad(rA[0][6], rB[0][1], rC[6][1]); \
            rC[7][1] = mad(rA[0][7], rB[0][1], rC[7][1]); \
            rC[0][2] = mad(rA[0][0], rB[0][2], rC[0][2]); \
            rC[1][2] = mad(rA[0][1], rB[0][2], rC[1][2]); \
            rC[2][2] = mad(rA[0][2], rB[0][2], rC[2][2]); \
            rC[3][2] = mad(rA[0][3], rB[0][2], rC[3][2]); \
            rC[4][2] = mad(rA[0][4], rB[0][2], rC[4][2]); \
            rC[5][2] = mad(rA[0][5], rB[0][2], rC[5][2]); \
            rC[6][2] = mad(rA[0][6], rB[0][2], rC[6][2]); \
            rC[7][2] = mad(rA[0][7], rB[0][2], rC[7][2]); \
            rC[0][3] = mad(rA[0][0], rB[0][3], rC[0][3]); \
            rC[1][3] = mad(rA[0][1], rB[0][3], rC[1][3]); \
            rC[2][3] = mad(rA[0][2], rB[0][3], rC[2][3]); \
            rC[3][3] = mad(rA[0][3], rB[0][3], rC[3][3]); \
            rC[4][3] = mad(rA[0][4], rB[0][3], rC[4][3]); \
            rC[5][3] = mad(rA[0][5], rB[0][3], rC[5][3]); \
            rC[6][3] = mad(rA[0][6], rB[0][3], rC[6][3]); \
            rC[7][3] = mad(rA[0][7], rB[0][3], rC[7][3]); \
            rC[0][4] = mad(rA[0][0], rB[0][4], rC[0][4]); \
            rC[1][4] = mad(rA[0][1], rB[0][4], rC[1][4]); \
            rC[2][4] = mad(rA[0][2], rB[0][4], rC[2][4]); \
            rC[3][4] = mad(rA[0][3], rB[0][4], rC[3][4]); \
            rC[4][4] = mad(rA[0][4], rB[0][4], rC[4][4]); \
            rC[5][4] = mad(rA[0][5], rB[0][4], rC[5][4]); \
            rC[6][4] = mad(rA[0][6], rB[0][4], rC[6][4]); \
            rC[7][4] = mad(rA[0][7], rB[0][4], rC[7][4]); \
            rC[0][5] = mad(rA[0][0], rB[0][5], rC[0][5]); \
            rC[1][5] = mad(rA[0][1], rB[0][5], rC[1][5]); \
            rC[2][5] = mad(rA[0][2], rB[0][5], rC[2][5]); \
            rC[3][5] = mad(rA[0][3], rB[0][5], rC[3][5]); \
            rC[4][5] = mad(rA[0][4], rB[0][5], rC[4][5]); \
            rC[5][5] = mad(rA[0][5], rB[0][5], rC[5][5]); \
            rC[6][5] = mad(rA[0][6], rB[0][5], rC[6][5]); \
            rC[7][5] = mad(rA[0][7], rB[0][5], rC[7][5]); \
            rC[0][6] = mad(rA[0][0], rB[0][6], rC[0][6]); \
            rC[1][6] = mad(rA[0][1], rB[0][6], rC[1][6]); \
            rC[2][6] = mad(rA[0][2], rB[0][6], rC[2][6]); \
            rC[3][6] = mad(rA[0][3], rB[0][6], rC[3][6]); \
            rC[4][6] = mad(rA[0][4], rB[0][6], rC[4][6]); \
            rC[5][6] = mad(rA[0][5], rB[0][6], rC[5][6]); \
            rC[6][6] = mad(rA[0][6], rB[0][6], rC[6][6]); \
            rC[7][6] = mad(rA[0][7], rB[0][6], rC[7][6]); \
            rC[0][7] = mad(rA[0][0], rB[0][7], rC[0][7]); \
            rC[1][7] = mad(rA[0][1], rB[0][7], rC[1][7]); \
            rC[2][7] = mad(rA[0][2], rB[0][7], rC[2][7]); \
            rC[3][7] = mad(rA[0][3], rB[0][7], rC[3][7]); \
            rC[4][7] = mad(rA[0][4], rB[0][7], rC[4][7]); \
            rC[5][7] = mad(rA[0][5], rB[0][7], rC[5][7]); \
            rC[6][7] = mad(rA[0][6], rB[0][7], rC[6][7]); \
            rC[7][7] = mad(rA[0][7], rB[0][7], rC[7][7]); \
            mem_fence(CLK_LOCAL_MEM_FENCE);\n

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_Col_NT_B1_MX128_NX128_KX16(
__global float const * restrict A,
__global float const * restrict B,
__global float * C,
float const alpha,
float const beta,
uint const M,
uint const N,
uint const K,
uint lda,
uint ldb,
uint ldc,
uint offsetA,
uint offsetB,
uint offsetC)
{
	float rC[8][8] = { (float)0 };
	float rA[1][8];
	float rB[1][8];

	A += offsetA;
	B += offsetB;
	C += offsetC;

	__local float lA[2064];
	__local float lB[2064];

	uint gidx = get_group_id(0);
	uint gidy = get_group_id(1);
	uint idx = get_local_id(0);
	uint idy = get_local_id(1);

	uint idt = 16 * idy + idx;
	uint idxT = idt % 16;
	uint idyT = idt / 16;

	A += gidx * 128 + idxT + idyT*lda;
	B += gidy * 128 + idxT + idyT*ldb;


	uint block_k = K >> 4;
	do
	{
		// for(unsigned int block_k=0 ; block_k< K ; block_k+=16)
		//{
		__local float* plA = lA + idyT * 129 + idxT;
		__local float* plB = lB + idyT * 129 + idxT;
		barrier(CLK_LOCAL_MEM_FENCE);
		plB[0] = B[0 + 0 * ldb];
		plB[16] = B[16 + 0 * ldb];
		plB[32] = B[32 + 0 * ldb];
		plB[48] = B[48 + 0 * ldb];
		plB[64] = B[64 + 0 * ldb];
		plB[80] = B[80 + 0 * ldb];
		plB[96] = B[96 + 0 * ldb];
		plB[112] = B[112 + 0 * ldb];

		plA[0] = A[0 + 0 * lda];
		plA[16] = A[16 + 0 * lda];
		plA[32] = A[32 + 0 * lda];
		plA[48] = A[48 + 0 * lda];
		plA[64] = A[64 + 0 * lda];
		plA[80] = A[80 + 0 * lda];
		plA[96] = A[96 + 0 * lda];
		plA[112] = A[112 + 0 * lda];

		barrier(CLK_LOCAL_MEM_FENCE);
		uint offA = idx;
		uint offB = idy;

		//        #pragma unroll 1
		//        for(unsigned int k = 0 ; k < 16; k+=1){
		//        }

		M8x8
			M8x8
			M8x8
			M8x8
			M8x8
			M8x8
			M8x8
			M8x8
			M8x8
			M8x8
			M8x8
			M8x8
			M8x8
			M8x8
			M8x8
			M8x8

			A += lda << 4;
		B += ldb << 4;
		//}
	} while (--block_k > 0);

	C += gidx * 128 + idx;
	C += gidy * 128 * ldc;
	C += idy*ldc;

	C[0 * ldc] = alpha*rC[0][0] + beta*C[0 * ldc];
	C[16 * ldc] = alpha*rC[0][1] + beta*C[16 * ldc];
	C[32 * ldc] = alpha*rC[0][2] + beta*C[32 * ldc];
	C[48 * ldc] = alpha*rC[0][3] + beta*C[48 * ldc];
	C[64 * ldc] = alpha*rC[0][4] + beta*C[64 * ldc];
	C[80 * ldc] = alpha*rC[0][5] + beta*C[80 * ldc];
	C[96 * ldc] = alpha*rC[0][6] + beta*C[96 * ldc];
	C[112 * ldc] = alpha*rC[0][7] + beta*C[112 * ldc];
	C += 16;
	C[0 * ldc] = alpha*rC[1][0] + beta*C[0 * ldc];
	C[16 * ldc] = alpha*rC[1][1] + beta*C[16 * ldc];
	C[32 * ldc] = alpha*rC[1][2] + beta*C[32 * ldc];
	C[48 * ldc] = alpha*rC[1][3] + beta*C[48 * ldc];
	C[64 * ldc] = alpha*rC[1][4] + beta*C[64 * ldc];
	C[80 * ldc] = alpha*rC[1][5] + beta*C[80 * ldc];
	C[96 * ldc] = alpha*rC[1][6] + beta*C[96 * ldc];
	C[112 * ldc] = alpha*rC[1][7] + beta*C[112 * ldc];
	C += 16;
	C[0 * ldc] = alpha*rC[2][0] + beta*C[0 * ldc];
	C[16 * ldc] = alpha*rC[2][1] + beta*C[16 * ldc];
	C[32 * ldc] = alpha*rC[2][2] + beta*C[32 * ldc];
	C[48 * ldc] = alpha*rC[2][3] + beta*C[48 * ldc];
	C[64 * ldc] = alpha*rC[2][4] + beta*C[64 * ldc];
	C[80 * ldc] = alpha*rC[2][5] + beta*C[80 * ldc];
	C[96 * ldc] = alpha*rC[2][6] + beta*C[96 * ldc];
	C[112 * ldc] = alpha*rC[2][7] + beta*C[112 * ldc];
	C += 16;
	C[0 * ldc] = alpha*rC[3][0] + beta*C[0 * ldc];
	C[16 * ldc] = alpha*rC[3][1] + beta*C[16 * ldc];
	C[32 * ldc] = alpha*rC[3][2] + beta*C[32 * ldc];
	C[48 * ldc] = alpha*rC[3][3] + beta*C[48 * ldc];
	C[64 * ldc] = alpha*rC[3][4] + beta*C[64 * ldc];
	C[80 * ldc] = alpha*rC[3][5] + beta*C[80 * ldc];
	C[96 * ldc] = alpha*rC[3][6] + beta*C[96 * ldc];
	C[112 * ldc] = alpha*rC[3][7] + beta*C[112 * ldc];
	C += 16;
	C[0 * ldc] = alpha*rC[4][0] + beta*C[0 * ldc];
	C[16 * ldc] = alpha*rC[4][1] + beta*C[16 * ldc];
	C[32 * ldc] = alpha*rC[4][2] + beta*C[32 * ldc];
	C[48 * ldc] = alpha*rC[4][3] + beta*C[48 * ldc];
	C[64 * ldc] = alpha*rC[4][4] + beta*C[64 * ldc];
	C[80 * ldc] = alpha*rC[4][5] + beta*C[80 * ldc];
	C[96 * ldc] = alpha*rC[4][6] + beta*C[96 * ldc];
	C[112 * ldc] = alpha*rC[4][7] + beta*C[112 * ldc];
	C += 16;
	C[0 * ldc] = alpha*rC[5][0] + beta*C[0 * ldc];
	C[16 * ldc] = alpha*rC[5][1] + beta*C[16 * ldc];
	C[32 * ldc] = alpha*rC[5][2] + beta*C[32 * ldc];
	C[48 * ldc] = alpha*rC[5][3] + beta*C[48 * ldc];
	C[64 * ldc] = alpha*rC[5][4] + beta*C[64 * ldc];
	C[80 * ldc] = alpha*rC[5][5] + beta*C[80 * ldc];
	C[96 * ldc] = alpha*rC[5][6] + beta*C[96 * ldc];
	C[112 * ldc] = alpha*rC[5][7] + beta*C[112 * ldc];
	C += 16;
	C[0 * ldc] = alpha*rC[6][0] + beta*C[0 * ldc];
	C[16 * ldc] = alpha*rC[6][1] + beta*C[16 * ldc];
	C[32 * ldc] = alpha*rC[6][2] + beta*C[32 * ldc];
	C[48 * ldc] = alpha*rC[6][3] + beta*C[48 * ldc];
	C[64 * ldc] = alpha*rC[6][4] + beta*C[64 * ldc];
	C[80 * ldc] = alpha*rC[6][5] + beta*C[80 * ldc];
	C[96 * ldc] = alpha*rC[6][6] + beta*C[96 * ldc];
	C[112 * ldc] = alpha*rC[6][7] + beta*C[112 * ldc];
	C += 16;
	C[0 * ldc] = alpha*rC[7][0] + beta*C[0 * ldc];
	C[16 * ldc] = alpha*rC[7][1] + beta*C[16 * ldc];
	C[32 * ldc] = alpha*rC[7][2] + beta*C[32 * ldc];
	C[48 * ldc] = alpha*rC[7][3] + beta*C[48 * ldc];
	C[64 * ldc] = alpha*rC[7][4] + beta*C[64 * ldc];
	C[80 * ldc] = alpha*rC[7][5] + beta*C[80 * ldc];
	C[96 * ldc] = alpha*rC[7][6] + beta*C[96 * ldc];
	C[112 * ldc] = alpha*rC[7][7] + beta*C[112 * ldc];

}
);
#endif
