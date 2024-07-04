//
// Created by stefano on 7/4/24.
//

#ifndef ASTAR_ENEMY_H
#define ASTAR_ENEMY_H

#include"GameCharacter.h"

class Enemy: public GameCharacter {
public:
    Enemy(int gridX, int gridY, float speed, const string& txtPath):  GameCharacter(gridX, gridY, speed, txtPath, false){}
    void move(float x, float y) override;
};


#endif //ASTAR_ENEMY_H
