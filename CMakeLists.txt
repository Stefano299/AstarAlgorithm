cmake_minimum_required(VERSION 3.26)
project(Astar)

set(CMAKE_CXX_STANDARD 11)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_subdirectory(test)
set(SOURCE_FILES main.cpp
        Game.cpp
        Game.h
        GameSingleton.cpp
        GameSingleton.h
        Square.cpp
        Square.h
        Grid.cpp
        Grid.h
        constants.h
        GridNode.cpp
        GridNode.h
        stlastar.h
        fsa.h)

# Link alle librerie Astar
add_executable(Astar ${SOURCE_FILES}

)

add_library(core ${SOURCE_FILES})
target_link_libraries(Astar sfml-graphics sfml-window sfml-system sfml-network sfml-audio core)
