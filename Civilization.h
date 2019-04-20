//
// Created by david on 4/3/2019.
//

#ifndef CIV_CIVILIZATION_H
#define CIV_CIVILIZATION_H
#include "Tile.h"
#include <vector>
#include "Map.h"
#include <iostream>

/**
 * Note the enum Civilization_Name in Unit.h
 */
class Civilization {

private:
    int gold, production, food;
    std::vector<Unit> units;
    Civilization_Name::Names name;

    bool ai;

public:
    /**
     * unit list must be initialized outside of civ constructor
     * default constructor defaults gold prod food to zero. Sets name to Civilization_Name::NONE
     */
    Civilization();
    /**
     *
     * @param nm name of civ (defaults to NONE if invalid)
     * @param start tile that civ should start on
     * @param is_ai is this civ computer or player controlled?
     */
    Civilization(std::string nm, std::shared_ptr<Tile> start, bool is_ai);
    Civilization(std::string nm, bool is_ai);

    /**
     * returns civilization name
     * @return
     */
    Civilization_Name::Names get_name() const;
    std::string get_name_str() const;

    int get_gold() const;
    int get_production() const;
    int get_food() const;

    bool is_ai() const;
    /**
     * adds a unit to the civ's unit list. Initializes units list if size is zero
     * @param type of unit to produce
     * @param place to start unit
     * @return success or failure
     */
    //bool add_unit(Unit un,Tile& place);
    bool add_unit(Unit * un );
    bool add_unit(Unit&un,Tile& place);
    bool add_unit(Unit*un,Tile& place);
    bool add_unit(Unit::Unit_Type type,Tile& place);

    Unit * get_unit(Civilization_Name::Names owner, int tileid);
    Unit * get_unit_const(Civilization_Name::Names owner, int tileid) const;
    Unit * get_unit(Civilization_Name::Names owner, Tile & loc);
    Unit * get_unit_const(Civilization_Name::Names owner, Tile & loc) const;
    std::vector<Unit *> get_units();
    //const version for copy operator
    std::vector<Unit *> get_units_const() const;

    /**
     * additional methods
     */

    bool lost();

    bool move_unit(Map& map,Unit& to_move, Tile& move_to);
    bool move_unit(Map * map, Unit * to_move, Tile * move_to);
    bool move_unit(Map * map, int fromid, int toid);

    /**
     * loops through units and removes the unit from the units vector if health is 0 or less
     */
    void destroy_units();

    //refresh at end of turn
    void refresh();

    void next_turn();

    //operators
    Civilization & operator=(Civilization const &);
    //equals operator checks name only
    bool operator==(Civilization const &);

    friend std::ostream & operator<<(std::ostream & outs, const Civilization & print);
    friend std::istream & operator>>(std::istream & ins, Civilization & fill);

    ~Civilization();

};


#endif //CIV_CIVILIZATION_H
