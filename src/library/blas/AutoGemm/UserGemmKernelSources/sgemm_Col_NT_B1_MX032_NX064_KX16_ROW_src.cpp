/*******************************************************************************
 * Hand-tuned kernel
 * below kernels work with an assumption: after the main matrix being computed by kernels with 64x64 micro tile size, the boundary are of size 32.
 * Thus, M and N are of mod32 and not necessarily of mod64.
 ******************************************************************************/

#ifndef KERNEL_SGEMM_COL_NT_B1_MX032_NX064_KX16_ROW_SRC_H
#define KERNEL_SGEMM_COL_NT_B1_MX032_NX064_KX16_ROW_SRC_H
#pragma message("AutoGemm's sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_src (if exists) overriden by user.")

#include "UserGemmKernelSourceIncludes.h"

#ifndef STRINGIFY
#define STRINGIFY(S) STRINGIFY2(S)
#define STRINGIFY2(S) #S
#endif

const unsigned int sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_workGroupNumRows = 16;
const unsigned int sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_workGroupNumCols = 16;
const unsigned int sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_microTileNumRows = 2;
const unsigned int sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_microTileNumCols = 4;
const unsigned int sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_unroll = 16;

//if precompiled is enabled. All hand tuned kerenls should be precompiled.
#ifndef AUTOGEMM_USE_PRE_COMPILED_KERNELS
unsigned char *sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_bin = 0;
size_t sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_binSize = 0;
#endif

const char * const sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_src = STRINGIFY(

#define  M2x4 \
            rA[0][0] = lA[offA + 0];				  \
            rA[0][1] = lA[offA + 16];				  \
            rB[0][0] = lB[offB + 0];				  \
            rB[0][1] = lB[offB + 16];				  \
            rB[0][2] = lB[offB + 32];				  \
            rB[0][3] = lB[offB + 48];				  \
            offA += 33;								  \
            offB += 65;								  \
            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]); \
            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]); \
            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]); \
            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]); \
            rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]); \
            rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]); \
            rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]); \
            rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]); \
            mem_fence(CLK_LOCAL_MEM_FENCE);\n

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_Col_NT_B1_MX032_NX064_KX16_ROW (
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
	float rC[2][4] = { (float)0 };
	float rA[1][2];
	float rB[1][4];


	A += offsetA;
	B += offsetB;
	C += offsetC;

	__local float lA[528];//16*32+16
	__local float lB[1040];//16*64+16

	uint gidx = M / 64;//get_group_id(0);
	uint gidy = get_group_id(1);
	uint idx = get_local_id(0);
	uint idy = get_local_id(1);


	int CurrentOffSetA = gidx * 64 + idx;

	A += gidx * 64 + idx + idy*lda;
	B += gidy * 64 + idx + idy*ldb;


	uint block_k = K >> 4;
	do
	{
		__local float* plA = lA + idy * 33 + idx;
		__local float* plB = lB + idy * 65 + idx;
		barrier(CLK_LOCAL_MEM_FENCE);

		plB[0] = B[0 + 0 * ldb];
		plB[16] = B[16 + 0 * ldb];
		plB[32] = B[32 + 0 * ldb];
		plB[48] = B[48 + 0 * ldb];

		//plA[0]  = CurrentOffSetA>=M?0.0:A[0];
		//plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
		//plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
		//plA[48] = CurrentOffSetA+48>=M?0.0:A[48];
		plA[0] = A[0];
		plA[16] = A[16];


		barrier(CLK_LOCAL_MEM_FENCE);
		uint offA = idx;
		uint offB = idy;


		    M2x4
			M2x4
			M2x4
			M2x4
			M2x4
			M2x4
			M2x4
			M2x4
			M2x4
			M2x4
			M2x4
			M2x4
			M2x4
			M2x4
			M2x4
			M2x4

			A += lda << 4;
		    B += ldb << 4;
	} while (--block_k > 0);


	int offset_x = gidx * 64 + idx;
	int offset_y = gidy * 64 + idy;

	//if(offset_x>=M )
	//  return;

	C += offset_x + offset_y*ldc;

	int i = 0;
    if (beta != 0) {
      do
      {
		C[0] = mad(alpha, rC[i][0], beta*C[0]);
		C[16 * ldc] = mad(alpha, rC[i][1], beta*C[16 * ldc]);
		C[32 * ldc] = mad(alpha, rC[i][2], beta*C[32 * ldc]);
		C[48 * ldc] = mad(alpha, rC[i][3], beta*C[48 * ldc]);
		C += 16;
		offset_x += 16;
		//if(offset_x>=M )
		//  return;
      } while (++i < 2);
    } else {
      do
      {
        C[0] = alpha * rC[i][0];
		C[16 * ldc] = alpha * rC[i][1];
		C[32 * ldc] = alpha * rC[i][2];
		C[48 * ldc] = alpha * rC[i][3];
		C += 16;
		offset_x += 16;
		//if(offset_x>=M )
		//  return;
      } while (++i < 2);
    }
}
);
#endif
