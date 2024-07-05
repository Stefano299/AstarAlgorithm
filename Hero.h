//
// Created by stefano on 7/4/24.
//

#ifndef ASTAR_HERO_H
#define ASTAR_HERO_H

#include"GameCharacter.h"

class Hero : public GameCharacter{
private:
    bool isColliding(float x, float y) const; //Per controllare se è in collisione con un ostacolo/parete, x e y indicanno lo spostamento che si vuole compiere
public:
    Hero(float x, float y, float speed, const string& txtPath):  GameCharacter(x, y, speed, txtPath, true){}
    bool move(float x, float y) override;  //Si muove di x e y, ritorna un booleano che indica se sono cambiate le coordinate del nodo

};


#endif //ASTAR_HERO_H
