//
// Created by david on 4/1/2019.
//

#include "Pause_Screen.h"

Pause_Screen::Pause_Screen() {
    return_to_start = Square();
    return_to_game = Square();
    exit = Square();
    message = "";
}

Pause_Screen::Pause_Screen(int h, int w) {
    init(h,w);
}

void Pause_Screen::init(int h, int w) {
    return_to_start = Square({w/2,h/4},{0,0,0},{0,255,0},h/4,w/2,"RETURN TO START", true);
    return_to_game = Square({w/2,h/2},{0,0,0},{0,255,0},h/4,w/2,"RETURN TO GAME", true);
    exit = Square({w/2,3*h/4},{0,0,0},{0,255,0},h/4,w/2,"EXIT GAME", true);
    message = "PAUSE SCREEN";
}

void Pause_Screen::draw() {
    Square(return_to_game.get_center(),{100,255,0},return_to_game.get_center().y * 2,return_to_game.get_center().x * 2,true);

    return_to_game.draw();
    return_to_start.draw();
    exit.draw();

    glColor3i(0,0,0);
    glRasterPos2i(return_to_start.get_center().x,return_to_start.get_center().y/2);
    for (char c : message) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c);
    }


}


Screen::names Pause_Screen::get_type() const {
    return Screen::PAUSE_SCREEN;
}

Screen::menu_options Pause_Screen::check_click(Coordinate click) {
    if (return_to_game.check_click(click)) {
        return Screen::RETURN_TO_GAME;
    }
    else if (return_to_start.check_click(click)) {
        return Screen::RETURN_TO_START;
    }
    else if (exit.check_click(click)) {
        return Screen::EXIT_GAME;
    }

    return Screen::NONE;
}

Pause_Screen::~Pause_Screen() {
    return_to_start = Square();
    return_to_game = Square();
    exit = Square();
    message = "";
}