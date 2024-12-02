#include "Interface.h"
#include <iostream>

Interface::Interface(const grid& g, int cellSize)
    : window(sf::VideoMode(g.getWidth() * cellSize, g.getHeight() * cellSize), "Game of Life"),
      cellSize(cellSize) {}

int Interface::getCellSize() const {
    return cellSize;
}

void Interface::render(const grid& g) {

    window.clear(sf::Color::White);

    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));

    for (int x = 0; x < g.getWidth(); ++x) {
        for (int y = 0; y < g.getHeight(); ++y) {
            if (g.getCell(x, y).getIsAlive() == 1) {
                cell.setFillColor(sf::Color::Black);
            } else if (g.getCell(x, y).getIsAlive() == 2) {
                cell.setFillColor(sf::Color::Red);
            } else if (g.getCell(x, y).getIsAlive() == 3) {
                cell.setFillColor(sf::Color::Green);
            } else {
                cell.setFillColor(sf::Color::White);
            }
            cell.setPosition(x * cellSize, y * cellSize);
            window.draw(cell);
        }
    }

    // Dessiner la grille
    sf::Vertex line[2];
    line[0].color = sf::Color::Black;
    line[1].color = sf::Color::Black;

    // Lignes verticales
    for (int x = 0; x <= g.getWidth(); ++x) {
        line[0].position = sf::Vector2f(x * cellSize, 0);
        line[1].position = sf::Vector2f(x * cellSize, g.getHeight() * cellSize);
        window.draw(line, 2, sf::Lines);
    }

    // Lignes horizontales
    for (int y = 0; y <= g.getHeight(); ++y) {
        line[0].position = sf::Vector2f(0, y * cellSize);
        line[1].position = sf::Vector2f(g.getWidth() * cellSize, y * cellSize);
        window.draw(line, 2, sf::Lines);
    }

    window.display();
}

bool Interface::isOpen() const {
    return window.isOpen();
}

void Interface::pollEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Interface::display(const grid& g) const {
    for (int y = 0; y < g.getHeight(); y++) {
        for (int x = 0; x < g.getWidth(); x++) {
            std::cout << g.getCell(x, y).getIsAlive() << " ";
        }
        std::cout << std::endl;
    }
}