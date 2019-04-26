//
// Created by willi on 4/22/19.
//

#include "Build_Menu.h"


Build_Menu::Build_Menu(){
    build_square_1 = Square();
    build_square_2 = Square();
    build_square_3 = Square();
    build_square_4 = Square();
    build_square_5 = Square();
    build_square_6 = Square();
    build_square_7 = Square();
    build_square_8 = Square();

    unit_square_1 = Square();
    unit_square_2 = Square();
    unit_square_3 = Square();
    unit_square_4 = Square();
    unit_square_5 = Square();
    unit_square_6 = Square();
}



Build_Menu::Build_Menu(int h, int w) : Square({6*w/2, 83*h/80}, Colors::WHITE, Colors::WHITE, h/4,3*w, "", true){


    build_square_1 = Square({4*w/2,77*h/80},Colors::WHITE,Colors::BLACK,h/20,w/2,"HARBOR",true);
    build_square_2 = Square({4*w/2,81*h/80},Colors::WHITE,Colors::BLACK,h/20,w/2,"LOGGING CAMP",true);
    build_square_3 = Square({4*w/2,85*h/80},Colors::WHITE,Colors::BLACK,h/20,w/2,"FARM",true);
    build_square_4 = Square({4*w/2,89*h/80},Colors::WHITE,Colors::BLACK,h/20,w/2,"MINE",true);
    build_square_5 = Square({5*w/2,77*h/80},Colors::WHITE,Colors::BLACK,h/20,w/2,"TRADING POST",true);
    build_square_6 = Square({5*w/2,81*h/80},Colors::WHITE,Colors::BLACK,h/20,w/2,"WORKSHOP",true);
    build_square_7 = Square({5*w/2,85*h/80},Colors::WHITE,Colors::BLACK,h/20,w/2,"MARKET",true);
    build_square_8 = Square({5*w/2,89*h/80},Colors::WHITE,Colors::BLACK,h/20,w/2,"BARRACKS",true);

    unit_square_1 = Square({7*w/2,77*h/80},Colors::WHITE,Colors::BLACK,h/15,w/2,"BOAT",true);
    unit_square_2 = Square({7*w/2,83*h/80},Colors::WHITE,Colors::BLACK,h/15,w/2,"WARRIOR",true);
    unit_square_3 = Square({7*w/2,89*h/80},Colors::WHITE,Colors::BLACK,h/15,w/2,"ARCHER",true);
    unit_square_4 = Square({8*w/2,77*h/80},Colors::WHITE,Colors::BLACK,h/15,w/2,"HORSEMAN",true);
    unit_square_5 = Square({8*w/2,83*h/80},Colors::WHITE,Colors::BLACK,h/15,w/2,"PLACE HOLD",true);
    unit_square_6 = Square({8*w/2,89*h/80},Colors::WHITE,Colors::BLACK,h/15,w/2,"PLACE HOLD",true);

}

void Build_Menu::set_selected_square(Square sq){
    selected_square = &sq;

}
Square Build_Menu::get_selected_square(){
    return *selected_square;
}

void Build_Menu::no_active_city_draw(){
    glColor3f(Colors::WHITE.get_red(),Colors::WHITE.get_green(),Colors::WHITE.get_blue());
    glRasterPos2i(525,875);
    std::string line = "Please Select an active City you own to show Building Menu";
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c);
    }
}

//void Build_Menu::compare_selected_square(Square sq){
//    if (sq == *selected_square){
//        selected_square->set_fill(Colors::WHITE);
//    }
//}

void Build_Menu::change_active_color(Square sq){
    if(sq == *selected_square){
sq.set_fill(Colors::YELLOW);

    }else if (sq != *selected_square){
        selected_square->set_fill(Colors::WHITE);
        sq.set_fill(Colors::YELLOW);
        selected_square = &sq;
    }
}
//void Build_Menu::selected_build_color(Game &game){
//    if(game.has_build_piece()){
//        if(game.has_build_unit()){
//            Unit::Unit_Type type;
//            type = game.get_build_unit().get_unit_type();
//
//            switch(type){
//                case(Unit::Unit_Type::BOAT) : {
//                    unit_square_1.set_fill(Colors::YELLOW);
//                    break;
//                }
//                case(Unit::Unit_Type::WARRIOR) : {
//                    unit_square_2.set_fill(Colors::YELLOW);
//                    break;
//                }
//                case(Unit::Unit_Type::ARCHER) : {
//                    unit_square_3.set_fill(Colors::YELLOW);
//                    break;
//                }
//                case(Unit::Unit_Type::HORSEMAN) : {
//                    unit_square_4.set_fill(Colors::YELLOW);
//                    break;
//                }
//                case(Unit::Unit_Type::SETTLER) : {
//                    break;
//                }
//                case(Unit::Unit_Type::SCOUT) : {
//                    break;
//                }
//                case(Unit::Unit_Type::NONE) : {
//                    break;
//                }
//            }
//
//        }else if(game.has_build_building()){
//            Building_Name::names nm;
//            nm = game.get_build_building().get_name();
//            switch(nm){
//                case(Building_Name::HARBOR) : {
//                    build_square_1.set_fill(Colors::YELLOW);
//                    break;
//                }
//                case(Building_Name::LOGGING_CAMP) : {
//                    build_square_2.set_fill(Colors::YELLOW);
//                    break;
//                }
//                case(Building_Name::FARM) : {
//                    build_square_3.set_fill(Colors::YELLOW);
//                    break;
//                }
//                case(Building_Name::MINE) : {
//                    build_square_4.set_fill(Colors::YELLOW);
//                    break;
//                }
//                case(Building_Name::TRADING_POST) : {
//                    build_square_5.set_fill(Colors::YELLOW);
//                    break;
//                }
//                case(Building_Name::WORKSHOP) : {
//                    build_square_6.set_fill(Colors::YELLOW);
//                    break;
//                }
//                case(Building_Name::MARKET) : {
//                    build_square_7.set_fill(Colors::YELLOW);
//                    break;
//                }
//                case(Building_Name::BARRACKS) : {
//                    build_square_8.set_fill(Colors::YELLOW);
//                    break;
//                }
//                case(Building_Name::NONE) : {
//                    break;
//                }
//            }
//
//        }
//    }
//}

std::string Build_Menu::ret_build_name(Coordinate click){
    if(build_square_1.check_click(click)){
        build_square_1.set_fill(Colors::YELLOW);
        selected_square->set_fill(Colors::WHITE);
        selected_square = &build_square_1;
        return "HARBOR";
    }
    else if (build_square_2.check_click(click)){
        build_square_2.set_fill(Colors::YELLOW);
        selected_square->set_fill(Colors::WHITE);
        selected_square = &build_square_2;

        return "LOGGING_CAMP";
    }
    else if (build_square_3.check_click(click)){
        build_square_3.set_fill(Colors::YELLOW);
        selected_square->set_fill(Colors::WHITE);
        selected_square = &build_square_3;

        return "FARM";
    }
    else if (build_square_4.check_click(click)){
        build_square_4.set_fill(Colors::YELLOW);
        selected_square->set_fill(Colors::WHITE);
        selected_square = &build_square_4;

        return "MINE";
    }
    else if(build_square_5.check_click(click)){
        build_square_5.set_fill(Colors::YELLOW);
        selected_square->set_fill(Colors::WHITE);
        selected_square = &build_square_5;

        return "TRADING POST";
    }
    else if (build_square_6.check_click(click)){
        build_square_6.set_fill(Colors::YELLOW);
        selected_square->set_fill(Colors::WHITE);
        selected_square = &build_square_6;
        return "WORKSHOP";
    }
    else if (build_square_7.check_click(click)){
        build_square_7.set_fill(Colors::YELLOW);
        selected_square->set_fill(Colors::WHITE);
        selected_square = &build_square_7;
        return "MARKET";
    }
    else if (build_square_8.check_click(click)){
        build_square_8.set_fill(Colors::YELLOW);
        selected_square->set_fill(Colors::WHITE);
        selected_square = &build_square_8;
        return "BARRACKS";
    }
    else if (unit_square_1.check_click(click)){
        unit_square_1.set_fill(Colors::YELLOW);
        selected_square->set_fill(Colors::WHITE);
        selected_square = &unit_square_1;
        return "BOAT";
    }
    else if (unit_square_2.check_click(click)){
        unit_square_2.set_fill(Colors::YELLOW);
        selected_square->set_fill(Colors::WHITE);
        selected_square = &unit_square_2;
        return "WARRIOR";
    }
    else if (unit_square_3.check_click(click)){
        unit_square_3.set_fill(Colors::YELLOW);
        selected_square->set_fill(Colors::WHITE);
        selected_square = &unit_square_3;
        return "ARCHER";
    }
    else if (unit_square_4.check_click(click)){
        unit_square_4.set_fill(Colors::YELLOW);
        selected_square->set_fill(Colors::WHITE);
        selected_square = &unit_square_4;
        return "HORSEMAN";
    }
    else if (unit_square_5.check_click(click)){
        return "NONE";
    }
    else if (unit_square_6.check_click(click)){
        return "NONE";
    }else{
        return "NONE";
    }
}

Square Build_Menu::return_square(std::string str){
    if(str == "HARBOR"){
        return build_square_1;
    }else if (str == "LOGGING_CAMP"){
        return build_square_2;
    }else if (str == "FARM"){
        return build_square_3;
    }else if (str == "MINE"){
        return build_square_4;
    }else if (str == "TRADING_POST"){
        return build_square_5;
    }else if (str == "WORKSHOP"){
        return build_square_6;
    }else if (str == "MARKET"){
        return build_square_7;
    }else if (str == "BARRACKS"){
        return build_square_8;
    }else if (str == "BOAT"){
        return unit_square_1;
    }else if (str == "WARRIOR"){
        return unit_square_2;
    }else if (str == "ARCHER"){
        return unit_square_3;
    }else if (str == "HORSEMAN"){
        return unit_square_4;
    }else{
        return unit_square_5;
    }
}


void Build_Menu::all_squares_white(){
    build_square_1.set_fill(Colors::WHITE);
    build_square_2.set_fill(Colors::WHITE);
    build_square_3.set_fill(Colors::WHITE);
    build_square_4.set_fill(Colors::WHITE);
    build_square_5.set_fill(Colors::WHITE);
    build_square_6.set_fill(Colors::WHITE);
    build_square_7.set_fill(Colors::WHITE);
    build_square_8.set_fill(Colors::WHITE);

    unit_square_1.set_fill(Colors::WHITE);
    unit_square_2.set_fill(Colors::WHITE);
    unit_square_3.set_fill(Colors::WHITE);
    unit_square_4.set_fill(Colors::WHITE);
    unit_square_5.set_fill(Colors::WHITE);
    unit_square_6.set_fill(Colors::WHITE);
}

//go through, compare the prod_val (how much production the city has)
//against the values of all of the squares
//this would work better as an array/vector but for the sake of not messing anything up we hard coding
//beige for now until I can figure out what grey is
void Build_Menu::grey_out(int prod_val) {
    //greater than 60 notihing needs to happen
    if(prod_val >= 50 && prod_val < 60){
        build_square_8.set_fill(Colors::BEIGE);

        unit_square_5.set_fill(Colors::BEIGE);
        unit_square_6.set_fill(Colors::BEIGE);
    }else if(prod_val >= 40 && prod_val < 50){

        build_square_6.set_fill(Colors::BEIGE);
        build_square_7.set_fill(Colors::BEIGE);
        build_square_8.set_fill(Colors::BEIGE);

        unit_square_4.set_fill(Colors::BEIGE);
        unit_square_5.set_fill(Colors::BEIGE);
        unit_square_6.set_fill(Colors::BEIGE);
    }else if(prod_val >= 30 && prod_val < 40){

        build_square_3.set_fill(Colors::BEIGE);
        build_square_4.set_fill(Colors::BEIGE);
        build_square_5.set_fill(Colors::BEIGE);
        build_square_6.set_fill(Colors::BEIGE);
        build_square_7.set_fill(Colors::BEIGE);
        build_square_8.set_fill(Colors::BEIGE);

        unit_square_3.set_fill(Colors::BEIGE);
        unit_square_4.set_fill(Colors::BEIGE);
        unit_square_5.set_fill(Colors::BEIGE);
        unit_square_6.set_fill(Colors::BEIGE);

    }else if(prod_val >= 20 && prod_val < 30){

        build_square_2.set_fill(Colors::BEIGE);
        build_square_3.set_fill(Colors::BEIGE);
        build_square_4.set_fill(Colors::BEIGE);
        build_square_5.set_fill(Colors::BEIGE);
        build_square_6.set_fill(Colors::BEIGE);
        build_square_7.set_fill(Colors::BEIGE);
        build_square_8.set_fill(Colors::BEIGE);

        unit_square_2.set_fill(Colors::BEIGE);
        unit_square_3.set_fill(Colors::BEIGE);
        unit_square_4.set_fill(Colors::BEIGE);
        unit_square_5.set_fill(Colors::BEIGE);
        unit_square_6.set_fill(Colors::BEIGE);

        //else it's less than 20 and nothing can be built
    }else if(prod_val > 20){

        build_square_1.set_fill(Colors::BEIGE);
        build_square_2.set_fill(Colors::BEIGE);
        build_square_3.set_fill(Colors::BEIGE);
        build_square_4.set_fill(Colors::BEIGE);
        build_square_5.set_fill(Colors::BEIGE);
        build_square_6.set_fill(Colors::BEIGE);
        build_square_7.set_fill(Colors::BEIGE);
        build_square_8.set_fill(Colors::BEIGE);

        unit_square_1.set_fill(Colors::BEIGE);
        unit_square_2.set_fill(Colors::BEIGE);
        unit_square_3.set_fill(Colors::BEIGE);
        unit_square_4.set_fill(Colors::BEIGE);
        unit_square_5.set_fill(Colors::BEIGE);
        unit_square_6.set_fill(Colors::BEIGE);

    }




}

void Build_Menu::draw() const {
    build_square_1.draw();
    build_square_2.draw();
    build_square_3.draw();
    build_square_4.draw();
    build_square_5.draw();
    build_square_6.draw();
    build_square_7.draw();
    build_square_8.draw();

    unit_square_1.draw();
    unit_square_2.draw();
    unit_square_3.draw();
    unit_square_4.draw();
    unit_square_5.draw();
    unit_square_6.draw();
}

