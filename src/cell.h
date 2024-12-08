#ifndef CELL_H
#define CELL_H

// Déclaration de la classe Cell
// Cette classe représente une cellule dans un automate cellulaire pour le jeu de la vie.
class Cell {
private:
    int isAlive;      // État actuel de la cellule : 0 si morte, 1 si vivante, 2 si obstacle mort et 3 si obstacle vivant.
    int willBeAlive;  // État futur de la cellule après mise à jour.

public:
    Cell() : isAlive(0), willBeAlive(0) {} // Constructeur par défaut : initialise la cellule comme morte

    int getIsAlive() const; // Accesseur pour obtenir l'état actuel de la cellule.

    void setIsAlive(int state); // Mutateur pour définir l'état actuel de la cellule.

    int getWillBeAlive() const; // Accesseur pour obtenir l'état futur de la cellule.

    void setWillBeAlive(int state); // Mutateur pour définir l'état futur de la cellule.

    void update(int x, int y, const class grid &grid); // Méthode pour mettre à jour l'état futur de la cellule en fonction
};

#endif // CELL_H
