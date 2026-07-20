#ifndef __REPOSITORY_H__
#define __REPOSITORY_H__

#include <string>

class Repository {
    private:
        std::string repository_name;
        std::string location;
        Repository* mapped_to;

    public:
        Repository(std::string name, std::string location, Repository* mapped_to);
        ~Repository();

        std::string get_repository_name(){ return repository_name; };
        std::string get_location(){ return location; };
        Repository* get_mapped_to_repository(){ return mapped_to; };
};

#endif