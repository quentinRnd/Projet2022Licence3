#ifndef COMPILE_HH
#define COMPILE_HH

#include <QAction>

// Une fenêtre contient une action compile
class Jeu;

// Compile le programme source depuis son fichier vers un fichier de destination
class Compile:
	public QAction
{
	public:

		// Instancie une action pour compiler dans le jeu
		explicit Compile(Jeu const & jeu);
};

#endif // COMPILE_HH
