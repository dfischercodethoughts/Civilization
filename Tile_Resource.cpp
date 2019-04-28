//tile_resources are woods, iron, wheat, fish, gazelle, gold, silver, stone

#include "Tile_Resource.h"
std::string Tile_Resource::resource_to_string(Tile_Resource::names res) {
    if (res == DEFAULT) {
        return "DEFAULT";
    } else if (res == WOODS) {
        return "WOODS";
    }else if (res == IRON) {
        return "IRON";
    } else if (res == WHEAT) {
        return "WHEAT";
    } else if (res == FISH) {
        return "FISH";
    } else if (res == GAZELLE) {
        return "GAZELLE";
    } else if (res == GOLD) {
        return "GOLD";
    } else if (res == SILVER) {
        return "SILVER";
    } else if (res == STONE) {
        return "STONE";
    } else {
        return "DEFAULT";
    }
}

Tile_Resource::names Tile_Resource::string_to_resource(std::string res) {
    if (res == "WOODS") {
        return names(WOODS);
    } else if (res == "IRON") {
        return names(IRON);
    } else if (res == "WHEAT") {
        return names(WHEAT);
    } else if (res == "GAZELLE") {
        return names(GAZELLE);
    } else if (res == "GOLD") {
        return names(GOLD);
    } else if (res == "SILVER") {
        return names(SILVER);
    } else if (res == "STONE") {
        return names(STONE);
    } else {
        return names(DEFAULT);
    }
}

float Tile_Resource::get_resource_probability(Tile_Resource::names res) {
    switch (res) {
        case (Tile_Resource::SILVER): {
            return .05;
        }
        case (Tile_Resource::GOLD): {
            return .05;
        }
        case (Tile_Resource::STONE): {
            return .1;
        }
        case (Tile_Resource::WHEAT): {
            return .25;
        }
        case (Tile_Resource::GAZELLE): {
            return .15;
        }
        case (Tile_Resource::WOODS): {
            return .2;
        }
        case (Tile_Resource::IRON): {
            return .1;
        }
        case (Tile_Resource::FISH): {
            return .1;
        }
        default:
            return 0;
    }
}
