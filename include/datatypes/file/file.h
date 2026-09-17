#ifndef __FILE_H__
#define __FILE_H__

#include <string>
#include <vector>
#include <mapping/mapped_type.h>

using namespace std;

class Repository;
class Function;

class File {
    private:
        string file_name;
        Repository* repository;
        MappedType* mapped_to;
        vector<Function*> function_list;

    public:
        File(string name, Repository* repository, MappedType* mapped_to=nullptr);
        ~File();

        string get_name() const { return file_name; };
        Repository* get_repository() const { return repository; };
        MappedType* get_mapped() const { return mapped_to; };

        void set_function_list(vector<Function*> functions){ this->function_list = functions; };
};

ostream& operator<<(ostream& os, File* file);

#endif