#ifndef __MAPPING_SELECTOR_CPP__
#define __MAPPING_SELECTOR_CPP__

#include <interface/selectors/mapping_selector.h>

using namespace std;

vector<string>* function_selector(vector<Function*> functions){
    vector<string> function_names = {"FILE"};
    ftxui::Component radioboxes ;

    for(const auto& function: functions){
        function_names.push_back(function->get_function_name());
    }

    return &function_names;
}

vector<ftxui::Component> file_selector(vector<File*> files, ftxui::App &screen, int &selected_file, int &selected_function){
    vector<string> file_names = {};
    vector<ftxui::Component> radioboxes = {};

    for(size_t i = 0; i < files.size(); i++){
        file_names.push_back(files[i]->get_name());
        radioboxes.push_back(ftxui::Radiobox(function_selector(files[i]->get_function_list()), &selected_function));
    }

    return radioboxes;
    
}

void map_file_and_functions(Repository* origin, Repository* target, ftxui::App &screen){
    int selected_origin_file = 0;
    int selected_origin_function = 0;
    int selected_target_file = 0;
    int selected_target_function = 0;

    vector<string> origin_file_names = {};
    vector<string> target_file_names = {};
    vector<File*> origin_file_list = origin->get_file_list();
    vector<File*> target_file_list = target->get_file_list();

    // Build name lists of the files
    for(const auto& file: origin_file_list){
        origin_file_names.push_back(file->get_name());
    }

    for(const auto& file: target_file_list){
        target_file_names.push_back(file->get_name());
    }

    // Build origin (left) UI component for file and function selection
    vector<ftxui::Component> origin_radioboxes = file_selector(origin->get_file_list(), screen, selected_origin_file, selected_origin_function);

    auto origin_tab_menu = ftxui::Menu(&origin_file_names, &selected_origin_file);
    auto origin_tab_container = ftxui::Container::Tab(origin_radioboxes, &selected_origin_file);

    auto origin_container = ftxui::Container::Horizontal({
        origin_tab_menu,
        origin_tab_container
    });

    // Build target (right) UI component for file and function selection
    vector<ftxui::Component> target_radioboxes = file_selector(origin->get_file_list(), screen, selected_target_file, selected_target_function);

    auto target_tab_menu = ftxui::Menu(&target_file_names, &selected_target_file);
    auto target_tab_container = ftxui::Container::Tab(target_radioboxes, &selected_target_file);

    auto target_container = ftxui::Container::Horizontal({
        target_tab_menu,
        target_tab_container
    });

    // Exit button
    auto exit_button = ftxui::Button("Exit", [&] {
        screen.ExitLoopClosure();
    });

    // Build global container
    auto container = ftxui::Container::Vertical({
        ftxui::Container::Horizontal({
            origin_tab_menu,
            origin_tab_container,
            target_tab_menu,
            target_tab_container
        }),
        exit_button
    });

    auto renderer = ftxui::Renderer(origin_container, [&] {
        return ftxui::vbox({
            ftxui::hbox({
                origin_tab_menu->Render(),
                ftxui::separator(),
                origin_tab_container->Render(),
                ftxui::separator(),
                target_tab_menu->Render(),
                ftxui::separator(),
                target_tab_container->Render(),
            }),
            ftxui::separator(),
            ftxui::hbox({
                exit_button->Render()
            })
        }) | ftxui::border;
    });

    // Handle "Enter" behavior: Creates mapping, no exitting.
    // 'selected_..._file - 1' is there to compensate the index 0 in the tab that happens to be the file itself.
    auto enter_handler = ftxui::CatchEvent(
        renderer, [&](ftxui::Event event) {
            if(event == ftxui::Event::Return){
                File* origin_file = find_file_by_name(origin->get_file_list(), origin_file_names[selected_origin_file]);
                vector<Function*> origin_functions = origin_file->get_function_list();
                vector<string> origin_function_names = {};

                for(const auto& function: origin_functions){
                    origin_function_names.push_back(function->get_function_name());
                }
                
                // Case File -> ?
                if(selected_origin_function == 0){

                    // Case File -> File
                    if(selected_target_function == 0){
                        File* target_file = find_file_by_name(target->get_file_list(), target_file_names[selected_target_file]);
                        map_file_to_file(origin_file, target_file);

                    // Case File -> Function
                    } else {

                    }
                // Case Function -> ?
                } else {
                    Function* origin_function = find_function_by_name(origin_functions, origin_function_names[selected_origin_function - 1]);
                    File* target_file = find_file_by_name(target->get_file_list(), target_file_names[selected_target_file]);
                    
                    // Case Function -> File
                    if(selected_target_function == 0){
                        map_function_to_file(origin_functions[selected_origin_function - 1], target_file);

                    // Case Function -> Function
                    } else {
                        vector<Function*> target_functions = target_file->get_function_list();
                        vector<string> target_function_names = {};

                        for(const auto& function: target_functions){
                            target_function_names.push_back(function->get_function_name());
                        }

                        Function* target_function = find_function_by_name(target_functions, target_function_names[selected_target_function - 1]);

                        map_function_to_function(origin_function, target_function);
                    }
                }

                return true;
            }

            return false;
        }
    );

    screen.Loop(renderer);
}

#endif