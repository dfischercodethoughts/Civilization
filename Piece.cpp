//
// Created by david on 4/3/2019.
//

#include "Piece.h"

std::string Piece::piece_type_to_string(Piece::Piece_Type type) {
    switch (type) {
        case (BUILDING) : {
            return "BUILDING";
        }
        case(CITY) : {
            return "CITY";
        }
        case (UNIT) : {
            return "UNIT";
        }
        case (TILE) : {
            return "TILE";
        }
        default :
            return "NONE";
    }
}

Piece::Piece_Type Piece::string_to_piece_type(std::string tp) {
    std::string type;
    for (char c : tp) {
        type += toupper(c);
    }
    if (type == "BUILDING") {
        return Piece::BUILDING;
    }
    else if (type == "TILE") {
        return Piece::TILE;
    }
    else if (type == "UNIT") {
        return Piece::UNIT;
    }
    else if (type == "CITY") {
        return Piece::CITY;
    }
    else {
        return Piece::NONE;
    }
}

Piece::Piece() : Square() {
    type = NONE;
}

Piece::Piece(std::string tp) : Square() {
    type = string_to_piece_type(tp);
}

Piece::Piece(Piece::Piece_Type tp) : Square() {
    type = tp;
}

Piece::Piece(Coordinate cnt, int h, int w, Color fill, Color text,Piece_Type tp) :
Square(cnt,text,fill,h,w,piece_type_to_string(tp),true)
{
    type = tp;
}

Piece::Piece_Type Piece::get_type() const {
    return type;
}

void Piece::set_type(std::string tp) {
    type = string_to_piece_type(tp);
}

void Piece::set_type(Piece::Piece_Type tp) {
    type = tp;
}

Piece::~Piece() {
    type = Piece_Type ::NONE;
}