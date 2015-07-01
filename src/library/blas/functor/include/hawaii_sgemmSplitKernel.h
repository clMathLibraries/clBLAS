#ifndef HAWAII_SGEMMMSPLITKERNEL
#define HAWAII_SGEMMMSPLITKERNEL

#include "gcn_sgemm.h"


class clBlashawaiiSgemmSplitKernelFunctor  : public clblasSgemmFunctorGCN 
{
public:
  struct Variant 
  {    
    const char *    variantName;
    const char *    kernel_name[4] ;  //order is main, row, column, single
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

  clBlashawaiiSgemmSplitKernelFunctor(Args & args, const Variant * variant, cl_int & err) ;
  cl_int KernelsLaunch(cl_command_queue queue, cl_kernel Kernel[4], Args &args);
  const Variant * m_variantSplit ; // Pointer to a 'const static' object describing the kernel variant. 
  
public:

  // Provide a suitable hawaii_sgemmChannelConflict for the specified args
  // or NULL if none 
  static clBlashawaiiSgemmSplitKernelFunctor * provide(clblasSgemmFunctor::Args & args,  char* DevName) ;
  virtual clblasStatus execute(Args &args) ;

};

#endif