//
// Created by willi on 4/19/19.
//

#ifndef CIV_BUILDING_H
#define CIV_BUILDING_H


#include "Piece.h"

#include "Building_Name.h"

class Building {

private:
    //name of the building
    Building_Name::names name;

    //hwether it's pillaged or not
    bool pillaged;

public:
    //basic building constructor
    Building();

    //create a building with a specified name
    Building(Building_Name::names nm);

    //returns the buidling name
    Building_Name::names get_name() const;

    //set the building name with a BUILDING NAME::names
    //not used
    void set_name(Building_Name::names);

    //set the building name with a building name as a string
    void set_name(std::string nm);

    //returns pillaged
    bool is_pillaged() const;
    //returns pillaged
    bool get_pillaged() const;

    //function to pillage a building
    void pillage();

    //function to repair a pillaged building
    void repair();

    /*
     * operators
     */
    Building & operator=(const Building & cp);

    friend std::ostream & operator<<(std::ostream & outs, const Building & print);
    friend std::istream & operator>>(std::istream & ins, Building & fill);

    int get_building_prod_cost();

    std::string building_to_string(Building_Name::names nm);

    int get_upkeep(Building_Name::names nm);

    ~Building();

};

bool operator==(const Building & cmp,const Building & rh);

#endif //CIV_BUILDING_H

