S. Chauveau
CAPS Entreprise
April 30, 2014

The Functor concept was introduced in clBLAS to simplify the creation 
of specialized versions for dedicated architectures.

The original system, referred as the 'Solver' system in this document, 
is very centralized and not flexible enough to insert customized kernels.

The Functor 
===========

A functor is simply a C++ object that provides an implementation of 
a function. In the current case, that function is one of the BLAS calls 
implemented in OpenCL. 

The base class of all functors is clblasFunctor 
  - see src/library/blas/functor/include/functor.h
  - see src/library/blas/functor/functor.cc
 
That class does not provide much by itself but it is supposed to be derived
once for each BLAS function to be implemented. 

For instance the clblasSgemmFunctor class will be the base class of all
functors providing a generic or specific implementation of SGEMM.

A generic functor is one that is applicable to all possible arguments of the
function it implements. In most cases, there will be at least one generic
functor that will simply call the existing Solver-based implementation of the
function. For SGEMM, that is the class clblasSgemmFunctorFallback.

A specific functor is one that is applicable to only a subset of the possible
arguments of the function it implements. For instance, a SGEMM functor could
only implement it for matrices of a given block size or only for square
matrices or only for a specific device architecture (e.g. AMD Hawai) etc

The Functor Selector 
====================

Multiple generic and specific functors may be available to implement each
clBLAS call. The selection of the proper functor is delegated to the class
clblasFunctorSelector whose default implementation typically returns the
fallback functors.

  - see src/library/blas/functor/include/functor_selector.h
  - see src/library/blas/functor/functor_selector.cc

So clblasFunctorSelector provides a large set of virtual selection methods.
Typically, a method to select a specific functor will be provided for each
supported BLAS function. Another method may be provided to select a generic 
functor but that is not mandatory.

The default implementation of clblasFunctorSelector is typically that the 
specific selector is redirected to the generic one returning the fallback 
functor (so using the existing Solver-based  implementation).  


The class clblasFunctorSelector is supposed to be derived once for each
supported architecture (e.g. Hawai, Tahiti, ...) and a single global instance
of each of those derived classes shall be created. This is important because
those instances register themselves in a global data structure that is later
used to find the proper clblasFunctorSelector according to the architecture
(see clblasFunctorSelector::find() )


Functor Management & Cache
==========================

Each functor contains a reference counter that, when it reaches zero, causes
the functor destruction. See the members clblasFunctor::retain() and
clblasFunctor::release().

Of course, to be efficient, functors must be reusable between BLAS calls so 
some mechanisms must be implemented to manage the functors. 

Some functors, such as the fallback functors, are independent of the 
arguments and of the opencl context & device. Those can typically be 
implemented using a single global instance that will never be destroyed.

Other functors, such as those that manage a cl_program internally, are 
dependent of the opencl context & device and sometimes of some arguments. 
They need to be stored in caches using some information as keys. 

In the current implementation, we propose that each functor class shall 
implement its own private cache. Such functors shall not be created directly 
using its constructor but via a dedicated 'provide' function (the name 'provide'
is not mandatory) that will take care of managing the internal cache.

The template class clblasFunctorCache<F> is provided as a simple
implementation of a cache of functors of type F. Use of that cache is not a
mandatory part of the functor design. Another strategies could be to keep a
single instance of the functor and implement a cache for the cl_program or to
implement a global cache shared by multiple functor classes.



  


