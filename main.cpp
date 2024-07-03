#include <iostream>

#include <SFML/Graphics.hpp>
#include"constants.h"
#include"Square.h"
#include "NumberGrid.h"
#include "SquareGrid.h"
#include"GridNode.h"
#include"GameCharacter.h"


void rightClick(int posX, int posY, SquareGrid& squareGrid, NumberGrid& numberGrid) {  //Rimuove un ostacolo in una posizioene
    int x  = posX/constants::SQUARE_SIZE;
    int y = posY/constants::SQUARE_SIZE;
    squareGrid.changeElementType(x, y, Type::Basic);
    numberGrid.changeElementType(x, y, Type::Basic);
    std::cout << x << " " << y << std::endl;
}


void leftClick(int posX, int posY, SquareGrid& squareGrid, NumberGrid& numberGrid) {  //Aggiunge un ostacolo in una posizione
    int x  = posX/constants::SQUARE_SIZE;
    int y = posY/constants::SQUARE_SIZE;
    squareGrid.changeElementType(x, y, Type::Obstacle);
    numberGrid.changeElementType(x, y, Type::Obstacle);
    std::cout << x << " " << y << std::endl;
}

void update(sf::RenderWindow& window, SquareGrid& squareGrid) {        //Game loop
    window.clear(sf::Color::Black);
    squareGrid.draw(window);

}

bool isEqual(float a, float b){
    if(abs(a-b) < 10)
        return true;
    else
        return false;
}

bool enoughDistant(const GameCharacter& hero, const GameCharacter& enemy){
    if(abs(hero.getPosX()-enemy.getPosX() ) > 40 || abs(hero.getPosY() -enemy.getPosY()) > 40){

        return true;
    }
    else
        return false;
}

void newPath(int& count, SquareGrid& squareGrid, vector<sf::Vector2i>& path, GameCharacter& enemy, GameCharacter& hero, bool& moving){
    if(enoughDistant(hero, enemy)){
        count = 0;
        squareGrid.reset();
        path = GridNode::getPath(*enemy.getNode(), *hero.getNode());
        for (auto it: path) {
            squareGrid.changeElementType(it.x, it.y, Type::Path);
        }
        moving = true;
    }
    else
        moving = false;
}



int main() {
    NumberGrid numberGrid;
    SquareGrid squareGrid;
    sf::RenderWindow window(sf::VideoMode(constants::SCREEN_SIZE, constants::SCREEN_SIZE), "Astar", sf::Style::Titlebar | sf::Style::Close); // con questi parametri rendo la finestra non ridimensionabile
    window.setFramerateLimit(60);
    sf::Texture heroTxt;
    if (!heroTxt.loadFromFile("../img/hero.png"))
    {
        cerr << "Impossibile caricare la texture" << endl;
    }
    sf::Texture enemyTxt;
    if (!enemyTxt.loadFromFile("../img/enemy.png"))
    {
        cerr << "Impossibile caricare la texture" << endl;
    }
    GameCharacter hero(50, 50, heroTxt, 6, (float)constants::SQUARE_SIZE/2, (float)constants::SQUARE_SIZE/2); //Voglio che l'hero abbia l'origine al centro, per gestire meglio le collisioni
    GameCharacter enemy(3, 3, enemyTxt, 5);
    GridNode::worldGrid = numberGrid.getArray();
    sf::Event event;
    bool moving = false;
    vector<sf::Vector2i> path;
    int count =0;
    while(window.isOpen()) {
        try {
            while (window.pollEvent(event)) {      //Loop per controllare la presenza di eventi
                if (event.type == sf::Event::Closed)
                    window.close();
                 if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {  //Aggiunge un ostacolo dove si clicca
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    leftClick(mousePos.x, mousePos.y, squareGrid, numberGrid);

                }
                 if(sf::Mouse::isButtonPressed((sf::Mouse::Right))){  //Rimuove un ostacolo dove si è fatto click destro
                     sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                     rightClick(mousePos.x, mousePos.y, squareGrid, numberGrid);
                 }
            }
            int dx = 0;
            int dy = 0;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                dy-=1;
                newPath(count, squareGrid, path, enemy, hero, moving);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                dy+=1;
                newPath(count, squareGrid, path, enemy, hero, moving);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                dx-=1;
                newPath(count, squareGrid, path, enemy, hero, moving);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                dx+=1;
                newPath(count, squareGrid, path, enemy, hero, moving);
            }
            hero.moveBy(10*dx, 10*dy);  //Faccio così per poter normalizzar il vettore spostamento nel metodo moveBy
            if(moving) {
                enemy.move(path[count].x, path[count].y);
                if (isEqual(enemy.getPosX(), path[count].x * constants::SQUARE_SIZE) &&
                    isEqual(enemy.getPosY(), path[count].y * constants::SQUARE_SIZE) && enoughDistant(hero, enemy)) {
                    cout << "change" << endl;
                    count++;
                    cout << count << endl;
                }
                else if(!enoughDistant(hero, enemy))
                    moving = false;
            }
            window.clear(sf::Color::White);
            squareGrid.draw(window);
            hero.draw(window);
            enemy.draw(window);
            window.display();
        }
        catch (runtime_error& e) {
            cerr << e.what() << endl;
            path.clear();
            moving = false;
        }
        catch (out_of_range& e){
            cerr<< e.what() << endl;
        }
    }

}