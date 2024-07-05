//
// Created by stefano on 7/4/24.
//

#include"gtest/gtest.h"
#include"../Enemy.h"

class EnemyFixture : public ::testing::Test {
protected:
    Enemy* enemy;

    void SetUp() override {
        enemy = new Enemy(100.0f, 200.0f, 2.5f, "../../img/enemy.png");
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
    Enemy enemy(100.0f, 200.0f, 2.5f, "../../img/enemy.png");
    enemy.move(150.0f, 250.0f);
    ASSERT_FLOAT_EQ(enemy.getPosX(), 101.29144);
    ASSERT_FLOAT_EQ(enemy.getPosY(), 202.14061);
}


