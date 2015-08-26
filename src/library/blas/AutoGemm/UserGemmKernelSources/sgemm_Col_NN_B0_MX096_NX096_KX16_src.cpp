/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_SGEMM_COL_NN_B0_MX096_NX096_KX16_SRC_C
#define KERNEL_SGEMM_COL_NN_B0_MX096_NX096_KX16_SRC_C

#ifndef STRINGIFY
#define STRINGIFY(S) STRINGIFY2(S)
#define STRINGIFY2(S) #S
#endif

const unsigned int sgemm_Col_NN_B0_MX096_NX096_KX16_workGroupNumRows = 16;
const unsigned int sgemm_Col_NN_B0_MX096_NX096_KX16_workGroupNumCols = 16;
const unsigned int sgemm_Col_NN_B0_MX096_NX096_KX16_microTileNumRows = 6;
const unsigned int sgemm_Col_NN_B0_MX096_NX096_KX16_microTileNumCols = 6;
const unsigned int sgemm_Col_NN_B0_MX096_NX096_KX16_unroll = 16;

const char * const sgemm_Col_NN_B0_MX096_NX096_KX16_src = STRINGIFY(
\n
\n#define  M6x6 \
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
			barrier(CLK_LOCAL_MEM_FENCE);\n
\n
\n__attribute__((reqd_work_group_size(16,16,1)))
\n__kernel void sgemm_Col_NN_B0_MX096_NX096_KX16 (
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
\n    float rC[6][6]  = {(float)0};
\n    float rA[1][6];
\n    float rB[1][6];
\n    
\n
\n    
\n    A += offsetA;
\n    B += offsetB;
\n    C+=offsetC;
\n    
\n    __local float lA[1552];
\n    __local float lB[1552];
\n    
\n    uint gidx = get_group_id(0);
\n    uint gidy = get_group_id(1);
\n    uint idx = get_local_id(0);
\n    uint idy = get_local_id(1);
\n
\n    A +=  gidx*96+ idx + idy*lda;
\n    B +=  gidy*96*ldb+ idx + idy*ldb;
\n    
\n   
\n    uint block_k = K >> 4;
\n    do 
\n	{
\n        __local float* plA = lA + idy*97+idx;
\n        __local float* plB = lB + idx*97+idy;
\n        barrier(CLK_LOCAL_MEM_FENCE);
\n        plB[0] = B[0];
\n        plB[16] = B[16*ldb];
\n        plB[32] = B[32*ldb];
\n        plB[48] = B[48*ldb];
\n        plB[64] = B[64*ldb];
\n        plB[80] = B[80*ldb];
\n	   
\n	    plA[0] = A[0+0*lda];
\n        plA[16] = A[16+0*lda];
\n        plA[32] = A[32+0*lda];
\n        plA[48] = A[48+0*lda];
\n        plA[64] = A[64+0*lda];
\n        plA[80] = A[80+0*lda];
\n
\n        
\n        barrier(CLK_LOCAL_MEM_FENCE);
\n        uint offA = idx;
\n        uint offB = idy;
\n
\n    M6x6
\n		M6x6
\n		M6x6
\n		M6x6
\n		M6x6
\n		M6x6
\n		M6x6
\n		M6x6
\n		M6x6
\n		M6x6
\n		M6x6
\n		M6x6
\n		M6x6
\n		M6x6
\n		M6x6
\n		M6x6
\n
\n        A += lda<<4;
\n        B += 16;
\n	} while (--block_k > 0);
\n
\n    C+= gidx*96+idx;
\n    C+= gidy*96*ldc;
\n    C+= idy*ldc;
\n    
\n    C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
\n    C[16*ldc] = alpha*rC[0][1] + beta*C[16*ldc];
\n    C[32*ldc] = alpha*rC[0][2] + beta*C[32*ldc];
\n    C[48*ldc] = alpha*rC[0][3] + beta*C[48*ldc];
\n    C[64*ldc] = alpha*rC[0][4] + beta*C[64*ldc];
\n    C[80*ldc] = alpha*rC[0][5] + beta*C[80*ldc];
\n    C+=16;
\n    C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
\n    C[16*ldc] = alpha*rC[1][1] + beta*C[16*ldc];
\n    C[32*ldc] = alpha*rC[1][2] + beta*C[32*ldc];
\n    C[48*ldc] = alpha*rC[1][3] + beta*C[48*ldc];
\n    C[64*ldc] = alpha*rC[1][4] + beta*C[64*ldc];
\n    C[80*ldc] = alpha*rC[1][5] + beta*C[80*ldc];
\n    C+=16;
\n    C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
\n    C[16*ldc] = alpha*rC[2][1] + beta*C[16*ldc];
\n    C[32*ldc] = alpha*rC[2][2] + beta*C[32*ldc];
\n    C[48*ldc] = alpha*rC[2][3] + beta*C[48*ldc];
\n    C[64*ldc] = alpha*rC[2][4] + beta*C[64*ldc];
\n    C[80*ldc] = alpha*rC[2][5] + beta*C[80*ldc];
\n    C+=16;
\n    C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
\n    C[16*ldc] = alpha*rC[3][1] + beta*C[16*ldc];
\n    C[32*ldc] = alpha*rC[3][2] + beta*C[32*ldc];
\n    C[48*ldc] = alpha*rC[3][3] + beta*C[48*ldc];
\n    C[64*ldc] = alpha*rC[3][4] + beta*C[64*ldc];
\n    C[80*ldc] = alpha*rC[3][5] + beta*C[80*ldc];
\n    C+=16;
\n    C[0*ldc] = alpha*rC[4][0] + beta*C[0*ldc];
\n    C[16*ldc] = alpha*rC[4][1] + beta*C[16*ldc];
\n    C[32*ldc] = alpha*rC[4][2] + beta*C[32*ldc];
\n    C[48*ldc] = alpha*rC[4][3] + beta*C[48*ldc];
\n    C[64*ldc] = alpha*rC[4][4] + beta*C[64*ldc];
\n    C[80*ldc] = alpha*rC[4][5] + beta*C[80*ldc];
\n    C+=16;
\n    C[0*ldc] = alpha*rC[5][0] + beta*C[0*ldc];
\n    C[16*ldc] = alpha*rC[5][1] + beta*C[16*ldc];
\n    C[32*ldc] = alpha*rC[5][2] + beta*C[32*ldc];
\n    C[48*ldc] = alpha*rC[5][3] + beta*C[48*ldc];
\n    C[64*ldc] = alpha*rC[5][4] + beta*C[64*ldc];
\n    C[80*ldc] = alpha*rC[5][5] + beta*C[80*ldc];
\n
\n}
);
#endif
