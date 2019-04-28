//
// Created by willi on 4/19/19.
//

#ifndef CIV_BUILDING_H
#define CIV_BUILDING_H


#include "Piece.h"

#include "Building_Name.h"
/**
 * building class is essentially an enum holder, but has potential for pillaging as an extension
 * Tiles have a building, which by default has a building name of none
 */
class Building {

private:
    Building_Name::names name;
    bool pillaged;

public:
    //constructors
    Building();
    Building(Building_Name::names nm);

    Building_Name::names get_name() const;
    void set_name(Building_Name::names);
    void set_name(std::string nm);

    /**
     * potential for future pillage functionality
     */
    bool is_pillaged() const;
    bool get_pillaged() const;
    void pillage();
    void repair();

    /*
     * operators
     */
    Building & operator=(const Building & cp);

    friend std::ostream & operator<<(std::ostream & outs, const Building & print);
    friend std::istream & operator>>(std::istream & ins, Building & fill);

    std::string building_to_string(Building_Name::names nm);

    int get_upkeep(Building_Name::names nm);

    ~Building();

};

bool operator==(const Building & cmp,const Building & rh);

#endif //CIV_BUILDING_H

