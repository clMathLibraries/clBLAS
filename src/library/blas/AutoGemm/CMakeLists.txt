set(AUTOGEMM_SRC
    ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/AutoGemm.py
    ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/AutoGemmParameters.py
    ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/Common.py
    ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/Includes.py
    ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/KernelOpenCL.py
    ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/KernelParameters.py
    ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/KernelSelection.py
)
set(AUTOGEMM_OUT
    ${CMAKE_BINARY_DIR}/include/AutoGemmClKernels.h
    ${CMAKE_BINARY_DIR}/include/AutoGemmBinaryBuildOptions.h
    ${CMAKE_BINARY_DIR}/include/AutoGemmBinaryIncludes.h
    ${CMAKE_BINARY_DIR}/include/AutoGemmBinaryNulls.h
    ${CMAKE_BINARY_DIR}/include/AutoGemmKernelSelection.h
    ${CMAKE_BINARY_DIR}/include/AutoGemmKernelSelectionSpecific.h
    ${CMAKE_BINARY_DIR}/include/AutoGemmKernelSourceBuildOptions.h
    ${CMAKE_BINARY_DIR}/include/AutoGemmKernelSourceIncludes.h
)

add_custom_command(
  OUTPUT ${AUTOGEMM_OUT}
  COMMAND
    python ${CMAKE_SOURCE_DIR}/library/blas/AutoGemm/AutoGemm.py ${CMAKE_BINARY_DIR}/include
  DEPENDS ${AUTOGEMM_SRC}
)

add_custom_target( AutoGemmHeaderGeneration
  DEPENDS ${AUTOGEMM_OUT} 
  SOURCES ${AUTOGEMM_SRC}
)

set(AUTOGEMM_TEST_SRC
  AutoGemmTools/TestAutoGemm.cpp
)
set(AUTOGEMM_PROFILER_SRC
  AutoGemmTools/ProfileAutoGemm.cpp
)

include_directories(
    ${OPENCL_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/library/tools/ktest/naive
    ${CMAKE_BINARY_DIR}/include
    .
)

add_executable(TestAutoGemm ${AUTOGEMM_TEST_SRC})
add_executable(ProfileAutoGemm ${AUTOGEMM_PROFILER_SRC})
target_link_libraries(TestAutoGemm ${OPENCL_LIBRARIES})
target_link_libraries(ProfileAutoGemm ${OPENCL_LIBRARIES})

set_property( TARGET AutoGemmHeaderGeneration PROPERTY FOLDER "AutoGemm")
set_property( TARGET TestAutoGemm PROPERTY FOLDER "AutoGemm")
set_property( TARGET ProfileAutoGemm PROPERTY FOLDER "AutoGemm")

source_group( AutoGemmScripts FILES ${AUTOGEMM_SRC} )
