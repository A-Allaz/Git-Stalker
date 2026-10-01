#ifndef __FILE_CPP__
#define __FILE_CPP__

#include <file/file.h>
#include <function/function.h>

using namespace std;

File::File(string name, Repository* repository, MappedType mapped_to){
    this->file_name = name;
    this->repository = repository;
    this->mapped_to = mapped_to;
};

ostream& operator<<(ostream& os, File* file) {
    os << file->get_name();

    return os;
}

string File::get_mapped_name() const {
    if(std::holds_alternative<std::monostate>(this->get_mapped())){
        return "none";
    }

    return visit([](const auto& obj) -> string {
        using T = decay_t<decltype(obj)>;

        if constexpr (is_same_v<T, Function*>){
            return "FUNCTION-" + obj->get_function_name();
        } else if constexpr (is_same_v<T, File*>){
            return "FILE-" + obj->get_name();
        } else {
            return "NULL";
        }
    }, (this->mapped_to));
}

#endif