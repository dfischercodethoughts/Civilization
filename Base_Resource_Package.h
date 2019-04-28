//
// Created by david on 4/19/2019.
//

#ifndef CIV_BASE_RESOURCE_PACKAGE_H
#define CIV_BASE_RESOURCE_PACKAGE_H

#include "Base_Resource.h"

class Base_Resource_Package {
/*
 *resource package structure holds the number of the resources, and a resource type. Tiles return this to cities or invading
 armies when requested (by a pillage operation, or a turn based gather operation)
 This is a low level structure used by tiles, cities, and civilizations to pass resources
 */
private:
    int num;
    Base_Resource::names type;

    friend class Tile_Output;

    //private methods to change the number of the resource
    bool increment_number();
    bool decrement_number();
    void add(int to_add);
    //changes the type of the resource in the package
    bool set_type(Base_Resource::names new_n);
    bool set_type(std::string new_type);

public:
    //constructors
    explicit Base_Resource_Package(Base_Resource::names res_type);
    explicit Base_Resource_Package(std::string res_type);
    explicit Base_Resource_Package(Base_Resource::names res, int amount);

    /**
     * @return number of the resource
     */
    const int get_number() const;

    /**
     * getters for the type of resource
     * @return
     */
    const Base_Resource::names get_type() const;
    const std::string get_type_str() const;

};


#endif //CIV_BASE_RESOURCE_PACKAGE_H
