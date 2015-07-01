#ifndef _CLBLAS_DTRSM192_FUNCTOR_GPU_H_
#define _CLBLAS_DTRSM192_FUNCTOR_GPU_H_

class clblasDtrsm192FunctorGpu : public clblasDtrsmFunctor 
{
public:
  
    
private:  // Constructor & Destructor

  clblasDtrsm192FunctorGpu(Args & args, cl_int & err, const char* DevName,  cl_uint _64BitsUse) ;
  
public:

  // Provide a suitable clblasDtrsmFunctorTahiti for the specified args
  // or NULL if none 
  static clblasDtrsm192FunctorGpu * provide(clblasDtrsmFunctor::Args & args, const char* DevName) ;

public: // inherited member from clblasDtrsmFunctor

  virtual clblasStatus execute(Args &args) ;

private:

  cl_program      m_program ;  
} ; 

#endif
