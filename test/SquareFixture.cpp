//
// Created by stefano on 7/2/24.
//

#include "gtest/gtest.h"
#include "../headers/Square.h"
#include"../headers/constants.h"
#include"../headers/exceptions.h"

class SquareTest : public ::testing::Test {
protected:
    Square* square;

    void SetUp() override {
        square = new Square;
    }

    void TearDown() override {
        delete square;
    }
};

TEST_F(SquareTest, DefaultConstructor) {
    ASSERT_EQ(square->getType(), Type::Basic);
}

TEST_F(SquareTest, GetShape) {
    sf::RectangleShape shape = square->getShape();
    ASSERT_TRUE(shape.getFillColor() == sf::Color::White);
}

TEST_F(SquareTest, GetSize) {
    ASSERT_EQ(square->getSize(), constants::SQUARE_SIZE);
}


TEST_F(SquareTest, SetTypeAndGetType) {
    square->setType(Type::Obstacle);
    ASSERT_EQ(square->getType(), Type::Obstacle);
}

TEST_F(SquareTest, SetPosPositive) {
    square->setPos(5, 7);
    ASSERT_EQ(square->getX(), 5);
    ASSERT_EQ(square->getY(), 7);
}

TEST_F(SquareTest, SetPosNegative) {
    ASSERT_THROW(square->setPos(-3, -4), invalid_coordinates);
}