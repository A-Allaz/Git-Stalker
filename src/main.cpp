#ifndef __MAIN_CPP__
#define __MAIN_CPP__

#include <parser/typescript_parser/repository_parser.h>
#include <parser/typescript_parser/file_parser.h>
#include <parser/typescript_parser/function_parser.h>
#include <interface/debug.h>
#include <interface/selectors/repository_selector.h>
#include <interface/selectors/mapping_selector.h>
#include <storage/get_handler.h>
#include <storage/storage_handler.h>
#include <utils/logger.h>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

int main(int argc, const char * argv[]){
//-------------------------------------------------------------------------------------------------
// Log Dumping option handling and Logfile initialization
//-------------------------------------------------------------------------------------------------

    const ofstream logfile = init_logfile();
    streambuf* std_cerr = cerr.rdbuf(logfile.rdbuf());    // May be used at termination to dump the logs in the terminal

//-------------------------------------------------------------------------------------------------
// No-Head mode & Options of Git-Stalker
//-------------------------------------------------------------------------------------------------

    // Handle --verbose option

    for(int i = 1; i < argc; i++){
        if(string_view(argv[i]) == "--verbose"){
            if(i > argc - 1){
                log("[ERROR] Value must be provided for verbose");
                cerr.rdbuf(std_cerr);
                return 1;
            }

            const int value = atoi(argv[i + 1]);
            
            if(value >= 0 && value < 3){
                verbose = value;
            } else {
                log("[ERROR] Invalid value for '--verbose'. Must be between 0 and 2");
                cerr.rdbuf(std_cerr);
                return 1;
            }

            break;
        }
    }

    // Handle git-stalker's options
    for(int i = 1; i < argc; i++){
        if(string_view(argv[i]) == "--help" || string_view(argv[i]) == "-h"){
            cout << endl << "Welcome to the helper for [Git-Stalker]. You will find the available flags and their description as well as some usage examples for [Git-Stalker]" << endl << endl;
            cout << "\t--get-target\t" << "[r/F/f] [<origin>] Gives the mapping target of the <origin> repository (r), file (F) or function (f). "<< endl;
            cout << "\t            \t" << "Repository take the relative access path to the origin." << endl;
            cout << "\t            \t" << "File, the relative path to the origin file." << endl;
            cout << "\t            \t" << "Function takes the file path and origin function name." << endl;
            cout << "\t--help, -h  \t" << "Displays this helper." << endl;
            cout << "\t--verbose X \t" << "Set the verbosity for the logs. X must be between 0 and 2." << endl;
            cout << "\t--clean-logs\t" << "Clean the logs created by Git-Stalker" << endl;

            cerr.rdbuf(std_cerr);
            return 0;
        }
        else if(string_view(argv[i]) == "--clean-logs"){
            clean_logs();

            cerr.rdbuf(std_cerr);
            return 0;
        }
        else if(string_view(argv[i]) == "--get-target"){
            if(i > argc - 2){
                log("[ERROR] Must specify a target type (r=repository, F=file, f=function)");
                cerr.rdbuf(std_cerr);
                return 1;
            }
            else if(i > argc - 1){
                log("[ERROR] Must specify a target name");
                cerr.rdbuf(std_cerr);
                return 1;
            }

            if(string_view(argv[i + 1]) == "r"){ // Repository
                const fs::path origin_path = fs::absolute(argv[i + 2]).lexically_normal();
                string target_output = get_repository_target(origin_path);

                if(target_output == "NULL"){
                    cout << "Did not found any mapping target for " << argv[i + 2] << endl;
                } else {
                    cout << argv[i + 2] << " is mapped to:" << endl;
                    cout << "\t" << target_output << endl;
                }
            }
            else if(string_view(argv[i + 1]) == "F"){ // File
                const fs::path origin_path = fs::absolute(argv[i + 2]).lexically_normal();
                const vector<string> targets = get_file_target(origin_path.string());

                if(!targets.size()){
                    cout << "Did not found any mapping target for " << argv[i + 2] << endl;
                } else {
                    cout << argv[i + 2] << " is mapped to:" << endl;

                    for(const auto& target: targets){
                        cout << "\t" << target << endl;
                    }
                }
            }
            else if(string_view(argv[i + 1]) == "f"){ // Function
                if(i > argc - 3){
                    log("[ERROR] Must specify a target function name");
                    cerr.rdbuf(std_cerr);
                    return 1;
                }

                const fs::path origin_file_path = fs::absolute(argv[i + 2]).lexically_normal();
                const string origin_function_name = argv[i + 3];

                const vector<string> targets = get_function_target(origin_file_path.string(), origin_function_name);

                if(!targets.size()){
                    cout << "Did not found any mapping target for " << argv[i + 3] << " at " << argv[i + 2] << endl;
                } else {
                    cout << argv[i + 3] << " is mapped to:" << endl;

                    for(const auto& target: targets){
                        cout << "\t" << target << endl;
                    }
                }
            } else {
                log("[ERROR] Invalid target type. Must be 'r', 'F' or 'f'");
                cerr.rdbuf(std_cerr);
                return 1;
            }

            cerr.rdbuf(std_cerr);
            return 0;
        }
    }

//-------------------------------------------------------------------------------------------------
// TUI mode of Git-Stalker
//-------------------------------------------------------------------------------------------------

    // Init the log file and overwrite the std::cerr to it
    string user = getenv("USERNAME") ? getenv("USERNAME") : getenv("USER");
    fs::path root_dir = fs::path("/home/") / user;

    fs::create_directories(root_dir / ".gitstalker");

    // Search for available repositories
    vector<Repository*> available_repositories = parse_repositories();
    vector<Repository*> loaded_repositories = {};

    if(!(fs::create_directories(root_dir / ".gitstalker/gitstalker_mappings"))){
        // Stored mapping should exist
    
        // Retrieve & load saved repositories
        vector<Repository*> loaded_repositories = retrieve_data();
        load_repositories(available_repositories, loaded_repositories);
    }

    ftxui::App screen = ftxui::App::Fullscreen();
    int map_return_code = 0;

    do{
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
        map_return_code = map_file_and_functions(selected_repositories[0], selected_repositories[1], screen);
        
        save_repositories(selected_repositories);
    } while(map_return_code);

    // Files and functions are handled inside the repository destructor
    for(auto repository: available_repositories){
        delete repository;
    }

    // Return std_cerr to cerr
    cerr.rdbuf(std_cerr);

    return 0;
};

#endif