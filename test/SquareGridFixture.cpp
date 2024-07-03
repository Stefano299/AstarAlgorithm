#include "gtest/gtest.h"
#include "../Square.h"
#include "../constants.h"
#include "../SquareGrid.h"

class SquareGridTest : public ::testing::Test {
protected:
    SquareGrid* grid;

    void SetUp() override {
        grid = new SquareGrid;
    }

    void TearDown() override {
        delete grid;
    }
};

TEST_F(SquareGridTest, DefaultConstructor) {
    EXPECT_EQ(grid->getHeight(), constants::GRID_SIZE);
    EXPECT_EQ(grid->getHeight(), constants::GRID_SIZE);
}

TEST_F(SquareGridTest, SquaresGeneration){
    EXPECT_EQ(7, grid->getSquare(7, 3).getX());
}

TEST_F(SquareGridTest, GetSquareException) {
    EXPECT_THROW(grid->getSquare(-1, 0), std::out_of_range);
}

TEST_F(SquareGridTest, GetElementType){
    grid->changeElementType(2, 4, Type::Obstacle);
    EXPECT_EQ(grid->getSquare(2, 4).getType(), Type::Obstacle);
}