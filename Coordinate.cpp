//
// Created by david on 4/3/2019.
//

#include "Coordinate.h"

Coordinate::Coordinate() {
    x = 0;
    y = 0;
}

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

bool Coordinate::operator!=(const Coordinate & rhs) {
    if (!(*this==rhs)) {
        return true;
    }
    return false;
}

std::ostream & operator<<(std::ostream &outs, const Coordinate &print) {
    std::string line = "COORDINATE:" + std::to_string(print.x) + ',' + std::to_string(print.y);
    outs << line << std::endl;
    return outs;
}

std::istream & operator>>(std::istream & ins, Coordinate & fill) {
    std::string line = "";
    std::getline(ins,line);

    //first token is thrown away
    line.erase(0,line.find(':') + 1);

    //second token is x coord
    std::string tok = line.substr(0,line.find(','));
    line.erase(0,line.find(',') + 1);
    fill.x = std::stoi(tok);

    fill.y = std::stoi(line);

    return ins;

}