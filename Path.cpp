//
// Created by stefano on 7/5/24.
//

#include "Path.h"
#include"exceptions.h"

void Path::nextNode() {
    if (index < path.size())
        index++;
    else
        throw path_out_of_bound("Tentato accesso al path con un indice non valido");
}

bool Path::isFinished() const {
    if (index >= path.size() - 1)
        return true;
    else
        return false;
}
