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

#include <iostream>
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

using namespace std;

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
