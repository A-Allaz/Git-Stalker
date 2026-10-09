#ifndef __FILE_H__
#define __FILE_H__

#include <string>
#include <vector>
#include <mapping/mapped_type.h>
#include <utils/status.h>

using namespace std;

class Repository;
class Function;

class File {
    private:
        string file_name;
        Repository* repository;
        vector<MappedType> mapped_to_list;
        vector<Function*> function_list;
        Status status;

    public:
        File(string name, Repository* repository);
        ~File();

        string get_name() const { return file_name; };
        Repository* get_repository() const { return repository; };
        vector<MappedType> get_mapped_list() const { return mapped_to_list; };
        vector<Function*> get_function_list() const { return this->function_list; }; 
        size_t get_function_list_length() const { return function_list.size(); };
        Status get_status() const { return this->status; };

        void set_function_list(vector<Function*> functions){ this->function_list = functions; };
        void set_mapped_to(vector<MappedType> mapped_to_list){ this->mapped_to_list = mapped_to_list; };
        void add_mapped_to(MappedType mapping_target){ this->mapped_to_list.push_back(mapping_target); };
        void add_function(Function* function){ this->function_list.push_back(function); };
        void set_status(Status new_status){ this->status = new_status; };
};

ostream& operator<<(ostream& os, File* file);

#endif