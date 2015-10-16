/* ************************************************************************
 * Copyright 2014 Advanced Micro Devices, Inc.
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


#include <binary_lookup.h>

#include <iostream>
#include <fstream>
#include <cassert>

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <devinfo.h>
#include <stdlib.h>



#ifdef _WIN32
#include <windows.h>
#include <direct.h> // for _mkdir
#else
#include <unistd.h>
#endif

extern "C"
{
#include <md5sum.h>
}

// size for clGetDeviceInfo queries
#define SIZE 256




#define CAPS_DEBUG 0

#include <string.h>

static char * sep()
{
#ifdef __WIN32
    return (char*)"\\";
#else
    return (char*)"/";
#endif
}

static std::string cache_path;
static bool cache_enabled(false);

extern "C" void clblasInitBinaryCache()
{
    const char * path = getenv("CLBLAS_CACHE_PATH");
    if (path)
    {
        cache_path = std::string(path) + sep();
        cache_enabled = true;
    }
    else
    {
        cache_path = "";
    }
}

BinaryLookup::CacheEntry::CacheEntry(const std::string & filename)
    : m_filename(filename), m_successful_creation(false)
{

}

void BinaryLookup::CacheEntry::close()
{
#ifdef _WIN32
    CloseHandle(this->m_handle);
#else
    ::close(*(int*)this->m_handle);
    delete (int*)this->m_handle;
#endif
}

bool BinaryLookup::CacheEntry::successful_creation()
{
    return this->m_successful_creation;
}

bool BinaryLookup::CacheEntry::exclusive_create()
{
#ifdef _WIN32
    HANDLE handle = CreateFile(this->m_filename.c_str(), 
                               GENERIC_WRITE, 
                               0, // no share with other process
                               NULL,
                               CREATE_NEW,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL);

    this->m_handle = handle;
    this->m_successful_creation = (handle != INVALID_HANDLE_VALUE);
    return this->m_successful_creation;
#else
    int * fd = new int[1];
    *fd = open (this->m_filename.c_str(),
                O_CREAT | O_EXCL, 
                S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    this->m_handle = fd;
    this->m_successful_creation = (*fd != -1);
    return *fd >= 0;
#endif
}

BinaryLookup::BinaryLookup(cl_context ctxt, cl_device_id device, const std::string & kernel_name)
    : m_context(ctxt), m_device(device), m_program(NULL), m_binary(0), m_signature(0), m_cache_enabled(cache_enabled)
{
    // initialize the entry name
    this->m_cache_entry_name = kernel_name;

    if (this->m_cache_enabled)
    {
        // retrieve device informations to compute the path of the cache
        cl_int err = this->retrieveDeviceAndDriverInfo();

        if (err != CL_SUCCESS)
        {
            cache_enabled = false;
            this->m_cache_enabled = false;
        }
    }
}

BinaryLookup::~BinaryLookup()
{
    delete this->m_binary;
    delete this->m_signature;
}

BinaryLookup::Variant::Variant()
    : m_kind((VariantKind)0), m_size(0), m_data(0)
{
}

BinaryLookup::Variant::Variant(VariantKind kind, char * data, size_t size)
    : m_kind(kind), m_size(size)
{
    this->m_data = new char[this->m_size];
    memcpy(this->m_data, data, size);
}

BinaryLookup::Variant::~Variant()
{
    // delete this->m_data;
}

void BinaryLookup::variantInt(int num)
{
    m_variants.push_back(Variant(INT, (char*)&num, sizeof(num)));
}
 
void BinaryLookup::variantDouble(double num)
{
    m_variants.push_back(Variant(DOUBLE, (char*)&num, sizeof(num)));
}

void BinaryLookup::variantCompileOptions(const std::string & opts)
{
    m_variants.push_back(Variant(STRING, (char*)opts.c_str(), opts.size()));
}

void BinaryLookup::variantRaw(const void * data, size_t bytes)
{
    m_variants.push_back(Variant(DATA, (char*)data, bytes));
}

enum BinaryRepresentation
{
    LSB,
    MSB,
    UNKNOWN
};

static enum BinaryRepresentation getStorageMode(char * data)
{
    if (data[0] == 'C' && 
        data[1] == 'L' && 
        data[2] == 'B' &&
        data[3] == '\0')
        return LSB;

    if (data[0] == 'B' && 
        data[1] == 'L' && 
        data[2] == 'C' &&
        data[3] == '\0')
        return MSB;

    return UNKNOWN;
}

void BinaryLookup::finalizeVariant()
{
    // serialize variants
    size_t whole_variant_size_in_bytes = 0;

    // store 1 byte for the variant kind
    whole_variant_size_in_bytes += this->m_variants.size() * sizeof(int); // for the variant kind
    whole_variant_size_in_bytes += this->m_variants.size() * sizeof(size_t); // for the variant size

    // add every variant sizes
    for(size_t i=0 ; i<this->m_variants.size() ; ++i)
    {
        const Variant & v = this->m_variants[i];

        // compute the whole size of the signature
        whole_variant_size_in_bytes += v.m_size;
    }

    this->m_header.signature_size = whole_variant_size_in_bytes;

    this->m_signature = new char[whole_variant_size_in_bytes];
    char * current_address = this->m_signature;
    for(size_t i=0 ; i<this->m_variants.size() ; ++i)
    {
        Variant v = this->m_variants[i];

        // write the variant kind
        memcpy(current_address, &v.m_kind, sizeof(int));
        current_address += sizeof(v.m_kind);

        // write the variant size
        memcpy(current_address, &v.m_size, sizeof(v.m_size));
        current_address += sizeof(v.m_size);

        // write the variant itself
        memcpy(current_address, v.m_data, v.m_size);
        current_address += v.m_size;
    }

    // Update the cache entry name if there are variants...
    if (whole_variant_size_in_bytes != 0)
    {
        char * md5_sum = md5sum(this->m_signature, this->m_header.signature_size);
        this->m_cache_entry_name = md5_sum;
        delete md5_sum;
    }
    else
    {
        this->m_cache_entry_name += ".db";
    }
}

bool BinaryLookup::loadHeader(std::ifstream &file, size_t length)
{
    file.read ((char*)&this->m_header, sizeof(Header));

    // FIXME: Consider LSB Vs MSB number representation
    assert(getStorageMode(this->m_header.magic_key) == LSB);

    if (this->m_header.whole_file_size != (int)length)
    {
        // the file has not been correctly initialized (yet)
        return false;
    }

    return true;
}

bool BinaryLookup::loadBinaryAndSignature(std::ifstream &file)
{
    {
        this->m_binary    = new unsigned char [this->m_header.binary_size];
        const std::istream& res = file.read((char*)this->m_binary, this->m_header.binary_size);
        if (!res.good())
            return false;
    }

    {
        this->m_signature = new char [this->m_header.signature_size];
        const std::istream& res = file.read((char*)this->m_signature, this->m_header.signature_size);

        if (!res.good())
            return false;

        this->m_variants.clear();

        char * current = this->m_signature;
        for (int i=0 ; i<this->m_header.signature_size ; ++i)
        {
            Variant v;
            v.m_kind = *(VariantKind*) current;
            i += sizeof(int);
            current += sizeof(int);

            v.m_size = *(size_t*) current;
            i += sizeof(size_t);
            current += sizeof(size_t);

            v.m_data = new char[v.m_size];
            memcpy(v.m_data, current, v.m_size);
            i += v.m_size;
            current += v.m_size;

            this->m_variants.push_back(v);
        }
    }

    return true;
}

bool BinaryLookup::tryLoadCacheFile()
{
    // may create empty file or may wait until file is ready
    const std::string & filename = this->m_path + this->m_cache_entry_name;
    std::ifstream file (filename.c_str(), std::ios_base::binary);

    if (file.is_open())
    {
        file.seekg (0, file.end);
        size_t length = file.tellg();
        file.seekg (0, file.beg);

        if (length == 0)
        {
            // the file is corrupted, so return false
            return false;
        }

        bool st;
        st = loadHeader(file, length);

        if (! st)
            return false;

        st = loadBinaryAndSignature(file);

        if (! st)
            return false;

        file.close();
        return true;
    }
    else
    {
        return false;
    }
}

bool BinaryLookup::found()
{
    // if we could not create the directory, it is useless to 
    if (! this->m_cache_enabled)
    {
        return false; // not found
    }

    this->finalizeVariant(); // serialize variant and cumpute checksum on it
    // also compute the tree to search from the cache entry (this->m_cache_entry_name, cache path ??)

    if (tryLoadCacheFile())
    {
        cl_int err = buildFromBinary(this->m_binary,
                                     this->m_header.binary_size, 
                                     NULL);

        // return false if the buildFromBinary failed, true else
        return err==CL_SUCCESS;
    }

    return false;
}

static cl_int getSingleBinaryFromProgram(cl_program program,
                                         std::vector<unsigned char*> & binary)
{
    // 3 - Determine the size of each program binary
    size_t size;
    cl_int err = clGetProgramInfo(program, CL_PROGRAM_BINARY_SIZES,
                                  sizeof(size_t),
                                  &size, NULL);
    if (err != CL_SUCCESS)
    {
        std::cerr << "Error querying for program binary sizes" << std::endl;
        return err;
    }

    binary.resize(size);
    binary[0] = new unsigned char[size];

    unsigned char * binary_address[1] = { binary[0] };

    // 4 - Get all of the program binaries
    err = clGetProgramInfo(program, CL_PROGRAM_BINARIES, 1 * sizeof(unsigned char*),
                           binary_address, NULL);


    if (err != CL_SUCCESS)
    {
#if CAPS_DEBUG
        std::cerr << "Error querying for program binaries" << std::endl;
#endif
        return err;
    }

    return CL_SUCCESS;
}

cl_int BinaryLookup::writeCacheFile(std::vector<unsigned char*> &data)
{
    if (! this->m_cache_enabled)
    {
        return 0;
    }

    // exclusive open to ensure that only one thread will write the file
    const std::string & filename = this->m_path + this->m_cache_entry_name;

    CacheEntry cache_file(filename);
    bool created = cache_file.exclusive_create();

    // try to exclusively create the cache file on the disk
    if (created)
    {
        // if it was created by the current thread, this one will write into cache file
        cache_file.close();

        const std::string & filename = this->m_path + this->m_cache_entry_name;
        std::ofstream file (filename.c_str(), std::ios_base::binary);

        file.write((char*)&this->m_header, sizeof(m_header));
        file.write((char*)data[0], this->m_header.binary_size);
        file.write((char*)this->m_signature, this->m_header.signature_size);
        file.close();

        return CL_SUCCESS;
    }

    // other thread do not write the cache file
    //Ben : do we really need to output something here, all the different branches return 0 (CL_SUCCESS)
    return CL_SUCCESS;
}

cl_int BinaryLookup::populateCache()
{
    // FIXME: support MSB
    this->m_header.magic_key[0] = 'C';
    this->m_header.magic_key[1] = 'L';
    this->m_header.magic_key[2] = 'B';
    this->m_header.magic_key[3] = '\0';

    std::vector<unsigned char*> data;
    cl_int err = getSingleBinaryFromProgram(this->m_program, data);

    if (err != CL_SUCCESS)
    {
        return err;
    }

    this->m_header.header_size = sizeof(Header);
    this->m_header.binary_size = data.size();
    this->m_header.whole_file_size = this->m_header.header_size + this->m_header.binary_size + this->m_header.signature_size;

    err = writeCacheFile(data);

    return CL_SUCCESS;
}

cl_int BinaryLookup::buildFromSource(const char * source)
{
    cl_int err;
    this->m_program = BinaryLookup::buildProgramFromSource(source,
                                                           this->m_context,
                                                           this->m_device,
                                                           err);

    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Warning: clCreateProgramWithSource failed with code %d\n", err);
        return err;
    }

    // write to the cache
    this->populateCache();

    return CL_SUCCESS;
}

cl_int BinaryLookup::buildFromLoadedBinary(const void * data,
                                           size_t len,
                                           const char * BuildOption)
{
    cl_int err;
    this->m_program = BinaryLookup::buildProgramFromBinary((char*) data,
                                                           len,
                                                           this->m_context,
                                                           this->m_device,
                                                           err,
                                                           BuildOption);

    return err;
}

cl_int BinaryLookup::buildFromBinary(const void * data,
                                     size_t len,
                                     const char * BuildOption )
{
    cl_int err = buildFromLoadedBinary(data, len, BuildOption);
    if (err != CL_SUCCESS)
        return err;

    // write to the cache
    this->populateCache();

    return CL_SUCCESS;
}

cl_program BinaryLookup::buildProgramFromSource(const char * source,
                                                cl_context context,
                                                cl_device_id device,
                                                cl_int & err,
                                                const char * options)
{
    cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source, NULL, &err);

    if (err != CL_SUCCESS)
        return NULL;

    err = clBuildProgram(program,
                         1, /* FIXME: 1 device */
                         &device,
                         options, 
                         NULL, 
                         NULL);

    if (err != CL_SUCCESS)
        return NULL;

    return program;
}



cl_program BinaryLookup::buildProgramFromBinary(const char * data,
                                                size_t data_size,
                                                cl_context context,
                                                cl_device_id device,
                                                cl_int & err,
                                                const char * options)
{
    cl_program program = clCreateProgramWithBinary(context,
                                                   1, // num_device
                                                   &device, // device_list
                                                   &data_size, // lengths
                                                   (const unsigned char **)&data,
                                                   NULL,
                                                   &err);
    if (err != CL_SUCCESS)
    {
        fprintf(stderr, "Warning: clCreateProgramWithBinary failed with code %d\n", err);
        return NULL;
    }

    err = clBuildProgram(program,
                         1, /* FIXME: 1 device */
                         &device,
                         options,
                         NULL,
                         NULL);

    if (err != CL_SUCCESS)
    {
        return NULL;
    }

    return program;
}

cl_program BinaryLookup::getProgram()
{
    return this->m_program;
}

void BinaryLookup::setProgram(cl_program program)
{
    this->m_program = program;
}


static int make_directory(const std::string &path)
{
#ifdef _WIN32
    return _mkdir (path.c_str());
#else
    return mkdir (path.c_str(), S_IRWXU);
#endif
}

static void do_mkdir(const std::string &path)
{
    int st = make_directory (path.c_str());

    if (st != 0)
    {
        if ( errno != EEXIST )
        {
            std::string tmp = "Cannot not create directory '" + std::string(path) + "': ";
            throw tmp;
        }
    }
}

cl_int BinaryLookup::retrieveDeviceAndDriverInfo()
{
    char m_device_vendor[SIZE];
    char m_device_name[SIZE];
    char m_driver_version[SIZE];

    cl_int err = clGetDeviceInfo(this->m_device, CL_DEVICE_VENDOR, sizeof(m_device_vendor),
                                 &m_device_vendor, NULL);
    if (err != CL_SUCCESS)
    {
        return err;
    }

    err = clGetDeviceInfo(this->m_device, CL_DEVICE_NAME, sizeof(m_device_name),
                          &m_device_name, NULL);
    if (err != CL_SUCCESS)
    {
        return err;
    }

    err = clGetDeviceInfo(this->m_device, CL_DRIVER_VERSION, sizeof(m_driver_version),
                          &m_driver_version, NULL);
    if (err != CL_SUCCESS)
    {
        return err;
    }

#if CAPS_DEBUG
    fprintf(stderr, "device vendor = %s\n", this->m_device_vendor);
    fprintf(stderr, "device name = %s\n", this->m_device_name);
    fprintf(stderr, "driver version = %s\n", this->m_driver_version);
#endif

    try
    {
        const std::string & root = (std::string(cache_path) + m_device_vendor + sep());
        do_mkdir(root.c_str());

        const std::string & root2 = (root + m_device_name + sep());
        do_mkdir(root2.c_str());

        const std::string & root3 = (root2 + m_driver_version + sep());
        do_mkdir(root3.c_str());

        const std::string & root4 = (root3 + this->m_cache_entry_name + sep());
        do_mkdir(root4.c_str());

        this->m_path = root4;
        
        return CL_SUCCESS;
    }
    catch (std::string & e)
    {
        fprintf(stderr, "%s\n", e.c_str());
        cache_enabled = false;
        this->m_cache_enabled = false;

        return CL_INVALID_VALUE;
    }
}
