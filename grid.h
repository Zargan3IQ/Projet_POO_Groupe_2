#ifndef GRID_H
#define GRID_H

#include "Cell.h"
#include <vector>

class grid {
private:
    int width, height;
    std::vector<std::vector<Cell>> cells;
    void update_p1_t1();

    void update_p2_t1() ;
    void update_p1_t2() ;
    void update_p2_t2() ;

public:
    grid(int w, int h);

    int getWidth() const;
    int getHeight() const;
    std::vector<std::vector<Cell>> getState() const;

    Cell& getCell(int x, int y);
    const Cell& getCell(int x, int y) const;

    void initializeWithState(const std::vector<std::vector<int>> &initialState);
    bool compareMatrix(const std::vector<std::vector<Cell>>& other) const;
    void update();


    //void display() const;
};

#endif // GRID_H
