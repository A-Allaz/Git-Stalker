#ifndef __MAPPER_CPP__
#define __MAPPER_CPP__

#include <mapper/mapper.h>

using namespace std;

void map_repositories(Repository* origin, Repository* target){
    origin->set_mapped_to(target);
};

#endif