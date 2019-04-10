//
// Created by david on 4/1/2019.
//

#ifndef CIV_SCREEN_H
#define CIV_SCREEN_H

#include "Square.h"
#include <vector>

class Screen {
private:
    Coordinate cnt;
    int screen_height, screen_width;

public:
    Screen();

    Coordinate get_center() const;
    int get_screen_height() const;
    int get_screen_width() const;
    void set_center(Coordinate newc);
    void set_screen_height(int nh);
    void set_screen_width(int nw);

    enum names {
        START_SCREEN,
        MAIN_GAME,
        END_SCREEN,
        PAUSE_SCREEN,
        DEFAULT
    };

    enum menu_options {
        START_GAME,
        EXIT_GAME,
        LOAD_GAME,
        SAVE_GAME,
        RETURN_TO_START,
        RETURN_TO_GAME,
        NONE
    };

    static std::string screen_to_string(names nme);
    static names string_to_screen(std::string nme);
    static std::string menu_option_to_string(menu_options op);
    static menu_options string_to_menu_option(std::string op);

    virtual void init(int h, int w) = 0;

    virtual void draw() = 0;

    virtual names get_type() const = 0;

    virtual menu_options check_click(Coordinate click) = 0;

    ~Screen();
};


#endif //CIV_SCREEN_H
