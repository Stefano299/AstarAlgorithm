#include <iostream>

#include <SFML/Graphics.hpp>
#include"GameSingleton.h"
#include"Square.h"

int main() {
    GameSingleton::getInstance().createWindow(1400, 1400, "prova");
    GameSingleton::getInstance().eventCheck();
}