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

struct Colors {
    static const Color RED;
    static const Color BLACK;
    static const Color WHITE;
    static const Color GREEN;
    static const Color BLUE;
    static const Color PURPLE;
    static const Color BEIGE;
    static const Color TEAL;
};

bool operator==(Color const & lhs, Color const & rhs);
bool operator!=(Color const & lhs, Color const & rhs);

#endif //CIV_COLOR_H
