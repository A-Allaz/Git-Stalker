#ifndef __STORAGE_HANDLER_CPP__
#define __STORAGE_HANDLER_CPP__

#include <storage/storage_handler.h>
#include <storage/json_handler.h>
#include <utils/finder.h>
#include <utils/logger.h>
#include <mapper/mapper.h>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

vector<Repository*> retrieve_data(){
    if(verbose > 1)
        log("Retrieving stored mapping data");

    string user = getenv("USERNAME") ? getenv("USERNAME") : getenv("USER");
    const fs::path root_dir = fs::path("/home/") / user;
    const fs::path git_stalker_dir = root_dir / ".gitstalker";
    
    fs::create_directories(git_stalker_dir / "gitstalker_mappings");

    const std::filesystem::path storage{git_stalker_dir / "gitstalker_mappings"};

    vector<Repository*> repositories = {};

    // directory_iterator can be iterated using a range-for loop
    for (auto const& dir_entry : std::filesystem::directory_iterator{storage}){
        log("Reading: " + dir_entry.path().string());

        const string file_name = (git_stalker_dir / dir_entry.path()).string();
        ifstream file(file_name);

        if(file.fail()){
            log("[ERROR] Could not open storage file: " + file_name);
        }
        
        json json;
        file >> json;

        // Parse all elements from json
        for(const auto& json_repository: json["repositories"]){
            repositories.push_back(json_to_repository(json_repository));
        }

        // Maps repositories according to json data
        for(const auto& json_repository: json["repositories"]){
            Repository* origin_repository = find_repository_by_name(repositories, json_repository["name"]);
            Repository* target_repository = find_repository_by_name(repositories, json_repository["mapped_to"]);

            vector<File*> visited_files = origin_repository->get_file_list();

            map_repositories(origin_repository, target_repository);

            for(const auto& json_file: json_repository["files"]){
                File* origin_file = find_file_by_name(visited_files, json_file["name"]);

                vector<Function*> origin_functions = origin_file->get_function_list();

                for(const auto& file_mapped_to:  json_file["mapped_to"]){
                    if(file_mapped_to["name"] != "NULL"){
                        string file_mapped_to_name = file_mapped_to["name"];
                        
                        if(file_mapped_to_name.find("FILE-") != string::npos){
                            File* target = find_file_by_name(target_repository->get_file_list(), file_mapped_to_name.erase(0,5));
                            map_file_to_file(origin_file, target);
                        } 
                        else if(file_mapped_to_name.find("FUNC-") != string::npos){
                            File* target_file = find_file_by_name(target_repository->get_file_list(), file_mapped_to["file_name"]);
                            Function* target = find_function_by_name(target_file->get_function_list(), file_mapped_to_name.erase(0,5));
                            map_file_to_function(origin_file, target);
                        }
                    }
                }

                if(json_file.contains("functions")){
                    for(const auto& json_function: json_file["functions"]){
                        Function* origin_function = find_function_by_name(origin_functions, json_function["name"]);
                        for(const auto& function_mapped_to: json_function["mapped_to"]){

                            string function_mapped_to_name = function_mapped_to["name"];

                            if(function_mapped_to_name == "NULL"){
                                break;
                            } 
                            
                            if(function_mapped_to_name.find("FILE-") != string::npos){
                                File* target = find_file_by_name(target_repository->get_file_list(), function_mapped_to_name.erase(0,5));
                                map_function_to_file(origin_function, target);
                            } 
                            else if(function_mapped_to_name.find("FUNC-") != string::npos){
                                File* target_file = find_file_by_name(target_repository->get_file_list(), function_mapped_to["file_name"]);
                                Function* target = find_function_by_name(target_file->get_function_list(), function_mapped_to_name.erase(0,5));
                                map_function_to_function(origin_function, target);
                            }
                        }
                    }
                }
            }
        }
    }

    return repositories;
}

void save_repositories(vector<Repository*> repositories){
    string user = getenv("USERNAME") ? getenv("USERNAME") : getenv("USER");
    const fs::path root_dir = fs::path("/home/") / user;
    const fs::path git_stalker_dir = root_dir / ".gitstalker";
    
    json json;
    string file_name = git_stalker_dir.string() + "/gitstalker_mappings/";

    fs::create_directories(git_stalker_dir / "gitstalker_mappings");

    for(size_t i = 0; i < repositories.size(); i++){
        file_name += repositories[i]->get_name() + (i == repositories.size() - 1 ? ".json" : "_");
        json["repositories"] += repository_to_json(*repositories[i]);
    }

    if(verbose > 0)
        log("Writing to " + file_name);

    ofstream file(file_name);
    file << json.dump(4);
}

void load_repositories(vector<Repository*>& available_repositories, vector<Repository*>& loaded_repositories){
    for(auto loaded_repo: loaded_repositories){
        Repository* tmp_repository = find_repository_by_name(available_repositories, loaded_repo->get_name());

        if(tmp_repository == nullptr){
            throw runtime_error("Could not find " + loaded_repo->get_name() + " in local filesystem");
        }

        // Look for the not-loaded repo, replace it with the newly storage-loaded one and free the not-loaded one.
        for(size_t i = 0; i < available_repositories.size(); i++){
            if(available_repositories[i]->get_name() == tmp_repository->get_name()){
                available_repositories[i] = loaded_repo;
                
                if(loaded_repo->get_last_commit() != tmp_repository->get_last_commit()){
                    loaded_repo->set_status(Status::CHANGED);

                    if(verbose > 0)
                        log("Status updated to 'CHANGED' for " + loaded_repo->get_name());
                }
                
                delete tmp_repository;

                break;
            }
        }
    }
}

#endif