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
#include <gcn_dgemm.h>

#include "BinaryBuild.h"


#define VERB 0


clblasStatus clblasDgemmFunctorGCN::execute(Args &args) 
{
  cl_int err;
  cl_command_queue queue = args.queue;

  if (VERB) printf(" ===> EXECUTE KERNEL %s\n", this->m_variant->kernel_name) ;

  cl_kernel kernel = clCreateKernel( this->m_program, this->m_variant->kernel_name,  &err);
  if (err != CL_SUCCESS) return clblasStatus(err) ; 

  if (VERB) printf(" ===> FOUND %s\n", this->m_variant->kernel_name) ;

  int M   = args.M, N = args.N, K = args.K;
  int lda = args.lda, ldb = args.ldb, ldc = args.ldc;

  int offsetA = args.offA;
  int offsetB = args.offB;
  int offsetC = args.offC;

  int arg=0 ; 

  // All dgemm kernels shall have the same arguments: (A,B,C,M,N,K,alpha,beta,lda,ldb,ldc,offa,offb,offc) 

  setKernelArg<cl_mem>(kernel, arg++, args.A);
  setKernelArg<cl_mem>(kernel, arg++, args.B);
  setKernelArg<cl_mem>(kernel, arg++, args.C);

  setKernelArg<int>(kernel, arg++, M);
  setKernelArg<int>(kernel, arg++, N);
  setKernelArg<int>(kernel, arg++, K);

  setKernelArg<cl_double>(kernel, arg++, args.alpha);
  if (args.beta!=0 && this->m_variant->mult.compare("__ALPHA")!=0)
    setKernelArg<cl_double>(kernel, arg++, args.beta);

  setKernelArg<int>(kernel, arg++, lda);
  setKernelArg<int>(kernel, arg++, ldb);
  setKernelArg<int>(kernel, arg++, ldc);

  setKernelArg<int>(kernel, arg++, offsetA);
  setKernelArg<int>(kernel, arg++, offsetB);
  setKernelArg<int>(kernel, arg++, offsetC);

  const size_t * ls  = this->m_variant->ls  ; // Each work group is made of ls[0] x ls[1]  PE
  const size_t * bwi = this->m_variant->bwi ; // Each PE updates bwi[0] x bwi[1] values

  size_t globalThreads[2];

  unsigned int thx, thy;

  thx   = M/bwi[0] + ((M%bwi[0] != 0) ? 1 : 0);   
  thx   = thx/ls[0] + ((thx%ls[0] != 0) ? 1 : 0); 
  thx   = ls[0] * thx;

  thy   = N/bwi[1] + ((N%bwi[1] != 0) ? 1 : 0);  
  thy   = thy/ls[1] + ((thy%ls[1] != 0) ? 1 : 0); 
  thy   = ls[1] * thy;

  globalThreads[0] = thx;
  globalThreads[1] = thy;

  err = clEnqueueNDRangeKernel(queue, kernel, 2, NULL,
    globalThreads, NULL , 
    args.numEventsInWaitList, 
    args.eventWaitList, 
    args.events);

  clReleaseKernel(kernel) ;

  if (VERB) printf(" ===> ERR=%d \n",(int)err) ;

  return clblasStatus(err) ;
}


//clblasDgemmFunctorGCN * 
//  clblasDgemmFunctorGCN::provide(clblasDgemmFunctor::Args & args, const char* DevName) 
//{
//
//  if ( args.order == clblasRowMajor ) 
//    return NULL ;   // The RowMajor case shall never occur. 
//
//  cl_device_id dev;
//  cl_context   ctxt;
//
//  cl_int err = getDeviceAndContext(args.queue, dev, ctxt);
//  if (err != CL_SUCCESS)
//  {
//    return NULL;
//  }
//  cl_uint bitness = getAddressBits(dev);
//
//  const Variant * variant = select_variant( args, DevName, bitness ) ;
//  if ( variant == NULL )  
//    return NULL ; 
//
//
//
//
//  Cache::Lookup lookup(cache, ctxt, dev, variant) ;
//
//  if ( lookup.ok() ){
//    clblasDgemmFunctorGCN * functor = lookup.get();
//    functor->retain(); // increment the reference counter to avoid deletion while it is still beeing used
//    return functor;
//  }
//
//  clblasDgemmFunctorGCN * functor = new clblasDgemmFunctorGCN(args, variant, err);
//  if (err != CL_SUCCESS)
//  {
//    return NULL;
//  }
//
//  lookup.set(functor) ;
//
//  return functor;
//
//}



