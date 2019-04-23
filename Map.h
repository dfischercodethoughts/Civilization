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


    void hide_map();

public:

    Map(int h, int w, int numx, int numy);
    Map(int h, int w, int numx, int numy,int xoff, int yoff);
    Map();

    int get_x() const;
    int get_y() const;

    //clears all tiles (for use before load)
    void clear();

    std::vector<std::vector<Tile>> * get_tiles();
    std::vector<std::vector<Tile>> get_tiles_const() const;

    Coordinate get_vector_coordinates_from_click(Coordinate click);

    Tile * get_tile_from_vector_coordinates(Coordinate coord);
    const Tile * get_const_tile_from_vector_coordinates(Coordinate coord) const;
    Tile * get_tile_from_click(Coordinate click);
    //assume id is good
    Tile * get_tile_from_id(int id);

    void set_background_square(Square set);

    static void remove_duplicates(std::vector<Tile*>& list);

    std::vector<Tile &> & get_tiles_driver(std::vector<std::unique_ptr<Tile>> & cur_list, Tile &cur_tile, int move_left);
    std::vector<Tile *> & get_tiles_driver(std::vector<Tile*> & cur_list, Tile & cur_tile, int move_left);
    std::vector<Tile *>* get_tiles_within_range(Tile *start, int movement);

    bool is_adjacent(Tile & first, Tile & second);

    /**
     * reveal method takes a unit or vector of units (which calls reveal unit on each unit in vector)
     * 
     * @param units
     */
    void reveal_units(std::vector<Unit *> units);
    void reveal_unit(Unit * unit);
    void reveal_city(City * city);
    void reveal_cities(std::vector<City *> rev);
    void make_visible(std::vector<Tile *>&);

    void draw() const override;

    //operators
    Map & operator=(Map const & cp);

    /**
     * outputs "MAP\nSQUARE\n...SQAUREINFO...\n#rows,#cols\nTILE1\nTILE2\n..."
     * @param outs
     * @param fill
     * @return
     */
    friend std::ostream & operator<<(std::ostream & outs, const Map & print);
    //assumes "MAP\n" has not already been read
    friend std::istream &operator>>(std::istream & ins, Map & fill);

    ~Map();
};

bool operator==(const Map & lhs, const Map & rhs);


#endif //CIV_MAP_H
