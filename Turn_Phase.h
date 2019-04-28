//
// Created by david on 3/29/2019.
//

#ifndef CIV_TURN_PHASE_H
#define CIV_TURN_PHASE_H

#include <string>

struct Turn_Phase {
    enum names {
        MOVE,
        BUILD,
        COLLECT,
        AI_TURN,
        DEFAULT
    };

    //returns a phase from a phase as a string
static Turn_Phase::names string_to_turn_phase(std::string phs);

//returns a string from a given phase
static std::string turn_phase_to_string(Turn_Phase::names nm);
};


#endif //CIV_TURN_PHASE_H
