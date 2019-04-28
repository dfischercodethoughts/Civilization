//
// Created by david on 4/3/2019.
//

#ifndef CIV_DRAW_MANAGER_H
#define CIV_DRAW_MANAGER_H

#include "Start_Screen.h"
#include "Main_Screen.h"
#include "Pause_Screen.h"
#include "End_Screen.h"

/**
 * draw constants would allow us to have offsets/etc. I think the textures make this essentially useless
 */
 /*
namespace Draw_Constants {

    static const Coordinate UNIT_OFFSET = Coordinate(Square::TILE_WIDTH/8,-3*Square::TILE_HEIGHT/8);
    static const Coordinate TERRAIN_OFFSET = Coordinate(-3*Square::TILE_WIDTH/8,-3*Square::TILE_HEIGHT/8);
    static const Coordinate RESOURCE_OFFSET = Coordinate(-3*Square::TILE_WIDTH/8,-Square::TILE_HEIGHT/8);
    static const Coordinate BUILDING_OFFSET = Coordinate(-3*Square::TILE_WIDTH/8,Square::TILE_HEIGHT/8);
    static const Coordinate CITY_OFFSET = Coordinate(Square::TILE_WIDTH/8,Square::TILE_HEIGHT/8);
};
*/

 /**
  * draw manager owns all other classes, and is used by main directly
  */
class Draw_Manager {
private:
    Screen * cur_screen;
    Main_Screen main;
    Start_Screen start;
    End_Screen end;
    Pause_Screen pause;


public:
    /**
     * constructor
     */
    Draw_Manager();
    Draw_Manager(int h, int w, int vech, int vecw);

    /**
     * draw switches on current screen type, and draws the appropriate screen
     */
    void draw();

    /**
     * processes a click
     * @param click
     * @return -1 to exit, anything else to not
     */
    int process_click(Coordinate click);

    /**
     * if there is a winner (from main screen's get winner method
     * sets the end screen to the appropriate screen, and switches the current screen to the end scree
     */
    void check_win();

    /**
     * sets the current screen based on the input
     */
    void set_screen(Screen::names);
    Screen * get_current_screen();

    /**
     * clears active pointers in main screen (in game, really, but uses main screen's clear active())
     * for use having a keyboard shortcut to clear active pointers in game
     */
    void clear_active();

    ~Draw_Manager();
};


#endif //CIV_DRAW_MANAGER_H
