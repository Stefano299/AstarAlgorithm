//
// Created by stefano on 7/5/24.
//

#ifndef ASTAR_PATH_H
#define ASTAR_PATH_H

#include<SFML/Graphics.hpp>
#include<exception>

class Hero;
class Enemy;
class Path {
private:
    unsigned int index;
    std::vector<sf::Vector2i> path;
public:
    Path():index(0){}
    void reset(){index = 0;}
    void nextNode();
    const std::vector<sf::Vector2i>& getPath() const{return path;}
    void setPath(std::vector<sf::Vector2i> p){path = p;}
    sf::Vector2i& getElement(){return path[index];}
    unsigned int getIndex() const{return index;}
    bool isFinished() const;
    bool isNodeReached(const Enemy &enemy) const;
};


#endif //ASTAR_PATH_H
