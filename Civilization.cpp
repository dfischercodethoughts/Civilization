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

std::vector<City *> Civilization::get_cities() {
    std::vector<City *> ret;
    for (int i = 0; i < cities.size();i++) {
        ret.emplace_back(&cities[i]);
    }
    return ret;
}

std::vector<const City *> Civilization::get_cities_const() const {
    std::vector<const City *> ret;
    for (int i = 0; i < cities.size();i++) {
        ret.emplace_back(&cities[i]);
    }
    return ret;
}

City * Civilization::get_city(int home_id) {
    for (int i= 0; i < cities.size();i++ ){
        if (cities[i].get_home_tile()->get_id() == home_id) {
            return &cities[i];
        }
    }
    return 0;
}

const City * Civilization::get_city_const(int home_id) const {
    for (int i= 0; i < cities.size();i++ ){
        if (cities[i].get_home_tile()->get_id() == home_id) {
            return &cities[i];
        }
    }
    return 0;
}

void Civilization::add_city(Map & m,Tile & newh) {
    City newc(newh);
    std::string line = "CITY " + std::to_string(cities.size());
    newc.set_name(line);
    for (Tile * t : *m.get_tiles_within_range(&newh,2)) {
        t->set_owner(name);
    }
    newc.add_tiles(*m.get_tiles_within_range(&newh, 2));

    cities.emplace_back(newc);
    newh.build_city(cities[cities.size()-1]);
}

void Civilization::remove_unit(const Unit & to_rem) {
    for (auto u = units.begin(); u < units.end();u++) {
        if (*u == to_rem) {
            units.erase(u);
            return;
        }
    }
}

bool Civilization::is_ai() const {
    return ai;
}

void Civilization::clear() {
    gold = 0;
    production = 0;
    food = 0;
    units.clear();
    name = Civilization_Name::NONE;
    ai = true;
}

bool Civilization::add_unit(Unit * un ) {
    if (un->get_unit_type()!=Unit::NONE && un->get_type() == Piece::UNIT) {
        Unit newu = Unit(*un);
        units.emplace_back(newu);
        return true;
    }
    return false;

}

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

bool Civilization::lost() {
    //todo: change to check if cities vector is empty
    if (units.empty()) {
        return true;
    }
    return false;
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

    Tile * move_from = &*map->get_tile_from_id(tilefrom);
    Tile * move_to = &*map->get_tile_from_id(tileto);
    std::vector<Tile *> *possible_tiles = map->get_tiles_within_range(move_from,get_unit(name,tilefrom)->get_current_movement());
    for (Tile * t : *possible_tiles) {
        if (*move_to == *t) {//tile selected is within movement range of the unit
            Unit *unit = get_unit(name, move_from->get_id());
            unit->use_movement(map->get_move_cost(move_from,move_to));
            unit->set_location(move_to->get_id());
            unit->set_center(move_to->get_center());
            //set move to tile unit; use move to's id since we already updated unit's location
            move_to->set_unit(*unit);
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
    for (int i = 0; i < units.size();i++){
        if (units[i].get_current_health() <= 0) {
            units.erase(units.begin() + i);
            i--;
        }
    }
}

void Civilization::next_turn(Map & m) {
    refresh();
    collect_resources();
    grow_cities(m);
}

void Civilization::collect_resources() {
    for (int i = 0; i < cities.size();i++) {
        Tile_Output tmp = cities[i].collect_resources();
        gold += tmp.get_gold();
        food += tmp.get_food();
        production += tmp.get_production();
    }
}

void Civilization::grow_cities(Map & m) {
    for (int i = 0; i < cities.size();i++) {
        if (cities[i].is_ready_to_grow())  {
            std::vector<Tile *> tl = *m.get_tiles_within_range(cities[i].get_home_tile(),cities[i].get_population()+1);
            //update civ
            for (Tile * t : tl) {
                t -> set_owner(name);
            }
            cities[i].grow(tl);
            //update tile city pointer
            m.get_tile_from_id(cities[i].get_home_tile()->get_id())->build_city(cities[i]);
        }
    }
}

bool Civilization::produce_building(Tile &to_build_upon, Building_Name::names blding) {
    for (City c : cities) {
        for (Tile *tmp : c.get_tiles()) {
            if (*tmp == to_build_upon) {
                to_build_upon.add_building(blding);
                return true;
            }
        }
    }
    return false;
}

bool Civilization::produce_building(Tile * to_build_upon, Building_Name::names blding) {
    for (City c : cities) {
        for (Tile *tmp : c.get_tiles()) {
            if (*tmp == to_build_upon) {
                to_build_upon->add_building(blding);
                return true;
            }
        }
    }
    return false;
}

bool Civilization::produce_unit(Tile & to_build_upon,Unit::Unit_Type u) {
    for (City c : cities) {
        for (Tile *tmp : c.get_tiles()) {
            if (*tmp == to_build_upon) {
                units.emplace_back(Unit(to_build_upon.get_id(),to_build_upon.get_center(),name,u));
                to_build_upon.set_unit(&*get_unit(name,to_build_upon.get_id()));
                return true;
            }
        }
    }
    return false;

}

bool Civilization::produce_unit(Tile *to_build_upon, Unit::Unit_Type unit) {
    for (City c : cities) {
        for (Tile *tmp : c.get_tiles()) {
            if (*tmp == to_build_upon) {
                units.emplace_back(Unit(to_build_upon->get_id(),to_build_upon->get_center(),name,unit));
                to_build_upon->set_unit(&*get_unit(name,to_build_upon->get_id()));
                return true;
            }
        }
    }
    return false;
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

    if (name != rh.get_name()) {
        return false;
    }
    for (int  i =0; i < units.size() && i < rh.get_units_const().size(); i++) {
        if (units[i] != *rh.get_units_const()[i]) {
            return false;
        }
    }
    if (ai != rh.is_ai()) {
        return false;
    }
    if (gold != rh.get_gold()) {
        return false;
    }
    if (production != rh.get_production()) {
        return false;
    }
    if (food != rh.get_food()) {
        return false;
    }

    return true;
}

std::ostream & operator<<(std::ostream & outs, const Civilization & print) {
    std::string line = "CIVILIZATION\n" + Civilization_Name::civ_name_to_string(print.name) + "\n" +
            std::to_string(print.gold) + ',' + std::to_string(print.production) + ',' +std::to_string(print.food) + "\n" +
            std::to_string(print.ai) + "\n";
    outs << line;
    for (int i =0 ; i < print.units.size();i++) {
        outs << print.units[i];
    }
    outs << "END"<<std::endl;//end marker because input burns line at end of for loop
    return outs;
}

std::istream & operator>>(std::istream & ins, Civilization & fill) {
    try {
        //NOTE: ASSUME "CIVILIZATION\n" is NOT already read (by game)
        //read in "name\n"
        std::string line = "";
        std::getline(ins,line);
        std::getline(ins, line);
        fill.name = Civilization_Name::string_to_civ_name(line);

        //read in "gold,prod,food\n"
        getline(ins, line);
        std::string tok = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        fill.gold = std::stoi(tok);
        tok = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        fill.production = std::stoi(tok);
        fill.food = std::stoi(line);

        //read in "is_ai\n"
        getline(ins,line);
        if (line == "1") {
            fill.ai = true;
        }
        else {
            fill.ai = false;
        }


        //read units while there is a unit in the next line
        getline(ins,line);
        while (line == "UNIT") {
            Unit *nu = new Unit();
            ins >> *nu;
            fill.add_unit(&*nu);
            getline(ins,line);
        }

    }
    catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }
    return ins;
}

Civilization::~Civilization() {
    gold = 0;
    production = 0;
    food = 0;
    units.clear();
    name = Civilization_Name::NONE;
    ai=false;
}