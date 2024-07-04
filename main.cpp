#include <iostream>

#include <SFML/Graphics.hpp>
#include"constants.h"
#include"Square.h"
#include "NumberGrid.h"
#include "SquareGrid.h"
#include"GridNode.h"
#include"GameCharacter.h"

using namespace constants;

void removeObstacle(int posX, int posY, SquareGrid &squareGrid, NumberGrid &numberGrid) {  //Rimuove un ostacolo in una posizioene
    int x = posX / SQUARE_SIZE;
    int y = posY / SQUARE_SIZE;
    squareGrid.changeElementType(x, y, Type::Basic);
    numberGrid.changeElementType(x, y, Type::Basic);
    std::cout << x << " " << y << std::endl;
}

void addObstacle(int posX, int posY, SquareGrid &squareGrid, NumberGrid &numberGrid) {  //Aggiunge un ostacolo in una posizione
    int x = posX / SQUARE_SIZE;
    int y = posY / SQUARE_SIZE;
    squareGrid.changeElementType(x, y, Type::Obstacle);
    numberGrid.changeElementType(x, y, Type::Obstacle);
    std::cout << x << " " << y << std::endl;
}

void update(sf::RenderWindow &window, const SquareGrid &squareGrid, const GameCharacter &hero, const GameCharacter &enemy) {        //Game loop
    window.clear(sf::Color::White);
    squareGrid.draw(window);
    hero.draw(window);
    enemy.draw(window);
    window.display();
}

bool isEqual(float a, float b) {  //NON voglio sapere quando i miei personaggi sono ESATTAMENTE vicini
    if (abs(a - b) < 10)
        return true;
    else
        return false;
}

bool enoughDistant(const GameCharacter &hero, const GameCharacter &enemy) {
    if (abs(hero.getPosX() - enemy.getPosX()) > 40 || abs(hero.getPosY() - enemy.getPosY()) > 40) {
        return true;
    } else
        return false;
}

void newPath(int &count, SquareGrid &squareGrid, vector<sf::Vector2i> &path, GameCharacter &enemy, GameCharacter &hero, bool &moving) {
    path = GridNode::getPath(*enemy.getNode(), *hero.getNode());
    count = 0;  //Count = 0 perchè deve cercare una nuova path
    squareGrid.reset();
    for (auto it: path) {
        squareGrid.changeElementType(it.x, it.y, Type::Path);
    }
}

void nextPathNode(const GameCharacter &hero, GameCharacter &enemy, const vector<sf::Vector2i> &path, int &count,
                  bool &moving) {
    if (moving) {
        enemy.move(path[count].x, path[count].y);
        if (isEqual(enemy.getPosX(), path[count].x * SQUARE_SIZE) &&
            isEqual(enemy.getPosY(), path[count].y * SQUARE_SIZE) &&
            enoughDistant(hero, enemy) && count < path.size()) {
            enemy.setNode(path[count].x, path[count].y);  //Aggiorno il nodo dell'enemy (che sarà il successivo start node)
            cout << "change" << endl;
            count++;
            cout << count << endl;
        } else if (!enoughDistant(hero, enemy))
            moving = false;
    }
}

int main() {
    NumberGrid numberGrid;
    SquareGrid squareGrid;
    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Astar", sf::Style::Titlebar |
                                                                              sf::Style::Close); // con questi parametri rendo la finestra non ridimensionabile
    window.setFramerateLimit(60);
    GameCharacter hero(50, 25, 6, "../img/hero.png",
                       true); //Voglio che l'hero abbia l'origine al centro, per gestire meglio le collisioni
    GameCharacter enemy(3, 25, 5, "../img/enemy.png");
    GridNode::worldGrid = numberGrid.getArray();
    vector<sf::Vector2i> path;
    int count;
    bool moving = false;
    while (window.isOpen()) {
        sf::Event event;
        try {
            while (window.pollEvent(event)) {      //Loop per controllare la presenza di eventi
                if (event.type == sf::Event::Closed)
                    window.close();
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {  //Aggiunge un ostacolo dove si clicca
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    addObstacle(mousePos.x, mousePos.y, squareGrid, numberGrid);

                }
                if (sf::Mouse::isButtonPressed(
                        (sf::Mouse::Right))) {  //Rimuove un ostacolo dove si è fatto click destro
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    removeObstacle(mousePos.x, mousePos.y, squareGrid, numberGrid);
                }
            }
            int dx = 0;   //
            int dy = 0;
            bool makePath = false;
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
            if (makePath) {
                if (enoughDistant(hero, enemy)) {      //La nuova path viene calcolata solo se l'eroe e il nemico sono sufficientemente distanti
                    try {
                        newPath(count, squareGrid, path, enemy, hero, moving);
                        moving = true;
                    } catch (
                            runtime_error &e) {     //Se non trova un percorso si ferma ma hero si può continuare a muovere
                        cout << e.what() << endl;
                        //L'enemy continua a seguire l'ultimo percorso trovato in caso abbia trovato e poi "perso" il personaggio
                    }
                } else {
                    moving = false;
                }
            }
            hero.moveBy(dx, dy);  //Faccio così per poter normalizzar il vettore spostamento nel metodo moveBy
            nextPathNode(hero, enemy, path, count, moving);
            update(window, squareGrid, hero, enemy);
        }
        catch (out_of_range &e) {
            cerr << e.what() << endl;
        }
    }

}

