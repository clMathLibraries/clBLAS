/* ************************************************************************
 * Copyright 2013 Advanced Micro Devices, Inc.
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


#ifndef RWLOCK_H_
#define RWLOCK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The rwlock functions provide an abstract implementation of a 
 * readers-writer lock (also called a shared/exclusive lock).
 *
 * Simply speaking, that kind of locks allows either 
 *  - multiple concurently read access to a data structure.
 *  - a single write access that excludes other read or write accesses. 
 *
 * A read region shall start by a call to rwlockReadLock() and stop with
 * rwlockReadUnlock()
 *  
 * A write region shall start by a call to rwlockWriteLock() and stop with
 * rwlockWriteUnlock()
 *
 * Of course two consecutive calls of either rwlockReadLock() and
 * rwlockWriteLock() in a single thread will cause a deadlock.
 *
 *
 * Example: Access to a protected counter
 *
 *
 *   int counter = 0 ;
 *   rwlock_t *lock = rwlockInit() ; 
 *
 *   int getCounter() 
 *   {
 *      int v ; 
 *      rwlockReadLock(lock) ; 
 *      v = counter ; 
 *      rwlockReadUnlock(lock) ;
 *      return v ; 
 *   } 
 *   
 *   int preIncrementCounter() 
 *   {
 *      int v ; 
 *      rwlockWriteLock(lock) ; 
 *      v = ++counter ; 
 *      rwlockWriteUnlock(lock) ;
 *      return v; 
 *   } 
 *   
 *   
 *
 */



typedef void* rwlock_t;

/* 
 * Create and initialize a new readers-writer lock
 *
 */ 
rwlock_t* rwlockInit(void);


/* 
 * Destroy a readers-writer lock previously created by rwlockInit() 
 *
 */ 
int rwlockDestroy(rwlock_t *rwlock);

/* 
 * Enter a (shared) read region
 *
 */
int rwlockReadLock(rwlock_t *rwlock );

/* 
 * Enter a (exclusive) write region
 *
 */
int rwlockWriteLock(rwlock_t *rwlock );

/* 
 * Leave a read region
 *
 */
int rwlockReadUnlock(rwlock_t *rwlock );

/* 
 * Leave a write region
 *
 */
int rwlockWriteUnlock(rwlock_t *rwlock );


#ifdef __cplusplus
}
#endif

#endif  /* RWLOCK_H_ */
