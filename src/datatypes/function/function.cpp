#ifndef __FUNCTION_CPP__
#define __FUNCTION_CPP__

#include <function/function.h>
#include <repository/repository.h>

using namespace std;

Function::Function(File* file, string name, size_t starting_line, size_t ending_line, MappedType* mapped_to){
    this->file = file;
    this->function_name = name;
    this->starting_line = starting_line;
    this->ending_line = ending_line;
    this->mapped_to = mapped_to;
};

#endif