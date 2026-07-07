#ifndef __BLOCK_CPP__
#define __BLOCK_CPP__

#include "../../../include/datatypes/block/block.h"

Block::Block(
    File* file, 
    unsigned int starting_line, 
    unsigned int ending_line, 
    std::variant<Instruction, Block, Function, File>* mapped_to
){
    this->file = file;
    this->starting_line = starting_line;
    this->ending_line = ending_line;
    this->mapped_to = mapped_to;

    // TODO
    /**
     * Get file name
     * Parse all instructions into the instructions* array
     */
};

#endif