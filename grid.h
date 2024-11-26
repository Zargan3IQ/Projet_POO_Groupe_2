#ifndef GRID_H
#define GRID_H

#include "Cell.h"
#include <vector>

class grid {
public:
    int width, height;
    std::vector<std::vector<Cell>> cells;

    grid(int w, int h);
    void createGrid();
    void update();
    Cell& getCell(int x, int y);
    const Cell& getCell(int x, int y) const;
    bool compareMatrix(std::vector<std::vector<Cell>> other) const;
    void display() const;
    void initializeWithState(const std::vector<std::vector<bool>> &initialState);
};

#endif // GRID_H