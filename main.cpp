#include <iostream>
#include <SFML/Graphics.hpp>

#include "constants.h"
#include "Square.h"
#include "NumberGrid.h"
#include "SquareGrid.h"
#include "GridNode.h"
#include "GameCharacter.h"
#include "Hero.h"
#include "Enemy.h"
#include "exceptions.h"
#include"Path.h"

using namespace constants;

bool handleHeroMovement(bool &makePath, Hero& hero) {
    int dx= 0;
    int dy= 0;
    makePath= false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        dy -= 1;
        makePath = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        dy += 1;
        makePath = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        dx -= 1;
        makePath = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        dx += 1;
        makePath = true;
    }
    return hero.move(dx, dy);  //Passo a move la direzione in cui hero si deve muovere, normalizzando (in caso) il vettore spostamento
}

void removeObstacle(int posX, int posY, SquareGrid &squareGrid, NumberGrid &numberGrid) {
    int x = posX / SQUARE_SIZE;
    int y = posY / SQUARE_SIZE;
    squareGrid.changeElementType(x, y, Type::Basic);  //Ridisegna i quadrati e rirende il quadrato percorribile
    numberGrid.changeElementType(x, y, Type::Basic);
}

void addObstacle(int posX, int posY, SquareGrid &squareGrid, NumberGrid &numberGrid) {
    int x = posX / SQUARE_SIZE;
    int y = posY / SQUARE_SIZE;
    squareGrid.changeElementType(x, y, Type::Obstacle);  //Disegna il quadrato dell'ostacolo
    numberGrid.changeElementType(x, y, Type::Obstacle);  //Rende l'ostacolo non percorribile
}

void handleEvents(sf::RenderWindow &window, SquareGrid &squareGrid) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {  //Aggiunge ostacolo nel quadrato clicclato dal mouse
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            addObstacle(mousePos.x, mousePos.y, squareGrid, GridNode::numberGrid);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {  //Rimuove ostacolo nel quadrato clicclato dal mouse
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            removeObstacle(mousePos.x, mousePos.y, squareGrid, GridNode::numberGrid);
        }
    }
}

void update(sf::RenderWindow &window, const SquareGrid &squareGrid, const GameCharacter &hero,
            const GameCharacter &enemy) {  //Aggiorna la finestra alla fine del (game) loop
    window.clear(sf::Color::White);
    squareGrid.draw(window);
    hero.draw(window);
    enemy.draw(window);
    window.display();
}

bool isEqual(float a, float b) {  //La uso per capire quando enemy raggiunge un nodo, voglio saperlo approsimativamente non esattamente (la  posizione non sarà completamente esatta)
    if(abs(a - b) < (float) SQUARE_SIZE / 2)
        return true;
    else
        return false;
}

bool isEnoughDistant(const GameCharacter &hero, const GameCharacter &enemy) {
    if(abs(hero.getPosX() - enemy.getPosX()) > SQUARE_SIZE * 2 ||
       abs(hero.getPosY() - enemy.getPosY()) > SQUARE_SIZE * 2)
        return true;
    else
        return false;
}

Path newPath(SquareGrid &squareGrid, GameCharacter &enemy, GameCharacter &hero) {
    GridNode heroNode = hero.getNode();
    GridNode enemyNode = enemy.getNode();
    Path pathState;
    pathState.setPath(GridNode::getPath(enemyNode, heroNode));
    pathState.resetCount();
    squareGrid.reset();
    for (auto &node : pathState.getPath()) {
        squareGrid.changeElementType(node.x, node.y, Type::Path);
    }
    return pathState;
}

bool nodeReached(const Hero &hero, Enemy &enemy, Path &pathState) {
    return isEqual(enemy.getPosX(), pathState.getElement().x * SQUARE_SIZE) &&
           isEqual(enemy.getPosY(), pathState.getElement().y * SQUARE_SIZE) &&
           isEnoughDistant(hero, enemy) && !pathState.isFinished();
}

void nextPathNode(const Hero &hero, Enemy &enemy, Path &pathState, SquareGrid &squareGrid) {
    if (nodeReached(hero, enemy, pathState)) {
        enemy.setNode(pathState.getElement().x, pathState.getElement().y);
        squareGrid.changeElementType(pathState.getElement().x,pathState.getElement().y, Type::Basic);
        pathState.increaseCount();
    } else if (!isEnoughDistant(hero, enemy) || pathState.isFinished()) {
        enemy.moving = false;
        squareGrid.reset();
    }
}

int main() {
    SquareGrid squareGrid;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Astar", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    try {
        Hero hero(1800, 700, 8, "../img/hero.png");
        Enemy enemy(70, 700, 5, "../img/enemy.png");
        Path pathState;
        enemy.moving = false;
        while (window.isOpen()) {
            try {
                handleEvents(window, squareGrid);
                bool makePath = false;
                bool heroNodeChanged = handleHeroMovement(makePath, hero);
                if ((makePath && heroNodeChanged) || pathState.isFinished()) {
                    if (isEnoughDistant(hero, enemy)) {
                        try {
                            pathState = newPath(squareGrid, enemy, hero);
                            enemy.moving = true;
                        } catch (path_not_found &e) {
                            std::cout << e.what() << std::endl;
                        }
                    } else {
                        enemy.moving = false;
                        squareGrid.reset();
                    }
                }
                if (enemy.moving) {
                    enemy.move(pathState.getElement().x, pathState.getElement().y);
                    nextPathNode(hero, enemy, pathState, squareGrid);
                }
                update(window, squareGrid, hero, enemy);
            } catch (invalid_coordinates &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    } catch (failed_character_init &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }catch(out_of_range& e){
        e.what();
        return -1;
    }
}