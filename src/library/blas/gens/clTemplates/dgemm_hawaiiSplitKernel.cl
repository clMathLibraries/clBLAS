static const char * dgemm_NT_8_SPLIT__ALPHABETA = "
//static const char * dgemm_NT_48_48_8_8x8_6x6__ALPHABETA_SPLIT = "
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
            barrier(CLK_LOCAL_MEM_FENCE);


__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_48_48_8_8x8_6x6__ALPHABETA_SPLIT_MAIN(__global double2 const * restrict A,
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



__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_1_48_8_8x8_6x6__ALPHABETA_SPLIT_ROW(__global double2 const * restrict A,
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

    int gidx = M/48;//get_group_id(0);
    int gidy = get_group_id(1);
    int idx  = get_local_id(0);
    int idy  = get_local_id(1);

	int CurrentOffSetA = 2*(gidx*24 + idx);

    uA.d += 2*(gidx*24 + idx) + idy*lda;
    uB.d += 2*(gidy*24 + idx) + idy*ldb;

	

    int block_k = K >> 3;
    do {
        __local double* plA = (lA + idy*48 + 2*idx);
       __local double2* plB = (__local double2*)(lB + idy*48 + 2*idx);
//        barrier(CLK_LOCAL_MEM_FENCE);
       
	    plB[0 ] = uB.d2v[0 ];
        plB[8 ] = uB.d2v[8 ];
        plB[16] = uB.d2v[16];
	   
//	    plB[0 ] = uB.d[0 ];
//		plB[1 ] = uB.d[1 ];
//      plB[16] = uB.d[16 ];
//      plB[17] = uB.d[17];
//      plB[32] = uB.d[32];
//		plB[33] = uB.d[33];


		plA[0]  =  CurrentOffSetA>=M?0.0:uA.d[0];
		plA[1]  =  CurrentOffSetA+1>=M?0.0:uA.d[1];
        plA[16] =  CurrentOffSetA+16>=M?0.0:uA.d[16];
        plA[17] =  CurrentOffSetA+17>=M?0.0:uA.d[17];
		plA[32] =  CurrentOffSetA+32>=M?0.0:uA.d[32];
        plA[33] =  CurrentOffSetA+33>=M?0.0:uA.d[33];

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
	

  if(offset_x>=M )
    return;

  C+=offset_x+offset_y*ldc;


  for (int i = 0; i<3; i++)
  {
    C[0]      = mad( beta, C[0]     , alpha * rC[0][2*i] );
    C[ldc]    = mad( beta, C[ldc]   , alpha * rC[1][2*i] );
    C[16*ldc] = mad( beta, C[16*ldc], alpha * rC[2][2*i] );
    C[17*ldc] = mad( beta, C[17*ldc], alpha * rC[3][2*i] );
    C[32*ldc] = mad( beta, C[32*ldc], alpha * rC[4][2*i] );
    C[33*ldc] = mad( beta, C[33*ldc], alpha * rC[5][2*i] );

	if(offset_x+1>=M )
	  return;
	
	C[1]        = mad( beta, C[1]     , alpha * rC[0][2*i+1] );
    C[1+ldc]    = mad( beta, C[1+ldc]   , alpha * rC[1][2*i+1] );
    C[1+16*ldc] = mad( beta, C[1+16*ldc], alpha * rC[2][2*i+1] );
    C[1+17*ldc] = mad( beta, C[1+17*ldc], alpha * rC[3][2*i+1] );
    C[1+32*ldc] = mad( beta, C[1+32*ldc], alpha * rC[4][2*i+1] );
    C[1+33*ldc] = mad( beta, C[1+33*ldc], alpha * rC[5][2*i+1] );

	C+=16;
	offset_x+=16;
	if(offset_x>=M )
       return;

  }
}

__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_48_1_8_8x8_6x6__ALPHABETA_SPLIT_COLUMN(__global double2 const * restrict A,
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
    int gidy = N/48;//get_group_id(1);
    int idx  = get_local_id(0);
    int idy  = get_local_id(1);

	int CurrentOffSetB = 2*(gidy*24 + idx);

    uA.d += 2*(gidx*24 + idx) + idy*lda;
    uB.d += 2*(gidy*24 + idx) + idy*ldb;

    int block_k = K >> 3;
    do {
        __local double2* plA = (__local double2*)(lA + idy*48 + 2*idx);
        __local double* plB = (lB + idy*48 + 2*idx);
//        barrier(CLK_LOCAL_MEM_FENCE);
        //plB[0 ] = uB.d2v[0 ];
        //plB[8 ] = uB.d2v[8 ];
        //plB[16] = uB.d2v[16];
       plB[0 ] = CurrentOffSetB>=N?0.0:uB.d[0 ];
	   plB[1 ] = CurrentOffSetB+1>=N?0.0:uB.d[1 ];
	   plB[16] = CurrentOffSetB+16>=N?0.0:uB.d[16 ];
	   plB[17] = CurrentOffSetB+17>=N?0.0:uB.d[17];
	   plB[32] = CurrentOffSetB+32>=N?0.0:uB.d[32];
	   plB[33] = CurrentOffSetB+33>=N?0.0:uB.d[33];

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
	

  if( offset_y>=N )
    return;

  C+=offset_x+offset_y*ldc;


  for (int i = 0; i<3; i++)
  {
    C[0]   = mad( beta, C[0], alpha * rC[0][2*i] );
	C[1]   = mad( beta, C[1], alpha * rC[0][2*i+1] );

	if(offset_y+1<N)
	{
      C[ldc]   = mad( beta, C[ldc], alpha * rC[1][2*i] );
	  C[1+ldc] = mad( beta, C[1+ldc], alpha * rC[1][2*i+1] );
	}

	if(offset_y+16<N)
	{
      C[16*ldc]   = mad( beta, C[16*ldc], alpha * rC[2][2*i] );
	  C[1+16*ldc] = mad( beta, C[1+16*ldc], alpha * rC[2][2*i+1] );
    }

	if(offset_y+17<N)
	{
      C[17*ldc]   = mad( beta, C[17*ldc], alpha * rC[3][2*i] );
	  C[1+17*ldc] = mad( beta, C[1+17*ldc], alpha * rC[3][2*i+1] );
    }

	if(offset_y+32<N)
	{
	  C[32*ldc]   = mad( beta, C[32*ldc], alpha * rC[4][2*i] );
	  C[1+32*ldc] = mad( beta, C[1+32*ldc], alpha * rC[4][2*i+1] );
	}

	if(offset_y+33<N)
	{
      C[33*ldc]   = mad( beta, C[33*ldc], alpha * rC[5][2*i] );
	  C[1+33*ldc] = mad( beta, C[1+33*ldc], alpha * rC[5][2*i+1] );
    }

	C+=16;
	
  }
}

__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_1_1_8_8x8_6x6__ALPHABETA_SPLIT_SINGLE(__global double2 const * restrict A,
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

    int gidx = M/48;//get_group_id(0);
    int gidy = N/48;//get_group_id(1);
    int idx  = get_local_id(0);
    int idy  = get_local_id(1);

	int CurrentOffSetA = 2*(gidx*24 + idx);
	int CurrentOffSetB = 2*(gidy*24 + idx);

    uA.d += 2*(gidx*24 + idx) + idy*lda;
    uB.d += 2*(gidy*24 + idx) + idy*ldb;

    int block_k = K >> 3;
    do {
        __local double* plA = (lA + idy*48 + 2*idx);
        __local double* plB = (lB + idy*48 + 2*idx);
//        barrier(CLK_LOCAL_MEM_FENCE);
        //plB[0 ] = uB.d2v[0 ];
        //plB[8 ] = uB.d2v[8 ];
        //plB[16] = uB.d2v[16];
        //plA[0 ] = uA.d2v[0 ];
        //plA[8 ] = uA.d2v[8 ];
        //plA[16] = uA.d2v[16];

	   plB[0 ] = CurrentOffSetB>=N?0.0:uB.d[0 ];
	   plB[1 ] = CurrentOffSetB+1>=N?0.0:uB.d[1 ];
	   plB[16] = CurrentOffSetB+16>=N?0.0:uB.d[16 ];
	   plB[17] = CurrentOffSetB+17>=N?0.0:uB.d[17];
	   plB[32] = CurrentOffSetB+32>=N?0.0:uB.d[32];
	   plB[33] = CurrentOffSetB+33>=N?0.0:uB.d[33];

	    plA[0]  =  CurrentOffSetA>=M?0.0:uA.d[0];
		plA[1]  =  CurrentOffSetA+1>=M?0.0:uA.d[1];
        plA[16] =  CurrentOffSetA+16>=M?0.0:uA.d[16];
        plA[17] =  CurrentOffSetA+17>=M?0.0:uA.d[17];
		plA[32] =  CurrentOffSetA+32>=M?0.0:uA.d[32];
        plA[33] =  CurrentOffSetA+33>=M?0.0:uA.d[33];




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
	

  if(offset_x>=M || offset_y>=N )
    return;

  C+=offset_x+offset_y*ldc;


  for (int i = 0; i<3; i++)
  {
    C[0]      = mad( beta, C[0]     , alpha * rC[0][2*i] );
	
	if(offset_y+1<N)
      C[ldc]    = mad( beta, C[ldc]   , alpha * rC[1][2*i] );
    if(offset_y+16<N)
      C[16*ldc] = mad( beta, C[16*ldc], alpha * rC[2][2*i] );
	if(offset_y+17<N)
      C[17*ldc] = mad( beta, C[17*ldc], alpha * rC[3][2*i] );
	if(offset_y+32<N)
      C[32*ldc] = mad( beta, C[32*ldc], alpha * rC[4][2*i] );
	if(offset_y+33<N)
      C[33*ldc] = mad( beta, C[33*ldc], alpha * rC[5][2*i] );

	if(offset_x+1>=M )
	  return;
	
	C[1] = mad( beta, C[1]     , alpha * rC[0][2*i+1] );
	
	if(offset_y+1<N)
      C[1+ldc]    = mad( beta, C[1+ldc]   , alpha * rC[1][2*i+1] );
	if(offset_y+16<N)
      C[1+16*ldc] = mad( beta, C[1+16*ldc], alpha * rC[2][2*i+1] );
	if(offset_y+17<N)
      C[1+17*ldc] = mad( beta, C[1+17*ldc], alpha * rC[3][2*i+1] );
	if(offset_y+32<N)
      C[1+32*ldc] = mad( beta, C[1+32*ldc], alpha * rC[4][2*i+1] );
	if(offset_y+33<N)
      C[1+33*ldc] = mad( beta, C[1+33*ldc], alpha * rC[5][2*i+1] );

	C+=16;
	offset_x+=16;
	if(offset_x>=M )
       return;

  }
}
";

static const char * dgemm_NT_8_SPLIT__ALPHA = "
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
            barrier(CLK_LOCAL_MEM_FENCE);


__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_48_48_8_8x8_6x6__ALPHA_SPLIT_MAIN(__global double2 const * restrict A,
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


__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_1_48_8_8x8_6x6__ALPHA_SPLIT_ROW(__global double2 const * restrict A,
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

    int gidx = M/48;//get_group_id(0);
    int gidy = get_group_id(1);
    int idx  = get_local_id(0);
    int idy  = get_local_id(1);

	 int CurrentOffSetA = 2*(gidx*24 + idx);

    uA.d += 2*(gidx*24 + idx) + idy*lda;
    uB.d += 2*(gidy*24 + idx) + idy*ldb;

    int block_k = K >> 3;
    do {
        __local double* plA = (lA + idy*48 + 2*idx);
        __local double2* plB = (__local double2*)(lB + idy*48 + 2*idx);
//        barrier(CLK_LOCAL_MEM_FENCE);
        plB[0 ] = uB.d2v[0 ];
        plB[8 ] = uB.d2v[8 ];
        plB[16] = uB.d2v[16];

        plA[0]  =  CurrentOffSetA>=M?0.0:uA.d[0];
        plA[1]  =  CurrentOffSetA+1>=M?0.0:uA.d[1];
        plA[16] =  CurrentOffSetA+16>=M?0.0:uA.d[16];
        plA[17] =  CurrentOffSetA+17>=M?0.0:uA.d[17];
        plA[32] =  CurrentOffSetA+32>=M?0.0:uA.d[32];
        plA[33] =  CurrentOffSetA+33>=M?0.0:uA.d[33];


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
	

  if(offset_x>=M )
    return;

  C+=offset_x+offset_y*ldc;


  for (int i = 0; i<3; i++)
  {
    C[0]      = alpha * rC[0][2*i] ;
    C[ldc]    = alpha * rC[1][2*i] ;
    C[16*ldc] = alpha * rC[2][2*i] ;
    C[17*ldc] = alpha * rC[3][2*i] ;
    C[32*ldc] = alpha * rC[4][2*i] ;
    C[33*ldc] = alpha * rC[5][2*i] ;

	if(offset_x+1>=M )
	  return;
	
	C[1]        =  alpha * rC[0][2*i+1] ;
    C[1+ldc]    =  alpha * rC[1][2*i+1] ;
    C[1+16*ldc] =  alpha * rC[2][2*i+1] ;
    C[1+17*ldc] =  alpha * rC[3][2*i+1] ;
    C[1+32*ldc] =  alpha * rC[4][2*i+1] ;
    C[1+33*ldc] =  alpha * rC[5][2*i+1] ;

	C+=16;
	offset_x+=16;
	if(offset_x>=M )
       return;

  }
}



__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_48_1_8_8x8_6x6__ALPHA_SPLIT_COLUMN(__global double2 const * restrict A,
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
    int gidy = N/48;//get_group_id(1);
    int idx  = get_local_id(0);
    int idy  = get_local_id(1);

	int CurrentOffSetB = 2*(gidy*24 + idx);
    uA.d += 2*(gidx*24 + idx) + idy*lda;
    uB.d += 2*(gidy*24 + idx) + idy*ldb;

    int block_k = K >> 3;
    do {
        __local double2* plA = (__local double2*) (lA + idy*48 + 2*idx);
        __local double* plB = (lB + idy*48 + 2*idx);
//        barrier(CLK_LOCAL_MEM_FENCE);
        plB[0 ] = CurrentOffSetB>=N?0.0:uB.d[0 ];
        plB[1 ] = CurrentOffSetB+1>=N?0.0:uB.d[1 ];
        plB[16] = CurrentOffSetB+16>=N?0.0:uB.d[16 ];
        plB[17] = CurrentOffSetB+17>=N?0.0:uB.d[17];
        plB[32] = CurrentOffSetB+32>=N?0.0:uB.d[32];
        plB[33] = CurrentOffSetB+33>=N?0.0:uB.d[33];

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
	

  if( offset_y>=N )
    return;

  C+=offset_x+offset_y*ldc;


  for (int i = 0; i<3; i++)
  {
    C[0]   = alpha * rC[0][2*i] ;
	C[1]   = alpha * rC[0][2*i+1] ;

	if(offset_y+1<N)
	{
      C[ldc]   =  alpha * rC[1][2*i] ;
	  C[1+ldc] =  alpha * rC[1][2*i+1] ;
	}

	if(offset_y+16<N)
	{
      C[16*ldc]   =  alpha * rC[2][2*i] ;
	  C[1+16*ldc] =  alpha * rC[2][2*i+1] ;
    }

	if(offset_y+17<N)
	{
      C[17*ldc]   =  alpha * rC[3][2*i] ;
	  C[1+17*ldc] =  alpha * rC[3][2*i+1] ;
    }

	if(offset_y+32<N)
	{
	  C[32*ldc]   =  alpha * rC[4][2*i] ;
	  C[1+32*ldc] =  alpha * rC[4][2*i+1] ;
	}

	if(offset_y+33<N)
	{
      C[33*ldc]   =  alpha * rC[5][2*i] ;
	  C[1+33*ldc] =  alpha * rC[5][2*i+1] ;
    }

	C+=16;
	
  }
}


__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_1_1_8_8x8_6x6__ALPHA_SPLIT_SINGLE(__global double2 const * restrict A,
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

    int gidx = M/48;//get_group_id(0);
    int gidy = N/48;//get_group_id(1);
    int idx  = get_local_id(0);
    int idy  = get_local_id(1);
	
	int CurrentOffSetA = 2*(gidx*24 + idx);
	int CurrentOffSetB = 2*(gidy*24 + idx);

    uA.d += 2*(gidx*24 + idx) + idy*lda;
    uB.d += 2*(gidy*24 + idx) + idy*ldb;

    int block_k = K >> 3;
    do {
        __local double* plA = (lA + idy*48 + 2*idx);
        __local double* plB = (lB + idy*48 + 2*idx);
//        barrier(CLK_LOCAL_MEM_FENCE);
        //plB[0 ] = uB.d2v[0 ];
        //plB[8 ] = uB.d2v[8 ];
        //plB[16] = uB.d2v[16];
        //plA[0 ] = uA.d2v[0 ];
        //plA[8 ] = uA.d2v[8 ];
        //plA[16] = uA.d2v[16];

		
        plB[0 ] = CurrentOffSetB>=N?0.0:uB.d[0 ];
        plB[1 ] = CurrentOffSetB+1>=N?0.0:uB.d[1 ];
        plB[16] = CurrentOffSetB+16>=N?0.0:uB.d[16 ];
        plB[17] = CurrentOffSetB+17>=N?0.0:uB.d[17];
        plB[32] = CurrentOffSetB+32>=N?0.0:uB.d[32];
        plB[33] = CurrentOffSetB+33>=N?0.0:uB.d[33];
        
        plA[0]  =  CurrentOffSetA>=M?0.0:uA.d[0];
        plA[1]  =  CurrentOffSetA+1>=M?0.0:uA.d[1];
        plA[16] =  CurrentOffSetA+16>=M?0.0:uA.d[16];
        plA[17] =  CurrentOffSetA+17>=M?0.0:uA.d[17];
        plA[32] =  CurrentOffSetA+32>=M?0.0:uA.d[32];
        plA[33] =  CurrentOffSetA+33>=M?0.0:uA.d[33];


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
	

  if(offset_x>=M || offset_y>=N )
    return;

  C+=offset_x+offset_y*ldc;


  for (int i = 0; i<3; i++)
  {
    C[0]      = alpha * rC[0][2*i] ;
	
	if(offset_y+1<N)
      C[ldc]    =  alpha * rC[1][2*i] ;
    if(offset_y+16<N)
      C[16*ldc] =  alpha * rC[2][2*i] ;
	if(offset_y+17<N)
      C[17*ldc] =  alpha * rC[3][2*i] ;
	if(offset_y+32<N)
      C[32*ldc] =  alpha * rC[4][2*i] ;
	if(offset_y+33<N)
      C[33*ldc] =  alpha * rC[5][2*i] ;

	if(offset_x+1>=M )
	  return;
	
	C[1]        =  alpha * rC[0][2*i+1] ;
	if(offset_y+1<N)
      C[1+ldc]    =  alpha * rC[1][2*i+1] ;
	if(offset_y+16<N)
      C[1+16*ldc] =  alpha * rC[2][2*i+1] ;
	if(offset_y+17<N)
      C[1+17*ldc] =  alpha * rC[3][2*i+1] ;
	if(offset_y+32<N)
      C[1+32*ldc] =  alpha * rC[4][2*i+1] ;
	if(offset_y+33<N)
      C[1+33*ldc] =  alpha * rC[5][2*i+1] ;

	C+=16;
	offset_x+=16;
	if(offset_x>=M )
       return;

  }
}
";





static const char * dgemm_NT_1_SPLIT__ALPHABETA = "

typedef union GPtr {
  __global float *f;
  __global double *d;
  __global float2 *f2v;
  __global double2 *d2v;
} GPtr;




__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_48_48_1_8x8_6x6__ALPHABETA_SPLIT_MAIN(__global double2 const * restrict A,
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

    int block_k = 0;//K >> 3;
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
	    #pragma unroll 1
        for(uint k = 0 ; k < min(8u, K-block_k ) ; k+=1)
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
			barrier(CLK_LOCAL_MEM_FENCE);
        }
        uA.d += lda << 3;
        uB.d += ldb << 3;
		block_k+=8;
    } while (block_k < K);




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



__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_1_48_1_8x8_6x6__ALPHABETA_SPLIT_ROW(__global double2 const * restrict A,
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

    int gidx = M/48;//get_group_id(0);
    int gidy = get_group_id(1);
    int idx  = get_local_id(0);
    int idy  = get_local_id(1);

	int CurrentOffSetA = 2*(gidx*24 + idx);
	
	  uA.d += 2*(gidx*24 + idx) + idy*lda;
    uB.d += 2*(gidy*24 + idx) + idy*ldb;

    int block_k = 0;//K >> 3;
    do {
        __local double* plA =(lA + idy*48 + 2*idx);
        __local double2* plB = (__local double2*)(lB + idy*48 + 2*idx);
//        barrier(CLK_LOCAL_MEM_FENCE);
        plB[0 ] = uB.d2v[0 ];
        plB[8 ] = uB.d2v[8 ];
        plB[16] = uB.d2v[16];
               
	    plA[0]  =  CurrentOffSetA>=M?0.0:uA.d[0];
        plA[1]  =  CurrentOffSetA+1>=M?0.0:uA.d[1];
        plA[16] =  CurrentOffSetA+16>=M?0.0:uA.d[16];
        plA[17] =  CurrentOffSetA+17>=M?0.0:uA.d[17];
        plA[32] =  CurrentOffSetA+32>=M?0.0:uA.d[32];
        plA[33] =  CurrentOffSetA+33>=M?0.0:uA.d[33];

        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx << 1;
        int offB = idy << 1;
        #pragma unroll 1
        for(uint k = 0 ; k < min(8u, K-block_k ); k+=1)
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
			barrier(CLK_LOCAL_MEM_FENCE);
        }
        uA.d += lda << 3;
        uB.d += ldb << 3;
		block_k+=8;
    } while (block_k < K);




    int offset_x = gidx*48+ idx*2;
    int offset_y = gidy*48+ idy*2;
	

  if(offset_x>=M )
    return;

  C+=offset_x+offset_y*ldc;


  for (int i = 0; i<3; i++)
  {
    C[0]      = mad( beta, C[0]     , alpha * rC[0][2*i] );
    C[ldc]    = mad( beta, C[ldc]   , alpha * rC[1][2*i] );
    C[16*ldc] = mad( beta, C[16*ldc], alpha * rC[2][2*i] );
    C[17*ldc] = mad( beta, C[17*ldc], alpha * rC[3][2*i] );
    C[32*ldc] = mad( beta, C[32*ldc], alpha * rC[4][2*i] );
    C[33*ldc] = mad( beta, C[33*ldc], alpha * rC[5][2*i] );

	if(offset_x+1>=M )
	  return;
	
	C[1]        = mad( beta, C[1]     , alpha * rC[0][2*i+1] );
    C[1+ldc]    = mad( beta, C[1+ldc]   , alpha * rC[1][2*i+1] );
    C[1+16*ldc] = mad( beta, C[1+16*ldc], alpha * rC[2][2*i+1] );
    C[1+17*ldc] = mad( beta, C[1+17*ldc], alpha * rC[3][2*i+1] );
    C[1+32*ldc] = mad( beta, C[1+32*ldc], alpha * rC[4][2*i+1] );
    C[1+33*ldc] = mad( beta, C[1+33*ldc], alpha * rC[5][2*i+1] );

	C+=16;
	offset_x+=16;
	if(offset_x>=M )
       return;

  }
}

__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_48_1_1_8x8_6x6__ALPHABETA_SPLIT_COLUMN(__global double2 const * restrict A,
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
    int gidy = N/48;//get_group_id(1);
    int idx  = get_local_id(0);
    int idy  = get_local_id(1);

	int CurrentOffSetB = 2*(gidy*24 + idx);

    uA.d += 2*(gidx*24 + idx) + idy*lda;
    uB.d += 2*(gidy*24 + idx) + idy*ldb;

    int block_k = 0;//K >> 3;
    do {
        __local double2* plA = (__local double2*)(lA + idy*48 + 2*idx);
        __local double* plB = (lB + idy*48 + 2*idx);
//        barrier(CLK_LOCAL_MEM_FENCE);
        plB[0 ] = CurrentOffSetB>=N?0.0:uB.d[0 ];
        plB[1 ] = CurrentOffSetB+1>=N?0.0:uB.d[1 ];
        plB[16] = CurrentOffSetB+16>=N?0.0:uB.d[16 ];
        plB[17] = CurrentOffSetB+17>=N?0.0:uB.d[17];
        plB[32] = CurrentOffSetB+32>=N?0.0:uB.d[32];
        plB[33] = CurrentOffSetB+33>=N?0.0:uB.d[33];

        plA[0 ] = uA.d2v[0 ];
        plA[8 ] = uA.d2v[8 ];
        plA[16] = uA.d2v[16];

        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx << 1;
        int offB = idy << 1;
                #pragma unroll 1
        for(uint k = 0 ; k <min(8u, K-block_k ); k+=1)
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
			barrier(CLK_LOCAL_MEM_FENCE);
        }
        uA.d += lda << 3;
        uB.d += ldb << 3;
		block_k+=8;
    } while (block_k < K);




    int offset_x = gidx*48+ idx*2;
    int offset_y = gidy*48+ idy*2;
	

  if( offset_y>=N )
    return;

  C+=offset_x+offset_y*ldc;


  for (int i = 0; i<3; i++)
  {
    C[0]   = mad( beta, C[0], alpha * rC[0][2*i] );
	C[1]   = mad( beta, C[1], alpha * rC[0][2*i+1] );

	if(offset_y+1<N)
	{
      C[ldc]   = mad( beta, C[ldc], alpha * rC[1][2*i] );
	  C[1+ldc] = mad( beta, C[1+ldc], alpha * rC[1][2*i+1] );
	}

	if(offset_y+16<N)
	{
      C[16*ldc]   = mad( beta, C[16*ldc], alpha * rC[2][2*i] );
	  C[1+16*ldc] = mad( beta, C[1+16*ldc], alpha * rC[2][2*i+1] );
    }

	if(offset_y+17<N)
	{
      C[17*ldc]   = mad( beta, C[17*ldc], alpha * rC[3][2*i] );
	  C[1+17*ldc] = mad( beta, C[1+17*ldc], alpha * rC[3][2*i+1] );
    }

	if(offset_y+32<N)
	{
	  C[32*ldc]   = mad( beta, C[32*ldc], alpha * rC[4][2*i] );
	  C[1+32*ldc] = mad( beta, C[1+32*ldc], alpha * rC[4][2*i+1] );
	}

	if(offset_y+33<N)
	{
      C[33*ldc]   = mad( beta, C[33*ldc], alpha * rC[5][2*i] );
	  C[1+33*ldc] = mad( beta, C[1+33*ldc], alpha * rC[5][2*i+1] );
    }

	C+=16;
	
  }
}

__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_1_1_1_8x8_6x6__ALPHABETA_SPLIT_SINGLE(__global double2 const * restrict A,
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

    int gidx = M/48;//get_group_id(0);
    int gidy = N/48;//get_group_id(1);
    int idx  = get_local_id(0);
    int idy  = get_local_id(1);
	int CurrentOffSetA = 2*(gidx*24 + idx);
	int CurrentOffSetB = 2*(gidy*24 + idx);

    uA.d += 2*(gidx*24 + idx) + idy*lda;
    uB.d += 2*(gidy*24 + idx) + idy*ldb;

    int block_k = 0;//K >> 3;
    do {
        __local double* plA = (lA + idy*48 + 2*idx);
        __local double* plB = (lB + idy*48 + 2*idx);
//        barrier(CLK_LOCAL_MEM_FENCE);
        
        plB[0 ] = CurrentOffSetB>=N?0.0:uB.d[0 ];
        plB[1 ] = CurrentOffSetB+1>=N?0.0:uB.d[1 ];
        plB[16] = CurrentOffSetB+16>=N?0.0:uB.d[16 ];
        plB[17] = CurrentOffSetB+17>=N?0.0:uB.d[17];
        plB[32] = CurrentOffSetB+32>=N?0.0:uB.d[32];
        plB[33] = CurrentOffSetB+33>=N?0.0:uB.d[33];
        
        plA[0]  =  CurrentOffSetA>=M?0.0:uA.d[0];
        plA[1]  =  CurrentOffSetA+1>=M?0.0:uA.d[1];
        plA[16] =  CurrentOffSetA+16>=M?0.0:uA.d[16];
        plA[17] =  CurrentOffSetA+17>=M?0.0:uA.d[17];
        plA[32] =  CurrentOffSetA+32>=M?0.0:uA.d[32];
        plA[33] =  CurrentOffSetA+33>=M?0.0:uA.d[33];


        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx << 1;
        int offB = idy << 1;
                #pragma unroll 1
        for(uint k = 0 ; k < min(8u, K-block_k ); k+=1)
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
			barrier(CLK_LOCAL_MEM_FENCE);
        }
        uA.d += lda << 3;
        uB.d += ldb << 3;
		block_k+=8;
    } while (block_k < K);




    int offset_x = gidx*48+ idx*2;
    int offset_y = gidy*48+ idy*2;
	

  if(offset_x>=M || offset_y>=N )
    return;

  C+=offset_x+offset_y*ldc;


  for (int i = 0; i<3; i++)
  {
    C[0]      = mad( beta, C[0]     , alpha * rC[0][2*i] );
	
	if(offset_y+1<N)
      C[ldc]    = mad( beta, C[ldc]   , alpha * rC[1][2*i] );
    if(offset_y+16<N)
      C[16*ldc] = mad( beta, C[16*ldc], alpha * rC[2][2*i] );
	if(offset_y+17<N)
      C[17*ldc] = mad( beta, C[17*ldc], alpha * rC[3][2*i] );
	if(offset_y+32<N)
      C[32*ldc] = mad( beta, C[32*ldc], alpha * rC[4][2*i] );
	if(offset_y+33<N)
      C[33*ldc] = mad( beta, C[33*ldc], alpha * rC[5][2*i] );

	if(offset_x+1>=M )
	  return;
	
	C[1] = mad( beta, C[1]     , alpha * rC[0][2*i+1] );
	
	if(offset_y+1<N)
      C[1+ldc]    = mad( beta, C[1+ldc]   , alpha * rC[1][2*i+1] );
	if(offset_y+16<N)
      C[1+16*ldc] = mad( beta, C[1+16*ldc], alpha * rC[2][2*i+1] );
	if(offset_y+17<N)
      C[1+17*ldc] = mad( beta, C[1+17*ldc], alpha * rC[3][2*i+1] );
	if(offset_y+32<N)
      C[1+32*ldc] = mad( beta, C[1+32*ldc], alpha * rC[4][2*i+1] );
	if(offset_y+33<N)
      C[1+33*ldc] = mad( beta, C[1+33*ldc], alpha * rC[5][2*i+1] );

	C+=16;
	offset_x+=16;
	if(offset_x>=M )
       return;

  }
}
";

static const char * dgemm_NT_1_SPLIT__ALPHA = "
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
            barrier(CLK_LOCAL_MEM_FENCE);


__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_48_48_1_8x8_6x6__ALPHA_SPLIT_MAIN(__global double2 const * restrict A,
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

    int block_k = 0;//K >> 3;
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
                #pragma unroll 1
        for(uint k = 0 ; k < min(8u, K-block_k ); k+=1)
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
			barrier(CLK_LOCAL_MEM_FENCE);
        }
        uA.d += lda << 3;
        uB.d += ldb << 3;
		block_k+=8;
    } while (block_k < K);




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


__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_1_48_1_8x8_6x6__ALPHA_SPLIT_ROW(__global double2 const * restrict A,
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

    int gidx = M/48;//get_group_id(0);
    int gidy = get_group_id(1);
    int idx  = get_local_id(0);
    int idy  = get_local_id(1);

	int CurrentOffSetA = 2*(gidx*24 + idx);

    uA.d += 2*(gidx*24 + idx) + idy*lda;
    uB.d += 2*(gidy*24 + idx) + idy*ldb;

    int block_k = 0;//K >> 3;
    do {
        __local double* plA = (lA + idy*48 + 2*idx);
        __local double2* plB = (__local double2*)(lB + idy*48 + 2*idx);
//        barrier(CLK_LOCAL_MEM_FENCE);
        plB[0 ] = uB.d2v[0 ];
        plB[8 ] = uB.d2v[8 ];
        plB[16] = uB.d2v[16];

        plA[0]  =  CurrentOffSetA>=M?0.0:uA.d[0];
        plA[1]  =  CurrentOffSetA+1>=M?0.0:uA.d[1];
        plA[16] =  CurrentOffSetA+16>=M?0.0:uA.d[16];
        plA[17] =  CurrentOffSetA+17>=M?0.0:uA.d[17];
        plA[32] =  CurrentOffSetA+32>=M?0.0:uA.d[32];
        plA[33] =  CurrentOffSetA+33>=M?0.0:uA.d[33];

        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx << 1;
        int offB = idy << 1;
                #pragma unroll 1
        for(uint k = 0 ; k < min(8u, K-block_k ); k+=1)
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
			barrier(CLK_LOCAL_MEM_FENCE);
        }
        uA.d += lda << 3;
        uB.d += ldb << 3;
		block_k+=8;
    } while (block_k < K);




    int offset_x = gidx*48+ idx*2;
    int offset_y = gidy*48+ idy*2;
	

  if(offset_x>=M )
    return;

  C+=offset_x+offset_y*ldc;


  for (int i = 0; i<3; i++)
  {
    C[0]      = alpha * rC[0][2*i] ;
    C[ldc]    = alpha * rC[1][2*i] ;
    C[16*ldc] = alpha * rC[2][2*i] ;
    C[17*ldc] = alpha * rC[3][2*i] ;
    C[32*ldc] = alpha * rC[4][2*i] ;
    C[33*ldc] = alpha * rC[5][2*i] ;

	if(offset_x+1>=M )
	  return;
	
	C[1]        =  alpha * rC[0][2*i+1] ;
    C[1+ldc]    =  alpha * rC[1][2*i+1] ;
    C[1+16*ldc] =  alpha * rC[2][2*i+1] ;
    C[1+17*ldc] =  alpha * rC[3][2*i+1] ;
    C[1+32*ldc] =  alpha * rC[4][2*i+1] ;
    C[1+33*ldc] =  alpha * rC[5][2*i+1] ;

	C+=16;
	offset_x+=16;
	if(offset_x>=M )
       return;

  }
}



__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_48_1_1_8x8_6x6__ALPHA_SPLIT_COLUMN(__global double2 const * restrict A,
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
    int gidy = N/48;//get_group_id(1);
    int idx  = get_local_id(0);
    int idy  = get_local_id(1);

	int CurrentOffSetB = 2*(gidy*24 + idx);
    uA.d += 2*(gidx*24 + idx) + idy*lda;
    uB.d += 2*(gidy*24 + idx) + idy*ldb;

    int block_k = 0;//K >> 3;
    do {
        __local double2* plA = (__local double2*)(lA + idy*48 + 2*idx);
        __local double* plB = (__local double*)(lB + idy*48 + 2*idx);
//        barrier(CLK_LOCAL_MEM_FENCE);
        plB[0 ] = CurrentOffSetB>=N?0.0:uB.d[0 ];
        plB[1 ] = CurrentOffSetB+1>=N?0.0:uB.d[1 ];
        plB[16] = CurrentOffSetB+16>=N?0.0:uB.d[16 ];
        plB[17] = CurrentOffSetB+17>=N?0.0:uB.d[17];
        plB[32] = CurrentOffSetB+32>=N?0.0:uB.d[32];
        plB[33] = CurrentOffSetB+33>=N?0.0:uB.d[33];
		
		plA[0 ] = uA.d2v[0 ];
        plA[8 ] = uA.d2v[8 ];
        plA[16] = uA.d2v[16];

        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx << 1;
        int offB = idy << 1;
       
	    #pragma unroll 1
        for(uint k = 0 ; k < min(8u, K-block_k ); k+=1)
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
			barrier(CLK_LOCAL_MEM_FENCE);
        }
        uA.d += lda << 3;
        uB.d += ldb << 3;
		block_k+=8;
    } while (block_k < K);



    int offset_x = gidx*48+ idx*2;
    int offset_y = gidy*48+ idy*2;
	

  if( offset_y>=N )
    return;

  C+=offset_x+offset_y*ldc;


  for (int i = 0; i<3; i++)
  {
    C[0]   = alpha * rC[0][2*i] ;
	C[1]   = alpha * rC[0][2*i+1] ;

	if(offset_y+1<N)
	{
      C[ldc]   =  alpha * rC[1][2*i] ;
	  C[1+ldc] =  alpha * rC[1][2*i+1] ;
	}

	if(offset_y+16<N)
	{
      C[16*ldc]   =  alpha * rC[2][2*i] ;
	  C[1+16*ldc] =  alpha * rC[2][2*i+1] ;
    }

	if(offset_y+17<N)
	{
      C[17*ldc]   =  alpha * rC[3][2*i] ;
	  C[1+17*ldc] =  alpha * rC[3][2*i+1] ;
    }

	if(offset_y+32<N)
	{
	  C[32*ldc]   =  alpha * rC[4][2*i] ;
	  C[1+32*ldc] =  alpha * rC[4][2*i+1] ;
	}

	if(offset_y+33<N)
	{
      C[33*ldc]   =  alpha * rC[5][2*i] ;
	  C[1+33*ldc] =  alpha * rC[5][2*i+1] ;
    }

	C+=16;
	
  }
}


__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NT_1_1_1_8x8_6x6__ALPHA_SPLIT_SINGLE(__global double2 const * restrict A,
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

    int gidx = M/48;//get_group_id(0);
    int gidy = N/48;//get_group_id(1);
    int idx  = get_local_id(0);
    int idy  = get_local_id(1);

	int CurrentOffSetA = 2*(gidx*24 + idx);
	int CurrentOffSetB = 2*(gidy*24 + idx);

    uA.d += 2*(gidx*24 + idx) + idy*lda;
    uB.d += 2*(gidy*24 + idx) + idy*ldb;

    int block_k = 0;//K >> 3;
    do {
        __local double* plA = (lA + idy*48 + 2*idx);
        __local double* plB = (lB + idy*48 + 2*idx);
//        barrier(CLK_LOCAL_MEM_FENCE);
        plB[0 ] = CurrentOffSetB>=N?0.0:uB.d[0 ];
        plB[1 ] = CurrentOffSetB+1>=N?0.0:uB.d[1 ];
        plB[16] = CurrentOffSetB+16>=N?0.0:uB.d[16 ];
        plB[17] = CurrentOffSetB+17>=N?0.0:uB.d[17];
        plB[32] = CurrentOffSetB+32>=N?0.0:uB.d[32];
        plB[33] = CurrentOffSetB+33>=N?0.0:uB.d[33];
        
        plA[0]  =  CurrentOffSetA>=M?0.0:uA.d[0];
        plA[1]  =  CurrentOffSetA+1>=M?0.0:uA.d[1];
        plA[16] =  CurrentOffSetA+16>=M?0.0:uA.d[16];
        plA[17] =  CurrentOffSetA+17>=M?0.0:uA.d[17];
        plA[32] =  CurrentOffSetA+32>=M?0.0:uA.d[32];
        plA[33] =  CurrentOffSetA+33>=M?0.0:uA.d[33];

        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx << 1;
        int offB = idy << 1;
             
        #pragma unroll 1
        for(uint k = 0 ; k < min(8u, K-block_k ); k+=1)
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
			barrier(CLK_LOCAL_MEM_FENCE);
        }
        uA.d += lda << 3;
        uB.d += ldb << 3;
		block_k+=8;
    } while (block_k < K);




    int offset_x = gidx*48+ idx*2;
    int offset_y = gidy*48+ idy*2;
	

  if(offset_x>=M || offset_y>=N )
    return;

  C+=offset_x+offset_y*ldc;


  for (int i = 0; i<3; i++)
  {
    C[0]      = alpha * rC[0][2*i] ;
	
	if(offset_y+1<N)
      C[ldc]    =  alpha * rC[1][2*i] ;
    if(offset_y+16<N)
      C[16*ldc] =  alpha * rC[2][2*i] ;
	if(offset_y+17<N)
      C[17*ldc] =  alpha * rC[3][2*i] ;
	if(offset_y+32<N)
      C[32*ldc] =  alpha * rC[4][2*i] ;
	if(offset_y+33<N)
      C[33*ldc] =  alpha * rC[5][2*i] ;

	if(offset_x+1>=M )
	  return;
	
	C[1]        =  alpha * rC[0][2*i+1] ;
	if(offset_y+1<N)
      C[1+ldc]    =  alpha * rC[1][2*i+1] ;
	if(offset_y+16<N)
      C[1+16*ldc] =  alpha * rC[2][2*i+1] ;
	if(offset_y+17<N)
      C[1+17*ldc] =  alpha * rC[3][2*i+1] ;
	if(offset_y+32<N)
      C[1+32*ldc] =  alpha * rC[4][2*i+1] ;
	if(offset_y+33<N)
      C[1+33*ldc] =  alpha * rC[5][2*i+1] ;

	C+=16;
	offset_x+=16;
	if(offset_x>=M )
       return;

  }
}
";


static const char * dgemm_NN_8_SPLIT__ALPHABETA = "



#define  M6x6 \
            rA[0] = lA[offA + 0];                       \
            rA[1] = lA[offA + 8];                       \
            rA[2] = lA[offA + 16];                      \
            rA[3] = lA[offA + 24];                      \
            rA[4] = lA[offA + 32];                      \
            rA[5] = lA[offA + 40];                      \
            rB[0] = lB[offB + 0];                       \
            rB[1] = lB[offB + 8];                       \
            rB[2] = lB[offB + 16];                      \
            rB[3] = lB[offB + 24];                      \
            rB[4] = lB[offB + 32];                      \
            rB[5] = lB[offB + 40];                      \
            offA += 49;                                 \
            offB += 49;                                 \
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
            barrier(CLK_LOCAL_MEM_FENCE);




__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NN_48_48_8_8x8_6x6__ALPHABETA_SPLIT_MAIN(__global double const * restrict A,
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


    A += offsetA;
    B += offsetB;
    C += offsetC;


    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];

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



    int block_k = K >> 3;
    do {

	    __local double* plA = lA + idyT*49 + idxT;
        __local double* plB = lB + idxT*49 + idyT;

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
        int offA = idx;
        int offB = idy;

        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        A += lda << 3;
        B += 8;
    } while (--block_k > 0);



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



__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NN_1_48_8_8x8_6x6__ALPHABETA_SPLIT_ROW(__global double const * restrict A,
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


    A += offsetA;
    B += offsetB;
    C += offsetC;


    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];
  __local double lA[392];
  __local double lB[392];

  int gidx = M/48;//get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;
 
  int CurrentOffSetA =   gidx*48 + idxT;
   
  A +=  gidx*48+ idxT + idyT*lda;
  B +=  gidy*48*ldb+ idx + idy*ldb;

    int block_k = K >> 3;
    do {

	    __local double* plA = lA + idyT*49 + idxT;
        __local double* plB = lB + idxT*49 + idyT;
    
       
	    plB[0] = B[0+0*ldb];
        plB[8] = B[0+8*ldb];
        plB[16] = B[0+16*ldb];
        plB[24] = B[0+24*ldb];
        plB[32] = B[0+32*ldb];
        plB[40] = B[0+40*ldb];

        plA[0] = CurrentOffSetA>=M?0.0:A[0];
        plA[8] = CurrentOffSetA+8>=M?0.0:A[8];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[24] = CurrentOffSetA+24>=M?0.0:A[24];
		plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[40] = CurrentOffSetA+40>=M?0.0:A[40];


        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx ;
        int offB = idy ;
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        A += lda << 3;
        B += 8;
    } while (--block_k > 0);



    int offset_x = gidx*48+ idx;
    int offset_y = gidy*48+ idy;
	

  if(offset_x>=M )
    return;

  C+= offset_x+ldc*offset_y; 
 
 
  //for (int i=0; i<6; i++)
  int i = 0;
  do
  {
    C[0*ldc+i*8]  = alpha*rC[i][0] + beta*C[0*ldc+i*8];
    C[8*ldc+i*8]  = alpha*rC[i][1] + beta*C[8*ldc+i*8];
    C[16*ldc+i*8] = alpha*rC[i][2] + beta*C[16*ldc+i*8];
    C[24*ldc+i*8] = alpha*rC[i][3] + beta*C[24*ldc+i*8];
    C[32*ldc+i*8] = alpha*rC[i][4] + beta*C[32*ldc+i*8];
    C[40*ldc+i*8] = alpha*rC[i][5] + beta*C[40*ldc+i*8];
	
    offset_x += 8;
    if(offset_x>=M)
        return;
  }while (++i < 6);
  
}

__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NN_48_1_8_8x8_6x6__ALPHABETA_SPLIT_COLUMN(__global double const * restrict A,
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


    A += offsetA;
    B += offsetB;
    C    += offsetC;


    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];

  __local double lA[392];
  __local double lB[392];

  int gidx = get_group_id(0);
  int gidy = N/48;//get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*48+ idxT + idyT*lda;
  B +=  (gidy*48+idyT)*ldb + idxT;

  int CurrentOffSetB =   gidy*48 + idyT;

    int block_k = K >> 3;
    do {

	    __local double* plA = lA + idyT*49 + idxT;
        __local double* plB = lB + idxT*49 + idyT;


		plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[8]  = CurrentOffSetB+8>=N?0.0:B[0+8*ldb];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[0+16*ldb];
        plB[24] = CurrentOffSetB+24>=N?0.0:B[0+24*ldb];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[0+32*ldb];
        plB[40] = CurrentOffSetB+40>=N?0.0:B[0+40*ldb];

        plA[0] = A[0+0*lda];
        plA[8] = A[8+0*lda];
        plA[16] = A[16+0*lda];
        plA[24] = A[24+0*lda];
        plA[32] = A[32+0*lda];
        plA[40] = A[40+0*lda];


        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx ;
        int offB = idy ;
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        A += lda << 3;
        B += 8;
    } while (--block_k > 0);



    int offset_x = gidx*48+ idx;
    int offset_y = gidy*48+ idy;
	

  if(offset_y>=N )
    return;

  C+= offset_x+ldc*offset_y; 
 
 
  //for (int i=0; i<6; i++)
  int i = 0;
  do
  {
    C[i*8]  = alpha*rC[i][0] + beta*C[i*8];
	
	if (offset_y+8<N)
      C[8*ldc+i*8]  = alpha*rC[i][1] + beta*C[8*ldc+i*8];
    
	if (offset_y+16<N)
	  C[16*ldc+i*8] = alpha*rC[i][2] + beta*C[16*ldc+i*8];
    
	if (offset_y+24<N)
	  C[24*ldc+i*8] = alpha*rC[i][3] + beta*C[24*ldc+i*8];
    
	if (offset_y+32<N)
      C[32*ldc+i*8] = alpha*rC[i][4] + beta*C[32*ldc+i*8];
    
	if (offset_y+40<N)
	  C[40*ldc+i*8] = alpha*rC[i][5] + beta*C[40*ldc+i*8];

  }while (++i < 6);


}

__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NN_1_1_8_8x8_6x6__ALPHABETA_SPLIT_SINGLE(__global double const * restrict A,
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


    A += offsetA;
    B += offsetB;
    C += offsetC;


    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];

    __local double lA[392];
    __local double lB[392];

    int gidx = M/48;//get_group_id(0);
    int gidy = N/48;//get_group_id(1);
    int idx  = get_local_id(0);
    int idy  = get_local_id(1);




  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  int CurrentOffSetA =   gidx*48 + idxT;
  int CurrentOffSetB =   gidy*48 + idyT;
 

  A +=  gidx*48+ idxT + idyT*lda;
  B +=  (gidy*48+idyT)*ldb + idxT;

  __local double* plA = lA + idyT*49 + idxT;
  __local double* plB = lB + idxT*49 + idyT;


    int block_k = K >> 3;
    do {


        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[8]  = CurrentOffSetB+8>=N?0.0:B[8*ldb];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];
        plB[24] = CurrentOffSetB+24>=N?0.0:B[24*ldb];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[32*ldb];
        plB[40] = CurrentOffSetB+40>=N?0.0:B[40*ldb];


        plA[0] = CurrentOffSetA>=M?0.0:A[0];
        plA[8] = CurrentOffSetA+8>=M?0.0:A[8];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[24] = CurrentOffSetA+24>=M?0.0:A[24];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[40] = CurrentOffSetA+40>=M?0.0:A[40];
        barrier(CLK_LOCAL_MEM_FENCE);

        int offA = idx ;
        int offB = idy ;
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        A += lda << 3;
        B += 8;
    } while (--block_k > 0);




    int offset_x = gidx*48+ idx;
    int offset_y = gidy*48+ idy;

  if(offset_x>=M || offset_y>=N )
    return;

  C+= offset_x+ldc*offset_y; 

 
 
  //for (int i=0; i<6; i++)
  int i = 0;
  do
  {

    C[0*ldc+i*8]  = alpha*rC[i][0] + beta*C[0*ldc+i*8];
	
	if (offset_y+8<N)
      C[8*ldc+i*8]  = alpha*rC[i][1] + beta*C[8*ldc+i*8];
    
	if (offset_y+16<N)
	  C[16*ldc+i*8] = alpha*rC[i][2] + beta*C[16*ldc+i*8];
    
	if (offset_y+24<N)
	  C[24*ldc+i*8] = alpha*rC[i][3] + beta*C[24*ldc+i*8];
    
	if (offset_y+32<N)
      C[32*ldc+i*8] = alpha*rC[i][4] + beta*C[32*ldc+i*8];
    
	if (offset_y+40<N)
	  C[40*ldc+i*8] = alpha*rC[i][5] + beta*C[40*ldc+i*8];

	offset_x += 8;
    if(offset_x>=M)
        return;


  }while (++i < 6);
}
";

static const char * dgemm_NN_8_SPLIT__ALPHA = "



#define  M6x6 \
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
            barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NN_48_48_8_8x8_6x6__ALPHA_SPLIT_MAIN(__global double const * restrict A,
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


    A += offsetA;
    B += offsetB;
    C += offsetC;


    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];
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



    int block_k = K >> 3;
    do {

	    __local double* plA = lA + idyT*49 + idxT;
        __local double* plB = lB + idxT*49 + idyT;

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
        int offA = idx ;
        int offB = idy ;
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        A += lda << 3;
        B += 8;
    } while (--block_k > 0);



  C+= gidx*48;
  C+= idx;
  C+= gidy*48*ldc;
  C+= idy*ldc;
 
  C[0*ldc] = alpha*rC[0][0]  ;
  C[8*ldc] = alpha*rC[0][1]  ;
  C[16*ldc] = alpha*rC[0][2] ;
  C[24*ldc] = alpha*rC[0][3] ;
  C[32*ldc] = alpha*rC[0][4] ;
  C[40*ldc] = alpha*rC[0][5] ;
  C+=8;						 ;
  C[0*ldc] = alpha*rC[1][0]  ;
  C[8*ldc] = alpha*rC[1][1]  ;
  C[16*ldc] = alpha*rC[1][2] ;
  C[24*ldc] = alpha*rC[1][3] ;
  C[32*ldc] = alpha*rC[1][4] ;
  C[40*ldc] = alpha*rC[1][5] ;
  C+=8;						 ;
  C[0*ldc] = alpha*rC[2][0]  ;
  C[8*ldc] = alpha*rC[2][1]  ;
  C[16*ldc] = alpha*rC[2][2] ;
  C[24*ldc] = alpha*rC[2][3] ;
  C[32*ldc] = alpha*rC[2][4] ;
  C[40*ldc] = alpha*rC[2][5] ;
  C+=8;						 ;
  C[0*ldc] = alpha*rC[3][0]  ;
  C[8*ldc] = alpha*rC[3][1]  ;
  C[16*ldc] = alpha*rC[3][2] ;
  C[24*ldc] = alpha*rC[3][3] ;
  C[32*ldc] = alpha*rC[3][4] ;
  C[40*ldc] = alpha*rC[3][5] ;
  C+=8;						 ;
  C[0*ldc] = alpha*rC[4][0]  ;
  C[8*ldc] = alpha*rC[4][1]  ;
  C[16*ldc] = alpha*rC[4][2] ;
  C[24*ldc] = alpha*rC[4][3] ;
  C[32*ldc] = alpha*rC[4][4] ;
  C[40*ldc] = alpha*rC[4][5] ;
  C+=8;						 ;
  C[0*ldc] = alpha*rC[5][0]  ;
  C[8*ldc] = alpha*rC[5][1]  ;
  C[16*ldc] = alpha*rC[5][2] ;
  C[24*ldc] = alpha*rC[5][3] ;
  C[32*ldc] = alpha*rC[5][4] ;
  C[40*ldc] = alpha*rC[5][5] ;
  
}


__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NN_1_48_8_8x8_6x6__ALPHA_SPLIT_ROW(__global double const * restrict A,
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
    A += offsetA;
    B += offsetB;
    C    += offsetC;


    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];

  __local double lA[392];
  __local double lB[392];

  int gidx = M/48;//get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  
int CurrentOffSetA =   gidx*48 + idxT;
  

  A +=  gidx*48+ idxT + idyT*lda;
  B +=  gidy*48*ldb+ idx + idy*ldb;



    int block_k = K >> 3;
    do {

	    __local double* plA = lA + idyT*49 + idxT;
        __local double* plB = lB + idxT*49 + idyT;

        
        plB[0] = B[0+0*ldb];
        plB[8] = B[0+8*ldb];
        plB[16] = B[0+16*ldb];
        plB[24] = B[0+24*ldb];
        plB[32] = B[0+32*ldb];
        plB[40] = B[0+40*ldb];

		 plA[0] = CurrentOffSetA>=M?0.0:A[0];
        plA[8] = CurrentOffSetA+8>=M?0.0:A[8];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[24] = CurrentOffSetA+24>=M?0.0:A[24];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[40] = CurrentOffSetA+40>=M?0.0:A[40];
		
		barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx ;
        int offB = idy ;
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        A += lda << 3;
        B += 8;
    } while (--block_k > 0);


    int offset_x = gidx*48+ idx;
    int offset_y = gidy*48+ idy;
	

  if(offset_x>=M )
    return;

  C+= offset_x+ldc*offset_y; 
 
 
  for (int i=0; i<6; i++)
  {
    C[0*ldc+i*8]  = alpha*rC[i][0] ;
    C[8*ldc+i*8]  = alpha*rC[i][1] ;
    C[16*ldc+i*8] = alpha*rC[i][2] ;
    C[24*ldc+i*8] = alpha*rC[i][3] ;
    C[32*ldc+i*8] = alpha*rC[i][4] ;
    C[40*ldc+i*8] = alpha*rC[i][5] ;
	
    offset_x += 8;
    if(offset_x>=M)
        return;
  }
}



__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NN_48_1_8_8x8_6x6__ALPHA_SPLIT_COLUMN(__global double const * restrict A,
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
    A += offsetA;
    B += offsetB;
    C += offsetC;


    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];

  __local double lA[392];
  __local double lB[392];

  int gidx = get_group_id(0);
  int gidy = N/48;//get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

   int CurrentOffSetB =   gidy*48 + idyT;

  A +=  gidx*48+ idxT + idyT*lda;
  B +=  gidy*48*ldb+ idx + idy*ldb;



    int block_k = K >> 3;
    do {

	    __local double* plA = lA + idyT*49 + idxT;
        __local double* plB = lB + idxT*49 + idyT;

		plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[8]  = CurrentOffSetB+8>=N?0.0:B[0+8*ldb];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[0+16*ldb];
        plB[24] = CurrentOffSetB+24>=N?0.0:B[0+24*ldb];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[0+32*ldb];
        plB[40] = CurrentOffSetB+40>=N?0.0:B[0+40*ldb];

        plA[0] = A[0+0*lda];
        plA[8] = A[8+0*lda];
        plA[16] = A[16+0*lda];
        plA[24] = A[24+0*lda];
        plA[32] = A[32+0*lda];
        plA[40] = A[40+0*lda];
        

        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx ;
        int offB = idy ;
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        A += lda << 3;
        B += 8;
    } while (--block_k > 0);



    int offset_x = gidx*48+ idx;
    int offset_y = gidy*48+ idy;
	

  if(offset_y>=N )
    return;

  C+= offset_x+ldc*offset_y; 
 
 
  //for (int i=0; i<6; i++)
  int i = 0;
  do
  {
    C[0*ldc+i*8]  = alpha*rC[i][0]   ;
	
	if (offset_y+8<N)
      C[8*ldc+i*8]  = alpha*rC[i][1] ;
    
	if (offset_y+16<N)
	  C[16*ldc+i*8] = alpha*rC[i][2] ;
    
	if (offset_y+24<N)
	  C[24*ldc+i*8] = alpha*rC[i][3] ;
    
	if (offset_y+32<N)
      C[32*ldc+i*8] = alpha*rC[i][4] ;
    
	if (offset_y+40<N)
	  C[40*ldc+i*8] = alpha*rC[i][5] ;



  }while (++i < 6);
  
}


__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NN_1_1_8_8x8_6x6__ALPHA_SPLIT_SINGLE(__global double const * restrict A,
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
    A += offsetA;
    B += offsetB;
    C  += offsetC;


    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];

  __local double lA[392];
  __local double lB[392];

  int gidx = M/48;//get_group_id(0);
  int gidy = N/48;//get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  
  int CurrentOffSetA =   gidx*48 + idxT;
  int CurrentOffSetB =   gidy*48 + idyT;

  A +=  gidx*48+ idxT + idyT*lda;
  B +=  gidy*48*ldb+ idx + idy*ldb;



    int block_k = K >> 3;
    do {

	    __local double* plA = lA + idyT*49 + idxT;
        __local double* plB = lB + idxT*49 + idyT;


	    plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[8]  = CurrentOffSetB+8>=N?0.0:B[0+8*ldb];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[0+16*ldb];
        plB[24] = CurrentOffSetB+24>=N?0.0:B[0+24*ldb];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[0+32*ldb];
        plB[40] = CurrentOffSetB+40>=N?0.0:B[0+40*ldb];


        plA[0] = CurrentOffSetA>=M?0.0:A[0];
        plA[8] = CurrentOffSetA+8>=M?0.0:A[8];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[24] = CurrentOffSetA+24>=M?0.0:A[24];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[40] = CurrentOffSetA+40>=M?0.0:A[40];


        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx ;
        int offB = idy ;
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        A += lda << 3;
        B += 8;
    } while (--block_k > 0);

    int offset_x = gidx*48+ idx;
    int offset_y = gidy*48+ idy;
	

  if(offset_x>=M || offset_y>=N )
    return;

  C+= offset_x+ldc*offset_y; 
 
 
  //for (int i=0; i<6; i++)
  int i = 0;
  do
  {
    C[0*ldc+i*8]  = alpha*rC[i][0]  ;
	
	if (offset_y+8<N)
      C[8*ldc+i*8]  = alpha*rC[i][1] ;
    
	if (offset_y+16<N)
	  C[16*ldc+i*8] = alpha*rC[i][2] ;
    
	if (offset_y+24<N)
	  C[24*ldc+i*8] = alpha*rC[i][3];
    
	if (offset_y+32<N)
      C[32*ldc+i*8] = alpha*rC[i][4];
    
	if (offset_y+40<N)
	  C[40*ldc+i*8] = alpha*rC[i][5];

	offset_x += 8;
    if(offset_x>=M)
        return;


  }while (++i < 6);
  
}
";





static const char * dgemm_NN_1_SPLIT__ALPHABETA = "





__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NN_48_48_1_8x8_6x6__ALPHABETA_SPLIT_MAIN(__global double const * restrict A,
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


    A += offsetA;
    B += offsetB;
    C    += offsetC;


    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];

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




    int block_k = 0;//K >> 3;
    do {

	    __local double* plA = lA + idyT*49 + idxT;
        __local double* plB = lB + idxT*49 + idyT;

		plB[0] = B[0+0*ldb];
        plB[8] = B[0+8*ldb];
        plB[16] = B[0+16*ldb];
        plB[24] = B[0+24*ldb];
        plB[32] = B[0+32*ldb];
        plB[40] = B[0+40*ldb];

        plA[0] = A[0+0*lda];
        plA[8] = A[8+0*lda];
        plA[16] = A[16+0*lda];
        plA[24] = A[24+0*lda];
        plA[32] = A[32+0*lda];
        plA[40] = A[40+0*lda];
        

        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx ;
        int offB = idy ;
        
	    #pragma unroll 1
        for(uint k = 0 ; k <min(8u, K-block_k ); k+=1)
        {
		  rA[0] = lA[offA + 0];               
		  rA[1] = lA[offA + 8];               
		  rA[2] = lA[offA + 16];              
		  rA[3] = lA[offA + 24];              
		  rA[4] = lA[offA + 32];              
		  rA[5] = lA[offA + 40];              
		  rB[0] = lB[offB + 0];               
		  rB[1] = lB[offB + 8];               
		  rB[2] = lB[offB + 16];              
		  rB[3] = lB[offB + 24];              
		  rB[4] = lB[offB + 32];              
		  rB[5] = lB[offB + 40];              
		  offA += 49;                         
		  offB += 49;                         
		  rC[0][0]=mad(rA[0],rB[0],rC[0][0]); 
		  rC[1][0]=mad(rA[1],rB[0],rC[1][0]); 
		  rC[2][0]=mad(rA[2],rB[0],rC[2][0]); 
		  rC[3][0]=mad(rA[3],rB[0],rC[3][0]); 
		  rC[4][0]=mad(rA[4],rB[0],rC[4][0]); 
		  rC[5][0]=mad(rA[5],rB[0],rC[5][0]); 
		  rC[0][1]=mad(rA[0],rB[1],rC[0][1]); 
		  rC[1][1]=mad(rA[1],rB[1],rC[1][1]); 
		  rC[2][1]=mad(rA[2],rB[1],rC[2][1]); 
		  rC[3][1]=mad(rA[3],rB[1],rC[3][1]); 
		  rC[4][1]=mad(rA[4],rB[1],rC[4][1]); 
		  rC[5][1]=mad(rA[5],rB[1],rC[5][1]); 
		  rC[0][2]=mad(rA[0],rB[2],rC[0][2]); 
		  rC[1][2]=mad(rA[1],rB[2],rC[1][2]); 
		  rC[2][2]=mad(rA[2],rB[2],rC[2][2]); 
		  rC[3][2]=mad(rA[3],rB[2],rC[3][2]); 
		  rC[4][2]=mad(rA[4],rB[2],rC[4][2]); 
		  rC[5][2]=mad(rA[5],rB[2],rC[5][2]); 
		  rC[0][3]=mad(rA[0],rB[3],rC[0][3]); 
		  rC[1][3]=mad(rA[1],rB[3],rC[1][3]); 
		  rC[2][3]=mad(rA[2],rB[3],rC[2][3]); 
		  rC[3][3]=mad(rA[3],rB[3],rC[3][3]); 
		  rC[4][3]=mad(rA[4],rB[3],rC[4][3]); 
		  rC[5][3]=mad(rA[5],rB[3],rC[5][3]); 
		  rC[0][4]=mad(rA[0],rB[4],rC[0][4]); 
		  rC[1][4]=mad(rA[1],rB[4],rC[1][4]); 
		  rC[2][4]=mad(rA[2],rB[4],rC[2][4]); 
		  rC[3][4]=mad(rA[3],rB[4],rC[3][4]); 
		  rC[4][4]=mad(rA[4],rB[4],rC[4][4]); 
		  rC[5][4]=mad(rA[5],rB[4],rC[5][4]); 
		  rC[0][5]=mad(rA[0],rB[5],rC[0][5]); 
		  rC[1][5]=mad(rA[1],rB[5],rC[1][5]); 
		  rC[2][5]=mad(rA[2],rB[5],rC[2][5]); 
		  rC[3][5]=mad(rA[3],rB[5],rC[3][5]); 
		  rC[4][5]=mad(rA[4],rB[5],rC[4][5]); 
		  rC[5][5]=mad(rA[5],rB[5],rC[5][5]); 
		  barrier(CLK_LOCAL_MEM_FENCE);
		}


        A += lda << 3;
        B += 8;	
		block_k+=8;
    } while (block_k < K);



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



__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NN_1_48_1_8x8_6x6__ALPHABETA_SPLIT_ROW(__global double const * restrict A,
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
    A += offsetA;
    B += offsetB;
    C    += offsetC;


    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];

  __local double lA[392];
  __local double lB[392];

  int gidx = M/48;//get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  int CurrentOffSetA =   gidx*48 + idxT;
   
  A +=  gidx*48+ idxT + idyT*lda;
  B +=  gidy*48*ldb+ idx + idy*ldb;




    int block_k = 0;//K >> 3;
    do {

	    __local double* plA = lA + idyT*49 + idxT;
        __local double* plB = lB + idxT*49 + idyT;

        
        plB[0] = B[0+0*ldb];
        plB[8] = B[0+8*ldb];
        plB[16] = B[0+16*ldb];
        plB[24] = B[0+24*ldb];
        plB[32] = B[0+32*ldb];
        plB[40] = B[0+40*ldb];

		plA[0] = CurrentOffSetA>=M?0.0:A[0];
        plA[8] = CurrentOffSetA+8>=M?0.0:A[8];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[24] = CurrentOffSetA+24>=M?0.0:A[24];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[40] = CurrentOffSetA+40>=M?0.0:A[40];



        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx ;
        int offB = idy ;
	    #pragma unroll 1
        for(uint k = 0 ; k <min(8u, K-block_k ); k+=1)
        {
		  rA[0] = lA[offA + 0];               
		  rA[1] = lA[offA + 8];               
		  rA[2] = lA[offA + 16];              
		  rA[3] = lA[offA + 24];              
		  rA[4] = lA[offA + 32];              
		  rA[5] = lA[offA + 40];              
		  rB[0] = lB[offB + 0];               
		  rB[1] = lB[offB + 8];               
		  rB[2] = lB[offB + 16];              
		  rB[3] = lB[offB + 24];              
		  rB[4] = lB[offB + 32];              
		  rB[5] = lB[offB + 40];              
		  offA += 49;                         
		  offB += 49;                         
		  rC[0][0]=mad(rA[0],rB[0],rC[0][0]); 
		  rC[1][0]=mad(rA[1],rB[0],rC[1][0]); 
		  rC[2][0]=mad(rA[2],rB[0],rC[2][0]); 
		  rC[3][0]=mad(rA[3],rB[0],rC[3][0]); 
		  rC[4][0]=mad(rA[4],rB[0],rC[4][0]); 
		  rC[5][0]=mad(rA[5],rB[0],rC[5][0]); 
		  rC[0][1]=mad(rA[0],rB[1],rC[0][1]); 
		  rC[1][1]=mad(rA[1],rB[1],rC[1][1]); 
		  rC[2][1]=mad(rA[2],rB[1],rC[2][1]); 
		  rC[3][1]=mad(rA[3],rB[1],rC[3][1]); 
		  rC[4][1]=mad(rA[4],rB[1],rC[4][1]); 
		  rC[5][1]=mad(rA[5],rB[1],rC[5][1]); 
		  rC[0][2]=mad(rA[0],rB[2],rC[0][2]); 
		  rC[1][2]=mad(rA[1],rB[2],rC[1][2]); 
		  rC[2][2]=mad(rA[2],rB[2],rC[2][2]); 
		  rC[3][2]=mad(rA[3],rB[2],rC[3][2]); 
		  rC[4][2]=mad(rA[4],rB[2],rC[4][2]); 
		  rC[5][2]=mad(rA[5],rB[2],rC[5][2]); 
		  rC[0][3]=mad(rA[0],rB[3],rC[0][3]); 
		  rC[1][3]=mad(rA[1],rB[3],rC[1][3]); 
		  rC[2][3]=mad(rA[2],rB[3],rC[2][3]); 
		  rC[3][3]=mad(rA[3],rB[3],rC[3][3]); 
		  rC[4][3]=mad(rA[4],rB[3],rC[4][3]); 
		  rC[5][3]=mad(rA[5],rB[3],rC[5][3]); 
		  rC[0][4]=mad(rA[0],rB[4],rC[0][4]); 
		  rC[1][4]=mad(rA[1],rB[4],rC[1][4]); 
		  rC[2][4]=mad(rA[2],rB[4],rC[2][4]); 
		  rC[3][4]=mad(rA[3],rB[4],rC[3][4]); 
		  rC[4][4]=mad(rA[4],rB[4],rC[4][4]); 
		  rC[5][4]=mad(rA[5],rB[4],rC[5][4]); 
		  rC[0][5]=mad(rA[0],rB[5],rC[0][5]); 
		  rC[1][5]=mad(rA[1],rB[5],rC[1][5]); 
		  rC[2][5]=mad(rA[2],rB[5],rC[2][5]); 
		  rC[3][5]=mad(rA[3],rB[5],rC[3][5]); 
		  rC[4][5]=mad(rA[4],rB[5],rC[4][5]); 
		  rC[5][5]=mad(rA[5],rB[5],rC[5][5]); 
		  barrier(CLK_LOCAL_MEM_FENCE);
		}
        A += lda << 3;
        B += 8;
        block_k+=8;
    } while (block_k < K);



    int offset_x = gidx*48+ idx;
    int offset_y = gidy*48+ idy;
	

  if(offset_x>=M  )
    return;

  C+= offset_x+ldc*offset_y; 
 
 
  //for (int i=0; i<6; i++)
  int i = 0;
  do
  {
    C[0*ldc+i*8]  = alpha*rC[i][0] + beta*C[0*ldc+i*8];
	
      C[8*ldc+i*8]  = alpha*rC[i][1] + beta*C[8*ldc+i*8];
    
	  C[16*ldc+i*8] = alpha*rC[i][2] + beta*C[16*ldc+i*8];
    
	  C[24*ldc+i*8] = alpha*rC[i][3] + beta*C[24*ldc+i*8];
    
      C[32*ldc+i*8] = alpha*rC[i][4] + beta*C[32*ldc+i*8];
    
	  C[40*ldc+i*8] = alpha*rC[i][5] + beta*C[40*ldc+i*8];

	offset_x += 8;
    if(offset_x>=M)
        return;

  }while (++i < 6);
}

__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NN_48_1_1_8x8_6x6__ALPHABETA_SPLIT_COLUMN(__global double const * restrict A,
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
    A += offsetA;
    B += offsetB;
    C    += offsetC;


    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];

  __local double lA[392];
  __local double lB[392];

  int gidx = get_group_id(0);
  int gidy = N/48;//get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*48+ idxT + idyT*lda;
  B +=  gidy*48*ldb+ idx + idy*ldb;


  int CurrentOffSetB =   gidy*48 + idyT;

    int block_k = 0;//K >> 3;
    do {

	    __local double* plA = lA + idyT*49 + idxT;
        __local double* plB = lB + idxT*49 + idyT;

		plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[8]  = CurrentOffSetB+8>=N?0.0:B[0+8*ldb];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[0+16*ldb];
        plB[24] = CurrentOffSetB+24>=N?0.0:B[0+24*ldb];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[0+32*ldb];
        plB[40] = CurrentOffSetB+40>=N?0.0:B[0+40*ldb];

        plA[0] = A[0+0*lda];
        plA[8] = A[8+0*lda];
        plA[16] = A[16+0*lda];
        plA[24] = A[24+0*lda];
        plA[32] = A[32+0*lda];
        plA[40] = A[40+0*lda];
        

        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx ;
        int offB = idy ;
	    #pragma unroll 1
        for(uint k = 0 ; k <min(8u, K-block_k ); k+=1)
        {
		  rA[0] = lA[offA + 0];               
		  rA[1] = lA[offA + 8];               
		  rA[2] = lA[offA + 16];              
		  rA[3] = lA[offA + 24];              
		  rA[4] = lA[offA + 32];              
		  rA[5] = lA[offA + 40];              
		  rB[0] = lB[offB + 0];               
		  rB[1] = lB[offB + 8];               
		  rB[2] = lB[offB + 16];              
		  rB[3] = lB[offB + 24];              
		  rB[4] = lB[offB + 32];              
		  rB[5] = lB[offB + 40];              
		  offA += 49;                         
		  offB += 49;                         
		  rC[0][0]=mad(rA[0],rB[0],rC[0][0]); 
		  rC[1][0]=mad(rA[1],rB[0],rC[1][0]); 
		  rC[2][0]=mad(rA[2],rB[0],rC[2][0]); 
		  rC[3][0]=mad(rA[3],rB[0],rC[3][0]); 
		  rC[4][0]=mad(rA[4],rB[0],rC[4][0]); 
		  rC[5][0]=mad(rA[5],rB[0],rC[5][0]); 
		  rC[0][1]=mad(rA[0],rB[1],rC[0][1]); 
		  rC[1][1]=mad(rA[1],rB[1],rC[1][1]); 
		  rC[2][1]=mad(rA[2],rB[1],rC[2][1]); 
		  rC[3][1]=mad(rA[3],rB[1],rC[3][1]); 
		  rC[4][1]=mad(rA[4],rB[1],rC[4][1]); 
		  rC[5][1]=mad(rA[5],rB[1],rC[5][1]); 
		  rC[0][2]=mad(rA[0],rB[2],rC[0][2]); 
		  rC[1][2]=mad(rA[1],rB[2],rC[1][2]); 
		  rC[2][2]=mad(rA[2],rB[2],rC[2][2]); 
		  rC[3][2]=mad(rA[3],rB[2],rC[3][2]); 
		  rC[4][2]=mad(rA[4],rB[2],rC[4][2]); 
		  rC[5][2]=mad(rA[5],rB[2],rC[5][2]); 
		  rC[0][3]=mad(rA[0],rB[3],rC[0][3]); 
		  rC[1][3]=mad(rA[1],rB[3],rC[1][3]); 
		  rC[2][3]=mad(rA[2],rB[3],rC[2][3]); 
		  rC[3][3]=mad(rA[3],rB[3],rC[3][3]); 
		  rC[4][3]=mad(rA[4],rB[3],rC[4][3]); 
		  rC[5][3]=mad(rA[5],rB[3],rC[5][3]); 
		  rC[0][4]=mad(rA[0],rB[4],rC[0][4]); 
		  rC[1][4]=mad(rA[1],rB[4],rC[1][4]); 
		  rC[2][4]=mad(rA[2],rB[4],rC[2][4]); 
		  rC[3][4]=mad(rA[3],rB[4],rC[3][4]); 
		  rC[4][4]=mad(rA[4],rB[4],rC[4][4]); 
		  rC[5][4]=mad(rA[5],rB[4],rC[5][4]); 
		  rC[0][5]=mad(rA[0],rB[5],rC[0][5]); 
		  rC[1][5]=mad(rA[1],rB[5],rC[1][5]); 
		  rC[2][5]=mad(rA[2],rB[5],rC[2][5]); 
		  rC[3][5]=mad(rA[3],rB[5],rC[3][5]); 
		  rC[4][5]=mad(rA[4],rB[5],rC[4][5]); 
		  rC[5][5]=mad(rA[5],rB[5],rC[5][5]); 
		  barrier(CLK_LOCAL_MEM_FENCE);
		}
        A += lda << 3;
        B += 8;block_k+=8;
    } while (block_k < K);



    int offset_x = gidx*48+ idx;
    int offset_y = gidy*48+ idy;
	

  if( offset_y>=N )
    return;

  C+= offset_x+ldc*offset_y; 
 
 
  //for (int i=0; i<6; i++)
  int i = 0;
  do
  {
    C[0*ldc+i*8]  = alpha*rC[i][0] + beta*C[0*ldc+i*8];
	
	if (offset_y+8<N)
      C[8*ldc+i*8]  = alpha*rC[i][1] + beta*C[8*ldc+i*8];
    
	if (offset_y+16<N)
	  C[16*ldc+i*8] = alpha*rC[i][2] + beta*C[16*ldc+i*8];
    
	if (offset_y+24<N)
	  C[24*ldc+i*8] = alpha*rC[i][3] + beta*C[24*ldc+i*8];
    
	if (offset_y+32<N)
      C[32*ldc+i*8] = alpha*rC[i][4] + beta*C[32*ldc+i*8];
    
	if (offset_y+40<N)
	  C[40*ldc+i*8] = alpha*rC[i][5] + beta*C[40*ldc+i*8];



  }while (++i < 6);
}

__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NN_1_1_1_8x8_6x6__ALPHABETA_SPLIT_SINGLE(__global double const * restrict A,
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


    A += offsetA;
    B += offsetB;
    C    += offsetC;


    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];

  __local double lA[392];
  __local double lB[392];

  int gidx = M/48;//get_group_id(0);
  int gidy = N/48; //get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  int CurrentOffSetA =   gidx*48 + idxT;
  int CurrentOffSetB =   gidy*48 + idyT;

  A +=  gidx*48+ idxT + idyT*lda;
  B +=  gidy*48*ldb+ idx + idy*ldb;




    int block_k = 0;//K >> 3;
    do {

	    __local double* plA = lA + idyT*49 + idxT;
        __local double* plB = lB + idxT*49 + idyT;

        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[8]  = CurrentOffSetB+8>=N?0.0:B[0+8*ldb];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[0+16*ldb];
        plB[24] = CurrentOffSetB+24>=N?0.0:B[0+24*ldb];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[0+32*ldb];
        plB[40] = CurrentOffSetB+40>=N?0.0:B[0+40*ldb];


        plA[0] = CurrentOffSetA>=M?0.0:A[0];
        plA[8] = CurrentOffSetA+8>=M?0.0:A[8];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[24] = CurrentOffSetA+24>=M?0.0:A[24];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[40] = CurrentOffSetA+40>=M?0.0:A[40];


        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx ;
        int offB = idy ;
	    #pragma unroll 1
        for(uint k = 0 ; k <min(8u, K-block_k ); k+=1)
        {
		  rA[0] = lA[offA + 0];               
		  rA[1] = lA[offA + 8];               
		  rA[2] = lA[offA + 16];              
		  rA[3] = lA[offA + 24];              
		  rA[4] = lA[offA + 32];              
		  rA[5] = lA[offA + 40];              
		  rB[0] = lB[offB + 0];               
		  rB[1] = lB[offB + 8];               
		  rB[2] = lB[offB + 16];              
		  rB[3] = lB[offB + 24];              
		  rB[4] = lB[offB + 32];              
		  rB[5] = lB[offB + 40];              
		  offA += 49;                         
		  offB += 49;                         
		  rC[0][0]=mad(rA[0],rB[0],rC[0][0]); 
		  rC[1][0]=mad(rA[1],rB[0],rC[1][0]); 
		  rC[2][0]=mad(rA[2],rB[0],rC[2][0]); 
		  rC[3][0]=mad(rA[3],rB[0],rC[3][0]); 
		  rC[4][0]=mad(rA[4],rB[0],rC[4][0]); 
		  rC[5][0]=mad(rA[5],rB[0],rC[5][0]); 
		  rC[0][1]=mad(rA[0],rB[1],rC[0][1]); 
		  rC[1][1]=mad(rA[1],rB[1],rC[1][1]); 
		  rC[2][1]=mad(rA[2],rB[1],rC[2][1]); 
		  rC[3][1]=mad(rA[3],rB[1],rC[3][1]); 
		  rC[4][1]=mad(rA[4],rB[1],rC[4][1]); 
		  rC[5][1]=mad(rA[5],rB[1],rC[5][1]); 
		  rC[0][2]=mad(rA[0],rB[2],rC[0][2]); 
		  rC[1][2]=mad(rA[1],rB[2],rC[1][2]); 
		  rC[2][2]=mad(rA[2],rB[2],rC[2][2]); 
		  rC[3][2]=mad(rA[3],rB[2],rC[3][2]); 
		  rC[4][2]=mad(rA[4],rB[2],rC[4][2]); 
		  rC[5][2]=mad(rA[5],rB[2],rC[5][2]); 
		  rC[0][3]=mad(rA[0],rB[3],rC[0][3]); 
		  rC[1][3]=mad(rA[1],rB[3],rC[1][3]); 
		  rC[2][3]=mad(rA[2],rB[3],rC[2][3]); 
		  rC[3][3]=mad(rA[3],rB[3],rC[3][3]); 
		  rC[4][3]=mad(rA[4],rB[3],rC[4][3]); 
		  rC[5][3]=mad(rA[5],rB[3],rC[5][3]); 
		  rC[0][4]=mad(rA[0],rB[4],rC[0][4]); 
		  rC[1][4]=mad(rA[1],rB[4],rC[1][4]); 
		  rC[2][4]=mad(rA[2],rB[4],rC[2][4]); 
		  rC[3][4]=mad(rA[3],rB[4],rC[3][4]); 
		  rC[4][4]=mad(rA[4],rB[4],rC[4][4]); 
		  rC[5][4]=mad(rA[5],rB[4],rC[5][4]); 
		  rC[0][5]=mad(rA[0],rB[5],rC[0][5]); 
		  rC[1][5]=mad(rA[1],rB[5],rC[1][5]); 
		  rC[2][5]=mad(rA[2],rB[5],rC[2][5]); 
		  rC[3][5]=mad(rA[3],rB[5],rC[3][5]); 
		  rC[4][5]=mad(rA[4],rB[5],rC[4][5]); 
		  rC[5][5]=mad(rA[5],rB[5],rC[5][5]); 
		  barrier(CLK_LOCAL_MEM_FENCE);
		}
        A += lda << 3;
        B += 8;
        block_k+=8;
    } while (block_k < K);




    int offset_x = gidx*48+ idx;
    int offset_y = gidy*48+ idy;
	

  if(offset_x>=M || offset_y>=N )
    return;

  C+= offset_x+ldc*offset_y; 
 
 
  //for (int i=0; i<6; i++)
  int i = 0;
  do
  {
    C[0*ldc+i*8]  = alpha*rC[i][0] + beta*C[0*ldc+i*8];
	
	if (offset_y+8<N)
      C[8*ldc+i*8]  = alpha*rC[i][1] + beta*C[8*ldc+i*8];
    
	if (offset_y+16<N)
	  C[16*ldc+i*8] = alpha*rC[i][2] + beta*C[16*ldc+i*8];
    
	if (offset_y+24<N)
	  C[24*ldc+i*8] = alpha*rC[i][3] + beta*C[24*ldc+i*8];
    
	if (offset_y+32<N)
      C[32*ldc+i*8] = alpha*rC[i][4] + beta*C[32*ldc+i*8];
    
	if (offset_y+40<N)
	  C[40*ldc+i*8] = alpha*rC[i][5] + beta*C[40*ldc+i*8];

	offset_x += 8;
    if(offset_x>=M)
        return;


  }while (++i < 6);
}
";

static const char * dgemm_NN_1_SPLIT__ALPHA = "






__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NN_48_48_1_8x8_6x6__ALPHA_SPLIT_MAIN(__global double const * restrict A,
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


    A += offsetA;
    B += offsetB;
    C    += offsetC;


    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];

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




    int block_k = 0;//K >> 3;
    do {

	    __local double* plA = lA + idyT*49 + idxT;
        __local double* plB = lB + idxT*49 + idyT;

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
        int offA = idx ;
        int offB = idy ;
	    #pragma unroll 1
        for(uint k = 0 ; k <min(8u, K-block_k ); k+=1)
        {
		  rA[0] = lA[offA + 0];               
		  rA[1] = lA[offA + 8];               
		  rA[2] = lA[offA + 16];              
		  rA[3] = lA[offA + 24];              
		  rA[4] = lA[offA + 32];              
		  rA[5] = lA[offA + 40];              
		  rB[0] = lB[offB + 0];               
		  rB[1] = lB[offB + 8];               
		  rB[2] = lB[offB + 16];              
		  rB[3] = lB[offB + 24];              
		  rB[4] = lB[offB + 32];              
		  rB[5] = lB[offB + 40];              
		  offA += 49;                         
		  offB += 49;                         
		  rC[0][0]=mad(rA[0],rB[0],rC[0][0]); 
		  rC[1][0]=mad(rA[1],rB[0],rC[1][0]); 
		  rC[2][0]=mad(rA[2],rB[0],rC[2][0]); 
		  rC[3][0]=mad(rA[3],rB[0],rC[3][0]); 
		  rC[4][0]=mad(rA[4],rB[0],rC[4][0]); 
		  rC[5][0]=mad(rA[5],rB[0],rC[5][0]); 
		  rC[0][1]=mad(rA[0],rB[1],rC[0][1]); 
		  rC[1][1]=mad(rA[1],rB[1],rC[1][1]); 
		  rC[2][1]=mad(rA[2],rB[1],rC[2][1]); 
		  rC[3][1]=mad(rA[3],rB[1],rC[3][1]); 
		  rC[4][1]=mad(rA[4],rB[1],rC[4][1]); 
		  rC[5][1]=mad(rA[5],rB[1],rC[5][1]); 
		  rC[0][2]=mad(rA[0],rB[2],rC[0][2]); 
		  rC[1][2]=mad(rA[1],rB[2],rC[1][2]); 
		  rC[2][2]=mad(rA[2],rB[2],rC[2][2]); 
		  rC[3][2]=mad(rA[3],rB[2],rC[3][2]); 
		  rC[4][2]=mad(rA[4],rB[2],rC[4][2]); 
		  rC[5][2]=mad(rA[5],rB[2],rC[5][2]); 
		  rC[0][3]=mad(rA[0],rB[3],rC[0][3]); 
		  rC[1][3]=mad(rA[1],rB[3],rC[1][3]); 
		  rC[2][3]=mad(rA[2],rB[3],rC[2][3]); 
		  rC[3][3]=mad(rA[3],rB[3],rC[3][3]); 
		  rC[4][3]=mad(rA[4],rB[3],rC[4][3]); 
		  rC[5][3]=mad(rA[5],rB[3],rC[5][3]); 
		  rC[0][4]=mad(rA[0],rB[4],rC[0][4]); 
		  rC[1][4]=mad(rA[1],rB[4],rC[1][4]); 
		  rC[2][4]=mad(rA[2],rB[4],rC[2][4]); 
		  rC[3][4]=mad(rA[3],rB[4],rC[3][4]); 
		  rC[4][4]=mad(rA[4],rB[4],rC[4][4]); 
		  rC[5][4]=mad(rA[5],rB[4],rC[5][4]); 
		  rC[0][5]=mad(rA[0],rB[5],rC[0][5]); 
		  rC[1][5]=mad(rA[1],rB[5],rC[1][5]); 
		  rC[2][5]=mad(rA[2],rB[5],rC[2][5]); 
		  rC[3][5]=mad(rA[3],rB[5],rC[3][5]); 
		  rC[4][5]=mad(rA[4],rB[5],rC[4][5]); 
		  rC[5][5]=mad(rA[5],rB[5],rC[5][5]); 
		  barrier(CLK_LOCAL_MEM_FENCE);
		}
        A += lda << 3;
        B += 8;
        block_k+=8;
    } while (block_k < K);


  C+= gidx*48;
  C+= idx;
  C+= gidy*48*ldc;
  C+= idy*ldc;
 
  C[0*ldc] = alpha*rC[0][0]  ;
  C[8*ldc] = alpha*rC[0][1]  ;
  C[16*ldc] = alpha*rC[0][2] ;
  C[24*ldc] = alpha*rC[0][3] ;
  C[32*ldc] = alpha*rC[0][4] ;
  C[40*ldc] = alpha*rC[0][5] ;
  C+=8;						 ;
  C[0*ldc] = alpha*rC[1][0]  ;
  C[8*ldc] = alpha*rC[1][1]  ;
  C[16*ldc] = alpha*rC[1][2] ;
  C[24*ldc] = alpha*rC[1][3] ;
  C[32*ldc] = alpha*rC[1][4] ;
  C[40*ldc] = alpha*rC[1][5] ;
  C+=8;						 ;
  C[0*ldc] = alpha*rC[2][0]  ;
  C[8*ldc] = alpha*rC[2][1]  ;
  C[16*ldc] = alpha*rC[2][2] ;
  C[24*ldc] = alpha*rC[2][3] ;
  C[32*ldc] = alpha*rC[2][4] ;
  C[40*ldc] = alpha*rC[2][5] ;
  C+=8;						 ;
  C[0*ldc] = alpha*rC[3][0]  ;
  C[8*ldc] = alpha*rC[3][1]  ;
  C[16*ldc] = alpha*rC[3][2] ;
  C[24*ldc] = alpha*rC[3][3] ;
  C[32*ldc] = alpha*rC[3][4] ;
  C[40*ldc] = alpha*rC[3][5] ;
  C+=8;						 ;
  C[0*ldc] = alpha*rC[4][0]  ;
  C[8*ldc] = alpha*rC[4][1]  ;
  C[16*ldc] = alpha*rC[4][2] ;
  C[24*ldc] = alpha*rC[4][3] ;
  C[32*ldc] = alpha*rC[4][4] ;
  C[40*ldc] = alpha*rC[4][5] ;
  C+=8;						 ;
  C[0*ldc] = alpha*rC[5][0]  ;
  C[8*ldc] = alpha*rC[5][1]  ;
  C[16*ldc] = alpha*rC[5][2] ;
  C[24*ldc] = alpha*rC[5][3] ;
  C[32*ldc] = alpha*rC[5][4] ;
  C[40*ldc] = alpha*rC[5][5] ;
}


__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NN_1_48_1_8x8_6x6__ALPHA_SPLIT_ROW(__global double const * restrict A,
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

    A += offsetA;
    B += offsetB;
    C    += offsetC;


    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];

  __local double lA[392];
  __local double lB[392];

  int gidx = M/48;//get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  int CurrentOffSetA =   gidx*48 + idxT;

  A +=  gidx*48+ idxT + idyT*lda;
  B +=  gidy*48*ldb+ idx + idy*ldb;




    int block_k = 0;//K >> 3;
    do {

	    __local double* plA = lA + idyT*49 + idxT;
        __local double* plB = lB + idxT*49 + idyT;

        
        plB[0] = B[0+0*ldb];
        plB[8] = B[0+8*ldb];
        plB[16] = B[0+16*ldb];
        plB[24] = B[0+24*ldb];
        plB[32] = B[0+32*ldb];
        plB[40] = B[0+40*ldb];

		plA[0] = CurrentOffSetA>=M?0.0:A[0];
        plA[8] = CurrentOffSetA+8>=M?0.0:A[8];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[24] = CurrentOffSetA+24>=M?0.0:A[24];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[40] = CurrentOffSetA+40>=M?0.0:A[40];

        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx ;
        int offB = idy ;
	    #pragma unroll 1
        for(uint k = 0 ; k <min(8u, K-block_k ); k+=1)
        {
		  rA[0] = lA[offA + 0];               
		  rA[1] = lA[offA + 8];               
		  rA[2] = lA[offA + 16];              
		  rA[3] = lA[offA + 24];              
		  rA[4] = lA[offA + 32];              
		  rA[5] = lA[offA + 40];              
		  rB[0] = lB[offB + 0];               
		  rB[1] = lB[offB + 8];               
		  rB[2] = lB[offB + 16];              
		  rB[3] = lB[offB + 24];              
		  rB[4] = lB[offB + 32];              
		  rB[5] = lB[offB + 40];              
		  offA += 49;                         
		  offB += 49;                         
		  rC[0][0]=mad(rA[0],rB[0],rC[0][0]); 
		  rC[1][0]=mad(rA[1],rB[0],rC[1][0]); 
		  rC[2][0]=mad(rA[2],rB[0],rC[2][0]); 
		  rC[3][0]=mad(rA[3],rB[0],rC[3][0]); 
		  rC[4][0]=mad(rA[4],rB[0],rC[4][0]); 
		  rC[5][0]=mad(rA[5],rB[0],rC[5][0]); 
		  rC[0][1]=mad(rA[0],rB[1],rC[0][1]); 
		  rC[1][1]=mad(rA[1],rB[1],rC[1][1]); 
		  rC[2][1]=mad(rA[2],rB[1],rC[2][1]); 
		  rC[3][1]=mad(rA[3],rB[1],rC[3][1]); 
		  rC[4][1]=mad(rA[4],rB[1],rC[4][1]); 
		  rC[5][1]=mad(rA[5],rB[1],rC[5][1]); 
		  rC[0][2]=mad(rA[0],rB[2],rC[0][2]); 
		  rC[1][2]=mad(rA[1],rB[2],rC[1][2]); 
		  rC[2][2]=mad(rA[2],rB[2],rC[2][2]); 
		  rC[3][2]=mad(rA[3],rB[2],rC[3][2]); 
		  rC[4][2]=mad(rA[4],rB[2],rC[4][2]); 
		  rC[5][2]=mad(rA[5],rB[2],rC[5][2]); 
		  rC[0][3]=mad(rA[0],rB[3],rC[0][3]); 
		  rC[1][3]=mad(rA[1],rB[3],rC[1][3]); 
		  rC[2][3]=mad(rA[2],rB[3],rC[2][3]); 
		  rC[3][3]=mad(rA[3],rB[3],rC[3][3]); 
		  rC[4][3]=mad(rA[4],rB[3],rC[4][3]); 
		  rC[5][3]=mad(rA[5],rB[3],rC[5][3]); 
		  rC[0][4]=mad(rA[0],rB[4],rC[0][4]); 
		  rC[1][4]=mad(rA[1],rB[4],rC[1][4]); 
		  rC[2][4]=mad(rA[2],rB[4],rC[2][4]); 
		  rC[3][4]=mad(rA[3],rB[4],rC[3][4]); 
		  rC[4][4]=mad(rA[4],rB[4],rC[4][4]); 
		  rC[5][4]=mad(rA[5],rB[4],rC[5][4]); 
		  rC[0][5]=mad(rA[0],rB[5],rC[0][5]); 
		  rC[1][5]=mad(rA[1],rB[5],rC[1][5]); 
		  rC[2][5]=mad(rA[2],rB[5],rC[2][5]); 
		  rC[3][5]=mad(rA[3],rB[5],rC[3][5]); 
		  rC[4][5]=mad(rA[4],rB[5],rC[4][5]); 
		  rC[5][5]=mad(rA[5],rB[5],rC[5][5]); 
		  barrier(CLK_LOCAL_MEM_FENCE);
		}
        A += lda << 3;
        B += 8;block_k+=8;
    } while (block_k < K);


    int offset_x = gidx*48+ idx;
    int offset_y = gidy*48+ idy;
	

  if(offset_x>=M )
    return;

  C+= offset_x+ldc*offset_y; 
 
 
  //for (int i=0; i<6; i++)
  int i = 0;
  do
  {
    C[0*ldc+i*8]  = alpha*rC[i][0]  ;
	
      C[8*ldc+i*8]  = alpha*rC[i][1] ;
    
	  C[16*ldc+i*8] = alpha*rC[i][2] ;
    
	  C[24*ldc+i*8] = alpha*rC[i][3];
    
      C[32*ldc+i*8] = alpha*rC[i][4];
    
	  C[40*ldc+i*8] = alpha*rC[i][5];

	offset_x += 8;
    if(offset_x>=M)
        return;


  }while (++i < 6);
}



__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NN_48_1_1_8x8_6x6__ALPHA_SPLIT_COLUMN(__global double const * restrict A,
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
    A += offsetA;
    B += offsetB;
    C    += offsetC;


    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];
  __local double lA[392];
  __local double lB[392];


  int gidx = get_group_id(0);
  int gidy = N/48;//get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

   int CurrentOffSetB =   gidy*48 + idyT;

  A +=  gidx*48+ idxT + idyT*lda;
  B +=  gidy*48*ldb+ idx + idy*ldb;




    int block_k = 0;//K >> 3;
    do {

	    __local double* plA = lA + idyT*49 + idxT;
        __local double* plB = lB + idxT*49 + idyT;

		plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[8]  = CurrentOffSetB+8>=N?0.0:B[0+8*ldb];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[0+16*ldb];
        plB[24] = CurrentOffSetB+24>=N?0.0:B[0+24*ldb];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[0+32*ldb];
        plB[40] = CurrentOffSetB+40>=N?0.0:B[0+40*ldb];

        plA[0] = A[0+0*lda];
        plA[8] = A[8+0*lda];
        plA[16] = A[16+0*lda];
        plA[24] = A[24+0*lda];
        plA[32] = A[32+0*lda];
        plA[40] = A[40+0*lda];
        

        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx ;
        int offB = idy ;
	    #pragma unroll 1
        for(uint k = 0 ; k <min(8u, K-block_k ); k+=1)
        {
		  rA[0] = lA[offA + 0];               
		  rA[1] = lA[offA + 8];               
		  rA[2] = lA[offA + 16];              
		  rA[3] = lA[offA + 24];              
		  rA[4] = lA[offA + 32];              
		  rA[5] = lA[offA + 40];              
		  rB[0] = lB[offB + 0];               
		  rB[1] = lB[offB + 8];               
		  rB[2] = lB[offB + 16];              
		  rB[3] = lB[offB + 24];              
		  rB[4] = lB[offB + 32];              
		  rB[5] = lB[offB + 40];              
		  offA += 49;                         
		  offB += 49;                         
		  rC[0][0]=mad(rA[0],rB[0],rC[0][0]); 
		  rC[1][0]=mad(rA[1],rB[0],rC[1][0]); 
		  rC[2][0]=mad(rA[2],rB[0],rC[2][0]); 
		  rC[3][0]=mad(rA[3],rB[0],rC[3][0]); 
		  rC[4][0]=mad(rA[4],rB[0],rC[4][0]); 
		  rC[5][0]=mad(rA[5],rB[0],rC[5][0]); 
		  rC[0][1]=mad(rA[0],rB[1],rC[0][1]); 
		  rC[1][1]=mad(rA[1],rB[1],rC[1][1]); 
		  rC[2][1]=mad(rA[2],rB[1],rC[2][1]); 
		  rC[3][1]=mad(rA[3],rB[1],rC[3][1]); 
		  rC[4][1]=mad(rA[4],rB[1],rC[4][1]); 
		  rC[5][1]=mad(rA[5],rB[1],rC[5][1]); 
		  rC[0][2]=mad(rA[0],rB[2],rC[0][2]); 
		  rC[1][2]=mad(rA[1],rB[2],rC[1][2]); 
		  rC[2][2]=mad(rA[2],rB[2],rC[2][2]); 
		  rC[3][2]=mad(rA[3],rB[2],rC[3][2]); 
		  rC[4][2]=mad(rA[4],rB[2],rC[4][2]); 
		  rC[5][2]=mad(rA[5],rB[2],rC[5][2]); 
		  rC[0][3]=mad(rA[0],rB[3],rC[0][3]); 
		  rC[1][3]=mad(rA[1],rB[3],rC[1][3]); 
		  rC[2][3]=mad(rA[2],rB[3],rC[2][3]); 
		  rC[3][3]=mad(rA[3],rB[3],rC[3][3]); 
		  rC[4][3]=mad(rA[4],rB[3],rC[4][3]); 
		  rC[5][3]=mad(rA[5],rB[3],rC[5][3]); 
		  rC[0][4]=mad(rA[0],rB[4],rC[0][4]); 
		  rC[1][4]=mad(rA[1],rB[4],rC[1][4]); 
		  rC[2][4]=mad(rA[2],rB[4],rC[2][4]); 
		  rC[3][4]=mad(rA[3],rB[4],rC[3][4]); 
		  rC[4][4]=mad(rA[4],rB[4],rC[4][4]); 
		  rC[5][4]=mad(rA[5],rB[4],rC[5][4]); 
		  rC[0][5]=mad(rA[0],rB[5],rC[0][5]); 
		  rC[1][5]=mad(rA[1],rB[5],rC[1][5]); 
		  rC[2][5]=mad(rA[2],rB[5],rC[2][5]); 
		  rC[3][5]=mad(rA[3],rB[5],rC[3][5]); 
		  rC[4][5]=mad(rA[4],rB[5],rC[4][5]); 
		  rC[5][5]=mad(rA[5],rB[5],rC[5][5]); 
		  barrier(CLK_LOCAL_MEM_FENCE);
		}
        A += lda << 3;
        B += 8;block_k+=8;
    } while (block_k < K);



    int offset_x = gidx*48+ idx;
    int offset_y = gidy*48+ idy;
	

  if(offset_y>=N )
    return;

  C+= offset_x+ldc*offset_y; 
 
 
  //for (int i=0; i<6; i++)
  int i = 0;
  do
  {
    C[0*ldc+i*8]  = alpha*rC[i][0]  ;
	
	if (offset_y+8<N)
      C[8*ldc+i*8]  = alpha*rC[i][1] ;
    
	if (offset_y+16<N)
	  C[16*ldc+i*8] = alpha*rC[i][2] ;
    
	if (offset_y+24<N)
	  C[24*ldc+i*8] = alpha*rC[i][3];
    
	if (offset_y+32<N)
      C[32*ldc+i*8] = alpha*rC[i][4];
    
	if (offset_y+40<N)
	  C[40*ldc+i*8] = alpha*rC[i][5];



  }while (++i < 6);
}


__attribute__((reqd_work_group_size(8,8,1)))
__kernel void dgemm_NN_1_1_1_8x8_6x6__ALPHA_SPLIT_SINGLE(__global double const * restrict A,
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
    A += offsetA;
    B += offsetB;
    C    += offsetC;


    double rC[6][6] = {(double)0};
    double rA[6];
    double rB[6];

  __local double lA[392];
  __local double lB[392];
  
  int gidx = M/48;//get_group_id(0);
  int gidy = N/48;//get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  int CurrentOffSetA =   gidx*48 + idxT;
  int CurrentOffSetB =   gidy*48 + idyT;


  A +=  gidx*48+ idxT + idyT*lda;
  B +=  gidy*48*ldb+ idx + idy*ldb;




    int block_k = 0;//K >> 3;
    do {

	    __local double* plA = lA + idyT*49 + idxT;
        __local double* plB = lB + idxT*49 + idyT;

        
	    plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[8]  = CurrentOffSetB+8>=N?0.0:B[0+8*ldb];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[0+16*ldb];
        plB[24] = CurrentOffSetB+24>=N?0.0:B[0+24*ldb];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[0+32*ldb];
        plB[40] = CurrentOffSetB+40>=N?0.0:B[0+40*ldb];


        plA[0] = CurrentOffSetA>=M?0.0:A[0];
        plA[8] = CurrentOffSetA+8>=M?0.0:A[8];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[24] = CurrentOffSetA+24>=M?0.0:A[24];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[40] = CurrentOffSetA+40>=M?0.0:A[40];

        barrier(CLK_LOCAL_MEM_FENCE);
        int offA = idx ;
        int offB = idy ;
	    #pragma unroll 1
        for(uint k = 0 ; k <min(8u, K-block_k ); k+=1)
        {
		  rA[0] = lA[offA + 0];               
		  rA[1] = lA[offA + 8];               
		  rA[2] = lA[offA + 16];              
		  rA[3] = lA[offA + 24];              
		  rA[4] = lA[offA + 32];              
		  rA[5] = lA[offA + 40];              
		  rB[0] = lB[offB + 0];               
		  rB[1] = lB[offB + 8];               
		  rB[2] = lB[offB + 16];              
		  rB[3] = lB[offB + 24];              
		  rB[4] = lB[offB + 32];              
		  rB[5] = lB[offB + 40];              
		  offA += 49;                         
		  offB += 49;                         
		  rC[0][0]=mad(rA[0],rB[0],rC[0][0]); 
		  rC[1][0]=mad(rA[1],rB[0],rC[1][0]); 
		  rC[2][0]=mad(rA[2],rB[0],rC[2][0]); 
		  rC[3][0]=mad(rA[3],rB[0],rC[3][0]); 
		  rC[4][0]=mad(rA[4],rB[0],rC[4][0]); 
		  rC[5][0]=mad(rA[5],rB[0],rC[5][0]); 
		  rC[0][1]=mad(rA[0],rB[1],rC[0][1]); 
		  rC[1][1]=mad(rA[1],rB[1],rC[1][1]); 
		  rC[2][1]=mad(rA[2],rB[1],rC[2][1]); 
		  rC[3][1]=mad(rA[3],rB[1],rC[3][1]); 
		  rC[4][1]=mad(rA[4],rB[1],rC[4][1]); 
		  rC[5][1]=mad(rA[5],rB[1],rC[5][1]); 
		  rC[0][2]=mad(rA[0],rB[2],rC[0][2]); 
		  rC[1][2]=mad(rA[1],rB[2],rC[1][2]); 
		  rC[2][2]=mad(rA[2],rB[2],rC[2][2]); 
		  rC[3][2]=mad(rA[3],rB[2],rC[3][2]); 
		  rC[4][2]=mad(rA[4],rB[2],rC[4][2]); 
		  rC[5][2]=mad(rA[5],rB[2],rC[5][2]); 
		  rC[0][3]=mad(rA[0],rB[3],rC[0][3]); 
		  rC[1][3]=mad(rA[1],rB[3],rC[1][3]); 
		  rC[2][3]=mad(rA[2],rB[3],rC[2][3]); 
		  rC[3][3]=mad(rA[3],rB[3],rC[3][3]); 
		  rC[4][3]=mad(rA[4],rB[3],rC[4][3]); 
		  rC[5][3]=mad(rA[5],rB[3],rC[5][3]); 
		  rC[0][4]=mad(rA[0],rB[4],rC[0][4]); 
		  rC[1][4]=mad(rA[1],rB[4],rC[1][4]); 
		  rC[2][4]=mad(rA[2],rB[4],rC[2][4]); 
		  rC[3][4]=mad(rA[3],rB[4],rC[3][4]); 
		  rC[4][4]=mad(rA[4],rB[4],rC[4][4]); 
		  rC[5][4]=mad(rA[5],rB[4],rC[5][4]); 
		  rC[0][5]=mad(rA[0],rB[5],rC[0][5]); 
		  rC[1][5]=mad(rA[1],rB[5],rC[1][5]); 
		  rC[2][5]=mad(rA[2],rB[5],rC[2][5]); 
		  rC[3][5]=mad(rA[3],rB[5],rC[3][5]); 
		  rC[4][5]=mad(rA[4],rB[5],rC[4][5]); 
		  rC[5][5]=mad(rA[5],rB[5],rC[5][5]); 
		  barrier(CLK_LOCAL_MEM_FENCE);
		}
        A += lda << 3;
        B += 8;block_k+=8;
    } while (block_k < K);


    int offset_x = gidx*48+ idx;
    int offset_y = gidy*48+ idy;
	

  if(offset_x>=M ||offset_y>=N )
    return;

  C+= offset_x+ldc*offset_y; 
 
 
  //for (int i=0; i<6; i++)
  int i = 0;
  do
  {
    C[0*ldc+i*8]  = alpha*rC[i][0]  ;
	
	if (offset_y+8<N)
      C[8*ldc+i*8]  = alpha*rC[i][1] ;
    
	if (offset_y+16<N)
	  C[16*ldc+i*8] = alpha*rC[i][2] ;
    
	if (offset_y+24<N)
	  C[24*ldc+i*8] = alpha*rC[i][3];
    
	if (offset_y+32<N)
      C[32*ldc+i*8] = alpha*rC[i][4];
    
	if (offset_y+40<N)
	  C[40*ldc+i*8] = alpha*rC[i][5];

	offset_x += 8;
    if(offset_x>=M)
        return;


  }while (++i < 6);
}
";