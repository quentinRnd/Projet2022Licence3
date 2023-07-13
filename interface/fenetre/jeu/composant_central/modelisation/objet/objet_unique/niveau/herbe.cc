#include "herbe.hh"

#include "../../../forme.hh"
#include "../../../texture.hh"

Herbe::Herbe
(
	std::array<Coordonnee::Distance, 3> const & position_xyz,
	std::array<Coordonnee::Angle, 3> const & orientation_xyz,
	std::array<Coordonnee::Distance, 3> const & taille_xyz
):
	Objet_unique(position_xyz, orientation_xyz),
	_taille_xyz(taille_xyz)
{}

std::array<Coordonnee::Distance, 3> const & Herbe::taille_xyz() const
{
	return _taille_xyz;
}

void Herbe::contenu_liste()
{
	// Positionne l'herbe en dessous de l'origine en y
	glTranslated(0, -_taille_xyz[1] / 2, 0);

	// Modélise le pavé d'herbe
	Forme::Dimension_3::pave_texture(_taille_xyz, Texture::Niveau::herbe);
}
