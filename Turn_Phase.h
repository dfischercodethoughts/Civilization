//
// Created by david on 3/29/2019.
//

#ifndef CIV_TURN_PHASE_H
#define CIV_TURN_PHASE_H

#include <string>
/**
 * low level turn phase struct holds the turn phase names enum and helper methods
 */
struct Turn_Phase {
    enum names {
        MOVE,
        BUILD,
        COLLECT,
        AI_TURN,
        DEFAULT
    };

static Turn_Phase::names string_to_turn_phase(std::string phs);
static std::string turn_phase_to_string(Turn_Phase::names nm);
};


#endif //CIV_TURN_PHASE_H
