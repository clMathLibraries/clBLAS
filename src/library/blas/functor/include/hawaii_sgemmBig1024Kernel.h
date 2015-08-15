/*
Handles lda=ldb=4096, 5120, 7168, 8192
lda=ldb=6144 should be handled by a special case in hawaii_sgemmSplitKernel
*/
#ifndef HAWAII_SGEMMBIG1024KERNEL
#define HAWAII_SGEMMBIG1024KERNEL

#include "gcn_sgemm.h"


class clBlashawaiiSgemmBig1024KernelFunctor  : public clblasSgemmFunctorGCN 
{
public:
  struct Variant 
  {    
    const char *    variantName;
    const char *    kernel_name[1] ;  //just one kernel here
    const char *    source ;   // the kernel source (shall be unique)
    const char *    build_options;
    const char *    bin ; 
    size_t          bin_size ; 
    clblasTranspose transA ;   //
    clblasTranspose transB ;   //
    unsigned        divK ;     // Required divisor of N  (use 1 when N can be of any value) 
    size_t          ls[2]  ;   // Local size (the work-group size)
    size_t          bwi[2] ;   // Block size work-item:  Number of elements calculated by each work items 
                               // So basically each kernel is computing a block of
                               //   (ls[0]*bwi[0]) x (ls[1]*bwi[1])  
                               // elements of C. 
    std::string mult;
    
  } ;


  private:  // Constructor & Destructor

  clBlashawaiiSgemmBig1024KernelFunctor(Args & args, const Variant * variant, cl_int & err);
  cl_int KernelsLaunch(cl_command_queue queue, cl_kernel Kernel[1], Args &args);
  const Variant * m_variantBig1024 ; // Pointer to a 'const static' object describing the kernel variant. 
  
public:

  static clBlashawaiiSgemmBig1024KernelFunctor * provide(clblasSgemmFunctor::Args & args, char* DevName);
  virtual clblasStatus execute(Args &args) ;

};

#endif