/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_DGEMM_COL_TN_B1_MX048_NX048_KX08_SRC_H
#define KERNEL_DGEMM_COL_TN_B1_MX048_NX048_KX08_SRC_H
#pragma message("AutoGemm's dgemm_Col_TN_B1_MX048_NX048_KX08_src overriden by user.")

#ifndef STRINGIFY
#define STRINGIFY(S) STRINGIFY2(S)
#define STRINGIFY2(S) #S
#endif

const unsigned int dgemm_Col_TN_B1_MX048_NX048_KX08_workGroupNumRows = 8;
const unsigned int dgemm_Col_TN_B1_MX048_NX048_KX08_workGroupNumCols = 8;
const unsigned int dgemm_Col_TN_B1_MX048_NX048_KX08_microTileNumRows = 6;
const unsigned int dgemm_Col_TN_B1_MX048_NX048_KX08_microTileNumCols = 6;
const unsigned int dgemm_Col_TN_B1_MX048_NX048_KX08_unroll = 8;

const char * const dgemm_Col_TN_B1_MX048_NX048_KX08_src = STRINGIFY(
_Pragma("OPENCL EXTENSION cl_khr_fp64 : enable")   \n

__attribute__( (reqd_work_group_size(8, 8, 1)) )
__kernel void dgemm_Col_TN_B1_MX048_NX048_KX08_src (
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
  uint const offsetA,
  uint const offsetB,
  uint const offsetC )
{
    double rC[6][6]  = { {(double)0} };
    double rA[1][6];
    double rB[1][6];


    A += offsetA;
    B += offsetB;
    C+=offsetC;

    __local double lA[392];
    __local double lB[392];

    int gidx = get_group_id(0);
    int gidy = get_group_id(1);
    int idx = get_local_id(0);
    int idy = get_local_id(1);

    int idt = 8*idy + idx;
    int idxT = idt % 4;
    int idyT = idt / 4;

    A +=  gidx*48*lda + idxT + idyT*lda;
    B +=  gidy*48*ldb+ idxT + idyT*ldb;

    //for( int block_k=0 ; block_k< K ; block_k+=8)
    uint block_k = K >> 3;
    do
	{
        __local double* plA = lA + idxT*49+ idyT;
        __local double* plB = lB + idxT*49+ idyT;

        barrier(CLK_LOCAL_MEM_FENCE);
        plA[0] = A[0];
        plA[196] = A[4];
        plA[16] = A[16*lda];
        plA[212] = A[4+16*lda];
        plA[32] = A[32*lda];
        plA[228] = A[4+32*lda];
        plB[0] = B[0];
        plB[196] = B[4+0*ldb];
        plB[16] = B[0+16*ldb];
        plB[212] = B[4+16*ldb];
        plB[32] = B[0+32*ldb];
        plB[228] = B[4+32*ldb];
        barrier(CLK_LOCAL_MEM_FENCE);

        int offA = 1*idx;
        int offB = 1*idy;

        for( int k = 0 ; k < 8; k+=1)
        {
            rA[0][0] = lA[offA + 0];
            rA[0][1] = lA[offA + 8];
            rA[0][2] = lA[offA + 16];
            rA[0][3] = lA[offA + 24];
            rA[0][4] = lA[offA + 32];
            rA[0][5] = lA[offA + 40];
            rB[0][0] = lB[offB + 0];
            rB[0][1] = lB[offB + 8];
            rB[0][2] = lB[offB + 16];
            rB[0][3] = lB[offB + 24];
            rB[0][4] = lB[offB + 32];
            rB[0][5] = lB[offB + 40];
            offA += 49;
            offB += 49;
            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
            rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
            rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
            rC[4][0]=mad(rA[0][4],rB[0][0],rC[4][0]);
            rC[5][0]=mad(rA[0][5],rB[0][0],rC[5][0]);
            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
            rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
            rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
            rC[4][1]=mad(rA[0][4],rB[0][1],rC[4][1]);
            rC[5][1]=mad(rA[0][5],rB[0][1],rC[5][1]);
            rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
            rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
            rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
            rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
            rC[4][2]=mad(rA[0][4],rB[0][2],rC[4][2]);
            rC[5][2]=mad(rA[0][5],rB[0][2],rC[5][2]);
            rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
            rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
            rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
            rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
            rC[4][3]=mad(rA[0][4],rB[0][3],rC[4][3]);
            rC[5][3]=mad(rA[0][5],rB[0][3],rC[5][3]);
            rC[0][4]=mad(rA[0][0],rB[0][4],rC[0][4]);
            rC[1][4]=mad(rA[0][1],rB[0][4],rC[1][4]);
            rC[2][4]=mad(rA[0][2],rB[0][4],rC[2][4]);
            rC[3][4]=mad(rA[0][3],rB[0][4],rC[3][4]);
            rC[4][4]=mad(rA[0][4],rB[0][4],rC[4][4]);
            rC[5][4]=mad(rA[0][5],rB[0][4],rC[5][4]);
            rC[0][5]=mad(rA[0][0],rB[0][5],rC[0][5]);
            rC[1][5]=mad(rA[0][1],rB[0][5],rC[1][5]);
            rC[2][5]=mad(rA[0][2],rB[0][5],rC[2][5]);
            rC[3][5]=mad(rA[0][3],rB[0][5],rC[3][5]);
            rC[4][5]=mad(rA[0][4],rB[0][5],rC[4][5]);
            rC[5][5]=mad(rA[0][5],rB[0][5],rC[5][5]);
        }
        A += 8;
        B += 8;
    }
	while (--block_k > 0);

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
    C+=8;
}
);
#endif
