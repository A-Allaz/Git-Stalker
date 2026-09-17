/**
 * This file is intended for function storgae.
 * These function should not be used by the programm but can be called to get some information mid-process 
 */

#ifndef __DEBUG_CPP__
#define __DEBUG_CPP__

#include <iostream>
#include <interface/debug.h>

using namespace std;

void print_repository(Repository* repository){
    cout << repository << endl;
}

void print_repositories(vector<Repository*> repositories, string message){
    cout << message << endl;

    for(size_t i = 0; i < repositories.size(); i++){
        cout << "(" << i << ") " << repositories[i]->get_repository_name() << endl;
    }

    return;
}

void print_file(File* file){
    cout << file << " from " << file->get_repository() << endl;
}

void print_files(vector<File*> files){
    for(size_t i = 0; i < files.size(); i++){
        print_file(files[i]);
    }
}

#endif