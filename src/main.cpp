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

    std::vector<Repository*> selected_repositories = select_repositories(repo_list, screen, selectors);
    print_repositories(selected_repositories);

    selected_repositories[0]->set_mapped_to(selected_repositories[1]);

    std::cout << "repository " << selected_repositories[0]->get_repository_name() << " was mapped to repository " << selected_repositories[0]->get_mapped_to_repository()->get_repository_name() << std::endl;

    return 0;
};

#endif