    #include "game.h"
    #include "FileManager.h"
    #include "Interface.h"
    #include <chrono>
    #include <iostream>

    void game::start() {
        int intervalTime;
        int mode;

        FileManager fileManager;
        fileManager.choseFile();

        int width, height;
        auto initialState = fileManager.readGrid(width, height);

        grid g(width, height);
        g.initializeWithState(initialState);

        std::cout << "Choisissez le mode d'affichage :\n";
        std::cout << "1. Console\n";
        std::cout << "2. Graphique\n";
        std::cin >> mode;

        while (mode != 1 && mode !=2) {
            std::cout << "Le mode est inconnu : choisissez le mode d'affichage :\n";
            std::cout << "1. Console\n";
            std::cout << "2. Graphique\n";
            std::cin >> mode;
        }

        int CellSize = 10;
        Interface interface(g, CellSize);

        std::cout << "Etat initial de la grille :\n";
        g.display();

        if (mode == 1) {
            fileManager.CreateDirectory();
            fileManager.Save(g, 0);
        }
        if (mode == 2) {
            std::cout << "Entrez le temps entre chaque intervalle : ";
            std::cin >> intervalTime;
        }

            for (int generation = 0; generation < 500; ++generation) {
                if (mode == 2) {
                    if (!interface.isOpen()) {
                        std::cout << "Fenetre fermee. Fin du jeu.\n";
                        break;
                    }
                    interface.pollEvents();
                }

                auto previousState = g.getState();
                g.update();

                if (g.compareMatrix(previousState)) {
                    std::cout << "Fin du jeu : Etat stable atteint a la generation : " << generation << ".\n";
                    break;
                }

                std::cout << "Generation " << generation + 1 << ":\n";

                if (mode == 1) {
                    g.display();
                    fileManager.Save(g, generation + 1);
                    sleep(sf::milliseconds(1000));
                } else {
                    interface.render(g);
                    sleep(sf::milliseconds(intervalTime));
                }
            }
        }
