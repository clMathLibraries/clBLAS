#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
#include <stdio.h>
#include <string.h>
#include <clBLAS.h>

#include <devinfo.h>
#include "clblas-internal.h"
#include "solution_seq.h"

#include <functor.h>
#include <binary_lookup.h>
#include <iostream>

#include <functor_xgemm.h>
#include <tahiti.h>
#include <hawaii.h>

#include "BinaryBuild.h"
#include "hawaii_sgemmBig1024Kernel.h"

//only non-multiples of 32 is implemented right now, which is a small matrix.
#if BUILD_KERNEL_FROM_STRING
#include "sgemm_gcn_BigMatrices.clT"
#else 
#include "sgemm_gcn_BigMatrices.clHawaii_64.bin.clT"
#include "sgemm_gcn_BigMatrices.clBonaire_64.bin.clT"
#endif

// Just because the full name is too long
typedef clBlashawaiiSgemmBig1024KernelFunctor::Variant Variant;

//define the string name of the soure/binary code
#define SGEMM_SRC_NAME(TA,TB, DIVK, MULT)    sgemm_##TA##TB##_##DIVK##_SPLIT##MULT
#define SGEMM_SRC_NAME_HAWAII(TA,TB, DIVK, MULT, BITS)   sgemm_##TA##TB##_##DIVK##_SPLIT##MULT##_##BITS##_bin_Hawaii
#define SGEMM_SRC_NAME_BONAIRE(TA,TB, DIVK, MULT, BITS)   sgemm_##TA##TB##_##DIVK##_SPLIT##MULT##_##BITS##_bin_Bonaire
#define SGEMM_SRC_NAME_BIN(TA,TB, DIVK, MULT, BITS, DEVICE)   SGEMM_SRC_NAME##_##DEVICE(TA,TB, DIVK, MULT, BITS)


//variant name used to differentiate the different ones
#define SGEMM_VARIANT_NAME(TA,TB, DIVK, MULT) "sgemm_" #TA #TB "_" #DIVK "_SPLIT" #MULT
//SGEMM_VARIANT_NAME(TA, TB, DIVM , DIVN, DIVK, GREATER48M, GREATER48N, NBKERNEL),    

#define SGEMM_KERNEL_NAME(TA,TB,DIVM,DIVN,DIVK,BS0,BS1,NV0,NV1,MULT) "sgemm_"  #TA #TB "_" #DIVM "_" #DIVN "_" #DIVK "_" #BS0 "x" #BS1 "_" #NV0 "x" #NV1 #MULT


#define trans_N clblasNoTrans
#define trans_T clblasTrans

// Fill a variant descriptor using OpenCL source 
#define SGEMM_VARIANT_OBJ(TA,TB,DIVK,BS0,BS1,NV0,NV1, BITS, MULT,  \
  KERNEL_NAME_MAIN, \
  KERNELS_SRC,  \
  KERNEL_BUILD_OPTIONS,  \
  KERNELS_BIN,  \
  KERNEL_BIN_SIZE) { \
  SGEMM_VARIANT_NAME(TA,TB, DIVK, MULT),                                          \
{ KERNEL_NAME_MAIN } , \
  KERNELS_SRC,  \
  KERNEL_BUILD_OPTIONS, \
  KERNELS_BIN, \
  KERNEL_BIN_SIZE, \
  trans_##TA, trans_##TB,                                       \
  DIVK ,                                                        \
{ BS0, BS1 } ,                                                \
{ NV0, NV1 } ,                                                      \
#MULT                                                               \
} 

typedef clblasFunctorCache<clBlashawaiiSgemmBig1024KernelFunctor, const Variant *> CacheBig1024;
static CacheBig1024 cachebig1024;

// Make it 1 to enable additional debug 'print' 
#define VERB 0



//static bool applicable( const Variant & var, clblasSgemmFunctor::Args & args, int RefMultiple ) 
//{
//#if 0
//  // Transpose values are tested in select_variant
//  if ( args.transA != var.transA ) return false ;
//  if ( args.transB != var.transB ) return false ;
//#endif
//
//  //if (args.N>=var.divN && args.N % var.divN != 0 )
//  if ( args.N % var.divN != 0 ) 
//    return false ; 
//  if ( args.M % var.divM != 0 ) 
//    return false ; 
//  if(var.Greater[0]?args.M<RefMultiple:args.M>=RefMultiple)
//    return false;
//  if(var.Greater[1]?args.N<RefMultiple:args.N>=RefMultiple)
//    return false;
//  if ( args.beta==0 && var.mult.compare("__ALPHA")!=0)
//    return false ;
//  return true ;
//}

static void to_upper(char* input)
{
  while(*input)
  {
    *input=toupper(*input);
    input++;
  }
}


static const Variant * select_variant_Big1024Kernel(clblasSgemmFunctor::Args & args, const char* DevName, cl_uint _64BitsUse)
{
	if (_64BitsUse != 64)
	{
		std::cout << "we don't support clblas on 32 bits" << std::endl;
		assert(1);
		return NULL;
	}


	if (args.transA == clblasNoTrans)
	{
		if (args.transB == clblasNoTrans)
		{

			// ===== sgemm NN ======
			// sgemm NN does not have big 1024 perf drop problem


			return NULL;
		}
		if (args.transB == clblasTrans)
		{


			// ===== SGEMM NT ======
			//sgemm_NT_128_128_16_16x16_8x8__ALPHABETA
			const char* KName_NT = SGEMM_KERNEL_NAME(N, T, 128, 128, 16, 16, 16, 8, 8, __ALPHABETA);


			const char* KBin_NT64;
			size_t KBin_NTSize64 = 0;


#if BUILD_KERNEL_FROM_STRING
			//currently not supported
			return NULL;
#else
			if (!strcmp(DevName, "Hawaii"))
			{
				//KBin_NT64             = SGEMM_SRC_NAME_BIN(N, T, 16, __ALPHABETA,  64, HAWAII) ;
				KBin_NT64 = sgemm_NT_128_128_16_16x16_8x8__ALPHABETA_64_bin_Hawaii;
				KBin_NTSize64 = sizeof(sgemm_NT_128_128_16_16x16_8x8__ALPHABETA_64_bin_Hawaii);

			}

#endif

			// ===== SGEMM NT ======
			static const Variant variant = SGEMM_VARIANT_OBJ(N, T, 16, 16, 16, 8, 8, 64, __ALPHABETA,
				KName_NT,
				NULL,
				NULL,
				KBin_NT64,
				KBin_NTSize64);

			return &variant;
		}
	}
	else
	{
		if (args.transB == clblasNoTrans)
		{

				// ===== sgemm TN ======
				//sgemm TN does not have big 1024 perf drop problem
			    return NULL;
		}
		return NULL;
	}

		return NULL;
}


clBlashawaiiSgemmBig1024KernelFunctor::clBlashawaiiSgemmBig1024KernelFunctor(Args & args, const Variant * variant, cl_int & err)
{

  cl_device_id device;
  cl_context context;
  m_program=NULL;
  m_variantBig1024 = variant;


  cl_command_queue queue = args.queue;
  err = getDeviceAndContext(queue, device, context);
  if( err != CL_SUCCESS )
  {
    return;
  }

  if (VERB) printf(" ===> GET KERNEL %s\n", this->m_variantBig1024->variantName);

  //Ben do I use the correct "kernel_name"?
  BinaryLookup bl(context, device, "clBlashawaiiSgemmBig1024KernelFunctor");

  bl.variantRaw(this->m_variantBig1024->variantName, strlen(this->m_variantBig1024->variantName) + 1);

  if ( !bl.found() ) // may create empty file or may wait until file is ready  
  {
	if (this->m_variantBig1024->bin != NULL)
    {
      // build from a pre-compiled version of the kernel (SPIR or cl binaries)
      //only 1 binary containing all the kernel
	  err = bl.buildFromBinary(this->m_variantBig1024->bin, this->m_variantBig1024->bin_size, "-cl-std=2.0");
    }
    else
    {
      //// directly build from a char* 
      if (VERB) printf(" ===> BUILD PROBLEM WE DON'T SUPPORT SOURCE BUILD FOR big 1024 SGEMM\n") ;
      return;
    } 

    if ( err != CL_SUCCESS )
    {  
      if (VERB) printf(" ===> BUILD PROBLEM\n") ;

      return;
    }
  }

  this->m_program = bl.getProgram();
}



clBlashawaiiSgemmBig1024KernelFunctor *
clBlashawaiiSgemmBig1024KernelFunctor::provide(clblasSgemmFunctor::Args & args, char* DevName)
{

  if ( args.order == clblasRowMajor ) 
    return NULL ;   // The RowMajor case shall never occur. 

  cl_device_id dev;
  cl_context   ctxt;

  cl_int err = getDeviceAndContext(args.queue, dev, ctxt);
  if (err != CL_SUCCESS)
  {
    return NULL;
  }
  cl_uint bitness = getAddressBits(dev);

  int major;
  int minor;

  getCLVersion(dev, major, minor);

  //if (major<2)
  //  return NULL;

  // to_upper( DevName);
  const Variant * variant = select_variant_Big1024Kernel(args, DevName, bitness);
  if ( variant == NULL )  
    return NULL ; 



  CacheBig1024::Lookup lookup(cachebig1024, ctxt, dev, variant) ;


  if ( lookup.ok() )
  {
	clBlashawaiiSgemmBig1024KernelFunctor * functor = lookup.get();
    functor->retain(); // increment the reference counter to avoid deletion while it is still beeing used
    return functor;
  }

  clBlashawaiiSgemmBig1024KernelFunctor * functor = new clBlashawaiiSgemmBig1024KernelFunctor(args, variant, err);
  if (err != CL_SUCCESS)
  {
    return NULL;
  }

  lookup.set(functor) ;

  return functor;

}


cl_int clBlashawaiiSgemmBig1024KernelFunctor::KernelsLaunch(cl_command_queue queue, cl_kernel Kernel[1], Args &args)
{
	if (args.lda < 7168)
	{
		//((Mvalue - 1) / 128 + 1) * 16
		size_t GlobalX = ((args.M - 1) / 128 + 1) * 16;
		size_t GlobalY = ((args.N - 1) / 128 + 1) * 16;


		std::size_t gs[2] = { GlobalX, GlobalY };
		cl_int error = 0;


		//if (VERB) printf(" ===> EXECUTE KERNEL 0 \n") ;
		error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantBig1024->ls, args.numEventsInWaitList, args.eventWaitList, args.events);
		return error;
	}
	else
	{
		//for example, when M=N=K=8192
		//we are gonna call 16 GEMMs 
		//each GEMM has M=N=K=4096
		//note are direct GEMM call has a 0.7 TFLOPS performance

		//     [ A11 | A12 | A13 | A14 ]      [ B11 | B12 | B13 | B14 ]      [ C11 | C12 ]
		// A = [ A21 | A22 | A23 | A24 ]  B = [ B21 | B22 | B23 | B24 ]  C = [ C21 | C22 ] 

		// 16 GEMMs are
		// #01: C11 = a*A11*B11 + b*C11
		// #02: C11 = a*A12*B12 + 1*C11
		// #03: C11 = a*A13*B13 + 1*C11
		// #04: C11 = a*A14*B14 + 1*C11 now we are done with C11

		// #05: C12 = a*A11*B21 + b*C12
		// #06: C12 = a*A12*B22 + 1*C12
		// #07: C12 = a*A12*B22 + 1*C12
		// #08: C12 = a*A12*B22 + 1*C12 now we are done with C12

		// #09: C21 = a*A21*B11 + b*C21
		// #10: C21 = a*A22*B12 + 1*C21
		// #11: C21 = a*A23*B13 + 1*C21
		// #12: C21 = a*A24*B14 + 1*C21 now we are done with C21

		// #13: C22 = a*A21*B21 + b*C22
		// #14: C22 = a*A22*B22 + 1*C22
		// #15: C22 = a*A23*B23 + 1*C22
		// #16: C22 = a*A24*B24 + 1*C22 now we are done with C22

		unsigned int small_M = args.M / 2;
		unsigned int small_N = args.N / 2;
		unsigned int small_K = args.K / 4;

		size_t GlobalX = ((small_M - 1) / 128 + 1) * 16;
		size_t GlobalY = ((small_N - 1) / 128 + 1) * 16;
		std::size_t gs[2] = { GlobalX, GlobalY };
		cl_int error = 0;

		//GEMM #1
		error = clSetKernelArg(Kernel[0], 3, sizeof(cl_uint), &small_M);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 4, sizeof(cl_uint), &small_N);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 5, sizeof(cl_uint), &small_K);
		assert(error == CL_SUCCESS);

		error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL,
			gs, m_variantBig1024->ls, args.numEventsInWaitList, args.eventWaitList, NULL);
		assert(error == CL_SUCCESS);

		// GEMM #2: C11 = a*A12*B12 + 1*C11

		unsigned int offa_A2 = args.lda*args.K / 4;
		unsigned int offb_B2 = args.ldb*args.K / 4;
		cl_float betaone = 1;

		error = clSetKernelArg(Kernel[0], 7, sizeof(cl_float), &betaone);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 11, sizeof(cl_uint), &offa_A2);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 12, sizeof(cl_uint), &offb_B2);
		assert(error == CL_SUCCESS);

		error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL,
			gs, m_variantBig1024->ls, 0, NULL, NULL);
		assert(error == CL_SUCCESS);

		// GEMM #3: C11 = a*A13*B13 + 1*C11

		unsigned int offa_A3 = args.lda*args.K / 4 * 2;
		unsigned int offb_B3 = args.ldb*args.K / 4 * 2;

		error = clSetKernelArg(Kernel[0], 11, sizeof(cl_uint), &offa_A3);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 12, sizeof(cl_uint), &offb_B3);
		assert(error == CL_SUCCESS);

		error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL,
			gs, m_variantBig1024->ls, 0, NULL, NULL);
		assert(error == CL_SUCCESS);

		// GEMM #4: C11 = a*A14*B14 + 1*C11 now we are done with C11

		unsigned int offa_A4 = args.lda*args.K / 4 * 3;
		unsigned int offb_B4 = args.ldb*args.K / 4 * 3;

		error = clSetKernelArg(Kernel[0], 11, sizeof(cl_uint), &offa_A4);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 12, sizeof(cl_uint), &offb_B4);
		assert(error == CL_SUCCESS);

		error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL,
			gs, m_variantBig1024->ls, 0, NULL, NULL);
		assert(error == CL_SUCCESS);

		// GEMM #5: C12 = a*A11*B21 + b*C12
		unsigned int offa_A5 = 0;
		unsigned int offb_B5 = args.N / 2;
		unsigned int offc_C5 = args.ldc*args.N / 2;

		error = clSetKernelArg(Kernel[0], 7, sizeof(cl_float), &(args.beta));
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 11, sizeof(cl_uint), &offa_A5);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 12, sizeof(cl_uint), &offb_B5);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 13, sizeof(cl_uint), &offc_C5);
		assert(error == CL_SUCCESS);

		error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL,
			gs, m_variantBig1024->ls, 0, NULL, NULL);
		assert(error == CL_SUCCESS);

		// GEMM #6: C12 = a*A12*B22 + 1*C12
		unsigned int offa_A6 = args.lda*args.K / 4;
		unsigned int offb_B6 = args.ldb*args.K / 4 + args.N / 2;

		error = clSetKernelArg(Kernel[0], 7, sizeof(cl_float), &betaone);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 11, sizeof(cl_uint), &offa_A6);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 12, sizeof(cl_uint), &offb_B6);
		assert(error == CL_SUCCESS);

		error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL,
			gs, m_variantBig1024->ls, 0, NULL, NULL);
		assert(error == CL_SUCCESS);

		// GEMM #7: C12 = a*A13*B23 + 1*C12
		unsigned int offa_A7 = args.lda*args.K / 4 * 2;
		unsigned int offb_B7 = args.ldb*args.K / 4 * 2 + args.N / 2;

		error = clSetKernelArg(Kernel[0], 11, sizeof(cl_uint), &offa_A7);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 12, sizeof(cl_uint), &offb_B7);
		assert(error == CL_SUCCESS);

		error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL,
			gs, m_variantBig1024->ls, 0, NULL, NULL);
		assert(error == CL_SUCCESS);

		// GEMM #8: C12 = a*A14*B24 + 1*C12 now we are done with C12
		unsigned int offa_A8 = args.lda*args.K / 4 * 3;
		unsigned int offb_B8 = args.ldb*args.K / 4 * 3 + args.N / 2;

		error = clSetKernelArg(Kernel[0], 11, sizeof(cl_uint), &offa_A8);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 12, sizeof(cl_uint), &offb_B8);
		assert(error == CL_SUCCESS);

		error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL,
			gs, m_variantBig1024->ls, 0, NULL, NULL);
		assert(error == CL_SUCCESS);

		// GEMM #9: C21 = a*A21*B11 + b*C21
		unsigned int offa_A9 = args.M / 2;
		unsigned int offb_B9 = 0;
		unsigned int offc_C9 = args.M / 2;

		error = clSetKernelArg(Kernel[0], 7, sizeof(cl_float), &(args.beta));
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 11, sizeof(cl_uint), &offa_A9);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 12, sizeof(cl_uint), &offb_B9);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 13, sizeof(cl_uint), &offc_C9);
		assert(error == CL_SUCCESS);

		error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL,
			gs, m_variantBig1024->ls, 0, NULL, NULL);
		assert(error == CL_SUCCESS);

		// GEMM #10: C21 = a*A22*B12 + 1*C21 

		unsigned int offa_A10 = args.lda*args.K / 4 + args.M / 2;
		unsigned int offb_B10 = args.ldb*args.K / 4;

		error = clSetKernelArg(Kernel[0], 7, sizeof(cl_float), &betaone);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 11, sizeof(cl_uint), &offa_A10);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 12, sizeof(cl_uint), &offb_B10);
		assert(error == CL_SUCCESS);

		error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL,
			gs, m_variantBig1024->ls, 0, NULL, NULL);
		assert(error == CL_SUCCESS);

		// GEMM #11: C21 = a*A23*B13 + 1*C21 

		unsigned int offa_A11 = args.lda*args.K / 4 * 2 + args.M / 2;
		unsigned int offb_B11 = args.ldb*args.K / 4 * 2;

		error = clSetKernelArg(Kernel[0], 11, sizeof(cl_uint), &offa_A11);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 12, sizeof(cl_uint), &offb_B11);
		assert(error == CL_SUCCESS);

		error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL,
			gs, m_variantBig1024->ls, 0, NULL, NULL);
		assert(error == CL_SUCCESS);

		// GEMM #12: C21 = a*A24*B14 + 1*C21 now we are done with C21

		unsigned int offa_A12 = args.lda*args.K / 4 * 3 + args.M / 2;
		unsigned int offb_B12 = args.ldb*args.K / 4 * 3;

		error = clSetKernelArg(Kernel[0], 11, sizeof(cl_uint), &offa_A12);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 12, sizeof(cl_uint), &offb_B12);
		assert(error == CL_SUCCESS);

		error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL,
			gs, m_variantBig1024->ls, 0, NULL, NULL);
		assert(error == CL_SUCCESS);

		// GEMM #13: C22 = a*A21*B21 + b*C22
		unsigned int offa_A13 = args.M / 2;
		unsigned int offb_B13 = args.N / 2;
		unsigned int offc_C13 = args.ldc*args.N / 2 + args.M / 2;

		error = clSetKernelArg(Kernel[0], 7, sizeof(cl_float), &(args.beta));
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 11, sizeof(cl_uint), &offa_A13);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 12, sizeof(cl_uint), &offb_B13);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 13, sizeof(cl_uint), &offc_C13);
		assert(error == CL_SUCCESS);

		error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL,
			gs, m_variantBig1024->ls, 0, NULL, NULL);
		assert(error == CL_SUCCESS);

		// #14: C22 = a*A22*B22 + 1*C22 
		unsigned int offa_A14 = args.lda*args.K / 4 + args.M / 2;
		unsigned int offb_B14 = args.ldb*args.K / 4 + args.N / 2;

		error = clSetKernelArg(Kernel[0], 7, sizeof(cl_float), &betaone);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 11, sizeof(cl_uint), &offa_A14);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 12, sizeof(cl_uint), &offb_B14);
		assert(error == CL_SUCCESS);

		error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL,
			gs, m_variantBig1024->ls, 0, NULL, NULL);
		assert(error == CL_SUCCESS);

		// #15: C22 = a*A23*B23 + 1*C22 
		unsigned int offa_A15 = args.lda*args.K / 4 * 2 + args.M / 2;
		unsigned int offb_B15 = args.ldb*args.K / 4 * 2 + args.N / 2;

		error = clSetKernelArg(Kernel[0], 11, sizeof(cl_uint), &offa_A15);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 12, sizeof(cl_uint), &offb_B15);
		assert(error == CL_SUCCESS);

		error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL,
			gs, m_variantBig1024->ls, 0, NULL, NULL);
		assert(error == CL_SUCCESS);

		// #16: C22 = a*A24*B24 + 1*C22 
		unsigned int offa_A16 = args.lda*args.K / 4 * 3 + args.M / 2;
		unsigned int offb_B16 = args.ldb*args.K / 4 * 3 + args.N / 2;

		error = clSetKernelArg(Kernel[0], 11, sizeof(cl_uint), &offa_A16);
		assert(error == CL_SUCCESS);
		error = clSetKernelArg(Kernel[0], 12, sizeof(cl_uint), &offb_B16);
		assert(error == CL_SUCCESS);

		error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL,
			gs, m_variantBig1024->ls, 0, NULL, args.events);
		assert(error == CL_SUCCESS);

		return error;
	}


  return clblasNotImplemented;
}



clblasStatus clBlashawaiiSgemmBig1024KernelFunctor::execute(Args &args)
{
  cl_int err;
  cl_command_queue queue = args.queue;

  if (VERB) printf(" ===> EXECUTE KERNEL %s, alpha =%f ,beta = %f\n", this->m_variantBig1024->kernel_name, args.alpha, args.beta);

  cl_kernel kernel[1]; 
  int NBKernel = 0;


  if (this->m_variantBig1024->kernel_name[0])
  {
	kernel[0] = clCreateKernel(this->m_program, this->m_variantBig1024->kernel_name[0], &err);
    if (err != CL_SUCCESS)
        return clblasStatus(err) ; 
    NBKernel++;
  }


  if (NBKernel != 1) return clblasStatus(clblasBuildProgramFailure) ; 

  if (VERB)
  {
    for (int i=0; i<NBKernel; i++)
		printf(" ===> FOUND %s\n", this->m_variantBig1024->kernel_name[i]);
  }

  int M   = args.M, N = args.N, K = args.K;
  int lda = args.lda, ldb = args.ldb, ldc = args.ldc;

  int offsetA = args.offA;
  int offsetB = args.offB;
  int offsetC = args.offC;

  int arg[4]={0, 0, 0, 0} ; 

  //// All sgemm kernels shall have the same arguments: (A,B,C,M,N,K,alpha,beta,lda,ldb,ldc,offa,offb,offc) 

  for (int i=0; i<NBKernel; i++)
  {
    setKernelArg<cl_mem>(kernel[i], arg[i]++, args.A);
    setKernelArg<cl_mem>(kernel[i], arg[i]++, args.B);
    setKernelArg<cl_mem>(kernel[i], arg[i]++, args.C);

    setKernelArg<int>(kernel[i], arg[i]++, M);
    setKernelArg<int>(kernel[i], arg[i]++, N);
    setKernelArg<int>(kernel[i], arg[i]++, K);

    setKernelArg<cl_float>(kernel[i], arg[i]++, args.alpha);
    setKernelArg<cl_float>(kernel[i], arg[i]++, args.beta);

    setKernelArg<int>(kernel[i], arg[i]++, lda);
    setKernelArg<int>(kernel[i], arg[i]++, ldb);
    setKernelArg<int>(kernel[i], arg[i]++, ldc);

    setKernelArg<int>(kernel[i], arg[i]++, offsetA);
    setKernelArg<int>(kernel[i], arg[i]++, offsetB);
    setKernelArg<int>(kernel[i], arg[i]++, offsetC);
  }

  err = KernelsLaunch(queue, kernel, args);



  for (int i = 0; i<NBKernel; i++)
    clReleaseKernel(kernel[i]) ;

  if (VERB) printf(" ===> ERR=%d \n",(int)err) ;

  // err= clFinish(queue);
  return clblasStatus(err) ;

}
#endif
