/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_SGEMM_COL_NN_B0_MX032_NX032_KX16_SRC_C
#define KERNEL_SGEMM_COL_NN_B0_MX032_NX032_KX16_SRC_C

#ifndef STRINGIFY
#define STRINGIFY(S) STRINGIFY2(S)
#define STRINGIFY2(S) #S
#endif

const unsigned int sgemm_Col_NN_B0_MX032_NX032_KX16_workGroupNumRows = 16;
const unsigned int sgemm_Col_NN_B0_MX032_NX032_KX16_workGroupNumCols = 16;
const unsigned int sgemm_Col_NN_B0_MX032_NX032_KX16_microTileNumRows = 2;
const unsigned int sgemm_Col_NN_B0_MX032_NX032_KX16_microTileNumCols = 2;
const unsigned int sgemm_Col_NN_B0_MX032_NX032_KX16_unroll = 16;

const char * const sgemm_Col_NN_B0_MX032_NX032_KX16_src = STRINGIFY(
\n
\n#define  M2x2 \\
\n            rA[0][0] = lA[offA + 0];				  \\
\n            rA[0][1] = lA[offA + 16];				  \\
\n            rB[0][0] = lB[offB + 0];				  \\
\n            rB[0][1] = lB[offB + 16];				  \\
\n            offA += 33;								  \\
\n            offB += 33;								  \\
\n            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]); \\
\n            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]); \\
\n            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]); \\
\n            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]); \\
\n			barrier(CLK_LOCAL_MEM_FENCE);\n
\n
\n__attribute__((reqd_work_group_size(16,16,1)))
\n__kernel void sgemm_Col_NN_B0_MX032_NX032_KX16 (
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
\n    float rC[2][2]  = {(float)0};
\n    float rA[1][2];
\n    float rB[1][2];
\n    
\n    
\n    A += offsetA;
\n    B += offsetB;
\n    C+=offsetC;
\n    
\n    __local float lA[544];
\n    __local float lB[544];
\n    
\n    uint gidx = get_group_id(0);
\n    uint gidy = get_group_id(1);
\n    uint idx = get_local_id(0);
\n    uint idy = get_local_id(1);
\n    
\n    uint idt = 16*idy + idx;
\n    uint idxT = idt % 16;
\n    uint idyT = idt / 16;
\n    
\n    A +=  gidx*32+ idxT + idyT*lda;
\n    B +=  (gidy*32+idyT)*ldb + idxT;
\n    
\n   
\n  uint block_k = K >> 4;
\n  do 
\n	{
\n    __local float* plA = lA + idyT*33+idxT;
\n    __local float* plB = lB + idxT*33+idyT;
\n    plB[0] = B[0];
\n    plB[16] = B[16*ldb];
\n        
\n	  plA[0] = A[0+0*lda];
\n    plA[16] = A[16+0*lda];
\n       
\n        
\n    barrier(CLK_LOCAL_MEM_FENCE);
\n    uint offA = idx;
\n    uint offB = idy;
\n
\n
\n    M2x2
\n		M2x2
\n		M2x2
\n		M2x2
\n		M2x2
\n		M2x2
\n		M2x2
\n		M2x2
\n		M2x2
\n		M2x2
\n		M2x2
\n		M2x2
\n		M2x2
\n		M2x2
\n		M2x2
\n		M2x2
\n
\n    A += lda<<4;
\n    B += 16;
\n   
\n	} while (--block_k > 0);
\n
\n    C+= gidx*32+idx;
\n    C+= gidy*32*ldc;
\n    C+= idy*ldc;
\n    
\n	  C[0*ldc] = alpha*rC[0][0] ;
\n    C[16*ldc] = alpha*rC[0][1];
\n    C+=16;					  
\n    C[0*ldc] = alpha*rC[1][0] ;
\n    C[16*ldc] = alpha*rC[1][1]; 
}
\n
\n);
#endif
