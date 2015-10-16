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
#include <iostream>

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
//#define stat _stat
#endif

#include "CL/cl.h"

void find_and_replace(std::string& str, const std::string& findStr, const std::string& replaceStr){
    size_t pos = 0;
    while ((pos = str.find(findStr, pos)) != std::string::npos){
        str.replace(pos, findStr.length(), replaceStr);
        pos += replaceStr.length();
    }
}

/******************************************************************************
* Check OpenCL Errors
*****************************************************************************/
#define CL_CHECK(STATUS) \
  if(STATUS != CL_SUCCESS) { \
    printf("OpenCL error %i on line %u\n", STATUS, __LINE__); \
    assert(false); \
    }

/******************************************************************************
* write binary to stream
*****************************************************************************/
void writeBinaryToStream(std::ostream & out, char *binary, size_t binarySize) {
    for (int i = 0; i < binarySize; i++) {

        out << std::setw(4) << (int)binary[i];

        if (i < binarySize - 1) {
            out << ",";
        }
        if ((i + 1) % 16 == 0) {
            out << std::endl;
        }
    }
    out << std::endl;
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
    if (status != CL_SUCCESS) {
        std::cout << "Error: clGetPlatformIDs failed. Error code: " << status << std::endl;
        return status;
    }

    if (numPlatforms > 0) {
        // Get selected platform
        cl_platform_id* platforms = new cl_platform_id[numPlatforms];
        status = clGetPlatformIDs(numPlatforms, platforms, NULL);
        if (status != CL_SUCCESS) {
            std::cout << "Error: clGetPlatformIDs failed. Error code : " << status << std::endl;
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

            if (status != CL_SUCCESS) {
                std::cout << "Error: clGetPlatformInfo failed. Error code : " << status << std::endl;
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

            if (status != CL_SUCCESS) {
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

        if (status != CL_SUCCESS) {
            std::cout << "Error: clGetPlatformInfo failed. Error code: " << status << std::endl;
            return status;
        }
        if (strcmp(pbuf, "Advanced Micro Devices, Inc.")) {
            std::cout << "AMD platform not found" << std::endl;
            return CL_INVALID_PLATFORM;
        }

    }
    else {
        std::cout << "No OpenCL platforms found." << std::endl;
        return CL_INVALID_PLATFORM;
    }

    return status;
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
    cl_program program = clCreateProgramWithSource(context, 1, &source, NULL, &status);
    CL_CHECK(status);

    cl_uint numDevicesInContext;
    status = clGetContextInfo(context, CL_CONTEXT_NUM_DEVICES, sizeof(cl_uint), &numDevicesInContext, NULL);
    CL_CHECK(status);

    // get devices
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

        size_t len = 0;
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

    binary[0] = new char[*binarySize];

    status = clGetProgramInfo(program, CL_PROGRAM_BINARIES, 8 /*?*/, binary, NULL);
    CL_CHECK(status);

    return CL_SUCCESS;
}

int main(int argc, char *argv[])
{
    /*
    OCLBinaryGenerator requires at least two inputs
    1, path the kernel file
    2, file name
    3, output directory
    4, optional compiler flags
    5, [optional] trageted hardware. If this is not supplied OCLBinaryGenerator will generate binary for the first device on system
    */
    if (argc < 4)
    {
        printf("not enough arguments. OCLBinaryGenerator aborted.\n");
        exit(-1);
    }

    //get the input path
    std::string inputPath = argv[1];
    inputPath += "/";
    std::cout << "OCLBinaryGenerator input path is " << inputPath <<std::endl;

    //get the input filename
    std::string inputFilename = argv[2];
    inputFilename += ".cpp";
    std::cout << "OCLBinaryGenerator input filename is " << inputFilename << std::endl;
    
    //get the path to destination
    std::string outputPath = argv[3];
    outputPath += "/";
    std::cout << "OCLBinaryGenerator output path is " << outputPath << std::endl;

    //output filename
    std::string outputFilename = argv[2];
    std::string outputKernelName = argv[2];
    outputFilename += "_bin.cpp";
    std::cout << "OCLBinaryGenerator output filename is " << outputFilename << std::endl;

    //get compiler flag
    std::string OCL_flag = " ";
    if (argc > 4)
        OCL_flag = argv[4];
    std::cout << "OCLBinaryGenerator compiler flag is " << OCL_flag << std::endl;

    //start writing file
    std::ofstream outputFile;
    outputFile.open((outputPath+outputFilename).c_str(), std::ios::out);

    const char *outputFileHeader =
        "/*****************************************************************************\n"
        " * kernel binary file\n"
        " ****************************************************************************/\n\n";
    outputFile << outputFileHeader;

    // get AMD platform
    cl_platform_id platform;
    cl_int status = getAMDPlatform(&platform);
    CL_CHECK(status);

    cl_uint numDevices;
    status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
    CL_CHECK(status);

    // get all gpu devices
    cl_device_id* devices = new cl_device_id[numDevices];
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, numDevices, devices, NULL);
    CL_CHECK(status);

    // choose device 0 or we can choose a target device in the future
    cl_device_id device = devices[0];

    // create context
    cl_context_properties cps[3] = 
    {
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
    CL_CHECK(status);

    char **kernelBinary = new char*[1];
    size_t kernelBinarySize;

    
    std::ifstream inputfile((inputPath+inputFilename).c_str());
    if (!inputfile.is_open())
    {
        printf("Input file does not exist. OCLBinaryGenerator aborted.\n");
        exit(-1);
    }
    std::string str((std::istreambuf_iterator<char>(inputfile)), std::istreambuf_iterator<char>());
    inputfile.close();
    //std::cout<<str<<std::endl;
    std::string str_temp("= STRINGIFY(");
    size_t startOfKernel = str.find("= STRINGIFY(");
    startOfKernel += str_temp.length();
    size_t endOfKernel = str.find("// end of kernel");
    std::string kernelStr = str.substr(startOfKernel, endOfKernel - startOfKernel);
    //std::cout << "kernelStr = " << std::endl;
    //std::cout << kernelStr << std::endl;
    find_and_replace(kernelStr, "\\n", " ");
    //std::cout << "after kernelStr = " <<std::endl;
    //std::cout << kernelStr << std::endl;


    status = getKernelBinaryFromSource(context, kernelStr.c_str(), OCL_flag.c_str(), kernelBinary, &kernelBinarySize);
    CL_CHECK(status);
    //writing the file
    outputFile << "char " << outputKernelName << "_binArray[" << kernelBinarySize << "] = {" <<std::endl;
    writeBinaryToStream(outputFile, *kernelBinary, kernelBinarySize);
    outputFile << "};" << std::endl;

    outputFile << "unsigned char *" << outputKernelName << "_bin = " << "reinterpret_cast<unsigned char *>(" << outputKernelName << "_binArray);" << std::endl;
    outputFile << "size_t " << outputKernelName << "_binSize = " << kernelBinarySize << ";" << std::endl;
    outputFile << "const char * const " << outputKernelName << "_src = NULL;" << std::endl;

    //end writing file
    outputFile.close();
    printf("OCLBinaryGenerator finished.\n");
}
