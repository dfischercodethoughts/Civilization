//
// Created by david on 4/1/2019.
//

#ifndef CIV_END_SCREEN_H
#define CIV_END_SCREEN_H

#include "Screen.h"

class End_Screen : public Screen {
private:
    Square return_to_start;
    Square exit;
    Square message_port;


public:
    End_Screen();
    End_Screen(bool won);
    End_Screen(int h, int w, bool won);

    void init(int h, int w) override;
    void init(bool won, int h, int w);

    void draw() override;
    names get_type() const override;

    menu_options check_click(Coordinate click) override;

    void win();
    void lose();

    ~End_Screen();
};


#endif //CIV_END_SCREEN_H
