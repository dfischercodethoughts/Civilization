//
// Created by willi on 4/22/19.
//

#ifndef CIV_BUILD_MENU_H
#define CIV_BUILD_MENU_H
#include "Tile.h"
#include "Square.h"



class Build_Menu : public Square {
private:
    Square build_square_1;
    Square build_square_2;
    Square build_square_3;
    Square build_square_4;
    Square build_square_5;

    Square unit_square_1;
    Square unit_square_2;
    Square unit_square_3;
    Square unit_square_4;
    Square unit_square_5;
    Square unit_square_6;
public:
    Build_Menu();
    Build_Menu(int h, int w);

};


#endif //CIV_BUILD_MENU_H
