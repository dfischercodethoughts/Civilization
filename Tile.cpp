//
// Created by david on 4/3/2019.
//

#include "Tile.h"

int Tile::num_tiles = 0;

Tile::Tile():
Piece(Piece::TILE)
{
    num_tiles++;
    init(Tile_Terrain::DEFAULT,Tile_Resource::DEFAULT,nullptr,false);
}

Tile::Tile(Tile *cp):
Piece(cp->get_center(),cp->get_height(),cp->get_width(),cp->get_fill(),cp->get_text_color(),Piece::TILE)
{
    num_tiles++;
    init(cp->get_terrain(),cp->get_resource(),cp->get_const_unit(),cp->is_visible(),cp->get_id());
}

Tile::Tile(const Tile *cp):
        Piece(cp->get_center(),cp->get_height(),cp->get_width(),cp->get_fill(),cp->get_text_color(),Piece::TILE)
{
    num_tiles++;
    init(cp->get_terrain(),cp->get_resource(),cp->get_const_unit(),cp->is_visible(),cp->get_id());
}


Tile::Tile(const Tile & cp):
Piece(cp.get_center(),cp.get_height(),cp.get_width(),cp.get_fill(),cp.get_text_color(),Piece::TILE)
{
    num_tiles++;
    init(cp.get_terrain(),cp.get_resource(),cp.get_const_unit(),cp.is_visible(),cp.get_id());
}

Tile::Tile(std::unique_ptr<Tile> cp):
Piece(Piece::TILE)
{
    num_tiles++;
    init(cp->get_terrain(),cp->get_resource(),cp->get_const_unit(),cp->is_visible(),cp->get_id());
}

Tile::Tile(std::string ter, std::string res):
Piece(Piece::TILE)
{
    num_tiles++;
    init(Tile_Terrain::string_to_terrain(ter),Tile_Resource::string_to_resource(res),nullptr,false);
}

Tile::Tile(Tile_Terrain::names ter,Tile_Resource::names res):
Piece(Piece::TILE)
{
    num_tiles++;
    init(ter,res,nullptr,false);
}

Tile::Tile(std::string ter, std::string res, Unit & u):
Piece(u.get_center(),u.get_height(),u.get_width(),u.get_fill(),u.get_text_color(),Piece::TILE){
    num_tiles++;
    init(Tile_Terrain::string_to_terrain(ter),Tile_Resource::string_to_resource(res),&u,false);
}

Tile::Tile(Tile_Terrain::names ter,Tile_Resource::names res, Unit & u):
Piece(u.get_center(),u.get_height(),u.get_width(),u.get_fill(),u.get_text_color(),Piece::TILE) {
    num_tiles++;
    init(ter,res,unit,false);
}

Tile::Tile(Tile_Terrain::names nm):
Piece(Piece::TILE)
{
    num_tiles++;
    init(nm,Tile_Resource::DEFAULT,nullptr,false);
}

Tile::Tile(std::string ter, std::string res, std::shared_ptr<Unit> & u):
Piece(u->get_center(),u->get_height(),u->get_width(),u->get_fill(),u->get_text_color(),Piece::TILE)
{
    num_tiles++;
    init(Tile_Terrain::string_to_terrain(ter),Tile_Resource::string_to_resource(res),&*u,false);
}

Tile::Tile(Tile_Terrain::names ter,Tile_Resource::names res, std::shared_ptr<Unit> & u):
Piece(u->get_center(),u->get_height(),u->get_width(),u->get_fill(),u->get_text_color(),Piece::TILE) {
    num_tiles++;
    init(ter,res,&*u,false);
}

Tile::Tile(Coordinate cnt, int h, int w, Color fill, Color text, Tile_Terrain::names ter,Tile_Resource::names res):
Piece(cnt,h,w,fill,text,Piece::TILE)
{
    num_tiles++;
    init(ter,res,nullptr,false);
}

Tile::Tile(Coordinate cnt, int h, int w, Color fill, Color text, Tile_Terrain::names ter,Tile_Resource::names res,int i):
        Piece(cnt,h,w,fill,text,Piece::TILE)
{
    num_tiles++;
    init(ter,res,nullptr,false);
}

Tile::Tile(Coordinate cnt, int h, int w, Color fill, Color text, Tile_Terrain::names ter,Tile_Resource::names res,bool vis):
        Piece(cnt,h,w,fill,text,Piece::TILE)
{
    num_tiles++;
    init(ter,res,nullptr,vis);
}

void Tile::init(Tile_Terrain::names ter, Tile_Resource::names res, Unit * u, bool vis) {
    terrain = ter;
    resource = res;
    unit = &*u;
    if(vis) {
        this->reveal();
    }
    else {
        this->hide();
    }
    id = get_num_tiles();
}

void Tile::init(Tile_Terrain::names ter, Tile_Resource::names res, Unit * u, bool vis, int i) {
    terrain = ter;
    resource = res;
    unit = &*u;
    if(vis) {
        this->reveal();
    }
    else {
        this->hide();
    }
    id = i;
}

int Tile::get_num_tiles() {
    return Tile::num_tiles;
}

void Tile::increment_num_tiles() {
    Tile::num_tiles = Tile::num_tiles+1;
}

void Tile::init_id() {
    Tile::num_tiles = 0;
}

Square Tile::get_base_square() const {
    Square toret(this->get_center(),this->get_fill(),this->get_text_color(),this->get_height(),this->get_width(),this->get_message(),this->is_visible());
    toret.set_x_offset(this->get_x_offset());
    toret.set_y_offset(this->get_y_offset());
    return toret;
}

void Tile::set_base_square(Square set) {
    this->set_center(set.get_center());
    this->set_y_offset(set.get_y_offset());
    this->set_x_offset(set.get_x_offset());
    this->set_fill(set.get_fill());
    this->set_text_color(set.get_text_color());
    this->set_width(set.get_width());
    this->set_height(set.get_height());
    this->set_message(set.get_message());
    if (set.is_visible()) {
        this->reveal();
    }
    else {
        this->hide();
    }
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
    return unit;
}

void Tile::set_unit(Unit &newu) {
    unit = &newu;
}

void Tile::set_unit(Unit *newu) {
    unit = newu;
}

void Tile::set_background_square(Square set) {
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

void Tile::draw() const {
    //draw T: terrain
    //     R: resource
    //     U: unit_type
    if (is_visible()) {
        std::string line;
        if (this->has_unit()) {
            Square(get_center(), Colors::YELLOW, Colors::BLACK, get_height(), get_width(), "", true).draw();
            glColor3f(Colors::BLACK.get_red(), Colors::BLACK.get_green(), Colors::BLACK.get_blue());
            glRasterPos2i(this->get_center().x - (3 * this->get_width() / 8),
                          this->get_center().y + this->get_height() / 3);

            Unit::Unit_Type type = get_const_unit()->get_unit_type();
            line = "U: " + Unit::unit_type_to_string(type);
            for (char c: line) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }
        } else {
            Square(get_center(), Colors::WHITE, Colors::BLACK, get_height(), get_width(), "", true).draw();
        }



        line = "T: ";
        glColor3f(Colors::BLACK.get_red(), Colors::BLACK.get_green(), Colors::BLACK.get_blue());
        glRasterPos2i(this->get_center().x - (3 * this->get_width() / 8),
                      this->get_center().y - this->get_height() / 3);
        line += Tile_Terrain::terrain_to_string(this->get_terrain());
        for (char c: line) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }

        glColor3f(Colors::BLACK.get_red(), Colors::BLACK.get_green(), Colors::BLACK.get_blue());
        glRasterPos2i(this->get_center().x - (3 * this->get_width() / 8), this->get_center().y);
        line = "R: " + Tile_Resource::resource_to_string(this->get_resource());
        for (char c: line) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }
    }

    //if not visible print black square
    else {
        Square(get_center(),Colors::BLACK,Colors::WHITE,get_height(),get_width(),"",true).draw();
    }
}

void Tile::draw_on_viewport(Square viewport_base) {
    viewport_base.draw();
    std::string line = "";
    glColor3f(Colors::BLACK.get_red(),Colors::BLACK.get_green(),Colors::BLACK.get_blue());
    glRasterPos2i(viewport_base.get_center().x-3*viewport_base.get_width()/8,viewport_base.get_center().y-3*viewport_base.get_height()/8);
    line += "TERRAIN TYPE: " + Tile_Terrain::terrain_to_string(terrain);
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,c);
    }

    glColor3f(Colors::BLACK.get_red(),Colors::BLACK.get_green(),Colors::BLACK.get_blue());
    glRasterPos2i(viewport_base.get_center().x-3*viewport_base.get_width()/8,viewport_base.get_center().y);
    line = "RESOURCE TYPE: " + Tile_Resource::resource_to_string(resource);
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,c);
    }

    glColor3f(Colors::BLACK.get_red(),Colors::BLACK.get_green(),Colors::BLACK.get_blue());
    glRasterPos2i(viewport_base.get_center().x-3*viewport_base.get_width()/8,viewport_base.get_center().y+3*viewport_base.get_height()/8);
    line = "MOVEMENT COST: "+std::to_string(Tile_Terrain::get_movement_cost(terrain));
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,c);
    }
}

std::ostream & operator<<(std::ostream & outs, const Tile & print) {
    std::string line = "TILE\n";
    outs << line;
    outs << print.get_base_square();

    line =Tile_Terrain::terrain_to_string(print.terrain) + "\n" + Tile_Resource::resource_to_string(print.resource) +
            "\n" + std::to_string(print.id);
    //todo: add building to tile output (before id output)
    outs << line << std::endl;
    return outs;
}

std::istream & operator>>(std::istream & ins, Tile & fill) {
    try {
        //assume "TILE\n" already read
        fill.set_type(Piece::TILE);
        Square base;
        ins >> base;
        fill.set_base_square(base);

        std::string line = "";

        //read terrain
        std::getline(ins, line);
        fill.terrain = Tile_Terrain::string_to_terrain(line);

        //read resource
        std::getline(ins,line);
        fill.resource = Tile_Resource::string_to_resource(line);

        //todo:add building input to tile

        std::getline(ins,line);
        fill.id = std::stoi(line);

    }
    catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }
    return ins;
}

Tile & Tile::operator=(const Tile & rhs) {
    //todo:add set building to tile overloaded equals operator
    set_center(rhs.get_center());
    set_height(rhs.get_height());
    set_width(rhs.get_width());
    set_text_color(rhs.get_text_color());
    set_fill(rhs.get_fill());
    set_message(rhs.get_message());
    init(rhs.get_terrain(),rhs.get_resource(),rhs.get_const_unit(),rhs.is_visible(),rhs.get_id());
    return *this;
}

bool Tile::operator==(Tile const & rhs) const {
    //todo: add building to tile equality
    if ((get_id() == rhs.get_id()) && (terrain == rhs.get_terrain()) &&
            (resource == rhs.get_resource())) {
        return true;
    }
    return false;
}

bool Tile::operator!=(Tile const & rhs) const {
    if (!(*this == rhs)) {
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
    reveal();
    num_tiles--;
}