#include "../src/game.h"
#include "Grid_Test.cpp"
#include "Cell_Test.cpp"
#include "File_Test.cpp"
#include "Performance_Test.cpp"

int main() {
    testStabilityOfBlocks();
    testsetisAlive();
    testsetWillBeAlive();
    testGridState();
    testMatrixComparison();
    testReadFile();
    testSaveFile();
    testPerformance();
    return 0;
}