#include <iostream>
#include <SFML/Graphics.hpp>

#include "../headers/constants.h"
#include "../headers/Square.h"
#include "../headers/NumberGrid.h"
#include "../headers/SquareGrid.h"
#include "../headers/GridNode.h"
#include "../headers/GameCharacter.h"
#include "../headers/Hero.h"
#include "../headers/Enemy.h"
#include "../headers/exceptions.h"
#include"../headers/Path.h"

using namespace constants;

void initWindow(sf::RenderWindow &window);
void removeObstacle(int posX, int posY, SquareGrid &squareGrid, NumberGrid &numberGrid);
void addObstacle(int posX, int posY, SquareGrid &squareGrid, NumberGrid &numberGrid);
void handleEvents(sf::RenderWindow &window, SquareGrid &squareGrid);
void handleEnemyMovement(SquareGrid &squareGrid,const Hero &hero, Enemy &enemy);
void handleHeroMovement(Hero& hero);
void update(sf::RenderWindow &window, const SquareGrid &squareGrid, const GameCharacter &hero, const GameCharacter &enemy);
Path newPath(SquareGrid &squareGrid, const GameCharacter &enemy, const GameCharacter &hero);
void nextPathNode(Path &pathState, SquareGrid &squareGrid);
bool isDistantEnough(const GameCharacter &hero, const GameCharacter &enemy);



int main() {
    SquareGrid squareGrid;
    sf::RenderWindow window;
    initWindow(window);
    try {
        Hero hero(SCREEN_WIDTH-50, SCREEN_HEIGHT/2, 8, "../assets/hero.png");
        Enemy enemy(50, SCREEN_HEIGHT/2, 5, "../assets/enemy.png");
        while (window.isOpen()) {
            try {
                handleEvents(window, squareGrid);  //Per aggiunta/rimozione ostacoli con il mouse
                handleHeroMovement(hero);  //per muovere hero cons WASD
                handleEnemyMovement(squareGrid, hero, enemy); //Per fare muovere enemy lungo il percorso trovato
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
        std::cerr << e.what() << std::endl;
        return -1;
    }
}


void initWindow(sf::RenderWindow &window){
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Astar", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
}

/*La uso per capire quando enemy raggiunge un nodo, voglio saperlo approsimativamente
non esattamente (la  posizione non sarà completamente esatta)*/
bool isDistantEnough(const GameCharacter &hero, const GameCharacter &enemy) {
    return (abs(hero.getPosX() - enemy.getPosX()) > SQUARE_SIZE * 2 ||  //Controllo che hero e enemy non siano troppo vicini
            abs(hero.getPosY() - enemy.getPosY()) > SQUARE_SIZE * 2);
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
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {  //Aggiunge ostacolo nel quadrato clicclato dal mouse
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            addObstacle(mousePos.x, mousePos.y, squareGrid, GridNode::numberGrid);
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {  //Rimuove ostacolo nel quadrato clicclato dal mouse
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            removeObstacle(mousePos.x, mousePos.y, squareGrid, GridNode::numberGrid);
        }
    }
}

void handleHeroMovement(Hero& hero) {
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
    hero.move(dx, dy);  //Passo a move la direzione in cui hero si deve muovere, normalizzando (in caso) il vettore spostamento
}

Path newPath(SquareGrid &squareGrid, const GameCharacter &enemy, const GameCharacter &hero) { //Calcolo un nuovo percorso da enemy a hero
    Path pathToHero;
    //Calcolo il percorso dal nodo di enemy al nodo di hero
    pathToHero.setPath(GridNode::getPath(enemy.getNode(), hero.getNode()));  //Do all'oggetto Path il percorso calcolato
    pathToHero.reset();
    squareGrid.resetPath();  //Una volta trovato un nuovo percorso cancello quello becchio
    for (auto &node : pathToHero.getPath()) {  //Disegno il nuovo percorso trovato
        squareGrid.changeElementType(node.x, node.y, Type::Path);
    }
    return pathToHero;
}



void nextPathNode(Enemy &enemy, Path &pathState, SquareGrid &squareGrid) { //Per passare al nodo successivo del percorso
    enemy.setNode(pathState.getElement().x, pathState.getElement().y);  //Voglio aggiornare il nodo di enemy, e quindi il nodo di inizio dei prossimi percorsi
    squareGrid.changeElementType(pathState.getElement().x,pathState.getElement().y, Type::Basic);      //Tolgo il disegno del tracciato per il nodo appena percorso
    pathState.nextNode();
}

void handleEnemyMovement(SquareGrid &squareGrid,const Hero &hero, Enemy &enemy) {
    /*Voglio trovare un nuovo percorso se è cambiata la posizione del nodo di hero o anche se
    enemy ha finito di percorrere l'ultimo percorso calcolato (sennò hero potrebbe rimanere fermo
    e non verrebbe calcolato nessun nuovo percorso, in caso agli ultimi movimenti di hero non siano stati trovati
    percorsi*/
    static Path pathToHero;  //Statica perchè voglio rimanga la stessa a ogni chiamata della funzione
    if ((hero.isNodeChanged()) || pathToHero.isFinished()) {
        if (isDistantEnough(hero, enemy)) {
            try {
                pathToHero = newPath(squareGrid, enemy, hero);  //Calcolo e salvo un nuovo percorso
                enemy.startMovement(); //Se è stato trovato un percorso voglio che enemy si muova
            } catch (path_not_found &e) {  //Se il percorso non viene trovato voglio che il programma non si fermi, e ne venga poi cercato un altro
                cout << e.what() << endl;
            }
        } else {    //Se hero si muove ma è molto vicino a enemy non voglio venga calcolato un percorso, fermo quindi enemy
            enemy.stop();
            squareGrid.resetPath();  //Tolgo il disegno dell'ultimo percorso trovato
        }
    }
    if (enemy.isMovementStarted()) {  //Se enemy si deve muovere
        enemy.move(pathToHero.getElement().x, pathToHero.getElement().y); //Muovo enemy al nodo (più vicino) del percorso trovato
        //Controllo se enemy ha raggiunto il nodo del suo percorso, se è abbastanza lontano e si assicura il percorso non sia terminato
        if(pathToHero.isNodeReached(enemy) && isDistantEnough(hero, enemy) && !pathToHero.isFinished()) {
            nextPathNode(enemy, pathToHero, squareGrid);  //se le condizioni sono verificate voglio passare al nodo successivo del percorso
        } else if (!isDistantEnough(hero, enemy) || pathToHero.isFinished()) {
            //Se sono vicini o se il percorso è finito fermo enemy e rimuovo il percorso disegnato
            enemy.stop();
            squareGrid.resetPath();
        }
    }
}

void update(sf::RenderWindow &window, const SquareGrid &squareGrid, const GameCharacter &hero, const GameCharacter &enemy) {  //Aggiorna la finestra alla fine del (game) loop
    window.clear();
    squareGrid.draw(window);
    hero.draw(window);
    enemy.draw(window);
    window.display();
}
