#include "game.h"
#include <chrono>
#include <iostream>
#include <thread> // Pour std::this_thread::sleep_for

game::game()
    : g(0, 0), interface(nullptr), mode(0), intervalTime(1000), generationLimit(2000) {}

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

    g = grid(width, height);
    g.initializeWithState(initialState);

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
        interface = new Interface(g, 10);
    }

    std::cout << "Etat initial de la grille :\n";
    interface->display(g);

    if (mode == 1) {
        fileManager.CreateDirectory();
        fileManager.Save(g, 0);
    }
}

void game::runConsoleMode() {
    for (int generation = 1; generation <= generationLimit; ++generation) {
        processGeneration(generation);
        interface->display(g);
        fileManager.Save(g, generation);

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
        interface->render(g);
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalTime));
    }
}

void game::processGeneration(int generation) {
    auto previousState = g.getState();
    g.update();
    std::cout << "Generation : " << generation << std::endl;

    if (g.compareMatrix(previousState)) {
        std::cout << "Fin du jeu : Etat stable atteint a la generation " << generation << ".\n";
        generationLimit = generation;
    }
}
