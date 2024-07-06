#include<cmath>
#include<stdexcept>

#include"../headers/GridNode.h"
#include"../headers/exceptions.h"

using namespace std;
using namespace constants;

NumberGrid GridNode::numberGrid(constants::GRID_WIDTH, constants::GRID_HEIGHT); //Viene creata la griglia coi numeri che indicano gli ostacoli

void GridNode::setX(int x) {
    if(x >= 0 && x < GRID_WIDTH)
        this->x =  x;
    else
        throw invalid_coordinates("Coordiante del nodo invalide");
}

void GridNode::setY(int y) {
    if(y >= 0 && y < GRID_HEIGHT)
        this->y =  y;
    else
        throw invalid_coordinates("Coordiante del nodo invalide");
}


int GridNode::GetGrid(int x, int y) const {
    if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT) {
        return 9;  //Fuori dalla finestra non èuò andare, come se fosse un ostacolo
    }
    return numberGrid.getNumber(x,y);
}

bool GridNode::IsSameState(const GridNode &rhs) const{ //Nel mio caso sue nodi hanno lo stesso "stato" se hanno le stesse coordinate
    return((x == rhs.x) && (y == rhs.y));
}

size_t GridNode::Hash() const{
    size_t h1 = std::hash<float>{}(x);
    size_t h2 = std::hash<float>{}(y);
    return h1 ^ (h2 << 1);
}

float GridNode::GoalDistanceEstimate(const GridNode &nodeGoal) const{
    return sqrt((x - nodeGoal.x) * (x - nodeGoal.x) + (y - nodeGoal.y) * (y - nodeGoal.y)); //Euclidea
    //return (abs(x - nodeGoal.x) + abs(y - nodeGoal.y)); MANHATTAN
}

bool GridNode::IsGoal(const GridNode &nodeGoal) const {
    return ((x == nodeGoal.x) && (y == nodeGoal.y));
}

bool GridNode::GetSuccessors(AStarSearch<GridNode> *astarsearch, GridNode *parent_node) const{ //Prendo i nodi successori
    int parent_x = -1;
    int parent_y = -1;

    if (parent_node) {    //Controllo che il parent node esista
        parent_x = parent_node->x;
        parent_y = parent_node->y;
    }

    GridNode NewNode;

    int directions[8][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, -1}, {1, -1}, {1, 1}, {-1, 1}};

    for (const auto &direction : directions) { //Per ogni direzione
        int newX = x + direction[0];
        int newY = y + direction[1];

        if (abs(direction[0]) + abs(direction[1]) == 2) {  //per impedire movimenti diagonali tra gli angoli d ostacoli
            if (GetGrid(x + direction[0], y) == 9 || GetGrid(x, y + direction[1]) == 9)
                continue;
        }
        if ((GetGrid(newX, newY) < 9)
            && !((parent_x == newX) && (parent_y == newY))  //Se non è un ostacolo e se il nuovo nodo non è uguale al nodo padre, lo aggiungo ai successori
                ) {
            NewNode = GridNode(newX, newY);
            astarsearch->AddSuccessor(NewNode);
        }
    }

    return true;
}


float GridNode::GetCost(const GridNode &successor) const{ //Il costo del movimento tra due nodi
    int dx = abs(x - successor.x);
    int dy = abs(y - successor.y);
    if (dx + dy == 2) { // Il costo  del movimento in diagonale è minore
        return sqrt(2);
    } else { // Movimento ortogonale
        return 1;
    }
}

vector<sf::Vector2i> GridNode::getPath(GridNode &nodeStart,GridNode &nodeEnd){
    vector<sf::Vector2i> path;
    AStarSearch<GridNode> astarsearch;
    unsigned int SearchCount = 0;
    const unsigned int NumSearches = 1;
    while (SearchCount < NumSearches) {
        astarsearch.SetStartAndGoalStates(nodeStart, nodeEnd);  //Imposto il nodo di partenza e di arrivo

        unsigned int SearchState;
        unsigned int SearchSteps = 0;  //Conto i passi fatti per trovare il percorso

        do {
            SearchState = astarsearch.SearchStep();
            SearchSteps++;
        } while (SearchState == AStarSearch<GridNode>::SEARCH_STATE_SEARCHING);

        if (SearchState == AStarSearch<GridNode>::SEARCH_STATE_SUCCEEDED) {
            GridNode *node = astarsearch.GetSolutionStart(); //Prendo il nodo iniziale del percorso
            int steps = 0;
            //Qua salto i dettagli dell'inizio del percorso
            for (;;) {
                node = astarsearch.GetSolutionNext();
                if (!node) { //Se non c'è un nodo successivo, ho finito il percorso
                    break;
                }
                path.push_back(sf::Vector2i(node->x, node->y)); //Aggiungo il nodo al percorso
                steps++;
            };
            astarsearch.FreeSolutionNodes(); //Liberare il vettore dei nodi una volta che è stato trovato il percorso

        } else if (SearchState == AStarSearch<GridNode>::SEARCH_STATE_FAILED) {
            throw path_not_found("Percorso non trovato");
        }
        SearchCount++;
        astarsearch.EnsureMemoryFreed(); //Libero la memoria
    }
    return path;
}

