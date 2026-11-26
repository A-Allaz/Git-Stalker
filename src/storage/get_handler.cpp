#ifndef __GET_HANDLER_CPP__
#define __GET_HANDLER_CPP__

#include <storage/storage_handler.h>
#include <storage/get_handler.h>
#include <utils/finder.h>
#include <utils/logger.h>

string get_repository_target(string repository_location){
    vector<Repository*> repositories = retrieve_data();

    log("Looking for repository " + repository_location);

    Repository* origin = find_repository_by_location(repositories, repository_location);

    if(origin != nullptr){
        return origin->get_mapped_to_repository()->get_location();
    } else {
        return "NULL";
    }
}

vector<string> get_file_target(string file_name){
    vector<Repository*> repositories = retrieve_data();
    vector<string> target_names_list = {};
    File* origin = nullptr;

    log("Looking for origin file: " + file_name);

    for(auto& repo: repositories){
        origin = find_file_by_name(repo->get_file_list(), file_name);

        // Found the file we're looking for, avoids rexritting `origin` with a nullptr value.
        if(origin != nullptr)
            break;
    }

    if(origin != nullptr){
        if(verbose > 0)
            log("Found origin file: " + origin->get_name());
    } else {
        // No origin found -> no target found.
        return target_names_list;
    }

    const vector<MappedType> target_list = origin->get_mapped_list();
    
    for(const auto& target: target_list){
        if(auto* function = get_if<Function*>(&target)){
            target_names_list.push_back((*function)->get_name() + " at file://" + (*function)->get_file()->get_name());
        } else if(auto* file = get_if<File*>(&target)){
            target_names_list.push_back((*file)->get_name());
        }
    }

    for(auto& repo: repositories){
        delete repo;
    }

    return target_names_list;
}

vector<string> get_function_target(string file_path, string function_name){
    vector<Repository*> repositories = retrieve_data();
    vector<string> target_names_list = {};
    File* origin_file = nullptr;

    log("Looking for origin function: " + function_name);

    for(auto& repo: repositories){
        origin_file = find_file_by_name(repo->get_file_list(), file_path);

        // Found the file we're looking for, avoids rexritting `origin` with a nullptr value.
        if(origin_file != nullptr)
            break;
    }

    if(origin_file != nullptr){
        if(verbose > 0)
            log("Found origin file: " + origin_file->get_name());
    } else {
        // No origin found -> no target found.
        return target_names_list;
    }

    Function* origin_function = find_function_by_name(origin_file->get_function_list(), function_name);

    if(origin_function != nullptr){
        if(verbose > 0)
            log("Found origin function: " + origin_function->get_name());
    } else {
        // No origin found -> no target found.
        return target_names_list;
    }

    const vector<MappedType> target_list = origin_function->get_mapped_list();
    
    for(const auto& target: target_list){
        if(auto* function = get_if<Function*>(&target)){
            target_names_list.push_back((*function)->get_name() + " at file://" + (*function)->get_file()->get_name());
        } else if(auto* file = get_if<File*>(&target)){
            target_names_list.push_back((*file)->get_name());
        }
    }

    for(auto& repo: repositories){
        delete repo;
    }

    return target_names_list;
}

#endif