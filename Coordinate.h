//
// Created by david on 4/3/2019.
//

#ifndef CIV_COORDINATE_H
#define CIV_COORDINATE_H

#include <iostream>

/**
 * low level coordinate structure has public x and y values
 */
struct Coordinate {
public:
    int x,y;

    Coordinate();
    Coordinate(int xn, int ny);

    bool operator==(Coordinate const & rhs);
    bool operator!=(const Coordinate & rhs);
    friend std::ostream & operator<<(std::ostream & outs, const Coordinate & print);
    friend std::istream & operator>>(std::istream & ins, Coordinate & fill);
};


#endif //CIV_COORDINATE_H
