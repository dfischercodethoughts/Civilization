//
// Created by david on 4/1/2019.
//

#include "End_Screen.h"

End_Screen::End_Screen() {
    return_to_start = Square();
    exit = Square();

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
    return_to_start = Square(Coordinate(w/2,h/2),Colors::BEIGE,Colors::BLACK,h/8,w/4,"Return To Start",true);
    exit = Square(Coordinate(w/2,5*h/8),Colors::BEIGE,Colors::BLACK,h/8,w/4,"Exit Game",true);
    message_port = Square(Coordinate(w/2,h/8),Colors::PURPLE,Colors::WHITE,2*h/8,w/4,"",true);
    return_to_start.set_text_size(Square::LARGE);
    exit.set_text_size(Square::LARGE);
    message_port.set_text_size(Square::LARGE);
    message_port.set_x_offset(-20);
    if (won) {
        message_port.set_message("YOU WIN! CONGRATULATIONS!");
    }
    else {
        message_port.set_message("YOU LOST. TRY AGAIN?");
    }
}

void End_Screen::draw() {
    /*
    //end screen has green background
    glColor3f(50,200,30);
    glBegin(GL_QUADS);
    glVertex2i(0,0);
    glVertex2i(this->get_screen_width(),0);
    glVertex2i(this->get_screen_width(),get_screen_height());
    glVertex2i(0,get_screen_height());
    glEnd();
*/
    Square(get_center(),Colors::TEAL,Colors::WHITE,get_screen_height(),get_screen_width(),"",true).draw();
    return_to_start.draw();
    exit.draw();
    message_port.draw();
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
    message_port.set_message("CONGRATULATIONS; YOU WIN!");
}

void End_Screen::lose() {
    message_port.set_message("YOU LOST. TRY AGAIN?");
}

End_Screen::~End_Screen() {
    return_to_start = Square();
    exit = Square();
    message_port.set_message("");
}