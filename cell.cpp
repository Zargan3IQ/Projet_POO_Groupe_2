#include <iostream>
#include <ostream>
#include "Cell.h"
#include "grid.h"

int Cell::getIsAlive() const {
    return isAlive;
}

void Cell::setIsAlive(int state) {
    if (state >= 0 && state <= 3) {
        isAlive = state;
    }
    else {
        std::cout<<"Error in Cell::setIsAlive, state undefined"<<std::endl;
    }
}

int Cell::getWillBeAlive() const {
    return willBeAlive;
}

void Cell::setWillBeAlive(int state) {
    if (state >= 0 && state <= 3) {
        willBeAlive = state;
    }
    else {
        std::cout<<"Error in Cell::willBeAlive, state undefined"<<std::endl;
    }
}

void Cell::update(int x, int y, const grid &grid) {
    int nbCellAlive = 0;

    for (int Ix = x - 1 ; Ix <= x + 1 ; Ix++) {
        for (int Jy = y - 1 ; Jy <= y + 1 ; Jy++) {
            if (Ix == x && Jy == y) continue;

            int nx = grid.getisToric() ? (Ix + grid.getWidth()) % grid.getWidth() : Ix;
            int ny = grid.getisToric() ? (Jy + grid.getHeight()) % grid.getHeight() : Jy;

            if (nx >= 0 && nx < grid.getWidth() && ny >= 0 && ny < grid.getHeight()) {
                int neighborState = grid.getCell(nx, ny).getIsAlive();
                if (neighborState == 1 || neighborState == 3) nbCellAlive++;
            }
        }
    }

    // Mise à jour de l'état futur
    if (isAlive == 1) {
        willBeAlive = (nbCellAlive == 2 || nbCellAlive == 3) ? 1 : 0;
    } else if (isAlive == 0) {
        willBeAlive = (nbCellAlive == 3) ? 1 : 0;
    } else if (isAlive == 3) {
        willBeAlive = 3;
    } else if (isAlive == 2) {
        willBeAlive = 2;
    }
}