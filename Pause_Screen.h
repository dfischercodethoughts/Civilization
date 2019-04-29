//
// Created by david on 4/1/2019.
//

#ifndef CIV_PAUSE_SCREEN_H
#define CIV_PAUSE_SCREEN_H

#include "Screen.h"

/**
 * pause screen is used in game and allows returning to start screen to start a new game, and exiting
 *  or saving and loading the game
 */
class Pause_Screen : public Screen {
private:
    Square return_to_start;
    Square return_to_game;
    Square save;
    Square load;
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
