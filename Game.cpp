//
// Created by stefano on 7/2/24.
//

#include "Game.h"
#include"Square.h"
#include<exception>

void Game::createWindow(int w, int h, const std::string &t){ //Creazione (unica) finestra di gioco
    width = w;
    height = h;
    title = t;
    window.create(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close); // con questi parametri rendo la finestra non ridimensionabile
    window.setFramerateLimit(60);
}

void Game::update() {        //Game loop
    window.clear(sf::Color::Black);
    grid.draw(window);
    window.display();
}

void Game::eventCheck() {
    while(window.isOpen()){
        while(window.pollEvent(event)){      //Loop per controllare la presenza di eventi
            if(event.type== sf::Event::Closed)
                window.close();
        }
        update();
    }
}

