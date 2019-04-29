//
// Created by david on 3/29/2019.
//

#ifndef CIV_TILE_RESOURCE_H
#define CIV_TILE_RESOURCE_H
#include <string>
/**
 * low level tile resource struct holds the resource names enum and static helper methods
 */
struct Tile_Resource {
    enum names {
        DEFAULT,
        WOODS,
        IRON,
        WHEAT,
        FISH,
        GAZELLE,
        GOLD,
        SILVER,
        STONE
    };

    static std::string resource_to_string(Tile_Resource::names res);

    static names string_to_resource(std::string res);

};

#endif //CIV_TILE_RESOURCE_H
