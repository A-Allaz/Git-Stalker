#ifndef __JSON_HANDLER_CPP_
#define __JSON_HANDLER_CPP_

#include <storage/json_handler.h>

using namespace std;
using json = nlohmann::json;

//-------------------------------------------------------------------------------------------------
// Objects -> Storage
//-------------------------------------------------------------------------------------------------

json function_to_json(Function& function){
    vector<MappedType> mapped_list = function.get_mapped_list();

    return {
        {"name", function.get_name()},
        {"starting_line", function.get_starting_line()},
        {"ending_line", function.get_ending_line()},
        {"mapped_to", mapped_list.size() ? mapped_to_json(mapped_list) : "NULL" }
    };
}

json file_to_json(File& file){
    json json;
    vector<Function*> functions;
    vector<MappedType> mapped_list;

    try
    {
        functions = file.get_function_list();
        mapped_list = file.get_mapped_list();

        json["name"] = file.get_name();
        json["mapped_to"] = mapped_list.size() ? mapped_to_json(mapped_list) : "NULL";

        for(size_t i = 0; i < file.get_function_list_length(); i++){
            json["functions"] += function_to_json(*functions[i]);
        }
    }
    catch(const exception& e)
    {
        cerr << "Couldn't retrieve function list for file " << file.get_name() << " : " << e.what() << endl;;
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
    json["last_commit"] = git_oid_tostr_s(git_commit_id(repository.get_last_commit()));

    try{
        repository.get_file_list();
    } catch(const exception& e){
        cerr << "Couldn't retrieve function list for file " << repository.get_repository_name() << " : " << e.what() << endl;;
    }
    
    for(size_t i = 0; i < repository.get_file_list_size(); i++){
        json["files"] += file_to_json(*files[i]);
    }

    return json;
}

json mapped_to_json(vector<MappedType> mapped_to_list){
    json json;

    for(const auto& mapped_to: mapped_to_list){
        if(auto* function = get_if<Function*>(&mapped_to)){
            json += {{"name", "FUNC-" + (*function)->get_name()}};
        } else if(auto* file = get_if<File*>(&mapped_to)){
            json += {{"name", "FILE-" + (*file)->get_name()}};
        }
    }

    return json;
}


//-------------------------------------------------------------------------------------------------
// Storage -> Objects
//-------------------------------------------------------------------------------------------------

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

    git_oid oid;
    git_repository* repo = nullptr;
    git_commit* commit = nullptr;
    git_oid_fromstr(&oid, json["last_commit"].get<string>().c_str());
    git_repository_open(&repo, repository->get_location().c_str());
    git_commit_lookup(&commit, repo, &oid);
    repository->set_last_commit(commit);

    for(const auto& json_file: json["files"]){
        File* file = json_to_file(json_file, repository, visited_functions);

        repository->get_file_list().push_back(file);
        visited_files.push_back(file);
    }

    return repository;
}

#endif
