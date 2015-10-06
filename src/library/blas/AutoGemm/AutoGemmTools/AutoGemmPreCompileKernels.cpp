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

#include <assert.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <cstring>

#ifdef __GNUC__
// Linux
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#else
// Windows
#include <Windows.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#define stat _stat
#endif

#include "CL/opencl.h"
//#include "naive_blas.cpp"
//using namespace NaiveBlas;
#include "AutoGemmIncludes/AutoGemmKernelsToPreCompile.h"
#include "AutoGemmIncludes/AutoGemmKernelSelectionSpecific.h"
#include "UserGemmKernelSources/UserGemmClKernels.h"
#include "UserGemmKernelSources/UserGemmKernelSourceIncludes.h"

unsigned int totalKernelsToCompile;
unsigned int numKernelsCompiled;
char *path;
std::ofstream includeFile;

//std::clock_t clockStart;
unsigned long long clockStart;
unsigned long long clockFrequency;



/******************************************************************************
 * Check OpenCL Errors
 *****************************************************************************/
#define CL_CHECK(STATUS) \
  if(STATUS != CL_SUCCESS) { \
    printf("OpenCL error %i on line %u\n", STATUS, __LINE__); \
    assert(false); \
  }

/******************************************************************************
 * Get AMD Platform
 *****************************************************************************/
cl_int getAMDPlatform(cl_platform_id *platform) {
  *platform = NULL;
  cl_int status = CL_SUCCESS;

  // get num platforms
  cl_uint numPlatforms;
  status = clGetPlatformIDs(0, NULL, &numPlatforms);
  if(status != CL_SUCCESS) {
    std::cout << "Error: clGetPlatformIDs failed. Error code: " << status << std::endl;
    return status;
  }

  if (numPlatforms > 0) {
    // Get selected platform
    cl_platform_id* platforms = new cl_platform_id[numPlatforms];
    status = clGetPlatformIDs(numPlatforms, platforms, NULL);
    if(status != CL_SUCCESS) {
      std::cout<<"Error: clGetPlatformIDs failed. Error code : " << status << std::endl;
      return status;
    }

    // Print all platforms
    for (unsigned i = 0; i < numPlatforms; ++i) {
      char pbuf[100];
      status = clGetPlatformInfo(platforms[i],
        CL_PLATFORM_VENDOR,
        sizeof(pbuf),
        pbuf,
        NULL);

      if(status != CL_SUCCESS) {
        std::cout<<"Error: clGetPlatformInfo failed. Error code : " << status << std::endl;
        return status;
      }

      //std::cout << "Platform " << i << " : " << pbuf << std::endl;
    }

    // Get AMD platform
    for (unsigned i = 0; i < numPlatforms; ++i) {
      char pbuf[100];
      status = clGetPlatformInfo(platforms[i],
        CL_PLATFORM_VENDOR,
        sizeof(pbuf),
        pbuf,
        NULL);

      if(status != CL_SUCCESS) {
        std::cout << "Error: clGetPlatformInfo failed. Error code: " << status << std::endl;
        return status;
      }

      *platform = platforms[i];
      if (!strcmp(pbuf, "Advanced Micro Devices, Inc.")) {
        break;
      }
    }

    // verify AMD platform
    char pbuf[100];
    status = clGetPlatformInfo(*platform,
      CL_PLATFORM_VENDOR,
      sizeof(pbuf),
      pbuf,
      NULL);

    if(status != CL_SUCCESS) {
      std::cout<<"Error: clGetPlatformInfo failed. Error code: " << status << std::endl;
      return status;
    }
    if (strcmp(pbuf, "Advanced Micro Devices, Inc.")) {
      std::cout << "AMD platform not found" << std::endl;
      return CL_INVALID_PLATFORM; 
    }

  } else {
      std::cout << "No OpenCL platforms found." << std::endl;
      return CL_INVALID_PLATFORM;
  }

  return status;
}


/******************************************************************************
 * Precision -> char
 *****************************************************************************/
template<typename Precision> char getPrecisionChar();
template<> char getPrecisionChar<float>(){ return 's'; }
template<> char getPrecisionChar<double>(){ return 'd'; }
template<> char getPrecisionChar<FloatComplex>(){ return 'c'; }
template<> char getPrecisionChar<DoubleComplex>(){ return 'z'; }


/******************************************************************************
 * get kernel name
 *****************************************************************************/
template<typename Precision>
int getKernelName(
  char **kernelName,
  clblasOrder order,
  clblasTranspose transA,
  clblasTranspose transB,
  bool beta,
  unsigned int macroTileNumRows,
  unsigned int macroTileNumCols,
  unsigned int unroll,
  bool extraRow,
  bool extraCol,
  char *appendstring)
{
  int n = sprintf( *kernelName,
    "%cgemm_%s_%s%s_B%i_M%c%03u_N%c%03u_KX%02u",
    getPrecisionChar<Precision>(),
    order==clblasColumnMajor ? "Col" : "Row",
    transA==clblasNoTrans ? "N" : transA==clblasTrans ? "T" : "C",
    transB==clblasNoTrans ? "N" : transB==clblasTrans ? "T" : "C",
    beta ? 1 : 0,
    extraRow ? 'L' : 'X',
    macroTileNumRows,
    extraCol ? 'L' : 'X',
    macroTileNumCols,
    unroll );
  int n2 = 0;
  if (appendstring != NULL)
  {
	  n2 = sprintf((*kernelName) + n, appendstring);
  }
  return n2 + n;
}

template<typename Precision>
int getStringName(
  char **stringName,
  clblasOrder order,
  clblasTranspose transA,
  clblasTranspose transB,
  bool beta,
  unsigned int macroTileNumRows,
  unsigned int macroTileNumCols,
  unsigned int unroll,
  bool extraRow,
  bool extraCol,
  char *appendstring)
{
  int n = getKernelName<Precision>(stringName, order, transA, transB, beta, macroTileNumRows, macroTileNumCols, unroll, extraRow, extraCol, appendstring);
  int n2 = sprintf( (*stringName)+n, "_bin" );
  return n+n2;
}

template<typename Precision>
int getFileName(
  char **fileName,
  clblasOrder order,
  clblasTranspose transA,
  clblasTranspose transB,
  bool beta,
  unsigned int macroTileNumRows,
  unsigned int macroTileNumCols,
  unsigned int unroll,
  bool extraRow,
  bool extraCol,
  char *appendstring)
{
  int n = getKernelName<Precision>(fileName, order, transA, transB, beta, macroTileNumRows, macroTileNumCols, unroll, extraRow, extraCol, appendstring);
  int n2 = sprintf( (*fileName)+n, "_bin.cpp" );
  return n+n2;
}

template<typename Precision>
int getPreprocessorName(
  char **preprocessorName,
  clblasOrder order,
  clblasTranspose transA,
  clblasTranspose transB,
  bool beta,
  unsigned int macroTileNumRows,
  unsigned int macroTileNumCols,
  unsigned int unroll,
  bool extraRow,
  bool extraCol,
  char *appendstring)
{
  char kernelNameArray[64];
  char *kernelName = kernelNameArray;
  int n = getKernelName<Precision>(&kernelName, order, transA, transB, beta, macroTileNumRows, macroTileNumCols, unroll, extraRow, extraCol, appendstring);
  for ( int i = 0; i < n; i++) {
    kernelName[i] = toupper(kernelName[i]);
  }
  int n2 = sprintf( *preprocessorName, "KERNEL_%s_BIN_CPP", kernelName );
  return n2;
}


/******************************************************************************
 * get kernel binary from source
 *****************************************************************************/
cl_int getKernelBinaryFromSource(
  cl_context context,
  const char *source,
  const char *buildOptions,
  char **binary,
  size_t *binarySize)
{
  cl_int status = CL_SUCCESS;

  // create program
  cl_program program = clCreateProgramWithSource(context,1, &source, NULL, &status);
  CL_CHECK(status);

  cl_uint numDevicesInContext;
  status = clGetContextInfo(context, CL_CONTEXT_NUM_DEVICES, sizeof(cl_uint), &numDevicesInContext, NULL);
  CL_CHECK(status);
  
  // get devices
  //printf("Devices: %u\n", numDevicesInContext);
  cl_device_id* devices = new cl_device_id[numDevicesInContext];
  clGetContextInfo(context, CL_CONTEXT_DEVICES, numDevicesInContext*sizeof(cl_device_id), devices, NULL);
  CL_CHECK(status);

  // choose device 0
  cl_device_id device = devices[0];

  // build program for device
  status = clBuildProgram(program, 1, &device, buildOptions, NULL, NULL);


  // print build failure
  if (status != CL_SUCCESS) {
    printf("clBuildProgram Failed\n");
    printf("status = %d\n", status);

    size_t len=0;
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &len);
    char* buildLog = new char[len];

    printf("Error: Failed to build program executable!\n");
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, len*sizeof(char), buildLog, 0);
    printf("\nBuild Log:\n\n");
    printf("%s\n", buildLog);
    printf("\n\nKernel String:\n\n");
    printf("%s\n", source);

    binary[0] = 0;
    *binarySize = 0;
    return status;
  }


  // get binary from program
  status = clGetProgramInfo(program, CL_PROGRAM_BINARY_SIZES, sizeof(size_t), binarySize, NULL);
  //printf("BinarySize: %llu\n", *binarySize);
  binary[0] = new char[*binarySize];
  //for (int i = 0; i < *binarySize; i++) binary[0][i] = 512;
  
  //size_t size = 2;
  //status = -1;
  //for (int i = 0; status; i++) {
  //  printf("size=%i\n", i);
    status = clGetProgramInfo(program, CL_PROGRAM_BINARIES, 8 /*?*/, binary, NULL);
  //}
  CL_CHECK(status);

  //for (int i = 0; i < *binarySize; i++) {
  //  std::cout << std::setw(3) << (int)binary[0][i] << ",";
  //}
  //printf("binary[0][0] = %p\n", binary[0][0]);
  //printf("binary[0]    = %p\n", binary[0]);
  //printf("binary       = %p\n", binary);
  //printf("&binary      = %p\n", &binary);

  return CL_SUCCESS;
}


/******************************************************************************
 * write binary to stream
 *****************************************************************************/
void writeBinaryToStream(std::ostream & out, char *binary, size_t binarySize) {
  for(int i = 0; i < binarySize; i++) {

    out << std::setw(4) << (int) binary[i];
    
    if(i < binarySize-1) {
      out << ",";
    }
    if((i+1)%16 == 0) {
      out << std::endl;
    }
  }
  out << std::endl;
}


/******************************************************************************
 * Pre-compile kernels within parameter group and write to file
 *****************************************************************************/
template<typename Precision>
void compileKernelAndWriteToFile(
  cl_context context,
  clblasOrder order,
  clblasTranspose transA,
  clblasTranspose transB,
  bool beta,
  unsigned int macroTileNumRows,
  unsigned int macroTileNumCols,
  unsigned int unroll,
  bool extraRow,
  bool extraCol,
  const char *source,
  const char *buildOptions,
  char* appendString)
{
  // get kernel name
  char stringNameArray[64];
  char fileNameArray[64];
  char preprocessorNameArray[64];
  char *stringName = &stringNameArray[0];
  char *fileName = &fileNameArray[0];
  char *preprocessorName = &preprocessorNameArray[0];
  int stringNameLength = getStringName<Precision>(&stringName, order, transA, transB, beta, macroTileNumRows, macroTileNumCols, unroll, extraRow, extraCol, appendString);
  int fileNameLength = getFileName<Precision>(&fileName, order, transA, transB, beta, macroTileNumRows, macroTileNumCols, unroll, extraRow, extraCol, appendString);
  int preprocessorNameLength = getPreprocessorName<Precision>(&preprocessorName, order, transA, transB, beta, macroTileNumRows, macroTileNumCols, unroll, extraRow, extraCol, appendString);
  
  // get kernel binary
  char **kernelBinary = new char*[1];
  kernelBinary[0] = 0;
  size_t kernelBinarySize;
  cl_int status = getKernelBinaryFromSource(context, source, buildOptions, kernelBinary, &kernelBinarySize);
  
  if (status == CL_SUCCESS) {
    // write binary to file
    std::ofstream kernelFile;
    std::string fullFilePath;
    fullFilePath += path;
    fullFilePath += fileName;
    kernelFile.open(fullFilePath.c_str(), std::ios::out);
    kernelFile << "/* AutoGemm Pre-Compiled kernel binary */" << std::endl << std::endl;
    kernelFile << "#define " << preprocessorName << std::endl << std::endl;
    
    kernelFile << "char " << stringName << "Array[" << kernelBinarySize << "] = {" << std::endl;
    //kernelFile << "unsigned char *" << stringName << " = {" << std::endl;
    //kernelFile << "unsigned char " << stringName << "[] = {" << std::endl;
    
    writeBinaryToStream( kernelFile, *kernelBinary, kernelBinarySize );
    kernelFile << "};" << std::endl;
    kernelFile << "unsigned char *" << stringName << " = " << "reinterpret_cast<unsigned char *>(" << stringName << "Array);" << std::endl;
    kernelFile << "size_t " << stringName << "Size = " << kernelBinarySize << ";" << std::endl;
    kernelFile.close();

    // add file to include
    includeFile << "#include \"AutoGemmKernelBinaries/" << fileName << "\"" << std::endl;
  }
  if (kernelBinary[0])
    delete[] kernelBinary[0];
  delete[] kernelBinary;

  // report kernel compiled
  numKernelsCompiled++;

  // how much time left
  unsigned long long clockCurrent;
  #if defined( _WIN32 )
	::QueryPerformanceCounter( reinterpret_cast<LARGE_INTEGER*>( &clockCurrent ) );
#else
	struct timeval s;
	gettimeofday(&s, 0);
	clockCurrent = (unsigned long long)s.tv_sec * 1000000 + (unsigned long long)s.tv_usec;
#endif



  double elapsedTimeSec = ((double) clockCurrent - clockStart) / clockFrequency;
  double timePerKernel = elapsedTimeSec / numKernelsCompiled;
  double timeRemaining = timePerKernel * (totalKernelsToCompile - numKernelsCompiled);
  //printf("AutoGemm-PreCompile[%3u/%3u]: %s %7u bytes ( %.0f sec remaining)\n", numKernelsCompiled, totalKernelsToCompile, stringName, kernelBinarySize, timeRemaining);
  std::cout << "AutoGemm-PreCompile[" << std::setw(3) << numKernelsCompiled << "/" << std::setw(3) << totalKernelsToCompile << "]: " << stringName << std::setw(4) << kernelBinarySize/1024 << " kB (" << std::setw(4) << (int) timeRemaining << " sec remaining)" << std::endl;
}


/******************************************************************************
 * compile kernels within parameter group and write to file
 *****************************************************************************/
template<typename Precision>
cl_int compileKernelGroupAndWriteToFile(
  cl_context context,
  clblasOrder order,
  clblasTranspose transA,
  clblasTranspose transB,
  bool beta,
  unsigned int macroTileNumRows,
  unsigned int macroTileNumCols,
  unsigned int unroll )
{
  const char *tileKernelSource;
  const char *rowKernelSource;
  const char *colKernelSource;
  const char *cornerKernelSource;
  const char *sourceBuildOptions;
  const unsigned char *tileKernelBinary;
  const unsigned char *rowKernelBinary;
  const unsigned char *colKernelBinary;
  const unsigned char *cornerKernelBinary;
  size_t *tileKernelBinarySize;
  size_t *rowKernelBinarySize;
  size_t *colKernelBinarySize;
  size_t *cornerKernelBinarySize;
  const char *binaryBuildOptions;
  cl_kernel *tileClKernel;
  cl_kernel *rowClKernel;
  cl_kernel *colClKernel;
  cl_kernel *cornerClKernel;
  unsigned int workGroupNumRows;
  unsigned int workGroupNumCols;
  unsigned int microTileNumRows;
  unsigned int microTileNumCols;
  bool kernelFound = gemmSelectKernelSpecific<Precision>(
      order,
      transA,
      transB,
      beta,
      macroTileNumRows,
      macroTileNumCols,
      unroll,
      &tileKernelSource,
      &rowKernelSource,
      &colKernelSource,
      &cornerKernelSource,
      &sourceBuildOptions,
      &tileKernelBinary,
      &rowKernelBinary,
      &colKernelBinary,
      &cornerKernelBinary,
      &tileKernelBinarySize,
      &rowKernelBinarySize,
      &colKernelBinarySize,
      &cornerKernelBinarySize,
      &binaryBuildOptions,
      &tileClKernel,
      &rowClKernel,
      &colClKernel,
      &cornerClKernel,
      &workGroupNumRows,
      &workGroupNumCols,
      &microTileNumRows,
      &microTileNumCols );

  if (!kernelFound) {
    totalKernelsToCompile -= 4;
    char stringNameArray[64];
    char *stringName = &stringNameArray[0];
    int stringNameLength = getStringName<Precision>( &stringName, order, transA, transB, beta, macroTileNumRows, macroTileNumCols, unroll, 0, 0, NULL);
    printf("AutoGemm-PreCompile: %s not found; skipping.\n", stringName );
    return 0;
  }

  compileKernelAndWriteToFile<Precision>(
      context,
      order,
      transA,
      transB,
      beta,
      macroTileNumRows,
      macroTileNumCols,
      unroll,
      false, // extra row
      false, // extra col
      tileKernelSource,
      sourceBuildOptions,
	  NULL);
    
    compileKernelAndWriteToFile<Precision>(
        context,
        order,
        transA,
        transB,
        beta,
        macroTileNumRows,
        macroTileNumCols,
        unroll,
        true, // extra row
        false, // extra col
        rowKernelSource,
        sourceBuildOptions,
		NULL);

    compileKernelAndWriteToFile<Precision>(
        context,
        order,
        transA,
        transB,
        beta,
        macroTileNumRows,
        macroTileNumCols,
        unroll,
        false, // extra row
        true, // extra col
        colKernelSource,
        sourceBuildOptions,
		NULL);

    compileKernelAndWriteToFile<Precision>(
        context,
        order,
        transA,
        transB,
        beta,
        macroTileNumRows,
        macroTileNumCols,
        unroll,
        true, // extra row
        true, // extra col
        cornerKernelSource,
        sourceBuildOptions,
		NULL);

  return 1;
}

/******************************************************************************
 * Main
 *****************************************************************************/
int main( int argc, char *argv[] ) {

  if (argc < 2 ) {
    printf("AutoGemmPreCompileKernels requires output path as argument\n");
    exit(-1);
  }

  size_t pathLength = std::strlen(argv[1]);
  path = new char[pathLength+64];
  sprintf(path, "%s/include/AutoGemmKernelBinaries/", argv[1]);
  //printf("AutoGemm-PreCompile: writing to %s\n", path);

  std::string fullIncludeFilePath;
  fullIncludeFilePath += path;
  fullIncludeFilePath += "AutoGemmKernelBinariesPreCompiled.h";
  includeFile.open(fullIncludeFilePath.c_str(), std::ios::out);
  const char *includeFileHeader =
    "/*****************************************************************************\n"
    " * this file auto-generated by AutoGemmPreCompileKernels\n"
    " ****************************************************************************/\n\n";
  includeFile << includeFileHeader;

  // get AMD platform
  cl_platform_id platform;
  cl_int status = getAMDPlatform( &platform );
  CL_CHECK(status);

  cl_uint numDevices;
  status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
  CL_CHECK(status);
  
  // get all gpu devices
  //printf("NumDevicesInPlatform: %u\n", numDevices);
  cl_device_id* devices = new cl_device_id[numDevices];
  clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, numDevices, devices, NULL);
  CL_CHECK(status);

  // choose device 0
  cl_device_id device = devices[0];

  // create context
  cl_context_properties cps[3] = {
    CL_CONTEXT_PLATFORM,
    (cl_context_properties)platform,
    0
  };
  cl_context context = clCreateContext(
    cps,
    1, // device
    &device,
    NULL,
    NULL,
    &status);
  CL_CHECK(status);

  cl_uint numDevicesInContext;
  status = clGetContextInfo(context, CL_CONTEXT_NUM_DEVICES, sizeof(cl_uint), &numDevicesInContext, NULL);
  //printf("NumDevicesInContext: %u\n", numDevicesInContext);
  CL_CHECK(status);

  
  clblasOrder order;
  clblasTranspose transA;
  clblasTranspose transB;
  bool beta;
  unsigned int macroTileNumRows;
  unsigned int macroTileNumCols;
  unsigned int unroll;

  // timer
  clockStart = clock();
  
#if defined( _WIN32 )
	//	OS call to get ticks per second2
	::QueryPerformanceFrequency( reinterpret_cast<LARGE_INTEGER*>( &clockFrequency ) );
#else
	clockFrequency = 1000000;
#endif



#if defined( _WIN32 )
	::QueryPerformanceCounter( reinterpret_cast<LARGE_INTEGER*>( &clockStart ) );
#else
	struct timeval s;
	gettimeofday(&s, 0);
	clockStart = (unsigned long long)s.tv_sec * 1000000 + (unsigned long long)s.tv_usec;
#endif
	const int specialKernelCount = user_kernel_count;

	totalKernelsToCompile = gemmPreCompileNum;
	totalKernelsToCompile *= 4;
	totalKernelsToCompile += specialKernelCount;
	numKernelsCompiled = 0;
    //precompile user defined kernels
    //all of the user defined special kernels will be precompiled if precompile is active
    //there are 7 user defined special kernels refer to UserGemmKernelIncludes.h
	const char *tileKernelSourceArray[specialKernelCount] =
	{
		sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_src,
		sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_src,
		sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_src,
		sgemm_Col_NT_B1_MX128_NX128_KX16_src,
		sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_src,
		sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_src,
		sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_src
	};
	const unsigned char *tileKernelBinaryArray[specialKernelCount] =
	{
		sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_bin,
		sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_bin,
		sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_bin,
		sgemm_Col_NT_B1_MX128_NX128_KX16_bin,
		sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_bin,
		sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_bin,
		sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_bin
	};
	size_t tileKernelBinarySizeArray[specialKernelCount] =
	{
		sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_binSize,
		sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_binSize,
		sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_binSize,
		sgemm_Col_NT_B1_MX128_NX128_KX16_binSize,
		sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_binSize,
		sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_binSize,
		sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_binSize
	};
	unsigned int  workGroupNumRowsArray[specialKernelCount] =
	{
		sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_workGroupNumRows,
		sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_workGroupNumRows,
		sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_workGroupNumRows,
		sgemm_Col_NT_B1_MX128_NX128_KX16_workGroupNumRows,
		sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_workGroupNumRows,
		sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_workGroupNumRows,
		sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_workGroupNumRows
	};
	unsigned int  workGroupNumColsArray[specialKernelCount] =
	{
		sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_workGroupNumCols,
		sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_workGroupNumCols,
		sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_workGroupNumCols,
		sgemm_Col_NT_B1_MX128_NX128_KX16_workGroupNumCols,
		sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_workGroupNumCols,
		sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_workGroupNumCols,
		sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_workGroupNumCols
	};
	unsigned int  microTileNumRowsArray[specialKernelCount] =
	{
		sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_microTileNumRows,
		sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_microTileNumRows,
		sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_microTileNumRows,
		sgemm_Col_NT_B1_MX128_NX128_KX16_microTileNumRows,
		sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_microTileNumRows,
		sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_microTileNumRows,
		sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_microTileNumRows
	};
	unsigned int  microTileNumColsArray[specialKernelCount] =
	{
		sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_microTileNumCols,
		sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_microTileNumCols,
		sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_microTileNumCols,
		sgemm_Col_NT_B1_MX128_NX128_KX16_microTileNumCols,
		sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_microTileNumCols,
		sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_microTileNumCols,
		sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_microTileNumCols
	};
	unsigned int  unrollArray[specialKernelCount] =
	{
		sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_unroll,
		sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_unroll,
		sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_unroll,
		sgemm_Col_NT_B1_MX128_NX128_KX16_unroll,
		sgemm_Col_NN_B1_MX032_NX032_KX16_BRANCH_unroll,
		sgemm_Col_NT_B1_MX032_NX032_KX16_BRANCH_unroll,
		sgemm_Col_TN_B1_MX032_NX032_KX16_BRANCH_unroll
	};
	char *appendStringArray[specialKernelCount] =
	{
		"_ROW",
		"_COLUMN",
		"_SINGLE",
		NULL,
		"_BRANCH",
		"_BRANCH",
		"_BRANCH"
	};
	clblasTranspose transA_Array[specialKernelCount] =
	{
		clblasNoTrans,
		clblasNoTrans,
		clblasNoTrans,
		clblasNoTrans,
		clblasNoTrans,
		clblasNoTrans,
		clblasTrans
	};
	clblasTranspose transB_Array[specialKernelCount] =
	{
		clblasTrans,
		clblasTrans,
		clblasTrans,
		clblasTrans,
		clblasNoTrans,
		clblasTrans,
		clblasNoTrans
	};
	
  for (int i = 0; i < specialKernelCount; i++)
  {
	  const char *tileKernelSource;
	  const unsigned char *tileKernelBinary;
	  size_t tileKernelBinarySize;
	  const char *binaryBuildOptions;
	  //cl_kernel *tileClKernel;
	  unsigned int workGroupNumRows;
	  unsigned int workGroupNumCols;
	  unsigned int unroll;

	  tileKernelSource = tileKernelSourceArray[i];
	  tileKernelBinary = tileKernelBinaryArray[i];
	  tileKernelBinarySize = tileKernelBinarySizeArray[i];
	  binaryBuildOptions = User_binBuildOptions;
	  workGroupNumRows = workGroupNumRowsArray[i];
	  workGroupNumCols = workGroupNumColsArray[i];
	  macroTileNumRows = microTileNumRowsArray[i] * workGroupNumRowsArray[i];
	  macroTileNumCols = microTileNumColsArray[i] * workGroupNumColsArray[i];
	  unroll = unrollArray[i];
	  beta = 1.0;
	  char *appendString = appendStringArray[i];

  
	  compileKernelAndWriteToFile<float>(
		  context,
		  clblasColumnMajor,
		  transA_Array[i],
		  transB_Array[i],
		  beta,
		  macroTileNumRows,
		  macroTileNumCols,
		  unroll,
		  false, // extra row
		  false, // extra col
		  tileKernelSource,
		  binaryBuildOptions,
		  appendString);
        
  }
  
  // for each kernel to be pre-compiled
  
  //totalKernelsToCompile = gemmPreCompileNum;
  //totalKernelsToCompile *= 4;
  //numKernelsCompiled = 0;
  
  for (unsigned int i = 0; i < gemmPreCompileNum ; i++) {
    // unload parameters
    // idx 0 is precision
    order = gemmPreCompile[i][1]==1 ? clblasColumnMajor : clblasRowMajor;
    transA = gemmPreCompile[i][2]==0 ? clblasNoTrans : gemmPreCompile[i][2]==1 ? clblasTrans : clblasConjTrans;
    transB = gemmPreCompile[i][3]==0 ? clblasNoTrans : gemmPreCompile[i][3]==1 ? clblasTrans : clblasConjTrans;
    beta = gemmPreCompile[i][4]==1;
    macroTileNumRows = gemmPreCompile[i][5];
    macroTileNumCols = gemmPreCompile[i][6];
    unroll = gemmPreCompile[i][7];

    if (gemmPreCompile[i][0] == 0) { // sgemm
      compileKernelGroupAndWriteToFile<float>(
        context,
        order,
        transA,
        transB,
        beta,
        macroTileNumRows,
        macroTileNumCols,
        unroll
        );
    } else if (gemmPreCompile[i][0] == 1) { // dgemm
      compileKernelGroupAndWriteToFile<double>(
        context,
        order,
        transA,
        transB,
        beta,
        macroTileNumRows,
        macroTileNumCols,
        unroll
        );
    } else if (gemmPreCompile[i][0] == 2) { // cgemm
      compileKernelGroupAndWriteToFile<FloatComplex>(
        context,
        order,
        transA,
        transB,
        beta,
        macroTileNumRows,
        macroTileNumCols,
        unroll
        );
    } else if (gemmPreCompile[i][0] == 3) { // zgemm
      compileKernelGroupAndWriteToFile<DoubleComplex>(
        context,
        order,
        transA,
        transB,
        beta,
        macroTileNumRows,
        macroTileNumCols,
        unroll
        );
    }
  }// end for
  
  //precompile user defined kernels


  unsigned long long clockCurrent;
#if defined( _WIN32 )
	::QueryPerformanceCounter( reinterpret_cast<LARGE_INTEGER*>( &clockCurrent ) );
#else
	gettimeofday(&s, 0);
	clockCurrent = (unsigned long long)s.tv_sec * 1000000 + (unsigned long long)s.tv_usec;
#endif
  double elapsedTimeSec = ((double)clockCurrent - clockStart) / clockFrequency;
  includeFile.close();
  std::cout << "Total Compile Time: " << elapsedTimeSec << " sec" << std::endl;
  //system("PAUSE");
  return 0;
}

