#include "etat.hh"

Etat::Etat(Fenetre const & fenetre):
	QWidget(),
	_disposition(this),
	_ensemble_position("Position"),
	_disposition_position(&_ensemble_position),
	_position(fenetre),
	_ensemble_orientation("Orientation"),
	_disposition_orientation(&_ensemble_orientation),
	_orientation(fenetre)
{
	// Définie la disposition des éléments des ensembles
	_disposition_position.addWidget(&_position);
	_disposition_orientation.addWidget(&_orientation);

	// Définie la disposition des éléments de l'affichage d'état du robot
	_disposition.addWidget(&_ensemble_position, 0, 0);
	_disposition.addWidget(&_ensemble_orientation, 0, 1);
}
