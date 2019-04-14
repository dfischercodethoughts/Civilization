//
// Created by david on 4/3/2019.
//

#ifndef CIV_UNIT_H
#define CIV_UNIT_H

#include "Piece.h"
#include "Civilization_Name.h"
#include <memory>

//todo:implement the rest of the unit classes

class Unit : public Piece {
public:
    enum Unit_Type {
        NONE,
        SCOUT,
        WARRIOR,
        ARCHER,
        SETTLER,
        BOAT,
        HORSEMAN
    };

    static std::string unit_type_to_string(Unit_Type unit_name);
    static Unit_Type string_to_unit_type(std::string);
    static int get_max_health(Unit_Type type);
    static int get_max_movement(Unit_Type type);
    static int get_upkeep(Unit_Type type);
    static int get_gold_cost(Unit_Type type);
    static int get_damage(Unit_Type type);

private:
    int tile_id;
    Civilization_Name::Names owner;
    //todo: switch all std::shared_ptr<Civilization> to Civilization &

    int health, damage,movement;

    Unit_Type unit_type;

    void set_movement(int newm);
    void reset_movement();//refreshes based on type
    void set_health(int newh);
    void reset_health();
    void set_damage();

public:
    /**
     * sets parent (piece) type to unit
     */
    Unit();
    Unit(int start_tile, Unit_Type tp);
    Unit(int loca, Civilization_Name::Names owner, Unit_Type tp);
    Unit(int loca,Coordinate c, Civilization_Name::Names owner, Unit_Type tp);
    Unit(Unit const & to_cpy);
    Unit(Unit const * cpy);
    Unit(std::unique_ptr<Unit> to_cpy);

    int get_location_id() const;

    Civilization_Name::Names get_owner() const;

    int get_current_health() const;
    int get_current_movement() const;

    int get_upkeep() const;
    int get_max_health() const;
    int get_damage() const;

    Unit_Type get_unit_type() const;

    void set_location(int newl);

    void set_owner(Civilization_Name::Names newown);

    void set_unit_type(Unit_Type newtype);

    void use_movement(int touse);

    /**
     * extra functions
     */
    //draw functions
    void draw();
    void draw_on_tile(Square base);
    void draw_on_viewport(Square viewport_base) override;

    /**
     *  switches on attacker and deals damage accordingly
     */
    int cause_damage(Unit_Type attacking_unit);

    /**
     * heals 1/20 of total possible health if not already at full health
     * @return newhealth after heal
     */
    //heals fully
    void full_heal();
    //heals 1/20th
    void heal();

    //refills movement points, and heals (not full)
    void refresh();

    /**
     * overloaded operators
     */
     //equality based on tile equality (only one unit per tile)
    bool operator==(Unit const & rhs);

    Unit & operator=(Unit const & rhs);

    ~Unit();
};


#endif //CIV_UNIT_H
