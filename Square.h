//
// Created by stefano on 7/2/24.
//

#ifndef SFML_SQUARE_H
#define SFML_SQUARE_H

#include<SFML/Graphics.hpp>
#include"GameSingleton.h"

enum class Type{
    Basic,
    Obstacle,
    Path,
    Waypoint,
};

class Square {
protected:
    sf::Color associateColor(Type type) const;
    sf::RectangleShape shape;
    sf::Color color;
    Type type;
    int x;
    int y;
    int size;
public:
    explicit Square(Type t = Type::Basic);
    const sf::RectangleShape& getShape() const;
    int getSize() const{return size;}
    const sf::Color& getColor() const{return color;}
    void setType(Type type);
    void setPos(int x, int y);
    int getX() const{return x;}
    int getY() const{return y;}
    Type getType() const;
};


#endif //SFML_SQUARE_H
