#ifndef __FILE_PARSER_CPP__
#define __FILE_PARSER_CPP__

#include <vector>
#include <filesystem>
#include <algorithm>
#include "../../../include/datatypes/repository/repository.h"

namespace fs = std::filesystem;

std::vector<Repository*> parse_repositories(){
    std::vector<Repository*> repositories;
    fs::path root_dir = "~" + fs::current_path().string();  // Gets the asssumed home directory
    
    for(auto iter = fs::recursive_directory_iterator(root_dir); iter != fs::recursive_directory_iterator();)
    {
        if(iter->path().string().find(".git") != std::string::npos && iter->path().string().find(".gitignore") == std::string::npos)
        {
            std::string repo_name = iter->path().parent_path().string();
            Repository* tmp = new Repository(repo_name, root_dir.string() + repo_name, nullptr);

            if(std::find(repositories.begin(), repositories.end(), tmp) == repositories.end())
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

#endif