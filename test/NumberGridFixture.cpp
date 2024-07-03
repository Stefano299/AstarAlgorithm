#include "gtest/gtest.h"
#include "../NumberGrid.h"
#include"../Square.h"

class NumberGridTest : public ::testing::Test {
protected:
    NumberGrid* numberGrid;

    void SetUp() override {
        numberGrid = new NumberGrid();
    }

    void TearDown() override {
        delete numberGrid;
    }
};

TEST_F(NumberGridTest, ChangeElementTypeToObstacle) {    //Così testo anche getNumber
    numberGrid->changeElementType(1, 2, Type::Obstacle);
    EXPECT_EQ(numberGrid->getNummber(1, 2), 9);
}

TEST_F(NumberGridTest, ChangeElementTypeToBasic) {
    numberGrid->changeElementType(3, 4, Type::Basic);
    EXPECT_EQ(numberGrid->getNummber(3, 4), 1);
}

TEST_F(NumberGridTest, GetNumberExceptione) {
    EXPECT_THROW(numberGrid->getNummber(-1, 0), std::out_of_range);
}