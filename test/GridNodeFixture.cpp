#include <gtest/gtest.h>
#include "../headers/GridNode.h"

class GridNodeTest : public ::testing::Test {
protected:
    void SetUp() override {
        NumberGrid numberGrid(10, 10);
    }
};

TEST_F(GridNodeTest, GoalDistanceEstimate) {
    GridNode nodeStart(0, 0);
    GridNode nodeGoal(3, 4);
    float distance = nodeStart.GoalDistanceEstimate(nodeGoal);
    ASSERT_FLOAT_EQ(distance, 5.0); // Dovrebbe essere 5 per il teorema di Pitagora
}

TEST_F(GridNodeTest, NodeCost) {
    GridNode node(0, 0);
    GridNode nodeSuccessor(1, 0);
    float cost = node.GetCost(nodeSuccessor);
    ASSERT_EQ(cost, sqrt(1)); // Dovrebbe essere 5 per il teorema di Pitagora
}


TEST_F(GridNodeTest, NodeCostDiagonal) {
    GridNode node(0, 0);
    GridNode nodeSuccessor(1, 1);
    float cost = node.GetCost(nodeSuccessor);
    ASSERT_FLOAT_EQ(cost, sqrt(2)); // Dovrebbe essere 5 per il teorema di Pitagora
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
