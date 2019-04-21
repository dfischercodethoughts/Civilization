//
// Created by david on 4/3/2019.
//


#include "Game.h"

const std::string Game::MAP_FILENAME = "map.save";
const std::string Game::CIVS_FILENAME = "civs.save";
const std::string Game::TM_FILENAME = "tm.save";

void Game::play_ai() {
    for (Unit * unit : ai.get_units()) {
        bool moved=  false;
        int unit_id = unit->get_location_id();
        Tile * start_tile = map.get_tile_from_id(unit_id);
        std::vector<Tile *>* possible_moves = map.get_tiles_within_range(start_tile,unit->get_current_movement());
        for (Tile *tile : *possible_moves) {
            if (tile->get_unit() != nullptr & tile->get_unit()->get_owner()!= Civilization_Name::WESTEROS) {
                set_active_unit(*unit);
                move_active_unit(*tile);
                moved = true;
                break;
            }

        }
        if (!moved) {
            unsigned time_stamp = std::chrono::system_clock::now().time_since_epoch().count();
            std::mt19937 generator(time_stamp);
            int ind_to_move = generator() % (possible_moves->size() - 1);
            set_active_unit(*unit);
            move_active_unit(*(*possible_moves)[ind_to_move]);
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

void Game::clear() {
    player.clear();
    ai.clear();
    manager = Turn_Manager();
    active_unit = nullptr;
    active_tile = nullptr;
    map.clear();
}

Game::Game() {
    player = Civilization();
    ai = Civilization();
    manager = Turn_Manager();
    active_unit = nullptr;
    active_tile = nullptr;
    map = Map();
}

Game::Game(long width, long height, long vecw, long vech) {

    map = Map(height,width,vecw,vech,MAP_X_OFF,MAP_Y_OFF);
    player = Civilization("Westeros",false);
    player.add_unit(new Unit(map.get_tile_from_vector_coordinates(Coordinate(0,0))->get_id(),player.get_name(),Unit::WARRIOR),*map.get_tile_from_vector_coordinates(Coordinate(0,0)));
    player.add_unit(new Unit(map.get_tile_from_vector_coordinates(Coordinate(1,0))->get_id(),player.get_name(),Unit::SCOUT),*map.get_tile_from_vector_coordinates(Coordinate(1,0)));
    ai = Civilization("Night King",true);
    ai.add_unit(new Unit(map.get_tile_from_vector_coordinates(Coordinate(vecw-1,vech-1))->get_id(),ai.get_name(),Unit::WARRIOR),*map.get_tile_from_vector_coordinates(Coordinate(vecw-1,vech-1)));
    //player.add_unit(Unit::WARRIOR,*map.get_tile_from_vector_coordinates({0,0}));
    //ai.add_unit(Unit::WARRIOR,*map.get_tile_from_vector_coordinates({vecw-1,vech-1}));
    reveal();
    active_unit = nullptr;
    active_tile = nullptr;
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

const Turn_Manager &Game::get_turn_manager() const {
    return manager;
}

void Game::set_active_tile(Tile &tile) {
    active_tile = &tile;
}

void Game::set_active_unit(Unit &unit) {
    active_unit = &unit;
}

bool Game::has_active_unit() const {
    if (active_unit != nullptr) {
        return true;
    }
    return false;
}

bool Game::has_active_tile() const {
    if (active_tile != nullptr) {
        return true;
    }
    return false;
}

void Game::clear_active_tile() {
    active_tile = nullptr;
}

void Game::clear_active_unit() {
    active_unit = nullptr;
}

void Game::reveal_unit(Unit * to_rev) {
    map.reveal_unit(to_rev);

}

void Game::reveal_unit(std::unique_ptr<Unit>& to_rev) {
    map.reveal_unit(&*to_rev);

}

void Game::reveal() {

    for (Unit * u : player.get_units()) {
        reveal_unit(u);
    }
}

bool Game::move_active_unit(Tile &to_move_to) {//game must have active unit, and tile clicked is next to it
    if (to_move_to.has_unit() ) {
        if (to_move_to.get_unit()->get_owner() != Civilization_Name::WESTEROS) {
            //attack

            ai.get_unit(Civilization_Name::NIGHT_KING,to_move_to.get_id())->cause_damage(active_unit->get_unit_type());
            to_move_to.set_unit(ai.get_unit(Civilization_Name::NIGHT_KING,to_move_to.get_id()));
            Unit * pu = player.get_unit(Civilization_Name::WESTEROS,active_unit->get_location_id());
            pu->cause_damage(to_move_to.get_unit()->get_unit_type());
            //if attack destroys defender, remove it from tile (still need to remove from civilization, done in game::process click)
            if (to_move_to.get_unit()->get_current_health() <= 0) {
                to_move_to.clear_unit();
                ai.destroy_units();
            }
            if (pu->get_current_health() <= 0) {
                map.get_tile_from_id(active_unit->get_location_id())->clear_unit();
                player.destroy_units();
            }
            else {
                active_unit->use_movement(Unit::get_max_movement(active_unit->get_unit_type()));
            }


            //do nothing if player unit on square

        }
        return false;//unit on tile to move to means unit didn't actually move (even if it did attack)
    }
    else if (player.move_unit(&map,active_unit->get_location_id(),to_move_to.get_id())) {
        reveal_unit(to_move_to.get_unit());
        return true;
    }

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

std::string Game::get_phase(){
    return manager.get_current_phase_str();
}

void Game::next_turn() {
    manager.set_current_phase(Turn_Phase::AI_TURN);
    ai.refresh();
    //play_ai();
    player.refresh();
    map.reveal_units(player.get_units());
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