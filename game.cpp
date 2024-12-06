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

    std::cout << "Choisissez le mode d'affichage :"<< std::endl;
    std::cout << "1. Console"<< std::endl;
    std::cout << "2. Graphique" << std::endl;
    std::cin >> mode;

    char toricChoice;
    std::cout << "Voulez-vous activer la grille torique ? (Y/N) : " << std::endl;
    std::cin >> toricChoice;
    Grid.setisToric(toricChoice == 'Y' || toricChoice == 'y');

    while (mode != 1 && mode != 2) {
        std::cout << "Le mode est inconnu : choisissez le mode d'affichage : "<< std::endl;
        std::cin >> mode;
    }

    if (mode == 2) {
        std::cout << "Entrez le temps entre chaque intervalle (ms) : " << std::endl;;
        std::cin >> intervalTime;
        int cellSize = 10;
        interface = new Interface(Grid, cellSize);
        interface->render(Grid, 0);
        // Attendre 10 secondes pour afficher la génération initiale
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }


    if (mode == 1) {
        fileManager.createDirectory();
        fileManager.save(Grid, 0);
        std::cout << "Etat initial de la grille :" << std::endl;
        interface->display(Grid, 0);
    }
}

void game::runConsoleMode() {
    for (int generation = 1; generation <= generationLimit; ++generation) {
        processGeneration(generation);
        interface->display(Grid, generation);
        fileManager.save(Grid, generation);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void game::runGraphicsMode() {
    for (int generation = 1; generation <= generationLimit; ++generation) {
        while (interface->isPaused()) {
            // Rendre la fenêtre (pour éviter qu'elle semble figée en pause).
            interface->pollEvents();
            interface->render(Grid, generation);
            if (!interface->isOpen()) {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        if (!interface->isOpen()) {
            std::cout << "Fenetre fermee. Fin du jeu." << std::endl;
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
        std::cout << "Fin du jeu : Etat stable atteint a la generation " << generation << std::endl;
        generationLimit = generation;
    }
}