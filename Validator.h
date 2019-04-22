//
// Created by david on 3/29/2019.
//

#ifndef CIV_VALIDATOR_H
#define CIV_VALIDATOR_H

#include <string>

struct Validator {
    static bool is_num(char dig);
    static bool is_special_char(char dig);
    static bool has_special_char(std::string line);
    static bool is_char(char dig);
    static bool has_num(std::string line);
    static bool is_num(std::string line);
    static bool is_string(std::string line);
};

#endif //CIV_VALIDATOR_H
