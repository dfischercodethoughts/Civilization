//


// Created by david on 4/3/2019.
//

#include "Main_Screen.h"
Main_Screen::Main_Screen() {
    game = Game();
    next_turn = Square();
    next_phase = Square();

    build_city_button = Square();
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
    city_view_port = Square();
}

Main_Screen::Main_Screen(int h, int w, int vecx, int vecy) {
    init(h,w,vecx,vecy);
}

void Main_Screen::init(int h, int w) {
    init(h,w,10,10);
}

void Main_Screen::init(int h, int w,int x, int y) {
    set_screen_height(h);
    set_screen_width(w);
    set_center({w/2,h/2});
    game = Game(3*w/4,3*h/4,x,y);

    next_phase = Square({7*w/8,22*h/32},Colors::WHITE,Colors::BLACK,h/12,w/5, "NEXT PHASE",true);

    build_city_button = Square({w/16+Tile::TILE_WIDTH/2,15*h/16-Tile::TILE_HEIGHT/2},Colors::WHITE,Colors::BLACK,h/8,w/8,"Build City",false);


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

    next_turn = Square({7*w/8,7*h/8},Colors::WHITE,Colors::BLACK,h/4,w/4,"NEXT TURN",true);
    next_turn.set_x_offset(2*next_turn.get_x_offset());
    next_turn.set_y_offset(-15);
    next_turn.set_text_size(Square::LARGE);
    game_view_port = Square({3*w/8,3*h/8},Colors::WHITE,3*h/4,3*w/4,false);
    piece_view_port = Square({7*w/8,1*h/8},Colors::WHITE,Colors::BLACK,2*h/8,w/4,"UNIT INFO",true);
    piece_view_port.set_y_offset(-3*h/16);
    tile_view_port = Square({11*w/16-5,7*h/8},Colors::WHITE,Colors::BLACK,h/4,w/8,"TILE INFO",true);
    tile_view_port.set_y_offset(-6*h/64);
    tile_view_port.set_x_offset(tile_view_port.get_x_offset()-20);
    tile_view_port.set_text_size(Square::MEDIUM);
    city_view_port = Square({7*w/8,h/2},Colors::WHITE,Colors::BLACK,h/4,w/8,"",true);
  
    buildmenu = Build_Menu(62*h/72, 10*w/72);
}

void Main_Screen::draw() {

    //TODO:: build draw boxes for other phases

    game_view_port.draw();
    game.get_map().draw();//tiles have references to units, and will draw if visible

    next_turn.draw();
    next_phase.draw();
    std::string line = "Turn: " + std::to_string(game.get_turn_manager().get_num_turns());
    Square({next_turn.get_center().x-5,next_turn.get_center().y-50},Colors::WHITE,Colors::BLACK,15,50,line,true).draw();
    game.phase_on_button(next_phase);
    build_city_button.draw();

    if (game.has_active_unit()) {
        game.get_active_unit()->draw_on_viewport(piece_view_port);
    }
    if (game.has_active_tile()) {
        game.get_active_tile()->draw_on_viewport(tile_view_port);
    }
    if (game.has_active_city()) {
        game.get_active_city()->draw_on_viewport(city_view_port);

  //TODO:: figure out how to get player production (it works with hard coded values but not game.act city -> get prod or any forms of that)
        //buildmenu.grey_out(35);
        //buildmenu.selected_build_color(game);
     //   buildmenu.change_active_color(buildmenu.get_selected_square());
//        buildmenu.compare_selected_square(buildmenu.get_selected_square());
//        buildmenu.grey_out(game.get_active_city()->get_production());
        //buildmenu.grey_out(game.get_active_city()->get_production());
        buildmenu.draw();

    }


//        build_square_1.draw();
//        build_square_2.draw();
//        build_square_3.draw();
//        build_square_4.draw();
//        build_square_5.draw();

    }
    //&& game.has_active_city()
//    if (game.get_phase() == "BUILD" ) {
////grey (beige) out works
////TODO:: figure out how to get player production
////TODO:: figure out how to get an active city after it's clicked on
//        buildmenu.grey_out(35);
//        buildmenu.draw();
//    }
//    }else if (game.get_phase() == "BUILD" && (!game.has_active_city())){
//            buildmenu.no_active_city_draw();

//
//        }






Screen::names Main_Screen::get_type() const {
    return Screen::MAIN_GAME;
}

void Main_Screen::clear_active() {
    if (game.has_active_unit() && game.get_active_unit()->get_unit_type() == Unit::SETTLER) {
        build_city_button.hide();
    }
    game.clear_active_unit();
    game.clear_active_tile();
    game.clear_active_city();
    piece_view_port.hide();
    tile_view_port.hide();
    city_view_port.hide();
    buildmenu.hide();
}

Screen::menu_options Main_Screen::check_click(Coordinate click) {
    std::string to_build;
    Building_Name::names blding;
    Unit::Unit_Type unit;

    if (next_turn.check_click(click)) {
        game.next_turn();

    }
    else if (next_phase.check_click(click) && Turn_Phase::string_to_turn_phase(game.get_phase()) != Turn_Phase::AI_TURN) {
        game.next_phase();
    }

    else if (game.has_active_city()) {
        //if click is on the build menu
        if (buildmenu.check_click(click)) {
//TODO::write function that takes in a square and a game function that draws it a different color if it is selected
            //returns the string of the build_menu sqaure clicked
            to_build = buildmenu.ret_build_name(click);
//            blding = Building_Name::string_to_building_name(to_build);
//            unit = Unit::string_to_unit_type(to_build);

            //if the blding in the menu selected is a unit (aka == none when run against the string to building name)
//            if(blding == Building_Name::NONE){
//                Unit new_unit = Unit();
//                new_unit.set_unit_type(unit);
//                game.set_build_unit(new_unit);
//                //otherwise it's a building name
//            }else{
//                Building new_building = Building(blding);
//                game.set_build_building(new_building);
//            }



            //if the cost of the square clicked is less than the amount of production the active city has
            //make the appropriate unit or building (internally), and set it to the appropriate build pointer in game
        }
        else if (game_view_port.check_click(click) && game.has_build_piece()) {
            //buildmenu.all_squares_white();
            //else if click is on the game viewport and there's a building or unit to build
            //if tile clicked is within the tiles that the city controls, try to build the building or
            //unit selected on the tile clicked
            //clear all active
        }
        else if (game_view_port.check_click(click)) {
            //else if click is on game viewport and there is no building or unit to build
            //go to move unit/select tile logic
            process_move(click);
        }

    }
    else if(game_view_port.check_click(click) || build_city_button.check_click(click)) {//there is no active city and click is on game port

        if (game.has_active_unit() && game.get_active_unit()->get_unit_type() == Unit::SETTLER) {
            if (build_city_button.check_click(click)) {
                Tile *settler_tile = game.get_map().get_tile_from_id(game.get_active_unit()->get_location_id());
                game.build_city(Civilization_Name::WESTEROS, *settler_tile);//building a city destroys the settler
                game.reveal();
            }
        }

        process_move(click);
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
                    clear_active();
                }//end if unit has movement

                clear_active();
                select_tile(tile_clicked);


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
        if (game.get_active_unit()->get_unit_type() == Unit::SETTLER) {
            build_city_button.reveal();
        }
        piece_view_port.reveal();
    }
    if (game.get_active_tile()->has_city()) {
        if (game.get_active_tile()->get_owner() == Civilization_Name::WESTEROS) {
            game.set_active_city(*game.get_player().get_city(game.get_active_tile()->get_id()));
        }
        else if (game.get_active_tile()->get_owner() == Civilization_Name::NIGHT_KING) {
            game.set_active_city(*game.get_ai().get_city(game.get_active_tile()->get_id()));
        }
        buildmenu.reveal();
        city_view_port.reveal();
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