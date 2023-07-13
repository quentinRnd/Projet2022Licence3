#include "position.hh"
#include "../../../jeu.hh"

Position::Position(Fenetre const & /*fenetre*/):
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
/*
	connect
	(
		jeu->composant_central()->modelisation()->niveau()->robot(),
		&Coordonnees::Coordonnees<GLdouble>::modifie_x,
		&_nombre_x,
		static_cast<void (QLCDNumber::*)(double)>(&QLCDNumber::display)
	);
*/
/*
	connect
	(
		static_cast<Coordonnees::Coordonnees<GLdouble> const *>(&jeu->composant_central()->modelisation()->niveau()->robot()->_position),
		static_cast<void (Coordonnees::Coordonnees<GLdouble>::*)(GLdouble) const>(&Coordonnees::Coordonnees<GLdouble>::modifie_x),
		&_nombre_x,
		static_cast<void (QLCDNumber::*)(double)>(&QLCDNumber::display)
	);
*/
	// Définie la disposition des éléments de l'affichage de la position du robot
	_disposition.addWidget(&_etiquette_x, 0, 0);
	_disposition.addWidget(&_nombre_x, 0, 1);
	_disposition.addWidget(&_etiquette_y, 1, 0);
	_disposition.addWidget(&_nombre_y, 1, 1);
	_disposition.addWidget(&_etiquette_z, 2, 0);
	_disposition.addWidget(&_nombre_z, 2, 1);
}
