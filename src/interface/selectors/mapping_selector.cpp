#ifndef __MAPPING_SELECTOR_CPP__
#define __MAPPING_SELECTOR_CPP__

#include <interface/selectors/mapping_selector.h>

#include <algorithm>
#include <filesystem>
#include <ftxui/screen/string.hpp>

using namespace std;
namespace fs = filesystem;

vector<string> function_selector(vector<Function*> functions){
    vector<string> function_names = {"FILE"};
    ftxui::Component radioboxes ;

    for(const auto& function: functions){
        function_names.push_back(function->get_name());
    }

    return function_names;
}

string visible_suffix(const string& label, int width){
    if(width <= 0){
        return {};
    }

    const vector<string> glyphs = ftxui::Utf8ToGlyphs(label);
    string result;
    int used_width = 0;

    for(auto it = glyphs.rbegin(); it != glyphs.rend(); ++it){
        const int glyph_width = ftxui::string_width(*it);
        if(used_width + glyph_width > width){
            break;
        }

        result = *it + result;
        used_width += glyph_width;
    }

    return result;
}

vector<ftxui::Component> file_selector(
    vector<File*> files,
    int& selected_function,
    int visible_width
){
    vector<ftxui::Component> radioboxes = {};

    for(size_t i = 0; i < files.size(); i++){
        auto options = ftxui::RadioboxOption::Simple();
        auto default_transform = options.transform;
        options.transform = [default_transform, visible_width](const ftxui::EntryState& state) {
            ftxui::EntryState display_state = state;
            if(state.active || state.focused){
                // The default radiobox marker uses up approximately four cells.
                display_state.label = visible_suffix(state.label, visible_width - 4);
            }

            auto row = default_transform(display_state);
            if(state.active || state.focused){
                row |= ftxui::bgcolor(ftxui::Color::Blue)
                    | ftxui::color(ftxui::Color::White);
            }
            return row;
        };

        radioboxes.push_back(ftxui::Radiobox(
            function_selector(files[i]->get_function_list()),
            &selected_function,
            options
        ));
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

    const int screen_width = screen.dimx();
    const int screen_height = screen.dimy();

    const int origin_files_width = screen_width * 30 / 100;
    const int origin_functions_width = screen_width * 20 / 100;
    const int target_files_width = screen_width * 30 / 100;
    const int target_functions_width = screen_width
        - origin_files_width
        - origin_functions_width
        - target_files_width;

    const int exit_row_height = max(1, screen_height / 10);
    const int summary_row_height = 1;
    const int mapping_height = max(
        1,
        screen_height - exit_row_height - summary_row_height - 5
    );
    const int summary_width = max(1, (screen_width - 3) / 2);

    auto selection_summary = [](const vector<File*>& files, int file_index, int function_index){
        if(file_index < 0 || file_index >= static_cast<int>(files.size())){
            return string{};
        }

        File* file = files[file_index];
        const string& path = file->get_name();
        if(function_index == 0){
            return path;
        }

        const vector<Function*> functions = file->get_function_list();
        const int function_index_in_file = function_index - 1;
        if(function_index_in_file < 0 ||
           function_index_in_file >= static_cast<int>(functions.size())){
            return path;
        }

        const string file_name = fs::path(path).filename().string();
        return functions[function_index_in_file]->get_name() + "() in " + file_name;
    };

    string user = getenv("USERNAME") ? getenv("USERNAME") : getenv("USER");

    // Build origin (left) UI component for file and function selection
    for(const auto& file: origin_file_list){
        string file_name = file->get_name();
        origin_file_names.push_back(file_name.substr(file_name.find(user) + user.length() + 1));
    }

    vector<ftxui::Component> origin_radioboxes = file_selector(
        origin_file_list, selected_origin_function, origin_functions_width
    );

    ftxui::MenuOption origin_menu_options;
    origin_menu_options.entries_option.transform =
        [origin_files_width](const ftxui::EntryState& state) {
            const bool current = state.active || state.focused;
            const string label = current
                ? visible_suffix(state.label, origin_files_width - 2)
                : state.label;
            auto row = ftxui::text(
                (state.active ? "> " : "  ") + label
            );
            if(current){
                row |= ftxui::bgcolor(ftxui::Color::Blue)
                    | ftxui::color(ftxui::Color::White);
            }
            return row;
        };

    auto origin_tab_menu = ftxui::Menu(
        &origin_file_names, &selected_origin_file, origin_menu_options
    );
    auto origin_tab_container = ftxui::Container::Tab(origin_radioboxes, &selected_origin_file);

    // Build target (right) UI component for file and function selection
    for(const auto& file: target_file_list){
        string file_name = file->get_name();
        target_file_names.push_back(file_name.substr(file_name.find(user) + user.length() + 1));
    }

    vector<ftxui::Component> target_radioboxes = file_selector(
        target_file_list, selected_target_function, target_functions_width
    );

    ftxui::MenuOption target_menu_options;
    target_menu_options.entries_option.transform =
        [target_files_width](const ftxui::EntryState& state) {
            const bool current = state.active || state.focused;
            const string label = current
                ? visible_suffix(state.label, target_files_width - 2)
                : state.label;
            auto row = ftxui::text(
                (state.active ? "> " : "  ") + label
            );
            if(current){
                row |= ftxui::bgcolor(ftxui::Color::Blue)
                    | ftxui::color(ftxui::Color::White);
            }
            return row;
        };

    auto target_tab_menu = ftxui::Menu(
        &target_file_names, &selected_target_file, target_menu_options
    );
    auto target_tab_container = ftxui::Container::Tab(target_radioboxes, &selected_target_file);

    // Exit button
    auto exit_button = ftxui::Button("Exit", screen.ExitLoopClosure());

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

    auto renderer = ftxui::Renderer(container, [&] {
        return ftxui::vbox({
            ftxui::hbox({
                ftxui::text(selection_summary(
                    origin_file_list, selected_origin_file, selected_origin_function
                ))
                    | ftxui::focusPositionRelative(1.f, 0.f)
                    | ftxui::frame
                    | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, summary_width),
                ftxui::separator(),
                ftxui::text(selection_summary(
                    target_file_list, selected_target_file, selected_target_function
                ))
                    | ftxui::focusPositionRelative(1.f, 0.f)
                    | ftxui::frame
                    | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, summary_width),
            }) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, summary_row_height),
            ftxui::separator(),
            ftxui::hbox({
                origin_tab_menu->Render()
                    | ftxui::frame
                    | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, origin_files_width),
                ftxui::separator(),
                origin_tab_container->Render()
                    | ftxui::frame
                    | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, origin_functions_width),
                ftxui::separator(),
                target_tab_menu->Render()
                    | ftxui::frame
                    | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, target_files_width),
                ftxui::separator(),
                target_tab_container->Render()
                    | ftxui::frame
                    | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, target_functions_width),
            }) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, mapping_height),
            ftxui::separator(),
            ftxui::hbox({
                exit_button->Render()
            }) | ftxui::size(ftxui::HEIGHT, ftxui::GREATER_THAN, exit_row_height)
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
                    origin_function_names.push_back(function->get_name());
                }
                
                // Case File -> ?
                if(selected_origin_function == 0){
                    File* target_file = find_file_by_name(target->get_file_list(), target_file_names[selected_target_file]);

                    // Case File -> File
                    if(selected_target_function == 0){
                        map_file_to_file(origin_file, target_file);

                    // Case File -> Function
                    } else {
                        vector<Function*> target_functions = target_file->get_function_list();
                        vector<string> target_function_names = {};

                        for(const auto& function: target_functions){
                            target_function_names.push_back(function->get_name());
                        }

                        Function* target_function = find_function_by_name(target_functions, target_function_names[selected_target_function - 1]);
                        
                        map_file_to_function(origin_file, target_function);
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
                            target_function_names.push_back(function->get_name());
                        }

                        Function* target_function = find_function_by_name(target_functions, target_function_names[selected_target_function - 1]);

                        map_function_to_function(origin_function, target_function);
                    }
                }

                selected_origin_file = 0;
                selected_origin_function = 0;
                selected_target_file = 0;
                selected_target_function = 0;

                return true;
            }

            return false;
        }
    );

    screen.Loop(enter_handler);
}

#endif
