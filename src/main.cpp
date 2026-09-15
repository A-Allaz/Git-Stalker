#ifndef __MAIN_CPP__
#define __MAIN_CPP__

#include <cstdio>
#include "../include/parser/repository_parser.h"
#include "../include/interface/debug.h"
#include "../include/interface/selectors/repository_selector.h"

int main(){
    // std::freopen(".logs", "w", stdout);

    // Retrieve available repositories
    const std::vector<Repository*> available_repositories = parse_repositories();
    // print_repositories(available_repositories);

    Repository* selected_repository = select_repository(available_repositories);
    print_repository(selected_repository);

    return 0;
};

#endif