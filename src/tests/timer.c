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


#include "timer.h"

#if defined(_MSC_VER)

#include <windows.h>

nano_time_t
conv2nanosec(nano_time_t t)
{
    LARGE_INTEGER count;

	if (QueryPerformanceFrequency(&count) == FALSE) {
        return 0;
    }
    t = (t * 1000000)/count.QuadPart;

    return (nano_time_t)(t * 1000);
}

nano_time_t
conv2microsec(nano_time_t t)
{
    LARGE_INTEGER count;

	if (QueryPerformanceFrequency(&count) == FALSE) {
        return 0;
    }

    return (t * 1000000ULL)/count.QuadPart;
}

nano_time_t
conv2millisec(nano_time_t t)
{
    LARGE_INTEGER count;

    if (QueryPerformanceFrequency(&count) == FALSE) {
        return 0;
    }

    return (t * 1000) / count.QuadPart;
}

nano_time_t
getCurrentTime(void)
{
     LARGE_INTEGER count;

     if (QueryPerformanceCounter(&count) == FALSE) {
         return 0;
     }
     return (nano_time_t)count.QuadPart;
}

void
sleepTime(nano_time_t time) {
    DWORD tms = (DWORD)(time/1000000);

    Sleep(tms);
}
#else /* defined(_MCS_VER) */

#include <time.h>

nano_time_t
conv2nanosec(nano_time_t t)
{
    /* clock_... functions measure time in nanoseconds */
    return t;
}

nano_time_t
conv2microsec(nano_time_t t)
{
    return t/1000;
}

nano_time_t
conv2millisec(nano_time_t t)
{
    return t/1000000;
}

nano_time_t
getCurrentTime(void)
{
    int err;
    struct timespec t;

    err = clock_gettime(CLOCK_REALTIME, &t);
    if (err == 0) {
        return (t.tv_sec * 1000000000UL + t.tv_nsec);
    }
    return 0;
}

void
sleepTime(nano_time_t time) {
    struct timespec t1;

    t1.tv_sec = 0;
    t1.tv_nsec = time;
    nanosleep(&t1, NULL);
}

// namespace )

#endif  /* defined(_MCS_VER) */
