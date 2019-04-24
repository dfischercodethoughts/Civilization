//
// Created by willi on 4/22/19.
//

#ifndef CIV_BUILD_MENU_H
#define CIV_BUILD_MENU_H
#include "Tile.h"
#include <vector>
#include "Square.h"



class Build_Menu : public Square {
private:
    int w = 1920;
    int h = 1000;

    std::vector<std::vector<Square>> build_menu;


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
    void draw() const override;
    void no_active_city_draw();

//    void grey_out(int prod_val){
//        if ()
//    }


};


#endif //CIV_BUILD_MENU_H
