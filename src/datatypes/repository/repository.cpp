#ifndef __REPOSITORY_CPP__
#define __REPOSITORY_CPP__

#include <function/function.h>
#include <repository/repository.h>

using namespace std;

Repository::Repository(string name,  string location, Repository* mapped_to){
    this->repository_name = name;
    this->location = location;
    this->mapped_to = mapped_to;
};

Repository::~Repository(){};

ostream& operator<<(ostream& os, Repository* repository){
    os << repository->get_repository_name();
    return os;
}

#endif