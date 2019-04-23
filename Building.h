//
// Created by willi on 4/19/19.
//

#ifndef CIV_BUILDING_H
#define CIV_BUILDING_H


#include "Piece.h"

#include "Building_Name.h"

class Building {

private:
    Building_Name::names name;
public:
    Building();
    Building(Building_Name::names nm);

    std::string building_to_string(Building_Name::names nm);

    int get_upkeep(Building_Name::names nm);


    Building_Name::names get_name();
    void set_name();

    ~Building();

};

#endif //CIV_BUILDING_H

