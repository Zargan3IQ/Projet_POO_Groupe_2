#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include "grid.h"

namespace fs = std::filesystem;

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

    FileInput >> height >> width; //Lecture de la ppremière ligne
    std::vector grid(height, std::vector<int>(width));

    // Lecture de la matrice
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int cell;
            FileInput >> cell;
            grid[y][x] = cell;
        }
    }

    FileInput.close();
    return grid;

}

void FileManager::CreateDirectory() {
    directory = entryFile.substr(0, entryFile.find_last_of('.')) + "_out";

    try {
        if (fs::create_directory(directory)) {
            std::cout << "Repertoire cree : " << directory << "\n";
        }
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de la création du répertoire : " << e.what() << "\n";
    }
}

void FileManager::Save(const grid &grid, int gen) {
    std::string filePath = directory + "/generation_" + std::to_string(gen) + ".txt";

    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible de creer le fichier " << filePath << "\n";
        return;
    }

    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            file << grid.getCell(x, y).getIsAlive() << " ";
        }
        file << "\n";
    }
}