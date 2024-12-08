#include "..//src/grid.h"
#include <cassert>
#include <iostream>

static void testsetHeight() {
    grid Grid(1,1);
    Grid.setHeight(30);
    assert(Grid.getHeight()==30);
    std::cout << "Test reussi : Le setter Height fonctionne" << std::endl;
}

static void testsetWidth() {
    grid Grid(1,1);
    Grid.setWidth(30);
    assert(Grid.getWidth()==30);
    std::cout << "Test reussi : Le setter Width fonctionne" << std::endl;
}

static void testsetToric() {
    grid Grid(1,1);
    Grid.setisToric(true);
    assert(Grid.getisToric());
    std::cout << "Test reussi : Le setter Toric fonctionne" << std::endl;
}

static void testInitializeWithState() {
    const int width = 3;
    const int height = 3;

    // État initial de la grille sous forme de matrice de 0 et 1
    std::vector<std::vector<int>> initialState = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 1, 1}
    };

    // Créer une grille de dimensions 3x3
    grid myGrid(width, height);

    // Initialiser la grille avec l'état spécifié
    myGrid.initializeWithState(initialState);

    // Vérifier que l'état des cellules correspond à l'état initial
    auto finalState = myGrid.getState();

    // Parcours de toutes les cellules pour vérifier leur état
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            assert(finalState[x][y].getIsAlive() == initialState[y][x]);
        }
    }

    std::cout << "Test reussi : L'initialisation avec l'etat donne est correcte." << std::endl;
}


static void testGridState() {

    const int width = 5;
    const int height = 5;

    std::vector<std::vector<int>> initialState = {
        {0, 0, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    };

    std::vector<std::vector<int>> expectedState = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1},
        {0, 0, 1, 1, 1},
        {0, 0, 0, 0, 0},
    };

    grid myGrid(width, height);
    myGrid.initializeWithState(initialState);

    for (int i = 0; i < 6; ++i) {
        myGrid.update();
    }

    auto finalState = myGrid.getState();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            assert(finalState[x][y].getIsAlive() == expectedState[y][x]);
        }
    }

    std::cout << "Test reussi : L'etat final apres 5 iterations est correct." << std::endl;
}

static void testMatrixComparison() {
    const int width = 4, height = 4;

    grid grid1(width, height);
    grid grid2(width, height);

    std::vector<std::vector<int>> initialState = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };

    std::vector<std::vector<int>> initialState2 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };

    grid1.initializeWithState(initialState);
    grid2.initializeWithState(initialState2);

    bool areEqual = grid1.compareMatrix(grid2.getState());

    assert(areEqual);

    std::cout << "Test reussi : La comparaison des matrices fonctionne." << std::endl;
}
