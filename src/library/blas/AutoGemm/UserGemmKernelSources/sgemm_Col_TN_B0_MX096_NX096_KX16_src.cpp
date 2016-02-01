/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_SGEMM_COL_TN_B0_MX096_NX096_KX16_SRC_H
#define KERNEL_SGEMM_COL_TN_B0_MX096_NX096_KX16_SRC_H
#pragma message("AutoGemm's sgemm_Col_TN_B0_MX096_NX096_KX16_src overriden by user.")

#ifndef STRINGIFY
#define STRINGIFY(S) STRINGIFY2(S)
#define STRINGIFY2(S) #S
#endif

const unsigned int sgemm_Col_TN_B0_MX096_NX096_KX16_workGroupNumRows = 16;
const unsigned int sgemm_Col_TN_B0_MX096_NX096_KX16_workGroupNumCols = 16;
const unsigned int sgemm_Col_TN_B0_MX096_NX096_KX16_microTileNumRows = 6;
const unsigned int sgemm_Col_TN_B0_MX096_NX096_KX16_microTileNumCols = 6;
const unsigned int sgemm_Col_TN_B0_MX096_NX096_KX16_unroll = 16;

const char * const sgemm_Col_TN_B0_MX096_NX096_KX16_src = STRINGIFY(

#define  M6x6 \
            rA[0][0] = lA[offA + 0];				  \
            rA[0][1] = lA[offA + 16];				  \
            rA[0][2] = lA[offA + 32];				  \
            rA[0][3] = lA[offA + 48];				  \
            rA[0][4] = lA[offA + 64];				  \
            rA[0][5] = lA[offA + 80];				  \
            rB[0][0] = lB[offB + 0];				  \
            rB[0][1] = lB[offB + 16];				  \
            rB[0][2] = lB[offB + 32];				  \
            rB[0][3] = lB[offB + 48];				  \
            rB[0][4] = lB[offB + 64];				  \
            rB[0][5] = lB[offB + 80];				  \
            offA += 97;								  \
            offB += 97;								  \
            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]); \
            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]); \
            rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]); \
            rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]); \
            rC[4][0]=mad(rA[0][4],rB[0][0],rC[4][0]); \
            rC[5][0]=mad(rA[0][5],rB[0][0],rC[5][0]); \
            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]); \
            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]); \
            rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]); \
            rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]); \
            rC[4][1]=mad(rA[0][4],rB[0][1],rC[4][1]); \
            rC[5][1]=mad(rA[0][5],rB[0][1],rC[5][1]); \
            rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]); \
            rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]); \
            rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]); \
            rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]); \
            rC[4][2]=mad(rA[0][4],rB[0][2],rC[4][2]); \
            rC[5][2]=mad(rA[0][5],rB[0][2],rC[5][2]); \
            rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]); \
            rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]); \
            rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]); \
            rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]); \
            rC[4][3]=mad(rA[0][4],rB[0][3],rC[4][3]); \
            rC[5][3]=mad(rA[0][5],rB[0][3],rC[5][3]); \
            rC[0][4]=mad(rA[0][0],rB[0][4],rC[0][4]); \
            rC[1][4]=mad(rA[0][1],rB[0][4],rC[1][4]); \
            rC[2][4]=mad(rA[0][2],rB[0][4],rC[2][4]); \
            rC[3][4]=mad(rA[0][3],rB[0][4],rC[3][4]); \
            rC[4][4]=mad(rA[0][4],rB[0][4],rC[4][4]); \
            rC[5][4]=mad(rA[0][5],rB[0][4],rC[5][4]); \
            rC[0][5]=mad(rA[0][0],rB[0][5],rC[0][5]); \
            rC[1][5]=mad(rA[0][1],rB[0][5],rC[1][5]); \
            rC[2][5]=mad(rA[0][2],rB[0][5],rC[2][5]); \
            rC[3][5]=mad(rA[0][3],rB[0][5],rC[3][5]); \
            rC[4][5]=mad(rA[0][4],rB[0][5],rC[4][5]); \
            rC[5][5]=mad(rA[0][5],rB[0][5],rC[5][5]); \
			      mem_fence(CLK_LOCAL_MEM_FENCE);\n

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_Col_TN_B0_MX096_NX096_KX16 (
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
  float rC[6][6]  = { {(float)0} };
  float rA[1][6];
  float rB[1][6];



  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local float lA[1552];
  __local float lB[1552];

  uint gidx = get_group_id(0);
  uint gidy = get_group_id(1);
  uint idx = get_local_id(0);
  uint idy = get_local_id(1);

  A +=  (gidx*96+idy)*lda + idx;
  B +=  (gidy*96+idy)*ldb + idx;


  uint block_k = K >> 4;
  do
  {
    __local float* plA = lA + idx*97+idy;
    __local float* plB = lB + idx*97+idy;
    barrier(CLK_LOCAL_MEM_FENCE);

    plB[0] = B[0];
    plB[16] = B[16*ldb];
    plB[32] = B[32*ldb];
    plB[48] = B[48*ldb];
    plB[64] = B[64*ldb];
    plB[80] = B[80*ldb];

    plA[0] = A[0];
    plA[16] = A[16*lda];
    plA[32] = A[32*lda];
    plA[48] = A[48*lda];
    plA[64] = A[64*lda];
    plA[80] = A[80*lda];


    barrier(CLK_LOCAL_MEM_FENCE);
    uint offA = idx;
    uint offB = idy;

    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6

    A += 16;
    B += 16;
  } while (--block_k > 0);

  C+= gidx*96+idx;
  C+= gidy*96*ldc;
  C+= idy*ldc;

  C[0*ldc] = alpha*rC[0][0];
  C[16*ldc] = alpha*rC[0][1];
  C[32*ldc] = alpha*rC[0][2];
  C[48*ldc] = alpha*rC[0][3];
  C[64*ldc] = alpha*rC[0][4];
  C[80*ldc] = alpha*rC[0][5];
  C+=16;
  C[0*ldc] = alpha*rC[1][0];
  C[16*ldc] = alpha*rC[1][1];
  C[32*ldc] = alpha*rC[1][2];
  C[48*ldc] = alpha*rC[1][3];
  C[64*ldc] = alpha*rC[1][4];
  C[80*ldc] = alpha*rC[1][5];
  C+=16;
  C[0*ldc] = alpha*rC[2][0];
  C[16*ldc] = alpha*rC[2][1];
  C[32*ldc] = alpha*rC[2][2];
  C[48*ldc] = alpha*rC[2][3];
  C[64*ldc] = alpha*rC[2][4];
  C[80*ldc] = alpha*rC[2][5];
  C+=16;
  C[0*ldc] = alpha*rC[3][0];
  C[16*ldc] = alpha*rC[3][1];
  C[32*ldc] = alpha*rC[3][2];
  C[48*ldc] = alpha*rC[3][3];
  C[64*ldc] = alpha*rC[3][4];
  C[80*ldc] = alpha*rC[3][5];
  C+=16;
  C[0*ldc] = alpha*rC[4][0];
  C[16*ldc] = alpha*rC[4][1];
  C[32*ldc] = alpha*rC[4][2];
  C[48*ldc] = alpha*rC[4][3];
  C[64*ldc] = alpha*rC[4][4];
  C[80*ldc] = alpha*rC[4][5];
  C+=16;
  C[0*ldc] = alpha*rC[5][0];
  C[16*ldc] = alpha*rC[5][1];
  C[32*ldc] = alpha*rC[5][2];
  C[48*ldc] = alpha*rC[5][3];
  C[64*ldc] = alpha*rC[5][4];
  C[80*ldc] = alpha*rC[5][5];

}
);
#endif
