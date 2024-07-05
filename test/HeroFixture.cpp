#include <gtest/gtest.h>
#include "../Hero.h"
#include "../GridNode.h"

class HeroTest : public ::testing::Test {
protected:
    Hero* hero;

    void SetUp() override {
        hero = new Hero(100.0f, 200.0f, 3.0f, "../../img/hero.png");
    }
    void TearDown() override{
        delete hero;
    }
};

TEST_F(HeroTest, Constructor) {
    EXPECT_FLOAT_EQ(hero->getPosX(), 100.0f);
    EXPECT_FLOAT_EQ(hero->getPosY(), 200.0f);
    EXPECT_FLOAT_EQ(hero->getSpeed(), 3.0f);
}

TEST_F(HeroTest, MovesToNewPosition) {
    hero->move(150.0f, 250.0f);
    ASSERT_FLOAT_EQ(hero->getPosX(), 101.54349);
    ASSERT_FLOAT_EQ(hero->getPosY(), 202.57248);

}


TEST_F(HeroTest, MoveReturnFalse) {
    bool result = hero->move(constants::SCREEN_HEIGHT + 10.0f, constants::SCREEN_WIDTH + 10.f); //C'è una collisione
    ASSERT_FALSE(result);
}


