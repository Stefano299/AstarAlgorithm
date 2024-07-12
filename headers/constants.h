//
// Created by stefano on 7/2/24.
//

#ifndef ASTAR_CONSTANTS_H
#define ASTAR_CONSTANTS_H

/*Cambiare qualsiasi costante NON rompe in nessun modo il funzionamento del programma.
//Anche le dimensioni degli sprite si regolano da sole, bisogna solo stare attenti alle coordinate in cui vengono
//inizializzati hero e enemy nel main. L'unica cosa IMPORTANTE è che, chiaramente SCREEN_HEIGHT deve essere = GRID_HEIGHT*SQUARE_SIZE.
e SCREE_WIDTH = GRID_WIDTH*SQUARE_SIZE. */
namespace constants{
    const int SQUARE_SIZE = 13;
    const int GRID_WIDTH = 90;
    const int GRID_HEIGHT = 56;
    const int SCREEN_HEIGHT = 728;
    const int SCREEN_WIDTH = 1170;
}


#endif //ASTAR_CONSTANTS_H
