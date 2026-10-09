#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <string>
#include <vector>
#include <mapping/mapped_type.h>
#include <utils/status.h>

class File;

using namespace std;

class Function {
    private:
        File* file;
        string function_name;
        size_t starting_line;
        size_t ending_line;
        vector<MappedType> mapped_to_list;
        Status status;

    public:
        Function(File* file, string name, size_t starting_line, size_t ending_line);
        ~Function();

        File* get_file() const { return file; };
        string get_name() const { return function_name; };
        size_t get_starting_line() const { return this->starting_line; };
        size_t get_ending_line() const { return this->ending_line; };
        vector<MappedType> get_mapped_list() const { return mapped_to_list; };
        Status get_status() const { return this->status; };

        void set_mapped_list(vector<MappedType> target_list) { this->mapped_to_list = target_list; }
        void add_mapped_to(MappedType target){ this->mapped_to_list.push_back(target); };
        void set_status(Status new_status){ this->status = new_status; };
};

#endif