//
// Created by stefano on 7/4/24.
//

#include"Enemy.h"
#include"constants.h"

using namespace constants;

bool Enemy::move(float x, float y){   //Va ad una determinata coordinata (x, y)
    sprite.move(x*SQUARE_SIZE, y*SQUARE_SIZE);
    float dx = (float)x*SQUARE_SIZE-posX;  //Differenze di posizione
    float dy = (float)y*SQUARE_SIZE-posY;
    float hyp = sqrt(dx*dx+dy*dy); //Calcolo l'ipotenusa del triangolo
    float senx = dy/hyp;    //Calcolo seno e coseno del triangolo
    float cosx = dx/hyp;
    posX += speed*cosx;
    posY += speed*senx;
    sprite.setPosition(posX, posY);  //SI muove un passo alla volta
    return true; //Inutile nell'enemy, ma deve ritornare un booleano perchè serve in Hero (e move è un metodo della classe base quindi devono avere stesso tipo di ritorno)
}