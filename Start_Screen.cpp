//
// Created by david on 4/1/2019.
//

#include "Start_Screen.h"

Start_Screen::Start_Screen() {
    new_game = Square();
    exit_game = Square();
    load_game = Square();
    width = 0;
    height = 0;
}

Start_Screen::Start_Screen(int h, int w) {
    init(h,w);
}

void Start_Screen::init(int h, int w) {
    width = w;
    height = h;
    set_screen_height(h);
    set_screen_width(w);
    set_center(Coordinate(w/2,h/2));
    new_game = Square(Coordinate(width/2,3*height/8),Colors::BLUE,Colors::BLACK,h/8,w/4,"New Game",true);
    exit_game = Square(Coordinate(width/2,5*height/8),Colors::BLUE,Colors::BLACK,h/8,w/4,"Exit Game",true);
    load_game = Square(Coordinate(width/2,4*height/8),Colors::BLUE,Colors::BLACK,h/8,w/4,"Load Game",true);
    title_port = Square(Coordinate(width/2,height/8),Colors::GREEN,Colors::BLACK,height/10,width/5,"CIVILIZATION",true);
    title_port.set_text_size(Square::Text_Size::LARGE);
}

void Start_Screen::draw() {
    Square(Coordinate(width/2,height/2),Colors::GREEN,height,width,true).draw();
    title_port.draw();
    new_game.draw();
    exit_game.draw();
    load_game.draw();

}

Screen::names Start_Screen::get_type() const {
    return Screen::START_SCREEN;
}

Screen::menu_options Start_Screen::check_click(Coordinate click) {
    if (new_game.check_click(click)) {
        return Screen::START_GAME;
    }
    else if (exit_game.check_click(click)) {
        return Screen::EXIT_GAME;
    }
    else if (load_game.check_click(click)) {
        return Screen::LOAD_GAME;
    }
    return Screen::NONE;
}

Start_Screen& Start_Screen::operator=(const Start_Screen &cp) {
    new_game = cp.new_game;
    exit_game = cp.exit_game;
    load_game = cp.load_game;
    width = cp.width;
    height = cp.height;
}

Start_Screen::~Start_Screen() {
    new_game = Square();
    exit_game = Square();
    load_game = Square();
    width = 0;
    height = 0;
}