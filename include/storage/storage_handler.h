#ifndef __STORAGE_HANDLER_H__
#define __STORAGE_HANDLER_H__

#include <storage/json_handler.h>

vector<Repository*> retrieve_data();

void save_repositories(vector<Repository*>);

void load_repositories(vector<Repository*>& available_repositories, vector<Repository*>& loaded_repositories);

#endif