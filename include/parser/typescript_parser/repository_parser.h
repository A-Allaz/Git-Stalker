#ifndef __REPOSITORY_PARSER_H__
#define __REPOSITORY_PARSER_H__

#include <vector>
#include<iostream>
#include <filesystem>
#include <repository/repository.h>

using namespace std;

vector<Repository*> parse_repositories();

#endif