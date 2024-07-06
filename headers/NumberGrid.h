//
// Created by stefano on 7/3/24.
//

#ifndef ASTAR_NUMBERGRID_H
#define ASTAR_NUMBERGRID_H

#include"Grid.h"
#include"constants.h"

class NumberGrid: public Grid{
private:
    int* numbers; //Numeri che indicano se una casella è percorribile o no
public:
    explicit NumberGrid(int width = constants::GRID_WIDTH, int height = constants::GRID_HEIGHT);
    virtual ~NumberGrid();
    void changeElementType(int x,  int y, Type type) override;
    int getNumber(int x, int y) const;
    //Operatore di assegnazione e costruttore di copia
    NumberGrid& operator=(const NumberGrid& right);
    NumberGrid(const NumberGrid &original);
};


#endif //ASTAR_NUMBERGRID_H
