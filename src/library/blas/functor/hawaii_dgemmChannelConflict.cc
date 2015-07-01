#ifndef CLBLAS_HAWAII_DYNAMIC_KERNEL
#include <stdio.h>
#include <string.h>
#include <clBLAS.h>

#include <devinfo.h>
#include "clblas-internal.h"
#include "solution_seq.h"

#include <functor.h>
#include <binary_lookup.h>
#include <iostream>

#include <functor_xgemm.h>
#include <tahiti.h>
#include <hawaii.h>

#include "BinaryBuild.h"
#include "hawaii_dgemmChannelConflict.h"


#if BUILD_KERNEL_FROM_STRING
#include "dgemm_hawaiiChannelConfilct.clT"
#else 

#include "dgemm_hawaiiChannelConfilct.clHawaii_64.bin.clT"
#endif

// Just because the full name is too long
typedef clblasDgemmFunctorGCN::Variant Variant ; 

//typedef clblasFunctorCache<clBlashawaiiDgemmChannelConflictFunctor,const Variant *> Cache ;
//static Cache cache  ;

// Make it 1 to enable additional debug 'print' 
#define VERB 0

static const Variant * select_variant_hawaiiChannelConflict( clblasDgemmFunctor::Args & args, cl_uint _64BitsUse )
{
  //return the only variant we have for the moment as we only support NT!!!!!
#if BUILD_KERNEL_FROM_STRING
  static const Variant variant = {"dgemmBlockTempLocalPrefetch", dgemm_NT_ChannelConflict, NULL, NULL, 0, clblasNoTrans, clblasTrans, 256,256,2, {8,8}, {2,4}};
  return &variant;
#else

    
  if(_64BitsUse==64)
  {
    static const Variant variant = {"dgemmBlockTempLocalPrefetch", NULL, NULL, dgemm_NT_ChannelConflict_64_bin_Hawaii, sizeof(dgemm_NT_ChannelConflict_64_bin_Hawaii), clblasNoTrans, clblasTrans, 256,256,2, {8,8}, {2,4}};
    return &variant ; 
  }
  else
  {
            std::cout<<"we don't support clblas on 32 bits"<< std::endl;
			      assert(1);
            return NULL;
  }

    
#endif
  
  //return NULL;
}

clBlashawaiiDgemmChannelConflictFunctor::clBlashawaiiDgemmChannelConflictFunctor(Args & args, const Variant * variant, cl_int & err) 
{

  cl_device_id device;
  cl_context context;
  m_program=NULL;
  m_variant = variant;


  cl_command_queue queue = args.queue;
  err = getDeviceAndContext(queue, device, context);
  if( err != CL_SUCCESS )
  {
    return;
  }

  if (VERB) printf(" ===> GET KERNEL %s\n", this->m_variant->kernel_name) ;

  //Ben do I use the correct "kernel_name"?
  BinaryLookup bl(context, device, "clBlashawaiiDgemmChannelConflictFunctor");

  bl.variantRaw( this->m_variant->kernel_name, strlen(this->m_variant->kernel_name)+1 ) ;

  if ( !bl.found() ) // may create empty file or may wait until file is ready  
  {
    if ( this->m_variant->bin != 0 ) 
    {
      // build from a pre-compiled version of the kernel (SPIR or cl binaries)
      err = bl.buildFromBinary(this->m_variant->bin, this->m_variant->bin_size, this->m_variant->build_options);
    }
    else
    {
      // directly build from a char* 
      err = bl.buildFromSource(this->m_variant->source);
    } 

    if ( err != CL_SUCCESS )
    {  
      if (VERB) printf(" ===> BUILD PROBLEM\n") ;

      return;
    }
  }

  this->m_program = bl.getProgram();
}



clBlashawaiiDgemmChannelConflictFunctor * 
  clBlashawaiiDgemmChannelConflictFunctor::provide(clblasDgemmFunctor::Args & args) 
{

  if ( args.order == clblasRowMajor ) 
    return NULL ;   // The RowMajor case shall never occur. 

  cl_device_id dev;
  cl_context   ctxt;

  cl_int err = getDeviceAndContext(args.queue, dev, ctxt);
  if (err != CL_SUCCESS)
  {
    return NULL;
  }
  cl_uint bitness = getAddressBits(dev);

  const Variant * variant = select_variant_hawaiiChannelConflict( args,  bitness ) ;
  if ( variant == NULL )  
    return NULL ; 



  //for now we only have one variant, but we are working on others one and therefore I prefer keeping the code to manage them
  //Cache::Lookup lookup(cache, ctxt, dev, variant) ;
  

  //if ( lookup.ok() )
  //{
  //  clBlashawaiiDgemmChannelConflictFunctor * functor = lookup.get();
  //  functor->retain(); // increment the reference counter to avoid deletion while it is still beeing used
  //  return functor;
  //}

  clBlashawaiiDgemmChannelConflictFunctor * functor = new clBlashawaiiDgemmChannelConflictFunctor(args, variant, err);
  if (err != CL_SUCCESS)
  {
    return NULL;
  }

  //lookup.set(functor) ;

  return functor;

}
#endif