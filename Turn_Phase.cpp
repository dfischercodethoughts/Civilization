//
// Created by david on 3/29/2019.
//

#include "Turn_Phase.h"

Turn_Phase::names Turn_Phase::string_to_turn_phase(std::string phs){
    if (phs == "MOVE") {
        return Turn_Phase::MOVE;
    }
    else if (phs == "BUILD") {
        return Turn_Phase::BUILD;
    }
    else if (phs == "COLLECT") {
        return Turn_Phase::COLLECT;
    }

    else if (phs == "AI_TURN" || phs == "AI TURN") {
        return Turn_Phase::AI_TURN;
    }
    else return Turn_Phase::DEFAULT;
}


std::string Turn_Phase::turn_phase_to_string(Turn_Phase::names nm) {
    switch(nm) {
        case (MOVE) : {
            return "MOVE";
            break;
        }
        case (BUILD) : {
            return "BUILD";
            break;
        }
        case (COLLECT) : {
            return "COLLECT";
            break;
        }
        case (AI_TURN) : {
            return "AI_TURN";
            break;
        }
        default : {
            return "DEFAULT";
        }
    }
}
