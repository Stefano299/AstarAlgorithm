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

bool handleHeroMovement(Hero& hero) {
    int dx= 0;
    int dy= 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        dy -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        dy += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        dx -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        dx += 1;
    }
    return hero.move(dx, dy);  //Passo a move la direzione in cui hero si deve muovere, normalizzando (in caso) il vettore spostamento
    //Ritorna vero se è cambiata la posizione del suo nodo. Se è cambiata voglio che il percorso sia ricalcolato
}


void update(sf::RenderWindow &window, const SquareGrid &squareGrid, const GameCharacter &hero,
            const GameCharacter &enemy) {  //Aggiorna la finestra alla fine del (game) loop
    window.clear(sf::Color::White);
    squareGrid.draw(window);
    hero.draw(window);
    enemy.draw(window);
    window.display();
}

/*La uso per capire quando enemy raggiunge un nodo, voglio saperlo approsimativamente
non esattamente (la  posizione non sarà completamente esatta)*/
bool isNear(float a, float b) {
    if(abs(a - b) < (float) SQUARE_SIZE / 2)
        return true;
    else
        return false;
}

bool isDistantEnough(const GameCharacter &hero, const GameCharacter &enemy) {
    if(abs(hero.getPosX() - enemy.getPosX()) > SQUARE_SIZE * 2 ||  //Controllo che hero e enemy non siano troppo vicini
       abs(hero.getPosY() - enemy.getPosY()) > SQUARE_SIZE * 2)
        return true;
    else
        return false;
}

Path newPath(SquareGrid &squareGrid, GameCharacter &enemy, GameCharacter &hero) { //Calcolo un nuovo percorso da enemy a hero
    GridNode heroNode = hero.getNode();  //Imposto i nodi di enemy e hero come inizio e fine del percorso da trovare
    GridNode enemyNode = enemy.getNode();
    Path pathToHero;
    pathToHero.setPath(GridNode::getPath(enemyNode, heroNode));  //Do all'oggetto Path il percorso calcolato
    pathToHero.reset();
    squareGrid.resetPath();  //Una volta trovato un nuovo percorso cancello quello becchio
    for (auto &node : pathToHero.getPath()) {  //Disegno il nuovo percorso trovato
        squareGrid.changeElementType(node.x, node.y, Type::Path);
    }
    return pathToHero;
}

bool nodeReached(const Hero &hero, Enemy &enemy, Path &pathState) {  //Verifica se enemy ha raggiunto il nodo del percorso  che aveva come obbiettivo
    return isNear(enemy.getPosX(), pathState.getElement().x * SQUARE_SIZE) &&
           isNear(enemy.getPosY(), pathState.getElement().y * SQUARE_SIZE) &&
           isDistantEnough(hero, enemy) && !pathState.isFinished();
}

void nextPathNode(const Hero &hero, Enemy &enemy, Path &pathState, SquareGrid &squareGrid) { //Per passare al nodo successivo del percorso
    enemy.setNode(pathState.getElement().x, pathState.getElement().y);  //Voglio aggiornare il nodo di enemy, e quindi il nodo di inizio dei prossimi percorsi
    squareGrid.changeElementType(pathState.getElement().x,pathState.getElement().y, Type::Basic);      //Tolgo il disegno del tracciato per il nodo appena percorso
    pathState.nextNode();
}

int main() {
    SquareGrid squareGrid;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Astar", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    try {
        Hero hero(1800, 700, 8, "../img/hero.png");
        Enemy enemy(70, 700, 5, "../img/enemy.png");
        Path pathState;
        while (window.isOpen()) {
            try {
                handleEvents(window, squareGrid);  //Per aggiunta/rimozione ostacoli con il mouse
                bool heroNodeChanged = handleHeroMovement(hero);  //Vero se è cambiata la posizione del nodo di hero e voglio quindi ricalcolare il percorso
                /*Voglio trovare un nuovo percorso se è cambiata la posizione del nodo di hero o anche se
                enemy ha finito di percorrere l'ultimo percorso calcolato (sennò hero potrebbe rimanere fermo
                e non verrebbe calcolato nessun nuovo percorso, in caso agli ultimi movimenti di hero non siano stati trovati
                percorsi*/
                if ((heroNodeChanged) || pathState.isFinished()) {
                    if (isDistantEnough(hero, enemy)) {
                        try {
                            pathState = newPath(squareGrid, enemy, hero);  //Calcolo e salvo un nuovo percorso
                            enemy.startMovement(); //Se è stato trovato un percorso voglio che enemy si muova
                        } catch (path_not_found &e) {  //Se il percorso non viene trovato voglio che il programma non si fermi, e ne venga poi cercato un altro
                            std::cout << e.what() << std::endl;
                        }
                    } else {    //Se hero si muove ma è molto vicino a enemy non voglio venga calcolato un percorso, fermo quindi enemy
                        enemy.stop();
                        squareGrid.resetPath();  //Tolgo il disegno dell'ultimo percorso trovato
                    }
                }
                if (enemy.isMovementStarted()) {  //Se enemy si deve muovere
                    enemy.move(pathState.getElement().x, pathState.getElement().y); //Muovo enemy al nodo (più vicino) del percorso trovato
                    if(nodeReached(hero, enemy, pathState)) {  //Controllo se enemy ha raggiunto il nodo del suo percorso
                        nextPathNode(hero, enemy, pathState, squareGrid);  //se lo ha raggiunto voglio passare al nodo successivo del percorso
                    } else if (!isDistantEnough(hero, enemy) || pathState.isFinished()) {
                        //Se sono vicini o se il percorso è finito fermo enemy e rimuovo il percorso disegnato
                        enemy.startMovement();
                        squareGrid.resetPath();
                    }
                }
                update(window, squareGrid, hero, enemy);  //Aggiorno la finestra
                /* Se un blocco è posizionato fuori dalla finestra il programma continua al loop successivo
                non voglio che il programma termini*/
            } catch (invalid_coordinates &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    } catch (failed_character_init &e) {  //In caso un personaggio non sia inizializzato correttamente voglio terminare il programma
        std::cerr << e.what() << std::endl;
        return -1;
    }catch(path_out_of_bound& e){   //In caso sia acceda al vettore path con un indice non valido voglio termini il programma
        e.what();
        return -1;
    }
}