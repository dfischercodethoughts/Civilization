//
// Created by david on 3/29/2019.
//

#include "Validator.h"

bool Validator::is_num(char dig) {
    if (dig == '1' || dig == '2' || dig == '3' || dig == '4' || dig == '5' || dig == '6' || dig == '7' || dig == '8' || dig == '9' || dig == '0') {
        return true;
    }
    return false;
}

bool Validator::is_special_char(char dig) {
    if (dig == '!' || dig == '@' || dig == '#'|| dig == '$'|| dig == '%'|| dig == '^'|| dig == '&'|| dig == '*'|| dig == '('|| dig == ')'|| dig == '-'|| dig == '_'|| dig == '+'|| dig == '='|| dig == '['|| dig == '{'|| dig == ']'|| dig == '}'|| dig == '\\'|| dig == '|'|| dig == ':'|| dig == ';' || dig == '\''|| dig == '\"'|| dig == '<'|| dig == ','|| dig == '.'|| dig == '>'|| dig == '/'|| dig == '?' || dig == '`'|| dig == '~') {
        return true;
    }
    return false;
}

bool Validator::has_special_char(std::string check) {
    for (int i = 0; i < check.size(); i++) {
        if (is_special_char(check[i])) {
            return true;
        }
    }
    return false;
}

bool Validator::is_char(char dig) {
    if (! is_num(dig) & ! is_special_char(dig)) {
        return true;
    }
    return false;
}

bool Validator::has_num(std::string line) {
    for (int i = 0; i < line.size(); i+=1) {
        if (is_num(line[i])) {
            return true;
        }
    }

    return false;
}

bool Validator::is_num(std::string line) {
    for (int i = 0; i < line.size(); i+=1) {
        if (!is_num(line[i])) {
            return false;
        }
    }
    return true;
}

bool Validator::is_string(std::string line) {
    for (int i = 0; i < line.size(); i+=1) {
        if (!is_char(line[i])) {
            return false;
        }
    }
    return true;
}