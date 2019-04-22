//
// Created by JING LU on 2019-04-19.
//

#include "City.h"
void City::set_name(std::string nme) {
    if (nme.length() < 15 && !Validator::has_special_char(nme) && !Validator::has_num(nme)) {
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
    home_tile = &home;
}

std::string City::get_name() const {
    return name;
}

std::string City::get_production_item() const {
    switch (prod_type) {
        case (BUILDING) : {
            return Building_Name::building_name_to_string(building_in_production);
        }
        case (UNIT) : {
            return Unit::unit_type_to_string(unit_in_production);
        }
        default: {
            return "NONE";
        }
    }
}

int City::get_production_output() const {
    int sum = 0;
    for (Tile * tile : tiles) {
        sum += tile->get_output().get_production();
    }
    return sum;
}

int City::get_food_output() const {
    int sum = 0;
    for (Tile * tile :tiles) {
        sum += tile->get_output().get_food();
    }
    return sum;
}

int City::get_gold_output() const {
    int sum = 0;
    for (Tile * tile : tiles) {
        sum += tile->get_output().get_gold();
    }
    return sum;
}

int City::get_population() const {
    return population;
}

Tile_Output City::get_output() const {
    Tile_Output ret;
    for (Tile * t : tiles) {
        ret.add_gold(t->get_output().get_gold());
        ret.add_food(t->get_output().get_food());
        ret.add_production(t->get_output().get_production());
    }
    return ret;
}

std::vector<Tile *> City::get_tiles() {
    std::vector<Tile *> ret;
    for (Tile *t : tiles) {
        ret.emplace_back(t);
    }
    return ret;
}

void City::add_tiles(std::vector<Tile *> to_add) {
    for (Tile * add : to_add) {
        tiles.emplace(&*add);
    }
}

Tile_Output City::update_resources() {
    int tmp_food = 0;
    int tmp_production = 0;
    int tmp_gold = 0;
    Tile_Output to_ret;
    for (Tile * tile : tiles) {
        Tile_Output temp = tile -> get_output();
        tmp_food += temp.get_food();
        tmp_gold += temp.get_gold();
        tmp_production += temp.get_production();
        to_ret.add_gold(temp.get_gold());
        to_ret.add_food(temp.get_food());
        to_ret.add_production(temp.get_production());
    }
    production += tmp_production;
    food += tmp_food;
    switch (prod_type) {
        case (BUILDING) : {
            if (production > Building_Name::get_production_cost(building_in_production)) {
                ready_to_produce = true;
            }
            break;
        }
        case (UNIT) : {
            if(production > Unit::get_production_cost(unit_in_production)) {
                ready_to_produce = true;
            }
            break;
        }
    }

    if (food > (population^2+40)) {
        ready_to_grow = true;
    }

    return to_ret;
}

Tile * City::get_home_tile() const {
    return home_tile;
}

bool City::has_barracks() const {
    for (Tile * t : tiles) {
        if (t->get_building().get_name()==Building_Name::BARRACKS) {
            return true;
        }
    }
    return false;
}

bool City::set_production(std::string new_production) {
    Building_Name::names building_attempt = Building_Name::string_to_building_name(new_production);
    Unit::Unit_Type unit_attempt = Unit::string_to_unit_type(new_production);
    if (unit_attempt != Unit::NONE) {
        // we are producing a unit
        building_in_production = Building_Name::NONE;
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


