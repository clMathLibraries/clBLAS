/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_SGEMM_COL_NN_B0_MX064_NX064_KX16_SRC_H
#define KERNEL_SGEMM_COL_NN_B0_MX064_NX064_KX16_SRC_H
// #pragma message("AutoGemm's sgemm_Col_NN_B0_MX064_NX064_KX16_src overriden by user.")

#ifndef STRINGIFY
#define STRINGIFY(S) STRINGIFY2(S)
#define STRINGIFY2(S) #S
#endif

const unsigned int sgemm_Col_NN_B0_MX064_NX064_KX16_workGroupNumRows = 16;
const unsigned int sgemm_Col_NN_B0_MX064_NX064_KX16_workGroupNumCols = 16;
const unsigned int sgemm_Col_NN_B0_MX064_NX064_KX16_microTileNumRows = 4;
const unsigned int sgemm_Col_NN_B0_MX064_NX064_KX16_microTileNumCols = 4;
const unsigned int sgemm_Col_NN_B0_MX064_NX064_KX16_unroll = 16;

const char * const sgemm_Col_NN_B0_MX064_NX064_KX16_src = STRINGIFY(

#define  M4x4 \
    rA[0][0] = lA[offA + 0];  \
    rA[0][1] = lA[offA + 16]; \
    rA[0][2] = lA[offA + 32]; \
    rA[0][3] = lA[offA + 48]; \
    rB[0][0] = lB[offB + 0];  \
    rB[0][1] = lB[offB + 16]; \
    rB[0][2] = lB[offB + 32]; \
    rB[0][3] = lB[offB + 48]; \
    offA += 65; \
    offB += 65; \
    rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]); \
    rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]); \
    rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]); \
    rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]); \
    rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]); \
    rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]); \
    rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]); \
    rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]); \
    rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]); \
    rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]); \
    rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]); \
    rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]); \
    rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]); \
    rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]); \
    rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]); \
    rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]); \
    mem_fence(CLK_LOCAL_MEM_FENCE);\n

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_Col_NN_B0_MX064_NX064_KX16 (
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
    float rC[4][4]  = { {(float)0} };
    float rA[1][4];
    float rB[1][4];



    A += offsetA;
    B += offsetB;
    C+=offsetC;

    __local float lA[1056];
    __local float lB[1056];

    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);

    A +=  gidx*64+ idx + idy*lda;
    B +=  (gidy*64+idy)*ldb+ idx;


    uint block_k = K >> 4;
    do {
        __local float* plA = lA + idy*65+idx;
        __local float* plB = lB + idx*65+idy;
        barrier(CLK_LOCAL_MEM_FENCE);
        plB[0] = B[0];
        plB[16] = B[16*ldb];
        plB[32] = B[32*ldb];
        plB[48] = B[48*ldb];


        plA[0] = A[0+0*lda];
        plA[16] = A[16+0*lda];
        plA[32] = A[32+0*lda];
        plA[48] = A[48+0*lda];



        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;

    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4

        A += lda<<4;
        B += 16;
  } while (--block_k > 0);

    C+= gidx*64+idx;
    C+= gidy*64*ldc;
    C+= idy*ldc;

    C[0*ldc] = alpha*rC[0][0] ;
    C[16*ldc] = alpha*rC[0][1];
    C[32*ldc] = alpha*rC[0][2];
    C[48*ldc] = alpha*rC[0][3];
    C+=16;
    C[0*ldc] = alpha*rC[1][0] ;
    C[16*ldc] = alpha*rC[1][1];
    C[32*ldc] = alpha*rC[1][2];
    C[48*ldc] = alpha*rC[1][3];
    C+=16;
    C[0*ldc] = alpha*rC[2][0] ;
    C[16*ldc] = alpha*rC[2][1];
    C[32*ldc] = alpha*rC[2][2];
    C[48*ldc] = alpha*rC[2][3];
    C+=16;
    C[0*ldc] = alpha*rC[3][0] ;
    C[16*ldc] = alpha*rC[3][1];
    C[32*ldc] = alpha*rC[3][2];
    C[48*ldc] = alpha*rC[3][3];


}
);
#endif
