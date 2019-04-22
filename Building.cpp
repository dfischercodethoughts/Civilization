//
// Created by willi on 4/19/19.
//

#include "Building.h"

Building::Building() {
    name = Building_Name::NONE;
}

Building::Building(Building_Name::names nm) {
    name = nm;
}

Building_Name::names Building::get_name() const {
    return name;
}

void Building::set_name(Building_Name::names nm) {
    name = nm;
}

void Building::set_name(std::string nm) {
    name = Building_Name::string_to_building_name(nm);
}

bool Building::is_pillaged() const {
    return pillaged;
}

bool Building::get_pillaged() const {
    return pillaged;
}

void Building::pillage() {
    pillaged = true;
}

void Building::repair() {
    pillaged= false;
}

bool operator==(const Building & lhs, const Building & rhs) {
    return lhs.get_name()==rhs.get_name();
}

Building & Building::operator=(const Building & cp) {
    name = cp.get_name();
}

Building::~Building() {
    name = Building_Name::NONE;
}
