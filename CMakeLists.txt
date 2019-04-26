cmake_minimum_required(VERSION 3.13)
project(MaroonTeam)

if (WIN32)

    set(FREEGLUT_INCLUDE_DIRS "C:/Program\ Files/Common\ Files/freeglut/include")
    set(FREEGLUT_LIBRARY_DIRS "C:/Program\ Files/Common\ Files/freeglut/lib")
    find_library(winmm_LIBRARY_PATH winmm)
endif (WIN32)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wno-deprecated -Wreturn-type -Werror")

find_package (OpenGL REQUIRED)

if (APPLE)
    find_package(GLUT REQUIRED)
endif (APPLE)
if (UNIX)
    find_package(GLUT REQUIRED)
endif (UNIX)

if (WIN32)
    include_directories(${OPENGL_INCLUDE_DIR}  ${FREEGLUT_INCLUDE_DIRS})
    link_directories(${FREEGLUT_LIBRARY_DIRS})
elseif (APPLE)
    include_directories(${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIRS})
elseif (UNIX)
    include_directories(${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIRS})
endif ()

file(GLOB SOURCE_FILES
        *.cpp
        *.h
        )

add_executable(main.cpp main.h main.cpp Validator.h Validator.cpp Game.cpp Game.h Piece.cpp Piece.h Coordinate.cpp
        Coordinate.h Color.cpp Color.h Square.cpp Square.h Unit.cpp Unit.h Tile.cpp Tile.h Draw_Manager.cpp
        Draw_Manager.h Main_Screen.cpp Main_Screen.h Map.cpp Map.h Civilization.cpp Civilization.h Civilization_Name.cpp
        Civilization_Name.h Screen.cpp Screen.h Tile_Terrain.h Tile_Terrain.cpp End_Screen.cpp End_Screen.h Pause_Screen.cpp
        Pause_Screen.h Building.h Building.cpp Start_Screen.cpp Start_Screen.h Tile_Resource.h Tile_Resource.cpp Turn_Manager.h
        Turn_Manager.cpp Turn_Phase.h  Turn_Phase.cpp  Tile_Output.h Tile_Output.cpp Base_Resource.h Base_Resource.cpp
        Base_Resource_Package.h Base_Resource_Package.cpp City.cpp Building_Name.h Building_Name.cpp Build_Menu.cpp
        Build_Menu.h Texture.h Texture.cpp)

if (WIN32)
    target_link_libraries (main.cpp ${OPENGL_LIBRARIES} freeglut)
    target_link_libraries(main.cpp ${winmm_LIBRARY_PATH})
elseif (APPLE)
    target_link_libraries (main.cpp ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
elseif (UNIX)
    target_link_libraries (main.cpp ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
endif ()
