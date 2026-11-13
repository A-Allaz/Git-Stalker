#ifndef __FILE_PARSER_CPP__
#define __FILE_PARSER_CPP__

#include <parser/typescript_parser/file_parser.h>
#include <utils/finder.h>
#include <repository/repository.h>
#include <utils/logger.h>

using namespace std;
namespace fs = filesystem;

vector<File*> parse_files(Repository* repository){
    vector<File*> files;
    fs::path root_dir = fs::path("/home") / (getenv("USERNAME") ? getenv("USERNAME") : getenv("USER"));
    fs::path root = root_dir / repository->get_name();

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

            File* file = new File(file_name, repository);
            File* tmp = find_file_by_name(repository->get_file_list(), file->get_name());

            if(tmp == nullptr){
                // File does not exist in prior parsing, add it to the list.
                if(verbose > 0)
                    log("File " + file_name + " does not exist in prior parsing, adding it to the repository.");

                files.push_back(file);
            } else {
                // File exist from prior parsing, just put it back.
                if(verbose > 0)
                    log("File " + file_name + " does exist in prior parsing, no changes done.");
                
                files.push_back(tmp);

                delete file;
                file = tmp;
            }

            // Parse the file functions
            visit_file(*file, file_path);
        }

        iter++;
    }

    return files;
}

#endif