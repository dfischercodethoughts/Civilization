//
// Created by david on 4/19/2019.
//

#ifndef CIV_BASE_RESOURCE_PACKAGE_H
#define CIV_BASE_RESOURCE_PACKAGE_H

#include "Base_Resource.h"

class Base_Resource_Package {
/*
 *resource package structure holds a number of resources, and a resource type. Tiles return this to cities or invading
 armies when requested (by a pillage operation, or a turn based gather operation)
 */
private:
    int num;
    Base_Resource::names type;

    friend class Tile_Output;

    bool increment_number();
    void add(int to_add);
    bool set_type(Base_Resource::names new_n);
    bool set_type(std::string new_type);

public:
    explicit Base_Resource_Package(Base_Resource::names res_type);
    explicit Base_Resource_Package(std::string res_type);
    explicit Base_Resource_Package(Base_Resource::names res, int amount);

    const int get_number() const;

    const Base_Resource::names get_type() const;
    const std::string get_type_str() const;

};


#endif //CIV_BASE_RESOURCE_PACKAGE_H
