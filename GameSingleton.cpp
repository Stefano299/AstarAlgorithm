//
// Created by stefano on 7/2/24.
//

#include "GameSingleton.h"

Game* GameSingleton::game = nullptr;

Game &GameSingleton::getInstance() {
    static Game game1;
    game = &game1;
    return *game;
}
