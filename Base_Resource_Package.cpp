//
// Created by david on 4/19/2019.
//

#include "Base_Resource_Package.h"
//
// Created by david on 3/29/2019.
//


bool Base_Resource_Package::increment_number() {

    if (num < 7) {
        num += 1;
        return true;
    }
    return false;
}

bool Base_Resource_Package::decrement_number() {

    if (num < 7) {
        num -= 1;
        return true;
    }
    return false;
}

void Base_Resource_Package::add(int to_add) {
    if (abs(to_add) < 100) {
        num += to_add;
    }
}

bool Base_Resource_Package::set_type(Base_Resource::names nme) {
    if (nme == Base_Resource::GOLD) {
        type = Base_Resource::GOLD;
        return true;
    } else if (nme == Base_Resource::PRODUCTION) {
        type = Base_Resource::PRODUCTION;
        return true;
    } else if (nme == Base_Resource::FOOD) {
        type = Base_Resource::FOOD;
        return true;
    }
    return false;
}

bool Base_Resource_Package::set_type(std::string nme) {
    Base_Resource::names new_n = Base_Resource::string_to_base_resource(nme);
    return set_type(new_n);
}

Base_Resource_Package::Base_Resource_Package(Base_Resource::names nme) {
    set_type(nme);
    num = 0;
}

Base_Resource_Package::Base_Resource_Package(std::string new_n) {
    set_type(new_n);
    num = 0;
}

Base_Resource_Package::Base_Resource_Package(Base_Resource::names res,int amount) :
        Base_Resource_Package(res)
{
    if (abs(amount) < 100) {
        num = 0;
    }
    num = amount;
}

const int Base_Resource_Package::get_number() const {
    return int(num);
}

const Base_Resource::names Base_Resource_Package::get_type() const {
    return Base_Resource::names(type);
}

const std::string Base_Resource_Package::get_type_str() const {
    return Base_Resource::to_string(type);
}