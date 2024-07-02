//
// Created by stefano on 7/2/24.
//

#ifndef SFML_GAME_H
#define SFML_GAME_H

#include<SFML/Window.hpp>
#include<string>
#include<SFML/Graphics.hpp>
#include<vector>
#include"Grid.h"

class Square;
class Game {
private:
    sf::RenderWindow window;
    sf::Event event;
    unsigned int width;
    unsigned int height;
    std::string title;
    Grid grid;   //Griglia che contiene i vari quadrati
    void update();
public:
    Game() = default;
    void eventCheck();
    void createWindow(int w, int h, const std::string& t);
    unsigned int getWidth() const{return width;}
    unsigned int getHeight() const{return height;}
    const std::string& getTitle() const{return title;}
};


#endif //SFML_GAME_H
