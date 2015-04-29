static const char * sgemm_NT_16_SPLIT__ALPHABETA = "

#define  M6x6 \
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
			mem_fence(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NT_96_96_16_16x16_6x6__ALPHABETA_SPLIT_MAIN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    

    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);

    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96+ idx + idy*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
   // for(unsigned int block_k=0 ; block_k< K ; block_k+=16)
	//{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idy*97+idx;
        barrier(CLK_LOCAL_MEM_FENCE);
        plB[0] = B[0+0*ldb];
        plB[16] = B[16+0*ldb];
        plB[32] = B[32+0*ldb];
        plB[48] = B[48+0*ldb];
        plB[64] = B[64+0*ldb];
        plB[80] = B[80+0*ldb];
	   
	    plA[0] = A[0+0*lda];
        plA[16] = A[16+0*lda];
        plA[32] = A[32+0*lda];
        plA[48] = A[48+0*lda];
        plA[64] = A[64+0*lda];
        plA[80] = A[80+0*lda];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;

//        #pragma unroll 1
//        for(unsigned int k = 0 ; k < 16; k+=1){
//        }

        M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6

        A += lda<<4;
        B += ldb<<4;
    //}
	} while (--block_k > 0);

    C+= gidx*96+idx;
    C+= gidy*96*ldc;
    C+= idy*ldc;
    
	C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[0][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[0][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[0][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[0][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[0][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[1][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[1][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[1][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[1][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[1][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[2][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[2][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[2][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[2][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[2][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[3][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[3][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[3][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[3][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[3][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[4][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[4][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[4][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[4][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[4][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[4][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[5][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[5][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[5][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[5][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[5][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[5][5] + beta*C[80*ldc];
   
}


__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NT_1_96_16_16x16_6x6__ALPHABETA_SPLIT_ROW( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = M/96;//get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    

	int CurrentOffSetA = gidx*96+ idx;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96+ idx + idy*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idy*97+idx;
        barrier(CLK_LOCAL_MEM_FENCE);

        plB[0] = B[0+0*ldb];
        plB[16] = B[16+0*ldb];
        plB[32] = B[32+0*ldb];
        plB[48] = B[48+0*ldb];
        plB[64] = B[64+0*ldb];
        plB[80] = B[80+0*ldb];
	   
	    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[48] = CurrentOffSetA+48>=M?0.0:A[48];
        plA[64] = CurrentOffSetA+64>=M?0.0:A[64];
        plA[80] = CurrentOffSetA+80>=M?0.0:A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6

        A += lda<<4;
        B += ldb<<4;
	} while (--block_k > 0);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

	if(offset_x>=M )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = mad(alpha, rC[i][0], beta*C[0]);
      C[16*ldc] = mad(alpha, rC[i][1], beta*C[16*ldc]);
      C[32*ldc] = mad(alpha, rC[i][2], beta*C[32*ldc]);
      C[48*ldc] = mad(alpha, rC[i][3], beta*C[48*ldc]);
      C[64*ldc] = mad(alpha, rC[i][4], beta*C[64*ldc]);
      C[80*ldc] = mad(alpha, rC[i][5], beta*C[80*ldc]);
      C+=16;
	  offset_x+=16;
	  if(offset_x>=M )
        return;
	}
    while (++i < 6);
}





__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NT_96_1_16_16x16_6x6__ALPHABETA_SPLIT_COLUMN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = N/96;//get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
	int CurrentOffSetB = gidy*96+ idx;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96+ idx + idy*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idy*97+idx;
        barrier(CLK_LOCAL_MEM_FENCE);

        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[32];
        plB[48] = CurrentOffSetB+48>=N?0.0:B[48];
        plB[64] = CurrentOffSetB+64>=N?0.0:B[64];
        plB[80] = CurrentOffSetB+80>=N?0.0:B[80];
	   
	      plA[0]  = A[0];
        plA[16] = A[16];
        plA[32] = A[32];
        plA[48] = A[48];
        plA[64] = A[64];
        plA[80] = A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6
        M6x6

        A += lda<<4;
        B += ldb<<4;
	} while (--block_k > 0);


	int offset_x = gidx*96+idx;
  int offset_y = gidy*96+ idy;

	if(offset_y>=N )
      return;

  C+=offset_x+offset_y*ldc;
    
	int i = 0;
  do 
	{
	  C[0     ] = mad(alpha, rC[i][0], beta*C[0]);
	  if(offset_y+16<N)
        C[16*ldc] = mad(alpha, rC[i][1], beta*C[16*ldc]);
      if(offset_y+32<N)
        C[32*ldc] = mad(alpha, rC[i][2], beta*C[32*ldc]);
      if(offset_y+48<N)
        C[48*ldc] = mad(alpha, rC[i][3], beta*C[48*ldc]);
	  if(offset_y+64<N)
        C[64*ldc] = mad(alpha, rC[i][4], beta*C[64*ldc]);
	  if(offset_y+80<N)
        C[80*ldc] = mad(alpha, rC[i][5], beta*C[80*ldc]);
      
	  C+=16;
	    
	}
    while (++i < 6);
}

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NT_1_1_16_16x16_6x6__ALPHABETA_SPLIT_SINGLE( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = M/96;//get_group_id(0);
    uint gidy = N/96;//get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
	int CurrentOffSetA = gidx*96+ idx;
	int CurrentOffSetB = gidy*96+ idx;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96+ idx + idy*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idy*97+idx;
        barrier(CLK_LOCAL_MEM_FENCE);

        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[32];
        plB[48] = CurrentOffSetB+48>=N?0.0:B[48];
        plB[64] = CurrentOffSetB+64>=N?0.0:B[64];
        plB[80] = CurrentOffSetB+80>=N?0.0:B[80];
	   
	    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[48] = CurrentOffSetA+48>=M?0.0:A[48];
        plA[64] = CurrentOffSetA+64>=M?0.0:A[64];
        plA[80] = CurrentOffSetA+80>=M?0.0:A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6

        A += lda<<4;
        B += ldb<<4;
	} while (--block_k > 0);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

    if(offset_x>=M || offset_y>=N )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = mad(alpha, rC[i][0], beta*C[0]);
	  if(offset_y+16<N)
        C[16*ldc] = mad(alpha, rC[i][1], beta*C[16*ldc]);
      if(offset_y+32<N)
        C[32*ldc] = mad(alpha, rC[i][2], beta*C[32*ldc]);
      if(offset_y+48<N)
        C[48*ldc] = mad(alpha, rC[i][3], beta*C[48*ldc]);
	  if(offset_y+64<N)
        C[64*ldc] = mad(alpha, rC[i][4], beta*C[64*ldc]);
	  if(offset_y+80<N)
        C[80*ldc] = mad(alpha, rC[i][5], beta*C[80*ldc]);
      
	  C+=16;
	  offset_x+=16;
	  if(offset_x>=M )
        return;

	    
	}
    while (++i < 6);
}
";

static const char * sgemm_NT_16_SPLIT__ALPHA = "
#define  M6x6 \
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
			mem_fence(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NT_96_96_16_16x16_6x6__ALPHA_SPLIT_MAIN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    

    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);

    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96+ idx + idy*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
   // for(unsigned int block_k=0 ; block_k< K ; block_k+=16)
	//{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idy*97+idx;
        barrier(CLK_LOCAL_MEM_FENCE);
        plB[0] = B[0+0*ldb];
        plB[16] = B[16+0*ldb];
        plB[32] = B[32+0*ldb];
        plB[48] = B[48+0*ldb];
        plB[64] = B[64+0*ldb];
        plB[80] = B[80+0*ldb];
	   
	    plA[0] = A[0+0*lda];
        plA[16] = A[16+0*lda];
        plA[32] = A[32+0*lda];
        plA[48] = A[48+0*lda];
        plA[64] = A[64+0*lda];
        plA[80] = A[80+0*lda];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;

//        #pragma unroll 1
//        for(unsigned int k = 0 ; k < 16; k+=1){
//        }

        M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6

        A += lda<<4;
        B += ldb<<4;
    //}
	} while (--block_k > 0);

    C+= gidx*96+idx;
    C+= gidy*96*ldc;
    C+= idy*ldc;
    
	C[0*ldc] = alpha*rC[0][0]  ;
    C[16*ldc] = alpha*rC[0][1] ;
    C[32*ldc] = alpha*rC[0][2] ;
    C[48*ldc] = alpha*rC[0][3] ;
    C[64*ldc] = alpha*rC[0][4] ;
    C[80*ldc] = alpha*rC[0][5] ;
    C+=16;					   
    C[0*ldc] = alpha*rC[1][0]  ;
    C[16*ldc] = alpha*rC[1][1] ;
    C[32*ldc] = alpha*rC[1][2] ;
    C[48*ldc] = alpha*rC[1][3] ;
    C[64*ldc] = alpha*rC[1][4] ;
    C[80*ldc] = alpha*rC[1][5] ;
    C+=16;					   
    C[0*ldc] = alpha*rC[2][0]  ;
    C[16*ldc] = alpha*rC[2][1] ;
    C[32*ldc] = alpha*rC[2][2] ;
    C[48*ldc] = alpha*rC[2][3] ;
    C[64*ldc] = alpha*rC[2][4] ;
    C[80*ldc] = alpha*rC[2][5] ;
    C+=16;					   
    C[0*ldc] = alpha*rC[3][0]  ;
    C[16*ldc] = alpha*rC[3][1] ;
    C[32*ldc] = alpha*rC[3][2] ;
    C[48*ldc] = alpha*rC[3][3] ;
    C[64*ldc] = alpha*rC[3][4] ;
    C[80*ldc] = alpha*rC[3][5] ;
    C+=16;					   
    C[0*ldc] = alpha*rC[4][0]  ;
    C[16*ldc] = alpha*rC[4][1] ;
    C[32*ldc] = alpha*rC[4][2] ;
    C[48*ldc] = alpha*rC[4][3] ;
    C[64*ldc] = alpha*rC[4][4] ;
    C[80*ldc] = alpha*rC[4][5] ;
    C+=16;					   
    C[0*ldc] = alpha*rC[5][0]  ;
    C[16*ldc] = alpha*rC[5][1] ;
    C[32*ldc] = alpha*rC[5][2] ;
    C[48*ldc] = alpha*rC[5][3] ;
    C[64*ldc] = alpha*rC[5][4] ;
    C[80*ldc] = alpha*rC[5][5] ;
   
}


__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NT_1_96_16_16x16_6x6__ALPHA_SPLIT_ROW( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = M/96;//get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    

	int CurrentOffSetA = gidx*96+ idx;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96+ idx + idy*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idy*97+idx;
        barrier(CLK_LOCAL_MEM_FENCE);

        plB[0] = B[0+0*ldb];
        plB[16] = B[16+0*ldb];
        plB[32] = B[32+0*ldb];
        plB[48] = B[48+0*ldb];
        plB[64] = B[64+0*ldb];
        plB[80] = B[80+0*ldb];
	   
	    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[48] = CurrentOffSetA+48>=M?0.0:A[48];
        plA[64] = CurrentOffSetA+64>=M?0.0:A[64];
        plA[80] = CurrentOffSetA+80>=M?0.0:A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6

        A += lda<<4;
        B += ldb<<4;
	} while (--block_k > 0);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

	if(offset_x>=M )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = alpha * rC[i][0];
      C[16*ldc] = alpha * rC[i][1];
      C[32*ldc] = alpha * rC[i][2];
      C[48*ldc] = alpha * rC[i][3];
      C[64*ldc] = alpha * rC[i][4];
      C[80*ldc] = alpha * rC[i][5];
      C+=16;
	  offset_x+=16;
	  if(offset_x>=M )
        return;
	}
    while (++i < 6);
}





__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NT_96_1_16_16x16_6x6__ALPHA_SPLIT_COLUMN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = N/96;//get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
	int CurrentOffSetB = gidy*96+ idx;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96+ idx + idy*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idy*97+idx;
        barrier(CLK_LOCAL_MEM_FENCE);

        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[32];
        plB[48] = CurrentOffSetB+48>=N?0.0:B[48];
        plB[64] = CurrentOffSetB+64>=N?0.0:B[64];
        plB[80] = CurrentOffSetB+80>=N?0.0:B[80];
	   
	    plA[0]  = A[0];
        plA[16] = A[16];
        plA[32] = A[32];
        plA[48] = A[48];
        plA[64] = A[64];
        plA[80] = A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6

        A += lda<<4;
        B += ldb<<4;
	} while (--block_k > 0);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

	if(offset_y>=N )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = alpha * rC[i][0];
	  if(offset_y+16<N)
        C[16*ldc] = alpha * rC[i][1];
      if(offset_y+32<N)
        C[32*ldc] = alpha * rC[i][2];
      if(offset_y+48<N)
        C[48*ldc] = alpha * rC[i][3];
	  if(offset_y+64<N)
        C[64*ldc] = alpha * rC[i][4];
	  if(offset_y+80<N)
        C[80*ldc] = alpha * rC[i][5];
      
	  C+=16;
	    
	}
    while (++i < 6);
}

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NT_1_1_16_16x16_6x6__ALPHA_SPLIT_SINGLE( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = M/96;//get_group_id(0);
    uint gidy = N/96;//get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
	int CurrentOffSetA = gidx*96+ idx;
	int CurrentOffSetB = gidy*96+ idx;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96+ idx + idy*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idy*97+idx;
        barrier(CLK_LOCAL_MEM_FENCE);

        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[32];
        plB[48] = CurrentOffSetB+48>=N?0.0:B[48];
        plB[64] = CurrentOffSetB+64>=N?0.0:B[64];
        plB[80] = CurrentOffSetB+80>=N?0.0:B[80];
	   
	    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[48] = CurrentOffSetA+48>=M?0.0:A[48];
        plA[64] = CurrentOffSetA+64>=M?0.0:A[64];
        plA[80] = CurrentOffSetA+80>=M?0.0:A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6

        A += lda<<4;
        B += ldb<<4;
	} while (--block_k > 0);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

    if(offset_x>=M || offset_y>=N )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = alpha * rC[i][0];
	  if(offset_y+16<N)
        C[16*ldc] = alpha * rC[i][1];
      if(offset_y+32<N)
        C[32*ldc] = alpha * rC[i][2];
      if(offset_y+48<N)
        C[48*ldc] = alpha * rC[i][3];
	  if(offset_y+64<N)
        C[64*ldc] = alpha * rC[i][4];
	  if(offset_y+80<N)
        C[80*ldc] = alpha * rC[i][5];
      
	  C+=16;
	  offset_x+=16;
	  if(offset_x>=M )
        return;
	    
	}
    while (++i < 6);
}
";












/*********************************************************************************************************************/

static const char * sgemm_NT_1_SPLIT__ALPHABETA = "




__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NT_96_96_1_16x16_6x6__ALPHABETA_SPLIT_MAIN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    

    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);

    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96+ idx + idy*ldb;
    
   
    uint block_k = 0;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idy*97+idx;
       // barrier(CLK_LOCAL_MEM_FENCE);
        plB[0] = B[0+0*ldb];
        plB[16] = B[16+0*ldb];
        plB[32] = B[32+0*ldb];
        plB[48] = B[48+0*ldb];
        plB[64] = B[64+0*ldb];
        plB[80] = B[80+0*ldb];
	   
	    plA[0] = A[0+0*lda];
        plA[16] = A[16+0*lda];
        plA[32] = A[32+0*lda];
        plA[48] = A[48+0*lda];
        plA[64] = A[64+0*lda];
        plA[80] = A[80+0*lda];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;

        #pragma unroll 1
        for(unsigned int k = 0 ; k < min(16u, K-block_k ); k+=1)
	    {

	        rA[0][0] = lA[offA + 0];				  
            rA[0][1] = lA[offA + 16];				  
            rA[0][2] = lA[offA + 32];				  
            rA[0][3] = lA[offA + 48];				  
            rA[0][4] = lA[offA + 64];				  
            rA[0][5] = lA[offA + 80];				  
            rB[0][0] = lB[offB + 0];				  
            rB[0][1] = lB[offB + 16];				  
            rB[0][2] = lB[offB + 32];				  
            rB[0][3] = lB[offB + 48];				  
            rB[0][4] = lB[offB + 64];				  
            rB[0][5] = lB[offB + 80];				  
            offA += 97;								  
            offB += 97;								  
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
			barrier(CLK_LOCAL_MEM_FENCE);


        }



        A += lda<<4;
        B += ldb<<4;
        block_k+=16 ;
    } while (block_k < K);

    C+= gidx*96+idx;
    C+= gidy*96*ldc;
    C+= idy*ldc;
    
	C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[0][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[0][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[0][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[0][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[0][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[1][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[1][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[1][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[1][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[1][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[2][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[2][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[2][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[2][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[2][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[3][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[3][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[3][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[3][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[3][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[4][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[4][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[4][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[4][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[4][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[4][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[5][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[5][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[5][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[5][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[5][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[5][5] + beta*C[80*ldc];
   
}


__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NT_1_96_1_16x16_6x6__ALPHABETA_SPLIT_ROW( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = M/96;//get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    

	int CurrentOffSetA = gidx*96+ idx;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96+ idx + idy*ldb;
    
   
    uint block_k = 0;//= K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idy*97+idx;

        plB[0] = B[0+0*ldb];
        plB[16] = B[16+0*ldb];
        plB[32] = B[32+0*ldb];
        plB[48] = B[48+0*ldb];
        plB[64] = B[64+0*ldb];
        plB[80] = B[80+0*ldb];
	   
	    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[48] = CurrentOffSetA+48>=M?0.0:A[48];
        plA[64] = CurrentOffSetA+64>=M?0.0:A[64];
        plA[80] = CurrentOffSetA+80>=M?0.0:A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;

        #pragma unroll 1
        for(unsigned int k = 0 ; k < min(16u, K-block_k ); k+=1)
	    {

	        rA[0][0] = lA[offA + 0];				  
            rA[0][1] = lA[offA + 16];				  
            rA[0][2] = lA[offA + 32];				  
            rA[0][3] = lA[offA + 48];				  
            rA[0][4] = lA[offA + 64];				  
            rA[0][5] = lA[offA + 80];				  
            rB[0][0] = lB[offB + 0];				  
            rB[0][1] = lB[offB + 16];				  
            rB[0][2] = lB[offB + 32];				  
            rB[0][3] = lB[offB + 48];				  
            rB[0][4] = lB[offB + 64];				  
            rB[0][5] = lB[offB + 80];				  
            offA += 97;								  
            offB += 97;								  
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
			barrier(CLK_LOCAL_MEM_FENCE);


        }

        A += lda<<4;
        B += ldb<<4;
	    block_k+=16;
    } while (block_k < K);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

	if(offset_x>=M )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = mad(alpha, rC[i][0], beta*C[0]);
      C[16*ldc] = mad(alpha, rC[i][1], beta*C[16*ldc]);
      C[32*ldc] = mad(alpha, rC[i][2], beta*C[32*ldc]);
      C[48*ldc] = mad(alpha, rC[i][3], beta*C[48*ldc]);
      C[64*ldc] = mad(alpha, rC[i][4], beta*C[64*ldc]);
      C[80*ldc] = mad(alpha, rC[i][5], beta*C[80*ldc]);
      C+=16;
	  offset_x+=16;
	  if(offset_x>=M )
        return;
	}
    while (++i < 6);
}





__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NT_96_1_1_16x16_6x6__ALPHABETA_SPLIT_COLUMN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = N/96;//get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
	int CurrentOffSetB = gidy*96+ idx;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96+ idx + idy*ldb;
    
   
    uint block_k = 0;//K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idy*97+idx;

        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[32];
        plB[48] = CurrentOffSetB+48>=N?0.0:B[48];
        plB[64] = CurrentOffSetB+64>=N?0.0:B[64];
        plB[80] = CurrentOffSetB+80>=N?0.0:B[80];
	   
	    plA[0]  = A[0];
        plA[16] = A[16];
        plA[32] = A[32];
        plA[48] = A[48];
        plA[64] = A[64];
        plA[80] = A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        #pragma unroll 1
        for(unsigned int k = 0 ; k < min(16u, K-block_k ); k+=1)
	    {

	        rA[0][0] = lA[offA + 0];				  
            rA[0][1] = lA[offA + 16];				  
            rA[0][2] = lA[offA + 32];				  
            rA[0][3] = lA[offA + 48];				  
            rA[0][4] = lA[offA + 64];				  
            rA[0][5] = lA[offA + 80];				  
            rB[0][0] = lB[offB + 0];				  
            rB[0][1] = lB[offB + 16];				  
            rB[0][2] = lB[offB + 32];				  
            rB[0][3] = lB[offB + 48];				  
            rB[0][4] = lB[offB + 64];				  
            rB[0][5] = lB[offB + 80];				  
            offA += 97;								  
            offB += 97;								  
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
			barrier(CLK_LOCAL_MEM_FENCE);


        }
        A += lda<<4;
        B += ldb<<4;
	    block_k+=16;
    } while (block_k < K);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

	if(offset_y>=N )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = mad(alpha, rC[i][0], beta*C[0]);
	  if(offset_y+16<N)
        C[16*ldc] = mad(alpha, rC[i][1], beta*C[16*ldc]);
      if(offset_y+32<N)
        C[32*ldc] = mad(alpha, rC[i][2], beta*C[32*ldc]);
      if(offset_y+48<N)
        C[48*ldc] = mad(alpha, rC[i][3], beta*C[48*ldc]);
	  if(offset_y+64<N)
        C[64*ldc] = mad(alpha, rC[i][4], beta*C[64*ldc]);
	  if(offset_y+80<N)
        C[80*ldc] = mad(alpha, rC[i][5], beta*C[80*ldc]);
      
	  C+=16;
	    
	}
    while (++i < 6);
}

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NT_1_1_1_16x16_6x6__ALPHABETA_SPLIT_SINGLE( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = M/96;//get_group_id(0);
    uint gidy = N/96;//get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
	int CurrentOffSetA = gidx*96+ idx;
	int CurrentOffSetB = gidy*96+ idx;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96+ idx + idy*ldb;
    
   
    uint block_k = 0;//K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idy*97+idx;

        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[32];
        plB[48] = CurrentOffSetB+48>=N?0.0:B[48];
        plB[64] = CurrentOffSetB+64>=N?0.0:B[64];
        plB[80] = CurrentOffSetB+80>=N?0.0:B[80];
	   
	    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[48] = CurrentOffSetA+48>=M?0.0:A[48];
        plA[64] = CurrentOffSetA+64>=M?0.0:A[64];
        plA[80] = CurrentOffSetA+80>=M?0.0:A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        #pragma unroll 1
        for(unsigned int k = 0 ; k < min(16u, K-block_k ); k+=1)
	    {

	        rA[0][0] = lA[offA + 0];				  
            rA[0][1] = lA[offA + 16];				  
            rA[0][2] = lA[offA + 32];				  
            rA[0][3] = lA[offA + 48];				  
            rA[0][4] = lA[offA + 64];				  
            rA[0][5] = lA[offA + 80];				  
            rB[0][0] = lB[offB + 0];				  
            rB[0][1] = lB[offB + 16];				  
            rB[0][2] = lB[offB + 32];				  
            rB[0][3] = lB[offB + 48];				  
            rB[0][4] = lB[offB + 64];				  
            rB[0][5] = lB[offB + 80];				  
            offA += 97;								  
            offB += 97;								  
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
			barrier(CLK_LOCAL_MEM_FENCE);


        }

        A += lda<<4;
        B += ldb<<4;
        block_k+=16;
    } while (block_k < K);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

    if(offset_x>=M || offset_y>=N )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = mad(alpha, rC[i][0], beta*C[0]);
	  if(offset_y+16<N)
        C[16*ldc] = mad(alpha, rC[i][1], beta*C[16*ldc]);
      if(offset_y+32<N)
        C[32*ldc] = mad(alpha, rC[i][2], beta*C[32*ldc]);
      if(offset_y+48<N)
        C[48*ldc] = mad(alpha, rC[i][3], beta*C[48*ldc]);
	  if(offset_y+64<N)
        C[64*ldc] = mad(alpha, rC[i][4], beta*C[64*ldc]);
	  if(offset_y+80<N)
        C[80*ldc] = mad(alpha, rC[i][5], beta*C[80*ldc]);
      
	  C+=16;
	  offset_x+=16;
	  if(offset_x>=M )
        return;

	    
	}
    while (++i < 6);
}
";

static const char * sgemm_NT_1_SPLIT__ALPHA = "
#define  M6x6 \
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
			mem_fence(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NT_96_96_1_16x16_6x6__ALPHA_SPLIT_MAIN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    

    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);

    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96+ idx + idy*ldb;
    
   
    uint block_k =0;// K >> 4;
    do 
	{
   // for(unsigned int block_k=0 ; block_k< K ; block_k+=16)
	//{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idy*97+idx;
       // barrier(CLK_LOCAL_MEM_FENCE);
        plB[0] = B[0+0*ldb];
        plB[16] = B[16+0*ldb];
        plB[32] = B[32+0*ldb];
        plB[48] = B[48+0*ldb];
        plB[64] = B[64+0*ldb];
        plB[80] = B[80+0*ldb];
	   
	    plA[0] = A[0+0*lda];
        plA[16] = A[16+0*lda];
        plA[32] = A[32+0*lda];
        plA[48] = A[48+0*lda];
        plA[64] = A[64+0*lda];
        plA[80] = A[80+0*lda];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;

        #pragma unroll 1
        for(unsigned int k = 0 ; k < min(16u, K-block_k ); k+=1)
	    {

	        rA[0][0] = lA[offA + 0];				  
            rA[0][1] = lA[offA + 16];				  
            rA[0][2] = lA[offA + 32];				  
            rA[0][3] = lA[offA + 48];				  
            rA[0][4] = lA[offA + 64];				  
            rA[0][5] = lA[offA + 80];				  
            rB[0][0] = lB[offB + 0];				  
            rB[0][1] = lB[offB + 16];				  
            rB[0][2] = lB[offB + 32];				  
            rB[0][3] = lB[offB + 48];				  
            rB[0][4] = lB[offB + 64];				  
            rB[0][5] = lB[offB + 80];				  
            offA += 97;								  
            offB += 97;								  
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
			barrier(CLK_LOCAL_MEM_FENCE);


        }
        A += lda<<4;
        B += ldb<<4;
        block_k+=16;
    } while (block_k < K);

    C+= gidx*96+idx;
    C+= gidy*96*ldc;
    C+= idy*ldc;
    
	C[0*ldc] = alpha*rC[0][0]  ;
    C[16*ldc] = alpha*rC[0][1] ;
    C[32*ldc] = alpha*rC[0][2] ;
    C[48*ldc] = alpha*rC[0][3] ;
    C[64*ldc] = alpha*rC[0][4] ;
    C[80*ldc] = alpha*rC[0][5] ;
    C+=16;					   
    C[0*ldc] = alpha*rC[1][0]  ;
    C[16*ldc] = alpha*rC[1][1] ;
    C[32*ldc] = alpha*rC[1][2] ;
    C[48*ldc] = alpha*rC[1][3] ;
    C[64*ldc] = alpha*rC[1][4] ;
    C[80*ldc] = alpha*rC[1][5] ;
    C+=16;					   
    C[0*ldc] = alpha*rC[2][0]  ;
    C[16*ldc] = alpha*rC[2][1] ;
    C[32*ldc] = alpha*rC[2][2] ;
    C[48*ldc] = alpha*rC[2][3] ;
    C[64*ldc] = alpha*rC[2][4] ;
    C[80*ldc] = alpha*rC[2][5] ;
    C+=16;					   
    C[0*ldc] = alpha*rC[3][0]  ;
    C[16*ldc] = alpha*rC[3][1] ;
    C[32*ldc] = alpha*rC[3][2] ;
    C[48*ldc] = alpha*rC[3][3] ;
    C[64*ldc] = alpha*rC[3][4] ;
    C[80*ldc] = alpha*rC[3][5] ;
    C+=16;					   
    C[0*ldc] = alpha*rC[4][0]  ;
    C[16*ldc] = alpha*rC[4][1] ;
    C[32*ldc] = alpha*rC[4][2] ;
    C[48*ldc] = alpha*rC[4][3] ;
    C[64*ldc] = alpha*rC[4][4] ;
    C[80*ldc] = alpha*rC[4][5] ;
    C+=16;					   
    C[0*ldc] = alpha*rC[5][0]  ;
    C[16*ldc] = alpha*rC[5][1] ;
    C[32*ldc] = alpha*rC[5][2] ;
    C[48*ldc] = alpha*rC[5][3] ;
    C[64*ldc] = alpha*rC[5][4] ;
    C[80*ldc] = alpha*rC[5][5] ;
   
}


__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NT_1_96_1_16x16_6x6__ALPHA_SPLIT_ROW( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = M/96;//get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    

	int CurrentOffSetA = gidx*96+ idx;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96+ idx + idy*ldb;
    
   
    uint block_k = 0;//K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idy*97+idx;

        plB[0] = B[0+0*ldb];
        plB[16] = B[16+0*ldb];
        plB[32] = B[32+0*ldb];
        plB[48] = B[48+0*ldb];
        plB[64] = B[64+0*ldb];
        plB[80] = B[80+0*ldb];
	   
	    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[48] = CurrentOffSetA+48>=M?0.0:A[48];
        plA[64] = CurrentOffSetA+64>=M?0.0:A[64];
        plA[80] = CurrentOffSetA+80>=M?0.0:A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        #pragma unroll 1
        for(unsigned int k = 0 ; k < min(16u, K-block_k ); k+=1)
	    {

	        rA[0][0] = lA[offA + 0];				  
            rA[0][1] = lA[offA + 16];				  
            rA[0][2] = lA[offA + 32];				  
            rA[0][3] = lA[offA + 48];				  
            rA[0][4] = lA[offA + 64];				  
            rA[0][5] = lA[offA + 80];				  
            rB[0][0] = lB[offB + 0];				  
            rB[0][1] = lB[offB + 16];				  
            rB[0][2] = lB[offB + 32];				  
            rB[0][3] = lB[offB + 48];				  
            rB[0][4] = lB[offB + 64];				  
            rB[0][5] = lB[offB + 80];				  
            offA += 97;								  
            offB += 97;								  
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
			barrier(CLK_LOCAL_MEM_FENCE);


        }

        A += lda<<4;
        B += ldb<<4;
		block_k+=16;
    } while (block_k < K);



	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

	if(offset_x>=M )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = alpha * rC[i][0];
      C[16*ldc] = alpha * rC[i][1];
      C[32*ldc] = alpha * rC[i][2];
      C[48*ldc] = alpha * rC[i][3];
      C[64*ldc] = alpha * rC[i][4];
      C[80*ldc] = alpha * rC[i][5];
      C+=16;
	  offset_x+=16;
	  if(offset_x>=M )
        return;
	}
    while (++i < 6);
}





__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NT_96_1_1_16x16_6x6__ALPHA_SPLIT_COLUMN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = N/96;//get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
	int CurrentOffSetB = gidy*96+ idx;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96+ idx + idy*ldb;
    
   
    uint block_k = 0;//K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idy*97+idx;

        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[32];
        plB[48] = CurrentOffSetB+48>=N?0.0:B[48];
        plB[64] = CurrentOffSetB+64>=N?0.0:B[64];
        plB[80] = CurrentOffSetB+80>=N?0.0:B[80];
	   
	    plA[0]  = A[0];
        plA[16] = A[16];
        plA[32] = A[32];
        plA[48] = A[48];
        plA[64] = A[64];
        plA[80] = A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        #pragma unroll 1
        for(unsigned int k = 0 ; k < min(16u, K-block_k ); k+=1)
	    {

	        rA[0][0] = lA[offA + 0];				  
            rA[0][1] = lA[offA + 16];				  
            rA[0][2] = lA[offA + 32];				  
            rA[0][3] = lA[offA + 48];				  
            rA[0][4] = lA[offA + 64];				  
            rA[0][5] = lA[offA + 80];				  
            rB[0][0] = lB[offB + 0];				  
            rB[0][1] = lB[offB + 16];				  
            rB[0][2] = lB[offB + 32];				  
            rB[0][3] = lB[offB + 48];				  
            rB[0][4] = lB[offB + 64];				  
            rB[0][5] = lB[offB + 80];				  
            offA += 97;								  
            offB += 97;								  
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
			barrier(CLK_LOCAL_MEM_FENCE);


        }
        A += lda<<4;
        B += ldb<<4;
        block_k+=16;
    } while (block_k < K);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

	if(offset_y>=N )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = alpha * rC[i][0];
	  if(offset_y+16<N)
        C[16*ldc] = alpha * rC[i][1];
      if(offset_y+32<N)
        C[32*ldc] = alpha * rC[i][2];
      if(offset_y+48<N)
        C[48*ldc] = alpha * rC[i][3];
	  if(offset_y+64<N)
        C[64*ldc] = alpha * rC[i][4];
	  if(offset_y+80<N)
        C[80*ldc] = alpha * rC[i][5];
      
	  C+=16;
	    
	}
    while (++i < 6);
}

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NT_1_1_1_16x16_6x6__ALPHA_SPLIT_SINGLE( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = M/96;//get_group_id(0);
    uint gidy = N/96;//get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
	int CurrentOffSetA = gidx*96+ idx;
	int CurrentOffSetB = gidy*96+ idx;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96+ idx + idy*ldb;
    
   
    uint block_k = 0;// K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idy*97+idx;

        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[32];
        plB[48] = CurrentOffSetB+48>=N?0.0:B[48];
        plB[64] = CurrentOffSetB+64>=N?0.0:B[64];
        plB[80] = CurrentOffSetB+80>=N?0.0:B[80];
	   
	    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[48] = CurrentOffSetA+48>=M?0.0:A[48];
        plA[64] = CurrentOffSetA+64>=M?0.0:A[64];
        plA[80] = CurrentOffSetA+80>=M?0.0:A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        #pragma unroll 1
        for(unsigned int k = 0 ; k < min(16u, K-block_k ); k+=1)
	    {

	        rA[0][0] = lA[offA + 0];				  
            rA[0][1] = lA[offA + 16];				  
            rA[0][2] = lA[offA + 32];				  
            rA[0][3] = lA[offA + 48];				  
            rA[0][4] = lA[offA + 64];				  
            rA[0][5] = lA[offA + 80];				  
            rB[0][0] = lB[offB + 0];				  
            rB[0][1] = lB[offB + 16];				  
            rB[0][2] = lB[offB + 32];				  
            rB[0][3] = lB[offB + 48];				  
            rB[0][4] = lB[offB + 64];				  
            rB[0][5] = lB[offB + 80];				  
            offA += 97;								  
            offB += 97;								  
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
			barrier(CLK_LOCAL_MEM_FENCE);


        }
        A += lda<<4;
        B += ldb<<4;
		block_k+=16;
    } while (block_k < K);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

    if(offset_x>=M || offset_y>=N )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = alpha * rC[i][0];
	  if(offset_y+16<N)
        C[16*ldc] = alpha * rC[i][1];
      if(offset_y+32<N)
        C[32*ldc] = alpha * rC[i][2];
      if(offset_y+48<N)
        C[48*ldc] = alpha * rC[i][3];
	  if(offset_y+64<N)
        C[64*ldc] = alpha * rC[i][4];
	  if(offset_y+80<N)
        C[80*ldc] = alpha * rC[i][5];
      
	  C+=16;
	  offset_x+=16;
	  if(offset_x>=M )
        return;
	    
	}
    while (++i < 6);
}
";



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char * sgemm_NN_16_SPLIT__ALPHABETA = "

#define  M6x6 \
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
			mem_fence(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NN_96_96_16_16x16_6x6__ALPHABETA_SPLIT_MAIN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    

    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);

    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96*ldb+ idx + idy*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idx*97+idy;
		barrier(CLK_LOCAL_MEM_FENCE);
        plB[0] = B[0];
        plB[16] = B[16*ldb];
        plB[32] = B[32*ldb];
        plB[48] = B[48*ldb];
        plB[64] = B[64*ldb];
        plB[80] = B[80*ldb];
	   
	      plA[0] = A[0+0*lda];
        plA[16] = A[16+0*lda];
        plA[32] = A[32+0*lda];
        plA[48] = A[48+0*lda];
        plA[64] = A[64+0*lda];
        plA[80] = A[80+0*lda];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;

        M6x6
	      M6x6
	      M6x6
	      M6x6
	      M6x6
	      M6x6
	      M6x6
	      M6x6
	      M6x6
	      M6x6
	      M6x6
	      M6x6
	      M6x6
	      M6x6
	      M6x6
	      M6x6

        A += lda<<4;
        B += 16;
    //}
	} while (--block_k > 0);

    C+= gidx*96+idx;
    C+= gidy*96*ldc;
    C+= idy*ldc;
    
	C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[0][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[0][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[0][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[0][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[0][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[1][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[1][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[1][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[1][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[1][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[2][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[2][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[2][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[2][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[2][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[3][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[3][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[3][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[3][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[3][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[4][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[4][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[4][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[4][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[4][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[4][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[5][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[5][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[5][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[5][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[5][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[5][5] + beta*C[80*ldc];
   
}


__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NN_1_96_16_16x16_6x6__ALPHABETA_SPLIT_ROW( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = M/96;//get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    

   int CurrentOffSetA = gidx*96+ idx;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96*ldb+ idx + idy*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idx*97+idy;
        barrier(CLK_LOCAL_MEM_FENCE);

        plB[0] = B[0];
        plB[16] = B[16*ldb];
        plB[32] = B[32*ldb];
        plB[48] = B[48*ldb];
        plB[64] = B[64*ldb];
        plB[80] = B[80*ldb];
	   
	      plA[0]  = CurrentOffSetA>=M?0.0:A[0];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[48] = CurrentOffSetA+48>=M?0.0:A[48];
        plA[64] = CurrentOffSetA+64>=M?0.0:A[64];
        plA[80] = CurrentOffSetA+80>=M?0.0:A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6

        A += lda<<4;
        B += 16;
	} while (--block_k > 0);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

	if(offset_x>=M )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = mad(alpha, rC[i][0], beta*C[0]);
      C[16*ldc] = mad(alpha, rC[i][1], beta*C[16*ldc]);
      C[32*ldc] = mad(alpha, rC[i][2], beta*C[32*ldc]);
      C[48*ldc] = mad(alpha, rC[i][3], beta*C[48*ldc]);
      C[64*ldc] = mad(alpha, rC[i][4], beta*C[64*ldc]);
      C[80*ldc] = mad(alpha, rC[i][5], beta*C[80*ldc]);
      C+=16;
	  offset_x+=16;
	  if(offset_x>=M )
        return;
	}
    while (++i < 6);
}





__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NN_96_1_16_16x16_6x6__ALPHABETA_SPLIT_COLUMN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = N/96;//get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
    int CurrentOffSetB = gidy*96+ idy;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96*ldb+ idx + idy*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idx*97+idy;
        barrier(CLK_LOCAL_MEM_FENCE);

        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[32*ldb];
        plB[48] = CurrentOffSetB+48>=N?0.0:B[48*ldb];
        plB[64] = CurrentOffSetB+64>=N?0.0:B[64*ldb];
        plB[80] = CurrentOffSetB+80>=N?0.0:B[80*ldb];
	   
	    plA[0]  = A[0];
        plA[16] = A[16];
        plA[32] = A[32];
        plA[48] = A[48];
        plA[64] = A[64];
        plA[80] = A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6

        A += lda<<4;
        B += 16;
	} while (--block_k > 0);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

	if(offset_y>=N )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = mad(alpha, rC[i][0], beta*C[0]);
	  if(offset_y+16<N)
        C[16*ldc] = mad(alpha, rC[i][1], beta*C[16*ldc]);
      if(offset_y+32<N)
        C[32*ldc] = mad(alpha, rC[i][2], beta*C[32*ldc]);
      if(offset_y+48<N)
        C[48*ldc] = mad(alpha, rC[i][3], beta*C[48*ldc]);
	  if(offset_y+64<N)
        C[64*ldc] = mad(alpha, rC[i][4], beta*C[64*ldc]);
	  if(offset_y+80<N)
        C[80*ldc] = mad(alpha, rC[i][5], beta*C[80*ldc]);
      
	  C+=16;
	    
	}
    while (++i < 6);
}

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NN_1_1_16_16x16_6x6__ALPHABETA_SPLIT_SINGLE( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = M/96;//get_group_id(0);
    uint gidy = N/96;//get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
	int CurrentOffSetA = gidx*96+ idx;
	int CurrentOffSetB = gidy*96+ idy;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96*ldb+ idx + idy*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idx*97+idy;
        barrier(CLK_LOCAL_MEM_FENCE);

        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[32*ldb];
        plB[48] = CurrentOffSetB+48>=N?0.0:B[48*ldb];
        plB[64] = CurrentOffSetB+64>=N?0.0:B[64*ldb];
        plB[80] = CurrentOffSetB+80>=N?0.0:B[80*ldb];
	   
	    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[48] = CurrentOffSetA+48>=M?0.0:A[48];
        plA[64] = CurrentOffSetA+64>=M?0.0:A[64];
        plA[80] = CurrentOffSetA+80>=M?0.0:A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6

        A += lda<<4;
        B += 16;
	} while (--block_k > 0);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

    if(offset_x>=M || offset_y>=N )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = mad(alpha, rC[i][0], beta*C[0]);
	  if(offset_y+16<N)
        C[16*ldc] = mad(alpha, rC[i][1], beta*C[16*ldc]);
      if(offset_y+32<N)
        C[32*ldc] = mad(alpha, rC[i][2], beta*C[32*ldc]);
      if(offset_y+48<N)
        C[48*ldc] = mad(alpha, rC[i][3], beta*C[48*ldc]);
	  if(offset_y+64<N)
        C[64*ldc] = mad(alpha, rC[i][4], beta*C[64*ldc]);
	  if(offset_y+80<N)
        C[80*ldc] = mad(alpha, rC[i][5], beta*C[80*ldc]);
      
	  C+=16;
	  offset_x+=16;
	  if(offset_x>=M )
        return;

	    
	}
    while (++i < 6);
}
";



static const char * sgemm_NN_16_SPLIT__ALPHA = "

#define  M6x6 \
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
			mem_fence(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NN_96_96_16_16x16_6x6__ALPHA_SPLIT_MAIN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    

    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);

    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96*ldb+ idx + idy*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
   // for(unsigned int block_k=0 ; block_k< K ; block_k+=16)
	//{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idx*97+idy;
        barrier(CLK_LOCAL_MEM_FENCE);
        plB[0] = B[0];
        plB[16] = B[16*ldb];
        plB[32] = B[32*ldb];
        plB[48] = B[48*ldb];
        plB[64] = B[64*ldb];
        plB[80] = B[80*ldb];
	   
	    plA[0] = A[0+0*lda];
        plA[16] = A[16+0*lda];
        plA[32] = A[32+0*lda];
        plA[48] = A[48+0*lda];
        plA[64] = A[64+0*lda];
        plA[80] = A[80+0*lda];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;

//        #pragma unroll 1
//        for(unsigned int k = 0 ; k < 16; k+=1){
//        }

        M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6

        A += lda<<4;
        B += 16;
    //}
	} while (--block_k > 0);

    C+= gidx*96+idx;
    C+= gidy*96*ldc;
    C+= idy*ldc;
    
	C[0*ldc] = alpha*rC[0][0] ;
    C[16*ldc] = alpha*rC[0][1];
    C[32*ldc] = alpha*rC[0][2];
    C[48*ldc] = alpha*rC[0][3];
    C[64*ldc] = alpha*rC[0][4];
    C[80*ldc] = alpha*rC[0][5];
    C+=16;					  ;
    C[0*ldc] = alpha*rC[1][0] ;
    C[16*ldc] = alpha*rC[1][1];
    C[32*ldc] = alpha*rC[1][2];
    C[48*ldc] = alpha*rC[1][3];
    C[64*ldc] = alpha*rC[1][4];
    C[80*ldc] = alpha*rC[1][5];
    C+=16;					  ;
    C[0*ldc] = alpha*rC[2][0] ;
    C[16*ldc] = alpha*rC[2][1];
    C[32*ldc] = alpha*rC[2][2];
    C[48*ldc] = alpha*rC[2][3];
    C[64*ldc] = alpha*rC[2][4];
    C[80*ldc] = alpha*rC[2][5];
    C+=16;					  ;
    C[0*ldc] = alpha*rC[3][0] ;
    C[16*ldc] = alpha*rC[3][1];
    C[32*ldc] = alpha*rC[3][2];
    C[48*ldc] = alpha*rC[3][3];
    C[64*ldc] = alpha*rC[3][4];
    C[80*ldc] = alpha*rC[3][5];
    C+=16;					  ;
    C[0*ldc] = alpha*rC[4][0] ;
    C[16*ldc] = alpha*rC[4][1];
    C[32*ldc] = alpha*rC[4][2];
    C[48*ldc] = alpha*rC[4][3];
    C[64*ldc] = alpha*rC[4][4];
    C[80*ldc] = alpha*rC[4][5];
    C+=16;					  ;
    C[0*ldc] = alpha*rC[5][0] ;
    C[16*ldc] = alpha*rC[5][1];
    C[32*ldc] = alpha*rC[5][2];
    C[48*ldc] = alpha*rC[5][3];
    C[64*ldc] = alpha*rC[5][4];
    C[80*ldc] = alpha*rC[5][5];
   
}


__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NN_1_96_16_16x16_6x6__ALPHA_SPLIT_ROW( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = M/96;//get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    

	int CurrentOffSetA = gidx*96+ idx;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96*ldb+ idx + idy*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idx*97+idy;
        barrier(CLK_LOCAL_MEM_FENCE);
		
        plB[0] = B[0];
        plB[16] = B[16*ldb];
        plB[32] = B[32*ldb];
        plB[48] = B[48*ldb];
        plB[64] = B[64*ldb];
        plB[80] = B[80*ldb];
	   
	    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[48] = CurrentOffSetA+48>=M?0.0:A[48];
        plA[64] = CurrentOffSetA+64>=M?0.0:A[64];
        plA[80] = CurrentOffSetA+80>=M?0.0:A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6

        A += lda<<4;
        B += 16;
	} while (--block_k > 0);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

	if(offset_x>=M )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = alpha * rC[i][0];
      C[16*ldc] = alpha * rC[i][1];
      C[32*ldc] = alpha * rC[i][2];
      C[48*ldc] = alpha * rC[i][3];
      C[64*ldc] = alpha * rC[i][4];
      C[80*ldc] = alpha * rC[i][5];
      C+=16;
	  offset_x+=16;
	  if(offset_x>=M )
        return;
	}
    while (++i < 6);
}





__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NN_96_1_16_16x16_6x6__ALPHA_SPLIT_COLUMN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = N/96;//get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
	int CurrentOffSetB = gidy*96+ idy;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96*ldb+ idx + idy*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idx*97+idy;
        barrier(CLK_LOCAL_MEM_FENCE);

        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[32*ldb];
        plB[48] = CurrentOffSetB+48>=N?0.0:B[48*ldb];
        plB[64] = CurrentOffSetB+64>=N?0.0:B[64*ldb];
        plB[80] = CurrentOffSetB+80>=N?0.0:B[80*ldb];
	   
	    plA[0]  = A[0];
        plA[16] = A[16];
        plA[32] = A[32];
        plA[48] = A[48];
        plA[64] = A[64];
        plA[80] = A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6

        A += lda<<4;
        B += 16;
	} while (--block_k > 0);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

	if(offset_y>=N )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = alpha * rC[i][0] ;
	  if(offset_y+16<N)
        C[16*ldc] = alpha * rC[i][1];
      if(offset_y+32<N)
        C[32*ldc] = alpha * rC[i][2];
      if(offset_y+48<N)
        C[48*ldc] = alpha * rC[i][3];
	  if(offset_y+64<N)
        C[64*ldc] = alpha * rC[i][4];
	  if(offset_y+80<N)
        C[80*ldc] = alpha * rC[i][5];
      
	  C+=16;
	    
	}
    while (++i < 6);
}

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NN_1_1_16_16x16_6x6__ALPHA_SPLIT_SINGLE( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = M/96;//get_group_id(0);
    uint gidy = N/96;//get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
	int CurrentOffSetA = gidx*96+ idx;
	int CurrentOffSetB = gidy*96+ idy;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96*ldb+ idx + idy*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idx*97+idy;
        barrier(CLK_LOCAL_MEM_FENCE);
		
        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[32*ldb];
        plB[48] = CurrentOffSetB+48>=N?0.0:B[48*ldb];
        plB[64] = CurrentOffSetB+64>=N?0.0:B[64*ldb];
        plB[80] = CurrentOffSetB+80>=N?0.0:B[80*ldb];
	   
	    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[48] = CurrentOffSetA+48>=M?0.0:A[48];
        plA[64] = CurrentOffSetA+64>=M?0.0:A[64];
        plA[80] = CurrentOffSetA+80>=M?0.0:A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6
		M6x6

        A += lda<<4;
        B += 16;
	} while (--block_k > 0);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

    if(offset_x>=M || offset_y>=N )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = alpha * rC[i][0] ;
	  if(offset_y+16<N)				   
        C[16*ldc] = alpha * rC[i][1];
      if(offset_y+32<N)		 	    
        C[32*ldc] = alpha * rC[i][2];
      if(offset_y+48<N)		 	    
        C[48*ldc] = alpha * rC[i][3];
	  if(offset_y+64<N)		 	    
        C[64*ldc] = alpha * rC[i][4];
	  if(offset_y+80<N)		    
        C[80*ldc] = alpha * rC[i][5];
      
	  C+=16;
	  offset_x+=16;
	  if(offset_x>=M )
        return;

	    
	}
    while (++i < 6);
}
";
























static const char * sgemm_NN_1_SPLIT__ALPHABETA = "

#define  M6x6 \
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
			mem_fence(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NN_96_96_1_16x16_6x6__ALPHABETA_SPLIT_MAIN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    

    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);

    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96*ldb+ idx + idy*ldb;
    
   
    int block_k = 0;//K >> 4
    do 
	{
   // for(unsigned int block_k=0 ; block_k< K ; block_k+=16)
	//{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idx*97+idy;
       // barrier(CLK_LOCAL_MEM_FENCE);
        plB[0] = B[0];
        plB[16] = B[16*ldb];
        plB[32] = B[32*ldb];
        plB[48] = B[48*ldb];
        plB[64] = B[64*ldb];
        plB[80] = B[80*ldb];
	   
	    plA[0] = A[0+0*lda];
        plA[16] = A[16+0*lda];
        plA[32] = A[32+0*lda];
        plA[48] = A[48+0*lda];
        plA[64] = A[64+0*lda];
        plA[80] = A[80+0*lda];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;

        #pragma unroll 1
        for(unsigned int k = 0 ; k < min(16u, K-block_k ); k+=1)
	    {

	        rA[0][0] = lA[offA + 0];				  
            rA[0][1] = lA[offA + 16];				  
            rA[0][2] = lA[offA + 32];				  
            rA[0][3] = lA[offA + 48];				  
            rA[0][4] = lA[offA + 64];				  
            rA[0][5] = lA[offA + 80];				  
            rB[0][0] = lB[offB + 0];				  
            rB[0][1] = lB[offB + 16];				  
            rB[0][2] = lB[offB + 32];				  
            rB[0][3] = lB[offB + 48];				  
            rB[0][4] = lB[offB + 64];				  
            rB[0][5] = lB[offB + 80];				  
            offA += 97;								  
            offB += 97;								  
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
			barrier(CLK_LOCAL_MEM_FENCE);


        }



        A += lda<<4;
        B += 16;
        block_k+=16;
    } while (block_k < K);

    C+= gidx*96+idx;
    C+= gidy*96*ldc;
    C+= idy*ldc;
    
	C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[0][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[0][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[0][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[0][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[0][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[1][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[1][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[1][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[1][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[1][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[2][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[2][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[2][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[2][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[2][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[3][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[3][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[3][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[3][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[3][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[4][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[4][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[4][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[4][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[4][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[4][5] + beta*C[80*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[5][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[5][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[5][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[5][3] + beta*C[48*ldc];
    C[64*ldc] = alpha*rC[5][4] + beta*C[64*ldc];
    C[80*ldc] = alpha*rC[5][5] + beta*C[80*ldc];
   
}


__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NN_1_96_1_16x16_6x6__ALPHABETA_SPLIT_ROW( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = M/96;//get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    

	int CurrentOffSetA = gidx*96+ idx;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96*ldb+ idx + idy*ldb;
    
   
    int block_k = 0;//K >> 4
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idx*97+idy;

        plB[0] = B[0];
        plB[16] = B[16*ldb];
        plB[32] = B[32*ldb];
        plB[48] = B[48*ldb];
        plB[64] = B[64*ldb];
        plB[80] = B[80*ldb];
	   
	    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[48] = CurrentOffSetA+48>=M?0.0:A[48];
        plA[64] = CurrentOffSetA+64>=M?0.0:A[64];
        plA[80] = CurrentOffSetA+80>=M?0.0:A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        #pragma unroll 1
        for(unsigned int k = 0 ; k < min(16u, K-block_k ); k+=1)
	    {

	        rA[0][0] = lA[offA + 0];				  
            rA[0][1] = lA[offA + 16];				  
            rA[0][2] = lA[offA + 32];				  
            rA[0][3] = lA[offA + 48];				  
            rA[0][4] = lA[offA + 64];				  
            rA[0][5] = lA[offA + 80];				  
            rB[0][0] = lB[offB + 0];				  
            rB[0][1] = lB[offB + 16];				  
            rB[0][2] = lB[offB + 32];				  
            rB[0][3] = lB[offB + 48];				  
            rB[0][4] = lB[offB + 64];				  
            rB[0][5] = lB[offB + 80];				  
            offA += 97;								  
            offB += 97;								  
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
			barrier(CLK_LOCAL_MEM_FENCE);


        }


        A += lda<<4;
        B += 16;
        block_k+=16;
    } while (block_k < K);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

	if(offset_x>=M )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = mad(alpha, rC[i][0], beta*C[0]);
      C[16*ldc] = mad(alpha, rC[i][1], beta*C[16*ldc]);
      C[32*ldc] = mad(alpha, rC[i][2], beta*C[32*ldc]);
      C[48*ldc] = mad(alpha, rC[i][3], beta*C[48*ldc]);
      C[64*ldc] = mad(alpha, rC[i][4], beta*C[64*ldc]);
      C[80*ldc] = mad(alpha, rC[i][5], beta*C[80*ldc]);
      C+=16;
	  offset_x+=16;
	  if(offset_x>=M )
        return;
	}
    while (++i < 6);
}





__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NN_96_1_1_16x16_6x6__ALPHABETA_SPLIT_COLUMN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = N/96;//get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
	int CurrentOffSetB = gidy*96+ idy;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96*ldb+ idx + idy*ldb;
    
   
    int block_k = 0;//K >> 4
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idx*97+idy;

        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[32*ldb];
        plB[48] = CurrentOffSetB+48>=N?0.0:B[48*ldb];
        plB[64] = CurrentOffSetB+64>=N?0.0:B[64*ldb];
        plB[80] = CurrentOffSetB+80>=N?0.0:B[80*ldb];
	   
	    plA[0]  = A[0];
        plA[16] = A[16];
        plA[32] = A[32];
        plA[48] = A[48];
        plA[64] = A[64];
        plA[80] = A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        #pragma unroll 1
        for(unsigned int k = 0 ; k < min(16u, K-block_k ); k+=1)
	    {

	        rA[0][0] = lA[offA + 0];				  
            rA[0][1] = lA[offA + 16];				  
            rA[0][2] = lA[offA + 32];				  
            rA[0][3] = lA[offA + 48];				  
            rA[0][4] = lA[offA + 64];				  
            rA[0][5] = lA[offA + 80];				  
            rB[0][0] = lB[offB + 0];				  
            rB[0][1] = lB[offB + 16];				  
            rB[0][2] = lB[offB + 32];				  
            rB[0][3] = lB[offB + 48];				  
            rB[0][4] = lB[offB + 64];				  
            rB[0][5] = lB[offB + 80];				  
            offA += 97;								  
            offB += 97;								  
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
			barrier(CLK_LOCAL_MEM_FENCE);


        }


        A += lda<<4;
        B += 16;
        block_k+=16;
    } while (block_k < K);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

	if(offset_y>=N )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = mad(alpha, rC[i][0], beta*C[0]);
	  if(offset_y+16<N)
        C[16*ldc] = mad(alpha, rC[i][1], beta*C[16*ldc]);
      if(offset_y+32<N)
        C[32*ldc] = mad(alpha, rC[i][2], beta*C[32*ldc]);
      if(offset_y+48<N)
        C[48*ldc] = mad(alpha, rC[i][3], beta*C[48*ldc]);
	  if(offset_y+64<N)
        C[64*ldc] = mad(alpha, rC[i][4], beta*C[64*ldc]);
	  if(offset_y+80<N)
        C[80*ldc] = mad(alpha, rC[i][5], beta*C[80*ldc]);
      
	  C+=16;
	    
	}
    while (++i < 6);
}

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NN_1_1_1_16x16_6x6__ALPHABETA_SPLIT_SINGLE( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = M/96;//get_group_id(0);
    uint gidy = N/96;//get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
	int CurrentOffSetA = gidx*96+ idx;
	int CurrentOffSetB = gidy*96+ idy;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96*ldb+ idx + idy*ldb;
    
   
    int block_k = 0;//K >> 4
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idx*97+idy;

        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[32*ldb];
        plB[48] = CurrentOffSetB+48>=N?0.0:B[48*ldb];
        plB[64] = CurrentOffSetB+64>=N?0.0:B[64*ldb];
        plB[80] = CurrentOffSetB+80>=N?0.0:B[80*ldb];

	  // plB[0]  = (CurrentOffSetB>=N || idx>=M)?0.0:B[0];
	  // plB[16] = (CurrentOffSetB+16>=N || idx>=M)?0.0:B[16*ldb];
	  // plB[32] = (CurrentOffSetB+32>=N || idx>=M)?0.0:B[32*ldb];
	  // plB[48] = (CurrentOffSetB+48>=N || idx>=M)?0.0:B[48*ldb];
	  // plB[64] = (CurrentOffSetB+64>=N || idx>=M)?0.0:B[64*ldb];
	  // plB[80] = (CurrentOffSetB+80>=N || idx>=M)?0.0:B[80*ldb];

	   
	    plA[0]  = (CurrentOffSetA>=M )?0.0:A[0];
        plA[16] = (CurrentOffSetA+16>=M )?0.0:A[16];
        plA[32] = (CurrentOffSetA+32>=M )?0.0:A[32];
        plA[48] = (CurrentOffSetA+48>=M )?0.0:A[48];
        plA[64] = (CurrentOffSetA+64>=M )?0.0:A[64];
        plA[80] = (CurrentOffSetA+80>=M )?0.0:A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;

        #pragma unroll 1
        for(unsigned int k = 0 ; k < min(16u, K-block_k ); k+=1)
	    {

	        rA[0][0] = lA[offA + 0];				  
            rA[0][1] = lA[offA + 16];				  
            rA[0][2] = lA[offA + 32];				  
            rA[0][3] = lA[offA + 48];				  
            rA[0][4] = lA[offA + 64];				  
            rA[0][5] = lA[offA + 80];				  
            rB[0][0] = lB[offB + 0];				  
            rB[0][1] = lB[offB + 16];				  
            rB[0][2] = lB[offB + 32];				  
            rB[0][3] = lB[offB + 48];				  
            rB[0][4] = lB[offB + 64];				  
            rB[0][5] = lB[offB + 80];				  
            offA += 97;								  
            offB += 97;								  
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
			barrier(CLK_LOCAL_MEM_FENCE);


        }

        A += lda<<4;
        B += 16;
		block_k+=16;
	}  while (block_k < K);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

    if(offset_x>=M || offset_y>=N )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = mad(alpha, rC[i][0], beta*C[0]);
	  if(offset_y+16<N)
        C[16*ldc] = mad(alpha, rC[i][1], beta*C[16*ldc]);
      if(offset_y+32<N)
        C[32*ldc] = mad(alpha, rC[i][2], beta*C[32*ldc]);
      if(offset_y+48<N)
        C[48*ldc] = mad(alpha, rC[i][3], beta*C[48*ldc]);
	  if(offset_y+64<N)
        C[64*ldc] = mad(alpha, rC[i][4], beta*C[64*ldc]);
	  if(offset_y+80<N)
        C[80*ldc] = mad(alpha, rC[i][5], beta*C[80*ldc]);
      
	  C+=16;
	  offset_x+=16;
	  if(offset_x>=M )
        return;

	    
	}
    while (++i < 6);
}
";



static const char * sgemm_NN_1_SPLIT__ALPHA = "

#define  M6x6 \
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
			mem_fence(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NN_96_96_1_16x16_6x6__ALPHA_SPLIT_MAIN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    

    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);

    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96*ldb+ idx + idy*ldb;
    
   
    uint block_k = 0;//K >> 4;
    do 
    {
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idx*97+idy;
      
        plB[0] = B[0];
        plB[16] = B[16*ldb];
        plB[32] = B[32*ldb];
        plB[48] = B[48*ldb];
        plB[64] = B[64*ldb];
        plB[80] = B[80*ldb];
	   
	      plA[0] = A[0+0*lda];
        plA[16] = A[16+0*lda];
        plA[32] = A[32+0*lda];
        plA[48] = A[48+0*lda];
        plA[64] = A[64+0*lda];
        plA[80] = A[80+0*lda];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;

        #pragma unroll 1
        for(unsigned int k = 0 ; k < min(16u, K-block_k ); k+=1)
	      {

	          rA[0][0] = lA[offA + 0];				  
            rA[0][1] = lA[offA + 16];				  
            rA[0][2] = lA[offA + 32];				  
            rA[0][3] = lA[offA + 48];				  
            rA[0][4] = lA[offA + 64];				  
            rA[0][5] = lA[offA + 80];				  
            rB[0][0] = lB[offB + 0];				  
            rB[0][1] = lB[offB + 16];				  
            rB[0][2] = lB[offB + 32];				  
            rB[0][3] = lB[offB + 48];				  
            rB[0][4] = lB[offB + 64];				  
            rB[0][5] = lB[offB + 80];				  
            offA += 97;								  
            offB += 97;								  
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
            barrier(CLK_LOCAL_MEM_FENCE);
        }



        A += lda<<4;
        B += 16;
        block_k+=16;
    } while (block_k < K);

    C+= gidx*96+idx;
    C+= gidy*96*ldc;
    C+= idy*ldc;
    
	C[0*ldc] = alpha*rC[0][0] ;
    C[16*ldc] = alpha*rC[0][1];
    C[32*ldc] = alpha*rC[0][2];
    C[48*ldc] = alpha*rC[0][3];
    C[64*ldc] = alpha*rC[0][4];
    C[80*ldc] = alpha*rC[0][5];
    C+=16;					  ;
    C[0*ldc] = alpha*rC[1][0] ;
    C[16*ldc] = alpha*rC[1][1];
    C[32*ldc] = alpha*rC[1][2];
    C[48*ldc] = alpha*rC[1][3];
    C[64*ldc] = alpha*rC[1][4];
    C[80*ldc] = alpha*rC[1][5];
    C+=16;					  ;
    C[0*ldc] = alpha*rC[2][0] ;
    C[16*ldc] = alpha*rC[2][1];
    C[32*ldc] = alpha*rC[2][2];
    C[48*ldc] = alpha*rC[2][3];
    C[64*ldc] = alpha*rC[2][4];
    C[80*ldc] = alpha*rC[2][5];
    C+=16;					  ;
    C[0*ldc] = alpha*rC[3][0] ;
    C[16*ldc] = alpha*rC[3][1];
    C[32*ldc] = alpha*rC[3][2];
    C[48*ldc] = alpha*rC[3][3];
    C[64*ldc] = alpha*rC[3][4];
    C[80*ldc] = alpha*rC[3][5];
    C+=16;					  ;
    C[0*ldc] = alpha*rC[4][0] ;
    C[16*ldc] = alpha*rC[4][1];
    C[32*ldc] = alpha*rC[4][2];
    C[48*ldc] = alpha*rC[4][3];
    C[64*ldc] = alpha*rC[4][4];
    C[80*ldc] = alpha*rC[4][5];
    C+=16;					  ;
    C[0*ldc] = alpha*rC[5][0] ;
    C[16*ldc] = alpha*rC[5][1];
    C[32*ldc] = alpha*rC[5][2];
    C[48*ldc] = alpha*rC[5][3];
    C[64*ldc] = alpha*rC[5][4];
    C[80*ldc] = alpha*rC[5][5];
   
}


__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NN_1_96_1_16x16_6x6__ALPHA_SPLIT_ROW( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = M/96;//get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    

	int CurrentOffSetA = gidx*96+ idx;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96*ldb+ idx + idy*ldb;
    
   
    uint block_k = 0;//K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idx*97+idy;

        plB[0] = B[0];
        plB[16] = B[16*ldb];
        plB[32] = B[32*ldb];
        plB[48] = B[48*ldb];
        plB[64] = B[64*ldb];
        plB[80] = B[80*ldb];
	   
	    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[48] = CurrentOffSetA+48>=M?0.0:A[48];
        plA[64] = CurrentOffSetA+64>=M?0.0:A[64];
        plA[80] = CurrentOffSetA+80>=M?0.0:A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        #pragma unroll 1
        for(unsigned int k = 0 ; k < min(16u, K-block_k ); k+=1)
	    {

	        rA[0][0] = lA[offA + 0];				  
            rA[0][1] = lA[offA + 16];				  
            rA[0][2] = lA[offA + 32];				  
            rA[0][3] = lA[offA + 48];				  
            rA[0][4] = lA[offA + 64];				  
            rA[0][5] = lA[offA + 80];				  
            rB[0][0] = lB[offB + 0];				  
            rB[0][1] = lB[offB + 16];				  
            rB[0][2] = lB[offB + 32];				  
            rB[0][3] = lB[offB + 48];				  
            rB[0][4] = lB[offB + 64];				  
            rB[0][5] = lB[offB + 80];				  
            offA += 97;								  
            offB += 97;								  
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
			barrier(CLK_LOCAL_MEM_FENCE);


        }



        A += lda<<4;
        B += 16;
        block_k+=16;
    } while (block_k < K);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

	if(offset_x>=M )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = alpha * rC[i][0];
      C[16*ldc] = alpha * rC[i][1];
      C[32*ldc] = alpha * rC[i][2];
      C[48*ldc] = alpha * rC[i][3];
      C[64*ldc] = alpha * rC[i][4];
      C[80*ldc] = alpha * rC[i][5];
      C+=16;
	  offset_x+=16;
	  if(offset_x>=M )
        return;
	}
    while (++i < 6);
}





__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NN_96_1_1_16x16_6x6__ALPHA_SPLIT_COLUMN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = N/96;//get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
	int CurrentOffSetB = gidy*96+ idy;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96*ldb+ idx + idy*ldb;
    
   
    uint block_k = 0;//K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idx*97+idy;

        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[32*ldb];
        plB[48] = CurrentOffSetB+48>=N?0.0:B[48*ldb];
        plB[64] = CurrentOffSetB+64>=N?0.0:B[64*ldb];
        plB[80] = CurrentOffSetB+80>=N?0.0:B[80*ldb];
	   
	      plA[0]  = A[0];
        plA[16] = A[16];
        plA[32] = A[32];
        plA[48] = A[48];
        plA[64] = A[64];
        plA[80] = A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        #pragma unroll 1
        for(unsigned int k = 0 ; k < min(16u, K-block_k ); k+=1)
	      {

	          rA[0][0] = lA[offA + 0];				  
            rA[0][1] = lA[offA + 16];				  
            rA[0][2] = lA[offA + 32];				  
            rA[0][3] = lA[offA + 48];				  
            rA[0][4] = lA[offA + 64];				  
            rA[0][5] = lA[offA + 80];				  
            rB[0][0] = lB[offB + 0];				  
            rB[0][1] = lB[offB + 16];				  
            rB[0][2] = lB[offB + 32];				  
            rB[0][3] = lB[offB + 48];				  
            rB[0][4] = lB[offB + 64];				  
            rB[0][5] = lB[offB + 80];				  
            offA += 97;								  
            offB += 97;								  
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
			      barrier(CLK_LOCAL_MEM_FENCE);
        }



        A += lda<<4;
        B += 16;
        block_k+=16;
    } while (block_k < K);


	int offset_x = gidx*96+idx;
  int offset_y = gidy*96+ idy;

	if(offset_y>=N )
      return;

  C+=offset_x+offset_y*ldc;
    
  int i = 0;
  do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = alpha * rC[i][0] ;
	  if(offset_y+16<N)
      C[16*ldc] = alpha * rC[i][1];
    if(offset_y+32<N)
      C[32*ldc] = alpha * rC[i][2];
    if(offset_y+48<N)
      C[48*ldc] = alpha * rC[i][3];
	  if(offset_y+64<N)
      C[64*ldc] = alpha * rC[i][4];
	  if(offset_y+80<N)
      C[80*ldc] = alpha * rC[i][5];
      
	  C+=16;
	    
	}
  while (++i < 6);
}

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NN_1_1_1_16x16_6x6__ALPHA_SPLIT_SINGLE( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
    float rC[6][6]  = {(float)0};
    float rA[1][6];
    float rB[1][6];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = M/96;//get_group_id(0);
    uint gidy = N/96;//get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
	int CurrentOffSetA = gidx*96+ idx;
	int CurrentOffSetB = gidy*96+ idy;
    
    A +=  gidx*96+ idx + idy*lda;
    B +=  gidy*96*ldb+ idx + idy*ldb;
    
   
    uint block_k = 0;//K >> 4;
    do 
	{
        __local float* plA = lA + idy*97+idx;
        __local float* plB = lB + idx*97+idy;

        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];
        plB[32] = CurrentOffSetB+32>=N?0.0:B[32*ldb];
        plB[48] = CurrentOffSetB+48>=N?0.0:B[48*ldb];
        plB[64] = CurrentOffSetB+64>=N?0.0:B[64*ldb];
        plB[80] = CurrentOffSetB+80>=N?0.0:B[80*ldb];
	   
	    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
        plA[16] = CurrentOffSetA+16>=M?0.0:A[16];
        plA[32] = CurrentOffSetA+32>=M?0.0:A[32];
        plA[48] = CurrentOffSetA+48>=M?0.0:A[48];
        plA[64] = CurrentOffSetA+64>=M?0.0:A[64];
        plA[80] = CurrentOffSetA+80>=M?0.0:A[80];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        #pragma unroll 1
        for(unsigned int k = 0 ; k < min(16u, K-block_k ); k+=1)
	    {

	        rA[0][0] = lA[offA + 0];				  
            rA[0][1] = lA[offA + 16];				  
            rA[0][2] = lA[offA + 32];				  
            rA[0][3] = lA[offA + 48];				  
            rA[0][4] = lA[offA + 64];				  
            rA[0][5] = lA[offA + 80];				  
            rB[0][0] = lB[offB + 0];				  
            rB[0][1] = lB[offB + 16];				  
            rB[0][2] = lB[offB + 32];				  
            rB[0][3] = lB[offB + 48];				  
            rB[0][4] = lB[offB + 64];				  
            rB[0][5] = lB[offB + 80];				  
            offA += 97;								  
            offB += 97;								  
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
			barrier(CLK_LOCAL_MEM_FENCE);


        }



        A += lda<<4;
        B += 16;
        block_k+=16;
    } while (block_k < K);


	int offset_x = gidx*96+idx;
    int offset_y = gidy*96+ idy;

    if(offset_x>=M || offset_y>=N )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
    do 
	//for (int i=0; i<6; i++)
	{
	  C[0     ] = alpha * rC[i][0] ;
	  if(offset_y+16<N)				   
        C[16*ldc] = alpha * rC[i][1];
      if(offset_y+32<N)		 	    
        C[32*ldc] = alpha * rC[i][2];
      if(offset_y+48<N)		 	    
        C[48*ldc] = alpha * rC[i][3];
	  if(offset_y+64<N)		 	    
        C[64*ldc] = alpha * rC[i][4];
	  if(offset_y+80<N)		    
        C[80*ldc] = alpha * rC[i][5];
      
	  C+=16;
	  offset_x+=16;
	  if(offset_x>=M )
        return;

	    
	}
    while (++i < 6);
}
";




/*************************************************************************************************/
static const char * sgemm_TN_16_SPLIT__ALPHABETA = "

#define  M6x6 \
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
  mem_fence(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))
  __kernel void sgemm_TN_96_96_16_16x16_6x6__ALPHABETA_SPLIT_MAIN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
  float rC[6][6]  = {(float)0};
  float rA[1][6];
  float rB[1][6];



  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local float lA[1552];
  __local float lB[1552];

  uint gidx = get_group_id(0);
  uint gidy = get_group_id(1);
  uint idx = get_local_id(0);
  uint idy = get_local_id(1);

  A +=  (gidx*96+idy)*lda + idx;
  B +=  (gidy*96+idy)*ldb + idx;


  uint block_k = K >> 4;
  do 
  {
    __local float* plA = lA + idx*97+idy;
    __local float* plB = lB + idx*97+idy;
    barrier(CLK_LOCAL_MEM_FENCE);

    plB[0] = B[0];
    plB[16] = B[16*ldb];
    plB[32] = B[32*ldb];
    plB[48] = B[48*ldb];
    plB[64] = B[64*ldb];
    plB[80] = B[80*ldb];

    plA[0] = A[0];
    plA[16] = A[16*lda];
    plA[32] = A[32*lda];
    plA[48] = A[48*lda];
    plA[64] = A[64*lda];
    plA[80] = A[80*lda];


    barrier(CLK_LOCAL_MEM_FENCE);
    uint offA = idx;
    uint offB = idy;

    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6

    A += 16;
    B += 16;
  } while (--block_k > 0);

  C+= gidx*96+idx;
  C+= gidy*96*ldc;
  C+= idy*ldc;

  C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
  C[16*ldc] = alpha*rC[0][1] + beta*C[16*ldc];
  C[32*ldc] = alpha*rC[0][2] + beta*C[32*ldc];
  C[48*ldc] = alpha*rC[0][3] + beta*C[48*ldc];
  C[64*ldc] = alpha*rC[0][4] + beta*C[64*ldc];
  C[80*ldc] = alpha*rC[0][5] + beta*C[80*ldc];
  C+=16;
  C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
  C[16*ldc] = alpha*rC[1][1] + beta*C[16*ldc];
  C[32*ldc] = alpha*rC[1][2] + beta*C[32*ldc];
  C[48*ldc] = alpha*rC[1][3] + beta*C[48*ldc];
  C[64*ldc] = alpha*rC[1][4] + beta*C[64*ldc];
  C[80*ldc] = alpha*rC[1][5] + beta*C[80*ldc];
  C+=16;
  C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
  C[16*ldc] = alpha*rC[2][1] + beta*C[16*ldc];
  C[32*ldc] = alpha*rC[2][2] + beta*C[32*ldc];
  C[48*ldc] = alpha*rC[2][3] + beta*C[48*ldc];
  C[64*ldc] = alpha*rC[2][4] + beta*C[64*ldc];
  C[80*ldc] = alpha*rC[2][5] + beta*C[80*ldc];
  C+=16;
  C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
  C[16*ldc] = alpha*rC[3][1] + beta*C[16*ldc];
  C[32*ldc] = alpha*rC[3][2] + beta*C[32*ldc];
  C[48*ldc] = alpha*rC[3][3] + beta*C[48*ldc];
  C[64*ldc] = alpha*rC[3][4] + beta*C[64*ldc];
  C[80*ldc] = alpha*rC[3][5] + beta*C[80*ldc];
  C+=16;
  C[0*ldc] = alpha*rC[4][0] + beta*C[0*ldc];
  C[16*ldc] = alpha*rC[4][1] + beta*C[16*ldc];
  C[32*ldc] = alpha*rC[4][2] + beta*C[32*ldc];
  C[48*ldc] = alpha*rC[4][3] + beta*C[48*ldc];
  C[64*ldc] = alpha*rC[4][4] + beta*C[64*ldc];
  C[80*ldc] = alpha*rC[4][5] + beta*C[80*ldc];
  C+=16;
  C[0*ldc] = alpha*rC[5][0] + beta*C[0*ldc];
  C[16*ldc] = alpha*rC[5][1] + beta*C[16*ldc];
  C[32*ldc] = alpha*rC[5][2] + beta*C[32*ldc];
  C[48*ldc] = alpha*rC[5][3] + beta*C[48*ldc];
  C[64*ldc] = alpha*rC[5][4] + beta*C[64*ldc];
  C[80*ldc] = alpha*rC[5][5] + beta*C[80*ldc];

}


__attribute__((reqd_work_group_size(16,16,1)))
  __kernel void sgemm_TN_1_96_16_16x16_6x6__ALPHABETA_SPLIT_ROW( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
  float rC[6][6]  = {(float)0};
  float rA[1][6];
  float rB[1][6];


  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local float lA[1552];
  __local float lB[1552];

  uint gidx = M/96;//get_group_id(0);
  uint gidy = get_group_id(1);
  uint idx = get_local_id(0);
  uint idy = get_local_id(1);


  int CurrentOffSetA = gidx*96+ idy;

  A +=  (gidx*96+idy)*lda + idx;
  B +=  (gidy*96+idy)*ldb + idx;


  uint block_k = K >> 4;
  do 
  {
    __local float* plA = lA + idx*97+idy;
    __local float* plB = lB + idx*97+idy;
    barrier(CLK_LOCAL_MEM_FENCE);

    plB[0] = B[0];
    plB[16] = B[16*ldb];
    plB[32] = B[32*ldb];
    plB[48] = B[48*ldb];
    plB[64] = B[64*ldb];
    plB[80] = B[80*ldb];

    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
    plA[16] = CurrentOffSetA+16>=M?0.0:A[16*lda];
    plA[32] = CurrentOffSetA+32>=M?0.0:A[32*lda];
    plA[48] = CurrentOffSetA+48>=M?0.0:A[48*lda];
    plA[64] = CurrentOffSetA+64>=M?0.0:A[64*lda];
    plA[80] = CurrentOffSetA+80>=M?0.0:A[80*lda];


    barrier(CLK_LOCAL_MEM_FENCE);
    uint offA = idx;
    uint offB = idy;


    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6

    A += 16;
    B += 16;
  } while (--block_k > 0);


  int offset_x = gidx*96+idx;
  int offset_y = gidy*96+ idy;

  if(offset_x>=M )
    return;

  C+=offset_x+offset_y*ldc;

  int i = 0;
  do 
  //for (int i=0; i<6; i++)
  {
    C[0     ] = mad(alpha, rC[i][0], beta*C[0]);
    C[16*ldc] = mad(alpha, rC[i][1], beta*C[16*ldc]);
    C[32*ldc] = mad(alpha, rC[i][2], beta*C[32*ldc]);
    C[48*ldc] = mad(alpha, rC[i][3], beta*C[48*ldc]);
    C[64*ldc] = mad(alpha, rC[i][4], beta*C[64*ldc]);
    C[80*ldc] = mad(alpha, rC[i][5], beta*C[80*ldc]);
    C+=16;
    offset_x+=16;
    if(offset_x>=M )
      return;
  }
  while (++i < 6);
}





__attribute__((reqd_work_group_size(16,16,1)))
  __kernel void sgemm_TN_96_1_16_16x16_6x6__ALPHABETA_SPLIT_COLUMN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
  float rC[6][6]  = {(float)0};
  float rA[1][6];
  float rB[1][6];


  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local float lA[1552];
  __local float lB[1552];

  uint gidx = get_group_id(0);
  uint gidy = N/96;//get_group_id(1);
  uint idx = get_local_id(0);
  uint idy = get_local_id(1);

  int CurrentOffSetB = gidy*96+ idy;

  A +=  (gidx*96+idy)*lda + idx;
  B +=  (gidy*96+idy)*ldb + idx;


  uint block_k = K >> 4;
  do 
  {
    __local float* plA = lA + idx*97+idy;
    __local float* plB = lB + idx*97+idy;
    barrier(CLK_LOCAL_MEM_FENCE);

    plB[0]  = CurrentOffSetB>=N?0.0:B[0];
    plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];
    plB[32] = CurrentOffSetB+32>=N?0.0:B[32*ldb];
    plB[48] = CurrentOffSetB+48>=N?0.0:B[48*ldb];
    plB[64] = CurrentOffSetB+64>=N?0.0:B[64*ldb];
    plB[80] = CurrentOffSetB+80>=N?0.0:B[80*ldb];

    plA[0]  = A[0];
    plA[16] = A[16*lda];
    plA[32] = A[32*lda];
    plA[48] = A[48*lda];
    plA[64] = A[64*lda];
    plA[80] = A[80*lda];


    barrier(CLK_LOCAL_MEM_FENCE);
    uint offA = idx;
    uint offB = idy;


    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6

    A += 16;
    B += 16;
  } while (--block_k > 0);


  int offset_x = gidx*96+idx;
  int offset_y = gidy*96+ idy;

  if(offset_y>=N )
    return;

  C+=offset_x+offset_y*ldc;

  int i = 0;
  do 
  //for (int i=0; i<6; i++)
  {
    C[0     ] = mad(alpha, rC[i][0], beta*C[0]);
    if(offset_y+16<N)
      C[16*ldc] = mad(alpha, rC[i][1], beta*C[16*ldc]);
    if(offset_y+32<N)
      C[32*ldc] = mad(alpha, rC[i][2], beta*C[32*ldc]);
    if(offset_y+48<N)
      C[48*ldc] = mad(alpha, rC[i][3], beta*C[48*ldc]);
    if(offset_y+64<N)
      C[64*ldc] = mad(alpha, rC[i][4], beta*C[64*ldc]);
    if(offset_y+80<N)
      C[80*ldc] = mad(alpha, rC[i][5], beta*C[80*ldc]);

    C+=16;

  }
  while (++i < 6);
}

__attribute__((reqd_work_group_size(16,16,1)))
  __kernel void sgemm_TN_1_1_16_16x16_6x6__ALPHABETA_SPLIT_SINGLE( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  float const beta,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
  float rC[6][6]  = {(float)0};
  float rA[1][6];
  float rB[1][6];


  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local float lA[1552];
  __local float lB[1552];

  uint gidx = M/96;//get_group_id(0);
  uint gidy = N/96;//get_group_id(1);
  uint idx = get_local_id(0);
  uint idy = get_local_id(1);

  int CurrentOffSetA = gidx*96+ idy;
  int CurrentOffSetB = gidy*96+ idy;

  A +=  (gidx*96+idy)*lda + idx;
  B +=  (gidy*96+idy)*ldb + idx;


  uint block_k = K >> 4;
  do 
  {
    __local float* plA = lA + idx*97+idy;
    __local float* plB = lB + idx*97+idy;
    barrier(CLK_LOCAL_MEM_FENCE);

    plB[0]  = CurrentOffSetB>=N?0.0:B[0];
    plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];
    plB[32] = CurrentOffSetB+32>=N?0.0:B[32*ldb];
    plB[48] = CurrentOffSetB+48>=N?0.0:B[48*ldb];
    plB[64] = CurrentOffSetB+64>=N?0.0:B[64*ldb];
    plB[80] = CurrentOffSetB+80>=N?0.0:B[80*ldb];

    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
    plA[16] = CurrentOffSetA+16>=M?0.0:A[16*lda];
    plA[32] = CurrentOffSetA+32>=M?0.0:A[32*lda];
    plA[48] = CurrentOffSetA+48>=M?0.0:A[48*lda];
    plA[64] = CurrentOffSetA+64>=M?0.0:A[64*lda];
    plA[80] = CurrentOffSetA+80>=M?0.0:A[80*lda];


    barrier(CLK_LOCAL_MEM_FENCE);
    uint offA = idx;
    uint offB = idy;


    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6

    A += 16;
    B += 16;
  } while (--block_k > 0);


  int offset_x = gidx*96+idx;
  int offset_y = gidy*96+ idy;

  if(offset_x>=M || offset_y>=N )
    return;

  C+=offset_x+offset_y*ldc;

  int i = 0;
  do 
  //for (int i=0; i<6; i++)
  {
    C[0     ] = mad(alpha, rC[i][0], beta*C[0]);
    if(offset_y+16<N)
      C[16*ldc] = mad(alpha, rC[i][1], beta*C[16*ldc]);
    if(offset_y+32<N)
      C[32*ldc] = mad(alpha, rC[i][2], beta*C[32*ldc]);
    if(offset_y+48<N)
      C[48*ldc] = mad(alpha, rC[i][3], beta*C[48*ldc]);
    if(offset_y+64<N)
      C[64*ldc] = mad(alpha, rC[i][4], beta*C[64*ldc]);
    if(offset_y+80<N)
      C[80*ldc] = mad(alpha, rC[i][5], beta*C[80*ldc]);

    C+=16;
    offset_x+=16;
    if(offset_x>=M )
      return;


  }
  while (++i < 6);
}
";

static const char * sgemm_TN_16_SPLIT__ALPHA = "

#define  M6x6 \
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
  mem_fence(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))
  __kernel void sgemm_TN_96_96_16_16x16_6x6__ALPHA_SPLIT_MAIN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
  float rC[6][6]  = {(float)0};
  float rA[1][6];
  float rB[1][6];



  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local float lA[1552];
  __local float lB[1552];

  uint gidx = get_group_id(0);
  uint gidy = get_group_id(1);
  uint idx = get_local_id(0);
  uint idy = get_local_id(1);

  A +=  (gidx*96+idy)*lda + idx;
  B +=  (gidy*96+idy)*ldb + idx;


  uint block_k = K >> 4;
  do 
  {
    __local float* plA = lA + idx*97+idy;
    __local float* plB = lB + idx*97+idy;
    barrier(CLK_LOCAL_MEM_FENCE);

    plB[0] = B[0];
    plB[16] = B[16*ldb];
    plB[32] = B[32*ldb];
    plB[48] = B[48*ldb];
    plB[64] = B[64*ldb];
    plB[80] = B[80*ldb];

    plA[0] = A[0];
    plA[16] = A[16*lda];
    plA[32] = A[32*lda];
    plA[48] = A[48*lda];
    plA[64] = A[64*lda];
    plA[80] = A[80*lda];


    barrier(CLK_LOCAL_MEM_FENCE);
    uint offA = idx;
    uint offB = idy;

    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6

    A += 16;
    B += 16;
  } while (--block_k > 0);

  C+= gidx*96+idx;
  C+= gidy*96*ldc;
  C+= idy*ldc;

  C[0*ldc] = alpha*rC[0][0]  ;
  C[16*ldc] = alpha*rC[0][1] ;
  C[32*ldc] = alpha*rC[0][2] ;
  C[48*ldc] = alpha*rC[0][3] ;
  C[64*ldc] = alpha*rC[0][4] ;
  C[80*ldc] = alpha*rC[0][5] ;
  C+=16;
  C[0*ldc] = alpha*rC[1][0]  ;
  C[16*ldc] = alpha*rC[1][1] ;
  C[32*ldc] = alpha*rC[1][2] ;
  C[48*ldc] = alpha*rC[1][3] ;
  C[64*ldc] = alpha*rC[1][4] ;
  C[80*ldc] = alpha*rC[1][5] ;
  C+=16;
  C[0*ldc] = alpha*rC[2][0]  ;
  C[16*ldc] = alpha*rC[2][1] ;
  C[32*ldc] = alpha*rC[2][2] ;
  C[48*ldc] = alpha*rC[2][3] ;
  C[64*ldc] = alpha*rC[2][4] ;
  C[80*ldc] = alpha*rC[2][5] ;
  C+=16;
  C[0*ldc] = alpha*rC[3][0]  ;
  C[16*ldc] = alpha*rC[3][1] ;
  C[32*ldc] = alpha*rC[3][2] ;
  C[48*ldc] = alpha*rC[3][3] ;
  C[64*ldc] = alpha*rC[3][4] ;
  C[80*ldc] = alpha*rC[3][5] ;
  C+=16;
  C[0*ldc] = alpha*rC[4][0]  ;
  C[16*ldc] = alpha*rC[4][1] ;
  C[32*ldc] = alpha*rC[4][2] ;
  C[48*ldc] = alpha*rC[4][3] ;
  C[64*ldc] = alpha*rC[4][4] ;
  C[80*ldc] = alpha*rC[4][5] ;
  C+=16;
  C[0*ldc] = alpha*rC[5][0]  ;
  C[16*ldc] = alpha*rC[5][1] ;
  C[32*ldc] = alpha*rC[5][2] ;
  C[48*ldc] = alpha*rC[5][3] ;
  C[64*ldc] = alpha*rC[5][4] ;
  C[80*ldc] = alpha*rC[5][5] ;

}


__attribute__((reqd_work_group_size(16,16,1)))
  __kernel void sgemm_TN_1_96_16_16x16_6x6__ALPHA_SPLIT_ROW( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
  float rC[6][6]  = {(float)0};
  float rA[1][6];
  float rB[1][6];


  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local float lA[1552];
  __local float lB[1552];

  uint gidx = M/96;//get_group_id(0);
  uint gidy = get_group_id(1);
  uint idx = get_local_id(0);
  uint idy = get_local_id(1);


  int CurrentOffSetA = gidx*96+ idy;

  A +=  (gidx*96+idy)*lda + idx;
  B +=  (gidy*96+idy)*ldb + idx;


  uint block_k = K >> 4;
  do 
  {
    __local float* plA = lA + idx*97+idy;
    __local float* plB = lB + idx*97+idy;
    barrier(CLK_LOCAL_MEM_FENCE);

    plB[0] = B[0];
    plB[16] = B[16*ldb];
    plB[32] = B[32*ldb];
    plB[48] = B[48*ldb];
    plB[64] = B[64*ldb];
    plB[80] = B[80*ldb];

    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
    plA[16] = CurrentOffSetA+16>=M?0.0:A[16*lda];
    plA[32] = CurrentOffSetA+32>=M?0.0:A[32*lda];
    plA[48] = CurrentOffSetA+48>=M?0.0:A[48*lda];
    plA[64] = CurrentOffSetA+64>=M?0.0:A[64*lda];
    plA[80] = CurrentOffSetA+80>=M?0.0:A[80*lda];


    barrier(CLK_LOCAL_MEM_FENCE);
    uint offA = idx;
    uint offB = idy;


    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6

    A += 16;
    B += 16;
  } while (--block_k > 0);


  int offset_x = gidx*96+idx;
  int offset_y = gidy*96+ idy;

  if(offset_x>=M )
    return;

  C+=offset_x+offset_y*ldc;

  int i = 0;
  do 
  //for (int i=0; i<6; i++)
  {
    C[0     ] = mad(alpha, rC[i][0], 0);
    C[16*ldc] = mad(alpha, rC[i][1], 0);
    C[32*ldc] = mad(alpha, rC[i][2], 0);
    C[48*ldc] = mad(alpha, rC[i][3], 0);
    C[64*ldc] = mad(alpha, rC[i][4], 0);
    C[80*ldc] = mad(alpha, rC[i][5], 0);
    C+=16;
    offset_x+=16;
    if(offset_x>=M )
      return;
  }
  while (++i < 6);
}





__attribute__((reqd_work_group_size(16,16,1)))
  __kernel void sgemm_TN_96_1_16_16x16_6x6__ALPHA_SPLIT_COLUMN( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
  float rC[6][6]  = {(float)0};
  float rA[1][6];
  float rB[1][6];


  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local float lA[1552];
  __local float lB[1552];

  uint gidx = get_group_id(0);
  uint gidy = N/96;//get_group_id(1);
  uint idx = get_local_id(0);
  uint idy = get_local_id(1);

  int CurrentOffSetB = gidy*96+ idy;

  A +=  (gidx*96+idy)*lda + idx;
  B +=  (gidy*96+idy)*ldb + idx;


  uint block_k = K >> 4;
  do 
  {
    __local float* plA = lA + idx*97+idy;
    __local float* plB = lB + idx*97+idy;
    barrier(CLK_LOCAL_MEM_FENCE);

    plB[0]  = CurrentOffSetB>=N?0.0:B[0];
    plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];
    plB[32] = CurrentOffSetB+32>=N?0.0:B[32*ldb];
    plB[48] = CurrentOffSetB+48>=N?0.0:B[48*ldb];
    plB[64] = CurrentOffSetB+64>=N?0.0:B[64*ldb];
    plB[80] = CurrentOffSetB+80>=N?0.0:B[80*ldb];

    plA[0]  = A[0];
    plA[16] = A[16*lda];
    plA[32] = A[32*lda];
    plA[48] = A[48*lda];
    plA[64] = A[64*lda];
    plA[80] = A[80*lda];


    barrier(CLK_LOCAL_MEM_FENCE);
    uint offA = idx;
    uint offB = idy;


    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6

    A += 16;
    B += 16;
  } while (--block_k > 0);


  int offset_x = gidx*96+idx;
  int offset_y = gidy*96+ idy;

  if(offset_y>=N )
    return;

  C+=offset_x+offset_y*ldc;

  int i = 0;
  do 
  //for (int i=0; i<6; i++)
  {
    C[0     ] = mad(alpha, rC[i][0], 0);
    if(offset_y+16<N)
      C[16*ldc] = mad(alpha, rC[i][1], 0);
    if(offset_y+32<N)
      C[32*ldc] = mad(alpha, rC[i][2], 0);
    if(offset_y+48<N)
      C[48*ldc] = mad(alpha, rC[i][3], 0);
    if(offset_y+64<N)
      C[64*ldc] = mad(alpha, rC[i][4], 0);
    if(offset_y+80<N)
      C[80*ldc] = mad(alpha, rC[i][5], 0);

    C+=16;

  }
  while (++i < 6);
}

__attribute__((reqd_work_group_size(16,16,1)))
  __kernel void sgemm_TN_1_1_16_16x16_6x6__ALPHA_SPLIT_SINGLE( __global float const * restrict A,
  __global float const * restrict B,
  __global float * C,
  uint const M,
  uint const N,
  uint const K,
  float const alpha,
  uint lda,
  uint ldb,
  uint ldc,
  uint offsetA,
  uint offsetB,
  uint offsetC)
{
  float rC[6][6]  = {(float)0};
  float rA[1][6];
  float rB[1][6];


  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local float lA[1552];
  __local float lB[1552];

  uint gidx = M/96;//get_group_id(0);
  uint gidy = N/96;//get_group_id(1);
  uint idx = get_local_id(0);
  uint idy = get_local_id(1);

  int CurrentOffSetA = gidx*96+ idy;
  int CurrentOffSetB = gidy*96+ idy;

  A +=  (gidx*96+idy)*lda + idx;
  B +=  (gidy*96+idy)*ldb + idx;


  uint block_k = K >> 4;
  do 
  {
    __local float* plA = lA + idx*97+idy;
    __local float* plB = lB + idx*97+idy;
    barrier(CLK_LOCAL_MEM_FENCE);

    plB[0]  = CurrentOffSetB>=N?0.0:B[0];
    plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];
    plB[32] = CurrentOffSetB+32>=N?0.0:B[32*ldb];
    plB[48] = CurrentOffSetB+48>=N?0.0:B[48*ldb];
    plB[64] = CurrentOffSetB+64>=N?0.0:B[64*ldb];
    plB[80] = CurrentOffSetB+80>=N?0.0:B[80*ldb];

    plA[0]  = CurrentOffSetA>=M?0.0:A[0];
    plA[16] = CurrentOffSetA+16>=M?0.0:A[16*lda];
    plA[32] = CurrentOffSetA+32>=M?0.0:A[32*lda];
    plA[48] = CurrentOffSetA+48>=M?0.0:A[48*lda];
    plA[64] = CurrentOffSetA+64>=M?0.0:A[64*lda];
    plA[80] = CurrentOffSetA+80>=M?0.0:A[80*lda];


    barrier(CLK_LOCAL_MEM_FENCE);
    uint offA = idx;
    uint offB = idy;


    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6
    M6x6

    A += 16;
    B += 16;
  } while (--block_k > 0);


  int offset_x = gidx*96+idx;
  int offset_y = gidy*96+ idy;

  if(offset_x>=M || offset_y>=N )
    return;

  C+=offset_x+offset_y*ldc;

  int i = 0;
  do 
  //for (int i=0; i<6; i++)
  {
    C[0     ] = mad(alpha, rC[i][0], 0);
    if(offset_y+16<N)
      C[16*ldc] = mad(alpha, rC[i][1], 0);
    if(offset_y+32<N)
      C[32*ldc] = mad(alpha, rC[i][2], 0);
    if(offset_y+48<N)
      C[48*ldc] = mad(alpha, rC[i][3], 0);
    if(offset_y+64<N)
      C[64*ldc] = mad(alpha, rC[i][4], 0);
    if(offset_y+80<N)
      C[80*ldc] = mad(alpha, rC[i][5], 0);

    C+=16;
    offset_x+=16;
    if(offset_x>=M )
      return;


  }
  while (++i < 6);
}
";

