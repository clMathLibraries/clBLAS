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
  //((Mvalue - 1) / 128 + 1) * 16
  size_t GlobalX = ((args.M-1) / 128 + 1)*16 ;
  
  //

  size_t GlobalY = ((args.N - 1) / 128 + 1) * 16;


  std::size_t gs[2] = {GlobalX, GlobalY};
  cl_int error = 0;


  //if (VERB) printf(" ===> EXECUTE KERNEL 0 \n") ;
  error = clEnqueueNDRangeKernel(queue, Kernel[0], 2, NULL, gs, m_variantBig1024->ls, args.numEventsInWaitList, args.eventWaitList,args.events);
  return error;


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
