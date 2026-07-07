#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "../file/file.h"
#include "../block/block.h"
#include "../instruction/instruction.h"

class Function {
    private:
        File* file;
        std::string function_name;
        std::variant<Instruction, Block, Function, File>* mapped_to;

    public:
        Function(File* file, std::string name, std::variant<Instruction, Block, Function, File>* mapped_to);
        ~Function();

        File* get_file() const { return file; };
        std::string get_function_name() const { return function_name; };
        std::variant<Instruction, Block, Function, File>* get_mapped() const { return mapped_to; };
};

#endif