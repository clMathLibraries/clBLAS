
message(STATUS "inside OCLBinaryGenerator.cmake")
message(STATUS "OCLBinary.cmake SOURCE_DIR=${SOURCE_DIR}")
message(STATUS "OCLBinary.cmake BINARY_DIR=${BINARY_DIR}")

execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri diag_dtrtri_lower_128_16 ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri diag_dtrtri_upper_128_16 ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri diag_dtrtri_upper_192_12 ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_128_16_PART1_L ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_128_16_PART2_L ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_128_16_R ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_128_32_PART1_L ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_128_32_PART1_R ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_128_32_PART2_L ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_128_32_PART2_R ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_128_64_PART1_L ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_128_64_PART1_R ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_128_64_PART2_L ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_128_64_PART2_R ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_128_ABOVE64_PART1_L ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_128_ABOVE64_PART1_R ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_128_ABOVE64_PART2_L ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_128_ABOVE64_PART2_R ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_128_ABOVE64_PART3_L ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_128_ABOVE64_PART3_R ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_192_12_R ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_192_24_PART1_R ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_192_24_PART2_R ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_192_48_PART1_R ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_192_48_PART2_R ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_192_96_PART1_R ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
execute_process(
	COMMAND ${OCLBinaryGeneratorBinaryDir}/OCLBinaryGenerator ${SOURCE_DIR}/library/blas/trtri triple_dgemm_update_192_96_PART2_R ${BINARY_DIR}/include ${OCL_COMPILER_FLAGS}
	)
