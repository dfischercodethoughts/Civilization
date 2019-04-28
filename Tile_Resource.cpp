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
