//
// Created by stefano on 7/2/24.
//

#ifndef SFML_GAME_H
#define SFML_GAME_H

#include<SFML/Window.hpp>
#include<string>
#include<SFML/Graphics.hpp>
#include "GridNode.h"

class NumberGrid;
class SquareGrid;
class Square;
class Game {
private:
    sf::RenderWindow window;
    sf::Event event;
    unsigned int width;
    unsigned int height;
    std::string title;
    SquareGrid* squareGrid;   //Griglia che contiene i vari quadrati
    NumberGrid* numberGrid;
    GridNode startNode;
    GridNode endNode;
    void update();
    void leftClick(int posX, int posY);
public:
    Game();
    ~Game();
    void eventCheck();
    int* getNumberGridArray() const;
    void createWindow(int w, int h, const std::string& t);
    unsigned int getWidth() const{return width;}
    unsigned int getHeight() const{return height;}
    const std::string& getTitle() const{return title;}
};


#endif //SFML_GAME_H
