//
// Created by david on 4/3/2019.
//

#ifndef CIV_COLOR_H
#define CIV_COLOR_H

#include <fstream>

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



    /**
     * sticks "COLOR: R,G,B\n" into an ostream, and reads the same from an istream
     * @param out
     * @param print
     * @return
     */
    friend std::ostream & operator<<(std::ostream & out,const  Color & print);
    friend std::istream & operator>>(std::istream & ins, Color & fill);
};

bool operator==(Color const & lhs, Color const & rhs);
bool operator!=(Color const & lhs, Color const & rhs);

namespace Colors {
    static const Color RED = Color(255,0,0);
    static const Color BLACK = Color(0,0,0);
    static const Color WHITE = Color(255,255,255);
    static const Color GREEN = Color(0,255,0);
    static const Color BLUE = Color (0,0,255);
}


#endif //CIV_COLOR_H
