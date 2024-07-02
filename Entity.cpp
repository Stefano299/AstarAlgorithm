//
// Created by stefano on 7/2/24.
//

#include "Entity.h"

Entity::Entity(float s, const sf::Color &c): size(s), color(c) {
    shape.setSize(sf::Vector2f(s,s));
    shape.setFillColor(c);
    GameSingleton::getInstance().addEntity(this);
}

const sf::RectangleShape &Entity::getShape() const {
    return shape;
}
