//
// Created by JING LU on 2019-04-19.
//

#include "City.h"
void City::set_name(std::string nme) {
    if (nme.length() < 15 & !Validator::has_special_char(nme) & !Validator::has_num(nme)) {
        name = nme;
    }
}

City::City() {
    ready_to_produce = false;
    ready_to_grow = false;
    building_in_production = Building_Name::NONE;
    unit_in_production = Unit::NONE;
    name = "Default";
    production = 0;
    food = 0;
    population = 0;
    prod_type = production_type::NONE;
}

City::City(std::string name) {
    //todo:implement city load from file constructor
}

City::City(Tile & home) {
    ready_to_produce = false;
    ready_to_grow = false;
    building_in_production = Building_Name::NONE;
    unit_in_production = Unit::NONE;
    name = "Default";
    production = 0;
    food = 0;
    population = 0;
    prod_type = production_type::NONE;
    home_tile = std::make_shared<Tile>(home);
}

std::string City::get_name() const {
    return name;
}

std::string City::get_production_item() const {
    switch (prod_type) {
        case (BUILDING) : {
            return Building::building_to_string(building_in_production);
        }
        case (UNIT) : {
            return Unit::unit_to_string(unit_in_production);
        }
        default: {
            return "None";
        }
    }
}

int City::get_production_output() const {
    int sum = 0;
    for (std::shared_ptr<Tile> tile : tiles) {
        sum += tile->get_output()->get_production();
    }
    return sum;
}

int City::get_food_output() const {
    int sum = 0;
    for (std::shared_ptr<Tile> tile :tiles) {
        sum += tile->get_output()->get_food();
    }
    return sum;
}

int City::get_gold_output() const {
    int sum = 0;
    for (std::shared_ptr<Tile> tile : tiles) {
        sum += tile->get_output()->get_gold();
    }
    return sum;
}

int City::get_population() const {
    return population;
}

void City::increase_population(std::vector<std::shared_ptr<Tile>> to_add) {
    population++;
    for (std::shared_ptr<Tile> add : to_add) {
        tiles.emplace_back(add);
    }
}

Tile_Output City::update_resources() {
    int tmp_food = 0;
    int tmp_production = 0;
    int tmp_gold = 0;
    Tile_Output to_ret;
    for (std::shared_ptr<Tile> tile : tiles) {
        std::shared_ptr<Tile_Output> temp = tile -> get_output();
        tmp_food += temp->get_food();
        tmp_gold += temp->get_gold();
        tmp_production += temp->get_production();
        to_ret.add_gold(temp->get_gold());
        to_ret.add_food(temp->get_food());
        to_ret.add_production(temp->get_production());
    }
    production += tmp_production;
    food += tmp_food;
    switch (prod_type) {
        case (BUILDING) : {
            if (production > Building::get_upkeep(building_in_production)) {
                ready_to_produce = true;
            }
            break;
        }
        case (UNIT) : {
            if(production > Unit::get_upkeep(unit_in_production)) {
                ready_to_produce = true;
            }
            break;
        }
    }

    if (food > (population^2)) {
        ready_to_grow = true;
    }

    return to_ret;
}

std::vector<std::shared_ptr<Building>> City::get_buildings() const {
    return buildings;
}

std::shared_ptr<Building> City::get_building(Tile &building) {
    return building.get_building();
}

std::vector<std::shared_ptr<Tile>> City::get_tiles() {
    return tiles;
}

void City::add_tiles(std::vector<std::shared_ptr<Tile>> to_add) {
    for (std::shared_ptr<Tile> tile : to_add) {
        tiles.emplace_back(tile);
    }
}

std::shared_ptr<Tile> City::get_home_tile() const {
    return home_tile;
}

bool City::set_production(std::string new_production) {
    Building_Name::names building_attempt = Building::string_to_building(new_production);
    Unit::names unit_attempt = Unit::string_to_unit(new_production);
    if (unit_attempt != Unit::NONE) {
        // we are producing a unit
        building_in_production = Building::NONE;
        prod_type = production_type::UNIT;
        unit_in_production = unit_attempt;
        return true;
    }
    else if (building_attempt != Building_Name::NONE) {
        building_in_production = building_attempt;
        prod_type = production_type::BUILDING;
        unit_in_production = Unit::NONE;
        return true;
    }
    return false;
}

bool City::produce_building(Tile &to_build_upon, Building_Name::names blding) {
    to_build_upon.create_building(blding);
}

bool City::produce_building(std::shared_ptr<Tile>to_build_upon, Building_Name::names blding) {
    to_build_upon->create_building(blding);
}
