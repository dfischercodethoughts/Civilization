//
// Created by david on 4/3/2019.
//

#include "Civilization.h"

Civilization::Civilization() {
    name = Civilization_Name ::NONE;
    gold = 0;
    food = 0;
    production = 0;
    units = std::vector<Unit>();
}

Civilization::Civilization(std::string nm, std::shared_ptr<Tile> start, bool is_ai) {
    name = Civilization_Name::string_to_civ_name(nm);
    gold = 0;
    food=0;
    production=0;
    ai = is_ai;
    units = std::vector<Unit>();
}

Civilization::Civilization(std::string nm, bool is_ai) {
    name = Civilization_Name::string_to_civ_name(nm);
    gold = 0;
    food=0;
    production=0;
    ai = is_ai;
    units = std::vector<Unit>();
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

/**
bool Civilization::add_unit(Unit newu, Tile & place) {
    if (place.get_unit() == nullptr) {
        //Unit * u  = new Unit (newu);
        newu.set_center(place.get_center());
        newu.set_location(place.get_id());
        place.set_unit(newu);

        if (units.size() == 0) {
            units = std::vector<Unit>();
            units.emplace_back(&newu);
        }
        else {
            units.emplace_back(&newu);
        }
        return true;
    }
    else {
        return false;
    }

}
*/
bool Civilization::add_unit(Unit& newu, Tile & place) {
    if (place.get_unit() == nullptr) {
        newu.set_center(place.get_center());
        newu.set_location(place.get_id());
        place.set_unit(newu);
        units.emplace_back(&(newu));

        return true;
    }
    else {
        return false;
    }

}

bool Civilization::add_unit(Unit* newu, Tile & place) {
    if (place.get_unit() == nullptr) {
        newu->set_center(place.get_center());
        newu->set_location(place.get_id());
        units.emplace_back(*newu);
        place.set_unit(&*newu);
        return true;
    }
    else {
        return false;
    }

}

bool Civilization::add_unit(Unit::Unit_Type type, Tile & place) {

    if (place.get_unit() == nullptr) {
        Unit tmp = new Unit(place.get_id(),place.get_center(),get_name(),type);
        tmp.set_center(place.get_center());
        units.emplace_back(tmp);
        place.set_unit(tmp);
        return true;
    }
    else {
        return false;
    }

}

Unit * Civilization::get_unit(Civilization_Name::Names owner, int tileid) {
    for(int i = 0; i < units.size();i++) {
        if (units[i].get_location_id() == tileid && units[i].get_owner() == owner) {
            return &units[i];
        }
    }
    return &*new Unit();
}

Unit * Civilization::get_unit_const(Civilization_Name::Names owner, int tileid) const {
    for(int i = 0; i < units.size();i++) {
        if (units[i].get_location_id() == tileid && units[i].get_owner() == owner) {
            return &*new Unit(units[i]);
        }
    }
    return &*new Unit();
}

Unit * Civilization::get_unit(Civilization_Name::Names owner, Tile & tile) {
    for(int i = 0; i < units.size();i++) {
        if (units[i].get_location_id() == tile.get_id() && units[i].get_owner() == owner) {
            return &units[i];
        }
    }
    return &*new Unit();
}

Unit * Civilization::get_unit_const(Civilization_Name::Names owner, Tile & tile) const {
    for(int i = 0; i < units.size();i++) {
        if (units[i].get_location_id() == tile.get_id() && units[i].get_owner() == owner) {
            return &*new Unit(units[i]);
        }
    }
    return &*new Unit();
}

std::vector<Unit *> Civilization::get_units() {
    std::vector<Unit*> to_ret;
    for (int i = 0; i < units.size();i++) {
        to_ret.emplace_back(new Unit(units[i]));
    }
    return to_ret;
}

std::vector<Unit *> Civilization::get_units_const()  const{
    std::vector<Unit*> to_ret;
    for (int i = 0; i < units.size();i++) {
        Unit * u = new Unit(units[i]);
        to_ret.emplace_back(u);
    }
    return to_ret;
}

bool Civilization::move_unit(Map & map, Unit & to_move, Tile & move_to) {
 //   std::vector<Tile *> tiles = map.get_tiles_within_range(&tile,to_move.get_current_movement());
  //  for (int i = 0 ; i < tiles.size()-1;i++) {
    //    if ((*tiles[i]) == move_to) {
    Tile * move_from = map.get_tile_from_click(to_move.get_center());
    to_move.use_movement(Tile_Terrain::get_movement_cost(move_to.get_terrain()));
    to_move.set_location(move_to.get_id());
    to_move.set_center(move_to.get_center());
    move_to.set_unit(to_move);
    move_from->clear_unit();
    return true;
    //    }
   // }
}

bool Civilization::move_unit(Map * map, Unit * to_move, Tile * move_to) {
    ;
    //   std::vector<Tile *> tiles = map.get_tiles_within_range(&tile,to_move.get_current_movement());
    //  for (int i = 0 ; i < tiles.size()-1;i++) {
    //    if ((*tiles[i]) == move_to) {
    Tile * move_from = map->get_tile_from_click(to_move->get_center());
    to_move->use_movement(Tile_Terrain::get_movement_cost(move_to->get_terrain()));
    to_move->set_location(move_to->get_id());
    to_move->set_center(move_to->get_center());
    move_to->set_unit(*to_move);
    move_from->clear_unit();
    return true;
    //    }
    // }
}

bool Civilization::move_unit(Map * map, int tilefrom, int tileto) {

    Tile * move_from = map->get_tile_from_id(tilefrom);
    Tile * move_to = map->get_tile_from_id(tileto);
    if (move_from->has_unit()) {
        Unit *to_move = get_unit(Civilization_Name::WESTEROS, tilefrom);
        if (move_from->has_unit() && map->is_adjacent(*move_from, *move_to) && move_to->has_unit() &&
            move_to->get_unit()->get_owner() != Civilization_Name::WESTEROS) {
            //todo : cause damage
            move_to->get_unit()->cause_damage(to_move->get_unit_type());
            to_move->cause_damage(move_to->get_unit()->get_unit_type());
            //if attack destroys defender, remove it from tile (still need to remove from civilization, done in game::process click)
            if (move_to->get_unit()->get_current_health() <= 0 ) {
                move_to->clear_unit();
            }
            if (to_move->get_current_health() <= 0) {
                move_from->clear_unit();
            }
            to_move->use_movement(Unit::get_max_movement(to_move->get_unit_type()));
            return false;//attacked but did not actually move the unit, so return false

        //do nothing if player unit on square
        } else if (move_from->has_unit() && map->is_adjacent(*move_from, *move_to) && move_to->has_unit()) {
            return false;
        }
        //perform a normal move if tile clicked is adjacent to tile to move from
        else if (map->is_adjacent(*move_from, *move_to)) {
            to_move->use_movement(Tile_Terrain::get_movement_cost(move_to->get_terrain()));
            to_move->set_location(move_to->get_id());
            to_move->set_center(move_to->get_center());
            move_to->set_unit(to_move);
            move_from->clear_unit();
            move_from->draw();
            move_to->draw();

            return true;
        }


    }
    return false;

}

void Civilization::refresh() {
    for (int i = 0; i < units.size(); i++) {
        units[i].refresh();
    }
}

void Civilization::destroy_units() {
    for (auto u = units.begin();u != units.end(); u++){
        if (u->get_current_health() <= 0) {
            units.erase(u);
        }
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
    auto u = rh.get_units_const();
    for (int i = 0; i < u.size();i++) {
        Unit *un = new Unit(u[i]);
        units.emplace_back(*un);
    }
    name = rh.get_name();
    ai = rh.is_ai();
	return *this;
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