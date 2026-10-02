#ifndef __FILE_PARSER_H__
#define __FILE_PARSER_H__

#include <vector>
#include<iostream>
#include <filesystem>
#include <file/file.h>

#include <parser/typescript_parser/function_parser.h>

using namespace std;

vector<File*> parse_files(Repository* repository);

#endif