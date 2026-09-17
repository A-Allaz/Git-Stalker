/**
 * This file is intended for function storgae.
 * These function should not be used by the programm but can be called to get some information mid-process 
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <vector>
#include <file/file.h>

using namespace std;

void print_repository(Repository* repository);

void print_repositories(vector<Repository*> repositories, string message="list of repositories: ");

void print_file(File* file);

void print_files(vector<File*> files);

#endif