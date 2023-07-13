#ifndef POSITION_HH
#define POSITION_HH

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

// Une fenêtre contient l'affichage de la position du robot
class Fenetre;

// Affiche le position du robot
class Position:
	public QWidget
{
	public:

		// Instancie un affichage de la position du robot dans u jeu
		explicit Position(Fenetre const & fenetre);

	private:

		// Disposition de l'affichage de la position du robot
		QGridLayout _disposition;

		// Position x
		QLabel _etiquette_x;
		QLabel _nombre_x;

		// Position y
		QLabel _etiquette_y;
		QLabel _nombre_y;

		// Position x
		QLabel _etiquette_z;
		QLabel _nombre_z;
};

#endif // POSITION_HH
