#ifndef __MAPPER_H__
#define __MAPPER_H__

#include <repository/repository.h>
#include <file/file.h>
#include <function/function.h>

using namespace std;

void map_repositories(Repository* origin, Repository* target);

void map_file_to_file(File* origin, File* target);

void map_file_to_function(File* origin, Function* target);

void map_function_to_file(Function* origin, File* target);

void map_function_to_function(Function* origin, Function* target);

#endif