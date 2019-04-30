//
// Created by david on 4/3/2019.
//

#ifndef CIV_MAIN_SCREEN_H
#define CIV_MAIN_SCREEN_H

#include "Screen.h"
#include "Game.h"
#include <vector>
#include "Civilization.h"



/**
 * main screen is the screen that holds the main game
 */
class Main_Screen : public Screen {
public:
    enum Main_Options {
        NEXT_TURN,
        SELECT_TILE,
        BUILD,
        MOVE
    };

private:
    Game game;
    Square next_turn;
    Square next_phase;

    Square build_city_button;

    Build_Menu buildmenu;

    Square game_view_port;
    Square piece_view_port;
    Square tile_view_port;
    Square city_view_port;

public:
    /**
     * constructors call init
     */
    Main_Screen();
    Main_Screen(int h, int w, int vecx, int vecy);

    /**
     * sets all the squares used in the main game based on input height and width
     *  giving vector x and vector y coordinates allows you to choose how many tiles the game board has
     * @param h
     * @param w
     */
    void init(int h, int w) override;
    void init(int h, int w,int vecx, int vecy);

    /**
     *
     */
    void draw() override;

    /**
     * @return screen type::main
     */
    names get_type() const override;

    /**
     * clears active pointers in game (sets to nullptr)
     */
    void clear_active();

    /**
     * processes a click
     * rather complex logic
     * @param click
     * @return
     */
    menu_options check_click(Coordinate click) override;

    /**
     * @returns the string name of the winner or NONE
     */
    std::string check_winner();

    /**
     * process click and process build logic
     * @param click
     */
    void process_move(Coordinate click);
    void process_build(Coordinate click);

    /**
     * sets active tile, and unit if applicable.
     * todo:set active city
     * @param tile
     */
    void select_tile(Tile * tile);//todo: add active city pointer

    Game * get_game();
    //creates new game with given vals and sets game equal to it
    void new_game(int h, int w, int vh, int vw);

    ~Main_Screen();
};


#endif //CIV_MAIN_SCREEN_H
