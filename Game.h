//
// Created by david on 4/3/2019.
//

#ifndef CIV_GAME_H
#define CIV_GAME_H

#include <memory>
#include "Civilization.h"
#include "Map.h"
#include "Turn_Manager.h"
#include <random>
#include <fstream>
#include <chrono>


class Game {
private:
    Civilization player;
    Civilization ai;
    Turn_Manager manager;

    Tile * active_tile;
    //std::shared_ptr<City> active_city;
    Unit * active_unit;
    //std::shared_ptr<Building> active_building;

    Map map;

    //justmoves units for now - will attack if can, otherwise moves randomly
    void play_ai();

    void save_map();
    void save_civilizations();
    void save_turn_manager();

    void load_map();
    void load_civilizations();
    void load_turn_manager();
    void load_map(std::string filename);
    void load_civilizations(std::string filename);
    void load_turn_manager(std::string filename);

    /**
     * for use before load, clears all info from current game
     */
    void clear();

public:
    const static int MAP_X_OFF = 25;
    const static int MAP_Y_OFF = 25;
    const static std::string MAP_FILENAME;
    const static std::string CIVS_FILENAME;
    const static std::string TM_FILENAME;

    Game();
    Game(long width, long height, long vecw, long vech);

    Civilization & get_player();
    const Civilization & get_player_const() const;
    Civilization & get_ai();
    const Civilization & get_ai_const() const;

    Tile * get_active_tile();
    const Tile * get_active_tile_const() const;
    //std::shared_ptr<City> & get_active_city();
    Unit* get_active_unit();
    const Unit * get_active_unit_const() const;

    const Turn_Manager &get_turn_manager() const;

    //todo: deal with nullptr case
    void set_active_tile(Tile & tile);
    void set_active_unit(Unit & unit);
    bool has_active_unit() const;
    bool has_active_tile() const;
    void clear_active_tile();
    void clear_active_unit();

    void reveal_unit(Unit * to_rev);
    void reveal_unit(std::unique_ptr<Unit>& to_rev);
    /**
     * sets all tiles within visible range (max movement range) of all units in players civ
     */
    void reveal();

    bool move_active_unit(Tile & to_move_to);

    Map & get_map();
    const Map & get_map_const() const;

    void set_phase(Turn_Phase::names newphase);

    void next_phase();

    void phase_on_button(Square base);

    std::string get_phase();

    void next_turn();//moves to next player turn; plays ai turn

    Coordinate get_unit_location_coordinates(Unit & u);

    void save();
    void load();
    void load(std::string civs_filename, std::string map_filename, std::string tm_filename);

    Game & operator=(const Game & cp);
    bool operator==(const Game & rhs);
    bool operator!=(const Game & rhs);

    ~Game();
};


#endif //CIV_GAME_H
