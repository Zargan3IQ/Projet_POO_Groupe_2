#ifndef CELL_H
#define CELL_H

class Cell {
private:
    bool isAlive;      // État actuel de la cellule (vivante ou morte)
    bool willBeAlive;  // État futur de la cellule

public:
    Cell() : isAlive(false), willBeAlive(false) {}

    bool getIsAlive() const;
    void setIsAlive(bool state);

    bool getWillBeAlive() const;
    void setWillBeAlive(bool state);

    void update(int x, int y, const class grid &grid);
};

#endif // CELL_H
