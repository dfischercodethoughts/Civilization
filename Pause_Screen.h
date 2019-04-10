//
// Created by david on 4/1/2019.
//

#ifndef CIV_PAUSE_SCREEN_H
#define CIV_PAUSE_SCREEN_H

#include "Screen.h"

class Pause_Screen : public Screen {
private:
    Square return_to_start;
    Square return_to_game;
    Square exit;
    std::string message;

public:
    Pause_Screen();
    Pause_Screen(int h, int w);

    void init(int h, int w) override;

    void draw() override;
    Screen::names get_type() const override;

    Screen::menu_options check_click(Coordinate click) override;

    ~Pause_Screen();
};


#endif //CIV_PAUSE_SCREEN_H
