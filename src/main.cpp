#ifndef __MAIN_CPP__
#define __MAIN_CPP__

#include "./parser/repository_parser.cpp"

int main(){
    // Retrieve available repositories
    const std::vector<Repository*> available_repositories = parse_repositories();
};

#endif