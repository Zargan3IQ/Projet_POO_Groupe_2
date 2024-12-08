#ifndef MANAGEFILE_H
#define MANAGEFILE_H

#include <string>
#include <vector>
#include "grid.h"

// Classe FileManager : gestionnaire des fichiers pour une grille
// Cette classe permet de manipuler les fichiers d'entrée/sortie pour la sauvegarde
class FileManager {
private:
    std::string entryFile;  // Nom du fichier d'entrée à lire
    std::string directory;  // Nom du répertoire pour les fichiers de sortie

public:
    // Définit le nom du fichier d'entrée à utiliser.
    void setentryFile(std::string File);

    // Recupere le nom du fichier d'entrée à utiliser.
    std::string getentryFile();

    // Définit le répertoire où les fichiers seront créés/sauvegardés.
    void setDirectory(std::string Directory);

    // Recupere le nom du fichier d'entrée à utiliser.
    std::string getDirectory();

    // Permet de choisir un fichier interactivement.
    void choseFile();

    // Lit une grille depuis un fichier.
    // Retourne une matrice 2D représentant la grille (vecteur de vecteurs d'entiers).
    std::vector<std::vector<int>> readGrid(int &width, int &height);

    // Crée un répertoire pour sauvegarder les fichiers de sortie.
    void createDirectory();

    // Sauvegarde l'état actuel de la grille dans un fichier.
    void save(const grid &grid, int gen, int height, int width);
};

#endif // MANAGEFILE_H