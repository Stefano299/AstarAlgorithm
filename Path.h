//
// Created by stefano on 7/5/24.
//

#ifndef ASTAR_PATH_H
#define ASTAR_PATH_H

#include<SFML/Graphics.hpp>
#include<exception>

class Path {
private:
    unsigned int count;
    std::vector<sf::Vector2i> path;
public:
    Path():count(0){}
    void resetCount(){count = 0;}
    void increaseCount();
    const std::vector<sf::Vector2i>& getPath() const{return path;}
    void setPath(std::vector<sf::Vector2i> p){path = p;}
    sf::Vector2i& getElement(){return path[count];}
    bool isFinished() const;
};


#endif //ASTAR_PATH_H
