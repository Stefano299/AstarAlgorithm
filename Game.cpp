//
// Created by stefano on 7/2/24.
//

#include<exception>
#include<iostream>

#include "Game.h"
#include"Square.h"
#include"SquareGrid.h"
#include"NumberGrid.h"

void Game::createWindow(int w, int h, const std::string &t){ //Creazione (unica) finestra di gioco
    width = w;
    height = h;
    title = t;
    window.create(sf::VideoMode(w, h), title, sf::Style::Titlebar | sf::Style::Close); // con questi parametri rendo la finestra non ridimensionabile
    window.setFramerateLimit(60);
}

void Game::update() {        //Game loop
    window.clear(sf::Color::Black);
    squareGrid->draw(window);
    window.display();
}

void Game::eventCheck() {
    while(window.isOpen()){
        while(window.pollEvent(event)){      //Loop per controllare la presenza di eventi
            if(event.type== sf::Event::Closed)
                window.close();
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                leftClick(mousePos.x, mousePos.y);
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                for(int i = 0; i < constants::GRID_SIZE; i++) {
                    for (int j = 0; j < constants::GRID_SIZE; j++) {
                        cout << numberGrid->getNummber(j, i);
                    }
                    cout << endl;
                }
                GridNode node;
                vector<sf::Vector2i> path;
                path = GridNode::getPath(startNode, endNode);

            }
        }
        update();
    }
}

Game::Game() {
    squareGrid = new SquareGrid;
    numberGrid = new NumberGrid;
    startNode = GridNode(0,0);
    endNode = GridNode(47, 53);
}

Game::~Game() {
    delete squareGrid;
    delete numberGrid;
}

void Game::leftClick(int posX, int posY) {
    int x  = posX/25;
    int y = posY/25;
    squareGrid->changeElementType(x, y, Type::Obstacle);
    numberGrid->changeElementType(x, y, Type::Obstacle);


    std::cout << x << " " << y << std::endl;
}

int *Game::getNumberGridArray() const {
    return numberGrid->getArray();
}

