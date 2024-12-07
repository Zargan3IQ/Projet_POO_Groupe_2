#ifndef CELL_H
#define CELL_H

// Déclaration de la classe Cell
// Cette classe représente une cellule dans un automate cellulaire pour le jeu de la vie.
class Cell {
private:
    int isAlive;      // État actuel de la cellule : 1 si vivante, 0 si morte.
    int willBeAlive;  // État futur de la cellule après mise à jour.

public:
    // Constructeur par défaut : initialise la cellule comme morte
    Cell() : isAlive(0), willBeAlive(0) {}

    // Accesseur pour obtenir l'état actuel de la cellule.
    int getIsAlive() const;

    // Mutateur pour définir l'état actuel de la cellule.
    void setIsAlive(int state);

    // Accesseur pour obtenir l'état futur de la cellule.
    int getWillBeAlive() const;

    // Mutateur pour définir l'état futur de la cellule.
    void setWillBeAlive(int state);

    // Méthode pour mettre à jour l'état futur de la cellule en fonction
    void update(int x, int y, const class grid &grid);
};

#endif // CELL_H
