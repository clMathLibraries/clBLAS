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

#ifndef _CLBLAS_ATOMIC_COUNTER_H_
#define _CLBLAS_ATOMIC_COUNTER_H_

#include <mutex.h>

//
// This header provides the class clblasAtomicCounter that can be
// used to implement a thread-safe usage counter as follow:
//  
// class MyObject 
// {
//    ...
//    clblasAtomicCounter counter ; 
//    ... 
// 
//    MyObject() : counter(1) {
//      ...
//    }
//
//    void retain() {
//       counter.increment() ; 
//    }
// 
//    void release() {
//       if ( counter.decrement() == 0 ) {
//         delete this ; 
//       } 
//    }
//   
// }
//
//
// This header provides 2 versions controled by the macro CLBLAS_USE_STD_ATOMIC:
//
//  - if CLBLAS_USE_STD_ATOMIC is set to non-zero then an implementation 
//    based on <atomic> from C++11 is used 
//
//  - if CLBLAS_USE_STD_ATOMIC is set to zero then a portable but less efficient 
//    version using mutex is used 
//
//  - else if CLBLAS_USE_STD_ATOMIC is unset then an automatic detection of <atomic> 
//    and C++11 is automatically attempted 
//
// Remark: there exists several other atomic implementations (e.g. boost, ...) that
//         could be implemented here
//

#ifndef CLBLAS_USE_STD_ATOMIC

//
// FIXME: G++ does not properly declare __cplusplus  according to the standard
//        but may provide <atomic> at least in recent versions
//

#if __cplusplus >= 201103L 
#define CLBLAS_USE_STD_ATOMIC 1
#else
#define CLBLAS_USE_STD_ATOMIC 0 
#endif

#endif


#if CLBLAS_USE_STD_ATOMIC

// This is the optimized version using std::atomic from C++11 
//
// On the long term that shall be the only version  
//

#include <atomic> 

class clblasAtomicCounter 
{
private:
    std::atomic<int> value;
public:

    clblasAtomicCounter(int v) : value(v) { }  

    // Increments the counter and returns the incremented value. 
    // (so a pre-increment) 
    int increment() {
      return ++ value;
    }

    // Decrements the counter and returns the decremented value. 
    // (so a pre-decremment) 
    int decrement() {
      return -- value;
    }

    // Provide the counter value 
    int get(){
        return value.load();
    }
};

#else

//
// A less optimized but more portable version using 
// a mutex to insure atomicity
//

class clblasAtomicCounter 
{
private:
  
  int       value;
  mutex_t * mutex ; 
  
public:

  clblasAtomicCounter(int v) : value(v)
  { 
    mutex = mutexInit() ; 
  }  

  ~clblasAtomicCounter() 
  { 
    mutexDestroy(mutex) ;
  }  
  
  int increment()
  {
    int v ;
    mutexLock( this->mutex ) ; 
    v = ++ this->value ;
    mutexUnlock( this->mutex ) ; 
    return v ; 
  }
  
  int decrement()
  {
    int v ;
    mutexLock( this->mutex ) ; 
    v = -- this->value;
    mutexUnlock( this->mutex ) ; 
    return v ; 
  }

  int get(){
    int v ;
    mutexLock( this->mutex ) ; 
    v = this->value ;
    mutexUnlock( this->mutex ) ; 
    return v ; 
  }


};

#endif


#endif
