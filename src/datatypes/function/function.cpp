#ifndef __FUNCTION_CPP__
#define __FUNCTION_CPP__

#include <file/file.h>
#include <function/function.h>
#include <repository/repository.h>

using namespace std;

Function::Function(File* file, string name, size_t starting_line, size_t ending_line, MappedType mapped_to){
    this->file = file;
    this->function_name = name;
    this->starting_line = starting_line;
    this->ending_line = ending_line;
    this->mapped_to = mapped_to;
};

string Function::get_mapped_name() const {
    if(std::holds_alternative<std::monostate>(this->get_mapped())){
        return "none";
    }

    return visit([](const auto& obj) -> string {
        using T = decay_t<decltype(obj)>;

        if constexpr (is_same_v<T, Function*>){
            return "FUNC-" + obj->get_function_name();
        } else if constexpr (is_same_v<T, File*>){
            return "FILE-" + obj->get_name();
        } else {
            return "NULL";
        }
    }, (this->mapped_to));
}

#endif