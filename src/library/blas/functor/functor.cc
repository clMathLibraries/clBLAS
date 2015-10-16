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
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <ios>

#include <functor.h>

#include <clblas-internal.h>

#include <vector>
#include <set>


clblasFunctor::clblasFunctor()
    : refcount(1) // implicit retain
{
}


clblasFunctor::~clblasFunctor() 
{
}


void clblasFunctor::retain()
{
    refcount.increment() ;
}

void clblasFunctor::release()
{
    int n = refcount.decrement() ; 

    if (n==0)
    {
      delete this;
    }
}

cl_int clblasFunctor::getDeviceAndContext(cl_command_queue queue,
                                    cl_device_id & device,
                                    cl_context & context)
{
  cl_int err;
  err = getQueueContext(queue, &context);

  if (err != CL_SUCCESS)
  {
      return err;
  }

  err = getQueueDevice(queue, &device);

  if (err != CL_SUCCESS)
  {
      return err;
  }

  return CL_SUCCESS;
}

cl_uint clblasFunctor::getAddressBits(cl_device_id & device)
{
  cl_uint bitness;
  cl_uint error = clGetDeviceInfo(device, CL_DEVICE_ADDRESS_BITS, sizeof(cl_uint), &bitness, NULL);
  if(error==CL_SUCCESS)
    return bitness;
  else
    return 32;
}

void clblasFunctor::getCLVersion(cl_device_id & device, int&major, int& minor)
{
  size_t size = 0;
  cl_int success = 0;
  major = 0;
  minor = 0;

  success = clGetDeviceInfo(device, CL_DEVICE_OPENCL_C_VERSION, 0, NULL, &size);
  if (success == CL_SUCCESS)
  {
    char* CLVersion = NULL;
    if (size)
    {
      CLVersion = new char[size];
      if (CLVersion)
        success = clGetDeviceInfo(device, CL_DEVICE_OPENCL_C_VERSION, size, CLVersion, NULL);
      else
        return;
    
      if (success != CL_SUCCESS)
        return;

      char Major = CLVersion[9];
      char Minor = CLVersion[11];
      major = atoi(&Major);
      minor = atoi(&Minor);

    }
  }
}
