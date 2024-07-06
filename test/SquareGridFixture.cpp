#include "gtest/gtest.h"
#include "../headers/Square.h"
#include "../headers/constants.h"
#include "../headers/SquareGrid.h"
#include"../headers/exceptions.h"

class SquareGridTest : public ::testing::Test {
protected:
    SquareGrid* grid;

    void SetUp() override {
        grid = new SquareGrid(constants::GRID_WIDTH,  constants::GRID_HEIGHT);
    }

    void TearDown() override {
        delete grid;
    }
};

TEST_F(SquareGridTest, DefaultConstructor) {
    ASSERT_EQ(grid->getHeight(), constants::GRID_HEIGHT);
    ASSERT_EQ(grid->getWidth(), constants::GRID_WIDTH);
}

TEST_F(SquareGridTest, SquaresGeneration){
    ASSERT_EQ(7, grid->getSquare(7, 3).getX());
}

TEST_F(SquareGridTest, GetSquareException) {
    ASSERT_THROW(grid->getSquare(-1, 0), invalid_coordinates);
}

TEST_F(SquareGridTest, GetElementType){
    grid->changeElementType(2, 4, Type::Obstacle);
    ASSERT_EQ(grid->getSquare(2, 4).getType(), Type::Obstacle);
}