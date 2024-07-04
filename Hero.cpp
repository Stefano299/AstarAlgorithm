//
// Created by stefano on 7/4/24.
//

#include "Hero.h"
#include"GridNode.h"
#include"constants.h"

using namespace constants;

int sign(float x){  //Per prendere il segno di un float
    if(x==0)
        return 0;
    else if(x > 0)
        return 1;
    else
        return -1;
}

void Hero::move(float x, float y) {
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

bool Hero::isColliding(float x, float y)const {  //x e y indicano lo spostamento che si vuole compiere
    int fx = x*speed;  //Per quando la velocità è alta, non voglio salti un'intera casella
    int fy = y*speed;
    float originPos = (float)SQUARE_SIZE/2; //Posizione dell'origine rispetto al personaggio (è al centro)
    if(fx > originPos)
        fx = originPos;
    if(fy > originPos)
        fy = originPos;
    int futureX = (int)(posX + fx +originPos*sign(x))/SQUARE_SIZE; //Controllo un po' più avanti rispetto alla mia posizione
    int futureY = (int)(posY + fy + originPos*sign(y))/SQUARE_SIZE;
    if(GridNode::numberGrid.getNummber(futureX, futureY) == 9) //Controllo che in una casella vicina non ci sia un ostacolo
        return true;
    if(GridNode::numberGrid.getNummber(futureX-sign(x), futureY) == 9 && GridNode::numberGrid.getNummber(futureX, futureY-sign(y))) //NON PUO' PASSARE NEGLIA ANGOLI
        return true;
    else
        return false;
}

void Hero::setInsideWindow() {  //Controlla se character è fuori dalla finestra, se lo è, lo rimett dentro
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