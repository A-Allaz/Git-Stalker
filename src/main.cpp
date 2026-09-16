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

    ftxui::App screen = ftxui::App::TerminalOutput();

    std::vector<std::vector<Repository*>> repo_list = {available_repositories, available_repositories};
    std::vector<int> selectors;
    for(std::size_t i = 0; i < repo_list.size(); i++) {
        selectors.push_back(0);
    }

    select_repositories(repo_list, screen, selectors);

    return 0;
};

#endif