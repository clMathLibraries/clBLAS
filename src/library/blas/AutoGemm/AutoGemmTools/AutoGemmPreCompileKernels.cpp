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

#ifdef __GNUC__
// Linux
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#else
// Windows
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

unsigned int totalKernelsToCompile;
unsigned int numKernelsCompiled;
char *path;
std::ofstream includeFile;

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
  bool extraCol )
{
  return sprintf( *kernelName,
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
  bool extraCol )
{
  int n = getKernelName<Precision>(stringName, order, transA, transB, beta, macroTileNumRows, macroTileNumCols, unroll, extraRow, extraCol);
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
  bool extraCol )
{
  int n = getKernelName<Precision>(fileName, order, transA, transB, beta, macroTileNumRows, macroTileNumCols, unroll, extraRow, extraCol);
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
  bool extraCol )
{
  char kernelNameArray[64];
  char *kernelName = kernelNameArray;
  int n = getKernelName<Precision>(&kernelName, order, transA, transB, beta, macroTileNumRows, macroTileNumCols, unroll, extraRow, extraCol);
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
  unsigned char **binary,
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
    printf("%s\n", buildLog);
  }


  // get binary from program
  status = clGetProgramInfo(program, CL_PROGRAM_BINARY_SIZES, sizeof(size_t), binarySize, NULL);
  //printf("BinarySize: %llu\n", *binarySize);
  binary[0] = new unsigned char[*binarySize];
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
void writeBinaryToStream(std::ostream & out, unsigned char *binary, size_t binarySize) {
  for(int i = 0; i < binarySize; i++) {

    out << std::setw(3) << (unsigned int) binary[i];
    
    if(i < binarySize-1) {
      out << ",";
    }
    if((i+1)%20 == 0) {
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
  const char *buildOptions )
{
  // get kernel name
  char stringNameArray[64];
  char fileNameArray[64];
  char preprocessorNameArray[64];
  char *stringName = &stringNameArray[0];
  char *fileName = &fileNameArray[0];
  char *preprocessorName = &preprocessorNameArray[0];
  int stringNameLength = getStringName<Precision>(      &stringName,       order, transA, transB, beta, macroTileNumRows, macroTileNumCols, unroll, extraRow, extraCol);
  int fileNameLength = getFileName<Precision>(        &fileName,         order, transA, transB, beta, macroTileNumRows, macroTileNumCols, unroll, extraRow, extraCol);
  int preprocessorNameLength = getPreprocessorName<Precision>(&preprocessorName, order, transA, transB, beta, macroTileNumRows, macroTileNumCols, unroll, extraRow, extraCol);
  
  // get kernel binary
  unsigned char **kernelBinary = new unsigned char*[1];
  size_t kernelBinarySize;
  getKernelBinaryFromSource(context, source, buildOptions, kernelBinary, &kernelBinarySize);
  printf("AutoGemm-PreCompile[%3u/%3u]: %s %7u bytes\n", numKernelsCompiled, totalKernelsToCompile, stringName, kernelBinarySize);

  // write binary to file
  std::ofstream kernelFile;
  std::string fullFilePath;
  fullFilePath += path;
  fullFilePath += fileName;
  kernelFile.open(fullFilePath, 'w');
  kernelFile << "/* AutoGemm Pre-Compiled kernel binary */" << std::endl << std::endl;
  kernelFile << "#define " << preprocessorName << std::endl << std::endl;
  kernelFile << "unsigned char " << stringName << "[" << kernelBinarySize << "] = {" << std::endl;
  writeBinaryToStream( kernelFile, *kernelBinary, kernelBinarySize );
  kernelFile << "};" << std::endl;
  kernelFile.close();

  // add file to include
  includeFile << "#include \"AutoGemmKernelBinaries/" << fileName << "\"" << std::endl;

  delete[] kernelBinary[0];
  delete[] kernelBinary;

  // report kernel compiled
  numKernelsCompiled++;
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
  unsigned int unroll,
  bool preCompileNonMultiples )
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
  const char *binaryBuildOptions;
  cl_kernel  *tileClKernel;
  cl_kernel  *rowClKernel;
  cl_kernel  *colClKernel;
  cl_kernel  *cornerClKernel;
  unsigned int workGroupNumRows;
  unsigned int workGroupNumCols;
  unsigned int microTileNumRows;
  unsigned int microTileNumCols;
  gemmSelectKernelSpecific<Precision>(
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
      &binaryBuildOptions,
      &tileClKernel,
      &rowClKernel,
      &colClKernel,
      &cornerClKernel,
      &workGroupNumRows,
      &workGroupNumCols,
      &microTileNumRows,
      &microTileNumCols );

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
      sourceBuildOptions );

  if (preCompileNonMultiples) {
    
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
        sourceBuildOptions );
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
        sourceBuildOptions );
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
        sourceBuildOptions );
  }

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
  fullIncludeFilePath += "AutoGemmKernelBinariesPreCompiled.cpp";
  includeFile.open(fullIncludeFilePath, 'w');
  char *includeFileHeader =
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

  // for each kernel to be pre-compiled
  
  totalKernelsToCompile = gemmPreCompileNum;
  if (gemmPreCompileNonMultiples) { totalKernelsToCompile *= 4; }
  numKernelsCompiled = 0;
  for (unsigned int i = 0; i < gemmPreCompileNum; i++) {
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
        unroll,
        gemmPreCompileNonMultiples==1
        );
    }
  }// end for
  includeFile.close();
  //system("PAUSE");
  return 0;
}

















#if 0

// from tplint
void binaryToChar(const string &inputStr, std::ostream &outFile)
{
  //Get the binary location in fileName
  size_t found = inputStr.find( '@' );
  string fileName = inputStr.substr (found+1);

  //Open the binary
  std::ifstream file (fileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
  size_t fileSize;
  if(!file.is_open())
  {
    std::cerr << "fail to open binary file '" <<  fileName << "'" << std::endl;
    exit(1);
  }

  //Get contents of the binary
  char* fileContents;
  fileSize = file.tellg();
  fileContents = new char[fileSize];
  file.seekg(0, std::ios::beg);
  if(!file.read(fileContents, fileSize))
  {
    std::cerr << "fail to read binary file '" <<  fileName << "'" << std::endl;
    exit(1);
  }
  file.close();


  outFile << "//generated from the binary: " << fileName << "\n";

  //Copy the chars found before the @
  outFile <<  inputStr.substr (0,found);

  //Write contents of the binary
  outFile << "[" << fileSize << "] = {\n";
  for(int i=0; i < fileSize; i++)
  {
    outFile << (int) fileContents[i];
    if(i < fileSize-1) outFile << ",";
    if((i+1)%50 == 0) outFile << "\n";
  }
  outFile << "\n};\n";
}








//const char* NameDevicesToSupport [] = {"Tahiti", "Hawaii"};
char* NameDevicesToSupport = NULL;

int writeBinaryToFile(const char* fileName, const char* binary, size_t numBytes)
{
  ofstream output;
  output.open(fileName, ios::binary | ios::trunc);
  if (output.is_open())
  {
    output.write(binary, numBytes);
    output.close();
    return 0;
  }
  else
  {
    return 1;
  }
}



cl_int GenBinary(cl_context context, const char * source, const char * outFile)
{
  cl_int status = CL_SUCCESS;

  size_t sourceSize[] = {strlen(source)};
  cl_program program = clCreateProgramWithSource(context,1, &source,sourceSize,&status);
  if (status!=CL_SUCCESS)
  {
    cout<<" error clCreateProgramWithSource, can't generate binaries"<<endl;
    return status;
  }


  size_t nbDevicesInContext;
  status = clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL, &nbDevicesInContext);
  if (status!=CL_SUCCESS)
  {
    cout<<" error clGetContextInfo, can't generate binaries"<<endl;
    return status;
  }


  //getting dev id of the only devices we support see NameDevicesToSupport
  cl_device_id* devicesContext = new cl_device_id[nbDevicesInContext];
  clGetContextInfo(context, CL_CONTEXT_DEVICES, nbDevicesInContext, devicesContext, NULL);
  if (status!=CL_SUCCESS)
  {
    cout<<" error clGetContextInfo, can't generate binaries"<<endl;
    return status;
  }

  //size_t numDevices = sizeof(NameDevicesToSupport)/sizeof(char *); 
  cl_device_id DeviceToSupport ;
  int j =0;
  for(size_t i = 0; i < nbDevicesInContext; i++)
  {    
    char deviceName[1024];
    status = clGetDeviceInfo(devicesContext[i], CL_DEVICE_NAME,sizeof(deviceName),deviceName, NULL);
    if (!strcmp(deviceName, NameDevicesToSupport)   )
    {
      DeviceToSupport = devicesContext[i];
      j++;
      if (j==1)
        break;
    }
  }

  //building for the only devices we want to support
  status = clBuildProgram(program,1,&DeviceToSupport,"",NULL,NULL);


  /* This function is intentionally left without a error check
  as it may not pass if kernels rely on specific properties of devices
  In such cases, binaries for eligible devices are geenrated and dumped
  even wen this function will return an error */
  //CHECK_OPENCL_ERROR(status, "clBuildProgram failed.");
#ifdef _DEBUG
  if (status != CL_SUCCESS)
  {
    printf("clBuildProgram Failed\n");
    printf("status = %d\n", status);
    size_t len=0;

    clGetProgramBuildInfo(program, DeviceToSupport, CL_PROGRAM_BUILD_LOG, 0, NULL, &len);
    char* buffer= new char[len];

    printf("Error: Failed to build program executable!\n");
    clGetProgramBuildInfo(program, DeviceToSupport, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, 0);
    printf("%s\n", buffer);
  }

#endif



  /* figure out the sizes of each of the binaries. */    
  size_t *binarySizes = new size_t[1];
  status = clGetProgramInfo(program,CL_PROGRAM_BINARY_SIZES,sizeof(size_t) * 1,binarySizes,NULL);

  size_t i = 0;
  /* copy over all of the generated binaries. */
  char **binaries = new char*[1];

  for(i = 0; i < 1; i++)
  {
    if(binarySizes[i] != 0)
      binaries[i] = new char[binarySizes[i]];
    else
      binaries[i] = NULL;
  }



  status = clGetProgramInfo(program,CL_PROGRAM_BINARIES,sizeof(char *) * 1,binaries,NULL);

  /* dump out each binary into its own separate file. */
  for(i = 0; i < 1; i++)
  {
    char fileName[200];
    char deviceName[1024];
    status = clGetDeviceInfo(DeviceToSupport, CL_DEVICE_NAME,sizeof(deviceName),deviceName, NULL);

    sprintf(fileName, "%s.%s", outFile, deviceName);

    if(binarySizes[i] != 0)
    {
      cout<<deviceName<<" binary kernel: "<<fileName<<endl;
      if(writeBinaryToFile(fileName,binaries[i],binarySizes[i]))
      {
        std::cout << "Failed to load kernel file : " << fileName << std::endl;
        return 1;
      }
    }
    else
    {
      cout<< deviceName<<  "binary kernel(" << fileName << ") : Skipping as there is no binary data to write!" <<endl;
    }

  }
  // Release all resouces and memory
  for(i = 0; i < 1; i++)
  {
    if(binaries[i] != NULL)
    {
      delete [] binaries[i];
      binaries[i] = NULL;
    }
  }
  if(binaries != NULL)
  {
    delete [] binaries;
    binaries = NULL;
  }
  if(binarySizes != NULL)
  {
    delete [] binarySizes;
    binarySizes = NULL;
  }

  if(devicesContext)
  {
    delete [] devicesContext;
    devicesContext = NULL;
  }
  status = clReleaseProgram(program);



  return 0;
}

cl_int FinCLPlatform(cl_platform_id& platform)
{
  cl_int status = CL_SUCCESS;
  cl_uint numPlatforms;
  //cl_platform_id platform = NULL;
  status = clGetPlatformIDs(0, NULL, &numPlatforms);
  if(status != CL_SUCCESS)
  {
    cout<<"Error: clGetPlatformIDs failed. Error code : ";
    return status;
  }

  if (0 < numPlatforms) 
  {
    // Get selected platform
    cl_platform_id* platforms = new cl_platform_id[numPlatforms];
    status = clGetPlatformIDs(numPlatforms, platforms, NULL);
    if(status != CL_SUCCESS)
    {
      cout<<"Error: clGetPlatformIDs failed. Error code : "<<status;
      return status;
    }

    // Print all platforms
    for (unsigned i = 0; i < numPlatforms; ++i) 
    {
      char pbuf[100];
      status = clGetPlatformInfo(platforms[i],
        CL_PLATFORM_VENDOR,
        sizeof(pbuf),
        pbuf,
        NULL);

      if(status != CL_SUCCESS)
      {
        cout<<"Error: clGetPlatformInfo failed. Error code : "<<status;
        return status;
      }

      cout << "Platform " << i << " : " << pbuf << endl;
    }

    // Get AMD platform
    for (unsigned i = 0; i < numPlatforms; ++i) 
    {
      char pbuf[100];
      status = clGetPlatformInfo(platforms[i],
        CL_PLATFORM_VENDOR,
        sizeof(pbuf),
        pbuf,
        NULL);

      if(status != CL_SUCCESS)
      {
        cout<<"Error: clGetPlatformInfo failed. Error code : "<<status;
        return status;
      }

      platform = platforms[i];
      if (!strcmp(pbuf, "Advanced Micro Devices, Inc.")) 
      {
        break;
      }
    }

    // Check for AMD platform
    char pbuf[100];
    status = clGetPlatformInfo(platform,
      CL_PLATFORM_VENDOR,
      sizeof(pbuf),
      pbuf,
      NULL);

    if(status != CL_SUCCESS)
    {
      cout<<"Error: clGetPlatformInfo failed. Error code : "<<status;
      return status;
    }
    if (strcmp(pbuf, "Advanced Micro Devices, Inc.")) 
    {
      cout << "AMD platform not found" << endl;
      return -1; 
    }

  }

  return status;

}

//we know the input string will be in the form :static const char* kernelname = \"
string FindKernelNameFromString(string inputLine)
{
  string result;
  size_t pos = inputLine.find( '*' );

  size_t StartKernelName = 1+pos;
  char space = inputLine[StartKernelName];
  while(space==' ')
  {
    StartKernelName++;
    space = inputLine[StartKernelName];
  }

  size_t endKernelName = StartKernelName+1; 
  space = inputLine[endKernelName];
  while(space!=' ')
  {
    endKernelName++;
    space = inputLine[endKernelName];
  }
  result = inputLine.substr(StartKernelName,endKernelName-StartKernelName );
  return result;
}


int main( int argc, char *argv[] )
{
  cl_int status = CL_SUCCESS;
  cl_platform_id platform = NULL;
  cout<< "entering bingen function"<<endl;




  if (argc < 3)
  {
    cout<< "we found only "<<argc <<" arguments"<<endl;
    cout<< "needs at least 3 argument"<<endl;
    cout<< "app [deviceName] [file name]..."<<endl;
    return -1;
  }


  NameDevicesToSupport = argv[1];



 // cl_uint error = clGetDeviceInfo(device, CL_DEVICE_ADDRESS_BITS, sizeof(cl_uint), &bitness, NULL);
  int _64BitsUse = 0;
#if defined( _WIN64 ) || defined(__LP64__) || defined(_LP64)
  _64BitsUse = 1;
#endif

  status = FinCLPlatform(platform);

  if(status!=CL_SUCCESS || platform==NULL)
  {
    cout<< "can't find a AMD platform for OpenCL" << endl;
    return status;
  }

  cl_context_properties cps[5] =
  {
    CL_CONTEXT_PLATFORM,
    (cl_context_properties)platform,
    CL_CONTEXT_OFFLINE_DEVICES_AMD,
    (cl_context_properties)1,
    0
  };
  cl_context context = clCreateContextFromType(
    cps,
    CL_DEVICE_TYPE_ALL,
    NULL,
    NULL,
    &status);

  if(status!=CL_SUCCESS)
  {
    cout<<"can't create offline context"<<endl;
    return status;
  }

  //const char * _64Bits = getenv("GPU_FORCE_64BIT_PTR");
  const char *outputPrefix = "";
  for ( int i=2; i<argc; i++ )
  {
    char cltFile[1024];

    strcpy(cltFile, outputPrefix);
#ifdef __GNUC__
    //   strcat(cltFile, "/");
#else
    //strcat(cltFile, "\\" );
#endif
    strcat(cltFile, argv[i]);
    strcat(cltFile,NameDevicesToSupport );
    if (_64BitsUse)
      strcat(cltFile, "_64");
    else
      strcat(cltFile, "_32");
    strcat(cltFile, ".bin.cl");

    //if( !isModified(argv[i], cltFile ) )
    //{
    //  continue;
    //}
	string tempfile(cltFile);
	string subtempFile = tempfile.substr(tempfile.find_last_of("\\/") + 1, tempfile.length());
	std::cout << "sub string " << subtempFile << std::endl;
	
    std::cout << "Processing " << argv[i] << std::endl;
	std::cout << "outfile name " << subtempFile.c_str() << std::endl;

    ifstream inFile( argv[i] );
	ofstream outFile(subtempFile.c_str());

    stringstream ss;

    if( !(inFile.is_open()) ) 
    {
      cerr << "\tWARNING: couldn't open input file!" << std::endl;
      continue;
    }

    if (!(outFile.is_open() ))
    {
      cerr << "\tWARNING: couldn't open output file!" << std::endl;
      continue;
    }

    bool validKernel = false;
    string kernelName;
    string str;
    size_t found;
    int lineCount;
    vector<string> kernelnames;
    while( inFile.good() )
    {
      getline( inFile, str );

      // Replace all tabs with spaces
      found = str.find( '\t' );
      while (found != string::npos)
      {
        str.replace( found, 1, "    " );
        found = str.find( '\t' );
      }

      // Find for beginning of the kernel, which will give the kernelName
      if ( !validKernel && (str.find( "char" ) != string::npos) && (str.find( '*' ) != string::npos)
        && (str.find( '"' ) != string::npos))       // Beginning of the kernel
      {
        kernelName = FindKernelNameFromString(str);
        if(_64BitsUse)
          kernelName+="_64";
        else
          kernelName+="_32";

        kernelName+="_bin";
        kernelnames.push_back(kernelName);
        validKernel = true;
        // ss << str << "\\\n";
        lineCount = 1;
      }
      // Deals with the case of a binary

      // Find for end of kernel
      else if( (str.find( "\";" ) != string::npos) && validKernel )
      {
        //ss << str << "\n\n\n";
        cout<<"string kernel name: "<<kernelName<<endl;
        GenBinary(context, ss.str().c_str(), kernelName.c_str());
        validKernel = false;

        //reinitialize ss
        //ss=stringstream(); this doesn't work on linux with gcc4.4.7
        ss.str("");
        str.clear();

      }
      else if( validKernel )
      {
        ss << str <<"\n";//<< "\\n\\\n";                   // All other lines
        lineCount ++;
        // Break the string every 50 lines so that it does not overflow string limitations on windows
        //if( (lineCount%50) == 0 )
        //  ss << "\"\n\"\\\n";
      } 

    }
    inFile.close();

    // int numDevices = sizeof(NameDevicesToSupport)/sizeof(char *); 

    cout<< "CL binaries generation terminated, now generating the .bin.cl file for tplgen process : "<< cltFile<< endl;

    for (int i=0; i<kernelnames.size(); i++)
    {
      // for(int j = 0; j<numDevices; j++)
      outFile << "const char " <<kernelnames[i]<<"_"<<NameDevicesToSupport<<" @"<<kernelnames[i]<<"."<<NameDevicesToSupport<<"\n";
      cout << "const char " <<kernelnames[i]<<"_"<<NameDevicesToSupport<<" @"<<kernelnames[i]<<"."<<NameDevicesToSupport<<"\n";
    }
    outFile.close();
  }

  clReleaseContext(context);
  return 0;
}

#endif