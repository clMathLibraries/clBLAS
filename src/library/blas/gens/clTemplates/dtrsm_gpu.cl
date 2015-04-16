
static const char * dtrsm_gpu_kernels = "

//#define __mul(i,j) ((i)*(j))
//#define qmod(a, b) ((a)-(__mul((b), (a)/(b))))

#define __mul(i,j) ((i)*(j))
#define qmod(a, b) ((a)%(b))


#define BLOCK_SIZE 16 // inner blocking size, <=32
#define NB 128        // outer blocking size, >BLOCK_SIZE

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


//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//


__kernel void DIAG_DTRTRI_KERNEL_LOWER(int isDiagUnit, 
				       __global double const * restrict A,
                                       uint offA,
				       __global double *d_dinvA,
				       uint lda,
                                       uint na)
{
  
  int i, j;
  double Ystx=  0;
  __local double *Bw=0, *x=0, *y=0;
  double switcher;
  double neg_switcher;


 // Thread index
  int tx = get_local_id(0);
  int txw;

  int gx = get_global_id(0);

  // Block index
  int bx = get_group_id(0);

  A = A + offA;

  __global const double *Aoff = A+bx*lda*BLOCK_SIZE+bx*BLOCK_SIZE;
  int NumBLperNB = NB/BLOCK_SIZE;
  d_dinvA += bx/NumBLperNB*NB*NB + (bx % NumBLperNB)*(NB*BLOCK_SIZE + BLOCK_SIZE);

  __local double Bs[BLOCK_SIZE*BLOCK_SIZE];
  __local double workspace[BLOCK_SIZE];    // workspace used to store the current working column

  // load A
#pragma unroll
  for( i=0; i < BLOCK_SIZE; i++ )
    {
      if(tx >= i && gx < na )
        {
	  Bs[i*BLOCK_SIZE+tx] = *(Aoff+i*lda+tx);
        }
      else
        {
	  Bs[i*BLOCK_SIZE+tx] = ZERO;
        }
    }

  // read in the whole square block of my A and zero out the non data triangular
  // not the upper or lower diagonal

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

  /*
   * the lower case
   */


  if( !(tx < BLOCK_SIZE-1) )
    {
      switcher = ONE;
    }
  else
    {
      switcher = ZERO;
    }

  Bs[(BLOCK_SIZE-1)*BLOCK_SIZE+tx] = switcher * Bs[(BLOCK_SIZE-1)*BLOCK_SIZE+tx];    
  // zero out the last column, except the diagonal element

  for( i=BLOCK_SIZE-2; i >= 0; i-- ) {
    Ystx =  ZERO;
       
    if( tx > i)
      {
	switcher = ONE;
      }
    else
      {
	switcher = ZERO;
      }

    //dtrmv
    Bw = Bs+(i+1)*BLOCK_SIZE+i+1;
    workspace[tx] = *(Bs+i*BLOCK_SIZE+tx);
    x = workspace+i+1;
    y = Bs+i*BLOCK_SIZE;

    txw = (tx-i-1);

#pragma unroll
    for( j=0; j < BLOCK_SIZE-i-1; j++ )
      Ystx += switcher*(*(Bw+j*BLOCK_SIZE+txw)*x[j]);

    //sscal

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

    y[tx] = switcher * Ystx*(-Bs[i*BLOCK_SIZE+i])+ neg_switcher *y[tx];

    //__syncthreads();
    barrier(CLK_LOCAL_MEM_FENCE);

  }

  // write back A
#pragma unroll
  for( i=0; i < BLOCK_SIZE; i++ )
    *(d_dinvA+i*NB+tx) = Bs[i*BLOCK_SIZE+tx];
}


/*
 * daxpy computes c += alpha*b, where b and c are 16-element vectors.
 */
static void daxpy(
    double alpha,
    __local const double * __restrict__ b,
    double * __restrict__ c )
{
    c[0]  += alpha * b[0];
    c[1]  += alpha * b[1];
    c[2]  += alpha * b[2];
    c[3]  += alpha * b[3];
    c[4]  += alpha * b[4];
    c[5]  += alpha * b[5];
    c[6]  += alpha * b[6];
    c[7]  += alpha * b[7];
    c[8]  += alpha * b[8];
    c[9]  += alpha * b[9];
    c[10] += alpha * b[10];
    c[11] += alpha * b[11];
    c[12] += alpha * b[12];
    c[13] += alpha * b[13];
    c[14] += alpha * b[14];
    c[15] += alpha * b[15];
}


/*
 * B21 = -inv(A11)*A12*inv(A22)
 */
__kernel void 
TRIPLE_DGEMM_UPDATE_16_R (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, uint lda, int npages, int na)
{
    const int bIdy = get_group_id(1)/npages;
    //const int page = (blockIdx.y)%(npages);
    const int page = qmod(get_group_id(1), npages);
    const int inx = get_local_id(0);
    const int iny = get_local_id(1);
    const int ibx = get_group_id(0) * (get_local_size(0)*get_local_size(1));
    const int iby = bIdy * 16;
    const int id = inx + iny*get_local_size(0);
    __local double bs[16][17];

    Ain = Ain + offAin;

    int PagesPerNB = NB/(blk*2);
    //--------------------------part one---------------------------//
    {
        // A12*inv(A22) -> A12
        // A=A12, B=inv(A22), C=A12(d_dinvA)
        __global const double *A;
        __global double *B, *C;
        int ldb = NB;
        int ldc = NB;

        d_dinvA += NB*NB*(page/PagesPerNB)
                + (qmod(page, PagesPerNB))*(blk*2)*NB
                + (qmod(page, PagesPerNB))*(blk*2);

        int xa = page*blk*2 + ibx + id ; 
        int ya = page*blk*2 + blk ; 
        int incA = ya * lda + xa ; 

        // maxA will be used to detect overflow on all subsequent accesses on A(xa, ya:ya+???) 

        int maxA ;
        if ( xa < na ) 
          maxA = lda*na ;  // macro READA will detect overflow on y dimension 
        else  
          maxA  = 0 ;  // there is already an overflow on xa 

#define READA ( (incA < maxA ) ? Ain[incA] : 0 )  
              
        B = d_dinvA + blk*NB + blk;
        C = d_dinvA + blk*NB;

        B += inx + __mul( iby + iny, ldb );
        C += ibx + id  + __mul( iby, ldc );

        __global const double *Blast = B + blk;

        double c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        do {
            double a[4]  ;
            a[0] = READA ; incA += lda ; 
            a[1] = READA ; incA += lda ; 
            a[2] = READA ; incA += lda ; 
            a[3] = READA ; incA += lda ; 

            bs[inx   ][iny   ] = B[    0*ldb];
            bs[inx   ][iny+ 4] = B[    4*ldb];
            bs[inx   ][iny+ 8] = B[    8*ldb];
            bs[inx   ][iny+12] = B[   12*ldb];
            bs[inx+ 4][iny   ] = B[ 4+ 0*ldb];
            bs[inx+ 4][iny+ 4] = B[ 4+ 4*ldb];
            bs[inx+ 4][iny+ 8] = B[ 4+ 8*ldb];
            bs[inx+ 4][iny+12] = B[ 4+12*ldb];
            bs[inx+ 8][iny   ] = B[ 8+ 0*ldb];
            bs[inx+ 8][iny+ 4] = B[ 8+ 4*ldb];
            bs[inx+ 8][iny+ 8] = B[ 8+ 8*ldb];
            bs[inx+ 8][iny+12] = B[ 8+12*ldb];
            bs[inx+12][iny   ] = B[12+ 0*ldb];
            bs[inx+12][iny+ 4] = B[12+ 4*ldb];
            bs[inx+12][iny+ 8] = B[12+ 8*ldb];
            bs[inx+12][iny+12] = B[12+12*ldb];
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);

            daxpy( a[0], &bs[ 0][0], c );  a[0] = READA ; incA += lda ;
            daxpy( a[1], &bs[ 1][0], c );  a[1] = READA ; incA += lda ;
            daxpy( a[2], &bs[ 2][0], c );  a[2] = READA ; incA += lda ;
            daxpy( a[3], &bs[ 3][0], c );  a[3] = READA ; incA += lda ;

            daxpy( a[0], &bs[ 4][0], c );  a[0] = READA ; incA += lda ;
            daxpy( a[1], &bs[ 5][0], c );  a[1] = READA ; incA += lda ;
            daxpy( a[2], &bs[ 6][0], c );  a[2] = READA ; incA += lda ;
            daxpy( a[3], &bs[ 7][0], c );  a[3] = READA ; incA += lda ;

            daxpy( a[0], &bs[ 8][0], c );  a[0] = READA ; incA += lda ;
            daxpy( a[1], &bs[ 9][0], c );  a[1] = READA ; incA += lda ;
            daxpy( a[2], &bs[10][0], c );  a[2] = READA ; incA += lda ;
            daxpy( a[3], &bs[11][0], c );  a[3] = READA ; incA += lda ;

            daxpy( a[0], &bs[12][0], c );
            daxpy( a[1], &bs[13][0], c );
            daxpy( a[2], &bs[14][0], c );
            daxpy( a[3], &bs[15][0], c );

            B += 16;
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
        } while( B < Blast );

        for( int i = 0; i < 16; i++ ) {
            C[0] = c[i];
            C += ldc;
        }
    }
    //__syncthreads();
    barrier(CLK_LOCAL_MEM_FENCE);

#undef READA

    //--------------------------part two---------------------------//
    {
        // -inv(A11)*A12 -> A12
        // A=inv(A11), B=A12, C=A12
        __global double *A, *B, *C;
        int lda = NB;
        int ldb = NB;
        int ldc = NB;

        A = d_dinvA;
        B = C = d_dinvA + blk*NB;

        A += ibx + id;
        B += inx + __mul( iby + iny, ldb );
        C += ibx + id  + __mul( iby, ldc );

        __global const double *Blast = B + blk;

        double c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        do {
            double a[4] = { A[0*lda], A[1*lda], A[2*lda], A[3*lda] };

            bs[inx   ][iny   ] = B[    0*ldb];
            bs[inx   ][iny+ 4] = B[    4*ldb];
            bs[inx   ][iny+ 8] = B[    8*ldb];
            bs[inx   ][iny+12] = B[   12*ldb];
            bs[inx+ 4][iny   ] = B[ 4+ 0*ldb];
            bs[inx+ 4][iny+ 4] = B[ 4+ 4*ldb];
            bs[inx+ 4][iny+ 8] = B[ 4+ 8*ldb];
            bs[inx+ 4][iny+12] = B[ 4+12*ldb];
            bs[inx+ 8][iny   ] = B[ 8+ 0*ldb];
            bs[inx+ 8][iny+ 4] = B[ 8+ 4*ldb];
            bs[inx+ 8][iny+ 8] = B[ 8+ 8*ldb];
            bs[inx+ 8][iny+12] = B[ 8+12*ldb];
            bs[inx+12][iny   ] = B[12+ 0*ldb];
            bs[inx+12][iny+ 4] = B[12+ 4*ldb];
            bs[inx+12][iny+ 8] = B[12+ 8*ldb];
            bs[inx+12][iny+12] = B[12+12*ldb];
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);

            A += 4*lda;
            daxpy( a[0], &bs[ 0][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 1][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[ 2][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[ 3][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[ 4][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 5][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[ 6][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[ 7][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[ 8][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 9][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[10][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[11][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[12][0], c );
            daxpy( a[1], &bs[13][0], c );
            daxpy( a[2], &bs[14][0], c );
            daxpy( a[3], &bs[15][0], c );

            B += 16;
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
        } while( B < Blast );

        for( int i = 0; i < 16; i++ ) {
            C[0] = (-1)*c[i];
            C += ldc;
        }
    }
}



__kernel void
TRIPLE_DGEMM_UPDATE_16_PART1_L (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
    const int bIdy = get_group_id(1)/npages;
    //const int page = (get_group_id(1))%(npages);
    const int page = qmod(get_group_id(1), npages);
    const int inx = get_local_id(0);
    const int iny = get_local_id(1);
    const int ibx = get_group_id(0) * (get_local_size(0)*get_local_size(1));
    const int iby = bIdy * 16;
    const int id = inx + iny*get_local_size(0);
    __local double bs[16][17];

    Ain = Ain + offAin;

    //--------------------------part one---------------------------//
    {
        // A21*inv(A11) -> A21
        // A=A21, B=inv(A11), C=A21
        __global const double *A;
        __global double *B, *C;
        int ldb = NB;
        int ldc = NB;

        int PagesPerNB = NB/(blk*2);

        d_dinvA += NB*NB*(page/PagesPerNB)
                + (qmod(page, PagesPerNB))*(blk*2)*NB
                + (qmod(page, PagesPerNB))*(blk*2);

        int xa = page*blk*2 + blk + ibx + id ; 
        int ya = page*blk*2  ; 
        int incA = ya * lda + xa ; 

        // maxA will be used to detect overflow on all subsequent accesses on A(xa, ya:ya+???) 

        int maxA ;
        if ( xa < na ) 
          maxA = lda*na ;  // macro READA will detect overflow on y dimension 
        else  
          maxA  = 0 ;  // there is already an overflow on xa 

#define READA ( (incA < maxA ) ? Ain[incA] : 0 )  
              
        B = d_dinvA;
        C = d_dinvA + blk;

        B += inx + __mul( iby + iny, ldb );
        C += ibx + id  + __mul( iby, ldc );

        __global const double *Blast = B + blk;

        double c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        do {
            double a[4]  ;
            a[0] = READA ; incA += lda ; 
            a[1] = READA ; incA += lda ; 
            a[2] = READA ; incA += lda ; 
            a[3] = READA ; incA += lda ; 

            bs[inx   ][iny   ] = B[    0*ldb];
            bs[inx   ][iny+ 4] = B[    4*ldb];
            bs[inx   ][iny+ 8] = B[    8*ldb];
            bs[inx   ][iny+12] = B[   12*ldb];
            bs[inx+ 4][iny   ] = B[ 4+ 0*ldb];
            bs[inx+ 4][iny+ 4] = B[ 4+ 4*ldb];
            bs[inx+ 4][iny+ 8] = B[ 4+ 8*ldb];
            bs[inx+ 4][iny+12] = B[ 4+12*ldb];
            bs[inx+ 8][iny   ] = B[ 8+ 0*ldb];
            bs[inx+ 8][iny+ 4] = B[ 8+ 4*ldb];
            bs[inx+ 8][iny+ 8] = B[ 8+ 8*ldb];
            bs[inx+ 8][iny+12] = B[ 8+12*ldb];
            bs[inx+12][iny   ] = B[12+ 0*ldb];
            bs[inx+12][iny+ 4] = B[12+ 4*ldb];
            bs[inx+12][iny+ 8] = B[12+ 8*ldb];
            bs[inx+12][iny+12] = B[12+12*ldb];
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);

            daxpy( a[0], &bs[ 0][0], c );  a[0] = READA ; incA += lda ; 
            daxpy( a[1], &bs[ 1][0], c );  a[1] = READA ; incA += lda ; 
            daxpy( a[2], &bs[ 2][0], c );  a[2] = READA ; incA += lda ; 
            daxpy( a[3], &bs[ 3][0], c );  a[3] = READA ; incA += lda ; 

            daxpy( a[0], &bs[ 4][0], c );  a[0] = READA ; incA += lda ; 
            daxpy( a[1], &bs[ 5][0], c );  a[1] = READA ; incA += lda ; 
            daxpy( a[2], &bs[ 6][0], c );  a[2] = READA ; incA += lda ; 
            daxpy( a[3], &bs[ 7][0], c );  a[3] = READA ; incA += lda ; 

            daxpy( a[0], &bs[ 8][0], c );  a[0] = READA ; incA += lda ; 
            daxpy( a[1], &bs[ 9][0], c );  a[1] = READA ; incA += lda ; 
            daxpy( a[2], &bs[10][0], c );  a[2] = READA ; incA += lda ; 
            daxpy( a[3], &bs[11][0], c );  a[3] = READA ; incA += lda ; 

            daxpy( a[0], &bs[12][0], c );
            daxpy( a[1], &bs[13][0], c );
            daxpy( a[2], &bs[14][0], c );
            daxpy( a[3], &bs[15][0], c );

            B += 16;
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
        } while( B < Blast );

        for( int i = 0; i < 16; i++ ) {
            C[0] = c[i];
            C += ldc;
        }
    }

#undef READA

    //__syncthreads();
    barrier(CLK_LOCAL_MEM_FENCE);
}



/*
 * B21 = -inv(A22)*A21*inv(A11)
 */
__kernel void
TRIPLE_DGEMM_UPDATE_16_PART2_L (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
    const int bIdy = get_group_id(1)/npages;
    const int page = qmod(get_group_id(1), npages);
    const int inx = get_local_id(0);
    const int iny = get_local_id(1);
    const int ibx = get_group_id(0) * (get_local_size(0)*get_local_size(1));
    const int iby = bIdy * 16;
    const int id = inx + iny*get_local_size(0);
    __local double bs[16][17];

    Ain = Ain + offAin;

    //--------------------------part two---------------------------//
    {
        // -inv(A22)*A21 -> A21
        // A=inv(A22), B=A21, C=A21
        __global double *A, *B, *C;
        int lda = NB;
        int ldb = NB;
        int ldc = NB;

        int PagesPerNB = NB/(blk*2);
        d_dinvA += NB*NB*(page/PagesPerNB)
                + (qmod(page, PagesPerNB))*(blk*2)*NB
                + (qmod(page, PagesPerNB))*(blk*2);

        A = d_dinvA + blk*NB + blk;
        B = C = d_dinvA + blk;

        A += ibx + id;
        B += inx + __mul( iby + iny, ldb );
        C += ibx + id  + __mul( iby, ldc );

        __global const double *Blast = B + blk;

        double c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        do {
            double a[4] = { A[0*lda], A[1*lda], A[2*lda], A[3*lda] };

            bs[inx   ][iny   ] = B[    0*ldb];
            bs[inx   ][iny+ 4] = B[    4*ldb];
            bs[inx   ][iny+ 8] = B[    8*ldb];
            bs[inx   ][iny+12] = B[   12*ldb];
            bs[inx+ 4][iny   ] = B[ 4+ 0*ldb];
            bs[inx+ 4][iny+ 4] = B[ 4+ 4*ldb];
            bs[inx+ 4][iny+ 8] = B[ 4+ 8*ldb];
            bs[inx+ 4][iny+12] = B[ 4+12*ldb];
            bs[inx+ 8][iny   ] = B[ 8+ 0*ldb];
            bs[inx+ 8][iny+ 4] = B[ 8+ 4*ldb];
            bs[inx+ 8][iny+ 8] = B[ 8+ 8*ldb];
            bs[inx+ 8][iny+12] = B[ 8+12*ldb];
            bs[inx+12][iny   ] = B[12+ 0*ldb];
            bs[inx+12][iny+ 4] = B[12+ 4*ldb];
            bs[inx+12][iny+ 8] = B[12+ 8*ldb];
            bs[inx+12][iny+12] = B[12+12*ldb];
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);

            A += 4*lda;
            daxpy( a[0], &bs[ 0][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 1][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[ 2][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[ 3][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[ 4][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 5][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[ 6][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[ 7][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[ 8][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 9][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[10][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[11][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[12][0], c );
            daxpy( a[1], &bs[13][0], c );
            daxpy( a[2], &bs[14][0], c );
            daxpy( a[3], &bs[15][0], c );

            B += 16;
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
        } while( B < Blast );

        for( int i = 0; i < 16; i++ ) {
            C[0] = (-1)*c[i];
            C += ldc;
        }
    }
    //__syncthreads();
    barrier(CLK_LOCAL_MEM_FENCE);
}

/*
 * B21 = -inv(A11)*A12*inv(A22)
 */
__kernel void
TRIPLE_DGEMM_UPDATE_32_PART1_R (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
    const int bIdy = get_group_id(1)/npages;
    const int page = qmod(get_group_id(1), npages);
    const int inx = get_local_id(0);
    const int iny = get_local_id(1);
    const int ibx = get_group_id(0) * (get_local_size(0)*get_local_size(1));
    const int iby = bIdy * 16;
    const int id = inx + iny*get_local_size(0);
    __local double bs[16][17];

    Ain = Ain + offAin;

    int PagesPerNB = NB/(blk*2);
    //--------------------------part one---------------------------//
    {
        // A12*inv(A22) -> A21
        // A=A12, B=inv(A22), C=A12(d_dinvA)
        __global const double *A;
        __global double *B, *C;
        int ldb = NB;
        int ldc = NB;

        d_dinvA += NB*NB*(page/PagesPerNB)
                + (qmod(page, PagesPerNB))*(blk*2)*NB
                + (qmod(page, PagesPerNB))*(blk*2);

        int xa = page*blk*2 + ibx + id ; 
        int ya = page*blk*2 + blk ; 
        int incA = ya * lda + xa ; 

        // maxA will be used to detect overflow on all subsequent accesses on A(xa, ya:ya+???) 

        int maxA ;
        if ( xa < na ) 
          maxA = lda*na ;   // macro READA will detect overflow on y dimension  
        else  
          maxA  = 0 ;  // there is already an overflow on xa 

#define READA ( (incA < maxA ) ? Ain[incA] : 0 )  

        B = d_dinvA + blk*NB + blk;
        C = d_dinvA + blk*NB;

        B += inx + __mul( iby + iny, ldb );
        C += ibx + id  + __mul( iby, ldc );

        __global const double *Blast = B + blk;

        double c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        do {
            double a[4]  ;
            a[0] = READA ; incA += lda ; 
            a[1] = READA ; incA += lda ; 
            a[2] = READA ; incA += lda ; 
            a[3] = READA ; incA += lda ; 

            bs[inx  ][iny   ] = B[   0*ldb];
            bs[inx  ][iny+ 4] = B[   4*ldb];
            bs[inx  ][iny+ 8] = B[   8*ldb];
            bs[inx  ][iny+12] = B[  12*ldb];
            bs[inx+8][iny   ] = B[8+ 0*ldb];
            bs[inx+8][iny+ 4] = B[8+ 4*ldb];
            bs[inx+8][iny+ 8] = B[8+ 8*ldb];
            bs[inx+8][iny+12] = B[8+12*ldb];
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);

            daxpy( a[0], &bs[ 0][0], c );  a[0] = READA ; incA += lda ;
            daxpy( a[1], &bs[ 1][0], c );  a[1] = READA ; incA += lda ;
            daxpy( a[2], &bs[ 2][0], c );  a[2] = READA ; incA += lda ;
            daxpy( a[3], &bs[ 3][0], c );  a[3] = READA ; incA += lda ;

            daxpy( a[0], &bs[ 4][0], c );  a[0] = READA ; incA += lda ;
            daxpy( a[1], &bs[ 5][0], c );  a[1] = READA ; incA += lda ;
            daxpy( a[2], &bs[ 6][0], c );  a[2] = READA ; incA += lda ;
            daxpy( a[3], &bs[ 7][0], c );  a[3] = READA ; incA += lda ;

            daxpy( a[0], &bs[ 8][0], c );  a[0] = READA ; incA += lda ;
            daxpy( a[1], &bs[ 9][0], c );  a[1] = READA ; incA += lda ;
            daxpy( a[2], &bs[10][0], c );  a[2] = READA ; incA += lda ;
            daxpy( a[3], &bs[11][0], c );  a[3] = READA ; incA += lda ;

            daxpy( a[0], &bs[12][0], c );
            daxpy( a[1], &bs[13][0], c );
            daxpy( a[2], &bs[14][0], c );
            daxpy( a[3], &bs[15][0], c );

            B += 16;
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
        } while( B < Blast );

        for( int i = 0; i < 16; i++ ) {
            C[0] = c[i];
            C += ldc;
        }
    }

    //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
}

/*
 * B21 = -inv(A11)*A12*inv(A22)
 */
__kernel void
TRIPLE_DGEMM_UPDATE_32_PART2_R (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
    const int bIdy = get_group_id(1)/npages;
    const int page = qmod(get_group_id(1), npages);
    const int inx = get_local_id(0);
    const int iny = get_local_id(1);
    const int ibx = get_group_id(0) * (get_local_size(0)*get_local_size(1));
    const int iby = bIdy * 16;
    const int id = inx + iny*get_local_size(0);
    __local double bs[16][17];

    Ain = Ain + offAin;

    int PagesPerNB = NB/(blk*2);

    //--------------------------part two---------------------------//
    {
        // -inv(A11)*A12 -> A12
        // A=inv(A11), B=A12, C=A12
        __global double *A, *B, *C;
        int lda = NB;
        int ldb = NB;
        int ldc = NB;

        d_dinvA += NB*NB*(page/PagesPerNB)
                + (qmod(page, PagesPerNB))*(blk*2)*NB
                + (qmod(page, PagesPerNB))*(blk*2);

        A = d_dinvA;
        B = C = d_dinvA + blk*NB;

        A += ibx + id;
        B += inx + __mul( iby + iny, ldb );
        C += ibx + id  + __mul( iby, ldc );

        __global const double *Blast = B + blk;

        double c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        do {
            double a[4] = { A[0*lda], A[1*lda], A[2*lda], A[3*lda] };

            bs[inx  ][iny   ] = B[   0*ldb];
            bs[inx  ][iny+ 4] = B[   4*ldb];
            bs[inx  ][iny+ 8] = B[   8*ldb];
            bs[inx  ][iny+12] = B[  12*ldb];
            bs[inx+8][iny   ] = B[8+ 0*ldb];
            bs[inx+8][iny+ 4] = B[8+ 4*ldb];
            bs[inx+8][iny+ 8] = B[8+ 8*ldb];
            bs[inx+8][iny+12] = B[8+12*ldb];
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);

            A += 4*lda;
            daxpy( a[0], &bs[ 0][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 1][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[ 2][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[ 3][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[ 4][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 5][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[ 6][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[ 7][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[ 8][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 9][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[10][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[11][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[12][0], c );
            daxpy( a[1], &bs[13][0], c );
            daxpy( a[2], &bs[14][0], c );
            daxpy( a[3], &bs[15][0], c );

            B += 16;
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
        } while( B < Blast );

        for( int i = 0; i < 16; i++ ) {
            C[0] = (-1)*c[i];
            C += ldc;
        }
    }
}

/*
 * B21 = -inv(A22)*A21*inv(A11)
 */
__kernel void
TRIPLE_DGEMM_UPDATE_32_PART1_L (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
    const int bIdy = get_group_id(1)/npages;
    const int page = qmod(get_group_id(1), npages);
    const int inx = get_local_id(0);
    const int iny = get_local_id(1);
    const int ibx = get_group_id(0) * (get_local_size(0)*get_local_size(1));
    const int iby = bIdy * 16;
    const int id = inx + iny*get_local_size(0);
    __local double bs[16][17];

    Ain = Ain + offAin;

    int PagesPerNB = NB/(blk*2);
    //--------------------------part one---------------------------//
    {
        // A21*inv(A11) -> A21
        // A=A21, B=inv(A11), C=A21
        __global const double *A;
        __global double *B, *C;
        int ldb = NB;
        int ldc = NB;

        d_dinvA += NB*NB*(page/PagesPerNB)
                + (qmod(page, PagesPerNB))*(blk*2)*NB
                + (qmod(page, PagesPerNB))*(blk*2);

        int xa = page*blk*2 + blk +  ibx + id ; 
        int ya = page*blk*2 ; 
        int incA = ya * lda + xa ; 

        // maxA will be used to detect overflow on all subsequent accesses on A(xa, ya:ya+???) 

        int maxA ;
        if ( xa < na ) 
          maxA = lda*na ;  // macro READA will detect overflow on y dimension 
        else  
          maxA  = 0 ;  // there is already an overflow on xa 

#define READA ( (incA < maxA ) ? Ain[incA] : 0 )  
              
        B = d_dinvA;
        C = d_dinvA + blk;

        B += inx + __mul( iby + iny, ldb );
        C += ibx + id  + __mul( iby, ldc );

        __global const double *Blast = B + blk;

        double c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        do {
            double a[4]  ;
            a[0] = READA ; incA += lda ; 
            a[1] = READA ; incA += lda ; 
            a[2] = READA ; incA += lda ; 
            a[3] = READA ; incA += lda ; 

            bs[inx  ][iny   ] = B[   0*ldb];
            bs[inx  ][iny+ 4] = B[   4*ldb];
            bs[inx  ][iny+ 8] = B[   8*ldb];
            bs[inx  ][iny+12] = B[  12*ldb];
            bs[inx+8][iny   ] = B[8+ 0*ldb];
            bs[inx+8][iny+ 4] = B[8+ 4*ldb];
            bs[inx+8][iny+ 8] = B[8+ 8*ldb];
            bs[inx+8][iny+12] = B[8+12*ldb];
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);

            daxpy( a[0], &bs[ 0][0], c );  a[0] = READA ; incA += lda ; 
            daxpy( a[1], &bs[ 1][0], c );  a[1] = READA ; incA += lda ; 
            daxpy( a[2], &bs[ 2][0], c );  a[2] = READA ; incA += lda ; 
            daxpy( a[3], &bs[ 3][0], c );  a[3] = READA ; incA += lda ; 

            daxpy( a[0], &bs[ 4][0], c );  a[0] = READA ; incA += lda ; 
            daxpy( a[1], &bs[ 5][0], c );  a[1] = READA ; incA += lda ; 
            daxpy( a[2], &bs[ 6][0], c );  a[2] = READA ; incA += lda ; 
            daxpy( a[3], &bs[ 7][0], c );  a[3] = READA ; incA += lda ; 

            daxpy( a[0], &bs[ 8][0], c );  a[0] = READA ; incA += lda ; 
            daxpy( a[1], &bs[ 9][0], c );  a[1] = READA ; incA += lda ; 
            daxpy( a[2], &bs[10][0], c );  a[2] = READA ; incA += lda ; 
            daxpy( a[3], &bs[11][0], c );  a[3] = READA ; incA += lda ; 

            daxpy( a[0], &bs[12][0], c );
            daxpy( a[1], &bs[13][0], c );
            daxpy( a[2], &bs[14][0], c );
            daxpy( a[3], &bs[15][0], c );

            B += 16;
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
        } while( B < Blast );

        for( int i = 0; i < 16; i++ ) {
            C[0] = c[i];
            C += ldc;
        }
    }

    //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
}

/*
 * B21 = -inv(A22)*A21*inv(A11)
 */
__kernel void
TRIPLE_DGEMM_UPDATE_32_PART2_L (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
    const int bIdy = get_group_id(1)/npages;
    const int page = qmod(get_group_id(1), npages);
    const int inx = get_local_id(0);
    const int iny = get_local_id(1);
    const int ibx = get_group_id(0) * (get_local_size(0)*get_local_size(1));
    const int iby = bIdy * 16;
    const int id = inx + iny*get_local_size(0);
    __local double bs[16][17];

    Ain = Ain + offAin;

    int PagesPerNB = NB/(blk*2);
    //--------------------------part two---------------------------//
    {
        // -inv(A22)*A21 -> A21
        // A=inv(A22), B=A21, C=A21
        __global const double *A;
        __global double *B, *C;
        int lda = NB;
        int ldb = NB;
        int ldc = NB;

        d_dinvA += NB*NB*(page/PagesPerNB)
                + (qmod(page, PagesPerNB))*(blk*2)*NB
                + (qmod(page, PagesPerNB))*(blk*2);

        A = d_dinvA + blk*NB + blk;
        B = C = d_dinvA + blk;

        A += ibx + id;
        B += inx + __mul( iby + iny, ldb );
        C += ibx + id  + __mul( iby, ldc );

        __global const double *Blast = B + blk;

        double c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        do {
            double a[4] = { A[0*lda], A[1*lda], A[2*lda], A[3*lda] };

            bs[inx  ][iny   ] = B[   0*ldb];
            bs[inx  ][iny+ 4] = B[   4*ldb];
            bs[inx  ][iny+ 8] = B[   8*ldb];
            bs[inx  ][iny+12] = B[  12*ldb];
            bs[inx+8][iny   ] = B[8+ 0*ldb];
            bs[inx+8][iny+ 4] = B[8+ 4*ldb];
            bs[inx+8][iny+ 8] = B[8+ 8*ldb];
            bs[inx+8][iny+12] = B[8+12*ldb];
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);

            A += 4*lda;
            daxpy( a[0], &bs[ 0][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 1][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[ 2][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[ 3][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[ 4][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 5][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[ 6][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[ 7][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[ 8][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 9][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[10][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[11][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[12][0], c );
            daxpy( a[1], &bs[13][0], c );
            daxpy( a[2], &bs[14][0], c );
            daxpy( a[3], &bs[15][0], c );

            B += 16;
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
        } while( B < Blast );

        for( int i = 0; i < 16; i++ ) {
            C[0] = (-1)*c[i];
            C += ldc;
        }
    }
}

/*
 * B21 = -inv(A11)*A12*inv(A22)
 */
__kernel void
TRIPLE_DGEMM_UPDATE_64_PART1_R (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
    const int bIdy = get_group_id(1)/npages;
    const int page = qmod(get_group_id(1), npages);
    const int inx = get_local_id(0);
    const int iny = get_local_id(1);
    const int ibx = get_group_id(0)*64;
    const int iby = bIdy*16;
    const int id = inx + iny*16;
    __local double bs[16][17];

    Ain = Ain + offAin;

    int PagesPerNB = NB/(blk*2);
    //--------------------------part one---------------------------//
    {
        // A12*inv(A22) -> A12(d_dinvA)
        // A=A12, B=inv(A22), C=A12
        __global const double *A;
        __global double *B, *C;
        int ldb = NB;
        int ldc = NB;

        d_dinvA += NB*NB*(page/PagesPerNB)
                + (qmod(page, PagesPerNB))*(blk*2)*NB
                + (qmod(page, PagesPerNB))*(blk*2);

        int xa = page*blk*2 + ibx + id ; 
        int ya = page*blk*2 + blk ; 
        int incA = ya * lda + xa ; 

        // maxA will be used to detect overflow on all subsequent accesses on A(xa, ya:ya+???) 

        int maxA ;
        if ( xa < na ) 
          maxA = lda*na ;   // macro READA will detect overflow on y dimension
        else  
          maxA  = 0 ;  // there is already an overflow on xa 

#define READA ( (incA < maxA ) ? Ain[incA] : 0 )  

        B = d_dinvA + blk*NB + blk;
        C = d_dinvA + blk*NB;

        B += inx + __mul( iby + iny, ldb );
        C += ibx + id  + __mul( iby, ldc );

        __global const double *Blast = B + blk;

        double c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        do {
            double a[4]  ;
            a[0] = READA ; incA += lda ; 
            a[1] = READA ; incA += lda ; 
            a[2] = READA ; incA += lda ; 
            a[3] = READA ; incA += lda ; 

            bs[inx][iny   ] = B[ 0*ldb];
            bs[inx][iny+ 4] = B[ 4*ldb];
            bs[inx][iny+ 8] = B[ 8*ldb];
            bs[inx][iny+12] = B[12*ldb];
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);

            daxpy( a[0], &bs[ 0][0], c );  a[0] = READA ; incA += lda ;
            daxpy( a[1], &bs[ 1][0], c );  a[1] = READA ; incA += lda ;
            daxpy( a[2], &bs[ 2][0], c );  a[2] = READA ; incA += lda ;
            daxpy( a[3], &bs[ 3][0], c );  a[3] = READA ; incA += lda ;

            daxpy( a[0], &bs[ 4][0], c );  a[0] = READA ; incA += lda ;
            daxpy( a[1], &bs[ 5][0], c );  a[1] = READA ; incA += lda ;
            daxpy( a[2], &bs[ 6][0], c );  a[2] = READA ; incA += lda ;
            daxpy( a[3], &bs[ 7][0], c );  a[3] = READA ; incA += lda ;

            daxpy( a[0], &bs[ 8][0], c );  a[0] = READA ; incA += lda ;
            daxpy( a[1], &bs[ 9][0], c );  a[1] = READA ; incA += lda ;
            daxpy( a[2], &bs[10][0], c );  a[2] = READA ; incA += lda ;
            daxpy( a[3], &bs[11][0], c );  a[3] = READA ; incA += lda ;

            daxpy( a[0], &bs[12][0], c );
            daxpy( a[1], &bs[13][0], c );
            daxpy( a[2], &bs[14][0], c );
            daxpy( a[3], &bs[15][0], c );

            B += 16;
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
        } while( B < Blast );

#undef READA
        for( int i = 0; i < 16; i++ ) {
            C[0] = c[i];
            C += ldc;
        }
    }
}

/*
 * B21 = -inv(A11)*A12*inv(A22)
 */
__kernel void
TRIPLE_DGEMM_UPDATE_64_PART2_R (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
    const int bIdy = get_group_id(1)/npages;
    const int page = qmod(get_group_id(1), npages);
    const int inx = get_local_id(0);
    const int iny = get_local_id(1);
    const int ibx = get_group_id(0)*64;
    const int iby = bIdy*16;
    const int id = inx + iny*16;
    __local double bs[16][17];

    Ain = Ain + offAin;

    int PagesPerNB = NB/(blk*2);

    //--------------------------part two---------------------------//
    {
        // -inv(A11)*A12 -> A12
        // A=inv(A11), B=A12, C=A12
        __global const double *A;
        __global double *B, *C;
        int lda = NB;
        int ldb = NB;
        int ldc = NB;

        d_dinvA += NB*NB*(page/PagesPerNB)
                + (qmod(page, PagesPerNB))*(blk*2)*NB
                + (qmod(page, PagesPerNB))*(blk*2);

        A = d_dinvA;
        B = C = d_dinvA + blk*NB;

        A += ibx + id;
        B += inx + __mul( iby + iny, ldb );
        C += ibx + id  + __mul( iby, ldc );

        __global const double *Blast = B + blk;

        double c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        do {
            double a[4] = { A[0*lda], A[1*lda], A[2*lda], A[3*lda] };

            bs[inx][iny   ] = B[ 0*ldb];
            bs[inx][iny+ 4] = B[ 4*ldb];
            bs[inx][iny+ 8] = B[ 8*ldb];
            bs[inx][iny+12] = B[12*ldb];
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);

            A += 4*lda;
            daxpy( a[0], &bs[ 0][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 1][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[ 2][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[ 3][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[ 4][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 5][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[ 6][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[ 7][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[ 8][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 9][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[10][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[11][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[12][0], c );
            daxpy( a[1], &bs[13][0], c );
            daxpy( a[2], &bs[14][0], c );
            daxpy( a[3], &bs[15][0], c );

            B += 16;
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
        } while( B < Blast );

        for( int i = 0; i < 16; i++ ) {
            C[0] = (-1)*c[i];
            C += ldc;
        }
    }
}

/*
 * B21 = -inv(A22)*A21*inv(A11)
 */
__kernel void
TRIPLE_DGEMM_UPDATE_64_PART1_L (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
    const int bIdy = get_group_id(1)/npages;
    const int page = qmod(get_group_id(1), npages);
    const int inx = get_local_id(0);
    const int iny = get_local_id(1);
    const int ibx = get_group_id(0)*64;
    const int iby = bIdy*16;
    const int id = inx + iny*16;
    __local double bs[16][17];

    Ain = Ain + offAin;

    int PagesPerNB = NB/(blk*2);
    //--------------------------part one---------------------------//
    {
        // A21*inv(A11) -> A21
        // A=A21, B=inv(A11), C=A21
        __global const double *A;
        __global double *B, *C;
        int ldb = NB;
        int ldc = NB;

        d_dinvA += NB*NB*(page/PagesPerNB)
                + (qmod(page, PagesPerNB))*(blk*2)*NB
                + (qmod(page, PagesPerNB))*(blk*2);
        int xa = page*blk*2 + blk + ibx + id ; 
        int ya = page*blk*2 ; 
        int incA = ya * lda + xa ; 

        // maxA will be used to detect overflow on all subsequent accesses on A(xa, ya:ya+???) 

        int maxA ;
        if ( xa < na ) 
          maxA = lda*na ;  // macro READA will detect overflow on y dimension 
        else  
          maxA  = 0 ;  // there is already an overflow on xa 

#define READA ( (incA < maxA ) ? Ain[incA] : 0 )  
              
        B = d_dinvA;
        C = d_dinvA + blk;

        B += inx + __mul( iby + iny, ldb );
        C += ibx + id  + __mul( iby, ldc );

        __global const double *Blast = B + blk;

        double c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        do {
            double a[4]  ;
            a[0] = READA ; incA += lda ; 
            a[1] = READA ; incA += lda ; 
            a[2] = READA ; incA += lda ; 
            a[3] = READA ; incA += lda ; 

            bs[inx][iny   ] = B[ 0*ldb];
            bs[inx][iny+ 4] = B[ 4*ldb];
            bs[inx][iny+ 8] = B[ 8*ldb];
            bs[inx][iny+12] = B[12*ldb];
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);

            daxpy( a[0], &bs[ 0][0], c );  a[0] = READA ; incA += lda ; 
            daxpy( a[1], &bs[ 1][0], c );  a[1] = READA ; incA += lda ; 
            daxpy( a[2], &bs[ 2][0], c );  a[2] = READA ; incA += lda ; 
            daxpy( a[3], &bs[ 3][0], c );  a[3] = READA ; incA += lda ; 

            daxpy( a[0], &bs[ 4][0], c );  a[0] = READA ; incA += lda ; 
            daxpy( a[1], &bs[ 5][0], c );  a[1] = READA ; incA += lda ; 
            daxpy( a[2], &bs[ 6][0], c );  a[2] = READA ; incA += lda ; 
            daxpy( a[3], &bs[ 7][0], c );  a[3] = READA ; incA += lda ; 

            daxpy( a[0], &bs[ 8][0], c );  a[0] = READA ; incA += lda ; 
            daxpy( a[1], &bs[ 9][0], c );  a[1] = READA ; incA += lda ; 
            daxpy( a[2], &bs[10][0], c );  a[2] = READA ; incA += lda ; 
            daxpy( a[3], &bs[11][0], c );  a[3] = READA ; incA += lda ; 

            daxpy( a[0], &bs[12][0], c );
            daxpy( a[1], &bs[13][0], c );
            daxpy( a[2], &bs[14][0], c );
            daxpy( a[3], &bs[15][0], c );

#undef READA

            B += 16;
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
        } while( B < Blast );

        for( int i = 0; i < 16; i++ ) {
            C[0] = c[i];
            C += ldc;
        }
    }
}

/*
 * B21 = -inv(A22)*A21*inv(A11)
 */
__kernel void
TRIPLE_DGEMM_UPDATE_64_PART2_L (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
    const int bIdy = get_group_id(1)/npages;
    const int page = qmod(get_group_id(1), npages);
    const int inx = get_local_id(0);
    const int iny = get_local_id(1);
    const int ibx = get_group_id(0)*64;
    const int iby = bIdy*16;
    const int id = inx + iny*16;
    __local double bs[16][17];

    Ain = Ain + offAin;

    int PagesPerNB = NB/(blk*2);

    //--------------------------part two---------------------------//
    {
        // -inv(A22)*A21 -> A21
        // A=inv(A22), B=A21, C=A21
        __global const double *A;
        __global double *B, *C;
        int lda = NB;
        int ldb = NB;
        int ldc = NB;

        d_dinvA += NB*NB*(page/PagesPerNB)
                + (qmod(page, PagesPerNB))*(blk*2)*NB
                + (qmod(page, PagesPerNB))*(blk*2);

        A = d_dinvA + blk*NB + blk;
        B = C = d_dinvA + blk;

        A += ibx + id;
        B += inx + __mul( iby + iny, ldb );
        C += ibx + id  + __mul( iby, ldc );

        __global const double *Blast = B + blk;

        double c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        do {
            double a[4] = { A[0*lda], A[1*lda], A[2*lda], A[3*lda] };

            bs[inx][iny   ] = B[ 0*ldb];
            bs[inx][iny+ 4] = B[ 4*ldb];
            bs[inx][iny+ 8] = B[ 8*ldb];
            bs[inx][iny+12] = B[12*ldb];
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);

            A += 4*lda;
            daxpy( a[0], &bs[ 0][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 1][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[ 2][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[ 3][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[ 4][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 5][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[ 6][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[ 7][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[ 8][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 9][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[10][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[11][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[12][0], c );
            daxpy( a[1], &bs[13][0], c );
            daxpy( a[2], &bs[14][0], c );
            daxpy( a[3], &bs[15][0], c );

            B += 16;
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
        } while( B < Blast );

        for( int i = 0; i < 16; i++ ) {
            C[0] = (-1)*c[i];
            C += ldc;
        }
    }
}

/*
 * B21 = -inv(A11)*A12*inv(A22)
 */
__kernel void
TRIPLE_DGEMM_UPDATE_ABOVE64_PART1_R (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
    const int bIdy = get_group_id(1)/npages;
    const int page = qmod(get_group_id(1), npages);
    const int inx = get_local_id(0);
    const int iny = get_local_id(1);
    const int ibx = get_group_id(0)*64;
    const int iby = bIdy*16;
    const int id = inx + iny*16;
    __local double bs[16][17];

    Ain = Ain + offAin;

    int PagesPerNB = NB/(blk*2);
    //--------------------------part one---------------------------//
    {
        // A12*inv(A22) -> A12(d_dinvA)
        // A=A12, B=inv(A22), C=A12
        __global const double *A;
        __global double *B, *C;
        int ldb = NB;
        int ldc = NB;

        d_dinvA += NB*NB*(page/PagesPerNB)
                + (qmod(page, PagesPerNB))*(blk*2)*NB
                + (qmod(page, PagesPerNB))*(blk*2);

        int xa = page*blk*2 + ibx + id ; 
        int ya = page*blk*2 + blk ; 
        int incA = ya * lda + xa ; 

        // maxA will be used to detect overflow on all subsequent accesses on A(xa, ya:ya+???) 

        int maxA ;
        if ( xa < na ) 
          maxA = lda*na ;   // macro READA will detect overflow on y dimension
        else  
          maxA  = 0 ;  // there is already an overflow on xa 

#define READA ( (incA < maxA ) ? Ain[incA] : 0 )  

        B = d_dinvA + blk*NB + blk;
        C = d_dinvA + blk*NB;

        B += inx + __mul( iby + iny, ldb );
        C += ibx + id  + __mul( iby, ldc );

        __global const double *Blast = B + blk;

        double c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        do {
            double a[4] ;
            a[0] = READA ; incA += lda ; 
            a[1] = READA ; incA += lda ; 
            a[2] = READA ; incA += lda ; 
            a[3] = READA ; incA += lda ; 

            bs[inx][iny   ] = B[ 0*ldb];
            bs[inx][iny+ 4] = B[ 4*ldb];
            bs[inx][iny+ 8] = B[ 8*ldb];
            bs[inx][iny+12] = B[12*ldb];
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);

            daxpy( a[0], &bs[ 0][0], c );  a[0] = READA ; incA += lda ;
            daxpy( a[1], &bs[ 1][0], c );  a[1] = READA ; incA += lda ;
            daxpy( a[2], &bs[ 2][0], c );  a[2] = READA ; incA += lda ;
            daxpy( a[3], &bs[ 3][0], c );  a[3] = READA ; incA += lda ;

            daxpy( a[0], &bs[ 4][0], c );  a[0] = READA ; incA += lda ;
            daxpy( a[1], &bs[ 5][0], c );  a[1] = READA ; incA += lda ;
            daxpy( a[2], &bs[ 6][0], c );  a[2] = READA ; incA += lda ;
            daxpy( a[3], &bs[ 7][0], c );  a[3] = READA ; incA += lda ;

            daxpy( a[0], &bs[ 8][0], c );  a[0] = READA ; incA += lda ;
            daxpy( a[1], &bs[ 9][0], c );  a[1] = READA ; incA += lda ;
            daxpy( a[2], &bs[10][0], c );  a[2] = READA ; incA += lda ;
            daxpy( a[3], &bs[11][0], c );  a[3] = READA ; incA += lda ;

            daxpy( a[0], &bs[12][0], c );
            daxpy( a[1], &bs[13][0], c );
            daxpy( a[2], &bs[14][0], c );
            daxpy( a[3], &bs[15][0], c );

            B += 16;
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
        } while( B < Blast );

        for( int i = 0; i < 16; i++ ) {
            C[0] = c[i];
            C += ldc;
        }
    }
}
#undef READA

/*
 * B21 = -inv(A22)*A21*inv(A11)
 */
__kernel void
TRIPLE_DGEMM_UPDATE_ABOVE64_PART1_L (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
    const int bIdy = get_group_id(1)/npages;
    const int page = qmod(get_group_id(1), npages);
    const int inx = get_local_id(0);
    const int iny = get_local_id(1);
    const int ibx = get_group_id(0)*64;
    const int iby = bIdy*16;
    const int id = inx + iny*16;
    __local double bs[16][17];

    Ain = Ain + offAin;

    int PagesPerNB = NB/(blk*2);
    //--------------------------part one---------------------------//
    {
        // A21*inv(A11) -> A21
        // A=A21, B=inv(A11), C=A21
        __global const double *A;
        __global double *B, *C;
        int ldb = NB;
        int ldc = NB;

        d_dinvA += NB*NB*(page/PagesPerNB)
                + (qmod(page, PagesPerNB))*(blk*2)*NB
                + (qmod(page, PagesPerNB))*(blk*2);

        int xa = page*blk*2 + blk + ibx + id ; 
        int ya = page*blk*2 ; 
        int incA = ya * lda + xa ; 

        // maxA will be used to detect overflow on all subsequent accesses on A(xa, ya:ya+???) 

        int maxA ;
        if ( xa < na ) 
          maxA = lda*na ;  // macro READA will detect overflow on y dimension 
        else  
          maxA  = 0 ;  // there is already an overflow on xa 

#define READA ( (incA < maxA ) ? Ain[incA] : 0 )  

        B = d_dinvA;
        C = d_dinvA + blk;

        B += inx + __mul( iby + iny, ldb );
        C += ibx + id  + __mul( iby, ldc );

        __global const double *Blast = B + blk;

        double c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        do {
            double a[4]  ;
            a[0] = READA ; incA += lda ; 
            a[1] = READA ; incA += lda ; 
            a[2] = READA ; incA += lda ; 
            a[3] = READA ; incA += lda ; 

            bs[inx][iny   ] = B[ 0*ldb];
            bs[inx][iny+ 4] = B[ 4*ldb];
            bs[inx][iny+ 8] = B[ 8*ldb];
            bs[inx][iny+12] = B[12*ldb];
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);

            daxpy( a[0], &bs[ 0][0], c );  a[0] = READA ; incA += lda ;
            daxpy( a[1], &bs[ 1][0], c );  a[1] = READA ; incA += lda ;
            daxpy( a[2], &bs[ 2][0], c );  a[2] = READA ; incA += lda ;
            daxpy( a[3], &bs[ 3][0], c );  a[3] = READA ; incA += lda ;

            daxpy( a[0], &bs[ 4][0], c );  a[0] = READA ; incA += lda ;
            daxpy( a[1], &bs[ 5][0], c );  a[1] = READA ; incA += lda ;
            daxpy( a[2], &bs[ 6][0], c );  a[2] = READA ; incA += lda ;
            daxpy( a[3], &bs[ 7][0], c );  a[3] = READA ; incA += lda ;

            daxpy( a[0], &bs[ 8][0], c );  a[0] = READA ; incA += lda ;
            daxpy( a[1], &bs[ 9][0], c );  a[1] = READA ; incA += lda ;
            daxpy( a[2], &bs[10][0], c );  a[2] = READA ; incA += lda ;
            daxpy( a[3], &bs[11][0], c );  a[3] = READA ; incA += lda ;

            daxpy( a[0], &bs[12][0], c );
            daxpy( a[1], &bs[13][0], c );
            daxpy( a[2], &bs[14][0], c );
            daxpy( a[3], &bs[15][0], c );

            B += 16;
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
        } while( B < Blast );

#undef READA

        for( int i = 0; i < 16; i++ ) {
            C[0] = c[i];
            C += ldc;
        }
    }
}

/*
 * B21 = -inv(A11)*A12*inv(A22)
 */
__kernel void
TRIPLE_DGEMM_UPDATE_ABOVE64_PART2_R (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
    const int bIdy = get_group_id(1)/npages;
    const int page = qmod(get_group_id(1), npages);
    const int inx = get_local_id(0);
    const int iny = get_local_id(1);
    const int ibx = get_group_id(0)*64;
    const int iby = bIdy*16;
    const int id = inx + iny*16;
    __local double bs[16][17];

    Ain = Ain + offAin;

    int PagesPerNB = NB/(blk*2);

    //--------------------------part two---------------------------//
    {
        // -inv(A11)*A12 -> A12
        // A=inv(A11), B=A12, C=A12
        __global const double *A;
        __global double *B, *C;
        int lda = NB;
        int ldb = NB;
        int ldc = NB;

        d_dinvA += NB*NB*(page/PagesPerNB)
                + (qmod(page, PagesPerNB))*(blk*2)*NB
                + (qmod(page, PagesPerNB))*(blk*2);

        A = d_dinvA;
        B = d_dinvA + blk*NB;
        C = d_dinvA + blk;

        A += ibx + id;
        B += inx + __mul( iby + iny, ldb );
        C += ibx + id  + __mul( iby, ldc );

        __global const double *Blast = B + blk;

        double c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        do {
            double a[4] = { A[0*lda], A[1*lda], A[2*lda], A[3*lda] };

            bs[inx][iny   ] = B[ 0*ldb];
            bs[inx][iny+ 4] = B[ 4*ldb];
            bs[inx][iny+ 8] = B[ 8*ldb];
            bs[inx][iny+12] = B[12*ldb];
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);

            A += 4*lda;
            daxpy( a[0], &bs[ 0][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 1][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[ 2][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[ 3][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[ 4][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 5][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[ 6][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[ 7][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[ 8][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 9][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[10][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[11][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[12][0], c );
            daxpy( a[1], &bs[13][0], c );
            daxpy( a[2], &bs[14][0], c );
            daxpy( a[3], &bs[15][0], c );

            B += 16;
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
        } while( B < Blast );

        for( int i = 0; i < 16; i++ ) {
            C[0] = (-1)*c[i];
            C += ldc;
        }
    }
}

/*
 * part 3, copy data into position
 */
__kernel void
TRIPLE_DGEMM_UPDATE_ABOVE64_PART3_R (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
    const int bIdy = get_group_id(1)/npages;
    const int page = qmod(get_group_id(1), npages);
    const int inx = get_local_id(0);
    const int iny = get_local_id(1);
    const int ibx = get_group_id(0)*64;
    const int iby = bIdy*16;
    const int id = inx + iny*16;

    Ain = Ain + offAin;

    int PagesPerNB = NB/(blk*2);

    //--------------------------part two---------------------------//
    {
        // -inv(A11)*A12 -> A12
        // A=inv(A11), B=A12, C=A12
        __global double *C_temp, *C_real;
        int ldc = NB;

        C_temp = d_dinvA + NB*NB*(page/PagesPerNB)
               + (qmod(page, PagesPerNB))*(blk*2)*NB
               + (qmod(page, PagesPerNB))*(blk*2)
               + blk;

        C_real = d_dinvA + NB*NB*(page/PagesPerNB)
               + (qmod(page, PagesPerNB))*(blk*2)*NB
               + blk*NB
               + (qmod(page, PagesPerNB))*(blk*2);

        C_temp += ibx + id  + __mul( iby, ldc );
        C_real += ibx + id  + __mul( iby, ldc );

        for( int i = 0; i < 16; i++ ) {
            C_real[0] = C_temp[0];
            C_temp[0] = ZERO;
            C_temp += ldc;
            C_real += ldc;
        }
    }
}

/*
 * part 3: copy data back to position
 */
__kernel void
TRIPLE_DGEMM_UPDATE_ABOVE64_PART3_L (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
    const int bIdy = get_group_id(1)/npages;
    const int page = qmod(get_group_id(1), npages);
    const int inx = get_local_id(0);
    const int iny = get_local_id(1);
    const int ibx = get_group_id(0)*64;
    const int iby = bIdy*16;
    const int id = inx + iny*16;

    Ain = Ain + offAin;

    int PagesPerNB = NB/(blk*2);

    //--------------------------part three---------------------------//
    {
        // -inv(A22)*A21 -> A21
        // A=inv(A22), B=A21, C=A21
        __global double *C_temp, *C_real;
        int ldc = NB;

        d_dinvA += NB*NB*(page/PagesPerNB)
                + (qmod(page, PagesPerNB))*(blk*2)*NB
                + (qmod(page, PagesPerNB))*(blk*2);

        C_real = d_dinvA + blk;

        C_temp = d_dinvA + blk*NB;

        C_temp += ibx + id  + __mul( iby, ldc );
        C_real += ibx + id  + __mul( iby, ldc );

        for( int i = 0; i < 16; i++ ) {
            C_real[0] = C_temp[0];
            C_temp[0] = ZERO;
            C_real += ldc;
            C_temp += ldc;
        }
    }
    //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
}

/*
 * B21 = -inv(A22)*A21*inv(A11)
 */
__kernel void
TRIPLE_DGEMM_UPDATE_ABOVE64_PART2_L (__global const double *Ain, uint offAin, __global double *d_dinvA, int blk, int lda, int npages, int na)
{
    const int bIdy = get_group_id(1)/npages;
    const int page = qmod(get_group_id(1), npages);
    const int inx = get_local_id(0);
    const int iny = get_local_id(1);
    const int ibx = get_group_id(0)*64;
    const int iby = bIdy*16;
    const int id = inx + iny*16;
    __local double bs[16][17];

    Ain = Ain + offAin;

    int PagesPerNB = NB/(blk*2);

    //--------------------------part two---------------------------//
    {
        // -inv(A22)*A21 -> A21
        // A=inv(A22), B=A21, C=A21
        __global double *A, *B, *C;
        int lda = NB;
        int ldb = NB;
        int ldc = NB;

        d_dinvA += NB*NB*(page/PagesPerNB)
                + (qmod(page, PagesPerNB))*(blk*2)*NB
                + (qmod(page, PagesPerNB))*(blk*2);

        A = d_dinvA + blk*NB + blk;
        B = d_dinvA + blk;

        C = d_dinvA + blk*NB;

        A += ibx + id;
        B += inx + __mul( iby + iny, ldb );
        C += ibx + id  + __mul( iby, ldc );

        __global const double *Blast = B + blk;

        double c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        do {
            double a[4] = { A[0*lda], A[1*lda], A[2*lda], A[3*lda] };

            bs[inx][iny   ] = B[ 0*ldb];
            bs[inx][iny+ 4] = B[ 4*ldb];
            bs[inx][iny+ 8] = B[ 8*ldb];
            bs[inx][iny+12] = B[12*ldb];
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);

            A += 4*lda;
            daxpy( a[0], &bs[ 0][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 1][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[ 2][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[ 3][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[ 4][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 5][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[ 6][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[ 7][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[ 8][0], c );  a[0] = A[0*lda];
            daxpy( a[1], &bs[ 9][0], c );  a[1] = A[1*lda];
            daxpy( a[2], &bs[10][0], c );  a[2] = A[2*lda];
            daxpy( a[3], &bs[11][0], c );  a[3] = A[3*lda];

            A += 4*lda;
            daxpy( a[0], &bs[12][0], c );
            daxpy( a[1], &bs[13][0], c );
            daxpy( a[2], &bs[14][0], c );
            daxpy( a[3], &bs[15][0], c );

            B += 16;
            //__syncthreads();
	    barrier(CLK_LOCAL_MEM_FENCE);
        } while( B < Blast );

        for( int i = 0; i < 16; i++ ) {
            C[0] = (-1)*c[i];
            C += ldc;
        }
    }
}


";
