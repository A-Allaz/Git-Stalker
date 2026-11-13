#ifndef __MAIN_CPP__
#define __MAIN_CPP__

#include <parser/typescript_parser/repository_parser.h>
#include <parser/typescript_parser/file_parser.h>
#include <parser/typescript_parser/function_parser.h>
#include <interface/debug.h>
#include <interface/selectors/repository_selector.h>
#include <interface/selectors/mapping_selector.h>
#include <storage/storage_handler.h>
#include <utils/logger.h>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

int main(int argc, const char * argv[]){
    // Handle git-stalker's options
    for(int i = 1; i < argc; i++){
        if(string_view(argv[i]) == "--help" || string_view(argv[i]) == "-h"){
            cout << endl << "Welcome to the helper for [Git-Stalker]. You will find the available flags and their description as well as some usage examples for [Git-Stalker]" << endl << endl;
            cout << "\t--help, -h  \t" << "Displays this helper." << endl;
            cout << "\t--verbose X \t" << "Set the verbosity for the logs. X must be between 0 and 2." << endl;
            cout << "\t--clean-logs\t" << "Clean the logs created by Git-Stalker" << endl;

            return 0;
        }
        else if(string_view(argv[i]) == "--clean-logs"){
            clean_logs();

            return 0;
        }
        else if(string_view(argv[i]) == "--verbose"){
            if(argc > i){
                log("[ERROR] Value must be provided for verbose");
                return 1;
            }

            const int value = atoi(argv[i + 1]);
            
            if(value >= 0 && value < 3){
                verbose = value;
            } else {
                log("[ERROR] Invalid value for '--verbose'. Must be between 0 and 2");
                return 1;
            }

            i++;
        }
    }

    // Init the log file and overwrite the std::cerr to it
    string user = getenv("USERNAME") ? getenv("USERNAME") : getenv("USER");
    fs::path root_dir = fs::path("/home/") / user;

    fs::create_directories(root_dir / ".gitstalker");
    
    const ofstream logfile = init_logfile();

    streambuf* std_cerr = cerr.rdbuf(logfile.rdbuf());    // May be used at termination to dump the logs in the terminal

    // Search for available repositories
    vector<Repository*> available_repositories = parse_repositories();
    
    // Retrieve saved repositories
    vector<Repository*> loaded_repositories = retrieve_data("storage.json");
    
    load_repositories(available_repositories, loaded_repositories);

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

    // Return std_cerr to cerr
    cerr.rdbuf(std_cerr);

    return 0;
};

#endif