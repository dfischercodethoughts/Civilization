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
    build_square_6 = Square();
    build_square_7 = Square();
    build_square_8 = Square();

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

    unit_square_1 = Square({7*w/2,77*h/80},Colors::WHITE,Colors::BLACK,h/15,w/2,"BOAT",true);
    unit_square_2 = Square({7*w/2,83*h/80},Colors::WHITE,Colors::BLACK,h/15,w/2,"WARRIOR",true);
    unit_square_3 = Square({7*w/2,89*h/80},Colors::WHITE,Colors::BLACK,h/15,w/2,"ARCHER",true);
    unit_square_4 = Square({8*w/2,77*h/80},Colors::WHITE,Colors::BLACK,h/15,w/2,"HORSEMAN",true);
    unit_square_5 = Square({8*w/2,83*h/80},Colors::WHITE,Colors::BLACK,h/15,w/2,"PLACE HOLD",true);
    unit_square_6 = Square({8*w/2,89*h/80},Colors::WHITE,Colors::BLACK,h/15,w/2,"PLACE HOLD",true);
}

void Build_Menu::no_active_city_draw(){
    glColor3f(Colors::WHITE.get_red(),Colors::WHITE.get_green(),Colors::WHITE.get_blue());
    glRasterPos2i(525,875);
    std::string line = "Please Select an active City you own to show Building Menu";
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c);
    }
}

//go through, compare the prod_val (how much production the city has)
//against the values of all of the squares
//this would work better as an array/vector but for the sake of not messing anything up we hard coding
//beige for now until I can figure out what grey is
void Build_Menu::grey_out(int prod_val) {
    //greater than 60 notihing needs to happen
    if(prod_val >= 50 && prod_val < 60){
        build_square_8.set_fill(Colors::BEIGE);

        unit_square_5.set_fill(Colors::BEIGE);
        unit_square_6.set_fill(Colors::BEIGE);
    }else if(prod_val >= 40 && prod_val < 50){

        build_square_6.set_fill(Colors::BEIGE);
        build_square_7.set_fill(Colors::BEIGE);
        build_square_8.set_fill(Colors::BEIGE);

        unit_square_4.set_fill(Colors::BEIGE);
        unit_square_5.set_fill(Colors::BEIGE);
        unit_square_6.set_fill(Colors::BEIGE);
    }else if(prod_val >= 30 && prod_val < 40){

        build_square_3.set_fill(Colors::BEIGE);
        build_square_4.set_fill(Colors::BEIGE);
        build_square_5.set_fill(Colors::BEIGE);
        build_square_6.set_fill(Colors::BEIGE);
        build_square_7.set_fill(Colors::BEIGE);
        build_square_8.set_fill(Colors::BEIGE);

        unit_square_3.set_fill(Colors::BEIGE);
        unit_square_4.set_fill(Colors::BEIGE);
        unit_square_5.set_fill(Colors::BEIGE);
        unit_square_6.set_fill(Colors::BEIGE);

    }else if(prod_val >= 20 && prod_val < 30){

        build_square_2.set_fill(Colors::BEIGE);
        build_square_3.set_fill(Colors::BEIGE);
        build_square_4.set_fill(Colors::BEIGE);
        build_square_5.set_fill(Colors::BEIGE);
        build_square_6.set_fill(Colors::BEIGE);
        build_square_7.set_fill(Colors::BEIGE);
        build_square_8.set_fill(Colors::BEIGE);

        unit_square_2.set_fill(Colors::BEIGE);
        unit_square_3.set_fill(Colors::BEIGE);
        unit_square_4.set_fill(Colors::BEIGE);
        unit_square_5.set_fill(Colors::BEIGE);
        unit_square_6.set_fill(Colors::BEIGE);

        //else it's less than 20 and nothing can be built
    }else if(prod_val > 20){

        build_square_1.set_fill(Colors::BEIGE);
        build_square_2.set_fill(Colors::BEIGE);
        build_square_3.set_fill(Colors::BEIGE);
        build_square_4.set_fill(Colors::BEIGE);
        build_square_5.set_fill(Colors::BEIGE);
        build_square_6.set_fill(Colors::BEIGE);
        build_square_7.set_fill(Colors::BEIGE);
        build_square_8.set_fill(Colors::BEIGE);

        unit_square_1.set_fill(Colors::BEIGE);
        unit_square_2.set_fill(Colors::BEIGE);
        unit_square_3.set_fill(Colors::BEIGE);
        unit_square_4.set_fill(Colors::BEIGE);
        unit_square_5.set_fill(Colors::BEIGE);
        unit_square_6.set_fill(Colors::BEIGE);

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