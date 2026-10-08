#ifndef __MAPPER_CPP__
#define __MAPPER_CPP__

#include <mapper/mapper.h>
#include <iostream>

using namespace std;

void map_repositories(Repository* origin, Repository* target){
    origin->set_mapped_to(target);
};

void map_file_to_file(File* origin, File* target){
    origin->add_mapped_to(target);
};

void map_file_to_function(File* origin, Function* target){
    origin->add_mapped_to(target);
};

void map_function_to_file(Function* origin, File* target){
    origin->add_mapped_to(target);
};

void map_function_to_function(Function* origin, Function* target){
    origin->add_mapped_to(target);
};

#endif