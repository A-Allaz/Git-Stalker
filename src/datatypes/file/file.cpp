#ifndef __FILE_CPP__
#define __FILE_CPP__

#include <file/file.h>
#include <function/function.h>

using namespace std;

File::File(string name, Repository* repository){
    this->file_name = name;
    this->repository = repository;
};

File::~File(){
    for(auto function: this->function_list){
        free(function);
    }
};

ostream& operator<<(ostream& os, File* file) {
    os << file->get_name();

    return os;
};

#endif