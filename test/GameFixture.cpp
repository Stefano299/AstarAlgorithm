#include<SFML/Graphics.hpp>

#include "gtest/gtest.h"

#include "../Game.h"
#include "../Entity.h"

class GameFixture : public ::testing::Test {

protected:
    virtual void SetUp() {
        g.createWindow(1000, 1000, "test");
        entity = new Entity(50, sf::Color::Green);
        g.addEntity(entity);
    }
    virtual void TearDown(){
        delete entity;
    }
    Game g;
    Entity* entity;
};

TEST_F(GameFixture, TestCreateWindow){
    ASSERT_EQ(1000, g.getWidth());
    ASSERT_EQ(1000, g.getHeight());
    ASSERT_EQ("test",g.getTitle());
}

TEST_F(GameFixture, TestAddEntity){
    ASSERT_EQ(entity, g.getEntity(0));
}