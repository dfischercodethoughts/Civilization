//
// Created by david on 4/13/2019.
//

#include "Map.h"
#include "iostream"
#include "Civilization.h"
#include "Turn_Manager.h"

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

bool test_turn_manager_intput_output() {
    std::string filename = "turn_manager.save";

    std::cout << "TESTING TURN MANAGER INPUT OUTPUT..." << std::endl << std::endl;

    std::cout << "CREATING TURN MANAGER..." << std::endl;

    Turn_Manager tm;
    std::cout << tm;

    std::cout << "DONE. INCREMENTING COUNT TWICE..." << std::endl;
    tm.next_turn();tm.next_turn();
    std::cout << "DONE. INCREMENTING PHASE TWICE..." << std::endl;
    tm.next_phase();tm.next_phase();

    std::cout<<"DONE. SAVING TO FILE (look for " << filename << ")..." << std::endl;

    std::ofstream outs;
    outs.open(filename);
    outs << tm;
    outs.close();

    std::cout << "DONE. LOADING FROM FILE..." << std::endl;
    Turn_Manager new_tm;
    std::ifstream ins;
    ins.open(filename);
    ins >> new_tm;
    ins.close();
    std::cout << "DONE:" <<std::endl<< new_tm;

    if (new_tm == tm) {
        std::cout<<"SUCCESS." << std::endl;
        return true;
    }
    std::cout << "DONE." << std::endl;
    std::cout << "FAIL." << std::endl;

    return false;
}

bool test_unit_input_output() {
    std::string filename = "unit_test.save";

    std::cout << "TESTING UNIT INPUT OUTPUT..." << std::endl << std::endl;

    std::cout << "CREATING UNIT..." << std::endl;

    Unit u1;
    Unit u2(1,Unit::WARRIOR);
    Unit u3(64,Civilization_Name::WESTEROS,Unit::SCOUT);
    Unit u4(-5,{250,250},Civilization_Name::NIGHT_KING,Unit::HORSEMAN);
    std::vector<Unit> old_units;
    old_units.emplace_back(u1);
    old_units.emplace_back(u2);
    old_units.emplace_back(u3);
    old_units.emplace_back(u4);
    for (int i = 0; i < old_units.size();i++) {
        std::cout << old_units[i];
    }

    std::cout << std::endl << "DONE. SAVING TO FILE (look for " << filename << ")..."<< std::endl;

    std::ofstream outs;
    outs.open(filename);
    for (int i = 0; i < old_units.size();i++) {
        outs << old_units[i];
    }
    outs.close();
    std::cout << "DONE. LOADING FROM FILE..." << std::endl;
    Unit nu1, nu2, nu3, nu4;
    std::vector<Unit> units;
    std::ifstream ins;
    ins.open(filename);
    std::string line = "";
    std::getline(ins,line);
    while (line == "UNIT") {
        Unit * tmp = new Unit();
        ins >> *tmp;
        units.emplace_back(*tmp);
        std::getline(ins,line);
    }

    ins.close();
    std::cout << "DONE:"<<std::endl;
    for (int i = 0; i < units.size(); i++) {
        std::cout << units[i];
    }
    bool flag = false;
    for (int i = 0; i < units.size(); i++) {
        if (units[i] != old_units[i]) {
            flag = true;
        }
    }

    if (!flag) {
        std::cout << "SUCCEED." << std::endl;
        return true;
    }

    std::cout <<"FAIL." << std::endl;
    return false;
}

bool test_civilization_input_output() {
    std::string filename = "civilization.save";

    std::cout << "TESTING CIVILIZATION INPUT OUTPUT..." << std::endl << std::endl;

    std::cout << "CREATING CIVILIZATION AND UNITS..." << std::endl;

    Civilization civ1("WESTEROS",false);
    Unit u1;
    Unit u2(1,Unit::WARRIOR);
    Unit u3(64,Civilization_Name::WESTEROS,Unit::SCOUT);
    Unit u4(-5,{250,250},Civilization_Name::NIGHT_KING,Unit::HORSEMAN);
    civ1.add_unit(&u1);
    civ1.add_unit(&u2);
    civ1.add_unit(&u3);
    civ1.add_unit(&u4);
    std::cout <<civ1;

    std::cout << std::endl << "DONE. SAVING TO FILE (look for " << filename << ")..."<< std::endl;

    std::ofstream outs;
    outs.open(filename);
    outs << civ1;
    outs.close();
    std::cout << "DONE. LOADING FROM FILE..." << std::endl;
    Civilization civ2;

    std::ifstream ins;
    ins.open(filename);
    std::string line;
    getline(ins,line);//read "CIVILIZATION\n"
    ins >> civ2;
    ins.close();

    std::cout << "DONE:"<<std::endl;
    std::cout << civ2;
    if (civ2 == civ1) {
        std::cout << std::endl << "SUCCEED." << std::endl;
        return true;
    }
    std::cout << std::endl << "FAIL." << std::endl;
    return false;
}

bool test_tile_input_output() {
    //todo: add building to tile input/output tests
    std::string filename = "tile_test.save";

    std::cout << "TESTING TILE INPUT OUTPUT..." << std::endl << std::endl;

    std::cout << "CREATING TILES..." << std::endl;

    Tile t1;
    Tile t2("GRASSLAND","IRON");
    Tile t3("HILL","WOODS");
    Tile t4("MOUNTAIN","GAZELLE");
    std::vector<Tile> ot;
    ot.emplace_back(t1);ot.emplace_back(t2);ot.emplace_back(t3);ot.emplace_back(t4);
    for (int i = 0; i < ot.size();i++) {
        std::cout << ot[i];
    }

    std::cout << std::endl << "DONE. SAVING TO FILE (look for " << filename << ")..."<< std::endl;

    std::ofstream outs;
    outs.open(filename);
    for (int i = 0; i < ot.size();i++) {
        outs << ot[i];
    }
    outs.close();
    std::cout << "DONE. LOADING FROM FILE..." << std::endl;
    Tile nt1, nt2, nt3, nt4;
    std::vector<Tile> new_tiles;
    std::ifstream ins;
    ins.open(filename);
    std::string line = "";
    std::getline(ins,line);
    while (line == "TILE") {
        Tile * tmp = new Tile();
        ins >> *tmp;
        new_tiles.emplace_back(*tmp);
        std::getline(ins,line);
    }

    ins.close();
    std::cout << "DONE:"<<std::endl;
    for (int i = 0; i < new_tiles.size(); i++) {
        std::cout << new_tiles[i];
    }
    bool flag = false;
    for (int i = 0; i < new_tiles.size(); i++) {
        if (ot[i] != new_tiles[i]) {
            flag = true;
        }
    }

    if (!flag) {
        std::cout << "SUCCEED." << std::endl;
        return true;
    }

    std::cout <<"FAIL." << std::endl;
    return false;
}

bool test_map_input_output() {
    std::string filename = "map.save";

    std::cout << "TESTING MAP INPUT OUTPUT..." << std::endl << std::endl;

    std::cout << "CREATING MAP AND TILES..." << std::endl;

    Civilization civ1("WESTEROS",false);
    Unit u1;
    Unit u2(1,Unit::WARRIOR);
    Unit u3(64,Civilization_Name::WESTEROS,Unit::SCOUT);
    Unit u4(-5,{250,250},Civilization_Name::NIGHT_KING,Unit::HORSEMAN);
    civ1.add_unit(&u1);
    civ1.add_unit(&u2);
    civ1.add_unit(&u3);
    civ1.add_unit(&u4);
    std::cout <<civ1;

    std::cout << std::endl << "DONE. SAVING TO FILE (look for " << filename << ")..."<< std::endl;

    std::ofstream outs;
    outs.open(filename);
    outs << civ1;
    outs.close();
    std::cout << "DONE. LOADING FROM FILE..." << std::endl;
    Civilization civ2;

    std::ifstream ins;
    ins.open(filename);
    std::string line;
    getline(ins,line);//read "CIVILIZATION\n"
    ins >> civ2;
    ins.close();

    std::cout << "DONE:"<<std::endl;
    std::cout << civ2;
    if (civ2 == civ1) {
        std::cout << std::endl << "SUCCEED." << std::endl;
        return true;
    }
    std::cout << std::endl << "FAIL." << std::endl;
    return false;
}

int main (int argc, char** argv) {
    //test_turn_manager_intput_output();
    //test_unit_input_output();
    //test_civilization_input_output();
    test_tile_input_output();
   // test_map_input_output();

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
    //test_coordinate_input_output();


}