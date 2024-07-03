#include <iostream>

#include <SFML/Graphics.hpp>
#include"constants.h"
#include"Square.h"
#include "NumberGrid.h"
#include "SquareGrid.h"
#include"GridNode.h"
#include"GameCharacter.h"


void leftClick(int posX, int posY, SquareGrid& squareGrid, NumberGrid& numberGrid) {
    int x  = posX/25;
    int y = posY/25;

    squareGrid.changeElementType(x, y, Type::Obstacle);
    numberGrid.changeElementType(x, y, Type::Obstacle);


    std::cout << x << " " << y << std::endl;
}

void update(sf::RenderWindow& window, SquareGrid& squareGrid) {        //Game loop
    window.clear(sf::Color::Black);
    squareGrid.draw(window);

}

bool isEqual(float a, float b){
    if(abs(a-b) < 2)
        return true;
    else
        return false;
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
    GameCharacter hero(50, 50, heroTxt, 0.1);
    GameCharacter enemy(3, 3, enemyTxt, 2);
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
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    leftClick(mousePos.x, mousePos.y, squareGrid, numberGrid);

                } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    for (int i = 0; i < constants::GRID_SIZE; i++) {
                        for (int j = 0; j < constants::GRID_SIZE; j++) {
                            cout << numberGrid.getNummber(j, i);
                        }
                        cout << endl;
                    }
                    count = 0;
                    squareGrid.reset();
                    path = GridNode::getPath(*enemy.getNode(), *hero.getNode());
                    for (auto it: path) {
                        squareGrid.changeElementType(it.x, it.y, Type::Path);
                    }
                    moving = true;


                }

            }
            if(moving) {
                enemy.move(path[count].x, path[count].y);
                cout << enemy.getPosX()  << endl << path[count].x*constants::SQUARE_SIZE << endl;
                cout << enemy.getPosY()  << endl << path[count].y*constants::SQUARE_SIZE << endl;
                if (isEqual(enemy.getPosX(), path[count].x * constants::SQUARE_SIZE) &&
                    isEqual(enemy.getPosY(), path[count].y * constants::SQUARE_SIZE) &&count < 20) {

                    cout << "change" << endl;
                    count++;
                }
            }

            window.clear(sf::Color::Black);
            squareGrid.draw(window);
            hero.draw(window);
            enemy.draw(window);
            window.display();
        }
        catch (out_of_range& e) {
            cerr << e.what() << endl;
        }
    }

}