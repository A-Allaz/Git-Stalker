/**
 * This file is intended for function storgae.
 * These function should not be used by the programm but can be called to get some information mid-process 
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <vector>
#include <repository/repository.h>

using namespace std;

void print_repository(Repository* repository);

void print_repositories(vector<Repository*> repositories, string message="list of repositories: ");

#endif