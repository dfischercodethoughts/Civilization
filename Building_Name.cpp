//
// Created by willi on 4/19/19.
//

#include "Building_Name.h"

int Building_Name::get_production_cost(names n) {
    switch (n) {
        case (FARM) : {
            return 40;
            break;
        }
        case (MINE) : {
            return 40;
            break;
        }
        case (HARBOR) : {
            return 20;
            break;
        }
        case (TRADING_POST) : {
            return 40;
            break;
        }
        case (WORKSHOP) : {
            return 50;
            break;
        }
        case (LOGGING_CAMP) : {
            return 30   ;
            break;
        }
        case (MARKET) : {
            return 50;
            break;
        }
        case (BARRACKS) : {
            return 60;
            break;
        }

    }
}

std::string Building_Name::building_name_to_string(Building_Name::names nm) {
    switch (nm) {
        case (FARM) : {
            return "FARM";
        }
        case (MINE) : {
            return "MINE";
        }
        case (HARBOR) : {
            return "HARBOR";
        }
        case (TRADING_POST) : {
            return "TRADING POST";
        }
        case (WORKSHOP) : {
            return "WORKSHOP";
        }
        case (LOGGING_CAMP) : {
            return "LOGGING CAMP";
        }
        case (MARKET) : {
            return "MARKET";
        }
        case (BARRACKS) : {
            return "BARRACKS";
        }
        default : {
            return "NONE";
        }
    }
}

Building_Name::names Building_Name::string_to_building_name(std::string nm) {
    std::string name = "";
    for (int i = 0; i < nm.size();i++) {
        name += std::toupper(nm[i]);
    }
    if (name == "FARM") {
        return FARM;
    }
    else if (name == "MINE") {
        return MINE;
    }
    else if (name == "HARBOR") {
        return HARBOR;
    }
    else if (name == "TRADING_PORT" || name == "TRADING_POST") {
        return TRADING_POST;
    }
    else if (name == "WORKSHOP") {
        return WORKSHOP;
    }
    else if (name == "LOGGING_CAMP" || name == "LOGGING CAMP") {
        return LOGGING_CAMP;
    }
    else if (name == "MARKET") {
        return MARKET;
    }
    else {
        return NONE;
    }
}