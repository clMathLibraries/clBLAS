/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_SGEMM_COL_NN_B0_MX064_NX064_KX16_SRC_C
#define KERNEL_SGEMM_COL_NN_B0_MX064_NX064_KX16_SRC_C

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
\n
\n#define  M4x4 \
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
    barrier(CLK_LOCAL_MEM_FENCE);\n
\n
\n__attribute__((reqd_work_group_size(16,16,1)))
\n__kernel void sgemm_Col_NN_B0_MX064_NX064_KX16 (
\n  __global float const * restrict A,
\n  __global float const * restrict B,
\n  __global float * C,
\n  float const alpha,
\n  float const beta,
\n  uint const M,
\n  uint const N,
\n  uint const K,
\n  uint lda,
\n  uint ldb,
\n  uint ldc,
\n  uint offsetA,
\n  uint offsetB,
\n  uint offsetC)
\n{
\n    float rC[4][4]  = {(float)0};
\n    float rA[1][4];
\n    float rB[1][4];
\n    
\n
\n    
\n    A += offsetA;
\n    B += offsetB;
\n    C+=offsetC;
\n    
\n    __local float lA[1056];
\n    __local float lB[1056];
\n    
\n    uint gidx = get_group_id(0);
\n    uint gidy = get_group_id(1);
\n    uint idx = get_local_id(0);
\n    uint idy = get_local_id(1);
\n
\n    A +=  gidx*64+ idx + idy*lda;
\n    B +=  (gidy*64+idy)*ldb+ idx;
\n    
\n   
\n    uint block_k = K >> 4;
\n    do {
\n        __local float* plA = lA + idy*65+idx;
\n        __local float* plB = lB + idx*65+idy;
\n        plB[0] = B[0];
\n        plB[16] = B[16*ldb];
\n        plB[32] = B[32*ldb];
\n        plB[48] = B[48*ldb];
\n   
\n     
\n        plA[0] = A[0+0*lda];
\n        plA[16] = A[16+0*lda];
\n        plA[32] = A[32+0*lda];
\n        plA[48] = A[48+0*lda];
\n
\n
\n        
\n        barrier(CLK_LOCAL_MEM_FENCE);
\n        uint offA = idx;
\n        uint offB = idy;
\n
\n    M4x4
\n    M4x4
\n    M4x4
\n    M4x4
\n    M4x4
\n    M4x4
\n    M4x4
\n    M4x4
\n    M4x4
\n    M4x4
\n    M4x4
\n    M4x4
\n    M4x4
\n    M4x4
\n    M4x4
\n    M4x4
\n
\n        A += lda<<4;
\n        B += 16;
\n  } while (--block_k > 0);
\n
\n    C+= gidx*64+idx;
\n    C+= gidy*64*ldc;
\n    C+= idy*ldc;
\n    
\n    C[0*ldc] = alpha*rC[0][0] ;
\n    C[16*ldc] = alpha*rC[0][1];
\n    C[32*ldc] = alpha*rC[0][2];
\n    C[48*ldc] = alpha*rC[0][3];
\n    C+=16;
\n    C[0*ldc] = alpha*rC[1][0] ;
\n    C[16*ldc] = alpha*rC[1][1];
\n    C[32*ldc] = alpha*rC[1][2];
\n    C[48*ldc] = alpha*rC[1][3];
\n    C+=16;
\n    C[0*ldc] = alpha*rC[2][0] ;
\n    C[16*ldc] = alpha*rC[2][1];
\n    C[32*ldc] = alpha*rC[2][2];
\n    C[48*ldc] = alpha*rC[2][3];
\n    C+=16;
\n    C[0*ldc] = alpha*rC[3][0] ;
\n    C[16*ldc] = alpha*rC[3][1];
\n    C[32*ldc] = alpha*rC[3][2];
\n    C[48*ldc] = alpha*rC[3][3];
\n    
\n   
\n}
);
#endif
