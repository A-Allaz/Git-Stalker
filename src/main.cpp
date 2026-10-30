#ifndef __MAIN_CPP__
#define __MAIN_CPP__

#include <cstdio>
#include <parser/typescript_parser/repository_parser.h>
#include <parser/typescript_parser/file_parser.h>
#include <parser/typescript_parser/function_parser.h>
#include <interface/debug.h>
#include <interface/selectors/repository_selector.h>
#include <interface/selectors/mapping_selector.h>
#include <storage/storage_handler.h>

using namespace std;

int main(){

    cout << "here 0" << endl;

    // Search for available repositories
    vector<Repository*> available_repositories = parse_repositories();

    cout << "here 1" << endl;

    // Retrieve saved repositories
    vector<Repository*> loaded_repositories = retrieve_data("storage.json");

    cout << "here 2" << endl;
    
    load_repositories(available_repositories, loaded_repositories);

    cout << "here 3" << endl;

    ftxui::App screen = ftxui::App::TerminalOutput();

    // Init repositories & selectors lists
    vector<vector<Repository*>> repo_list = {available_repositories, available_repositories};
    vector<int> selectors;
    for(size_t i = 0; i < repo_list.size(); i++) {
        selectors.push_back(0);
    }

    // TUI repository selector
    vector<Repository*> selected_repositories = select_repositories(repo_list, screen, selectors);
    
    // Only parse the files and functions for the selected repositories
    for(auto& repository: selected_repositories){
        vector<File*> files = parse_files(repository);
        repository->set_file_list(files);
    }

    // TUI mapper for selected repositories
    map_file_and_functions(selected_repositories[0], selected_repositories[1], screen);
    
    save_repositories(selected_repositories, "storage.json");

    // Files and functions are handled inside the repository destructor
    for(auto repository: available_repositories){
        delete repository;
    }

    return 0;
};

#endif