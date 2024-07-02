#include "gtest/gtest.h"
#include "../Square.h"
#include "../constants.h"

class GridTest : public ::testing::Test {
protected:
    Grid* grid;

    void SetUp() override {
        grid = new Grid;
    }

    void TearDown() override {
        delete grid;
    }
};

TEST_F(GridTest, DefaultConstructor) {
    EXPECT_EQ(grid->getHeight(), constants::GRID_SIZE);
    EXPECT_EQ(grid->getHeight(), constants::GRID_SIZE);
}

TEST_F(GridTest, SquaresGeneration){
    EXPECT_EQ(7, grid->getSquare(7, 3).getX());
}

TEST_F(GridTest, GetSquareException) {
    EXPECT_THROW(grid->getSquare(-1, 0), std::out_of_range);
}