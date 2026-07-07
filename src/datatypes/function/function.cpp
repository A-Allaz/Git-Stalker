#ifndef __FUNCTION_CPP__
#define __FUNCTION_CPP__

#include "../../../include/datatypes/function/function.h"

Function::Function(File* file, std::string name, std::variant<Function, File>* mapped_to, unsigned int starting_line, unsigned int ending_line){
    this->file = file;
    this->function_name = name;
    this->starting_line = starting_line;
    this->ending_line = ending_line;
    this->mapped_to = mapped_to;
};

#endif