#include "buisson.hh"

#include "../../../forme.hh"
#include "../../../texture.hh"

Buisson::Buisson
(
	std::array<Coordonnee::Distance, 3> const & position_xyz,
	std::array<Coordonnee::Angle, 3> const & orientation_xyz,
	Coordonnee::Distance const & diametre_xyz
):
	Objet_unique(position_xyz, orientation_xyz),
	_diametre_xyz(diametre_xyz)
{}

Coordonnee::Distance const & Buisson::diametre_xyz() const
{
	return _diametre_xyz;
}

void Buisson::contenu_liste()
{
	// Positionne le buisson au dessus de l'origine en y
	glTranslated(0, _diametre_xyz / 2, 0);

	// Modélise le buisson
	Forme::Dimension_3::sphere_texture(_diametre_xyz, Texture::Niveau::buisson);
}
