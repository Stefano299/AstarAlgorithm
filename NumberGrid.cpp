//
// Created by stefano on 7/3/24.
//

#include "NumberGrid.h"
#include "constants.h"
#include"Square.h"
#include"GridNode.h"

using namespace constants;

NumberGrid::NumberGrid():Grid(GRID_SIZE, GRID_SIZE) {
    numbers = new int[GRID_SIZE*GRID_SIZE];  //Crea una griglia di numeri (Di stesse dimensioni di quelle del quadrato)
    for(int i = 0; i < GRID_SIZE*GRID_SIZE; i++){
        numbers[i] = 1; //1 significa percorribile
    }
}

void NumberGrid::changeElementType(int x, int y, Type type) {
    if(isValid(x, y)){
        //GridNode::worldGrid = numbers;
        if(type == Type::Basic){
            numbers[y*GRID_SIZE+x] = 1; //Percorribile
        }
        else if(type == Type::Obstacle){
            numbers[y*GRID_SIZE+x] = 9;
        }
        else
            throw std::invalid_argument("Tipo di numero non valido"); //I numeri possono essere solo percorribili o non
    }
}

NumberGrid::~NumberGrid() {
    delete[] numbers;
}

int NumberGrid::getNummber(int x, int y) const {
    if(isValid(x, y))
        return numbers[y*GRID_SIZE+x];
    else
        throw std::out_of_range("Coordinate del numero non valide");
}
