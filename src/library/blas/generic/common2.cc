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

/*
 * Common C functions using C++ APIs
 */

#include <binary_lookup.h>

#include <clblas-internal.h>

#include <stdio.h>

#define CAPS_DEBUG 0

extern "C" Kernel* makeKernelCached(cl_device_id device,
                                    cl_context context,
                                    solver_id_t sid,
                                    KernelKey * key,
                                    SolverKgen kernelGenerator,
                                    const SubproblemDim *dims,
                                    const PGranularity *pgran,
                                    const CLBLASKernExtra *extra,
                                    const char *buildOpts,
                                    cl_int *error)
{
    // For now on, use the solver id to identify the kernel
    // FIXME: it should be better to use the FunctionID but it sounds that there 
    // is a confusion between BlasFunctionID and BlasRoutineID in makeSolutionSeq() function...
    char name[20];
    sprintf(name, "solver%d", (int)sid);

    BinaryLookup bl(context, device, name);

    // Use the whole extra field as signature to identify the kernel binary for now on
    // may be improved...
    bl.variantInt(sid);
    bl.variantInt(key->nrDims);
    bl.variantRaw(key->subdims, sizeof(SubproblemDim) * key->nrDims);
    bl.variantRaw(extra, sizeof(CLBLASKernExtra));

    if (bl.found())
    {
#if CAPS_DEBUG
        printf("Kernel loaded from cache\n");
#endif
        return makeKernel(device,
                          context,
                          0, // generator is not needed because the program
                             // was loaded from the disk
                          bl.getProgram(), // pass the program loaded from the
                                           // disk
                          dims,
                          pgran,
                          extra,
                          buildOpts,
                          error);

    }
    else
    {
#if CAPS_DEBUG
        printf("Kernel generated from source\n");
#endif
        Kernel * kernel = makeKernel(device,
                                     context,
                                     kernelGenerator,
                                     0, // cl_program = 0 because it was not loaded from the disk
                                     dims,
                                     pgran,
                                     extra,
                                     buildOpts,
                                     error);

        bl.setProgram(kernel->program);

        bl.populateCache();

        return kernel;
    }
}




