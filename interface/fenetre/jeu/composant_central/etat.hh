#ifndef ETAT_HH
#define ETAT_HH

#include <QGridLayout>
#include <QGroupBox>
#include <QStackedLayout>

#include "etat/position.hh"
#include "etat/orientation.hh"

// Une fenêtre contient l'affichage d'état du robot
class Fenetre;

// Affiche l'état courant du robot
class Etat:
	public QWidget
{
	public:

		// Instancie un affichage d'état du robot dans un jeu
		explicit Etat(Fenetre const & fenetre);

	private:

		// Disposition de l'affichage d'état du robot
		QGridLayout _disposition;

		// Affiche la position du robot
		QGroupBox _ensemble_position;
		QStackedLayout _disposition_position;
		Position _position;

		// Affiche l'orientation du robot
		QGroupBox _ensemble_orientation;
		QStackedLayout _disposition_orientation;
		Orientation _orientation;
};

#endif // ETAT_HH
