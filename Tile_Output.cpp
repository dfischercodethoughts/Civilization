//
// Created by david on 4/19/2019.
//

#include "Tile_Output.h"

#include "Tile_Output.h"

bool Tile_Output::increment_production() {
    int old = get_production();
    production -> increment_number();
    if (get_production() == old) {
        return false;
    }
    return true;
}

bool Tile_Output::increment_food() {
    int old = get_food();
    food -> increment_number();
    if (get_food() == old) {
        return false;
    }
    return true;
}

bool Tile_Output::increment_gold() {
    int old = get_gold();
    gold -> increment_number();
    if (old == get_gold()) {
        return false;
    }
    return true;
}

bool Tile_Output::check_building(Building_Name::names nm) {
    switch (nm) {
        case (Building_Name::names::FARM ) : {
            if (increment_food()) {
                return true;
            } else return false;
        } case (Building_Name::names::HUNTING_LODGE) : {
            if (increment_food()) {
                return true;
            } else return false;
        }
        case (Building_Name::names::MARKET) : {
            if (increment_gold()) {
                return true;
            } else return false;
        } case (Building_Name::names::LOGGING_CAMP) : {
            if (increment_production()) {
                return true;
            } else return false;
        }
        case (Building_Name::names::MINE) : {
            if (increment_production()) {
                return true;
            } else return false;
        }
        default : {
            return false;
        }
    }
}

Tile_Output::Tile_Output() {
    production = std::make_unique<Base_Resource_Package>(Base_Resource::PRODUCTION);
    food = std::make_unique<Base_Resource_Package>(Base_Resource::FOOD);
    gold = std::make_unique<Base_Resource_Package>(Base_Resource::GOLD);
}

Tile_Output::Tile_Output(const Tile_Output & to_copy) {
    production = std::make_unique<Base_Resource_Package>(Base_Resource::PRODUCTION);
    food = std::make_unique<Base_Resource_Package>(Base_Resource::FOOD);
    gold = std::make_unique<Base_Resource_Package>(Base_Resource::GOLD);

    for ( int i = 0; i < to_copy.get_food();i++) {
        this -> increment_food();
    }
    for ( int i = 0; i < to_copy.get_production();i++) {
        this -> increment_production();
    }
    for ( int i = 0; i < to_copy.get_gold();i++) {
        this -> increment_gold();
    }
}

Tile_Output::Tile_Output(Tile_Resource::names res, Tile_Terrain::names terr) : Tile_Output() {
    switch (res) {
        case(Tile_Resource::WOODS): {
            increment_production();
        }
        case (Tile_Resource::IRON ): {
            increment_production();
        }
        case (Tile_Resource::STONE): {
            increment_production();
        }
        case (Tile_Resource::WHEAT) :  {
            increment_food();
        }
        case (Tile_Resource::GAZELLE) :  {
            increment_food();
        }
        case (Tile_Resource::FISH) :  {
            increment_food();
        }
        case (Tile_Resource::GOLD) : {
            increment_gold();
        }
        case(Tile_Resource::SILVER) : {
            increment_gold();
        }
    }

    switch(terr) {
        case (Tile_Terrain::WATER || Tile_Terrain::GRASSLAND) : {
            increment_food();
        }
        case (Tile_Terrain::HILL) : {
            increment_production();
        }
        case (Tile_Terrain::MOUNTAIN) : {
            increment_gold();
        }
    }
}

Tile_Output::Tile_Output(Tile_Resource::names res, Tile_Terrain::names terr, Building_Name::names bld) : Tile_Output(res,terr) {
    check_building(bld);
}

Tile_Output::Tile_Output(int prod, int fd, int gld) {
    production = std::make_unique<Base_Resource_Package>(Base_Resource_Package(Base_Resource::PRODUCTION,prod));
    food = std::make_unique<Base_Resource_Package>(Base_Resource_Package(Base_Resource::FOOD,fd));
    gold = std::make_unique<Base_Resource_Package>(Base_Resource_Package(Base_Resource::GOLD,gld));
}


void Tile_Output::add_production(int to_add) {
    production->add(to_add);
}

int Tile_Output::get_production() const {
    return production -> get_number();
}

void Tile_Output::add_gold(int tadd) {
    gold->add(tadd);
}

int Tile_Output::get_gold() const {
    return gold -> get_number();
}

void Tile_Output::add_food(int tad) {
    food->add(tad);
}

int Tile_Output::get_food() const {
    return food -> get_number();
}

Tile_Output & Tile_Output::operator=(const Tile_Output &to_copy) {
    for ( int i = 0; i < to_copy.get_food();i++) {
        this -> increment_food();
    }
    for ( int i = 0; i < to_copy.get_production();i++) {
        this -> increment_production();
    }
    for ( int i = 0; i < to_copy.get_gold();i++) {
        this -> increment_gold();
    }
    return *this;
}