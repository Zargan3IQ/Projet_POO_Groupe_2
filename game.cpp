#include "game.h"
#include <chrono>
#include <iostream>
#include <thread> // Pour std::this_thread::sleep_for

game::game()
        : Grid(1, 1), interface(nullptr), mode(0), intervalTime(1000), generationLimit(10000) {}

game::~game() {
    delete interface;
}

void game::start() {
    initializeGame();

    if (mode == 1) {
        runConsoleMode();
    } else if (mode == 2) {
        runGraphicsMode();
    }
}

void game::initializeGame() {
    fileManager.choseFile();

    int width, height;
    auto initialState = fileManager.readGrid(width, height);

    Grid = grid(width, height);
    Grid.initializeWithState(initialState);

    std::cout << "Choisissez le mode d'affichage :\n";
    std::cout << "1. Console\n";
    std::cout << "2. Graphique\n";
    std::cin >> mode;

    while (mode != 1 && mode != 2) {
        std::cout << "Le mode est inconnu : choisissez le mode d'affichage :\n";
        std::cin >> mode;
    }

    if (mode == 2) {
        std::cout << "Entrez le temps entre chaque intervalle (ms) : ";
        std::cin >> intervalTime;
        int cellSize = 10;
        interface = new Interface(Grid, cellSize);
    }

    std::cout << "Etat initial de la grille :\n";
    interface->display(Grid, 0);

    if (mode == 1) {
        fileManager.CreateDirectory();
        fileManager.Save(Grid, 0);
    }
}

void game::runConsoleMode() {
    for (int generation = 1; generation <= generationLimit; ++generation) {
        processGeneration(generation);
        interface->display(Grid, generation);
        fileManager.Save(Grid, generation);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
       }
}

void game::runGraphicsMode() {
    for (int generation = 1; generation <= generationLimit; ++generation) {
        if (!interface->isOpen()) {
            std::cout << "Fenetre fermee. Fin du jeu.\n";
            break;
        }

        interface->pollEvents();
        processGeneration(generation);
        interface->render(Grid, generation);
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalTime));
    }
}

void game::processGeneration(int generation) {
    auto previousState = Grid.getState();
    Grid.update();
    if (Grid.compareMatrix(previousState)) {
        std::cout << "Fin du jeu : Etat stable atteint a la generation " << generation << ".\n";
        generationLimit = generation;
    }
}