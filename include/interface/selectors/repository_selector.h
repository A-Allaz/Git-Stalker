#ifndef __REPO_SELECTOR_H__
#define __REPO_SELECTOR_H__

#include <iostream>
#include "../../datatypes/repository/repository.h"

#include "ftxui/component/app.hpp"                // for App
#include "ftxui/component/captured_mouse.hpp"     // for ftxui
#include "ftxui/component/component.hpp"          // for Menu
#include "ftxui/component/component_options.hpp"  // for MenuOption
#include "ftxui/dom/elements.hpp"                 // for hbox

ftxui::Component repository_selector(std::vector<std::string> &repositories_names, ftxui::App &screen, int &selector);

std::vector<Repository*> select_repositories(std::vector<std::vector<Repository*>> repositories_list, ftxui::App &screen, std::vector<int> &selectors);

#endif