//
// Created by stefano on 7/2/24.
//

#include "Game.h"
#include"Entity.h"
#include<exception>

void Game::createWindow(int w, int h, const std::string &t){
    width = w;
    height = h;
    title = t;
    window.create(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close); // con questi parametri rendo la finestra non ridimensionabile
    window.setFramerateLimit(60);
}

void Game::update() {
    window.clear(sf::Color::Black);
    for(const auto& it: entities){  //disegna tutti i blocchi
        window.draw(it->getShape());
    }
    window.display();
}

void Game::eventCheck() {
    while(window.isOpen()){
        while(window.pollEvent(event)){      //event loop
            if(event.type== sf::Event::Closed)
                window.close();
        }
        update();
    }
}

void Game::addEntity(Entity *entity) {
    entities.push_back(entity);
}

Entity *Game::getEntity(int pos) const {
    if(pos < entities.size())
        return entities[pos];
    else
        throw std::out_of_range("Posizione non accessibile");
}

