//
// Created by JING LU on 2019-04-19.
//

#ifndef CIV_CITY_H
#define CIV_CITY_H
#include "Validator.h"
#include "Tile.h"
#include "Building.h"
#include <vector>
#include <set>

/**
 * city class is owned by civilization
 * can grow, and has a production pool as well as a food pool, as well as a population level. It has a vector of tile pointers to tiles
 *      under its influence. has a pointer to its home tile
 * previous functionality included a production type, so the city had a production, and would work on it until it was completed,
 *      similar to the video game
 */
class City {
private:
    enum production_type {
        BUILDING,
        UNIT,
        NONE
    };

    bool ready_to_grow;
    /*
    bool ready_to_produce;
    production_type prod_type;

    Building_Name::names building_in_production;
    Unit::Unit_Type unit_in_production;
     */
    std::string name;
    int production;
    int food;
    int population;
    std::set<Tile *> tiles;
    Tile * home_tile;

    //increases population by one
    void increment_population();

public:
    //default city does not init tiles or home tile
    City();
    City(City * c);
    explicit City(Tile & home);

    //name getters and setters
    std::string get_name() const;
    void set_name(std::string newname);

    //ready to grow getters
    bool is_ready_to_grow() const;
    bool get_ready_to_grow() const;

    /*
     * @return amount the city makes of each resource per turn
     */
    int get_production_output() const;
    int get_food_output() const;
    int get_gold_output() const;

    //property pool getters
    int get_population() const;
    int get_production() const;
    //uses a certain amount of production; does not set production less than 0
    void use_production(int to_use);
    int get_food() const;

    //returns essentially a tuple structure with the amount of food, gold and production produced by the city
    Tile_Output get_output() const;

    /**
     * tiles under city's control getters
     * @return tiles
     */
    std::vector<Tile *> get_tiles();
    void add_tiles(std::vector<Tile*> & to_add);

    std::vector<const Tile *> get_tiles_const() const;

    /**
     * iterates through tiles in control and updates resource pools based on tile attributes
     *      uses tile::get_output()
     * @return tile output with total amount of city's
     */
    Tile_Output collect_resources();

    /**
     * home tile getter and setter
     */
    Tile * get_home_tile() const;
    void set_home_tile(Tile & newt);

    bool has_barracks()const;

    //actual building of unit or building done by civilization

    //flips is ready to grow, sets food to zero, and adds given tiles
    void grow(std::vector<Tile *> tiles);

    //draws city information on top of white square copied from square given
    void draw_on_viewport(Square sq);


    /******************************************************************************************
     * operators
     */
     City & operator=(const City & rhs);

     /**
      * outputs CITY
      *             name
      *             production
      *             food
      *             population
      *             home_tile_id
      *             is_ready_to_grow
      *      Note that this does not populate the cities tiles, but fills it with placeholders (with the proper id)
      *      game will need to iterate through a civ's cities, and tie them to the map tiles
      * @param outs
      * @param city to print or city to fill
      * @return
      */
     friend std::ostream & operator<<(std::ostream & outs, const City & ct);
     friend std::istream & operator>>(std::istream & ins, City & fill);
};

bool operator==(const City & lhs, const City & rhs);
bool operator!=(const City & lhs, const City & rhs);
#endif //CIV_CITY_H
