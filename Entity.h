//
// Created by stefano on 7/2/24.
//

#ifndef SFML_ENTITY_H
#define SFML_ENTITY_H

#include<SFML/Graphics.hpp>
#include"GameSingleton.h"

class Entity {
protected:
    sf::RectangleShape shape;
    sf::Color color;
    float size;
public:
    Entity() = default;
    Entity(float s, const sf::Color& color);
    const sf::RectangleShape& getShape() const;
    int getSize() const{return size;}
    const sf::Color& getColor() const{return color;}
};


#endif //SFML_ENTITY_H
