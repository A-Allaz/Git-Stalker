#ifndef __INSTRUCTION_CPP__
#define __INSTRUCTION_CPP__

#include "../../../include/datatypes/instruction/instruction.h"

Instruction::Instruction(File* file, std::variant<Instruction, Block, Function, File>* mapped_to, unsigned int line_number, Block* block){
    this->file = file;
    this->block = block;
    this->mapped_to = mapped_to;
    this->line_number = line_number;
};

#endif