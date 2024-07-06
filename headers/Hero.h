//
// Created by stefano on 7/4/24.
//

#ifndef ASTAR_HERO_H
#define ASTAR_HERO_H

#include"GameCharacter.h"

class Hero : public GameCharacter{
private:
    bool isColliding(float x, float y) const; //Per controllare se è in collisione con un ostacolo/parete, x e y indicanno lo spostamento che si vuole compiere
    bool nodeChanged; //Indica se le coordinate del nodo sono cambiate
public:
    Hero(float x, float y, float speed, const string& txtPath):  GameCharacter(x, y, speed, txtPath, true){}
    void move(float x, float y) override;
    bool isNodeChanged() const{return nodeChanged;} //Ritorna vero se il nodo di hero è cambiato, e bisogna quindi trovare un nuovo percorso
};


#endif //ASTAR_HERO_H
