/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_SGEMM_COL_NN_B1_MX032_NX032_KX16_BRANCH_SRC_H
#define KERNEL_SGEMM_COL_NN_B1_MX032_NX032_KX16_BRANCH_SRC_H
#pragma message("AutoGemm's sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_src (if exists) overriden by user.")

#ifndef STRINGIFY
#define STRINGIFY(S) STRINGIFY2(S)
#define STRINGIFY2(S) #S
#endif

const unsigned int sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_workGroupNumRows = 16;
const unsigned int sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_workGroupNumCols = 16;
const unsigned int sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_microTileNumRows = 2;
const unsigned int sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_microTileNumCols = 2;
const unsigned int sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_unroll = 16;

#ifndef AUTOGEMM_USE_PRE_COMPILED_KERNELS
unsigned char *sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_bin = 0;
size_t sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_binSize = 0;
#endif

const char * const sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_src = STRINGIFY(

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
__kernel void sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH (
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

    __local float lA[528];//16*32+16
    __local float lB[528];

    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);

	int CurrentOffSetA = gidx*32+ idx;
	int CurrentOffSetB = gidy*32+ idy;

    A +=  gidx*32+ idx + idy*lda;
    B +=  gidy*32*ldb+ idx + idy*ldb;


    uint block_k = K >> 4;
    do
	{
        __local float* plA = lA + idy*33+idx;
        __local float* plB = lB + idx*33+idy;
        barrier(CLK_LOCAL_MEM_FENCE);

        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];

	    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];


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
        B += 16;
    //}
	} while (--block_k > 0);

	int offset_x = gidx*32+idx;
    int offset_y = gidy*32+ idy;
    if(offset_x>=M || offset_y>=N )
      return;

    C+=offset_x+offset_y*ldc;


	int i = 0;
    if (beta != 0) {
      do
      {
        C[0     ] = mad(alpha, rC[i][0], beta*C[0]);
        if(offset_y+16<N)
          C[16*ldc] = mad(alpha, rC[i][1], beta*C[16*ldc]);
          C+=16;
          offset_x+=16;
          if(offset_x>=M )
            return;
      }
      while (++i < 2);
    } else {
      do
      {
        C[0     ] = alpha * rC[i][0];
        if(offset_y+16<N)
          C[16*ldc] = alpha * rC[i][1];
        C+=16;
        offset_x+=16;
        if(offset_x>=M )
          return;
      }
      while (++i < 2);
    }
}

);
#endif
