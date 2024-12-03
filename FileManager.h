#ifndef MANAGEFILE_H
#define MANAGEFILE_H

#include <string>
#include <vector>

#include "grid.h"

class FileManager {
private:
    std::string entryFile;
    std::string directory;

public:
    void choseFile();
    std::vector<std::vector<int>> readGrid(int &width, int &height);
    void CreateDirectory();
    void Save(const grid &grid,int gen);
};

#endif // MANAGEFILE_H