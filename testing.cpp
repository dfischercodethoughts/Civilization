//
// Created by david on 4/13/2019.
//

#include "Map.h"
#include "iostream"

void test_get_vec_coordinates_from_click(Map & m) {
    std::cout << "TESTING GET VEC COORDINATES FROM CLICK" << std::endl;
    for (std::vector<Tile> list : *m.get_tiles()) {
        for (Tile t : list) {
            std::cout << "GETTING VECTOR COORDINATES OF TILE CENTERED AT " << std::to_string(t.get_center().x) << "," << std::to_string(t.get_center().y) << std::endl;
            Coordinate coo = m.get_vector_coordinates_from_click(t.get_center());
            std::cout << "\t[" << std::to_string(coo.x) << "," << std::to_string(coo.y) << "]" << std::endl;
        }
    }
}

bool test_get_tile_from_vec_coord(Map & m) {
    std::cout << "TESTING GET TILE FROM VEC COORDS" << std::endl;
    for (int i = 0 ; i < m.get_tiles()->size();i++) {
        for (int j = 0; j < m.get_tiles()[0].size();j++) {
            //std::cout << "GETTING TILE FROM [" << std::to_string(i) << "," << std::to_string(j) <<"]"<< std::endl;
            Tile* t = m.get_tile_from_vector_coordinates({i,j});
            Coordinate c = m.get_vector_coordinates_from_click(t->get_center());
            if (c.x != i || c.y != j) {
                return false;
            }
            //std::cout << "\t[" << std::to_string(c.x) << "," << std::to_string(c.y) << "]" << std::endl;
        }
    }
    return true;
}

bool test_get_tiles_within_range(Map & m) {
    std::cout << "\nTESTING GET TILES WITHIN RANGE FUNCTION" << std::endl;
    for (int i = 0; i < 8;i++) {
        //std::cout << "\nTiles within range 2 of [" + std::to_string(i) + "," + std::to_string(i) + "]: " << std::endl;
        std::vector<Tile *> * tiles = m.get_tiles_within_range(m.get_tile_from_vector_coordinates({i,i}),2);
        for (int j = 0; j < tiles->size();j++) {
            Coordinate c = m.get_vector_coordinates_from_click((*tiles)[j]->get_center());
            if (abs(c.x-i) > 1) {
                return false;//failed a case (returned a square more than two tiles away from start)
            }
            //std::cout<<"\t["<< std::to_string(c.x) << "," << std::to_string(c.y) <<"]" <<std::endl;
        }
    }
    return true;
}

int main (int argc, char** argv) {
    Map m = Map(1200,800,8,8);
    std::cout << "TESTING MAP CLASS\n"<<std::endl;
    //test_get_vec_coordinates_from_click(m);
    if (test_get_tile_from_vec_coord(m)) {
        std::cout << "SUCCESS" << std::endl;
    }
    else {
        std::cout <<"FAIL" << std::endl;
    }
    if (test_get_tiles_within_range(m)) {
        std::cout<<"SUCCESS"<<std::endl;
    }
    else {
        std::cout << "FAIL" << std::endl;
    }
}