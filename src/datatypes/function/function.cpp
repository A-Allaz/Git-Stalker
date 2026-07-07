#ifndef __FUNCTION_CPP__
#define __FUNCTION_CPP__

#include "../../../include/datatypes/function/function.h"

Function::Function(File* file, std::string name, std::variant<Instruction, Block, Function, File>* mapped_to){
    this->file = file;
    this->function_name = name;
    this->mapped_to = mapped_to;
};

#endif