/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_DGEMM_COL_TN_B1_MX048_NX048_KX08_SRC_C
#define KERNEL_DGEMM_COL_TN_B1_MX048_NX048_KX08_SRC_C

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
\n
\n__attribute__( (reqd_work_group_size(8, 8, 1)) )
\n__kernel void dgemm_Col_TN_B1_MX048_NX048_KX08_src (
\n  __global double const * restrict A,
\n  __global double const * restrict B,
\n  __global double * C,  
\n  double const alpha,  
\n  double const beta,   
\n  uint const M, 
\n  uint const N, 
\n  uint const K,
\n  uint lda,
\n  uint ldb, 
\n  uint ldc, 
\n  uint const offsetA, 
\n  uint const offsetB,
\n  uint const offsetC )
\n{
\n    double rC[6][6]  = {(double)0};
\n    double rA[1][6];
\n    double rB[1][6];
\n    
\n    
\n    A += offsetA;
\n    B += offsetB;
\n    C+=offsetC;
\n    
\n    __local double lA[392];
\n    __local double lB[392];
\n    
\n    int gidx = get_group_id(0);
\n    int gidy = get_group_id(1);
\n    int idx = get_local_id(0);
\n    int idy = get_local_id(1);
\n    
\n    int idt = 8*idy + idx;
\n    int idxT = idt % 4;
\n    int idyT = idt / 4;
\n    
\n    A +=  gidx*48*lda + idxT + idyT*lda;
\n    B +=  gidy*48*ldb+ idxT + idyT*ldb;
\n    
\n    //for( int block_k=0 ; block_k< K ; block_k+=8)
\n    uint block_k = K >> 3;
\n    do
\n	{
\n        __local double* plA = lA + idxT*49+ idyT;
\n        __local double* plB = lB + idxT*49+ idyT;
\n   
\n        barrier(CLK_LOCAL_MEM_FENCE);
\n        plA[0] = A[0];
\n        plA[196] = A[4];
\n        plA[16] = A[16*lda];
\n        plA[212] = A[4+16*lda];
\n        plA[32] = A[32*lda];
\n        plA[228] = A[4+32*lda];
\n        plB[0] = B[0];
\n        plB[196] = B[4+0*ldb];
\n        plB[16] = B[0+16*ldb];
\n        plB[212] = B[4+16*ldb];
\n        plB[32] = B[0+32*ldb];
\n        plB[228] = B[4+32*ldb];
\n        barrier(CLK_LOCAL_MEM_FENCE);
\n       
\n        int offA = 1*idx;
\n        int offB = 1*idy;
\n       
\n        for( int k = 0 ; k < 8; k+=1)
\n        {
\n            rA[0][0] = lA[offA + 0];
\n            rA[0][1] = lA[offA + 8];
\n            rA[0][2] = lA[offA + 16];
\n            rA[0][3] = lA[offA + 24];
\n            rA[0][4] = lA[offA + 32];
\n            rA[0][5] = lA[offA + 40];
\n            rB[0][0] = lB[offB + 0];
\n            rB[0][1] = lB[offB + 8];
\n            rB[0][2] = lB[offB + 16];
\n            rB[0][3] = lB[offB + 24];
\n            rB[0][4] = lB[offB + 32];
\n            rB[0][5] = lB[offB + 40];
\n            offA += 49;
\n            offB += 49;
\n            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
\n            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
\n            rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
\n            rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
\n            rC[4][0]=mad(rA[0][4],rB[0][0],rC[4][0]);
\n            rC[5][0]=mad(rA[0][5],rB[0][0],rC[5][0]);
\n            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
\n            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
\n            rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
\n            rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
\n            rC[4][1]=mad(rA[0][4],rB[0][1],rC[4][1]);
\n            rC[5][1]=mad(rA[0][5],rB[0][1],rC[5][1]);
\n            rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
\n            rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
\n            rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
\n            rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
\n            rC[4][2]=mad(rA[0][4],rB[0][2],rC[4][2]);
\n            rC[5][2]=mad(rA[0][5],rB[0][2],rC[5][2]);
\n            rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
\n            rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
\n            rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
\n            rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
\n            rC[4][3]=mad(rA[0][4],rB[0][3],rC[4][3]);
\n            rC[5][3]=mad(rA[0][5],rB[0][3],rC[5][3]);
\n            rC[0][4]=mad(rA[0][0],rB[0][4],rC[0][4]);
\n            rC[1][4]=mad(rA[0][1],rB[0][4],rC[1][4]);
\n            rC[2][4]=mad(rA[0][2],rB[0][4],rC[2][4]);
\n            rC[3][4]=mad(rA[0][3],rB[0][4],rC[3][4]);
\n            rC[4][4]=mad(rA[0][4],rB[0][4],rC[4][4]);
\n            rC[5][4]=mad(rA[0][5],rB[0][4],rC[5][4]);
\n            rC[0][5]=mad(rA[0][0],rB[0][5],rC[0][5]);
\n            rC[1][5]=mad(rA[0][1],rB[0][5],rC[1][5]);
\n            rC[2][5]=mad(rA[0][2],rB[0][5],rC[2][5]);
\n            rC[3][5]=mad(rA[0][3],rB[0][5],rC[3][5]);
\n            rC[4][5]=mad(rA[0][4],rB[0][5],rC[4][5]);
\n            rC[5][5]=mad(rA[0][5],rB[0][5],rC[5][5]);
\n        }
\n        A += 8;
\n        B += 8;
\n    }
\n	while (--block_k > 0);
\n
\n    C+= gidx*48;
\n    C+= idx;
\n    C+= gidy*48*ldc;
\n    C+= idy*ldc;
\n    
\n    C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
\n    C[8*ldc] = alpha*rC[0][1] + beta*C[8*ldc];
\n    C[16*ldc] = alpha*rC[0][2] + beta*C[16*ldc];
\n    C[24*ldc] = alpha*rC[0][3] + beta*C[24*ldc];
\n    C[32*ldc] = alpha*rC[0][4] + beta*C[32*ldc];
\n    C[40*ldc] = alpha*rC[0][5] + beta*C[40*ldc];
\n    C+=8;
\n    C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
\n    C[8*ldc] = alpha*rC[1][1] + beta*C[8*ldc];
\n    C[16*ldc] = alpha*rC[1][2] + beta*C[16*ldc];
\n    C[24*ldc] = alpha*rC[1][3] + beta*C[24*ldc];
\n    C[32*ldc] = alpha*rC[1][4] + beta*C[32*ldc];
\n    C[40*ldc] = alpha*rC[1][5] + beta*C[40*ldc];
\n    C+=8;
\n    C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
\n    C[8*ldc] = alpha*rC[2][1] + beta*C[8*ldc];
\n    C[16*ldc] = alpha*rC[2][2] + beta*C[16*ldc];
\n    C[24*ldc] = alpha*rC[2][3] + beta*C[24*ldc];
\n    C[32*ldc] = alpha*rC[2][4] + beta*C[32*ldc];
\n    C[40*ldc] = alpha*rC[2][5] + beta*C[40*ldc];
\n    C+=8;
\n    C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
\n    C[8*ldc] = alpha*rC[3][1] + beta*C[8*ldc];
\n    C[16*ldc] = alpha*rC[3][2] + beta*C[16*ldc];
\n    C[24*ldc] = alpha*rC[3][3] + beta*C[24*ldc];
\n    C[32*ldc] = alpha*rC[3][4] + beta*C[32*ldc];
\n    C[40*ldc] = alpha*rC[3][5] + beta*C[40*ldc];
\n    C+=8;
\n    C[0*ldc] = alpha*rC[4][0] + beta*C[0*ldc];
\n    C[8*ldc] = alpha*rC[4][1] + beta*C[8*ldc];
\n    C[16*ldc] = alpha*rC[4][2] + beta*C[16*ldc];
\n    C[24*ldc] = alpha*rC[4][3] + beta*C[24*ldc];
\n    C[32*ldc] = alpha*rC[4][4] + beta*C[32*ldc];
\n    C[40*ldc] = alpha*rC[4][5] + beta*C[40*ldc];
\n    C+=8;
\n    C[0*ldc] = alpha*rC[5][0] + beta*C[0*ldc];
\n    C[8*ldc] = alpha*rC[5][1] + beta*C[8*ldc];
\n    C[16*ldc] = alpha*rC[5][2] + beta*C[16*ldc];
\n    C[24*ldc] = alpha*rC[5][3] + beta*C[24*ldc];
\n    C[32*ldc] = alpha*rC[5][4] + beta*C[32*ldc];
\n    C[40*ldc] = alpha*rC[5][5] + beta*C[40*ldc];
\n    C+=8;
\n}
); 
#endif
