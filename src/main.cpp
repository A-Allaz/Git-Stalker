#ifndef __MAIN_CPP__
#define __MAIN_CPP__

#include "../include/parser/repository_parser.h"
#include "../include/interface/debug.h"

int main(){
    // Retrieve available repositories
    const std::vector<Repository*> available_repositories = parse_repositories();

    print_repositories(available_repositories);

    return 0;
};

#endif