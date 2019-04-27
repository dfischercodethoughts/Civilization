//
// Created by david on 3/29/2019.
//

#include "main.h"
#include "Texture.h"

GLdouble width, height;
int wd;

static Draw_Manager *dm = nullptr;


void init() {
    width = 1920;
    height = 1066;

    dm = (new Draw_Manager(height,width,8,8));

    //do map things to game here
    TextureManager::Register(Tile_Terrain::terrain_to_string(Tile_Terrain::GRASSLAND).c_str(), Texture("assets\\grassland.png"));
    TextureManager::Register(Tile_Terrain::terrain_to_string(Tile_Terrain::HILL).c_str(), Texture("assets\\hill.png"));
    TextureManager::Register(Tile_Terrain::terrain_to_string(Tile_Terrain::MOUNTAIN).c_str(), Texture("assets\\mountain.png"));
    TextureManager::Register(Tile_Terrain::terrain_to_string(Tile_Terrain::WATER).c_str(), Texture("assets\\water.png"));

    TextureManager::Register(Tile_Resource::resource_to_string(Tile_Resource::WHEAT).c_str(), Texture("assets\\wheat.png"));
    TextureManager::Register(Tile_Resource::resource_to_string(Tile_Resource::GAZELLE).c_str(), Texture("assets\\gazelle.png"));
    TextureManager::Register(Tile_Resource::resource_to_string(Tile_Resource::FISH).c_str(), Texture("assets\\fish.png"));
    TextureManager::Register(Tile_Resource::resource_to_string(Tile_Resource::STONE).c_str(), Texture("assets\\stone.png"));
    TextureManager::Register(Tile_Resource::resource_to_string(Tile_Resource::WOODS).c_str(), Texture("assets\\wood.png"));
    TextureManager::Register(Tile_Resource::resource_to_string(Tile_Resource::IRON).c_str(), Texture("assets\\iron.png"));
    TextureManager::Register(Tile_Resource::resource_to_string(Tile_Resource::SILVER).c_str(), Texture("assets\\silver.png"));
    TextureManager::Register(Tile_Resource::resource_to_string(Tile_Resource::GOLD).c_str(), Texture("assets\\gold.png"));

    TextureManager::Register(Unit::unit_type_to_string(Unit::ARCHER).c_str(), Texture("assets\\archer.png"));
    TextureManager::Register(Unit::unit_type_to_string(Unit::SCOUT).c_str(), Texture("assets\\scout.png"));
    TextureManager::Register(Unit::unit_type_to_string(Unit::WARRIOR).c_str(), Texture("assets\\warrior.png"));
    TextureManager::Register(Unit::unit_type_to_string(Unit::SETTLER).c_str(), Texture("assets\\settler.png"));
    TextureManager::Register(Unit::unit_type_to_string(Unit::BOAT).c_str(), Texture("assets\\boat.png"));
    TextureManager::Register(Unit::unit_type_to_string(Unit::HORSEMAN).c_str(), Texture("assets\\horseman.png"));
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /*
     * Draw here
     */
    dm->draw();


    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{

    // escape
    if (key == 27) {

        if (dm->get_current_screen()->get_type() == Screen::PAUSE_SCREEN) {
            dm->set_screen(Screen::MAIN_GAME);
        }
        else if (dm->get_current_screen()->get_type() == Screen::MAIN_GAME) {
            dm->set_screen(Screen::PAUSE_SCREEN);
        }
    }
    //C or c
    else if ((key == 67 || key == 99) && dm->get_current_screen()->get_type() == Screen::MAIN_GAME) {
        dm->clear_active();
    }

    glutPostRedisplay();

    return;
}

void kbdS(int key, int x, int y) {


    switch(key) {
        case GLUT_KEY_DOWN:

            break;
        case GLUT_KEY_LEFT:

            break;
        case GLUT_KEY_RIGHT:

            break;
        case GLUT_KEY_UP:

            break;
    }

    glutPostRedisplay();

    return;
}

void cursor(int x, int y) {


    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if (state == GLUT_UP) {
        int res = dm->process_click(Coordinate(x, y));
        if (res == -1) {
            glutDestroyWindow(wd);
            exit(0);
        }
    }

    glutPostRedisplay();
}

void timer(int extra) {

    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(0, 0); // Position the window relative to top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Civilization!" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 5;
}
