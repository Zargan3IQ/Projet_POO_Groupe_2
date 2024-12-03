#include <iostream>
#include <ostream>

#include "Cell.h"
#include "grid.h"

int Cell::getIsAlive() const {
    return isAlive;
}

void Cell::setIsAlive(int state) {
    if (state==1||state==2||state==3||state==0) {
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
    if (state==1||state==2||state==3||state==0) {
        willBeAlive = state;
    }
    else {
        std::cout<<"Error in Cell::willBeAlive, state undefined"<<std::endl;
    }
}

// Calcule le futur état de la cellule
void Cell::update(int x, int y, const grid &grid) {
    int nbCellAlive = 0;
    int xmin = x - 1;
    int xmax = x + 1;
    int ymin = y - 1;
    int ymax = y + 1;

    for (int Ix = xmin; Ix <= xmax; Ix++) {
        for (int Jy = ymin; Jy <= ymax; Jy++) {
            if (Ix == x && Jy == y) continue;

            int teleportX = (Ix + grid.getWidth()) % grid.getWidth();
            int teleportY = (Jy + grid.getHeight()) % grid.getHeight();

            // Compte les voisins vivants
            if (grid.getCell(teleportX, teleportY).getIsAlive() == 1 || grid.getCell(teleportX, teleportY).getIsAlive() == 3) {
                nbCellAlive++;
            }
        }
    }

    // Mise à jour de l'état futur selon les règles du jeu
    if (isAlive == 1) {
        willBeAlive = (nbCellAlive == 2 || nbCellAlive == 3) ? 1 : 0;
    } else if (isAlive == 0) {
        willBeAlive = (nbCellAlive == 3) ? 1 : 0;
    } else if (isAlive == 3) {
        willBeAlive = 3; // Les règles spéciales pour l'état 3 sont conservées
    } else if (isAlive == 2) {
        willBeAlive = 2; // Les règles spéciales pour l'état 2 sont conservées
    }
}