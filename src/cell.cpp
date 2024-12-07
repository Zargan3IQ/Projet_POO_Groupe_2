#include <iostream>
#include <ostream>
#include "Cell.h"
#include "grid.h"

// Retourne l'état actuel de la cellule (vivante ou morte).
int Cell::getIsAlive() const {
    return isAlive;
}

// Définit l'état actuel de la cellule avec validation.
void Cell::setIsAlive(int state) {
    // Vérifie que l'état est bien entre 0 et 3.
    if (state >= 0 && state <= 3) {
        isAlive = state;
    } else {
        // Message d'erreur si l'état est invalide.
        std::cout << "Error in Cell::setIsAlive, state undefined" << std::endl;
    }
}

// Retourne l'état futur de la cellule.
int Cell::getWillBeAlive() const {
    return willBeAlive;
}

// Définit l'état futur de la cellule avec validation.
void Cell::setWillBeAlive(int state) {
    // Vérifie que l'état est bien entre 0 et 3.
    if (state >= 0 && state <= 3) {
        willBeAlive = state;
    } else {
        // Message d'erreur si l'état est invalide.
        std::cout << "Error in Cell::willBeAlive, state undefined" << std::endl;
    }
}

// Met à jour l'état futur de la cellule en fonction de ses voisins.
void Cell::update(int x, int y, const grid &grid) {
    int nbCellAlive = 0; // Compteur des cellules voisines vivantes.

    // Parcourt les voisins dans un carré 3x3 centré sur la cellule en x et y.
    for (int Ix = x - 1; Ix <= x + 1; Ix++) {
        for (int Jy = y - 1; Jy <= y + 1; Jy++) {
            // Ignore la cellule en elle-même.
            if (Ix == x && Jy == y) continue;

            // Gestion des bords pour une grille torique ou non. Si elle est torique les coordonnées limite renverrons a l'opposé si elle ne l'est pas elle s'arreteras à la limite
            int nx = grid.getisToric() ? (Ix + grid.getWidth()) % grid.getWidth() : Ix;
            int ny = grid.getisToric() ? (Jy + grid.getHeight()) % grid.getHeight() : Jy;

            // Vérifie que les coordonnées (nx, ny) sont valides dans la grille.
            if (nx >= 0 && nx < grid.getWidth() && ny >= 0 && ny < grid.getHeight()) {
                // Obtient l'état de la cellule voisine.
                int neighborState = grid.getCell(nx, ny).getIsAlive();
                // Compte les cellules vivantes (états 1 ou 3).
                if (neighborState == 1 || neighborState == 3) nbCellAlive++;
            }
        }
    }

    // Détermine l'état futur en fonction des règles et de l'état actuel.
    if (isAlive == 1) {
        // Si la cellule est vivante, elle survit si elle a 2 ou 3 voisins vivants.
        willBeAlive = (nbCellAlive == 2 || nbCellAlive == 3) ? 1 : 0;
    } else if (isAlive == 0) {
        // Si la cellule est morte, elle naît si elle a exactement 3 voisins vivants.
        willBeAlive = (nbCellAlive == 3) ? 1 : 0;
    } else if (isAlive == 3) {
        // Une cellule dans l'état spécial 3 reste dans cet état, c'est un obstacle vivant.
        willBeAlive = 3;
    } else if (isAlive == 2) {
        // Une cellule dans l'état spécial 2 reste également inchangée, c'est un obstacle mort.
        willBeAlive = 2;
    }
}
