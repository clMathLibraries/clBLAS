/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_DGEMM_COL_NN_B1_MX048_NX048_KX08_SRC_H
#define KERNEL_DGEMM_COL_NN_B1_MX048_NX048_KX08_SRC_H
#pragma message("AutoGemm's dgemm_Col_NN_B1_MX048_NX048_KX08_src overriden by user.")

#ifndef STRINGIFY
#define STRINGIFY(S) STRINGIFY2(S)
#define STRINGIFY2(S) #S
#endif

const unsigned int dgemm_Col_NN_B1_MX048_NX048_KX08_workGroupNumRows = 8;
const unsigned int dgemm_Col_NN_B1_MX048_NX048_KX08_workGroupNumCols = 8;
const unsigned int dgemm_Col_NN_B1_MX048_NX048_KX08_microTileNumRows = 6;
const unsigned int dgemm_Col_NN_B1_MX048_NX048_KX08_microTileNumCols = 6;
const unsigned int dgemm_Col_NN_B1_MX048_NX048_KX08_unroll = 8;

const char * const dgemm_Col_NN_B1_MX048_NX048_KX08_src = STRINGIFY(
_Pragma("OPENCL EXTENSION cl_khr_fp64 : enable")   \n

#define  M6x6 \
            rA[0] = lA[offA + 0];                       \
            rA[1] = lA[offA + 8];                       \
            rA[2] = lA[offA + 16];                      \
            rA[3] = lA[offA + 24];                      \
            rA[4] = lA[offA + 32];                      \
            rA[5] = lA[offA + 40];                      \
            rB[0] = lB[offB + 0];                       \
            rB[1] = lB[offB + 8];                       \
            rB[2] = lB[offB + 16];                      \
            rB[3] = lB[offB + 24];                      \
            rB[4] = lB[offB + 32];                      \
            rB[5] = lB[offB + 40];                      \
            offA += 49;                                 \
            offB += 49;                                 \
            rC[0][0]=mad(rA[0],rB[0],rC[0][0]);         \
            rC[1][0]=mad(rA[1],rB[0],rC[1][0]);         \
            rC[2][0]=mad(rA[2],rB[0],rC[2][0]);         \
            rC[3][0]=mad(rA[3],rB[0],rC[3][0]);         \
            rC[4][0]=mad(rA[4],rB[0],rC[4][0]);         \
            rC[5][0]=mad(rA[5],rB[0],rC[5][0]);         \
            rC[0][1]=mad(rA[0],rB[1],rC[0][1]);         \
            rC[1][1]=mad(rA[1],rB[1],rC[1][1]);         \
            rC[2][1]=mad(rA[2],rB[1],rC[2][1]);         \
            rC[3][1]=mad(rA[3],rB[1],rC[3][1]);         \
            rC[4][1]=mad(rA[4],rB[1],rC[4][1]);         \
            rC[5][1]=mad(rA[5],rB[1],rC[5][1]);         \
            rC[0][2]=mad(rA[0],rB[2],rC[0][2]);         \
            rC[1][2]=mad(rA[1],rB[2],rC[1][2]);         \
            rC[2][2]=mad(rA[2],rB[2],rC[2][2]);         \
            rC[3][2]=mad(rA[3],rB[2],rC[3][2]);         \
            rC[4][2]=mad(rA[4],rB[2],rC[4][2]);         \
            rC[5][2]=mad(rA[5],rB[2],rC[5][2]);         \
            rC[0][3]=mad(rA[0],rB[3],rC[0][3]);         \
            rC[1][3]=mad(rA[1],rB[3],rC[1][3]);         \
            rC[2][3]=mad(rA[2],rB[3],rC[2][3]);         \
            rC[3][3]=mad(rA[3],rB[3],rC[3][3]);         \
            rC[4][3]=mad(rA[4],rB[3],rC[4][3]);         \
            rC[5][3]=mad(rA[5],rB[3],rC[5][3]);         \
            rC[0][4]=mad(rA[0],rB[4],rC[0][4]);         \
            rC[1][4]=mad(rA[1],rB[4],rC[1][4]);         \
            rC[2][4]=mad(rA[2],rB[4],rC[2][4]);         \
            rC[3][4]=mad(rA[3],rB[4],rC[3][4]);         \
            rC[4][4]=mad(rA[4],rB[4],rC[4][4]);         \
            rC[5][4]=mad(rA[5],rB[4],rC[5][4]);         \
            rC[0][5]=mad(rA[0],rB[5],rC[0][5]);         \
            rC[1][5]=mad(rA[1],rB[5],rC[1][5]);         \
            rC[2][5]=mad(rA[2],rB[5],rC[2][5]);         \
            rC[3][5]=mad(rA[3],rB[5],rC[3][5]);         \
            rC[4][5]=mad(rA[4],rB[5],rC[4][5]);         \
            rC[5][5]=mad(rA[5],rB[5],rC[5][5]);         \
            mem_fence(CLK_LOCAL_MEM_FENCE);\n

__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_Col_NN_B1_MX048_NX048_KX08 (
    __global double const * restrict A,
    __global double const * restrict B,
    __global double * C,
    double const alpha,
    double const beta,
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
    A += offsetA;
    B += offsetB;
    C += offsetC;


    double rC[6][6] = { {(double)0} };
    double rA[6];
    double rB[6];

  __local double lA[392];
  __local double lB[392];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*48+ idxT + idyT*lda;
  B +=  gidy*48*ldb+ idx + idy*ldb;



    int block_k = K >> 3;
    do {

	      __local double* plA = lA + idyT*49 + idxT;
        __local double* plB = lB + idxT*49 + idyT;
        barrier(CLK_LOCAL_MEM_FENCE);
        plA[0] = A[0+0*lda];
        plA[8] = A[8+0*lda];
        plA[16] = A[16+0*lda];
        plA[24] = A[24+0*lda];
        plA[32] = A[32+0*lda];
        plA[40] = A[40+0*lda];
        plB[0] = B[0+0*ldb];
        plB[8] = B[0+8*ldb];
        plB[16] = B[0+16*ldb];
        plB[24] = B[0+24*ldb];
        plB[32] = B[0+32*ldb];
        plB[40] = B[0+40*ldb];

        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx;
        int offB = idy;

        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        A += lda << 3;
        B += 8;
    } while (--block_k > 0);



  C+= gidx*48;
  C+= idx;
  C+= gidy*48*ldc;
  C+= idy*ldc;

  C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[0][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[0][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[0][3] + beta*C[24*ldc];
  C[32*ldc] = alpha*rC[0][4] + beta*C[32*ldc];
  C[40*ldc] = alpha*rC[0][5] + beta*C[40*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[1][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[1][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[1][3] + beta*C[24*ldc];
  C[32*ldc] = alpha*rC[1][4] + beta*C[32*ldc];
  C[40*ldc] = alpha*rC[1][5] + beta*C[40*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[2][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[2][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[2][3] + beta*C[24*ldc];
  C[32*ldc] = alpha*rC[2][4] + beta*C[32*ldc];
  C[40*ldc] = alpha*rC[2][5] + beta*C[40*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[3][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[3][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[3][3] + beta*C[24*ldc];
  C[32*ldc] = alpha*rC[3][4] + beta*C[32*ldc];
  C[40*ldc] = alpha*rC[3][5] + beta*C[40*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[4][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[4][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[4][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[4][3] + beta*C[24*ldc];
  C[32*ldc] = alpha*rC[4][4] + beta*C[32*ldc];
  C[40*ldc] = alpha*rC[4][5] + beta*C[40*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[5][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[5][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[5][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[5][3] + beta*C[24*ldc];
  C[32*ldc] = alpha*rC[5][4] + beta*C[32*ldc];
  C[40*ldc] = alpha*rC[5][5] + beta*C[40*ldc];
}
);
#endif
