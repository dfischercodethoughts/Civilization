//
// Created by david on 4/19/2019.
//

#include "Base_Resource.h"

std::string Base_Resource::to_string(names resource) {
    if (resource == FOOD)
        return "FOOD";
    else if (resource == PRODUCTION)
        return "PRODUCTION";
    else if (resource == GOLD)
        return "GOLD";
    else
        return "DEFAULT";
}


Base_Resource::names Base_Resource::string_to_base_resource(std::string res_str) {
    if (res_str == "FOOD") {
        return names(FOOD);
    } else if (res_str == "PRODUCTION") {
        return names(PRODUCTION);
    }else if (res_str == "GOLD") {
        return names(GOLD);
    }
    else {
        return names(DEFAULT);
    }
}