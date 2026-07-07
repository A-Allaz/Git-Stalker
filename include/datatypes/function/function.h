#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "../file/file.h"

class Function {
    private:
        File* file;
        std::string function_name;
        unsigned int starting_line;
        unsigned int ending_line;
        std::variant<Function, File>* mapped_to;

    public:
        Function(File* file, std::string name, std::variant<Function, File>* mapped_to, unsigned int starting_line, unsigned int ending_line);
        ~Function();

        File* get_file() const { return file; };
        std::string get_function_name() const { return function_name; };
        std::variant<Function, File>* get_mapped() const { return mapped_to; };
};

#endif