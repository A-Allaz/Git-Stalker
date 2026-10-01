#ifndef __FILE_PARSER_CPP__
#define __FILE_PARSER_CPP__

#include <parser/typescript_parser/file_parser.h>
#include <repository/repository.h>

using namespace std;
namespace fs = filesystem;

vector<File*> parse_files(Repository* repository){
    vector<File*> files;
    fs::path root_dir = fs::path("/home") / (getenv("USERNAME") ? getenv("USERNAME") : getenv("USER"));
    fs::path root = root_dir / repository->get_repository_name();

    for(auto iter = fs::recursive_directory_iterator(root); iter != fs::recursive_directory_iterator();){
        const string file_path = iter->path().string();
        if(
            file_path.find(".ts") != string::npos && 
            file_path.find("node_modules") == string::npos && 
            file_path.find(".d.ts") == string::npos && 
            file_path.find(".test.ts") == string::npos &&
            file_path.find(".tsx") == string::npos
        ){
            const string file_name = iter->path().string();
            files.push_back(new File(file_name, repository));
        }

        iter++;
    }

    return files;
}

#endif