/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_SGEMM_COL_NT_B1_MX032_NX032_KX16_SRC_H
#define KERNEL_SGEMM_COL_NT_B1_MX032_NX032_KX16_SRC_H
// #pragma message("AutoGemm's sgemm_Col_NT_B1_MX032_NX032_KX16_src overriden by user.")

#ifndef STRINGIFY
#define STRINGIFY(S) STRINGIFY2(S)
#define STRINGIFY2(S) #S
#endif

const unsigned int sgemm_Col_NT_B1_MX032_NX032_KX16_workGroupNumRows = 16;
const unsigned int sgemm_Col_NT_B1_MX032_NX032_KX16_workGroupNumCols = 16;
const unsigned int sgemm_Col_NT_B1_MX032_NX032_KX16_microTileNumRows = 2;
const unsigned int sgemm_Col_NT_B1_MX032_NX032_KX16_microTileNumCols = 2;
const unsigned int sgemm_Col_NT_B1_MX032_NX032_KX16_unroll = 16;

const char * const sgemm_Col_NT_B1_MX032_NX032_KX16_src = STRINGIFY(

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
			      mem_fence(CLK_LOCAL_MEM_FENCE);\n

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_Col_NT_B1_MX032_NX032_KX16 (
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
    float rC[2][2]  = { {(float)0} };
    float rA[1][2];
    float rB[1][2];

    A += offsetA;
    B += offsetB;
    C+=offsetC;

    __local float lA[544];
    __local float lB[544];

    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);

    uint idt = 16*idy + idx;
    uint idxT = idt % 16;
    uint idyT = idt / 16;

    A +=  gidx*32+ idxT + idyT*lda;
    B +=  gidy*32+ idxT + idyT*ldb;


    uint block_k = K >> 4;
    do
	{
        __local float* plA = lA + idyT*33+idxT;
        __local float* plB = lB + idyT*33+idxT;
        barrier(CLK_LOCAL_MEM_FENCE);
        plB[0] = B[0+0*ldb];
        plB[16] = B[16+0*ldb];

	    plA[0] = A[0+0*lda];
        plA[16] = A[16+0*lda];

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

        A += lda<<4;
        B += ldb<<4;
	} while (--block_k > 0);

    C+= gidx*32+idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;

	C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[0][1] + beta*C[16*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[1][1] + beta*C[16*ldc];

}
);
#endif
