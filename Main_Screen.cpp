//


// Created by david on 4/3/2019.
//

#include "Main_Screen.h"
Main_Screen::Main_Screen() {
    game = Game();
    next_turn = Square();
    next_phase = Square();

    buildmenu = Build_Menu();

    //build_view_port = Square();
//    build_square_1 = Square();
//    build_square_2 = Square();
//    build_square_3 = Square();
//    build_square_4 = Square();
//    build_square_5 = Square();
//
//    unit_square_1 = Square();
//    unit_square_2 = Square();
//    unit_square_3 = Square();
//    unit_square_4 = Square();
//    unit_square_5 = Square();
//    unit_square_6 = Square();


    game_view_port = Square();
    piece_view_port = Square();
    tile_view_port = Square();
}

Main_Screen::Main_Screen(int h, int w, int vecx, int vecy) {
    init(h,w,vecx,vecy);
}

void Main_Screen::init(int h, int w) {
    init(h,w,8,8);
}

void Main_Screen::init(int h, int w,int x, int y) {
    set_screen_height(h);
    set_screen_width(w);
    set_center({w/2,h/2});
    game = Game(3*w/4,3*h/4,x,y);
    next_phase = Square({7*w/8,22*h/32},Colors::WHITE,Colors::BLACK,h/12,w/5, "NEXT PHASE",true);//TODO::create a next phase button, update button text with the turn we are on

    //build_view_port = Square({3*w/8,7*h/8},Colors::WHITE,Colors::BLACK,h/4,w/3,"BUILDING MENU place holder",true);
    //follow same logic for unit squares
//    build_square_1 = Square({10*w/72,62*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"FARM",true);
//    build_square_2 = Square({10*w/72,68*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"MINE",true);
//    build_square_3 = Square({16*w/72,62*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"HUNTING LODGE",true);
//    build_square_4 = Square({16*w/72,68*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"LOGGING CAMP",true);
//    build_square_5 = Square({22*w/72,62*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"MARKET",true);
//
//    unit_square_1 = Square({34*w/72,62*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"unit 1",true);
//    unit_square_2 = Square({34*w/72,68*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"unit 2",true);
//    unit_square_3 = Square({40*w/72,62*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"unit 3",true);
//    unit_square_4 = Square({40*w/72,68*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"unit 4",true);
//    unit_square_5 = Square({46*w/72,62*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"unit 5",true);
//    unit_square_6 = Square({46*w/72,68*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"unit 6",true);

    next_turn = Square({7*w/8,7*h/8},Colors::WHITE,Colors::BLACK,h/4,w/5,"Next Turn",true);
    next_turn.set_x_offset(-25);
    next_turn.set_y_offset(-25);
    game_view_port = Square({3*w/8 + Game::MAP_X_OFF,3*h/8+Game::MAP_Y_OFF},Colors::WHITE,3*h/4,3*w/4,false);
    piece_view_port = Square({7*w/8,1*h/8},Colors::WHITE,Colors::BLACK,2*h/8,w/4,"Unit Info",true);
    piece_view_port.set_y_offset(-3*h/16);
    tile_view_port = Square({7*w/8,4*h/8},Colors::WHITE,Colors::BLACK,3*h/16,w/8,"TILE INFO",true);
    tile_view_port.set_y_offset(-3*h/16);

    buildmenu = Build_Menu(62*h/72, 10*w/72);

}

void Main_Screen::draw() {
    //TODO:: build draw boxes for other phases

    game_view_port.draw();
    game.get_map().draw();//tiles have references to units, and will draw if visible
    next_turn.draw();
    next_phase.draw();
    game.phase_on_button(next_phase);

    if (game.has_active_unit()) {
        game.get_active_unit()->draw_on_viewport(piece_view_port);
    }
    if (game.has_active_tile()) {
        game.get_active_tile()->draw_on_viewport(tile_view_port);
    }
    if (game.get_phase() == "BUILD"){
        buildmenu.draw();

//        build_square_1.draw();
//        build_square_2.draw();
//        build_square_3.draw();
//        build_square_4.draw();
//        build_square_5.draw();
//
//        unit_square_1.draw();
//        unit_square_2.draw();
//        unit_square_3.draw();
//        unit_square_4.draw();
//        unit_square_5.draw();
//        unit_square_6.draw();

        //game.print_build_menu_title(build_square_3, unit_square_3);

    }
}

Screen::names Main_Screen::get_type() const {
    return Screen::MAIN_GAME;
}

void Main_Screen::clear_active() {
    game.clear_active_unit();
    game.clear_active_tile();
    piece_view_port.hide();
    tile_view_port.hide();
}

Screen::menu_options Main_Screen::check_click(Coordinate click) {
    if (next_turn.check_click(click)) {
        game.next_turn();
    }
    else if (next_phase.check_click(click) && Turn_Phase::string_to_turn_phase(game.get_phase()) != Turn_Phase::AI_TURN) {
        game.next_phase();
    }
    else {
        switch (Turn_Phase::string_to_turn_phase(game.get_phase())) {
            case (Turn_Phase::MOVE): {
                if (game_view_port.check_click(click)) {
                    process_move(click);
                }
                break;
            }

            case (Turn_Phase::BUILD): {
                if (game_view_port.check_click(click)) {
                    process_build(click);
                }
                //TODO:: implement check click options for the build squares
//                else if (build_view_port.check_click(click)) {
//                    /*
//                     * in pseudo code: we are going to have a build menu that will have a function that
//                     *                  returns the piece type of the click, which we assign to a piece_type
//                     *                  variable
//                     *                 then we switch on the piece type and call the appropriate change_city_production
//                     *                  method in main_screen.
//                     */
//                    //change_active_city_build(Building::names );
//                }
                break;
            }
        }
    }

}

std::string Main_Screen::check_winner() {
    if (game.get_player().lost()) {
        return game.get_ai().get_name_str();
    }
    if (game.get_ai().lost()) {
        return game.get_player().get_name_str();
    }
    return "NONE";
}

void Main_Screen::process_move(Coordinate click) {

    Tile *tile_clicked = &*game.get_map().get_tile_from_click(click);

    if (tile_clicked!= nullptr && tile_clicked->is_visible()) {

        if (game.has_active_unit()) {
            Unit *unit = &*game.get_active_unit();

            if (unit->get_owner() == Civilization_Name::WESTEROS) {
                if (unit->get_current_movement() > 0) {
                    if (unit->get_unit_type() == Unit::ARCHER) {
                        //get tile and get tiles available to move to with a range of 2
                        if (tile_clicked->has_unit()) {
                            std::vector<Tile *> *tiles_in_range = game.get_map().get_tiles_within_range(
                                    game.get_map().get_tile_from_id(game.get_active_unit()->get_location_id()), 2);
                            for (int i = 0; i < tiles_in_range->size(); i++) {
                                if (*((*tiles_in_range)[i]) == *tile_clicked) {
                                    //cause archer damage on unit
                                    tile_clicked->get_unit()->cause_damage(Unit::ARCHER);
                                    break;
                                }
                            }
                        }
                    } else if (unit->get_unit_type() == Unit::BOAT) {//is a non archer unit
                        //implement boat move/attack
                    } else {
                        //only do stuff if tile selected is right next to tile of unit
                        if (game.get_map().is_adjacent(*tile_clicked,
                                                       *game.get_map().get_tile_from_id(unit->get_location_id()))) {
                            //call game move unit method
                            if (game.move_active_unit(*tile_clicked)) {
                                //clear unit from active tile
                                game.get_active_tile()->clear_unit();
                                //redraw active tile
                                game.get_active_tile()->draw();

                            }

                        }
                    }//end unit type cases
                }//end if unit has movement
                clear_active();
            } else if (unit->get_owner() == Civilization_Name::NIGHT_KING) {
                clear_active();
                select_tile(tile_clicked);
            }


        }//end if has active player unit, so has no active unit, so set active tile and active unit

        else {
            select_tile(tile_clicked);
        }
    }//do nothing if tile selected is not visible
    else {

        clear_active();
    }
}

void Main_Screen::process_build(Coordinate click) {

    Tile *tile_clicked = &*game.get_map().get_tile_from_click(click);

    if (tile_clicked!= nullptr && tile_clicked->is_visible()) {
        clear_active();
        select_tile(tile_clicked);
    } else {
        clear_active();
    }
    /**
     * logic to come
     * in pseudo code
     * if a city is selected and has something to place, then if the click is on the game viewport
     *      and the tile selected is empty of buildings or cities (or enemy units) call the player's
     *      build function on active city and tile selected (which will check if tile is in range before building)
     * else if city is selected and has something to place and click is on the build menu, do nothing (have to
     *      place unit/building to be build before selecting new production)
     * if a city is selected and has nothing to place, then do clear active if click on game viewport.
     *      if click is on the building menu, then switch active city's active production to the item selected
     * if city selected, nothing to place, and click is on build, then switch production to selected item
     */
//     if(game.get_phase() == "BUILD"){
//         bool x = true;
//     }else{
//         bool x = false;
//     }
}

void Main_Screen::select_tile(Tile * tile) {
    game.set_active_tile(*tile);
    tile_view_port.reveal();
    if (game.get_active_tile_const()->has_unit()) {
        game.set_active_unit(*tile->get_unit());
        piece_view_port.reveal();
    }
}

Game* Main_Screen::get_game() {
    return &game;
}

void Main_Screen::new_game() {
    game.load("new_civs.save","new_map.save","new_tm.save");
}

Main_Screen::~Main_Screen() {
    game = Game();
    next_turn = Square();
    next_phase = Square();
    buildmenu = Build_Menu();

    //build_view_port = Square();
//    build_square_1 = Square();
//    build_square_2 = Square();
//    build_square_3 = Square();
//    build_square_4 = Square();
//    build_square_5 = Square();
//
//    unit_square_1 = Square();
//    unit_square_2 = Square();
//    unit_square_3 = Square();
//    unit_square_4 = Square();
//    unit_square_5 = Square();
//    unit_square_6 = Square();

    game_view_port = Square();
    piece_view_port = Square();
    tile_view_port = Square();
}