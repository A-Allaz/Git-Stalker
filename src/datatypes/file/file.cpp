#ifndef __FILE_CPP__
#define __FILE_CPP__

#include <file/file.h>

using namespace std;

File::File(string name, Repository* repository, MappedType* mapped_to){
    this->file_name = name;
    this->repository = repository;
    this->mapped_to = mapped_to;
};

ostream& operator<<(ostream& os, File* file) {
    os << file->get_name();

    return os;
}

#endif