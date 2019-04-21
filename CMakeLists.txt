cmake_minimum_required(VERSION 3.13.0)

project(civ)

set (FREEGLUT_INCLUDE_DIRS "C:/Program\ Files/Common\ Files/freeglut/include")
set (FREEGLUT_LIBRARY_DIRS "C:/Program\ Files/Common\ Files/freeglut/lib/x64")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wno-deprecated")

find_package(OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIR} ${FREEGLUT_INCLUDE_DIRS} )
link_directories(${FREEGLUT_LIBRARY_DIRS})

file (GLOB SOURCE_FILES
        *.h
        *.cpp

        )
        
add_executable(main.cpp main.cpp Validator.h Game.cpp Game.h Piece.cpp Piece.h Coordinate.cpp Coordinate.h Color.cpp Color.h Square.cpp Square.h Unit.cpp Unit.h Tile.cpp Tile.h Draw_Manager.cpp Draw_Manager.h Main_Screen.cpp Main_Screen.h Map.cpp Map.h Civilization.cpp Civilization.h Civilization_Name.cpp Civilization_Name.h Screen.cpp Screen.h Tile_Terrain.h Tile_Terrain.cpp End_Screen.cpp End_Screen.h Pause_Screen.cpp Pause_Screen.h Building.h Building.cpp Start_Screen.cpp Start_Screen.h Tile_Resource.h Tile_Resource.cpp Turn_Manager.h Turn_Manager.cpp Turn_Phase.h  Turn_Phase.cpp  Tile_Output.h Tile_Output.cpp Base_Resource.h Base_Resource.cpp Base_Resource_Package.h Base_Resource_Package.cpp )

target_link_libraries( main.cpp ${OPENGL_LIBRARIES} freeglut )