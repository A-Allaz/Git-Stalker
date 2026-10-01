#ifndef __JSON_HANDLER_CPP_
#define __JSON_HANDLER_CPP_

#include <storage/json_handler.h>
#include <iostream>

using namespace std;
using json = nlohmann::json;

json function_to_json(Function& function){
    return {
        {"name", function.get_function_name()},
        {"starting_line", function.get_starting_line()},
        {"ending_line", function.get_ending_line()},
        {"mapped_to", function.get_mapped() != nullptr ? function.get_mapped_name() : "NULL" }
    };
}

json file_to_json(File& file){
    json json;
    vector<Function*> functions;

    try
    {
        functions = file.get_function_list();

        json["name"] = file.get_name();
        json["mapped_to"] = file.get_mapped_name();

        for(size_t i = 0; i < file.get_function_list_length(); i++){
            json["functions"] += function_to_json(*functions[i]);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Couldn't retrieve function list for file " << file.get_name() << " : " << e.what() << '\n';
    }

    return json;
}

json repository_to_json(Repository& repository){
    json json;
    Repository* mapped_to = repository.get_mapped_to_repository();
    vector<File*> files = repository.get_file_list();

    json["name"] = repository.get_repository_name();
    json["location"] = repository.get_location();
    json["mapped_to"] = mapped_to != nullptr ? mapped_to->get_repository_name() : "NULL";

    try{
        repository.get_file_list();
    } catch(const std::exception& e){
        std::cerr << "Couldn't retrieve function list for file " << repository.get_repository_name() << " : " << e.what() << '\n';
    }
    
    for(size_t i = 0; i < repository.get_file_list_size(); i++){
        json["files"] += file_to_json(*files[i]);
    }

    return json;
}

Function* json_to_function(json json, File* file){
    return new Function(file, json["name"], json["starting_line"], json["ending_line"]);
}

File* json_to_file(json json, Repository* repository, vector<Function*>& visited_functions){
    File* file = new File(json["name"], repository);

    for(const auto& json_function: json["functions"]){
        Function* function = json_to_function(json_function, file);

        file->get_function_list().push_back(function);
        visited_functions.push_back(function);
    }

    return file;
}

Repository* json_to_repository(json json, vector<File*>& visited_files, vector<Function*>& visited_functions){
    Repository* repository = new Repository(json["name"], json["location"]);

    for(const auto& json_file: json["files"]){
        File* file = json_to_file(json_file, repository, visited_functions);

        repository->get_file_list().push_back(file);
        visited_files.push_back(file);
    }

    return repository;
}

#endif
