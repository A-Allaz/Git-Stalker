/**
 * This file is intended for function storgae.
 * These function should not be used by the programm but can be called to get some information mid-process 
 */

 #ifndef __DEBUG_H__
 #define __DEBUG_H__

 #include <vector>
 #include "../datatypes/repository/repository.h"

void print_repositories(std::vector<Repository*> repositories);

 #endif