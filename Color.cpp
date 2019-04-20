//
// Created by david on 4/3/2019.
//

#include "Color.h"

Color::Color() {
    r= 0;
    g=0;
    b=0;
}

Color::Color(int re, int gr, int bl)
{
    r = re;
    g = gr;
    b = bl;
}

int Color::get_red() const {
    return r;
}

int Color::get_green() const {
    return g;
}

int Color::get_blue() const {
    return b;
}

void Color::set_red(int newr) {
    if (newr>=0 & newr <= 255) {
        r = newr;
    }
}

void Color::set_green(int ng) {
    if (ng>=0 & ng <= 255) {
        r = ng;
    }
}

void Color::set_blue(int nb) {
    if (nb>=0 & nb <= 255) {
        r = nb;
    }
}

std::ostream & operator<<(std::ostream & outs, const Color & print) {
    std::string p = "COLOR: " + std::to_string(print.r) + "," + std::to_string(print.g) + "," + std::to_string(print.b);
    outs << p << std::endl;
    return outs;
}

std::istream & operator>>(std::istream & ins, Color & fill) {
    std::string line = "";

    std::getline(ins,line);
    line.erase(0,line.find(' ')+1);

    std::string tok = line.substr(0,line.find(','));
    line.erase(0,line.find(',')+1);
    fill.r = std::stoi(tok);

    tok = line.substr(0,line.find(','));
    line.erase(0,line.find(',')+1);
    fill.g = std::stoi(tok);

    fill.b = std::stoi(line);

    return ins;
}

bool operator==(const Color & lhs, const Color & rhs) {
    if (rhs.get_red() == lhs.get_red() && rhs.get_blue() == lhs.get_blue() && rhs.get_green() == lhs.get_green()) {
        return true;
    }
    return false;
}

bool operator!=(const Color& lhs, const Color & rhs) {
    if (!(lhs==rhs)) {
        return true;
    }
    return false;
}