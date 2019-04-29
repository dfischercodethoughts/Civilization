//
// Created by willi on 4/22/19.
//

#include "Build_Menu.h"

Build_Menu::Build_Menu(){
    selected_square = nullptr;

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
    selected_square = nullptr;

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

void Build_Menu::change_active_color(Square sq){
    if(sq == *selected_square){
        sq.set_fill(Colors::YELLOW);

    }else if (sq != *selected_square){
        selected_square->set_fill(Colors::WHITE);
        sq.set_fill(Colors::YELLOW);
        selected_square = &sq;
    }
}

std::string Build_Menu::ret_build_name(Coordinate click, int prod){
    if(build_square_1.check_click(click) && prod >= Building_Name::get_production_cost(Building_Name::HARBOR)){
        if (selected_square != nullptr) {
            selected_square->set_fill(Colors::WHITE);
        }
        build_square_1.set_fill(Colors::YELLOW);
        selected_square = &build_square_1;
        return "HARBOR";
    }
    else if (build_square_2.check_click(click)&& prod >= Building_Name::get_production_cost(Building_Name::LOGGING_CAMP)){
        if (selected_square != nullptr) {
            selected_square->set_fill(Colors::WHITE);
        }
        build_square_2.set_fill(Colors::YELLOW);
        selected_square = &build_square_2;

        return "LOGGING_CAMP";
    }
    else if (build_square_3.check_click(click)&& prod >= Building_Name::get_production_cost(Building_Name::FARM)){
        if (selected_square != nullptr) {
            selected_square->set_fill(Colors::WHITE);
        }
        build_square_3.set_fill(Colors::YELLOW);
        selected_square = &build_square_3;

        return "FARM";
    }
    else if (build_square_4.check_click(click)&& prod >= Building_Name::get_production_cost(Building_Name::MINE)){
        if (selected_square != nullptr) {
            selected_square->set_fill(Colors::WHITE);
        }
        build_square_4.set_fill(Colors::YELLOW);
        selected_square = &build_square_4;

        return "MINE";
    }
    else if(build_square_5.check_click(click)&& prod >= Building_Name::get_production_cost(Building_Name::TRADING_POST)){
        if (selected_square != nullptr) {
            selected_square->set_fill(Colors::WHITE);
        }
        build_square_5.set_fill(Colors::YELLOW);
        selected_square = &build_square_5;

        return "TRADING POST";
    }
    else if (build_square_6.check_click(click)&& prod >= Building_Name::get_production_cost(Building_Name::WORKSHOP)){
        if (selected_square != nullptr) {
            selected_square->set_fill(Colors::WHITE);
        }
        build_square_6.set_fill(Colors::YELLOW);
        selected_square = &build_square_6;
        return "WORKSHOP";
    }
    else if (build_square_7.check_click(click)&& prod >= Building_Name::get_production_cost(Building_Name::MARKET)){
        if (selected_square != nullptr) {
            selected_square->set_fill(Colors::WHITE);
        }
        build_square_7.set_fill(Colors::YELLOW);
        selected_square = &build_square_7;
        return "MARKET";
    }
    else if (build_square_8.check_click(click)&& prod >= Building_Name::get_production_cost(Building_Name::BARRACKS)){
        if (selected_square != nullptr) {
            selected_square->set_fill(Colors::WHITE);
        }
        build_square_8.set_fill(Colors::YELLOW);
        selected_square = &build_square_8;
        return "BARRACKS";
    }
    else if (unit_square_1.check_click(click)&& prod >= Unit::get_production_cost(Unit::BOAT)){
        if (selected_square != nullptr) {
            selected_square->set_fill(Colors::WHITE);
        }
        unit_square_1.set_fill(Colors::YELLOW);
        selected_square = &unit_square_1;
        return "BOAT";
    }
    else if (unit_square_2.check_click(click)&& prod >= Unit::get_production_cost(Unit::WARRIOR)){
        if (selected_square != nullptr) {
            selected_square->set_fill(Colors::WHITE);
        }
        unit_square_2.set_fill(Colors::YELLOW);
        selected_square = &unit_square_2;
        return "WARRIOR";
    }
    else if (unit_square_3.check_click(click)&& prod >= Unit::get_production_cost(Unit::ARCHER)){
        if (selected_square != nullptr) {
            selected_square->set_fill(Colors::WHITE);
        }
        unit_square_3.set_fill(Colors::YELLOW);
        selected_square = &unit_square_3;
        return "ARCHER";
    }
    else if (unit_square_4.check_click(click)&& prod >= Unit::get_production_cost(Unit::HORSEMAN)){
        if (selected_square != nullptr) {
            selected_square->set_fill(Colors::WHITE);
        }
        unit_square_4.set_fill(Colors::YELLOW);
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

void Build_Menu::print_production_cost_building(Square sq, Building_Name::names nm) const{
    std::string line = "Cost: " + std::to_string(Building_Name::get_production_cost(nm));
    glColor3f(Colors::RED.get_red(),Colors::RED.get_green(),Colors::RED.get_blue());
    glRasterPos2i(sq.get_center().x-sq.get_width()/2+sq.get_width()/7,sq.get_center().y-19*sq.get_height()/64);
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,c);
    }
}

void Build_Menu::print_production_cost_unit(Square sq, Unit::Unit_Type type) const{
    std::string line = "Cost: " + std::to_string(Unit::get_production_cost(type));
    glColor3f(Colors::RED.get_red(),Colors::RED.get_green(),Colors::RED.get_blue());
    glRasterPos2i(sq.get_center().x-sq.get_width()/2+sq.get_width()/7,sq.get_center().y-5*sq.get_height()/16);
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,c);
    }
}

int Build_Menu::grey_out(int prod_val) {
    if(prod_val < 20){

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

        return 0;

    }else if(prod_val > 19 && prod_val < 30){

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

        return 0;
    }else if(prod_val > 29 && prod_val < 40){

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

        return 0;

    }else if(prod_val > 39 && prod_val < 50){

        build_square_6.set_fill(Colors::BEIGE);
        build_square_7.set_fill(Colors::BEIGE);
        build_square_8.set_fill(Colors::BEIGE);

        unit_square_4.set_fill(Colors::BEIGE);
        unit_square_5.set_fill(Colors::BEIGE);
        unit_square_6.set_fill(Colors::BEIGE);

        return 0;
    }else if(prod_val > 49 && prod_val < 60){
        build_square_8.set_fill(Colors::BEIGE);

        unit_square_5.set_fill(Colors::BEIGE);
        unit_square_6.set_fill(Colors::BEIGE);

        return 0;
    }else{
        return 0;
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

    print_production_cost_building(build_square_1, Building_Name::HARBOR);
    print_production_cost_building(build_square_2, Building_Name::LOGGING_CAMP);
    print_production_cost_building(build_square_3, Building_Name::FARM);
    print_production_cost_building(build_square_4, Building_Name::MINE);
    print_production_cost_building(build_square_5, Building_Name::TRADING_POST);
    print_production_cost_building(build_square_6, Building_Name::WORKSHOP);
    print_production_cost_building(build_square_7, Building_Name::MARKET);
    print_production_cost_building(build_square_8, Building_Name::BARRACKS);

    print_production_cost_unit(unit_square_1, Unit::BOAT);
    print_production_cost_unit(unit_square_2, Unit::WARRIOR);
    print_production_cost_unit(unit_square_3, Unit::ARCHER);
    print_production_cost_unit(unit_square_4, Unit::HORSEMAN);







}

