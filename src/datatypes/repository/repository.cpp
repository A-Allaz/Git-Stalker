#ifndef __REPOSITORY_CPP__
#define __REPOSITORY_CPP__

#include "../../../include/datatypes/repository/repository.h"

Repository::Repository(std::string name, std:: string location, Repository* mapped_to){
    this->repository_name = name;
    this->location = location;
    this->mapped_to = mapped_to;
};

Repository::~Repository(){};

std::ostream& Repository::operator<<(std::ostream& os){
    os << this->get_repository_name() + " at " + this->get_location();
    return os;
}

#endif