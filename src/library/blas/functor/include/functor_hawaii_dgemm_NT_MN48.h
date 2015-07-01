/* ************************************************************************
 * Copyright 2014 Advanced Micro Devices, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ************************************************************************/

#include <functor.h>
#include <binary_lookup.h>
#include <iostream>

#define BUILD_KERNEL_FROM_STRING 0

#if BUILD_KERNEL_FROM_STRING
#include <dgemm_NT_MN48.clT>
#else
#include <dgemm_NT_MN48.spir.clT>
#endif



class clblasDgemmFunctorHawaii_NT_MN48 : public clblasDgemmFunctor 
{
private:  // Constructor & Destructor

  clblasDgemmFunctorHawaii_NT_MN48(Args & args, cl_int & err);
  ~clblasDgemmFunctorHawaii_NT_MN48();
  
public: // Members inherited from clblasDgemmFunctor 
  virtual clblasStatus execute(Args & a);

public: 
  static clblasDgemmFunctorHawaii_NT_MN48 * provide(Args & args);

private:

  typedef clblasFunctorCache<clblasDgemmFunctorHawaii_NT_MN48,bool> Cache ;
  static  Cache cache;

private:  
  cl_program program ;  
};



clblasDgemmFunctorHawaii_NT_MN48::Cache clblasDgemmFunctorHawaii_NT_MN48::cache;

clblasDgemmFunctorHawaii_NT_MN48 * 
clblasDgemmFunctorHawaii_NT_MN48::provide(clblasDgemmFunctor::Args & args)
{
  //Work only if TRANSA == N, TRANSB == T, M and N multiple of 48
  //Note: Are K%48 == 0  LDA LDB %2 == 0 and OFFA OFFB %2 == 0 required?
  bool applicable =  (args.transA == clblasNoTrans) 
                  && (args.transB == clblasTrans) 
                  && (args.M % 48 == 0) 
                  && (args.N % 48 == 0)
                  && (args.K % 48 == 0) 
                  && (args.order == clblasColumnMajor) ;
  if(!applicable)
  {
    return NULL;
  }

  cl_device_id dev;
  cl_context   ctxt;

  cl_int err = getDeviceAndContext(args.queue, dev, ctxt);

  if (err != CL_SUCCESS)
  {
      return NULL;
  }

  Cache::Lookup lookup(cache, ctxt, dev, true ) ;

  if ( lookup.ok() ){
    clblasDgemmFunctorHawaii_NT_MN48 * functor = lookup.get();
    functor->retain(); // increment the reference counter to avoid deletion while it is still beeing used
    return functor;
  }
 
  clblasDgemmFunctorHawaii_NT_MN48 * functor = new clblasDgemmFunctorHawaii_NT_MN48(args, err);
  if (err != CL_SUCCESS)
  {
      return NULL;
  }

  lookup.set(functor) ;

  return functor;
}

clblasDgemmFunctorHawaii_NT_MN48::clblasDgemmFunctorHawaii_NT_MN48(Args & args, cl_int & err) :
  program(0) 
{
  //Hawaii kernel here only for test.
  //Work only if TRANSA == N, TRANSB == T, M and N multiple of 48
  //Note: Are K%48 == 0  LDA LDB %2 == 0 and OFFA OFFB %2 == 0 required?

  cl_device_id device;
  cl_context context;

  cl_command_queue queue = args.queue;
  err = getDeviceAndContext(queue, device, context);
  if( err != CL_SUCCESS )
  {
      return;
  }

  BinaryLookup bl(context, device, "clblasDgemmFunctorHawaii_NT_MN48");

  bl.variantInt(48);

  if ( !bl.found() ) // may create empty file or may wait until file is ready  
  {
#if BUILD_KERNEL_FROM_STRING
    // directly build from a char* 
    err = bl.buildFromSource(DGEMM_NT_MN48_KERNEL);
#else
    // build from compiled version of the kernel (SPIR)
    err = bl.buildFromBinary(DGEMM_NT_MN48_SPIR_KERNEL, sizeof(DGEMM_NT_MN48_SPIR_KERNEL));
#endif
    if( err != CL_SUCCESS )
    {
      return;
    }
  }

  this->program = bl.getProgram();
}

clblasDgemmFunctorHawaii_NT_MN48::~clblasDgemmFunctorHawaii_NT_MN48()
{
  if (this->program) {
    clReleaseProgram( this->program ) ; 
  } 
}

clblasStatus clblasDgemmFunctorHawaii_NT_MN48::execute(Args & args)
{
  cl_int err;
  cl_command_queue queue = args.queue;

  cl_kernel kernel = clCreateKernel( this->program, "dgemm",  &err);
  if (err != CL_SUCCESS) return clblasStatus(err) ; 

  int M = args.M, N = args.N, K = args.K;
  int lda = args.lda, ldb = args.ldb, ldc = args.ldc;

  int offsetA = args.offA;
  int offsetB = args.offB;
  int offsetC = args.offC;

  setKernelArg<cl_mem>(kernel, 0, args.C);
  setKernelArg<cl_mem>(kernel, 1, args.B);
  setKernelArg<cl_mem>(kernel, 2, args.A);

  setKernelArg<int>(kernel, 3, N);
  setKernelArg<int>(kernel, 4, M);
  setKernelArg<int>(kernel, 5, K);

  setKernelArg<cl_double>(kernel, 6, args.alpha);
  setKernelArg<cl_double>(kernel, 7, args.beta);

  setKernelArg<int>(kernel,  8, ldc);
  setKernelArg<int>(kernel,  9, ldb);
  setKernelArg<int>(kernel, 10, lda);

  setKernelArg<int>(kernel, 11, offsetC);
  setKernelArg<int>(kernel, 12, offsetB);
  setKernelArg<int>(kernel, 13, offsetA);

  const size_t ls[2]  = {8, 8};
  const size_t bwi[2] = {6, 6};

  size_t globalThreads[2];

  unsigned int thx, thy;

  thx   = M/bwi[0] + ((M%bwi[0] != 0) ? 1 : 0);   // Each PE updates (bwi[0] x bwi[1])=(6 x 6) values
  thx   = thx/ls[0] + ((thx%ls[0] != 0) ? 1 : 0); // Each work group is made of (ls[0] x ls[1])=(8 x 8) PE
  thx   = ls[0] * thx;

  thy   = N/bwi[1] + ((N%bwi[1] != 0) ? 1 : 0);   // Each PE updates (bwi[0] x bwi[1])=(6 x 6) values
  thy   = thy/ls[1] + ((thy%ls[1] != 0) ? 1 : 0); // Each work group is made of (ls[0] x ls[1])=(8 x 8) PE
  thy   = ls[1] * thy;

  globalThreads[0] = thx;
  globalThreads[1] = thy;

  err = clEnqueueNDRangeKernel(queue, kernel, 2, NULL,
                               globalThreads, NULL , 
                               args.numEventsInWaitList, 
                               args.eventWaitList, 
                               args.events);

  clReleaseKernel(kernel) ;


  return clblasStatus(err) ;
}
