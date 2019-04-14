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
    //todo: change main screen piece and tile view panels to correct place
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

int Draw_Manager::process_click(Coordinate click) {
    switch (cur_screen->get_type()) {
        case(Screen::START_SCREEN) : {
            Start_Screen::menu_options result = start.check_click(click);
            switch (result) {
                case(Screen::START_GAME) : {
                    //game = new Game();
                    set_screen(Screen::MAIN_GAME);
                    return 0;
                    break;
                }
                case (Screen::EXIT_GAME) : {
                    return -1;
                    break;
                }
                case (Screen::SAVE_GAME) : {
                    //todo: implement game save/load
                    //game.save();
                    break;
                }
                case (Screen::LOAD_GAME) : {
                    //todo: get text input, or do it hardcoded in load
                    //game.load();
                    break;
                }

            }
            break;
        }
        case (Screen::MAIN_GAME) : {
            main.check_click(click);
            break;

        }
                /**
                 * build functionality to come
                case (Main_Screen::BUILD) : {
                    std::shared_ptr<Game> temp_game = main.get_game();
                    if (temp_game->get_active_tile() != nullptr) {

                    }
                    break;
                }
                 */

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
                case (Screen::SAVE_GAME) : {
                    //todo: implement game save/load
                    //game.save();
                    break;
                }
                case (Screen::LOAD_GAME) : {
                    //todo: get text input, or do it hardcoded in load
                    //game.load();
                    break;
                }

            }
            break;
        }

        case (Screen::PAUSE_SCREEN) : {
            Screen::menu_options  ch = pause.check_click(click);
            switch(ch) {
                case (Screen::RETURN_TO_GAME) : {
                    set_screen(Screen::MAIN_GAME);
                    break;
                }
                case ( Screen::EXIT_GAME) : {
                    return -1;
                }
                case ( Screen::LOAD_GAME) : {
                    //todo:implement load game logic
                    break;
                }
            }
        }
    }
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

Draw_Manager::~Draw_Manager() {
    cur_screen = nullptr;
    main = Main_Screen();
    start = Start_Screen();
    end = End_Screen();
    pause = Pause_Screen();
}