//
// Created by david on 3/29/2019.
//
#ifndef CIV_TILE_TERRAIN_H
#define CIV_TILE_TERRAIN_H

#include <string>
#include <algorithm>

struct Tile_Terrain{


    enum names {
        DEFAULT,
        WATER,
        GRASSLAND,
        MOUNTAIN,
        HILL
    };

    static int get_movement_cost(names tocheck);

    static std::string terrain_to_string(names ter);

    static names string_to_terrain(std::string ter);

};

#endif //CIV_TILE_TERRAIN_H
