#include "objet.hh"

Objet::Objet
(
	std::array<Coordonnee::Distance, 3> const & position_xyz,
	std::array<Coordonnee::Angle, 3> const & orientation_xyz
):
	_position_xyz(position_xyz),
	_orientation_xyz(orientation_xyz),
	_position_xyz_initiale(position_xyz),
	_orientation_xyz_initiale(orientation_xyz)
{}


std::array<Coordonnee::Distance, 3> const & Objet::position_xyz() const
{
	return _position_xyz;
}

std::array<Coordonnee::Angle, 3> const & Objet::orientation_xyz() const
{
	return _orientation_xyz;
}

void Objet::position_xyz(std::array<Coordonnee::Distance, 3> const & position_xyz)
{
	_position_xyz = position_xyz;
}

void Objet::orientation_xyz(std::array<Coordonnee::Angle, 3> const & orientation_xyz)
{
	_orientation_xyz = orientation_xyz;
}

void Objet::reinitialise_parametres()
{
	_position_xyz = _position_xyz_initiale;
	_orientation_xyz = _orientation_xyz_initiale;
}

void Objet::positionne_oriente() const
{
	// Positionne
	glTranslated(_position_xyz[0], _position_xyz[1], _position_xyz[2]);

	// Oriente
	glRotated(_orientation_xyz[0], 1, 0, 0);
	glRotated(_orientation_xyz[1], 0, 1, 0);
	glRotated(_orientation_xyz[2], 0, 0, 1);
}
