//
// Created by stefano on 7/5/24.
//

#include "../headers/Path.h"
#include"../headers/exceptions.h"
#include"../headers/Hero.h"
#include"../headers/Enemy.h"

bool isNear(float a, float b) {
    return(abs(a - b) < (float) constants::SQUARE_SIZE / 2);
}

void Path::nextNode() {
    if (index < path.size() && index > 0)  //Passa al prossimo nodo del percorso
        index++;
    else
        throw path_out_of_bound("Tentato accesso al path con un indice non valido");
}

bool Path::isFinished() const { //Ritorna vero se si è alla fine del percorso
    return (index >= path.size() - 1);
}

bool Path::isNodeReached(const Enemy &enemy) const{ //Ritorna vero se enemy ha raggiunto il nodo del percorso  che aveva come obbiettivo
    return (isNear(enemy.getPosX(), path[index].x * constants::SQUARE_SIZE) &&
            isNear(enemy.getPosY(), path[index].y * constants::SQUARE_SIZE));

}
