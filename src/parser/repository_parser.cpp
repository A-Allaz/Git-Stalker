#ifndef __REPOSITORY_PARSER_CPP__
#define __REPOSITORY_PARSER_CPP__

#include <parser/repository_parser.h>

using namespace std;
namespace fs = filesystem;

bool is_in_vector(vector<Repository*> vector, Repository* repository);

vector<Repository*> parse_repositories(){
    vector<Repository*> repositories;
    string user = getenv("USERNAME") ? getenv("USERNAME") : getenv("USER");
    fs::path root_dir = fs::path("/home") / user;  // Gets the home directory of the assumed user
    
    for(auto iter = fs::recursive_directory_iterator(root_dir); iter != fs::recursive_directory_iterator();)
    {
        if(iter->path().string().find(".git") != string::npos)
        {
            const string repo_path = iter->path().parent_path().string();
            const string repo_name = repo_path.substr(repo_path.find(user) + user.length() + 1);
            Repository* tmp = new Repository(repo_name, root_dir.string() + repo_name, nullptr);

            if(!is_in_vector(repositories, tmp) && !(repo_name[0] == '.')) // Not saved yet and not a hidden folder
            {
                repositories.push_back(tmp);
            } else {
                delete tmp;
            }

            // go back to the previous folder and skip loop iteration (already managed by "iter.pop()")
            iter.pop();
            continue;
        }

        iter++;
    }

    return repositories;
};

bool is_in_vector(vector<Repository*> vector, Repository* repository){
    for(long unsigned int i = 0; i < vector.size(); i++){
        if(vector[i]->get_repository_name() == repository->get_repository_name()){
            return true;
        }
    }
    return false;
};

#endif