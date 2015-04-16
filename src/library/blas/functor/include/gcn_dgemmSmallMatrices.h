#ifndef GCN_DGEMMMSMALLMATRICES
#define GCN_DGEMMMSMALLMATRICES

#include "gcn_dgemm.h"


class clBlasGCNDgemmSmallMatricesFunctor  : public clblasDgemmFunctorGCN 
{
public:



  private:  // Constructor & Destructor

  clBlasGCNDgemmSmallMatricesFunctor(Args & args, const Variant * variant, cl_int & err) ;
  //cl_int KernelsLaunch(cl_command_queue queue, cl_kernel Kernel[4], Args &args);
  
public:

  // Provide a suitable hawaii_dgemmChannelConflict for the specified args
  // or NULL if none 
  static clBlasGCNDgemmSmallMatricesFunctor * provide(clblasDgemmFunctor::Args & args, const char* DevName) ;
  virtual clblasStatus execute(Args &args) ;

};

#endif