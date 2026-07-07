#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <variant>
#include "../file/file.h"
#include "../function/function.h"
#include "../instruction/instruction.h"

class Block {
    private:
        File* file;
        unsigned int starting_line;
        unsigned int ending_line;
        std::variant<Instruction, Block, Function, File>* mapped_to;
        std::string* instructions;

    public:
        Block(
            File* file, 
            unsigned int starting_line, 
            unsigned int ending_line, 
            std::variant<Instruction, Block, Function, File>* mapped_to
        );
        ~Block();

        File* get_file() const { return file; };
        unsigned int get_starting_line() const { return starting_line; };
        unsigned int get_ending_line() const { return ending_line; };
        std::variant<Instruction, Block, Function, File>* get_mapped() const { return mapped_to; };
        std::string* get_instructions() const { return instructions; };
};

#endif