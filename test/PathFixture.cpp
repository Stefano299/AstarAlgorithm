#include <gtest/gtest.h>
#include "../Path.h"
#include "../exceptions.h"
class PathFixture : public ::testing::Test {
protected:
    Path* path;
    void SetUp() override {
        path = new Path;
    }
    void TearDown() override{
        delete path;
    }
};

TEST_F(PathFixture, PathConstructor) {
    ASSERT_TRUE(path->getPath().empty());
    ASSERT_EQ(path->getIndex(), 0);
}

TEST_F(PathFixture, AddNodeIncreasesLength) {
    path->setPath({sf::Vector2i(1, 1)});
    ASSERT_EQ(1, path->getPath().size());
}

TEST_F(PathFixture, ResetIndex) {
    path->setPath({sf::Vector2i(1, 1), sf::Vector2i(2, 2)});
    path->nextNode(); // Advance the index
    path->reset();
    ASSERT_EQ(path->getElement(), sf::Vector2i(1, 1)); // Should return the first element
}

TEST_F(PathFixture, InvalidIndexThrowsException) {
    ASSERT_THROW(path->nextNode(), path_out_of_bound);
}


TEST_F(PathFixture, NextNode) {
    path->setPath({sf::Vector2i(1, 1), sf::Vector2i(2, 2)});
    path->nextNode();
    ASSERT_EQ(path->getElement(), sf::Vector2i(2, 2));
}

TEST_F(PathFixture, IsFinishedFalse) {
    path->setPath({sf::Vector2i(1, 1), sf::Vector2i(2, 2)});
    ASSERT_FALSE(path->isFinished());
}

TEST_F(PathFixture, IsFinishedTrue) {
    path->setPath({sf::Vector2i(1, 1)});
    path->nextNode(); // Advance to the end
    ASSERT_TRUE(path->isFinished());
}

TEST_F(PathFixture, GetElement) {
    path->setPath({sf::Vector2i(1, 1), sf::Vector2i(2, 2), sf::Vector2i(3, 3)});
    path->nextNode(); // Advance the index to 1
    ASSERT_EQ(path->getElement(), sf::Vector2i(2, 2));
}
