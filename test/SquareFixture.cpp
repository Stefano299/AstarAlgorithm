//
// Created by stefano on 7/2/24.
//

#include "gtest/gtest.h"
#include "../Square.h"
#include"../constants.h"

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
    EXPECT_EQ(square->getType(), Type::Basic);
}

TEST_F(SquareTest, GetShape) {
    sf::RectangleShape shape = square->getShape();
    EXPECT_TRUE(shape.getFillColor() == sf::Color::White);
}

TEST_F(SquareTest, GetSize) {
    EXPECT_EQ(square->getSize(), constants::SQUARE_SIZE);
}

TEST_F(SquareTest, GetColor) {
    EXPECT_EQ(square->getColor(), sf::Color::White);
}

TEST_F(SquareTest, SetTypeAndGetType) {
    square->setType(Type::Obstacle);
    EXPECT_EQ(square->getType(), Type::Obstacle);
}

TEST_F(SquareTest, SetPosPositive) {
    square->setPos(5, 7);
    EXPECT_EQ(square->getX(), 5);
    EXPECT_EQ(square->getY(), 7);
}

TEST_F(SquareTest, SetPosNegative) {
    EXPECT_THROW(square->setPos(-3, -4),std::out_of_range);
}