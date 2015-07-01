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

#ifndef _CLBLAS_FUNCTOR_H_
#define _CLBLAS_FUNCTOR_H_

#include <clBLAS.h>
#include <cassert>
#include <map>
#include <rwlock.h>
#include "atomic_counter.h"
#include "functor_utils.h"

//
// clblasFunctor is the base class for all functors used to implemetn clBLAS API calls 
//
// A functor is basically an object that provides an implementation of a given function
// as a virtual member. 
//
// The clblasFunctor class itself does not provide such function but all its
// derived classes shall provide one. For consistancy, it is recommanded to
// use 'execute' as the name for the member providing that function.
//
// So the class clblasFunctor shall be derived once for each supported
// function. For instance, the class clblasDgemmFunctor provides the base
// functor class for implementing the DGEMM call. 
//
// The class clblasDgemmFunctor is itself derived one or more times to provide
// the real implementations of the DGEMM functionnality. 
//
// The choice of the proper implementation amongst the available functors is 
// typically delegated to another mechanism (see clblasFunctorSelector for instance). 
//
class clblasFunctor 
{
public:

    clblasFunctor();
    virtual ~clblasFunctor() ;

    static cl_int getDeviceAndContext(cl_command_queue q,
                                      cl_device_id & device,
                                      cl_context & context);
    static cl_uint getAddressBits(cl_device_id & device);

	static void getCLVersion(cl_device_id & device, int&major, int& minor);


    template <class T>
    static void setKernelArg(cl_kernel kernel,
                             int index,
                             T data)
    {
        cl_int err = clSetKernelArg(kernel,
                                    (unsigned int)index,
                                    sizeof(T),
                                    (const void *)&data);

        assert( err == CL_SUCCESS );
    }
   
    static void setKernelArgPtr(cl_kernel kernel,
                                int index,
                                size_t sz,
                                const void *data)
    {
        cl_int err = clSetKernelArg(kernel,
                                    (unsigned int)index,
                                    sz,
                                    data);

        assert( err == CL_SUCCESS );
    }

    // Indicate that this object has one more user.
    // The default behavior is to increase the internal use counter.
    // This function is thread-safe.
    virtual void retain();

    
    // Indicate that this object has one less user.
    // The default behavior is to decrease the internal use counter
    // and, if it reaches zero, to destroy this object.
    // This function is thread-safe.
    virtual void release();

private:
  
    // Thread-safe reference counter used by the default implementation 
    // of retain and release
    clblasAtomicCounter refcount; 

  //protected:
  //   cl_program program;
  //   cl_kernel kernel;
};



//
// This class shall be the base class for all Functor caches.  
// 
// The idea is that all Functor caches derived from that class 
// will register themselves in a global cache pool thus allowing 
// some global cache management tasks to be performed
//
// As of now, the only implemented task is to discard all 
// cache entries (see cleanFunctorCaches() typically called 
// during clblasTeardown()) but, in future versions, it 
// would be nice to have other management tasks such as 
// removing all cache entries using a specific context 
// or controling the overall size of the cache
//
class clblasFunctorCacheBase {
public:
  // Constructor: will register the cache in global cache pool  
  clblasFunctorCacheBase(); 
  // Constructor: will unregister the cache in global cache pool 
  virtual ~clblasFunctorCacheBase() ;
public:
  // Discard all members of the cache 
  virtual void discardAll() = 0 ;

} ;


//
// A dummy class used to represent the absence of additional data. 
//
// 
class clblasNoData {
public:
  // Provide the operator '<' needed by std::less 
  inline bool operator<(const clblasNoData &) const { return false ; }
} ;

//
// Represents the only possible value for clblasNoData 
//
#define CLBLAS_NO_DATA clblasNoData() 

//
// The templated class clblasFunctorCache<F,D> provides a reusable 
// implementation of a cache of functors of type F according to the 
// openCL context and the openCL device.  
//
// The type D is optional and represents additional data used to 
// index the cache entries. The third optional template 
// argument CompareD is a comparison object for the type D similar 
// to those used in std::map or std::sort. 
//
// The idea is that each physical implementation of a functor is
// supposed to manage its own cache in order to become reusable
// between subsequent calls to clBLAS.
//
// The cache implementation is thread-safe assuming that it is used 
// properly:
//   (1) The lookup() method shall be called to search an existing 
//       entry corresponding to the specified context and device. 
//   (2) If the lookup() is successfull then the reference counter 
//       on the returned functor is implicitly increased and that 
//       functor can be used immediately. 
//   (3) If the lookup() is not successfull - that is if the 
//       resulting functor is null, then the cache is locked for 
//       writing and a new cache entry is prepared. The user 
//       is then responsible for creating a new functor that must 
//       be registered via a call to setFunctorInEntry().
//       Alternatively, the new cache entry can be dropped by a 
//       call to dropEntry().
//       Not calling setFunctorInEntry() or dropEntry() will leave 
//       the cache in a locked state thus making it unusable and 
//       likely to cause a dead-lock. 
//
// In order to simplify development and to avoid errors, the
// clblasFunctorCache provides an Lookup object class that hides most
// of those details and insure that the case does not stay in an
// locked state (as long as the loopup object is properly destroyed).
//
// In case a non-trivial custom type D is specified it may be necessary 
// to provide the comparison operator '<' needed by less<D> as in the 
// following example:
//
//    struct MyData 
//    { 
//
//      int x,y,z ; 
//       
//      inline bool operator< ( const MyData &b ) const 
//      {
//        const MyData & a = *this ; 
//        if ( a.x < b.x ) return true else if ( a.x > b.x ) return false ; 
//        if ( a.y < b.y ) return true else if ( a.y > b.y ) return false ; 
//        if ( a.z < b.z ) return true else if ( a.z > b.z ) return false ; 
//        return false ; 
//      }
//
//    }
//
// Alternatively, if the custom type D is known to be a fully
// initialized POD (including the unused bits) then the operator 
// '<' can be provided using memcmp()
//
//    #include <cstring>
//
//    struct MyData 
//    { 
//      MyData() { std::memset(this,0,sizeof(MyData) ; } 
// 
//      int x,y,z ; 
//       
//      inline bool operator< ( const MyData &b ) const 
//      {
//        return std::memcmp( this, b ) < 0 ; 
//      }
//    }
//   
//
//
//
template<class F, typename D = clblasNoData , typename CompareD = std::less<D> >
class clblasFunctorCache  : public clblasFunctorCacheBase 
{

private:

  struct Key { 
    cl_device_id dev;
    cl_context   ctxt;
    D            data ;  // Additional user data in the key 


    //compare two Keys
    bool operator< (const Key & b) const {
      const Key &a = *this;
      if(a.dev != b.dev)
        return a.dev < b.dev;        
      
      if(a.ctxt != b.ctxt)
        return a.ctxt < b.ctxt;  

      CompareD cmp ; 
      return cmp(a.data,b.data) ;
    }
  };


  typedef clblasFunctorCache<F,D,CompareD> Cache;

  // The current implementation is using a std::map internally. 
  // That may not be the most efficient but that can easily be 
  // changed if needed.

  typedef std::map<Key, F *>        Map;
  typedef typename Map::iterator    Entry;


private:

  Map        m_map;
  rwlock_t * m_rwlock;

public:

  //Cache constructor: init mutex
  clblasFunctorCache()
  {
    this->m_rwlock = rwlockInit();
  }

  
  //Cache destructor: destroy mutex
  ~clblasFunctorCache(){
    rwlockDestroy(this->m_rwlock);
  }


public:

  // 
  // Lookup objects are short time objects used to perform a single query in 
  // the cache. 
  //
  // The usage pattern of a Lookup object shall always be the same
  //
  //  - Declare a local Lookup object 
  //  - Perform a call to the ok() member 
  //     (1) if true then use the functor returned by get() 
  //     (2) if false then the cache is locked until the user provides 
  //         a new functor with a call to set().
  //  - Destroy the Lookup object
  //
  // So a functor implementation can implement its own cache as illustrated 
  // by the following example:
  // 
  //    class MyDGemmFunctor: public clblasDGemmFunctor
  //    {
  //
  //      ... 
  //
  //      typedef clblasFunctorCache<MyDGemmFunctor> Cache ;  
  //      static Cache cache;
  //
  //      ...
  //    
  //      MyDGemmFunctor * provide(...)
  //      {
  //        MyDGemmFunctor * functor ; 
  //
  //        MyDGemmFunctor::Cache::Lookup lookup(MyDGemmFunctor::cache, ctxt, dev) ;
  //        
  //        if ( lookup.ok() ) 
  //        {
  //          return lookup.get() ; 
  //        } 
  //        else 
  //        {
  //          MyDGemmFunctor * functor = new MyDGemmFunctor(...);
  //          lookup.set(functor) ;
  //          return functor ;
  //        }
  //        
  //      }
  //
  //      ... 
  // 
  //    } ;
  //
  //
  class Lookup {
  private:
    Entry         m_entry ;
    F *           m_functor ;
    Cache &       m_cache ;

  public:

    // Constructor
    //
    // Perform a lookup in the specified cache 
    // 
    Lookup(Cache & cache, cl_context ctxt,  cl_device_id dev , const D & data) : m_cache(cache) 
    {
      this->m_functor = m_cache.lookup(ctxt,dev,data,this->m_entry) ;
    }

    //
    // Alternative constructor when D is the default type clblasNoData
    // 
    Lookup(Cache & cache, cl_context ctxt,  cl_device_id dev ) : m_cache(cache) 
    {
      this->m_functor = m_cache.lookup(ctxt,dev,CLBLAS_NO_DATA,this->m_entry) ;
    }
   

    // Destructor 
    ~Lookup()
    {
      if (  !this->ok() ) {
        // Hoops! Something went wrong! 
        // It is important to drop the pending cache entry
        m_cache.dropPendingEntry(this->m_entry) ;
      }
    } 
    
     
    bool ok() {
      return this->m_functor != NULL ;
    }
    
    
    F * get() {
      assert(this->ok()) ;
      //return m_cache.getFunctorFromEntry(this->entry) ;
      return this->m_functor;
    }
    
    // Set the functor in the 
    void set(F* f) 
    {
      assert(!this->ok()) ;
      assert(f != NULL) ;
      m_cache.fillPendingEntry(this->m_entry,f) ;
      this->m_functor = f ;
      this->m_functor->retain();
    }
    
  } ;

 
private:
  
  // Perform a lookup in the cache.
  //
  // In case of success, returns the found functor.
  //
  // In case of failure, locks the cache, creates a new pending cache entry (in argument 'entry')
  // and returns NULL.  The pending 'entry' shall then be populated with a valid functor by a 
  // call to fillPendingEntry() or shall be dropped by a called dropPendingEntry(). Any failure 
  // to perform one of those action will let the cache in a locked state thus making is unusable
  // 
  // Remark: Direct use of this member is discouraged. Use the Lookup classe instead. 
  // 
  F* lookup(cl_context ctxt, cl_device_id dev, const D & data, Entry & entry)
  {

    Key key = { dev, ctxt , data };

    rwlockReadLock(this->m_rwlock);
    {

      Entry l_entry = this->m_map.find(key);
      if( l_entry != this->m_map.end() )
      {
        entry = l_entry;
        F * f =  entry->second;
        rwlockReadUnlock(this->m_rwlock);
 
        return f ; 
      }
    }
    rwlockReadUnlock(this->m_rwlock);

    // key was not found! It must be created
    std::pair<Entry,bool> ret;
    
    rwlockWriteLock(this->m_rwlock);

    ret = this->m_map.insert ( std::make_pair(key,(F *) NULL) );

    if (!ret.second)  {
      // The key already exists! 
      F * f  = ret.first->second ;
      rwlockWriteUnlock(this->m_rwlock);
      return f ; 
    }

    entry = ret.first;

    // Reminder: the lookup() returns with the cache in a write-locked state
    return NULL;    

  };


  // Fill a pending cache entry with a valid functor as provided by an
  // unsuccessfull call to lookup().
  void fillPendingEntry(Entry & entry, F * functor)
  {
    assert(functor != NULL) ;
    entry->second = functor ;
    rwlockWriteUnlock(this->m_rwlock);
  }

  // Drop a pending cache entry with a valid functor as provided by 
  // an unsuccessfull call to lookup(). 
  void dropPendingEntry(Entry & entry ) 
  {
    this->m_map.erase(entry) ;
    rwlockWriteUnlock(this->m_rwlock);
  }

public: // Inherited members from clblasFunctorCacheBase

  void discardAll() 
  {
     rwlockWriteLock(this->m_rwlock);
     
    while ( true ) 
    {
      Entry entry = this->m_map.begin() ;
      if ( entry == this->m_map.end() ) 
        break ; 
      entry->second->release() ;
      this->m_map.erase(entry) ;
    }
    rwlockWriteUnlock(this->m_rwlock);   
  }


};


#endif // _CLBLAS_FUNCTOR_H_
