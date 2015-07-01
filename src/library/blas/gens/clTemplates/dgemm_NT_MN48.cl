#ifndef PURE_CL
static const char *DGEMM_NT_MN48_KERNEL = "

typedef union GPtr {
  __global float *f;
  __global double *d;
  __global float2 *f2v;
  __global double2 *d2v;
} GPtr;

__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm(__global double * C,
                    __global double2 const * restrict B,
                    __global double2 const * restrict A,
                    uint const N,
                    uint const M,
                    uint const K,
                    double const alpha,
                    double const beta,
                    uint ldc,
                    uint ldb,
                    uint lda,
                    uint offsetC,
                    uint offsetB,
                    uint offsetA)
{
    GPtr uA, uB;
    uA.d2v = (__global double2 *)A;
    uB.d2v = (__global double2 *)B;

    uA.d += offsetA;
    uB.d += offsetB;
    C    += offsetC;
    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];

    __local double lA[392];
    __local double lB[392];

    uint gidx = 24*get_group_id(0);
    uint gidy = 24*get_group_id(1);
    uint idx  = get_local_id(0);
    uint idy  = get_local_id(1);
    uint GX   = (gidx+idx) << 1;
    uint GY   = (gidy+idy) << 1;
    uint GYX  = (gidy+idx) << 1;

    uA.d += GX  + idy*lda;
    uB.d += GYX + idy*ldb;

    __local double* plA = lA + idy*49 + 2*idx;
    __local double* plB = lB + idy*49 + 2*idx;
    uint ik = 0;
    for(unsigned int block_k = 0; block_k < K; block_k+=8)
    {
        barrier(CLK_LOCAL_MEM_FENCE);
        vstore2(uA.d2v[0 ], 0, plA+0 );
        vstore2(uA.d2v[8 ], 0, plA+16);
        vstore2(uA.d2v[16], 0, plA+32);
        vstore2(uB.d2v[0 ], 0, plB+0 );
        vstore2(uB.d2v[8 ], 0, plB+16);
        vstore2(uB.d2v[16], 0, plB+32);
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx << 1;
        uint offB = idy << 1;
        for(unsigned int k = 0 ; k < 8; k++)
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
            offA += 49;
            offB += 49;
            rC[0][0] = fma(rA[0],rB[0],rC[0][0]);
            rC[0][1] = fma(rA[1],rB[0],rC[0][1]);
            rC[0][2] = fma(rA[2],rB[0],rC[0][2]);
            rC[0][3] = fma(rA[3],rB[0],rC[0][3]);
            rC[0][4] = fma(rA[4],rB[0],rC[0][4]);
            rC[0][5] = fma(rA[5],rB[0],rC[0][5]);
            rC[1][0] = fma(rA[0],rB[1],rC[1][0]);
            rC[1][1] = fma(rA[1],rB[1],rC[1][1]);
            rC[1][2] = fma(rA[2],rB[1],rC[1][2]);
            rC[1][3] = fma(rA[3],rB[1],rC[1][3]);
            rC[1][4] = fma(rA[4],rB[1],rC[1][4]);
            rC[1][5] = fma(rA[5],rB[1],rC[1][5]);
            rC[2][0] = fma(rA[0],rB[2],rC[2][0]);
            rC[2][1] = fma(rA[1],rB[2],rC[2][1]);
            rC[2][2] = fma(rA[2],rB[2],rC[2][2]);
            rC[2][3] = fma(rA[3],rB[2],rC[2][3]);
            rC[2][4] = fma(rA[4],rB[2],rC[2][4]);
            rC[2][5] = fma(rA[5],rB[2],rC[2][5]);
            rC[3][0] = fma(rA[0],rB[3],rC[3][0]);
            rC[3][1] = fma(rA[1],rB[3],rC[3][1]);
            rC[3][2] = fma(rA[2],rB[3],rC[3][2]);
            rC[3][3] = fma(rA[3],rB[3],rC[3][3]);
            rC[3][4] = fma(rA[4],rB[3],rC[3][4]);
            rC[3][5] = fma(rA[5],rB[3],rC[3][5]);
            rC[4][0] = fma(rA[0],rB[4],rC[4][0]);
            rC[4][1] = fma(rA[1],rB[4],rC[4][1]);
            rC[4][2] = fma(rA[2],rB[4],rC[4][2]);
            rC[4][3] = fma(rA[3],rB[4],rC[4][3]);
            rC[4][4] = fma(rA[4],rB[4],rC[4][4]);
            rC[4][5] = fma(rA[5],rB[4],rC[4][5]);
            rC[5][0] = fma(rA[0],rB[5],rC[5][0]);
            rC[5][1] = fma(rA[1],rB[5],rC[5][1]);
            rC[5][2] = fma(rA[2],rB[5],rC[5][2]);
            rC[5][3] = fma(rA[3],rB[5],rC[5][3]);
            rC[5][4] = fma(rA[4],rB[5],rC[5][4]);
            rC[5][5] = fma(rA[5],rB[5],rC[5][5]);
        }
        uA.d += lda << 3;
        uB.d += ldb << 3;
    }
    uint index;
    GPtr uC;
    double2 CC, RCv2;

    for (int i=0; i < 3; i++)
    {
        int ic = i << 1;
        index = (GX + i * 16) + (GY +  0) * ldc;
        uC.d = (__global double *)&C[index];
        vstore2(uC.d2v[0], (size_t) 0, (__private double*) &CC);
        vstore2(((double2 *)&rC[0][ic])[0], (size_t) 0, (__private double*) &RCv2);
        CC = fma((double2)(beta), CC, (double2)(alpha) * RCv2);
        uC.d2v[0] = vload2((size_t) 0, (__private double*) &CC);

        index += ldc;
        uC.d = (__global double *)&C[index];
        vstore2(uC.d2v[0], (size_t) 0, (__private double*) &CC);
        vstore2(((double2 *)&rC[1][ic])[0], (size_t) 0, (__private double*) &RCv2);
        CC = fma((double2)(beta), CC, (double2)(alpha) * RCv2);
        uC.d2v[0] = vload2((size_t) 0, (__private double*) &CC);

        index += 15 * ldc;
        uC.d = (__global double *)&C[index];
        vstore2(uC.d2v[0], (size_t) 0, (__private double*) &CC);
        vstore2(((double2 *)&rC[2][ic])[0], (size_t) 0, (__private double*) &RCv2);
        CC = fma((double2)(beta), CC, (double2)(alpha) * RCv2);
        uC.d2v[0] = vload2((size_t) 0, (__private double*) &CC);

        index += ldc;
        uC.d = (__global double *)&C[index];
        vstore2(uC.d2v[0], (size_t) 0, (__private double*) &CC);
        vstore2(((double2 *)&rC[3][ic])[0], (size_t) 0, (__private double*) &RCv2);
        CC = fma((double2)(beta), CC, (double2)(alpha) * RCv2);
        uC.d2v[0] = vload2((size_t) 0, (__private double*) &CC);

        index += 15 * ldc;
        uC.d = (__global double *)&C[index];
        vstore2(uC.d2v[0], (size_t) 0, (__private double*) &CC);
        vstore2(((double2 *)&rC[4][ic])[0], (size_t) 0, (__private double*) &RCv2);
        CC = fma((double2)(beta), CC, (double2)(alpha) * RCv2);
        uC.d2v[0] = vload2((size_t) 0, (__private double*) &CC);

        index += ldc;
        uC.d = (__global double *)&C[index];
        vstore2(uC.d2v[0], (size_t) 0, (__private double*) &CC);
        vstore2(((double2 *)&rC[5][ic])[0], (size_t) 0, (__private double*) &RCv2);
        CC = fma((double2)(beta), CC, (double2)(alpha) * RCv2);
        uC.d2v[0] = vload2((size_t) 0, (__private double*) &CC);
    }
}

";
#else

typedef union GPtr {
  __global float *f;
  __global double *d;
  __global float2 *f2v;
  __global double2 *d2v;
} GPtr;

__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm(__global double * C,
                    __global double2 const * restrict B,
                    __global double2 const * restrict A,
                    uint const N,
                    uint const M,
                    uint const K,
                    double const alpha,
                    double const beta,
                    uint ldc,
                    uint ldb,
                    uint lda,
                    uint offsetC,
                    uint offsetB,
                    uint offsetA)
{
    GPtr uA, uB;
    uA.d2v = (__global double2 *)A;
    uB.d2v = (__global double2 *)B;

    uA.d += offsetA;
    uB.d += offsetB;
    C    += offsetC;
    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];

    __local double lA[392];
    __local double lB[392];

    uint gidx = 24*get_group_id(0);
    uint gidy = 24*get_group_id(1);
    uint idx  = get_local_id(0);
    uint idy  = get_local_id(1);
    uint GX   = (gidx+idx) << 1;
    uint GY   = (gidy+idy) << 1;
    uint GYX  = (gidy+idx) << 1;

    uA.d += GX  + idy*lda;
    uB.d += GYX + idy*ldb;

    __local double* plA = lA + idy*49 + 2*idx;
    __local double* plB = lB + idy*49 + 2*idx;
    uint ik = 0;
    for(unsigned int block_k = 0; block_k < K; block_k+=8)
    {
        barrier(CLK_LOCAL_MEM_FENCE);
        vstore2(uA.d2v[0 ], 0, plA+0 );
        vstore2(uA.d2v[8 ], 0, plA+16);
        vstore2(uA.d2v[16], 0, plA+32);
        vstore2(uB.d2v[0 ], 0, plB+0 );
        vstore2(uB.d2v[8 ], 0, plB+16);
        vstore2(uB.d2v[16], 0, plB+32);
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx << 1;
        uint offB = idy << 1;
        for(unsigned int k = 0 ; k < 8; k++)
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
            offA += 49;
            offB += 49;
            rC[0][0] = fma(rA[0],rB[0],rC[0][0]);
            rC[0][1] = fma(rA[1],rB[0],rC[0][1]);
            rC[0][2] = fma(rA[2],rB[0],rC[0][2]);
            rC[0][3] = fma(rA[3],rB[0],rC[0][3]);
            rC[0][4] = fma(rA[4],rB[0],rC[0][4]);
            rC[0][5] = fma(rA[5],rB[0],rC[0][5]);
            rC[1][0] = fma(rA[0],rB[1],rC[1][0]);
            rC[1][1] = fma(rA[1],rB[1],rC[1][1]);
            rC[1][2] = fma(rA[2],rB[1],rC[1][2]);
            rC[1][3] = fma(rA[3],rB[1],rC[1][3]);
            rC[1][4] = fma(rA[4],rB[1],rC[1][4]);
            rC[1][5] = fma(rA[5],rB[1],rC[1][5]);
            rC[2][0] = fma(rA[0],rB[2],rC[2][0]);
            rC[2][1] = fma(rA[1],rB[2],rC[2][1]);
            rC[2][2] = fma(rA[2],rB[2],rC[2][2]);
            rC[2][3] = fma(rA[3],rB[2],rC[2][3]);
            rC[2][4] = fma(rA[4],rB[2],rC[2][4]);
            rC[2][5] = fma(rA[5],rB[2],rC[2][5]);
            rC[3][0] = fma(rA[0],rB[3],rC[3][0]);
            rC[3][1] = fma(rA[1],rB[3],rC[3][1]);
            rC[3][2] = fma(rA[2],rB[3],rC[3][2]);
            rC[3][3] = fma(rA[3],rB[3],rC[3][3]);
            rC[3][4] = fma(rA[4],rB[3],rC[3][4]);
            rC[3][5] = fma(rA[5],rB[3],rC[3][5]);
            rC[4][0] = fma(rA[0],rB[4],rC[4][0]);
            rC[4][1] = fma(rA[1],rB[4],rC[4][1]);
            rC[4][2] = fma(rA[2],rB[4],rC[4][2]);
            rC[4][3] = fma(rA[3],rB[4],rC[4][3]);
            rC[4][4] = fma(rA[4],rB[4],rC[4][4]);
            rC[4][5] = fma(rA[5],rB[4],rC[4][5]);
            rC[5][0] = fma(rA[0],rB[5],rC[5][0]);
            rC[5][1] = fma(rA[1],rB[5],rC[5][1]);
            rC[5][2] = fma(rA[2],rB[5],rC[5][2]);
            rC[5][3] = fma(rA[3],rB[5],rC[5][3]);
            rC[5][4] = fma(rA[4],rB[5],rC[5][4]);
            rC[5][5] = fma(rA[5],rB[5],rC[5][5]);
        }
        uA.d += lda << 3;
        uB.d += ldb << 3;
    }
    uint index;
    GPtr uC;
    double2 CC, RCv2;

    for (int i=0; i < 3; i++)
    {
        int ic = i << 1;
        index = (GX + i * 16) + (GY +  0) * ldc;
        uC.d = (__global double *)&C[index];
        vstore2(uC.d2v[0], (size_t) 0, (__private double*) &CC);
        vstore2(((double2 *)&rC[0][ic])[0], (size_t) 0, (__private double*) &RCv2);
        CC = fma((double2)(beta), CC, (double2)(alpha) * RCv2);
        uC.d2v[0] = vload2((size_t) 0, (__private double*) &CC);

        index += ldc;
        uC.d = (__global double *)&C[index];
        vstore2(uC.d2v[0], (size_t) 0, (__private double*) &CC);
        vstore2(((double2 *)&rC[1][ic])[0], (size_t) 0, (__private double*) &RCv2);
        CC = fma((double2)(beta), CC, (double2)(alpha) * RCv2);
        uC.d2v[0] = vload2((size_t) 0, (__private double*) &CC);

        index += 15 * ldc;
        uC.d = (__global double *)&C[index];
        vstore2(uC.d2v[0], (size_t) 0, (__private double*) &CC);
        vstore2(((double2 *)&rC[2][ic])[0], (size_t) 0, (__private double*) &RCv2);
        CC = fma((double2)(beta), CC, (double2)(alpha) * RCv2);
        uC.d2v[0] = vload2((size_t) 0, (__private double*) &CC);

        index += ldc;
        uC.d = (__global double *)&C[index];
        vstore2(uC.d2v[0], (size_t) 0, (__private double*) &CC);
        vstore2(((double2 *)&rC[3][ic])[0], (size_t) 0, (__private double*) &RCv2);
        CC = fma((double2)(beta), CC, (double2)(alpha) * RCv2);
        uC.d2v[0] = vload2((size_t) 0, (__private double*) &CC);

        index += 15 * ldc;
        uC.d = (__global double *)&C[index];
        vstore2(uC.d2v[0], (size_t) 0, (__private double*) &CC);
        vstore2(((double2 *)&rC[4][ic])[0], (size_t) 0, (__private double*) &RCv2);
        CC = fma((double2)(beta), CC, (double2)(alpha) * RCv2);
        uC.d2v[0] = vload2((size_t) 0, (__private double*) &CC);

        index += ldc;
        uC.d = (__global double *)&C[index];
        vstore2(uC.d2v[0], (size_t) 0, (__private double*) &CC);
        vstore2(((double2 *)&rC[5][ic])[0], (size_t) 0, (__private double*) &RCv2);
        CC = fma((double2)(beta), CC, (double2)(alpha) * RCv2);
        uC.d2v[0] = vload2((size_t) 0, (__private double*) &CC);
    }
}

#endif
