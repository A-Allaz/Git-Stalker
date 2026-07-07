#ifndef __FILE_H__
#define __FILE_H__

#include <variant>
#include <string>
#include "../block/block.h"
#include "../function/function.h"
#include "../instruction/instruction.h"

class File {
    private:
        std::string file_name;
        std::variant<Instruction, Block, Function, File>* mapped_to;

    public:
        File(std::string name, std::variant<Instruction, Block, Function, File>* mapped_to);
        ~File();

        std::string get_name() const { return file_name; };
        std::variant<Instruction, Block, Function, File>* get_mapped() const { return mapped_to; };
};

#endif