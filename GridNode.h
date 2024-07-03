//
// Created by stefano on 7/2/24.
//

#ifndef ASTAR_GRIDNODE_H
#define ASTAR_GRIDNODE_H

#include <iostream>
#include <stdio.h>
#include <math.h>
#include<SFML/Graphics.hpp>
#include "stlastar.h"
#include"constants.h"

using namespace std;

class GridNode {   //Classe che rappresenta un nodo della mia griglia
private:
    int GetGrid(int x, int y) const; //Se una coordinata è fuori dalla griglia è come se fosse un ostacolo
    static int* worldGrid;  //La griglia che indica dove sono gli ostacoli
    int x;     // the (x,y) positions of the node
    int y;
public:
    GridNode(): x(0), y(0){}
    GridNode(int px, int py) : x(px), y(py){}
    float GoalDistanceEstimate(GridNode &nodeGoal);
    bool IsGoal(GridNode &nodeGoal);
    bool GetSuccessors(AStarSearch<GridNode> *astarsearch, GridNode *parent_node);
    float GetCost(GridNode &successor);
    bool IsSameState(GridNode &rhs);
    size_t Hash();
    static vector<sf::Vector2i> getPath(GridNode &nodeStart, GridNode &nodeEnd);
    void PrintNodeInfo();
};


#endif //ASTAR_GRIDNODE_H
