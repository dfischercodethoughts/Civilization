//
// Created by david on 4/1/2019.
//

#ifndef CIV_END_SCREEN_H
#define CIV_END_SCREEN_H

#include "Screen.h"

/**
 * end screen has buttons to return to the start screen or exit the game
 */
class End_Screen : public Screen {
private:
    Square return_to_start;
    Square exit;
    Square message_port;


public:
    /**
     * constructors
     */
    End_Screen();
    End_Screen(bool won);
    End_Screen(int h, int w, bool won);

    /**
     * constructors use init to set base height and width
     * @param h eight
     * @param w idth
     */
    void init(int h, int w) override;
    void init(bool won, int h, int w);

    /**
     * draws all the squares on the end screen
     */
    void draw() override;
    names get_type() const override;

    /**
     * checks the click and returns the menu option selected
     * @param click
     * @return option selected (or NONE)
     */
    menu_options check_click(Coordinate click) override;

    /**
     * sets message based on whether the player won or lost
     */
    void win();
    void lose();

    ~End_Screen();
};


#endif //CIV_END_SCREEN_H
