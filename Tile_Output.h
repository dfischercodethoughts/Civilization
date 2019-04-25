//
// Created by david on 4/19/2019.
//

#ifndef CIV_TILE_OUTPUT_H
#define CIV_TILE_OUTPUT_H

//
// Created by david on 3/29/2019.
//

#include "Base_Resource_Package.h"
#include <memory>
#include "Building.h"
#include "Tile_Resource.h"
#include "Tile_Terrain.h"

//todo:implement copy constructor
class Tile_Output {

    private:
        //0 - food 1 - gold 2 - production
        std::unique_ptr<Base_Resource_Package> production;
        std::unique_ptr<Base_Resource_Package> food;
        std::unique_ptr<Base_Resource_Package> gold;

        friend class Tile;

        bool increment_production();
        bool increment_gold();
        bool increment_food();
		bool check_building(Building::names nm);

    public:
        Tile_Output();
        Tile_Output(const Tile_Output & output_cpy);
        Tile_Output(Tile_Resource::names res, Tile_Terrain::names ter);
        Tile_Output(Tile_Resource::names res, Tile_Terrain::names ter, Building::names bld);
        Tile_Output(int production,int food, int gold);

        void add_production(int to_add);
        int get_production() const;

        void add_gold(int to_add);
        int get_gold() const;

        void add_food(int to_add);
        int get_food() const;

        Tile_Output & operator=(const Tile_Output & to_copy);
};



#endif //CIV_TILE_OUTPUT_H
