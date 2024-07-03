//
// Created by stefano on 7/2/24.
//

#include "SquareGrid.h"
#include"Square.h"
#include"constants.h"
#include<exception>

SquareGrid::SquareGrid(): Grid(constants::GRID_SIZE, constants::GRID_SIZE) {    //1400/25 = 56
    squares = new Square[width*height];
    for(int i = 0; i < constants::GRID_SIZE; i++){
        for(int j = 0; j < constants::GRID_SIZE; j++){
            squares[i*constants::GRID_SIZE+j].setPos(j, i);  //I quadrati vengono messi nella loro posizione nello schermo
        }
    } //Inizializzo  la mia griglia riempiendola di quadrati (bianchi) 25x25 percorribili
}

SquareGrid::~SquareGrid(){
    delete[] squares;
}


const Square& SquareGrid::getSquare(int x, int y) const {
    if(isValid(x,y)){  //Verifico validità posizione
        return squares[y*constants::GRID_SIZE+x];
    }
    else
        throw std::out_of_range("Coordinate del quadrato non valide");
}

void SquareGrid::draw(sf::RenderWindow& window) const {
    for(int i = 0; i < constants::GRID_SIZE*constants::GRID_SIZE; i++){
        window.draw(squares[i].getShape());
    }  //Vengono disegnati tutti i quadrati. Metodo chiamato in Game
}

void SquareGrid::changeElementType(int x, int y, Type type) {
    if(isValid(x, y)){
        squares[y*constants::GRID_SIZE+x].setType(type);
    }
    else
        throw std::out_of_range("Coordinate del quadrato non valide");
}

void SquareGrid::reset() {
    for(int i = 0; i < constants::GRID_SIZE*constants::GRID_SIZE; i++){
        if(squares[i].getType()==Type::Path){
            squares[i].setType(Type::Basic);
        }
    }
}
