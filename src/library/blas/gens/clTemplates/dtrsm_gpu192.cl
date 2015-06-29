static const char * dtrsm_gpu192_kernels = "

//only supports upper triangle matrix for now

#define BLOCK_SIZE 12 // inner blocking size, <=32
#define NB 192        // outer blocking size, >BLOCK_SIZE

#define ZERO              ( 0.0)
#define ONE               ( 1.0)

#ifdef DOUBLE_PRECISION
#ifdef cl_khr_fp64
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#else
#pragma OPENCL EXTENSION cl_amd_fp64 : enable
#endif
#endif

__kernel void DIAG_DTRTRI_KERNEL_UPPER(int  isDiagUnit, 
				       __global double const * restrict A,
                                       uint offA,
				       __global double *d_dinvA,
				       uint lda,
                                       uint na)
{

  int i, j;
  double Ystx = 0;
  __local double *y = 0;
  double switcher;
  double neg_switcher;

  // Thread index
  int tx = get_local_id(0);

  // Thread index
  int gx = get_global_id(0);

  // Block index
  int bx = get_group_id(0);

  A = A + offA;

  __global const double *Aoff = A + bx*lda*BLOCK_SIZE + bx*BLOCK_SIZE;
  int NumBLperNB = NB/BLOCK_SIZE;
  d_dinvA += bx/NumBLperNB*NB*NB + (bx % NumBLperNB)*(NB*BLOCK_SIZE + BLOCK_SIZE);

  __local double Bs[BLOCK_SIZE*BLOCK_SIZE];
  __local double workspace[BLOCK_SIZE];    // workspace used to store the current working column

  // load A
  #pragma unroll
  for( i=0; i < BLOCK_SIZE; i++ )
    {
      if(tx <= i && i+bx*BLOCK_SIZE < na )
        {
	  Bs[i*BLOCK_SIZE+tx] = *(Aoff+i*lda+tx);    
        }
      else
        {
	  Bs[i*BLOCK_SIZE+tx] = ZERO; 
        }
    } 
  // read in the whole square block of my A and zero out the non data triangular
 
  // Synchronize to make sure the matrices are loaded
  //__syncthreads(); 
  barrier(CLK_LOCAL_MEM_FENCE);

  // solve the diagonals

  if(isDiagUnit == 1)
    {
      Bs[tx*BLOCK_SIZE+tx] = ONE;
    }
  else
    {
      if( Bs[tx*BLOCK_SIZE+tx] == ZERO )
	{
	  Bs[tx*BLOCK_SIZE+tx] = ONE;  
	}
      else
	{
	  Bs[tx*BLOCK_SIZE+tx] = ONE / ( Bs[tx*BLOCK_SIZE+tx]) ;
	}      
    }


  /* the upper case */
  for( i=0; i < BLOCK_SIZE; i++ ) {
    Ystx =  ZERO;
    if( tx < i)
      {
	switcher = ONE;
      }
    else
      {
	switcher = ZERO;
      }

    //dtrmv
    workspace[tx] = *(Bs+i*BLOCK_SIZE+tx);
    y = Bs+i*BLOCK_SIZE;

    #pragma unroll
    //for( j=tx; j < i; j++ )
    for( j=0; j < i; j++ )
      Ystx += switcher * (*(Bs+j*BLOCK_SIZE+tx)*workspace[j]);

    //sscal
    // if (tx != i) y[tx]=switcher*Ystx*(-Bs[i*BLOCK_SIZE+i]);

    if( tx != i)
      {
	switcher = ONE;
	neg_switcher =  ZERO;
      }
    else
      {
	switcher = ZERO;
	neg_switcher =  ONE;
      }

    y[tx] = switcher *Ystx*(-Bs[i*BLOCK_SIZE+i])+neg_switcher*y[tx];

    // __syncthreads();
    barrier(CLK_LOCAL_MEM_FENCE);
  }

  // write back A
#pragma unroll
  for( i=0; i < BLOCK_SIZE; i++ )
    *(d_dinvA+i*NB+tx) = Bs[i*BLOCK_SIZE+tx];

}

/*
 * B21 = -inv(A11)*A12*inv(A22)
 * 12 to 24
 */
__kernel void 
TRIPLE_DGEMM_UPDATE_12_R (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, uint lda, int npages, int na)
{
	// Ain is the non inverse matrix; the size of Ain is lda * na
	// offAin is the offset of Ain
	// d_dinvA is the inversed matrix. the size of d_invA is NB * (na-1)/NB + 1
	// blk is subblock size, which is 12 here.
	// lda in leading dimension. Column major here
	// npages = (na-1)/12*2 + 1; for 96 this is 4 for 192 this is 8

	//Work group size is [12]
	//global work size is [96*number of blocks]
	//each work item in each work group is responsible for every element in that row
	//each work group is responsible for one gemm;\


	////////////// A12*invA22
    const uint gidx = get_group_id(0);
    const uint idx = get_local_id(0);

	const uint page = gidx % npages;
	const uint page_block = page/8;//8 pages per page block
	const uint page_index_in_block = page%8;
	
	
	__global double *B, *C;
    __local double lA[12][12];
    __local double lB[12][12];
	double privateC[12] = {(double)0};
	
	//decide A12 location for each page
    Ain = Ain + offAin;
	Ain += (page*blk*2 + blk) * lda + page * 2 * blk;
	
	//decide invA22 (B) location for each page
	B = d_dinvA + page_block*NB*NB + (page_index_in_block*blk*2 + blk) * NB + page_index_in_block * 2 * blk + blk;
	
	//decide invA12 location for each page
	C = d_dinvA + page_block*NB*NB + (page_index_in_block*blk*2 + blk) * NB + page_index_in_block * 2 * blk;
	
	//read A and B into LDS no transpose operated here
	lA[idx][0] = Ain[idx];
	lA[idx][1] = Ain[idx + lda];
	lA[idx][2] = Ain[idx + lda*2];
	lA[idx][3] = Ain[idx + lda*3];
	lA[idx][4] = Ain[idx + lda*4];
	lA[idx][5] = Ain[idx + lda*5];
	lA[idx][6] = Ain[idx + lda*6];
	lA[idx][7] = Ain[idx + lda*7];
	lA[idx][8] = Ain[idx + lda*8];
	lA[idx][9] = Ain[idx + lda*9];
	lA[idx][10] = Ain[idx + lda*10];
	lA[idx][11] = Ain[idx + lda*11];
	
	lB[idx][0] = B[idx];
	lB[idx][1] = B[idx + NB];
	lB[idx][2] = B[idx + NB*2];
	lB[idx][3] = B[idx + NB*3];
	lB[idx][4] = B[idx + NB*4];
	lB[idx][5] = B[idx + NB*5];
	lB[idx][6] = B[idx + NB*6];
	lB[idx][7] = B[idx + NB*7];
	lB[idx][8] = B[idx + NB*8];
	lB[idx][9] = B[idx + NB*9];
	lB[idx][10] = B[idx + NB*10];
	lB[idx][11] = B[idx + NB*11];
	barrier(CLK_LOCAL_MEM_FENCE);
	
	//do math
	
	uint i = 0;
	
	do{
	    privateC[0]=mad(lA[idx][i],lB[i][0],privateC[0]); 
	    privateC[1]=mad(lA[idx][i],lB[i][1],privateC[1]); 
	    privateC[2]=mad(lA[idx][i],lB[i][2],privateC[2]); 
	    privateC[3]=mad(lA[idx][i],lB[i][3],privateC[3]); 
	    privateC[4]=mad(lA[idx][i],lB[i][4],privateC[4]); 
	    privateC[5]=mad(lA[idx][i],lB[i][5],privateC[5]); 
	    privateC[6]=mad(lA[idx][i],lB[i][6],privateC[6]); 
	    privateC[7]=mad(lA[idx][i],lB[i][7],privateC[7]); 
	    privateC[8]=mad(lA[idx][i],lB[i][8],privateC[8]); 
	    privateC[9]=mad(lA[idx][i],lB[i][9],privateC[9]); 
	    privateC[10]=mad(lA[idx][i],lB[i][10],privateC[10]); 
	    privateC[11]=mad(lA[idx][i],lB[i][11],privateC[11]); 
		//mem_fence(CLK_LOCAL_MEM_FENCE);
	    i = i + 1;
	}while(i < 12);
	
	i = 0;
	do{
        C[NB*i+idx] = privateC[i];
	    i = i + 1;
	}while(i < 12);
	
    ////////////// -invA11*invA12
	barrier(CLK_GLOBAL_MEM_FENCE);
	//A is moving to invA11
	__global double *A;
	A = d_dinvA + page_block*NB*NB + ( (page%4)*blk*2 ) * NB + (page%4) * 2 * blk;
	//both B and C are pointing at invA12
	B = C;
	
	//read A and B into LDS no transpose operated here
	lA[idx][0] = A[idx];
	lA[idx][1] = A[idx + NB];
	lA[idx][2] = A[idx + NB*2];
	lA[idx][3] = A[idx + NB*3];
	lA[idx][4] = A[idx + NB*4];
	lA[idx][5] = A[idx + NB*5];
	lA[idx][6] = A[idx + NB*6];
	lA[idx][7] = A[idx + NB*7];
	lA[idx][8] = A[idx + NB*8];
	lA[idx][9] = A[idx + NB*9];
	lA[idx][10] = A[idx + NB*10];
	lA[idx][11] = A[idx + NB*11];
	
	lB[idx][0] = B[idx];
	lB[idx][1] = B[idx + NB];
	lB[idx][2] = B[idx + NB*2];
	lB[idx][3] = B[idx + NB*3];
	lB[idx][4] = B[idx + NB*4];
	lB[idx][5] = B[idx + NB*5];
	lB[idx][6] = B[idx + NB*6];
	lB[idx][7] = B[idx + NB*7];
	lB[idx][8] = B[idx + NB*8];
	lB[idx][9] = B[idx + NB*9];
	lB[idx][10] = B[idx + NB*10];
	lB[idx][11] = B[idx + NB*11];
	barrier(CLK_LOCAL_MEM_FENCE);
	
    //do math
	
	i = 0;
	privateC[0] = 0;	
	privateC[1] = 0;
	privateC[2] = 0;
	privateC[3] = 0;
	privateC[4] = 0;
	privateC[5] = 0;
	privateC[6] = 0;
	privateC[7] = 0;
	privateC[8] = 0;
	privateC[9] = 0;
	privateC[10] = 0;
	privateC[11] = 0;
	do{
	    privateC[0]=mad(lA[idx][i],lB[i][0],privateC[0]); 
	    privateC[1]=mad(lA[idx][i],lB[i][1],privateC[1]); 
	    privateC[2]=mad(lA[idx][i],lB[i][2],privateC[2]); 
	    privateC[3]=mad(lA[idx][i],lB[i][3],privateC[3]); 
	    privateC[4]=mad(lA[idx][i],lB[i][4],privateC[4]); 
	    privateC[5]=mad(lA[idx][i],lB[i][5],privateC[5]); 
	    privateC[6]=mad(lA[idx][i],lB[i][6],privateC[6]); 
	    privateC[7]=mad(lA[idx][i],lB[i][7],privateC[7]); 
	    privateC[8]=mad(lA[idx][i],lB[i][8],privateC[8]); 
	    privateC[9]=mad(lA[idx][i],lB[i][9],privateC[9]); 
	    privateC[10]=mad(lA[idx][i],lB[i][10],privateC[10]); 
	    privateC[11]=mad(lA[idx][i],lB[i][11],privateC[11]); 
		//mem_fence(CLK_LOCAL_MEM_FENCE);
	    i = i + 1;
	}while(i < 12);

    i = 0;
	do{
        C[NB*i+idx] = -1*privateC[i];
	    i = i + 1;
	}while(i < 12);
	
}

__kernel void 
TRIPLE_DGEMM_UPDATE_24_PART1_R (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, uint lda, int npages, int na)
{
	// Ain is the non inverse matrix; the size of Ain is lda * na
	// offAin is the offset of Ain
	// d_dinvA is the inversed matrix. the size of d_invA is NB * (na-1)/NB + 1
	// blk is subblock size, which is 24 here.
	// lda in leading dimension. Column major here
	// npages = (na-1)/12*2 + 1; for 96 this is 2 for 192 this is 4

	//Work group size is [24, 2]
	//global work size is [96*number of blocks, 2]
	//each work item in each work group is responsible for 12 elements (half) in that row
	//each work group is responsible for one gemm;


	////////////// A12*invA22
    const uint gidx = get_group_id(0);
	const uint gidy = get_group_id(1);
    const uint idx = get_local_id(0);
	const uint idy = get_local_id(1);

	const uint page = gidx % npages;//0-3 for 192; 0-1 for 96
	const uint page_block = page/4;//4 pages per page block

	
	
	__global double *B, *C;
    __local double lA[24][24];
    __local double lB[24][24];
	double privateC[12] = {(double)0};
	
	//decide A12 location for each page
    Ain = Ain + offAin;
	Ain += (page*blk*2 + blk) * lda + page * 2 * blk;
	
	//decide invA22 (B) location for each page
	B = d_dinvA + page_block*NB*NB + ((page%4)*blk*2 + blk) * NB + (page%4) * 2 * blk + blk;
	
	//decide invA12 location for each page
	C = d_dinvA + page_block*NB*NB + ((page%4)*blk*2 + blk) * NB + (page%4) * 2 * blk;
	
	//read A and B into LDS no transpose operated here
	//each work iteam loads half a row
	lA[idx][0+idy*12] = Ain[idx + idy*12*lda];
	lA[idx][1+idy*12] = Ain[idx + lda + idy*12*lda];
	lA[idx][2+idy*12] = Ain[idx + lda*2 + idy*12*lda];
	lA[idx][3+idy*12] = Ain[idx + lda*3 + idy*12*lda];
	lA[idx][4+idy*12] = Ain[idx + lda*4 + idy*12*lda];
	lA[idx][5+idy*12] = Ain[idx + lda*5 + idy*12*lda];
	lA[idx][6+idy*12] = Ain[idx + lda*6 + idy*12*lda];
	lA[idx][7+idy*12] = Ain[idx + lda*7 + idy*12*lda];
	lA[idx][8+idy*12] = Ain[idx + lda*8 + idy*12*lda];
	lA[idx][9+idy*12] = Ain[idx + lda*9 + idy*12*lda];
	lA[idx][10+idy*12] = Ain[idx + lda*10 + idy*12*lda];
	lA[idx][11+idy*12] = Ain[idx + lda*11 + idy*12*lda];
	
	lB[idx][0+idy*12] = B[idx + idy*12*NB];
	lB[idx][1+idy*12] = B[idx + NB + idy*12*NB];
	lB[idx][2+idy*12] = B[idx + NB*2 + idy*12*NB];
	lB[idx][3+idy*12] = B[idx + NB*3 + idy*12*NB];
	lB[idx][4+idy*12] = B[idx + NB*4 + idy*12*NB];
	lB[idx][5+idy*12] = B[idx + NB*5 + idy*12*NB];
	lB[idx][6+idy*12] = B[idx + NB*6 + idy*12*NB];
	lB[idx][7+idy*12] = B[idx + NB*7 + idy*12*NB];
	lB[idx][8+idy*12] = B[idx + NB*8 + idy*12*NB];
	lB[idx][9+idy*12] = B[idx + NB*9 + idy*12*NB];
	lB[idx][10+idy*12] = B[idx + NB*10 + idy*12*NB];
	lB[idx][11+idy*12] = B[idx + NB*11 + idy*12*NB];
	barrier(CLK_LOCAL_MEM_FENCE);
	
	//do math
	
	uint i = 0;
	
	do{
	    privateC[0]=mad(lA[idx][i],lB[i][0+idy*12],privateC[0]); 
	    privateC[1]=mad(lA[idx][i],lB[i][1+idy*12],privateC[1]); 
	    privateC[2]=mad(lA[idx][i],lB[i][2+idy*12],privateC[2]); 
	    privateC[3]=mad(lA[idx][i],lB[i][3+idy*12],privateC[3]); 
	    privateC[4]=mad(lA[idx][i],lB[i][4+idy*12],privateC[4]); 
	    privateC[5]=mad(lA[idx][i],lB[i][5+idy*12],privateC[5]); 
	    privateC[6]=mad(lA[idx][i],lB[i][6+idy*12],privateC[6]); 
	    privateC[7]=mad(lA[idx][i],lB[i][7+idy*12],privateC[7]); 
	    privateC[8]=mad(lA[idx][i],lB[i][8+idy*12],privateC[8]); 
	    privateC[9]=mad(lA[idx][i],lB[i][9+idy*12],privateC[9]); 
	    privateC[10]=mad(lA[idx][i],lB[i][10+idy*12],privateC[10]); 
	    privateC[11]=mad(lA[idx][i],lB[i][11+idy*12],privateC[11]); 
	    i = i + 1;
	}while(i < 24);
	
	i = 0;
	do{
        C[NB*idy*12+NB*i+idx] = privateC[i];
	    i = i + 1;
	}while(i < 12);
}

__kernel void
TRIPLE_DGEMM_UPDATE_24_PART2_R (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
	// Ain is the non inverse matrix; the size of Ain is lda * na
	// offAin is the offset of Ain
	// d_dinvA is the inversed matrix. the size of d_invA is NB * (na-1)/NB + 1
	// blk is subblock size, which is 24 here.
	// lda in leading dimension. Column major here
	// npages = (na-1)/12*2 + 1; for 96 this is 2 for 192 this is 4

	//Work group size is [24, 2]
	//global work size is [96*number of blocks, 2]
	//each work item in each work group is responsible for 12 elements (half) in that row
	//each work group is responsible for one gemm;

	
	////////////// -invA11*invA12
	const uint gidx = get_group_id(0);
	const uint gidy = get_group_id(1);
    const uint idx = get_local_id(0);
	const uint idy = get_local_id(1);
	
	const uint page = gidx % npages;//0-3 for 192; 0-1 for 96
	const uint page_block = page/4;//4 pages per page block
	
	__global double *A, *B, *C;
    __local double lA[24][24];
    __local double lB[24][24];
	double privateC[12] = {(double)0};
	
	//decide invA11 location for each page
	A = d_dinvA + page_block*NB*NB + (page%4)*blk*2 * NB + (page%4) * 2 * blk;
	//decide invA12 location for each page
	B = d_dinvA + page_block*NB*NB + ((page%4)*blk*2 + blk) * NB + (page%4) * 2 * blk;
	C = B;
	//C = d_dinvA + page_block*NB*NB + ((page%4)*blk*2) * NB + (page%4) * 2 * blk + blk;
	
	//read A and B into LDS no transpose operated here
	//each work iteam loads half a row
	lA[idx][0+idy*12] = A[idx + idy*12*NB];
	lA[idx][1+idy*12] = A[idx + NB + idy*12*NB];
	lA[idx][2+idy*12] = A[idx + NB*2 + idy*12*NB];
	lA[idx][3+idy*12] = A[idx + NB*3 + idy*12*NB];
	lA[idx][4+idy*12] = A[idx + NB*4 + idy*12*NB];
	lA[idx][5+idy*12] = A[idx + NB*5 + idy*12*NB];
	lA[idx][6+idy*12] = A[idx + NB*6 + idy*12*NB];
	lA[idx][7+idy*12] = A[idx + NB*7 + idy*12*NB];
	lA[idx][8+idy*12] = A[idx + NB*8 + idy*12*NB];
	lA[idx][9+idy*12] = A[idx + NB*9 + idy*12*NB];
	lA[idx][10+idy*12] = A[idx + NB*10 + idy*12*NB];
	lA[idx][11+idy*12] = A[idx + NB*11 + idy*12*NB];
	
	lB[idx][0+idy*12] = B[idx + idy*12*NB];
	lB[idx][1+idy*12] = B[idx + NB + idy*12*NB];
	lB[idx][2+idy*12] = B[idx + NB*2 + idy*12*NB];
	lB[idx][3+idy*12] = B[idx + NB*3 + idy*12*NB];
	lB[idx][4+idy*12] = B[idx + NB*4 + idy*12*NB];
	lB[idx][5+idy*12] = B[idx + NB*5 + idy*12*NB];
	lB[idx][6+idy*12] = B[idx + NB*6 + idy*12*NB];
	lB[idx][7+idy*12] = B[idx + NB*7 + idy*12*NB];
	lB[idx][8+idy*12] = B[idx + NB*8 + idy*12*NB];
	lB[idx][9+idy*12] = B[idx + NB*9 + idy*12*NB];
	lB[idx][10+idy*12] = B[idx + NB*10 + idy*12*NB];
	lB[idx][11+idy*12] = B[idx + NB*11 + idy*12*NB];
	barrier(CLK_LOCAL_MEM_FENCE);
	//do math
	
	uint i = 0;
	
	do{
	    privateC[0]=mad(lA[idx][i],lB[i][0+idy*12],privateC[0]); 
	    privateC[1]=mad(lA[idx][i],lB[i][1+idy*12],privateC[1]); 
	    privateC[2]=mad(lA[idx][i],lB[i][2+idy*12],privateC[2]); 
	    privateC[3]=mad(lA[idx][i],lB[i][3+idy*12],privateC[3]); 
	    privateC[4]=mad(lA[idx][i],lB[i][4+idy*12],privateC[4]); 
	    privateC[5]=mad(lA[idx][i],lB[i][5+idy*12],privateC[5]); 
	    privateC[6]=mad(lA[idx][i],lB[i][6+idy*12],privateC[6]); 
	    privateC[7]=mad(lA[idx][i],lB[i][7+idy*12],privateC[7]); 
	    privateC[8]=mad(lA[idx][i],lB[i][8+idy*12],privateC[8]); 
	    privateC[9]=mad(lA[idx][i],lB[i][9+idy*12],privateC[9]); 
	    privateC[10]=mad(lA[idx][i],lB[i][10+idy*12],privateC[10]); 
	    privateC[11]=mad(lA[idx][i],lB[i][11+idy*12],privateC[11]); 
	    i = i + 1;
	}while(i < 24);
	
	i = 0;
	do{
        C[NB*idy*12+NB*i+idx] = -1 * privateC[i];
	    i = i + 1;
	}while(i < 12);	

}

__kernel void
TRIPLE_DGEMM_UPDATE_48_PART1_R (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
	// Ain is the non inverse matrix; the size of Ain is lda * na
	// offAin is the offset of Ain
	// d_dinvA is the inversed matrix. the size of d_invA is NB * (na-1)/NB + 1
	// blk is subblock size, which is 48 here.
	// lda in leading dimension. Column major here
	// npages = (na-1)/12*2 + 1; for 96 this is 1 for 192 this is 2

	//Work group size is [24, 2]
	//global work size is [96*number of blocks, 4]
	//each work item in each work group is responsible for 12 elements (1/4) in that row
	//each work group is responsible for 24 by 24 macro tile;
	
	////////////// A12*invA22
    const uint gidx = get_group_id(0);
	const uint gidy = get_group_id(1);
    const uint idx = get_local_id(0);
	const uint idy = get_local_id(1);
	
	//uint page = gidx / 2;//0-1 for 192; 0 for 96
	const uint page = (gidx/2)%2;//index of page within a page_block; 2 pages per page_block
	const uint page_block = gidx/4;//#index of page_block; 2 WG per page; 4 WG per page_block
	
	__global double *B, *C;
    __local double lA[24][48];
    __local double lB[48][24];
	double privateC[12] = {(double)0};
	
	//decide A12 location for each page
	//each workgroup loads half of A (left or right)
    Ain = Ain + offAin;
	Ain += page_block*NB*lda + page_block*NB + page*blk*2*lda + page*blk*2 + blk*lda + gidx%2*(blk/2);
	
	//decide invA22 (B) location for each page
	//each workgroup loads half of B (up or down)
	B = d_dinvA + page_block*NB*NB + page*blk*2*NB + page*blk*2 + blk*NB + blk + gidy*(blk/2)*NB;
	
	//decide invA12 location for each page; 
	//Actually this will be stored in invA21 temporarily
	//each workgroup writes 1/4 of C
	C = d_dinvA + page_block*NB*NB + page*blk*2*NB + page*blk*2 + blk*NB + gidx%2*(blk/2) + gidy*(blk/2)*NB;
	
	//read A and B into LDS no transpose operated here
	//each work item loads a half row of A and half column of B
	//idx 0-23 idy 0-1
	lA[idx][0+idy*24] = Ain[idx + idy*24*lda];
	lA[idx][1+idy*24] = Ain[idx + lda + idy*24*lda];
	lA[idx][2+idy*24] = Ain[idx + lda*2 + idy*24*lda];
	lA[idx][3+idy*24] = Ain[idx + lda*3 + idy*24*lda];
	lA[idx][4+idy*24] = Ain[idx + lda*4 + idy*24*lda];
	lA[idx][5+idy*24] = Ain[idx + lda*5 + idy*24*lda];
	lA[idx][6+idy*24] = Ain[idx + lda*6 + idy*24*lda];
	lA[idx][7+idy*24] = Ain[idx + lda*7 + idy*24*lda];
	lA[idx][8+idy*24] = Ain[idx + lda*8 + idy*24*lda];
	lA[idx][9+idy*24] = Ain[idx + lda*9 + idy*24*lda];
	lA[idx][10+idy*24] = Ain[idx + lda*10 + idy*24*lda];
	lA[idx][11+idy*24] = Ain[idx + lda*11 + idy*24*lda];
	lA[idx][12+idy*24] = Ain[idx + lda*12 + idy*24*lda];
	lA[idx][13+idy*24] = Ain[idx + lda*13 + idy*24*lda];
	lA[idx][14+idy*24] = Ain[idx + lda*14 + idy*24*lda];
	lA[idx][15+idy*24] = Ain[idx + lda*15 + idy*24*lda];
	lA[idx][16+idy*24] = Ain[idx + lda*16 + idy*24*lda];
	lA[idx][17+idy*24] = Ain[idx + lda*17 + idy*24*lda];
	lA[idx][18+idy*24] = Ain[idx + lda*18 + idy*24*lda];
	lA[idx][19+idy*24] = Ain[idx + lda*19 + idy*24*lda];
	lA[idx][20+idy*24] = Ain[idx + lda*20 + idy*24*lda];
	lA[idx][21+idy*24] = Ain[idx + lda*21 + idy*24*lda];
	lA[idx][22+idy*24] = Ain[idx + lda*22 + idy*24*lda];
	lA[idx][23+idy*24] = Ain[idx + lda*23 + idy*24*lda];
	
	lB[0+idy*24][idx] = B[idx*NB + idy*24];
	lB[1+idy*24][idx]  = B[idx*NB + idy*24 + 1];
	lB[2+idy*24][idx]  = B[idx*NB + idy*24 + 2];
	lB[3+idy*24][idx]  = B[idx*NB + idy*24 + 3];
	lB[4+idy*24][idx]  = B[idx*NB + idy*24 + 4];
	lB[5+idy*24][idx]  = B[idx*NB + idy*24 + 5];
	lB[6+idy*24][idx]  = B[idx*NB + idy*24 + 6];
	lB[7+idy*24][idx]  = B[idx*NB + idy*24 + 7];
	lB[8+idy*24][idx]  = B[idx*NB + idy*24 + 8];
	lB[9+idy*24][idx]  = B[idx*NB + idy*24 + 9];
	lB[10+idy*24][idx]  = B[idx*NB + idy*24 + 10];
	lB[11+idy*24][idx]  = B[idx*NB + idy*24 + 11];
	lB[12+idy*24][idx]  = B[idx*NB + idy*24 + 12];
	lB[13+idy*24][idx]  = B[idx*NB + idy*24 + 13];
	lB[14+idy*24][idx]  = B[idx*NB + idy*24 + 14];
	lB[15+idy*24][idx]  = B[idx*NB + idy*24 + 15];
	lB[16+idy*24][idx]  = B[idx*NB + idy*24 + 16];
	lB[17+idy*24][idx]  = B[idx*NB + idy*24 + 17];
	lB[18+idy*24][idx]  = B[idx*NB + idy*24 + 18];
	lB[19+idy*24][idx]  = B[idx*NB + idy*24 + 19];
	lB[20+idy*24][idx]  = B[idx*NB + idy*24 + 20];
	lB[21+idy*24][idx]  = B[idx*NB + idy*24 + 21];
	lB[22+idy*24][idx]  = B[idx*NB + idy*24 + 22];
	lB[23+idy*24][idx]  = B[idx*NB + idy*24 + 23];
	barrier(CLK_LOCAL_MEM_FENCE);
	
    //do math
	
	uint i = 0;
	
	do{
	    privateC[0]=mad(lA[idx][i],lB[i][0+idy*12],privateC[0]); 
	    privateC[1]=mad(lA[idx][i],lB[i][1+idy*12],privateC[1]); 
	    privateC[2]=mad(lA[idx][i],lB[i][2+idy*12],privateC[2]); 
	    privateC[3]=mad(lA[idx][i],lB[i][3+idy*12],privateC[3]); 
	    privateC[4]=mad(lA[idx][i],lB[i][4+idy*12],privateC[4]); 
	    privateC[5]=mad(lA[idx][i],lB[i][5+idy*12],privateC[5]); 
	    privateC[6]=mad(lA[idx][i],lB[i][6+idy*12],privateC[6]); 
	    privateC[7]=mad(lA[idx][i],lB[i][7+idy*12],privateC[7]); 
	    privateC[8]=mad(lA[idx][i],lB[i][8+idy*12],privateC[8]); 
	    privateC[9]=mad(lA[idx][i],lB[i][9+idy*12],privateC[9]); 
	    privateC[10]=mad(lA[idx][i],lB[i][10+idy*12],privateC[10]); 
	    privateC[11]=mad(lA[idx][i],lB[i][11+idy*12],privateC[11]); 
	    i = i + 1;
	}while(i < 48);
	
	i = 0;
	do{
        C[NB*idy*12+NB*i+idx] = privateC[i];
	    i = i + 1;
	}while(i < 12);
	
	
}

__kernel void
TRIPLE_DGEMM_UPDATE_48_PART2_R (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
	// Ain is the non inverse matrix; the size of Ain is lda * na
	// offAin is the offset of Ain
	// d_dinvA is the inversed matrix. the size of d_invA is NB * (na-1)/NB + 1
	// blk is subblock size, which is 48 here.
	// lda in leading dimension. Column major here
	// npages = (na-1)/12*2 + 1; for 96 this is 1 for 192 this is 2

	//Work group size is [24, 2]
	//global work size is [96*number of blocks, 4]
	//each work item in each work group is responsible for 12 elements (1/4) in that row
	//each work group is responsible for 24 by 24 macro tile;
	
	////////////// -invA11*invA12
    const uint gidx = get_group_id(0);
	const uint gidy = get_group_id(1);
    const uint idx = get_local_id(0);
	const uint idy = get_local_id(1);
	
	//uint page = gidx / 2;//0-1 for 192; 0 for 96
    const uint page = (gidx/2)%2;//index of page within a page_block; 2 pages per page_block
	const uint page_block = gidx/4;//#index of page_block; 2 WG per page; 4 WG per page_block
	
	__global double *A, *B, *C;
    __local double lA[24][48];
    __local double lB[48][24];
	double privateC[12] = {(double)0};
	
	//decide invA11 location for each page
	//each workgroup loads half of A (left or right)
	A = d_dinvA + page_block*NB*NB + page*blk*2*NB + page*blk*2 + gidx%2*(blk/2);
	
	//decide invA12 (B) location for each page
	//actually it was saved in invA21 from last kernel
	//each workgroup loads half of B (up or down)
	B = d_dinvA + page_block*NB*NB + page*blk*2*NB + page*blk*2 + blk*NB + gidy*(blk/2)*NB;
	
	//decide invA12 location for each page
	//each workgroup writes 1/4 of C
	C = d_dinvA + page_block*NB*NB + page*blk*2*NB + page*blk*2 + blk*NB + gidx%2*(blk/2) + gidy*(blk/2)*NB;
	
	//read A and B into LDS no transpose operated here
	//each work item loads a half row of A and half column of B
	//idx 0-23 idy 0-1
	lA[idx][0+idy*24] = A[idx + idy*24*NB];
	lA[idx][1+idy*24] = A[idx + NB + idy*24*NB];
	lA[idx][2+idy*24] = A[idx + NB*2 + idy*24*NB];
	lA[idx][3+idy*24] = A[idx + NB*3 + idy*24*NB];
	lA[idx][4+idy*24] = A[idx + NB*4 + idy*24*NB];
	lA[idx][5+idy*24] = A[idx + NB*5 + idy*24*NB];
	lA[idx][6+idy*24] = A[idx + NB*6 + idy*24*NB];
	lA[idx][7+idy*24] = A[idx + NB*7 + idy*24*NB];
	lA[idx][8+idy*24] = A[idx + NB*8 + idy*24*NB];
	lA[idx][9+idy*24] = A[idx + NB*9 + idy*24*NB];
	lA[idx][10+idy*24] = A[idx + NB*10 + idy*24*NB];
	lA[idx][11+idy*24] = A[idx + NB*11 + idy*24*NB];
	lA[idx][12+idy*24] = A[idx + NB*12 + idy*24*NB];
	lA[idx][13+idy*24] = A[idx + NB*13 + idy*24*NB];
	lA[idx][14+idy*24] = A[idx + NB*14 + idy*24*NB];
	lA[idx][15+idy*24] = A[idx + NB*15 + idy*24*NB];
	lA[idx][16+idy*24] = A[idx + NB*16 + idy*24*NB];
	lA[idx][17+idy*24] = A[idx + NB*17 + idy*24*NB];
	lA[idx][18+idy*24] = A[idx + NB*18 + idy*24*NB];
	lA[idx][19+idy*24] = A[idx + NB*19 + idy*24*NB];
	lA[idx][20+idy*24] = A[idx + NB*20 + idy*24*NB];
	lA[idx][21+idy*24] = A[idx + NB*21 + idy*24*NB];
	lA[idx][22+idy*24] = A[idx + NB*22 + idy*24*NB];
	lA[idx][23+idy*24] = A[idx + NB*23 + idy*24*NB];
	
	lB[0+idy*24][idx] = B[idx*NB + idy*24];
	lB[1+idy*24][idx]  = B[idx*NB + idy*24 + 1];
	lB[2+idy*24][idx]  = B[idx*NB + idy*24 + 2];
	lB[3+idy*24][idx]  = B[idx*NB + idy*24 + 3];
	lB[4+idy*24][idx]  = B[idx*NB + idy*24 + 4];
	lB[5+idy*24][idx]  = B[idx*NB + idy*24 + 5];
	lB[6+idy*24][idx]  = B[idx*NB + idy*24 + 6];
	lB[7+idy*24][idx]  = B[idx*NB + idy*24 + 7];
	lB[8+idy*24][idx]  = B[idx*NB + idy*24 + 8];
	lB[9+idy*24][idx]  = B[idx*NB + idy*24 + 9];
	lB[10+idy*24][idx]  = B[idx*NB + idy*24 + 10];
	lB[11+idy*24][idx]  = B[idx*NB + idy*24 + 11];
	lB[12+idy*24][idx]  = B[idx*NB + idy*24 + 12];
	lB[13+idy*24][idx]  = B[idx*NB + idy*24 + 13];
	lB[14+idy*24][idx]  = B[idx*NB + idy*24 + 14];
	lB[15+idy*24][idx]  = B[idx*NB + idy*24 + 15];
	lB[16+idy*24][idx]  = B[idx*NB + idy*24 + 16];
	lB[17+idy*24][idx]  = B[idx*NB + idy*24 + 17];
	lB[18+idy*24][idx]  = B[idx*NB + idy*24 + 18];
	lB[19+idy*24][idx]  = B[idx*NB + idy*24 + 19];
	lB[20+idy*24][idx]  = B[idx*NB + idy*24 + 20];
	lB[21+idy*24][idx]  = B[idx*NB + idy*24 + 21];
	lB[22+idy*24][idx]  = B[idx*NB + idy*24 + 22];
	lB[23+idy*24][idx]  = B[idx*NB + idy*24 + 23];
	barrier(CLK_LOCAL_MEM_FENCE);
	
    //do math
	
	uint i = 0;
	
	do{
	    privateC[0]=mad(lA[idx][i],lB[i][0+idy*12],privateC[0]); 
	    privateC[1]=mad(lA[idx][i],lB[i][1+idy*12],privateC[1]); 
	    privateC[2]=mad(lA[idx][i],lB[i][2+idy*12],privateC[2]); 
	    privateC[3]=mad(lA[idx][i],lB[i][3+idy*12],privateC[3]); 
	    privateC[4]=mad(lA[idx][i],lB[i][4+idy*12],privateC[4]); 
	    privateC[5]=mad(lA[idx][i],lB[i][5+idy*12],privateC[5]); 
	    privateC[6]=mad(lA[idx][i],lB[i][6+idy*12],privateC[6]); 
	    privateC[7]=mad(lA[idx][i],lB[i][7+idy*12],privateC[7]); 
	    privateC[8]=mad(lA[idx][i],lB[i][8+idy*12],privateC[8]); 
	    privateC[9]=mad(lA[idx][i],lB[i][9+idy*12],privateC[9]); 
	    privateC[10]=mad(lA[idx][i],lB[i][10+idy*12],privateC[10]); 
	    privateC[11]=mad(lA[idx][i],lB[i][11+idy*12],privateC[11]); 
	    i = i + 1;
	}while(i < 48);
	
	i = 0;
	do{
        C[NB*idy*12+NB*i+idx] = -1 * privateC[i];
	    i = i + 1;
	}while(i < 12);
	
	
}

__kernel void
TRIPLE_DGEMM_UPDATE_96_PART1_R (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
	// Ain is the non inverse matrix; the size of Ain is lda * na
	// offAin is the offset of Ain
	// d_dinvA is the inversed matrix. the size of d_invA is NB * (na-1)/NB + 1
	// blk is subblock size, which is 96 here.
	// lda in leading dimension. Column major here
	// npages = (na-1)/12*2 + 1; for 192 this is 1 for 384 this is 2

	//Work group size is [24, 2]
	//global work size is [96*number of blocks, 8]
	//each work item in each work group is responsible for 12 elements (1/8) in that row
	//each work group is responsible for 24 by 24 macro tile;
	
	////////////// A12*invA22
    const uint gidx = get_group_id(0);
	const uint gidy = get_group_id(1);
    const uint idx = get_local_id(0);
	const uint idy = get_local_id(1);
	
	//uint page = gidx / 2;//0-1 for 192; 0 for 96
	//const uint page = (gidx/4)%1;//index of page within a page_block; 1 pages per page_block
	const uint page_block = gidx/4;//#index of page_block; 4 WG per page; 4 WG per page_block
	
	
	__global double *B, *C;
    __local double lA[24][48];
    __local double lB[48][24];
	double privateC[12] = {(double)0};
	
	//decide A12 location for each page
	//each workgroup loads 1/4 of A (left or right)
    Ain = Ain + offAin;
	Ain += page_block*NB*lda + page_block*NB + blk*lda + gidx%4*(blk/4);
	
	//decide invA22 (B) location for each page
	//each workgroup loads 1/4 of B (up or down)
	B = d_dinvA + page_block*NB*NB + blk*NB + blk + gidy*(blk/4)*NB;
	
	//decide invA12 location for each page; 
	//Actually this will be stored in invA21 temporarily
	//each workgroup writes 1/4*1/4 of C
	C = d_dinvA + page_block*NB*NB + blk*NB + gidx%4*(blk/4) + gidy*(blk/4)*NB;
	
	//read A and B into LDS no transpose operated here
	//each work item loads a half row of A and half column of B
	//each loop loads 1/4 row of A and 1/4 column of B
	//idx 0-23 idy 0-1
	
	uint block_k = blk / 48; //thus we need 2 iterations here
	do{
	    barrier(CLK_LOCAL_MEM_FENCE);
		lA[idx][0+idy*24] = Ain[idx + idy*24*lda];
		lA[idx][1+idy*24] = Ain[idx + lda + idy*24*lda];
		lA[idx][2+idy*24] = Ain[idx + lda*2 + idy*24*lda];
		lA[idx][3+idy*24] = Ain[idx + lda*3 + idy*24*lda];
		lA[idx][4+idy*24] = Ain[idx + lda*4 + idy*24*lda];
		lA[idx][5+idy*24] = Ain[idx + lda*5 + idy*24*lda];
		lA[idx][6+idy*24] = Ain[idx + lda*6 + idy*24*lda];
		lA[idx][7+idy*24] = Ain[idx + lda*7 + idy*24*lda];
		lA[idx][8+idy*24] = Ain[idx + lda*8 + idy*24*lda];
		lA[idx][9+idy*24] = Ain[idx + lda*9 + idy*24*lda];
		lA[idx][10+idy*24] = Ain[idx + lda*10 + idy*24*lda];
		lA[idx][11+idy*24] = Ain[idx + lda*11 + idy*24*lda];
		lA[idx][12+idy*24] = Ain[idx + lda*12 + idy*24*lda];
		lA[idx][13+idy*24] = Ain[idx + lda*13 + idy*24*lda];
		lA[idx][14+idy*24] = Ain[idx + lda*14 + idy*24*lda];
		lA[idx][15+idy*24] = Ain[idx + lda*15 + idy*24*lda];
		lA[idx][16+idy*24] = Ain[idx + lda*16 + idy*24*lda];
		lA[idx][17+idy*24] = Ain[idx + lda*17 + idy*24*lda];
		lA[idx][18+idy*24] = Ain[idx + lda*18 + idy*24*lda];
		lA[idx][19+idy*24] = Ain[idx + lda*19 + idy*24*lda];
		lA[idx][20+idy*24] = Ain[idx + lda*20 + idy*24*lda];
		lA[idx][21+idy*24] = Ain[idx + lda*21 + idy*24*lda];
		lA[idx][22+idy*24] = Ain[idx + lda*22 + idy*24*lda];
		lA[idx][23+idy*24] = Ain[idx + lda*23 + idy*24*lda];
		
		lB[0+idy*24][idx] = B[idx*NB + idy*24];
		lB[1+idy*24][idx]  = B[idx*NB + idy*24 + 1];
		lB[2+idy*24][idx]  = B[idx*NB + idy*24 + 2];
		lB[3+idy*24][idx]  = B[idx*NB + idy*24 + 3];
		lB[4+idy*24][idx]  = B[idx*NB + idy*24 + 4];
		lB[5+idy*24][idx]  = B[idx*NB + idy*24 + 5];
		lB[6+idy*24][idx]  = B[idx*NB + idy*24 + 6];
		lB[7+idy*24][idx]  = B[idx*NB + idy*24 + 7];
		lB[8+idy*24][idx]  = B[idx*NB + idy*24 + 8];
		lB[9+idy*24][idx]  = B[idx*NB + idy*24 + 9];
		lB[10+idy*24][idx]  = B[idx*NB + idy*24 + 10];
		lB[11+idy*24][idx]  = B[idx*NB + idy*24 + 11];
		lB[12+idy*24][idx]  = B[idx*NB + idy*24 + 12];
		lB[13+idy*24][idx]  = B[idx*NB + idy*24 + 13];
		lB[14+idy*24][idx]  = B[idx*NB + idy*24 + 14];
		lB[15+idy*24][idx]  = B[idx*NB + idy*24 + 15];
		lB[16+idy*24][idx]  = B[idx*NB + idy*24 + 16];
		lB[17+idy*24][idx]  = B[idx*NB + idy*24 + 17];
		lB[18+idy*24][idx]  = B[idx*NB + idy*24 + 18];
		lB[19+idy*24][idx]  = B[idx*NB + idy*24 + 19];
		lB[20+idy*24][idx]  = B[idx*NB + idy*24 + 20];
		lB[21+idy*24][idx]  = B[idx*NB + idy*24 + 21];
		lB[22+idy*24][idx]  = B[idx*NB + idy*24 + 22];
		lB[23+idy*24][idx]  = B[idx*NB + idy*24 + 23];
		barrier(CLK_LOCAL_MEM_FENCE);
		
		//do math
		
		uint i = 0;
		
		do{
			privateC[0]=mad(lA[idx][i],lB[i][0+idy*12],privateC[0]); 
			privateC[1]=mad(lA[idx][i],lB[i][1+idy*12],privateC[1]); 
			privateC[2]=mad(lA[idx][i],lB[i][2+idy*12],privateC[2]); 
			privateC[3]=mad(lA[idx][i],lB[i][3+idy*12],privateC[3]); 
			privateC[4]=mad(lA[idx][i],lB[i][4+idy*12],privateC[4]); 
			privateC[5]=mad(lA[idx][i],lB[i][5+idy*12],privateC[5]); 
			privateC[6]=mad(lA[idx][i],lB[i][6+idy*12],privateC[6]); 
			privateC[7]=mad(lA[idx][i],lB[i][7+idy*12],privateC[7]); 
			privateC[8]=mad(lA[idx][i],lB[i][8+idy*12],privateC[8]); 
			privateC[9]=mad(lA[idx][i],lB[i][9+idy*12],privateC[9]); 
			privateC[10]=mad(lA[idx][i],lB[i][10+idy*12],privateC[10]); 
			privateC[11]=mad(lA[idx][i],lB[i][11+idy*12],privateC[11]); 
			i = i + 1;
		}while(i < 48);
		
		Ain += 48*lda;
		B += 48;
	}while(--block_k>0);
	
	uint i = 0;
	do{
        C[NB*idy*12+NB*i+idx] = privateC[i];
	    i = i + 1;
	}while(i < 12);
	
	
}

__kernel void
TRIPLE_DGEMM_UPDATE_96_PART2_R (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
	// Ain is the non inverse matrix; the size of Ain is lda * na
	// offAin is the offset of Ain
	// d_dinvA is the inversed matrix. the size of d_invA is NB * (na-1)/NB + 1
	// blk is subblock size, which is 48 here.
	// lda in leading dimension. Column major here
	// npages = (na-1)/12*2 + 1; for 96 this is 1 for 192 this is 2

	//Work group size is [24, 2]
	//global work size is [48*number of blocks, 4]
	//each work item in each work group is responsible for 12 elements (1/4) in that row
	//each work group is responsible for 24 by 24 macro tile;
	
	////////////// -invA11*invA12
    const uint gidx = get_group_id(0);
	const uint gidy = get_group_id(1);
    const uint idx = get_local_id(0);
	const uint idy = get_local_id(1);
	
	//uint page = gidx / 2;//0-1 for 192; 0 for 96
    //const uint page = (gidx/2)%2;//index of page within a page_block; 1 pages per page_block
	const uint page_block = gidx/4;//#index of page_block; 4 WG per page; 4 WG per page_block
	
	__global double *A, *B, *C;
    __local double lA[24][48];
    __local double lB[48][24];
	double privateC[12] = {(double)0};
	
	//decide invA11 location for each page
	//each workgroup loads half of A (left or right)
	//A = d_dinvA + page*NB*NB + gidx%2*(blk/2);
	A = d_dinvA + page_block*NB*NB + gidx%4*(blk/4);
	
	//decide invA12 (B) location for each page
	//actually it was saved in invA21 from last kernel
	//each workgroup loads half of B (up or down)
	//B = d_dinvA + page*NB*NB + blk*NB + gidy*(blk/2)*NB;
	B = d_dinvA + page_block*NB*NB + blk*NB + gidy*(blk/4)*NB;
	
	//decide invA12 location for each page
	//each workgroup writes 1/4 of C
	//C = d_dinvA + page*NB*NB + blk * NB + gidx%2*(blk/2) + gidy*(blk/2)*NB;
	C = d_dinvA + page_block*NB*NB + blk*NB + gidx%4*(blk/4) + gidy*(blk/4)*NB;
	
	//read A and B into LDS no transpose operated here
	//each work item loads a half row of A and half column of B
	//idx 0-23 idy 0-1
	
	uint block_k = blk / 48; //thus we need 2 iterations here
	do{
	    barrier(CLK_LOCAL_MEM_FENCE);
		lA[idx][0+idy*24] = A[idx + idy*24*NB];
		lA[idx][1+idy*24] = A[idx + NB + idy*24*NB];
		lA[idx][2+idy*24] = A[idx + NB*2 + idy*24*NB];
		lA[idx][3+idy*24] = A[idx + NB*3 + idy*24*NB];
		lA[idx][4+idy*24] = A[idx + NB*4 + idy*24*NB];
		lA[idx][5+idy*24] = A[idx + NB*5 + idy*24*NB];
		lA[idx][6+idy*24] = A[idx + NB*6 + idy*24*NB];
		lA[idx][7+idy*24] = A[idx + NB*7 + idy*24*NB];
		lA[idx][8+idy*24] = A[idx + NB*8 + idy*24*NB];
		lA[idx][9+idy*24] = A[idx + NB*9 + idy*24*NB];
		lA[idx][10+idy*24] = A[idx + NB*10 + idy*24*NB];
		lA[idx][11+idy*24] = A[idx + NB*11 + idy*24*NB];
		lA[idx][12+idy*24] = A[idx + NB*12 + idy*24*NB];
		lA[idx][13+idy*24] = A[idx + NB*13 + idy*24*NB];
		lA[idx][14+idy*24] = A[idx + NB*14 + idy*24*NB];
		lA[idx][15+idy*24] = A[idx + NB*15 + idy*24*NB];
		lA[idx][16+idy*24] = A[idx + NB*16 + idy*24*NB];
		lA[idx][17+idy*24] = A[idx + NB*17 + idy*24*NB];
		lA[idx][18+idy*24] = A[idx + NB*18 + idy*24*NB];
		lA[idx][19+idy*24] = A[idx + NB*19 + idy*24*NB];
		lA[idx][20+idy*24] = A[idx + NB*20 + idy*24*NB];
		lA[idx][21+idy*24] = A[idx + NB*21 + idy*24*NB];
		lA[idx][22+idy*24] = A[idx + NB*22 + idy*24*NB];
		lA[idx][23+idy*24] = A[idx + NB*23 + idy*24*NB];
		
		lB[0+idy*24][idx] = B[idx*NB + idy*24];
		lB[1+idy*24][idx]  = B[idx*NB + idy*24 + 1];
		lB[2+idy*24][idx]  = B[idx*NB + idy*24 + 2];
		lB[3+idy*24][idx]  = B[idx*NB + idy*24 + 3];
		lB[4+idy*24][idx]  = B[idx*NB + idy*24 + 4];
		lB[5+idy*24][idx]  = B[idx*NB + idy*24 + 5];
		lB[6+idy*24][idx]  = B[idx*NB + idy*24 + 6];
		lB[7+idy*24][idx]  = B[idx*NB + idy*24 + 7];
		lB[8+idy*24][idx]  = B[idx*NB + idy*24 + 8];
		lB[9+idy*24][idx]  = B[idx*NB + idy*24 + 9];
		lB[10+idy*24][idx]  = B[idx*NB + idy*24 + 10];
		lB[11+idy*24][idx]  = B[idx*NB + idy*24 + 11];
		lB[12+idy*24][idx]  = B[idx*NB + idy*24 + 12];
		lB[13+idy*24][idx]  = B[idx*NB + idy*24 + 13];
		lB[14+idy*24][idx]  = B[idx*NB + idy*24 + 14];
		lB[15+idy*24][idx]  = B[idx*NB + idy*24 + 15];
		lB[16+idy*24][idx]  = B[idx*NB + idy*24 + 16];
		lB[17+idy*24][idx]  = B[idx*NB + idy*24 + 17];
		lB[18+idy*24][idx]  = B[idx*NB + idy*24 + 18];
		lB[19+idy*24][idx]  = B[idx*NB + idy*24 + 19];
		lB[20+idy*24][idx]  = B[idx*NB + idy*24 + 20];
		lB[21+idy*24][idx]  = B[idx*NB + idy*24 + 21];
		lB[22+idy*24][idx]  = B[idx*NB + idy*24 + 22];
		lB[23+idy*24][idx]  = B[idx*NB + idy*24 + 23];
		barrier(CLK_LOCAL_MEM_FENCE);
		
		//do math
		
		uint i = 0;
		
		do{
			privateC[0]=mad(lA[idx][i],lB[i][0+idy*12],privateC[0]); 
			privateC[1]=mad(lA[idx][i],lB[i][1+idy*12],privateC[1]); 
			privateC[2]=mad(lA[idx][i],lB[i][2+idy*12],privateC[2]); 
			privateC[3]=mad(lA[idx][i],lB[i][3+idy*12],privateC[3]); 
			privateC[4]=mad(lA[idx][i],lB[i][4+idy*12],privateC[4]); 
			privateC[5]=mad(lA[idx][i],lB[i][5+idy*12],privateC[5]); 
			privateC[6]=mad(lA[idx][i],lB[i][6+idy*12],privateC[6]); 
			privateC[7]=mad(lA[idx][i],lB[i][7+idy*12],privateC[7]); 
			privateC[8]=mad(lA[idx][i],lB[i][8+idy*12],privateC[8]); 
			privateC[9]=mad(lA[idx][i],lB[i][9+idy*12],privateC[9]); 
			privateC[10]=mad(lA[idx][i],lB[i][10+idy*12],privateC[10]); 
			privateC[11]=mad(lA[idx][i],lB[i][11+idy*12],privateC[11]); 
			i = i + 1;
		}while(i < 48);
		
		A += 48*NB;
		B += 48;
	
	}while(--block_k>0);
	
	uint i = 0;
	do{
        C[NB*idy*12+NB*i+idx] = -1 * privateC[i];
	    i = i + 1;
	}while(i < 12);
	
	
}

";