//
// Created by david on 4/3/2019.
//

#include "Tile.h"
int Tile::num_tiles;

Tile::Tile():
Piece(Piece::TILE)
{
    init(Tile_Terrain::DEFAULT,Tile_Resource::DEFAULT,nullptr,true);
}

Tile::Tile(Tile *cp):
Piece(cp->get_center(),cp->get_height(),cp->get_width(),cp->get_fill(),cp->get_text_color(),Piece::TILE)
{
    init(cp->get_terrain(),cp->get_resource(),cp->get_const_unit(),true);
}

Tile::Tile(const Tile & cp):
Piece(cp.get_center(),cp.get_height(),cp.get_width(),cp.get_fill(),cp.get_text_color(),Piece::TILE)
        {
    init(cp.get_terrain(),cp.get_resource(),cp.get_const_unit(),true);
}

Tile::Tile(std::unique_ptr<Tile> cp):
Piece(Piece::TILE)
{
    init(cp->get_terrain(),cp->get_resource(),cp->get_const_unit(),true);
}

Tile::Tile(std::string ter, std::string res):
Piece(Piece::TILE)
{
    init(Tile_Terrain::string_to_terrain(ter),Tile_Resource::string_to_resource(res),nullptr,true);
}

Tile::Tile(Tile_Terrain::names ter,Tile_Resource::names res):
Piece(Piece::TILE)
{
    init(ter,res,nullptr,true);
}

Tile::Tile(std::string ter, std::string res, Unit & u):
Piece(u.get_center(),u.get_height(),u.get_width(),u.get_fill(),u.get_text_color(),Piece::TILE){
    init(Tile_Terrain::string_to_terrain(ter),Tile_Resource::string_to_resource(res),&u,true);
}

Tile::Tile(Tile_Terrain::names ter,Tile_Resource::names res, Unit & u):
Piece(u.get_center(),u.get_height(),u.get_width(),u.get_fill(),u.get_text_color(),Piece::TILE) {
    init(ter,res,unit,true);
}

Tile::Tile(Tile_Terrain::names nm):
Piece(Piece::TILE)
{
    init(nm,Tile_Resource::DEFAULT,nullptr,true);
}

Tile::Tile(std::string ter, std::string res, std::shared_ptr<Unit> & u):
Piece(u->get_center(),u->get_height(),u->get_width(),u->get_fill(),u->get_text_color(),Piece::TILE)
{
    init(Tile_Terrain::string_to_terrain(ter),Tile_Resource::string_to_resource(res),&*u,true);
}

Tile::Tile(Tile_Terrain::names ter,Tile_Resource::names res, std::shared_ptr<Unit> & u):
Piece(u->get_center(),u->get_height(),u->get_width(),u->get_fill(),u->get_text_color(),Piece::TILE) {
    init(ter,res,&*u,true);
}

Tile::Tile(Coordinate cnt, int h, int w, Color fill, Color text, Tile_Terrain::names ter,Tile_Resource::names res):
Piece(cnt,h,w,fill,text,Piece::TILE)
{
    init(ter,res,nullptr,true);
}

Tile::Tile(Coordinate cnt, int h, int w, Color fill, Color text, Tile_Terrain::names ter,Tile_Resource::names res,int i):
        Piece(cnt,h,w,fill,text,Piece::TILE)
{
    init(ter,res,nullptr,true,i);
}

void Tile::init(Tile_Terrain::names ter, Tile_Resource::names res, Unit * u, bool vis) {
    terrain = ter;
    resource = res;
    unit = &*u;
    visible = vis;
    id = num_tiles++;
}

void Tile::init(Tile_Terrain::names ter, Tile_Resource::names res, Unit * u, bool vis, int i) {
    terrain = ter;
    resource = res;
    unit = &*u;
    visible = vis;
    id = i;
}

int Tile::get_num_tiles() {
    return num_tiles;
}

void Tile::init_id() {
    num_tiles = 0;
}

Tile_Terrain::names Tile::get_terrain() const {
    return terrain;
}

Tile_Resource::names Tile::get_resource() const {
    return resource;
}

int Tile::get_id() const {
    return id;
}

void Tile::clear_unit() {
    unit = nullptr;
}

bool Tile::has_unit() const {
    if (unit != nullptr) {
        return true;
    }
    return false;
}

Unit* Tile::get_const_unit() const {
    return &*unit;
}

Unit* Tile::get_unit() {
    return &*unit;
}

void Tile::set_unit(Unit &newu) {
    unit = &newu;
}

void Tile::draw() {
    //draw T: terrain
    //     R: resource
    //     U: unit_type
    if (visible) {
        Square(get_center(),get_text_color(),get_fill(),get_height(),get_width(),get_message(),true).draw();
        std::string line = "T: ";
        glColor3f(this->get_text_color().get_red(),this->get_text_color().get_green(),this->get_text_color().get_blue());
        glRasterPos2i(this->get_center().x-(3*this->get_width()/8),this->get_center().y-this->get_height()/3);
        line += Tile_Terrain::terrain_to_string(this->get_terrain());
        for (char c: line) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
        }

        glRasterPos2i(this->get_center().x-(3*this->get_width()/8),this->get_center().y);
        line ="R: " + Tile_Resource::resource_to_string(this->get_resource());
        for (char c: line) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
        }

        if (this->has_unit()) {
            glRasterPos2i(this->get_center().x - (3 * this->get_width() / 8),
                          this->get_center().y + this->get_height() / 3);
            line = "U: " + Unit::unit_type_to_string(this->get_unit()->get_unit_type());
            for (char c: line) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }
        }
    }
    //if not visible print white square
    else {
        Square(get_center(),get_text_color(),{255,255,255},get_height(),get_width(),get_message(),true).draw();
    }
}

void Tile::draw_on_viewport(Square viewport_base) {
    viewport_base.draw();
    std::string line = "";
    glColor3f(get_text_color().get_red(),get_text_color().get_green(),get_text_color().get_blue());
    glRasterPos2i(viewport_base.get_center().x-3*viewport_base.get_width()/8,viewport_base.get_center().y-viewport_base.get_height()/8);
    line += "TERRAIN TYPE: " + Tile_Terrain::terrain_to_string(terrain);
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,c);
    }

    glColor3f(get_text_color().get_red(),get_text_color().get_green(),get_text_color().get_blue());
    glRasterPos2i(viewport_base.get_center().x-3*viewport_base.get_width()/8,viewport_base.get_center().y+viewport_base.get_height()/8);
    line = "RESOURCE TYPE: " + Tile_Resource::resource_to_string(resource);
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,c);
    }

    glColor3f(get_text_color().get_red(),get_text_color().get_green(),get_text_color().get_blue());
    glRasterPos2i(viewport_base.get_center().x-3*viewport_base.get_width()/8,viewport_base.get_center().y+3*viewport_base.get_height()/8);
    line = "MOVEMENT COST: "+std::to_string(Tile_Terrain::get_movement_cost(terrain));
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,c);
    }
}

Tile & Tile::operator=(const Tile & rhs) {
    id = rhs.get_id();
    set_center(rhs.get_center());
    set_height(rhs.get_height());
    set_width(rhs.get_width());
    set_text_color(rhs.get_text_color());
    set_fill(rhs.get_fill());
    set_message(rhs.get_message());
    init(rhs.get_terrain(),rhs.get_resource(),rhs.get_const_unit(),true);
    return *this;
}

bool Tile::operator==(Tile const & rhs) const {
    if ((get_center() == rhs.get_center()) & (terrain == rhs.get_terrain()) &
            (resource == rhs.get_resource())) {
        return true;
    }
    return false;
}

bool Tile::operator<(const Tile & rhs) const {
    return (get_id() < rhs.get_id());
}

Tile::~Tile() {
    id = -1;
    terrain = Tile_Terrain::DEFAULT;
    resource = Tile_Resource::DEFAULT;

    unit = nullptr;
    visible = true;
    num_tiles--;
}