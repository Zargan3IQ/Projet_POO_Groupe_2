#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include "grid.h"

class Interface {
private:
    const int cellSize;
    sf::RenderWindow window;
    sf::RenderWindow statsWindow;
    bool paused = false; // Indique si le jeu est en pause.

public:
    Interface(const grid& g, int cellSize);
    void render(const grid& g, int currentGeneration);
    bool isOpen() const;
    void pollEvents();
    void display(const grid& g, int currentGeneration) const;
    void rendStats(int aliveCount, int currentGeneration);
    bool isPaused() const; // Ajout de l'accès à l'état de pause.
};

#endif // INTERFACE_H
