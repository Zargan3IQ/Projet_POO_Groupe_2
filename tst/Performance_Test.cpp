#include <iostream>
#include <chrono>
#include "../src/grid.h"

static void testPerformance() {
    const int width = 150;
    const int height = 150;
    const int iterations = 2000;

    grid g(width, height);

    std::vector initialState(height, std::vector<int>(width, 0));

    g.initializeWithState(initialState);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        g.update();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Test de performance avec multithreading : " << iterations << " iterations avec une grille "
              << width << "x" << height << " prend "
              << duration.count() << " secondes." << std::endl;

    g.initializeWithState(initialState);

    auto start2 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        std::vector<std::vector<Cell>> currentState = g.getState();  // Sauvegarde de l'état actuel pour référence

        // Mise à jour de toutes les cellules, sans optimisation parallèle
        for (int x = 0; x < g.getWidth(); x++) {
            // Utilisation des dimensions de `g`
            for (int y = 0; y < g.getHeight(); y++) {
                g.getCell(x, y).update(x, y, g);  // Mise à jour en fonction des règles du jeu de la vie

            }
        }

        // Applique les mises à jour (transition des états "souhaités" vers l'état final)
        for (int x = 0; x < g.getWidth(); x++) {
            for (int y = 0; y < g.getHeight(); y++) {
                Cell& cell = g.getCell(x, y);  // Récupération d'une référence mutable
                cell.setIsAlive(cell.getWillBeAlive());  // Mise à jour finale de l'état des cellules
            }
        }
    }

    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;

    std::cout << "Test de performance sans multithreading : " << iterations << " iterations avec une grille "
              << width << "x" << height << " prend "
              << duration2.count() << " secondes." << std::endl;

}
