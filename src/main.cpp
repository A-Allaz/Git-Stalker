#ifndef __MAIN_CPP__
#define __MAIN_CPP__

#include <cstdio>
#include <parser/repository_parser.h>
#include <parser/file_parser.h>
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
    
    vector<File*> files = parse_files(selected_repositories[0]);
    
    print_files(files);

    return 0;
};

#endif