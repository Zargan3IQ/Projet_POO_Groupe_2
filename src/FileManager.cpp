#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

// Utilisation de l'espace de noms std::filesystem pour simplifier l'accès
namespace fs = std::filesystem;

// Définit le fichier d'entrée
void FileManager::setentryFile(std::string File) {
    entryFile = File; // Stocke le nom du fichier d'entrée
}

// Définit le répertoire pour les fichiers de sortie
void FileManager::setDirectory(std::string Directory) {
    directory = Directory; // Stocke le chemin du répertoire
}

// Permet à l'utilisateur de saisir le nom du fichier d'entrée via la console
void FileManager::choseFile() {
    std::cout << "Entrez le nom du fichier d'entree : ";
    std::getline(std::cin, entryFile); // Lit une ligne complète (y compris les espaces)
}

// Lit une grille à partir d'un fichier et retourne un tableau 2D
std::vector<std::vector<int>> FileManager::readGrid(int &width, int &height) {
    std::ifstream FileInput(entryFile); // Ouvre le fichier d'entrée en lecture
    if (!FileInput.is_open()) { // Vérifie si le fichier est accessible
        std::cerr << "Erreur : Impossible d'ouvrir le fichier d'entree.\n";
        exit(EXIT_FAILURE); // Arrête le programme en cas d'erreur
    }

    if (FileInput.peek() == std::ifstream::traits_type::eof()) { // Vérifie si le fichier est vide, peek permet de voir le prochain caractère a lire et si il n'existe pas et donc que le fichier est vide peek reneverras eof
        std::cerr << "Erreur : Le fichier est vide.\n";
        exit(EXIT_FAILURE);
    }

    FileInput >> height >> width; // Lecture des dimensions de la grille depuis le fichier

    // Vérifie si les dimensions sont valides
    if (height <= 0 || width <= 0) {
        std::cerr << "Erreur : Dimensions invalides dans le fichier (doivent etre positives).\n";
        exit(EXIT_FAILURE);
    }

    // Initialise une matrice 2D avec les dimensions spécifiées
    std::vector grid(height, std::vector<int>(width));
    int cellCount = 0; // Compte le nombre de cellules lues

    // Parcours de chaque cellule pour lire ses valeurs
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Vérifie qu'il y a suffisamment de données dans le fichier
            if (!(FileInput >> grid[y][x])) {
                std::cerr << "Erreur : Donnees insuffisantes dans le fichier pour remplir la grille.\n";
                exit(EXIT_FAILURE);
            }

            // Vérifie que chaque cellule contient une valeur valide (0, 1, 2 ou 3)
            if (grid[y][x] != 0 && grid[y][x] != 1 && grid[y][x] != 2 && grid[y][x] != 3) {
                std::cerr << "Erreur : Données incomprehensibles donnees en entree.\n";
                exit(EXIT_FAILURE);
            }

            cellCount++; // Incrémente le compteur de cellules
        }
    }

    // Vérifie s'il reste des données supplémentaires dans le fichier
    int extraData;
    if (FileInput >> extraData) {
        std::cerr << "Erreur : Trop de données dans le fichier, dépassant les dimensions spécifiées.\n";
        exit(EXIT_FAILURE);
    }

    // Vérifie que le nombre total de cellules correspond aux dimensions spécifiées
    if (cellCount != width * height) {
        std::cerr << "Erreur : Les dimensions spécifiées ne correspondent pas aux données fournies.\n";
        exit(EXIT_FAILURE);
    }

    FileInput.close(); // Ferme le fichier après lecture
    return grid; // Retourne la grille lue
}

// Crée un répertoire pour sauvegarder les fichiers de sortie
void FileManager::createDirectory() {
    // Génère un nom de répertoire basé sur le nom du fichier d'entrée
    directory = entryFile.substr(0, entryFile.find_last_of('.')) + "_out";

    try {
        // Crée le répertoire
        if (fs::create_directory(directory)) {
            std::cout << "Repertoire cree : " << directory << "\n"; // Confirmation
        }
    } catch (const std::exception &e) {
        // Gestion des erreurs lors de la création du répertoire
        std::cerr << "Erreur lors de la création du répertoire : " << e.what() << "\n";
    }
}

// Sauvegarde l'état de la grille dans un fichier
void FileManager::save(const grid &grid, int gen, int height, int width) {
    // Construit le chemin complet du fichier de sauvegarde
    std::string filePath = directory + "/generation_" + std::to_string(gen) + ".txt";

    std::ofstream file(filePath); // Ouvre le fichier en écriture
    if (!file.is_open()) { // Vérifie si le fichier est accessible
        std::cerr << "Erreur : Impossible de creer le fichier " << filePath << "\n";
        exit(EXIT_FAILURE);
    }

    // Écrit les dimensions de la grille au début du fichier
    file << height << " " << width << "\n";

    // Parcourt chaque cellule pour enregistrer son état
    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            file << grid.getCell(x, y).getIsAlive() << " "; // Écrit l'état de la cellule
        }
        file << "\n"; // Nouvelle ligne après chaque rangée
    }

    file.close(); // Ferme le fichier après écriture
}