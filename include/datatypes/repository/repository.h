#ifndef __REPOSITORY_H__
#define __REPOSITORY_H__

#include <string>

using namespace std;

class Repository {
    private:
        string repository_name;
        string location;
        Repository* mapped_to;

    public:
        // Constructor-Destructor
        Repository(string name, string location, Repository* mapped_to);
        ~Repository();
        // Getters-Setters
        string get_repository_name(){ return repository_name; };
        string get_location(){ return location; };
        Repository* get_mapped_to_repository(){ return mapped_to; };

        void set_mapped_to(Repository* repository){ this->mapped_to = repository; };
};

ostream& operator<<(ostream& os, Repository repository);

#endif