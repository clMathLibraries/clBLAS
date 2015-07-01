#ifndef HAWAII_DGEMMMCHANNELCONFLICT
#define HAWAII_DGEMMMCHANNELCONFLICT

#include "gcn_dgemm.h"


class clBlashawaiiDgemmChannelConflictFunctor  : public clblasDgemmFunctorGCN 
{

  private:  // Constructor & Destructor

  clBlashawaiiDgemmChannelConflictFunctor(Args & args, const Variant * variant, cl_int & err) ;
  
public:

  // Provide a suitable hawaii_dgemmChannelConflict for the specified args
  // or NULL if none 
  static clBlashawaiiDgemmChannelConflictFunctor * provide(clblasDgemmFunctor::Args & args) ;

};

#endif