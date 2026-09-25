#ifndef __JSON_HANDLER_H__
#define __JSON_HANDLER_H__

#include <nlohmann/json.hpp>
#include <file/file.h>
#include <function/function.h>
#include <repository/repository.h>
#include <fstream>

using json = nlohmann::json;

json function_to_json(Function& function);

json file_to_json(File& file);

json repository_to_json(Repository& repository);

Function* json_to_function(File& file, json json);

File* json_to_file(Repository* repository, json json);

Repository* json_to_repository(json json);

#endif
