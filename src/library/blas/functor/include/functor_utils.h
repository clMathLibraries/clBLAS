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

#ifndef _CLBLAS_FUNCTOR_UTILS_
#define _CLBLAS_FUNCTOR_UTILS_

#include <clblas-internal.h>

static inline clblasStatus checkQueues(cl_uint numCommandQueues,
                                       cl_command_queue *commandQueues)
{
    if (numCommandQueues<=0)
    {
        return clblasInvalidCommandQueue;
    }
                                                                        
    if (commandQueues == 0)
    {
        return clblasInvalidCommandQueue;
    }

    for (cl_uint i=0 ; i<numCommandQueues ; ++i)
    {
        if (commandQueues[i] == 0)
        {
            return clblasInvalidCommandQueue;
        }
    }
    return clblasSuccess ;
}

static inline clblasStatus checkEventWaitList(cl_uint numEventsInWaitList,
                                              const cl_event *eventWaitList)
{                                                                        
    if (numEventsInWaitList>0 && eventWaitList == 0)
    {
        return clblasInvalidEventWaitList;
    }

    for (cl_uint i=0 ; i<numEventsInWaitList ; ++i)
    {
        if (eventWaitList[i] == 0)
        {
            return clblasInvalidEventWaitList;
        }
    }
    return clblasSuccess ;
}

static inline clblasStatus checkMatrixA(DataType dtype, clblasOrder order, clblasTranspose trans, cl_mem mat, size_t size1, size_t size2, size_t off, size_t ld)
{
    return checkMatrixSizes(dtype, order, trans, size1, size2, mat, off, ld, A_MAT_ERRSET);
}

static inline clblasStatus checkMatrixB(DataType dtype, clblasOrder order, clblasTranspose trans, cl_mem mat, size_t size1, size_t size2, size_t off, size_t ld)
{
    return checkMatrixSizes(dtype, order, trans, size1, size2, mat, off, ld, B_MAT_ERRSET);
}

static inline clblasStatus checkMatrixC(DataType dtype, clblasOrder order, clblasTranspose trans, cl_mem mat, size_t size1, size_t size2, size_t off, size_t ld)
{
    return checkMatrixSizes(dtype, order, trans, size1, size2, mat, off, ld, C_MAT_ERRSET);
}

static inline clblasStatus checkVectorX(DataType dtype, size_t N, cl_mem X, size_t offx, int incx)
{
    return checkVectorSizes(dtype, N, X, offx, incx, X_VEC_ERRSET);
}

static inline clblasStatus checkVectorY(DataType dtype, size_t N, cl_mem Y, size_t offy, int incy)
{
    return checkVectorSizes(dtype, N, Y, offy, incy, Y_VEC_ERRSET);
}

#define RETURN_ON_ERROR(EXPR)          \
    do {                               \
       clblasStatus err = EXPR ;       \
       if (err != clblasSuccess)       \
           return err ;                \
    } while(0);

#define CHECK_QUEUES(numCommandQueues, commandQueues)                    \
   RETURN_ON_ERROR( checkQueues(numCommandQueues, commandQueues) )

#define CHECK_EVENTS(numEventsInWaitList, eventWaitList)                 \
   RETURN_ON_ERROR( checkEventWaitList(numEventsInWaitList, eventWaitList) )

#define CHECK_MATRIX_A(type, order, trans, mat, size1, size2, off, ld)   \
    RETURN_ON_ERROR( checkMatrixA(type, order, trans, mat, size1, size2, off, ld) )

#define CHECK_MATRIX_B(type, order, trans, mat, size1, size2, off, ld)   \
    RETURN_ON_ERROR( checkMatrixB(type, order, trans, mat, size1, size2, off, ld) )

#define CHECK_MATRIX_C(type, order, trans, mat, size1, size2, off, ld)   \
    RETURN_ON_ERROR( checkMatrixC(type, order, trans, mat, size1, size2, off, ld) )

#define CHECK_VECTOR_X(type, N, X, offx, incx)                           \
    RETURN_ON_ERROR( checkVectorX(type, N, X, offx, incx) )

#define CHECK_VECTOR_Y(N, Y, offy, incy)                                 \
   RETURN_ON_ERROR( checkVectorY(type, N, Y, offy, incy) )

#endif // _CLBLAS_FUNCTOR_UTILS_
