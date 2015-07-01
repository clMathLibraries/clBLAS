#ifndef GCN_SGEMMMSMALLMATRICES
#define GCN_SGEMMMSMALLMATRICES

#include "gcn_sgemm.h"


class clBlasGCNSgemmSmallMatricesFunctor  : public clblasSgemmFunctorGCN 
{
public:



  private:  // Constructor & Destructor

  clBlasGCNSgemmSmallMatricesFunctor(Args & args, const Variant * variant, cl_int & err) ;
  //cl_int KernelsLaunch(cl_command_queue queue, cl_kernel Kernel[4], Args &args);
  
public:

  // Provide a suitable hawaii_dgemmChannelConflict for the specified args
  // or NULL if none 
  static clBlasGCNSgemmSmallMatricesFunctor * provide(clblasSgemmFunctor::Args & args, const char* DevName) ;
  virtual clblasStatus execute(Args &args) ;

};

#endif