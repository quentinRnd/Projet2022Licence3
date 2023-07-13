#include "orientation.hh"
#include "../../../jeu.hh"

Orientation::Orientation(Fenetre const & /*fenetre*/):
	QWidget(),
	_disposition(this),

	// X
	_etiquette_x("x"),
	_nombre_x(),

	// Y
	_etiquette_y("y"),
	_nombre_y(),

	// Z
	_etiquette_z("z"),
	_nombre_z()
{
	// Ajoute l'affichage de l'orientation x
	_disposition.addWidget(&_etiquette_x, 0, 0);
	_disposition.addWidget(&_nombre_x, 0, 1);

	// Ajoute l'affichage de l'orientation y
	_disposition.addWidget(&_etiquette_y, 1, 0);
	_disposition.addWidget(&_nombre_y, 1, 1);

	// Ajoute l'affichage de l'orientation z
	_disposition.addWidget(&_etiquette_z, 2, 0);
	_disposition.addWidget(&_nombre_z, 2, 1);
}
