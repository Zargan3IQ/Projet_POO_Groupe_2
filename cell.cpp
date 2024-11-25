#include "Cell.h"
#include "grid.h"

// Calcule le futur état de la cellule
void Cell::update(int x, int y, const grid &grid) {
    int nbCellAlive = 0; // Compteur pour le nombre de cellules vivantes
    int xmin = x - 1;    // Coordonnée minimale en x pour la zone des voisins
    int xmax = x + 1;    // Coordonnée maximale en x pour la zone des voisins
    int ymin = y - 1;    // Coordonnée minimale en y pour la zone des voisins
    int ymax = y + 1;    // Coordonnée maximale en y pour la zone des voisins

    // Parcourt toutes les cellules voisines dans la zone délimitée par (xmin, ymin) et (xmax, ymax)
    for (int Ix = xmin; Ix <= xmax; Ix++) {
        for (int Jy = ymin; Jy <= ymax; Jy++) {
            // Ignorer la cellule elle-même
            if (Ix == x && Jy == y)
                continue;

            // Vérifie que les coordonnées de la cellule voisine sont valides (dans les limites de la grille)
            if (Ix >= 0 && Ix < grid.width && Jy >= 0 && Jy < grid.height) {
                // Si la cellule voisine est vivante, incrémenter le compteur
                if (grid.getCell(Ix, Jy).isAlive) {
                    nbCellAlive++;
                }
            }
        }
    }

    // Appliquer les règles du Jeu de la vie de Conway
    // Si la cellule actuelle est vivante
    if (isAlive) {
        // Elle survit uniquement si elle a exactement 2 ou 3 voisins vivants
        willBeAlive = (nbCellAlive == 2 || nbCellAlive == 3);
    } else {
        // Une cellule morte devient vivante si elle a exactement 3 voisins vivants
        willBeAlive = (nbCellAlive == 3);
    }
}
