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
    c = c%4;
    current_phase = Turn_Phase::names(c);
}

std::string Turn_Manager::get_current_phase_str() const {
    switch (current_phase) {

        case (Turn_Phase::MOVE) : {
            return "MOVE";
        }
        case (Turn_Phase::BUILD) : {
            return "BUILD";
        }
        case (Turn_Phase::COLLECT) : {
            return "COLLECT";
        }
        default : {
            return "AI_TURN";
        }
    }
}

int Turn_Manager::get_num_turns() const {
    return count;
}

std::string to_string(Turn_Phase::names nm) {
    switch (nm) {

        case (Turn_Phase::MOVE) : {
            return "MOVE";
        }
        case (Turn_Phase::BUILD) : {
            return "BUILD";
        }
        case (Turn_Phase::COLLECT) : {
            return "COLLECT";
        }
        default : {
            return "AI_TURN";
        }
    }
}

void Turn_Manager::next_turn(){
    current_phase = Turn_Phase::MOVE;
    count++;
}


std::ostream & operator<<(std::ostream &outs, const Turn_Manager & print) {
    std::string line = "TURN MANAGER:" + std::to_string(print.count) + "," + Turn_Phase::turn_phase_to_string(print.current_phase);
    outs << line << std::endl;
    return outs;
}

std::istream & operator>>(std::istream & ins, Turn_Manager & fill) {
    std::string line = "";
    std::getline(ins,line);
    //burn first token
    line.erase(0,line.find(':')+1);
    std::string tok = line.substr(0,line.find(','));
    fill.count = std::stoi(tok);

    line.erase(0,line.find(',')+1);
    fill.current_phase = Turn_Phase::string_to_turn_phase(line.substr(0,line.length()));
    return ins;
}

Turn_Manager::~Turn_Manager() {
    count = -1;
    current_phase = Turn_Phase::AI_TURN;
}

bool operator==(const Turn_Manager & lhs, const Turn_Manager & rhs) {
    if (lhs.get_current_phase() == rhs.get_current_phase() && lhs.get_num_turns() == rhs.get_num_turns()) {
        return true;
    }
    return false;
}