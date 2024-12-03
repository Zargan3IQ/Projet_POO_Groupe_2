#ifndef GRID_H
#define GRID_H

#include "Cell.h"
#include <vector>

class grid {
private:
    int width, height;
    std::vector<std::vector<Cell>> cells;

    void updateHalf(int start, int end);

public:
    grid(int w, int h);

    int getWidth() const;
    int getHeight() const;

    const Cell& getCell(int x, int y) const;

    std::vector<std::vector<Cell>> getState() const;

    void initializeWithState(const std::vector<std::vector<int>> &initialState);
    bool compareMatrix(const std::vector<std::vector<Cell>>& other) const;
    void update();

};

#endif // GRID_H