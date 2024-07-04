//
// Created by stefano on 7/2/24.
//

#include "Square.h"
#include"constants.h"

using namespace constants;

Square::Square(Type t): size(SQUARE_SIZE), type(t) {     //Li rendo quadrati di lato 25
    shape.setSize(sf::Vector2f(size,size));
    color = associateColor(t);//Associa il colore in base al tipo di quadrato
    shape.setFillColor(color);
}

const sf::RectangleShape &Square::getShape() const {
    return shape;
}

sf::Color Square::associateColor(Type type) const {   //Ad ogni tipo di quadrato è associato in preciso colore, per riconoscerlo facilmente nel gioco
    switch(type){
        case Type::Basic:
            return sf::Color::White;
        case Type::Obstacle:
            return sf::Color(128,128,128); //Grigio in RGB
        case Type::Path:
            return sf::Color(255, 140, 140); //rosso chiaro
        default:
            throw std::invalid_argument("Tipo non esistente"); //Ci sono solo 4 tipi...,
            //TODO gestire eccezione
    }
}

void Square::setType(Type type) {   //Se cambia il tipo del quadrato deve cambiare anche il suo colore
    this->type = type;
    color = associateColor(type);
    shape.setFillColor(color);
}

Type Square::getType() const {
    return type;
}

void Square::setPos(int x, int y) {     //La x e la y indicano le coordinate nella griglia, ma col metodo setPosition inserisco la posizione nella finestra di gioco
    if(x>=0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE){
        shape.setPosition(x*SQUARE_SIZE, y*SQUARE_SIZE);
        this->x = x;
        this->y = y;
    }
    else
        throw std::out_of_range("Posizione del quadrato non valida");
}
