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
private:
    Coordinate center;
    int height, width;
    int xoff,yoff;
    Color fill;
    Color text_color;
    std::string msg;
    bool visible;


public:
    static const int TILE_HEIGHT = 100;
    static const int TILE_WIDTH = 150;

    /**
     * constructors
     * visible defaults to true, color to white and text_color to black
     */
    Square();
    Square(Coordinate cnt, Color fill, int h, int w, bool vis);
    Square(Coordinate cnt, Color text, Color fill, int h, int w, std::string msg, bool vis);

    Coordinate get_center() const;
    int get_height() const;
    int get_width() const;
    Color get_fill() const;
    Color get_text_color() const;
    std::string get_message() const;
    bool is_visible();
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

    virtual void draw();

    ~Square();

    //operators
    Square & operator=(const Square & cp);
};


#endif //CIV_SQUARE_H
