//
// Created by david on 4/3/2019.
//

#include "Map.h"
#include "Game.h"


void Map::hide_map() {
    for (int  i = 0; i < tiles.size();i++) {
        for (int j = 0;j<tiles[i].size();j++){
            tiles[i][j].hide();
        }
    }
}

Map::Map(int h, int w, int numx, int numy):
Square(Coordinate(w/2,h/2),Color(150,150,25),Color(0,0,0),h,w,"",true)
{
    int tile_width = w/numx;
    int tile_height = h/numy;
    int count = 0;
    for (int i = 0; i < numx; i++) {
        tiles.emplace_back( std::vector<Tile>());
        for (int j = 0; j < numy; j++) {
            count +=1;
            tiles[i].emplace_back( Tile({i*tile_width+tile_width/2,j*tile_height+tile_height/2},tile_height,tile_width,Color(255,255,255),Color(0,0,0),Tile_Terrain::GRASSLAND,Tile_Resource::WHEAT,count));
        }
    }
}

Map::Map(int h, int w, int numx, int numy,int xoff, int yoff):
        Square(Coordinate(w/2,h/2),Color(150,150,25),Color(0,0,0),h,w,"",true)
{
    int tile_width = w/numx;
    int tile_height = h/numy;
    int count = 0;
    for (int i = 0; i < numx; i++) {
        tiles.emplace_back( std::vector<Tile>());
        for (int j = 0; j < numy; j++) {
            count +=1;
            tiles[i].emplace_back( Tile({i*tile_width+tile_width/2+xoff,j*tile_height+tile_height/2+yoff},tile_height,tile_width,Color(255,255,255),Color(0,0,0),Tile_Terrain::GRASSLAND,Tile_Resource::WHEAT,count));
        }
    }
}

Map::Map()
{
    tiles = std::vector<std::vector<Tile>>();
}

void Map::random_init(int h, int w, int numx, int numy)
{
    set_center(Coordinate(w/2,h/2));
    set_fill(Color(150,150,25));
    set_text_color(Color(0,0,0));
    set_height(h);
    set_width(w);
    set_message("");
    reveal();
    int tile_width = w/numx;
    int tile_height = h/numy;
    int count = 0;
    //seed random num generator
    std::mt19937 rand_gen;
    uint64_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    rand_gen.seed(seed);

    for (int i = 0; i < numx; i++) {
        tiles.emplace_back( std::vector<Tile>());
        for (int j = 0; j < numy; j++) {
            count +=1;
            //randomly generate tile

            float rand = float(rand_gen())/std::mt19937::max();
            Tile_Terrain::names ter;
            Tile_Resource::names res;
            if (rand >0 && rand <=.1) {
                ter = Tile_Terrain::WATER;
            }
            else if ( rand <= .5) {
                ter = Tile_Terrain::GRASSLAND;
            }
            else if (rand <.8) {
                ter = Tile_Terrain::HILL;
            }
            else if (rand)

            tiles[i].emplace_back( Tile({i*tile_width+tile_width/2+this->get_x_offset(),j*tile_height+tile_height/2+this->get_y_offset()},tile_height,tile_width,Color(255,255,255),Color(0,0,0),Tile_Terrain::GRASSLAND,Tile_Resource::WHEAT,count));
        }
    }
}

int Map::get_x() const {
    return tiles.size();
}

int Map::get_y() const {
    if (!tiles.empty()) {
        return tiles[0].size();
    }
    return 0;
}

void Map::clear() {
    tiles.clear();
}


std::vector<std::vector<Tile>> * Map::get_tiles() {
    return &tiles;
}

std::vector<std::vector<Tile>> Map::get_tiles_const() const {
    return tiles;
}

Coordinate Map::get_vector_coordinates_from_click(Coordinate click) {
    for (int x = 0; x < tiles.size();x++) {
        for (int y = 0; y < tiles[0].size();y++) {
            if (tiles[x][y].check_click(click)) {
                return Coordinate(x,y);
            }
        }
    }
    return {0,0};
}

//x is up and down
//y is left to right
//should influence underlying tile
Tile * Map::get_tile_from_vector_coordinates(Coordinate coord) {
    if (coord.x  >= 0 && coord.y >= 0 && coord.y < tiles[0].size() && coord.x < tiles.size()) {
        return &tiles[coord.x][coord.y];
    }
    return nullptr;
}

const Tile * Map::get_const_tile_from_vector_coordinates(Coordinate coord) const {
    if (coord.x  >= 0 && coord.y >= 0 && coord.y < tiles[0].size() && coord.x < tiles.size()) {
        return &tiles[coord.x][coord.y];
    }
    return nullptr;
}

Tile * Map::get_tile_from_click(Coordinate click) {
    if (click.x < this->get_width() && click.y < this->get_height()) {
        for (int i = 0; i < tiles.size();i++) {

            for (int j = 0; j < tiles[0].size();j++) {
                if (tiles[i][j].check_click(click)) {
                    return &tiles[i][j];
                }
            }
        }
    }
    return nullptr;
}

Tile * Map::get_tile_from_id(int id) {
    //todo: test this logic...
    for (int i = 0; i < tiles.size();i++) {
        for (int j = 0; j < tiles[0].size();j++) {
            if (tiles[i][j].get_id() == id) {
                return &tiles[i][j];
            }
        }
    }
    return 0;
}

void Map::set_background_square(Square set) {
    this->set_center(set.get_center());
    this -> set_x_offset(set.get_x_offset());
    this->set_y_offset(set.get_y_offset());
    this->set_text_color(set.get_text_color());
    this->set_message(set.get_message());
    this->set_fill(set.get_fill());
    if (set.is_visible()) {
        this->reveal();
    }
    else {
        this->hide();
    }
    this->set_height(set.get_height());
    this->set_width(set.get_width());
}

void Map::remove_duplicates(std::vector<Tile *> & list) {
    // potentially more efficient implementation possible
    std::set<Tile*> unique_set;
    for (int i = 0; i < list.size()-1;i++) {
        unique_set.emplace(&*list[i]);
    }

    list.clear();
    for (auto i = unique_set.begin();i!= unique_set.end();i++) {
        list.push_back(*i);
    }

}

std::set<Tile *>& Map::get_tiles_driver(std::set<Tile*> &cur_list,Tile & start, int move_left) {
    Coordinate vec = get_vector_coordinates_from_click(start.get_center());
    cur_list.emplace(&start);
    if (move_left > 0) {

        Tile * btm_lf = get_tile_from_vector_coordinates({vec.x-1,vec.y-1});
        Tile * left = get_tile_from_vector_coordinates({vec.x-1,vec.y});
        Tile * top_lf = get_tile_from_vector_coordinates({vec.x-1,vec.y+1});
        Tile * top = get_tile_from_vector_coordinates({vec.x,vec.y+1});
        Tile * btm = get_tile_from_vector_coordinates({vec.x,vec.y-1});
        Tile * top_rt = get_tile_from_vector_coordinates({vec.x+1,vec.y+1});
        Tile * rt = get_tile_from_vector_coordinates({vec.x+1,vec.y});
        Tile * btm_rt = get_tile_from_vector_coordinates({vec.x+1,vec.y-1});

        if(btm_lf != nullptr) {
            get_tiles_driver(cur_list, *btm_lf, move_left - Tile_Terrain::get_movement_cost(start.get_terrain()));
        }
        if (left != nullptr) {
            get_tiles_driver(cur_list, *left, move_left - Tile_Terrain::get_movement_cost(start.get_terrain()));
        }
        if (top_lf != nullptr) {
            get_tiles_driver(cur_list,*top_lf,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
        }
        if (btm != nullptr) {
            get_tiles_driver(cur_list,*btm,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
        }
        if (top != nullptr) {
            get_tiles_driver(cur_list,*top,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
        }
        if (top_rt != nullptr) {
            get_tiles_driver(cur_list,*top_rt,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
        }
        if (rt != nullptr) {
            get_tiles_driver(cur_list,*rt,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
        }
        if (btm_rt != nullptr) {
            get_tiles_driver(cur_list,*btm_rt,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
        }
/** old logic
        if (vec. x > 0 && vec.y > 0) {
            if(btm_lf != nullptr) {
                get_tiles_driver(cur_list, *btm_lf, move_left - Tile_Terrain::get_movement_cost(start.get_terrain()));
            }
            if (left != nullptr) {
                get_tiles_driver(cur_list, *left, move_left - Tile_Terrain::get_movement_cost(start.get_terrain()));
            }
            if (top_lf != nullptr) {
                get_tiles_driver(cur_list,*top_lf,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
            }
            if (btm != nullptr) {
                get_tiles_driver(cur_list,*btm,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
            }
            if (top != nullptr) {
                get_tiles_driver(cur_list,*top,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
            }
            if (top_rt != nullptr) {
                get_tiles_driver(cur_list,*top_rt,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
            }
            if (rt != nullptr) {
                get_tiles_driver(cur_list,*rt,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
            }
            if (btm_rt != nullptr) {
                get_tiles_driver(cur_list,*btm_rt,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
            }
        }
        else if (vec.x > 0 ) {
            if (left != nullptr) {
                get_tiles_driver(cur_list,*left,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
            }
            if (top_lf != nullptr) {
                get_tiles_driver(cur_list,*top_lf,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
            }
            if (top != nullptr) {
                get_tiles_driver(cur_list,*top,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
            }
            if (top_rt != nullptr) {
                get_tiles_driver(cur_list,*top_rt,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
            }
            if (rt != nullptr) {
                get_tiles_driver(cur_list,*rt,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
            }

        }
        else if (vec.y > 0 ) {

            if (btm != nullptr) {
                get_tiles_driver(cur_list,*btm,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
            }
            if (top != nullptr) {
                get_tiles_driver(cur_list,*top,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
            }
            if (top_rt != nullptr) {
                get_tiles_driver(cur_list,*top_rt,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
            }
            if (rt != nullptr) {
                get_tiles_driver(cur_list,*rt,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
            }
            if (btm_rt != nullptr) {
                get_tiles_driver(cur_list,*btm_rt,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
            }

        }*/
    }
    return cur_list;
}

std::vector<Tile *>* Map::get_tiles_within_range(Tile * start, int movement) {
    auto ret = new std::vector<Tile*>();
    auto holder  = new std::set<Tile *>();
    auto tmp = &get_tiles_driver(*holder,*start,movement);
    for (Tile * t : *holder) {
        ret->emplace_back(&*t);
    }
   // remove_duplicates(to_ret);
    return ret;
}


int Map::get_move_cost(Tile * s, Tile * e) {
    //gets the smallest possible cost of moving between two tiles
    int ret = 0;

    Coordinate start = get_vector_coordinates_from_click(s->get_center());
    Coordinate end = get_vector_coordinates_from_click(e->get_center());
    while (start.x < end.x && start.y < end.y) {
        start.x +=1;
        start.y += 1;
        ret += Tile_Terrain::get_movement_cost(get_tile_from_vector_coordinates(start)->get_terrain());
    }
    while (start.x < end.x && start.y > end.y) {
        start.x += 1;
        start.y -= 1;
        ret += Tile_Terrain::get_movement_cost(get_tile_from_vector_coordinates(start)->get_terrain());
    }
    while (start.x > end.x && start.y < end.y) {
        start.x -= 1;
        start.y += 1;
        ret += Tile_Terrain::get_movement_cost(get_tile_from_vector_coordinates(start)->get_terrain());
    }
    while (start.x > end.x && start.y > end.y) {
        start.x -= 1;
        start.y -= 1;
        ret += Tile_Terrain::get_movement_cost(get_tile_from_vector_coordinates(start)->get_terrain());
    }
    while (start.x > end.x) {
        start.x -= 1;
        ret += Tile_Terrain::get_movement_cost(get_tile_from_vector_coordinates(start)->get_terrain());
    }
    while (start.x <end.x) {
        start.x += 1;
        ret += Tile_Terrain::get_movement_cost(get_tile_from_vector_coordinates(start)->get_terrain());
    }
    while (start.y > end.y) {
        start.y -= 1;
        ret += Tile_Terrain::get_movement_cost(get_tile_from_vector_coordinates(start)->get_terrain());
    }
    while (start.y < end.y) {
        start.y += 1;
        ret += Tile_Terrain::get_movement_cost(get_tile_from_vector_coordinates(start)->get_terrain());
    }
    return ret;
}

Tile * Map::get_closest_tile(Tile * s, Tile * e) {
    //gets the smallest possible cost of moving between two tiles
    Tile * ret;

    Coordinate start = get_vector_coordinates_from_click(s->get_center());
    Coordinate end = get_vector_coordinates_from_click(e->get_center());
    while (start.x < end.x-1 && start.y < end.y-1) {
        start.x +=1;
        start.y += 1;

    }
    while (start.x < end.x-1 && start.y > end.y+1) {
        start.x += 1;
        start.y -= 1;
    }
    while (start.x > end.x+1 && start.y < end.y-1) {
        start.x -= 1;
        start.y += 1;
    }
    while (start.x > end.x+1 && start.y > end.y+1) {
        start.x -= 1;
        start.y -= 1;
    }
    while (start.x > end.x+1) {
        start.x -= 1;
    }
    while (start.x <end.x-1) {
        start.x += 1;
    }
    while (start.y > end.y+1) {
        start.y -= 1;
    }
    while (start.y < end.y-1) {
        start.y += 1;
    }
    ret = get_tile_from_vector_coordinates(start);
    return ret;
}

bool Map::is_adjacent(Tile & first, Tile & second){
    Coordinate first_coord = get_vector_coordinates_from_click(first.get_center());
    Coordinate second_coord = get_vector_coordinates_from_click(second.get_center());

    if (abs(first_coord.x - second_coord.x) <= 1) {
        if (abs(second_coord.y - first_coord.y) <= 1) {
            return true;
        }
    }
    return false;
}

void Map::reveal_units(std::vector<Unit *> units) {
    hide_map();
    for (Unit * u : units) {
        reveal_unit(u);
    }

}

void Map::reveal_unit(Unit * unit) {
    std::vector<Tile *> *rev = get_tiles_within_range(get_tile_from_id(unit->get_location_id()),
                                                      unit->get_max_movement(unit->get_unit_type()));
    make_visible(*rev);
}

void Map::reveal_city(City *city) {
    std::vector<Tile *> rev = city->get_tiles();
    make_visible(rev);
}

void Map::reveal_cities(std::vector<City *> cities) {
    for (City * c : cities) {
        reveal_city(c);
    }
}

void Map::make_visible(std::vector<Tile *> &to) {
    for (Tile * tl :to) {
        tl->reveal();
    }
}

void Map::draw() const {
    for (std::vector<Tile> const & list : tiles) {
        for (Tile const & t : list) {
            t.draw();
        }
    }
}

Map & Map::operator=(const Map & cp ) {
    if (cp.tiles.size() > 0) {
        for (int i = 0; i < cp.tiles.size(); i++) {
            tiles.emplace_back(std::vector<Tile>());

            for (int j = 0; j < cp.tiles[0].size(); j++) {//this assumes square grid...
                Tile tmp = Tile(cp.tiles[i][j]);
                tiles[i].emplace_back(&tmp);
            }
        }
    }
    this->set_center(cp.get_center());
    set_height(cp.get_height());
    set_width(cp.get_width());
    set_fill(cp.get_fill());
    set_message(cp.get_message());
    set_text_color(cp.get_text_color());
    set_x_offset(cp.get_x_offset());
    set_y_offset(cp.get_y_offset());

    return *this;
}

std::ostream & operator<<(std::ostream & outs, const Map & print) {
    try {
        std::string line = "MAP\n";
        outs << line;
        Square tmp(print.get_center(),print.get_fill(),print.get_text_color(),print.get_height(),print.get_width(),print.get_message(),print.is_visible());
        tmp.set_x_offset(print.get_x_offset());
        tmp.set_y_offset(print.get_y_offset());
        outs << tmp;
        line =std::to_string(print.tiles[0].size()) + ',' + std::to_string(print.tiles.size()) + "\n";
        outs << line;
        for (std::vector<Tile> col : print.tiles) {
            for (Tile t : col) {
                outs << t;
            }    std::string building_to_string(Building_Name::names nm);

        }
        outs<<"END"<<std::endl;//add end marker because input operator burns line at end of while loop
    }
    catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }
    return outs;
}

std::istream & operator>>(std::istream & ins, Map & fill) {
    try {
        std::string line = "";
        std::getline(ins, line);//burn "MAP\n"
        //read SQUARE infom
        Square tmp;
        ins >> tmp;
        fill.set_background_square(tmp);//fill in background square info

        std::getline(ins,line);
        std::string tok = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        //start making tiles
        int x = std::stoi(line);
        int y = std::stoi(tok);

        int county = 0; int countx = 0;
        std::getline(ins,line);
        while (line == "TILE") {
            if (county % y == 0) {
                fill.tiles.emplace_back(std::vector<Tile>());
                countx++;
                county = 0;
            }
            if (countx == x+1) {
                break;
            }
            Tile tmp_tile;
            ins >> tmp_tile;
            fill.tiles[countx-1].emplace_back(tmp_tile);
            county++;
            std::getline(ins,line);
        }

    }
    catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }
    return ins;
}

Map::~Map() {
    tiles.clear();
}

bool operator==(const Map & lhs, const Map & rhs) {
    if (lhs.get_x() != rhs.get_x() || lhs.get_y() != rhs.get_y()) {
        return false;
    }
    for (int i = 0; i < lhs.get_x();i++) {
        for (int j = 0; j < lhs.get_y();j++) {
            if (lhs.get_tiles_const()[i][j] != rhs.get_tiles_const()[i][j]) {
                return false;
            }
        }
    }
    return true;
}