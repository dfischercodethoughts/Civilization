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

class City {
private:
    enum production_type {
        BUILDING,
        UNIT,
        NONE
    };
    bool ready_to_produce;
    bool ready_to_grow;
    production_type prod_type;
    Building_Name::names building_in_production;
    Unit::Unit_Type unit_in_production;
    std::string name;
    int production;
    int food;
    int population;
    std::set<Tile *> tiles;
    Tile * home_tile;

    void increment_population();


public:
    //default city does not init tiles or home tile
    City();
    explicit City(Tile & home);

    std::string get_name() const;
    void set_name(std::string newname);

    bool is_ready_to_produce() const;
    bool get_ready_to_produce() const;
    bool is_ready_to_grow() const;
    bool get_ready_to_grow() const;

    std::string get_production_item() const;

    int get_production_output() const;
    int get_food_output() const;
    int get_gold_output() const;

    int get_population() const;

    Tile_Output get_output() const;

    std::vector<Tile *> get_tiles();
    void add_tiles(std::vector<Tile*> & to_add);

    std::vector<const Tile *> get_tiles_const() const;

    Tile_Output collect_resources();

    Tile * get_home_tile() const;
    void set_home_tile(Tile & newt);

    bool has_barracks()const;

    /**
     * @param new_production string of unit or building name
     * @return false if new production is not a unit or building (does nothing in that case), true else
     */
    bool set_production(std::string new_production);
    int get_production();
    //actual building of unit or building done by civilization


    //flips is ready to grow, sets food to zero, and adds given tiles
    void grow(std::vector<Tile *> tiles);

    void draw_on_viewport(Square sq);


    /******************************************************************************************
     * operators
     */
     City & operator=(const City & rhs);

     friend std::ostream & operator<<(std::ostream & outs, const City & ct);
     friend std::istream & operator>>(std::istream & ins, City & fill);
};

bool operator==(const City & lhs, const City & rhs);
#endif //CIV_CITY_H
