#include "gtest/gtest.h"
#include "../headers/NumberGrid.h"
#include"../headers/Square.h"
#include"../headers/exceptions.h"

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
    ASSERT_EQ(numberGrid->getNumber(1, 2), 9);
}

TEST_F(NumberGridTest, ChangeElementTypeToBasic) {
    numberGrid->changeElementType(3, 4, Type::Basic);
    ASSERT_EQ(numberGrid->getNumber(3, 4), 1);
}

TEST_F(NumberGridTest, GetNumberExceptione) {
    ASSERT_THROW(numberGrid->getNumber(-1, 0), invalid_coordinates);
}