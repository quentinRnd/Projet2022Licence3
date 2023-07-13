#ifndef ARRETE_HH
#define ARRETE_HH

#include <QAction>

// Une fenêtre contient une action arrête
class Jeu;

// Arrête l'exécution du programme du robot
class Arrete:
	public QAction
{
	public:

		// Instancie une action pour arrêter dans le jeu
		explicit Arrete(Jeu const & jeu);
};

#endif // ARRETE_HH
