cmake_minimum_required(VERSION 3.26)
project(Astar)

set(CMAKE_CXX_STANDARD 11)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_subdirectory(test)

set(SOURCE_FILES main.cpp
        Square.cpp
        Square.h
        SquareGrid.cpp
        SquareGrid.h
        constants.h
        GridNode.cpp
        GridNode.h
        astar/stlastar.h
        astar/fsa.h
        Grid.h
        NumberGrid.cpp
        NumberGrid.h
        Grid.cpp
        GameCharacter.cpp
        GameCharacter.h
        Hero.cpp
        Hero.h
        Enemy.cpp
        Enemy.h
        exceptions.h)

# Link alle librerie Astar
add_executable(Astar ${SOURCE_FILES}
        Path.cpp
        Path.h
)

add_library(core ${SOURCE_FILES})
target_link_libraries(Astar sfml-graphics sfml-window sfml-system sfml-network sfml-audio core)
