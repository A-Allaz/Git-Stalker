#ifndef __REPOSITORY_H__
#define __REPOSITORY_H__

#include <string>
#include <vector>

using namespace std;

class File;

class Repository {
    private:
        string repository_name;
        string location;
        Repository* mapped_to;
        vector<File*> file_list;

    public:
        // Constructor-Destructor
        Repository(string name, string location, Repository* mapped_to=nullptr);
        ~Repository();
        // Getters-Setters
        string get_repository_name() const { return repository_name; };
        string get_location() const { return location; };
        Repository* get_mapped_to_repository() const { return mapped_to; };
        vector<File*> get_file_list() const { return this->file_list; };
        size_t get_file_list_size() const { return this->file_list.size(); };

        void set_mapped_to(Repository* repository){ this->mapped_to = repository; };
        void set_file_list(vector<File*> files){ this->file_list = files; };
};

ostream& operator<<(ostream& os, Repository* repository);

#endif