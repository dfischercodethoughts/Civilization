//
// Created by david on 4/3/2019.
//

#ifndef CIV_DRAW_MANAGER_H
#define CIV_DRAW_MANAGER_H

#include "Start_Screen.h"
#include "Main_Screen.h"
#include "Pause_Screen.h"
#include "End_Screen.h"

namespace Draw_Constants {

    static const Coordinate UNIT_OFFSET = Coordinate(Square::TILE_WIDTH/8,-3*Square::TILE_HEIGHT/8);
    static const Coordinate TERRAIN_OFFSET = Coordinate(-3*Square::TILE_WIDTH/8,-3*Square::TILE_HEIGHT/8);
    static const Coordinate RESOURCE_OFFSET = Coordinate(-3*Square::TILE_WIDTH/8,-Square::TILE_HEIGHT/8);
    static const Coordinate BUILDING_OFFSET = Coordinate(-3*Square::TILE_WIDTH/8,Square::TILE_HEIGHT/8);
    static const Coordinate CITY_OFFSET = Coordinate(Square::TILE_WIDTH/8,Square::TILE_HEIGHT/8);
};

class Draw_Manager {
private:
    Screen * cur_screen;
    Main_Screen main;
    Start_Screen start;
    End_Screen end;
    Pause_Screen pause;


public:
    Draw_Manager();
    Draw_Manager(int h, int w, int vech, int vecw);

    void draw();

    int process_click(Coordinate click);

    void check_win();

    void set_screen(Screen::names);
    Screen * get_current_screen();

    void clear_active();

    ~Draw_Manager();
};


#endif //CIV_DRAW_MANAGER_H
