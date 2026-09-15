#ifndef __REPO_SELECTOR_H__
#define __REPO_SELECTOR_H__

#include <iostream>
#include "../../datatypes/repository/repository.h"

#include "ftxui/component/app.hpp"                // for App
#include "ftxui/component/captured_mouse.hpp"     // for ftxui
#include "ftxui/component/component.hpp"          // for Menu
#include "ftxui/component/component_options.hpp"  // for MenuOption

Repository* select_repository(std::vector<Repository*> repositories);

#endif