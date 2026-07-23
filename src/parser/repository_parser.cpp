#ifndef __FILE_PARSER_CPP__
#define __FILE_PARSER_CPP__

#include<iostream>
#include <filesystem>
#include <algorithm>
#include "../../include/parser/repository_parser.h"

namespace fs = std::filesystem;

bool is_in_vector(std::vector<Repository*> vector, Repository* repository);

std::vector<Repository*> parse_repositories(){
    std::vector<Repository*> repositories;
    fs::path root_dir = fs::current_path().string() + "/../";  // Gets the asssumed home directory
    
    for(auto iter = fs::recursive_directory_iterator(root_dir); iter != fs::recursive_directory_iterator();)
    {
        if(iter->path().string().find(".git") != std::string::npos)
        {
            const std::string repo_path = iter->path().parent_path().string();
            const std::string repo_name = repo_path.substr(repo_path.find("../") + 3);
            Repository* tmp = new Repository(repo_name, root_dir.string() + repo_name, nullptr);

            if(!is_in_vector(repositories, tmp) && !(repo_name[0] == '.')) // Not saved yet and not a hidden folder
            {
                repositories.push_back(tmp);
            } else {
                delete tmp;
            }

            // go back to the previous folder and skip loop iteration (already managed by "iter.pop()")
            iter.pop();
            continue;
        }
        iter++;
    }

    return repositories;
};

bool is_in_vector(std::vector<Repository*> vector, Repository* repository){
    for(long unsigned int i = 0; i < vector.size(); i++){
        if(vector[i]->get_repository_name() == repository->get_repository_name()){
            return true;
        }
    }
    return false;
};

#endif