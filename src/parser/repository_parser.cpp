#ifndef __FILE_PARSER_CPP__
#define __FILE_PARSER_CPP__

#include <vector>
#include <filesystem>
#include "../../../include/repository/repository.h"

namespace fs = std::filesystem;

std::vector<Repository*> parse_repositories(){
    std::vector<Repository*> repositories;
    fs::path root_dir = "../" + fs::current_path().string();  // Gets the asssumed home directory
    
    for(const auto &entry : fs::directory_iterator(root_dir)){
        if(entry.path().string().find(".git") != std::string::npos){
            if()
        }
    }

    return;
};

#endif