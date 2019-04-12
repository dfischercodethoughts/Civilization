//
// Created by david on 4/3/2019.
//

#include "Unit.h"
#include "Square.h"
#include "Tile.h"


std::string Unit::unit_type_to_string(Unit::Unit_Type unit_name) {
    switch (unit_name) {
        case(WARRIOR): {
            return("WARRIOR");
        }
        case (ARCHER) : {
            return("ARCHER");
        }
        case (BOAT): {
            return("BOAT");
        }
        case (HORSEMAN): {
            return("HORSEMAN");
        }
        case (SCOUT) : {
            return("SCOUT");
        }
        case(SETTLER) : {
            return("SETTLER");
        }
        default : {
            return "NONE";
        }
    }
}

Unit::Unit_Type Unit::string_to_unit_type(std::string type) {
    if (type == "WARRIOR") {
        return WARRIOR;
    }
    else if (type == "ARCHER") {
        return ARCHER;
    }
    else if (type == "BOAT") {
        return BOAT;
    }
    else if (type == "SETTLER") {
        return SETTLER;
    }
    else if (type == "HORSEMAN") {
        return HORSEMAN;
    }
    else if (type == "SCOUT") {
        return SCOUT;
    }
    else {
        return NONE;
    }
}

int Unit::get_max_health(Unit_Type tp) {
    switch (tp) {
        case(WARRIOR): {
            return(40);
        }
        case (ARCHER) : {
            return(25);
        }
        case (BOAT): {
            return(65);
        }
        case (HORSEMAN): {
            return(60);
        }
        case (SCOUT) : {
            return(25);
        }
        case(SETTLER) : {
            return(10);
        }
    }
}

int Unit::get_max_movement(Unit::Unit_Type tp) {
    switch(tp) {
        case(WARRIOR) : {
            return(2);
        }
        case(ARCHER) : {
            return(2);
        }
        case(BOAT) : {
            return(5);
        }
        case(SETTLER) : {
            return(4);
        }
        case (SCOUT) : {
            return(5);
        }
        case (HORSEMAN) : {
            return(6);
        }
    }
}

int Unit::get_upkeep(Unit_Type ty) {
    switch (ty) {
        case (ARCHER) : {
            return 1;
        }
        case (WARRIOR) : {
            return 1;
        }
        case (HORSEMAN) : {
            return 3;
        }
        case (BOAT) : {
            return 2;
        }
        default : {
            return 0;
        }
    }
}

int Unit::get_gold_cost(Unit::Unit_Type tp) {
    switch (tp) {
        case (ARCHER) : {
            return 10;
        }
        case (WARRIOR) : {
            return 10;
        }
        case (HORSEMAN) : {
            return 30;
        }
        case (BOAT) : {
            return 20;
        }
        default : {
            return 0;
        }
    }
}

int Unit::get_damage(Unit_Type tp) {
    switch (tp) {
        case (WARRIOR) : {
            return 10;
        }
        case (ARCHER) : {
            return  13;
        }
        case (BOAT): {
            return  25;
        }
        case (HORSEMAN) : {
            return  20;
        }
        case (SCOUT) : {
            return  5;
        }
        case (SETTLER) : {
            return  1;
        }
    }
}

void Unit::set_movement(int newm) {
    if (abs(newm) < 10) {
        movement = newm;
    }
}

void Unit::reset_movement() {
    movement = get_max_movement(unit_type);
}

void Unit::set_health(int newh) {
    if (newh >= 0 & newh < 100) {
        health = newh;
    }
}

void Unit::reset_health() {
    health = get_max_health(unit_type);
}

void Unit::set_damage() {
    damage = get_damage(unit_type);
}

Unit::Unit() {
    tile_id = 0;
    owner = Civilization_Name::NONE;
    health = -1; damage = -1; movement = -1;
    unit_type = NONE;
    this->set_type(Piece_Type::UNIT);
}

Unit::Unit(int  loc, Unit_Type tp) {
    this->set_type(Piece_Type::UNIT);
    tile_id = loc;
    unit_type = tp;
    owner = Civilization_Name::NONE;
    full_heal();
    set_damage();
    reset_movement();
}

Unit::Unit(int loc, Civilization_Name::Names own, Unit_Type tp) {
    this->set_type(Piece_Type::UNIT);
    this->set_height(Tile::TILE_HEIGHT);
    this->set_width(Tile::TILE_WIDTH);
    this->set_center({0,0});
    tile_id = loc;
    unit_type = tp;
    owner = own;
    full_heal();
    set_damage();
    reset_movement();
}

Unit::Unit(Unit const & cp) {
    this->set_type("UNIT");
    this->set_height(cp.get_height());
    this->set_width(cp.get_width());
    this->set_center(cp.get_center());
    tile_id = cp.get_location_id();
    unit_type = cp.get_unit_type();
    owner  = cp.get_owner();
    full_heal();
    set_damage();
    reset_movement();
}

Unit::Unit(Unit const * cpy) {
    this->set_type(Piece_Type::UNIT);
    this->set_height(cpy->get_height());
    this->set_width(cpy->get_width());
    this->set_center(cpy->get_center());
    tile_id = cpy->get_location_id();
    unit_type = cpy->get_unit_type();
    owner = cpy->get_owner();
    full_heal();
    set_damage();
    reset_movement();
}

int Unit::get_location_id() const {
    return tile_id;
}

Civilization_Name::Names Unit::get_owner() const {
    return owner;
}

int Unit::get_current_health() const {
    return health;
}

int Unit::get_current_movement() const {
    return movement;
}

int Unit::get_upkeep() const {
    return get_upkeep(unit_type);
}

int Unit::get_max_health() const {
    return get_max_health(unit_type);
}

int Unit::get_damage() const {
    return get_damage(unit_type);
}

Unit::Unit_Type Unit::get_unit_type() const {
    return unit_type;
}

void Unit::set_location(int newl) {
    if (newl>=0&newl<10) {
        tile_id = newl;
    }
}


void Unit::set_owner(Civilization_Name::Names newown) {
    owner = newown;
}

void Unit::set_unit_type(Unit_Type newtype) {
    if (newtype != NONE) {
        unit_type = newtype;
    }
}

void Unit::use_movement(int use) {
    use = abs(use);
    movement = std::max(0,movement-use);
}

void Unit::draw() {

}

void Unit::draw_on_tile(Square base) {
    glColor3f(base.get_text_color().get_red(),base.get_text_color().get_green(),base.get_text_color().get_blue());
    glRasterPos2i(base.get_center().x+base.get_width()/8, base.get_center().y - 3*base.get_height()/8);
    std::string line = "U: " + unit_type_to_string(get_unit_type());
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,c);
    }
}

void Unit::draw_on_viewport(Square base) {
    glColor3f(base.get_text_color().get_red(),base.get_text_color().get_green(),base.get_text_color().get_blue());
    glRasterPos2i(base.get_center().x-3*base.get_width()/8,base.get_center().y - 3*base.get_height()/8);
    std::string line = "TYPE: " + unit_type_to_string(get_unit_type());
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,c);
    }

    glColor3f(base.get_text_color().get_red(),base.get_text_color().get_green(),base.get_text_color().get_blue());
    glRasterPos2i(base.get_center().x-3*base.get_width()/8,base.get_center().y - base.get_height()/8);
    line = "OWNER: " + Civilization_Name::civ_name_to_string(get_owner());
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,c);
    }

    glColor3f(base.get_text_color().get_red(),base.get_text_color().get_green(),base.get_text_color().get_blue());
    glRasterPos2i(base.get_center().x-3*base.get_width()/8,base.get_center().y + base.get_height()/8);
    line = "MOVEMENT LEFT: " + std::to_string(get_current_movement());
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,c);
    }

    glColor3f(base.get_text_color().get_red(),base.get_text_color().get_green(),base.get_text_color().get_blue());
    glRasterPos2i(base.get_center().x-3*base.get_width()/8,base.get_center().y + 3*base.get_height()/8);
    line = "MAX MOVEMENT: " + std::to_string(get_max_movement(get_unit_type()));
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,c);
    }

    glColor3f(base.get_text_color().get_red(),base.get_text_color().get_green(),base.get_text_color().get_blue());
    glRasterPos2i(base.get_center().x+base.get_width()/8,base.get_center().y -3* base.get_height()/8);
    line = "HEALTH LEFT: " + std::to_string(get_current_health());
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,c);
    }

    glColor3f(base.get_text_color().get_red(),base.get_text_color().get_green(),base.get_text_color().get_blue());
    glRasterPos2i(base.get_center().x+base.get_width()/8,base.get_center().y - base.get_height()/8);
    line = "MAX HEALTH: " + std::to_string(get_max_health());
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,c);
    }
}

int Unit::cause_damage(Unit_Type attacking) {
    set_health(get_damage(attacking));
}

void Unit::full_heal() {
    health = get_max_health(unit_type);
}

void Unit::heal() {
    int maxh = get_max_health(unit_type);
    health = std::min(maxh, health + (maxh/20));
}

void Unit::refresh() {
    heal();
    reset_movement();
}

bool Unit::operator==(Unit const & rhs) {
    if (owner == rhs.get_owner() && tile_id == rhs.get_location_id()) {
        return true;
    }
    return false;
}

Unit & Unit::operator=(Unit const &rhs) {
    this->set_type(rhs.get_type());
    this->set_center(rhs.get_center());
    set_message(rhs.get_message());
    set_height(rhs.get_height());
    set_fill(rhs.get_fill());
    set_text_color(rhs.get_text_color());
    set_width(rhs.get_width());
    set_y_offset(rhs.get_y_offset());
    set_x_offset(rhs.get_x_offset());
    owner = rhs.get_owner();
    unit_type = rhs.unit_type;
    reset_movement();
    reset_health();
    set_damage();
    set_location(rhs.get_location_id());
}

Unit::~Unit() {
    tile_id = -1;
    owner = Civilization_Name::NONE;
    health = -1;
    damage = -1;
    movement = -1;
    unit_type = Unit_Type ::NONE;

}