#include <iostream>

#include <SFML/Graphics.hpp>
#include"constants.h"
#include"Square.h"
#include "NumberGrid.h"
#include "SquareGrid.h"
#include"GridNode.h"

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
    window.display();
}



int main() {
    NumberGrid numberGrid;
    SquareGrid squareGrid;
    sf::RenderWindow window(sf::VideoMode(constants::SCREEN_SIZE, constants::SCREEN_SIZE), "Astar", sf::Style::Titlebar | sf::Style::Close); // con questi parametri rendo la finestra non ridimensionabile
    window.setFramerateLimit(60);
    GridNode startNode(0,0);
    GridNode endNode(45, 50);
    GridNode::worldGrid = numberGrid.getArray();
    sf::Event event;
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
                    GridNode node;
                    vector<sf::Vector2i> path;
                    path = GridNode::getPath(startNode, endNode);
                    for (auto it: path) {
                        squareGrid.changeElementType(it.x, it.y, Type::Path);
                    }

                }

            }
            update(window, squareGrid);
        }
        catch (out_of_range& e) {
            cerr << e.what() << endl;
        }
    }

}