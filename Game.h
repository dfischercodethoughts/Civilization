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
#include "Build_Menu.h"
#include <chrono>

/**
 * Game class holds all information about the internal state of the game
 */
class Game {
private:
    Civilization player;
    Civilization ai;
    Turn_Manager manager;
    Build_Menu buildmenu;

    /**
     * game has pointers to "active" tile, unit, city
     * also has pointer to a building or unit to build
     */
    Tile * active_tile;
    City * active_city;
    Unit * active_unit;
    Building * building_to_build;
    Unit * unit_to_build;
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

    //updates map with latest unit info
    void update_map();

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
    City * get_active_city();
    const City * get_active_city_const() const;
    Piece * get_build_piece();

    const Turn_Manager &get_turn_manager() const;

    //todo: deal with nullptr case
    void set_active_tile(Tile & tile);
    void set_active_unit(Unit & unit);
    void set_active_city(City & c);
    void set_build_building(Building & p);
    void set_build_unit(Unit & u);
    bool has_active_unit() const;
    bool has_active_tile() const;
    bool has_active_city() const;
    bool has_build_piece() const;
    bool has_build_building() const;
    bool has_build_unit() const;
    void clear_active_tile();
    void clear_active_unit();
    void clear_active_city();
    void clear_build_building();
    void clear_build_unit();

    void reveal_unit(Unit * to_rev);
    void reveal_city(City * rev);

    /**
     * reveals all tiles within visible range (max movement range) of all units in players civ
     */
    void reveal();

    bool move_active_unit(Tile & to_move_to);

    void build_city(Civilization_Name::Names civ, Tile & build_on);

    int get_num_cities(Civilization_Name::Names civ);

    Map & get_map();
    const Map & get_map_const() const;

    void set_phase(Turn_Phase::names newphase);

    void next_phase();

    void phase_on_button(Square base);

    void print_build_menu_title(Square base, Square base2);

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
