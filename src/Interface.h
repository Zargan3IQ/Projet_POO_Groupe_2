#ifndef INTERFACE_H
#define INTERFACE_H
#include <SFML/Graphics.hpp>
#include "grid.h"

// Déclaration de la classe Interface qui gère l'affichage et l'interaction avec l'utilisateur.
class Interface {
private:
    const int cellSize; // La taille d'une cellule dans l'affichage graphique.
    sf::RenderWindow window; // Fenêtre principale d'affichage.
    sf::RenderWindow statsWindow; // Fenêtre secondaire pour afficher des informations statistiques.
    bool paused = false; // Booléen pour savoir si le jeu est en pause ou non.

public:
    Interface(const grid& g, int cellSize); // Constructeur de la classe Interface

    void render(const grid& g, int currentGeneration); // Méthode pour effectuer le rendu des éléments de la grille à l'écran.
    bool isOpen() const; // Méthode pour vérifier si la fenêtre principale est toujours ouverte.
    void pollEvents(); // Méthode pour récupérer les événements de la fenêtre
    void display(const grid& g, int currentGeneration) const; // Méthode pour afficher la grille sur la console
    void rendStats(int aliveCount, int currentGeneration); // Méthode pour afficher des informations statistiques comme le nombre de cellules vivantes et la génération actuelle.
    bool isPaused() const; // Méthode pour vérifier si le jeu est actuellement en pause.
};

#endif // INTERFACE_H
