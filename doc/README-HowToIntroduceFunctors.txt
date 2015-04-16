S. Chauveau
CAPS Entreprise
clBLAS Project
------------------------------
April 30,2014

This document describes the steps needed to introduce the Functor framework
for a clBLAS function currently implemented using the previous Solver mechanism.

The procedure is composed of the following steps:

  (1) Declaration of a new base functor classes for the
      considered clBLAS function. 

  (2) Create a new fallback class derived from the class created
      in (1) and using the existing Solver implementation. 

  (3) Add the appropriate members to the clblasFunctorSolver 
      class

  (4) Modify the clBLAS function to use the functor. 

In the following, we will consider the case of the XSCAL functions. 

Initial State
=============

The XSCAL functions are originally implemented in the file src/library/blas/xscal.c

Most of the Solver-based implementation occurs within the static function
doScal() that is shared by all SCAL functions. clblasSscal(), clblasDscal()
... are basically a single call to doScal()

  clblasStatus doScal(...) 
  { 
    ...  // Do all the magic  
  } 

  clblasStatus
  clblasSscal( size_t N,
               float alpha,
               cl_mem X,
               size_t offx,
               int incx,
               cl_uint numCommandQueues,
               cl_command_queue *commandQueues,
               cl_uint numEventsInWaitList,
               const cl_event *eventWaitList,
               cl_event *events
               )
  {
      CLBlasKargs kargs;

      #ifdef DEBUG_SCAL
      printf("\nSSCAL Called\n");
      #endif

      memset(&kargs, 0, sizeof(kargs));
      kargs.dtype = TYPE_FLOAT;
      kargs.alpha.argFloat = alpha;

      return doScal(&kargs, N, X, offx, incx, numCommandQueues, commandQueues, numEventsInWaitList, eventWaitList, events);
   }

   clblasStatus clblasDscal(...) 
   ... 
   clblasStatus clblasCscal(...) 
   ... 
   clblasStatus clblasZscal(...) 
   ... 
   ...
   
Step 1:  Declaration of new base functor classes 
================================================

All the SCAL variants have identical arguments so it is reasonable to 
use a templates to avoid rewriting similar classes again and again. 
Using macros would also work. That is just a matter of personal taste.

For convenience, the base template class will provide an internal
structure type called Args that will be used to store the argument.
Using an Args type is not strictly needed but it simplifies a lot the
creation of the functor classes and of their future derived classes.
 
So create a new file src/library/blas/functor/include/functor_xscal.h 
containing the base functor class. In that specific case we also have 
to consider the case of clblasZdscal() and clblasCsscal(), which explains
why the template requires two types TX and Talpha. TX is the type of 
the vector elements while Talpha is the type of the alpha argument.
 
      
      
      template<typename TX, typename Talpha> 
      class clblasXscalFunctor : public clblasFunctor 
      {
      public:
      
        // Structure used to store all XSCAL arguments
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
        
          Args(size_t N,
               Talpha alpha,
               cl_mem X,
               size_t offx,
               int    incx,
               cl_command_queue queue,
               cl_uint          numEventsInWaitList,
               const cl_event * eventWaitList,
               cl_event *       events) 
            : N(N),
              alpha(alpha),
              X(X),
              offx(offx),
              incx(incx),
              queue(queue),
              numEventsInWaitList(numEventsInWaitList),
              eventWaitList(eventWaitList),
              events(events)
          {
          }
        };
      
        virtual clblasStatus execute(Args & args) = 0;
      };
      
      
Using this template class it is now possible to define the base functor
class corresponding to each SCAL function:
      
      
      class clblasSscalFunctor: public clblasXscalFunctor<cl_float, cl_float> 
      {
      };
      //
      // Base class for all functors providing a DSCAL implementation
      //
      class clblasDscalFunctor: public clblasXscalFunctor<cl_double, cl_double>
      {
      };
      
      //
      // Base class for all functors providing a CSCAL implementation
      //
      class clblasCscalFunctor: public clblasXscalFunctor<cl_float2, cl_float2>
      {
      };
      
      //
      // Base class for all functors providing a ZSCAL implementation
      //
      class clblasZscalFunctor: public clblasXscalFunctor<cl_double2, cl_double2>
      {
      };
      
      //
      // Base class for all functors providing a CSSCAL implementation
      //
      class clblasCsscalFunctor: public clblasXscalFunctor<cl_float2, cl_float>
      {
      };
      
      //
      // Base class for all functors providing a ZDSCAL implementation
      //
      class clblasZdscalFunctor: public clblasXscalFunctor<cl_double2, cl_double>
      {
      };
      

A shorter alternative could be to use 'typedef' instead but using class
offers the opportunity to extend the functor with specific features (i.e. 
it is possible to add new members to a class but not to a typedef).



STEP 2: Create the new fallback classes
=======================================   

In the following, we only consider the case of clblasSscal. 

For each of the functor classes declared during STEP 1, we should now 
declare the fallback functor class that will provide the Solver-based 
implementation of the function. 

We add the following src/library/blas/functor/include/functor_xscal.h

   //
   // Fallback functor for SSCAL : implement the sscal using the old solver mechanism
   //
   class clblasSscalFunctorFallback : public clblasSscalFunctor 
   {
     public:   // Inherited members from clblasFunctor 
      virtual void retain();  
      virtual void release();
     public:  // Inherited members from clblasSscalFunctor 
      virtual clblasStatus execute(Args & a);
     public:
      static clblasSscalFunctorFallback * provide ();
    };


The file src/library/blas/xscal.c is then renamed into src/library/blas/functor/functor_xscal.cc
and modified as follow:

First, the clblasSscal() function is transformed into clblasSscalFunctorFallback::execute() 

    clblasStatus clblasSscalFunctorFallback::execute(Args & args)
    {
    
      CLBlasKargs kargs;
    
      memset(&kargs, 0, sizeof(kargs));
      kargs.dtype = TYPE_DOUBLE;
      kargs.alpha.argDouble = args.alpha;
    
      return doScal(&kargs, 
                    args.N, 
                    args.X, 
                    args.offx, 
                    args.incx, 
                    1,
                    &args.queue, 
                    args.numEventsInWaitList, 
                    args.eventWaitList, 
                    args.events);
    
    }
    

Second, a single instance of clblasSscalFunctorFallback is created as a static variable 
that will be returned by the clblasSscalFunctorFallback::provide() member. 


    static clblasSscalFunctorFallback dscal_fallback; 
 
    clblasSscalFunctorFallback * clblasSscalFunctorFallback::provide ()
    {
      static clblasSscalFunctorFallback dscal_fallback;
      return & dscal_fallback;
    }


Third, the retain() and release() members must be reimplemented to prevent the
destruction of the unique clblasSscalFunctorFallback instance.

   
     void clblasSscalFunctorFallback::retain()
     {
       // clblasSscalFunctorFallback has a single global instance 
       // and shall never be freed 
     }


     void clblasSscalFunctorFallback::release()
     {
       // clblasSscalFunctorFallback has a single global instance 
       // and shall never be freed
     }


STEP 3: Add the appropriate members to the clblasFunctorSolver class
=======================================================================   

The clblasFunctorSolver shall typically be extended with two new virtual 
methods: one to select a specific functor and one to select a generic functor. 

Edit the file  src/library/blas/functor/include/functor_selector.h and add
the following members declarations to the class clblasFunctorSelector:

      // Provide a XSCAL Functor usable in all cases 

    virtual clblasSscalFunctor  * select_sscal_generic();
    virtual clblasDscalFunctor  * select_dscal_generic();
    virtual clblasCscalFunctor  * select_cscal_generic();
    virtual clblasZscalFunctor  * select_zscal_generic();
    virtual clblasCsscalFunctor * select_csscal_generic();
    virtual clblasZdscalFunctor * select_zdscal_generic();

    // Provide XSCAL functors optimized for specific arguments

    virtual clblasSscalFunctor  * select_sscal_specific(clblasSscalFunctor::Args & args);
    virtual clblasDscalFunctor  * select_dscal_specific(clblasDscalFunctor::Args & args);
    virtual clblasCscalFunctor  * select_cscal_specific(clblasCscalFunctor::Args & args);
    virtual clblasZscalFunctor  * select_zscal_specific(clblasZscalFunctor::Args & args);
    virtual clblasCsscalFunctor * select_csscal_specific(clblasCsscalFunctor::Args & args);
    virtual clblasZdscalFunctor * select_zdscal_specific(clblasZdscalFunctor::Args & args);

The naming scheme used here is not mandatory but is recommended to keep the
whole infrastructure consistent.

Then, add their default implementation in src/library/blas/functor/functor_selector.cc.


    clblasSscalFunctor * 
    clblasFunctorSelector::select_sscal_generic()  
    { 
        return clblasSscalFunctorFallback::provide();
    }  

    clblasSscalFunctor * 
    clblasFunctorSelector::select_sscal_specific(clblasSscalFunctor::Args &)
    { 
        return this->select_sscal_generic() ;
    }

    ...


STEP 4: Modify the clBLAS function to use the functor
=====================================================

Create a file src/library/blas/xscal.cc to reimplement the clBLAS API functions. 

First, copy the original functions skeletons from the now obsolete file src/library/blas/xscal.c

Then fill the skeleton to perform the following actions:
  (A) Perform some consistency checks on the arguments      
  (B) Create and initialize a local Args object  
  (C) Obtain the clblasFunctorSelector corresponding 
      to the current device (via the queue)
  (D) Ask that selector for a specific functor
  (E) Execute the functor
  (F) Release the functor 
 
The code shall typically look like that 
      
      extern "C" 
      clblasStatus
      clblasSscal(
          size_t N,
          float alpha,
          cl_mem X,
          size_t offx,
          int incx,
          cl_uint numCommandQueues,
          cl_command_queue *commandQueues,
          cl_uint numEventsInWaitList,
          const cl_event *eventWaitList,
          cl_event *events)
      {
      
        CHECK_VECTOR_X( X , N,  offx, incx ) ;
        CHECK_QUEUES( numCommandQueues, commandQueues ) ;
        CHECK_WAITLIST( numEventsInWaitList, eventWaitList ) ;

        if ( numCommandQueues>1 ) {
          numCommandQueues = 1 ;  // No support for multi-device (yet)
        }
      
        cl_command_queue queue = commandQueues[0]; 
      
        clblasSscalFunctor::Args args(N,
                                      alpha,H
                                      X,
                                      offx,
                                      incx,
                                      queue,
                                      numEventsInWaitList,
                                      eventWaitList,
                                      events);
        
         clblasFunctorSelector  * fselector = clblasFunctorSelector::find(queue);
         
         functor = fselector->select_sscal_specific(args);
      
         clblasStatus res = functor->execute(args);
      
         functor->release();
      
         return res;
      }
      
      
Reminder: this is a C++ file so the API functions shall be declared extern "C" 
      
Remark: what is missing in that exemple is a proper verification of the arguments
        (e.g. numCommandQueues shall be strictly positive. commandQueues[0] shall
         be non-NULL, ...) 



Conclusion
==========

After following all the steps above, the clBLAS APIs shall now use the Solver
based implementation via their respective fallback functor.

Other specialized functors can then be implemented and integrated in the  
appropriate methods of the functor selector. 



