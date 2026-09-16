#ifndef __REPO_SELECTOR_CPP__
#define __REPO_SELECTOR_CPP__

#include <selectors/repository_selector.h>

ftxui::Component repository_selector(std::vector<std::string> &repositories_names, ftxui::App &screen, int &selector){
    ftxui::MenuOption option;
    option.on_enter = screen.ExitLoopClosure();
    ftxui::Component menu = ftxui::Menu(&repositories_names, &selector, option);

    return menu;
};

std::vector<Repository*> select_repositories(std::vector<std::vector<Repository*>> repositories_list, ftxui::App &screen, std::vector<int> &selectors){

    if(repositories_list.size() != selectors.size()){
        throw std::invalid_argument("Repository list and selector list must have the same size");
    }
    
    std::vector<ftxui::Component> menus;
    ftxui::Component container;
    std::vector<std::vector<std::string>> repositories_names_list(repositories_list.size());
    std::vector<Repository*> selected_repositories;

    menus.reserve(repositories_list.size());

    for(std::size_t i = 0; i < repositories_list.size(); i++){
        std::vector<std::string> repositories_names;

        for(std::size_t j = 0; j < repositories_list[i].size(); j++){
            repositories_names.push_back(repositories_list[i][j]->get_repository_name());
        }

        repositories_names_list[i] = repositories_names;

        menus.push_back(repository_selector(repositories_names_list[i], screen, selectors[i]));
    }

    container = ftxui::Container::Horizontal(menus);

    auto renderer = ftxui::Renderer(container, [&] {
        ftxui::Elements menu_boxes;

        for(std::size_t i = 0; i < menus.size(); i++){
            menu_boxes.push_back(menus[i]->Render()|
            ftxui::frame |
            ftxui::size(ftxui::HEIGHT, ftxui::LESS_THAN, 30));
        }

        return ftxui::hbox(menu_boxes | ftxui::xflex | ftxui::size(ftxui::HEIGHT, ftxui::LESS_THAN, 30) | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 40));
    });

    screen.Loop(renderer);

    for(std::size_t i = 0; i < repositories_list.size(); i++){
        selected_repositories.push_back(repositories_list[i][selectors[i]]);
    }

    return selected_repositories;
}

#endif