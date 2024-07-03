//
// Created by stefano on 7/3/24.
//

#include "gtest/gtest.h"
#include "../GameCharacter.h"
#include <SFML/Graphics.hpp>

class GameCharacterTest : public ::testing::Test {
protected:
    GameCharacter* character;
    sf::Texture texture;

    void SetUp() override {
        texture.create(25,25);
        // Assumendo che la texture sia caricata correttamente
        character = new GameCharacter(1, 1, texture, 5.0);
    }

    void TearDown() override {
        delete character;
    }
};

TEST_F(GameCharacterTest, ConstructorAndGetters) {
    EXPECT_EQ(character->getGridX(), 1);
    EXPECT_EQ(character->getGridY(), 1);
    EXPECT_FLOAT_EQ(character->getPosX(), 25.0f);
    EXPECT_FLOAT_EQ(character->getPosY(), 25.0f);
    EXPECT_FLOAT_EQ(character->getSpeed(), 5.0f);
}

TEST_F(GameCharacterTest, MoveBy){
    character->moveBy(1, 0);
    EXPECT_EQ(character->getPosX(), 25);
}