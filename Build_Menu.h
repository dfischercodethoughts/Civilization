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
    /**
     * constructors
     */
    Build_Menu();
    //allows setting the height and width of the base square
    Build_Menu(int h, int w);
    //sets the selected square to the square given
    void set_selected_square(Square sq);
    /**
     * @return getter for selected square
     */
    Square get_selected_square();

    /**
     * overrides square base draw method, and gives additional opetions for drawing
     */
    void draw() const override;
    void no_active_city_draw();
    void change_active_color(Square sq);
    /**
     * makes all the square white
     */
    void all_squares_white();
    void grey_out(int prod_val);
    Square return_square(std::string str);
    /**
     * @param click
     * @param production from the active city trying to build something
     * @return string of the building or unit to build, or none if not enough production
     */
    std::string ret_build_name(Coordinate click, int prod);

};


#endif //CIV_BUILD_MENU_H
