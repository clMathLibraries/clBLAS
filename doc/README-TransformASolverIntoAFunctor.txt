S. Chauveau
CAPS Entreprise
clBLAS Project
------------------------------
April 30,2014

This document describes a possible procedure to transform an existing 
solver-based implementation for a given BLAS function into a functor-based
implementation. 

We assume here that the basic functor infrastructure is already implemented 
for that function. 

More precisely, we will consider the case of the family of the XSCAL functions
for which this exercise was already performed. The resulting code can currently 
be found in the files

  - src/library/blas/functor/include/functor_xscal_generic.h
  - src/library/blas/functor/functor_xscal_generic.cc

So XSCAL consists of 6 functions all performing the scaling (i.e. multiplication) 
of a vector X by a scalar alpha.  SSCAL, DSCAL, CSCAL and ZSCAL are respectively 
for the float, double, complex float and complex double cases while CSSCAL and ZDSCAL 
are special cases when the vector X is complex and the scalar alpha is not. 

The file 'functor_xscal.h' defines a generic functor type for each of
those functions:

  - clblasSscalFunctor
  - clblasDscalFunctor
  - clblasCscalFunctor
  - clblasZscalFunctor
  - clblasCSscalFunctor
  - clblasZDscalFunctor

Each of those base functor types defines a similar internal type Args that is used 
to store the corresponding SCAL arguments (that is Talpha in the code sample below) . 
 
  
  struct Args
  {
    size_t           N;
    Talpha           alpha;
    cl_mem           X;
    size_t           offx;
    int              incx;
    cl_command_queue queue;
    cl_uint          numEventsInWaitList;
    const cl_event * eventWaitList;
    cl_event *       events;
    ...
  } 



The OpenCL code used in the generic functor can be found in the file 
  - src/library/blas/gens/clTemplates/scal.cl

This file is not really an OpenCL program but a template that needs to
be processed using the existing 'kprint' API. We assume that the reader
is already familiar with that API.

Apart from the data type (float, double, ...) that template can also be 
parametrized using two coefficients:
  - a vector size 
  - whether the X is properly aligned for the chosen vector size.

Those coefficient (combined with the OpenCL context and device) will
form what could be called the signature of the functors. Since all
generic functors will use the same kind of signature, the file 
'functor_xscal_generic.h' starts by defining a reusable POD (Plain 
Old Data) type for it:

  struct _clblasXscalFunctorGenericData 
  {
    int  vecLen  ;  // Vectorization size
    bool doVLOAD ;  // if aligned vector load/store can be used 
  
    //
    // The operator < is needed for the cache 
    //
    bool operator<(const _clblasXscalFunctorGenericData &b) const 
    {
      const  _clblasXscalFunctorGenericData &a = *this ;    
      if ( a.vecLen  != b.vecLen  ) return a.vecLen  < b.vecLen  ;
      if ( a.doVLOAD != b.doVLOAD ) return a.doVLOAD < b.doVLOAD ;
      return false ;
    }  
  } ;
  
This type will later be used as key in the functor caches so it is 
given the 'operator<' implementation needed to use it as key in
the class clblasFunctorCache.  

Next, the file 'functor_xscal_generic.h' provides the declaration of the
functors. For SSCAL that is that the class clblasSscalFunctorGeneric
defined as follow:  

 
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

You should recognize here the execute() method that has to be
implemented by all implementation of clblasSscalFunctor and the
provide() method that will be used in place of the constructor to
insure that the functor is properly cached.

A static cache is also provided using _clblasXscalFunctorGenericData (or its local 
version Data) as custom key. 

Ideally the constructor shall be private to prevent using it directly
but for technical reasons (i.e. the use of templates to factorize the
implementation of 'provide') it had to be made public.

Each functor also carries a Data member and a cl_program member that will be 
used by execute function.

The other functors are implemented in a very similar way. In fact, the
6 functor classes defined in this file are almost identical except for
minor details. Their implementation in 'functor_xscal_generic.cpp'
will make extensive use of templates to avoid rewriting too much
code. Another approach that requires some minor but not negligible
architectural changes is possible and described in Appendix A below.


The 'execute' method is implemented is implemented in functor_xscal_generic.cc 
using the static templated function 'xscalExecute':


    clblasStatus clblasSscalFunctorGeneric::execute(Args & args)
    {
      size_t nThreads = args.N; //to customize accord   ing to the device, data and args
      return xscalExecute<cl_float>(args.queue, 
                                    this->program, 
                                    "Sscal_kernel",
                                    args.alpha, 
                                    args.X, 
                                    args.N, 
                                    args.offx, 
                                    args.incx,
                                    nThreads);
    }
    
The last argument of xscalExecute represents the number of threads. In
that version it is simply set to args.N which is functionally correct
but clearly not optimal.  A more complex formula depending of the
architecture and of the Data is clearly needed here.


The template type cl_float is the type of the alpha which is strictly
speaking not mandatory in this case (because it can be inferred from
the argument).  Apart from the arguments, the command queue and the
OpenCL program, the template mechanism also changes the kernel name
which is passed here as third argument. 

The implementation of xscalExecute() is a typical OpenCL kernel call:

    template <typename TA>
    static clblasStatus xscalExecute(cl_command_queue queue, 
                                     cl_program program, 
                                     const char * kernelName, 
                                     TA alpha, 
                                     cl_mem X, 
                                     uint N, 
                                     uint offx, 
                                     int incx,
                                     size_t nThreads)
    {
      cl_int err;
      cl_kernel kernel = clCreateKernel( program, kernelName,  &err);
      if (err != CL_SUCCESS) return clblasStatus(err) ; 
    
      clblasFunctor::setKernelArg<TA>     (kernel, 0, alpha);
      clblasFunctor::setKernelArg<cl_mem> (kernel, 1, X);
      clblasFunctor::setKernelArg<uint>   (kernel, 2, N);
      clblasFunctor::setKernelArg<uint>   (kernel, 3, offx);
      clblasFunctor::setKernelArg<int>    (kernel, 4, incx);
      
      size_t globalThreads[1] = { nThreads };
    
      cl_event event;
      err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL,
                                   globalThreads, NULL , 
                                   0, NULL, &event);
    
      clReleaseKernel(kernel) ;
      return clblasStatus(err) ;
    }
    
The functor constructor is implemented in a similar way using the templated
static function xcalCreateProgram: 

     
     template <class FUNCTOR>
     static cl_program xcalCreateProgram(cl_context ctxt, 
                                         cl_device_id dev,
                                         char type,
                                         const char* functorName,
                                         const typename FUNCTOR::Data & data,
                                         cl_int & err)
     {
       BinaryLookup bl(ctxt, dev, functorName);
     
       bl.variantInt(data.vecLen);
       bl.variantInt(data.doVLOAD);
     
       if ( bl.found() ) // may create empty file or may wait until file is ready  
       {
         return bl.getProgram();
       }
       else
       {
         char tempTemplate[32*1024];
         char buf         [32*1024];
         cl_program scalProgram;
     
         strcpy( tempTemplate, (char*)scal_kernel );
         kprintf kobj( type, data.vecLen, data.doVLOAD, data.doVLOAD);
         kobj.spit((char*)buf, tempTemplate);
     
         scalProgram = BinaryLookup::buildProgramFromSource(buf, ctxt, dev, err /*, options*/);
         
         if(scalProgram)
         {
           bl.setProgram(scalProgram);
           bl.populateCache();
         }
         
         return scalProgram;
       }
     
     }

     clblasSscalFunctorGeneric::clblasSscalFunctorGeneric(cl_context ctxt, 
                                                          cl_device_id dev,
                                                          const Data & data,
                                                          cl_int & err) : program(0)
     {
       this->program = xcalCreateProgram<clblasSscalFunctorGeneric>(
              ctxt, dev,  'S', "clblasSscalFunctorGeneric", data, err
             );
     }

We recognize here a typical use of the BinaryLookup class used to manage the 
binary cache on disk when enabled. The query effectively occurs during the 
call to 'bl.found()'. Before that, the members of the Data structure which is 
also used as key in this cache are added to the lookup object. It is very 
important not to forget any member else binary cache entries could be reused 
for incompatible functors. The functorName argument is also used to index 
the cache entries. It shall be unique so the functor class name is used here.

After the call to bl.found(), then 2 cases are to be
considered. First, if a compatible entry was found in the binary cache
then a proper cl_program can be obtain bl.getProgram(). Else, the
program shall be manually built in that case using the kprintf and the
BinaryLookup::buildProgramFromSource utility functions. The resulting
program shall then be stored in the binary cache for further reuses.


Last but not least, the 'provide' member is also implemented using a 
templated call: 

  
     
     template <class FUNCTOR>
     static FUNCTOR * xscalProvide(typename FUNCTOR::Args & args)
     {
       cl_device_id dev;
       cl_context   ctxt;
       cl_int err = clblasFunctor::getDeviceAndContext(args.queue, dev, ctxt);
     
       if (err != CL_SUCCESS)
       {
           return NULL;
       }
     
       uint vecLen  = 1 ;      // To customize according to the device and args
       uint doVLOAD = false ;  // TO DO (see scal_reg.cpp)
     
       typename FUNCTOR::Data data = { vecLen , doVLOAD };
     
       typename FUNCTOR::Cache::Lookup lookup(FUNCTOR::cache, ctxt, dev, data ) ;
     
       if ( lookup.ok() ){
         FUNCTOR * functor = lookup.get();
         functor->retain(); 
         return functor;
       }
      
       FUNCTOR * functor = new FUNCTOR(ctxt, dev, data, err);
       if (err != CL_SUCCESS)
       {
           return NULL;
       }
     
       lookup.set(functor) ;
     
       return functor;
     }
     
     clblasSscalFunctorGeneric * 
     clblasSscalFunctorGeneric::provide (clblasSscalFunctor::Args & args)
     {
       return xscalProvide<clblasSscalFunctorGeneric>(args);
     }


This implementation of xscalProvide is pretty basic. After extracting
the device and context from the queue (which would probably be better
done earlier), the coefficients of the Data structure are chosen. In 
this early implementation, a vector size of 1 is used which is safe 
but not optimal. What is still missing is a set of utility function to 
help analyze the properties of the vector argument X in order to figure 
out the best choice for the vectorization. This code probably exists 
somewhere in the current Solver implementation but still needs to be 
provided for the functor.

On the Data structure is populated a lookup in the private 
cache of this functor can be performed. As with the binary cache, 
we have to differentiate the cases where a cache entry already 
exists or not. In the later case, the functor must be manually created. 





Appendix A - Alternative approach to improve code reuse
=======================================================


The implementation described above suffers from a significant problem
due to a variant of the so called diamond problem of C++ (and most
Object-Oriented programming languages). Simply speaking, the technical
choice made to create one base class for each functor of the SCAL family 
implies that it becomes very difficult to share code between the  
classes derived from those base classes.

                          clblasFunctor 
                      /          |           \  
                     /           |            \
     clblasSscalFunctor   clblasDscalFunctor  ...
           |                     |
           |                     | 
 clblasSscalFunctorGeneric  clblaDscalFunctorGeneric   ... 


The problem is partially solved by introducing some templated functions 
but this is not a very elegant solution. 

An alternative could be to define only base class for all functors of
the SCAL family and then to define only one 'generic' functor call
(and one fallback class).

The immediate advantage is that the number of functor classes to be
written would be greatly reduced (typically 4 times for most BLAS
functions). The disadvantage is that the implementation of those
classes would be slightly more complex since they would have to manage
all their variants at once. It is not too late to switch to that new
design as long as not too many functors are written. This is a minor 
change to the overall functor design. 






