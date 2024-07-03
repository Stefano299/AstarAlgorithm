//
// Created by stefano on 7/3/24.
//

#include "GameCharacter.h"
#include "constants.h"

GameCharacter::GameCharacter(int gridX, int gridY, const sf::Texture& texture, float speed) {
    this->speed = speed;
    this->gridX = gridX;
    this->gridY = gridY;
    posX = gridX*constants::SQUARE_SIZE;
    posY = gridY*constants::SQUARE_SIZE;
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
    node = new GridNode(gridX, gridY); //Lo posizione sulla griglia
}

void GameCharacter::move(int x, int y) {
    sprite.move(x*constants::SQUARE_SIZE, y*constants::SQUARE_SIZE);
    float dx = x*constants::SQUARE_SIZE-posX;  //Differenze di posizione
    float dy = y*constants::SQUARE_SIZE-posY;
    float hyp = sqrt(dx*dx+dy*dy); //Calcolo l'ipotenusa del triangolo
    float senx = dy/hyp;    //Calcolo seno e coseno del triangolo
    float cosx = dx/hyp;
    posX += speed*cosx;
    posY += speed*senx;
    gridX = posX/constants::SQUARE_SIZE;
    gridY = posY/constants::SQUARE_SIZE;
    node->x = gridX;
    node->y = gridY;
    sprite.setPosition(posX, posY);  //SI muove un passo alla volta
}

GameCharacter::~GameCharacter() {
    delete node;
}

void GameCharacter::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}