#ifndef __FILE_H__
#define __FILE_H__

#include <variant>
#include <string>
#include "../function/function.h"
#include "../repository/repository.h"

class File {
    private:
        std::string file_name;
        Repository* repository;
        std::variant<Function, File>* mapped_to;

    public:
        File(std::string name, Repository* repository, std::variant<Function, File>* mapped_to);
        ~File();

        std::string get_name() const { return file_name; };
        std::variant<Function, File>* get_mapped() const { return mapped_to; };
};

#endif