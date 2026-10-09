#ifndef __REPOSITORY_H__
#define __REPOSITORY_H__

#include <string>
#include <vector>
#include <git2.h>
#include <utils/status.h>

using namespace std;

class File;

class Repository {
    private:
        string repository_name;
        string location;
        Repository* mapped_to;
        vector<File*> file_list;
        git_commit* last_commit;
        Status status;

    public:
        Repository(string name, string location, Repository* mapped_to=nullptr);
        ~Repository();

        string get_repository_name() const { return repository_name; };
        string get_location() const { return location; };
        Repository* get_mapped_to_repository() const { return mapped_to; };
        vector<File*> get_file_list() const { return this->file_list; };
        size_t get_file_list_size() const { return this->file_list.size(); };
        git_commit* get_last_commit() const { return this->last_commit; };
        Status get_status() const { return this->status; };

        void set_mapped_to(Repository* repository){ this->mapped_to = repository; };
        void set_file_list(vector<File*> files){ this->file_list = files; };
        void add_file(File* file) { this->file_list.push_back(file); };
        void set_last_commit(git_commit* commit){ this->last_commit = commit; };
        void update_last_commit();
        void set_status(Status new_status){ this->status = new_status; };
};

ostream& operator<<(ostream& os, Repository* repository);

#endif