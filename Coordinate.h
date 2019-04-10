//
// Created by david on 4/3/2019.
//

#ifndef CIV_COORDINATE_H
#define CIV_COORDINATE_H


struct Coordinate {
public:
    int x,y;

    Coordinate(int xn, int ny);

    bool operator==(Coordinate const & rhs);

};


#endif //CIV_COORDINATE_H
