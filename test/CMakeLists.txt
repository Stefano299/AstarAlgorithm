cmake_minimum_required(VERSION 3.5)

project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(TEST_SOURCE_FILES runAllTests.cpp
        SquareGridFixture.cpp
        SquareFixture.cpp
        NumberGridFixture.cpp
        GameCharacterFixture.cpp
        GridNodeFixture.cpp
)
add_executable(runTests ${TEST_SOURCE_FILES})

target_link_libraries(runTests gtest gtest_main core sfml-graphics sfml-window sfml-system sfml-network sfml-audio)