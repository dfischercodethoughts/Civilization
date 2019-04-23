//
// Created by willi on 4/22/19.
//

#include "Build_Menu.h"


Build_Menu::Build_Menu(){
    build_square_1 = Square();
    build_square_2 = Square();
    build_square_3 = Square();
    build_square_4 = Square();
    build_square_5 = Square();

    unit_square_1 = Square();
    unit_square_2 = Square();
    unit_square_3 = Square();
    unit_square_4 = Square();
    unit_square_5 = Square();
    unit_square_6 = Square();
}

Build_Menu::Build_Menu(int h, int w){
    build_square_1 = Square({10*w/72,62*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"FARM",true);
    build_square_2 = Square({10*w/72,68*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"MINE",true);
    build_square_3 = Square({16*w/72,62*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"HUNTING LODGE",true);
    build_square_4 = Square({16*w/72,68*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"LOGGING CAMP",true);
    build_square_5 = Square({22*w/72,62*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"MARKET",true);

    unit_square_1 = Square({34*w/72,62*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"unit 1",true);
    unit_square_2 = Square({34*w/72,68*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"unit 2",true);
    unit_square_3 = Square({40*w/72,62*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"unit 3",true);
    unit_square_4 = Square({40*w/72,68*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"unit 4",true);
    unit_square_5 = Square({46*w/72,62*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"unit 5",true);
    unit_square_6 = Square({46*w/72,68*h/72},Colors::WHITE,Colors::BLACK,h/12,w/12,"unit 6",true);
}