//
// Created by JING LU on 2019-04-19.
//

#include "City.h"
void City::increment_population() {
    population++;
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
void City::set_name(std::string nme) {
    if (nme.length() < 15 && !Validator::has_special_char(nme) && !Validator::has_num(nme)) {
        name = nme;
    }
}

bool City::is_ready_to_produce() const {
    return ready_to_produce;
}

bool City::get_ready_to_produce() const {
    return ready_to_produce;
}

bool City::is_ready_to_grow() const {
    return ready_to_grow;
}

bool City::get_ready_to_grow() const {
    return ready_to_grow;
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

void City::add_tiles(std::vector<Tile *> & to_add) {
    for (Tile * add : to_add) {
        tiles.emplace(&*add);
    }
}

std::vector<const Tile *> City::get_tiles_const() const {
    std::vector<const Tile *> ret;
    for(Tile * t:tiles) {
        ret.emplace_back(t);
    }
    return ret;
}

Tile_Output City::collect_resources() {
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

void City::set_home_tile(Tile & t) {
    home_tile = &t;
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

void City::grow(std::vector<Tile *> tl) {
    increment_population();
    add_tiles(tl);
}

void City::draw_on_viewport(Square sq) {
    sq.draw();
    std::string line = "CITY: " + name;
    glColor3f(Colors::BLACK.get_red(),Colors::BLACK.get_green(),Colors::BLACK.get_blue());
    glRasterPos2i(sq.get_center().x-sq.get_width()/2+sq.get_width()/4,sq.get_center().y-3*sq.get_height()/8);
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c);
    }

    line = "PROD: " + std::to_string(production);
    glRasterPos2i(sq.get_center().x-sq.get_width()/2+sq.get_width()/16,sq.get_center().y-sq.get_height()/8);
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
    }

    line = "FOOD: " + std::to_string(food);
    glRasterPos2i(sq.get_center().x-sq.get_width()/2+sq.get_width()/16,sq.get_center().y+sq.get_height()/8);
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
    }

    line = "GOLD: " + std::to_string(get_gold_output());
    glRasterPos2i(sq.get_center().x-sq.get_width()/2+sq.get_width()/16,sq.get_center().y+3*sq.get_height()/8);
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
    }

    line = "PRODUCING";
    glRasterPos2i(sq.get_center().x+sq.get_width()/16,sq.get_center().y-sq.get_height()/8);
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
    }

    line = get_production_item();
    glRasterPos2i(sq.get_center().x+sq.get_width()/16,sq.get_center().y+sq.get_height()/8);
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
    }
}

City & City::operator=(const City & rhs) {
    ready_to_grow = rhs.ready_to_grow;
    ready_to_produce = rhs.ready_to_produce;
    prod_type = rhs.prod_type;
    building_in_production = rhs.building_in_production;
    unit_in_production = rhs.unit_in_production;
    if (rhs.name.size() < 25) {
        name = rhs.name;
    }
    else {
        name = "";
    }
    production = rhs.production;
    food = rhs.food;
    population = rhs.population;
    home_tile = &*rhs.home_tile;
    for (auto t = rhs.tiles.begin();t != rhs.tiles.end();t++) {
        tiles.emplace(new Tile(*t));
    }
}

//todo:implement city input output

bool operator==(const City & lhs, const City & rhs) {
    if (lhs.is_ready_to_produce() == rhs.is_ready_to_produce() && lhs.get_production_item() == rhs.get_production_item() &&
        lhs.get_name() == rhs.get_name() && *lhs.get_home_tile() == *rhs.get_home_tile()) {
        return true;
    }
    return false;
}
