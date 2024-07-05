//
// Created by stefano on 7/2/24.
//

#ifndef SFML_GRID_H
#define SFML_GRID_H

#include<SFML/Graphics.hpp>

#include"Grid.h"
#include"constants.h"

enum class Type;
class Square;
class SquareGrid: public Grid {
private:
    Square* squares;  //Griglia di quadrati (intesi come forme geometriche disegnabili)
public:
    explicit SquareGrid(int width = constants::GRID_WIDTH, int height = constants::GRID_HEIGHT);
    virtual ~SquareGrid();
    void reset(); //Rimuove i blocchi path per quando si trova una nuova path
    void draw(sf::RenderWindow& window) const;
    void changeElementType(int x, int y, Type type) override;
    const Square& getSquare(int x, int y) const;
};


#endif //SFML_GRID_H
