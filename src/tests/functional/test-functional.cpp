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


#include <gtest/gtest.h>
#include "BlasBase.h"


///////////////////////////////////////////////////////////////////////////////

int
main(int argc, char *argv[])
{
    int ret;
    if ((argc > 1) && (!strcmp(argv[1], "--test-help") || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
        printUsage("test-functional");
        ::testing::InitGoogleTest(&argc, argv);
        return 0;
    }

    TestParams params;
    params.optFlags = NO_FLAGS;
    params.devType = CL_DEVICE_TYPE_ALL;
    params.devName = NULL;
    params.devOrd = 0;
    params.platOrd = 0;

    if (argc != 1) {
        if (parseBlasCmdLineArgs(argc, argv, &params) != 0) {
            printUsage(argv[0]);
            return 1;
        }
    }

    ::testing::InitGoogleTest(&argc, argv);
    ::std::cout << "Initialize default OpenCL and clblas..." << ::std::endl;
    ::clMath::BlasBase *base = ::clMath::BlasBase::getInstance();
    if (base == NULL) {
        ::std::cerr << "Fatal error, OpenCL or clblas initialization failed! "
                       "Leaving the test." << ::std::endl;
        return -1;
    }

    if (params.optFlags & SET_SEED) {
        base->setSeed(params.seed);
    }
    if (params.optFlags & SET_ALPHA) {
        base->setAlpha(params.alpha);
    }
    if (params.optFlags & SET_BETA) {
        base->setBeta(params.beta);
    }
    if (params.optFlags & SET_M) {
        base->setM(params.M);
    }
    if (params.optFlags & SET_N) {
        base->setN(params.N);
    }
    if (params.optFlags & SET_K) {
        base->setK(params.K);
    }
    if (params.optFlags & SET_INCX) {
        base->setIncX(params.incx);
    }
    if (params.optFlags & SET_INCY) {
        base->setIncY(params.incy);
    }
    if (params.optFlags & SET_NUM_COMMAND_QUEUES) {
        base->setNumCommandQueues(params.numCommandQueues);
    }
    if ((params.optFlags & SET_DEVICE_TYPE) || (params.optFlags & SET_PLATFORM_ORD) || (params.optFlags & SET_DEVICE_ORD)) {
        if (!base->setDeviceType( params )) {
            ::std::cerr << "Fatal error, OpenCL or clblas "
                    "initialization failed! Leaving the test." <<
                    ::std::endl;
            return -1;
        }
    }

    parseEnv(&params);
    if ((params.optFlags & SET_USE_IMAGES) &&
            (params.devType != CL_DEVICE_TYPE_CPU)) {
        base->setUseImages(params.useImages);
    }

	/* Use of image based buffers is deprecated
    if (base->useImages()) {
        if (base->addScratchImages()) {
            std::cerr << "FATAL ERROR, CANNOT CREATE SCRATCH IMAGES!" << std::endl;
        }
    }
	*/

    base->printEnvInfo();
    ret = RUN_ALL_TESTS();

    if (base->useImages()) {
        base->removeScratchImages();
    }

    return ret;
}
