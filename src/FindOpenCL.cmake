# ########################################################################
# Copyright 2013 Advanced Micro Devices, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ########################################################################


# Locate an OpenCL implementation.
# Currently supports AMD APP SDK (http://developer.amd.com/sdks/AMDAPPSDK/Pages/default.aspx/)
#
# Defines the following variables:
#
#   OPENCL_FOUND - Found the OPENCL framework
#   OPENCL_INCLUDE_DIRS - Include directories
#
# Also defines the library variables below as normal
# variables.  These contain debug/optimized keywords when
# a debugging library is found.
#
#   OPENCL_LIBRARIES - libopencl
#
# Accepts the following variables as input:
#
#   OPENCL_ROOT - (as a CMake or environment variable)
#                The root directory of the OpenCL implementation found
#
#   FIND_LIBRARY_USE_LIB64_PATHS - Global property that controls whether findOpenCL should search for
#                              64bit or 32bit libs
#-----------------------
# Example Usage:
#
#    find_package(OPENCL REQUIRED)
#    include_directories(${OPENCL_INCLUDE_DIRS})
#
#    add_executable(foo foo.cc)
#    target_link_libraries(foo ${OPENCL_LIBRARIES})
#
#-----------------------
if( DEFINED ENV{AMDAPPSDKROOT} )
	set( OPENCL_ROOT $ENV{AMDAPPSDKROOT} CACHE PATH "Environment variable defining the root of OPENCL implementation" )
elseif( DEFINED ENV{CUDA_PATH} )
        set( OPENCL_ROOT $ENV{CUDA_PATH} CACHE PATH "Environment variable defining the root of OPENCL implementation" )
else( )
	set( OPENCL_ROOT "/usr/lib" CACHE PATH "Environment variable defining the root of OPENCL implementation" )
endif( )

find_path(OPENCL_INCLUDE_DIRS
	NAMES OpenCL/cl.h CL/cl.h
    HINTS
		${OPENCL_ROOT}/include
		ENV AMDAPPSDKROOT/include
	PATHS
		/usr/include
		/usr/local/include
	DOC "OpenCL header file path"
)
mark_as_advanced( OPENCL_INCLUDE_DIRS )

# Search for 64bit libs if FIND_LIBRARY_USE_LIB64_PATHS is set to true in the global environment, 32bit libs else
get_property( LIB64 GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS )

if( LIB64 )
	find_library( OPENCL_LIBRARIES
		NAMES OpenCL
		HINTS
            ${OPENCL_ROOT}/lib
            ENV AMDAPPSDKROOT/lib
		DOC "OpenCL dynamic library path"
		PATH_SUFFIXES x86_64 x64
	)
else( )
	find_library( OPENCL_LIBRARIES
		NAMES OpenCL
		HINTS
            ${OPENCL_ROOT}/lib
            ENV AMDAPPSDKROOT/lib
		DOC "OpenCL dynamic library path"
		PATH_SUFFIXES x86 Win32
	)
endif( )
mark_as_advanced( OPENCL_LIBRARIES )

include( FindPackageHandleStandardArgs )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( OPENCL DEFAULT_MSG OPENCL_LIBRARIES OPENCL_INCLUDE_DIRS )

if( NOT OPENCL_FOUND )
	message( STATUS "FindOpenCL looked for libraries named: OpenCL" )
endif()
