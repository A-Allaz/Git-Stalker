#ifndef __FINDER_H__
#define __FINDER_H__

#include <file/file.h>
#include <function/function.h>
#include <repository/repository.h>

using namespace std;

Repository* find_repository_by_name(vector<Repository*> repositories, string name);

File* find_file_by_name(vector<File*> files, string name);

Function* find_function_by_name(vector<Function*> functions, string name);

#endif