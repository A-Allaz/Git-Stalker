#ifndef __FILE_CPP__
#define __FILE_CPP__

#include "../../../include/datatypes/file/file.h"

File::File(std::string name, Repository* repository, MappedType mapped_to){
    this->file_name = name;
    this->repository = repository;
    this->mapped_to= mapped_to;
};

#endif