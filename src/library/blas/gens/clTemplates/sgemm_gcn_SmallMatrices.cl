static const char * sgemm_NT_32_32_16_16x16_2x2__ALPHABETA = "

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
			barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_NT_32_32_16_16x16_2x2__ALPHABETA( __global float const * restrict A,
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
    float rC[2][2]  = {(float)0};
    float rA[1][2];
    float rB[1][2];
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[544];
    __local float lB[544];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
    uint idt = 16*idy + idx;
    uint idxT = idt % 16;
    uint idyT = idt / 16;
    
    A +=  gidx*32+ idxT + idyT*lda;
    B +=  gidy*32+ idxT + idyT*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
        __local float* plA = lA + idyT*33+idxT;
        __local float* plB = lB + idyT*33+idxT;
        plB[0] = B[0+0*ldb];
        plB[16] = B[16+0*ldb];
        	   
	    plA[0] = A[0+0*lda];
        plA[16] = A[16+0*lda];
               
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
        B += ldb<<4;
    //}
	} while (--block_k > 0);

    C+= gidx*32+idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;
    
	C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[0][1] + beta*C[16*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[1][1] + beta*C[16*ldc];
    
}

";



static const char * sgemm_NT_32_32_16_16x16_2x2__ALPHA = "


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
			barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_NT_32_32_16_16x16_2x2__ALPHA( __global float const * restrict A,
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
    float rC[2][2]  = {(float)0};
    float rA[1][2];
    float rB[1][2];

    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[544];
    __local float lB[544];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
    uint idt = 16*idy + idx;
    uint idxT = idt % 16;
    uint idyT = idt / 16;
    
    A +=  gidx*32+ idxT + idyT*lda;
    B +=  gidy*32+ idxT + idyT*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
   // for(unsigned int block_k=0 ; block_k< K ; block_k+=16)
	//{
        __local float* plA = lA + idyT*33+idxT;
        __local float* plB = lB + idyT*33+idxT;
       // barrier(CLK_LOCAL_MEM_FENCE);
        plB[0] = B[0+0*ldb];
        plB[16] = B[16+0*ldb];
	   
	    plA[0] = A[0+0*lda];
        plA[16] = A[16+0*lda];

        
        barrier(CLK_LOCAL_MEM_FENCE);
        uint offA = idx;
        uint offB = idy;

//        #pragma unroll 1
//        for(unsigned int k = 0 ; k < 16; k+=1){
//        }

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
        B += ldb<<4;
    //}
	} while (--block_k > 0);

    C+= gidx*32+idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;
    
	C[0*ldc] = alpha*rC[0][0] ;
    C[16*ldc] = alpha*rC[0][1];
    C+=16;					  
    C[0*ldc] = alpha*rC[1][0] ;
    C[16*ldc] = alpha*rC[1][1];
    
}

";

static const char * sgemm_NT_32_32_16_16x16_2x2__ALPHABETA_BRANCH = "

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
			mem_fence(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_NT_32_32_16_16x16_2x2__ALPHABETA_BRANCH( __global float const * restrict A,
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
    float rC[2][2]  = {(float)0};
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
	int CurrentOffSetB = gidy*32+ idx;
    
    A +=  gidx*32+ idx + idy*lda;
    B +=  gidy*32+ idx + idy*ldb;
    
   
    uint block_k = K >> 4;
    do 
	{
        __local float* plA = lA + idy*33+idx;
        __local float* plB = lB + idy*33+idx;
        barrier(CLK_LOCAL_MEM_FENCE);
		
        plB[0]  = CurrentOffSetB>=N?0.0:B[0];
        plB[16] = CurrentOffSetB+16>=N?0.0:B[16];
	   
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
        B += ldb<<4;
	} while (--block_k > 0);


	int offset_x = gidx*32+idx;
    int offset_y = gidy*32+ idy;

    if(offset_x>=M || offset_y>=N )
      return;

    C+=offset_x+offset_y*ldc;
    
	int i = 0;
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
    
}

";


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char * sgemm_NN_32_32_16_16x16_2x2__ALPHABETA = "

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
            barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_NN_32_32_16_16x16_2x2__ALPHABETA( __global float const * restrict A,
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
    float rC[2][2]  = {(float)0};
    float rA[1][2];
    float rB[1][2];
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[544];
    __local float lB[544];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
    uint idt = 16*idy + idx;
    uint idxT = idt % 16;
    uint idyT = idt / 16;
    
    A +=  gidx*32+ idxT + idyT*lda;
    B +=  (gidy*32+idyT)*ldb + idxT;
    
   
    uint block_k = K >> 4;
    do 
	  {

      __local float* plA = lA + idyT*33+idxT;
      __local float* plB = lB + idxT*33+idyT;
      plB[0] = B[0];
      plB[16] = B[16*ldb];
	   
	    plA[0] = A[0+0*lda];
      plA[16] = A[16+0*lda];
              
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
	  } while (--block_k > 0);

    C+= gidx*32+idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;
    
	  C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[0][1] + beta*C[16*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[1][1] + beta*C[16*ldc];
}

";



static const char * sgemm_NN_32_32_16_16x16_2x2__ALPHA = "

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
			barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_NN_32_32_16_16x16_2x2__ALPHA( __global float const * restrict A,
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
    float rC[2][2]  = {(float)0};
    float rA[1][2];
    float rB[1][2];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[544];
    __local float lB[544];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
    uint idt = 16*idy + idx;
    uint idxT = idt % 16;
    uint idyT = idt / 16;
    
    A +=  gidx*32+ idxT + idyT*lda;
    B +=  (gidy*32+idyT)*ldb + idxT;
    
   
  uint block_k = K >> 4;
  do 
	{
    __local float* plA = lA + idyT*33+idxT;
    __local float* plB = lB + idxT*33+idyT;
    plB[0] = B[0];
    plB[16] = B[16*ldb];
        
	  plA[0] = A[0+0*lda];
    plA[16] = A[16+0*lda];
       
        
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
   
	} while (--block_k > 0);

    C+= gidx*32+idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;
    
	  C[0*ldc] = alpha*rC[0][0] ;
    C[16*ldc] = alpha*rC[0][1];
    C+=16;					  
    C[0*ldc] = alpha*rC[1][0] ;
    C[16*ldc] = alpha*rC[1][1]; 
}

";

static const char * sgemm_NN_32_32_16_16x16_2x2__ALPHABETA_BRANCH = "

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
			mem_fence(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_NN_32_32_16_16x16_2x2__ALPHABETA_BRANCH( __global float const * restrict A,
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
    float rC[2][2]  = {(float)0};
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
   
}

";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char * sgemm_TN_32_32_16_16x16_2x2__ALPHABETA = "

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
            barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_TN_32_32_16_16x16_2x2__ALPHABETA( __global float const * restrict A,
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
    float rC[2][2]  = {(float)0};
    float rA[1][2];
    float rB[1][2];
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[544];
    __local float lB[544];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
    uint idt = 16*idy + idx;
    uint idxT = idt % 16;
    uint idyT = idt / 16;
    
    A += (gidx*32+idyT)*lda+ idxT ;
    B += (gidy*32+idyT)*ldb + idxT;
    
   
    uint block_k = K >> 4;
    do 
	  {

      __local float* plA = lA + idxT*33+idyT;
      __local float* plB = lB + idxT*33+idyT;
      plB[0] = B[0];
      plB[16] = B[16*ldb];
	   
	    plA[0] = A[0];
      plA[16] = A[16*lda];
              
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

      A += 16;
      B += 16;
	  } while (--block_k > 0);

    C+= gidx*32+idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;
    
	  C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[0][1] + beta*C[16*ldc];
    C+=16;
    C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
    C[16*ldc] = alpha*rC[1][1] + beta*C[16*ldc];
}

";



static const char * sgemm_TN_32_32_16_16x16_2x2__ALPHA = "

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
			barrier(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_TN_32_32_16_16x16_2x2__ALPHA( __global float const * restrict A,
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
    float rC[2][2]  = {(float)0};
    float rA[1][2];
    float rB[1][2];
    
    
    A += offsetA;
    B += offsetB;
    C+=offsetC;
    
    __local float lA[544];
    __local float lB[544];
    
    uint gidx = get_group_id(0);
    uint gidy = get_group_id(1);
    uint idx = get_local_id(0);
    uint idy = get_local_id(1);
    
    uint idt = 16*idy + idx;
    uint idxT = idt % 16;
    uint idyT = idt / 16;
    
    A +=  (gidx*32+idyT)*lda+ idxT ;
    B +=  (gidy*32+idyT)*ldb + idxT;
    
   
  uint block_k = K >> 4;
  do 
	{
    __local float* plA = lA + idxT*33+idyT;
    __local float* plB = lB + idxT*33+idyT;
    plB[0] = B[0];
    plB[16] = B[16*ldb];
        
	  plA[0] = A[0];
    plA[16] = A[16*lda];
       
        
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

    A += 16;
    B += 16;
   
	} while (--block_k > 0);

    C+= gidx*32+idx;
    C+= gidy*32*ldc;
    C+= idy*ldc;
    
	  C[0*ldc] = alpha*rC[0][0] ;
    C[16*ldc] = alpha*rC[0][1];
    C+=16;					  
    C[0*ldc] = alpha*rC[1][0] ;
    C[16*ldc] = alpha*rC[1][1]; 
}

";

static const char * sgemm_TN_32_32_16_16x16_2x2__ALPHABETA_BRANCH = "

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
			mem_fence(CLK_LOCAL_MEM_FENCE);

__attribute__((reqd_work_group_size(16,16,1)))

__kernel void sgemm_TN_32_32_16_16x16_2x2__ALPHABETA_BRANCH( __global float const * restrict A,
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
    float rC[2][2]  = {(float)0};
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
    
    int CurrentOffSetA = gidx*32+ idy;
    int CurrentOffSetB = gidy*32+ idy;

    A +=  (gidx*32+idy)*lda + idx;
    B +=  (gidy*32+idy)*ldb + idx;
    
   
    uint block_k = K >> 4;
    do 
    {
      __local float* plA = lA + idx*33+idy;
      __local float* plB = lB + idx*33+idy;
      barrier(CLK_LOCAL_MEM_FENCE);
  
      plB[0]  = CurrentOffSetB>=N?0.0:B[0];
      plB[16] = CurrentOffSetB+16>=N?0.0:B[16*ldb];

      plA[0]  = CurrentOffSetA>=M?0.0:A[0];
      plA[16] = CurrentOffSetA+16>=M?0.0:A[16*lda];


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

      A += 16;
      B += 16;
    } while (--block_k > 0);


    int offset_x = gidx*32+idx;
    int offset_y = gidy*32+ idy;

    if(offset_x>=M || offset_y>=N )
      return;

    C+=offset_x+offset_y*ldc;

    int i = 0;
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
}

";

