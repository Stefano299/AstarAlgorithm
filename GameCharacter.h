//
// Created by stefano on 7/3/24.
//

#ifndef ASTAR_GAMECHARACTER_H
#define ASTAR_GAMECHARACTER_H

#include<SFML/Graphics.hpp>

#include"GridNode.h"

class GameCharacter {
protected:
    //TODO fare due classi separate per hero e enemy
    float posX;    //Posizione in pixel, NON sulla griglia
    float posY;
    float speed;   //TODO refactor troopi attributi
    GridNode* node;
    sf::Sprite sprite;
    sf::Texture texture;
public:
    GameCharacter(float x, float y, float speed, const string& txtPath, bool centerOrigin = false);
    virtual ~GameCharacter();
    virtual bool move(float x, float y) = 0;   //Si muove in una posizione INDICATA SULLA GRIGLIA
    void draw(sf::RenderWindow& window) const;
    GridNode getNode() const{return node;}
    float getPosY() const {return posY;}
    float getPosX() const {return posX;}
    float getSpeed() const{return speed;}
    void setNode(int x, int y);
};


#endif //ASTAR_GAMECHARACTER_H
