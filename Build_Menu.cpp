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
    build_square_1 = Square({4*w/2,77*h/80},Colors::WHITE,Colors::BLACK,h/20, w/2,"HARBOR",true);
    build_square_2 = Square({4*w/2,81*h/80},Colors::WHITE,Colors::BLACK,h/20, w/2,"LOGGING CAMP",true);
    build_square_3 = Square({4*w/2,85*h/80},Colors::WHITE,Colors::BLACK,h/20,w/2,"FARM",true);
    build_square_4 = Square({4*w/2,89*h/80},Colors::WHITE,Colors::BLACK,h/20,w/2,"MINE",true);
    build_square_5 = Square({5*w/2,77*h/80},Colors::WHITE,Colors::BLACK,h/20,w/2,"TRADING POST",true);
    build_square_6 = Square({5*w/2,81*h/80},Colors::WHITE,Colors::BLACK,h/20,w/2,"WORKSHOP",true);
    build_square_7 = Square({5*w/2,85*h/80},Colors::WHITE,Colors::BLACK,h/20,w/2,"MARKET",true);
    build_square_8 = Square({5*w/2,89*h/80},Colors::WHITE,Colors::BLACK,h/20,w/2,"BARRACKS",true);

    unit_square_1 = Square({7*w/2,77*h/80},Colors::WHITE,Colors::BLACK,h/15,w/2,"SCOUT",true);
    unit_square_2 = Square({7*w/2,83*h/80},Colors::WHITE,Colors::BLACK,h/15,w/2,"WARRIOR",true);
    unit_square_3 = Square({7*w/2,89*h/80},Colors::WHITE,Colors::BLACK,h/15,w/2,"ARCHER",true);
    unit_square_4 = Square({8*w/2,77*h/80},Colors::WHITE,Colors::BLACK,h/15,w/2,"SETTLER",true);
    unit_square_5 = Square({8*w/2,83*h/80},Colors::WHITE,Colors::BLACK,h/15,w/2,"BOAT",true);
    unit_square_6 = Square({8*w/2,89*h/80},Colors::WHITE,Colors::BLACK,h/15,w/2,"HORSEMAN",true);
}

void Build_Menu::no_active_city_draw(){
    glColor3f(Colors::WHITE.get_red(),Colors::WHITE.get_green(),Colors::WHITE.get_blue());
    glRasterPos2i(525,875);
    std::string line = "Please Select an active City you own to show Building Menu";
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c);
    }
}

void Build_Menu::draw() const {
    build_square_1.draw();
    build_square_2.draw();
    build_square_3.draw();
    build_square_4.draw();
    build_square_5.draw();
    build_square_6.draw();
    build_square_7.draw();
    build_square_8.draw();


    unit_square_1.draw();
    unit_square_2.draw();
    unit_square_3.draw();
    unit_square_4.draw();
    unit_square_5.draw();
    unit_square_6.draw();
}