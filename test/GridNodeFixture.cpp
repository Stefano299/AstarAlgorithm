#include <gtest/gtest.h>
#include "../GridNode.h"

class GridNodeTest : public ::testing::Test {
protected:
    void SetUp() override {
        GridNode::worldGrid = new int[100]; // Assuming a 10x10 grid for simplicity
        for(int i = 0; i < 100; ++i) {
            GridNode::worldGrid[i] = 1; // Initialize all cells as non-obstacles
        }
    }

    void TearDown() override {
        delete[] GridNode::worldGrid;
    }
};

TEST_F(GridNodeTest, GoalDistanceEstimate) {
    GridNode nodeStart(0, 0);
    GridNode nodeGoal(3, 4);
    float distance = nodeStart.GoalDistanceEstimate(nodeGoal);
    ASSERT_FLOAT_EQ(distance, 5.0); // Dovrebbe essere 5 per il teorema di Pitagora
}

TEST_F(GridNodeTest, IsGoalTrue) {
    GridNode nodeStart(5, 5);
    GridNode nodeGoal(5, 5);
    ASSERT_TRUE(nodeStart.IsGoal(nodeGoal));
}

TEST_F(GridNodeTest, IsGoalFalse) {
    GridNode nodeStart(5, 5);
    GridNode nodeGoal(5, 6);
    ASSERT_FALSE(nodeStart.IsGoal(nodeGoal));
}


TEST_F(GridNodeTest, IsSameStateSameNodes) {
    GridNode node1(5, 5);
    GridNode node2(5, 5);
    ASSERT_TRUE(node1.IsSameState(node2));
}

TEST_F(GridNodeTest, IsSameStateDifferentNodes) {
    GridNode node1(5, 5);
    GridNode node2(6, 5);
    ASSERT_FALSE(node1.IsSameState(node2));
}

TEST_F(GridNodeTest, GetPath) {          //Controllo semplicemente che trovi una (qualsiasi) path
    GridNode nodeStart(0, 0);
    GridNode nodeEnd(5, 5);
    auto path = GridNode::getPath(nodeStart, nodeEnd);
    ASSERT_FALSE(path.empty());
}