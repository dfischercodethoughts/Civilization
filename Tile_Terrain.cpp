//terrains for tiles are water, grassland, mountain, hill
#include "Tile_Terrain.h"

int Tile_Terrain::get_movement_cost(names tocheck) {
    switch (tocheck) {
        case (WATER) : {
            return 1;

        }
        case (GRASSLAND) : {
            return 1;

        }
        case (MOUNTAIN ) : {
            return 4;

        }
        case (HILL) : {
            return 2;

        }
        default : {
            return 0;
        }
    }
}

std::string Tile_Terrain::terrain_to_string(Tile_Terrain::names ter) {
    if (ter == Tile_Terrain::WATER) {
        return "WATER";
    } else if (ter == Tile_Terrain::GRASSLAND) {
        return "GRASSLAND";
    }else if (ter == Tile_Terrain::MOUNTAIN) {
        return "MOUNTAIN";
    }else if (ter == Tile_Terrain::HILL) {
        return "HILL";
    } else {
        return "DEFAULT";
    }
}

Tile_Terrain::names Tile_Terrain::string_to_terrain(std::string ter) {
    std::transform(ter.begin(),ter.end(),ter.begin(),::toupper);
    if (ter == "WATER") {
        return Tile_Terrain::names(Tile_Terrain::WATER);
    } else if (ter == "GRASSLAND") {
        return Tile_Terrain::names(Tile_Terrain::GRASSLAND);
    } else if (ter == "MOUNTAIN") {
        return Tile_Terrain::names(Tile_Terrain::MOUNTAIN);
    } else if (ter == "HILL") {
        return Tile_Terrain::names(Tile_Terrain::HILL);
    } else {
        return Tile_Terrain::names(Tile_Terrain::DEFAULT);
    }
}
