# AutoGemm src and out files
set(AUTOGEMM_SRC
    ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/AutoGemm.py
    ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/AutoGemmParameters.py
    ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/Common.py
    ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/Includes.py
    ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/KernelOpenCL.py
    ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/KernelParameters.py
    ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/KernelSelection.py
    ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/KernelsToPreCompile.py
)
set(AUTOGEMM_HEADERS
    ${CMAKE_BINARY_DIR}/include/AutoGemmClKernels.h
    ${CMAKE_BINARY_DIR}/include/AutoGemmBinaryBuildOptions.h
    ${CMAKE_BINARY_DIR}/include/AutoGemmBinaryIncludes.h
    ${CMAKE_BINARY_DIR}/include/AutoGemmBinaryNulls.h
    ${CMAKE_BINARY_DIR}/include/AutoGemmKernelSelection.h
    ${CMAKE_BINARY_DIR}/include/AutoGemmKernelSelectionSpecific.h
    ${CMAKE_BINARY_DIR}/include/AutoGemmKernelSourceBuildOptions.h
    ${CMAKE_BINARY_DIR}/include/AutoGemmKernelSourceIncludes.h
)
set(AUTOGEMM_TEST_SRC
  AutoGemmTools/TestAutoGemm.cpp
)
set(AUTOGEMM_PROFILER_SRC
  AutoGemmTools/ProfileAutoGemm.cpp
)
set(AUTOGEMM_PRECOMPILE_SRC
  AutoGemmTools/AutoGemmPreCompileKernels.cpp
)

# AutoGemm options for pre-compiling kernels
option( AutoGemmPreCompile_PRECISION_SGEMM "AutoGemm: pre-compile sgemm kernels" OFF)
option( AutoGemmPreCompile_PRECISION_DGEMM "AutoGemm: pre-compile dgemm kernels" OFF)
option( AutoGemmPreCompile_PRECISION_CGEMM "AutoGemm: pre-compile cgemm kernels" OFF)
option( AutoGemmPreCompile_PRECISION_ZGEMM "AutoGemm: pre-compile zgemm kernels" OFF)

option( AutoGemmPreCompile_TRANS_NN "AutoGemm: pre-compile NN transpose cases" OFF)
option( AutoGemmPreCompile_TRANS_NT "AutoGemm: pre-compile NT transpose cases" OFF)
option( AutoGemmPreCompile_TRANS_NC "AutoGemm: pre-compile NC transpose cases" OFF)
option( AutoGemmPreCompile_TRANS_TN "AutoGemm: pre-compile TN transpose cases" OFF)
option( AutoGemmPreCompile_TRANS_TT "AutoGemm: pre-compile TT transpose cases" OFF)
option( AutoGemmPreCompile_TRANS_TC "AutoGemm: pre-compile TC transpose cases" OFF)
option( AutoGemmPreCompile_TRANS_CN "AutoGemm: pre-compile CN transpose cases" OFF)
option( AutoGemmPreCompile_TRANS_CT "AutoGemm: pre-compile CT transpose cases" OFF)
option( AutoGemmPreCompile_TRANS_CC "AutoGemm: pre-compile CC transpose cases" OFF)

option( AutoGemmPreCompile_TILE_96x96 "AutoGemm: pre-compile 96x96 tiles" OFF)
option( AutoGemmPreCompile_TILE_80x80 "AutoGemm: pre-compile 80x80 tiles" OFF)
option( AutoGemmPreCompile_TILE_64x64 "AutoGemm: pre-compile 64x64 tiles" OFF)
option( AutoGemmPreCompile_TILE_48x48 "AutoGemm: pre-compile 48x48 tiles" OFF)
option( AutoGemmPreCompile_TILE_32x32 "AutoGemm: pre-compile 32x32 tiles" OFF)
option( AutoGemmPreCompile_TILE_16x16 "AutoGemm: pre-compile 32x32 tiles" OFF)
option( AutoGemmPreCompile_TILE_NONMULTIPLES "AutoGemm: pre-compile kernels for matrices which are not a multiple of any tile" OFF)

# PreCompile precision selected?
set( AutoGemmPreCompile_PRECISION_SELECTED OFF)
if (   AutoGemmPreCompile_PRECISION_SGEMM
    OR AutoGemmPreCompile_PRECISION_DGEMM
    OR AutoGemmPreCompile_PRECISION_CGEMM
    OR AutoGemmPreCompile_PRECISION_ZGEMM )
  set( AutoGemmPreCompile_PRECISION_SELECTED ON)
endif()

# PreCompile transpose selected?
set( AutoGemmPreCompile_TRANS_SELECTED OFF)
if (   AutoGemmPreCompile_TRANS_NN
    OR AutoGemmPreCompile_TRANS_NT
    OR AutoGemmPreCompile_TRANS_NC
    OR AutoGemmPreCompile_TRANS_TN
    OR AutoGemmPreCompile_TRANS_TT
    OR AutoGemmPreCompile_TRANS_TC
    OR AutoGemmPreCompile_TRANS_CN
    OR AutoGemmPreCompile_TRANS_CT
    OR AutoGemmPreCompile_TRANS_CC )
  set( AutoGemmPreCompile_TRANS_SELECTED ON)
endif()

# PreCompile tiles selected?
set( AutoGemmPreCompile_TILE_SELECTED OFF)
if (   AutoGemmPreCompile_TILE_96x96
    OR AutoGemmPreCompile_TILE_80x80
    OR AutoGemmPreCompile_TILE_64x64
    OR AutoGemmPreCompile_TILE_48x48
    OR AutoGemmPreCompile_TILE_32x32
    OR AutoGemmPreCompile_TILE_16x16
    OR AutoGemmPreCompile_TILE_NONMULTIPLES )
  set( AutoGemmPreCompile_TILE_SELECTED ON)
endif()

# PreCompile is valid and active?
set( AutoGemmPreCompile_ACTIVE OFF)
if ( AutoGemmPreCompile_PRECISION_SELECTED
    AND AutoGemmPreCompile_TRANS_SELECTED
    AND AutoGemmPreCompile_TILE_SELECTED)
  # valid selection
  set( AutoGemmPreCompile_ACTIVE ON)
  MESSAGE( STATUS "AutoGemm-PreCompile: selected kernels will be pre-compiled." )
elseif(NOT AutoGemmPreCompile_PRECISION_SELECTED
    AND NOT AutoGemmPreCompile_TRANS_SELECTED
    AND NOT AutoGemmPreCompile_TILE_SELECTED)
  MESSAGE( STATUS "AutoGemm-PreCompile: no kernels to be pre-compiled." )
else()
  MESSAGE( SEND_ERROR "AutoGemm-PreCompile: To pre-compile gemm kernels, select at lease one option from each of AutoGemmPreCompile_PRECISION_*, AutoGemmPreCompile_TRANS_*, AutoGemmPreCompile_TILE_*; otherwise, unselect all AutoGemmPreCompile_* options to not pre-compile any gemm kernels." )
endif()

# build commandline argument for AutoGemm
set( AGPC_ARGS )
set( AGPC_ARGS ${AGPC_ARGS} --output ${CMAKE_BINARY_DIR}/include )

if ( AutoGemmPreCompile_ACTIVE )
  # precisions
  set(AGPC_ARGS ${AGPC_ARGS} --precisions )
  if (AutoGemmPreCompile_PRECISION_SGEMM)
    set(AGPC_ARGS ${AGPC_ARGS} s )
  endif()
  if (AutoGemmPreCompile_PRECISION_DGEMM)
    set(AGPC_ARGS ${AGPC_ARGS} d )
  endif()
  if (AutoGemmPreCompile_PRECISION_CGEMM)
    set(AGPC_ARGS ${AGPC_ARGS} c )
  endif()
  if (AutoGemmPreCompile_PRECISION_ZGEMM)
    set(AGPC_ARGS ${AGPC_ARGS} z )
  endif()

  # orders
  set(AGPC_ARGS ${AGPC_ARGS} --orders clblasColumnMajor )

  # transposes
  set(AGPC_ARGS ${AGPC_ARGS} --transposes )
  if (AutoGemmPreCompile_TRANS_NN)
    set(AGPC_ARGS ${AGPC_ARGS} NN )
  endif()
  if (AutoGemmPreCompile_TRANS_NT)
    set(AGPC_ARGS ${AGPC_ARGS} NT )
  endif()
  if (AutoGemmPreCompile_TRANS_NC)
    set(AGPC_ARGS ${AGPC_ARGS} NC )
  endif()
  if (AutoGemmPreCompile_TRANS_TN)
    set(AGPC_ARGS ${AGPC_ARGS} TN )
  endif()
  if (AutoGemmPreCompile_TRANS_TT)
    set(AGPC_ARGS ${AGPC_ARGS} TT )
  endif()
  if (AutoGemmPreCompile_TRANS_TC)
    set(AGPC_ARGS ${AGPC_ARGS} TC )
  endif()
  if (AutoGemmPreCompile_TRANS_CN)
    set(AGPC_ARGS ${AGPC_ARGS} CN )
  endif()
  if (AutoGemmPreCompile_TRANS_CT)
    set(AGPC_ARGS ${AGPC_ARGS} CT )
  endif()
  if (AutoGemmPreCompile_TRANS_CC)
    set(AGPC_ARGS ${AGPC_ARGS} CC )
  endif()

  # betas
  set(AGPC_ARGS ${AGPC_ARGS} --betas 0 1 )

  # tiles
  set(AGPC_ARGS ${AGPC_ARGS} --tiles )
  if (AutoGemmPreCompile_TILE_96x96)
    set(AGPC_ARGS ${AGPC_ARGS} 96x96 )
  endif()
  if (AutoGemmPreCompile_TILE_80x80)
    set(AGPC_ARGS ${AGPC_ARGS} 80x80 )
  endif()
  if (AutoGemmPreCompile_TILE_64x64)
    set(AGPC_ARGS ${AGPC_ARGS} 64x64 )
  endif()
  if (AutoGemmPreCompile_TILE_48x48)
    set(AGPC_ARGS ${AGPC_ARGS} 48x48 )
  endif()
  if (AutoGemmPreCompile_TILE_32x32)
    set(AGPC_ARGS ${AGPC_ARGS} 32x32 )
  endif()
  if (AutoGemmPreCompile_TILE_16x16)
    set(AGPC_ARGS ${AGPC_ARGS} 16x16 )
  endif()
endif()
MESSAGE( STATUS "AutoGemmPreCompile: python KernelsToPreCompile.py ${AGPC_ARGS}" )


################################################################################
# add target for generating pre-compile WhichKernels header
################################################################################
set( AUTOGEMM_PRECOMPILE_HEADER_SRC ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/KernelsToPreCompile.py )
set( AUTOGEMM_PRECOMPILE_HEADER_OUT ${CMAKE_BINARY_DIR}/include/AutoGemmKernelsToPreCompile.h )
add_custom_target( AutoGemmPreCompile_GenerateHeader
  #DEPENDS ${AUTOGEMM_PRECOMPILE_HEADER_OUT} 
  SOURCES ${AUTOGEMM_PRECOMPILE_HEADER_SRC}
  )
add_custom_command(
  TARGET AutoGemmPreCompile_GenerateHeader
  #OUTPUT ${AUTOGEMM_PRECOMPILE_HEADER_OUT}
  #MESSAGE( STATUS "python ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/KernelsToPreCompile.py ${AGPC_ARGS}" )
  COMMAND echo python ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/KernelsToPreCompile.py ${AGPC_ARGS}
  COMMAND python ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/KernelsToPreCompile.py ${AGPC_ARGS}
  DEPENDS ${AUTOGEMM_PRECOMPILE_HEADER_SRC}
)
set_property( TARGET AutoGemmPreCompile_GenerateHeader PROPERTY FOLDER "AutoGemm")


################################################################################
# add target for compiling pre-compile executable
################################################################################
add_executable(AutoGemmPreCompileKernels ${AUTOGEMM_PRECOMPILE_SRC} ${AUTO_GEMM_PRECOMPILE_HEADER_OUT})
add_dependencies(AutoGemmPreCompileKernels AutoGemmPreCompile_GenerateHeader)
target_link_libraries(AutoGemmPreCompileKernels ${OPENCL_LIBRARIES})
set_property( TARGET AutoGemmPreCompileKernels PROPERTY FOLDER "AutoGemm")


################################################################################
# add target for running pre-compile executable
################################################################################
set( AUTOGEMM_PRECOMPILE_HEADER
  ${AUTOGEMM_BINARY_DIR}/include/AutoGemmIncludes/AutoGemmKernelBinaryIncludes.h )
add_custom_target( AutoGemmPreCompile_Run
  #DEPENDS AutoGemmPreCompileKernels
  SOURCES ${AUTOGEMM_PRECOMPILE_HEADER}
)
add_custom_command(
  OUTPUT ${AUTOGEMM_PRECOMPILE_HEADER}
  COMMAND AutoGemmPreCompileKernels
  DEPENDS AutoGemmPreCompileKernels
)
set_property( TARGET AutoGemmPreCompile_Run PROPERTY FOLDER "AutoGemm")


################################################################################
# add target for running pre-compile executable
################################################################################
add_custom_target( AutoGemmHeaderGeneration
  #DEPENDS ${AUTOGEMM_HEADERS} 
  SOURCES ${AUTOGEMM_SRC}
)
add_custom_command(
  OUTPUT ${AUTOGEMM_HEADERS}
  COMMAND python ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/AutoGemm.py ${CMAKE_BINARY_DIR}/include
  DEPENDS ${AUTOGEMM_SRC}
)
set_property( TARGET AutoGemmHeaderGeneration PROPERTY FOLDER "AutoGemm")



include_directories(
    ${OPENCL_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/library/tools/ktest/naive
    ${CMAKE_BINARY_DIR}/include
    .
)

add_executable(TestAutoGemm ${AUTOGEMM_TEST_SRC})
add_dependencies(TestAutoGemm AutoGemmHeaderGeneration)
target_link_libraries(TestAutoGemm ${OPENCL_LIBRARIES})
set_property( TARGET TestAutoGemm PROPERTY FOLDER "AutoGemm")

add_executable(ProfileAutoGemm ${AUTOGEMM_PROFILER_SRC})
add_dependencies(ProfileAutoGemm AutoGemmHeaderGeneration)
target_link_libraries(ProfileAutoGemm ${OPENCL_LIBRARIES})
set_property( TARGET ProfileAutoGemm PROPERTY FOLDER "AutoGemm")

source_group( AutoGemmScripts FILES ${AUTOGEMM_SRC} ${AUTOGEMM_PRECOMPILE_HEADER_SRC} )
