#ifndef __FILE_H__
#define __FILE_H__

#include <string>
#include <mapping/mapped_type.h>
#include <repository/repository.h>

using namespace std;

class File {
    private:
        string file_name;
        Repository* repository;
        MappedType* mapped_to;

    public:
        File(string name, Repository* repository, MappedType* mapped_to=nullptr);
        ~File();

        string get_name() const { return file_name; };
        Repository* get_repository() const { return repository; };
        MappedType* get_mapped() const { return mapped_to; };
};

ostream& operator<<(ostream& os, File* file);

#endif