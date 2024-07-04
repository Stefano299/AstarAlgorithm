//
// Created by stefano on 7/4/24.
//

#ifndef ASTAR_HERO_H
#define ASTAR_HERO_H

#include"GameCharacter.h"

class Hero : public GameCharacter{
private:
    bool isColliding(float x, float y) const; //Per controllare se è in collisione con un ostacolo/parete, x e y indicanno lo spostamento che si vuole compiere
    void setInsideWindow();
public:
    Hero(int gridX, int gridY, float speed, const string& txtPath):  GameCharacter(gridX, gridY, speed, txtPath, true){setInsideWindow();} //Faccio setInsideWidnwo per evitare venga creato fuori dalla finestra
    void move(float x, float y) override;  //Si muove di x e y

};


#endif //ASTAR_HERO_H
