#include "GridNode.h"

int GridNode::GetGrid(int x, int y) const {   //Se una coordinata è fuori dalla griglia è come se fosse un ostacolo
    if (x < 0 ||
        x >= constants::GRID_SIZE ||
        y < 0 ||
        y >= constants::GRID_SIZE) {
        return 9;
    }
    return worldGrid[(y * constants::GRID_SIZE) + x];
}


bool GridNode::IsSameState(GridNode &rhs) {
    // same state in a maze search is simply when (x,y) are the same
    if ((x == rhs.x) &&
        (y == rhs.y)) {
        return true;
    } else {
        return false;
    }

}

size_t GridNode::Hash() {
    size_t h1 = hash<float>{}(x);
    size_t h2 = hash<float>{}(y);
    return h1 ^ (h2 << 1);
}

void GridNode::PrintNodeInfo() {
    cout << "Nodo alla posizione: " << x << ", " << y << endl;
}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal.

float GridNode::GoalDistanceEstimate(GridNode &nodeGoal) {
    return sqrt((float) (x - nodeGoal.x) * (x - nodeGoal.x) + (float) (y - nodeGoal.y) * (y - nodeGoal.y));
}

bool GridNode::IsGoal(GridNode &nodeGoal) {

    if ((x == nodeGoal.x) &&
        (y == nodeGoal.y)) {
        return true;
    }

    return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool GridNode::GetSuccessors(AStarSearch<GridNode> *astarsearch, GridNode *parent_node) {

    int parent_x = -1;
    int parent_y = -1;

    if (parent_node) {
        parent_x = parent_node->x;
        parent_y = parent_node->y;
    }


    GridNode NewNode;

    // push each possible move except allowing the search to go backwards
    if ((GetGrid(x - 1, y) < 9)
        && !((parent_x == x - 1) && (parent_y == y))
            ) {
        NewNode = GridNode(x - 1, y);
        astarsearch->AddSuccessor(NewNode);
    }

    if ((GetGrid(x, y - 1) < 9)
        && !((parent_x == x) && (parent_y == y - 1))
            ) {
        NewNode = GridNode(x, y - 1);
        astarsearch->AddSuccessor(NewNode);
    }
    if ((GetGrid(x + 1, y) < 9)
        && !((parent_x == x + 1) && (parent_y == y))
            ) {
        NewNode = GridNode(x + 1, y);
        astarsearch->AddSuccessor(NewNode);
    }
    if ((GetGrid(x - 1, y - 1) < 9)
        && !((parent_x == x - 1) && (parent_y == y - 1))
            ) {
        NewNode = GridNode(x - 1, y - 1);
        astarsearch->AddSuccessor(NewNode);
    }
    if ((GetGrid(x + 1, y - 1) < 9)
        && !((parent_x == x + 1) && (parent_y == y - 1))
            ) {
        NewNode = GridNode(x + 1, y - 1);
        astarsearch->AddSuccessor(NewNode);
    }
    if ((GetGrid(x + 1, y + 1) < 9)
        && !((parent_x == x + 1) && (parent_y == y + 1))
            ) {
        NewNode = GridNode(x + 1, y + 1);
        astarsearch->AddSuccessor(NewNode);
    }


    if ((GetGrid(x - 1, y + 1) < 9)
        && !((parent_x == x - 1) && (parent_y == y + 1))
            ) {
        NewNode = GridNode(x - 1, y + 1);
        astarsearch->AddSuccessor(NewNode);
    }


    if ((GetGrid(x, y + 1) < 9)
        && !((parent_x == x) && (parent_y == y + 1))
            ) {
        NewNode = GridNode(x, y + 1);
        astarsearch->AddSuccessor(NewNode);
    }

    return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is
// conceptually where we're moving

float GridNode::GetCost(GridNode &successor) {
    return (float) GetGrid(x, y);

}

