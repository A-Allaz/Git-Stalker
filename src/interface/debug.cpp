/**
 * This file is intended for function storgae.
 * These function should not be used by the programm but can be called to get some information mid-process 
 */

 #ifndef __DEBUG_CPP__
 #define __DEBUG_CPP__

 #include <iostream>
 #include "../../include/interface/debug.h"

void print_repositories(std::vector<Repository*> repositories){
    std::cout << "Parsed Repositories: " << std::endl;
    
    for(unsigned int i = 0; i < repositories.size(); i++){
        std::cout << "(" << i << ") " << repositories[i]->get_repository_name() << std::endl;
    }

    return;
}

 #endif