#include "grid.h"
#include <iostream>
#include <cstdlib>
#include <thread>

// Builder de la classe grid
grid::grid(int w, int h)
    : width(w), height(h), cells(w, std::vector<Cell>(h)) {}// Grille de dimensions `width` x `height` en créant un vecteur de Cellules

// Créer et initialiser la grille avec des cellules ayant des états aléatoires (pour l'instant a changer)
void grid::createGrid() {
    // Parcourt chaque cellule de la grille
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            // Assigne un état aléatoire (0 ou 1) à la cellule
            cells[x][y].isAlive = rand() % 2; // 0 pour morte, 1 pour vivante
        }
    }
}

// Getter pour obtenir une cellule pouvant etre modifiée
Cell& grid::getCell(int x, int y) {
    return cells[x][y];
}

// Getter pour obtenir une cellule non modifiable
const Cell& grid::getCell(int x, int y) const {
    return cells[x][y];
}


// Afficher la grille dans la console
void grid::display() const {
    // Parcourt chaque ligne de la grille
    for (int y = 0; y < height; y++) {
        // Parcourt chaque cellule de la ligne
        for (int x = 0; x < width; x++) {
            // Affiche "1" si la cellule est vivante, "0" si elle est morte
            std::cout << (cells[x][y].isAlive ? "1" : "0") << " ";
        }
        // Passe à la ligne suivante après avoir affiché une ligne entière
        std::cout << std::endl;
    }
}

bool grid::compareMatrix(std::vector<std::vector<Cell>> other) const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (cells[x][y].isAlive != other[x][y].isAlive) {
                return false; // Les matrices ne sont pas égales
            }
        }
    }
    return true;
}


// Mettre à jour l'état de la grille selon certaines règles
void grid::update() {
    std::vector<std::vector<Cell>> temp = this->cells;
    // Calculer le futur état pour chaque cellule
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            // Appelle la méthode update de la classe Cell
            cells[x][y].update(x, y, *this);
        }
    }
    // Ensuite appliquer les changements en actualisant `isAlive`
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            // willBeAlive calculé à la première étape est maintenant appliqué
            cells[x][y].isAlive = cells[x][y].willBeAlive;
        }
    }
    if (compareMatrix(temp)==false) {
        display();
        std::cout << "Le programme n'est pas stable" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Pause de 1s
    }

}

// Initialise la grille avec une configuration donnée
void grid::initializeWithState(const std::vector<std::vector<bool>> &initialState) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cells[x][y].isAlive = initialState[y][x];
        }
    }
}