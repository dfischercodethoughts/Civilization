//
// Created by david on 4/3/2019.
//

#include "Square.h"
Square::Square() :center(Coordinate(0,0)) {
    height = 0;
    width = 0;
    fill = Color(255,255,255);
    text_color = Color(0,0,0);
    msg = "";
    visible = false;
    xoff = 0;
    yoff = 0;
}

Square::Square(Coordinate cnt, Color fll, int h, int w, bool vis):
center(cnt)
{
    fill = fll;
    text_color = Color(0,0,0);
    height = h;
    width = w;
    visible = vis;
    msg = "";
    xoff = 0;
    yoff = 0;
}

Square::Square(Coordinate cnt, Color fll, Color text, int h, int w, std::string mesg, bool vis):
center(cnt)
{
    fill = fll;
    text_color = text;
    height = h;
    width = w;
    msg = mesg;
    visible = vis;
    xoff =  -msg.size()/2;
    yoff = 0;
}

Coordinate Square::get_center() const {
    return center;
}

int Square::get_height() const {
    return height;
}

int Square::get_width() const {
    return width;
}

Color Square::get_fill() const {
    return fill;
}

Color Square::get_text_color() const {
    return text_color;
}

std::string Square::get_message() const {
    return msg;
}

bool Square::is_visible() {
    return visible;
}

int Square::get_x_offset() const {
    return xoff;
}

int Square::get_y_offset() const {
    return yoff;
}

void Square::set_center(Coordinate newl) {
    if (newl.x > 0 & newl.y > 0) {
        center = newl;
    }
}

void Square::set_height(int newh) {
    if (newh > 0) {
        height = newh;
    }
}

void Square::set_width(int neww) {
    if (neww > 0) {
        width = neww;
    }
}

void Square::set_fill(Color newf) {
    fill = newf;
}

void Square::set_text_color(Color newc) {
    text_color = newc;
}

void Square::set_message(std::string newm) {
    msg = newm;
    xoff = -msg.size()/2;
}

void Square::set_x_offset(int newxoff) {
    if (abs(newxoff)<1000) {
        xoff = newxoff;
    }
}

void Square::set_y_offset(int newy) {
    if (abs(newy) < 1000) {
        yoff = newy;
    }
}

void Square::reveal() {
    visible = true;
}

void Square::hide() {
    visible = false;
}

bool Square::check_click(Coordinate click) {
    if (click.x > (center.x-width/2) && click.x < (center.x + width/2) &&
        click.y > (center.y-height/2) && click.y < (center.y + height/2)) {
        return true;
    }
    return false;
}

void Square::draw() {
    if (visible) {
        glColor3f(fill.get_red(), fill.get_green(), fill.get_blue());
        glBegin(GL_QUADS);
        //top left
        glVertex2i(center.x - width / 2, center.y - height / 2);
        glVertex2i(center.x + width / 2, center.y - height / 2);
        //bottom right
        glVertex2i(center.x + width / 2, center.y + height / 2);
        glVertex2i(center.x - width / 2, center.y + height / 2);
        glEnd();

        //draw message
        glColor3f(text_color.get_red(), text_color.get_green(), text_color.get_blue());
        glRasterPos2i(center.x + xoff, center.y + yoff);
        for (char c : msg) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }
    }
}


Square::~Square() {
    center = {-1,-1};
    height = 0;
    width = 0;
    xoff = 0;
    yoff = 0;
    fill = {0,0,0};
    text_color = {255,255,255};
    msg = "DESTROY";
    visible = true;
}

Square & Square::operator=(const Square & cp) {
    center = cp.get_center();
    height = cp.get_height();
    width = cp.get_width();
    xoff = cp.get_x_offset();
    yoff = cp.get_y_offset();
    fill = cp.get_fill();
    text_color = cp.get_text_color();
    msg = cp.get_message();
    visible = cp.visible;
}