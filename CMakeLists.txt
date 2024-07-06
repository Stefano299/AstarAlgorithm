cmake_minimum_required(VERSION 3.26)
project(Astar)

set(CMAKE_CXX_STANDARD 11)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_subdirectory(test)

set(SOURCE_FILES sources/main.cpp
        sources/Square.cpp
        headers/Square.h
        sources/SquareGrid.cpp
        headers/SquareGrid.h
        headers/constants.h
        sources/GridNode.cpp
        headers/GridNode.h
        includes/stlastar.h
        includes/fsa.h
        headers/Grid.h
        sources/NumberGrid.cpp
        headers/NumberGrid.h
        sources/Grid.cpp
        sources/GameCharacter.cpp
        headers/GameCharacter.h
        sources/Hero.cpp
        headers/Hero.h
        sources/Enemy.cpp
        headers/Enemy.h
        headers/exceptions.h
        sources/Path.cpp
        headers/Path.h)

# Link alle librerie Astar
add_executable(Astar ${SOURCE_FILES}

)

add_library(core ${SOURCE_FILES})
target_link_libraries(Astar sfml-graphics sfml-window sfml-system sfml-network sfml-audio core)
