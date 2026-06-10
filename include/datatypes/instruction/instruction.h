#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <variant>
#include "../file/file.h"
#include "../function/function.h"
#include "../instruction/instruction.h"

class Instruction {
    private:
        File file;
        Block block;
        std::variant<Instruction, Block, Function, File> mapped_to;
        unsigned line_number;

    public:
        Instruction(){}
        ~Instruction(){}

        File get_file() const { return file_name };
        Block get_block() const { return block };
        std::variant<Instruction, Block, Function, File> get_mapped() const { return mapped_to };
        unsigned get_line() const { return line_number };
}

#endif