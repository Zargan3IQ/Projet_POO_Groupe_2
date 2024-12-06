#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include "grid.h"
#include <fcntl.h>

namespace fs = std::filesystem;

void FileManager::setentryFile(std::string File) {
    entryFile = File;
}

void FileManager::setDirectory(std::string Directory) {
    directory = Directory;
}

void FileManager::choseFile() {
    std::cout << "Entrez le nom du fichier d'entree : ";
    std::getline(std::cin, entryFile);
}

std::vector<std::vector<int>> FileManager::readGrid(int &width, int &height) {
    std::ifstream FileInput(entryFile);
    if (!FileInput.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier d'entree.\n";
        exit(EXIT_FAILURE);
    }

    if (FileInput.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "Erreur : Le fichier est vide.\n";
        exit(EXIT_FAILURE);
    }

    FileInput >> height >> width; // Lecture de la première ligne

    if (height <= 0 || width <= 0) {
        std::cerr << "Erreur : Dimensions invalides dans le fichier (doivent etre positives).\n";
        exit(EXIT_FAILURE);
    }

    std::vector grid(height, std::vector<int>(width));
    int cellCount = 0;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {

                if (!(FileInput >> grid[y][x])) {
                    std::cerr << "Erreur : Donnees insuffisantes dans le fichier pour remplir la grille.\n";
                    exit(EXIT_FAILURE);
                }

                if (grid[y][x] != 0 && grid[y][x] != 1 && grid[y][x] != 2 && grid[y][x] != 3) {
                    std::cerr << "Erreur : Données incomprehensible donnees en entree.\n";
                    exit(EXIT_FAILURE);
                }

                cellCount++;
            }
        }

    int extraData;
    if (FileInput >> extraData) {
        std::cerr << "Erreur : Trop de données dans le fichier, dépassant les dimensions spécifiées.\n";
        exit(EXIT_FAILURE);
    }

    if (cellCount != width * height) {
        std::cerr << "Erreur : Les dimensions spécifiées ne correspondent pas aux données fournies.\n";
        exit(EXIT_FAILURE);
    }

    FileInput.close();
    return grid;
}

void FileManager::createDirectory() {
    directory = entryFile.substr(0, entryFile.find_last_of('.')) + "_out";

    try {
        if (fs::create_directory(directory)) {
            std::cout << "Repertoire cree : " << directory << "\n";
        }
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de la création du répertoire : " << e.what() << "\n";
    }
}

void FileManager::save(const grid &grid, int gen) {
    std::string filePath = directory + "/generation_" + std::to_string(gen) + ".txt";

    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible de creer le fichier " << filePath << "\n";
        exit(EXIT_FAILURE);
    }

    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            file << grid.getCell(x, y).getIsAlive() << " ";
        }
        file << "\n";
    }
}