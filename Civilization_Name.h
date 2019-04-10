//
// Created by david on 4/5/2019.
//

#ifndef CIV_CIVILIZATION_NAME_H
#define CIV_CIVILIZATION_NAME_H

#include <string>

struct Civilization_Name {
    enum Names {
        WESTEROS,
        NIGHT_KING,
        NONE
    };

    static std::string civ_name_to_string(Civilization_Name::Names nm);

    static Civilization_Name::Names string_to_civ_name(std::string nm);
};


#endif //CIV_CIVILIZATION_NAME_H
