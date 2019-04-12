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
            /**
            switch (choice) {
                case (Main_Screen::NEXT_TURN): {
                    Game * temp_game = main.get_game();
                    temp_game -> set_phase(Turn_Phase::AI_TURN);
                    temp_game->next_turn();
                    temp_game->set_phase(Turn_Phase::MOVE);
                    break;
                }
                case (Main_Screen::SELECT_TILE) : {

                    Game* temp_game = main.get_game();
                    Tile * temp_tile = &*temp_game->get_map().get_tile_from_click(click);
                    //if a player unit on the tile, select the unit
                    //todo:fix line
                    std::unique_ptr<Unit> temp = std::make_unique<Unit>(temp_tile->get_unit());
                    if (temp_tile->get_unit()->get_unit_type() != Unit::NONE & temp_tile->get_unit()->get_owner()==Civilization_Name::WESTEROS) {
                        temp_game->set_active_unit(*temp.get());
                    }
                    //if a unit is selected and can move
                    else if (temp_game->get_active_unit()!=nullptr & (temp_game->get_active_unit()->get_current_movement() > 0)) {
                        //if there is not a friendly unit on the tile, move there
                        if (temp_tile->get_unit()->get_unit_type() != Unit::NONE & temp_tile->get_unit()->get_owner()!=Civilization_Name::WESTEROS) {
                            //attack handled in game
                            temp_game->move_active_unit(*temp_tile);
                        }
                        //no unit on the tile, move there
                        else if (temp_tile->get_unit()->get_unit_type()== Unit::NONE) {
                            temp_game->move_active_unit(*temp_tile);
                        }
                        temp_game->clear_active_unit();
                    }
                    //a unit is selected and cant move
                    else if (temp_game->get_active_unit()!=nullptr) {
                        temp_game->clear_active_unit();
                    }
                    //otherwise, select this tile
                    else {
                        temp_game -> set_active_tile(*temp_tile);
                    }
                    break;
                }
                */
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