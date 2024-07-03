//
// Created by stefano on 7/2/24.
//

#ifndef SFML_GAMESINGLETON_H
#define SFML_GAMESINGLETON_H

#include"Game.h"

class GameSingleton {  //Per assicurarmi ci sia una sola istanza di Game e che sia accessibile facilmente
public:
    static Game& getInstance();
private:
    static Game* game;
    GameSingleton() = default;
    ~GameSingleton() = default;
    GameSingleton& operator=(const GameSingleton&) = default;
    GameSingleton(const GameSingleton&) = default;
};


#endif //SFML_GAMESINGLETON_H
