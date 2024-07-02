//
// Created by stefano on 7/2/24.
//

#include "Grid.h"
#include"Square.h"
#include"constants.h"

Grid::Grid():width(constants::GRID_SIZE), height(constants::GRID_SIZE) {    //1400/25 = 56
    squares = new Square[width*height];
}
