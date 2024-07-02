//
// Created by stefano on 7/2/24.
//

#include "Grid.h"
#include"Square.h"
#include"constants.h"
#include<exception>

Grid::Grid():width(constants::GRID_SIZE), height(constants::GRID_SIZE) {    //1400/25 = 56
    squares = new Square[width*height];
    for(int i = 0; i < constants::GRID_SIZE; i++){
        for(int j = 0; j < constants::GRID_SIZE; j++){
            squares[i*constants::GRID_SIZE+j].setPos(j, i);
        }
    }
}

Grid::~Grid(){
    delete[] squares;
}


const Square& Grid::getSquare(int x, int y) const {
    if(x >= 0 && x < constants::GRID_SIZE && y >= 0 && y < constants::GRID_SIZE){
        return squares[y*constants::GRID_SIZE+x];
    }
    else
        throw std::out_of_range("Coordinate del quadrato non valide");
}

void Grid::draw(sf::RenderWindow& window) const {
    for(int i = 0; i < constants::GRID_SIZE*constants::GRID_SIZE; i++){
        window.draw(squares[i].getShape());
    }
}
