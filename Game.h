//
// Created by stefano on 7/2/24.
//

#ifndef SFML_GAME_H
#define SFML_GAME_H

#include<SFML/Window.hpp>
#include<string>
#include<SFML/Graphics.hpp>
#include<vector>

class Entity;
class Game {
private:
    sf::RenderWindow window;
    sf::Event event;
    unsigned int width;
    unsigned int height;
    std::string title;
    std::vector<Entity*> entities;   //vettore composto dai vari blocchi che vengono disegnati su chermo
    void update();
public:
    Game() = default;
    void eventCheck();
    void createWindow(int w, int h, const std::string& t);
    void addEntity(Entity* entity);
    Entity* getEntity(int pos) const;
    unsigned int getWidth() const{return width;}
    unsigned int getHeight() const{return height;}
    const std::string& getTitle() const{return title;}
    const sf::Event& getEvent() const{return event;}
};


#endif //SFML_GAME_H
