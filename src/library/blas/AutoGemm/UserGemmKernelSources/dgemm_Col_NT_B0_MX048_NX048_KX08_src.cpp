/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_DGEMM_COL_NT_B0_MX048_NX048_KX08_SRC_H
#define KERNEL_DGEMM_COL_NT_B0_MX048_NX048_KX08_SRC_H
#pragma message("AutoGemm's dgemm_Col_NT_B0_MX048_NX048_KX08_src overriden by user.")

#ifndef STRINGIFY
#define STRINGIFY(S) STRINGIFY2(S)
#define STRINGIFY2(S) #S
#endif

const unsigned int dgemm_Col_NT_B0_MX048_NX048_KX08_workGroupNumRows = 8;
const unsigned int dgemm_Col_NT_B0_MX048_NX048_KX08_workGroupNumCols = 8;
const unsigned int dgemm_Col_NT_B0_MX048_NX048_KX08_microTileNumRows = 6;
const unsigned int dgemm_Col_NT_B0_MX048_NX048_KX08_microTileNumCols = 6;
const unsigned int dgemm_Col_NT_B0_MX048_NX048_KX08_unroll = 8;

const char * const dgemm_Col_NT_B0_MX048_NX048_KX08_src = STRINGIFY(
_Pragma("OPENCL EXTENSION cl_khr_fp64 : enable")   \n
\n
\ntypedef union _GPtr {
\n  __global float *f;
\n  __global double *d;
\n  __global float2 *f2v;
\n  __global double2 *d2v;
\n} GPtr;
\n
#define  M6x6 \
            rA[0] = lA[offA +  0];                        \
            rA[1] = lA[offA +  1];                        \
            rA[2] = lA[offA + 16];                        \
            rA[3] = lA[offA + 17];                        \
            rA[4] = lA[offA + 32];                        \
            rA[5] = lA[offA + 33];                        \
            rB[0] = lB[offB +  0];                        \
            rB[1] = lB[offB +  1];                        \
            rB[2] = lB[offB + 16];                        \
            rB[3] = lB[offB + 17];                        \
            rB[4] = lB[offB + 32];                        \
            rB[5] = lB[offB + 33];                        \
            offA += 48;                                   \
            offB += 48;                                   \
            rC[0][0] = mad(rA[0],rB[0],rC[0][0]);         \
            rC[0][1] = mad(rA[1],rB[0],rC[0][1]);         \
            rC[0][2] = mad(rA[2],rB[0],rC[0][2]);         \
            rC[0][3] = mad(rA[3],rB[0],rC[0][3]);         \
            rC[0][4] = mad(rA[4],rB[0],rC[0][4]);         \
            rC[0][5] = mad(rA[5],rB[0],rC[0][5]);         \
            rC[1][0] = mad(rA[0],rB[1],rC[1][0]);         \
            rC[1][1] = mad(rA[1],rB[1],rC[1][1]);         \
            rC[1][2] = mad(rA[2],rB[1],rC[1][2]);         \
            rC[1][3] = mad(rA[3],rB[1],rC[1][3]);         \
            rC[1][4] = mad(rA[4],rB[1],rC[1][4]);         \
            rC[1][5] = mad(rA[5],rB[1],rC[1][5]);         \
            rC[2][0] = mad(rA[0],rB[2],rC[2][0]);         \
            rC[2][1] = mad(rA[1],rB[2],rC[2][1]);         \
            rC[2][2] = mad(rA[2],rB[2],rC[2][2]);         \
            rC[2][3] = mad(rA[3],rB[2],rC[2][3]);         \
            rC[2][4] = mad(rA[4],rB[2],rC[2][4]);         \
            rC[2][5] = mad(rA[5],rB[2],rC[2][5]);         \
            rC[3][0] = mad(rA[0],rB[3],rC[3][0]);         \
            rC[3][1] = mad(rA[1],rB[3],rC[3][1]);         \
            rC[3][2] = mad(rA[2],rB[3],rC[3][2]);         \
            rC[3][3] = mad(rA[3],rB[3],rC[3][3]);         \
            rC[3][4] = mad(rA[4],rB[3],rC[3][4]);         \
            rC[3][5] = mad(rA[5],rB[3],rC[3][5]);         \
            rC[4][0] = mad(rA[0],rB[4],rC[4][0]);         \
            rC[4][1] = mad(rA[1],rB[4],rC[4][1]);         \
            rC[4][2] = mad(rA[2],rB[4],rC[4][2]);         \
            rC[4][3] = mad(rA[3],rB[4],rC[4][3]);         \
            rC[4][4] = mad(rA[4],rB[4],rC[4][4]);         \
            rC[4][5] = mad(rA[5],rB[4],rC[4][5]);         \
            rC[5][0] = mad(rA[0],rB[5],rC[5][0]);         \
            rC[5][1] = mad(rA[1],rB[5],rC[5][1]);         \
            rC[5][2] = mad(rA[2],rB[5],rC[5][2]);         \
            rC[5][3] = mad(rA[3],rB[5],rC[5][3]);         \
            rC[5][4] = mad(rA[4],rB[5],rC[5][4]);         \
            rC[5][5] = mad(rA[5],rB[5],rC[5][5]);         \
            mem_fence(CLK_LOCAL_MEM_FENCE);\n
\n
\n
\n__attribute__((reqd_work_group_size(8,8,1)))
\n__kernel void dgemm_Col_NT_B0_MX048_NX048_KX08 (
\n    __global double2 const * restrict A,
\n    __global double2 const * restrict B,
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
\n    GPtr uA;
\n    GPtr uB;
\n    uA.d2v = (__global double2 *)A;
\n    uB.d2v = (__global double2 *)B;
\n
\n
\n    uA.d += offsetA;
\n    uB.d += offsetB;
\n    C    += offsetC;
\n
\n
\n    double rC[6][6] = { {(double)0} };
\n    double rA[6];
\n    double rB[6];
\n
\n    __local double lA[392];
\n    __local double lB[392];
\n
\n    int gidx = get_group_id(0);
\n    int gidy = get_group_id(1);
\n    int idx  = get_local_id(0);
\n    int idy  = get_local_id(1);
\n
\n
\n    uA.d += 2*(gidx*24 + idx) + idy*lda;
\n    uB.d += 2*(gidy*24 + idx) + idy*ldb;
\n
\n    int block_k = K >> 3;
\n    do {
\n        __local double2* plA = (__local double2*)(lA + idy*48 + 2*idx);
\n        __local double2* plB = (__local double2*)(lB + idy*48 + 2*idx);
\n        barrier(CLK_LOCAL_MEM_FENCE);
\n        plB[0 ] = uB.d2v[0 ];
\n        plB[8 ] = uB.d2v[8 ];
\n        plB[16] = uB.d2v[16];
\n        plA[0 ] = uA.d2v[0 ];
\n        plA[8 ] = uA.d2v[8 ];
\n        plA[16] = uA.d2v[16];
\n
\n        barrier(CLK_LOCAL_MEM_FENCE);
\n        int offA = idx << 1;
\n        int offB = idy << 1;
\n        M6x6
\n        M6x6
\n        M6x6
\n        M6x6
\n        M6x6
\n        M6x6
\n        M6x6
\n        M6x6
\n        uA.d += lda << 3;
\n        uB.d += ldb << 3;
\n    } while (--block_k > 0);
\n
\n
\n
\n    int offset_x = gidx*48+ idx*2;
\n    int offset_y = gidy*48+ idy*2;
\n    (C[(offset_x +  0) + (offset_y +  0) * ldc] = alpha * rC[0][0]);
\n    (C[(offset_x +  1) + (offset_y +  0) * ldc] = alpha * rC[0][1]);
\n    (C[(offset_x +  0) + (offset_y +  1) * ldc] = alpha * rC[1][0]);
\n    (C[(offset_x +  1) + (offset_y +  1) * ldc] = alpha * rC[1][1]);
\n    (C[(offset_x +  0) + (offset_y + 16) * ldc] = alpha * rC[2][0]);
\n    (C[(offset_x +  1) + (offset_y + 16) * ldc] = alpha * rC[2][1]);
\n    (C[(offset_x +  0) + (offset_y + 17) * ldc] = alpha * rC[3][0]);
\n    (C[(offset_x +  1) + (offset_y + 17) * ldc] = alpha * rC[3][1]);
\n    (C[(offset_x +  0) + (offset_y + 32) * ldc] = alpha * rC[4][0]);
\n    (C[(offset_x +  1) + (offset_y + 32) * ldc] = alpha * rC[4][1]);
\n    (C[(offset_x +  0) + (offset_y + 33) * ldc] = alpha * rC[5][0]);
\n    (C[(offset_x +  1) + (offset_y + 33) * ldc] = alpha * rC[5][1]);
\n    (C[(offset_x + 16) + (offset_y +  0) * ldc] = alpha * rC[0][2]);
\n    (C[(offset_x + 17) + (offset_y +  0) * ldc] = alpha * rC[0][3]);
\n    (C[(offset_x + 16) + (offset_y +  1) * ldc] = alpha * rC[1][2]);
\n    (C[(offset_x + 17) + (offset_y +  1) * ldc] = alpha * rC[1][3]);
\n    (C[(offset_x + 16) + (offset_y + 16) * ldc] = alpha * rC[2][2]);
\n    (C[(offset_x + 17) + (offset_y + 16) * ldc] = alpha * rC[2][3]);
\n    (C[(offset_x + 16) + (offset_y + 17) * ldc] = alpha * rC[3][2]);
\n    (C[(offset_x + 17) + (offset_y + 17) * ldc] = alpha * rC[3][3]);
\n    (C[(offset_x + 16) + (offset_y + 32) * ldc] = alpha * rC[4][2]);
\n    (C[(offset_x + 17) + (offset_y + 32) * ldc] = alpha * rC[4][3]);
\n    (C[(offset_x + 16) + (offset_y + 33) * ldc] = alpha * rC[5][2]);
\n    (C[(offset_x + 17) + (offset_y + 33) * ldc] = alpha * rC[5][3]);
\n    (C[(offset_x + 32) + (offset_y +  0) * ldc] = alpha * rC[0][4]);
\n    (C[(offset_x + 33) + (offset_y +  0) * ldc] = alpha * rC[0][5]);
\n    (C[(offset_x + 32) + (offset_y +  1) * ldc] = alpha * rC[1][4]);
\n    (C[(offset_x + 33) + (offset_y +  1) * ldc] = alpha * rC[1][5]);
\n    (C[(offset_x + 32) + (offset_y + 16) * ldc] = alpha * rC[2][4]);
\n    (C[(offset_x + 33) + (offset_y + 16) * ldc] = alpha * rC[2][5]);
\n    (C[(offset_x + 32) + (offset_y + 17) * ldc] = alpha * rC[3][4]);
\n    (C[(offset_x + 33) + (offset_y + 17) * ldc] = alpha * rC[3][5]);
\n    (C[(offset_x + 32) + (offset_y + 32) * ldc] = alpha * rC[4][4]);
\n    (C[(offset_x + 33) + (offset_y + 32) * ldc] = alpha * rC[4][5]);
\n    (C[(offset_x + 32) + (offset_y + 33) * ldc] = alpha * rC[5][4]);
\n    (C[(offset_x + 33) + (offset_y + 33) * ldc] = alpha * rC[5][5]);
\n}
);
#endif
