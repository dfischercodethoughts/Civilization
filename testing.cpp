//
// Created by david on 4/13/2019.
//

#include "Map.h"
#include "iostream"
#include "Civilization.h"

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

bool test_civ_add_unit(Map & m) {
    Civilization ai;
    ai = Civilization("Night King",true);
    ai.add_unit(new Unit(m.get_tile_from_vector_coordinates(Coordinate(7,7))->get_id(),ai.get_name(),Unit::WARRIOR),*m.get_tile_from_vector_coordinates(Coordinate(7,7)));
    std::vector<Unit *> units = ai.get_units();
    for (Unit * u : units) {
        //std::cout<<u->get_unit_type() << u->get_owner() << "[" << u->get_center().x <<","  << u->get_center().y << "]" << std::endl;
        if (u->get_owner() != Civilization_Name::NIGHT_KING) {
            return false;
        }
        if (u->get_location_id() != 64) {
            return false;
        }
    }
    return true;
}

bool test_color_input_output() {
    std::string filename = "colorio.save";
    std::cout << "TESTING COLOR INPUT/OUTPUT"<< std::endl;

    std::cout << "MAKING RED COLOR" << std::endl;
    Color red_old = Colors::RED;
    std::cout << red_old << std::endl;

    std::cout << "MAKING GREEN COLOR" << std::endl;
    Color green_old = Colors::GREEN;
    std::cout << green_old << std::endl;

    std::cout << "MAKING BLUE COLOR" << std::endl;
    Color blue_old = Colors::BLUE;
    std::cout << blue_old << std::endl;

    std::cout << "MAKING BLACK COLOR" << std::endl;
    Color black_old = Colors::BLACK;
    std::cout << black_old << std::endl;

    std::cout << "TESTING COLOR FILE INPUT/OUTPUT; LOOK FOR "<<filename<< std::endl;

    std::ofstream outs;
    outs.open(filename);

    outs << red_old << green_old << blue_old << black_old << std::endl;

    outs.close();

    std::cout << "DONE SAVING. NOW LOADING..." << std::endl;
    Color red, green, blue, black;
    std::ifstream ins;
    ins.open(filename);
    ins >> red >> green >> blue >> black;
    ins.close();
    std::cout << "DONE LOADING. NOW PRINTING..." << std::endl;
    std::cout << red << green << blue << black << std::endl;

    std::cout << "DONE." << std::endl;

    if (red != red_old || green != green_old || blue != blue_old) {
        return false;
    }
    return true;
}

bool test_coordinate_input_output() {
    std::string filename = "coordinateio.save";

    std::cout << "TESTING COORDINATE INPUT/OUTPUT OPERATION..." << std::endl;
    std::cout << "CREATING COORDINATES..." << std::endl;
    Coordinate c1(0,0);
    Coordinate c2(15,15);
    Coordinate c3(-15,15);
    Coordinate c4(1000000,100000000);
    Coordinate c5(-99999,-10000000);

    std::cout << "DONE." << std::endl;

    std::cout << c1 << c2 << c3 << c4 << c5 << std::endl;

    std::cout << "SAVING COORDINATES (look for " << filename << ")..." << std::endl;
    std::ofstream outs;
    outs.open(filename);
    outs << c1 <<c2 << c3 << c4 << c5 <<std::endl;
    outs.close();
    std::cout << "DONE. LOADING COORDINATES..." << std::endl;

    Coordinate n1,n2,n3,n4,n5;
    std::ifstream ins;
    ins.open(filename);
    ins >> n1 >> n2 >> n3 >> n4 >> n5;
    ins.close();
    std::cout << "DONE." << std::endl;

    std::cout << n1 << n2 << n3 << n4 << n5;

    if (n1 == c1 && n2 == c2 && n3 == c3 && n4 == c4 && n5 == c5) {
        std::cout <<std::endl<< "SUCCESS." << std::endl;
        return true;
    }
    std::cout <<std::endl<< "FAIL." << std::endl;
    return false;

}

int main (int argc, char** argv) {
    /*
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

   //std::cout << "TESTING CIVILIZATION ADD UNIT" << std::endl;
     test_color_input_output();
    */
    test_coordinate_input_output();


}