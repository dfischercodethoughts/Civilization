//
// Created by willi on 4/19/19.
//

#include "Building.h"

//base constructor for building
Building::Building() {
    name = Building_Name::NONE;
}

//specified building
Building::Building(Building_Name::names nm) {
    name = nm;
}

//returns building name
Building_Name::names Building::get_name() const {
    return name;
}

//set building name
void Building::set_name(Building_Name::names nm) {
    name = nm;
}

//set name from a string
void Building::set_name(std::string nm) {
    name = Building_Name::string_to_building_name(nm);
}

//returns whether or not a building has been pillaged
bool Building::is_pillaged() const {
    return pillaged;
}

//has a building been pillaged
bool Building::get_pillaged() const {
    return pillaged;
}

//pillage a building
void Building::pillage() {
    pillaged = true;
}

//unpillage a building
void Building::repair() {
    pillaged= false;
}

bool operator==(const Building & lhs, const Building & rhs) {
    return lhs.get_name()==rhs.get_name();
}

Building & Building::operator=(const Building & cp) {
    name = cp.get_name();
    return *this;
}

//returns the prouction cost from the building name
//made for testing purposes
int Building::get_building_prod_cost(){
    return Building_Name::get_production_cost(name);
}

//turns a BUILDINGNAME into a string
std::string Building::building_to_string(Building_Name::names nm){
    switch(nm){
        case(Building_Name::FARM):
            return "FARM";
        case(Building_Name::MINE):
            return "MINE";
        case(Building_Name::LOGGING_CAMP):
            return "LOGGING_CAMP";
        case(Building_Name::MARKET):
            return "MARKET";
        case(Building_Name::NONE):
            return "NONE";

        default:
            break;
    }
    return 0;
}


//returns the upkeep of a building
int Building::get_upkeep(Building_Name::names nm){
    //mine or farms require 1 production
    if(nm == Building_Name::FARM or nm == Building_Name::MINE){
        return 1;
        //logging camps and hunting lodge require 2 production
    } //else if(nm == Building_Name::LOGGING_CAMP or nm == Building_Name::HUNTING_LODGE){
        //return 2;
        //market requires 3 production
    //}
    else if(nm == Building_Name::MARKET){
        return 3;
        //otherwise, that means their is nothing there so there is no production upkeep value
    }else{
        return 0;
    }
}


Building::~Building() {
    name = Building_Name::NONE;
}
