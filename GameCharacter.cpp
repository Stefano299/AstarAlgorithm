//
// Created by stefano on 7/3/24.
//

#include "GameCharacter.h"
#include "constants.h"

GameCharacter::GameCharacter(int gridX, int gridY, const sf::Texture& texture, float speed, float originX, float originY) {
    this->speed = speed;
    this->gridX = gridX;
    this->gridY = gridY;
    posX = gridX*constants::SQUARE_SIZE;
    posY = gridY*constants::SQUARE_SIZE;
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
    sprite.setOrigin(originX, originY); //L'origine dello sprite: da dove si controlla
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

void GameCharacter::moveBy(float x, float y) {
    if(!isColliding(x, y)){     //Il mio personaggio non può attraversare i muri...
        float length = sqrt(x*x + y*y);  //Normalizzo il vettore così da non andare più veloce in diagonale
        if(length > 0) {
            x /= length;
            y /= length;
        }
        posX += x*speed;
        posY += y*speed;
        gridX = posX/constants::SQUARE_SIZE;
        gridY = posY/constants::SQUARE_SIZE;
        node->x = gridX;
        node->y = gridY;
        sprite.setPosition(posX, posY);
        setInsideWindow(); //Per essere sicuro che non esca dalla finestra
    }
    else {
        cout << "COlliding" << endl; //Per sicurezza in caso di collisione lo mando indietro
    }
}

bool GameCharacter::isColliding(float x, float y)const {  //x e y indicano lo spostamento che si vuole compiere
    int tx = (int)(posX + x*1.5)/constants::SQUARE_SIZE; //Controllo un po' più avanti rispetto alla mia posizione
    int ty = (int)(posY + y*1.5)/constants::SQUARE_SIZE;
    if(GridNode::worldGrid[ty*constants::GRID_SIZE+tx]) //Controllo che in una casella vicina non ci sia un ostacolo e che non esca dalla finestra
        return false;
    else
        return true;
}

void GameCharacter::setInsideWindow() {  //Controlla se character è fuori dalla finestra, se lo è, lo rimett detnro
    float temp = (float)constants::SQUARE_SIZE/2;
    if(posX < temp){
        posX = temp;
    }
    else if(posY < temp){
        posY = temp;
    }
    else if(posX > constants::SCREEN_SIZE-temp){
        posX = constants::SCREEN_SIZE-temp;
    }
    else if(posY > constants::SCREEN_SIZE-temp){
        posY = constants::SCREEN_SIZE-temp;
    }
}
