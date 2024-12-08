#include "../src/grid.h"
#include "../src/FileManager.h"
#include <cassert>
#include <iostream>
#include <fstream>

static void testsetentryFile() {
    FileManager fileManager;
    fileManager.setentryFile("test.txt");
    assert(fileManager.getentryFile() == "test.txt");
    std::cout << "Test reussi : Le setter EntryFile fonctionne" << std::endl;
}

static void testsetdirectory() {
    FileManager fileManager;
    fileManager.setDirectory("Directory/test.txt");
    assert(fileManager.getDirectory() == "Directory/test.txt");
    std::cout << "Test reussi : Le setter Directory fonctionne" << std::endl;
}

static void testReadFile() {

    int width = 3, height = 3;
    std::string File = "../Files_Test//Test_File.txt";

    FileManager fileManager;
    grid initialState(width, height);
    grid expectedState(width, height);

    fileManager.setentryFile(File);

    auto initialFile = fileManager.readGrid(width, height);

    std::vector<std::vector<int>> gridexpectedState = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };

    expectedState.initializeWithState(gridexpectedState);
    initialState.initializeWithState(initialFile);

    bool areEqual = initialState.compareMatrix(expectedState.getState());

    assert(areEqual);

    std::cout << "Test reussi : Le fichier est correctement lu et transforme en matrice" << std::endl;

}


static void testSaveFile() {
    std::string inputFile = "..//Files_Test//Tests_Save.txt";
    std::string outputFile = "..//Files_Test//Tests_Save_out//generation_0.txt";
    int width = 3, height = 3;

    FileManager fileManager;
    fileManager.setentryFile(inputFile);
    fileManager.createDirectory();

    std::vector<std::vector<int>> StateGrid = {
        {0, 0, 1},
        {1, 0, 1},
        {0, 1, 1}
    };

    grid initialState(width, height);
    grid expectedState(width, height);
    initialState.initializeWithState(StateGrid);
    expectedState.initializeWithState(StateGrid);

    fileManager.setentryFile(outputFile);
    fileManager.save(initialState, 0, width, height);

    auto savedState = fileManager.readGrid(width, height);
    initialState.initializeWithState(savedState);

    assert(expectedState.compareMatrix(initialState.getState()));

    std::cout << "Test reussi : Fichier correctement sauvegarde" << std::endl;
}
