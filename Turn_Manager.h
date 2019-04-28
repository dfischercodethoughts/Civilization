
#ifndef TURN_MANAGER_H
#define TURN_MANAGER_H

#include "Turn_Phase.h"
#include <iostream>

/**
turn manager keeps track of the number of turns played, and the current turn phase (it turns into the ai turn)
 at a certain point)
*/
class Turn_Manager {
private:
    int count;
    Turn_Phase::names current_phase;
	
public:

    Turn_Manager();

    Turn_Phase::names get_current_phase() const;

    std::string get_current_phase_str() const;

    int get_num_turns() const;

    void set_current_phase(Turn_Phase::names new_phase);

    void next_phase();

    void next_turn();

    /**
     * prints TURN MANAGER:turns,cur_phase\n
     * @param outs
     * @param print
     * @return
     */
    friend std::ostream & operator<<(std::ostream & outs, const Turn_Manager & print);
    friend std::istream & operator>>(std::istream & ins, Turn_Manager & fill);


    ~Turn_Manager();
};

bool operator==(const Turn_Manager & lhs, const Turn_Manager & rhs);

#endif