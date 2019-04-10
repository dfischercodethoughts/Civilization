
#ifndef TURN_MANAGER_H
#define TURN_MANAGER_H

#include "Turn_Phase.h"

/**
turn manager has a bunch of methods that change a civilization and map object
*/
class Turn_Manager {
private:
    int count;
    Turn_Phase::names current_phase;
	
public:

    //todo: implement

    Turn_Manager();

    Turn_Phase::names get_current_phase() const;

    void set_current_phase(Turn_Phase::names new_phase);

    void next_phase();

    void next_turn();

    ~Turn_Manager();
};

#endif