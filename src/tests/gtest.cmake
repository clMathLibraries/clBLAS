
option(USE_SYSTEM_GTEST "Use system installed gtest when set to ON, or build gtest locally when set to OFF" OFF)

if(USE_SYSTEM_GTEST)
  if( (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} VERSION_LESS 2.8) )
    message( STATUS "Cmake version 2.8 or greater needed to use GTest" )
  else()
    # This will define GTEST_FOUND
    find_package( GTest )
  endif()
else()
  if(CMAKE_VERSION VERSION_LESS 3.2 AND CMAKE_GENERATOR MATCHES "Ninja")
    message(WARNING "Building GTest with Ninja has known issues with CMake older than 3.2")
  endif()

  include(ExternalProject)

  set(GTEST_LIBRARIES gtest gtest_main)
  # the binary dir must be know before creating the external project in order
  # to pass the byproducts
  set(prefix "${CMAKE_CURRENT_BINARY_DIR}/gtest-external-prefix")
  set(binary_dir "${prefix}/src/gtest-external-build")

  set(byproducts)
  foreach(lib ${GTEST_LIBRARIES})
    set(${lib}_location
      ${binary_dir}/${CMAKE_CFG_INTDIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${lib}${CMAKE_STATIC_LIBRARY_SUFFIX})
    list(APPEND byproducts ${${lib}_location})
  endforeach()

  if( MSVC )
	if( MSVC_VERSION LESS 1800 )  
      set(EXTRA_FLAG "/D_VARIADIC_MAX=10 ")
	else()
	  set(EXTRA_FLAG "")
	endif()
  else()
    set(EXTRA_FLAG "")
  endif()
  
  ExternalProject_Add(
    gtest-external
    URL https://github.com/google/googletest/archive/release-1.7.0.zip
    URL_MD5 ef5e700c8a0f3ee123e2e0209b8b4961
    PREFIX ${prefix}
    BINARY_DIR ${binary_dir}
    CMAKE_CACHE_ARGS
      -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
      -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
      -DCMAKE_CXX_FLAGS_DEBUG:STRING=${EXTRA_FLAG}${CMAKE_CXX_FLAGS_DEBUG}
      -DCMAKE_CXX_FLAGS_MINSIZEREL:STRING=${EXTRA_FLAG}${CMAKE_CXX_FLAGS_MINSIZEREL}
      -DCMAKE_CXX_FLAGS_RELEASE:STRING=${EXTRA_FLAG}${CMAKE_CXX_FLAGS_RELEASE}
      -DCMAKE_CXX_FLAGS_RELWITHDEBINFO:STRING=${EXTRA_FLAG}${CMAKE_CXX_FLAGS_RELWITHDEBINFO}
      -DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}
      -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
      -DCMAKE_C_FLAGS_DEBUG:STRING=${CMAKE_C_FLAGS_DEBUG}
      -DCMAKE_C_FLAGS_MINSIZEREL:STRING=${CMAKE_C_FLAGS_MINSIZEREL}
      -DCMAKE_C_FLAGS_RELEASE:STRING=${CMAKE_C_FLAGS_RELEASE}
      -DCMAKE_C_FLAGS_RELWITHDEBINFO:STRING=${CMAKE_C_FLAGS_RELWITHDEBINFO}
      -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
      -Dgtest_force_shared_crt:BOOL=ON
    BUILD_BYPRODUCTS ${byproducts}
    INSTALL_COMMAND "")

  foreach(lib ${GTEST_LIBRARIES})
    add_library(${lib} IMPORTED STATIC)
    add_dependencies(${lib} gtest-external)
    set_target_properties(${lib} PROPERTIES IMPORTED_LOCATION ${${lib}_location})
  endforeach()

  ExternalProject_Get_Property(gtest-external source_dir)
  set(GTEST_INCLUDE_DIRS ${source_dir}/include)
  set(GTEST_FOUND ON)
endif()

# Hack to get googletest v1.6 to work with vs2012
if( MSVC11 )
  add_definitions( "/D_VARIADIC_MAX=10" )
endif( )
