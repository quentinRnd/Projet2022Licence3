#ifndef PAUSE_HH
#define PAUSE_HH

#include <QAction>

// Une fenêtre contient une action execute
class Jeu;

// Met en pause l'exécution du programme du robot
class Pause:
	public QAction
{
	public:

		// Instancie une action pour mettre en pause dans le jeu
		explicit Pause(Jeu const & jeu);
};

#endif // PAUSE_HH
