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

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <ios>

#include <../functor/include/functor.h>
#include <clblas-internal.h>

#include <vector>
#include <set>



// ==================================================
// == clblasFunctorCacheBase
// ==================================================

typedef std::set<clblasFunctorCacheBase*> clblasFunctorCacheSet ; 

// Provide the set of all existing functor cache
//
// Remark: Since the set is typically populated by the constructors
//         of global objects, we use the "construct on first use" 
//         idiom, to avoid the infamous "static initialization order fiasco".
//         See for example  http://www.parashift.com/c++-faq/static-init-order.html
// 
// Remark: The current implementation is not thread-safe but that should
//         be fine since the cache is supposed to be populated at startup 
//         (assuming that all functor caches are global objects) and 
//
static clblasFunctorCacheSet & getFunctorCacheSet() 
{
  static clblasFunctorCacheSet * all = new clblasFunctorCacheSet ; 
  return * all ; 
}

//
// This function is supposed to be called from clblasTearDown to empty all caches
//
extern "C" void cleanFunctorCaches(void) 
{
  // Ask each registered cache to clean itself. 
  clblasFunctorCacheSet & all = getFunctorCacheSet() ; 
  for (clblasFunctorCacheSet::iterator it= all.begin(); it!=all.end(); ++it)
    {
      clblasFunctorCacheBase * cache = *it ; 
      cache->discardAll() ; 
    }
}

clblasFunctorCacheBase::clblasFunctorCacheBase()
{
  //  if ( _cleanFunctorCachesHook == 0 ) 
  //   _cleanFunctorCachesHook = cleanFunctorCaches ; // Install the hook to call cleanFunctorCaches

  clblasFunctorCacheSet & all = getFunctorCacheSet() ; 
  all.insert(this) ; 
}  

clblasFunctorCacheBase::~clblasFunctorCacheBase() 
{
  clblasFunctorCacheSet & all = getFunctorCacheSet() ; 
  all.erase(this) ; 
}
