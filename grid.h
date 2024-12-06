#ifndef GRID_H
#define GRID_H

#include "Cell.h"
#include <vector>

class grid {
private:
    int width, height;
    std::vector<std::vector<Cell>> cells;
    bool isToric;
    void updateHalf(int start, int end);

public:
    grid(int w, int h);

    int getWidth() const;
    int getHeight() const;
    bool getisToric() const;
    void setisToric(bool Toric);

    const Cell& getCell(int x, int y) const;
    Cell& getCell(int x, int y);

    std::vector<std::vector<Cell>> getState() const;

    void initializeWithState(const std::vector<std::vector<int>> &initialState);
    bool compareMatrix(const std::vector<std::vector<Cell>>& other) const;
    void update();
    void updateTest();

};

#endif // GRID_H