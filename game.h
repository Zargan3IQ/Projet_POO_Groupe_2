#ifndef GAME_H
#define GAME_H

#include "grid.h"
#include "FileManager.h"
#include "Interface.h"

class game {
private:
    grid Grid;                       // La grille du jeu
    FileManager fileManager;      // Gestionnaire de fichiers
    Interface* interface;         // Interface graphique (optionnelle)
    int mode;                     // Mode d'affichage
    int intervalTime;             // Temps entre générations (mode graphique)
    int generationLimit;          // Limite des générations

    void initializeGame();        // Initialisation du jeu
    void runConsoleMode();        // Mode console
    void runGraphicsMode();       // Mode graphique
    void processGeneration(int generation); // Traiter une génération

public:
    game();
    ~game();
    void start();                 // Lancer le jeu
};

#endif // GAME_H
