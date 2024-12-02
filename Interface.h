#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include "grid.h"

class Interface {
private:
    const int cellSize;
    sf::RenderWindow window;

public:
    Interface(const grid& g, int cellSize);
    void render(const grid& g);
    bool isOpen() const;
    void pollEvents();
    int getCellSize() const;
    void display(const grid& g) const;
};

#endif // INTERFACE_H
