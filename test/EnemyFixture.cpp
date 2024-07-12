//
// Created by stefano on 7/4/24.
//

#include"gtest/gtest.h"
#include"../headers/Enemy.h"

class EnemyFixture : public ::testing::Test {
protected:
    Enemy* enemy;

    void SetUp() override {
        enemy = new Enemy(100.0f, 200.0f, 2.5f, "../../assets/enemy.png");
    }
    void TearDown() override{
        delete enemy;
    }
};

TEST_F(EnemyFixture, EnemyConstructor) {
    ASSERT_EQ(enemy->getPosY(), 200.0f);
    ASSERT_EQ(enemy->getPosX(), 100.0f);
    ASSERT_EQ(enemy->getSpeed(), 2.5f);
}

TEST_F(EnemyFixture, EnemyMove) {
    Enemy enemy(100.0f, 200.0f, 2.5f, "../../assets/enemy.png");
    float pastX = enemy.getPosX();
    float pastY = enemy.getPosY();
    enemy.move(150.0f, 250.0f);
    ASSERT_TRUE(enemy.getPosX() > pastX);
    ASSERT_TRUE(enemy.getPosY() > pastY);
}


