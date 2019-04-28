//
// Created by david on 4/19/2019.
//

#ifndef CIV_BASE_RESOURCE_H
#define CIV_BASE_RESOURCE_H

#include<string>
//base resources holds an enum with values production, gold, and food
struct Base_Resource {
    enum names {
        DEFAULT,
        FOOD,
        PRODUCTION,
        GOLD
    };

    //functions to turn from string to base resource and back again
    static std::string to_string(names resource);


    static names string_to_base_resource(std::string res_str);
};


#endif //CIV_BASE_RESOURCE_H
