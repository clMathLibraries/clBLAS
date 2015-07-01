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

#ifndef _CLBLAS_FUNCTOR_XSCAL_GENERIC_H_
#define _CLBLAS_FUNCTOR_XSCAL_GENERIC_H_

#include <functor_xscal.h>


// A POD type used to index the functors below
struct _clblasXscalFunctorGenericData 
{
  int  vecLen  ;
  bool doVLOAD ;
  bool noUnity ;
  // operator< is needed for the cache 
  bool operator<(const _clblasXscalFunctorGenericData &b) const 
  {
    const  _clblasXscalFunctorGenericData &a = *this ;    
    if ( a.vecLen  != b.vecLen  ) return a.vecLen  < b.vecLen  ;
    if ( a.doVLOAD != b.doVLOAD ) return a.doVLOAD < b.doVLOAD ;
    if ( a.noUnity != b.noUnity ) return a.noUnity < b.noUnity ;
    return false ;
  }  
} ;

//
// Generic functor for SSCAL : implement the sscal using kprintf generator
//
class clblasSscalFunctorGeneric : public clblasSscalFunctor 
{ 
  public: 
    typedef _clblasXscalFunctorGenericData Data ;  
    Data data;
  public:  // Constructor & Destructor
    clblasSscalFunctorGeneric(cl_context ctxt, cl_device_id dev, const Data & data, cl_int & err);
    ~clblasSscalFunctorGeneric();
  public:  // Inherited members from clblasSscalFunctor 
    virtual clblasStatus execute(Args & a);
  public:
    static clblasSscalFunctorGeneric * provide (Args & a);
  public:
    typedef clblasFunctorCache<clblasSscalFunctorGeneric, Data> Cache;
    static Cache cache;
  public:  
    cl_program program;
};

//
// Generic functor for DSCAL : implement the dscal using the kprintf generator
//
class clblasDscalFunctorGeneric : public clblasDscalFunctor 
{
  public: 
    typedef _clblasXscalFunctorGenericData Data ;  
    Data data;
  public:  // Constructor & Destructor
    clblasDscalFunctorGeneric(cl_context ctxt, cl_device_id dev, const Data & data, cl_int & err);
    ~clblasDscalFunctorGeneric();
  public:  // Inherited members from clblasDscalFunctor 
    virtual clblasStatus execute(Args & a);
  public:
    static clblasDscalFunctorGeneric * provide (Args & a);
  public:
    typedef clblasFunctorCache<clblasDscalFunctorGeneric, Data> Cache;
    static Cache cache;
  public:  
    cl_program program;
};

//
// Generic functor for CSCAL : implement the Cscal using the kprintf generator
//
class clblasCscalFunctorGeneric : public clblasCscalFunctor 
{
  public: 
    typedef _clblasXscalFunctorGenericData Data ;  
    Data data;
  public:  // Constructor & Destructor
    clblasCscalFunctorGeneric(cl_context ctxt, cl_device_id dev, const Data & data, cl_int & err);
    ~clblasCscalFunctorGeneric();
  public:  // Inherited members from clblasCscalFunctor 
    virtual clblasStatus execute(Args & a);
  public:
    static clblasCscalFunctorGeneric * provide (Args & a);
  public:
    typedef clblasFunctorCache<clblasCscalFunctorGeneric, Data> Cache;
    static Cache cache;
  public:  
    cl_program program;
};

//
// Generic functor for ZSCAL : implement the zscal using the kprintf generator
//
class clblasZscalFunctorGeneric : public clblasZscalFunctor 
{
  public: 
    typedef _clblasXscalFunctorGenericData Data ;  
    Data data;
  public:  // Constructor & Destructor
    clblasZscalFunctorGeneric(cl_context ctxt, cl_device_id dev, const Data & data, cl_int & err);
    ~clblasZscalFunctorGeneric();
  public:  // Inherited members from clblasZscalFunctor 
    virtual clblasStatus execute(Args & a);
  public:
    static clblasZscalFunctorGeneric * provide (Args & a);
  public:
    typedef clblasFunctorCache<clblasZscalFunctorGeneric, Data> Cache;
    static Cache cache;
  public:  
    cl_program program;
};

//
// Generic functor for CSSCAL : implement the Csscal using the kprintf generator
//
class clblasCsscalFunctorGeneric : public clblasCsscalFunctor 
{
  public: 
    typedef _clblasXscalFunctorGenericData Data ;  
    Data data;
  public:  // Constructor & Destructor
    clblasCsscalFunctorGeneric(cl_context ctxt, cl_device_id dev, const Data & data, cl_int & err);
    ~clblasCsscalFunctorGeneric();
  public:  // Inherited members from clblasCsscalFunctor 
    virtual clblasStatus execute(Args & a);
  public:
    static clblasCsscalFunctorGeneric * provide (Args & a);
  public:
    typedef clblasFunctorCache<clblasCsscalFunctorGeneric, Data> Cache;
    static Cache cache;
  public:  
    cl_program program;
};

//
// Generic functor for ZDSCAL : implement the zdscal using the kprintf generator
//
class clblasZdscalFunctorGeneric : public clblasZdscalFunctor 
{
  public: 
    typedef _clblasXscalFunctorGenericData Data ;  
    Data data;
  public:  // Constructor & Destructor
    clblasZdscalFunctorGeneric(cl_context ctxt, cl_device_id dev, const Data & data, cl_int & err);
    ~clblasZdscalFunctorGeneric();
  public:  // Inherited members from clblasZdscalFunctor 
    virtual clblasStatus execute(Args & a);
  public:
    static clblasZdscalFunctorGeneric * provide (Args & a);
  public:
    typedef clblasFunctorCache<clblasZdscalFunctorGeneric, Data> Cache;
    static Cache cache;
  public:  
    cl_program program;
};


#endif // _CLBLAS_FUNCTOR_XSCAL_GENERIC_H_
