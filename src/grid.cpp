#include "grid.h"
#include <thread>
#include <iostream>

// Constructeur de la classe grid, initialisant la grille avec des dimensions w (largeur) et h (hauteur)
grid::grid(int w, int h) : width(w), height(h), cells(w, std::vector<Cell>(h)) {
    // Vérification que les dimensions sont valides (positives)
    if (w <= 0 || h <= 0) {
        std::cerr << "Error in grid initialization, incorrect width or height";
        exit(EXIT_FAILURE);  // Quitter l'application si les dimensions sont incorrectes
    }
}

// Accesseur constant pour obtenir une cellule spécifique de la grille (accès en lecture)
const Cell& grid::getCell(int x, int y) const {
    return cells[x][y];
}
// Accesseur constant pour obtenir une cellule spécifique de la grille (accès en lecture)
 Cell& grid::getCell(int x, int y)  {
    return cells[x][y];
}

// Fonction pour récupérer l'état entier de la grille sous forme de matrice
std::vector<std::vector<Cell>> grid::getState() const {
    return cells;
}

// Accesseur pour obtenir la largeur de la grille
int grid::getWidth() const {
    return width;
}

// Accesseur pour obtenir la hauteur de la grille
int grid::getHeight() const {
    return height;
}

// Vérifie si la grille est torique (bordures connectées)
bool grid::getisToric() const {
    return isToric;
}

// Modifie l'état "torique" de la grille (si les bords doivent se connecter ou non)
void grid::setisToric(bool Toric) {
    isToric = Toric;
}

// Initialise la grille avec un état donné sous forme de matrice de 0 et 1
void grid::initializeWithState(const std::vector<std::vector<int>> &initialState) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Initialisation de chaque cellule en fonction de l'état passé
            cells[x][y].setIsAlive(initialState[y][x]);
        }
    }
}

// Fonction qui compare l'état actuel de la grille avec une autre matrice de cellules
bool grid::compareMatrix(const std::vector<std::vector<Cell>> &other) const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (cells[x][y].getIsAlive() != other[x][y].getIsAlive()) {
                return false;  // Les matrices sont différentes
            }
        }
    }
    return true;  // Les matrices sont égales
}

// Mise à jour d'une partie de la grille (utilisé pour la mise à jour parallèle)
void grid::updateHalf(int start, int end) {
    for (int y = start; y < end; ++y) {
        for (int x = 0; x < width; ++x) {
            // Mise à jour de chaque cellule en fonction de son état actuel et des voisins
            cells[x][y].update(x, y, *this);
        }
    }
}

// Fonction principale pour mettre à jour toute la grille, avec un support pour l'exécution parallèle
void grid::update() {
    if (width < 2) {
        updateHalf(0, height);  // Si la largeur est trop petite, effectuer la mise à jour sur toute la grille
    } else {
        std::vector<std::vector<Cell>> previousState = cells;  // Sauvegarde de l'état précédent (pas utilisé ici mais pourrait être utile)

        // Lancement de deux threads pour effectuer la mise à jour en parallèle sur deux moitiés de la grille
        std::thread t1(&grid::updateHalf, this, 0, height / 2);
        std::thread t2(&grid::updateHalf, this, height / 2, height);

        t1.join();  // Attente de la fin du premier thread
        t2.join();  // Attente de la fin du deuxième thread

        // Application des nouvelles valeurs de cellules après la mise à jour
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                cells[x][y].setIsAlive(cells[x][y].getWillBeAlive());  // Mise à jour de l'état réel des cellules
            }
        }
    }
}

/*
// Fonction de mise à jour sans exécution parallèle, utilisée pour un test simple
void grid::updateTest() {
    std::vector<std::vector<Cell>> currentState = cells;  // Sauvegarde de l'état actuel pour référence

    // Mise à jour de toutes les cellules, sans optimisation parallèle
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            cells[x][y].update(x, y, *this);  // Mise à jour en fonction des règles du jeu de la vie
        }
    }

    // Applique les mises à jour (transition des états "souhaités" vers l'état final)
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            cells[x][y].setIsAlive(cells[x][y].getWillBeAlive());  // Mise à jour finale de l'état des cellules
        }
    }
}
*/
