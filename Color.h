//
// Created by david on 4/3/2019.
//

#ifndef CIV_COLOR_H
#define CIV_COLOR_H


class Color {
private:
    int r, g, b;

public:
    Color();//defaults to black
    Color(int r, int g, int b);

    int get_red() const;
    int get_green() const;
    int get_blue() const;

    void set_red(int newr);
    void set_green(int newg);
    void set_blue(int newb);

};

namespace Colors {
    static const Color RED = Color(255,0,0);
    static const Color BLACK = Color(0,0,0);
    static const Color WHITE = Color(255,255,255);
    static const Color GREEN = Color(0,255,0);
    static const Color BLUE = Color (0,0,255);
}


#endif //CIV_COLOR_H
