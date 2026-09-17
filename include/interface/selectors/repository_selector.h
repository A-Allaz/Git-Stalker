#ifndef __REPO_SELECTOR_H__
#define __REPO_SELECTOR_H__

#include <iostream>
#include <repository/repository.h>

#include "ftxui/component/app.hpp"                // for App
#include "ftxui/component/captured_mouse.hpp"     // for ftxui
#include "ftxui/component/component.hpp"          // for Menu
#include "ftxui/component/component_options.hpp"  // for MenuOption
#include "ftxui/dom/elements.hpp"                 // for hbox

using namespace std;

ftxui::Component repository_selector(vector<string> &repositories_names, ftxui::App &screen, int &selector);

vector<Repository*> select_repositories(vector<vector<Repository*>> repositories_list, ftxui::App &screen, vector<int> &selectors);

#endif