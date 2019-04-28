//
// Created by david on 4/3/2019.
//

#ifndef CIV_CIVILIZATION_H
#define CIV_CIVILIZATION_H
#include "Tile.h"
#include <vector>
#include "Map.h"
#include "City.h"
#include <iostream>

/**
 * Civilization class holds all information about a given civilization
 * Civilizations are owned by game
 * Civilizations are identified by name
 * holds a vector of cities, and a vector of units
 * has an overall gold production and food gathered statistic but at present does not use them
 * has a boolean to tell if it is ai or not
 *      (aside: currently we don't have this functionality, but it would be relatively trivial to modify game to have a vector
 *          of civilizations)
 */
class Civilization {

private:
    int gold, production, food;
    std::vector<Unit> units;
    std::vector<City> cities;
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
    Civilization(std::string nm, bool is_ai);

    /**
     * returns civilization name
     * @return
     */
    Civilization_Name::Names get_name() const;
    std::string get_name_str() const;

    /**
     * civ statistics getters and setters
     * @return
     */
    int get_gold() const;
    int get_production() const;
    int get_food() const;

    /**
     * civilization cities getters
     * @return
     */
    std::vector<City *> get_cities();
    std::vector<const City *> get_cities_const() const;
    City * get_city(int home_id);
    const City * get_city_const(int homeid) const;
    /**
     * adds a city to the civilization. Uses map to add the city to the home tile as well
     * @param m
     * @param newh
     */
    void add_city(Map & m,Tile & newh);

    //removes a unit that matches the one given. Used by destroy units method
    void remove_unit(const Unit & re);

    //ai boolean getter
    bool is_ai() const;

    /**
     * resets all civilization's properties. For use in loading
     */
    void clear();

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

    /**
     * getters for units
     * @param owner
     * @param tileid
     * @return
     */
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

    //returns true if the civ has no units in it
    bool lost();

    /**
     * methods to move units -- handles unit and terrain types
     *  does not cause damage
     * @param map
     * @param to_move
     * @param move_to
     * @return
     */
    bool move_unit(Map& map,Unit& to_move, Tile& move_to);
    bool move_unit(Map * map, Unit * to_move, Tile * move_to);
    bool move_unit(Map * map, int fromid, int toid);

    /**
     * loops through units and removes the unit from the units vector if health is 0 or less
     */
    void destroy_units();

    //refresh at end of turn
    void refresh();

    //refreshes units and collects resources from cities
    //uses map to grow cities
    void next_turn(Map & m);

    //iterates through tiles and updates resources based on tile get output
    //if a cities food is greater than population ^3, switch ready_to_grow flag
    void collect_resources();

    //if a city is ready to grow, grow it based on the map
    void grow_cities(Map & m);


    //operators
    Civilization & operator=(Civilization const &);
    //equals operator checks name only
    bool operator==(Civilization const &);

    /**
     * outputs CIVILIZATION
     *             name
     *             gold, production, food
     *             bool ai
     *             UNIT
     *              ...
     *             UNIT
     *              ...
     *             ...
     *             END\n
     *             CITY
     *             ...
     *             City
     *             ...
     *             ...
     *             END
     * @param outs
     * @param print
     * @return
     */
    friend std::ostream & operator<<(std::ostream & outs, const Civilization & print);
    friend std::istream & operator>>(std::istream & ins, Civilization & fill);

    ~Civilization();

};


#endif //CIV_CIVILIZATION_H
