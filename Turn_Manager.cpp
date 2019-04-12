#include "Turn_Manager.h"
/*TODO:: possibly combine turn manager and turn phase
    include logic to change the viewport with Main_Screen::process_click(Coordinate click)
    or Main_Screen::check_click(Coordinate click)
    return the value of turn phase enum to decide what the view port displays
    ie. move shows unit info when clicked on, BUILD phase only displays buildings that can be built
*/
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