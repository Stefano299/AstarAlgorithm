//
// Created by stefano on 7/2/24.
//

#ifndef SFML_SQUARE_H
#define SFML_SQUARE_H

#include<SFML/Graphics.hpp>
#include<map>

#include"constants.h"

enum class Type{   //Enumerazione dei possibili tipo di quadrato
    Basic,
    Obstacle,
    Path,
};

class Square {
private:
    const static std::map<Type, sf::Color> colors;
    sf::RectangleShape shape;
    Type type;
    int x;   //Posizioni nella griglia
    int y;
    float size;
public:
    Square(Type t = Type::Basic, float s = constants::SQUARE_SIZE, int x = 0, int y = 0);
    const sf::RectangleShape& getShape() const;
    float getSize() const{return size;}
    Type getType() const;
    void setType(Type type);
    void setPos(int x, int y);
    int getX() const{return x;}
    int getY() const{return y;}
};


#endif //SFML_SQUARE_H
