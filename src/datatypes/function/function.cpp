#ifndef __FUNCTION_CPP__
#define __FUNCTION_CPP__

#include <file/file.h>
#include <function/function.h>
#include <repository/repository.h>

using namespace std;

Function::Function(File* file, string name, size_t starting_line, size_t ending_line, MappedType* mapped_to){
    this->file = file;
    this->function_name = name;
    this->starting_line = starting_line;
    this->ending_line = ending_line;
    this->mapped_to = mapped_to;
};

string Function::get_mapped_name() const {
    return visit([](const auto& obj) -> string {
        using T = decay_t<decltype(obj)>;

        if constexpr (is_same_v<T, Function*>){
            return "File-" + obj->get_function_name();
        } else {
            return "Function-" + obj->get_name();
        }
    }, *(this->mapped_to));
}

#endif