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
    setInsideWindow(); //Per essere sicuro non sia inizializzato fuori dalla finestra
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
    if(centerOrigin)
        sprite.setOrigin((float)SQUARE_SIZE/2, (float)SQUARE_SIZE/2); //L'origine dello sprite: da dove si controlla
    node = new GridNode(gridX, gridY); //Lo posizione sulla griglia
}

void GameCharacter::move(int x, int y) {
    sprite.move(x*SQUARE_SIZE, y*SQUARE_SIZE);
    float dx = (float)x*SQUARE_SIZE-posX;  //Differenze di posizione
    float dy = (float)y*SQUARE_SIZE-posY;
    float hyp = sqrt(dx*dx+dy*dy); //Calcolo l'ipotenusa del triangolo
    float senx = dy/hyp;    //Calcolo seno e coseno del triangolo
    float cosx = dx/hyp;
    posX += speed*cosx;
    posY += speed*senx;
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
        node->x = posX/SQUARE_SIZE;
        node->y = posY/SQUARE_SIZE;
        setInsideWindow();//Per essere sicuro che non esca dalla finestra
        sprite.setPosition(posX, posY);
    }
    else {
        cout << "Colliding" << endl; //Per sicurezza in caso di collisione lo mando indietro
    }
}

int sign(float x){
    if(x==0)
        return 0;
    else if(x > 0)
        return 1;
    else
        return -1;
}

bool GameCharacter::isColliding(float x, float y)const {  //x e y indicano lo spostamento che si vuole compiere
    int fx = x*speed;  //Per quando la velocità è alta, non voglio salti un'intera casella
    int fy = y*speed;
    float originPos = (float)SQUARE_SIZE/2; //Posizione dell'origine rispetto al personaggio (è al centro)
    if(fx > originPos)
        fx = originPos;
    if(fy > originPos)
        fy = originPos;
    int futureX = (int)(posX + fx +originPos*sign(x))/SQUARE_SIZE; //Controllo un po' più avanti rispetto alla mia posizione
    int futureY = (int)(posY + fy + originPos*sign(y))/SQUARE_SIZE;
    if(GridNode::worldGrid[futureY*GRID_SIZE+futureX] == 9) //Controllo che in una casella vicina non ci sia un ostacolo
        return true;
    if(GridNode::worldGrid[futureY*GRID_SIZE+futureX-sign(x)] == 9 && GridNode::worldGrid[(futureY-sign(y))*GRID_SIZE+futureX] == 9) //NON PUO' PASSARE NEGLIA ANGOLI
        return true;
    else
        return false;
}  //TODO cambiare sistema di collisione

void GameCharacter::setInsideWindow() {  //Controlla se character è fuori dalla finestra, se lo è, lo rimett detnro
    float temp = (float)SQUARE_SIZE/2;
    if(posX < temp){
        posX = temp;
    }
    if(posY < temp){
        posY = temp;
    }
    if(posX > SCREEN_SIZE-temp){
        posX = SCREEN_SIZE-temp;
    }
    if(posY > SCREEN_SIZE-temp){
        posY = SCREEN_SIZE-temp;
    }
}

void GameCharacter::setNode(int x, int y) {
    node->x = x;
    node->y = y;
}
