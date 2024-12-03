#include "grid.h"
#include <thread>
#include <chrono>
#include <cmath>
#include <iostream>

// Builder de la classe grid
grid::grid(int w, int h) : width(w), height(h), cells(w, std::vector<Cell>(h)) {
    if (w <= 0 || h <= 0) {
        std::cerr <<" Error in grid initialization, incorrect width or heigt";
        exit(EXIT_FAILURE);
    }
}

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

void grid::updateHalf(int start, int end) {
    for (int y = start; y < end; ++y) {
        for (int x = 0; x < width; ++x) {
            cells[x][y].update(x, y, *this);
        }
    }
}

void grid::update() {
    if (width<2) {
        updateHalf(0, height);
    }
    else {
        std::vector<std::vector<Cell>> previousState = cells;

        // Mise à jour parallèle
        std::thread t1(&grid::updateHalf, this, 0, height / 2);
        std::thread t2(&grid::updateHalf, this, height / 2, height);

        t1.join();
        t2.join();

        // Appliquer les mises à jour
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                cells[x][y].setIsAlive(cells[x][y].getWillBeAlive());
            }
        }
    }
}