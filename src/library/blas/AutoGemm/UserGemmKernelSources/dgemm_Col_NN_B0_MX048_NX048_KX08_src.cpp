/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_DGEMM_COL_NN_B0_MX048_NX048_KX08_SRC_C
#define KERNEL_DGEMM_COL_NN_B0_MX048_NX048_KX08_SRC_C

#ifndef STRINGIFY
#define STRINGIFY(S) STRINGIFY2(S)
#define STRINGIFY2(S) #S
#endif

const unsigned int dgemm_Col_NN_B0_MX048_NX048_KX08_workGroupNumRows = 8;
const unsigned int dgemm_Col_NN_B0_MX048_NX048_KX08_workGroupNumCols = 8;
const unsigned int dgemm_Col_NN_B0_MX048_NX048_KX08_microTileNumRows = 6;
const unsigned int dgemm_Col_NN_B0_MX048_NX048_KX08_microTileNumCols = 6;
const unsigned int dgemm_Col_NN_B0_MX048_NX048_KX08_unroll = 8;

const char * const dgemm_Col_NN_B0_MX048_NX048_KX08_src = STRINGIFY(
\n
\n#define  M6x6 \
            rA[0] = lA[offA + 0];\
            rA[1] = lA[offA + 8];\
            rA[2] = lA[offA + 16];\
            rA[3] = lA[offA + 24];\
            rA[4] = lA[offA + 32];\
            rA[5] = lA[offA + 40];\
            rB[0] = lB[offB + 0];\
            rB[1] = lB[offB + 8];\
            rB[2] = lB[offB + 16];\
            rB[3] = lB[offB + 24]; \
            rB[4] = lB[offB + 32]; \
            rB[5] = lB[offB + 40]; \
            offA += 49; \
            offB += 49; \
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
            barrier(CLK_LOCAL_MEM_FENCE);\n

\n__attribute__((reqd_work_group_size(8,8,1)))
\n__kernel void dgemm_Col_NN_B0_MX048_NX048_KX08 (
\n    __global double const * restrict A,
\n    __global double const * restrict B,
\n    __global double * C,
\n    double const alpha,
\n    double const beta,
\n    uint const M,
\n    uint const N,
\n    uint const K,
\n    uint lda,
\n    uint ldb,
\n    uint ldc,
\n    uint offsetA,
\n    uint offsetB,
\n    uint offsetC)
\n{
\n
\n
\n    A += offsetA;
\n    B += offsetB;
\n    C += offsetC;
\n
\n
\n    double rC[6][6] = {(double)0};
\n    double rA[6];
\n    double rB[6];
\n  __local double lA[392];
\n  __local double lB[392];
\n
\n  int gidx = get_group_id(0);
\n  int gidy = get_group_id(1);
\n  int idx = get_local_id(0);
\n  int idy = get_local_id(1);
\n
\n  int idt = 8*idy + idx;
\n  int idxT = idt % 8;
\n  int idyT = idt / 8;
\n
\n  A +=  gidx*48+ idxT + idyT*lda;
\n  B +=  gidy*48*ldb+ idx + idy*ldb;
\n
\n
\n
\n    int block_k = K >> 3;
\n    do {
\n
\n	    __local double* plA = lA + idyT*49 + idxT;
\n        __local double* plB = lB + idxT*49 + idyT;
\n
\n        plA[0] = A[0+0*lda];
\n        plA[8] = A[8+0*lda];
\n        plA[16] = A[16+0*lda];
\n        plA[24] = A[24+0*lda];
\n        plA[32] = A[32+0*lda];
\n        plA[40] = A[40+0*lda];
\n        plB[0] = B[0+0*ldb];
\n        plB[8] = B[0+8*ldb];
\n        plB[16] = B[0+16*ldb];
\n        plB[24] = B[0+24*ldb];
\n        plB[32] = B[0+32*ldb];
\n        plB[40] = B[0+40*ldb];
\n        barrier(CLK_LOCAL_MEM_FENCE);
\n        int offA = idx ;
\n        int offB = idy ;
\n        M6x6
\n        M6x6
\n        M6x6
\n        M6x6
\n        M6x6
\n        M6x6
\n        M6x6
\n        M6x6
\n        A += lda << 3;
\n        B += 8;
\n    } while (--block_k > 0);
\n
\n
\n
\n  C+= gidx*48;
\n  C+= idx;
\n  C+= gidy*48*ldc;
\n  C+= idy*ldc;
\n 
\n  C[0*ldc] = alpha*rC[0][0]  ;
\n  C[8*ldc] = alpha*rC[0][1]  ;
\n  C[16*ldc] = alpha*rC[0][2] ;
\n  C[24*ldc] = alpha*rC[0][3] ;
\n  C[32*ldc] = alpha*rC[0][4] ;
\n  C[40*ldc] = alpha*rC[0][5] ;
\n  C+=8;						 ;
\n  C[0*ldc] = alpha*rC[1][0]  ;
\n  C[8*ldc] = alpha*rC[1][1]  ;
\n  C[16*ldc] = alpha*rC[1][2] ;
\n  C[24*ldc] = alpha*rC[1][3] ;
\n  C[32*ldc] = alpha*rC[1][4] ;
\n  C[40*ldc] = alpha*rC[1][5] ;
\n  C+=8;						 ;
\n  C[0*ldc] = alpha*rC[2][0]  ;
\n  C[8*ldc] = alpha*rC[2][1]  ;
\n  C[16*ldc] = alpha*rC[2][2] ;
\n  C[24*ldc] = alpha*rC[2][3] ;
\n  C[32*ldc] = alpha*rC[2][4] ;
\n  C[40*ldc] = alpha*rC[2][5] ;
\n  C+=8;						 ;
\n  C[0*ldc] = alpha*rC[3][0]  ;
\n  C[8*ldc] = alpha*rC[3][1]  ;
\n  C[16*ldc] = alpha*rC[3][2] ;
\n  C[24*ldc] = alpha*rC[3][3] ;
\n  C[32*ldc] = alpha*rC[3][4] ;
\n  C[40*ldc] = alpha*rC[3][5] ;
\n  C+=8;						 ;
\n  C[0*ldc] = alpha*rC[4][0]  ;
\n  C[8*ldc] = alpha*rC[4][1]  ;
\n  C[16*ldc] = alpha*rC[4][2] ;
\n  C[24*ldc] = alpha*rC[4][3] ;
\n  C[32*ldc] = alpha*rC[4][4] ;
\n  C[40*ldc] = alpha*rC[4][5] ;
\n  C+=8;						 ;
\n  C[0*ldc] = alpha*rC[5][0]  ;
\n  C[8*ldc] = alpha*rC[5][1]  ;
\n  C[16*ldc] = alpha*rC[5][2] ;
\n  C[24*ldc] = alpha*rC[5][3] ;
\n  C[32*ldc] = alpha*rC[5][4] ;
\n  C[40*ldc] = alpha*rC[5][5] ;
\n  
\n}
);
#endif
