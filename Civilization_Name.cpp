//
// Created by david on 4/5/2019.
//

#include "Civilization_Name.h"
std::string Civilization_Name::civ_name_to_string(Civilization_Name::Names nm) {
    //todo:implement
    switch(nm) {
        case (WESTEROS) : {
            return "WESTEROS";
        }
        case (NIGHT_KING) : {
            return "NIGHT KING";
        }
        default : {
            return "NONE";
        }
    }
}

Civilization_Name::Names Civilization_Name::string_to_civ_name(std::string nm) {
    std::string n = "";
    for (char c : nm) {
        n+= std::toupper(c);
    }
    if ((n== "NIGHT_KING") || (n == "NIGHT KING")) {
        return Civilization_Name::NIGHT_KING;
    }
    else if (n == "WESTEROS") {
        return Civilization_Name::WESTEROS;
    }
    else {
        return Civilization_Name::NONE;
    }
}