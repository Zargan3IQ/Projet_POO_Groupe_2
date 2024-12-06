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
    void setentryFile(std::string File);
    void setDirectory(std::string Directory);
    void choseFile();
    std::vector<std::vector<int>> readGrid(int &width, int &height);
    void createDirectory();
    void save(const grid &grid,int gen);
};

#endif // MANAGEFILE_H