//
// Created by stefano on 7/2/24.
//

#ifndef ASTAR_GRIDNODE_H
#define ASTAR_GRIDNODE_H

#include<iostream>
#include<stdio.h>
#include<math.h>
#include<SFML/Graphics.hpp>

#include"../includes//stlastar.h"
#include"constants.h"
#include"NumberGrid.h"

using namespace std;

class GridNode {   //Classe che rappresenta un nodo della mia griglia
private:
    int x;
    int y;
    int GetGrid(int x, int y) const; //Se una coordinata è fuori dalla griglia è come se fosse un ostacolo
public:
    static NumberGrid numberGrid;
    GridNode(): x(0), y(0){}
    GridNode(int px, int py) : x(px), y(py){}
    void setX(int x);
    void setY(int y);
    int getX() const{return x;}
    int getY() const{return y;}
    float GoalDistanceEstimate(const GridNode &nodeGoal) const;
    bool IsGoal(const GridNode &nodeGoal) const;
    bool GetSuccessors(AStarSearch<GridNode> *astarsearch, GridNode *parent_node) const;
    float GetCost(const GridNode &successor) const;
    bool IsSameState(const GridNode &rhs) const;
    size_t Hash() const;
    static vector<sf::Vector2i> getPath(GridNode &nodeStart,GridNode &nodeEnd);
};


#endif //ASTAR_GRIDNODE_H
