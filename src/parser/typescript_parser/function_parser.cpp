#ifndef __FUNCTION_PARSER_CPP__
#define __FUNCTION_PARSER_CPP__

#include <parser/typescript_parser/function_parser.h>

using namespace std;
namespace fs = std::filesystem;

extern "C" const TSLanguage* tree_sitter_typescript();

string read_file(const fs::path& path){
    ifstream input(path);

    if(!input){
        throw runtime_error("Could not open: " + path.string());
    }

    ostringstream buffer;
    buffer << input.rdbuf();

    return buffer.str();
}

string extract_node(TSNode node, const string& file_content){
    const size_t start = ts_node_start_byte(node);
    const size_t end = ts_node_end_byte(node);

    return file_content.substr(start, end-start);
}

void parse_functions(TSNode node, const string& file_content, File& file){
    const char* type = ts_node_type(node);

    /*
    * Parsing for "regular" functions
    */ 
    if(!strcmp(type, "function_declaration")){
        TSNode name_node = ts_node_child_by_field_name(node, "name", 4);

        if(!ts_node_is_null(name_node)){
            const TSPoint start = ts_node_start_point(node);
            const TSPoint end = ts_node_end_point(node);

            file.add_function(new Function(&file, extract_node(name_node, file_content), start.row + 1, end.row + 1));
        }
    } 
    /*
    * Parsing for class methods
    */ 
    else if(!strcmp(type, "method_declaration")){
        TSNode name_node = ts_node_child_by_field_name(node, "name", 4);

        if(!ts_node_is_null(name_node)){
            const TSPoint start = ts_node_start_point(node);
            const TSPoint end = ts_node_end_point(node);

            file.add_function(new Function(&file, extract_node(name_node, file_content), start.row + 1, end.row + 1));
        }
    }

    const uint32_t child_count = ts_node_child_count(node);

    for(uint32_t i = 0; i < child_count; ++i){
        parse_functions(ts_node_child(node, i), file_content, file);
    }
}

void visit_file(File& file, const fs::path& path){
    const string file_content = read_file(path);

    TSParser* parser = ts_parser_new();

    if(!ts_parser_set_language(parser, tree_sitter_typescript())){
        ts_parser_delete(parser);
        throw runtime_error("Failed to load Typescript as parsing language");
    }

    TSTree* tree = ts_parser_parse_string(parser, nullptr, file_content.c_str(), file_content.size());

    if(tree == nullptr){
        ts_parser_delete(parser);
        throw runtime_error("Failed to parse file: " + file.get_name());
    }

    TSNode root_node = ts_tree_root_node(tree);

    parse_functions(root_node, file_content, file);

    ts_tree_delete(tree);
    ts_parser_delete(parser);
}

#endif