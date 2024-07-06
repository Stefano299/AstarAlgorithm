cmake_minimum_required(VERSION 3.26)
project(Astar)

set(CMAKE_CXX_STANDARD 11)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

include_directories(headers/)

set(SOURCE_FILES main.cpp
        Square.cpp
        headers/Square.h
        SquareGrid.cpp
        headers/SquareGrid.h
        headers/constants.h
        GridNode.cpp
        headers/GridNode.h
        astar/stlastar.h
        astar/fsa.h
        headers/Grid.h
        NumberGrid.cpp
        headers/NumberGrid.h
        Grid.cpp
        GameCharacter.cpp
        headers/GameCharacter.h
        Hero.cpp
        headers/Hero.h
        Enemy.cpp
        headers/Enemy.h
        headers/exceptions.h
        Path.cpp
        headers/Path.h)

# Link alle librerie Astar
add_executable(Astar ${SOURCE_FILES}

)

add_library(core ${SOURCE_FILES})
target_link_libraries(Astar sfml-graphics sfml-window sfml-system sfml-network sfml-audio core)
