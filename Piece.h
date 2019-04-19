//
// Created by david on 4/3/2019.
//

#ifndef CIV_PIECE_H
#define CIV_PIECE_H
#include "Square.h"
#include "Validator.h"

class Piece : public Square{
public:
    enum Piece_Type {
        BUILDING,
        CITY,
        UNIT,
        TILE,
        NONE
    };
    static std::string piece_type_to_string(Piece_Type type);
    static Piece_Type string_to_piece_type(std::string type);


private:
    Piece_Type type;

public:
    Piece();
    explicit Piece(std::string type);
    explicit Piece(Piece_Type type);
    Piece(Coordinate cnt, int h, int w, Color fill, Color text,Piece_Type tp);

    Piece_Type get_type() const;
    void set_type(std::string type);
    void set_type(Piece_Type type);

    virtual void draw_on_viewport(Square base)=0;

    ~Piece();
};


#endif //CIV_PIECE_H
