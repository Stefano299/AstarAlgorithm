//
// Created by stefano on 7/3/24.
//

#include"gtest/gtest.h"
#include"../GameCharacter.h"

TEST(GameCharacter, SetInsideWindow){
    sf::Texture texture;
    texture.create(25,25);
    GameCharacter character(-100, 0, texture, 5.0);
    ASSERT_EQ(character.getPosX(), (float)constants::SQUARE_SIZE/2);
}