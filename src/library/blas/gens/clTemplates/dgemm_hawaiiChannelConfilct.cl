static const char * dgemm_NT_ChannelConflict = "

typedef union GPtr {
    __global double *d;
    __global double2 *d2v;
    __global double4 *d4v;
    __global double8 *d8v;
    __global double16 *d16v;
} GPtr;



__attribute__((reqd_work_group_size(8, 8, 1)))
void __kernel
dgemmBlockTempLocalPrefetch(__global double2 const * restrict A,
                            __global double2 const * restrict B,
                            __global double2 * C,
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
    double2 a0     ;
    double b0[8], b1[8];
	double b0T, b1T;
    double2 c[8] = {(double2)(0,0)};
    int4 coord = 0; /* contains coordB, coordA, k */

    lda /= 2;
    ldb /= 2;
    
    int get_group_id_1;
    int get_global_id_1;
    A += (int)get_global_id(0);
    int lidY = get_local_id(1);
   
   
    get_group_id_1 = (get_group_id(0) + get_group_id(1))% get_num_groups(1);
    get_global_id_1 = get_group_id_1 * get_local_size(1) /*+ get_local_id(1)*/;

    //kif = (N % 256 != 0);
    //  get_global_id_1 = (kif*(uint)get_global_id(1)) + ((1-kif)*get_global_id_1);
   
  
   
    B += get_global_id_1 * 4 ;
	   
   
    coord.y = 2 * (int)get_global_id(0);
    coord.x = 8 * (get_global_id_1+lidY);

	GPtr uB;
	uB.d2v = B;

	local double blockB [128];
	
	int lid = get_local_id(0)+8*lidY; 

	
	blockB[lid] = uB.d[lid];
	blockB[lid+64] = uB.d[lid+2*ldb];
	barrier(CLK_LOCAL_MEM_FENCE);
	

    for (int k1 = 0; k1 < K; k1 += 2)
    {
        /* -- Tiles multiplier -- */

		///barrier(CLK_LOCAL_MEM_FENCE);
		
		uB.d2v += (ldb << 1);
		b0T = uB.d[lid];
		b1T = uB.d[lid+2*ldb];
		a0 = A[0];
		for (int i=0; i<8; i++)
		{
          b0[i] = blockB[i+8*lidY];
		  b1[i] = blockB[i+64+8*lidY];	
		}


        
		for (int i=0; i<8;i++)
		  c[i] = mad(a0, b0[i], c[i]);

        a0 = A[lda];

		for (int i=0; i<8;i++)
		  c[i] = mad(a0, b1[i], c[i]);


        A += (lda << 1);

		barrier(CLK_LOCAL_MEM_FENCE);
		blockB[lid] = b0T;
	    blockB[lid+64] = b1T;
		barrier(CLK_LOCAL_MEM_FENCE);
       // uB.d2v += (ldb << 1);
        /* ---------------------- */
    }

    GPtr uC;

    uC.d = C + (coord.x * ldc + coord.y)/2;

    __global double2 *pC = uC.d2v;

    double2 tempC0, tempC1, tempC2, tempC3, tempC4, tempC5, tempC6, tempC7;

    tempC0 = pC[0];
    tempC1 = pC[(ldc >> 1)];
    tempC2 = pC[ldc];
    tempC3 = pC[mad24(3u, (ldc >> 1), 0u)];
    tempC4 = pC[(ldc << 1)];
    tempC5 = pC[mad24(5u, (ldc >> 1), 0u)];
    tempC6 = pC[mad24(6u, (ldc >> 1), 0u)];
    tempC7 = pC[mad24(7u, (ldc >> 1), 0u)];
    tempC0 = mad(tempC0, beta, 0);
    tempC1 = mad(tempC1, beta, 0);
    tempC2 = mad(tempC2, beta, 0);
    tempC3 = mad(tempC3, beta, 0);
    tempC4 = mad(tempC4, beta, 0);
    tempC5 = mad(tempC5, beta, 0);
    tempC6 = mad(tempC6, beta, 0);
    tempC7 = mad(tempC7, beta, 0);
    tempC0 = mad(c[0], alpha, tempC0);
    tempC1 = mad(c[1], alpha, tempC1);
    tempC2 = mad(c[2], alpha, tempC2);
    tempC3 = mad(c[3], alpha, tempC3);
    tempC4 = mad(c[4], alpha, tempC4);
    tempC5 = mad(c[5], alpha, tempC5);
    tempC6 = mad(c[6], alpha, tempC6);
    tempC7 = mad(c[7], alpha, tempC7);
    pC[0] = tempC0;
    pC[(ldc >> 1)] = tempC1;
    pC[ldc] = tempC2;
    pC[mad24(3u, (ldc >> 1), 0u)] = tempC3;
    pC[(ldc << 1)] = tempC4;
    pC[mad24(5u, (ldc >> 1), 0u)] = tempC5;
    pC[mad24(6u, (ldc >> 1), 0u)] = tempC6;
    pC[mad24(7u, (ldc >> 1), 0u)] = tempC7;
}


";