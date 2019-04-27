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
//#include "Game.h"



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
    Build_Menu();
    Build_Menu(int h, int w);
    void set_selected_square(Square sq);
    Square get_selected_square();
    void draw() const override;
    void no_active_city_draw();
    void change_active_color(Square sq);
//    void compare_selected_square(Square sq);
//    void selected_build_color(Game &game);
    void all_squares_white();
    void grey_out(int prod_val);
    Square return_square(std::string str);
    std::string ret_build_name(Coordinate click);

//        if ()
//    }


};


#endif //CIV_BUILD_MENU_H
