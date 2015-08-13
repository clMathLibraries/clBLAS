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
  DEPENDS ${AUTO_GEMM_SRC}
)

add_custom_target( AutoGemm
  DEPENDS ${AUTOGEMM_OUT} 
  SOURCES ${AUTO_GEMM_SRC}
)

#add_library( AutoGemm
#  SOURCES ${AUTO_GEMM_SRC}
#)
#add_dependencies( AutoGemm ${AUTOGEMM_OUT} )

#source_group(AutoGemm\\source FILES ${AUTO_GEMM_SRC} )
