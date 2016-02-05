/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_DIAG_DTRTRI_UPPER_128_16_SRC_CPP
#define KERNEL_DIAG_DTRTRI_UPPER_128_16_SRC_CPP
#pragma message("#define KERNEL_DIAG_DTRTRI_UPPER_128_16_SRC_CPP.")

#ifndef STRINGIFY
#define STRINGIFY2(...) #__VA_ARGS__
#define STRINGIFY(...) STRINGIFY2(__VA_ARGS__)
#endif

unsigned char *diag_dtrtri_upper_128_16_bin = 0;
size_t diag_dtrtri_upper_128_16_binSize = 0;

const char * const diag_dtrtri_upper_128_16_src = STRINGIFY(
#define BLOCK_SIZE 16 
#define NB 128 
#define ZERO			  ( 0.0) 
#define ONE			   ( 1.0) 
#ifdef DOUBLE_PRECISION 
#ifdef cl_khr_fp64 
#pragma OPENCL EXTENSION cl_khr_fp64 : enable 
#else 
#pragma OPENCL EXTENSION cl_amd_fp64 : enable 
#endif 
#endif 
__kernel void diag_dtrtri_upper_128_16_src(
int  isDiagUnit,
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
  __local double workspace[BLOCK_SIZE];	// workspace used to store the current working column

  // load A
  _Pragma("unroll")
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

	_Pragma("unroll")
	//for( j=tx; j < i; j++ )
	for( j=0; j < i; j++ )
	{
	  Ystx += switcher * (*(Bs+j*BLOCK_SIZE+tx)*workspace[j]);
	}

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
  _Pragma("unroll")
  for( i=0; i < BLOCK_SIZE; i++ )
  {
	*(d_dinvA+i*NB+tx) = Bs[i*BLOCK_SIZE+tx];
  }
  
}
// end of kernel
);
#endif
