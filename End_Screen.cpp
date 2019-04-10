//
// Created by david on 4/1/2019.
//

#include "End_Screen.h"

End_Screen::End_Screen() {
    return_to_start = Square();
    exit = Square();
    message = "DEFAULT";
}

End_Screen::End_Screen(bool won) {
    init(800,1200,won);
}

End_Screen::End_Screen(int h, int w, bool won) {
    init(h,w,won);
}

void End_Screen::init(int h, int w) {
    init(false,h,w);
}

void End_Screen::init(bool won, int h, int w) {
    this->set_center(Coordinate(w/2,h/2));
    this->set_screen_height(h);
    this->set_screen_width(w);
    return_to_start = Square(Coordinate(w/2,h/2+100),{255,255,255},{200,100,200},300,200,"Return To Start",true);
    exit = Square(Coordinate(w/2,h/2+200),{255,255,255},{200,100,200},300,400,"Exit Game",true);
    if (won) {
        message = "YOU WIN! CONGRATULATIONS!";
    }
    else {
        message = "YOU LOST. TRY AGAIN?";
    }
}

void End_Screen::draw() {
    //end screen has green background
    glColor3i(50,200,30);
    glBegin(GL_QUADS);
    glVertex2i(0,0);
    glVertex2i(this->get_screen_width(),0);
    glVertex2i(this->get_screen_width(),get_screen_height());
    glVertex2i(0,get_screen_height());
    glEnd();

    return_to_start.draw();
    exit.draw();

    glColor3i(255,255,50);
    glRasterPos2i(get_center().x,get_center().y-100);
    for (char c : message) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c);
    }
}

Screen::names End_Screen::get_type() const {
    return Screen::END_SCREEN;
}

Screen::menu_options End_Screen::check_click(Coordinate click) {
    if(return_to_start.check_click(click)) {
        return Screen::RETURN_TO_START;
    }
    else if (exit.check_click(click)) {
        return Screen::EXIT_GAME;
    }
    else {
        return Screen::NONE;
    }
}

void End_Screen::win() {
    message = "CONGRATULATIONS; YOU WIN!";
}

void End_Screen::lose() {
    message = "YOU LOST. TRY AGAIN?";
}

End_Screen::~End_Screen() {
    return_to_start = Square();
    exit = Square();
    message = "";
}