#ifndef GRID_H
#define GRID_H

#include "Cell.h" // Inclut la définition de la classe Cell
#include <vector> // Utilisé pour stocker une grille 2D de cellules


//Représente une grille 2D composée de cellules, avec des fonctionnalités pour

class grid {
private:
    int width, height; // Dimensions de la grille
    std::vector<std::vector<Cell>> cells; // Matrice 2D contenant les cellules
    bool isToric; // Indique si la grille est torique (bordures connectées)

    void updateHalf(int start, int end); // Met à jour une partie de la grille. Utilisé pour les mises à jour parallélisées.

public:
    grid(int w, int h);// Constructeur de la grille

    int getWidth() const; // Obtient la largeur de la grille.
    int getHeight() const; // Obtient la hauteur de la grille.
    bool getisToric() const; // Vérifie si la grille est torique.
    void setisToric(bool Toric); // Définit si la grille est torique.
    const Cell& getCell(int x, int y) const; // Accède à une cellule en lecture seule.
    std::vector<std::vector<Cell>> getState() const; // Obtient l'état actuel de la grille sous forme de matrice 2D de cellules.

    void initializeWithState(const std::vector<std::vector<int>> &initialState); // Initialise la grille avec un état donné.
    bool compareMatrix(const std::vector<std::vector<Cell>>& other) const; // Compare l'état actuel de la grille avec une autre matrice.
    void update(); // Met à jour l'état de la grille selon les règles définies.
    void updateTest(); // Met à jour la grille pour les tests
};

#endif // GRID_H
