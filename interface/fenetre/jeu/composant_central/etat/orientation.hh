#ifndef ORIENTATION_HH
#define ORIENTATION_HH

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

// Une fenêtre contient l'affichage de l'orientation du robot
class Fenetre;

// Affiche l'orientation du robot
class Orientation:
	public QWidget
{
	public:

		// Instancie un affichage de l'orientation du robot dans un jeu
		explicit Orientation(Fenetre const & fenetre);

	private:

		// Disposition de l'affichage de l'orientation du robot
		QGridLayout _disposition;

		// Orientation x
		QLabel _etiquette_x;
		QLabel _nombre_x;

		// Orientation y
		QLabel _etiquette_y;
		QLabel _nombre_y;

		// Orientation x
		QLabel _etiquette_z;
		QLabel _nombre_z;
};

#endif // ORIENTATION_HH
