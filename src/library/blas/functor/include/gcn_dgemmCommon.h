#ifndef DGEMMMGCNCOMMON
#define DGEMMMGCNCOMMON

#include "gcn_dgemm.h"


class clBlasGCNdgemmCommonFunctor  : public clblasDgemmFunctorGCN 
{

  private:  // Constructor & Destructor

  clBlasGCNdgemmCommonFunctor(Args & args, const Variant * variant, cl_int & err) ;
  
public:

  // Provide a suitable hawaii_dgemmChannelConflict for the specified args
  // or NULL if none 
  static clBlasGCNdgemmCommonFunctor * provide(clblasDgemmFunctor::Args & args, const char* DevName) ;

};

#endif