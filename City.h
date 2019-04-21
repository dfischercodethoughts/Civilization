//
// Created by JING LU on 2019-04-19.
//

#ifndef CIV_CITY_H
#define CIV_CITY_H
#include "Validator.h"
#include "Tile.h"
#include <vector>

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
    Building::names building_in_production;
    Unit::names unit_in_production;
    std::string name;
    int production;
    int food;
    int population;
    std::vector<std::shared_ptr<Building>> buildings;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::shared_ptr<Tile> home_tile;

    void set_name(std::string nme);

public:
    //default city does not init tiles or home tile
    City();
    explicit City(std::string name);
    explicit City(Tile & home);

    std::string get_name() const;

    std::string get_production_item() const;

    int get_production_output() const;
    int get_food_output() const;
    int get_gold_output() const;

    int get_population() const;
    void increase_population(std::vector<std::shared_ptr<Tile>> to_add);

    Tile_Output update_resources();

    std::vector<std::shared_ptr<Building>> get_buildings() const;

    std::shared_ptr<Building> get_building(Tile & building);

    std::vector<std::shared_ptr<Tile>> get_tiles();
    void add_tiles(std::vector<std::shared_ptr<Tile>> to_add);

    std::shared_ptr<Tile> get_home_tile() const;



    /**
     *
     * @param new_production string of unit or building name
     * @return false if new production is not a unit or building (does nothing in that case), true else
     */
    bool set_production(std::string new_production);

    bool produce_building(Tile & to_build_upon, Building::names blding);
    bool produce_building(std::shared_ptr<Tile> to_build_upon, Building::names blding);

    bool produce_unit(Tile & to_build_upon, Unit::names unit);
    bool produce_unit(std::shared_ptr<Tile> to_build_upon, Unit::names unit);

    /**
     * switches on production type
     * units are made in the tile of the city
     * buildings are produced with a tile click
     * @return
     */
    bool produce();

    bool grow();
};
#endif //CIV_CITY_H
