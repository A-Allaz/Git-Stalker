#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <string>
#include "../mapping/mapped_type.h"

class Function {
    private:
        File* file;
        std::string function_name;
        unsigned int starting_line;
        unsigned int ending_line;
        MappedType mapped_to;

    public:
        Function(File* file, std::string name, MappedType mapped_to, unsigned int starting_line, unsigned int ending_line);
        ~Function();

        File* get_file() const { return file; };
        std::string get_function_name() const { return function_name; };
        MappedType get_mapped() const { return mapped_to; };
};

#endif