//


// Created by david on 4/3/2019.
//

#include "Main_Screen.h"
Main_Screen::Main_Screen()
{
    game = Game();
    next_turn = Square();
    //next_phase = Square();

    build_city_button = Square();
    buildmenu = Build_Menu();
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

    //next_phase = Square({7*w/8,22*h/32},Colors::WHITE,Colors::BLACK,h/12,w/5, "NEXT PHASE",true);

    build_city_button = Square({w/16+Tile::TILE_WIDTH/2,15*h/16-Tile::TILE_HEIGHT/2},Colors::WHITE,Colors::BLACK,h/8,w/8,"Build City",false);

    next_turn = Square({7*w/8,7*h/8},Colors::WHITE,Colors::BLACK,h/4,w/4,"NEXT TURN",true);
    next_turn.set_x_offset(2*next_turn.get_x_offset());
    next_turn.set_y_offset(-15);
    next_turn.set_text_size(Square::LARGE);
    game_view_port = Square({3*w/8,3*h/8},Colors::WHITE,3*h/4,3*w/4,false);
    piece_view_port = Square({7*w/8,1*h/8},Colors::WHITE,Colors::BLACK,2*h/8,w/4,"UNIT INFO",true);
    piece_view_port.set_y_offset(-3*h/16);
    tile_view_port = Square({11*w/16-5,7*h/8},Colors::WHITE,Colors::BLACK,h/5,w/8,"TILE INFO",true);
    tile_view_port.set_y_offset(-6*h/64);
    tile_view_port.set_x_offset(tile_view_port.get_x_offset()-20);
    tile_view_port.set_text_size(Square::MEDIUM);
    city_view_port = Square({7*w/8,h/2},Colors::WHITE,Colors::BLACK,h/4,w/8,"",true);
  
    buildmenu = Build_Menu(62*h/72, 10*w/72);
}

void Main_Screen::draw() {

    game_view_port.draw();
    game.get_map().draw();//tiles have references to units, and will draw if visible

    next_turn.draw();
    //next_phase.draw();
    std::string line = "Turn: " + std::to_string(game.get_turn_manager().get_num_turns());
    Square({next_turn.get_center().x - 5, next_turn.get_center().y - 50}, Colors::WHITE, Colors::BLACK, 15, 50, line,
           true).draw();
    game.phase_on_button(next_phase);
    build_city_button.draw();

//    buildmenu.grey_out(game.get_player().get_production())
    if (game.has_active_unit()) {
        game.get_active_unit()->draw_on_viewport(piece_view_port);
    }
    if (game.has_active_tile()) {
        game.get_active_tile()->draw_on_viewport(tile_view_port);
    }
    //if the game has an active city selected
    if (game.has_active_city()) {
        //this returns the production value from draw on viewport function, keeps everything the same
       game.get_active_city()->draw_on_viewport(city_view_port);
//        std::cout << "player.prod: " << game.get_player().get_production() << std::endl;


        //buildmenu.grey_out(production);
        //draw the build menu and the cost
        buildmenu.draw();


    }
}





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
    game.clear_build_unit();
    game.clear_build_building();
    piece_view_port.hide();
    tile_view_port.hide();
    city_view_port.hide();
    buildmenu.hide();
}

Screen::menu_options Main_Screen::check_click(Coordinate click) {

    if (next_turn.check_click(click)) {
        game.next_turn();
    }
    else if (next_phase.check_click(click) && Turn_Phase::string_to_turn_phase(game.get_phase()) != Turn_Phase::AI_TURN) {
        game.next_phase();
    }

    else if (game.has_active_city()) {
        //if click is on the build menu
        if (buildmenu.check_click(click)) {
            game.clear_build_building();
            game.clear_build_unit();

            //assigns the string of what should be built to a var
            std::string to_build = buildmenu.ret_build_name(click,game.get_active_city()->get_production());

            //tests whether its a unit or a building. If it's value is equal to NONE (see if statement)
            //then that means it is the other type of piece (ie. Unit::NONE means it/s a building.)
            Building_Name::names blding = Building_Name::string_to_building_name(to_build);
            Unit::Unit_Type unit = Unit::string_to_unit_type(to_build);

            //if the blding in the menu selected is a unit (aka == none when run against the string to building name)
            if(unit != Unit::NONE){
                Unit *  new_unit = new Unit();
                new_unit->set_unit_type(unit);
                new_unit->refresh();
                game.set_build_unit(*new_unit);

                //otherwise it's a building name
            }else if (blding != Building_Name::NONE) {

                Building *new_building = new Building(blding);
                game.set_build_building(*new_building);

            }


        }
        else if (game_view_port.check_click(click) && game.has_build_piece()) {

            //get the tile clicked
            Tile *tile_clicked = &*game.get_map().get_tile_from_click(click);
            //make a vector for the city tiles
            std::vector<Tile *> city_tiles;

            //citytiles is equal to all of the active tiles for the player city
           city_tiles = game.get_active_city()->get_tiles();
            for(int i = 0; i < city_tiles.size(); i++){
                //if the tile that was clicked equals a city tile
                if(*tile_clicked == *city_tiles[i]){
                    //and if there is a unit to build
                    if(game.has_build_unit()){
                        //build the unit at that spot
                        game.add_unit(Civilization_Name::WESTEROS,&*game.get_build_unit(),tile_clicked);
                    }else if (game.has_build_building()) {
                        //otherwise, check if you can add the building there and add it
                        //(add building returns true/false depending on if it can actually be built
                        if(tile_clicked->add_building(game.get_build_building().get_name())){
                            //this function sets the production value to that - the cost of producing a building
                            game.get_active_city()->set_production(game.get_active_city()->get_production() - game.get_build_building().get_building_prod_cost());

                        }
                    }
               }
            }
            //reset all squares to white and clear all actives
            buildmenu.all_squares_white();
            clear_active();
        }
        else if (game_view_port.check_click(click)) {
            buildmenu.all_squares_white();
            process_move(click);
        }

    }
    else if(game_view_port.check_click(click) || build_city_button.check_click(click)) {//there is no active city and click is on game port

        if (game.has_active_unit() && game.get_active_unit()->get_unit_type() == Unit::SETTLER) {
            if (build_city_button.check_click(click)) {
                Tile *settler_tile = game.get_map().get_tile_from_id(game.get_active_unit()->get_location_id());
                game.build_city(Civilization_Name::WESTEROS, *settler_tile);//building a city destroys the settler
                game.reveal();
                build_city_button.hide();
            }
        }

        process_move(click);
    }

    return Screen::NONE;
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
                    if (unit->get_unit_type() == Unit::BOAT) {//todo: implement boat movement
                        //implement boat move/attack
                    } else {

                        //call game move unit method, which causes damage, and handles terrain type
                        if (game.move_active_unit(*tile_clicked)) {
                            //clear unit from active tile
                            game.get_active_tile()->clear_unit();
                            //redraw active tile
                            game.get_active_tile()->draw();

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
    //next_phase = Square();
    buildmenu = Build_Menu();


    game_view_port = Square();
    piece_view_port = Square();
    tile_view_port = Square();
}