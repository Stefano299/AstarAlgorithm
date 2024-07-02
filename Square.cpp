//
// Created by stefano on 7/2/24.
//

#include "Square.h"
#include"constants.h"

Square::Square(Type t): size(constants::SQUARE_SIZE), type(t) {     //Lir endo quadrati di lato 25
    shape.setSize(sf::Vector2f(size,size));
    color = associateColor(t);//Associa il colore in base al tipo di quadrato
    shape.setFillColor(color);
}

const sf::RectangleShape &Square::getShape() const {
    return shape;
}

const sf::Color &Square::associateColor(Type type) const {
    switch(type){
        case Type::Basic:
            return sf::Color::White;
        case Type::Obstacle:
            return sf::Color(128,128,128); //Grigio in RGB
        case Type::Path:
            return sf::Color::Green;
        case Type::Waypoint:
            return sf::Color::Blue;
    }
}
