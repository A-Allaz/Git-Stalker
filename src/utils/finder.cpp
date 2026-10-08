#ifndef __FINDER_CPP__
#define __FINDER_CPP__

#include <utils/finder.h>

using namespace std;

Repository* find_repository_by_name(vector<Repository*> repositories, string name){
    for(auto& repository: repositories){
        if(repository->get_repository_name() == name){
            return repository;
        }
    }

    return nullptr;
}

File* find_file_by_name(vector<File*> files, string name){
    for(auto& file: files){
        if(file->get_name() == name){
            return file;
        }
    }

    return nullptr;
}

Function* find_function_by_name(vector<Function*> functions, string name){
    for(auto& function: functions){
        if(function->get_name() == name){
            return function;
        }
    }

    return nullptr;
}

#endif