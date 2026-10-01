#ifndef __STORAGE_HANDLER_CPP__
#define __STORAGE_HANDLER_CPP__

#include <storage/storage_handler.h>
#include <storage/json_handler.h>

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

    // Maps elements according to json data

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