#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include "grid.h"

class Interface {
private:
    const int cellSize;
    sf::RenderWindow window;
    sf::RenderWindow statsWindow;

public:
    Interface(const grid& g, int cellSize);
    void render(const grid& g, int currentGeneration);
    bool isOpen() const;
    void pollEvents();
    int getCellSize() const;
    void display(const grid& g, int currentGeneration) const;
    void rendStats(int aliveCount, int currentGeneration);
};

#endif // INTERFACE_H
