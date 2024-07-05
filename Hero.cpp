//
// Created by stefano on 7/4/24.
//

#include"Hero.h"
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

bool Hero::move(float x, float y) {
    if(!isColliding(x, y)){     //Il mio personaggio non può attraversare i muri...
        float length = sqrt(x*x + y*y);  //Normalizzo il vettore così da non andare più veloce in diagonale
        if(length > 0) {
            x /= length;
            y /= length;
        }
        posX += x*speed;
        posY += y*speed;
        int newNodeX = posX/SQUARE_SIZE;
        int newNodeY = posY/SQUARE_SIZE;
        //setInsideWindow();//Per essere sicuro che non esca dalla finestra
        sprite.setPosition(posX, posY);
        if(node->x != newNodeX || node->y != newNodeY){  //Ritorna vero se le coordinate del nodo sono cambiate
            node->x = newNodeX;
            node->y = newNodeY;
            return true;
        }
        else
            return false;
    }
    else {
        cout << "Colliding" << endl; //Per sicurezza in caso di collisione lo mando indietro
        return false;
    }
}

bool Hero::isColliding(float x, float y)const {  //x e y indicano lo spostamento che si vuole compiere
    int fx = x*speed;
    int fy = y*speed;
    float originPos = (float)SQUARE_SIZE/2; //Posizione dell'origine rispetto al personaggio (è al centro)
    if(fx > originPos)   //Per quando la velocità è alta, non voglio salti un'intera casella
        fx = originPos;
    if(fy > originPos)
        fy = originPos;
    float futureX = (posX + fx +originPos*sign(x))/SQUARE_SIZE; //Controllo un po' più avanti rispetto alla mia posizione
    float futureY = (posY + fy + originPos*sign(y))/SQUARE_SIZE;
    if(futureX >= GRID_WIDTH || futureY >= GRID_HEIGHT || futureX < 0 || futureY < 0) //Per non farlo uscire dalla finestra
        return true;
    if(GridNode::numberGrid.getNumber(futureX, futureY) == 9) //Controllo che in una casella vicina non ci sia un ostacolo
        return true;
    if(GridNode::numberGrid.getNumber(futureX-sign(x), futureY) == 9 && GridNode::numberGrid.getNumber(futureX, futureY-sign(y))) //NON PUO' PASSARE NEGLIA ANGOLI
        return true;
    else
        return false;
}

