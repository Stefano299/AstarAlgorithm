//
// Created by stefano on 7/2/24.
//

#ifndef SFML_GRID_H
#define SFML_GRID_H
#include<vector>
#include<SFML/Graphics.hpp>

enum class Type;
class Square;
class Grid {
private:
    Square* squares;  //Griglia di quadrati (intesi come forme geometriche disegnabili)
    int width;
    int height;
public:
    Grid();
    ~Grid();
    void draw(sf::RenderWindow& window) const;
    int getWidth() const{return width;}
    int getHeight() const{return height;}
    const Square& getSquare(int x, int y) const;
};


#endif //SFML_GRID_H
