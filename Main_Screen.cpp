//


// Created by david on 4/3/2019.
//

#include "Main_Screen.h"
Main_Screen::Main_Screen() {
    game = Game();
    next_turn = Square();
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
    next_turn = Square({7*w/8,7*h/8},Colors::WHITE,Colors::BLACK,h/4,w/5,"Next Turn",true);
    next_turn.set_x_offset(-25);
    next_turn.set_y_offset(-25);
    game_view_port = Square({3*w/8,3*h/8},Colors::WHITE,3*h/4,3*w/4,false);
    piece_view_port = Square({7*w/8,1*h/8},Colors::WHITE,Colors::BLACK,2*h/8,w/4,"Unit Info",true);
    piece_view_port.set_y_offset(-3*h/16);
    tile_view_port = Square({7*w/8,4*h/8},Colors::WHITE,Colors::BLACK,3*h/16,w/8,"TILE INFO",true);
    tile_view_port.set_y_offset(-3*h/16);
}

void Main_Screen::draw() {
    game_view_port.draw();
    game.get_map().draw();//tiles have references to units, and will draw if visible
    next_turn.draw();

    if (game.has_active_unit()) {
        game.get_active_unit()->draw_on_viewport(piece_view_port);
    }
    if (game.has_active_tile()) {
        game.get_active_tile()->draw_on_viewport(tile_view_port);
    }
}

Screen::names Main_Screen::get_type() const {
    return Screen::MAIN_GAME;
}

Screen::menu_options Main_Screen::check_click(Coordinate click) {
    if (game_view_port.check_click(click)) {
        //process click on a tile
         process_click(click);
    }
    else if (next_turn.check_click(click)) {
        //engage games next turn function
        game.next_turn();

    }
    return Screen::RETURN_TO_GAME;

    //todo: implement next phase button, build button, buy button,
}

void Main_Screen::process_click(Coordinate click) {
    /**
     * if a unit is selected, either the tile clicked on is in range or out of range
     * if tile clicked on next to tile of active unit, move there
     */
     if (game.get_active_unit() != nullptr) {
         Unit * unit = &*game.get_active_unit();
         Tile *tile_clicked = &*game.get_map().get_tile_from_click(click);
         if(unit->get_current_movement() > 0) {
             if (unit->get_unit_type() == Unit::ARCHER) {
                 //get tile and get tiles available to move to with a range of 2
                 if (tile_clicked->has_unit()) {
                     std::vector<Tile *>* tiles_in_range = game.get_map().get_tiles_within_range(
                             game.get_map().get_tile_from_id(game.get_active_unit()->get_location_id()), 3);
                     for (int i = 0; i < tiles_in_range->size(); i++) {
                         if (*((*tiles_in_range)[i]) == *tile_clicked) {
                             //cause archer damage on unit
                             tile_clicked->get_unit()->cause_damage(Unit::ARCHER);
                             break;
                         }
                     }
                 }

             }
             else if (unit->get_unit_type() == Unit::BOAT) {//is a non archer unit
                 //implement boat move/attack
             }
             else {
                 //only do stuff if tile selected is right next to tile of unit
                 if (game.get_map().is_adjacent(*tile_clicked,*game.get_map().get_tile_from_id(unit->get_location_id()))) {
                     if (tile_clicked->has_unit() && tile_clicked->get_unit()->get_owner() != Civilization_Name::WESTEROS) {
                         tile_clicked->get_unit()->cause_damage(unit->get_unit_type());
                         unit->cause_damage(tile_clicked->get_unit()->get_unit_type());
                     }
                     else {
                         //set unit to new tile
                         if (game.move_active_unit(*tile_clicked)) {
                             //reveal the tiles around the units new location
                            // game.reveal_unit(game.get_active_unit());
                             //clear unit from active tile
                             game.get_active_tile()->clear_unit();
                             //redraw active tile
                             game.get_active_tile()->draw();
                             game.clear_active_unit();
                             game.clear_active_tile();
                         }

                     }
                 }
             }
         }
         else {//current unit has no movement left, so clear the selection
             game.clear_active_tile();
             tile_view_port.hide();
             game.clear_active_unit();
             piece_view_port.hide();
         }
     }//game has no current unit, so select the tile and unit clicked on
     else {
         game.set_active_tile(*game.get_map().get_tile_from_click(click));
         tile_view_port.reveal();
         if (game.get_active_tile_const()->has_unit()) {
             game.set_active_unit(*game.get_map().get_tile_from_click(click)->get_unit());
            piece_view_port.reveal();
         }
     }
}

Game* Main_Screen::get_game() {
    return &game;
}

Main_Screen::~Main_Screen() {
    game = Game();
    next_turn = Square();
    game_view_port = Square();
    piece_view_port = Square();
    tile_view_port = Square();
}