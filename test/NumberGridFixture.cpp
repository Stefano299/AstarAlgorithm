#include "gtest/gtest.h"
#include "../NumberGrid.h"
#include"../Square.h"
#include"../exceptions.h"

class NumberGridTest : public ::testing::Test {
protected:
    NumberGrid* numberGrid;

    void SetUp() override {
        numberGrid = new NumberGrid(20, 20);
    }

    void TearDown() override {
        delete numberGrid;
    }
};

TEST_F(NumberGridTest, ChangeElementTypeToObstacle) {    //Così testo anche getNumber
    numberGrid->changeElementType(1, 2, Type::Obstacle);
    EXPECT_EQ(numberGrid->getNumber(1, 2), 9);
}

TEST_F(NumberGridTest, ChangeElementTypeToBasic) {
    numberGrid->changeElementType(3, 4, Type::Basic);
    EXPECT_EQ(numberGrid->getNumber(3, 4), 1);
}

TEST_F(NumberGridTest, GetNumberExceptione) {
    EXPECT_THROW(numberGrid->getNumber(-1, 0), invalid_coordinates);
}