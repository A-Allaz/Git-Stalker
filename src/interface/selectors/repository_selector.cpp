#ifndef __REPO_SELECTOR_CPP__
#define __REPO_SELECTOR_CPP__

#include "../../../include/interface/selectors/repository_selector.h"

Repository* select_repository(std::vector<Repository*> repositories){
    std::vector<std::string> repositories_names = {};

    for(int i = 0; i < repositories.size(); i++){
        repositories_names.push_back(repositories[i]->get_repository_name());
    }

    auto screen = ftxui::App::TerminalOutput();
    int selected = 0;

    ftxui::MenuOption option;
    option.on_enter = screen.ExitLoopClosure();
    auto menu = ftxui::Menu(&repositories_names, &selected, option);

    screen.Loop(menu);

    return repositories[selected];
};

#endif