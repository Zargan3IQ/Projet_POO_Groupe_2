#include "../src/grid.h"
#include "../src/cell.h"
#include <cassert>
#include <iostream>

static void testsetisAlive() {
    Cell cell;
    cell.setIsAlive(true);
    cell.getIsAlive();
    assert(cell.getIsAlive());
    std::cout << "Test reussi : Le setter isAlive fonctionne" << std::endl;
}

static void testsetWillBeAlive() {
    Cell cell;
    cell.setWillBeAlive(true);
    cell.getWillBeAlive();
    assert(cell.getWillBeAlive());
    std::cout << "Test reussi : Le setter willBeAlive fonctionne" << std::endl;
}

static void testStabilityOfBlocks() {
    grid g(3, 3);

    // Test pour l'état 2
    g.initializeWithState({
        {0, 0, 0},
        {0, 2, 0},
        {0, 0, 0}
    });

    for (int i = 0; i < 10; ++i) {
        g.update();
    }

    auto Grid = g.getState();

    assert(Grid[1][1].getIsAlive() == 2);

    g.initializeWithState({
    {0, 0, 0},
    {0, 3, 1},
    {0, 1, 1}
});

    for (int i = 0; i < 10; ++i) {
        g.update();
    }

    auto Grid2 = g.getState();

    assert(Grid2[1][1].getIsAlive() == 3);

    std::cout << "Test reussi : Stabilite des etats 2 et 3 passe." << std::endl;
}
