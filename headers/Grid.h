//
// Created by stefano on 7/3/24.
//

#ifndef ASTAR_GRID_H
#define ASTAR_GRID_H

enum class Type;
class Grid {    //Classe astratta per la griglia di nomi e di numeri
protected:
    bool isValid(int x, int y) const; //Funzione per verificare che due coordinate siano accessibili (Dentro una finestra)
    int width;
    int height;
public:
    Grid() = default;
    Grid(int w, int h):width(w), height(h){}
    virtual ~Grid() = default;
    virtual void changeElementType(int x,  int y, Type type) = 0;//Metodo per cambaire il tipo di un quadrato/numero ad una certa posizione
    int getWidth() const{return width;}
    int getHeight() const{return height;}
};


#endif //ASTAR_GRID_H
