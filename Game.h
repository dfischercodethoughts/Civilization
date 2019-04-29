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
 * can be saved and loaded from specific filenames (constants specified below
 */
 //todo: extend game to have more than one ai
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

    /**
     * internal ai play functions
     */
     void ai_build_building(City * c,Building_Name::names nm,std::mt19937 rand_gen);
     void ai_build_unit(City * c, Unit::Unit_Type un,std::mt19937 rand_gen);

    //just moves units for now - will attack if can, otherwise moves randomly
    void play_ai();

    /**
     * saves given property using input output operators using constant filename given above
     */
    void save_map();
    void save_civilizations();
    void save_turn_manager();

    /**
     * loads properties using io operators with either constant or given filenames
     */
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
    const static int SETTLE_AREA = 4;

    /**
     * constructors
     */
    Game();
    Game(long width, long height, long vecw, long vech);

    /**
     * civilization getters
     */
    Civilization & get_player();
    const Civilization & get_player_const() const;
    Civilization & get_ai();
    const Civilization & get_ai_const() const;

    /**
     * allows main screen to interact directly with tiles units and cities if necessary
     * @return
     */
    Tile * get_active_tile();
    const Tile * get_active_tile_const() const;
    //std::shared_ptr<City> & get_active_city();
    Unit* get_active_unit();
    const Unit * get_active_unit_const() const;
    City * get_active_city();
    const City * get_active_city_const() const;
    Piece * get_build_piece();

    const Turn_Manager &get_turn_manager() const;

    /**
     * active pointer getters and setters
     * @param tile
     */
    void set_active_tile(Tile & tile);
    void set_active_unit(Unit & unit);
    void set_active_city(City & c);
    void set_build_building(Building & p);
    void set_build_unit(Unit & u);

    bool has_active_unit() const;
    bool has_active_tile() const;
    bool has_active_city() const;
    bool has_build_piece() const;

    /**
     * returns true if the build menu has a building or unit ready to build
     * @return
     */
    bool has_build_building() const;
    bool has_build_unit() const;

    Building get_build_building();
    Unit * get_build_unit();

    /**
     * active pointer clearers sets the pointer to nullptr
     */
    void clear_active_tile();
    void clear_active_unit();
    void clear_active_city();
    void clear_build_building();
    void clear_build_unit();

    /**
     * adds a new copy of the given unit to the civilization and tile
     * @param n ame of the civilization to add the unit to
     * @param to_add the base unit to add (must have unit type)
     * @param place to place to unit
     */
    void add_unit(Civilization_Name::Names n, Unit * to_add, Tile * place);

    //add building is done directly on the tile

    /**reveals a unit baesd on the visibility of the unit type
     *      and reveals all the city's tiles
     * @param to_rev unit or city to reveal
     */
    void reveal_unit(Unit * to_rev);
    void reveal_city(City * rev);

    /**
     * reveals all tiles within visible range given by unit static method of all units in players civ
     */
    void reveal();

    /**
     * moves the currently active unit - returns true if unit physically moves
     *      updates active unit's current movement and resets the unit on the tile moving from
     * @param to_move_to
     * @return
     */
    bool move_active_unit(Tile & to_move_to);

    /**
     * builds a new base city on the tile given and with the civilization given
     * @param civ
     * @param build_on
     */
    void build_city(Civilization_Name::Names civ, Tile & build_on);

    int get_num_cities(Civilization_Name::Names civ);

    /**
     * map getters and setters
     * @return
     */
    Map & get_map();
    const Map & get_map_const() const;

    void set_phase(Turn_Phase::names newphase);

    /**
     * sets the turn managers phase to the next phase. essentially legacy functionality at this point
     */
    void next_phase();

    /**
     * draws the current phase on the square base given
     * @param base
     */
    void phase_on_button(Square base);

    void print_build_menu_title(Square base, Square base2);

    /**
     * @return current phase ase a string
     */
    std::string get_phase();

    /**
    * moves to next player turn; plays ai turn
    */
    void next_turn();

    Coordinate get_unit_location_coordinates(Unit & u);

    /**
     * saves to default file names
     */
    void save();
    void load();
    void load(std::string civs_filename, std::string map_filename, std::string tm_filename);

    Game & operator=(const Game & cp);
    bool operator==(const Game & rhs);
    bool operator!=(const Game & rhs);

    ~Game();
};


#endif //CIV_GAME_H
