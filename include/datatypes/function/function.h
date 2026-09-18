#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <string>
#include <mapping/mapped_type.h>

class File;

using namespace std;

class Function {
    private:
        File* file;
        string function_name;
        size_t starting_line;
        size_t ending_line;
        MappedType* mapped_to;

    public:
        Function(File* file, string name, size_t starting_line, size_t ending_line, MappedType* mapped_to=nullptr);
        ~Function();

        File* get_file() const { return file; };
        string get_function_name() const { return function_name; };
        MappedType* get_mapped() const { return mapped_to; };
};

#endif