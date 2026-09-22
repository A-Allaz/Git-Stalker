#ifndef __FILE_CPP__
#define __FILE_CPP__

#include <file/file.h>
#include <function/function.h>

using namespace std;

File::File(string name, Repository* repository, MappedType* mapped_to){
    this->file_name = name;
    this->repository = repository;
    this->mapped_to = mapped_to;
};

ostream& operator<<(ostream& os, File* file) {
    os << file->get_name();

    return os;
}

string File::get_mapped_name() const {
    return visit([](const auto& obj) -> string {
        using T = decay_t<decltype(obj)>;

        if constexpr (is_same_v<T, Function*>){
            return "Function-" + obj->get_function_name();
        } else {
            return "File-" + obj->get_name();
        }
    }, *(this->mapped_to));
}

#endif