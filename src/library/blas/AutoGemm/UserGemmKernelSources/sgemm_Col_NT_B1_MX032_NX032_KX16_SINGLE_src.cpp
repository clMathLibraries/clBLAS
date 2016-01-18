/*******************************************************************************
 * Hand-tuned kernel
 * below kernels work with an assumption: after the main matrix being computed by kernels with 64x64 micro tile size, the boundary are of size 32.
 * Thus, M and N are of mod32 and not necessarily of mod64.
 ******************************************************************************/

#ifndef KERNEL_SGEMM_COL_NT_B1_MX032_NX032_KX16_SINGLE_SRC_H
#define KERNEL_SGEMM_COL_NT_B1_MX032_NX032_KX16_SINGLE_SRC_H
#pragma message("AutoGemm's sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_src (if exists) overriden by user.")
#include "UserGemmKernelSourceIncludes.h"

#ifndef STRINGIFY
#define STRINGIFY(S) STRINGIFY2(S)
#define STRINGIFY2(S) #S
#endif

const unsigned int sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_workGroupNumRows = 16;
const unsigned int sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_workGroupNumCols = 16;
const unsigned int sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_microTileNumRows = 2;
const unsigned int sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_microTileNumCols = 2;
const unsigned int sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_unroll = 16;

#ifndef AUTOGEMM_USE_PRE_COMPILED_KERNELS
unsigned char *sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_bin = 0;
size_t sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_binSize = 0;
#endif

const char * const sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_src = STRINGIFY(

#define  M2x2 \
            rA[0][0] = lA[offA + 0];				  \
            rA[0][1] = lA[offA + 16];				  \
            rB[0][0] = lB[offB + 0];				  \
            rB[0][1] = lB[offB + 16];				  \
            offA += 33;								  \
            offB += 33;								  \
            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]); \
            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]); \
            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]); \
            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]); \
            rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]); \
            mem_fence(CLK_LOCAL_MEM_FENCE);\n

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE (
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
	float rC[2][2] = { (float)0 };
	float rA[1][2];
	float rB[1][2];


	A += offsetA;
	B += offsetB;
	C += offsetC;

	__local float lA[528];
	__local float lB[528];

	uint gidx = M / 64;//get_group_id(0);
	uint gidy = N / 64;//get_group_id(1);
	uint idx = get_local_id(0);
	uint idy = get_local_id(1);

	int CurrentOffSetA = gidx * 64 + idx;
	int CurrentOffSetB = gidy * 64 + idx;

	A += gidx * 64 + idx + idy*lda;
	B += gidy * 64 + idx + idy*ldb;


	uint block_k = K >> 4;
	do
	{
		__local float* plA = lA + idy * 33 + idx;
		__local float* plB = lB + idy * 33 + idx;
		barrier(CLK_LOCAL_MEM_FENCE);

		//plB[0]  = CurrentOffSetB>=N?0.0:B[0];
		//plB[16] = CurrentOffSetB+16>=N?0.0:B[16];
		//plB[32] = CurrentOffSetB+32>=N?0.0:B[32];
		//plB[48] = CurrentOffSetB+48>=N?0.0:B[48];
		plB[0] = B[0];
		plB[16] = B[16];

		//plA[0]  = CurrentOffSetA>=M?0.0:A[0];
		//plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
		//plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
		//plA[48] = CurrentOffSetA+48>=M?0.0:A[48];
		plA[0] = A[0];
		plA[16] = A[16];

		barrier(CLK_LOCAL_MEM_FENCE);
		uint offA = idx;
		uint offB = idy;


		M2x2
			M2x2
			M2x2
			M2x2
			M2x2
			M2x2
			M2x2
			M2x2
			M2x2
			M2x2
			M2x2
			M2x2
			M2x2
			M2x2
			M2x2
			M2x2

			A += lda << 4;
		B += ldb << 4;
	} while (--block_k > 0);


	int offset_x = gidx * 64 + idx;
	int offset_y = gidy * 64 + idy;

	C += offset_x + offset_y*ldc;

	int i = 0;
    if (beta != 0) {
      do
      {
        C[0] = mad(alpha, rC[i][0], beta*C[0]);
        C[16 * ldc] = mad(alpha, rC[i][1], beta*C[16 * ldc]);
        C += 16;
        offset_x += 16;
      } while (++i < 2);
    } else {
      do
      {
        C[0] = alpha * rC[i][0];
        C[16 * ldc] = alpha * rC[i][1];
        C += 16;
        offset_x += 16;
      } while (++i < 2);
    }

}
);
#endif
