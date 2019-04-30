# Final_Proj_v2
Civilization
Welcome to our game of civilization!

We now have textures!

Your units will be highlighted in yellow on the screen! Make sure you have the required save files before starting a new game: "new_civs.save", "new_tm.save", and "new_map.save". These files are directly imported into the game upon loading and are required for the game to function (copies of them can be found in the cmake-build-debug folder here on the github).

Essentially, destroy your enemies and build the largest empire you can!

UNIT MOVEMENT

Units can move until they have no more movement (at least one square). Click on a tile to select it, and all pieces on it (cities, units). Units cannot move on top of other units. Land units cannot move to water tiles, and boats cannot move onto land tiles. 

A consequence of the unit move logic is, if a unit has at least one movement and tries to move onto a tile with greater cost (eg. mountain), your unit makes a herculean effort and climbs the mountain with the last of its movement.

Units can move across (but not onto) water, with a movement cost of one.

With a unit selected, select a tile to move there if the unit has enough movement to get there, or to select the tile if the unit does not. With a unit selected, click on a tile occupied by the enemy (within movement range) to move to the tile closest to the enemy, and initiate an attack.

There is a known bug in which the AI will move onto water tiles.

ATTACKING

Attacks will cause damage to both the attacking and defending units. Attack damage is based purely on the participating units' types.

There is a known bug with the logic that moves a unit before attacking when if attacking a unit more than one square away, and if the tile closest to the attacked unit is not able to be occupied by the attacking unit (eg. it is a water tile or occupied by a players unit), the attacking unit will cause damage both ways and then disappear from the board until the next turn, at which point it will reappear in the tile it was originally.

CITIES & BUILDING

Cities have a list of tiles in their zones of control. Each turn, a city collects resources from each of the tiles within its range (note that current build allows overlap of city territories, so a tile can be harvested by more than one city). Currently, gold acts as a vanity resource.

With a city selected, click on the build menu (which should appear in the lower pane of the screen). If the city can build the unit or building, the respective square in the build menu will be highlighted with a yellow fill. With a building and a city selected, click on a square in the city's zone of influence to build the selected unit. The production cost will be deducted from the active city's production pool.

Cities have a population level which determines the number of tiles in its control. The maximum population is 6. The food level to reach the next level follows the curve f(x) = x^3 + 40. Mountains and hills will cause the city to grow more slowly in that direction.

Cities have no defense and will be destroyed upon an enemy unit entering its tile.

The AI can build cities on player owned tiles (and will own the tile it is placed on), but cannot own or collect resources from player owned tiles.


HOTKEYS
Press *esc* to bring up the pause menu.
Press 'c' to clear all active selections.

BUILD INSTRUCTIONS
The build requirements and CMAKE lists requires customization to the machine.
We could not make the graphics appear on a machine running linux.
The game runs on opengl and freeglut. freeglut.dll should already be in the cmake-build-debug folder above; that file must be in the working directory. The CMakeLists.txt also requires that C:/Program Files/Common Files/freeglut/include/ and C:/Program Files/Common Files/freeglut/lib/ have the appropriate files in them. The include folder should have the GL/ folder and all files inside of it within it. For reference, this is freeglut.h, freeglut_ext.h, freeglut_std.h, and glut.h. If your architecture is x64, then inside of lib you should have the x64 folder with libfreeglut.a and libfreeglut_static.a inside it. If you have a x32 architecture, you will need the files of the same name in the base lib folder in the repo. If you have an x32 architecture, you will also most likely need to change the line in CMakeLists.txt that sets the FREEGLUT_LIBRARY_DIRS variable to the base /Common Files/freeglut/lib/. For my windows x64 architecture, pulling from the repo into a CLion project set up with Cygwin and the appropriate dependecies installed allows me to run and play the game.
