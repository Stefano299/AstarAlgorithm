//
// Created by stefano on 7/3/24.
//
#include"../headers/Grid.h"
#include"../headers/constants.h"

bool Grid::isValid(int x, int y) const { //Ritorna vero se la posizione (x, y) è valida sulla griglia
    return(x >= 0 && x < constants::GRID_WIDTH&& y >= 0 && y < constants::GRID_HEIGHT);
}
