//
// Created by david on 4/3/2019.
//

#include "Civilization.h"

Civilization::Civilization() {
    name = Civilization_Name ::NONE;
    gold = 0;
    food = 0;
    production = 0;
}

Civilization::Civilization(std::string nm, std::shared_ptr<Tile> start, bool is_ai) {
    name = Civilization_Name::string_to_civ_name(nm);
    gold = 0;
    food=0;
    production=0;
    ai = is_ai;

}

Civilization::Civilization(std::string nm, bool is_ai) {
    name = Civilization_Name::string_to_civ_name(nm);
    gold = 0;
    food=0;
    production=0;
    ai = is_ai;

}

Civilization_Name::Names Civilization::get_name() const {
    return name;
}

std::string Civilization::get_name_str() const {
    return Civilization_Name::civ_name_to_string(name);
}

int Civilization::get_gold() const {
    return gold;
}

int Civilization::get_production() const {
    return production;
}

int Civilization::get_food() const {
    return food;
}

bool Civilization::is_ai() const {
    return ai;
}

bool Civilization::add_unit(Unit* newu, Tile & place) {
    if (place.get_unit() == nullptr) {
        Unit *to_add  =  new Unit(newu);
        to_add->set_center(place.get_center());
        units.emplace_back(&*to_add);
        place.set_unit(*to_add);
        return true;
    }
    else {
        return false;
    }

}

bool Civilization::add_unit(Unit::Unit_Type type, Tile & place) {

    if (place.get_unit() == nullptr) {
        Unit tmp = new Unit(place.get_id(),this->get_name(),type);
        tmp.set_center(place.get_center());
        units.emplace_back(tmp);
        place.set_unit(tmp);
        return true;
    }
    else {
        return false;
    }

}


std::vector<Unit *> Civilization::get_units() {
    std::vector<Unit*> to_ret;
    for (Unit &u : units) {
        to_ret.emplace_back(&u);
    }
    return to_ret;
}

std::vector<Unit *> Civilization::get_units_const()  const{
    std::vector<Unit*> to_ret;
    for (Unit u : units) {
        to_ret.emplace_back(&u);
    }
    return to_ret;
}

bool Civilization::move_unit(Map & map, Unit & to_move, Tile & move_to) {
    Tile & tile = *map.get_tile_from_click(to_move.get_center());
    std::vector<Tile *> tiles = map.get_tiles_within_range(&tile,to_move.get_current_movement());
    for (int i = 0 ; i < tiles.size()-1;i++) {
        if ((*tiles[i]) == move_to) {
            to_move.set_location(tiles[i]->get_id());
        }
    }
}

void Civilization::refresh() {
    for (int i = 0; i < units.size(); i++) {
        units[i].refresh();
    }
}

void Civilization::next_turn() {
    refresh();
    //todo:civilization next turn collects resources from cities

}

Civilization & Civilization::operator=(Civilization const &rh) {
    gold = rh.get_gold();
    production = rh.get_production();
    food = rh.get_food();
    for (Unit * un : rh.get_units_const()) {
        units.emplace_back(*un);
    }
    name = rh.get_name();
    ai = rh.is_ai();
}

bool Civilization::operator==(Civilization const & rh) {
    if (name == rh.get_name()) {
        return true;
    }
    return false;
}

Civilization::~Civilization() {
    gold = 0;
    production = 0;
    food = 0;
    units.clear();
    name = Civilization_Name::NONE;
    ai=false;
}