//
// Created by david on 4/3/2019.
//

#ifndef CIV_MAP_H
#define CIV_MAP_H

#include "Tile.h"
#include <vector>
#include <set>

class Map : public Square {
private:
    std::vector<std::vector<Tile>> tiles;

    void make_visible(std::vector<Tile *>&);
    void hide_map();

public:

    Map(int h, int w, int numx, int numy);
    Map(int h, int w, int numx, int numy,int xoff, int yoff);
    Map();

    Coordinate get_vector_coordinates_from_click(Coordinate click);

    Tile * get_tile_from_vector_coordinates(Coordinate coord);
    const Tile * get_const_tile_from_vector_coordinates(Coordinate coord) const;
    Tile * get_tile_from_click(Coordinate click);
    //assume id is good
    Tile * get_tile_from_id(int id);

    static void remove_duplicates(std::vector<Tile*>& list);

    std::vector<Tile &> & get_tiles_driver(std::vector<std::unique_ptr<Tile>> & cur_list, Tile &cur_tile, int move_left);
    std::vector<Tile *> & get_tiles_driver(std::vector<Tile*> & cur_list, Tile & cur_tile, int move_left);

    std::vector<Tile *> get_tiles_within_range(Tile *start, int movement);

    bool is_adjacent(Tile & first, Tile & second);

    //todo:implement map reveal method - sets tile visible to false if tile
    //more than two coordinates away from tile unit is on
    void reveal(std::vector<Unit *> units);

    void draw() const override;

    //operators
    Map & operator=(Map const & cp);

    ~Map();
};


#endif //CIV_MAP_H
