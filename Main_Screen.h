//
// Created by david on 4/3/2019.
//

#ifndef CIV_MAIN_SCREEN_H
#define CIV_MAIN_SCREEN_H

#include "Screen.h"
#include "Game.h"




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
    //Square build_view_port;
    Square build_square_1;
    Square build_square_2;
    Square build_square_3;
    Square build_square_4;

    Square game_view_port;
    Square piece_view_port;
    Square tile_view_port;

public:
    Main_Screen();
    Main_Screen(int h, int w, int vecx, int vecy);

    void init(int h, int w) override;
    void init(int h, int w,int vecx, int vecy);


    void draw() override;
    names get_type() const override;

    void clear_active();

    menu_options check_click(Coordinate click) override;

    void process_move(Coordinate click);
    void process_build(Coordinate click);//todo: add process_build logic

    /**
     * sets active tile, and unit if applicable.
     * todo:set active city
     * @param tile
     */
    void select_tile(Tile * tile);//todo: add active city pointer

    Game * get_game();

    ~Main_Screen();
};


#endif //CIV_MAIN_SCREEN_H
