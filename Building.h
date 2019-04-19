//
// Created by willi on 4/19/19.
//

#ifndef CIV_BUILDING_H
#define CIV_BUILDING_H
class Building {

public:
    enum names {
    FARM,
    MINE,
    HUNTING_LODGE,
    LOGGING_CAMP,
    MARKET,
    NONE
    };

    Building();
    Building(names name);

    Building::names get_name();
    void set_name();
private:
    Building::names name;
};

#endif //CIV_BUILDING_H
