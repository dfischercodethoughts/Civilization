//
// Created by david on 4/1/2019.
//

#ifndef CIV_START_SCREEN_H
#define CIV_START_SCREEN_H
#include "Screen.h"
/**
 * Screen the user is presented with on first starting the game
 */
class Start_Screen : public Screen {

private:
    const std::string GAME_NAME = "CIVILIZATION";
    Square new_game;
    Square exit_game;
    Square load_game;
    Square title_port;
    int width, height;

public:

    Start_Screen();
    Start_Screen(int h, int w);

    void init(int h,int w) override;

    void draw() override;

    names get_type() const override;

    menu_options check_click(Coordinate click) override;

    Start_Screen & operator=(const Start_Screen & cp);

    ~Start_Screen();
};


#endif //CIV_START_SCREEN_H
