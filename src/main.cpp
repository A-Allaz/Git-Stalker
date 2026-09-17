#ifndef __MAIN_CPP__
#define __MAIN_CPP__

#include <cstdio>
#include <parser/repository_parser.h>
#include <interface/debug.h>
#include <interface/selectors/repository_selector.h>
// #include <nlohmann/json.hpp>

using namespace std;

int main(){
    const vector<Repository*> available_repositories = parse_repositories();

    ftxui::App screen = ftxui::App::TerminalOutput();

    vector<vector<Repository*>> repo_list = {available_repositories, available_repositories};
    vector<int> selectors;
    for(size_t i = 0; i < repo_list.size(); i++) {
        selectors.push_back(0);
    }

    vector<Repository*> selected_repositories = select_repositories(repo_list, screen, selectors);
    print_repositories(selected_repositories);

    selected_repositories[0]->set_mapped_to(selected_repositories[1]);

    cout << "repository " << selected_repositories[0]->get_repository_name() << " was mapped to repository " << selected_repositories[0]->get_mapped_to_repository()->get_repository_name() << endl;

    return 0;
};

#endif