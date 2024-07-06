//
// Created by stefano on 7/2/24.
//

#include<exception>

#include"../headers/SquareGrid.h"
#include"../headers/Square.h"
#include"../headers/exceptions.h"

using namespace constants;

SquareGrid::SquareGrid(int width, int height): Grid(width, height){
    squares = new Square[width*height];
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            squares[i*width+j].setPos(j, i);  //I quadrati vengono messi nella loro posizione nello schermo
        }
    } //Inizializzo  la mia griglia riempiendola di quadrati (bianchi) 25x25 percorribili
}

SquareGrid::~SquareGrid(){
    delete[] squares;
}


const Square& SquareGrid::getSquare(int x, int y) const {
    if(isValid(x,y)){  //Verifico validità posizione
        return squares[y*width+x];
    }
    else
        throw invalid_coordinates("Coordinate del quadrato non valide");
}

void SquareGrid::draw(sf::RenderWindow& window) const {
    for(int i = 0; i < width*height; i++){
        window.draw(squares[i].getShape());
    }  //Vengono disegnati tutti i quadrati. Metodo chiamato in Game
}

void SquareGrid::changeElementType(int x, int y, Type type) {
    if(isValid(x, y)){
        squares[y*width+x].setType(type);
    }
    else
        throw invalid_coordinates("Coordinate del quadrato non valide");
}

void SquareGrid::resetPath() {  //Riporta i blocchi del percorsoallo stato iniziale (Baic)
    for(int i = 0; i < height*width; i++){
        if(squares[i].getType()==Type::Path){
            squares[i].setType(Type::Basic);
        }
    }
}
