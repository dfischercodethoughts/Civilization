//
// Created by david on 4/3/2019.
//

#include "Map.h"

void Map::make_visible(std::vector<Tile *> &to) {
    for (Tile * tl :to) {
        tl->reveal();
    }
}

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

Map::Map()
{
    tiles = std::vector<std::vector<Tile>>();
}

Coordinate Map::get_vector_coordinates_from_click(Coordinate click) {
    Coordinate to_ret(0,0);
    if (click.x > 0 && click. x < this->get_width() && click.y > 0 && click.y < this->get_height()) {
        to_ret.x = click.x / Tile::TILE_WIDTH;
        to_ret.y = click.y/Tile::TILE_HEIGHT;
    }
    return to_ret;
}

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

}

void Map::remove_duplicates(std::vector<Tile *> & list) {
    // potentially more efficient?
    std::set<Tile*> unique_set;
    for (int i = 0; i < list.size()-1;i++) {
        unique_set.emplace(&*list[i]);
    }

    list.clear();
    for (auto i = unique_set.begin();i!= unique_set.end();i++) {
        list.push_back(*i);
    }

}

std::vector<Tile *>& Map::get_tiles_driver(std::vector<Tile*> &cur_list,Tile & start, int move_left) {
    Coordinate vec = get_vector_coordinates_from_click(start.get_center());
    if (move_left > 0) {
        cur_list.emplace_back(&start);
        Tile * btm_lf = get_tile_from_vector_coordinates({vec.x-1,vec.y-1});
        Tile * left = get_tile_from_vector_coordinates({vec.x-1,vec.y});
        Tile * top_lf = get_tile_from_vector_coordinates({vec.x-1,vec.y+1});
        Tile * top = get_tile_from_vector_coordinates({vec.x,vec.y+1});
        Tile * btm = get_tile_from_vector_coordinates({vec.x,vec.y-1});
        Tile * top_rt = get_tile_from_vector_coordinates({vec.x+1,vec.y+1});
        Tile * rt = get_tile_from_vector_coordinates({vec.x+1,vec.y});
        Tile * btm_rt = get_tile_from_vector_coordinates({vec.x+1,vec.y-1});

        if(btm_lf != nullptr) {
            cur_list = get_tiles_driver(cur_list, *btm_lf, move_left - Tile_Terrain::get_movement_cost(start.get_terrain()));
        }
        if (left != nullptr) {
            cur_list = get_tiles_driver(cur_list, *left, move_left - Tile_Terrain::get_movement_cost(start.get_terrain()));
        }
        if (top_lf != nullptr) {
            cur_list = get_tiles_driver(cur_list,*top_lf,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
        }
        if (btm != nullptr) {
            cur_list = get_tiles_driver(cur_list,*btm,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
        }
        if (top != nullptr) {
            cur_list = get_tiles_driver(cur_list,*top,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
        }
        if (top_rt != nullptr) {
            cur_list = get_tiles_driver(cur_list,*top_rt,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
        }
        if (rt != nullptr) {
            cur_list= get_tiles_driver(cur_list,*rt,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
        }
        if (btm_rt != nullptr) {
            cur_list = get_tiles_driver(cur_list,*btm_rt,move_left-Tile_Terrain::get_movement_cost(start.get_terrain()));
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

std::vector<Tile *> Map::get_tiles_within_range(Tile * start, int movement) {
    std::vector<Tile*> to_ret = std::vector<Tile*>();
    to_ret= get_tiles_driver(to_ret,*start,movement);
    //remove_duplicates(to_ret);
    return to_ret;
}

bool Map::is_adjacent(Tile & first, Tile & second){
    Coordinate first_coord = get_vector_coordinates_from_click(first.get_center());
    Coordinate second_coord = get_vector_coordinates_from_click(first.get_center());

    if (abs(first_coord.x - second_coord.x) <= 1) {
        if (abs(second_coord.y - first_coord.y) <= 1) {
            return true;
        }
    }
    return false;
}

void Map::reveal(std::vector<Unit *> units) {
    hide_map();
    for (int  i = 0; i < units.size();i++) {
        std::vector<Tile * > visible_tiles =std::vector<Tile *>();
        visible_tiles = get_tiles_within_range(get_tile_from_id(units[i]->get_location_id()),Unit::get_max_movement(units[i]->get_unit_type()));
        make_visible(visible_tiles);
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
            //temporary vector of tiles
            std::vector<Tile> * tmp = new std::vector<Tile>();
            for (int j = 0; j < cp.tiles[0].size(); j++) {//this assumes square grid...
                tmp->emplace_back(cp.tiles[i][j]);
            }
            tiles.emplace_back(*tmp);
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


}

Map::~Map() {
    tiles.clear();
}