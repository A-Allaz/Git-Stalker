#ifndef __JSON_HANDLER_H__
#define __JSON_HANDLER_H__

#include <nlohmann/json.hpp>
#include <file/file.h>
#include <function/function.h>
#include <repository/repository.h>
#include <fstream>
#include <iostream>
#include <mapping/mapped_type.h>

using json = nlohmann::json;

json function_to_json(Function& function);

json file_to_json(File& file);

json repository_to_json(Repository& repository);

json mapped_to_json(vector<MappedType> mapped_to_list);

Function* json_to_function(json json, File* file);

File* json_to_file(json json, Repository* repository, vector<Function*>& visited_functions);

Repository* json_to_repository(json json, vector<File*>& visited_files, vector<Function*>& visited_functions);

#endif
