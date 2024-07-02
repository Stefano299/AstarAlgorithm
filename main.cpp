#include <iostream>

#include <SFML/Graphics.hpp>
#include"GameSingleton.h"
#include"Entity.h"

int main() {
    GameSingleton::getInstance().createWindow(1400, 1400, "prova");
    Entity entity(50, sf::Color::Green);
    GameSingleton::getInstance().eventCheck();
}