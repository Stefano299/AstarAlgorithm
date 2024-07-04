#include "GridNode.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

using namespace std;

NumberGrid GridNode::numberGrid;

int GridNode::GetGrid(int x, int y) const {
    if (x < 0 || x >= constants::GRID_SIZE || y < 0 || y >= constants::GRID_SIZE) {
        return 9;
    }
    return numberGrid.getNummber(x,y);
}

bool GridNode::IsSameState(GridNode &rhs) {
    if((x == rhs.x) && (y == rhs.y))
        return true;
    else
        return false;
}

size_t GridNode::Hash() {
    size_t h1 = std::hash<float>{}(x);
    size_t h2 = std::hash<float>{}(y);
    return h1 ^ (h2 << 1);
}

void GridNode::PrintNodeInfo() {
    cout << "Nodo alla posizione: " << x << ", " << y << endl;
}

float GridNode::GoalDistanceEstimate(GridNode &nodeGoal) {
    return sqrt((x - nodeGoal.x) * (x - nodeGoal.x) + (y - nodeGoal.y) * (y - nodeGoal.y)); //Euclidea
    //return (abs(x - nodeGoal.x) + abs(y - nodeGoal.y)); MANHATTAN
}

bool GridNode::IsGoal(GridNode &nodeGoal) {
    if((x == nodeGoal.x) && (y == nodeGoal.y))
        return true;
    else
        return false;
}

bool GridNode::GetSuccessors(AStarSearch<GridNode> *astarsearch, GridNode *parent_node) {
    int parent_x = -1;
    int parent_y = -1;

    if (parent_node) {    //Controllo che il parent node esista
        parent_x = parent_node->x;
        parent_y = parent_node->y;
    }

    GridNode NewNode;

    int directions[8][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, -1}, {1, -1}, {1, 1}, {-1, 1}};

    for (const auto &direction : directions) {
        int newX = x + direction[0];
        int newY = y + direction[1];

        if (newX == parent_x && newY == parent_y)
            continue; //Per evitare torni indietro al nodo parente

        if (abs(direction[0]) + abs(direction[1]) == 2) {  //per impedire movimenti diagonali tra gli angoli
            if (GetGrid(x + direction[0], y) == 9 || GetGrid(x, y + direction[1]) == 9)
                continue;
        }

        if (GetGrid(newX, newY) < 9) {
            NewNode = GridNode(newX, newY);
            astarsearch->AddSuccessor(NewNode);
        }
    }

    return true;
}


float GridNode::GetCost(GridNode &successor) {
    int dx = abs(x - successor.x);
    int dy = abs(y - successor.y);
    if (dx + dy == 2) { // Il costo  del movimento in diagonale è minore
        return sqrt(2);
    } else { // Movimento ortogonale
        return 1;
    }
}

vector<sf::Vector2i> GridNode::getPath(GridNode &nodeStart, GridNode &nodeEnd) {
    vector<sf::Vector2i> path;
    AStarSearch<GridNode> astarsearch;
    unsigned int SearchCount = 0;
    const unsigned int NumSearches = 1;
    while (SearchCount < NumSearches) {
        astarsearch.SetStartAndGoalStates(nodeStart, nodeEnd);

        unsigned int SearchState;
        unsigned int SearchSteps = 0;

        do {
            SearchState = astarsearch.SearchStep();

            SearchSteps++;
        } while (SearchState == AStarSearch<GridNode>::SEARCH_STATE_SEARCHING);

        if (SearchState == AStarSearch<GridNode>::SEARCH_STATE_SUCCEEDED) {
            cout << "Trovato un percorso" << endl;
            GridNode *node = astarsearch.GetSolutionStart();
            int steps = 0;
            //Qua salto i dettagli dell'inizio del percorso
            for (;;) {
                node = astarsearch.GetSolutionNext();
                if (!node) {
                    break;
                }
                path.push_back(sf::Vector2i(node->x, node->y));
                steps++;
            };
            astarsearch.FreeSolutionNodes(); //Liberare il vettore dei nodi una volta che è stato trovato il percorso

        } else if (SearchState == AStarSearch<GridNode>::SEARCH_STATE_FAILED) {
            cout << "Non è stato possibile trovare un percorso" << endl;
            throw runtime_error("Percorso non trovato");
        }
        SearchCount++;
        astarsearch.EnsureMemoryFreed();
    }
    return path;
}
