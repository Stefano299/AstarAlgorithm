//
// Created by stefano on 7/4/24.
//

#ifndef ASTAR_ENEMY_H
#define ASTAR_ENEMY_H

#include"GameCharacter.h"

class Enemy: public GameCharacter {
private:
    bool needsToMove;
public:
    Enemy(float x, float y, float speed, const string& txtPath): GameCharacter(x, y, speed, txtPath, false), needsToMove(false){}
    void move(float x, float y) override;
    bool isMovementStarted() const{return needsToMove;}
    void stop(){ needsToMove = false;}
    void startMovement(){ needsToMove = true;}
};


#endif //ASTAR_ENEMY_H
