//
// Created by stefano on 7/5/24.
//

#include "Path.h"

void Path::increaseCount() {
    if (count < path.size())
        count++;
    else
        throw std::out_of_range("Tentato accesso al path con un indice non valido");
}

bool Path::isFinished() const {
    if (count >= path.size() - 1)
        return true;
    else
        return false;
}
