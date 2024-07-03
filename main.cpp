#include <iostream>

#include <SFML/Graphics.hpp>
#include"GameSingleton.h"
#include"constants.h"
#include"Square.h"

int main() {
    GameSingleton::getInstance().createWindow(constants::SCREEN_SIZE, constants::SCREEN_SIZE, "prova");
    GameSingleton::getInstance().eventCheck();
}