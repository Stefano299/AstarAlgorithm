//
// Created by stefano on 7/2/24.
//

#include<iostream>

#include"../headers/Square.h"
#include"../headers/exceptions.h"
/*Sarebbe inutile fare sì che ogni quadrato abbia un diverso colore, in quanto questi consumano memoria
 e sono più o meno uguali per tutti. Perciò creo una mappa statica: questi vengono allocati una sola volta
 e ad ogni quadrato viene associato il suo.*/
const std::map<Type, sf::Color> Square::colors = {{Type::Basic, sf::Color::White},
                                            {Type::Obstacle, sf::Color(128,128,128)},
                                            {Type::Path, sf::Color(255, 140, 140)}};

using namespace constants;

Square::Square(Type t, float s, int x, int y): size(s), type(t) {     //Li rendo quadrati di lato 25
    this->x = x;
    this->y = y;
    shape.setSize(sf::Vector2f(size,size));
    auto color = colors.find(t); //Iteratore al colore che voglio, non ne controllo la validità perché i tipi sono solo 3: per forza trova qualcosa
    shape.setFillColor(color->second);
}

const sf::RectangleShape &Square::getShape() const {
    return shape;
}

void Square::setType(Type type) {   //Se cambia il tipo del quadrato deve cambiare anche il suo colore
    this->type = type;
    auto color = colors.find(type); //Iteratore al colore che voglio
    shape.setFillColor(color->second);
}

Type Square::getType() const {
    return type;
}

void Square::setPos(int x, int y) {     //La x e la y indicano le coordinate nella griglia, ma col metodo setPosition inserisco la posizione nella finestra di gioco
    if(x>=0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT){
        shape.setPosition(x*SQUARE_SIZE, y*SQUARE_SIZE);
        this->x = x;
        this->y = y;
    }
    else {
        throw invalid_coordinates("Posizione del quadrato non valida");
    }
}
