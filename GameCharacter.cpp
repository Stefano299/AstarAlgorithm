//
// Created by stefano on 7/3/24.
//

#include "GameCharacter.h"
#include "constants.h"
using namespace constants;

GameCharacter::GameCharacter(int gridX, int gridY, float speed,  const string& txtPath, bool centerOrigin) {
    if (!texture.loadFromFile(txtPath)) {
        cerr << "Impossibile caricare texture" << endl;
    }
    this->speed = speed;
    posX = gridX*SQUARE_SIZE;
    posY = gridY*SQUARE_SIZE;
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
    if(centerOrigin)
        sprite.setOrigin((float)SQUARE_SIZE/2, (float)SQUARE_SIZE/2); //L'origine dello sprite: da dove si controlla
    node = new GridNode(gridX, gridY); //Lo posizione sulla griglia
}

GameCharacter::~GameCharacter() {
    delete node;
}

void GameCharacter::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void GameCharacter::setNode(int x, int y) {
    node->x = x;
    node->y = y;
}
