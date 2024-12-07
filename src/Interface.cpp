#include "Interface.h"
#include <iostream>

// Le constructeur de la classe Interface initialise deux fenêtres : une pour le rendu du jeu et une autre pour afficher les statistiques.
Interface::Interface(const grid& g, int cellSize)
    : window(sf::VideoMode(g.getWidth() * cellSize, g.getHeight() * cellSize), "Game of Life"),  // Fenêtre principale pour le jeu
      statsWindow(sf::VideoMode(300, 200), "Statistiques"),  // Fenêtre secondaire pour les statistiques
      cellSize(cellSize) {  // Initialisation de la taille de la cellule
}

// La méthode render est responsable de l'affichage de la grille et des cellules à l'écran.
void Interface::render(const grid& g, int currentGeneration) {
    // Efface la fenêtre principale avec une couleur blanche avant de dessiner.
    window.clear(sf::Color::White);

    // Déclaration d'une forme rectangle pour chaque cellule.
    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));

    int aliveCount = 0;  // Compteur pour les cellules vivantes

    // Parcours de chaque cellule de la grille pour l'affichage.
    for (int x = 0; x < g.getWidth(); ++x) {
        for (int y = 0; y < g.getHeight(); ++y) {
            int cellState = g.getCell(x, y).getIsAlive();  // Récupère l'état de la cellule (vivante, morte, etc.)

            // Si la cellule est vivante, la colorier en noir. Si c'est un obstacle mort ou vivant, colorier en rouge ou vert.
            if (cellState == 1) {
                aliveCount++;  // Incrémente le compteur des cellules vivantes
                cell.setFillColor(sf::Color::Black);
            } else if (cellState == 2) {
                cell.setFillColor(sf::Color::Red);  // Cellule obstacles morte donc colorée en rouge
            } else if (cellState == 3) {
                cell.setFillColor(sf::Color::Green);  // Cellule dans un autre état spécial
                aliveCount++;
            } else {
                cell.setFillColor(sf::Color::White);  // Cellule morte
            }

            // Positionne la cellule sur la fenêtre selon ses coordonnées (x, y).
            cell.setPosition(x * cellSize, y * cellSize);
            window.draw(cell);  // Dessine la cellule à sa position
        }
    }

    // Dessin de la grille (lignes de séparation entre les cellules)
    sf::Vertex line[2];  // Déclare deux sommets pour dessiner une ligne
    line[0].color = sf::Color::Black;  // Définition de la couleur de la ligne
    line[1].color = sf::Color::Black;

    // Dessin des lignes verticales pour la grille
    for (int x = 0; x <= g.getWidth(); ++x) {
        line[0].position = sf::Vector2f(x * cellSize, 0);  // Première extrémité de la ligne
        line[1].position = sf::Vector2f(x * cellSize, g.getHeight() * cellSize);  // Deuxième extrémité
        window.draw(line, 2, sf::Lines);  // Dessine la ligne
    }

    // Dessin des lignes horizontales pour la grille
    for (int y = 0; y <= g.getHeight(); ++y) {
        line[0].position = sf::Vector2f(0, y * cellSize);
        line[1].position = sf::Vector2f(g.getWidth() * cellSize, y * cellSize);
        window.draw(line, 2, sf::Lines);
    }

    window.display();  // Affiche tout ce qui a été dessiné dans la fenêtre principale
    rendStats(aliveCount, currentGeneration);  // Met à jour et affiche les statistiques dans la fenêtre secondaire
}

// La méthode rendStats est responsable de l'affichage des statistiques dans la fenêtre secondaire.
void Interface::rendStats(int aliveCount, int currentGeneration) {
    // Efface la fenêtre des statistiques avec une couleur blanche avant de dessiner.
    statsWindow.clear(sf::Color::White);

    sf::Font font;
    // Charge la police de caractère à partir d'un fichier (si l'échec, afficher un message d'erreur)
    if (!font.loadFromFile("..//Police//arial.ttf")) {
        std::cout << "Erreur: Impossible de charger la police." << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);  // Associe la police de caractère au texte

    // Crée le texte à afficher, en incluant le nombre de cellules vivantes et la génération actuelle.
    text.setString("Cellules en vie: " + std::to_string(aliveCount) +
                   "\nGeneration actuelle: " + std::to_string(currentGeneration));

    text.setCharacterSize(24);  // Taille du texte
    text.setFillColor(sf::Color::Black);  // Couleur du texte

    // Centrage du texte dans la fenêtre des statistiques
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                   textBounds.top + textBounds.height / 2.0f);
    text.setPosition(statsWindow.getSize().x / 2.0f, statsWindow.getSize().y / 2.0f);

    statsWindow.draw(text);  // Dessine le texte dans la fenêtre des statistiques
    statsWindow.display();  // Affiche le texte dans la fenêtre des statistiques
}

// Méthode pour vérifier si la fenêtre principale est ouverte.
bool Interface::isOpen() const {
    return window.isOpen();
}

// Méthode pour vérifier si le jeu est en pause.
bool Interface::isPaused() const {
    return paused;
}

// La méthode pollEvents permet de gérer les événements de la fenêtre, comme les clics, les touches de clavier, etc.
void Interface::pollEvents() {
    sf::Event event;
    // Gère les événements de la fenêtre principale.
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();  // Ferme la fenêtre si un événement de fermeture est reçu.

        if (event.type == sf::Event::KeyPressed) {
            // Si la touche "Espace" est pressée, inverse l'état de pause.
            if (event.key.code == sf::Keyboard::Space) {
                paused = !paused;
            }
        }
    }

    // Gère les événements de la fenêtre des statistiques.
    while (statsWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            statsWindow.close();  // Ferme la fenêtre des statistiques si un événement de fermeture est reçu.
    }
}

// Méthode qui affiche l'état de la grille dans la console.
void Interface::display(const grid& g, int currentGeneration) const {
    std::cout << "Generation: " << currentGeneration << std::endl;
    for (int y = 0; y < g.getHeight(); y++) {
        for (int x = 0; x < g.getWidth(); x++) {
            std::cout << g.getCell(x, y).getIsAlive() << " ";  // Affiche l'état de chaque cellule
        }
        std::cout << std::endl;  // Nouvelle ligne pour chaque ligne de la grille
    }
}
