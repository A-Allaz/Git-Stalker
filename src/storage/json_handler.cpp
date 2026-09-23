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
    // vector<Function*> functions = file.get_function_list();

    json["name"] = file.get_name();
    json["mapped_to"] = file.get_mapped_name();

    // for(size_t i = 0; i < file.get_function_list_length(); i++){
    //     json["functions"] += function_to_json(*functions[i]);
    // }

    return json;
}

json repository_to_json(Repository& repository){
    json json;
    Repository* mapped_to = repository.get_mapped_to_repository();
    vector<File*> files = repository.get_file_list();

    json["name"] = repository.get_repository_name();
    json["location"] = repository.get_location();
    json["mapped_to"] = mapped_to != nullptr ? mapped_to->get_repository_name() : "NULL";

    for(size_t i = 0; i < repository.get_file_list_size(); i++){
        json["files"] += file_to_json(*files[i]);
    }

    return json;
}

Function* json_to_function(File& file, json json){
    
    //TODO: handle the mapped_to value -> create new function/file or reference an existing one

    return new Function(&file, json["name"], json["starting_line"], json["ending_line"]);
}

File* json_to_file(Repository* repository, json json){

    //TODO: handle the mapped_to value -> create new function/file or reference an existing one

    return new File(json["name"], repository);
}

Repository* json_to_repository(json json){

    //TODO: handle mapping

    return new Repository(json["name"], json["location"]);
}

void save_repository(Repository* repository){
    ofstream file("storage.json");

    file << repository_to_json(*repository);
}

#endif
