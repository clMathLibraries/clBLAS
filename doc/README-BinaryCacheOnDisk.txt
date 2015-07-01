S. Chauveau
CAPS Entreprise
clBLAS Project
------------------------------
April 30,2014


The implementation of a binary cache for CL programs can be found in 
files src/include/binary_lookup.h and src/library/blas/generic/binary_lookup.cc

The cache is currently disabled by default. It can be enabled by
setting the environment variable 'CLBLAS_CACHE_PATH' to the directory
containing the cache entries.

In the code itself, accesses to the cache are controlled by the
BinaryLookup class. A typical cache query looks as follow:

   (1) Create a local instance of BinaryLookup 
   
   (2) Specify the additional characteristics (i.e. variants) of the
       requested program. That information combined with the program name
       and the OpenCL context and device shall form a unique signature
       for the binary program.
   
   (3) Perform the effective search by calling the 'found' method
   
   (4a) If the search was successful then cl_program can be retrieved 
       by a call to the 'getProgram' method
   
   (4b) If the search was not successful then a cl_program 
       must be created  and populated in the cache by a call 
       to the 'setProgram' method.
   
   (5) Destroy the BinaryLookup local instance.


So in practice a typical query shall looks as follow:

  cl_program program  ;

  // The program name is part of the signature and shall be unique 
  const char * program_name = "... my unique program name ... " ;

  BinaryLookup bl(context, device, program_name);

  // Specify some additional information used to build a 
  // unique signature for that cache entry
               
  bl.variantInt( vectorSize );
  bl.variantInt( hasBorder );
  ... 

  // Perform the query 
  if ( bl.found() ) 
  {
     // Success! use the cl_program retrieved from the cache
     program = bl.getProgram();
  }
  else 
  {
     // Failure! we need to build the program 
     program = build_my_program(context,device,vectorSize,...) ; 
     // and inform the lookup object of the program
     bl.setProgram(program);  
     // and finally populate the cache
     bl.populateCache() 
  }

  // The BinaryLookup shall now be destroyed 
