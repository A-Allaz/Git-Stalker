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
        Repository(string name, string location, Repository* mapped_to);
        ~Repository();
        // Getters-Setters
        string get_repository_name(){ return repository_name; };
        string get_location(){ return location; };
        Repository* get_mapped_to_repository(){ return mapped_to; };

        void set_mapped_to(Repository* repository){ this->mapped_to = repository; };
        void set_file_list(vector<File*> files){ this->file_list = files; };
};

ostream& operator<<(ostream& os, Repository* repository);

#endif