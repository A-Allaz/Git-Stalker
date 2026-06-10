#ifndef __FILE_H__
#define __FILE_H__

#include <variant>
#include "../block/block.h"
#include "../function/function.h"
#include "../instruction/instruction.h"

class File {
    private:
        std::string file_name;
        std::variant<Instruction, Block, Function, File> mapped_to;
        Block* blocks;

    public:
        File(){}
        ~File(){}

        std::string get_name() const { return file_name };
        std::variant<Instruction, Block, Function, File> get_mapped() const { return mapped_to };
        Block* get_blocks() const { return instructions };
}

#endif