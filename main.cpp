#include <iostream>
#include <SFML/Graphics.hpp>

#include"constants.h"
#include"Square.h"
#include"NumberGrid.h"
#include"SquareGrid.h"
#include"GridNode.h"
#include"GameCharacter.h"
#include"Hero.h"
#include"Enemy.h"
#include"exceptions.h"

using namespace constants;

void removeObstacle(int posX, int posY, SquareGrid &squareGrid,
                    NumberGrid &numberGrid) {  //Rimuove un ostacolo in una posizioene
    int x = posX / SQUARE_SIZE;
    int y = posY / SQUARE_SIZE;
    squareGrid.changeElementType(x, y, Type::Basic);
    numberGrid.changeElementType(x, y, Type::Basic);
}

void addObstacle(int posX, int posY, SquareGrid &squareGrid,
                 NumberGrid &numberGrid) {  //Aggiunge un ostacolo in una posizione
    int x = posX / SQUARE_SIZE;
    int y = posY / SQUARE_SIZE;
    squareGrid.changeElementType(x, y, Type::Obstacle);
    numberGrid.changeElementType(x, y, Type::Obstacle);
}

void update(sf::RenderWindow &window, const SquareGrid &squareGrid, const GameCharacter &hero,
            const GameCharacter &enemy) {        //Game loop
    window.clear(sf::Color::White);
    squareGrid.draw(window);
    hero.draw(window);
    enemy.draw(window);
    window.display();
}

bool isEqual(float a, float b) {  //NON voglio sapere quando i miei personaggi sono ESATTAMENTE vicini
    if (abs(a - b) < (float) SQUARE_SIZE / 2)
        return true;
    else
        return false;
}

bool isEnoughDistant(const GameCharacter &hero, const GameCharacter &enemy) {
    if (abs(hero.getPosX() - enemy.getPosX()) > SQUARE_SIZE * 2 ||
        abs(hero.getPosY() - enemy.getPosY()) > SQUARE_SIZE * 2) {
        return true;
    } else
        return false;
}

vector<sf::Vector2i> newPath(int &count, SquareGrid &squareGrid, GameCharacter &enemy, GameCharacter &hero,
             bool &moving) {
    vector<sf::Vector2i> path = GridNode::getPath(*enemy.getNode(), *hero.getNode());
    count = 0;  //Count = 0 perchè deve cercare una nuova path
    squareGrid.reset();  //Rimuovo il disegno della vecchia path
    for (auto it: path) {
        squareGrid.changeElementType(it.x, it.y, Type::Path);
    }
    return path;

}

void nextPathNode(const GameCharacter &hero, GameCharacter &enemy, const vector<sf::Vector2i> &path, int &count,
                  bool &enemyMoving) {
    if (isEqual(enemy.getPosX(), path[count].x * SQUARE_SIZE) &&  //Se l'enemy ha raggiunto la posizione del nodo, si passa al nodo successivo nel percorso; così continua ad andare avanti
        isEqual(enemy.getPosY(), path[count].y * SQUARE_SIZE) &&
        isEnoughDistant(hero, enemy) && count < path.size()-1){  //Controllo anche che siano abbastanza distanti (sennò è inutile cercare un percorso) e che count (l'indice del vettore) non vada out of bound
        enemy.setNode(path[count].x, path[count].y);  //Aggiorno il nodo dell'enemy (che sarà il successivo start node)
        count++;
    } else if (!isEnoughDistant(hero, enemy) || count == path.size()-1) //Se enemy e hero sono molto vicini o se enemy ha percorso tutto il percorso, enemy si ferma
        enemyMoving = false;
}

int main() {
    SquareGrid squareGrid(GRID_WIDTH, GRID_HEIGHT);
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEGIHT), "Astar", sf::Style::Titlebar |
                                                                              sf::Style::Close); // con questi parametri rendo la finestra non ridimensionabile
    window.setFramerateLimit(60);
    try {
        Hero hero(1800, 700, 8,
                  "../img/hero.png"); //Voglio che l'hero abbia l'origine al centro, per gestire meglio le collision
        Enemy enemy(70, 700, 5, "../img/enemy.png");
        //GridNode::worldGrid = numberGrid.getArray();
        vector<sf::Vector2i> path;
        int count;
        bool enemyMoving = false;   //Se l'enemy si muove
        while (window.isOpen()) {
            sf::Event event;
            try {
                while (window.pollEvent(event)) {      //Loop per controllare la presenza di eventi
                    if (event.type == sf::Event::Closed)
                        window.close();
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {  //Aggiunge un ostacolo dove si clicca
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        addObstacle(mousePos.x, mousePos.y, squareGrid, GridNode::numberGrid);

                    }
                    if (sf::Mouse::isButtonPressed(
                            (sf::Mouse::Right))) {  //Rimuove un ostacolo dove si è fatto click destro
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        removeObstacle(mousePos.x, mousePos.y, squareGrid, GridNode::numberGrid);
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
                bool heroNodeChanged = false; //Booleano che indica  se la posizione del nodo dell'hero è cambiata, per non creare nuovi percorsi inutilmente
                heroNodeChanged = hero.move(dx,
                                            dy);  //Faccio così per poter normalizzar il vettore spostamento nel metodo moveBy
                if (makePath &&
                    heroNodeChanged) { //MakePath è = 1 se hero si è mosso, e c'è quindi bisogno di creare un nuovo percorso
                    if (isEnoughDistant(hero,
                                        enemy)) {      //La nuova path viene calcolata solo se l'eroe e il nemico sono sufficientemente distanti
                        try {
                            path = newPath(count, squareGrid, enemy, hero, enemyMoving);
                            enemyMoving = true;
                        } catch (
                                path_not_found &e) {     //Se non trova un percorso si ferma ma hero si può continuare a muovere
                            cout << e.what() << endl;
                            //L'enemy continua a seguire l'ultimo percorso trovato in caso abbia trovato e poi "perso" il personaggio
                        }
                    } else {
                        enemyMoving = false;
                    }
                }
                if (enemyMoving) {
                    enemy.move(path[count].x, path[count].y);
                    nextPathNode(hero, enemy, path, count,
                                 enemyMoving); //controlla se è necessario che l'enemy vada al nodo successivo del suo percorso, in caso lo fa
                }
                update(window, squareGrid, hero, enemy);
            }
            catch (invalid_coordinates &e) {
                cerr << e.what() << endl;
            }
        }
    }catch(failed_character_init& e){
        cerr << e.what() << endl;
        return -1;
    }
}

