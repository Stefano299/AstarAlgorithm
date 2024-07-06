//
// Created by stefano on 7/4/24.
//

#ifndef ASTAR_ENEMY_H
#define ASTAR_ENEMY_H

#include"GameCharacter.h"

class Enemy: public GameCharacter {
private:
    bool moving;
public:
    Enemy(float x, float y, float speed, const string& txtPath):  GameCharacter(x, y, speed, txtPath, false){}
    bool isMovementStarted() const{return true;}
    void stop(){moving = false;}
    void startMovement(){moving = true;}
    bool move(float x, float y) override;
};


#endif //ASTAR_ENEMY_H
