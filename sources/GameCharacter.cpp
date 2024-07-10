//
// Created by stefano on 7/3/24.
//

#include"../headers/GameCharacter.h"
#include"../headers/exceptions.h"

using namespace constants;

GameCharacter::GameCharacter(float x, float y, float speed,  const string& txtPath, bool centerOrigin) {
    if (!texture.loadFromFile(txtPath)) {
        throw failed_character_init("Impossibile caricare texture");
    }
    if(x >= SCREEN_WIDTH || x<0 || y <0 || y >= SCREEN_HEIGHT){  //Non voglio venga messo fuori dalla finestra
        throw failed_character_init("Coordinate del personaggio non valide");
    }
    this->speed = speed;
    posX = x;
    posY = y;
    sprite.setTexture(texture);
    //La texture è 25x25, e quindi anche lo sprite. Voglio che questo, se cambia la dimsione dei quadrati, abbia sempre la loro dimensione
    sprite.setScale((float)SQUARE_SIZE/25, (float)SQUARE_SIZE/25);
    sprite.setPosition(posX, posY);
    if(centerOrigin)
        sprite.setOrigin((float)SQUARE_SIZE/2, (float)SQUARE_SIZE/2); //L'origine dello sprite: da dove si controlla
    node = GridNode(x/SQUARE_SIZE, y/SQUARE_SIZE); //Lo posizione sulla griglia
}


void GameCharacter::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void GameCharacter::setNode(int x, int y) {
    node.setX(x);
    node.setY(y);
}