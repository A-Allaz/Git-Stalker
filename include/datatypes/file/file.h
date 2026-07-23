#ifndef __FILE_H__
#define __FILE_H__

#include <string>
#include "../mapping/mapped_type.h"
#include "../repository/repository.h"

class File {
    private:
        std::string file_name;
        Repository* repository;
        MappedType mapped_to;

    public:
        File(std::string name, Repository* repository, MappedType mapped_to);
        ~File();

        std::string get_name() const { return file_name; };
        MappedType get_mapped() const { return mapped_to; };
};

#endif