#ifndef __REPOSITORY_CPP__
#define __REPOSITORY_CPP__

#include <function/function.h>
#include <repository/repository.h>

#include <iostream>

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

void Repository::update_last_commit(){
    git_libgit2_init();

    git_repository* repository = nullptr;
    git_reference* head = nullptr;

    int result = git_repository_open(
    &repository,
    this->get_location().c_str()
    );

    if (result < 0) {
        const git_error* error = git_error_last();

        std::cerr << "Repository path: " << this->get_location() << '\n';
        std::cerr << "libgit2 error code: " << result << '\n';

        if (error != nullptr) {
            std::cerr << "libgit2 error: " << error->message << '\n';
        }

        __throw_runtime_error("Failed to open repository");
    }
    if(git_repository_head(&head, repository)){
        __throw_runtime_error("Failed to get HEAD reference");
    }
    if(git_commit_lookup(&(this->last_commit), repository, git_reference_target(head))){
        __throw_runtime_error("Failed to get commit");
    }

    git_reference_free(head);
    git_repository_free(repository);
}

#endif