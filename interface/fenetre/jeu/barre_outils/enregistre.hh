#ifndef ENREGISTRE_HH
#define ENREGISTRE_HH

#include <QAction>

// Une fenêtre contient une action enregistre
class Jeu;

// Enregistre le programme source de l'éditeur de texte dans un fichier
class Enregistre:
	public QAction
{
	public:

		// Instancie une action pour enregistrer dans le jeu
		explicit Enregistre(Jeu const & jeu);
};

#endif // ENREGISTRE_HH
