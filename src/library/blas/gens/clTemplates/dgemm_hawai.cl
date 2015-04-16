
// DGEMM kernels for Hawai & Tahiti 
//
// All kernels are ColumnMajor. The case RowMajor is handled by an earlier transformation 
// into an equivalent ColumnMajor (using the property that (A*B)' is equal to B'A' that the 
// conversion from Row to Column major is basically a transpose) 
//
// The naming scheme for the kernels is dgemm_<ta><tb>_<divn>_<divm>_<divk>_<bs0>x<bs1>_<nv0>x<nv1> where 
//    - <ta> is N or T representing the transpose operation on A
//    - <tb> is N or T representing the transpose operation on B
//    - <divn> is a required divisor of N (1 for any value)
//    - <divm> is a required divisor of M (1 for any value)
//    - <divk> is a required divisor of K (1 for any value)
//    - <bs0>x<bs1> is the block size
//    - <nv0>x<nv1> is the number of points computed per work-item
//
// For instance a kernel named 'dgemm_NT_16_32_1_8x8_2x4' 
//    - would implement C = C + A * B' 
//    - for N multiple of 16
//    - for M multiple of 32 
//    - for any value of K
//    - using work-groups of size (8,8)
//    - with each thread computing 2x4 points of C 
//
//
// The kernel prototype shall be compatible with
//
//    __kernel void dgemm( __global double const * restrict A, 
//                         __global double const * restrict B, 
//                         __global double * C,
//                         uint   M, 
//                         uint   N, 
//                         uint   K,
//                         double alpha,  
//                         double beta,   
//                         uint   lda,
//                         uint   ldb, 
//                         uint   ldc, 
//                         uint   offsetA, 
//                         uint   offsetB , 
//                         uint   offsetC 
//                       )
//
//
//
//
//


// =====  dgemm_NT_MN48.cl
static const char * dgemm_NT_48_48_8_8x8_6x6__ALPHABETA = "

typedef union GPtr {
  __global float *f;
  __global double *d;
  __global float2 *f2v;
  __global double2 *d2v;
} GPtr;



__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_48_48_8_8x8_6x6__ALPHABETA(__global double2 const * restrict A,
                                       __global double2 const * restrict B,
                                       __global double * C,
                                       uint const M,
                                       uint const N,
                                       uint const K,
                                       double const alpha,
                                       double const beta,
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

    uint block_k = K >> 3;
    do {
        __local double* plA = lA + idy*48 + 2*idx;
        __local double* plB = lB + idy*48 + 2*idx;
        barrier(CLK_LOCAL_MEM_FENCE);
        vstore2( uA.d2v[0 ], 0, plA+0  );
        vstore2( uA.d2v[8 ], 0, plA+16 );
        vstore2( uA.d2v[16], 0, plA+32 );
        vstore2( uB.d2v[0 ], 0, plB+0  );
        vstore2( uB.d2v[8 ], 0, plB+16 );
        vstore2( uB.d2v[16], 0, plB+32 );
        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx << 1;
        int offB = idy << 1;
       
	    #pragma unroll 1
        for(uint k = 0 ; k < 8; k+=1)
        {
            rA[0] = lA[offA +  0];
            rA[1] = lA[offA +  1];
            rA[2] = lA[offA + 16];
            rA[3] = lA[offA + 17];
            rA[4] = lA[offA + 32];
            rA[5] = lA[offA + 33];
            rB[0] = lB[offB +  0];
            rB[1] = lB[offB +  1];
            rB[2] = lB[offB + 16];
            rB[3] = lB[offB + 17];
            rB[4] = lB[offB + 32];
            rB[5] = lB[offB + 33];
            offA += 48;
            offB += 48;
            rC[0][0] = mad(rA[0],rB[0],rC[0][0]);
            rC[0][1] = mad(rA[1],rB[0],rC[0][1]);
            rC[0][2] = mad(rA[2],rB[0],rC[0][2]);
            rC[0][3] = mad(rA[3],rB[0],rC[0][3]);
            rC[0][4] = mad(rA[4],rB[0],rC[0][4]);
            rC[0][5] = mad(rA[5],rB[0],rC[0][5]);
            rC[1][0] = mad(rA[0],rB[1],rC[1][0]);
            rC[1][1] = mad(rA[1],rB[1],rC[1][1]);
            rC[1][2] = mad(rA[2],rB[1],rC[1][2]);
            rC[1][3] = mad(rA[3],rB[1],rC[1][3]);
            rC[1][4] = mad(rA[4],rB[1],rC[1][4]);
            rC[1][5] = mad(rA[5],rB[1],rC[1][5]);
            rC[2][0] = mad(rA[0],rB[2],rC[2][0]);
            rC[2][1] = mad(rA[1],rB[2],rC[2][1]);
            rC[2][2] = mad(rA[2],rB[2],rC[2][2]);
            rC[2][3] = mad(rA[3],rB[2],rC[2][3]);
            rC[2][4] = mad(rA[4],rB[2],rC[2][4]);
            rC[2][5] = mad(rA[5],rB[2],rC[2][5]);
            rC[3][0] = mad(rA[0],rB[3],rC[3][0]);
            rC[3][1] = mad(rA[1],rB[3],rC[3][1]);
            rC[3][2] = mad(rA[2],rB[3],rC[3][2]);
            rC[3][3] = mad(rA[3],rB[3],rC[3][3]);
            rC[3][4] = mad(rA[4],rB[3],rC[3][4]);
            rC[3][5] = mad(rA[5],rB[3],rC[3][5]);
            rC[4][0] = mad(rA[0],rB[4],rC[4][0]);
            rC[4][1] = mad(rA[1],rB[4],rC[4][1]);
            rC[4][2] = mad(rA[2],rB[4],rC[4][2]);
            rC[4][3] = mad(rA[3],rB[4],rC[4][3]);
            rC[4][4] = mad(rA[4],rB[4],rC[4][4]);
            rC[4][5] = mad(rA[5],rB[4],rC[4][5]);
            rC[5][0] = mad(rA[0],rB[5],rC[5][0]);
            rC[5][1] = mad(rA[1],rB[5],rC[5][1]);
            rC[5][2] = mad(rA[2],rB[5],rC[5][2]);
            rC[5][3] = mad(rA[3],rB[5],rC[5][3]);
            rC[5][4] = mad(rA[4],rB[5],rC[5][4]);
            rC[5][5] = mad(rA[5],rB[5],rC[5][5]);
        }
        uA.d += lda << 3;
        uB.d += ldb << 3;
    } while (--block_k > 0);



    int offset_x = gidx*48+ idx*2;
    int offset_y = gidy*48+ idy*2;
    (C[(offset_x +  0) + (offset_y +  0) * ldc] = mad(beta, C[(offset_x +  0) + (offset_y +  0) * ldc], alpha * rC[0][0]));
    (C[(offset_x +  1) + (offset_y +  0) * ldc] = mad(beta, C[(offset_x +  1) + (offset_y +  0) * ldc], alpha * rC[0][1]));
    (C[(offset_x +  0) + (offset_y +  1) * ldc] = mad(beta, C[(offset_x +  0) + (offset_y +  1) * ldc], alpha * rC[1][0]));
    (C[(offset_x +  1) + (offset_y +  1) * ldc] = mad(beta, C[(offset_x +  1) + (offset_y +  1) * ldc], alpha * rC[1][1]));
    (C[(offset_x +  0) + (offset_y + 16) * ldc] = mad(beta, C[(offset_x +  0) + (offset_y + 16) * ldc], alpha * rC[2][0]));
    (C[(offset_x +  1) + (offset_y + 16) * ldc] = mad(beta, C[(offset_x +  1) + (offset_y + 16) * ldc], alpha * rC[2][1]));
    (C[(offset_x +  0) + (offset_y + 17) * ldc] = mad(beta, C[(offset_x +  0) + (offset_y + 17) * ldc], alpha * rC[3][0]));
    (C[(offset_x +  1) + (offset_y + 17) * ldc] = mad(beta, C[(offset_x +  1) + (offset_y + 17) * ldc], alpha * rC[3][1]));
    (C[(offset_x +  0) + (offset_y + 32) * ldc] = mad(beta, C[(offset_x +  0) + (offset_y + 32) * ldc], alpha * rC[4][0]));
    (C[(offset_x +  1) + (offset_y + 32) * ldc] = mad(beta, C[(offset_x +  1) + (offset_y + 32) * ldc], alpha * rC[4][1]));
    (C[(offset_x +  0) + (offset_y + 33) * ldc] = mad(beta, C[(offset_x +  0) + (offset_y + 33) * ldc], alpha * rC[5][0]));
    (C[(offset_x +  1) + (offset_y + 33) * ldc] = mad(beta, C[(offset_x +  1) + (offset_y + 33) * ldc], alpha * rC[5][1]));
    (C[(offset_x + 16) + (offset_y +  0) * ldc] = mad(beta, C[(offset_x + 16) + (offset_y +  0) * ldc], alpha * rC[0][2]));
    (C[(offset_x + 17) + (offset_y +  0) * ldc] = mad(beta, C[(offset_x + 17) + (offset_y +  0) * ldc], alpha * rC[0][3]));
    (C[(offset_x + 16) + (offset_y +  1) * ldc] = mad(beta, C[(offset_x + 16) + (offset_y +  1) * ldc], alpha * rC[1][2]));
    (C[(offset_x + 17) + (offset_y +  1) * ldc] = mad(beta, C[(offset_x + 17) + (offset_y +  1) * ldc], alpha * rC[1][3]));
    (C[(offset_x + 16) + (offset_y + 16) * ldc] = mad(beta, C[(offset_x + 16) + (offset_y + 16) * ldc], alpha * rC[2][2]));
    (C[(offset_x + 17) + (offset_y + 16) * ldc] = mad(beta, C[(offset_x + 17) + (offset_y + 16) * ldc], alpha * rC[2][3]));
    (C[(offset_x + 16) + (offset_y + 17) * ldc] = mad(beta, C[(offset_x + 16) + (offset_y + 17) * ldc], alpha * rC[3][2]));
    (C[(offset_x + 17) + (offset_y + 17) * ldc] = mad(beta, C[(offset_x + 17) + (offset_y + 17) * ldc], alpha * rC[3][3]));
    (C[(offset_x + 16) + (offset_y + 32) * ldc] = mad(beta, C[(offset_x + 16) + (offset_y + 32) * ldc], alpha * rC[4][2]));
    (C[(offset_x + 17) + (offset_y + 32) * ldc] = mad(beta, C[(offset_x + 17) + (offset_y + 32) * ldc], alpha * rC[4][3]));
    (C[(offset_x + 16) + (offset_y + 33) * ldc] = mad(beta, C[(offset_x + 16) + (offset_y + 33) * ldc], alpha * rC[5][2]));
    (C[(offset_x + 17) + (offset_y + 33) * ldc] = mad(beta, C[(offset_x + 17) + (offset_y + 33) * ldc], alpha * rC[5][3]));
    (C[(offset_x + 32) + (offset_y +  0) * ldc] = mad(beta, C[(offset_x + 32) + (offset_y +  0) * ldc], alpha * rC[0][4]));
    (C[(offset_x + 33) + (offset_y +  0) * ldc] = mad(beta, C[(offset_x + 33) + (offset_y +  0) * ldc], alpha * rC[0][5]));
    (C[(offset_x + 32) + (offset_y +  1) * ldc] = mad(beta, C[(offset_x + 32) + (offset_y +  1) * ldc], alpha * rC[1][4]));
    (C[(offset_x + 33) + (offset_y +  1) * ldc] = mad(beta, C[(offset_x + 33) + (offset_y +  1) * ldc], alpha * rC[1][5]));
    (C[(offset_x + 32) + (offset_y + 16) * ldc] = mad(beta, C[(offset_x + 32) + (offset_y + 16) * ldc], alpha * rC[2][4]));
    (C[(offset_x + 33) + (offset_y + 16) * ldc] = mad(beta, C[(offset_x + 33) + (offset_y + 16) * ldc], alpha * rC[2][5]));
    (C[(offset_x + 32) + (offset_y + 17) * ldc] = mad(beta, C[(offset_x + 32) + (offset_y + 17) * ldc], alpha * rC[3][4]));
    (C[(offset_x + 33) + (offset_y + 17) * ldc] = mad(beta, C[(offset_x + 33) + (offset_y + 17) * ldc], alpha * rC[3][5]));
    (C[(offset_x + 32) + (offset_y + 32) * ldc] = mad(beta, C[(offset_x + 32) + (offset_y + 32) * ldc], alpha * rC[4][4]));
    (C[(offset_x + 33) + (offset_y + 32) * ldc] = mad(beta, C[(offset_x + 33) + (offset_y + 32) * ldc], alpha * rC[4][5]));
    (C[(offset_x + 32) + (offset_y + 33) * ldc] = mad(beta, C[(offset_x + 32) + (offset_y + 33) * ldc], alpha * rC[5][4]));
    (C[(offset_x + 33) + (offset_y + 33) * ldc] = mad(beta, C[(offset_x + 33) + (offset_y + 33) * ldc], alpha * rC[5][5]));
}


";

static const char * dgemm_NT_48_48_8_8x8_6x6__ALPHA = "

typedef union GPtr {
  __global float *f;
  __global double *d;
  __global float2 *f2v;
  __global double2 *d2v;
} GPtr;

__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_48_48_8_8x8_6x6__ALPHA(__global double2 const * restrict A,
                                       __global double2 const * restrict B,
                                       __global double * C,
                                       uint const M,
                                       uint const N,
                                       uint const K,
                                       double const alpha,
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

    uint block_k = K >> 3;
    do {
        __local double* plA = lA + idy*48 + 2*idx;
        __local double* plB = lB + idy*48 + 2*idx;
        barrier(CLK_LOCAL_MEM_FENCE);
        vstore2( uA.d2v[0 ], 0, plA+0  );
        vstore2( uA.d2v[8 ], 0, plA+16 );
        vstore2( uA.d2v[16], 0, plA+32 );
        vstore2( uB.d2v[0 ], 0, plB+0  );
        vstore2( uB.d2v[8 ], 0, plB+16 );
        vstore2( uB.d2v[16], 0, plB+32 );
        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx << 1;
        int offB = idy << 1;
       
	    #pragma unroll 1
        for(uint k = 0 ; k < 8; k+=1)
        {
            rA[0] = lA[offA +  0];
            rA[1] = lA[offA +  1];
            rA[2] = lA[offA + 16];
            rA[3] = lA[offA + 17];
            rA[4] = lA[offA + 32];
            rA[5] = lA[offA + 33];
            rB[0] = lB[offB +  0];
            rB[1] = lB[offB +  1];
            rB[2] = lB[offB + 16];
            rB[3] = lB[offB + 17];
            rB[4] = lB[offB + 32];
            rB[5] = lB[offB + 33];
            offA += 48;
            offB += 48;
            rC[0][0] = mad(rA[0],rB[0],rC[0][0]);
            rC[0][1] = mad(rA[1],rB[0],rC[0][1]);
            rC[0][2] = mad(rA[2],rB[0],rC[0][2]);
            rC[0][3] = mad(rA[3],rB[0],rC[0][3]);
            rC[0][4] = mad(rA[4],rB[0],rC[0][4]);
            rC[0][5] = mad(rA[5],rB[0],rC[0][5]);
            rC[1][0] = mad(rA[0],rB[1],rC[1][0]);
            rC[1][1] = mad(rA[1],rB[1],rC[1][1]);
            rC[1][2] = mad(rA[2],rB[1],rC[1][2]);
            rC[1][3] = mad(rA[3],rB[1],rC[1][3]);
            rC[1][4] = mad(rA[4],rB[1],rC[1][4]);
            rC[1][5] = mad(rA[5],rB[1],rC[1][5]);
            rC[2][0] = mad(rA[0],rB[2],rC[2][0]);
            rC[2][1] = mad(rA[1],rB[2],rC[2][1]);
            rC[2][2] = mad(rA[2],rB[2],rC[2][2]);
            rC[2][3] = mad(rA[3],rB[2],rC[2][3]);
            rC[2][4] = mad(rA[4],rB[2],rC[2][4]);
            rC[2][5] = mad(rA[5],rB[2],rC[2][5]);
            rC[3][0] = mad(rA[0],rB[3],rC[3][0]);
            rC[3][1] = mad(rA[1],rB[3],rC[3][1]);
            rC[3][2] = mad(rA[2],rB[3],rC[3][2]);
            rC[3][3] = mad(rA[3],rB[3],rC[3][3]);
            rC[3][4] = mad(rA[4],rB[3],rC[3][4]);
            rC[3][5] = mad(rA[5],rB[3],rC[3][5]);
            rC[4][0] = mad(rA[0],rB[4],rC[4][0]);
            rC[4][1] = mad(rA[1],rB[4],rC[4][1]);
            rC[4][2] = mad(rA[2],rB[4],rC[4][2]);
            rC[4][3] = mad(rA[3],rB[4],rC[4][3]);
            rC[4][4] = mad(rA[4],rB[4],rC[4][4]);
            rC[4][5] = mad(rA[5],rB[4],rC[4][5]);
            rC[5][0] = mad(rA[0],rB[5],rC[5][0]);
            rC[5][1] = mad(rA[1],rB[5],rC[5][1]);
            rC[5][2] = mad(rA[2],rB[5],rC[5][2]);
            rC[5][3] = mad(rA[3],rB[5],rC[5][3]);
            rC[5][4] = mad(rA[4],rB[5],rC[5][4]);
            rC[5][5] = mad(rA[5],rB[5],rC[5][5]);
        }
        uA.d += lda << 3;
        uB.d += ldb << 3;
    } while (--block_k > 0);



    int offset_x = gidx*48+ idx*2;
    int offset_y = gidy*48+ idy*2;
    C[(offset_x +  0) + (offset_y +  0) * ldc] = alpha * rC[0][0];
    C[(offset_x +  1) + (offset_y +  0) * ldc] = alpha * rC[0][1];
    C[(offset_x +  0) + (offset_y +  1) * ldc] = alpha * rC[1][0];
    C[(offset_x +  1) + (offset_y +  1) * ldc] = alpha * rC[1][1];
    C[(offset_x +  0) + (offset_y + 16) * ldc] = alpha * rC[2][0];
    C[(offset_x +  1) + (offset_y + 16) * ldc] = alpha * rC[2][1];
    C[(offset_x +  0) + (offset_y + 17) * ldc] = alpha * rC[3][0];
    C[(offset_x +  1) + (offset_y + 17) * ldc] = alpha * rC[3][1];
    C[(offset_x +  0) + (offset_y + 32) * ldc] = alpha * rC[4][0];
    C[(offset_x +  1) + (offset_y + 32) * ldc] = alpha * rC[4][1];
    C[(offset_x +  0) + (offset_y + 33) * ldc] = alpha * rC[5][0];
    C[(offset_x +  1) + (offset_y + 33) * ldc] = alpha * rC[5][1];
    C[(offset_x + 16) + (offset_y +  0) * ldc] = alpha * rC[0][2];
    C[(offset_x + 17) + (offset_y +  0) * ldc] = alpha * rC[0][3];
    C[(offset_x + 16) + (offset_y +  1) * ldc] = alpha * rC[1][2];
    C[(offset_x + 17) + (offset_y +  1) * ldc] = alpha * rC[1][3];
    C[(offset_x + 16) + (offset_y + 16) * ldc] = alpha * rC[2][2];
    C[(offset_x + 17) + (offset_y + 16) * ldc] = alpha * rC[2][3];
    C[(offset_x + 16) + (offset_y + 17) * ldc] = alpha * rC[3][2];
    C[(offset_x + 17) + (offset_y + 17) * ldc] = alpha * rC[3][3];
    C[(offset_x + 16) + (offset_y + 32) * ldc] = alpha * rC[4][2];
    C[(offset_x + 17) + (offset_y + 32) * ldc] = alpha * rC[4][3];
    C[(offset_x + 16) + (offset_y + 33) * ldc] = alpha * rC[5][2];
    C[(offset_x + 17) + (offset_y + 33) * ldc] = alpha * rC[5][3];
    C[(offset_x + 32) + (offset_y +  0) * ldc] = alpha * rC[0][4];
    C[(offset_x + 33) + (offset_y +  0) * ldc] = alpha * rC[0][5];
    C[(offset_x + 32) + (offset_y +  1) * ldc] = alpha * rC[1][4];
    C[(offset_x + 33) + (offset_y +  1) * ldc] = alpha * rC[1][5];
    C[(offset_x + 32) + (offset_y + 16) * ldc] = alpha * rC[2][4];
    C[(offset_x + 33) + (offset_y + 16) * ldc] = alpha * rC[2][5];
    C[(offset_x + 32) + (offset_y + 17) * ldc] = alpha * rC[3][4];
    C[(offset_x + 33) + (offset_y + 17) * ldc] = alpha * rC[3][5];
    C[(offset_x + 32) + (offset_y + 32) * ldc] = alpha * rC[4][4];
    C[(offset_x + 33) + (offset_y + 32) * ldc] = alpha * rC[4][5];
    C[(offset_x + 32) + (offset_y + 33) * ldc] = alpha * rC[5][4];
    C[(offset_x + 33) + (offset_y + 33) * ldc] = alpha * rC[5][5];
}


";

static const char * dgemm_NT_32_32_8_8x8_4x4__ALPHABETA = "
__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_32_32_8_8x8_4x4__ALPHABETA( __global double const * restrict A, 
                                       __global double const * restrict B,
                                       __global double * C,  
                                       uint const M, 
                                       uint const N, 
                                       uint const K,
                                       double const alpha,  
                                       double const beta,   
                                       uint lda,
                                       uint ldb, 
                                       uint ldc, 
                                       uint const offsetA,
                                       uint const offsetB,
                                       uint const offsetC)
{
    double rC[4][4]  = {(double)0};
    double rA[1][4];
    double rB[1][4];

	double PreFetchA[4];
	double PreFetchB[4];

    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local double lA[264];
    __local double lB[264];
    
    int gidx = get_group_id(0);
    int gidy = get_group_id(1);
    int idx = get_local_id(0);
    int idy = get_local_id(1);
    
    int idt = 8*idy + idx;
    int idxT = idt % 16;
    int idyT = idt / 16;
    
    A +=  gidx*32+ idxT + idyT*lda;
    B +=  gidy*32+ idxT + idyT*ldb;

	__local double* plA = lA + idyT*33+idxT;
    __local double* plB = lB + idyT*33+idxT;

	plA[0] = A[0];
    plA[16] = A[16];
    plA[132] = A[4*lda];
    plA[148] = A[16+4*lda];
    plB[0] = B[0];
    plB[16] = B[16];
    plB[132] = B[4*ldb];
    plB[148] = B[16+4*ldb];
    barrier(CLK_LOCAL_MEM_FENCE);
	
    
    for( int block_k=0 ; block_k< K ; block_k+=8)
    {
        //barrier(CLK_LOCAL_MEM_FENCE);
        A += 8*lda;
        B += 8*ldb;
       
	   PreFetchA[0] = A[0];
	   PreFetchA[1] = A[16];
	   PreFetchA[2] = A[4*lda];
	   PreFetchA[3] = A[16+4*lda];
	   PreFetchB[0] = B[0];
	   PreFetchB[1] = B[16];
	   PreFetchB[2] = B[4*ldb];
	   PreFetchB[3] = B[16+4*ldb];


	    int offA = idx;
        int offB = idy;


      
        for( int k = 0 ; k < 8; k+=1)
        {
            rA[0][0] = lA[offA + 0];
            rA[0][1] = lA[offA + 8];
            rA[0][2] = lA[offA + 16];
            rA[0][3] = lA[offA + 24];
            rB[0][0] = lB[offB + 0];
            rB[0][1] = lB[offB + 8];
            rB[0][2] = lB[offB + 16];
            rB[0][3] = lB[offB + 24];
            offA += 33;
            offB += 33;
            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
            rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
            rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
            rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
            rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
            rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
            rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
            rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
            rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
            rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
            rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
            rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
            rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
        }

		barrier(CLK_LOCAL_MEM_FENCE);
		plA[0]   = PreFetchA[0];
        plA[16]  = PreFetchA[1];
        plA[132] = PreFetchA[2];
        plA[148] = PreFetchA[3];
        plB[0]   = PreFetchB[0];
        plB[16]  = PreFetchB[1];
        plB[132] = PreFetchB[2];
        plB[148] = PreFetchB[3];
		barrier(CLK_LOCAL_MEM_FENCE);

      //  A += 8*lda;
      //  B += 8*ldb;
    }

    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;
    C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
    C[8*ldc] = alpha*rC[0][1] + beta*C[8*ldc];
    C[16*ldc] = alpha*rC[0][2] + beta*C[16*ldc];
    C[24*ldc] = alpha*rC[0][3] + beta*C[24*ldc];
    C+=8;
    C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
    C[8*ldc] = alpha*rC[1][1] + beta*C[8*ldc];
    C[16*ldc] = alpha*rC[1][2] + beta*C[16*ldc];
    C[24*ldc] = alpha*rC[1][3] + beta*C[24*ldc];
    C+=8;
    C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
    C[8*ldc] = alpha*rC[2][1] + beta*C[8*ldc];
    C[16*ldc] = alpha*rC[2][2] + beta*C[16*ldc];
    C[24*ldc] = alpha*rC[2][3] + beta*C[24*ldc];
    C+=8;
    C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
    C[8*ldc] = alpha*rC[3][1] + beta*C[8*ldc];
    C[16*ldc] = alpha*rC[3][2] + beta*C[16*ldc];
    C[24*ldc] = alpha*rC[3][3] + beta*C[24*ldc];
    C+=8;
}
";

static const char * dgemm_NT_32_32_8_8x8_4x4__ALPHA = "
__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_32_32_8_8x8_4x4__ALPHA( __global double const * restrict A, 
                                       __global double const * restrict B,
                                       __global double * C,  
                                       uint const M, 
                                       uint const N, 
                                       uint const K,
                                       double const alpha,    
                                       uint lda,
                                       uint ldb, 
                                       uint ldc, 
                                       uint const offsetA,
                                       uint const offsetB,
                                       uint const offsetC)
{
    double rC[4][4]  = {(double)0};
    double rA[1][4];
    double rB[1][4];

	double PreFetchA[4];
	double PreFetchB[4];

    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local double lA[264];
    __local double lB[264];
    
    int gidx = get_group_id(0);
    int gidy = get_group_id(1);
    int idx = get_local_id(0);
    int idy = get_local_id(1);
    
    int idt = 8*idy + idx;
    int idxT = idt % 16;
    int idyT = idt / 16;
    
    A +=  gidx*32+ idxT + idyT*lda;
    B +=  gidy*32+ idxT + idyT*ldb;

	__local double* plA = lA + idyT*33+idxT;
    __local double* plB = lB + idyT*33+idxT;

	plA[0] = A[0];
    plA[16] = A[16];
    plA[132] = A[4*lda];
    plA[148] = A[16+4*lda];
    plB[0] = B[0];
    plB[16] = B[16];
    plB[132] = B[4*ldb];
    plB[148] = B[16+4*ldb];
    barrier(CLK_LOCAL_MEM_FENCE);
	
    
    for( int block_k=0 ; block_k< K ; block_k+=8)
    {
        //barrier(CLK_LOCAL_MEM_FENCE);
        A += 8*lda;
        B += 8*ldb;
       
	   PreFetchA[0] = A[0];
	   PreFetchA[1] = A[16];
	   PreFetchA[2] = A[4*lda];
	   PreFetchA[3] = A[16+4*lda];
	   PreFetchB[0] = B[0];
	   PreFetchB[1] = B[16];
	   PreFetchB[2] = B[4*ldb];
	   PreFetchB[3] = B[16+4*ldb];


	    int offA = idx;
        int offB = idy;


      
        for( int k = 0 ; k < 8; k+=1)
        {
            rA[0][0] = lA[offA + 0];
            rA[0][1] = lA[offA + 8];
            rA[0][2] = lA[offA + 16];
            rA[0][3] = lA[offA + 24];
            rB[0][0] = lB[offB + 0];
            rB[0][1] = lB[offB + 8];
            rB[0][2] = lB[offB + 16];
            rB[0][3] = lB[offB + 24];
            offA += 33;
            offB += 33;
            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
            rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
            rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
            rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
            rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
            rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
            rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
            rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
            rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
            rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
            rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
            rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
            rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
        }

		barrier(CLK_LOCAL_MEM_FENCE);
		plA[0]   = PreFetchA[0];
        plA[16]  = PreFetchA[1];
        plA[132] = PreFetchA[2];
        plA[148] = PreFetchA[3];
        plB[0]   = PreFetchB[0];
        plB[16]  = PreFetchB[1];
        plB[132] = PreFetchB[2];
        plB[148] = PreFetchB[3];
		barrier(CLK_LOCAL_MEM_FENCE);

      //  A += 8*lda;
      //  B += 8*ldb;
    }

    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;
    C[0*ldc] = alpha*rC[0][0] ;
    C[8*ldc] = alpha*rC[0][1] ;
    C[16*ldc] = alpha*rC[0][2];
    C[24*ldc] = alpha*rC[0][3];
    C+=8;                     ;
    C[0*ldc] = alpha*rC[1][0] ;
    C[8*ldc] = alpha*rC[1][1] ;
    C[16*ldc] = alpha*rC[1][2];
    C[24*ldc] = alpha*rC[1][3];
    C+=8;                     ;
    C[0*ldc] = alpha*rC[2][0] ;
    C[8*ldc] = alpha*rC[2][1] ;
    C[16*ldc] = alpha*rC[2][2];
    C[24*ldc] = alpha*rC[2][3];
    C+=8;                     ;
    C[0*ldc] = alpha*rC[3][0] ;
    C[8*ldc] = alpha*rC[3][1] ;
    C[16*ldc] = alpha*rC[3][2];
    C[24*ldc] = alpha*rC[3][3];
    C+=8;
}
";



static const char * dgemm_NT_40_40_8_8x8_5x5__ALPHABETA = "

__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_40_40_8_8x8_5x5__ALPHABETA( __global double const * restrict A, 
                                       __global double const * restrict B,
                                       __global double * C,  
                                       uint const M, 
                                       uint const N, 
                                       uint const K,
                                       double const alpha,  
                                       double const beta,   
                                       uint lda,
                                       uint ldb, 
                                       uint ldc, 
                                       uint const offsetA,
                                       uint const offsetB,
                                       uint const offsetC)
{
  double rC[5][5]  = {(double)0};
  double rA[1][5];
  double rB[1][5];

  double PreFetchA[5];
  double PreFetchB[5];

  //double PreFetchA_5;
  //double PreFetchB_5;

  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[320];
  __local double lB[320];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;
  

  A +=  gidx*40+ idxT + idyT*lda;
  B +=  gidy*40+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*40+idxT;
  __local double* plB = lB + idyT*40+idxT;

  

    plA[0]  = A[0];
    plA[8]  = A[8];
    plA[16] = A[16];
    plA[24] = A[24];
    plA[32] = A[32]; 
    plB[0]  = B[0];
    plB[8]  = B[8];
    plB[16] = B[16];
    plB[24] = B[24];
    plB[32] = B[32];
    barrier(CLK_LOCAL_MEM_FENCE);


  //for( int block_k=0 ; block_k< K ; block_k+=8)
  uint block_k = K >> 3;
  do
  {
/*    barrier(CLK_LOCAL_MEM_FENCE);


    plA[0] = A[0];
    plA[8] = A[8];
    plA[16] = A[16];
    plA[24] = A[24];
    plA[32] = A[32]; 
    plB[0] = B[0];
    plB[8] = B[8];
    plB[16] = B[16];
    plB[24] = B[24];
    plB[32] = B[32];
    barrier(CLK_LOCAL_MEM_FENCE);
*/
A += 8*lda;
B += 8*ldb;
    PreFetchA[0] = A[0];
	PreFetchA[1] = A[8];
	PreFetchA[2] = A[16];
	PreFetchA[3] = A[24];
	PreFetchA[4] = A[32];
	PreFetchB[0] = B[0];
	PreFetchB[1] = B[8];
	PreFetchB[2] = B[16];
	PreFetchB[3] = B[24];
	PreFetchB[4] = B[32];



    int offA = idx;
    int offB = idy;
   // int off256 = 256;


#pragma unroll 1
    for( int k = 0 ; k < 8; k+=1)
    {
      rA[0][0] = lA[offA + 0];
      rA[0][1] = lA[offA + 8];
      rA[0][2] = lA[offA + 16];
      rA[0][3] = lA[offA + 24];
      rA[0][4] = lA[offA + 32];

      rB[0][0] = lB[offB + 0];
      rB[0][1] = lB[offB + 8];
      rB[0][2] = lB[offB + 16];
      rB[0][3] = lB[offB + 24];
      rB[0][4] = lB[offB + 32];


      offA += 40;
      offB += 40;
      //off256 -= 24;
      rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
      rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
      rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
      rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
      rC[4][0]=mad(rA[0][4],rB[0][0],rC[4][0]);

      rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
      rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
      rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
      rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
      rC[4][1]=mad(rA[0][4],rB[0][1],rC[4][1]);

      rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
      rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
      rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
      rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
      rC[4][2]=mad(rA[0][4],rB[0][2],rC[4][2]);

      rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
      rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
      rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
      rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      rC[4][3]=mad(rA[0][4],rB[0][3],rC[4][3]);

      rC[0][4]=mad(rA[0][0],rB[0][4],rC[0][4]);
      rC[1][4]=mad(rA[0][1],rB[0][4],rC[1][4]);
      rC[2][4]=mad(rA[0][2],rB[0][4],rC[2][4]);
      rC[3][4]=mad(rA[0][3],rB[0][4],rC[3][4]);
      rC[4][4]=mad(rA[0][4],rB[0][4],rC[4][4]);

    }

	barrier(CLK_LOCAL_MEM_FENCE);
    plA[0]  = PreFetchA[0];
    plA[8]  = PreFetchA[1];
    plA[16] = PreFetchA[2];
    plA[24] = PreFetchA[3];
    plA[32] = PreFetchA[4];
    plB[0]  = PreFetchB[0];
    plB[8]  = PreFetchB[1];
    plB[16] = PreFetchB[2];
    plB[24] = PreFetchB[3];
    plB[32] = PreFetchB[4];

    barrier(CLK_LOCAL_MEM_FENCE);
    //  A += 8*lda;
    //  B += 8*ldb;
  }
  while (--block_k > 0);

  C+= gidx*40;
  C+= idx;
  C+= gidy*40*ldc;
  C+= idy*ldc;
 
  C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[0][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[0][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[0][3] + beta*C[24*ldc];
  C[32*ldc] = alpha*rC[0][4] + beta*C[32*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[1][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[1][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[1][3] + beta*C[24*ldc];
  C[32*ldc] = alpha*rC[1][4] + beta*C[32*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[2][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[2][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[2][3] + beta*C[24*ldc];
  C[32*ldc] = alpha*rC[2][4] + beta*C[32*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[3][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[3][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[3][3] + beta*C[24*ldc];
  C[32*ldc] = alpha*rC[3][4] + beta*C[32*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[4][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[4][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[4][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[4][3] + beta*C[24*ldc];
  C[32*ldc] = alpha*rC[4][4] + beta*C[32*ldc];
   
}
";


static const char * dgemm_NT_40_40_8_8x8_5x5__ALPHA = "

__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_40_40_8_8x8_5x5__ALPHA( __global double const * restrict A, 
                                       __global double const * restrict B,
                                       __global double * C,  
                                       uint const M, 
                                       uint const N, 
                                       uint const K,
                                       double const alpha,
                                       uint lda,
                                       uint ldb, 
                                       uint ldc, 
                                       uint const offsetA,
                                       uint const offsetB,
                                       uint const offsetC)
{
  double rC[5][5]  = {(double)0};
  double rA[1][5];
  double rB[1][5];

  double PreFetchA[5];
  double PreFetchB[5];

  //double PreFetchA_5;
  //double PreFetchB_5;

  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[320];
  __local double lB[320];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;
  

  A +=  gidx*40+ idxT + idyT*lda;
  B +=  gidy*40+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*40+idxT;
  __local double* plB = lB + idyT*40+idxT;

  

    plA[0]  = A[0];
    plA[8]  = A[8];
    plA[16] = A[16];
    plA[24] = A[24];
    plA[32] = A[32]; 
    plB[0]  = B[0];
    plB[8]  = B[8];
    plB[16] = B[16];
    plB[24] = B[24];
    plB[32] = B[32];
    barrier(CLK_LOCAL_MEM_FENCE);


  //for( int block_k=0 ; block_k< K ; block_k+=8)
  uint block_k = K >> 3;
  do
  {
/*    barrier(CLK_LOCAL_MEM_FENCE);


    plA[0] = A[0];
    plA[8] = A[8];
    plA[16] = A[16];
    plA[24] = A[24];
    plA[32] = A[32]; 
    plB[0] = B[0];
    plB[8] = B[8];
    plB[16] = B[16];
    plB[24] = B[24];
    plB[32] = B[32];
    barrier(CLK_LOCAL_MEM_FENCE);
*/
A += 8*lda;
B += 8*ldb;
    PreFetchA[0] = A[0];
	PreFetchA[1] = A[8];
	PreFetchA[2] = A[16];
	PreFetchA[3] = A[24];
	PreFetchA[4] = A[32];
	PreFetchB[0] = B[0];
	PreFetchB[1] = B[8];
	PreFetchB[2] = B[16];
	PreFetchB[3] = B[24];
	PreFetchB[4] = B[32];



    int offA = idx;
    int offB = idy;
   // int off256 = 256;


#pragma unroll 1
    for( int k = 0 ; k < 8; k+=1)
    {
      rA[0][0] = lA[offA + 0];
      rA[0][1] = lA[offA + 8];
      rA[0][2] = lA[offA + 16];
      rA[0][3] = lA[offA + 24];
      rA[0][4] = lA[offA + 32];

      rB[0][0] = lB[offB + 0];
      rB[0][1] = lB[offB + 8];
      rB[0][2] = lB[offB + 16];
      rB[0][3] = lB[offB + 24];
      rB[0][4] = lB[offB + 32];


      offA += 40;
      offB += 40;
      //off256 -= 24;
      rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
      rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
      rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
      rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
      rC[4][0]=mad(rA[0][4],rB[0][0],rC[4][0]);

      rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
      rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
      rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
      rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
      rC[4][1]=mad(rA[0][4],rB[0][1],rC[4][1]);

      rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
      rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
      rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
      rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
      rC[4][2]=mad(rA[0][4],rB[0][2],rC[4][2]);

      rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
      rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
      rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
      rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      rC[4][3]=mad(rA[0][4],rB[0][3],rC[4][3]);

      rC[0][4]=mad(rA[0][0],rB[0][4],rC[0][4]);
      rC[1][4]=mad(rA[0][1],rB[0][4],rC[1][4]);
      rC[2][4]=mad(rA[0][2],rB[0][4],rC[2][4]);
      rC[3][4]=mad(rA[0][3],rB[0][4],rC[3][4]);
      rC[4][4]=mad(rA[0][4],rB[0][4],rC[4][4]);

    }

	barrier(CLK_LOCAL_MEM_FENCE);
    plA[0]  = PreFetchA[0];
    plA[8]  = PreFetchA[1];
    plA[16] = PreFetchA[2];
    plA[24] = PreFetchA[3];
    plA[32] = PreFetchA[4];
    plB[0]  = PreFetchB[0];
    plB[8]  = PreFetchB[1];
    plB[16] = PreFetchB[2];
    plB[24] = PreFetchB[3];
    plB[32] = PreFetchB[4];

    barrier(CLK_LOCAL_MEM_FENCE);
    //  A += 8*lda;
    //  B += 8*ldb;
  }
  while (--block_k > 0);

  C+= gidx*40;
  C+= idx;
  C+= gidy*40*ldc;
  C+= idy*ldc;
 
  C[0*ldc] = alpha*rC[0][0] ;
  C[8*ldc] = alpha*rC[0][1] ;
  C[16*ldc] = alpha*rC[0][2];
  C[24*ldc] = alpha*rC[0][3];
  C[32*ldc] = alpha*rC[0][4];
  C+=8;                     
  C[0*ldc] = alpha*rC[1][0] ;
  C[8*ldc] = alpha*rC[1][1] ;
  C[16*ldc] = alpha*rC[1][2];
  C[24*ldc] = alpha*rC[1][3];
  C[32*ldc] = alpha*rC[1][4];
  C+=8;                     
  C[0*ldc] = alpha*rC[2][0] ;
  C[8*ldc] = alpha*rC[2][1] ;
  C[16*ldc] = alpha*rC[2][2];
  C[24*ldc] = alpha*rC[2][3];
  C[32*ldc] = alpha*rC[2][4];
  C+=8;                     
  C[0*ldc] = alpha*rC[3][0] ;
  C[8*ldc] = alpha*rC[3][1] ;
  C[16*ldc] = alpha*rC[3][2];
  C[24*ldc] = alpha*rC[3][3];
  C[32*ldc] = alpha*rC[3][4];
  C+=8;                     
  C[0*ldc] = alpha*rC[4][0] ;
  C[8*ldc] = alpha*rC[4][1] ;
  C[16*ldc] = alpha*rC[4][2];
  C[24*ldc] = alpha*rC[4][3];
  C[32*ldc] = alpha*rC[4][4];
   
}
";

// ============= genericDgemm.cl
// was DgemmGenericMNK 
// M, N, K 
/// local size 8,8
//padding 32
static const char * dgemm_NT_1_1_1_8x8_4x4__ALPHABETA = "


__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_1_1_1_8x8_4x4__ALPHABETA(  __global double const * restrict A, 
                                       __global double const * restrict B,
                                       __global double * C,  
                                       uint const M, 
                                       uint const N, 
                                       uint const K,
                                       double const alpha,  
                                       double const beta,   
                                       uint lda,
                                       uint ldb, 
                                       uint ldc, 
                                       uint const offsetA,
                                       uint const offsetB,
                                       uint const offsetC)
{
  double rC[4][4]  = {(double)0};
  double rA[1][4];
  double rB[1][4];


  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[264];
  __local double lB[264];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 16;
  int idyT = idt / 16;

  A +=  gidx*32+ idxT + idyT*lda;
  B +=  gidy*32+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*33+1*idxT;
  __local double* plB = lB + idyT*33+1*idxT;


  if(gidx==get_num_groups(0)-1 || gidy==get_num_groups(1)-1 )
  {

    int CurrentOffSetA = gidx*32+ idxT;
    int CurrentOffSetB = gidy*32+ idxT;

    for( int block_k=0 ; block_k< K ; block_k+=8)
    {
      
      barrier(CLK_LOCAL_MEM_FENCE);
      plA[0]   = CurrentOffSetA>=M?0.0:A[0];
      plA[16]  = CurrentOffSetA+16>=M?0.0:A[16];
      plA[132] = CurrentOffSetA>=M?0.0:A[4*lda];
      plA[148] = CurrentOffSetA+16>=M?0.0:A[16+4*lda];
     
      plB[0]   = CurrentOffSetB>=N?0.0:B[0];
      plB[16]  = CurrentOffSetB+16>=N?0.0:B[16];
      plB[132] = CurrentOffSetB>=N?0.0:B[4*ldb];
      plB[148] = CurrentOffSetB+16>=N?0.0:B[16+4*ldb];
      barrier(CLK_LOCAL_MEM_FENCE);
     
      int offA = idx;
      int offB = idy;

      for( int k = 0 ; k < min(8u, K-block_k); k+=1)
      {
        rA[0][0] = lA[offA + 0];
        rA[0][1] = lA[offA + 8];
        rA[0][2] = lA[offA + 16];
        rA[0][3] = lA[offA + 24];
        rB[0][0] = lB[offB + 0];
        rB[0][1] = lB[offB + 8];
        rB[0][2] = lB[offB + 16];
        rB[0][3] = lB[offB + 24];
        offA += 33;
        offB += 33;
        rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
        rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
        rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
        rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
        rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
        rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
        rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
        rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
        rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
        rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
        rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
        rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
        rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
        rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
        rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      }
      A += 8*lda;
      B += 8*ldb;
    }

    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;
    
    int OffSetCM = gidx*32+idx;
    int OffSetCN = gidy*32+idy;
    if(OffSetCM>=M || OffSetCN>=N)
      return;


    for (int i = 0; i<4; i++)
    {
      C[0*ldc] = alpha*rC[i][0] + beta*C[0*ldc];
      
      if (OffSetCN+8<N)
        C[8*ldc] = alpha*rC[i][1] + beta*C[8*ldc];
      
      if (OffSetCN+16<N)
        C[16*ldc] = alpha*rC[i][2] + beta*C[16*ldc];
      
      if (OffSetCN+24<N)
        C[24*ldc] = alpha*rC[i][3] + beta*C[24*ldc];

      C+=8;
      OffSetCM += 8;
      if(OffSetCM>=M)
        return;
      

    }
  }
  else
  {

    for( int block_k=0 ; block_k< K ; block_k+=8)
    {

      barrier(CLK_LOCAL_MEM_FENCE);
      plA[0] = A[0];
      plA[16] = A[16];
      plA[132] = A[4*lda];
      plA[148] = A[16+4*lda];
      plB[0] = B[0];
      plB[16] = B[16];
      plB[132] = B[4*ldb];
      plB[148] = B[16+4*ldb];
      barrier(CLK_LOCAL_MEM_FENCE);

      int offA = idx;
      int offB = idy;
     

      for( int k = 0 ; k < min(8u, K-block_k); k+=1)
      {
        rA[0][0] = lA[offA + 0];
        rA[0][1] = lA[offA + 8];
        rA[0][2] = lA[offA + 16];
        rA[0][3] = lA[offA + 24];
        rB[0][0] = lB[offB + 0];
        rB[0][1] = lB[offB + 8];
        rB[0][2] = lB[offB + 16];
        rB[0][3] = lB[offB + 24];
        offA += 33;
        offB += 33;
        rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
        rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
        rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
        rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
        rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
        rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
        rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
        rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
        rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
        rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
        rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
        rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
        rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
        rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
        rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      }
      A += 8*lda;
      B += 8*ldb;
    }

    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;


    C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
    C[8*ldc] = alpha*rC[0][1] + beta*C[8*ldc];
    C[16*ldc] = alpha*rC[0][2] + beta*C[16*ldc];
    C[24*ldc] = alpha*rC[0][3] + beta*C[24*ldc];
    C+=8;
    C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
    C[8*ldc] = alpha*rC[1][1] + beta*C[8*ldc];
    C[16*ldc] = alpha*rC[1][2] + beta*C[16*ldc];
    C[24*ldc] = alpha*rC[1][3] + beta*C[24*ldc];
    C+=8;
    C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
    C[8*ldc] = alpha*rC[2][1] + beta*C[8*ldc];
    C[16*ldc] = alpha*rC[2][2] + beta*C[16*ldc];
    C[24*ldc] = alpha*rC[2][3] + beta*C[24*ldc];
    C+=8;
    C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
    C[8*ldc] = alpha*rC[3][1] + beta*C[8*ldc];
    C[16*ldc] = alpha*rC[3][2] + beta*C[16*ldc];
    C[24*ldc] = alpha*rC[3][3] + beta*C[24*ldc];
 
  }
  
}

"; 



static const char * dgemm_NT_1_1_1_8x8_4x4__ALPHA = "


__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_1_1_1_8x8_4x4__ALPHA(  __global double const * restrict A, 
                                       __global double const * restrict B,
                                       __global double * C,  
                                       uint const M, 
                                       uint const N, 
                                       uint const K,
                                       double const alpha, 
                                       uint lda,
                                       uint ldb, 
                                       uint ldc, 
                                       uint const offsetA,
                                       uint const offsetB,
                                       uint const offsetC)
{
  double rC[4][4]  = {(double)0};
  double rA[1][4];
  double rB[1][4];


  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[264];
  __local double lB[264];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 16;
  int idyT = idt / 16;

  A +=  gidx*32+ idxT + idyT*lda;
  B +=  gidy*32+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*33+1*idxT;
  __local double* plB = lB + idyT*33+1*idxT;


  if(gidx==get_num_groups(0)-1 || gidy==get_num_groups(1)-1 )
  {

    int CurrentOffSetA = gidx*32+ idxT;
    int CurrentOffSetB = gidy*32+ idxT;

    for( int block_k=0 ; block_k< K ; block_k+=8)
    {
      
      barrier(CLK_LOCAL_MEM_FENCE);
      plA[0]   = CurrentOffSetA>=M?0.0:A[0];
      plA[16]  = CurrentOffSetA+16>=M?0.0:A[16];
      plA[132] = CurrentOffSetA>=M?0.0:A[4*lda];
      plA[148] = CurrentOffSetA+16>=M?0.0:A[16+4*lda];
     
      plB[0]   = CurrentOffSetB>=N?0.0:B[0];
      plB[16]  = CurrentOffSetB+16>=N?0.0:B[16];
      plB[132] = CurrentOffSetB>=N?0.0:B[4*ldb];
      plB[148] = CurrentOffSetB+16>=N?0.0:B[16+4*ldb];
      barrier(CLK_LOCAL_MEM_FENCE);
     
      int offA = idx;
      int offB = idy;

      for( int k = 0 ; k < min(8u, K-block_k); k+=1)
      {
        rA[0][0] = lA[offA + 0];
        rA[0][1] = lA[offA + 8];
        rA[0][2] = lA[offA + 16];
        rA[0][3] = lA[offA + 24];
        rB[0][0] = lB[offB + 0];
        rB[0][1] = lB[offB + 8];
        rB[0][2] = lB[offB + 16];
        rB[0][3] = lB[offB + 24];
        offA += 33;
        offB += 33;
        rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
        rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
        rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
        rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
        rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
        rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
        rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
        rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
        rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
        rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
        rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
        rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
        rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
        rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
        rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      }
      A += 8*lda;
      B += 8*ldb;
    }

    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;
    
    int OffSetCM = gidx*32+idx;
    int OffSetCN = gidy*32+idy;
    if(OffSetCM>=M || OffSetCN>=N)
      return;


    for (int i = 0; i<4; i++)
    {
      C[0*ldc] = alpha*rC[i][0];
      
      if (OffSetCN+8<N)
        C[8*ldc] = alpha*rC[i][1];
      
      if (OffSetCN+16<N)
        C[16*ldc] = alpha*rC[i][2];
      
      if (OffSetCN+24<N)
        C[24*ldc] = alpha*rC[i][3];

      C+=8;
      OffSetCM += 8;
      if(OffSetCM>=M)
        return;
      

    }
  }
  else
  {

    for( int block_k=0 ; block_k< K ; block_k+=8)
    {

      barrier(CLK_LOCAL_MEM_FENCE);
      plA[0] = A[0];
      plA[16] = A[16];
      plA[132] = A[4*lda];
      plA[148] = A[16+4*lda];
      plB[0] = B[0];
      plB[16] = B[16];
      plB[132] = B[4*ldb];
      plB[148] = B[16+4*ldb];
      barrier(CLK_LOCAL_MEM_FENCE);

      int offA = idx;
      int offB = idy;
     

      for( int k = 0 ; k < min(8u, K-block_k); k+=1)
      {
        rA[0][0] = lA[offA + 0];
        rA[0][1] = lA[offA + 8];
        rA[0][2] = lA[offA + 16];
        rA[0][3] = lA[offA + 24];
        rB[0][0] = lB[offB + 0];
        rB[0][1] = lB[offB + 8];
        rB[0][2] = lB[offB + 16];
        rB[0][3] = lB[offB + 24];
        offA += 33;
        offB += 33;
        rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
        rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
        rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
        rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
        rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
        rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
        rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
        rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
        rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
        rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
        rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
        rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
        rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
        rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
        rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      }
      A += 8*lda;
      B += 8*ldb;
    }

    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;


    C[0*ldc]  = alpha*rC[0][0];
    C[8*ldc]  = alpha*rC[0][1];
    C[16*ldc] = alpha*rC[0][2];
    C[24*ldc] = alpha*rC[0][3];
    C+=8;                     
    C[0*ldc]  = alpha*rC[1][0];
    C[8*ldc]  = alpha*rC[1][1];
    C[16*ldc] = alpha*rC[1][2];
    C[24*ldc] = alpha*rC[1][3];
    C+=8;                     
    C[0*ldc]  = alpha*rC[2][0];
    C[8*ldc]  = alpha*rC[2][1];
    C[16*ldc] = alpha*rC[2][2];
    C[24*ldc] = alpha*rC[2][3];
    C+=8;                     
    C[0*ldc]  = alpha*rC[3][0];
    C[8*ldc]  = alpha*rC[3][1];
    C[16*ldc] = alpha*rC[3][2];
    C[24*ldc] = alpha*rC[3][3];
 
  }
  
}

"; 
// was DgemmGenericMN
// M, N, K%8 
static const char * dgemm_NT_1_1_8_8x8_4x4__ALPHABETA = "


__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_1_1_8_8x8_4x4__ALPHABETA(  __global double const * restrict A, 
                                       __global double const * restrict B,
                                       __global double * C,  
                                       uint const M, 
                                       uint const N, 
                                       uint const K,
                                       double const alpha,  
                                       double const beta,  
                                       uint lda,
                                       uint ldb, 
                                       uint ldc, 
                                       uint const offsetA, 
                                       uint const offsetB, 
                                       uint const offsetC)
{
  double rC[4][4]  = {(double)0};
  double rA[1][4];
  double rB[1][4];


  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[264];
  __local double lB[264];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 16;
  int idyT = idt / 16;

  A +=  gidx*32+ idxT + idyT*lda;
  B +=  gidy*32+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*33+1*idxT;
  __local double* plB = lB + idyT*33+1*idxT;


  if(gidx==get_num_groups(0)-1 || gidy==get_num_groups(1)-1 )
  {

    int CurrentOffSetA = gidx*32+ idxT;
    int CurrentOffSetB = gidy*32+ idxT;

    for( int block_k=0 ; block_k< K ; block_k+=8)
    {
      
      barrier(CLK_LOCAL_MEM_FENCE);
      plA[0]   = CurrentOffSetA>=M?0.0:A[0];
      plA[16]  = CurrentOffSetA+16>=M?0.0:A[16];
      plA[132] = CurrentOffSetA>=M?0.0:A[4*lda];
      plA[148] = CurrentOffSetA+16>=M?0.0:A[16+4*lda];
     
      plB[0]   = CurrentOffSetB>=N?0.0:B[0];
      plB[16]  = CurrentOffSetB+16>=N?0.0:B[16];
      plB[132] = CurrentOffSetB>=N?0.0:B[4*ldb];
      plB[148] = CurrentOffSetB+16>=N?0.0:B[16+4*ldb];
      barrier(CLK_LOCAL_MEM_FENCE);
     
      int offA = 1*idx;
      int offB = 1*idy;

      for( int k = 0 ; k < 8; k+=1)
      {
        rA[0][0] = lA[offA + 0];
        rA[0][1] = lA[offA + 8];
        rA[0][2] = lA[offA + 16];
        rA[0][3] = lA[offA + 24];
        rB[0][0] = lB[offB + 0];
        rB[0][1] = lB[offB + 8];
        rB[0][2] = lB[offB + 16];
        rB[0][3] = lB[offB + 24];
        offA += 33;
        offB += 33;
        rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
        rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
        rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
        rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
        rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
        rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
        rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
        rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
        rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
        rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
        rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
        rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
        rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
        rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
        rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      }
      A += 8*lda;
      B += 8*ldb;
    }

    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;
    
    int OffSetCM = gidx*32+idx;
    int OffSetCN = gidy*32+idy;
    if(OffSetCM>=M || OffSetCN>=N)
     {
      return;
    }


    for (int i = 0; i<4; i++)
    {
      C[0*ldc] = alpha*rC[i][0] + beta*C[0*ldc];
      
      if (OffSetCN+8<N)
        C[8*ldc] = alpha*rC[i][1] + beta*C[8*ldc];
      
      if (OffSetCN+16<N)
        C[16*ldc] = alpha*rC[i][2] + beta*C[16*ldc];
      
      if (OffSetCN+24<N)
        C[24*ldc] = alpha*rC[i][3] + beta*C[24*ldc];

      C+=8;
      OffSetCM += 8;
      if(OffSetCM>=M)
      {
        return;
      }

    }
  }
  else
  {

    for( int block_k=0 ; block_k< K ; block_k+=8)
    {

      barrier(CLK_LOCAL_MEM_FENCE);
      plA[0] = A[0];
      plA[16] = A[16];
      plA[132] = A[4*lda];
      plA[148] = A[16+4*lda];
      plB[0] = B[0];
      plB[16] = B[16];
      plB[132] = B[4*ldb];
      plB[148] = B[16+4*ldb];
      barrier(CLK_LOCAL_MEM_FENCE);

      int offA = idx;
      int offB = idy;


      for( int k = 0 ; k < 8; k+=1)
      {
        rA[0][0] = lA[offA + 0];
        rA[0][1] = lA[offA + 8];
        rA[0][2] = lA[offA + 16];
        rA[0][3] = lA[offA + 24];
        rB[0][0] = lB[offB + 0];
        rB[0][1] = lB[offB + 8];
        rB[0][2] = lB[offB + 16];
        rB[0][3] = lB[offB + 24];
        offA += 33;
        offB += 33;
        rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
        rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
        rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
        rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
        rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
        rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
        rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
        rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
        rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
        rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
        rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
        rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
        rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
        rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
        rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      }
      A += 8*lda;
      B += 8*ldb;
    }

    C+= gidx*32;
    C+= idx*1;
    C+= gidy*32*ldc;
    C+= idy*1*ldc;


    C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
    C[8*ldc] = alpha*rC[0][1] + beta*C[8*ldc];
    C[16*ldc] = alpha*rC[0][2] + beta*C[16*ldc];
    C[24*ldc] = alpha*rC[0][3] + beta*C[24*ldc];
    C+=8;
    C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
    C[8*ldc] = alpha*rC[1][1] + beta*C[8*ldc];
    C[16*ldc] = alpha*rC[1][2] + beta*C[16*ldc];
    C[24*ldc] = alpha*rC[1][3] + beta*C[24*ldc];
    C+=8;
    C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
    C[8*ldc] = alpha*rC[2][1] + beta*C[8*ldc];
    C[16*ldc] = alpha*rC[2][2] + beta*C[16*ldc];
    C[24*ldc] = alpha*rC[2][3] + beta*C[24*ldc];
    C+=8;
    C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
    C[8*ldc] = alpha*rC[3][1] + beta*C[8*ldc];
    C[16*ldc] = alpha*rC[3][2] + beta*C[16*ldc];
    C[24*ldc] = alpha*rC[3][3] + beta*C[24*ldc];
 
  }
  
}

"; 


static const char * dgemm_NT_1_1_8_8x8_4x4__ALPHA = "


__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_1_1_8_8x8_4x4__ALPHA(  __global double const * restrict A, 
                                       __global double const * restrict B,
                                       __global double * C,  
                                       uint const M, 
                                       uint const N, 
                                       uint const K,
                                       double const alpha, 
                                       uint lda,
                                       uint ldb, 
                                       uint ldc, 
                                       uint const offsetA, 
                                       uint const offsetB, 
                                       uint const offsetC)
{
  double rC[4][4]  = {(double)0};
  double rA[1][4];
  double rB[1][4];


  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[264];
  __local double lB[264];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 16;
  int idyT = idt / 16;

  A +=  gidx*32+ idxT + idyT*lda;
  B +=  gidy*32+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*33+1*idxT;
  __local double* plB = lB + idyT*33+1*idxT;


  if(gidx==get_num_groups(0)-1 || gidy==get_num_groups(1)-1 )
  {

    int CurrentOffSetA = gidx*32+ idxT;
    int CurrentOffSetB = gidy*32+ idxT;

    for( int block_k=0 ; block_k< K ; block_k+=8)
    {
      
      barrier(CLK_LOCAL_MEM_FENCE);
      plA[0]   = CurrentOffSetA>=M?0.0:A[0];
      plA[16]  = CurrentOffSetA+16>=M?0.0:A[16];
      plA[132] = CurrentOffSetA>=M?0.0:A[4*lda];
      plA[148] = CurrentOffSetA+16>=M?0.0:A[16+4*lda];
     
      plB[0]   = CurrentOffSetB>=N?0.0:B[0];
      plB[16]  = CurrentOffSetB+16>=N?0.0:B[16];
      plB[132] = CurrentOffSetB>=N?0.0:B[4*ldb];
      plB[148] = CurrentOffSetB+16>=N?0.0:B[16+4*ldb];
      barrier(CLK_LOCAL_MEM_FENCE);
     
      int offA = 1*idx;
      int offB = 1*idy;

      for( int k = 0 ; k < 8; k+=1)
      {
        rA[0][0] = lA[offA + 0];
        rA[0][1] = lA[offA + 8];
        rA[0][2] = lA[offA + 16];
        rA[0][3] = lA[offA + 24];
        rB[0][0] = lB[offB + 0];
        rB[0][1] = lB[offB + 8];
        rB[0][2] = lB[offB + 16];
        rB[0][3] = lB[offB + 24];
        offA += 33;
        offB += 33;
        rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
        rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
        rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
        rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
        rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
        rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
        rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
        rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
        rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
        rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
        rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
        rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
        rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
        rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
        rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      }
      A += 8*lda;
      B += 8*ldb;
    }

    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;
    
    int OffSetCM = gidx*32+idx;
    int OffSetCN = gidy*32+idy;
    if(OffSetCM>=M || OffSetCN>=N)
     {
      return;
    }


    for (int i = 0; i<4; i++)
    {
      C[0*ldc] = alpha*rC[i][0];
      
      if (OffSetCN+8<N)
        C[8*ldc] = alpha*rC[i][1];
      
      if (OffSetCN+16<N)
        C[16*ldc] = alpha*rC[i][2];
      
      if (OffSetCN+24<N)
        C[24*ldc] = alpha*rC[i][3];

      C+=8;
      OffSetCM += 8;
      if(OffSetCM>=M)
      {
        return;
      }

    }
  }
  else
  {

    for( int block_k=0 ; block_k< K ; block_k+=8)
    {

      barrier(CLK_LOCAL_MEM_FENCE);
      plA[0] = A[0];
      plA[16] = A[16];
      plA[132] = A[4*lda];
      plA[148] = A[16+4*lda];
      plB[0] = B[0];
      plB[16] = B[16];
      plB[132] = B[4*ldb];
      plB[148] = B[16+4*ldb];
      barrier(CLK_LOCAL_MEM_FENCE);

      int offA = idx;
      int offB = idy;


      for( int k = 0 ; k < 8; k+=1)
      {
        rA[0][0] = lA[offA + 0];
        rA[0][1] = lA[offA + 8];
        rA[0][2] = lA[offA + 16];
        rA[0][3] = lA[offA + 24];
        rB[0][0] = lB[offB + 0];
        rB[0][1] = lB[offB + 8];
        rB[0][2] = lB[offB + 16];
        rB[0][3] = lB[offB + 24];
        offA += 33;
        offB += 33;
        rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
        rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
        rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
        rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
        rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
        rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
        rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
        rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
        rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
        rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
        rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
        rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
        rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
        rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
        rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      }
      A += 8*lda;
      B += 8*ldb;
    }

    C+= gidx*32;
    C+= idx*1;
    C+= gidy*32*ldc;
    C+= idy*1*ldc;


    C[0*ldc] = alpha*rC[0][0] ;
    C[8*ldc] = alpha*rC[0][1] ;
    C[16*ldc] = alpha*rC[0][2];
    C[24*ldc] = alpha*rC[0][3];
    C+=8;                     
    C[0*ldc] = alpha*rC[1][0] ;
    C[8*ldc] = alpha*rC[1][1] ;
    C[16*ldc] = alpha*rC[1][2];
    C[24*ldc] = alpha*rC[1][3];
    C+=8;                     
    C[0*ldc] = alpha*rC[2][0] ;
    C[8*ldc] = alpha*rC[2][1] ;
    C[16*ldc] = alpha*rC[2][2];
    C[24*ldc] = alpha*rC[2][3];
    C+=8;                     
    C[0*ldc] = alpha*rC[3][0] ;
    C[8*ldc] = alpha*rC[3][1] ;
    C[16*ldc] = alpha*rC[3][2];
    C[24*ldc] = alpha*rC[3][3];
 
  }
  
}

"; 


//
// was DgemmGenericK
//
static const char * dgemm_NT_32_32_1_8x8_4x4__ALPHABETA = "

__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_32_32_1_8x8_4x4__ALPHABETA(  __global double const * restrict A, 
                                         __global double const * restrict B,
                                         __global double * C,  
                                         uint const M, 
                                         uint const N, 
                                         uint const K,
                                         double const alpha,  
                                         double const beta,   
                                         uint lda,
                                         uint ldb, 
                                         uint ldc, 
                                         uint const offsetA, 
                                         uint const offsetB, 
                                         uint const offsetC)
{
    double rC[4][4]  = {(double)0};
    double rA[1][4];
    double rB[1][4];
	
    double PreFetchA[4];
    double PreFetchB[4];

    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local double lA[264];
    __local double lB[264];
    
    int gidx = get_group_id(0);
    int gidy = get_group_id(1);
    int idx = get_local_id(0);
    int idy = get_local_id(1);
    
    int idt = 8*idy + idx;
    int idxT = idt % 16;
    int idyT = idt / 16;
    
    A +=  gidx*32+ idxT + idyT*lda;
    B +=  gidy*32+ idxT + idyT*ldb;

    __local double* plA = lA + idyT*33+1*idxT;
    __local double* plB = lB + idyT*33+1*idxT;

    plA[0]   = A[0];
    plA[16]  = A[16];
    plA[132] = A[4*lda];
    plA[148] = A[16+4*lda];
    plB[0]   = B[0];
    plB[16]  = B[16];
    plB[132] = B[4*ldb];
    plB[148] = B[16+4*ldb];
    barrier(CLK_LOCAL_MEM_FENCE);
    
    for( int block_k=0 ; block_k< K ; block_k+=8)
    {
       // barrier(CLK_LOCAL_MEM_FENCE);
        A += 8*lda;
        B += 8*ldb;

		PreFetchA[0] = A[0];
		PreFetchA[1] = A[16];
		PreFetchA[2] = A[4*lda];
		PreFetchA[3] = A[16+4*lda];
		PreFetchB[0] = B[0];
		PreFetchB[1] = B[16];
		PreFetchB[2] = B[4*ldb];
		PreFetchB[3] = B[16+4*ldb];



        int offA = idx;
        int offB = idy;


      
        for( int k = 0 ; k < min(8u, K-block_k); k+=1)
        {
            rA[0][0] = lA[offA + 0];
            rA[0][1] = lA[offA + 8];
            rA[0][2] = lA[offA + 16];
            rA[0][3] = lA[offA + 24];
            rB[0][0] = lB[offB + 0];
            rB[0][1] = lB[offB + 8];
            rB[0][2] = lB[offB + 16];
            rB[0][3] = lB[offB + 24];
            offA += 33;
            offB += 33;
            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
            rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
            rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
            rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
            rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
            rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
            rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
            rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
            rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
            rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
            rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
            rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
            rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
        }
        
		barrier(CLK_LOCAL_MEM_FENCE);
		plA[0]   = PreFetchA[0];
		plA[16]  = PreFetchA[1];
		plA[132] = PreFetchA[2];
		plA[148] = PreFetchA[3];
		plB[0]   = PreFetchB[0];
		plB[16]  = PreFetchB[1];
		plB[132] = PreFetchB[2];
		plB[148] = PreFetchB[3];
		barrier(CLK_LOCAL_MEM_FENCE);
    }
    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;
    C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
    C[8*ldc] = alpha*rC[0][1] + beta*C[8*ldc];
    C[16*ldc] = alpha*rC[0][2] + beta*C[16*ldc];
    C[24*ldc] = alpha*rC[0][3] + beta*C[24*ldc];
    C+=8;
    C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
    C[8*ldc] = alpha*rC[1][1] + beta*C[8*ldc];
    C[16*ldc] = alpha*rC[1][2] + beta*C[16*ldc];
    C[24*ldc] = alpha*rC[1][3] + beta*C[24*ldc];
    C+=8;
    C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
    C[8*ldc] = alpha*rC[2][1] + beta*C[8*ldc];
    C[16*ldc] = alpha*rC[2][2] + beta*C[16*ldc];
    C[24*ldc] = alpha*rC[2][3] + beta*C[24*ldc];
    C+=8;
    C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
    C[8*ldc] = alpha*rC[3][1] + beta*C[8*ldc];
    C[16*ldc] = alpha*rC[3][2] + beta*C[16*ldc];
    C[24*ldc] = alpha*rC[3][3] + beta*C[24*ldc];
    C+=8;
}

";

static const char * dgemm_NT_32_32_1_8x8_4x4__ALPHA = "

__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_32_32_1_8x8_4x4__ALPHA(  __global double const * restrict A, 
                                         __global double const * restrict B,
                                         __global double * C,  
                                         uint const M, 
                                         uint const N, 
                                         uint const K,
                                         double const alpha,  
                                         uint lda,
                                         uint ldb, 
                                         uint ldc, 
                                         uint const offsetA, 
                                         uint const offsetB, 
                                         uint const offsetC)
{
    double rC[4][4]  = {(double)0};
    double rA[1][4];
    double rB[1][4];
	
    double PreFetchA[4];
    double PreFetchB[4];

    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local double lA[264];
    __local double lB[264];
    
    int gidx = get_group_id(0);
    int gidy = get_group_id(1);
    int idx = get_local_id(0);
    int idy = get_local_id(1);
    
    int idt = 8*idy + idx;
    int idxT = idt % 16;
    int idyT = idt / 16;
    
    A +=  gidx*32+ idxT + idyT*lda;
    B +=  gidy*32+ idxT + idyT*ldb;

    __local double* plA = lA + idyT*33+1*idxT;
    __local double* plB = lB + idyT*33+1*idxT;

    plA[0]   = A[0];
    plA[16]  = A[16];
    plA[132] = A[4*lda];
    plA[148] = A[16+4*lda];
    plB[0]   = B[0];
    plB[16]  = B[16];
    plB[132] = B[4*ldb];
    plB[148] = B[16+4*ldb];
    barrier(CLK_LOCAL_MEM_FENCE);
    
    for( int block_k=0 ; block_k< K ; block_k+=8)
    {
       // barrier(CLK_LOCAL_MEM_FENCE);
        A += 8*lda;
        B += 8*ldb;

		PreFetchA[0] = A[0];
		PreFetchA[1] = A[16];
		PreFetchA[2] = A[4*lda];
		PreFetchA[3] = A[16+4*lda];
		PreFetchB[0] = B[0];
		PreFetchB[1] = B[16];
		PreFetchB[2] = B[4*ldb];
		PreFetchB[3] = B[16+4*ldb];



        int offA = idx;
        int offB = idy;


      
        for( int k = 0 ; k < min(8u, K-block_k); k+=1)
        {
            rA[0][0] = lA[offA + 0];
            rA[0][1] = lA[offA + 8];
            rA[0][2] = lA[offA + 16];
            rA[0][3] = lA[offA + 24];
            rB[0][0] = lB[offB + 0];
            rB[0][1] = lB[offB + 8];
            rB[0][2] = lB[offB + 16];
            rB[0][3] = lB[offB + 24];
            offA += 33;
            offB += 33;
            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
            rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
            rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
            rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
            rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
            rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
            rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
            rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
            rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
            rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
            rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
            rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
            rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
        }
        
		barrier(CLK_LOCAL_MEM_FENCE);
		plA[0]   = PreFetchA[0];
		plA[16]  = PreFetchA[1];
		plA[132] = PreFetchA[2];
		plA[148] = PreFetchA[3];
		plB[0]   = PreFetchB[0];
		plB[16]  = PreFetchB[1];
		plB[132] = PreFetchB[2];
		plB[148] = PreFetchB[3];
		barrier(CLK_LOCAL_MEM_FENCE);
    }
    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;
    C[0*ldc] = alpha*rC[0][0] ;
    C[8*ldc] = alpha*rC[0][1] ;
    C[16*ldc] = alpha*rC[0][2];
    C[24*ldc] = alpha*rC[0][3];
    C+=8;                     
    C[0*ldc] = alpha*rC[1][0] ;
    C[8*ldc] = alpha*rC[1][1] ;
    C[16*ldc] = alpha*rC[1][2];
    C[24*ldc] = alpha*rC[1][3];
    C+=8;                     
    C[0*ldc] = alpha*rC[2][0] ;
    C[8*ldc] = alpha*rC[2][1] ;
    C[16*ldc] = alpha*rC[2][2];
    C[24*ldc] = alpha*rC[2][3];
    C+=8;                     
    C[0*ldc] = alpha*rC[3][0] ;
    C[8*ldc] = alpha*rC[3][1] ;
    C[16*ldc] = alpha*rC[3][2];
    C[24*ldc] = alpha*rC[3][3];
    C+=8;
}

";

// ============ TNDgemmColumn.cl 

static const char * dgemm_TN_32_32_16_8x16_4x2__ALPHABETA = "



__attribute__( (reqd_work_group_size(8, 16, 1)) )
__kernel void dgemm_TN_32_32_16_8x16_4x2__ALPHABETA( __global double const * restrict A, 
                                          __global double const * restrict B, 
                                          __global double * C,
                                          uint const M, 
                                          uint const N, 
                                          uint const K,
                                          double const alpha,  
                                          double const beta,   
                                          uint lda,
                                          uint ldb, 
                                          uint ldc, 
                                          uint const offsetA, 
                                          uint const offsetB , 
                                          uint const offsetC 
                                          )
{
    double rC[4][2]  = {(double)0};
    double rA[1][4];
    double rB[1][2];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local double lA[528];
    __local double lB[528];
    
    int gidx = get_group_id(0);
    int gidy = get_group_id(1);
    int idx = get_local_id(0);
    int idy = get_local_id(1);
    
    int idt = 8*idy + idx;
    int idxT = idt % 16;
    int idyT = idt / 16;
    
    A +=  gidx*32*lda + idxT + idyT*lda;
    B +=  gidy*32*ldb+ idxT + idyT*ldb;
    
    for( int block_k=0 ; block_k< K ; block_k+=16)
    {
        __local double* plA = lA + idxT*33+ idyT;
        __local double* plB = lB + idxT*33+ idyT;
      
        barrier(CLK_LOCAL_MEM_FENCE);
        plA[0] = A[0+0*lda];
        plA[8] = A[0+8*lda];
        plA[16] = A[0+16*lda];
        plA[24] = A[0+24*lda];
        plB[0] = B[0+0*ldb];
        plB[8] = B[0+8*ldb];
        plB[16] = B[0+16*ldb];
        plB[24] = B[0+24*ldb];
        barrier(CLK_LOCAL_MEM_FENCE);
       
        int offA = 1*idx;
        int offB = 1*idy;
       
        for( int k = 0 ; k < 16; k+=1)
        {
            rA[0][0] = lA[offA + 0];
            rA[0][1] = lA[offA + 8];
            rA[0][2] = lA[offA + 16];
            rA[0][3] = lA[offA + 24];
            rB[0][0] = lB[offB + 0];
            rB[0][1] = lB[offB + 16];
            offA += 33;
            offB += 33;
            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
            rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
            rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
            rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
            rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        }
        A += 16;
        B += 16;
    }
    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;
    C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[0][1] + beta*C[16*ldc];
    C+=8;
    C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[1][1] + beta*C[16*ldc];
    C+=8;
    C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[2][1] + beta*C[16*ldc];
    C+=8;
    C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[3][1] + beta*C[16*ldc];
    
}
"; 


static const char * dgemm_TN_32_32_16_8x16_4x2__ALPHA = "

__attribute__( (reqd_work_group_size(8, 16, 1)) )
__kernel void dgemm_TN_32_32_16_8x16_4x2__ALPHA( __global double const * restrict A, 
                                          __global double const * restrict B, 
                                          __global double * C,
                                          uint const M, 
                                          uint const N, 
                                          uint const K,
                                          double const alpha,  
                                          uint lda,
                                          uint ldb, 
                                          uint ldc, 
                                          uint const offsetA, 
                                          uint const offsetB , 
                                          uint const offsetC 
                                          )
{
    double rC[4][2]  = {(double)0};
    double rA[1][4];
    double rB[1][2];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local double lA[528];
    __local double lB[528];
    
    int gidx = get_group_id(0);
    int gidy = get_group_id(1);
    int idx = get_local_id(0);
    int idy = get_local_id(1);
    
    int idt = 8*idy + idx;
    int idxT = idt % 16;
    int idyT = idt / 16;
    
    A +=  gidx*32*lda + idxT + idyT*lda;
    B +=  gidy*32*ldb+ idxT + idyT*ldb;
    
    for( int block_k=0 ; block_k< K ; block_k+=16)
    {
        __local double* plA = lA + idxT*33+ idyT;
        __local double* plB = lB + idxT*33+ idyT;
      
        barrier(CLK_LOCAL_MEM_FENCE);
        plA[0] = A[0+0*lda];
        plA[8] = A[0+8*lda];
        plA[16] = A[0+16*lda];
        plA[24] = A[0+24*lda];
        plB[0] = B[0+0*ldb];
        plB[8] = B[0+8*ldb];
        plB[16] = B[0+16*ldb];
        plB[24] = B[0+24*ldb];
        barrier(CLK_LOCAL_MEM_FENCE);
       
        int offA = 1*idx;
        int offB = 1*idy;
       
        for( int k = 0 ; k < 16; k+=1)
        {
            rA[0][0] = lA[offA + 0];
            rA[0][1] = lA[offA + 8];
            rA[0][2] = lA[offA + 16];
            rA[0][3] = lA[offA + 24];
            rB[0][0] = lB[offB + 0];
            rB[0][1] = lB[offB + 16];
            offA += 33;
            offB += 33;
            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
            rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
            rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
            rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
            rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        }
        A += 16;
        B += 16;
    }
    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;
    C[0*ldc] = alpha*rC[0][0] ;
    C[16*ldc] = alpha*rC[0][1];
    C+=8;                     
    C[0*ldc] = alpha*rC[1][0] ;
    C[16*ldc] = alpha*rC[1][1];
    C+=8;                     
    C[0*ldc] = alpha*rC[2][0] ;
    C[16*ldc] = alpha*rC[2][1];
    C+=8;                     
    C[0*ldc] = alpha*rC[3][0] ;
    C[16*ldc] = alpha*rC[3][1];
}
"; 

static const char * dgemm_TN_48_48_8_8x8_6x6__ALPHABETA = "

__attribute__( (reqd_work_group_size(8, 8, 1)) )
__kernel void dgemm_TN_48_48_8_8x8_6x6__ALPHABETA(  __global double const * restrict A,
                                         __global double const * restrict B,
                                         __global double * C,  
                                         uint const M, 
                                         uint const N, 
                                         uint const K,
                                         double const alpha,  
                                         double const beta,   
                                         uint lda,
                                         uint ldb, 
                                         uint ldc, 
                                         uint const offsetA, 
                                         uint const offsetB,
                                         uint const offsetC
                                         )
{
    double rC[6][6]  = {(double)0};
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
"; 

static const char * dgemm_TN_48_48_8_8x8_6x6__ALPHA = "

__attribute__( (reqd_work_group_size(8, 8, 1)) )
__kernel void dgemm_TN_48_48_8_8x8_6x6__ALPHA(  __global double const * restrict A,
                                         __global double const * restrict B,
                                         __global double * C,  
                                         uint const M, 
                                         uint const N, 
                                         uint const K,
                                         double const alpha,  
                                         uint lda,
                                         uint ldb, 
                                         uint ldc, 
                                         uint const offsetA, 
                                         uint const offsetB,
                                         uint const offsetC
                                         )
{
    double rC[6][6]  = {(double)0};
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
    
    C[0*ldc] = alpha*rC[0][0] ;
    C[8*ldc] = alpha*rC[0][1] ;
    C[16*ldc] = alpha*rC[0][2];
    C[24*ldc] = alpha*rC[0][3];
    C[32*ldc] = alpha*rC[0][4];
    C[40*ldc] = alpha*rC[0][5];
    C+=8;                     
    C[0*ldc] = alpha*rC[1][0] ;
    C[8*ldc] = alpha*rC[1][1] ;
    C[16*ldc] = alpha*rC[1][2];
    C[24*ldc] = alpha*rC[1][3];
    C[32*ldc] = alpha*rC[1][4];
    C[40*ldc] = alpha*rC[1][5];
    C+=8;                     
    C[0*ldc] = alpha*rC[2][0] ;
    C[8*ldc] = alpha*rC[2][1] ;
    C[16*ldc] = alpha*rC[2][2];
    C[24*ldc] = alpha*rC[2][3];
    C[32*ldc] = alpha*rC[2][4];
    C[40*ldc] = alpha*rC[2][5];
    C+=8;                     
    C[0*ldc] = alpha*rC[3][0] ;
    C[8*ldc] = alpha*rC[3][1] ;
    C[16*ldc] = alpha*rC[3][2];
    C[24*ldc] = alpha*rC[3][3];
    C[32*ldc] = alpha*rC[3][4];
    C[40*ldc] = alpha*rC[3][5];
    C+=8;                     
    C[0*ldc] = alpha*rC[4][0] ;
    C[8*ldc] = alpha*rC[4][1] ;
    C[16*ldc] = alpha*rC[4][2];
    C[24*ldc] = alpha*rC[4][3];
    C[32*ldc] = alpha*rC[4][4];
    C[40*ldc] = alpha*rC[4][5];
    C+=8;                     
    C[0*ldc] = alpha*rC[5][0] ;
    C[8*ldc] = alpha*rC[5][1] ;
    C[16*ldc] = alpha*rC[5][2];
    C[24*ldc] = alpha*rC[5][3];
    C[32*ldc] = alpha*rC[5][4];
    C[40*ldc] = alpha*rC[5][5];
    
}
"; 


static const char * dgemm_TN_48_48_16_8x8_6x6__ALPHABETA = " 


__attribute__( (reqd_work_group_size(8, 8, 1)) )
__kernel void dgemm_TN_48_48_16_8x8_6x6__ALPHABETA(  __global double const * restrict A, 
                                          __global double const * restrict B,
                                          __global double * C,  
                                          uint const M, 
                                          uint const N, 
                                          uint const K,
                                          double const alpha,  
                                          double const beta,  
                                          uint lda,
                                          uint ldb, 
                                          uint ldc, 
                                          uint const offsetA, 
                                          uint const offsetB, 
                                          uint const offsetC)
{
    double rC[6][6]  = {(double)0};
    double rA[1][6];
    double rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local double lA[784];
    __local double lB[784];
    
    int gidx = get_group_id(0);
    int gidy = get_group_id(1);
    int idx = get_local_id(0);
    int idy = get_local_id(1);
    
    int idt = 8*idy + idx;
    int idxT = idt % 8;
    int idyT = idt / 8;
    
    A +=  gidx*48*lda + idxT + idyT*lda;
    B +=  gidy*48*ldb+ idxT + idyT*ldb;
    
    //for( int block_k=0 ; block_k< K ; block_k+=16)
	uint block_k = K >> 4;
    do
    {
        __local double* plA = lA + idxT*49+ idyT;
        __local double* plB = lB + idxT*49+ idyT;
      
        barrier(CLK_LOCAL_MEM_FENCE);
        plA[0] = A[0+0*lda];
        plA[392] = A[8+0*lda];
        plA[8] = A[0+8*lda];
        plA[400] = A[8+8*lda];
        plA[16] = A[0+16*lda];
        plA[408] = A[8+16*lda];
        plA[24] = A[0+24*lda];
        plA[416] = A[8+24*lda];
        plA[32] = A[0+32*lda];
        plA[424] = A[8+32*lda];
        plA[40] = A[0+40*lda];
        plA[432] = A[8+40*lda];
        plB[0] = B[0+0*ldb];
        plB[392] = B[8+0*ldb];
        plB[8] = B[0+8*ldb];
        plB[400] = B[8+8*ldb];
        plB[16] = B[0+16*ldb];
        plB[408] = B[8+16*ldb];
        plB[24] = B[0+24*ldb];
        plB[416] = B[8+24*ldb];
        plB[32] = B[0+32*ldb];
        plB[424] = B[8+32*ldb];
        plB[40] = B[0+40*ldb];
        plB[432] = B[8+40*ldb];
        barrier(CLK_LOCAL_MEM_FENCE);
       
        int offA = 1*idx;
        int offB = 1*idy;
       
        for( int k = 0 ; k < 16; k+=1)
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
        A += 16;
        B += 16;
    }
	while (--block_k > 0);

    C+= gidx*48;
    C+= idx*1;
    C+= gidy*48*ldc;
    C+= idy*1*ldc;
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
    C[0] = alpha*rC[5][0] + beta*C[0];
    C[8*ldc] = alpha*rC[5][1] + beta*C[8*ldc];
    C[16*ldc] = alpha*rC[5][2] + beta*C[16*ldc];
    C[24*ldc] = alpha*rC[5][3] + beta*C[24*ldc];
    C[32*ldc] = alpha*rC[5][4] + beta*C[32*ldc];
    C[40*ldc] = alpha*rC[5][5] + beta*C[40*ldc];
    C+=8;
}
";


static const char * dgemm_TN_48_48_16_8x8_6x6__ALPHA = " 


__attribute__( (reqd_work_group_size(8, 8, 1)) )
__kernel void dgemm_TN_48_48_16_8x8_6x6__ALPHA(  __global double const * restrict A, 
                                          __global double const * restrict B,
                                          __global double * C,  
                                          uint const M, 
                                          uint const N, 
                                          uint const K,
                                          double const alpha, 
                                          uint lda,
                                          uint ldb, 
                                          uint ldc, 
                                          uint const offsetA, 
                                          uint const offsetB, 
                                          uint const offsetC)
{
    double rC[6][6]  = {(double)0};
    double rA[1][6];
    double rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local double lA[784];
    __local double lB[784];
    
    int gidx = get_group_id(0);
    int gidy = get_group_id(1);
    int idx = get_local_id(0);
    int idy = get_local_id(1);
    
    int idt = 8*idy + idx;
    int idxT = idt % 8;
    int idyT = idt / 8;
    
    A +=  gidx*48*lda + idxT + idyT*lda;
    B +=  gidy*48*ldb+ idxT + idyT*ldb;
    
    //for( int block_k=0 ; block_k< K ; block_k+=16)
	uint block_k = K >> 4;
    do
    {
        __local double* plA = lA + idxT*49+ idyT;
        __local double* plB = lB + idxT*49+ idyT;
      
        barrier(CLK_LOCAL_MEM_FENCE);
        plA[0] = A[0+0*lda];
        plA[392] = A[8+0*lda];
        plA[8] = A[0+8*lda];
        plA[400] = A[8+8*lda];
        plA[16] = A[0+16*lda];
        plA[408] = A[8+16*lda];
        plA[24] = A[0+24*lda];
        plA[416] = A[8+24*lda];
        plA[32] = A[0+32*lda];
        plA[424] = A[8+32*lda];
        plA[40] = A[0+40*lda];
        plA[432] = A[8+40*lda];
        plB[0] = B[0+0*ldb];
        plB[392] = B[8+0*ldb];
        plB[8] = B[0+8*ldb];
        plB[400] = B[8+8*ldb];
        plB[16] = B[0+16*ldb];
        plB[408] = B[8+16*ldb];
        plB[24] = B[0+24*ldb];
        plB[416] = B[8+24*ldb];
        plB[32] = B[0+32*ldb];
        plB[424] = B[8+32*ldb];
        plB[40] = B[0+40*ldb];
        plB[432] = B[8+40*ldb];
        barrier(CLK_LOCAL_MEM_FENCE);
       
        int offA = 1*idx;
        int offB = 1*idy;
       
        for( int k = 0 ; k < 16; k+=1)
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
        A += 16;
        B += 16;
    }
	while (--block_k > 0);

    C+= gidx*48;
    C+= idx;
    C+= gidy*48*ldc;
    C+= idy*ldc;

    C[0*ldc] = alpha*rC[0][0] ;
    C[8*ldc] = alpha*rC[0][1] ;
    C[16*ldc] = alpha*rC[0][2];
    C[24*ldc] = alpha*rC[0][3];
    C[32*ldc] = alpha*rC[0][4];
    C[40*ldc] = alpha*rC[0][5];
    C+=8;                     
    C[0*ldc] = alpha*rC[1][0] ;
    C[8*ldc] = alpha*rC[1][1] ;
    C[16*ldc] = alpha*rC[1][2];
    C[24*ldc] = alpha*rC[1][3];
    C[32*ldc] = alpha*rC[1][4];
    C[40*ldc] = alpha*rC[1][5];
    C+=8;                     
    C[0*ldc] = alpha*rC[2][0] ;
    C[8*ldc] = alpha*rC[2][1] ;
    C[16*ldc] = alpha*rC[2][2];
    C[24*ldc] = alpha*rC[2][3];
    C[32*ldc] = alpha*rC[2][4];
    C[40*ldc] = alpha*rC[2][5];
    C+=8;                     
    C[0*ldc] = alpha*rC[3][0] ;
    C[8*ldc] = alpha*rC[3][1] ;
    C[16*ldc] = alpha*rC[3][2];
    C[24*ldc] = alpha*rC[3][3];
    C[32*ldc] = alpha*rC[3][4];
    C[40*ldc] = alpha*rC[3][5];
    C+=8;                     
    C[0*ldc] = alpha*rC[4][0] ;
    C[8*ldc] = alpha*rC[4][1] ;
    C[16*ldc] = alpha*rC[4][2];
    C[24*ldc] = alpha*rC[4][3];
    C[32*ldc] = alpha*rC[4][4];
    C[40*ldc] = alpha*rC[4][5];
    C+=8;                     
    C[0] = alpha*rC[5][0]     ;
    C[8*ldc] = alpha*rC[5][1] ;
    C[16*ldc] = alpha*rC[5][2];
    C[24*ldc] = alpha*rC[5][3];
    C[32*ldc] = alpha*rC[5][4];
    C[40*ldc] = alpha*rC[5][5];
    
}
";

static const char * dgemm_TN_1_1_1_8x16_4x2__ALPHABETA = " 

__attribute__( (reqd_work_group_size(8, 16, 1)) )
__kernel void dgemm_TN_1_1_1_8x16_4x2__ALPHABETA(  __global double const * restrict A, 
                                        __global double const * restrict B,
                                        __global double * C, 
                                        uint const M, 
                                        uint const N, 
                                        uint const K,
                                        double const alpha,  
                                        double const beta,
                                        uint lda,
                                        uint ldb, 
                                        uint ldc, 
                                        uint const offsetA, 
                                        uint const offsetB, 
                                        uint const offsetC)
{
    double rC[4][2]  = {(double)0};
    double rA[1][4];
    double rB[1][2];
    
    
    A += offsetA;
    B += offsetB;
    C += offsetC;
    
    __local double lA[528];
    __local double lB[528];
    
    int gidx = get_group_id(0);
    int gidy = get_group_id(1);
    int idx = get_local_id(0);
    int idy = get_local_id(1);
    
    int idt = 8*idy + idx;
    int idxT = idt % 16;
    int idyT = idt / 16;

    A +=  gidx*32*lda + idxT + idyT*lda;
    B +=  gidy*32*ldb+ idxT + idyT*ldb;
   
    __local double* plA = lA + idxT*33+ idyT;
    __local double* plB = lB + idxT*33+ idyT;


    if(gidx==get_num_groups(0)-1 || gidy==get_num_groups(1)-1 )
    {
      int CurrentOffSetA =  idyT;
      int CurrentOffSetB =  idyT;

      for( int block_k=0 ; block_k< K ; block_k+=16)
      {
        barrier(CLK_LOCAL_MEM_FENCE);
        plA[0] = CurrentOffSetA>=M?0.0:A[0];
        plA[8] = CurrentOffSetA+8>=M?0.0:A[8*lda];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16*lda];
        plA[24] = CurrentOffSetA+24>=M?0.0:A[24*lda];

        plB[0] = CurrentOffSetB>=N?0.0:B[0];
        plB[8] = CurrentOffSetB+8>=N?0.0:B[8*ldb];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];
        plB[24] = CurrentOffSetB+24>=N?0.0:B[24*ldb];
        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx;
        int offB = idy;

        for( int k = 0 ; k < min(16u, K-block_k); k+=1)
        {
          rA[0][0] = lA[offA ];
          rA[0][1] = lA[offA + 8];
          rA[0][2] = lA[offA + 16];
          rA[0][3] = lA[offA + 24];
          rB[0][0] = lB[offB ];
          rB[0][1] = lB[offB + 16];
          offA += 33;
          offB += 33;
          rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
          rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
          rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
          rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
          rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
          rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
          rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
          rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        }
        A += 16;
        B += 16;
      }
   
      C+= gidx*32;
      C+= idx;
      C+= gidy*32*ldc;
      C+= idy*ldc;

      int OffSetCM = gidx*32+idx;
      int OffSetCN = gidy*32+idy;
      if(OffSetCM>=M || OffSetCN>=N)
        return;

      for(int i = 0; i<4; i++)
      {
        C[0*ldc] = alpha*rC[i][0] + beta*C[0];

        if (OffSetCN+16<N)
          C[16*ldc] = alpha*rC[i][1] + beta*C[16*ldc];

        C+=8;
        OffSetCM += 8;
        if(OffSetCM>=M)
          return;
      }

    }
    else
    {

      for( int block_k=0 ; block_k< K ; block_k+=16)
      {
        barrier(CLK_LOCAL_MEM_FENCE);
        plA[0] = A[0];
        plA[8] = A[8*lda];
        plA[16] = A[16*lda];
        plA[24] = A[24*lda];
        plB[0] = B[0];
        plB[8] = B[8*ldb];
        plB[16] = B[16*ldb];
        plB[24] = B[24*ldb];
        barrier(CLK_LOCAL_MEM_FENCE);
        
        int offA = idx;
        int offB = idy;

        for( int k = 0 ; k < min(16u, K-block_k); k+=1)
        {
          rA[0][0] = lA[offA ];
          rA[0][1] = lA[offA + 8];
          rA[0][2] = lA[offA + 16];
          rA[0][3] = lA[offA + 24];
          rB[0][0] = lB[offB ];
          rB[0][1] = lB[offB + 16];
          offA += 33;
          offB += 33;
          rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
          rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
          rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
          rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
          rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
          rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
          rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
          rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        }
        A += 16;
        
        B += 16;
        

      }
      C+= gidx*32;
      C+= idx*1;
      C+= gidy*32*ldc;
      C+= idy*1*ldc;
      C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
      C[16*ldc] = alpha*rC[0][1] + beta*C[16*ldc];
      C+=8;
      C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
      C[16*ldc] = alpha*rC[1][1] + beta*C[16*ldc];
      C+=8;
      C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
      C[16*ldc] = alpha*rC[2][1] + beta*C[16*ldc];
      C+=8;
      C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
      C[16*ldc] = alpha*rC[3][1] + beta*C[16*ldc];
      
    }
}
"; 


static const char * dgemm_TN_1_1_1_8x16_4x2__ALPHA = " 

__attribute__( (reqd_work_group_size(8, 16, 1)) )
__kernel void dgemm_TN_1_1_1_8x16_4x2__ALPHA(  __global double const * restrict A, 
                                        __global double const * restrict B,
                                        __global double * C, 
                                        uint const M, 
                                        uint const N, 
                                        uint const K,
                                        double const alpha,
                                        uint lda,
                                        uint ldb, 
                                        uint ldc, 
                                        uint const offsetA, 
                                        uint const offsetB, 
                                        uint const offsetC)
{
    double rC[4][2]  = {(double)0};
    double rA[1][4];
    double rB[1][2];
    
    
    A += offsetA;
    B += offsetB;
    C += offsetC;
    
    __local double lA[528];
    __local double lB[528];
    
    int gidx = get_group_id(0);
    int gidy = get_group_id(1);
    int idx = get_local_id(0);
    int idy = get_local_id(1);
    
    int idt = 8*idy + idx;
    int idxT = idt % 16;
    int idyT = idt / 16;

    A +=  gidx*32*lda + idxT + idyT*lda;
    B +=  gidy*32*ldb+ idxT + idyT*ldb;
   
    __local double* plA = lA + idxT*33+ idyT;
    __local double* plB = lB + idxT*33+ idyT;


    if(gidx==get_num_groups(0)-1 || gidy==get_num_groups(1)-1 )
    {
      int CurrentOffSetA =  idyT;
      int CurrentOffSetB =  idyT;

      for( int block_k=0 ; block_k< K ; block_k+=16)
      {
        barrier(CLK_LOCAL_MEM_FENCE);
        plA[0] = CurrentOffSetA>=M?0.0:A[0];
        plA[8] = CurrentOffSetA+8>=M?0.0:A[8*lda];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16*lda];
        plA[24] = CurrentOffSetA+24>=M?0.0:A[24*lda];

        plB[0] = CurrentOffSetB>=N?0.0:B[0];
        plB[8] = CurrentOffSetB+8>=N?0.0:B[8*ldb];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];
        plB[24] = CurrentOffSetB+24>=N?0.0:B[24*ldb];
        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx;
        int offB = idy;

        for( int k = 0 ; k < min(16u, K-block_k); k+=1)
        {
          rA[0][0] = lA[offA ];
          rA[0][1] = lA[offA + 8];
          rA[0][2] = lA[offA + 16];
          rA[0][3] = lA[offA + 24];
          rB[0][0] = lB[offB ];
          rB[0][1] = lB[offB + 16];
          offA += 33;
          offB += 33;
          rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
          rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
          rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
          rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
          rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
          rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
          rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
          rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        }
        A += 16;
        B += 16;
      }
   
      C+= gidx*32;
      C+= idx;
      C+= gidy*32*ldc;
      C+= idy*ldc;

      int OffSetCM = gidx*32+idx;
      int OffSetCN = gidy*32+idy;
      if(OffSetCM>=M || OffSetCN>=N)
        return;

      for(int i = 0; i<4; i++)
      {
        C[0*ldc] = alpha*rC[i][0];

        if (OffSetCN+16<N)
          C[16*ldc] = alpha*rC[i][1];

        C+=8;
        OffSetCM += 8;
        if(OffSetCM>=M)
          return;
      }

    }
    else
    {

      for( int block_k=0 ; block_k< K ; block_k+=16)
      {
        barrier(CLK_LOCAL_MEM_FENCE);
        plA[0] = A[0];
        plA[8] = A[8*lda];
        plA[16] = A[16*lda];
        plA[24] = A[24*lda];
        plB[0] = B[0];
        plB[8] = B[8*ldb];
        plB[16] = B[16*ldb];
        plB[24] = B[24*ldb];
        barrier(CLK_LOCAL_MEM_FENCE);
        
        int offA = idx;
        int offB = idy;

        for( int k = 0 ; k < min(16u, K-block_k); k+=1)
        {
          rA[0][0] = lA[offA ];
          rA[0][1] = lA[offA + 8];
          rA[0][2] = lA[offA + 16];
          rA[0][3] = lA[offA + 24];
          rB[0][0] = lB[offB ];
          rB[0][1] = lB[offB + 16];
          offA += 33;
          offB += 33;
          rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
          rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
          rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
          rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
          rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
          rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
          rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
          rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        }
        A += 16;
        
        B += 16;
        

      }
      C+= gidx*32;
      C+= idx;
      C+= gidy*32*ldc;
      C+= idy*ldc;
      C[0*ldc] = alpha*rC[0][0];
      C[16*ldc] = alpha*rC[0][1];
      C+=8;
      C[0*ldc] = alpha*rC[1][0];
      C[16*ldc] = alpha*rC[1][1];
      C+=8;
      C[0*ldc] = alpha*rC[2][0];
      C[16*ldc] = alpha*rC[2][1];
      C+=8;
      C[0*ldc] = alpha*rC[3][0];
      C[16*ldc] = alpha*rC[3][1];
      
    }
}
"; 

static const char * dgemm_TN_1_1_16_8x16_4x2__ALPHABETA = "


__attribute__( (reqd_work_group_size(8, 16, 1)) )
__kernel void dgemm_TN_1_1_16_8x16_4x2__ALPHABETA(  __global double const * restrict A, 
                                         __global double const * restrict B,
                                         __global double * C,  
                                         uint const M, 
                                         uint const N, 
                                         uint const K,
                                         double const alpha,  
                                         double const beta,   
                                         uint lda,
                                         uint ldb, 
                                         uint ldc, 
                                         uint const offsetA, 
                                         uint const offsetB, 
                                         uint const offsetC)
{
    double rC[4][2]  = {(double)0};
    double rA[1][4];
    double rB[1][2];
    
    
    A += offsetA;
    B += offsetB;
    C += offsetC;
    
    __local double lA[528];
    __local double lB[528];
    
    int gidx = get_group_id(0);
    int gidy = get_group_id(1);
    int idx = get_local_id(0);
    int idy = get_local_id(1);
    
    int idt = 8*idy + idx;
    int idxT = idt % 16;
    int idyT = idt / 16;

    A +=  gidx*32*lda + idxT + idyT*lda;
    B +=  gidy*32*ldb+ idxT + idyT*ldb;
   
    __local double* plA = lA + idxT*33+ idyT;
    __local double* plB = lB + idxT*33+ idyT;


    if(gidx==get_num_groups(0)-1 || gidy==get_num_groups(1)-1 )
    {
      int CurrentOffSetA =  idyT;
      int CurrentOffSetB =  idyT;

      for( int block_k=0 ; block_k< K ; block_k+=16)
      {
        barrier(CLK_LOCAL_MEM_FENCE);
        plA[0] = CurrentOffSetA>=M?0.0:A[0];
        plA[8] = CurrentOffSetA+8>=M?0.0:A[8*lda];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16*lda];
        plA[24] = CurrentOffSetA+24>=M?0.0:A[24*lda];

        plB[0] = CurrentOffSetB>=N?0.0:B[0];
        plB[8] = CurrentOffSetB+8>=N?0.0:B[8*ldb];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];
        plB[24] = CurrentOffSetB+24>=N?0.0:B[24*ldb];
        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx;
        int offB = idy;

        for( int k = 0 ; k < 16; k+=1)
        {
          rA[0][0] = lA[offA ];
          rA[0][1] = lA[offA + 8];
          rA[0][2] = lA[offA + 16];
          rA[0][3] = lA[offA + 24];
          rB[0][0] = lB[offB ];
          rB[0][1] = lB[offB + 16];
          offA += 33;
          offB += 33;
          rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
          rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
          rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
          rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
          rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
          rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
          rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
          rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        }
        A += 16;
        B += 16;
      }
   
      C+= gidx*32;
      C+= idx;
      C+= gidy*32*ldc;
      C+= idy*ldc;

      int OffSetCM = gidx*32+idx;
      int OffSetCN = gidy*32+idy;
      if(OffSetCM>=M || OffSetCN>=N)
        return;



      for(int i = 0; i<4; i++)
      {
        C[0*ldc] = alpha*rC[i][0] + beta*C[0];

        if (OffSetCN+16<N)
          C[16*ldc] = alpha*rC[i][1] + beta*C[16*ldc];

        C+=8;
        OffSetCM += 8;
        if(OffSetCM>=M)
          return;
      }

    }
    else
    {

      for( int block_k=0 ; block_k< K ; block_k+=16)
      {
        barrier(CLK_LOCAL_MEM_FENCE);
        plA[0] = A[0];
        plA[8] = A[8*lda];
        plA[16] = A[16*lda];
        plA[24] = A[24*lda];
        plB[0] = B[0];
        plB[8] = B[8*ldb];
        plB[16] = B[16*ldb];
        plB[24] = B[24*ldb];
        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx;
        int offB = idy;

        for( int k = 0 ; k < 16; k+=1)
        {
          rA[0][0] = lA[offA ];
          rA[0][1] = lA[offA + 8];
          rA[0][2] = lA[offA + 16];
          rA[0][3] = lA[offA + 24];
          rB[0][0] = lB[offB ];
          rB[0][1] = lB[offB + 16];
          offA += 33;
          offB += 33;
          rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
          rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
          rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
          rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
          rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
          rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
          rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
          rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        }
        A += 16;
        B += 16;

      }
      C+= gidx*32;
      C+= idx*1;
      C+= gidy*32*ldc;
      C+= idy*1*ldc;
      C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
      C[16*ldc] = alpha*rC[0][1] + beta*C[16*ldc];
      C+=8;
      C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
      C[16*ldc] = alpha*rC[1][1] + beta*C[16*ldc];
      C+=8;
      C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
      C[16*ldc] = alpha*rC[2][1] + beta*C[16*ldc];
      C+=8;
      C[0*ldc] = alpha*rC[3][0] + beta*C[0];
      C[16*ldc] = alpha*rC[3][1] + beta*C[16*ldc];
      C+=8;
    }
}
"; 


static const char * dgemm_TN_1_1_16_8x16_4x2__ALPHA = "


__attribute__( (reqd_work_group_size(8, 16, 1)) )
__kernel void dgemm_TN_1_1_16_8x16_4x2__ALPHA(  __global double const * restrict A, 
                                         __global double const * restrict B,
                                         __global double * C,  
                                         uint const M, 
                                         uint const N, 
                                         uint const K,
                                         double const alpha,  
                                         uint lda,
                                         uint ldb, 
                                         uint ldc, 
                                         uint const offsetA, 
                                         uint const offsetB, 
                                         uint const offsetC)
{
    double rC[4][2]  = {(double)0};
    double rA[1][4];
    double rB[1][2];
    
    
    A += offsetA;
    B += offsetB;
    C += offsetC;
    
    __local double lA[528];
    __local double lB[528];
    
    int gidx = get_group_id(0);
    int gidy = get_group_id(1);
    int idx = get_local_id(0);
    int idy = get_local_id(1);
    
    int idt = 8*idy + idx;
    int idxT = idt % 16;
    int idyT = idt / 16;

    A +=  gidx*32*lda + idxT + idyT*lda;
    B +=  gidy*32*ldb+ idxT + idyT*ldb;
   
    __local double* plA = lA + idxT*33+ idyT;
    __local double* plB = lB + idxT*33+ idyT;


    if(gidx==get_num_groups(0)-1 || gidy==get_num_groups(1)-1 )
    {
      int CurrentOffSetA =  idyT;
      int CurrentOffSetB =  idyT;

      for( int block_k=0 ; block_k< K ; block_k+=16)
      {
        barrier(CLK_LOCAL_MEM_FENCE);
        plA[0] = CurrentOffSetA>=M?0.0:A[0];
        plA[8] = CurrentOffSetA+8>=M?0.0:A[8*lda];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16*lda];
        plA[24] = CurrentOffSetA+24>=M?0.0:A[24*lda];

        plB[0] = CurrentOffSetB>=N?0.0:B[0];
        plB[8] = CurrentOffSetB+8>=N?0.0:B[8*ldb];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];
        plB[24] = CurrentOffSetB+24>=N?0.0:B[24*ldb];
        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx;
        int offB = idy;

        for( int k = 0 ; k < 16; k+=1)
        {
          rA[0][0] = lA[offA ];
          rA[0][1] = lA[offA + 8];
          rA[0][2] = lA[offA + 16];
          rA[0][3] = lA[offA + 24];
          rB[0][0] = lB[offB ];
          rB[0][1] = lB[offB + 16];
          offA += 33;
          offB += 33;
          rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
          rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
          rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
          rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
          rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
          rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
          rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
          rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        }
        A += 16;
        B += 16;
      }
   
      C+= gidx*32;
      C+= idx;
      C+= gidy*32*ldc;
      C+= idy*ldc;

      int OffSetCM = gidx*32+idx;
      int OffSetCN = gidy*32+idy;
      if(OffSetCM>=M || OffSetCN>=N)
        return;



      for(int i = 0; i<4; i++)
      {
        C[0*ldc] = alpha*rC[i][0];

        if (OffSetCN+16<N)
          C[16*ldc] = alpha*rC[i][1];

        C+=8;
        OffSetCM += 8;
        if(OffSetCM>=M)
          return;
      }

    }
    else
    {

      for( int block_k=0 ; block_k< K ; block_k+=16)
      {
        barrier(CLK_LOCAL_MEM_FENCE);
        plA[0] = A[0];
        plA[8] = A[8*lda];
        plA[16] = A[16*lda];
        plA[24] = A[24*lda];
        plB[0] = B[0];
        plB[8] = B[8*ldb];
        plB[16] = B[16*ldb];
        plB[24] = B[24*ldb];
        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx;
        int offB = idy;

        for( int k = 0 ; k < 16; k+=1)
        {
          rA[0][0] = lA[offA ];
          rA[0][1] = lA[offA + 8];
          rA[0][2] = lA[offA + 16];
          rA[0][3] = lA[offA + 24];
          rB[0][0] = lB[offB ];
          rB[0][1] = lB[offB + 16];
          offA += 33;
          offB += 33;
          rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
          rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
          rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
          rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
          rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
          rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
          rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
          rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        }
        A += 16;
        B += 16;

      }
      C+= gidx*32;
      C+= idx*1;
      C+= gidy*32*ldc;
      C+= idy*1*ldc;
      C[0*ldc] = alpha*rC[0][0];
      C[16*ldc] = alpha*rC[0][1];
      C+=8;
      C[0*ldc] = alpha*rC[1][0];
      C[16*ldc] = alpha*rC[1][1];
      C+=8;
      C[0*ldc] = alpha*rC[2][0];
      C[16*ldc] = alpha*rC[2][1];
      C+=8;
      C[0*ldc] = alpha*rC[3][0];
      C[16*ldc] = alpha*rC[3][1];
      
    }
}
"; 


static const char * dgemm_TN_32_32_1_8x16_4x2__ALPHABETA = "


__attribute__( (reqd_work_group_size(8, 16, 1)) )
__kernel void dgemm_TN_32_32_1_8x16_4x2__ALPHABETA(  __global double const * restrict A, 
                                          __global double const * restrict B,
                                          __global double * C,  
                                          uint const M, 
                                          uint const N, 
                                          uint const K,
                                          double const alpha,  
                                          double const beta,   
                                          uint lda,
                                          uint ldb, 
                                          uint ldc, 
                                          uint const offsetA, 
                                          uint const offsetB, 
                                          uint const offsetC)
{
    double rC[4][2]  = {(double)0};
    double rA[1][4];
    double rB[1][2];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local double lA[528];
    __local double lB[528];
    
    int gidx = get_group_id(0);
    int gidy = get_group_id(1);
    int idx = get_local_id(0);
    int idy = get_local_id(1);
    
    int idt = 8*idy + idx;
    int idxT = idt % 16;
    int idyT = idt / 16;
    
    A +=  gidx*32*lda + idxT + idyT*lda;
    B +=  gidy*32*ldb+ idxT + idyT*ldb;
    
    for( int block_k=0 ; block_k< K ; block_k+=16)
    {
        __local double* plA = lA + idxT*33+ idyT;
        __local double* plB = lB + idxT*33+ idyT;
        
        barrier(CLK_LOCAL_MEM_FENCE);
        plA[0] = A[0+0*lda];
        plA[8] = A[0+8*lda];
        plA[16] = A[0+16*lda];
        plA[24] = A[0+24*lda];
        plB[0] = B[0+0*ldb];
        plB[8] = B[0+8*ldb];
        plB[16] = B[0+16*ldb];
        plB[24] = B[0+24*ldb];
        barrier(CLK_LOCAL_MEM_FENCE);
       
        int offA = 1*idx;
        int offB = 1*idy;
        
        for( int k = 0 ; k < min(16u, K-block_k); k+=1)
        {
            rA[0][0] = lA[offA + 0];
            rA[0][1] = lA[offA + 8];
            rA[0][2] = lA[offA + 16];
            rA[0][3] = lA[offA + 24];
            rB[0][0] = lB[offB + 0];
            rB[0][1] = lB[offB + 16];
            offA += 33;
            offB += 33;
            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
            rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
            rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
            rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
            rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        }
        A += 16;
        B += 16;
    }
    C+= gidx*32;
    C+= idx*1;
    C+= gidy*32*ldc;
    C+= idy*1*ldc;
    C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[0][1] + beta*C[16*ldc];
    C+=8;
    C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[1][1] + beta*C[16*ldc];
    C+=8;
    C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[2][1] + beta*C[16*ldc];
    C+=8;
    C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[3][1] + beta*C[16*ldc];
    C+=8;
}

"; 


static const char * dgemm_TN_32_32_1_8x16_4x2__ALPHA = "


__attribute__( (reqd_work_group_size(8, 16, 1)) )
__kernel void dgemm_TN_32_32_1_8x16_4x2__ALPHA(  __global double const * restrict A, 
                                          __global double const * restrict B,
                                          __global double * C,  
                                          uint const M, 
                                          uint const N, 
                                          uint const K,
                                          double const alpha,  
                                          uint lda,
                                          uint ldb, 
                                          uint ldc, 
                                          uint const offsetA, 
                                          uint const offsetB, 
                                          uint const offsetC)
{
    double rC[4][2]  = {(double)0};
    double rA[1][4];
    double rB[1][2];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local double lA[528];
    __local double lB[528];
    
    int gidx = get_group_id(0);
    int gidy = get_group_id(1);
    int idx = get_local_id(0);
    int idy = get_local_id(1);
    
    int idt = 8*idy + idx;
    int idxT = idt % 16;
    int idyT = idt / 16;
    
    A +=  gidx*32*lda + idxT + idyT*lda;
    B +=  gidy*32*ldb+ idxT + idyT*ldb;
    
    for( int block_k=0 ; block_k< K ; block_k+=16)
    {
        __local double* plA = lA + idxT*33+ idyT;
        __local double* plB = lB + idxT*33+ idyT;
        
        barrier(CLK_LOCAL_MEM_FENCE);
        plA[0] = A[0+0*lda];
        plA[8] = A[0+8*lda];
        plA[16] = A[0+16*lda];
        plA[24] = A[0+24*lda];
        plB[0] = B[0+0*ldb];
        plB[8] = B[0+8*ldb];
        plB[16] = B[0+16*ldb];
        plB[24] = B[0+24*ldb];
        barrier(CLK_LOCAL_MEM_FENCE);
       
        int offA = 1*idx;
        int offB = 1*idy;
        
        for( int k = 0 ; k < min(16u, K-block_k); k+=1)
        {
            rA[0][0] = lA[offA + 0];
            rA[0][1] = lA[offA + 8];
            rA[0][2] = lA[offA + 16];
            rA[0][3] = lA[offA + 24];
            rB[0][0] = lB[offB + 0];
            rB[0][1] = lB[offB + 16];
            offA += 33;
            offB += 33;
            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
            rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
            rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
            rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
            rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        }
        A += 16;
        B += 16;
    }
    C+= gidx*32;
    C+= idx*1;
    C+= gidy*32*ldc;
    C+= idy*1*ldc;
    C[0*ldc] = alpha*rC[0][0];
    C[16*ldc] = alpha*rC[0][1];
    C+=8;
    C[0*ldc] = alpha*rC[1][0];
    C[16*ldc] = alpha*rC[1][1];
    C+=8;
    C[0*ldc] = alpha*rC[2][0];
    C[16*ldc] = alpha*rC[2][1];
    C+=8;
    C[0*ldc] = alpha*rC[3][0];
    C[16*ldc] = alpha*rC[3][1];
    
}

"; 

static const char * dgemm_NN_48_48_8_8x8_6x6__ALPHABETA = "
__attribute__( (reqd_work_group_size(8, 8, 1)) )
  __kernel void dgemm_NN_48_48_8_8x8_6x6__ALPHABETA(__global double const * restrict A,
  __global double const * restrict B,
  __global double * C,
  uint const M,
  uint const N,
  uint const K,
  double const alpha,
  double const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
  double rC[6][6]  = {(double)0};
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
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*48+ idxT + idyT*lda;
  B +=  gidy*48*ldb+ idx + idy*ldb;

  __local double* plA = lA + idyT*49 + idxT;
  __local double* plB = lB + idxT*49 + idyT;


  //for( int block_k=0 ; block_k< K ; block_k+=8)
  uint block_k = K >> 3;
  do
  {
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
    
    int offA = 1*idx;
    int offB = 1*idy;
    
    for( int k = 0 ; k < 8; k+=1){
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
    A += 8*lda;
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
 
}

";

static const char * dgemm_NN_48_48_8_8x8_6x6__ALPHA = "
__attribute__( (reqd_work_group_size(8, 8, 1)) )
  __kernel void dgemm_NN_48_48_8_8x8_6x6__ALPHA(__global double const * restrict A,
  __global double const * restrict B,
  __global double * C,
  uint const M,
  uint const N,
  uint const K,
  double const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
  double rC[6][6]  = {(double)0};
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
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*48+ idxT + idyT*lda;
  B +=  gidy*48*ldb+ idx + idy*ldb;

  __local double* plA = lA + idyT*49 + idxT;
  __local double* plB = lB + idxT*49 + idyT;


  //for( int block_k=0 ; block_k< K ; block_k+=8)
  uint block_k = K >> 3;
  do
  {
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
    
    int offA = 1*idx;
    int offB = 1*idy;
    
    for( int k = 0 ; k < 8; k+=1){
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
    A += 8*lda;
    B += 8;
  }
  while (--block_k > 0);

  C+= gidx*48;
  C+= idx;
  C+= gidy*48*ldc;
  C+= idy*ldc;
 
	C[0*ldc] = alpha*rC[0][0] ;
  C[8*ldc] = alpha*rC[0][1] ;
  C[16*ldc] = alpha*rC[0][2];
  C[24*ldc] = alpha*rC[0][3];
  C[32*ldc] = alpha*rC[0][4];
  C[40*ldc] = alpha*rC[0][5];
  C+=8;                     
  C[0*ldc] = alpha*rC[1][0] ;
  C[8*ldc] = alpha*rC[1][1] ;
  C[16*ldc] = alpha*rC[1][2];
  C[24*ldc] = alpha*rC[1][3];
  C[32*ldc] = alpha*rC[1][4];
  C[40*ldc] = alpha*rC[1][5];
  C+=8;                     
  C[0*ldc] = alpha*rC[2][0] ;
  C[8*ldc] = alpha*rC[2][1] ;
  C[16*ldc] = alpha*rC[2][2];
  C[24*ldc] = alpha*rC[2][3];
  C[32*ldc] = alpha*rC[2][4];
  C[40*ldc] = alpha*rC[2][5];
  C+=8;                     
  C[0*ldc] = alpha*rC[3][0] ;
  C[8*ldc] = alpha*rC[3][1] ;
  C[16*ldc] = alpha*rC[3][2];
  C[24*ldc] = alpha*rC[3][3];
  C[32*ldc] = alpha*rC[3][4];
  C[40*ldc] = alpha*rC[3][5];
  C+=8;                     
  C[0*ldc] = alpha*rC[4][0] ;
  C[8*ldc] = alpha*rC[4][1] ;
  C[16*ldc] = alpha*rC[4][2];
  C[24*ldc] = alpha*rC[4][3];
  C[32*ldc] = alpha*rC[4][4];
  C[40*ldc] = alpha*rC[4][5];
  C+=8;                     
  C[0*ldc] = alpha*rC[5][0] ;
  C[8*ldc] = alpha*rC[5][1] ;
  C[16*ldc] = alpha*rC[5][2];
  C[24*ldc] = alpha*rC[5][3];
  C[32*ldc] = alpha*rC[5][4];
  C[40*ldc] = alpha*rC[5][5];
 
}

";


static const char * dgemm_NN_32_32_8_8x8_4x4__ALPHABETA = "
__attribute__( (reqd_work_group_size(8, 8, 1)) )
  __kernel void dgemm_NN_32_32_8_8x8_4x4__ALPHABETA(__global double const * restrict A,
  __global double const * restrict B,
  __global double * C,
  uint const M,
  uint const N,
  uint const K,
  double const alpha,
  double const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
  double rC[4][4]  = {(double)0};
  double rA[1][4];
  double rB[1][4];

  double PreFetchA[4];
  double PreFetchB[4];


  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[264];
  __local double lB[264];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*32+ idxT + idyT*lda;
  B +=  gidy*32*ldb+ idxT + idyT*ldb;


  __local double* plA = lA + idyT*33 + idxT;
  __local double* plB = lB + idxT*33 + idyT;


    plA[0] = A[0];
    plA[8] = A[8];
    plA[16] = A[16];
    plA[24] = A[24];
    plB[0] = B[0];
    plB[8] = B[8*ldb];
    plB[16] = B[16*ldb];
    plB[24] = B[24*ldb];
    barrier(CLK_LOCAL_MEM_FENCE);


  for( int block_k=0 ; block_k< K ; block_k+=8)
  {

   // barrier(CLK_LOCAL_MEM_FENCE);
    A += 8*lda;
    B += 8;

	PreFetchA[0] = A[0];
	PreFetchA[1] = A[8];
	PreFetchA[2] = A[16];
	PreFetchA[3] = A[24];

	PreFetchB[0] = B[0];
	PreFetchB[1] = B[8*ldb];
	PreFetchB[2] = B[16*ldb];
	PreFetchB[3] = B[24*ldb];

   /* plA[0] = A[0+0*lda];
    plA[8] = A[8+0*lda];
    plA[16] = A[16+0*lda];
    plA[24] = A[24+0*lda];
    plB[0] = B[0+0*ldb];
    plB[8] = B[0+8*ldb];
    plB[16] = B[0+16*ldb];
    plB[24] = B[0+24*ldb];*/
   // barrier(CLK_LOCAL_MEM_FENCE);

    int offA = idx;
    int offB = idy;

    for( int k = 0 ; k < 8; k+=1)
    {
      rA[0][0] = lA[offA + 0];
      rA[0][1] = lA[offA + 8];
      rA[0][2] = lA[offA + 16];
      rA[0][3] = lA[offA + 24];
      rB[0][0] = lB[offB + 0];
      rB[0][1] = lB[offB + 8];
      rB[0][2] = lB[offB + 16];
      rB[0][3] = lB[offB + 24];
      offA += 33;
      offB += 33;
      rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
      rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
      rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
      rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
      rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
      rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
      rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
      rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
      rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
      rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
      rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
      rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
      rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
      rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
      rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
      rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
    }

	barrier(CLK_LOCAL_MEM_FENCE);
	plA[0]  = PreFetchA[0];
    plA[8]  = PreFetchA[1];
    plA[16] = PreFetchA[2];
    plA[24] = PreFetchA[3];
    plB[0]  = PreFetchB[0];
    plB[8]  = PreFetchB[1];
    plB[16] = PreFetchB[2];
    plB[24] = PreFetchB[3];
	barrier(CLK_LOCAL_MEM_FENCE);
   /* A += 8*lda;
    B += 8;*/
  }


  C+= gidx*32;
  C+= idx;
  C+= gidy*32*ldc;
  C+= idy*ldc;
  
  C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[0][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[0][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[0][3] + beta*C[24*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[1][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[1][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[1][3] + beta*C[24*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[2][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[2][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[2][3] + beta*C[24*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[3][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[3][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[3][3] + beta*C[24*ldc];
  
}
";


static const char * dgemm_NN_32_32_8_8x8_4x4__ALPHA = "
__attribute__( (reqd_work_group_size(8, 8, 1)) )
  __kernel void dgemm_NN_32_32_8_8x8_4x4__ALPHA(__global double const * restrict A,
  __global double const * restrict B,
  __global double * C,
  uint const M,
  uint const N,
  uint const K,
  double const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
  double rC[4][4]  = {(double)0};
  double rA[1][4];
  double rB[1][4];

  double PreFetchA[4];
  double PreFetchB[4];


  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[264];
  __local double lB[264];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*32+ idxT + idyT*lda;
  B +=  gidy*32*ldb+ idxT + idyT*ldb;


  __local double* plA = lA + idyT*33 + idxT;
  __local double* plB = lB + idxT*33 + idyT;


    plA[0] = A[0];
    plA[8] = A[8];
    plA[16] = A[16];
    plA[24] = A[24];
    plB[0] = B[0];
    plB[8] = B[8*ldb];
    plB[16] = B[16*ldb];
    plB[24] = B[24*ldb];
    barrier(CLK_LOCAL_MEM_FENCE);


  for( int block_k=0 ; block_k< K ; block_k+=8)
  {

   // barrier(CLK_LOCAL_MEM_FENCE);
    A += 8*lda;
    B += 8;

	PreFetchA[0] = A[0];
	PreFetchA[1] = A[8];
	PreFetchA[2] = A[16];
	PreFetchA[3] = A[24];

	PreFetchB[0] = B[0];
	PreFetchB[1] = B[8*ldb];
	PreFetchB[2] = B[16*ldb];
	PreFetchB[3] = B[24*ldb];

   /* plA[0] = A[0+0*lda];
    plA[8] = A[8+0*lda];
    plA[16] = A[16+0*lda];
    plA[24] = A[24+0*lda];
    plB[0] = B[0+0*ldb];
    plB[8] = B[0+8*ldb];
    plB[16] = B[0+16*ldb];
    plB[24] = B[0+24*ldb];*/
   // barrier(CLK_LOCAL_MEM_FENCE);

    int offA = idx;
    int offB = idy;

    for( int k = 0 ; k < 8; k+=1)
    {
      rA[0][0] = lA[offA + 0];
      rA[0][1] = lA[offA + 8];
      rA[0][2] = lA[offA + 16];
      rA[0][3] = lA[offA + 24];
      rB[0][0] = lB[offB + 0];
      rB[0][1] = lB[offB + 8];
      rB[0][2] = lB[offB + 16];
      rB[0][3] = lB[offB + 24];
      offA += 33;
      offB += 33;
      rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
      rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
      rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
      rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
      rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
      rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
      rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
      rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
      rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
      rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
      rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
      rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
      rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
      rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
      rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
      rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
    }

	barrier(CLK_LOCAL_MEM_FENCE);
	plA[0]  = PreFetchA[0];
    plA[8]  = PreFetchA[1];
    plA[16] = PreFetchA[2];
    plA[24] = PreFetchA[3];
    plB[0]  = PreFetchB[0];
    plB[8]  = PreFetchB[1];
    plB[16] = PreFetchB[2];
    plB[24] = PreFetchB[3];
	barrier(CLK_LOCAL_MEM_FENCE);
   /* A += 8*lda;
    B += 8;*/
  }


  C+= gidx*32;
  C+= idx;
  C+= gidy*32*ldc;
  C+= idy*ldc;
  
  C[0*ldc] = alpha*rC[0][0] ;
  C[8*ldc] = alpha*rC[0][1] ;
  C[16*ldc] = alpha*rC[0][2];
  C[24*ldc] = alpha*rC[0][3];
  C+=8;                     
  C[0*ldc] = alpha*rC[1][0] ;
  C[8*ldc] = alpha*rC[1][1] ;
  C[16*ldc] = alpha*rC[1][2];
  C[24*ldc] = alpha*rC[1][3];
  C+=8;                     
  C[0*ldc] = alpha*rC[2][0] ;
  C[8*ldc] = alpha*rC[2][1] ;
  C[16*ldc] = alpha*rC[2][2];
  C[24*ldc] = alpha*rC[2][3];
  C+=8;                     
  C[0*ldc] = alpha*rC[3][0] ;
  C[8*ldc] = alpha*rC[3][1] ;
  C[16*ldc] = alpha*rC[3][2];
  C[24*ldc] = alpha*rC[3][3];
  
}
";


static const char * dgemm_NN_1_1_8_8x8_4x4__ALPHABETA = "
__attribute__( (reqd_work_group_size(8, 8, 1)) )
  __kernel void dgemm_NN_1_1_8_8x8_4x4__ALPHABETA(__global double const * restrict A,
  __global double const * restrict B,
  __global double * C,
  uint const M,
  uint const N,
  uint const K,
  double const alpha,
  double const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
  double rC[4][4]  = {(double)0};
  double rA[1][4];
  double rB[1][4];


  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[264];
  __local double lB[264];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*32+ idxT + idyT*lda;
  B +=  gidy*32*ldb+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*33+idxT;
  __local double* plB = lB + idxT*33+ idyT;

  if(gidx==get_num_groups(0)-1 || gidy==get_num_groups(1)-1 )
  {
    int CurrentOffSetA =   gidx*32 + idxT;
    int CurrentOffSetB =  idyT;

    for( int block_k=0 ; block_k< K ; block_k+=8)
    {
      barrier(CLK_LOCAL_MEM_FENCE);
   
      plA[0] = CurrentOffSetA>=M?0.0:A[0];
      plA[8] = CurrentOffSetA+8>=M?0.0:A[8];
      plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
      plA[24] = CurrentOffSetA+24>=M?0.0:A[24];
     
      plB[0] = CurrentOffSetB>=N?0.0:B[0];
      plB[8] = CurrentOffSetB+8>=N?0.0:B[0+8*ldb];
      plB[16] = CurrentOffSetB+16>=N?0.0: B[0+16*ldb];
      plB[24] = CurrentOffSetB+24>=N?0.0:B[0+24*ldb];
     
      barrier(CLK_LOCAL_MEM_FENCE);
     
      int offA = idx;
      int offB = idy;

      for( int k = 0 ; k < 8; k+=1)
      {
        rA[0][0] = lA[offA + 0];
        rA[0][1] = lA[offA + 8];
        rA[0][2] = lA[offA + 16];
        rA[0][3] = lA[offA + 24];
        rB[0][0] = lB[offB + 0];
        rB[0][1] = lB[offB + 8];
        rB[0][2] = lB[offB + 16];
        rB[0][3] = lB[offB + 24];
        offA += 33;
        offB += 33;
        rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
        rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
        rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
        rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
        rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
        rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
        rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
        rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
        rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
        rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
        rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
        rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
        rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
        rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
        rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      }
      A += 8*lda;
      B += 8;
    }

    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;

    int OffSetCM = gidx*32+idx;
    int OffSetCN = gidy*32+idy;
    if(OffSetCM>=M || OffSetCN>=N)
      return;



    for (int i = 0; i<4; i++)
    {
      C[0] = alpha*rC[i][0] + beta*C[0];
       
      if (OffSetCN+8<N)
        C[8*ldc] = alpha*rC[i][1] + beta*C[8*ldc];

      if (OffSetCN+16<N)
        C[16*ldc] = alpha*rC[i][2] + beta*C[16*ldc];
    
      if (OffSetCN+24<N)
        C[24*ldc] = alpha*rC[i][3] + beta*C[24*ldc];

      C+=8;
      OffSetCM += 8;
      if(OffSetCM>=M)
        return;
    }
  }

  else
  {
    for( int block_k=0 ; block_k< K ; block_k+=8)
    {
      barrier(CLK_LOCAL_MEM_FENCE);
      plA[0] = A[0+0*lda];
      plA[8] = A[8+0*lda];
      plA[16] = A[16+0*lda];
      plA[24] = A[24+0*lda];
      plB[0] = B[0+0*ldb];
      plB[8] = B[0+8*ldb];
      plB[16] = B[0+16*ldb];
      plB[24] = B[0+24*ldb];
      barrier(CLK_LOCAL_MEM_FENCE);
     
      int offA = idx;
      int offB = idy;
      
      for( int k = 0 ; k < 8; k+=1)
      {
        rA[0][0] = lA[offA + 0];
        rA[0][1] = lA[offA + 8];
        rA[0][2] = lA[offA + 16];
        rA[0][3] = lA[offA + 24];
        rB[0][0] = lB[offB + 0];
        rB[0][1] = lB[offB + 8];
        rB[0][2] = lB[offB + 16];
        rB[0][3] = lB[offB + 24];
        offA += 33;
        offB += 33;
        rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
        rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
        rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
        rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
        rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
        rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
        rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
        rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
        rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
        rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
        rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
        rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
        rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
        rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
        rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      }
      A += 8*lda;
      B += 8;
    }
    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;



    for (int i = 0; i<4; i++)
    {
      C[0] = alpha*rC[i][0] + beta*C[0];
      C[8*ldc] = alpha*rC[i][1] + beta*C[8*ldc];
      C[16*ldc] = alpha*rC[i][2] + beta*C[16*ldc];
      C[24*ldc] = alpha*rC[i][3] + beta*C[24*ldc];
      C+=8;
    }
  }
}
";

static const char * dgemm_NN_1_1_8_8x8_4x4__ALPHA = "
__attribute__( (reqd_work_group_size(8, 8, 1)) )
  __kernel void dgemm_NN_1_1_8_8x8_4x4__ALPHA(__global double const * restrict A,
  __global double const * restrict B,
  __global double * C,
  uint const M,
  uint const N,
  uint const K,
  double const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
  double rC[4][4]  = {(double)0};
  double rA[1][4];
  double rB[1][4];


  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[264];
  __local double lB[264];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*32+ idxT + idyT*lda;
  B +=  gidy*32*ldb+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*33+idxT;
  __local double* plB = lB + idxT*33+ idyT;

  if(gidx==get_num_groups(0)-1 || gidy==get_num_groups(1)-1 )
  {
    int CurrentOffSetA =   gidx*32 + idxT;
    int CurrentOffSetB =  idyT;

    for( int block_k=0 ; block_k< K ; block_k+=8)
    {
      barrier(CLK_LOCAL_MEM_FENCE);
   
      plA[0] = CurrentOffSetA>=M?0.0:A[0];
      plA[8] = CurrentOffSetA+8>=M?0.0:A[8];
      plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
      plA[24] = CurrentOffSetA+24>=M?0.0:A[24];
     
      plB[0] = CurrentOffSetB>=N?0.0:B[0];
      plB[8] = CurrentOffSetB+8>=N?0.0:B[0+8*ldb];
      plB[16] = CurrentOffSetB+16>=N?0.0: B[0+16*ldb];
      plB[24] = CurrentOffSetB+24>=N?0.0:B[0+24*ldb];
     
      barrier(CLK_LOCAL_MEM_FENCE);
     
      int offA = idx;
      int offB = idy;

      for( int k = 0 ; k < 8; k+=1)
      {
        rA[0][0] = lA[offA + 0];
        rA[0][1] = lA[offA + 8];
        rA[0][2] = lA[offA + 16];
        rA[0][3] = lA[offA + 24];
        rB[0][0] = lB[offB + 0];
        rB[0][1] = lB[offB + 8];
        rB[0][2] = lB[offB + 16];
        rB[0][3] = lB[offB + 24];
        offA += 33;
        offB += 33;
        rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
        rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
        rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
        rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
        rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
        rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
        rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
        rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
        rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
        rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
        rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
        rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
        rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
        rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
        rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      }
      A += 8*lda;
      B += 8;
    }

    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;

    int OffSetCM = gidx*32+idx;
    int OffSetCN = gidy*32+idy;
    if(OffSetCM>=M || OffSetCN>=N)
      return;



    for (int i = 0; i<4; i++)
    {
      C[0] = alpha*rC[i][0];
       
      if (OffSetCN+8<N)
        C[8*ldc] = alpha*rC[i][1];

      if (OffSetCN+16<N)
        C[16*ldc] = alpha*rC[i][2];
    
      if (OffSetCN+24<N)
        C[24*ldc] = alpha*rC[i][3];

      C+=8;
      OffSetCM += 8;
      if(OffSetCM>=M)
        return;
    }
  }

  else
  {
    for( int block_k=0 ; block_k< K ; block_k+=8)
    {
      barrier(CLK_LOCAL_MEM_FENCE);
      plA[0] = A[0+0*lda];
      plA[8] = A[8+0*lda];
      plA[16] = A[16+0*lda];
      plA[24] = A[24+0*lda];
      plB[0] = B[0+0*ldb];
      plB[8] = B[0+8*ldb];
      plB[16] = B[0+16*ldb];
      plB[24] = B[0+24*ldb];
      barrier(CLK_LOCAL_MEM_FENCE);
     
      int offA = idx;
      int offB = idy;
      
      for( int k = 0 ; k < 8; k+=1)
      {
        rA[0][0] = lA[offA + 0];
        rA[0][1] = lA[offA + 8];
        rA[0][2] = lA[offA + 16];
        rA[0][3] = lA[offA + 24];
        rB[0][0] = lB[offB + 0];
        rB[0][1] = lB[offB + 8];
        rB[0][2] = lB[offB + 16];
        rB[0][3] = lB[offB + 24];
        offA += 33;
        offB += 33;
        rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
        rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
        rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
        rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
        rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
        rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
        rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
        rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
        rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
        rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
        rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
        rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
        rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
        rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
        rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      }
      A += 8*lda;
      B += 8;
    }
    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;



    for (int i = 0; i<4; i++)
    {
      C[0] = alpha*rC[i][0];
      C[8*ldc] = alpha*rC[i][1];
      C[16*ldc] = alpha*rC[i][2] ;
      C[24*ldc] = alpha*rC[i][3];
      C+=8;
    }
  }
}
";

static const char * dgemm_NN_1_1_1_8x8_4x4__ALPHABETA = "
__attribute__( (reqd_work_group_size(8, 8, 1)) )
  __kernel void dgemm_NN_1_1_1_8x8_4x4__ALPHABETA(__global double const * restrict A,
  __global double const * restrict B,
  __global double * C,
  uint const M,
  uint const N,
  uint const K,
  double const alpha,
  double const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
  double rC[4][4]  = {(double)0};
  double rA[1][4];
  double rB[1][4];


  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[264];
  __local double lB[264];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*32+ idxT + idyT*lda;
  B +=  gidy*32*ldb+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*33+idxT;
  __local double* plB = lB + idxT*33+ idyT;

  if(gidx==get_num_groups(0)-1 || gidy==get_num_groups(1)-1 )
  {
    int CurrentOffSetA =   gidx*32 + idxT;
    int CurrentOffSetB =  idyT;

    for( int block_k=0 ; block_k< K ; block_k+=8)
    {
      barrier(CLK_LOCAL_MEM_FENCE);
   
      plA[0] = CurrentOffSetA>=M?0.0:A[0];
      plA[8] = CurrentOffSetA+8>=M?0.0:A[8];
      plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
      plA[24] = CurrentOffSetA+24>=M?0.0:A[24];
     
      plB[0] = CurrentOffSetB>=N?0.0:B[0];
      plB[8] = CurrentOffSetB+8>=N?0.0:B[0+8*ldb];
      plB[16] = CurrentOffSetB+16>=N?0.0: B[0+16*ldb];
      plB[24] = CurrentOffSetB+24>=N?0.0:B[0+24*ldb];
     
      barrier(CLK_LOCAL_MEM_FENCE);
     
      int offA = idx;
      int offB = idy;

      for( int k = 0 ; k < min(8u, K-block_k); k+=1)
      {
        rA[0][0] = lA[offA + 0];
        rA[0][1] = lA[offA + 8];
        rA[0][2] = lA[offA + 16];
        rA[0][3] = lA[offA + 24];
        rB[0][0] = lB[offB + 0];
        rB[0][1] = lB[offB + 8];
        rB[0][2] = lB[offB + 16];
        rB[0][3] = lB[offB + 24];
        offA += 33;
        offB += 33;
        rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
        rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
        rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
        rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
        rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
        rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
        rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
        rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
        rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
        rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
        rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
        rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
        rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
        rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
        rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      }
      A += 8*lda;
      B += 8;
    }
    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;

    int OffSetCM = gidx*32+idx;
    int OffSetCN = gidy*32+idy;
    if(OffSetCM>=M || OffSetCN>=N)
      return;



    for (int i = 0; i<4; i++)
    {
      C[0] = alpha*rC[i][0] + beta*C[0];
       
      if (OffSetCN+8<N)
        C[8*ldc] = alpha*rC[i][1] + beta*C[8*ldc];

      if (OffSetCN+16<N)
        C[16*ldc] = alpha*rC[i][2] + beta*C[16*ldc];
    
      if (OffSetCN+24<N)
        C[24*ldc] = alpha*rC[i][3] + beta*C[24*ldc];

      C+=8;
      OffSetCM += 8;
      if(OffSetCM>=M)
        return;
    }
  }

  else
  {
    for( int block_k=0 ; block_k< K ; block_k+=8)
    {
      barrier(CLK_LOCAL_MEM_FENCE);
      plA[0] = A[0+0*lda];
      plA[8] = A[8+0*lda];
      plA[16] = A[16+0*lda];
      plA[24] = A[24+0*lda];
      plB[0] = B[0+0*ldb];
      plB[8] = B[0+8*ldb];
      plB[16] = B[0+16*ldb];
      plB[24] = B[0+24*ldb];
      barrier(CLK_LOCAL_MEM_FENCE);
      
      int offA = idx;
      int offB = idy;
      for( int k = 0 ; k < min(8u, K-block_k); k+=1)
      {
        rA[0][0] = lA[offA + 0];
        rA[0][1] = lA[offA + 8];
        rA[0][2] = lA[offA + 16];
        rA[0][3] = lA[offA + 24];
        rB[0][0] = lB[offB + 0];
        rB[0][1] = lB[offB + 8];
        rB[0][2] = lB[offB + 16];
        rB[0][3] = lB[offB + 24];
        offA += 33;
        offB += 33;
        rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
        rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
        rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
        rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
        rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
        rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
        rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
        rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
        rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
        rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
        rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
        rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
        rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
        rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
        rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      }
      A += 8*lda;
      B += 8;
    }
    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;



    for (int i = 0; i<4; i++)
    {
      C[0] = alpha*rC[i][0] + beta*C[0];
      C[8*ldc] = alpha*rC[i][1] + beta*C[8*ldc];
      C[16*ldc] = alpha*rC[i][2] + beta*C[16*ldc];
      C[24*ldc] = alpha*rC[i][3] + beta*C[24*ldc];
      C+=8;
    }
  }
}
";


static const char * dgemm_NN_1_1_1_8x8_4x4__ALPHA = "
__attribute__( (reqd_work_group_size(8, 8, 1)) )
  __kernel void dgemm_NN_1_1_1_8x8_4x4__ALPHA(__global double const * restrict A,
  __global double const * restrict B,
  __global double * C,
  uint const M,
  uint const N,
  uint const K,
  double const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
  double rC[4][4]  = {(double)0};
  double rA[1][4];
  double rB[1][4];


  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[264];
  __local double lB[264];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*32+ idxT + idyT*lda;
  B +=  gidy*32*ldb+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*33+idxT;
  __local double* plB = lB + idxT*33+ idyT;

  if(gidx==get_num_groups(0)-1 || gidy==get_num_groups(1)-1 )
  {
    int CurrentOffSetA =   gidx*32 + idxT;
    int CurrentOffSetB =  idyT;

    for( int block_k=0 ; block_k< K ; block_k+=8)
    {
      barrier(CLK_LOCAL_MEM_FENCE);
   
      plA[0] = CurrentOffSetA>=M?0.0:A[0];
      plA[8] = CurrentOffSetA+8>=M?0.0:A[8];
      plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
      plA[24] = CurrentOffSetA+24>=M?0.0:A[24];
     
      plB[0] = CurrentOffSetB>=N?0.0:B[0];
      plB[8] = CurrentOffSetB+8>=N?0.0:B[0+8*ldb];
      plB[16] = CurrentOffSetB+16>=N?0.0: B[0+16*ldb];
      plB[24] = CurrentOffSetB+24>=N?0.0:B[0+24*ldb];
     
      barrier(CLK_LOCAL_MEM_FENCE);
     
      int offA = idx;
      int offB = idy;

      for( int k = 0 ; k < min(8u, K-block_k); k+=1)
      {
        rA[0][0] = lA[offA + 0];
        rA[0][1] = lA[offA + 8];
        rA[0][2] = lA[offA + 16];
        rA[0][3] = lA[offA + 24];
        rB[0][0] = lB[offB + 0];
        rB[0][1] = lB[offB + 8];
        rB[0][2] = lB[offB + 16];
        rB[0][3] = lB[offB + 24];
        offA += 33;
        offB += 33;
        rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
        rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
        rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
        rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
        rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
        rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
        rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
        rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
        rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
        rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
        rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
        rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
        rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
        rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
        rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      }
      A += 8*lda;
      B += 8;
    }
    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;

    int OffSetCM = gidx*32+idx;
    int OffSetCN = gidy*32+idy;
    if(OffSetCM>=M || OffSetCN>=N)
      return;



    for (int i = 0; i<4; i++)
    {
      C[0] = alpha*rC[i][0];
       
      if (OffSetCN+8<N)
        C[8*ldc] = alpha*rC[i][1];

      if (OffSetCN+16<N)
        C[16*ldc] = alpha*rC[i][2];
    
      if (OffSetCN+24<N)
        C[24*ldc] = alpha*rC[i][3];

      C+=8;
      OffSetCM += 8;
      if(OffSetCM>=M)
        return;
    }
  }

  else
  {
    for( int block_k=0 ; block_k< K ; block_k+=8)
    {
      barrier(CLK_LOCAL_MEM_FENCE);
      plA[0] = A[0+0*lda];
      plA[8] = A[8+0*lda];
      plA[16] = A[16+0*lda];
      plA[24] = A[24+0*lda];
      plB[0] = B[0+0*ldb];
      plB[8] = B[0+8*ldb];
      plB[16] = B[0+16*ldb];
      plB[24] = B[0+24*ldb];
      barrier(CLK_LOCAL_MEM_FENCE);
      
      int offA = idx;
      int offB = idy;
      for( int k = 0 ; k < min(8u, K-block_k); k+=1)
      {
        rA[0][0] = lA[offA + 0];
        rA[0][1] = lA[offA + 8];
        rA[0][2] = lA[offA + 16];
        rA[0][3] = lA[offA + 24];
        rB[0][0] = lB[offB + 0];
        rB[0][1] = lB[offB + 8];
        rB[0][2] = lB[offB + 16];
        rB[0][3] = lB[offB + 24];
        offA += 33;
        offB += 33;
        rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
        rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
        rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
        rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
        rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
        rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
        rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
        rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
        rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
        rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
        rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
        rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
        rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
        rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
        rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
        rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      }
      A += 8*lda;
      B += 8;
    }
    C+= gidx*32;
    C+= idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;



    for (int i = 0; i<4; i++)
    {
      C[0] = alpha*rC[i][0];
      C[8*ldc] = alpha*rC[i][1];
      C[16*ldc] = alpha*rC[i][2];
      C[24*ldc] = alpha*rC[i][3];
      C+=8;
    }
  }
}
";


static const char * dgemm_NN_32_32_1_8x8_4x4__ALPHABETA = "
__attribute__( (reqd_work_group_size(8, 8, 1)) )
  __kernel void dgemm_NN_32_32_1_8x8_4x4__ALPHABETA(__global double const * restrict A,
  __global double const * restrict B,
  __global double * C,
  uint const M,
  uint const N,
  uint const K,
  double const alpha,
  double const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
  double rC[4][4]  = {(double)0};
  double rA[1][4];
  double rB[1][4];

  double PreFetchA [4];
  double PreFetchB [4];

  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[264];
  __local double lB[264];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*32+ idxT + idyT*lda;
  B +=  gidy*32*ldb+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*33+1*idxT;
  __local double* plB = lB + idxT*33+ idyT;


  plA[0]  = A[0];
  plA[8]  = A[8];
  plA[16] = A[16];
  plA[24] = A[24];
  plB[0]  = B[0];
  plB[8]  = B[0+8*ldb];
  plB[16] = B[0+16*ldb];
  plB[24] = B[0+24*ldb];
  barrier(CLK_LOCAL_MEM_FENCE);

  for( int block_k=0 ; block_k< K ; block_k+=8)
  {
    
    //barrier(CLK_LOCAL_MEM_FENCE);
    A += 8*lda;
    B += 8;

	PreFetchA[0] = A[0];
	PreFetchA[1] = A[8];
	PreFetchA[2] = A[16];
	PreFetchA[3] = A[24];
	PreFetchB[0] = B[0];
	PreFetchB[1] = B[8*ldb];
	PreFetchB[2] = B[16*ldb];
	PreFetchB[3] = B[24*ldb];

    int offA = idx;
    int offB = idy;

    for( int k = 0 ; k < min(8u, K-block_k); k+=1)
    {
      rA[0][0] = lA[offA + 0];
      rA[0][1] = lA[offA + 8];
      rA[0][2] = lA[offA + 16];
      rA[0][3] = lA[offA + 24];
      rB[0][0] = lB[offB + 0];
      rB[0][1] = lB[offB + 8];
      rB[0][2] = lB[offB + 16];
      rB[0][3] = lB[offB + 24];
      offA += 33;
      offB += 33;
      rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
      rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
      rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
      rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
      rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
      rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
      rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
      rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
      rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
      rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
      rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
      rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
      rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
      rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
      rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
      rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
    }

	barrier(CLK_LOCAL_MEM_FENCE);
	plA[0]  = PreFetchA[0]; 
	plA[8]  = PreFetchA[1];
	plA[16] = PreFetchA[2];
	plA[24] = PreFetchA[3];
	plB[0]  = PreFetchB[0];
	plB[8]  = PreFetchB[1];
	plB[16] = PreFetchB[2];
	plB[24] = PreFetchB[3];
	barrier(CLK_LOCAL_MEM_FENCE);
    
  }

  C+= gidx*32;
  C+= idx*1;
  C+= gidy*32*ldc;
  C+= idy*1*ldc;
  C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[0][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[0][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[0][3] + beta*C[24*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[1][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[1][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[1][3] + beta*C[24*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[2][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[2][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[2][3] + beta*C[24*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[3][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[3][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[3][3] + beta*C[24*ldc];
  C+=8;
}
";

static const char * dgemm_NN_32_32_1_8x8_4x4__ALPHA = "
__attribute__( (reqd_work_group_size(8, 8, 1)) )
  __kernel void dgemm_NN_32_32_1_8x8_4x4__ALPHA(__global double const * restrict A,
  __global double const * restrict B,
  __global double * C,
  uint const M,
  uint const N,
  uint const K,
  double const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
  double rC[4][4]  = {(double)0};
  double rA[1][4];
  double rB[1][4];

  double PreFetchA [4];
  double PreFetchB [4];

  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[264];
  __local double lB[264];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*32+ idxT + idyT*lda;
  B +=  gidy*32*ldb+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*33+1*idxT;
  __local double* plB = lB + idxT*33+ idyT;


  plA[0]  = A[0];
  plA[8]  = A[8];
  plA[16] = A[16];
  plA[24] = A[24];
  plB[0]  = B[0];
  plB[8]  = B[0+8*ldb];
  plB[16] = B[0+16*ldb];
  plB[24] = B[0+24*ldb];
  barrier(CLK_LOCAL_MEM_FENCE);

  for( int block_k=0 ; block_k< K ; block_k+=8)
  {
    
    //barrier(CLK_LOCAL_MEM_FENCE);
    A += 8*lda;
    B += 8;

	PreFetchA[0] = A[0];
	PreFetchA[1] = A[8];
	PreFetchA[2] = A[16];
	PreFetchA[3] = A[24];
	PreFetchB[0] = B[0];
	PreFetchB[1] = B[8*ldb];
	PreFetchB[2] = B[16*ldb];
	PreFetchB[3] = B[24*ldb];

    int offA = idx;
    int offB = idy;

    for( int k = 0 ; k < min(8u, K-block_k); k+=1)
    {
      rA[0][0] = lA[offA + 0];
      rA[0][1] = lA[offA + 8];
      rA[0][2] = lA[offA + 16];
      rA[0][3] = lA[offA + 24];
      rB[0][0] = lB[offB + 0];
      rB[0][1] = lB[offB + 8];
      rB[0][2] = lB[offB + 16];
      rB[0][3] = lB[offB + 24];
      offA += 33;
      offB += 33;
      rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
      rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
      rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
      rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
      rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
      rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
      rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
      rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
      rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
      rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
      rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
      rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
      rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
      rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
      rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
      rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
    }

	barrier(CLK_LOCAL_MEM_FENCE);
	plA[0]  = PreFetchA[0]; 
	plA[8]  = PreFetchA[1];
	plA[16] = PreFetchA[2];
	plA[24] = PreFetchA[3];
	plB[0]  = PreFetchB[0];
	plB[8]  = PreFetchB[1];
	plB[16] = PreFetchB[2];
	plB[24] = PreFetchB[3];
	barrier(CLK_LOCAL_MEM_FENCE);
    
  }

  C+= gidx*32;
  C+= idx;
  C+= gidy*32*ldc;
  C+= idy*ldc;
  C[0*ldc] = alpha*rC[0][0] ;
  C[8*ldc] = alpha*rC[0][1] ;
  C[16*ldc] = alpha*rC[0][2];
  C[24*ldc] = alpha*rC[0][3];
  C+=8;                     
  C[0*ldc] = alpha*rC[1][0] ;
  C[8*ldc] = alpha*rC[1][1] ;
  C[16*ldc] = alpha*rC[1][2];
  C[24*ldc] = alpha*rC[1][3];
  C+=8;                     
  C[0*ldc] = alpha*rC[2][0] ;
  C[8*ldc] = alpha*rC[2][1] ;
  C[16*ldc] = alpha*rC[2][2];
  C[24*ldc] = alpha*rC[2][3];
  C+=8;                     
  C[0*ldc] = alpha*rC[3][0] ;
  C[8*ldc] = alpha*rC[3][1] ;
  C[16*ldc] = alpha*rC[3][2];
  C[24*ldc] = alpha*rC[3][3];
  
}
";


static const char * dgemm_NN_40_40_8_8x8_5x5__ALPHABETA = "
__attribute__((reqd_work_group_size(8,8,1)))
  __kernel void dgemm_NN_40_40_8_8x8_5x5__ALPHABETA( __global double const * restrict A, 
  __global double const * restrict B,
  __global double * C,  
  uint const M, 
  uint const N, 
  uint const K,
  double const alpha,  
  double const beta,   
  uint lda,
  uint ldb, 
  uint ldc, 
  uint const offsetA,
  uint const offsetB,
  uint const offsetC)
{
  double rC[5][5]  = {(double)0};
  double rA[1][5];
  double rB[1][5];

  double PreFetchA[5];
  double PreFetchB[5];

  //double PreFetchA_5;
  //double PreFetchB_5;

  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[320];
  __local double lB[320];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*40+ idxT + idyT*lda;
  B +=  gidy*40*ldb+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*40+idxT;
  __local double* plB = lB + idxT*40+idyT;


  plA[0]  = A[0];
  plA[8]  = A[8];
  plA[16] = A[16];
  plA[24] = A[24];
  plA[32] = A[32]; 
  plB[0]  = B[0];
  plB[8]  = B[8*ldb];
  plB[16] = B[16*ldb];
  plB[24] = B[24*ldb];
  plB[32] = B[32*ldb];
  barrier(CLK_LOCAL_MEM_FENCE);

  
  //for( int block_k=0 ; block_k< K ; block_k+=8)
  uint block_k = K >> 3;
  do
  {
 /*   barrier(CLK_LOCAL_MEM_FENCE);


    plA[0] = A[0];
    plA[8] = A[8];
    plA[16] = A[16];
    plA[24] = A[24];
    plA[32] = A[32]; 
    plB[0] = B[0];
    plB[8] = B[8*ldb];
    plB[16] = B[16*ldb];
    plB[24] = B[24*ldb];
    plB[32] = B[32*ldb];
    barrier(CLK_LOCAL_MEM_FENCE);
*/

    A += 8*lda;
    B += 8;
	 
    PreFetchA[0] = A[0];
	PreFetchA[1] = A[8];
	PreFetchA[2] = A[16];
	PreFetchA[3] = A[24];
	PreFetchA[4] = A[32]; 
	PreFetchB[0] = B[0];
	PreFetchB[1] = B[8*ldb];
	PreFetchB[2] = B[16*ldb];
	PreFetchB[3] = B[24*ldb];
	PreFetchB[4] = B[32*ldb];
    
    



    int offA = idx;
    int offB = idy;
   // int off256 = 256;


#pragma unroll 1
    for( int k = 0 ; k < 8; k+=1)
    {
      rA[0][0] = lA[offA + 0];
      rA[0][1] = lA[offA + 8];
      rA[0][2] = lA[offA + 16];
      rA[0][3] = lA[offA + 24];
      rA[0][4] = lA[offA + 32];

      rB[0][0] = lB[offB + 0];
      rB[0][1] = lB[offB + 8];
      rB[0][2] = lB[offB + 16];
      rB[0][3] = lB[offB + 24];
      rB[0][4] = lB[offB + 32];


      offA += 40;
      offB += 40;
     // off256 -= 24;
      rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
      rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
      rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
      rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
      rC[4][0]=mad(rA[0][4],rB[0][0],rC[4][0]);

      rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
      rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
      rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
      rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
      rC[4][1]=mad(rA[0][4],rB[0][1],rC[4][1]);

      rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
      rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
      rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
      rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
      rC[4][2]=mad(rA[0][4],rB[0][2],rC[4][2]);

      rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
      rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
      rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
      rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      rC[4][3]=mad(rA[0][4],rB[0][3],rC[4][3]);

      rC[0][4]=mad(rA[0][0],rB[0][4],rC[0][4]);
      rC[1][4]=mad(rA[0][1],rB[0][4],rC[1][4]);
      rC[2][4]=mad(rA[0][2],rB[0][4],rC[2][4]);
      rC[3][4]=mad(rA[0][3],rB[0][4],rC[3][4]);
      rC[4][4]=mad(rA[0][4],rB[0][4],rC[4][4]);

    }

    barrier(CLK_LOCAL_MEM_FENCE);
    plA[0]  = PreFetchA[0];
    plA[8]  = PreFetchA[1];
    plA[16] = PreFetchA[2];
    plA[24] = PreFetchA[3];
    plA[32] = PreFetchA[4];
    plB[0]  = PreFetchB[0];
    plB[8]  = PreFetchB[1];
    plB[16] = PreFetchB[2];
    plB[24] = PreFetchB[3];
    plB[32] = PreFetchB[4];

    barrier(CLK_LOCAL_MEM_FENCE);
    //  A += 8*lda;
    //  B += 8;
  }
  while (--block_k > 0);

  C+= gidx*40;
  C+= idx;
  C+= gidy*40*ldc;
  C+= idy*ldc;
 
  C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[0][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[0][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[0][3] + beta*C[24*ldc];
  C[32*ldc] = alpha*rC[0][4] + beta*C[32*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[1][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[1][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[1][3] + beta*C[24*ldc];
  C[32*ldc] = alpha*rC[1][4] + beta*C[32*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[2][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[2][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[2][3] + beta*C[24*ldc];
  C[32*ldc] = alpha*rC[2][4] + beta*C[32*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[3][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[3][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[3][3] + beta*C[24*ldc];
  C[32*ldc] = alpha*rC[3][4] + beta*C[32*ldc];
  C+=8;
  C[0*ldc] = alpha*rC[4][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[4][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[4][2] + beta*C[16*ldc];
  C[24*ldc] = alpha*rC[4][3] + beta*C[24*ldc];
  C[32*ldc] = alpha*rC[4][4] + beta*C[32*ldc];

}
";


static const char * dgemm_NN_40_40_8_8x8_5x5__ALPHA = "
__attribute__((reqd_work_group_size(8,8,1)))
  __kernel void dgemm_NN_40_40_8_8x8_5x5__ALPHA( __global double const * restrict A, 
  __global double const * restrict B,
  __global double * C,  
  uint const M, 
  uint const N, 
  uint const K,
  double const alpha,  
  uint lda,
  uint ldb, 
  uint ldc, 
  uint const offsetA,
  uint const offsetB,
  uint const offsetC)
{
  double rC[5][5]  = {(double)0};
  double rA[1][5];
  double rB[1][5];

  double PreFetchA[5];
  double PreFetchB[5];

  //double PreFetchA_5;
  //double PreFetchB_5;

  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[320];
  __local double lB[320];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*40+ idxT + idyT*lda;
  B +=  gidy*40*ldb+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*40+idxT;
  __local double* plB = lB + idxT*40+idyT;


  plA[0]  = A[0];
  plA[8]  = A[8];
  plA[16] = A[16];
  plA[24] = A[24];
  plA[32] = A[32]; 
  plB[0]  = B[0];
  plB[8]  = B[8*ldb];
  plB[16] = B[16*ldb];
  plB[24] = B[24*ldb];
  plB[32] = B[32*ldb];
  barrier(CLK_LOCAL_MEM_FENCE);

  
  //for( int block_k=0 ; block_k< K ; block_k+=8)
  uint block_k = K >> 3;
  do
  {
 /*   barrier(CLK_LOCAL_MEM_FENCE);


    plA[0] = A[0];
    plA[8] = A[8];
    plA[16] = A[16];
    plA[24] = A[24];
    plA[32] = A[32]; 
    plB[0] = B[0];
    plB[8] = B[8*ldb];
    plB[16] = B[16*ldb];
    plB[24] = B[24*ldb];
    plB[32] = B[32*ldb];
    barrier(CLK_LOCAL_MEM_FENCE);
*/

    A += 8*lda;
    B += 8;
	 
    PreFetchA[0] = A[0];
	PreFetchA[1] = A[8];
	PreFetchA[2] = A[16];
	PreFetchA[3] = A[24];
	PreFetchA[4] = A[32]; 
	PreFetchB[0] = B[0];
	PreFetchB[1] = B[8*ldb];
	PreFetchB[2] = B[16*ldb];
	PreFetchB[3] = B[24*ldb];
	PreFetchB[4] = B[32*ldb];
    
    



    int offA = idx;
    int offB = idy;
   // int off256 = 256;


#pragma unroll 1
    for( int k = 0 ; k < 8; k+=1)
    {
      rA[0][0] = lA[offA + 0];
      rA[0][1] = lA[offA + 8];
      rA[0][2] = lA[offA + 16];
      rA[0][3] = lA[offA + 24];
      rA[0][4] = lA[offA + 32];

      rB[0][0] = lB[offB + 0];
      rB[0][1] = lB[offB + 8];
      rB[0][2] = lB[offB + 16];
      rB[0][3] = lB[offB + 24];
      rB[0][4] = lB[offB + 32];


      offA += 40;
      offB += 40;
     // off256 -= 24;
      rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
      rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
      rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
      rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]);
      rC[4][0]=mad(rA[0][4],rB[0][0],rC[4][0]);

      rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
      rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
      rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
      rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]);
      rC[4][1]=mad(rA[0][4],rB[0][1],rC[4][1]);

      rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
      rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
      rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
      rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]);
      rC[4][2]=mad(rA[0][4],rB[0][2],rC[4][2]);

      rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]);
      rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]);
      rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]);
      rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]);
      rC[4][3]=mad(rA[0][4],rB[0][3],rC[4][3]);

      rC[0][4]=mad(rA[0][0],rB[0][4],rC[0][4]);
      rC[1][4]=mad(rA[0][1],rB[0][4],rC[1][4]);
      rC[2][4]=mad(rA[0][2],rB[0][4],rC[2][4]);
      rC[3][4]=mad(rA[0][3],rB[0][4],rC[3][4]);
      rC[4][4]=mad(rA[0][4],rB[0][4],rC[4][4]);

    }

    barrier(CLK_LOCAL_MEM_FENCE);
    plA[0]  = PreFetchA[0];
    plA[8]  = PreFetchA[1];
    plA[16] = PreFetchA[2];
    plA[24] = PreFetchA[3];
    plA[32] = PreFetchA[4];
    plB[0]  = PreFetchB[0];
    plB[8]  = PreFetchB[1];
    plB[16] = PreFetchB[2];
    plB[24] = PreFetchB[3];
    plB[32] = PreFetchB[4];

    barrier(CLK_LOCAL_MEM_FENCE);
    //  A += 8*lda;
    //  B += 8;
  }
  while (--block_k > 0);

  C+= gidx*40;
  C+= idx;
  C+= gidy*40*ldc;
  C+= idy*ldc;
 
  C[0*ldc] = alpha*rC[0][0] ;
  C[8*ldc] = alpha*rC[0][1] ;
  C[16*ldc] = alpha*rC[0][2];
  C[24*ldc] = alpha*rC[0][3];
  C[32*ldc] = alpha*rC[0][4];
  C+=8;                     
  C[0*ldc] = alpha*rC[1][0] ;
  C[8*ldc] = alpha*rC[1][1] ;
  C[16*ldc] = alpha*rC[1][2];
  C[24*ldc] = alpha*rC[1][3];
  C[32*ldc] = alpha*rC[1][4];
  C+=8;                     
  C[0*ldc] = alpha*rC[2][0] ;
  C[8*ldc] = alpha*rC[2][1] ;
  C[16*ldc] = alpha*rC[2][2];
  C[24*ldc] = alpha*rC[2][3];
  C[32*ldc] = alpha*rC[2][4];
  C+=8;                     
  C[0*ldc] = alpha*rC[3][0] ;
  C[8*ldc] = alpha*rC[3][1] ;
  C[16*ldc] = alpha*rC[3][2];
  C[24*ldc] = alpha*rC[3][3];
  C[32*ldc] = alpha*rC[3][4];
  C+=8;                     
  C[0*ldc] = alpha*rC[4][0] ;
  C[8*ldc] = alpha*rC[4][1] ;
  C[16*ldc] = alpha*rC[4][2];
  C[24*ldc] = alpha*rC[4][3];
  C[32*ldc] = alpha*rC[4][4];

}
";