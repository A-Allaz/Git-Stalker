#ifndef __STORAGE_HANDLER_CPP__
#define __STORAGE_HANDLER_CPP__

#include <storage/storage_handler.h>
#include <storage/json_handler.h>
#include <utils/finder.h>
#include<mapper/mapper.h>

using namespace std;

vector<Repository*> retrieve_data(string file_name){
    ifstream file(file_name);
    json json;
    file >> json;

    vector<Repository*> repositories = {};

    // Temporary lists to handle the mapping
    vector<File*> visited_files = {};
    vector<Function*> visited_functions = {};

    // Parse all elements from json
    for(const auto& json_repository: json["repositories"]){
        repositories.push_back(json_to_repository(json_repository, visited_files, visited_functions));
    }

    // Maps repositories according to json data
    for(const auto& json_repository: json["repositories"]){
        Repository* origin = find_repository_by_name(repositories, json_repository["name"]);
        Repository* target = find_repository_by_name(repositories, json_repository["mapped_to"]);

        map_repositories(origin, target);

        for(const auto& json_file: json_repository["files"]){
            File* origin = find_file_by_name(visited_files, json_file["name"]);
            string file_mapped_to_name = json_file["mapped_to"];

            if(file_mapped_to_name.find("NULL") != string::npos){
                break;
            } 
            else if(file_mapped_to_name.find("FILE-") != string::npos){
                File* target = find_file_by_name(visited_files, file_mapped_to_name.erase(0,5));
                map_file_to_file(origin, target);
            } 
            else if(file_mapped_to_name.find("FUNC-") != string::npos){
                Function* target = find_function_by_name(visited_functions, file_mapped_to_name.erase(0,5));
                map_file_to_function(origin, target);
            }

            for(const auto& json_function: json_file["functions"]){
                Function* origin = find_function_by_name(visited_functions, json_file["name"]);
                string function_mapped_to_name = json_function["mapped_to"];

                if(function_mapped_to_name.find("NULL") != string::npos){
                    break;
                } 
                else if(function_mapped_to_name.find("FILE-") != string::npos){
                    File* target = find_file_by_name(visited_files, function_mapped_to_name.erase(0,5));
                    map_function_to_file(origin, target);
                } 
                else if(function_mapped_to_name.find("FUNC-") != string::npos){
                    Function* target = find_function_by_name(visited_functions, function_mapped_to_name.erase(0,5));
                    map_function_to_function(origin, target);
                }
            }
        }
    }

    return repositories;
}

void save_repositories(vector<Repository*> repositories, string file_name){
    json json;

    for(size_t i = 0; i < repositories.size(); i++){
        json["repositories"] += repository_to_json(*repositories[i]);
    }

    ofstream file(file_name);
    file << json.dump(4);
}

#endif