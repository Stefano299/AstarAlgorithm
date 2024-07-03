//
// Created by stefano on 7/3/24.
//
#include"Grid.h"
#include"constants.h"

#include<exception>

bool Grid::isValid(int x, int y) const {
    if(x >= 0 && x < constants::GRID_SIZE && y >= 0 && y < constants::GRID_SIZE)
        return true;
    else
        return false;
}
