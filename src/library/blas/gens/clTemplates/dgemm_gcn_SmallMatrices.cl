
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




static const char * dgemm_NT_24_24_8_8x8_3x3__ALPHABETA = "

__attribute__((reqd_work_group_size(8,8,1)))
  __kernel void dgemm_NT_24_24_8_8x8_3x3__ALPHABETA( __global double const * restrict A, 
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
  double rC[3][3]  = {(double)0};
  double rA[1][3];
  double rB[1][3];

  double PreFetchA[3];
  double PreFetchB[3];

  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[192];
  __local double lB[192];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*24+ idxT + idyT*lda;
  B +=  gidy*24+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*24+idxT;
  __local double* plB = lB + idyT*24+idxT;

  plA[0] = A[0];
  plA[8] = A[8];
  plA[16] = A[16];
  
  plB[0] = B[0];
	plB[8] = B[8];
  plB[16] = B[16];
  
 
	
  barrier(CLK_LOCAL_MEM_FENCE);


  //for( int block_k=0 ; block_k< K ; block_k+=8)
  uint block_k = K >> 3;
  do
  {
    //barrier(CLK_LOCAL_MEM_FENCE);
    A += 8*lda;
    B += 8*ldb;

    PreFetchA[0] = A[0];
    PreFetchA[1] = A[8];
    PreFetchA[2] = A[16];
   
    PreFetchB[0] = B[0];
    PreFetchB[1] = B[8];
    PreFetchB[2] = B[16];
    
    int offA = idx;
    int offB = idy;



    for( int k = 0 ; k < 8; k+=1)
    {
      rA[0][0] = lA[offA + 0];
      rA[0][1] = lA[offA + 8];
      rA[0][2] = lA[offA + 16];
     
      rB[0][0] = lB[offB + 0];
      rB[0][1] = lB[offB + 8];
      rB[0][2] = lB[offB + 16];
      
      offA += 24;
      offB += 24;
			
      rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
      rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
      rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
  
      rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
      rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
      rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
  
      rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
      rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
      rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
     
    }

    barrier(CLK_LOCAL_MEM_FENCE);
    plA[0]   = PreFetchA[0];
    plA[8]  = PreFetchA[1];
    plA[16] = PreFetchA[2];
    
    plB[0]   = PreFetchB[0];
    plB[8]  = PreFetchB[1];
    plB[16] = PreFetchB[2];
    
    barrier(CLK_LOCAL_MEM_FENCE);

    //  A += 8*lda;
    //  B += 8*ldb;
  }
  while (--block_k > 0);

  C+= gidx*24;
  C+= idx;
  C+= gidy*24*ldc;
  C+= idy*ldc;
	
  C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[0][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[0][2] + beta*C[16*ldc];
  
  C+=8;
  C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[1][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[1][2] + beta*C[16*ldc];
  
  C+=8;
  C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[2][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[2][2] + beta*C[16*ldc];
  

}

";



static const char * dgemm_NT_16_16_8_8x8_2x2__ALPHABETA = "
__attribute__((reqd_work_group_size(8,8,1)))
  __kernel void dgemm_NT_16_16_8_8x8_2x2__ALPHABETA( __global double const * restrict A, 
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
  double rC[2][2]  = {(double)0};
  double rA[1][2];
  double rB[1][2];

  double PreFetchA[2];
  double PreFetchB[2];

  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[128];
  __local double lB[128];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*16+ idxT + idyT*lda;
  B +=  gidy*16+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*16+idxT;
  __local double* plB = lB + idyT*16+idxT;

  plA[0] = A[0];
  plA[8] = A[8];
  
  plB[0] = B[0];
  plB[8] = B[8];
  
 
	
  barrier(CLK_LOCAL_MEM_FENCE);


  //for( int block_k=0 ; block_k< K ; block_k+=8)
  uint block_k = K >> 3;
  do
  {
    //barrier(CLK_LOCAL_MEM_FENCE);
    A += 8*lda;
    B += 8*ldb;

    PreFetchA[0] = A[0];
    PreFetchA[1] = A[8];
   
    PreFetchB[0] = B[0];
    PreFetchB[1] = B[8];
    
    int offA = idx;
    int offB = idy;



    for( int k = 0 ; k < 8; k+=1)
    {
      rA[0][0] = lA[offA + 0];
      rA[0][1] = lA[offA + 8];
     
      rB[0][0] = lB[offB + 0];
      rB[0][1] = lB[offB + 8];
      
      offA += 16;
      offB += 16;
			
      rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
      rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
  
      rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
      rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
       
    }

    barrier(CLK_LOCAL_MEM_FENCE);
    plA[0]   = PreFetchA[0];
    plA[8]  = PreFetchA[1];
    
    plB[0]   = PreFetchB[0];
    plB[8]  = PreFetchB[1];
    
    barrier(CLK_LOCAL_MEM_FENCE);

    //  A += 8*lda;
    //  B += 8*ldb;
  }
  while (--block_k > 0);

  C+= gidx*16;
  C+= idx;
  C+= gidy*16*ldc;
  C+= idy*ldc;
	
  C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[0][1] + beta*C[8*ldc];
  
  C+=8;
  C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[1][1] + beta*C[8*ldc]; 

}
";



static const char * dgemm_NT_24_24_8_8x8_3x3__ALPHA = "

__attribute__((reqd_work_group_size(8,8,1)))
  __kernel void dgemm_NT_24_24_8_8x8_3x3__ALPHA( __global double const * restrict A, 
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
  double rC[3][3]  = {(double)0};
  double rA[1][3];
  double rB[1][3];

  double PreFetchA[3];
  double PreFetchB[3];

  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[192];
  __local double lB[192];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*24+ idxT + idyT*lda;
  B +=  gidy*24+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*24+idxT;
  __local double* plB = lB + idyT*24+idxT;

  plA[0] = A[0];
  plA[8] = A[8];
  plA[16] = A[16];
  
  plB[0] = B[0];
	plB[8] = B[8];
  plB[16] = B[16];
  
 
	
  barrier(CLK_LOCAL_MEM_FENCE);


  //for( int block_k=0 ; block_k< K ; block_k+=8)
  uint block_k = K >> 3;
  do
  {
    //barrier(CLK_LOCAL_MEM_FENCE);
    A += 8*lda;
    B += 8*ldb;

    PreFetchA[0] = A[0];
    PreFetchA[1] = A[8];
    PreFetchA[2] = A[16];
   
    PreFetchB[0] = B[0];
    PreFetchB[1] = B[8];
    PreFetchB[2] = B[16];
    
    int offA = idx;
    int offB = idy;



    for( int k = 0 ; k < 8; k+=1)
    {
      rA[0][0] = lA[offA + 0];
      rA[0][1] = lA[offA + 8];
      rA[0][2] = lA[offA + 16];
     
      rB[0][0] = lB[offB + 0];
      rB[0][1] = lB[offB + 8];
      rB[0][2] = lB[offB + 16];
      
      offA += 24;
      offB += 24;
			
      rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
      rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
      rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
  
      rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
      rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
      rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
  
      rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
      rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
      rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
     
    }

    barrier(CLK_LOCAL_MEM_FENCE);
    plA[0]   = PreFetchA[0];
    plA[8]  = PreFetchA[1];
    plA[16] = PreFetchA[2];
    
    plB[0]   = PreFetchB[0];
    plB[8]  = PreFetchB[1];
    plB[16] = PreFetchB[2];
    
    barrier(CLK_LOCAL_MEM_FENCE);

    //  A += 8*lda;
    //  B += 8*ldb;
  }
  while (--block_k > 0);

  C+= gidx*24;
  C+= idx;
  C+= gidy*24*ldc;
  C+= idy*ldc;
	
  C[0*ldc] = alpha*rC[0][0] ;
  C[8*ldc] = alpha*rC[0][1] ;
  C[16*ldc] = alpha*rC[0][2];
  							
  C+=8;						
  C[0*ldc] = alpha*rC[1][0] ;
  C[8*ldc] = alpha*rC[1][1] ;
  C[16*ldc] = alpha*rC[1][2];
  							
  C+=8;						
  C[0*ldc] = alpha*rC[2][0] ;
  C[8*ldc] = alpha*rC[2][1] ;
  C[16*ldc] = alpha*rC[2][2];
  

}
";


static const char * dgemm_NT_16_16_8_8x8_2x2__ALPHA = "


__attribute__((reqd_work_group_size(8,8,1)))
  __kernel void dgemm_NT_16_16_8_8x8_2x2__ALPHA( __global double const * restrict A, 
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
  double rC[2][2]  = {(double)0};
  double rA[1][2];
  double rB[1][2];

  double PreFetchA[2];
  double PreFetchB[2];

  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[128];
  __local double lB[128];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*16+ idxT + idyT*lda;
  B +=  gidy*16+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*16+idxT;
  __local double* plB = lB + idyT*16+idxT;

  plA[0] = A[0];
  plA[8] = A[8];
  
  plB[0] = B[0];
  plB[8] = B[8];
  
 
	
  barrier(CLK_LOCAL_MEM_FENCE);


  //for( int block_k=0 ; block_k< K ; block_k+=8)
  uint block_k = K >> 3;
  do
  {
    //barrier(CLK_LOCAL_MEM_FENCE);
    A += 8*lda;
    B += 8*ldb;

    PreFetchA[0] = A[0];
    PreFetchA[1] = A[8];
   
    PreFetchB[0] = B[0];
    PreFetchB[1] = B[8];
    
    int offA = idx;
    int offB = idy;



    for( int k = 0 ; k < 8; k+=1)
    {
      rA[0][0] = lA[offA + 0];
      rA[0][1] = lA[offA + 8];
     
      rB[0][0] = lB[offB + 0];
      rB[0][1] = lB[offB + 8];
      
      offA += 16;
      offB += 16;
			
      rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
      rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
  
      rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
      rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
       
    }

    barrier(CLK_LOCAL_MEM_FENCE);
    plA[0]   = PreFetchA[0];
    plA[8]  = PreFetchA[1];
    
    plB[0]   = PreFetchB[0];
    plB[8]  = PreFetchB[1];
    
    barrier(CLK_LOCAL_MEM_FENCE);

    //  A += 8*lda;
    //  B += 8*ldb;
  }
  while (--block_k > 0);

  C+= gidx*16;
  C+= idx;
  C+= gidy*16*ldc;
  C+= idy*ldc;
	
  C[0*ldc] = alpha*rC[0][0];
  C[8*ldc] = alpha*rC[0][1];
  
  C+=8;
  C[0*ldc] = alpha*rC[1][0];
  C[8*ldc] = alpha*rC[1][1]; 

}
";












static const char * dgemm_NN_24_24_8_8x8_3x3__ALPHABETA = "

__attribute__((reqd_work_group_size(8,8,1)))
  __kernel void dgemm_NN_24_24_8_8x8_3x3__ALPHABETA( __global double const * restrict A, 
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
  double rC[3][3]  = {(double)0};
  double rA[1][3];
  double rB[1][3];

  double PreFetchA[3];
  double PreFetchB[3];

  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[192];
  __local double lB[192];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*24+ idxT + idyT*lda;
  B +=  gidy*24*ldb+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*24+idxT;
  __local double* plB = lB + idxT*24+idyT;

  plA[0] = A[0];
  plA[8] = A[8];
  plA[16] = A[16];
  
  plB[0] = B[0];
  plB[8] = B[8*ldb];
  plB[16] = B[16*ldb];
  
 
	
  barrier(CLK_LOCAL_MEM_FENCE);


  //for( int block_k=0 ; block_k< K ; block_k+=8)
  uint block_k = K >> 3;
  do
  {
    //barrier(CLK_LOCAL_MEM_FENCE);
    A += 8*lda;
    B += 8;

    PreFetchA[0] = A[0];
    PreFetchA[1] = A[8];
    PreFetchA[2] = A[16];
   
    PreFetchB[0] = B[0];
    PreFetchB[1] = B[8*ldb];
    PreFetchB[2] = B[16*ldb];
    
    int offA = idx;
    int offB = idy;



    for( int k = 0 ; k < 8; k+=1)
    {
      rA[0][0] = lA[offA + 0];
      rA[0][1] = lA[offA + 8];
      rA[0][2] = lA[offA + 16];
     
      rB[0][0] = lB[offB + 0];
      rB[0][1] = lB[offB + 8];
      rB[0][2] = lB[offB + 16];
      
      offA += 24;
      offB += 24;
			
      rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
      rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
      rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
  
      rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
      rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
      rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
  
      rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
      rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
      rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
     
    }

    barrier(CLK_LOCAL_MEM_FENCE);
    plA[0]   = PreFetchA[0];
    plA[8]  = PreFetchA[1];
    plA[16] = PreFetchA[2];
    
    plB[0]   = PreFetchB[0];
    plB[8]  = PreFetchB[1];
    plB[16] = PreFetchB[2];
    
    barrier(CLK_LOCAL_MEM_FENCE);

    //  A += 8*lda;
    //  B += 8*ldb;
  }
  while (--block_k > 0);

  C+= gidx*24;
  C+= idx;
  C+= gidy*24*ldc;
  C+= idy*ldc;
	
  C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[0][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[0][2] + beta*C[16*ldc];
  
  C+=8;
  C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[1][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[1][2] + beta*C[16*ldc];
  
  C+=8;
  C[0*ldc] = alpha*rC[2][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[2][1] + beta*C[8*ldc];
  C[16*ldc] = alpha*rC[2][2] + beta*C[16*ldc];
  

}

";


static const char * dgemm_NN_16_16_8_8x8_2x2__ALPHABETA = "
__attribute__((reqd_work_group_size(8,8,1)))
  __kernel void dgemm_NN_16_16_8_8x8_2x2__ALPHABETA( __global double const * restrict A, 
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
  double rC[2][2]  = {(double)0};
  double rA[1][2];
  double rB[1][2];

  double PreFetchA[2];
  double PreFetchB[2];

  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[128];
  __local double lB[128];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*16+ idxT + idyT*lda;
  B +=  gidy*16*ldb+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*16+idxT;
  __local double* plB = lB + idxT*16+idyT;

  plA[0] = A[0];
  plA[8] = A[8];
  
  plB[0] = B[0];
  plB[8] = B[8*ldb];
  
 
	
  barrier(CLK_LOCAL_MEM_FENCE);


  //for( int block_k=0 ; block_k< K ; block_k+=8)
  uint block_k = K >> 3;
  do
  {
    //barrier(CLK_LOCAL_MEM_FENCE);
    A += 8*lda;
    B += 8;

    PreFetchA[0] = A[0];
    PreFetchA[1] = A[8];
   
    PreFetchB[0] = B[0];
    PreFetchB[1] = B[8*ldb];
    
    int offA = idx;
    int offB = idy;



    for( int k = 0 ; k < 8; k+=1)
    {
      rA[0][0] = lA[offA + 0];
      rA[0][1] = lA[offA + 8];
     
      rB[0][0] = lB[offB + 0];
      rB[0][1] = lB[offB + 8];
      
      offA += 16;
      offB += 16;
			
      rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
      rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
  
      rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
      rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
       
    }

    barrier(CLK_LOCAL_MEM_FENCE);
    plA[0]   = PreFetchA[0];
    plA[8]  = PreFetchA[1];
    
    plB[0]   = PreFetchB[0];
    plB[8]  = PreFetchB[1];
    
    barrier(CLK_LOCAL_MEM_FENCE);

    //  A += 8*lda;
    //  B += 8*ldb;
  }
  while (--block_k > 0);

  C+= gidx*16;
  C+= idx;
  C+= gidy*16*ldc;
  C+= idy*ldc;
	
  C[0*ldc] = alpha*rC[0][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[0][1] + beta*C[8*ldc];
  
  C+=8;
  C[0*ldc] = alpha*rC[1][0] + beta*C[0*ldc];
  C[8*ldc] = alpha*rC[1][1] + beta*C[8*ldc]; 

}
";



static const char * dgemm_NN_24_24_8_8x8_3x3__ALPHA = "

__attribute__((reqd_work_group_size(8,8,1)))
  __kernel void dgemm_NN_24_24_8_8x8_3x3__ALPHA( __global double const * restrict A, 
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
  double rC[3][3]  = {(double)0};
  double rA[1][3];
  double rB[1][3];

  double PreFetchA[3];
  double PreFetchB[3];

  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[192];
  __local double lB[192];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*24+ idxT + idyT*lda;
  B +=  gidy*24*ldb+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*24+idxT;
  __local double* plB = lB + idxT*24+idyT;

  plA[0] = A[0];
  plA[8] = A[8];
  plA[16] = A[16];
  
  plB[0] = B[0];
  plB[8] = B[8*ldb];
  plB[16] = B[16*ldb];
  
 
	
  barrier(CLK_LOCAL_MEM_FENCE);


  //for( int block_k=0 ; block_k< K ; block_k+=8)
  uint block_k = K >> 3;
  do
  {
    //barrier(CLK_LOCAL_MEM_FENCE);
    A += 8*lda;
    B += 8;

    PreFetchA[0] = A[0];
    PreFetchA[1] = A[8];
    PreFetchA[2] = A[16];
   
    PreFetchB[0] = B[0];
    PreFetchB[1] = B[8*ldb];
    PreFetchB[2] = B[16*ldb];
    
    int offA = idx;
    int offB = idy;



    for( int k = 0 ; k < 8; k+=1)
    {
      rA[0][0] = lA[offA + 0];
      rA[0][1] = lA[offA + 8];
      rA[0][2] = lA[offA + 16];
     
      rB[0][0] = lB[offB + 0];
      rB[0][1] = lB[offB + 8];
      rB[0][2] = lB[offB + 16];
      
      offA += 24;
      offB += 24;
			
      rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
      rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
      rC[2][0]=mad(rA[0][2],rB[0][0],rC[2][0]);
  
      rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
      rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
      rC[2][1]=mad(rA[0][2],rB[0][1],rC[2][1]);
  
      rC[0][2]=mad(rA[0][0],rB[0][2],rC[0][2]);
      rC[1][2]=mad(rA[0][1],rB[0][2],rC[1][2]);
      rC[2][2]=mad(rA[0][2],rB[0][2],rC[2][2]);
     
    }

    barrier(CLK_LOCAL_MEM_FENCE);
    plA[0]   = PreFetchA[0];
    plA[8]  = PreFetchA[1];
    plA[16] = PreFetchA[2];
    
    plB[0]   = PreFetchB[0];
    plB[8]  = PreFetchB[1];
    plB[16] = PreFetchB[2];
    
    barrier(CLK_LOCAL_MEM_FENCE);

    //  A += 8*lda;
    //  B += 8*ldb;
  }
  while (--block_k > 0);

  C+= gidx*24;
  C+= idx;
  C+= gidy*24*ldc;
  C+= idy*ldc;
	
  C[0*ldc] = alpha*rC[0][0] ;
  C[8*ldc] = alpha*rC[0][1] ;
  C[16*ldc] = alpha*rC[0][2];
  							
  C+=8;						
  C[0*ldc] = alpha*rC[1][0] ;
  C[8*ldc] = alpha*rC[1][1] ;
  C[16*ldc] = alpha*rC[1][2];
  							
  C+=8;						
  C[0*ldc] = alpha*rC[2][0] ;
  C[8*ldc] = alpha*rC[2][1] ;
  C[16*ldc] = alpha*rC[2][2];
  

}

";

static const char * dgemm_NN_16_16_8_8x8_2x2__ALPHA = "

__attribute__((reqd_work_group_size(8,8,1)))
  __kernel void dgemm_NN_16_16_8_8x8_2x2__ALPHA( __global double const * restrict A, 
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
  double rC[2][2]  = {(double)0};
  double rA[1][2];
  double rB[1][2];

  double PreFetchA[2];
  double PreFetchB[2];

  A += offsetA;
  B += offsetB;
  C+=offsetC;

  __local double lA[128];
  __local double lB[128];

  int gidx = get_group_id(0);
  int gidy = get_group_id(1);
  int idx = get_local_id(0);
  int idy = get_local_id(1);

  int idt = 8*idy + idx;
  int idxT = idt % 8;
  int idyT = idt / 8;

  A +=  gidx*16+ idxT + idyT*lda;
  B +=  gidy*16*ldb+ idxT + idyT*ldb;

  __local double* plA = lA + idyT*16+idxT;
  __local double* plB = lB + idxT*16+idyT;

  plA[0] = A[0];
  plA[8] = A[8];
  
  plB[0] = B[0];
  plB[8] = B[8*ldb];
  
 
	
  barrier(CLK_LOCAL_MEM_FENCE);


  //for( int block_k=0 ; block_k< K ; block_k+=8)
  uint block_k = K >> 3;
  do
  {
    //barrier(CLK_LOCAL_MEM_FENCE);
    A += 8*lda;
    B += 8;

    PreFetchA[0] = A[0];
    PreFetchA[1] = A[8];
   
    PreFetchB[0] = B[0];
    PreFetchB[1] = B[8*ldb];
    
    int offA = idx;
    int offB = idy;



    for( int k = 0 ; k < 8; k+=1)
    {
      rA[0][0] = lA[offA + 0];
      rA[0][1] = lA[offA + 8];
     
      rB[0][0] = lB[offB + 0];
      rB[0][1] = lB[offB + 8];
      
      offA += 16;
      offB += 16;
			
      rC[0][0]=mad(rA[0][0],rB[0][0],rC[0][0]);
      rC[1][0]=mad(rA[0][1],rB[0][0],rC[1][0]);
  
      rC[0][1]=mad(rA[0][0],rB[0][1],rC[0][1]);
      rC[1][1]=mad(rA[0][1],rB[0][1],rC[1][1]);
       
    }

    barrier(CLK_LOCAL_MEM_FENCE);
    plA[0]   = PreFetchA[0];
    plA[8]  = PreFetchA[1];
    
    plB[0]   = PreFetchB[0];
    plB[8]  = PreFetchB[1];
    
    barrier(CLK_LOCAL_MEM_FENCE);

    //  A += 8*lda;
    //  B += 8*ldb;
  }
  while (--block_k > 0);

  C+= gidx*16;
  C+= idx;
  C+= gidy*16*ldc;
  C+= idy*ldc;
	
  C[0*ldc] = alpha*rC[0][0];
  C[8*ldc] = alpha*rC[0][1];
  
  C+=8;
  C[0*ldc] = alpha*rC[1][0];
  C[8*ldc] = alpha*rC[1][1]; 

}
";

