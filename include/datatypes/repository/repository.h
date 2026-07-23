#ifndef __REPOSITORY_H__
#define __REPOSITORY_H__

#include <string>

class Repository {
    private:
        std::string repository_name;
        std::string location;
        Repository* mapped_to;

    public:
        // Constructor-Destructor
        Repository(std::string name, std::string location, Repository* mapped_to);
        ~Repository();
        // Getters-Setters
        std::string get_repository_name(){ return repository_name; };
        std::string get_location(){ return location; };
        Repository* get_mapped_to_repository(){ return mapped_to; };

        void set_mapped_to(Repository* repository){ this->mapped_to = repository; };
};

std::ostream& operator<<(std::ostream& os, Repository repository);

#endif