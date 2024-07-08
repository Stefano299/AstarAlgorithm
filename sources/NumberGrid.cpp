//
// Created by stefano on 7/3/24.
//

#include"../headers/NumberGrid.h"
#include"../headers/Square.h"
#include "../headers/exceptions.h"

using namespace constants;

NumberGrid::NumberGrid(int width, int height):Grid(width, height) {
    numbers = new int[width*height];  //Crea una griglia di numeri (Di stesse dimensioni di quella dei quadrati)
    for(int i = 0; i < width*height; i++){
        numbers[i] = 1; //1 significa percorribile
    }
}

void NumberGrid::changeElementType(int x, int y, Type type) {
    if(isValid(x, y)){
        //GridNode::worldGrid = numbers;
        if(type == Type::Basic){
            numbers[y* width+x] = 1; //Percorribile
        }
        else if(type == Type::Obstacle){
            numbers[y*width+x] = 9;
        }
    }
}

NumberGrid::~NumberGrid() {
    delete[] numbers;
}

int NumberGrid::getNumber(int x, int y) const {
    if(isValid(x, y))
        return numbers[y*width+x];
    else
        throw invalid_coordinates("Coordinate del numero non valide");
}

NumberGrid &NumberGrid::operator=(const NumberGrid &right) {
    if(this != &right) {
        delete[] numbers;
        width = right.width;
        height = right.height;
        numbers = new int[width*height];
        for(int i = 0; i < width*height; i++){
            numbers[i] = right.numbers[i];
        }
    }
    return *this;
}

NumberGrid::NumberGrid(const NumberGrid &original) {
    width = original.width;
    height = original.height;
    numbers = new int[width*height];
    for(int i = 0; i < width*height; i++){
        numbers[i] = original.numbers[i];
    }
}
