//
// Created by willi on 4/19/19.
//

#include "Building.h"

Building::Building() {
    name = Building_Name::NONE;


Building::Building(Building_Name::names nm) {
    name = nm;
}

Building_Name::names Building::get_name() {
    return name;
}

Building::~Building() {
    name = Building_Name::NONE;
}
