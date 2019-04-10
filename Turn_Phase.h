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
        AI_TURN
    };

static Turn_Phase::names string_to_turn_phase(std::string phs);
static std::string to_string(Turn_Phase::names);
};


#endif //CIV_TURN_PHASE_H
