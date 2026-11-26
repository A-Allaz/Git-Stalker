#ifndef __GET_HANDLER_H__
#define __GET_HANDLER_H__

#include <string>

string get_repository_target(string repository_location);

vector<string>  get_file_target(string file_name);

vector<string> get_function_target(string file_path, string function_name);

#endif