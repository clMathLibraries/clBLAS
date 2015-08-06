/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_DGEMM_COL_NT_B0_MX048_NX048_KX08_SRC_H
#define KERNEL_DGEMM_COL_NT_B0_MX048_NX048_KX08_SRC_H

#ifndef STRINGIFY
#define STRINGIFY(S) STRINGIFY2(S)
#define STRINGIFY2(S) #S
#endif

const unsigned int dgemm_Col_NT_B0_MX048_NX048_KX08_workGroupNumRows = 8;
const unsigned int dgemm_Col_NT_B0_MX048_NX048_KX08_workGroupNumCols = 8;
const unsigned int dgemm_Col_NT_B0_MX048_NX048_KX08_microTileNumRows = 6;
const unsigned int dgemm_Col_NT_B0_MX048_NX048_KX08_microTileNumCols = 6;
const unsigned int dgemm_Col_NT_B0_MX048_NX048_KX08_unroll = 8;

static const char * const dgemm_Col_NT_B0_MX048_NX048_KX08_src = STRINGIFY(

typedef union GPtr {
  __global float *f;
  __global double *d;
  __global float2 *f2v;
  __global double2 *d2v;
} GPtr;


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
            barrier(CLK_LOCAL_MEM_FENCE);\n


__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_Col_NT_B0_MX048_NX048_KX08 (
    __global double2 const * restrict A,
    __global double2 const * restrict B,
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
    GPtr uA, uB;
    uA.d2v = (__global double2 *)A;
    uB.d2v = (__global double2 *)B;
 //   C += offsetC;


    uA.d += offsetA;
    uB.d += offsetB;
    C    += offsetC;


    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];

    __local double lA[392];
    __local double lB[392];

    int gidx = get_group_id(0);
    int gidy = get_group_id(1);
    int idx  = get_local_id(0);
    int idy  = get_local_id(1);


    uA.d += 2*(gidx*24 + idx) + idy*lda;
    uB.d += 2*(gidy*24 + idx) + idy*ldb;

    int block_k = K >> 3;
    do {
        __local double2* plA = (__local double2*)(lA + idy*48 + 2*idx);
        __local double2* plB = (__local double2*)(lB + idy*48 + 2*idx);
//        barrier(CLK_LOCAL_MEM_FENCE);
        plB[0 ] = uB.d2v[0 ];
        plB[8 ] = uB.d2v[8 ];
        plB[16] = uB.d2v[16];
        plA[0 ] = uA.d2v[0 ];
        plA[8 ] = uA.d2v[8 ];
        plA[16] = uA.d2v[16];

        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx << 1;
        int offB = idy << 1;
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        uA.d += lda << 3;
        uB.d += ldb << 3;
    } while (--block_k > 0);



    int offset_x = gidx*48+ idx*2;
    int offset_y = gidy*48+ idy*2;
    (C[(offset_x +  0) + (offset_y +  0) * ldc] = alpha * rC[0][0]);
    (C[(offset_x +  1) + (offset_y +  0) * ldc] = alpha * rC[0][1]);
    (C[(offset_x +  0) + (offset_y +  1) * ldc] = alpha * rC[1][0]);
    (C[(offset_x +  1) + (offset_y +  1) * ldc] = alpha * rC[1][1]);
    (C[(offset_x +  0) + (offset_y + 16) * ldc] = alpha * rC[2][0]);
    (C[(offset_x +  1) + (offset_y + 16) * ldc] = alpha * rC[2][1]);
    (C[(offset_x +  0) + (offset_y + 17) * ldc] = alpha * rC[3][0]);
    (C[(offset_x +  1) + (offset_y + 17) * ldc] = alpha * rC[3][1]);
    (C[(offset_x +  0) + (offset_y + 32) * ldc] = alpha * rC[4][0]);
    (C[(offset_x +  1) + (offset_y + 32) * ldc] = alpha * rC[4][1]);
    (C[(offset_x +  0) + (offset_y + 33) * ldc] = alpha * rC[5][0]);
    (C[(offset_x +  1) + (offset_y + 33) * ldc] = alpha * rC[5][1]);
    (C[(offset_x + 16) + (offset_y +  0) * ldc] = alpha * rC[0][2]);
    (C[(offset_x + 17) + (offset_y +  0) * ldc] = alpha * rC[0][3]);
    (C[(offset_x + 16) + (offset_y +  1) * ldc] = alpha * rC[1][2]);
    (C[(offset_x + 17) + (offset_y +  1) * ldc] = alpha * rC[1][3]);
    (C[(offset_x + 16) + (offset_y + 16) * ldc] = alpha * rC[2][2]);
    (C[(offset_x + 17) + (offset_y + 16) * ldc] = alpha * rC[2][3]);
    (C[(offset_x + 16) + (offset_y + 17) * ldc] = alpha * rC[3][2]);
    (C[(offset_x + 17) + (offset_y + 17) * ldc] = alpha * rC[3][3]);
    (C[(offset_x + 16) + (offset_y + 32) * ldc] = alpha * rC[4][2]);
    (C[(offset_x + 17) + (offset_y + 32) * ldc] = alpha * rC[4][3]);
    (C[(offset_x + 16) + (offset_y + 33) * ldc] = alpha * rC[5][2]);
    (C[(offset_x + 17) + (offset_y + 33) * ldc] = alpha * rC[5][3]);
    (C[(offset_x + 32) + (offset_y +  0) * ldc] = alpha * rC[0][4]);
    (C[(offset_x + 33) + (offset_y +  0) * ldc] = alpha * rC[0][5]);
    (C[(offset_x + 32) + (offset_y +  1) * ldc] = alpha * rC[1][4]);
    (C[(offset_x + 33) + (offset_y +  1) * ldc] = alpha * rC[1][5]);
    (C[(offset_x + 32) + (offset_y + 16) * ldc] = alpha * rC[2][4]);
    (C[(offset_x + 33) + (offset_y + 16) * ldc] = alpha * rC[2][5]);
    (C[(offset_x + 32) + (offset_y + 17) * ldc] = alpha * rC[3][4]);
    (C[(offset_x + 33) + (offset_y + 17) * ldc] = alpha * rC[3][5]);
    (C[(offset_x + 32) + (offset_y + 32) * ldc] = alpha * rC[4][4]);
    (C[(offset_x + 33) + (offset_y + 32) * ldc] = alpha * rC[4][5]);
    (C[(offset_x + 32) + (offset_y + 33) * ldc] = alpha * rC[5][4]);
    (C[(offset_x + 33) + (offset_y + 33) * ldc] = alpha * rC[5][5]);
}
);
