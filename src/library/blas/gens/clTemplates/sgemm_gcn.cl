static const char * sgemm_NT_96_96_16_16x16_6x6__ALPHABETA = "

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
			barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_NT_96_96_16_16x16_6x6__ALPHABETA( __global float const * restrict A,
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
    
//    GPtr uA, uB;
//    uA.floatv = (__global float *)A;
//    uB.floatv = (__global float *)B;
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
    uint idt = 16*idy + idx;
    uint idxT = idt % 16;
    uint idyT = idt / 16;
    
    A +=  gidx*96+ idxT + idyT*lda;
    B +=  gidy*96+ idxT + idyT*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
   // for(unsigned int block_k=0 ; block_k< K ; block_k+=16)
	//{
        __local float* plA = lA + idyT*97+idxT;
        __local float* plB = lB + idyT*97+idxT;
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

";



static const char * sgemm_NT_96_96_16_16x16_6x6__ALPHA = "

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
			barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_NT_96_96_16_16x16_6x6__ALPHA( __global float const * restrict A,
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
    
//    GPtr uA, uB;
//    uA.floatv = (__global float *)A;
//    uB.floatv = (__global float *)B;
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
    uint idt = 16*idy + idx;
    uint idxT = idt % 16;
    uint idyT = idt / 16;
    
    A +=  gidx*96+ idxT + idyT*lda;
    B +=  gidy*96+ idxT + idyT*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
   // for(unsigned int block_k=0 ; block_k< K ; block_k+=16)
	//{
        __local float* plA = lA + idyT*97+idxT;
        __local float* plB = lB + idyT*97+idxT;
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
    
	C[0*ldc] = alpha*rC[0][0] ;
    C[16*ldc] = alpha*rC[0][1];
    C[32*ldc] = alpha*rC[0][2];
    C[48*ldc] = alpha*rC[0][3];
    C[64*ldc] = alpha*rC[0][4];
    C[80*ldc] = alpha*rC[0][5];
    C+=16;					  
    C[0*ldc] = alpha*rC[1][0] ;
    C[16*ldc] = alpha*rC[1][1];
    C[32*ldc] = alpha*rC[1][2];
    C[48*ldc] = alpha*rC[1][3];
    C[64*ldc] = alpha*rC[1][4];
    C[80*ldc] = alpha*rC[1][5];
    C+=16;					  
    C[0*ldc] = alpha*rC[2][0] ;
    C[16*ldc] = alpha*rC[2][1];
    C[32*ldc] = alpha*rC[2][2];
    C[48*ldc] = alpha*rC[2][3];
    C[64*ldc] = alpha*rC[2][4];
    C[80*ldc] = alpha*rC[2][5];
    C+=16;					  
    C[0*ldc] = alpha*rC[3][0] ;
    C[16*ldc] = alpha*rC[3][1];
    C[32*ldc] = alpha*rC[3][2];
    C[48*ldc] = alpha*rC[3][3];
    C[64*ldc] = alpha*rC[3][4];
    C[80*ldc] = alpha*rC[3][5];
    C+=16;					  
    C[0*ldc] = alpha*rC[4][0] ;
    C[16*ldc] = alpha*rC[4][1];
    C[32*ldc] = alpha*rC[4][2];
    C[48*ldc] = alpha*rC[4][3];
    C[64*ldc] = alpha*rC[4][4];
    C[80*ldc] = alpha*rC[4][5];
    C+=16;					  
    C[0*ldc] = alpha*rC[5][0] ;
    C[16*ldc] = alpha*rC[5][1];
    C[32*ldc] = alpha*rC[5][2];
    C[48*ldc] = alpha*rC[5][3];
    C[64*ldc] = alpha*rC[5][4];
    C[80*ldc] = alpha*rC[5][5];
   
}

";


static const char * sgemm_NT_64_64_16_16x16_4x4__ALPHABETA = "

#define  M4x4 \
            rA[0][0] = lA[offA + 0];				  \
            rA[0][1] = lA[offA + 16];				  \
            rA[0][2] = lA[offA + 32];				  \
            rA[0][3] = lA[offA + 48];				  \
            rB[0][0] = lB[offB + 0];				  \
            rB[0][1] = lB[offB + 16];				  \
            rB[0][2] = lB[offB + 32];				  \
            rB[0][3] = lB[offB + 48];				  \
            offA += 65;								  \
            offB += 65;								  \
            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]); \
            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]); \
            rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]); \
            rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]); \
            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]); \
            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]); \
            rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]); \
            rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]); \
            rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]); \
            rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]); \
            rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]); \
            rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]); \
            rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]); \
            rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]); \
            rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]); \
            rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]); \
			barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_NT_64_64_16_16x16_4x4__ALPHABETA( __global float const * restrict A,
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
    float rC[4][4]  = {(float)0};
    float rA[1][4];
    float rB[1][4];
    
//    GPtr uA, uB;
//    uA.floatv = (__global float *)A;
//    uB.floatv = (__global float *)B;
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1056];
    __local float lB[1056];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
    uint idt = 16*idy + idx;
    uint idxT = idt % 16;
    uint idyT = idt / 16;
    
    A +=  gidx*64+ idxT + idyT*lda;
    B +=  gidy*64+ idxT + idyT*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
   // for(unsigned int block_k=0 ; block_k< K ; block_k+=16)
	//{
        __local float* plA = lA + idyT*65+idxT;
        __local float* plB = lB + idyT*65+idxT;
       // barrier(CLK_LOCAL_MEM_FENCE);
        plB[0] = B[0+0*ldb];
        plB[16] = B[16+0*ldb];
        plB[32] = B[32+0*ldb];
        plB[48] = B[48+0*ldb];
	   
	    plA[0] = A[0+0*lda];
        plA[16] = A[16+0*lda];
        plA[32] = A[32+0*lda];
        plA[48] = A[48+0*lda];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;

//        #pragma unroll 1
//        for(unsigned int k = 0 ; k < 16; k+=1){
//        }

        M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4

        A += lda<<4;
        B += ldb<<4;
    //}
	} while (--block_k > 0);

    C+= gidx*64+idx;
    C+= gidy*64*ldc;
    C+= idy*ldc;
    
	C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[0][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[0][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[0][3] + beta*C[48*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[1][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[1][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[1][3] + beta*C[48*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[2][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[2][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[2][3] + beta*C[48*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[3][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[3][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[3][3] + beta*C[48*ldc];

   
}

";



static const char * sgemm_NT_64_64_16_16x16_4x4__ALPHA = "

#define  M4x4 \
            rA[0][0] = lA[offA + 0];				  \
            rA[0][1] = lA[offA + 16];				  \
            rA[0][2] = lA[offA + 32];				  \
            rA[0][3] = lA[offA + 48];				  \
            rB[0][0] = lB[offB + 0];				  \
            rB[0][1] = lB[offB + 16];				  \
            rB[0][2] = lB[offB + 32];				  \
            rB[0][3] = lB[offB + 48];				  \
            offA += 65;								  \
            offB += 65;								  \
            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]); \
            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]); \
            rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]); \
            rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]); \
            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]); \
            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]); \
            rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]); \
            rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]); \
            rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]); \
            rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]); \
            rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]); \
            rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]); \
            rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]); \
            rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]); \
            rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]); \
            rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]); \
			barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_NT_64_64_16_16x16_4x4__ALPHA( __global float const * restrict A,
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
    float rC[4][4]  = {(float)0};
    float rA[1][4];
    float rB[1][4];
    
//    GPtr uA, uB;
//    uA.floatv = (__global float *)A;
//    uB.floatv = (__global float *)B;
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1056];
    __local float lB[1056];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
    uint idt = 16*idy + idx;
    uint idxT = idt % 16;
    uint idyT = idt / 16;
    
    A +=  gidx*64+ idxT + idyT*lda;
    B +=  gidy*64+ idxT + idyT*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
        __local float* plA = lA + idyT*65+idxT;
        __local float* plB = lB + idyT*65+idxT;
        plB[0] = B[0+0*ldb];
        plB[16] = B[16+0*ldb];
        plB[32] = B[32+0*ldb];
        plB[48] = B[48+0*ldb];
	   
	    plA[0] = A[0+0*lda];
        plA[16] = A[16+0*lda];
        plA[32] = A[32+0*lda];
        plA[48] = A[48+0*lda];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;


        M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4

        A += lda<<4;
        B += ldb<<4;
    //}
	} while (--block_k > 0);

    C+= gidx*64+idx;
    C+= gidy*64*ldc;
    C+= idy*ldc;
    
	C[0*ldc] = alpha*rC[0][0] ;
    C[16*ldc] = alpha*rC[0][1];
    C[32*ldc] = alpha*rC[0][2];
    C[48*ldc] = alpha*rC[0][3];

    C+=16;					  
    C[0*ldc] = alpha*rC[1][0] ;
    C[16*ldc] = alpha*rC[1][1];
    C[32*ldc] = alpha*rC[1][2];
    C[48*ldc] = alpha*rC[1][3];

    C+=16;					  
    C[0*ldc] = alpha*rC[2][0] ;
    C[16*ldc] = alpha*rC[2][1];
    C[32*ldc] = alpha*rC[2][2];
    C[48*ldc] = alpha*rC[2][3];

    C+=16;					  
    C[0*ldc] = alpha*rC[3][0] ;
    C[16*ldc] = alpha*rC[3][1];
    C[32*ldc] = alpha*rC[3][2];
    C[48*ldc] = alpha*rC[3][3];

   
}

";


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char * sgemm_NN_96_96_16_16x16_6x6__ALPHABETA = "

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
			barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_NN_96_96_16_16x16_6x6__ALPHABETA( __global float const * restrict A,
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
    
//    GPtr uA, uB;
//    uA.floatv = (__global float *)A;
//    uB.floatv = (__global float *)B;
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1552];
    __local float lB[1552];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
    uint idt = 16*idy + idx;
    uint idxT = idt % 16;
    uint idyT = idt / 16;
    
    A +=  gidx*96+ idxT + idyT*lda;
    B +=  (gidy*96+idyT)*ldb + idxT;
    
   
    uint block_k = K >> 4;
    do 
	{

        __local float* plA = lA + idyT*97+idxT;
        __local float* plB = lB + idxT*97+idyT;
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

";



static const char * sgemm_NN_96_96_16_16x16_6x6__ALPHA = "

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
			barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_NN_96_96_16_16x16_6x6__ALPHA( __global float const * restrict A,
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
    
    uint idt = 16*idy + idx;
    uint idxT = idt % 16;
    uint idyT = idt / 16;
    
    A +=  gidx*96+ idxT + idyT*lda;
    B +=  (gidy*96+idyT)*ldb + idxT;
    
   
    uint block_k = K >> 4;
    do 
	{

        __local float* plA = lA + idyT*97+idxT;
        __local float* plB = lB + idxT*97+idyT;
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

    C+= gidx*96+idx;
    C+= gidy*96*ldc;
    C+= idy*ldc;
    
	C[0*ldc] = alpha*rC[0][0] ;
    C[16*ldc] = alpha*rC[0][1];
    C[32*ldc] = alpha*rC[0][2];
    C[48*ldc] = alpha*rC[0][3];
    C[64*ldc] = alpha*rC[0][4];
    C[80*ldc] = alpha*rC[0][5];
    C+=16;					  
    C[0*ldc] = alpha*rC[1][0] ;
    C[16*ldc] = alpha*rC[1][1];
    C[32*ldc] = alpha*rC[1][2];
    C[48*ldc] = alpha*rC[1][3];
    C[64*ldc] = alpha*rC[1][4];
    C[80*ldc] = alpha*rC[1][5];
    C+=16;					  
    C[0*ldc] = alpha*rC[2][0] ;
    C[16*ldc] = alpha*rC[2][1];
    C[32*ldc] = alpha*rC[2][2];
    C[48*ldc] = alpha*rC[2][3];
    C[64*ldc] = alpha*rC[2][4];
    C[80*ldc] = alpha*rC[2][5];
    C+=16;					  
    C[0*ldc] = alpha*rC[3][0] ;
    C[16*ldc] = alpha*rC[3][1];
    C[32*ldc] = alpha*rC[3][2];
    C[48*ldc] = alpha*rC[3][3];
    C[64*ldc] = alpha*rC[3][4];
    C[80*ldc] = alpha*rC[3][5];
    C+=16;					  
    C[0*ldc] = alpha*rC[4][0] ;
    C[16*ldc] = alpha*rC[4][1];
    C[32*ldc] = alpha*rC[4][2];
    C[48*ldc] = alpha*rC[4][3];
    C[64*ldc] = alpha*rC[4][4];
    C[80*ldc] = alpha*rC[4][5];
    C+=16;					  
    C[0*ldc] = alpha*rC[5][0] ;
    C[16*ldc] = alpha*rC[5][1];
    C[32*ldc] = alpha*rC[5][2];
    C[48*ldc] = alpha*rC[5][3];
    C[64*ldc] = alpha*rC[5][4];
    C[80*ldc] = alpha*rC[5][5];
   
}

";

static const char * sgemm_NN_64_64_16_16x16_4x4__ALPHABETA = "


#define  M4x4 \
            rA[0][0] = lA[offA + 0];				  \
            rA[0][1] = lA[offA + 16];				  \
            rA[0][2] = lA[offA + 32];				  \
            rA[0][3] = lA[offA + 48];				  \
            rB[0][0] = lB[offB + 0];				  \
            rB[0][1] = lB[offB + 16];				  \
            rB[0][2] = lB[offB + 32];				  \
            rB[0][3] = lB[offB + 48];				  \
            offA += 65;								  \
            offB += 65;								  \
            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]); \
            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]); \
            rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]); \
            rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]); \
            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]); \
            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]); \
            rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]); \
            rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]); \
            rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]); \
            rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]); \
            rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]); \
            rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]); \
            rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]); \
            rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]); \
            rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]); \
            rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]); \
			barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NN_64_64_16_16x16_4x4__ALPHABETA( __global float const * restrict A,
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
    float rC[4][4]  = {(float)0};
    float rA[1][4];
    float rB[1][4];
    

    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1056];
    __local float lB[1056];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);

    A +=  gidx*64+ idx + idy*lda;
    B +=  (gidy*64+idy)*ldb+ idx;
    
   
    uint block_k = K >> 4;
    do 
	{
        __local float* plA = lA + idy*65+idx;
        __local float* plB = lB + idx*65+idy;
        plB[0] = B[0];
        plB[16] = B[16*ldb];
        plB[32] = B[32*ldb];
        plB[48] = B[48*ldb];
   
	   
	    plA[0] = A[0+0*lda];
        plA[16] = A[16+0*lda];
        plA[32] = A[32+0*lda];
        plA[48] = A[48+0*lda];


        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;



        M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4

        A += lda<<4;
        B += 16;
	} while (--block_k > 0);

    C+= gidx*64+idx;
    C+= gidy*64*ldc;
    C+= idy*ldc;
    
	C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[0][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[0][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[0][3] + beta*C[48*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[1][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[1][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[1][3] + beta*C[48*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[2][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[2][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[2][3] + beta*C[48*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[3][1] + beta*C[16*ldc];
    C[32*ldc] = alpha*rC[3][2] + beta*C[32*ldc];
    C[48*ldc] = alpha*rC[3][3] + beta*C[48*ldc];
    
   
}
";


static const char * sgemm_NN_64_64_16_16x16_4x4__ALPHA = "


#define  M4x4 \
            rA[0][0] = lA[offA + 0];				  \
            rA[0][1] = lA[offA + 16];				  \
            rA[0][2] = lA[offA + 32];				  \
            rA[0][3] = lA[offA + 48];				  \
            rB[0][0] = lB[offB + 0];				  \
            rB[0][1] = lB[offB + 16];				  \
            rB[0][2] = lB[offB + 32];				  \
            rB[0][3] = lB[offB + 48];				  \
            offA += 65;								  \
            offB += 65;								  \
            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]); \
            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]); \
            rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]); \
            rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]); \
            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]); \
            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]); \
            rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]); \
            rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]); \
            rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]); \
            rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]); \
            rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]); \
            rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]); \
            rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]); \
            rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]); \
            rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]); \
            rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]); \
			barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))
__kernel void sgemm_NN_64_64_16_16x16_4x4__ALPHA( __global float const * restrict A,
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
    float rC[4][4]  = {(float)0};
    float rA[1][4];
    float rB[1][4];
    

    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[1056];
    __local float lB[1056];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);

    A +=  gidx*64+ idx + idy*lda;
    B +=  (gidy*64+idy)*ldb+ idx;
    
   
    uint block_k = K >> 4;
    do 
	{
        __local float* plA = lA + idy*65+idx;
        __local float* plB = lB + idx*65+idy;
        plB[0] = B[0];
        plB[16] = B[16*ldb];
        plB[32] = B[32*ldb];
        plB[48] = B[48*ldb];
   
	   
	    plA[0] = A[0+0*lda];
        plA[16] = A[16+0*lda];
        plA[32] = A[32+0*lda];
        plA[48] = A[48+0*lda];


        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;



        M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4
		M4x4

        A += lda<<4;
        B += 16;
	} while (--block_k > 0);

    C+= gidx*64+idx;
    C+= gidy*64*ldc;
    C+= idy*ldc;
    
	C[0*ldc] = alpha*rC[0][0] ;
    C[16*ldc] = alpha*rC[0][1];
    C[32*ldc] = alpha*rC[0][2];
    C[48*ldc] = alpha*rC[0][3];
    C+=16;
    C[0*ldc] = alpha*rC[1][0] ;
    C[16*ldc] = alpha*rC[1][1];
    C[32*ldc] = alpha*rC[1][2];
    C[48*ldc] = alpha*rC[1][3];
    C+=16;
    C[0*ldc] = alpha*rC[2][0] ;
    C[16*ldc] = alpha*rC[2][1];
    C[32*ldc] = alpha*rC[2][2];
    C[48*ldc] = alpha*rC[2][3];
    C+=16;
    C[0*ldc] = alpha*rC[3][0] ;
    C[16*ldc] = alpha*rC[3][1];
    C[32*ldc] = alpha*rC[3][2];
    C[48*ldc] = alpha*rC[3][3];
    
   
}
";








/************************************************************************************/
static const char * sgemm_TN_96_96_16_16x16_6x6__ALPHABETA = "

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
			barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_TN_96_96_16_16x16_6x6__ALPHABETA( __global float const * restrict A,
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

  uint idt = 16*idy + idx;
  uint idxT = idt % 16;
  uint idyT = idt / 16;

  A +=  gidx*96*lda+ idxT + idyT*lda;
  B +=  gidy*96*ldb+ idxT + idyT*ldb;


  uint block_k = K >> 4;
  do 
  {
    __local float* plA = lA + idxT*97+idyT;
    __local float* plB = lB + idxT*97+idyT;
    // barrier(CLK_LOCAL_MEM_FENCE);
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
";


static const char * sgemm_TN_96_96_16_16x16_6x6__ALPHA = "

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
			barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_TN_96_96_16_16x16_6x6__ALPHA( __global float const * restrict A,
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

  uint idt = 16*idy + idx;
  uint idxT = idt % 16;
  uint idyT = idt / 16;

  A +=  gidx*96*lda+ idxT + idyT*lda;
  B +=  gidy*96*ldb+ idxT + idyT*ldb;


  uint block_k = K >> 4;
  do 
  {
    __local float* plA = lA + idxT*97+idyT;
    __local float* plB = lB + idxT*97+idyT;
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

  C[0*ldc] = alpha*rC[0][0] ;
  C[16*ldc] = alpha*rC[0][1];
  C[32*ldc] = alpha*rC[0][2];
  C[48*ldc] = alpha*rC[0][3];
  C[64*ldc] = alpha*rC[0][4];
  C[80*ldc] = alpha*rC[0][5];
  C+=16;
  C[0*ldc] = alpha*rC[1][0] ;
  C[16*ldc] = alpha*rC[1][1];
  C[32*ldc] = alpha*rC[1][2];
  C[48*ldc] = alpha*rC[1][3];
  C[64*ldc] = alpha*rC[1][4];
  C[80*ldc] = alpha*rC[1][5];
  C+=16;
  C[0*ldc] = alpha*rC[2][0] ;
  C[16*ldc] = alpha*rC[2][1];
  C[32*ldc] = alpha*rC[2][2];
  C[48*ldc] = alpha*rC[2][3];
  C[64*ldc] = alpha*rC[2][4];
  C[80*ldc] = alpha*rC[2][5];
  C+=16;
  C[0*ldc] = alpha*rC[3][0] ;
  C[16*ldc] = alpha*rC[3][1];
  C[32*ldc] = alpha*rC[3][2];
  C[48*ldc] = alpha*rC[3][3];
  C[64*ldc] = alpha*rC[3][4];
  C[80*ldc] = alpha*rC[3][5];
  C+=16;
  C[0*ldc] = alpha*rC[4][0] ;
  C[16*ldc] = alpha*rC[4][1];
  C[32*ldc] = alpha*rC[4][2];
  C[48*ldc] = alpha*rC[4][3];
  C[64*ldc] = alpha*rC[4][4];
  C[80*ldc] = alpha*rC[4][5];
  C+=16;
  C[0*ldc] = alpha*rC[5][0] ;
  C[16*ldc] = alpha*rC[5][1];
  C[32*ldc] = alpha*rC[5][2];
  C[48*ldc] = alpha*rC[5][3];
  C[64*ldc] = alpha*rC[5][4];
  C[80*ldc] = alpha*rC[5][5];

}
";


static const char * sgemm_TN_64_64_16_16x16_4x4__ALPHABETA = "

#define  M4x4 \
            rA[0][0] = lA[offA + 0];				  \
            rA[0][1] = lA[offA + 16];				  \
            rA[0][2] = lA[offA + 32];				  \
            rA[0][3] = lA[offA + 48];				  \
            rB[0][0] = lB[offB + 0];				  \
            rB[0][1] = lB[offB + 16];				  \
            rB[0][2] = lB[offB + 32];				  \
            rB[0][3] = lB[offB + 48];				  \
            offA += 65;								  \
            offB += 65;								  \
            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]); \
            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]); \
            rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]); \
            rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]); \
            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]); \
            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]); \
            rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]); \
            rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]); \
            rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]); \
            rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]); \
            rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]); \
            rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]); \
            rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]); \
            rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]); \
            rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]); \
            rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]); \
			      barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_TN_64_64_16_16x16_4x4__ALPHABETA( __global float const * restrict A,
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
  float rC[4][4]  = {(float)0};
  float rA[1][4];
  float rB[1][4];


  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local float lA[1056];
  __local float lB[1056];

  uint gidx = get_group_id(0);
  uint gidy = get_group_id(1);
  uint idx = get_local_id(0);
  uint idy = get_local_id(1);

  uint idt = 16*idy + idx;
  uint idxT = idt % 16;
  uint idyT = idt / 16;

  A +=  gidx*64*lda+ idxT + idyT*lda;
  B +=  gidy*64*ldb+ idxT + idyT*ldb;


  uint block_k = K >> 4;
  do 
  {
    __local float* plA = lA + idxT*65+idyT;
    __local float* plB = lB + idxT*65+idyT;
    plB[0] = B[0];
    plB[16] = B[16*ldb];
    plB[32] = B[32*ldb];
    plB[48] = B[48*ldb];

    plA[0] = A[0];
    plA[16] = A[16*lda];
    plA[32] = A[32*lda];
    plA[48] = A[48*lda];


    barrier(CLK_LOCAL_MEM_FENCE);
    uint offA = idx;
    uint offB = idy;


    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4

    A += 16;
    B += 16;
    
  } while (--block_k > 0);

  C+= gidx*64+idx;
  C+= gidy*64*ldc;
  C+= idy*ldc;

  C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
  C[16*ldc] = alpha*rC[0][1] + beta*C[16*ldc];
  C[32*ldc] = alpha*rC[0][2] + beta*C[32*ldc];
  C[48*ldc] = alpha*rC[0][3] + beta*C[48*ldc];

  C+=16;
  C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
  C[16*ldc] = alpha*rC[1][1] + beta*C[16*ldc];
  C[32*ldc] = alpha*rC[1][2] + beta*C[32*ldc];
  C[48*ldc] = alpha*rC[1][3] + beta*C[48*ldc];

  C+=16;
  C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
  C[16*ldc] = alpha*rC[2][1] + beta*C[16*ldc];
  C[32*ldc] = alpha*rC[2][2] + beta*C[32*ldc];
  C[48*ldc] = alpha*rC[2][3] + beta*C[48*ldc];

  C+=16;
  C[0*ldc] = alpha*rC[3][0] + beta*C[0*ldc];
  C[16*ldc] = alpha*rC[3][1] + beta*C[16*ldc];
  C[32*ldc] = alpha*rC[3][2] + beta*C[32*ldc];
  C[48*ldc] = alpha*rC[3][3] + beta*C[48*ldc];
}
";



static const char * sgemm_TN_64_64_16_16x16_4x4__ALPHA = "

#define  M4x4 \
            rA[0][0] = lA[offA + 0];				  \
            rA[0][1] = lA[offA + 16];				  \
            rA[0][2] = lA[offA + 32];				  \
            rA[0][3] = lA[offA + 48];				  \
            rB[0][0] = lB[offB + 0];				  \
            rB[0][1] = lB[offB + 16];				  \
            rB[0][2] = lB[offB + 32];				  \
            rB[0][3] = lB[offB + 48];				  \
            offA += 65;								  \
            offB += 65;								  \
            rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]); \
            rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]); \
            rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]); \
            rC[3][0]=mad(rA[0][3],rB[0][0],rC[3][0]); \
            rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]); \
            rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]); \
            rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]); \
            rC[3][1]=mad(rA[0][3],rB[0][1],rC[3][1]); \
            rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]); \
            rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]); \
            rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]); \
            rC[3][2]=mad(rA[0][3],rB[0][2],rC[3][2]); \
            rC[0][3]=mad(rA[0][0],rB[0][3],rC[0][3]); \
            rC[1][3]=mad(rA[0][1],rB[0][3],rC[1][3]); \
            rC[2][3]=mad(rA[0][2],rB[0][3],rC[2][3]); \
            rC[3][3]=mad(rA[0][3],rB[0][3],rC[3][3]); \
			      barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_TN_64_64_16_16x16_4x4__ALPHA( __global float const * restrict A,
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
  float rC[4][4]  = {(float)0};
  float rA[1][4];
  float rB[1][4];


  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local float lA[1056];
  __local float lB[1056];

  uint gidx = get_group_id(0);
  uint gidy = get_group_id(1);
  uint idx = get_local_id(0);
  uint idy = get_local_id(1);

  uint idt = 16*idy + idx;
  uint idxT = idt % 16;
  uint idyT = idt / 16;

  A +=  gidx*64*lda+ idxT + idyT*lda;
  B +=  gidy*64*ldb+ idxT + idyT*ldb;


  uint block_k = K >> 4;
  do 
  {
    __local float* plA = lA + idxT*65+idyT;
    __local float* plB = lB + idxT*65+idyT;
    plB[0] = B[0];
    plB[16] = B[16*ldb];
    plB[32] = B[32*ldb];
    plB[48] = B[48*ldb];

    plA[0] = A[0];
    plA[16] = A[16*lda];
    plA[32] = A[32*lda];
    plA[48] = A[48*lda];


    barrier(CLK_LOCAL_MEM_FENCE);
    uint offA = idx;
    uint offB = idy;


    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4
    M4x4

    A += 16;
    B += 16;
    
  } while (--block_k > 0);

  C+= gidx*64+idx;
  C+= gidy*64*ldc;
  C+= idy*ldc;

  C[0*ldc] = alpha*rC[0][0]  ;
  C[16*ldc] = alpha*rC[0][1] ;
  C[32*ldc] = alpha*rC[0][2] ;
  C[48*ldc] = alpha*rC[0][3] ;

  C+=16;
  C[0*ldc] = alpha*rC[1][0] ; 
  C[16*ldc] = alpha*rC[1][1] ;
  C[32*ldc] = alpha*rC[1][2] ;
  C[48*ldc] = alpha*rC[1][3] ;

  C+=16;
  C[0*ldc] = alpha*rC[2][0]  ;
  C[16*ldc] = alpha*rC[2][1] ;
  C[32*ldc] = alpha*rC[2][2] ;
  C[48*ldc] = alpha*rC[2][3] ;

  C+=16;
  C[0*ldc] = alpha*rC[3][0]  ;
  C[16*ldc] = alpha*rC[3][1] ;
  C[32*ldc] = alpha*rC[3][2] ;
  C[48*ldc] = alpha*rC[3][3] ;
}
";
