#ifndef __FUNCTION_PARSER_H__
#define __FUNCTION_PARSER_H__

#include <fstream>
#include <sstream>
#include <cstring>
#include <filesystem>
#include <file/file.h>
#include <function/function.h>
#include <tree_sitter/api.h>

using namespace std;
namespace fs = std::filesystem;

extern "C" const TSLanguage* tree_sitter_typescript();

string read_file(const fs::path& path);

string extract_node(TSNode node, string& text_block);

void parse_functions(TSNode node, const string& text_block, File& file);

void visit_file(File& file, const fs::path& path);

#endif