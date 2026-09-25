#ifndef __STORAGE_HANDLER_H__
#define __STORAGE_HANDLER_H__

#include <storage/json_handler.h>

vector<Repository*> retrieve_repositories(string file_name);

void save_repositories(vector<Repository*>, string file_name);

#endif