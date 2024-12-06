#include "../src/grid.h"
#include "../src/FileManager.h"
#include <cassert>
#include <iostream>
#include <fstream>

static void testReadFile() {

    int width = 3, height = 3;
    std::string File = "..//tst//Files_Test//Test_File.txt";

    FileManager fileManager;
    grid initialState(width, height);
    grid expectedState(width, height);

    fileManager.setentryFile(File);

    auto initialFile = fileManager.readGrid(width, height);

    std::vector<std::vector<int>> expectedState2 = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };

    expectedState.initializeWithState(expectedState2);
    initialState.initializeWithState(initialFile);

    bool areEqual = initialState.compareMatrix(expectedState.getState());

    assert(areEqual);

    std::cout << "Test reussi : Le fichier est correctement lu et transforme en matrice" << std::endl;

}

/*
static void testSaveFile() {

    std::string File = "..//Tests//Files_Test//Tests_Save.txt";
    int width = 3, height = 3;

    FileManager fileManager;
    grid initialState(width, height);
    grid expectedState(width, height);

    fileManager.setentryFile(File);
    fileManager.CreateDirectory();

    std::vector<std::vector<int>> expectedState1 = {
        {0, 0, 1},
        {1, 0, 1},
        {0, 1, 1}
    };

    std::vector<std::vector<int>> expectedState2 = {
        {0, 0, 1},
        {1, 0, 1},
        {0, 1, 1}
    };

    std::string File2 = "..//Tests//Files_Test//Tests_Save_out//generation_0.txt";
    fileManager.setentryFile(File2);

    initialState.initializeWithState(expectedState1);
    expectedState.initializeWithState(expectedState2);

    fileManager.Save(initialState, 0);

    auto initialFile = fileManager.readGrid(width, height);

    bool areEqual = initialState.compareMatrix(expectedState.getState());

    assert(areEqual);

    std::cout << "Test reussi : Fichier correctement sauvegarde" << std::endl;
}

*/