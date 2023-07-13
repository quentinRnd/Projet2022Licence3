#ifndef CONTINUE_HH
#define CONTINUE_HH

#include <QAction>

// Une fenêtre contient une action execute
class Jeu;

// Continue l'exécution du programme du robot mis en pause
class Continue:
	public QAction
{
	public:

		// Instancie une action pour continuer dans le jeu
		explicit Continue(Jeu const & jeu);
};

#endif // CONTINUE_HH
