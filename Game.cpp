//
// Created by david on 4/3/2019.
//


#include "Game.h"

const std::string Game::MAP_FILENAME = "map.save";
const std::string Game::CIVS_FILENAME = "civs.save";
const std::string Game::TM_FILENAME = "tm.save";

void Game::play_ai() {
    manager.set_current_phase(Turn_Phase::AI_TURN);
    for (Unit * unit : ai.get_units()) {
        set_active_unit(*unit);
        bool moved=  false;
        int unit_id = unit->get_location_id();
        Tile * start_tile = map.get_tile_from_id(unit_id);
        while (active_unit != nullptr && active_unit->get_current_movement() > 0) {
            std::vector<Tile *> *possible_moves = map.get_tiles_within_range(start_tile, unit->get_current_movement());
            for (Tile *tile : *possible_moves) {
                //if there's a tile with an enemy unit on it: attack
                if (tile->get_unit() != nullptr && tile->get_unit()->get_owner() == Civilization_Name::WESTEROS) {
                    if (map.is_adjacent(*tile,*start_tile)) {

                        move_active_unit(*tile);
                    }
                    else {
                        //enemy in range, but not on a tile adjacent to the warrior
                        //set active unit and move to tile closest to enemy

                        move_active_unit(*map.get_closest_tile(start_tile,tile));
                        //if there's movement left (which there should be), attack the enemy
                        if (active_unit -> get_current_movement() > 0) {
                            move_active_unit(*tile);
                        }
                    }
                    moved = true;
                    break;
                }

            }
            if (!moved) {
                //if it hasn't attacked, then move randomly
                unsigned time_stamp = std::chrono::system_clock::now().time_since_epoch().count();
                std::mt19937 generator(time_stamp);
                int ind_to_move = generator() % (possible_moves->size());
                move_active_unit(*possible_moves->at(ind_to_move));
            }
           // set_active_unit()
        }
    }
}

void Game::save_map() {
    try {
        std::ofstream outs;
        outs.open(MAP_FILENAME);
        outs << map;
        outs.close();
    }
    catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }
}

void Game::save_civilizations() {
    try {
        std::ofstream outs;
        outs.open(CIVS_FILENAME);
        outs << player << ai;
        outs.close();
    }
    catch (std::exception & e ) {
        std::cout << e.what() << std::endl;
    }
}

void Game::save_turn_manager() {
    try {
        std::ofstream outs;
        outs.open(TM_FILENAME);
        outs << manager;
        outs.close();
    }
    catch (std::exception & e){
        std::cout << e.what() << std::endl;
    }
}

void Game::load_map() {
    try {
        std::ifstream ins;
        ins.open(MAP_FILENAME);
        ins >> map;
        ins.close();
    }
    catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }

}

void Game::load_civilizations() {
    try {
        std::ifstream ins;

        ins.open(CIVS_FILENAME);
        ins >> player;
        ins >> ai;
        ins.close();
    }
    catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }

}

void Game::load_turn_manager() {
    try {
        std::ifstream ins;
        ins.open(TM_FILENAME);
        ins >> manager;
        ins.close();
    }
    catch (std::exception & e){
        std::cout << e.what() << std::endl;
    }
}

void Game::load_map(std::string filename) {
    try {
        std::ifstream ins;
        ins.open(filename);
        ins >> map;
        ins.close();
    }
    catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }

}

void Game::load_civilizations(std::string filename) {
    try {
        std::ifstream ins;

        ins.open(filename);
        ins >> player;
        ins >> ai;
        ins.close();
    }
    catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }

}

void Game::load_turn_manager(std::string filename) {
    try {
        std::ifstream ins;
        ins.open(filename);
        ins >> manager;
        ins.close();
    }
    catch (std::exception & e){
        std::cout << e.what() << std::endl;
    }
}

void Game::update_map() {
    //todo: add loop to iterate through civilizations
    for (int i = 0;i<player.get_units().size();i++) {
        Tile * tile = map.get_tile_from_id(player.get_units()[i]->get_location_id());
        tile->set_unit(player.get_units()[i]);
    }
    for (int i = 0;i<ai.get_units().size();i++) {
        Tile * tile = map.get_tile_from_id(ai.get_units()[i]->get_location_id());
        tile->set_unit(ai.get_units()[i]);
    }
}

void Game::clear() {
    player.clear();
    ai.clear();
    manager = Turn_Manager();
    buildmenu = Build_Menu();
    active_unit = nullptr;
    active_tile = nullptr;
    active_city = nullptr;
    map.clear();
}

Game::Game() {
    player = Civilization();
    ai = Civilization();
    manager = Turn_Manager();
    buildmenu = Build_Menu();
    active_unit = nullptr;
    active_tile = nullptr;
    active_city = nullptr;
    map = Map();
}

Game::Game(long width, long height, long vecw, long vech) {

    map = Map(height,width,vecw,vech,MAP_X_OFF,MAP_Y_OFF);
    buildmenu = Build_Menu(height, width);
    player = Civilization("Westeros",false);
    Unit * to_add = new Unit(map.get_tile_from_vector_coordinates(Coordinate(0,1))->get_id(),player.get_name(),Unit::WARRIOR);
    player.add_unit(&*to_add);
    map.get_tile_from_vector_coordinates(Coordinate(0,1))->set_unit(&*to_add);

    to_add = new Unit(map.get_tile_from_vector_coordinates(Coordinate(1,0))->get_id(),player.get_name(),Unit::SCOUT);
    player.add_unit(&*to_add);
    map.get_tile_from_vector_coordinates(Coordinate(1,0))->set_unit(&*to_add);

    to_add = new Unit(new Unit(map.get_tile_from_vector_coordinates(Coordinate(0,0))->get_id(),player.get_name(),Unit::SETTLER));

    player.add_unit(to_add);
    map.get_tile_from_vector_coordinates(Coordinate(0,0))->set_unit(&*to_add);

    ai = Civilization("Night King",true);

    to_add = new Unit(map.get_tile_from_vector_coordinates(Coordinate(vecw-1,vech-1))->get_id(),ai.get_name(),Unit::WARRIOR);
    ai.add_unit(&*to_add);
    map.get_tile_from_id(to_add->get_location_id())->set_unit(ai.get_unit(Civilization_Name::NIGHT_KING,to_add->get_location_id()));
    //player.add_unit(Unit::WARRIOR,*map.get_tile_from_vector_coordinates({0,0}));
    //ai.add_unit(Unit::WARRIOR,*map.get_tile_from_vector_coordinates({vecw-1,vech-1}));
    reveal();
    active_unit = nullptr;
    active_tile = nullptr;
    active_city = nullptr;
    manager = Turn_Manager();
}

Civilization & Game::get_player() {
    return player;
}

const Civilization & Game::get_player_const() const {
    return player;
}

Civilization & Game::get_ai() {
    return ai;
}

const Civilization & Game::get_ai_const() const {
    return ai;
}

Tile * Game::get_active_tile() {
    return active_tile;
}

const Tile * Game::get_active_tile_const() const {
    return active_tile;
}

Unit * Game::get_active_unit() {
    return active_unit;
}

const Unit * Game::get_active_unit_const() const {
    return active_unit;
}

City * Game::get_active_city() {
    return active_city;
}

const City * Game::get_active_city_const() const {
    return active_city;
}

const Turn_Manager &Game::get_turn_manager() const {
    return manager;
}

void Game::set_active_tile(Tile &tile) {
    active_tile = &tile;
}

void Game::set_active_unit(Unit &unit) {
    active_unit = &unit;
}

void Game::set_active_city(City &c) {
    active_city = &c;
}

void Game::set_build_building(Building &p) {
    building_to_build = &p;
}

void Game::set_build_unit(Unit &u) {
    unit_to_build = &u;
}

bool Game::has_active_unit() const {
    return active_unit != nullptr;
}

bool Game::has_active_tile() const {
    return active_tile != nullptr;
}

bool Game::has_active_city() const {
    return active_city != nullptr;
}

bool Game::has_build_piece() const {
    return (has_build_unit() || has_build_building());

}

bool Game::has_build_unit() const {
    return (unit_to_build != nullptr);
}

bool Game::has_build_building() const {
    return (building_to_build != nullptr);
}

Building Game::get_build_building(){
    return *building_to_build;
}

Unit *Game::get_build_unit(){
    return unit_to_build;
}

void Game::clear_active_tile() {
    active_tile = nullptr;
}

void Game::clear_active_unit() {
    active_unit = nullptr;
}

void Game::clear_active_city() {
    active_city = nullptr;
}

void Game::clear_build_building(){
    building_to_build = nullptr;
}

void Game::clear_build_unit() {
    unit_to_build = nullptr;
}

void Game::add_unit(Civilization_Name::Names n, Unit * to_add, Tile * place) {
    //in future builds we will iterate through all civilizations in game
    if (n == Civilization_Name::WESTEROS) {
        player.add_unit(*to_add,*place);
    }
    else if (n == Civilization_Name::NIGHT_KING) {
        ai.add_unit(*to_add,*place);
    }
}

void Game::reveal_unit(Unit * to_rev) {
    map.reveal_unit(to_rev);

}

void Game::reveal_city(City * to_rev) {
    std::vector<Tile *> tmp = to_rev->get_tiles();
    map.make_visible(tmp);
}

void Game::reveal() {
    for (City * c : player.get_cities()) {
        reveal_city(c);
    }
    for (Unit * u : player.get_units()) {
        reveal_unit(u);
    }
}

void Game::build_city(Civilization_Name::Names civ, Tile & build_on) {
    Unit * u = build_on.get_unit();

    if (civ == Civilization_Name::WESTEROS) {//todo: loop through civs vector when choosing how to build city...
        player.add_city(map,build_on);
        player.remove_unit(*u);

    }
    else {
        ai.add_city(map,build_on);
        ai.remove_unit(*u);

    }
    //remove settler from tile
    build_on.clear_unit();

}

int Game::get_num_cities(Civilization_Name::Names nm) {
    //todo:loop through civs vector and return the appropriate number of cities
    if (nm == Civilization_Name::WESTEROS) {
        return get_player().get_cities().size();
    }
    else {
        return get_ai().get_cities().size();
    }
}

bool Game::move_active_unit(Tile &to_move_to) {//game must have active unit, and tile clicked is next to it
    if (manager.get_current_phase()!=Turn_Phase::AI_TURN) {//perform differently if ai unit is being moved
        if (to_move_to.has_unit()) {
            if (to_move_to.get_unit()->get_owner() != Civilization_Name::WESTEROS) {
                //attack

                ai.get_unit(Civilization_Name::NIGHT_KING, to_move_to.get_id())->cause_damage(
                        active_unit->get_unit_type());
                to_move_to.set_unit(ai.get_unit(Civilization_Name::NIGHT_KING, to_move_to.get_id()));
                Unit *pu = player.get_unit(Civilization_Name::WESTEROS, active_unit->get_location_id());
                pu->cause_damage(to_move_to.get_unit()->get_unit_type());
                //if attack destroys defender, remove it from tile (still need to remove from civilization, done in game::process click)
                if (to_move_to.get_unit()->get_current_health() <= 0) {
                    to_move_to.clear_unit();
                    ai.destroy_units();
                }
                if (pu->get_current_health() <= 0) {
                    map.get_tile_from_id(active_unit->get_location_id())->clear_unit();
                    player.destroy_units();
                } else {
                    active_unit->use_movement(Unit::get_max_movement(active_unit->get_unit_type()));
                }


                //do nothing if player unit on square

            }
            return false;//unit on tile to move to means unit didn't actually move (even if it did attack)
        } else if (player.move_unit(&map, active_unit->get_location_id(), to_move_to.get_id())) {
            reveal_unit(to_move_to.get_unit());
            return true;
        }
    }
    else {//AI MOVE
        if (to_move_to.has_unit()) {
            if (to_move_to.get_unit()->get_owner() == Civilization_Name::WESTEROS) {
                //attack

                player.get_unit(Civilization_Name::WESTEROS, to_move_to.get_id())->cause_damage(
                        active_unit->get_unit_type());
                to_move_to.set_unit(player.get_unit(Civilization_Name::WESTEROS, to_move_to.get_id()));
                Unit *aiu = ai.get_unit(Civilization_Name::NIGHT_KING, active_unit->get_location_id());
                aiu->cause_damage(to_move_to.get_unit()->get_unit_type());
                map.get_tile_from_id(active_unit->get_location_id())->set_unit(&*aiu);
                set_active_unit(*aiu);
                //if attack destroys defender, remove it from tile (still need to remove from civilization, done in game::play_ai)
                if (to_move_to.get_unit()->get_current_health() <= 0) {
                    to_move_to.clear_unit();
                    player.destroy_units();
                }
                if (aiu->get_current_health() <= 0) {
                    map.get_tile_from_id(active_unit->get_location_id())->clear_unit();
                    ai.destroy_units();
                    active_unit = nullptr;
                } else {
                    aiu->use_movement(Unit::get_max_movement(active_unit->get_unit_type()));
                    set_active_unit(*ai.get_unit(ai.get_name(),active_unit->get_location_id()));
                }


                //do nothing if player unit on square

            }
            return false;//unit on tile to move to means unit didn't actually move (even if it did attack)
        } else /*if (map.is_adjacent(*map.get_tile_from_id(active_unit->get_location_id()),to_move_to))*/ {
            //tile to move to does not have a unit on it
                if(ai.move_unit(&map, active_unit->get_location_id(), to_move_to.get_id())) {
                    //reveal_unit(to_move_to.get_unit());
                    set_active_unit(*ai.get_unit(ai.get_name(),to_move_to.get_id()));
                    return true;
                }

        }
    }//end ai move

    return false;
}

Map & Game::get_map() {
    return map;
}

const Map & Game::get_map_const() const {
    return map;
}

void Game::set_phase(Turn_Phase::names newphase) {
    manager.set_current_phase(newphase);
}

void Game::next_phase() {
    manager.next_phase();
}

void Game::phase_on_button(Square base){
    base.set_fill(Colors::WHITE);
    base.draw();
    glColor3f(Colors::BLACK.get_red(),Colors::BLACK.get_green(),Colors::BLACK.get_blue());
    glRasterPos2i(base.get_center().x-3*base.get_width()/8,base.get_center().y - 3*base.get_height()/8);
    std::string line = "CURRENT PHASE: " + manager.get_current_phase_str();
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,c);
    }

}


//function to print the words BUILDING MENU AND UNIT MENU
//right above their respective menus in build phase
void Game::print_build_menu_title(Square base, Square base2){
    glColor3f(Colors::WHITE.get_red(),Colors::WHITE.get_green(),Colors::WHITE.get_blue());
    glRasterPos2i(base.get_center().x-40*base.get_width()/72,base.get_center().y - 42*base.get_height()/72);
    std::string line = "BUILDING MENU";
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c);
    }

    glColor3f(Colors::WHITE.get_red(),Colors::WHITE.get_green(),Colors::WHITE.get_blue());
    glRasterPos2i(base2.get_center().x-27*base2.get_width()/72,base2.get_center().y - 42*base2.get_height()/72);
    std::string line2 = "UNIT MENU";
    for (char c : line2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c);
    }

}

std::string Game::get_phase(){
    return manager.get_current_phase_str();
}

void Game::next_turn() {
    manager.set_current_phase(Turn_Phase::AI_TURN);
    ai.next_turn(map);
    play_ai();
    player.next_turn(map);
    update_map();
    clear_active_tile();
    clear_active_unit();
    clear_active_city();
    map.reveal_units(player.get_units());
    map.reveal_cities(player.get_cities());
    manager.next_turn();
    manager.set_current_phase(Turn_Phase::MOVE);
}

Coordinate Game::get_unit_location_coordinates(Unit & u) {
    return map.get_vector_coordinates_from_click(u.get_center());
}

void Game::save() {
    save_civilizations();
    save_map();
    save_turn_manager();
}

void Game::load() {
    clear();
    load_civilizations();
    load_map();
    load_turn_manager();
    //link units to map
    for (int i = 0; i < player.get_units().size();i++) {
        Tile * to_set = map.get_tile_from_id(player.get_units()[i]->get_location_id());
        to_set->set_unit(player.get_units()[i]);
    }
    for (int i = 0; i < ai.get_units().size();i++) {
        Tile * to_set = map.get_tile_from_id(ai.get_units()[i]->get_location_id());
        to_set->set_unit(ai.get_units()[i]);
    }
    //todo: add multi ai functionality by looping through civilizations vector
    for (int i = 0; i < player.get_cities().size();i++) {
        City * c = &*player.get_cities()[i];
        //set home tile
        Tile * home_tile = map.get_tile_from_id(c->get_home_tile()->get_id());
        c->set_home_tile(*home_tile);

        //add tiles gotten from map
        std::vector<Tile *> city_tiles = *map.get_tiles_within_range(c->get_home_tile(),c->get_population()-1);
        for (Tile * t : city_tiles ) {
            t->set_owner(player.get_name());
        }
        c->add_tiles(city_tiles);
        home_tile -> set_city(*c);
    }
    for (int i = 0; i < ai.get_cities().size();i++) {
        City * c = ai.get_cities()[i];
        //set home tile
        Tile * home_tile = map.get_tile_from_id(c->get_home_tile()->get_id());
        c->set_home_tile(*home_tile);
        //add tiles gotten from map
        std::vector<Tile *> city_tiles = *map.get_tiles_within_range(c->get_home_tile(),c->get_population()-1);
        for (Tile * t : city_tiles ) {
            t->set_owner(ai.get_name());
        }
        c->add_tiles(city_tiles);
    }
}

void Game::load(std::string civs_filename, std::string map_filename,std::string tm_filename) {
    clear();
    load_civilizations(civs_filename);
    load_map(map_filename);
    load_turn_manager(tm_filename);
    //link units to map
    for (int i = 0; i < player.get_units().size();i++) {
        Tile * to_set = map.get_tile_from_id(player.get_units()[i]->get_location_id());
        to_set->set_unit(player.get_units()[i]);
    }
    for (int i = 0; i < ai.get_units().size();i++) {
        Tile * to_set = map.get_tile_from_id(ai.get_units()[i]->get_location_id());
        to_set->set_unit(ai.get_units()[i]);
    }

    //add tiles for player and ai cities
    //todo: add multi ai functionality by looping through civilizations vector
    for (int i = 0; i < player.get_cities().size();i++) {
        City * c = player.get_cities()[i];
        //set home tile
        Tile * home_tile = map.get_tile_from_id(c->get_home_tile()->get_id());
        c->set_home_tile(*home_tile);
        //add tiles gotten from map
        std::vector<Tile *> city_tiles = *map.get_tiles_within_range(c->get_home_tile(),c->get_population()-1);
        for (Tile * t : city_tiles ) {
            t->set_owner(player.get_name());
        }
        c->add_tiles(city_tiles);
    }
    for (int i = 0; i < ai.get_cities().size();i++) {
        City * c = ai.get_cities()[i];
        //set home tile
        Tile * home_tile = map.get_tile_from_id(c->get_home_tile()->get_id());
        c->set_home_tile(*home_tile);
        //add tiles gotten from map
        std::vector<Tile *> city_tiles = *map.get_tiles_within_range(c->get_home_tile(),c->get_population()-1);
        for (Tile * t : city_tiles ) {
            t->set_owner(ai.get_name());
        }
        c->add_tiles(city_tiles);
    }
}

Game& Game::operator=(const Game &cp) {
    player = cp.get_player_const();
    ai = cp.get_ai_const();
    manager = cp.get_turn_manager();
    map = cp.get_map_const();
    if (cp.has_active_unit()) {
        active_unit = &*new Unit(cp.get_active_unit_const());
    }
    else {
        active_unit = nullptr;
    }
    if (cp.has_active_tile()) {
        active_tile = &*new Tile(cp.get_active_tile_const());
    } else {
        active_tile = nullptr;
    }
}

bool Game::operator==(const Game & rhs) {
    return (player == rhs.get_player_const() && ai == rhs.get_ai_const() && manager == rhs.get_turn_manager() &&
        map == rhs.get_map_const());
}

bool Game::operator!=(const Game & rhs) {
    return (!(*this==rhs));
}

Game::~Game() {
    active_tile = nullptr;
    active_unit = nullptr;
}