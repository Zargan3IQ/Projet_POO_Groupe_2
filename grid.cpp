#include "grid.h"
#include <thread>
#include <chrono>

// Builder de la classe grid
grid::grid(int w, int h) : width(w), height(h), cells(w, std::vector<Cell>(h)) {}

const Cell& grid::getCell(int x, int y) const {
    return cells[x][y];
}

std::vector<std::vector<Cell>> grid::getState() const {
    return cells;
}

int grid::getWidth() const {
    return width;
}
int grid::getHeight() const {
    return height;
}

void grid::initializeWithState(const std::vector<std::vector<int>> &initialState) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cells[x][y].setIsAlive(initialState[y][x]);
        }
    }
}

bool grid::compareMatrix(const std::vector<std::vector<Cell>> &other) const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (cells[x][y].getIsAlive() != other[x][y].getIsAlive()) {
                return false; // Les matrices ne sont pas égales
            }
        }
    }
    return true;
}



void grid::update_p1_t1() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height/2; y++) {
            cells[x][y].update(x, y, *this);
        }
    }

}
void grid::update_p2_t1() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height/2; y++) {
            cells[x][y].setIsAlive(cells[x][y].getWillBeAlive());
        }
    }
}


void grid::update_p1_t2() {
    for (int x = 0; x < width; x++) {
        for (int y = height/2; y < height; y++) {
            cells[x][y].update(x, y, *this);
        }
    }

}

void grid::update_p2_t2() {
    for (int x = 0; x < width; x++) {
        for (int y = height/2; y < height; y++) {
            cells[x][y].setIsAlive(cells[x][y].getWillBeAlive());
        }
    }
}

void grid::update() {
    std::vector<std::vector<Cell>> currentState = cells; // État actuel
    std::thread t1(&grid::update_p1_t1, this);
    std::thread t2(&grid::update_p1_t2, this);
    t1.join();
    t2.join();
    std::thread t3(&grid::update_p2_t1, this);
    std::thread t4(&grid::update_p2_t2, this);
    t4.join();
    t3.join();




}

