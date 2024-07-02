//
// Created by stefano on 7/2/24.
//

#ifndef SFML_GRID_H
#define SFML_GRID_H
#include<vector>

class Square;
class Grid {
private:
    Square* squares;
    int width;
    int height;
public:
    Grid();
    ~Grid() = default;
    void addSquare(const Square& square);
    const Square& getSquare(int x, int y) const;
};


#endif //SFML_GRID_H
