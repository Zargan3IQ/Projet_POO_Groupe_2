#include "../src/game.h"
#include "Grid_Test.cpp"
#include "Cell_Test.cpp"
#include "File_Test.cpp"
#include "Performance_Test.cpp"

int main() {
    testStabilityOfBlocks();
    testsetisAlive();
    testsetWillBeAlive();
    testsetHeight();
    testsetWidth();
    testsetToric();
    testInitializeWithState();
    testGridState();
    testMatrixComparison();
    testsetentryFile();
    testsetdirectory();
    testReadFile();
    testSaveFile();
    testPerformance();
    return 0;
}