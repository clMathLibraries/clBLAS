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


#include <rwlock.h>

#if defined(_MSC_VER)

#pragma warning(push,3)
// Need Synchapi.h since Windows 8 or Windows Server 2012?
#include <windows.h>
#pragma warning(pop)


rwlock_t* 
rwlockInit(void)
{
  PSRWLOCK rwlock;

  rwlock = (PSRWLOCK)calloc(1, sizeof(SRWLOCK));
  if (rwlock == NULL)
      return NULL;

  InitializeSRWLock(rwlock);

  return (rwlock_t*) rwlock;
}

int 
rwlockDestroy(rwlock_t *_rwlock)
{
  if (_rwlock == NULL) {
    /* Mutex is invalid */
    return 1;
  }

  free(_rwlock);

  return 0;
}

int 
rwlockReadLock(rwlock_t *_rwlock )
{
  BOOLEAN acquired = 0;
   while(!acquired) 
    acquired = TryAcquireSRWLockShared((PSRWLOCK) _rwlock);

  return (acquired != 0);
}


int 
rwlockWriteLock(rwlock_t *_rwlock )
{
  BOOLEAN acquired = 0;
   while(!acquired) 
    acquired = TryAcquireSRWLockExclusive((PSRWLOCK) _rwlock);

  return (acquired != 0);
}


int 
rwlockReadUnlock(rwlock_t *_rwlock )
{
  ReleaseSRWLockShared((PSRWLOCK) _rwlock);

  return 0;
}


int 
rwlockWriteUnlock(rwlock_t *_rwlock )
{
  ReleaseSRWLockExclusive((PSRWLOCK)_rwlock);

  return 0;
}



#else /* defined(_MSC_VER) */

#include <stdlib.h>
#include <pthread.h>


rwlock_t*
rwlockInit(void)
{
    pthread_rwlock_t *rwlock;

    rwlock = calloc(1, sizeof(pthread_rwlock_t));
    if (rwlock == NULL)
        return NULL;
    if (pthread_rwlock_init(rwlock, NULL) != 0) {
        free(rwlock);
        return NULL;
    }

    return (rwlock_t*) rwlock;
}

int
rwlockDestroy(rwlock_t *_rwlock)
{
    pthread_rwlock_t *rwlock = (pthread_rwlock_t*)_rwlock;

    if (rwlock == NULL) {
        /* Mutex is invalid */
        return 1;
    }
    if (pthread_rwlock_destroy(rwlock) != 0) {
        /* Mutex is busy or invalid */
        return 1;
    }

    free(rwlock);
    return 0;
}


int
rwlockReadLock(rwlock_t *_rwlock )
{
    pthread_rwlock_t *rwlock = (pthread_rwlock_t*)_rwlock;

    return (pthread_rwlock_rdlock(rwlock ) == 0) ? 0 : 1;
}


int
rwlockWriteLock(rwlock_t *_rwlock ){

    pthread_rwlock_t *rwlock = (pthread_rwlock_t*)_rwlock;
    return (pthread_rwlock_wrlock(rwlock ) == 0) ? 0 : 1;

}


int
rwlockReadUnlock(rwlock_t *_rwlock )
{
    pthread_rwlock_t *rwlock = (pthread_rwlock_t*)_rwlock;

    return (pthread_rwlock_unlock(rwlock ) == 0) ? 0 : 1;
}


int
rwlockWriteUnlock(rwlock_t *_rwlock )
{
    pthread_rwlock_t *rwlock = (pthread_rwlock_t*)_rwlock;

    return (pthread_rwlock_unlock(rwlock ) == 0) ? 0 : 1;
}

#endif  /* defined (_MSC_VER) */
