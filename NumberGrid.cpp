//
// Created by stefano on 7/3/24.
//

#include "NumberGrid.h"
#include "constants.h"
#include"Square.h"
#include"GridNode.h"

NumberGrid::NumberGrid():Grid(constants::GRID_SIZE, constants::GRID_SIZE) {
    numbers = new int[constants::GRID_SIZE*constants::GRID_SIZE];  //Crea una griglia di numeri (Di stesse dimensioni di quelle del quadrato)
    for(int i = 0; i < constants::GRID_SIZE*constants::GRID_SIZE; i++){
        numbers[i] = 1; //1 significa percorribile
    }
}

void NumberGrid::changeElementType(int x, int y, Type type) {
    if(isValid(x, y)){
        GridNode::worldGrid = numbers;
        if(type == Type::Basic){
            numbers[y*constants::GRID_SIZE+x] = 1; //Percorribile
        }
        else if(type == Type::Obstacle){
            numbers[y*constants::GRID_SIZE+x] = 9;  //Non percorribile
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
        return numbers[y*constants::GRID_SIZE+x];
    else
        throw std::out_of_range("Coordinate del numero non valide");
}
