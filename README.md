# Projet Jeu de la Vie en C++

Ce projet implémente le célèbre "Jeu de la Vie" de John Conway en C++. Le Jeu de la Vie est un automate cellulaire basé sur une grille 2D où chaque cellule peut être vivante ou morte, et son état évolue au fil du temps en fonction de règles simples.

## Fonctionnalités

- **Grille dynamique** : Choisissez la taille de la grille.
- **Initialisation personnalisée** : Configurez l'état initial en le chargeant depuis un fichier.
- **Simulation automatique** : Laissez le programme exécuter automatiquement les générations.
- **Visualisation claire** : Affichage de l'état de la grille à chaque génération avec une interface graphique.
- **Sauvegarde** : Exportez les états de la grille vers des fichiers centralisés dans un dossier.

## Règles du Jeu de la Vie

1. Une cellule vivante avec **moins de 2 voisins vivants** meurt (sous-population).
2. Une cellule vivante avec **2 ou 3 voisins vivants** reste vivante.
3. Une cellule vivante avec **plus de 3 voisins vivants** meurt (surpopulation).
4. Une cellule morte avec **exactement 3 voisins vivants** devient vivante (reproduction).

## Prérequis

- Un compilateur C++ compatible avec la norme **C++11** ou supérieure (par exemple, g++, clang).
- Un système d'exploitation capable d'exécuter des applications C++.

## Initialisation

### Fichier d'entrée

Le fichier d'entrée devra contenir les dimensions de votre grille sur la première ligne et l'état initial de votre grille.
Chaque case de votre jeu de la vie devra être un des états suivants:

- **0 cellules mortes**

- **1 cellules vivantes**

- **2 cellules mortes immuables**

- **3 cellules vivantes immuables**

<ins> Exemple : </ins>

```plaintext
5 10
0 0 1 0 0 0 1 0 0 0
0 0 0 1 1 0 0 0 0 0
0 1 2 1 0 0 1 0 3 0
0 0 0 0 0 0 0 0 0 0
0 0 3 0 0 0 0 3 2 0
````

Le fichier d'entrée doit être au format txt.

Lors de l'exécution du programme, on vous demandera de renseigner l'emplacement du ficheir d'entrée, renseigner alors l'emplacement absolu. Cet emplacement sera aussi l'emplacement de sorti du dossier de sauvegarde.

### Choix des paramètres

Le programme va vous demander de chhoisir plusieurs paramètres, tels que l'activation de la grille torique (grille dont les bords opposés sont interconnectés), le nombre de génération ou le choix du mode.

## Les modes

### Mode Console

Dans ce mode, les générations sont affichés dans la console, les unes après les autres, en plus d'être enregistré dans un dossier nommé d'après le fichier d'entrée, et trouvable au même endroit que ce fichier. Dans le cas où un dossier du même nom existe déjà, on rajoute une numérotation au dossier pour éviter la superposition de données.

### Mode Graphique

Dans ce mode, les générations sont affichées dans une interface graphique dédiée. Il vous sera demander de renseigner l'intervalle souhaitée entre chaque génération.

> [!Caution]
> Ce mode ne comporte pas de sauvegarde.



<ins> Représentation visuelle: </ins>

⬜️ **Cellules mortes**

⬛️ **Cellules vivantes**

🟥 **Cellules mortes immuables**

🟩 **Cellules vivantes immuables**
