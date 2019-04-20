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
    xoff =  -msg.size()*4;
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

bool Square::is_visible() const {
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
    xoff = -msg.size()*4;
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

void Square::draw() const {
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
        glRasterPos2i(center.x +xoff, center.y + yoff+5);
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

bool Square::operator==(const Square & rhs) {
    if (center != rhs.center) {
        return false;
    }
    if (width != rhs.get_width()) {
         return false;
    }
    if (height != rhs.get_height()) {
        return false;
    }
    if (xoff != rhs.get_x_offset()) {
        return false;
    }
    if (yoff != rhs.get_y_offset()) {
        return false;
    }
    if (fill != rhs.get_fill()) {
        return false;
    }
    if (text_color != rhs.get_text_color()) {
        return false;
    }
    if (msg != rhs.get_message()) {
        return false;
    }
    if (visible != rhs.is_visible()) {
        return false;
    }
    return true;
}

bool Square::operator!=(const Square & rhs) {
    if (!(*this == rhs)) {
        return true;
    }
    return false;
}

std::istream & operator>>(std::istream & ins, Square & fill) {
    try {
        std::string line = "";
        std::getline(ins,line);//burn "SQUARE"
        ins >> fill.center;

        std::getline(ins,line);
        std::string tok = line.substr(0,line.find(','));
        line.erase(0,line.find(',')+1);
        fill.height = std::stoi(tok);

        tok = line.substr(0,line.find(','));
        line.erase(0,line.find(',')+1);
        fill.width = std::stoi(tok);

        tok = line.substr(0,line.find(','));
        line.erase(0,line.find(',')+1);
        fill.xoff = std::stoi(tok);
        fill.yoff = std::stoi(line);

        ins >> fill.fill >> fill.text_color;

        std::getline(ins,line);
        fill.msg = line;
        std::getline(ins,line);
        if (line == "1"){
            fill.visible = true;
        }
        else {
            fill.visible = false;
        }

    }
    catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }
    return ins;
}

std::ostream & operator<<(std::ostream & outs, const Square & fill) {
    std::string line = "SQUARE\n";
    outs << line << fill.center;
    line = std::to_string(fill.height) + ',' + std::to_string(fill.width) + ',' + std::to_string(fill.xoff) + ',' + std::to_string(fill.yoff) + "\n";
    outs << line << fill.fill << fill.text_color << fill.msg << std::endl << std::to_string(fill.visible) << std::endl;
    return outs;
}