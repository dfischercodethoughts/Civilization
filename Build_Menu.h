//
// Created by willi on 4/22/19.
//

#ifndef CIV_BUILD_MENU_H
#define CIV_BUILD_MENU_H
#include "Tile.h"
#include <vector>
#include "Square.h"
#include "Unit.h"
#include "City.h"

/**
 * Build menu is used in the main screen to display build options
 */
class Build_Menu : public Square {
private:
//    int w = 1920;
//    int h = 1000;

    Square *selected_square;

    //std::vector<std::vector<Square>> build_menu;

    Square build_square_1;
    Square build_square_2;
    Square build_square_3;
    Square build_square_4;
    Square build_square_5;
    Square build_square_6;
    Square build_square_7;
    Square build_square_8;

    Square unit_square_1;
    Square unit_square_2;
    Square unit_square_3;
    Square unit_square_4;
    Square unit_square_5;
    Square unit_square_6;


public:
    //base buildmenu
    Build_Menu();

    //specifiied build menu
    Build_Menu(int h, int w);

    //stes the selected square of the build menu
    //not used
    void set_selected_square(Square sq);

    //getter function to return the selected square
    //not used
    Square get_selected_square();

    //draw function for the buildmenu
    //draws all of the squares for it and the cost on top of them
    void draw() const override;

    //draw function that printed a statement; used in an earlier iteration of our program
    //not used
    void no_active_city_draw();

    //changed the color of the active square to yellow, this was moved elsewhere
    //not used
    void change_active_color(Square sq);

    //changes all squares of the menu back to the color white
    void all_squares_white();

    //prints the the production cost of a building, accepts a square to draw on, and building name
    void print_production_cost_building(Square sq, Building_Name::names nm) const;

    //prints the production cost of a unit, accepts a square to draw on, and a unit type
    void print_production_cost_unit(Square sq, Unit::Unit_Type type) const;

    //greys out a build square if the cost to produce it is greater than players production val
    //had trouble getting this to work
    //not used
    int grey_out(int prod_val);

    //took in a string of a unit or building and returns it's square
    //not used
    Square return_square(std::string str);

    //function takes in the click coordinate and a production value
    //if the click was on the square and production is greater than production cost, select that unit
    //also colors the square yellow if it was properly selected
    std::string ret_build_name(Coordinate click, int prod);


};


#endif //CIV_BUILD_MENU_H
