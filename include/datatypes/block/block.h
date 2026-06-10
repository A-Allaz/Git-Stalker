#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <variant>
#include "../file/file.h"
#include "../function/function.h"
#include "../instruction/instruction.h"

class Block {
    private:
        std::string file_name;
        std::variant<Instruction, Block, Function, File> mapped_to;
        std::string* instructions;
        unsigned starting_line;
        unsigned ending_line;

    public:
        Block(){}
        ~Block(){}

        std::string get_file() const { return file_name };
        std::variant<Instruction, Block, Function, File> get_mapped() const {};
        std::string* get_instructions() const { return instructions };
        unsigned get_starting_line() const { return starting_line };
        unsigned get_ending_line() const { return ending_line };
}

#endif