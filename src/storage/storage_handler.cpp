#ifndef __STORAGE_HANDLER_CPP__
#define __STORAGE_HANDLER_CPP__

#include <storage/storage_handler.h>
#include <storage/json_handler.h>

vector<Repository*> retrieve_repositories(string file_name){
    ofstream file(file_name);
}

void save_repositories(vector<Repository*> repositories, string file_name){
    ofstream file(file_name);

    for(auto i=0; i < repositories.size(); i++){
        repository_to_json(*repositories[i]);
    }
}

#endif