
#include<SFML/Graphics.hpp>

#include "../Game.h"
#include "../Square.h"
#include "gtest/gtest.h"

class GameFixture : public ::testing::Test {

protected:
    virtual void SetUp() {
        g.createWindow(1000, 1000, "test");
        entity = new Square(50, sf::Color::Green);
        g.addEntity(entity);
    }
    virtual void TearDown(){
        delete entity;
    }
    Game g;
    Square* entity;
};

TEST_F(GameFixture, TestCreateWindow){
    ASSERT_EQ(1000, g.getWidth());
    ASSERT_EQ(1000, g.getHeight());
    ASSERT_EQ("test",g.getTitle());
}

TEST_F(GameFixture, TestAddEntity){
    ASSERT_EQ(entity, g.getEntity(0));
}