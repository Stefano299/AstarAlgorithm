//
// Created by stefano on 7/3/24.
//

#ifndef ASTAR_GAMECHARACTER_H
#define ASTAR_GAMECHARACTER_H

#include<SFML/Graphics.hpp>
#include"GridNode.h"

class GameCharacter {
protected:
    float posX;    //Posizione in pixel, NON sulla griglia
    float posY;
    int gridX;  //POSIZIONE SULLA GRIGLIA
    int gridY;
    float speed;
    GridNode* node;
    sf::Sprite sprite;
public:
    GameCharacter(int gridX, int gridY, const sf::Texture& texture, float speed);
    ~GameCharacter();
    void move(int gridX, int gridY);   //Si muove in una posizione INDICATA SULLA GRIGLIA
    void draw(sf::RenderWindow& window) const;
    GridNode* getNode() const{return node;}
    int getGridY() const {return gridX;}
    int getGridX() const {return gridX;}
    float getPosY() const {return posY;}
    float getPosX() const {return posX;}
    float getSpeed() const{return speed;}

};


#endif //ASTAR_GAMECHARACTER_H
