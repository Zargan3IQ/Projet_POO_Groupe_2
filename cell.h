#ifndef CELL_H
#define CELL_H

class Cell {
private:
    int isAlive;      // État actuel de la cellule (vivante ou morte)
    int willBeAlive;  // État futur de la cellule

public:
    Cell() : isAlive(0), willBeAlive(0) {}

    int getIsAlive() const;
    void setIsAlive(int state);

    int getWillBeAlive() const;
    void setWillBeAlive(int state);

    void update(int x, int y, const class grid &grid);
};

#endif // CELL_H
