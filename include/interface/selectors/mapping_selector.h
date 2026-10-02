#ifndef __MAPPING_SELECTOR_H__
#define __MAPPING_SELECTOR_H__

#include <iostream>
#include <file/file.h>
#include <function/function.h>
#include <repository/repository.h>
#include <utils/finder.h>
#include <mapper/mapper.h>

#include "ftxui/component/app.hpp"                // for App
#include "ftxui/component/captured_mouse.hpp"     // for ftxui
#include "ftxui/component/component.hpp"          // for Menu
#include "ftxui/component/component_options.hpp"  // for MenuOption
#include "ftxui/dom/elements.hpp"                 // for hbox

using namespace std;

vector<string>* function_selector(vector<Function*> functions);

vector<ftxui::Component> file_selector(vector<File*> files, ftxui::App &screen, int &selected_file, int &selected_function);

void map_file_and_functions(Repository* origin, Repository* target, ftxui::App &screen);

#endif