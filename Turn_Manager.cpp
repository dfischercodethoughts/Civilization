#include "Turn_Manager.h"

Turn_Manager::Turn_Manager() {
    count = 0;
    current_phase = Turn_Phase::MOVE;
}

Turn_Phase::names Turn_Manager::get_current_phase() const {
    return current_phase;
}

void Turn_Manager::set_current_phase(Turn_Phase::names new_phase) {
    current_phase = new_phase;
}

void Turn_Manager::next_phase() {
    //todo: test turn manager next phase logic
    int c = current_phase;
    c++;
    current_phase = Turn_Phase::names(c);
}

void Turn_Manager::next_turn() {
    current_phase = Turn_Phase::MOVE;
    count++;
}

Turn_Manager::~Turn_Manager() {
    count = -1;
    current_phase = Turn_Phase::AI_TURN;
}