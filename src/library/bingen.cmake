
#set( bingenBinaryDir "${CMAKE_SOURCE_DIR}/library/tools/bingen/staging" )
set (BIN_CL_TEMPLATES_TAHITI
${CLTEMPLATE_PATH}/dgemm_hawai.cl
${CLTEMPLATE_PATH}/dtrsm_gpu.cl
${CLTEMPLATE_PATH}/dgemm_gcn_SmallMatrices.cl
${CLTEMPLATE_PATH}/sgemm_gcn.cl
${CLTEMPLATE_PATH}/sgemm_gcn_SmallMatrices.cl
#sgemm_hawaiiSplitKernel.cl
)

set (BIN_CL_TEMPLATES_HAWAII_CL2
${CLTEMPLATE_PATH}/dgemm_hawaiiSplitKernel.cl
${CLTEMPLATE_PATH}/sgemm_hawaiiSplitKernel.cl
${CLTEMPLATE_PATH}/sgemm_gcn.cl
${CLTEMPLATE_PATH}/zgemm_gcn.cl
${CLTEMPLATE_PATH}/sgemm_gcn_SmallMatrices.cl
${CLTEMPLATE_PATH}/sgemm_gcn_bigMatrices.cl
${CLTEMPLATE_PATH}/sgemm_hawaiiSplit64_32.cl
${CLTEMPLATE_PATH}/dtrsm_gpu192.cl
)


set (BIN_CL_TEMPLATES_BONAIRE_CL
${CLTEMPLATE_PATH}/sgemm_hawaiiSplitKernel.cl
${CLTEMPLATE_PATH}/sgemm_gcn.cl
${CLTEMPLATE_PATH}/sgemm_gcn_SmallMatrices.cl
)


set (BIN_CL_TEMPLATES_HAWAII_CL1
${CLTEMPLATE_PATH}/dgemm_hawai.cl
${CLTEMPLATE_PATH}/dtrsm_gpu.cl
${CLTEMPLATE_PATH}/dgemm_hawaiiChannelConfilct.cl
${CLTEMPLATE_PATH}/dgemm_gcn_SmallMatrices.cl
)

MESSAGE("run bingen")
if(UNIX)
MESSAGE("echo $LD_LIBRARY_PATH: $ENV{LD_LIBRARY_PATH}")
else()
MESSAGE("echo %PATH%: $ENV{PATH}")
endif()

if(OCL_OFFLINE_BUILD_TAHITI_KERNEL)
	if(LOAD_CL_FLAGS)
		if(UNIX)
		  set(ENV{LD_LIBRARY_PATH} "${ENV_PATH}")
		  MESSAGE("LD_LIBRARY_PATH : $ENV{LD_LIBRARY_PATH}")
		else()
		  set(ENV{PATH} "${ENV_PATH}")
		  MESSAGE("PATH : $ENV{PATH}")
		endif()
	string(REPLACE "\\" "" TAHITI_FLAG ${TAHITI_FLAG})
	set(ENV{AMD_OCL_BUILD_OPTIONS_APPEND} "${TAHITI_FLAG}")
	else()
	set(ENV{AMD_OCL_BUILD_OPTIONS_APPEND} "")
	endif()
	MESSAGE("TAHITI AMD_OCL_BUILD_OPTIONS_APPEND FLAGS : $ENV{AMD_OCL_BUILD_OPTIONS_APPEND}")
	MESSAGE("command : ${bingenBinaryDir}/bingen Tahiti ${BIN_CL_TEMPLATES_TAHITI}")
	execute_process(
		COMMAND  ${bingenBinaryDir}/bingen Tahiti ${BIN_CL_TEMPLATES_TAHITI}
		WORKING_DIRECTORY ${bingenBinaryDir}#

		)
else()
	MESSAGE(STATUS "Tahiti kernels will be built at runtime. Bingen not called.")
endif()

if (OCL_OFFLINE_BUILD_HAWAII_KERNEL)
	if(LOAD_CL_FLAGS)
		if(UNIX)
		  set(ENV{LD_LIBRARY_PATH} "${ENV_PATH}")
		  MESSAGE("LD_LIBRARY_PATH : $ENV{LD_LIBRARY_PATH}")
		else()
		  set(ENV{PATH} "${ENV_PATH}")
		  MESSAGE("PATH : $ENV{PATH}")
		endif()
	string(REPLACE "\\" "" HAWAII1_FLAG ${HAWAII1_FLAG})
	set(ENV{AMD_OCL_BUILD_OPTIONS_APPEND} "${HAWAII1_FLAG}")
	else()
	set(ENV{AMD_OCL_BUILD_OPTIONS_APPEND} "")
	endif()
	MESSAGE("HAWAII CL1 AMD_OCL_BUILD_OPTIONS_APPEND FLAGS : $ENV{AMD_OCL_BUILD_OPTIONS_APPEND}")
	MESSAGE("command : ${bingenBinaryDir}/bingen Hawaii ${BIN_CL_TEMPLATES_HAWAII_CL1}")
	execute_process(
		COMMAND  ${bingenBinaryDir}/bingen Hawaii ${BIN_CL_TEMPLATES_HAWAII_CL1}
		WORKING_DIRECTORY ${bingenBinaryDir}#

	)
else()
	MESSAGE(STATUS "Hawaii 1 kernels will be built at runtime. Bingen not called.")
endif()

if (OCL_OFFLINE_BUILD_HAWAII_KERNEL)
	if(LOAD_CL_FLAGS)
		if(UNIX)
		  set(ENV{LD_LIBRARY_PATH} "${ENV_PATH}")
		  MESSAGE("LD_LIBRARY_PATH : $ENV{LD_LIBRARY_PATH}")
		else()
		  set(ENV{PATH} "${ENV_PATH}")
		  MESSAGE("PATH : $ENV{PATH}")
		endif()
	string(REPLACE "\\" "" HAWAII2_FLAG ${HAWAII2_FLAG})
	message("HAWAII2_FLAG = ${HAWAII2_FLAG}")
	set(ENV{AMD_OCL_BUILD_OPTIONS_APPEND} "${HAWAII2_FLAG}")
	else()
	set(ENV{AMD_OCL_BUILD_OPTIONS_APPEND} "")
	endif()
	MESSAGE("HAWAII CL2 AMD_OCL_BUILD_OPTIONS_APPEND FLAGS : $ENV{AMD_OCL_BUILD_OPTIONS_APPEND}")
	MESSAGE("ENV : $ENV{AMD_OCL_BUILD_OPTIONS_APPEND}")
	MESSAGE("command : ${bingenBinaryDir}/bingen Hawaii ${BIN_CL_TEMPLATES_HAWAII_CL2}")
	execute_process(
		COMMAND  ${bingenBinaryDir}/bingen Hawaii ${BIN_CL_TEMPLATES_HAWAII_CL2}
		WORKING_DIRECTORY ${bingenBinaryDir}#
	)
else()
	MESSAGE(STATUS "Hawaii 2 kernels will be built at runtime. Bingen not called.")
endif()

if(OCL_OFFLINE_BUILD_BONAIRE_KERNEL)
	if(LOAD_CL_FLAGS)
		if(UNIX)
		  set(ENV{LD_LIBRARY_PATH} "${ENV_PATH}")
		  MESSAGE("LD_LIBRARY_PATH : $ENV{LD_LIBRARY_PATH}")
		else()
		  set(ENV{PATH} "${ENV_PATH}")
		  MESSAGE("PATH : $ENV{PATH}")
		endif()
	string(REPLACE "\\" "" BONAIRE_FLAG ${BONAIRE_FLAG})
	message("BONAIRE_FLAG = ${BONAIRE_FLAG}")
	set(ENV{AMD_OCL_BUILD_OPTIONS_APPEND} "${BONAIRE_FLAG}")
	else()
	set(ENV{AMD_OCL_BUILD_OPTIONS_APPEND} "")
	endif()
	MESSAGE("BONAIRE CL AMD_OCL_BUILD_OPTIONS_APPEND FLAGS : $ENV{AMD_OCL_BUILD_OPTIONS_APPEND}")
	MESSAGE("command : ${bingenBinaryDir}/bingen Bonaire ${BIN_CL_TEMPLATES_BONAIRE_CL}")
	execute_process(
		COMMAND  ${bingenBinaryDir}/bingen Bonaire ${BIN_CL_TEMPLATES_BONAIRE_CL}
		WORKING_DIRECTORY ${bingenBinaryDir}#

		)
else()
	MESSAGE(STATUS "Bonaire kernels will be built at runtime. Bingen not called.")
endif()
