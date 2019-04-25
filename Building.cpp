//
// Created by willi on 4/19/19.
//
#include "Building.h"

Building::Building()
{
	name = NONE;
}

Building::Building(names name)
{
	this->name = name;
}

Building::names Building::get_name()
{
	return name;
}


void Building::set_name(names newName)
{
	name = newName;
}

Building::~Building()
{

}
