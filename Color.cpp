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