//
// Created by david on 4/3/2019.
//

#ifndef CIV_SQUARE_H
#define CIV_SQUARE_H

#include "Color.h"
#include "Coordinate.h"
#include <string>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Square {
public:
    enum Text_Size {
        SMALL,
        MEDIUM,
        LARGE
    };

private:
    Coordinate center;
    int height, width;
    int xoff,yoff;
    Color fill;
    Color text_color;
    std::string msg;
    bool visible;
    Text_Size text_size;


public:


    static const int TILE_HEIGHT = 100;
    static const int TILE_WIDTH = 150;

    /**
     * constructors
     * visible defaults to true, color to white and text_color to black
     */
    Square();
    Square(Coordinate cnt, Color fill, int h, int w, bool vis);
    Square(Coordinate cnt, Color fill, Color text, int h, int w, std::string msg, bool vis);

    Text_Size get_text_size() const;
    void set_text_size(Text_Size size);

    Coordinate get_center() const;
    int get_height() const;
    int get_width() const;
    Color get_fill() const;
    Color get_text_color() const;
    std::string get_message() const;
    bool is_visible() const;
    int get_x_offset() const;
    int get_y_offset() const;

    void set_center(Coordinate newl);
    void set_height(int newh);
    void set_width(int neww);
    void set_fill(Color newf);
    void set_text_color(Color newc);
    void set_message(std::string newm);
    void set_x_offset(int newxoff);
    void set_y_offset(int newyoff);
    void reveal();
    void hide();

    bool check_click(Coordinate click);

    virtual void draw() const;

    ~Square();

    //operators
    Square & operator=(const Square & cp);

    bool operator==(const Square & rhs);
    bool operator!=(const Square & rhs);

    /**
     * burns leading SQUARE\n then fills in info by scheme of output operator
     * @param ins
     * @param fill
     * @return
     */
    friend std::istream & operator>>(std::istream & ins, Square & fill);
    /**
     * outputs "SQUARE\nCENTER\nheight,width,xoff,yoff\nfill\ntextcolor\nmsg\nvisible\n
     * @param outs
     * @param print
     * @return
     */
    friend std::ostream & operator<<(std::ostream & outs, const Square & print);
};


#endif //CIV_SQUARE_H
