//
// Created by david on 4/3/2019.
//

#include "Coordinate.h"

Coordinate::Coordinate(int xn, int ny) {
    if (xn >= -1 & xn < 10000) {
        x = xn;
    }
    else {
        x = 0;
    }
    if (ny >= -1 & ny < 10000) {
        y = ny;
    }
    else {
        y=0;
    }
}

bool Coordinate::operator==(Coordinate const &rhs) {
    if (x==rhs.x & y == rhs.y) {
        return true;
    }
    return false;
}