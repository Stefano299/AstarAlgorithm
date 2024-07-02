//
// Created by stefano on 7/2/24.
//
#include "gtest/gtest.h"
#include "../Game.h"

class GameTest : public ::testing::Test {
protected:
    Game* game;

    void SetUp() override {
        game = new Game();
    }

    void TearDown() override {
        delete game;
    }
};

TEST_F(GameTest, CreateWindowAndGetters) {
    game->createWindow(800, 600, "Test Game");
    EXPECT_EQ(game->getWidth(), 800);
    EXPECT_EQ(game->getHeight(), 600);
    EXPECT_EQ(game->getTitle(), "Test Game");
}
