/**
 * This file is intended for function storgae.
 * These function should not be used by the programm but can be called to get some information mid-process 
 */

#ifndef __DEBUG_CPP__
#define __DEBUG_CPP__

#include <iostream>
#include <interface/debug.h>

void print_repository(Repository* repository){
    std::cout << repository->get_repository_name() << std::endl;
}

void print_repositories(std::vector<Repository*> repositories, std::string message){
    std::cout << message << std::endl;

    for(std::size_t i = 0; i < repositories.size(); i++){
        std::cout << "(" << i << ") " << repositories[i]->get_repository_name() << std::endl;
    }

    return;
}

#endif