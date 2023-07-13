#ifndef DEMARRE_H
#define DEMARRE_H

#include <QAction>

// Une fenêtre contient une action execute
class Jeu;

// Exécute le programme chargé du robot
class Demarre:
	public QAction
{
	public:

		// Instancie une action pour exécuter dans le jeu
		explicit Demarre(Jeu const & jeu);
};

#endif // DEMARRE_H
