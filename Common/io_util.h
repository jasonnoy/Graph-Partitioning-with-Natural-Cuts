#ifndef __IO_UTIL_H_
#define __IO_UTIL_H_

#include <vector>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <string.h>
//#include <filesystem>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <thread>
#include <iostream>
#include <sstream>
#include <fstream>
#include "crp_types.h"
using namespace std;
using namespace navi::crp;

template<typename T>
int read_binary(const string &path,vector<T> &output){
    //0达标read 成功，-1代表带看文件失败，-2代表读取格式失败
    ifstream fs(path,ios::binary);
    if (!fs){
        cerr << "open file failed: " << path << endl;
        return -1;
    }
    uint32_t count;
    fs.read((char *)&count, sizeof(uint32_t));
    output.resize(count);
    fs.read((char *)&output[0], sizeof(T) * count);
    return fs.good() ? 0:-2;
}

template<typename T>
int write_binary(const string &path,vector<T> &data){
    ofstream fs(path,ios::binary);
    uint32_t count = data.size();
    fs.write((char *)&count, sizeof(uint32_t));
    if (data.size() > 0){
        fs.write((char *)&data[0], sizeof(T) * data.size());
    }
    return fs.good() ? 0: -2;
}

bool get_file_size(const string& file_path, uint64_t& file_size)
{
    struct stat sb;
    if (-1 == stat(file_path.c_str(), &sb))
    {
        perror(strerror(errno));
        return false;
    }
    file_size = (uint64_t)sb.st_size;
    return true;
}

topo_link_head_weight_t* read_topo_link(const string &topo_weight_path){
    ifstream fs(topo_weight_path,ios::binary);
    if (!fs){
        cerr << "open file failed: " << topo_weight_path << endl;
        return nullptr;
    }
    mode_t mode = umask(0);
    int32_t fd = open(topo_weight_path.c_str(), O_RDONLY, 0444);
    umask(mode);
    if (fd == -1)
    {
        return nullptr;
    }
    uint64_t file_size = 0;
    bool ret = get_file_size(topo_weight_path, file_size);
    if (!ret)
    {
        return nullptr;
    }
    char* mem_address = reinterpret_cast<char*>(mmap(NULL, file_size, PROT_READ, MAP_SHARED, fd, 0));
    if (mem_address == MAP_FAILED)
    {
        munmap(mem_address, file_size);
        return nullptr;
    }
    
    topo_link_head_weight_t* topo_link_head_ptr = reinterpret_cast<topo_link_head_weight_t*>(mem_address);
    return topo_link_head_ptr;
} 


#endif