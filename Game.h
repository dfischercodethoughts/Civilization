//
// Created by david on 4/3/2019.
//

#ifndef CIV_GAME_H
#define CIV_GAME_H

#include <memory>
#include "Civilization.h"
#include "Tile.h"
//#include"City.h"
#include"Unit.h"
#include "Map.h"
#include "Turn_Manager.h"
#include <random>

class Game {
private:
    Civilization player;
    Civilization ai;
    Turn_Manager manager;

    std::unique_ptr<Tile> active_tile;
    //std::shared_ptr<City> active_city;
    std::unique_ptr<Unit> active_unit;
    //std::shared_ptr<Building> active_building;

    Map map;

    //justmoves units for now - will attack if can, otherwise moves randomly
    void play_ai();


public:
    const static int MAP_X_OFF = 10;
    const static int MAP_Y_OFF = 210;

    Game();
    Game(int width, int height, int vecw, int vech);

    Civilization & get_player();
    const Civilization & get_player_const() const;
    Civilization & get_ai();
    const Civilization & get_ai_const() const;

    std::unique_ptr<Tile> & get_active_tile();
    const std::unique_ptr<Tile> & get_active_tile_const() const;
    //std::shared_ptr<City> & get_active_city();
    std::unique_ptr<Unit> & get_active_unit();
    const std::unique_ptr<Unit> & get_active_unit_const() const;

    const Turn_Manager &get_turn_manager() const;

    //todo: deal with nullptr case
    void set_active_tile(Tile & tile);
    void set_active_unit(Unit & unit);
    bool has_active_unit() const;
    bool has_active_tile() const;
    void clear_active_tile();
    void clear_active_unit();

    void move_active_unit(Tile & to_move_to);

    Map & get_map();
    const Map & get_map_const() const;

    void set_phase(Turn_Phase::names newphase);

    void next_phase();


    std::string get_phase();

    void next_turn();//moves to next player turn; plays ai turn

    Coordinate get_unit_location_coordinates(Unit & u);

    Game & operator=(const Game & cp);

    ~Game();
};


#endif //CIV_GAME_H
