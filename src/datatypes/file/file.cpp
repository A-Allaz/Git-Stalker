#ifndef __FILE_CPP__
#define __FILE_CPP__

#include "../../../include/datatypes/file/file.h"

File::File(std::string name, std::variant<Instruction, Block, Function, File>* mapped_to){
    this->file_name = name;
    this->mapped_to= mapped_to;
};

#endif