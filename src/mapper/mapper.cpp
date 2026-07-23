#ifndef __MAPPER_CPP__
#define __MAPPER_CPP__

#include "../../include/mapper/mapper.h"

void map_repositories(Repository* origin, Repository* target){
    origin->set_mapped_to(target);
};

#endif