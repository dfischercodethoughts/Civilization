//
// Created by david on 4/1/2019.
//

#include "Screen.h"


std::string Screen::screen_to_string(Screen::names nme) {
    switch (nme) {
        case (names::END_SCREEN) : {
            return "END_SCREEN";
        }
        case (names::START_SCREEN) : {
            return "START_SCREEN";
        }
        case (names::MAIN_GAME) : {
            return "MAIN_GAME";
        }
        case (names::PAUSE_SCREEN) : {
            return "PAUSE_SCREEN";
        }
        default : {
            return "NONE";
        }
    }
}

Screen::names Screen::string_to_screen(std::string nme) {
    if (nme == "MAIN_GAME") {
        return names::MAIN_GAME;
    }
    else if (nme == "END_SCREEN") {
        return names::END_SCREEN;
    }
    else if (nme == "START_SCREEN") {
        return names::START_SCREEN;
    }
    else if (nme == "PAUSE_SCREEN") {
        return names::PAUSE_SCREEN;
    }
    else {
        return names::DEFAULT;
    }
}

std::string Screen::menu_option_to_string(Screen::menu_options op) {
    switch(op) {
        case (START_GAME) : {
            return "START GAME";
        }
        case (EXIT_GAME) : {
            return "EXIT GAME";
        }
        case (LOAD_GAME) : {
            return "LOAD GAME";
        }
        case (SAVE_GAME) : {
            return "SAVE GAME";
        }
        case (RETURN_TO_START) : {
            return "RETURN TO START";
        }
        case (RETURN_TO_GAME) : {
            return "RETURN TO GAME";
        }
        default : {
            return "NONE";
        }
    }
}

Screen::menu_options Screen::string_to_menu_option(std::string op) {
    if (op == "START GAME" || op == "START_GAME") {
        return START_GAME;
    }
    else if (op == "EXIT GAME" || op == "EXIT_GAME") {
        return EXIT_GAME;
    }
    else if (op == "LOAD GAME" || op == "LOAD_GAME") {
        return LOAD_GAME;
    }
    else if (op == "SAVE GAME" || op == "SAVE_GAME") {
        return SAVE_GAME;
    }
    else if (op == "RETURN_TO_START" || op == "RETURN TO START") {
        return RETURN_TO_START;
    }
    else if (op == "RETURN TO GAME" || op == "RETURN_TO_GAME") {
        return RETURN_TO_GAME;
    }
    else {
        return NONE;
    }
}

Screen::Screen() :cnt({-1,-1}) {
    screen_height = 0;
    screen_width = 0;
}

Coordinate Screen::get_center() const {
    return cnt;
}

int Screen::get_screen_height() const {
    return screen_height;
}

int Screen::get_screen_width() const {
    return screen_width;
}

void Screen::set_center(Coordinate newc) {
    cnt = newc;
}

void Screen::set_screen_height(int nh) {
    if (nh >=0 & nh <= 10000) {
        screen_height = nh;
    }
}

void Screen::set_screen_width(int nw) {
    if (nw >= 0 & nw <= 10000) {
        screen_width = nw;
    }
}

Screen::~Screen() {
    cnt = {-1,-1};
    screen_width = -1;
    screen_height = -1;
}