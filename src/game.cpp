#include "game.h"
#include <chrono>      // Pour les délais avec std::chrono
#include <iostream>    // Pour les entrées/sorties standard
#include <thread>      // Pour std::this_thread::sleep_for

// Constructeur par défaut : initialise les membres avec des valeurs par défaut
game::game()
        : Grid(1, 1), // Initialisation d'une grille de dimensions 1x1
          interface(nullptr), // Pas d'interface associée initialement
          mode(0), // Mode d'affichage non défini
          intervalTime(1000), // Intervalle par défaut entre générations (en ms)
          generationLimit(10000) {} // Limite de générations par défaut

// Destructeur : libère la mémoire allouée dynamiquement pour l'interface
game::~game() {
    delete interface;
}

// Point d'entrée principal pour démarrer le jeu
void game::start() {
    initializeGame(); // Initialise la grille et les paramètres du jeu

    // Exécute le mode sélectionné (console ou graphique)
    if (mode == 1) {
        runConsoleMode();
    } else if (mode == 2) {
        runGraphicsMode();
    }
}

// Initialisation du jeu : lecture de la grille, choix des options et configuration initiale
void game::initializeGame() {
    fileManager.choseFile(); // Demande à l'utilisateur de choisir un fichier d'entrée

    int width, height;
    // Lit l'état initial de la grille depuis le fichier
    auto initialState = fileManager.readGrid(width, height);

    // Configure la grille avec les dimensions et l'état initial
    Grid = grid(width, height);
    Grid.initializeWithState(initialState);

    // Demande à l'utilisateur de choisir le mode d'affichage (console ou graphique)
    std::cout << "Choisissez le mode d'affichage :" << std::endl;
    std::cout << "1. Console" << std::endl;
    std::cout << "2. Graphique" << std::endl;
    std::cin >> mode;

    // Si le mode d'affichage est inconnu, redemander jusqu'à ce qu'un choix valide soit fait
    while (mode != 1 && mode != 2) {
        std::cout << "Le mode est inconnu : choisissez le mode d'affichage : " << std::endl;
        std::cin >> mode;
    }

    char toricChoice;
    std::cout << "Voulez-vous activer la grille torique ? (Y/N) : " << std::endl;
    std::cin >> toricChoice;

    while (toricChoice != 'Y' && toricChoice != 'y' && toricChoice != 'N' && toricChoice != 'n') {
        // Vérifie si l'entrée est valide
        std::cout << "Entree invalide. Veuillez entrer 'Y' ou 'N'." << std::endl;
        std::cin >> toricChoice;
    }

    // Appliquer le choix de l'utilisateur
    Grid.setisToric(toricChoice == 'Y' || toricChoice == 'y');


    std::cout << "Combien d'iterations voulez vous ? : " << std::endl;
    std::cin >> generationLimit;

    // Configuration spécifique au mode graphique
    if (mode == 2) {
        std::cout << "Entrez le temps entre chaque intervalle (ms) : " << std::endl;
        std::cin >> intervalTime; // Temps d'intervalle personnalisé

        int cellSize = 10; // Taille des cellules dans la fenêtre graphique
        interface = new Interface(Grid, cellSize); // Crée l'interface graphique
        interface->render(Grid, 0); // Affiche la génération initiale
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Pause de 5 secondes
    }

    // Configuration spécifique au mode console
    if (mode == 1) {
        fileManager.createDirectory(); // Crée un répertoire pour sauvegarder les fichiers de sortie
        fileManager.save(Grid, 0, Grid.getHeight(), Grid.getWidth()); // Sauvegarde l'état initial
        std::cout << "Etat initial de la grille :" << std::endl;
        interface->display(Grid, 0); // Affiche l'état initial de la grille
    }
}

// Mode console : exécution en boucle jusqu'à atteindre la limite de générations ou un état stable
void game::runConsoleMode() {
    for (int generation = 1; generation <= generationLimit; ++generation) {
        interface->display(Grid, generation); // Affiche la grille mise à jour
        fileManager.save(Grid, generation, Grid.getHeight(), Grid.getWidth()); // Sauvegarde la grille
        processGeneration(generation); // Met à jour la grille pour la génération actuelle

        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Pause entre générations
    }
}

// Mode graphique : gestion des événements et exécution en boucle jusqu'à atteindre la limite de générations ou un état stables
void game::runGraphicsMode() {
    for (int generation = 1; generation <= generationLimit; ++generation) {
        while (interface->isPaused()) { // Si le jeu est en pause
            interface->pollEvents(); // Gère les événements (fermeture, reprise, etc.)
            interface->render(Grid, generation); // Rafraîchit l'affichage pour éviter que la fenêtre semble figée
            if (!interface->isOpen()) { // Si la fenêtre est fermée
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pause pour limiter la charge CPU
        }

        if (!interface->isOpen()) { // Si la fenêtre est fermée, sortir de la boucle
            std::cout << "Fenetre fermee. Fin du jeu." << std::endl;
            break;
        }

        interface->pollEvents(); // Gère les événements pendant l'exécution
        processGeneration(generation); // Met à jour la grille pour la génération actuelle
        interface->render(Grid, generation); // Affiche la grille mise à jour
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalTime)); // Pause personnalisée
    }
}

// Met à jour la grille et vérifie si un état stable est atteint
void game::processGeneration(int generation) {
    auto previousState = Grid.getState(); // Sauvegarde l'état actuel
    Grid.update(); // Met à jour la grille selon les règles du jeu
    if (Grid.compareMatrix(previousState)) { // Vérifie si l'état actuel est identique au précédent
        std::cout << "Fin du jeu : Etat stable atteint a la generation " << generation << std::endl;
        generationLimit = generation; // Limite les générations si un état stable est atteint
    }
}
