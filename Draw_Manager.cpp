//
// Created by david on 4/3/2019.
//

#include "Draw_Manager.h"

Draw_Manager::Draw_Manager() {
    start = Start_Screen();
    main = Main_Screen();
    end = End_Screen();
    pause = Pause_Screen();
    cur_screen = nullptr;
}

Draw_Manager::Draw_Manager(int h, int w, int vech, int vecw) {
    start.init(h,w);
    main.init(h,w,vech,vecw);
    pause.init(h,w);
    end.init(h,w);
    cur_screen = &start;
}

void Draw_Manager::draw() {
    switch(cur_screen->get_type()) {
        case(Screen::START_SCREEN) : {
            start.draw();
            break;
        }
        case (Screen::MAIN_GAME) : {
            main.draw();
            break;
        }
        case (Screen::END_SCREEN) : {
            end.draw();
            break;
        }
        case (Screen::PAUSE_SCREEN) : {
            pause.draw();
            break;
        }
        default : {
            start.draw();
            break;
        }
    }
}

void Draw_Manager::check_win() {
    if (main.check_winner() == main.get_game()->get_player().get_name_str()) {
        end.win();
        set_screen(Screen::END_SCREEN);
    }
    else if (main.check_winner() == main.get_game()->get_ai().get_name_str()) {
        end.lose();
        set_screen(Screen::END_SCREEN);
    }
}

int Draw_Manager::process_click(Coordinate click) {
    switch (cur_screen->get_type()) {
        case(Screen::START_SCREEN) : {
            Start_Screen::menu_options result = start.check_click(click);
            switch (result) {
                case(Screen::START_GAME) : {
                    //main.new_game(main.get_screen_height(),main.get_screen_width(),10,10);
                    set_screen(Screen::MAIN_GAME);
                    return 0;

                }
                case (Screen::EXIT_GAME) : {
                    return -1;

                }
                case (Screen::LOAD_GAME) : {
                    //filenames are hardcoded into game class
                    main.get_game()->load();
                    set_screen(Screen::MAIN_GAME);
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case (Screen::MAIN_GAME) : {
            main.check_click(click);
            check_win();
            break;
        }

        case (Screen::END_SCREEN) : {
            Screen::menu_options choice = end.check_click(click);
            switch (choice) {
                case(Screen::RETURN_TO_START) : {
                    //game = new Game();
                    set_screen(Screen::START_SCREEN);
                    return 0;
                    break;
                }
                case (Screen::EXIT_GAME) : {
                    return -1;
                    break;
                }
                default:
                    break;
            }
            break;
        }

        case (Screen::PAUSE_SCREEN) : {
            Screen::menu_options  ch = pause.check_click(click);
            switch(ch) {
                case (Screen::RETURN_TO_START) : {
                    set_screen(Screen::START_SCREEN);
                    break;
                }
                case (Screen::RETURN_TO_GAME) : {
                    set_screen(Screen::MAIN_GAME);
                    break;
                }
                case ( Screen::EXIT_GAME) : {
                    return -1;
                }
                case (Screen::SAVE_GAME) : {
                    main.get_game()->save();
                    set_screen(Screen::MAIN_GAME);
                    break;
                }
                case ( Screen::LOAD_GAME) : {
                    main.get_game()->load();
                    set_screen(Screen::MAIN_GAME);
                    break;
                }
                default:
                    break;
            }
        }
        default:
            break;
    }
    return 0;
}

void Draw_Manager::set_screen(Screen::names s) {
    switch(s) {
        case(Screen::PAUSE_SCREEN): {
            cur_screen = &pause;
            break;
        }
        case (Screen::END_SCREEN) : {
            cur_screen = &end;
            break;
        }
        case (Screen::MAIN_GAME) : {
            cur_screen = &main;
            break;
        }
        case (Screen::START_SCREEN) : {
            cur_screen = &start;
            break;
        }
        default : {
            cur_screen = &pause;
        }
    }
}

Screen * Draw_Manager::get_current_screen() {
    return cur_screen;
}

void Draw_Manager::clear_active() {
    if (cur_screen->get_type() == Screen::MAIN_GAME) {
        main.clear_active();
    }
}

Draw_Manager::~Draw_Manager() {
    cur_screen = nullptr;
    main = Main_Screen();
    start = Start_Screen();
    end = End_Screen();
    pause = Pause_Screen();
}