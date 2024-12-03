#include "Interface.h"
#include <iostream>

Interface::Interface(const grid& g, int cellSize)
    : window(sf::VideoMode(g.getWidth() * cellSize, g.getHeight() * cellSize), "Game of Life"),
      statsWindow(sf::VideoMode(300, 200), "Statistiques"),
      cellSize(cellSize) {}

int Interface::getCellSize() const {
    return cellSize;
}

void Interface::render(const grid& g, int currentGeneration) {
    window.clear(sf::Color::White);

    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));

    int aliveCount = 0;

    for (int x = 0; x < g.getWidth(); ++x) {
        for (int y = 0; y < g.getHeight(); ++y) {
            int cellState = g.getCell(x, y).getIsAlive();
            if (cellState == 1) {
                aliveCount++;
                cell.setFillColor(sf::Color::Black);
            } else if (cellState == 2) {
                cell.setFillColor(sf::Color::Red);
            } else if (cellState == 3) {
                cell.setFillColor(sf::Color::Green);
                aliveCount++;
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
    rendStats(aliveCount, currentGeneration);
}

void Interface::rendStats(int aliveCount, int currentGeneration) {
    statsWindow.clear(sf::Color::White);

    sf::Font font;
    if (!font.loadFromFile("C://Users//exama//CLionProjects//Projet_POO_GameLife//Police//arial.ttf")) {
        std::cout << "Erreur: Impossible de charger la police." << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);

    text.setString("Cellules en vie: " + std::to_string(aliveCount) +
                   "\nGeneration actuelle: " + std::to_string(currentGeneration));

    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    // Centrer le texte dans la fenêtre
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                   textBounds.top + textBounds.height / 2.0f);
    text.setPosition(statsWindow.getSize().x / 2.0f, statsWindow.getSize().y / 2.0f);

    statsWindow.draw(text);
    statsWindow.display();
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
    while (statsWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            statsWindow.close();
    }
}

void Interface::display(const grid& g, int currentGeneration) const {
    std::cout << "Generation: " << currentGeneration << std::endl;
    for (int y = 0; y < g.getHeight(); y++) {
        for (int x = 0; x < g.getWidth(); x++) {
            std::cout << g.getCell(x, y).getIsAlive() << " ";
        }
        std::cout << std::endl;
    }
}