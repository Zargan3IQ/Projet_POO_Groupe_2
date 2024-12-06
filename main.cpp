#include "game.h"
#include "../tst/Grid_Test.cpp"
#include "../tst/Cell_Test.cpp"
#include "../tst/File_Test.cpp"
#include "../tst/Performance_Test.cpp"

int main() {
    game Life;
    testGridState();
    testMatrixComparison();
    testStabilityOfBlocks();
    testReadFile();
    testPerformance();
    //testSaveFile();
    Life.start();
    return 0;
}