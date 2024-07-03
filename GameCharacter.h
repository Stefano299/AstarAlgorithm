//
// Created by stefano on 7/3/24.
//

#ifndef ASTAR_GAMECHARACTER_H
#define ASTAR_GAMECHARACTER_H

#include<SFML/Graphics.hpp>
#include"GridNode.h"

class GameCharacter {
private:
    bool isColliding(float x, float y) const; //Per controllare se è in collisione con un ostacolo/parete, x e y indicanno lo spostamento che si vuole compiere
    void setInsideWindow();
    float posX;    //Posizione in pixel, NON sulla griglia
    float posY;
    int gridX;  //POSIZIONE SULLA GRIGLIA
    int gridY;
    float speed;
    GridNode* node;
    sf::Sprite sprite;
public:
    GameCharacter(int gridX, int gridY, const sf::Texture& texture, float speed, float originX = 0, float originY = 0);
    ~GameCharacter();
    void move(int x, int y);   //Si muove in una posizione INDICATA SULLA GRIGLIA
    void moveBy(float x, float y); //Si muove di x e y
    void draw(sf::RenderWindow& window) const;
    GridNode* getNode() const{return node;}
    int getGridY() const {return gridX;}
    int getGridX() const {return gridX;}
    float getPosY() const {return posY;}
    float getPosX() const {return posX;}
    float getSpeed() const{return speed;}

};


#endif //ASTAR_GAMECHARACTER_H
