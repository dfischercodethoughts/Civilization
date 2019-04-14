//
// Created by david on 4/3/2019.
//

#include <chrono>
#include "Game.h"

void Game::play_ai() {
    for (Unit * unit : ai.get_units()) {
        bool moved=  false;
        int unit_id = unit->get_location_id();
        Tile * start_tile = map.get_tile_from_id(unit_id);
        std::vector<Tile *> possible_moves = map.get_tiles_within_range(start_tile,unit->get_current_movement());
        for (Tile *tile : possible_moves) {
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
            int ind_to_move = generator() % (possible_moves.size() - 1);
            set_active_unit(*unit);
            move_active_unit(*possible_moves[ind_to_move]);
        }
    }
}

Game::Game() {
    player = Civilization();
    ai = Civilization();
    manager = Turn_Manager();
    active_unit = nullptr;
    active_tile = nullptr;
    map = Map();
}

Game::Game(int width, int height, int vecw, int vech) {
    map = Map(height,width,vecw,vech,MAP_X_OFF,MAP_Y_OFF);
    player = Civilization("Westeros",false);
    Unit player_start(map.get_tile_from_vector_coordinates(Coordinate(0,0))->get_id(),player.get_name(),Unit::WARRIOR);
    player.add_unit(&player_start,*map.get_tile_from_vector_coordinates(Coordinate(0,0)));
    ai = Civilization("Night King",true);
    Unit ai_start(map.get_tile_from_vector_coordinates(Coordinate(vecw-1,vech-1))->get_id(),ai.get_name(),Unit::WARRIOR);
    ai.add_unit(&ai_start,*map.get_tile_from_vector_coordinates(Coordinate(vecw-1,vech-1)));
    //player.add_unit(Unit::WARRIOR,*map.get_tile_from_vector_coordinates({0,0}));
    //ai.add_unit(Unit::WARRIOR,*map.get_tile_from_vector_coordinates({vecw-1,vech-1}));
    map.reveal(player.get_units());

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
std::unique_ptr<Tile> & Game::get_active_tile() {
    return active_tile;
}

const std::unique_ptr<Tile> & Game::get_active_tile_const() const {
    return active_tile;
}

std::unique_ptr<Unit>& Game::get_active_unit() {
    return active_unit;
}

const std::unique_ptr<Unit>& Game::get_active_unit_const() const {
    return active_unit;
}
const Turn_Manager &Game::get_turn_manager() const {
    return manager;
}

void Game::set_active_tile(Tile &tile) {
    active_tile = std::make_unique<Tile>(tile);
}

void Game::set_active_unit(Unit &unit) {
    active_unit = std::make_unique<Unit>(unit);
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

void Game::move_active_unit(Tile &to_move_to) {
    if (to_move_to.get_unit() != nullptr & to_move_to.get_unit()->get_owner() != Civilization_Name::WESTEROS) {
        Unit * unit = to_move_to.get_unit();
        unit->cause_damage(active_unit->get_unit_type());
        //todo: implement unit move before attack
    }
    else {
        to_move_to.set_unit(*active_unit);
        active_unit->set_location(to_move_to.get_id());
    }
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

std::string Game::get_phase(){
    return manager.get_current_phase_str();
}

void Game::next_turn() {
    manager.set_current_phase(Turn_Phase::AI_TURN);
    ai.refresh();

    //TODO::fix this function
    //play_ai();
    player.refresh();
    manager.set_current_phase(Turn_Phase::MOVE);
    //manager.next_turn();
}

Coordinate Game::get_unit_location_coordinates(Unit & u) {
    return map.get_vector_coordinates_from_click(u.get_center());
}

Game& Game::operator=(const Game &cp) {
    player = cp.get_player_const();
    ai = cp.get_ai_const();
    manager = cp.get_turn_manager();
    map = cp.get_map_const();
    if (cp.has_active_unit()) {
        active_unit = std::make_unique<Unit>(&*cp.get_active_unit_const().get());
    }
    else {
        active_unit = nullptr;
    }
    if (cp.has_active_tile()) {
        active_tile = std::make_unique<Tile>(&*cp.get_active_tile_const());
    } else {
        active_tile = nullptr;
    }
}

Game::~Game() {
    player = Civilization();
    ai = Civilization();
    manager = Turn_Manager();
    active_tile = nullptr;
    active_unit = nullptr;
}